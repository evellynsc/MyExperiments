/*
 * RandomInitialization.cpp
 *
 *  Created on: 24/09/2014
 *      Author: evellyn
 */

#include "RandomInitialization.h"

RandomInitialization::RandomInitialization(int size, int chromossome_size, int nones) {
	this->size = size;
	this->chromossome_size = chromossome_size;
	this->nones = nones;
}

RandomInitialization::~RandomInitialization() {
	// TODO Auto-generated destructor stub
}

vector<Individual> RandomInitialization::run() {
	vector<Individual> population;

	for(int i = 0; i < this->size; i++) {
		Individual individual = Individual(chromossome_size, nones);
		population.push_back(individual);
	}

	return population;
}

int RandomInitialization::get_size() {
	return this->size;
}
