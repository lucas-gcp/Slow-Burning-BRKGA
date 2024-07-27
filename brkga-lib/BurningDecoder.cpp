/*
 * BurningDecoder.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: rtoso
 */

#include <iostream>
#include "BurningDecoder.h"
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

vector<int> sortedIndexes(vector<double> v)
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

BurningDecoder::BurningDecoder(vector<vector<int>> g) { 

    this->graph = g;

}

BurningDecoder::~BurningDecoder() { }


double BurningDecoder::decode(const std::vector< double >& chromosome) const {
	// std::vector< std::pair< double, unsigned > > ranking(chromosome.size());

	// for(unsigned i = 0; i < chromosome.size(); ++i) {
	// 	ranking[i] = std::pair< double, unsigned >(chromosome[i], i);
	// }

	// // Here we sort 'permutation', which will then produce a permutation of [n] in pair::second:
	// std::sort(ranking.begin(), ranking.end());

	// // permutation[i].second is in {0, ..., n - 1}; a permutation can be obtained as follows
	// std::list< unsigned > permutation;
	// for(std::vector< std::pair< double, unsigned > >::const_iterator i = ranking.begin();
	// 		i != ranking.end(); ++i) {
	// 	permutation.push_back(i->second);
	// }

	// // sample fitness is the first allele
	// return chromosome.front();

    std::vector<int> burning_sequence;
    vector<int> burning_vertex;
    vector<int> indexes = sortedIndexes(chromosome);
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
        // for (auto i : burning_vertex)
        //     std::cout << i << " ";
        //  std::cout << std::endl;
    }

    return (double) turns;

}
