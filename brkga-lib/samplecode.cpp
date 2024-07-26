#include <iostream>
#include "BurningDecoder.h"
#include "MTRand.h"
#include "BRKGA.h"

int main(int argc, char* argv[]) {

	const unsigned n = 100;		// size of chromosomes
	const unsigned p = 1000;	// size of population
	const double pe = 0.20;		// fraction of population to be the elite-set
	const double pm = 0.10;		// fraction of population to be replaced by mutants
	const double rhoe = 0.70;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 2;	// number of threads for parallel decoding
	
    std::vector<std::vector<int>> graph{ { 0, 1 }, 
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

	BurningDecoder decoder(graph);			// initialize the decoder
	
	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);				// initialize the random number generator
	
	std::cout << "Antes" << std::endl;
	// initialize the BRKGA-based heuristic
	BRKGA< BurningDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
	std::cout << "Depois" << std::endl;
	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 1000;	// run for 1000 gens
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