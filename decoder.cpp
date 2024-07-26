#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include "brkga.h"
using std::vector;

vector<vector<int>>::size_type graphSize(vector<vector<int>> graph)
{
    vector<int> vertex_vector;
    for (auto edge : graph) {
        for (auto vertex : edge) {
	        if (std::find(vertex_vector.begin(), vertex_vector.end(), vertex) == vertex_vector.end())
	            vertex_vector.push_back(vertex);
	    }
    }
    return vertex_vector.size();
}

vector<int> neighbouringVertex(vector<vector<int>> graph, int vertex)
{
    vector<int> neighbours;
    for (auto edge : graph) {
        auto found_vertex = std::find(edge.begin(), edge.end(), vertex);
        if (found_vertex != edge.end()) {
            auto neighbouring_vertex = edge.begin() + (1 - (found_vertex-edge.begin()));
            neighbours.push_back(*neighbouring_vertex);
        }
    }
    return neighbours;
}	

vector<int> sortedIndexes(vector<float> v)
{
    vector<int> indexes;
    for (int i = 0; i != v.size(); ++i) {
 	    auto max_value = std::max_element(v.begin(), v.end());
        int index = max_value - v.begin();
	    indexes.push_back(index);
        *max_value = 0;
    }
    return indexes;
}

std::tuple<int, vector<int>> decoder(vector<vector<int>> graph, vector<float> key)
{
    vector<int> burning_sequence;
    vector<int> burning_vertex;
    vector<int> indexes = sortedIndexes(key);
    vector<int>::iterator index = indexes.begin();

    int turns = 0;
    while (burning_vertex.size() != graphSize(graph)) {
        for (auto vertex : burning_vertex) {
            for (auto neighbour : neighbouringVertex(graph, vertex)) {
                if (std::find(burning_vertex.begin(), burning_vertex.end(), neighbour) == burning_vertex.end())
                    burning_vertex.push_back(neighbour);
	        }
	    }	
        while (find(burning_vertex.begin(), burning_vertex.end(), *index) != burning_vertex.end())
            index++;
        if (indexes.end()-index > 0) {
            burning_sequence.push_back(*index);
            burning_vertex.push_back(*index);
        }
        turns++;
    }
    return { turns, burning_sequence };
}

int main()
{
    vector<vector<int>> graph{ { 0, 1 }, 
                               { 0, 2 },
                               { 0, 3 },
                               { 1, 2 },
                               { 1, 4 },
                               { 2, 4 },
                               { 2, 5 },
                               { 4, 8 },
                               { 4, 6 },
                               { 5, 7 },
                               { 7, 8 },
                               { 7, 9 }};
    
    vector<vector<int>>::size_type size = graphSize(graph);
    vector<float> random_key1 = createRandomVector(size);
    vector<float> random_key2 = createRandomVector(size);
    vector<float> mutated = mutation(random_key1, random_key2);
    printVector(mutated);
    std::tuple<int, vector<int>> burning_sequence = decoder(graph, mutated);
    for (auto i : std::get<1>(burning_sequence))
	    std::cout << i << " ";
    std::cout << std::endl << std::get<0>(burning_sequence) << std::endl;
}
