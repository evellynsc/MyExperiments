/*
 * ReplaceBelowAverageIntersections.cpp
 *
 *  Created on: 09/11/2014
 *      Author: evellyn
 */

#include "ReplaceBelowAverageIntersections.h"

ReplaceBelowAverageIntersections::ReplaceBelowAverageIntersections(DeployProblem *problem) {
	vehicles_per_intersections = problem->getVehiclesThroughIntersection();
	mean_vehicles =  problem->getMeanVehicles();
	for(unsigned i = 0; i < vehicles_per_intersections.size(); i++) {
		if(vehicles_per_intersections[i].second < mean_vehicles){
			limiting_index = i;
			break;
		}
	}
}

ReplaceBelowAverageIntersections::~ReplaceBelowAverageIntersections() {
	// TODO Auto-generated destructor stub
}

Individual ReplaceBelowAverageIntersections::run(Individual individual) {
	vector<int> above_mean_intersections;
	vector<int> below_mean_intersections;
	vector<int> new_intersections;
	vector<bool> new_chromossome;
	Individual new_individual(0,0);
	vector<bool> chromossome = individual.getChromossome();
	int i_control;
	for(unsigned i = 0; i < chromossome.size(); i++) {
		if(chromossome[i] == true) {
			if(is_above_mean(i)){
				above_mean_intersections.push_back(i);
			} else {
				below_mean_intersections.push_back(i);
			}
		}
	}
	i_control = above_mean_intersections.size();

	if(below_mean_intersections.size() != 0 && i_control < limiting_index) {
		for(unsigned i = 0; i < below_mean_intersections.size(); i++) {
			int pick_number = Randomize::generate_long();

			if(pick_number%2 == 0) {
				int index;
				while(true) {
					index = Randomize::generate_long() % limiting_index;
					if(!exist(index, above_mean_intersections) && !exist(index, new_intersections)) {
						new_intersections.push_back(vehicles_per_intersections[index].first);
						i_control++;
						break;
					}
					if(i_control == limiting_index)
						break;
				}
			} else {
				new_intersections.push_back(below_mean_intersections[i]);
			}
		}

		for(unsigned i = 0; i < chromossome.size(); i++) {
			new_chromossome.push_back(false);
		}
		for(unsigned i = 0; i < above_mean_intersections.size(); i++) {
			new_chromossome[above_mean_intersections[i]] = true;
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

bool ReplaceBelowAverageIntersections::is_above_mean(int intersection) {
	for(int i = 0; i < limiting_index; i++) {
		if(intersection == vehicles_per_intersections[i].first)
			return true;
	}
	return false;
}

bool ReplaceBelowAverageIntersections::exist(int index, vector<int> above_mean_intersections) {
	int intersection = vehicles_per_intersections[index].first;
	for(unsigned i = 0; i < above_mean_intersections.size(); i++) {
		if(intersection == above_mean_intersections[i]) {
			return true;
		}
	}
	return false;
}
