/*
 * ReplaceLessUsedIntersections.cpp
 *
 *  Created on: 09/11/2014
 *      Author: evellyn
 */

#include "ReplaceLessUsedIntersections.h"

ReplaceLessUsedIntersections::ReplaceLessUsedIntersections(DeployProblem *problem) {
	vehicles_per_intersections = problem->getVehiclesThroughIntersection();
}

ReplaceLessUsedIntersections::~ReplaceLessUsedIntersections() {
	// TODO Auto-generated destructor stub
}

Individual ReplaceLessUsedIntersections::run(Individual individual) {
	vector<int> more_used_intersections;
	vector<int> less_used_intersections;
	vector<int> new_intersections;
	vector<bool> new_chromossome;
	Individual new_individual(0,0);
	vector<bool> chromossome = individual.getChromossome();
	for(unsigned i = 0; i < chromossome.size(); i++) {
		if(chromossome[i] == true) {
			if(is_more_used(i)){
				more_used_intersections.push_back(i);
			} else {
				less_used_intersections.push_back(i);
			}
		}
	}
	if(less_used_intersections.size() != 0) {
		for(unsigned i = 0; i < less_used_intersections.size(); i++) {
			int pick_number = Randomize::generate_long();

			if(pick_number%2 == 0) {
				int index;
				while(true) {
					index = Randomize::generate_long() % (int) vehicles_per_intersections.size()/2;
					if(!exist(index, more_used_intersections) && !exist(index, new_intersections)) {
						new_intersections.push_back(vehicles_per_intersections[index].first);
						break;
					}
				}
			} else {
				new_intersections.push_back(less_used_intersections[i]);
			}
		}

		for(unsigned i = 0; i < chromossome.size(); i++) {
			new_chromossome.push_back(false);
		}
		for(unsigned i = 0; i < more_used_intersections.size(); i++) {
			new_chromossome[more_used_intersections[i]] = true;
		}
		for(unsigned i = 0; i < new_intersections.size(); i++) {
			new_chromossome[new_intersections[i]] = true;
		}
		new_individual.setSize(individual.getSize());
		new_individual.setOnes(individual.getOnes());
		new_individual.setChromossome(new_chromossome);
	} else {
		return new_individual = individual;
	}
	return new_individual;
}

bool ReplaceLessUsedIntersections::is_more_used(int intersection) {
	int total_more_used = (int)vehicles_per_intersections.size()/2;
	for(int i = 0; i < total_more_used; i++) {
		if(intersection == vehicles_per_intersections[i].first)
			return true;
	}
	return false;
}

bool ReplaceLessUsedIntersections::exist(int index, vector<int> more_used_intersections) {
	int intersection = vehicles_per_intersections[index].first;
	for(unsigned i = 0; i < more_used_intersections.size(); i++) {
		if(intersection == more_used_intersections[i]) {
			return true;
		}
	}
	return false;
}
