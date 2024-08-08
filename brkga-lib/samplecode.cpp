#include <iostream>
#include "graph.h"
#include "BurningDecoder.h"
#include "MTRand.h"
#include "BRKGA.h"

int main(int argc, char* argv[]) {
	std::string graph_path = (std::string)argv[1];
	vector<int> graph_info(readGraphInfo(graph_path));
	vector<vector<int>> graph(readGraph(graph_path));

	const unsigned n = graph_info[0];	  // size of chromosomes
	const unsigned p = 100;				  // size of population
	const double pe = 0.20;				  // fraction of population to be the elite-set
	const double pm = 0.10;				  // fraction of population to be replaced by mutants
	const double rhoe = 0.70;			  // probability that offspring inherit an allele from elite parent
	const unsigned K = 3;				  // number of independent populations
	const unsigned MAXT = 2;			  // number of threads for parallel decoding
	

	BurningDecoder decoder(graph);		// initialize the decoder
	
	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);				// initialize the random number generator
	
	// initialize the BRKGA-based heuristic
	BRKGA< BurningDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 50;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 200;	// run for 1000 gens
	do {
		algorithm.evolve();	// evolve the population for one generation

		std::cout << "Generation " << generation << " best solution found has objective value = "
	 			<< algorithm.getBestFitness() << std::endl;

		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}
	} while (generation < MAX_GENS);
	
	vector<int> burning_sequence(decoder.getBurningSequence(algorithm.getBestChromosome()));
	std::cout << "Best solution found has objective value = "
	 		<< algorithm.getBestFitness() << "\n"
			<< "and burning sequence is: ";
	for (auto i : burning_sequence)
		std::cout << i << " ";
	std::cout << std::endl;

	return 0;
}
