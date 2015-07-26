/*
 * LocalSearch.h
 *
 *  Created on: 09/11/2014
 *      Author: evellyn
 */

#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include "../Individual.h"

class LocalSearch {
public:
	virtual Individual run(Individual) = 0;
	virtual ~LocalSearch(){};
};



#endif /* LOCALSEARCH_H_ */
