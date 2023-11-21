#ifndef EVC_H_
#define EVC_H_

class EVC {
private:
	map<int, Location>			locations;
	int							locations_number;
	Weighted_Graph_Type			weighted_graph;

public:
	EVC();

	void input_locations();
	void print_locations();
	void print_adjacency_matrix();

	int						get_locations_number();
	Weighted_Graph_Type		get_weighted_graph();

	int	amount_to_charge_randomise();

	// Task 3
	vector<int>			locations_by_price_sort();
	void				locations_by_price_print(vector<int>);

	int					prompt_origin();
	int					prompt_destination(int);
	
	// Task 4
	vector<int>			adjacent_locations_with_charging_station_find(int);
	void				adjacent_locations_with_charging_station_print(int, vector<int>);

	// Task 5
	int					adjacent_location_with_lowest_charging_cost_find(int, int);
	void				adjacent_location_with_lowest_charging_cost_print(int, int, int);

	// Task 6
	pair<int, Path>		nearest_location_with_charging_station_find(int);
	void				nearest_location_with_charging_station_print(int, pair<int, Path>);

	// Task 7
	pair<int, double>	location_with_charging_station_lowest_total_cost_find(int, int);
	void				location_with_charging_station_lowest_total_cost_print(int, int, pair<int, double>);

	// Task 8 & 9
	void				print_best_path(int, int, Path);
	Path				best_path_one(int, int, int);
	Path				best_path_two(int, int, int);

	// Task 10
	int					find_location_index_from_location_name(string);

	void				locations_add();
	void				locations_remove();
	void				path_add();
	void				path_remove();
};

EVC::EVC() {
	input_locations();
	weighted_graph = Weighted_Graph_Type(locations_number);
}

void EVC::input_locations() {
	ifstream infile;
	char fileName[50] = "Locations.txt";

	infile.open(fileName);

	if (!infile) {
		cout << "Cannot open input file." << endl;
		return;
	}

	int location_index = 0;

	while (!infile.eof()) {
		Location l;
		string charger;
		string price;

		while (!infile.eof()) {
			getline(infile, l.name, ',');
			getline(infile, charger, ',');
			getline(infile, price);

			l.index = location_index;
			l.charger_installed = (stoi(charger) == 1) ? true : false;
			l.charging_price = stod(price);
			
			locations[location_index] = l;

			location_index++;
		}
	}

	locations_number = location_index;
}

void EVC::print_locations() {
	cout << "List of Locations and Charging Information: " << endl;

	cout << setw (8) << "Index" << setw (20) << "Location Name" << setw (20) <<"Charging Station" << setw(20) << "Charging Price" << endl;

	map<int, Location>::iterator it;

	for (it = locations.begin(); it != locations.end(); it++) {
		it->second.print();
	}

    cout << endl << endl;
}

void EVC::print_adjacency_matrix() {
	cout << "Adjacency Matrix:" << endl;

	cout << "(zero means no direct connection, non-zero value represents the distance of adjacent locations)" << endl << endl;

	cout << setw(13) << " ";

	for (int i = 0; i < locations_number; i++) {
		cout << setw(13) << locations[i].name;
	}
	cout << endl;

	for (int i = 0; i < locations_number; i++) {
		cout << setw(13) << locations[i].name;
		for (int j = 0; j < locations_number; j++) {
			cout << setw(13) << (weighted_graph.get_weight(i, j) == DBL_MAX ? 0.0 : weighted_graph.get_weight(i, j));
		}
		cout << endl;
	}

	cout << endl << endl;
}



int EVC::get_locations_number() {
	return locations_number;
}

Weighted_Graph_Type EVC::get_weighted_graph() {
	return weighted_graph;
}



int EVC::amount_to_charge_randomise() {
	return rand() % 40 + 10;
}



