/*
 * ReplaceLessUsedIntersections.h
 *
 *  Created on: 09/11/2014
 *      Author: evellyn
 */

#ifndef REPLACELESSUSEDINTERSECTIONS_H_
#define REPLACELESSUSEDINTERSECTIONS_H_

#include "../../framework/LocalSearch.h"
#include "../../utils/Randomize.h"
#include "../../DeployProblem.h"

class ReplaceLessUsedIntersections : public LocalSearch {
	vector< pair<int, int> > vehicles_per_intersections;
	bool is_more_used(int);
	bool exist(int, vector<int>);

public:
	ReplaceLessUsedIntersections(DeployProblem*);
	Individual run(Individual);
	virtual ~ReplaceLessUsedIntersections();
};

#endif /* REPLACELESSUSEDINTERSECTIONS_H_ */
