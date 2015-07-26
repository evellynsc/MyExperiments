/*
 * RandomInitialization.h
 *
 *  Created on: 24/09/2014
 *      Author: evellyn
 */

#ifndef RANDOMINITIALIZATION_H_
#define RANDOMINITIALIZATION_H_

#include "../../framework/PopulationInitialization.h"

class RandomInitialization : public PopulationInitialization {
	int size;
	int chromossome_size;
	int nones;

public:
	RandomInitialization(int size, int chromossome_size, int nones);
	virtual ~RandomInitialization();

	vector<Individual> run();
	int get_size();
};

#endif /* RANDOMINITIALIZATION_H_ */
