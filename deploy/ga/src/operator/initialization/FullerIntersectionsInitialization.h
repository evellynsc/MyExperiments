/*
 * FullerIntersectionsInitialization.h
 *
 *  Created on: 24/10/2014
 *      Author: evellyn
 */

#ifndef FULLERINTERSECTIONSINITIALIZATION_H_
#define FULLERINTERSECTIONSINITIALIZATION_H_

#include "../../DeployProblem.h"
#include "../../framework/PopulationInitialization.h"
#include "RandomInitialization.h"
#include "../../utils/Randomize.h"

using namespace std;

class FullerIntersectionsInitialization : public PopulationInitialization {
	int size;
	DeployProblem *problem;
	bool exist(vector<int>,int);

public:
	FullerIntersectionsInitialization(DeployProblem*, int);
	vector<Individual> run();
	int get_size();
	virtual ~FullerIntersectionsInitialization();
};

#endif /* FULLERINTERSECTIONSINITIALIZATION_H_ */
