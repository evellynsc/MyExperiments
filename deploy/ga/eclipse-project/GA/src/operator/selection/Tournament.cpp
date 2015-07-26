/*
 * Tournament.cpp
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#include "Tournament.h"

Tournament::Tournament(unsigned int size) {
	this->size = size;
}

Tournament::~Tournament() {
	// TODO Auto-generated destructor stub
}

Individual Tournament::run(vector<Individual> population) {
	int index;
	vector<Individual> pool;

	for(unsigned i  = 0; i < this->size; i++) {
		index = Randomize::generate_long() % population.size();
//		index = rand() % population.size();
		pool.push_back(population[index]);
	}

	Individual best = pool[0];

	for(unsigned i = 1; i < this->size; i++) {
		if(best.getFitness() < pool[i].getFitness()) {
			best = pool[i];
		}
	}

	return best;
}
