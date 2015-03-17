/*
 * Crossover.h
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include "../Individual.h"

class Crossover {
public:
	virtual vector<Individual> run(Individual, Individual) = 0;
	virtual ~Crossover(){};
};

#endif /* CROSSOVER_H_ */
