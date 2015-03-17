/*
 * ReplaceMoreUsedIntersections.h
 *
 *  Created on: 09/11/2014
 *      Author: evellyn
 */

#ifndef REPLACEMOREUSEDINTERSECTIONS_H_
#define REPLACEMOREUSEDINTERSECTIONS_H_

#include "../../framework/LocalSearch.h"
#include "../../utils/Randomize.h"
#include "../../DeployProblem.h"

class ReplaceMoreUsedIntersections : public LocalSearch {
	vector< pair<int, int> > vehicles_per_intersections;
	bool is_more_used(int);
	bool exist(int, vector<int>);

public:
	ReplaceMoreUsedIntersections(DeployProblem*);
	Individual run(Individual);
	virtual ~ReplaceMoreUsedIntersections();
};

#endif /* REPLACEMOREUSEDINTERSECTIONS_H_ */
