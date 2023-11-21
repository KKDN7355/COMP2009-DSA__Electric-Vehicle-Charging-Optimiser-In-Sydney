#ifndef WEIGHTED_GRAPH_TYPE_H_
#define WEIGHTED_GRAPH_TYPE_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>

using namespace std;

class Weighted_Graph_Type {
protected:
	int							vertices;						// Number of vertices.
	vector<vector<int>>			graph;							// Stores adjacency list.
	vector<vector<double>>		weights;						// Stores weights of edges.
	vector<pair<int, double>>	weights_smallest_vector_pair;	// Stores weights of smallest path to each vertex.

public:
	Weighted_Graph_Type();
	Weighted_Graph_Type(int);

	int				get_vertices();
	vector<int>		get_adjancency_list(int);
	double			get_weight(int, int);

	void print_adjacency_list();
	void print_adjacency_matrix();

	vector<pair<int, Path>> shortest_path_find(int);

	
	void vertex_add();
	void vertex_remove(int);

	void edge_add(int, int, double);
	void edge_remove(int, int);
	
};

Weighted_Graph_Type::Weighted_Graph_Type() {
	vertices = 0;
}

Weighted_Graph_Type::Weighted_Graph_Type(int v) {
	ifstream infile;
	char fileName[50] = "Weights.txt";

	infile.open(fileName);

	if (!infile) {
		cout << "Cannot open input file." << endl;
		return;
	}

	vertices = v;

	weights.resize(vertices);
	graph.resize(vertices);

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			double value;
			infile >> value;

			if (value == 0) {
				weights.at(i).push_back(DBL_MAX);
			}
			else {
				weights.at(i).push_back(value);
				graph.at(i).push_back(j);
			}
		}
	}

	infile.close();
}


int Weighted_Graph_Type::get_vertices() {
	return vertices;
}

vector<int> Weighted_Graph_Type::get_adjancency_list(int index) {
	return graph[index];
}

double Weighted_Graph_Type::get_weight(int i, int j) {
	return weights[i][j];
}


void Weighted_Graph_Type::print_adjacency_list() {
	cout << "Adjacency List:" << endl;

	for (int index = 0; index < vertices; index++) {
		cout << index << ": ";

		for (int e : graph[index]) {
			cout << e << " ";
		}

		cout << endl;
	}

	cout << endl;
}

void Weighted_Graph_Type::print_adjacency_matrix() {
	cout << "Adjacency Matrix:" << endl;

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			cout << setw(8) << (weights.at(i).at(j) == DBL_MAX ? 0.0 : weights.at(i).at(j));
		}
		cout << endl;
	}

	cout << endl;
}

bool weights_shortest_path_vector_pair_sorter(pair<int, Path>& a, pair<int, Path>& b) {
	return a.second.path_distance_in_km < b.second.path_distance_in_km;
}

vector<pair<int, Path>> Weighted_Graph_Type::shortest_path_find(int vertex) {
	vector<double>				weights_smallest_vector;
	vector<bool>				weight_found(vertices, false);

	vector<pair<int, Path>>		weights_shortest_path_vector_pair;
	vector<int>					path(vertices, -1);
	
	weights_smallest_vector.resize(vertices);
	
	for (int i = 0; i < vertices; i++) {
		weights_smallest_vector[i] = weights[vertex][i];
	}

	weights_smallest_vector[vertex] = 0;
	weight_found[vertex] = true;

	for (int i = 0; i < vertices - 1; i++) {
		double	weight_min = DBL_MAX;
		int		v;

		for (int j = 0; j < vertices; j++) {
			if (!weight_found[j]) {
				if (weights_smallest_vector[j] < weight_min) {
					v = j;
					weight_min = weights_smallest_vector[v];
				}
			}
		}

		weight_found[v] = true;

		for (int j = 0; j < vertices; j++) {
			if (!weight_found[j]) {
				if (weight_min + weights[v][j] < weights_smallest_vector[j]) {
					weights_smallest_vector[j] = weight_min + weights[v][j];
					path[j] = v;
				}
			}
		}
	}

	for (int i = 0; i < weights_smallest_vector.size(); i++) {
		pair<int, Path>		pair_temp;
		Path				path_temp;
		vector<int>			path_temp_path_vector;

		int current_vertex = i;

		while (current_vertex != -1) {
			path_temp_path_vector.push_back(current_vertex);
			current_vertex = path[current_vertex];
		}

		reverse(path_temp_path_vector.begin(), path_temp_path_vector.end());

		path_temp.path_destination_index = path_temp_path_vector.back();
		path_temp.path = path_temp_path_vector;
		path_temp.path_distance_in_locations = path_temp_path_vector.size();
		path_temp.path_distance_in_km = weights_smallest_vector[i];

		pair_temp.first = i;
		pair_temp.second = path_temp;

		weights_shortest_path_vector_pair.push_back(pair_temp);
	}

	// Now to sort the container based on the path's distance in km.
	sort(weights_shortest_path_vector_pair.begin(), weights_shortest_path_vector_pair.end(), weights_shortest_path_vector_pair_sorter);

	return weights_shortest_path_vector_pair;
}

void Weighted_Graph_Type::vertex_add() {
	int vertex_new = vertices;				// The index of the new vertex.
	vertices++;

	graph.push_back(vector<int>());
	weights.push_back(vector<double>());

	// Setting default weights of 0 for the new vertex.
	for (int i = 0; i < vertices - 1; i++) {
		graph[i].push_back(0);
		weights[i].push_back(0.0);
	}

	// Setting default weights of 0 for each edge.
	for (int i = 0; i < vertices; i++) {
		graph[vertex_new].push_back(0);
		weights[vertex_new].push_back(0.0);
	}
}

void Weighted_Graph_Type::vertex_remove(int vertex_index) {
	// Error Checking
	if (vertex_index >= vertices || vertex_index < 0) {
		cout << "Invalid vertex." << endl;
		return;
	}

	// Removing the vertex from the adjacency list.
	graph.erase(graph.begin() + vertex_index);

	// Removing the vertex from the weighted matrix.
	weights.erase(weights.begin() + vertex_index);

	// Removing the corresponding edges from other vertices.
	for (int i = 0; i < vertices; i++) {
		if (i < graph.size() && vertex_index < graph[i].size()) {
			graph[i].erase(graph[i].begin() + vertex_index);
			weights[i].erase(weights[i].begin() + vertex_index);
		}
	}

	vertices--;
}

void Weighted_Graph_Type::edge_add(int source, int destination, double weight) {
	// Error Checking
	if (source >= vertices || destination >= vertices || source < 0 || destination < 0) {
		cout << "Invalid source or destination vertex." << endl;
	}
	
	cout << "source: " << source << endl;
	cout << "destination: " << destination << endl;

	cout << "graph.at(source): " << graph.at(source).size();

	// graph.at(source).at(destination) = 1;
	// graph.at(destination).at(source) = 1;

	graph[source][destination] = 1;
	graph[destination][source] = 1;

	cout << "source: " << source << endl;
	cout << "destination: " << destination << endl;

	// There is a vector subscript error that occurs past this point.
	weights[source][destination] = weight;
	weights[destination][source] = weight;
}

void Weighted_Graph_Type::edge_remove(int source, int destination) {
	// Error Checking
	if (source >= vertices || destination >= vertices || source < 0 || destination < 0) {
		cout << "Invalid source or destination vertex." << endl;
		return;
	}

	graph[source][destination] = 0;
	graph[destination][source] = 0;

	weights[source][destination] = 0.0;
	weights[destination][source] = 0.0;
}

#endif /* WEIGHTED_GRAPH_TYPE_H_ */