/*
 * Selection.h
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#ifndef SELECTION_H_
#define SELECTION_H_

#include "../Individual.h"

class Selection {
public:
	virtual Individual run(vector<Individual>) = 0;
	virtual ~Selection(){};
};

#endif /* SELECTION_H_ */
