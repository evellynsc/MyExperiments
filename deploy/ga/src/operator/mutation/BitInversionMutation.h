/*
 * BitInversionMutation.h
 *
 *  Created on: 24/09/2014
 *      Author: evellyn
 */

#ifndef BITINVERSIONMUTATION_H_
#define BITINVERSIONMUTATION_H_

#include "../../framework/Mutation.h"
#include "../../utils/Randomize.h"

/*
 * Inverte aleatoriamente dois bits: um 0 e um 1.
 */

class BitInversionMutation : public Mutation {
public:
	BitInversionMutation();
	virtual ~BitInversionMutation();
	Individual run(Individual);
};

#endif /* BITINVERSIONMUTATION_H_ */