// Task 3 :)
vector<int> EVC::locations_by_price_sort() {
	priority_queue<Location>	locations_by_price_priority_queue;
	vector<int>					locations_by_price_vector;

	for (const auto& pair : locations) {
		locations_by_price_priority_queue.push(pair.second);
	}

	// Now that the list is sorted by price, let's just hold the indexes.
	while (!locations_by_price_priority_queue.empty()) {
		if (locations_by_price_priority_queue.top().charger_installed) {
			locations_by_price_vector.push_back(locations_by_price_priority_queue.top().index);
		}

		locations_by_price_priority_queue.pop();
	}

	return locations_by_price_vector;
}

void EVC::locations_by_price_print(vector<int> v) {
	cout << "List of Locations and Charging Information:" << endl;
	cout << setw(8) << "Index" << setw(20) << "Location Name" << setw(20) << "Charging Station" << setw(20) << "Charging Price" << endl;

	for (int i = 0; i < v.size(); i++) {
		Location location_temp;
		location_temp = locations[v[i]];
		location_temp.print();
	}

	cout << endl << endl;
}



int EVC::prompt_origin() {
	int		origin_index;
	string	origin_string;

	while (true) {
		cout << "Input Location of Origin: ";
		cin.ignore();
		getline(cin, origin_string);

		cout << endl;

		for (const auto& pair : locations) {
			if (pair.second.name == origin_string) {
				origin_index = pair.second.index;
				return origin_index;
			}
		}

		cout << "Invalid origin. Please try again." << endl;
	}
}

int EVC::prompt_destination(int origin_index) {
	int		destination_index = -1;
	string	destination_string;

	while (true) {
		cout << "Input Location of Destination: ";
		// cin.ignore();
		getline(cin, destination_string);

		cout << endl;

		for (const auto& pair : locations) {
			if (pair.second.name == destination_string) {
				destination_index = pair.second.index;
				if (destination_index == origin_index) {
					cout << "Destination cannot be the same as the origin." << endl << endl;
				}
				else {
					return destination_index;
				}
			}
		}

		cout << "Invalid destination. Please try again." << endl;
	}
}



// Task 4 :)
vector<int> EVC::adjacent_locations_with_charging_station_find(int origin_index) {
	vector<int>			adjacent_locations_vector;
	vector<int>			adjacent_locations_with_charging_station_vector;

	adjacent_locations_vector = weighted_graph.get_adjancency_list(origin_index);

	for (int i = 0; i < adjacent_locations_vector.size(); i++) {
		if (locations[adjacent_locations_vector[i]].charger_installed) {
			adjacent_locations_with_charging_station_vector.push_back(adjacent_locations_vector[i]);
		}
	}

	return adjacent_locations_with_charging_station_vector;
}

void EVC::adjacent_locations_with_charging_station_print(int origin_index, vector<int> v) {
	cout << "Adjacent Locations With Charging Station for " << locations[origin_index].name << ": " << endl;

	if (v.empty()) {
		cout << "NONE." << endl;
	}
	else {
		cout << setw(8) << "Index" << setw(20) << "Location Name" << setw(20) << "Charging Station" << setw(20) << "Charging Price" << endl;

		for (int i = 0; i < v.size(); i++) {
			Location location_temp;
			location_temp = locations[v[i]];
			location_temp.print();
		}
	}
	cout << endl << endl;
}

// Task 5 :)
int EVC::adjacent_location_with_lowest_charging_cost_find(int origin_index, int amount_to_charge) {
	vector<int> adjacent_locations_with_charging_station_vector = adjacent_locations_with_charging_station_find(origin_index);

	// Now to sort the vector in ascending order of charging price.
	sort(adjacent_locations_with_charging_station_vector.begin(), adjacent_locations_with_charging_station_vector.end(),
		[this](int a, int b) {
			return locations[a].charging_price < locations[b].charging_price;
		});

	for (int i = 0; i < adjacent_locations_with_charging_station_vector.size(); i++) {
		// Now to check the amount to charge, because if we need to charge over 25kWh, it means we cannot use a free charging station due to its limits.
		if (amount_to_charge > free_charging_station_limit && locations[adjacent_locations_with_charging_station_vector[i]].charging_price == 0) {
			continue;
		}
		else {
			return adjacent_locations_with_charging_station_vector[i];
		}
	}

	return -1;
}

