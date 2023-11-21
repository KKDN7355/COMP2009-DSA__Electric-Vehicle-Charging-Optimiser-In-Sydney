#ifndef PATH_H_
#define PATH_H_

class Path {
public:
	int				path_destination_index;			// Index of the path's destination.
	vector<int>		path;							// Container to hold the index of each location along the way from initial to destination.
	int				path_distance_in_locations;		// The distance represented in number of locations along the way.
	double			path_distance_in_km;			// The distance represented in number of kilometres.

	Location		location_to_charge_a;			// The index of the first location to charge at.
	Location		location_to_charge_b;			// The index of the second location to charge at.

	int				amount_to_charge_a;				// The amount to charge at the first location.
	int				amount_to_charge_b;				// The amount to charge at the second location.

	double			cost_travel;					// The total cost of the travel.
	double			cost_charge;					// The total cost of the charging.
	double			cost_total;						// The total cost of the path.

	Path() {

	}

	bool operator<(const Path& p)  const {
		return cost_total < p.cost_total;
	}
};

#endif /* PATH_H_ */