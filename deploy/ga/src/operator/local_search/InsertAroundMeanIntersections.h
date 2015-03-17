/*
 * InsertAroundMeanIntersections.h
 *
 *  Created on: 09/11/2014
 *      Author: evellyn
 */

#ifndef INSERTAROUNDMEANINTERSECTIONS_H_
#define INSERTAROUNDMEANINTERSECTIONS_H_

#include "../../framework/LocalSearch.h"
#include "../../utils/Randomize.h"
#include "../../DeployProblem.h"
#include <cmath>

class InsertAroundMeanIntersections : public LocalSearch {
	vector< pair<int, int> > vehicles_per_intersections;
	float mean_vehicles;
	vector<int> limiting_index;
	vector<float> interval;
	bool is_in_interval(int);
	bool exist(int, vector<int>);

public:
	InsertAroundMeanIntersections(DeployProblem*);
	Individual run(Individual);
	virtual ~InsertAroundMeanIntersections();
};

#endif /* INSERTAROUNDMEANINTERSECTIONS_H_ */