void EVC::adjacent_location_with_lowest_charging_cost_print(int origin_index, int amount_to_charge, int destination_index) {
	cout << "Adjacent Location With Lowest Charging Cost for " << locations[origin_index].name << ": " << endl;
	cout << "(assuming that the charging amount is " << amount_to_charge << "kWh)" << endl << endl;

	if (destination_index == -1) {
		cout << "NONE." << endl;
	}
	else {
		cout << setw(8) << "Index" << setw(20) << "Location Name" << setw(20) << "Charging Station" << setw(20) << "Charging Price" << endl;
		locations[destination_index].print();
	}

	cout << endl << endl;
}

// Task 6 :)
pair<int, Path> EVC::nearest_location_with_charging_station_find(int origin_index) {
	// Make vector that holds all the shortest paths to each vertex. Note that this is already sorted in ascending order based on their distance to the vertex_index.
	vector<pair<int, Path>> shortest_path_vector = weighted_graph.shortest_path_find(origin_index);

	// Time to find the shortest path with a charging station.
	for (int i = 0; i < shortest_path_vector.size(); i++) {
		// Skip if self.
		if (shortest_path_vector[i].first == origin_index) {
			continue;
		}
		// Skip if no charging station.
		if (!locations[shortest_path_vector[i].first].charger_installed) {
			continue;
		}
		else {
			return shortest_path_vector[i];
		}
	}
	return make_pair(-1, Path{});
}

void EVC::nearest_location_with_charging_station_print(int origin_index, pair<int, Path> destination_index_path_pair) {
	cout << "Nearest Location With Charging Station for " << locations[origin_index].name << ": " << endl;

	if (destination_index_path_pair.first == -1) {
		cout << "NONE." << endl;
	}

	cout << setw(8) << "Index" << setw(20) << "Location Name" << setw(20) << "Charging Station" << setw(20) << "Charging Price" << endl;
	locations[destination_index_path_pair.second.path_destination_index].print();
	cout << "(at a distance of " << destination_index_path_pair.second.path_distance_in_km << "km)" << endl << endl;
}

// Task 7 :)
pair<int, double> EVC::location_with_charging_station_lowest_total_cost_find(int origin_index, int amount_to_charge) {
	// Make vector that holds all the shortest paths to each vertex. Note that this is already sorted in ascending order based on their distance to the vertex_index.
	vector<pair<int, Path>>		shortest_path_vector = weighted_graph.shortest_path_find(origin_index);
	int							destination_index_lowest;
	double						cost_total_lowest = DBL_MAX;

	for (int i = 0; i < shortest_path_vector.size(); i++) {
		int			location_temp_index;
		Location	location_temp;

		double		charge_rate;
		double		cost_total_temp;

		location_temp_index = shortest_path_vector[i].first;
		location_temp = locations[location_temp_index];
		charge_rate = location_temp.charging_price;
		
		// Skip if self.
		if (location_temp.index == origin_index) {
			continue;
		}
		// Skip if no charging station.
		if (!location_temp.charger_installed) {
			continue;
		}
		// Skip if charging station is not suitable due to amount to charge.
		if (amount_to_charge > free_charging_station_limit && location_temp.charging_price == 0) {
			continue;
		}
		// Calculate total cost for comparing.
		cost_total_temp = shortest_path_vector[i].second.path_distance_in_km * 2 * travel_cost_per_km + amount_to_charge * charge_rate;

		// Now to compare.
		if (cost_total_temp < cost_total_lowest) {
			destination_index_lowest = location_temp_index;
			cost_total_lowest = cost_total_temp;
		}
	}

	// Store information as a pair that holds: output_index, the total cost of the trip.
	return make_pair(destination_index_lowest, cost_total_lowest);
}

