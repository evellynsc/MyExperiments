/*
 * BitInversionMutation.cpp
 *
 *  Created on: 24/09/2014
 *      Author: evellyn
 */

#include "BitInversionMutation.h"

BitInversionMutation::BitInversionMutation() {
	// TODO Auto-generated constructor stub

}

BitInversionMutation::~BitInversionMutation() {
	// TODO Auto-generated destructor stub
}

Individual BitInversionMutation::run(Individual individual) {
	vector<bool> chromossome = individual.getChromossome();
	vector<int> one;
	vector<int> zero;

	for(unsigned int i = 0; i < chromossome.size(); i++) {
		if(chromossome[i])
			one.push_back(i);
		else
			zero.push_back(i);
	}

	if(one.size() != 0) {
		int oneInverted = Randomize::generate_long() % one.size();
//		oneInverted = rand() % one.size();
		chromossome[one[oneInverted]] = false;
	}

	if(zero.size() != 0) {
		int zeroInverted = Randomize::generate_long() % zero.size();
//		zeroInverted = rand() % zero.size();
		chromossome[zero[zeroInverted]] = true;
	}

	Individual newIndividual = Individual(chromossome.size(), individual.getOnes(), chromossome);

	return newIndividual;
}
