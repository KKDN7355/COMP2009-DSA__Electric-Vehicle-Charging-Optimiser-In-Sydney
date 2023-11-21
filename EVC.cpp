#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <map>
#include <ctime>
#include <algorithm>

using namespace std;

#include "Constants.h"
#include "Location.h"
#include "Path.h"
#include "Weighted_Graph_Type.h"
#include "EVC.h"

int main() {
	srand((unsigned)time(NULL));

	cout << "Electric Vehicle Charging Tasks:" << endl;
	cout << "00) Exit program." << endl;
	cout << "01) Print locations." << endl;
	cout << "02) Print adjacency matrix." << endl;
	cout << "03) Task 03 - List all locations with charging stations in ascending order of charging price." << endl;
	cout << "04) Task 04 - List all adjacent locations with charging stations in ascending order of charging price." << endl;
	cout << "05) Task 05 - Find adjacent location with lowest charging cost." << endl;
	cout << "06) Task 06 - Find nearest location with a charging station." << endl;
	cout << "07) Task 07 - Find a location with the lowest total cost of travelling and charging." << endl;
	cout << "08) Task 08 - Find a path from origin to destination that will yield the lowest total cost of travelling and charging." << endl;
	cout << "09) Task 09 - Task 08 but permit more than one charging station." << endl;
	cout << "10) Task 10 - Allow for the adding and deleting of vertices and edges." << endl;

	cout << endl;

	cout << "Pick a task from above: ";

	EVC evc;

	int choice_a;
	cin >> choice_a;

	cout << endl;

	// evc.print_locations();
	// evc.print_adjacency_matrix();

	switch (choice_a) {
		case 0:
		{
			return 0;
		}
		case 1:
		{
			evc.print_locations();
			break;
		}
		case 2:
		{
			evc.print_adjacency_matrix();
			break;
		}
		case 3:
		{
			evc.locations_by_price_print(evc.locations_by_price_sort());
			break;
		}
		case 4:
		{
			for (int i = 0; i < evc.get_locations_number(); i++) {
				vector<int> j = evc.adjacent_locations_with_charging_station_find(i);
				evc.adjacent_locations_with_charging_station_print(i, j);
			}
			break;
		}
		case 5:
		{
			int i = evc.prompt_origin();
			int j = evc.amount_to_charge_randomise();
			int k = evc.adjacent_location_with_lowest_charging_cost_find(i, j);

			evc.adjacent_location_with_lowest_charging_cost_print(i, j, k);

			/*
			for (int i = 0; i < evc.get_locations_number(); i++) {
				int k = evc.adjacent_location_with_lowest_charging_cost_find(i, j);
				evc.adjacent_location_with_lowest_charging_cost_print(i, j, k);
			}
			*/
			break;
		}
		case 6:
		{
			int				i = evc.prompt_origin();
			pair<int, Path> j = evc.nearest_location_with_charging_station_find(i);

			evc.nearest_location_with_charging_station_print(i, j);
			
			/*
			for (int i = 0; i < evc.get_locations_number(); i++) {
				pair<int, Path> j = evc.nearest_location_with_charging_station_find(i);
				evc.nearest_location_with_charging_station_print(i, j);
			}
			*/
			break;
		}
		case 7:
		{
			int					i = evc.prompt_origin();
			int					j = evc.amount_to_charge_randomise();
			pair<int, double>	k = evc.location_with_charging_station_lowest_total_cost_find(i, j);

			evc.location_with_charging_station_lowest_total_cost_print(i, j, k);

			/*
			for (int i = 0; i < evc.get_locations_number(); i++) {
				pair<int, double> k = evc.location_with_charging_station_lowest_total_cost_find(i, j);
				evc.location_with_charging_station_lowest_total_cost_print(i, j, k);
			}
			*/
			break;
		}
		case 8:
		{
			int		i = evc.prompt_origin();
			int		j = evc.amount_to_charge_randomise();
			int		k = evc.prompt_destination(i);
			Path	l = evc.best_path_one(i, j, k);

			evc.print_best_path(i, j, l);

			/*
			for (int i = 0; i < evc.get_locations_number(); i++) {
				for (int k = 0; k < evc.get_locations_number(); k++) {
					if (i == k) {
						continue;
					}
					else {
						Path l = evc.best_path_one(i, j, k);
						evc.print_best_path(i, j, l);
					}
				}
			}
			*/
			break;
		}
		case 9:
		{
			int		i = evc.prompt_origin();
			int		j = evc.amount_to_charge_randomise();
			int		k = evc.prompt_destination(i);
			Path	l = evc.best_path_two(i, j, k);

			evc.print_best_path(i, j, l);

			/*
			for (int i = 0; i < evc.get_locations_number(); i++) {
				for (int k = 0; k < evc.get_locations_number(); k++) {
					if (i == k) {
						continue;
					}
					else {
						Path l = evc.best_path_two(i, j, k);
						evc.print_best_path(i, j, l);
					}
				}
			}
			*/
			break;
		}
		case 10:
		{
			int choice_b;

			do {
				cout << "Which of the following tasks would you like to perform?" << endl;
				cout << "0) None of the below." << endl;
				cout << "1) Vertex Addition." << endl;
				cout << "2) Vertex Subtraction." << endl;
				cout << "3) Edge Addition." << endl;
				cout << "4) Edge Subtraction." << endl;
				cout << endl;
				cout << "Pick a task from above: ";

				cin >> choice_b;

				switch (choice_b) {
					case 0:
					{
						break;
					}
					case 1:
					{
						evc.locations_add();
						cout << endl;
						break;
					}
					case 2:
					{
						evc.locations_remove();
						cout << endl;
						break;
					}
					case 3:
					{
						evc.path_add();
						cout << endl;
						break;
					}
					case 4:
					{

						cout << endl;
						break;
					}
				}

				evc.print_locations();
				evc.print_adjacency_matrix();
			} while (choice_b != 0);
		}
		
	}

	return 0;
}