void EVC::location_with_charging_station_lowest_total_cost_print(int origin_index, int amount_to_charge, pair<int, double> destination_index_cost_pair) {
	cout << "Location With Charging Station With The Lowest Total Cost for " << locations[origin_index].name << ": " << endl;
	cout << "(assuming that the charging amount is " << amount_to_charge << "kWh)" << endl << endl;
	cout << setw(8) << "Index" << setw(20) << "Location Name" << setw(20) << "Charging Station" << setw(20) << "Charging Price" << endl;
	locations[destination_index_cost_pair.first].print();
	cout << "(at a total cost of $" << destination_index_cost_pair.second << ")" << endl << endl;
}

// Task 8 & 9 :)
void EVC::print_best_path(int origin_index, int amount_to_charge, Path p) {
	cout << "The best path, if you want to travel from " << locations[origin_index].name << " to " << locations[p.path_destination_index].name << " is as follows:" << endl;
	cout << "(assuming that the charging amount is " << amount_to_charge << "kWh)" << endl << endl;

	cout << setw(8) << "Index" << setw(20) << "Location Name" << setw(20) << "Charging Station" << setw(20) << "Charging Price" << endl;

	for (int i = 0; i < p.path_distance_in_locations; i++) {
		Location location_temp;
		location_temp = locations[p.path[i]];

		if (location_temp == p.location_to_charge_a) {
			cout << endl;
			cout << setw(67) << "**** **** **** **** **** **** **** **** **** **** **** **** ****" << endl;
			location_temp.print();
			cout << setw(67) << "**** **** **** **** **** **** **** **** **** **** **** **** ****" << endl;
			cout << endl;
		}
		else if (location_temp == p.location_to_charge_b) {
			cout << endl;
			cout << setw(67) << "**** **** **** **** **** **** **** **** **** **** **** **** ****" << endl;
			location_temp.print();
			cout << setw(67) << "**** **** **** **** **** **** **** **** **** **** **** **** ****" << endl;
			cout << endl;
		}
		else {
			location_temp.print();
		}
	}

	cout << endl;

	cout << "Summary of Trip: " << endl;
	cout << "- Started At:  " << locations[origin_index].name << endl;

	if (p.amount_to_charge_b) {
		cout << "- Charged At:  " << endl;
		cout << "  * " << p.location_to_charge_a.name << " for " << p.amount_to_charge_a << "kWh" << endl;
		cout << "  * " << p.location_to_charge_b.name << " for " << p.amount_to_charge_b << "kWh" << endl;
	}
	else {
		cout << "- Charged At:  " << p.location_to_charge_a.name << " for " << p.amount_to_charge_a << "kWh" << endl;
	}

	cout << "- Ended Up At: " << locations[p.path_destination_index].name << endl;
	
	cout << "- Total Cost of Travelling... $" << p.cost_travel << endl;
	cout << "- Total Cost of Charging..... $" << p.cost_charge << endl;
	cout << "- Total Cost of Trip......... $" << p.cost_total << endl;

	cout << endl << endl;
}

