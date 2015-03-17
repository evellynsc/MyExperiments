/*
 * ReplaceBelowAverageIntersections.h
 *
 *  Created on: 09/11/2014
 *      Author: evellyn
 */

#ifndef REPLACEBELOWAVERAGEINTERSECTIONS_H_
#define REPLACEBELOWAVERAGEINTERSECTIONS_H_

#include "../../framework/LocalSearch.h"
#include "../../utils/Randomize.h"
#include "../../DeployProblem.h"

class ReplaceBelowAverageIntersections : public LocalSearch {
	vector< pair<int, int> > vehicles_per_intersections;
	float mean_vehicles;
	int limiting_index;
	bool is_above_mean(int);
	bool exist(int, vector<int>);

public:
	ReplaceBelowAverageIntersections(DeployProblem*);
	Individual run(Individual);
	virtual ~ReplaceBelowAverageIntersections();
};

#endif /* REPLACEBELOWAVERAGEINTERSECTIONS_H_ */
