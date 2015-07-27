/*
 * DeployGA.h
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#ifndef DEPLOYGA_H_
#define DEPLOYGA_H_

#include <vector>
#include <ctime>
#include "Individual.h"
#include "DeployProblem.h"
#include "framework/Crossover.h"
#include "framework/Selection.h"
#include "framework/Mutation.h"
#include "framework/PopulationInitialization.h"
#include "framework/LocalSearch.h"
#include "framework/GA.h"
#include "statistic/StatisticCollector.h"
#include "utils/Randomize.h"
#include "utils/Sort.h"


class DeployGA : public GA {
	vector<Individual> population;
	DeployProblem *problem;
	PopulationInitialization *popInit;
	Selection *selection;
	Crossover *crossover;
	StatisticCollector *statistic;
	Mutation *mutation;
	LocalSearch *localsearch;
	int ngeneration;
	float probMutation;
	float probLocalSearch;
	float probCrossover;
	float tolerance;
	float timeLimit;
	float totalTime;
	int nones;
	void prune_population(vector<Individual>);
	void evaluate();
	bool exist_individual(Individual);


public:
	DeployGA();
	DeployGA(StatisticCollector*, DeployProblem*, PopulationInitialization*, Selection*, Crossover*, Mutation*,
			LocalSearch*, float);
	~DeployGA();
	void set_parameters(int, float, float, float, float);
	Individual get_best();
	Individual get_worst();
	float get_total_time();
	void run();
};

#endif /* GA_H_ */
