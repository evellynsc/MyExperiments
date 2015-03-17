/*
 * StatisticCollector.h
 *
 *  Created on: 12/09/2014
 *      Author: evellyn
 */

#ifndef STATISTICCOLLECTOR_H_
#define STATISTICCOLLECTOR_H_

#include <iostream>
#include <fstream>
#include "../Individual.h"

using namespace std;

class StatisticCollector {
	vector<float> mean;
	vector<int> repeated_individuals;
	vector<Individual> best;
	vector<Individual> worst;
	int sample_size;
	string path;

public:
	StatisticCollector(int, string);
	void analyse(vector<Individual>);
	void write();
	virtual ~StatisticCollector();

	void empty();

	int getSampleSize() const {
		return sample_size;
	}

	void setSampleSize(int sampleSize) {
		sample_size = sampleSize;
	}
};

#endif /* STATISTICCOLLECTOR_H_ */
