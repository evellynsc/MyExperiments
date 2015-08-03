//============================================================================
// Name        : GA.cpp
// Author      : Evellyn
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
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
#include "operator/local_search/InsertAroundMeanIntersections.h"
#include "operator/local_search/ReplaceBelowAverageIntersections.h"
#include "operator/local_search/ReplaceLessUsedIntersections.h"
#include "operator/local_search/ReplaceMoreUsedIntersections.h"
#include "statistic/StatisticCollector.h"
#include "DeployProblem.h"
#include "DeployGA.h"

using namespace std;
static struct timeval *clock_start;

void load_genetic_parameters(char *path, int *ngen, int *popinit_id, int *pop_size, int *crossover_id,
		float *p_crossover, int *mutation_id, float *p_mutation, int *localsearch, float *p_localsearch);
void start_timer();
double get_timer();
float calculate_average_time(vector<float>);


int main(int argc, char **argv) {

	if (argc != 8){
		cout << "usage: \t" << argv[0] << " [number-replications] [time-limit]"
				" [required-time] [total-rsu] [param-genetic-file] [input-file] [output-file] " << endl << endl;
		return 0;
	}

	// experiment parameters
	int							replications;
	float						timeLimit;
	vector<float>				execution_times;
	istringstream is(argv[1]);
	is >> replications;
	is.str("");
	is.clear();
	is.str(argv[2]);
	is >> timeLimit;


	// statistic parameters
	string						output_path = argv[7];

	// genetic algorithm parameters
	int							ngen;
	int							popinit_id;
	int 						pop_size;
	int							crossover_id;
	float						p_crossover;
	int							mutation_id;
	float						p_mutation;
	int							localsearch_id;
	float						p_localsearch;
	char*						genetic_path = argv[5];


	load_genetic_parameters(genetic_path, &ngen, &popinit_id, &pop_size, &crossover_id, &p_crossover, &mutation_id,
			&p_mutation, &localsearch_id, &p_localsearch);

	// problem parameters
	int							required_time;
	int							total_rsu;
	string						problem_path = argv[6];
	is.str("");
	is.clear();
	is.str(argv[3]);
	is >> required_time;
	is.str("");
	is.clear();
	is.str(argv[4]);
	is >> total_rsu;

	// problem instantiation
	DeployProblem				*problem;
	problem = new DeployProblem(total_rsu, required_time, problem_path);

	// statistic instantiation
	StatisticCollector			*statistic;
	statistic = new StatisticCollector(1, output_path);

	// genetic algorithm instantiation
	PopulationInitialization	*popinit;
	Selection					*selection;
	Crossover					*crossover;
	Mutation					*mutation;
	LocalSearch					*localsearch;
	DeployGA					*ga;

	selection = new Tournament(2);

	switch(popinit_id) {
	case 1:
		popinit = new RandomInitialization(pop_size, problem->getNintersections(), total_rsu);
		break;

	case 2:
		popinit = new GreedInitialization(problem, pop_size);
		break;

	case 3:
		popinit = new RandomGreedInitialization(problem, pop_size, false);
		break;

	case 4:
		popinit = new RandomGreedInitialization(problem, pop_size, true);
		break;

	case 5:
		popinit = new FullerIntersectionsInitialization(problem, pop_size);
		break;
	}

	switch(crossover_id) {
	case 1:
		crossover = new OnePointCrossover();
		break;
	case 2:
		crossover = new FusionCrossover();
	}

	switch(mutation_id) {
	case 1:
		mutation = new BitInversionMutation();
	}

	switch(localsearch_id) {
		case 1:
			localsearch = new ReplaceMoreUsedIntersections(problem);
			break;

		case 2:
			localsearch = new ReplaceLessUsedIntersections(problem);
			break;

		case 3:
			localsearch = new ReplaceBelowAverageIntersections(problem);
			break;

		case 4:
			localsearch = new InsertAroundMeanIntersections(problem);
			break;
	}

	for(int i = 0; i < replications; i++) {
		ga = new DeployGA(statistic, problem, popinit, selection, crossover, mutation, localsearch, timeLimit);
		ga->set_parameters(ngen, p_crossover, p_mutation, p_localsearch, 0.0);
//		cout << "r" << i << ": ";
		ga->run();
		execution_times.push_back(ga->get_total_time());
		statistic->write();
		statistic->empty();
	}


	cout << "AVERAGE TIME: " << calculate_average_time(execution_times) << endl;

	//	cout << pop_size << " " << ngen << " " << p_crossover << " " << p_mutation << " " << genetic_path <<  endl;
	//	cout << popinit_id << " " << crossover_id << " " << mutation_id <<  endl;
	//	cout << required_time << " " << total_rsu << " " << problem_path << endl;
	//	cout << output_path << endl;

	delete ga;

	return 1;
}

void load_genetic_parameters(char *path, int *ngen, int *popinit_id, int *pop_size, int *crossover_id,
		float *p_crossover, int *mutation_id, float *p_mutation, int *localsearch_id, float *p_localsearch) {
	ifstream file(path);
	if(file.fail()) {
		cerr << "Falha na abertura do arquivo de parâmetros do GA.\n";
		exit(1);
	}

	//population size
	string line;
	getline(file, line);
	istringstream is(line);
	is >> *ngen;

	//generation number
	line = "";
	getline(file, line);
	is.str("");
	is.clear();
	is.str(line);
	is >> *popinit_id;
	is >> *pop_size;

	//probability of crossover
	line = "";
	getline(file, line);
	is.str("");
	is.clear();
	is.str(line);
	is >> *crossover_id;
	is >> *p_crossover;

	//probability of mutation
	line = "";
	getline(file, line);
	is.str("");
	is.clear();
	is.str(line);
	is >> *mutation_id;
	is >> *p_mutation;

	//probability of local search
	line = "";
	getline(file, line);
	is.str("");
	is.clear();
	is.str(line);
	is >> *localsearch_id;
	is >> *p_localsearch;
}


void start_timer()
{
	// current clock time
	clock_start = (struct timeval *) malloc(sizeof(struct timeval) );
	gettimeofday(clock_start, 0);
}

double get_timer()
{
	unsigned long clock_time;
	struct timeval *clock_stop;

	clock_stop = (struct timeval *) malloc( sizeof(struct timeval) );

	gettimeofday(clock_stop, 0);

	clock_time = 1.e6 * (clock_stop->tv_sec - clock_start->tv_sec) +
			(clock_stop->tv_usec - clock_start->tv_usec);

	double result = (double)clock_time / (double)1.e6;

	return result;
}


float calculate_average_time(vector<float> times) {
	float sum = 0.0;
	for(int i = 0; i < (int) times.size(); ++i) {
		sum += times[i];
	}
	float average = sum/times.size();
	return average;
}
