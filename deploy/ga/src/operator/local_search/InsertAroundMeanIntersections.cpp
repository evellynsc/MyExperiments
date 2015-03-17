/*
 * InsertAroundMeanIntersections.cpp
 *
 *  Created on: 09/11/2014
 *      Author: evellyn
 */

#include "InsertAroundMeanIntersections.h"

InsertAroundMeanIntersections::InsertAroundMeanIntersections(DeployProblem *problem) {
	vehicles_per_intersections = problem->getVehiclesThroughIntersection();
	mean_vehicles =  problem->getMeanVehicles();
	float half_mean = mean_vehicles/2;
	interval.push_back(mean_vehicles-half_mean);
	interval.push_back(mean_vehicles+half_mean);
	for(unsigned i = 0; i < vehicles_per_intersections.size(); i++) {
		if(vehicles_per_intersections[i].second == interval[0]) {
			limiting_index.push_back(i);
			break;
		} else if(vehicles_per_intersections[i].second < interval[0]) {
			limiting_index.push_back(i-1);
			break;
		}
	}
	for(unsigned i = 0; i < vehicles_per_intersections.size(); i++) {
		if(vehicles_per_intersections[i].second <= interval[1]) {
			limiting_index.push_back(i);
			break;
		}
	}
}

InsertAroundMeanIntersections::~InsertAroundMeanIntersections() {
	// TODO Auto-generated destructor stub
}

Individual InsertAroundMeanIntersections::run(Individual individual) {
	vector<int> out_interval_intersections;
	vector<int> in_interval_intersections;
	vector<int> new_intersections;
	vector<bool> new_chromossome;
	int possible_intersections = limiting_index[0]-limiting_index[1];
	Individual new_individual(0,0);
	vector<bool> chromossome = individual.getChromossome();
	int i_control;
	for(unsigned i = 0; i < chromossome.size(); i++) {
		if(chromossome[i] == true) {
			if(is_in_interval(i)){
				in_interval_intersections.push_back(i);
			} else {
				out_interval_intersections.push_back(i);
			}
		}
	}
	i_control = in_interval_intersections.size();

	if(out_interval_intersections.size() != 0 && i_control < possible_intersections) {
		for(unsigned i = 0; i < out_interval_intersections.size(); i++) {
			int pick_number = Randomize::generate_long();

			if(pick_number%2 == 0) {
				int index;
				while(true) {
					index = Randomize::generate_long() % (limiting_index[0]-limiting_index[1] + 1);
					index += limiting_index[1];
					if(i_control == possible_intersections) {
						new_intersections.push_back(out_interval_intersections[i]);
						break;
					}
					if(!exist(index, in_interval_intersections) && !exist(index, new_intersections)) {
						new_intersections.push_back(vehicles_per_intersections[index].first);
						i_control++;
						break;
					}
				}
			} else {
				new_intersections.push_back(out_interval_intersections[i]);
			}
		}

		for(unsigned i = 0; i < chromossome.size(); i++) {
			new_chromossome.push_back(false);
		}
		for(unsigned i = 0; i < in_interval_intersections.size(); i++) {
			new_chromossome[in_interval_intersections[i]] = true;
		}
		for(unsigned i = 0; i < new_intersections.size(); i++) {
			new_chromossome[new_intersections[i]] = true;
		}
		new_individual.setSize(individual.getSize());
		new_individual.setChromossome(new_chromossome);
	} else {
		return new_individual = individual;
	}
	return new_individual;
}

bool InsertAroundMeanIntersections::is_in_interval(int intersection) {
	for(int i = limiting_index[1]; i <= limiting_index[0]; i++) {
		if(intersection == vehicles_per_intersections[i].first)
			return true;
	}
	return false;
}

bool InsertAroundMeanIntersections::exist(int index, vector<int> intersections) {
	int intersection = vehicles_per_intersections[index].first;
	for(unsigned i = 0; i < intersections.size(); i++) {
		if(intersection == intersections[i]) {
			return true;
		}
	}
	return false;
}
