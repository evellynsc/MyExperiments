/*
 * OnePointCrossover.h
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#ifndef ONEPOINTCROSSOVER_H_
#define ONEPOINTCROSSOVER_H_

#include "../../framework/Crossover.h"
#include "../../utils/Randomize.h"

class OnePointCrossover : public Crossover {
public:
	OnePointCrossover();
	virtual ~OnePointCrossover();

	vector<Individual> run(Individual, Individual);
};

#endif /* ONEPOINTCROSSOVER_H_ */
