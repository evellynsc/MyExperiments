/*
 * GreedInitialization.h
 *
 *  Created on: 10/10/2014
 *      Author: evellyn
 */

#ifndef GREEDINITIALIZATION_H_
#define GREEDINITIALIZATION_H_

#include <iostream>
#include <vector>
#include "RandomInitialization.h"
#include "../../framework/PopulationInitialization.h"
#include "../../DeployProblem.h"
#include "../../Individual.h"
#include "../../utils/Sort.h"


using namespace std;

class GreedInitialization : public PopulationInitialization {
	DeployProblem *problem;
	Individual create_individual(vector<int>);
	bool exist(vector<int>,int);
	int size;

public:
	GreedInitialization(DeployProblem*, int);
	vector<Individual> run();
	int get_size();
	virtual ~GreedInitialization();
};


#endif /* GREEDINITIALIZATION_H_ */