Path EVC::best_path_one(int origin_index, int amount_to_charge, int destination_index) {
	// Make vector that holds all the shortest paths to each vertex. Note that this is already sorted in ascending order based on their distance to the vertex_index.
	vector<pair<int, Path>>		shortest_path_vector_a = weighted_graph.shortest_path_find(origin_index);
	
	Path		path_temp_a;
	Path		path_temp_b;
	Location	location;
	double		cost_travel = 0;
	double		cost_charge = 0;
	double		cost_total = DBL_MAX;

	for (int i = 0; i < shortest_path_vector_a.size(); i++) {
		pair<int, Path>		pair_temp_a;
		pair<int, Path>		pair_temp_b;

		Location			location_temp;
		double				cost_travel_temp;
		double				cost_charge_temp;
		double				cost_total_temp;

		// Iterating through container to find an appropriate location with an appropriate charging station.
		location_temp = locations[shortest_path_vector_a[i].second.path_destination_index];

		// Skip if no charging station.
		if (!location_temp.charger_installed) {
			continue;
		}
		// Skip if charging station is not suitable for amount to charge.
		if (amount_to_charge > free_charging_station_limit && location_temp.charging_price == 0) {
			continue;
		}

		// At this point, the chosen location is viable.
		pair_temp_a = shortest_path_vector_a[i];

		// Time to find the path to the destination.
		vector<pair<int, Path>> shortest_path_vector_b = weighted_graph.shortest_path_find(location_temp.index);

		for (int j = 0; j < shortest_path_vector_b.size(); j++) {
			if (shortest_path_vector_b[j].second.path_destination_index == destination_index) {
				pair_temp_b = shortest_path_vector_b[j];
			}
		}

		// Calculate the total cost.
		cost_travel_temp = (pair_temp_a.second.path_distance_in_km + pair_temp_b.second.path_distance_in_km) * travel_cost_per_km;
		cost_charge_temp = amount_to_charge * location_temp.charging_price;
		cost_total_temp = cost_travel_temp + cost_charge_temp;

		// Compare.
		if (cost_total_temp < cost_total) {
			path_temp_a = pair_temp_a.second;
			path_temp_b = pair_temp_b.second;
			location = location_temp;
			cost_travel = cost_travel_temp;
			cost_charge = cost_charge_temp;
			cost_total = cost_total_temp;
		}
	}

	vector<int> vector;
	vector.insert(vector.end(), path_temp_a.path.begin(), path_temp_a.path.end());
	vector.insert(vector.end(), path_temp_b.path.begin(), path_temp_b.path.end());

	double path_distance_in_km_temp = 0;
	path_distance_in_km_temp = path_distance_in_km_temp + path_temp_a.path_distance_in_km + path_temp_b.path_distance_in_km;

	Path path_temp;
	path_temp.path_destination_index = destination_index;
	path_temp.path = vector;
	path_temp.path_distance_in_locations = vector.size();
	path_temp.path_distance_in_km = path_distance_in_km_temp;
	path_temp.location_to_charge_a = location;
	path_temp.amount_to_charge_a = amount_to_charge;
	path_temp.cost_travel = cost_travel;
	path_temp.cost_charge = cost_charge;
	path_temp.cost_total = cost_total;

	return path_temp;
}

