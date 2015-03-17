//============================================================================
// Name        : GA.cpp
// Author      : Evellyn
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

/*#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include "Individual.h"
#include "operator/selection/Tournament.h"
#include "operator/crossover/OnePointCrossover.h"
#include "operator/crossover/FusionCrossover.h"
#include "operator/mutation/BitInversionMutation.h"
#include "operator/initialization/RandomGreedInitialization.h"
#include "operator/initialization/RandomInitialization.h"
#include "operator/initialization/GreedInitialization.h"
#include "operator/initialization/FullerIntersectionsInitialization.h"
#include "operator/local_search/ReplaceMoreUsedIntersections.h"
#include "operator/local_search/ReplaceLessUsedIntersections.h"
#include "operator/local_search/ReplaceBelowAverageIntersections.h"
#include "operator/local_search/InsertAroundMeanIntersections.h"
#include "framework/LocalSearch.h"
#include "statistic/StatisticCollector.h"
#include "DeployProblem.h"
#include "DeployGA.h"

using namespace std;

int main(int argc, char **argv) {

	// problem parameters
	DeployProblem				*problem;
	int							required_time	=	30;
	int							total_rsu		=	10;
	string						problem_path 	= 	"/home/evellyn/ga/E2-T-60s-4CP";
	problem = new DeployProblem(total_rsu, required_time, problem_path);


	PopulationInitialization	*popinit;
	int 						pop_size	=	100;
	popinit = new RandomInitialization(pop_size, problem->getNintersections(), total_rsu);

	vector<Individual> population = popinit->run();
	vector<Individual> new_population;

//	LocalSearch *local_search = new InsertAroundMeanIntersections(problem);
//	LocalSearch *local_search = new ReplaceBelowAverageIntersections(problem);
	LocalSearch *local_search = new ReplaceLessUsedIntersections(problem);
//	LocalSearch *local_search = new ReplaceMoreUsedIntersections(problem);

	for(unsigned i = 0; i < population.size(); i++) {
		population[i].setOnes(population[i].countOnes());
		new_population.push_back(local_search->run(population[i]));
		new_population[i].setOnes(new_population[i].countOnes());
		cout << "old: " << population[i] << ";" << population[i].getOnes() << " " << endl;
		cout << "new: " << new_population[i] <<  ";" << new_population[i].getOnes() << " " << endl;
	}

	return 1;
}

*/
