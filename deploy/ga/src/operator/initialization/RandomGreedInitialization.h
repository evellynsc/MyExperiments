/*
 * GreedInitialization.h
 *
 *  Created on: 10/10/2014
 *      Author: evellyn
 */

#ifndef RANDOMGREEDINITIALIZATION_H_
#define RANDOMGREEDINITIALIZATION_H_

#include <iostream>
#include <vector>
#include "RandomInitialization.h"
#include "../../framework/PopulationInitialization.h"
#include "../../DeployProblem.h"
#include "../../Individual.h"
#include "../../utils/Sort.h"


using namespace std;

class RandomGreedInitialization : public PopulationInitialization {
	DeployProblem *problem;
	Individual create_individual(vector<int>);
	bool add_greed_solution;
	bool exist(vector<int>,int);
	int size;

public:
	RandomGreedInitialization(DeployProblem *problem, int size, bool add_greed_solution);
	vector<Individual> run();
	int get_size();
	virtual ~RandomGreedInitialization();
};


#endif /* RANDOMGREEDINITIALIZATION_H_ */
