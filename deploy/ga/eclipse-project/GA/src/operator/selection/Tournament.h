/*
 * Tournament.h
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#ifndef TOURNAMENT_H_
#define TOURNAMENT_H_

#include "../../framework/Selection.h"
#include "../../utils/Randomize.h"


class Tournament : public Selection {
	unsigned int size;

public:
	Tournament(unsigned int);
	virtual ~Tournament();
	Individual run(vector<Individual>);
};

#endif /* TOURNAMENT_H_ */