Path EVC::best_path_two(int origin_index, int amount_to_charge, int destination_index) {
	if (amount_to_charge <= free_charging_station_limit) {
		Path path_temp = best_path_one(origin_index, amount_to_charge, destination_index);
		return path_temp;
	}
	else {
		Path		path_temp_a;
		Path		path_temp_b;
		Path		path_temp_c;
		Location	location_a;
		Location	location_b;
		int			amount_to_charge_a = 0;
		int			amount_to_charge_b = 0;
		double		cost_travel = 0;
		double		cost_charge = 0;
		double		cost_total = DBL_MAX;

		// Make vector that holds all the shortest paths to each vertex. Note that this is already sorted in ascending order based on their distance to the vertex_index.
		vector<pair<int, Path>>		shortest_path_vector_a = weighted_graph.shortest_path_find(origin_index);

		for (int i = 0; i < shortest_path_vector_a.size(); i++) {
			pair<int, Path>		pair_temp_a;
			pair<int, Path>		pair_temp_b;
			pair<int, Path>		pair_temp_c;

			Location			location_temp_a;
			Location			location_temp_b;
			int					amount_to_charge_a_temp = 0;
			int					amount_to_charge_b_temp = 0;
			double				cost_travel_temp = 0.0;
			double				cost_charge_temp = 0.0;
			double				cost_total_temp = 0.0;

			// Iterating through container to find an appropriate location with an appropriate charging station.
			location_temp_a = locations[shortest_path_vector_a[i].second.path_destination_index];

			// Skip if no charging station.
			if (!location_temp_a.charger_installed) {
				continue;
			}

			// At this point, the chosen location is viable.
			pair_temp_a = shortest_path_vector_a[i];

			// Time to find the path to the second charging station.
			vector<pair<int, Path>> shortest_path_vector_b = weighted_graph.shortest_path_find(location_temp_a.index);

			for (int j = 0; j < shortest_path_vector_b.size(); j++) {
				// Iterating through container to find an appropriate location with an appropriate charging station.
				location_temp_b = locations[shortest_path_vector_b[j].second.path_destination_index];

				// Skip if same as first chosen location.
				if (location_temp_b.index == location_temp_a.index) {
					continue;
				}
				// Skip if no charging station.
				if (!location_temp_b.charger_installed) {
					continue;
				}

				// At this point, the second chosen location is viable.
				pair_temp_b = shortest_path_vector_b[j];

				// Both charging stations are now acceptable, time to find the path from second charging station to the destination.
				vector<pair<int, Path>> shortest_path_vector_c = weighted_graph.shortest_path_find(location_temp_b.index);

				for (int k = 0; k < shortest_path_vector_c.size(); k++) {
					if (shortest_path_vector_c[k].second.path_destination_index == destination_index) {
						pair_temp_c = shortest_path_vector_c[k];
					}
				}

				// Determining how much to charge at each spot.
				amount_to_charge_a_temp = 0;
				amount_to_charge_b_temp = 0;

				if (location_temp_a.charging_price == 0) {
					amount_to_charge_a_temp = free_charging_station_limit;
					amount_to_charge_b_temp = amount_to_charge - amount_to_charge_a_temp;
				}
				else if (location_temp_b.charging_price == 0) {
					amount_to_charge_b_temp = free_charging_station_limit;
					amount_to_charge_a_temp = amount_to_charge - amount_to_charge_b_temp;
				}
				else if (location_temp_a.charging_price < location_temp_b.charging_price) {
					amount_to_charge_a_temp = amount_to_charge;
					amount_to_charge_b_temp = 0;
				}
				else if (location_temp_a.charging_price > location_temp_b.charging_price) {
					amount_to_charge_b_temp = amount_to_charge;
					amount_to_charge_a_temp = 0;
				}
				// Apparently I'm not pessimistic enough and spent hours to come up with this next block. :)
				else if (location_temp_a.charging_price == location_temp_b.charging_price) {
					amount_to_charge_a_temp = amount_to_charge / 2;
					amount_to_charge_b_temp = amount_to_charge / 2;
				}
				// Calculate total cost.
				cost_travel_temp = (pair_temp_a.second.path_distance_in_km + pair_temp_b.second.path_distance_in_km + pair_temp_c.second.path_distance_in_km) * travel_cost_per_km;
				cost_charge_temp = (amount_to_charge_a_temp * location_temp_a.charging_price) + (amount_to_charge_b_temp * location_temp_b.charging_price);
				cost_total_temp = cost_travel_temp + cost_charge_temp;

				// Compare.
				if (cost_total_temp < cost_total) {
					path_temp_a = pair_temp_a.second;
					path_temp_b = pair_temp_b.second;
					path_temp_c = pair_temp_c.second;
					location_a = location_temp_a;
					location_b = location_temp_b;
					amount_to_charge_a = amount_to_charge_a_temp;
					amount_to_charge_b = amount_to_charge_b_temp;
					cost_travel = cost_travel_temp;
					cost_charge = cost_charge_temp;
					cost_total = cost_total_temp;
				}
			}
		}

		vector<int> vector;
		vector.insert(vector.end(), path_temp_a.path.begin(), path_temp_a.path.end());
		vector.insert(vector.end(), path_temp_b.path.begin(), path_temp_b.path.end());
		vector.insert(vector.end(), path_temp_c.path.begin(), path_temp_c.path.end());

		double path_distance_in_km_temp = 0;
		path_distance_in_km_temp = path_distance_in_km_temp + path_temp_a.path_distance_in_km + path_temp_b.path_distance_in_km + path_temp_c.path_distance_in_km;

		Path path_temp;
		path_temp.path_destination_index = destination_index;
		path_temp.path = vector;
		path_temp.path_distance_in_locations = vector.size();
		path_temp.path_distance_in_km = path_distance_in_km_temp;
		path_temp.location_to_charge_a = location_a;
		path_temp.location_to_charge_b = location_b;
		path_temp.amount_to_charge_a = amount_to_charge_a;
		path_temp.amount_to_charge_b = amount_to_charge_b;
		path_temp.cost_travel = cost_travel;
		path_temp.cost_charge = cost_charge;
		path_temp.cost_total = cost_total;

		return path_temp;
	}
}



