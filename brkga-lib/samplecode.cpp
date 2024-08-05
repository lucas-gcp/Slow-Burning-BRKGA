#include <iostream>
#include <fstream>
#include "graph.h"
#include "BurningDecoder.h"
#include "MTRand.h"
#include "BRKGA.h"

vector<int> parseLine(std::string line)
{
	vector<int> parsed_line;
	std::string parser;
	for (auto i: line) {
		if (i != ' ') {
			parser.push_back(i);
		} else {
			parsed_line.push_back(stoi(parser));
			parser = std::string();
		}
	}
	parsed_line.push_back(stoi(parser));
	return parsed_line;
}

vector<int> readGraphInfo(std::string filepath)
{
	std::ifstream graph_txt(filepath);
	vector<int> info;
	std::string line;
	std::getline(graph_txt, line);
	info = parseLine(line);
	return info;
}

vector<vector<int>> readGraph(std::string filepath)
{
	std::ifstream graph_txt(filepath);
	vector<vector<int>> graph;
	std::string line;
	std::getline(graph_txt, line);
	while (std::getline(graph_txt, line))
		graph.push_back(parseLine(line));
	return graph;
}

int main(int argc, char* argv[]) {
	std::string graph_path = "./graph.txt";
	vector<int> graph_info(readGraphInfo(graph_path));
	vector<vector<int>> graph(readGraph(graph_path));

	const unsigned n = graphSize(graph);  // size of chromosomes
	const unsigned p = 100;				  // size of population
	const double pe = 0.20;				  // fraction of population to be the elite-set
	const double pm = 0.10;				  // fraction of population to be replaced by mutants
	const double rhoe = 0.70;			  // probability that offspring inherit an allele from elite parent
	const unsigned K = 3;				  // number of independent populations
	const unsigned MAXT = 1;			  // number of threads for parallel decoding
	

	BurningDecoder decoder(graph);		// initialize the decoder
	
	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);				// initialize the random number generator
	
	std::cout << "Antes" << std::endl;
	// initialize the BRKGA-based heuristic
	BRKGA< BurningDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
	std::cout << "Depois" << std::endl;
	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 50;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 200;	// run for 1000 gens
	do {
		std::cout << "Working on generation: " << generation << std::endl;
		algorithm.evolve();	// evolve the population for one generation

		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}
	} while (generation < MAX_GENS);
	
	std::cout << "Best solution found has objective value = "
	 		<< algorithm.getBestFitness() << std::endl;
	
	return 0;
}