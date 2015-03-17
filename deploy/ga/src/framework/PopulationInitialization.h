/*
 * PopulationInitializer.h
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#ifndef POPULATIONINITIALIZER_H_
#define POPULATIONINITIALIZER_H_

#include "../Individual.h"

class PopulationInitialization {
public:
	virtual ~PopulationInitialization(){};
	virtual vector<Individual> run() = 0 ;
	virtual int get_size() = 0;
};

#endif /* POPULATIONINITIALIZER_H_ */