// Task 10
int EVC::find_location_index_from_location_name(string location_name) {
	for (const auto& pair : locations) {
		if (pair.second.name == location_name) {
			return pair.second.index;
		}
	}
}

void EVC::locations_add() {
	Location	l;
	int			location_index;
	string		location_name;
	int			charger_installed_a;
	bool		charger_installed_b;
	double		charger_price;

	location_index = locations_number;

	cout << "Name of the location to add: ";
	cin >> location_name;

	cout << "And will there be a charger installed at this location? (0 for No and 1 for Yes) ";
	cin >> charger_installed_a;

	charger_installed_b = (charger_installed_a == 1) ? true : false;

	if (charger_installed_b) {
		cout << "And what will the price of the charger be (kWh)? ";
		cin >> charger_price;
	}
	else {
		charger_price = DBL_MAX;
	}

	// Time to set the things and then add to the map.
	l.index = location_index;
	l.name = location_name;
	l.charger_installed = charger_installed_b;
	l.charging_price = charger_price;

	locations[location_index] = l;
	locations_number++;

	weighted_graph.vertex_add();
}

void EVC::locations_remove() {
	int			location_index;
	string		location_name;

	location_index = -1;

	cout << "Name of the location to remove: ";
	cin >> location_name;

	location_index = find_location_index_from_location_name(location_name);

	// Remove from map.
	map<int, Location>::iterator it = locations.begin();
	advance(it, location_index);
	locations.erase(it);

	// Shifting elements from behind the removed element.
	map<int, Location> locations_temp;

	for (const auto& pair : locations) {
		int key_old = pair.first;

		if (key_old > location_index) {
			int key_new = key_old - 1;
			Location l = pair.second;
			l.index = l.index - 1;
			locations_temp[key_new] = l;
		}
		else {
			Location l = pair.second;
			locations_temp[key_old] = l;
		}
	}

	locations = move(locations_temp);

	locations_number--;

	weighted_graph.vertex_remove(location_index);
}

void EVC::path_add() {
	string	location_a_name;
	string	location_b_name;
	int		location_a_index;
	int		location_b_index;
	double	distance_in_km;

	cout << "What locations would you like to link with a path?" << endl;
	cout << "Location [1]: ";
	cin >> location_a_name;

	cout << "Location [2]: ";
	cin >> location_b_name;

	cout << "And how long is this path (km)? ";
	cin >> distance_in_km;

	// Converting strings to integers.
	location_a_index = find_location_index_from_location_name(location_a_name);
	location_b_index = find_location_index_from_location_name(location_b_name);

	weighted_graph.edge_add(location_a_index, location_b_index, distance_in_km);
}

void EVC::path_remove() {

}

#endif /* EVC_H_ */