/*
 * Mutation.h
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#ifndef MUTATION_H_
#define MUTATION_H_

#include "../Individual.h"

class Mutation {
public:
	virtual Individual run(Individual) = 0;
	virtual ~Mutation(){};
};

#endif /* MUTATION_H_ */
