/*
 * FusionCrossover.h
 *
 *  Created on: 24/09/2014
 *      Author: evellyn
 */

#ifndef FUSIONCROSSOVER_H_
#define FUSIONCROSSOVER_H_

#include "../../framework/Crossover.h"
#include "../../utils/Randomize.h"


class FusionCrossover : public Crossover {
public:
	FusionCrossover();
	virtual ~FusionCrossover();
	vector<Individual> run(Individual, Individual);
};

#endif /* FUSIONCROSSOVER_H_ */
