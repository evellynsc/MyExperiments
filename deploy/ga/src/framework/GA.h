/*
 * GA.h
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#ifndef GA_H_
#define GA_H_

#include "../Individual.h"

class GA {
public:
	virtual ~GA(){};
	virtual void set_parameters(int, float, float, float, float) = 0;
	virtual void prune_population(vector<Individual>) = 0;
	virtual void run() = 0;
	virtual void evaluate() = 0;
	virtual Individual get_best() = 0;
	virtual Individual get_worst() = 0;
};


#endif /* GA_H_ */
