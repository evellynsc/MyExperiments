/*
 * FullerIntersectionsInitialization.cpp
 *
 *  Created on: 24/10/2014
 *      Author: evellyn
 */

#include "FullerIntersectionsInitialization.h"

FullerIntersectionsInitialization::FullerIntersectionsInitialization(DeployProblem *problem, int size) {
	this->size = size;
	this->problem = problem;
}

FullerIntersectionsInitialization::~FullerIntersectionsInitialization() {
	// TODO Auto-generated destructor stub
}

vector<Individual> FullerIntersectionsInitialization::run() {
	vector< pair<int,int> > vehicles_per_intersections = problem->getVehiclesThroughIntersection();
	int total_intersections = problem->getNintersections();
	int num_selected_intersections = problem->getNrsu();
	RandomInitialization *random_init = new RandomInitialization(size/2, total_intersections, num_selected_intersections);
	vector<Individual> population = random_init->run();
	int sum_vehicles = 0;
	vector< pair<int, float> > roulette;

//	cout << "ROULETTE" << endl;
//	cout << "=======================" << endl;

	for(unsigned i = 0; i < vehicles_per_intersections.size(); i++) {
		sum_vehicles += vehicles_per_intersections[i].second;
	}

	for(unsigned i = 0; i < vehicles_per_intersections.size(); i++) {
		pair<int, float> percentage(vehicles_per_intersections[i].first, (float)vehicles_per_intersections[i].second/sum_vehicles);
		roulette.push_back(percentage);
	}

//	for(unsigned i = 0; i < roulette.size(); i++) {
//		cout << roulette[i].second << "+" ;
//	}
//	cout << "======================" << endl;
	while((int)population.size() != this->size) {
		vector<int> intersections;
		while((int)intersections.size() != num_selected_intersections) {
			double pocket = Randomize::generate_double();
			int selected = -1;
			for(unsigned i = 0; i < roulette.size(); i++) {
				if(roulette[i].second >= pocket) {
					selected = roulette[i].first;
				}
			}
			if(selected == -1) {
				selected = roulette[0].first;
			}
			if(!exist(intersections,selected)) {
				intersections.push_back(selected);
			}
		}

		vector<bool> chromossome;
		for(int i = 0; i < total_intersections; i++) {
			chromossome.push_back(false);
		}
		for(unsigned i = 0; i < intersections.size(); i++) {
			chromossome[intersections[i]] = true;
		}
		Individual individual = Individual((int)chromossome.size(), intersections.size(), chromossome);
		population.push_back(individual);
	}
	delete random_init;
	return population;
}

bool FullerIntersectionsInitialization::exist(vector<int> intersections, int drawn) {
	bool exist = false;
	for(unsigned i = 0; i < intersections.size(); i++) {
		if(intersections[i] == drawn) {
			exist = true;
			break;
		}
	}

	return exist;
}

int FullerIntersectionsInitialization::get_size() {
	return this->size;
}
