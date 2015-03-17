/*
 * GreedInitialization.cpp
 *
 *  Created on: 10/10/2014
 *      Author: evellyn
 */

#include "GreedInitialization.h"


GreedInitialization::GreedInitialization(DeployProblem *problem, int size) {
	this->problem = problem;
	this->size = size;
}

GreedInitialization::~GreedInitialization() {
	// TODO Auto-generated destructor stub
}

vector<Individual> GreedInitialization::run() {
	vector<int> aimed_time;
	vector<int> intersections;
	vector< pair<int, int> > time_intersections;
	vector<Individual> population;
	int num_intersections = problem->getNintersections();
	vector< vector<int> > scene = problem->getTable();
	int nones = problem->getNrsu();
	int num_vehicles = problem->getNvehicles();
	int required_time = problem->getRequiredTime();
	int sum = 0;
	int time_vehicle;

	intersections.clear();
	aimed_time.clear();
	for(int i = 0; i < num_vehicles; i++) {
		aimed_time.push_back(required_time);
	}

	int genes_count = 0;
	while(genes_count < nones) {
		time_intersections.clear();
		sum = 0;
//		cout << "time_intersections\n";
		for(int i = 0; i < num_intersections; i++) {
			sum = 0;
			for(int j = 0; j < num_vehicles; j++) {
				time_vehicle = scene[i][j];
				if(time_vehicle > aimed_time[j])
					time_vehicle = aimed_time[j];
				sum += time_vehicle;
			}
			time_intersections.push_back(pair<int,int>(i,sum));
		}


		sort(time_intersections.begin(), time_intersections.end(), decreased_pair_sort);
//		cout << "sort\n";

		int chosen = time_intersections[0].first;

//		cout << "aimed_time\n";
		for(int i = 0; i < num_vehicles; i++) {
			if(scene[chosen][i] != 0) {
				if(scene[chosen][i] >= aimed_time[i]) {
					aimed_time[i] = 0;
				} else {
					aimed_time[i] = aimed_time[i] - scene[chosen][i];
				}
			}
			scene[chosen][i] = 0;
		}
		genes_count++;
		intersections.push_back(chosen);
	}


	cout << "individual creation\n";
	population.push_back(create_individual(intersections));

	vector<Individual> random_population;
	RandomInitialization random_init = RandomInitialization(this->size-1, num_intersections, nones);
	random_population = random_init.run();
	cout << "terminou criação\n";

	for(unsigned i = 0; i < random_population.size(); i++) {
		population.push_back(random_population[i]);
	}

	return population;
}

Individual GreedInitialization::create_individual(vector<int> intersections) {
	vector<bool> chromossome;
	int chromossome_size = problem->getNintersections();

	for(int i = 0; i < chromossome_size; i++) {
		chromossome.push_back(false);
	}
	for(unsigned i = 0; i < intersections.size(); i++) {
//		cout << intersections[i] << " ";
		chromossome[intersections[i]] = true;
	}
//	cout << endl;
	Individual individual = Individual(chromossome_size, intersections.size(), chromossome);
//	cout << "created individual\n";

	return individual;
}

bool GreedInitialization::exist(vector<int> intersections, int drawn) {
	bool exist = false;
	for(unsigned i = 0; i < intersections.size(); i++) {
		if(intersections[i] == drawn) {
			exist = true;
			break;
		}
	}

	return exist;
}

int GreedInitialization::get_size() {
	return this->size;
}

