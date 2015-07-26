/*
 * Sort.h
 *
 *  Created on: 10/10/2014
 *      Author: evellyn
 */

#ifndef SORT_H_
#define SORT_H_

inline bool individual_sort(Individual i, Individual j) {
	if(i.getFitness() < j.getFitness())
		return true;
	return false;
}

inline bool decreased_pair_sort(pair<int,float> i, pair<int,float> j) {
	if(i.second <= j.second)
		return false;
	return true;
}


#endif /* SORT_H_ */
