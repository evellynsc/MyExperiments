/*
 * Individual.h
 *
 *  Created on: 12/09/2014
 *      Author: evellyn
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <set>
#include "utils/Randomize.h"

using namespace std;

class Individual {
	vector<bool> chromossome;
	int size;
	int nOnes;
	float fitness;
	int coverage;
	vector<bool> create();

public:
	Individual(int, int);
	Individual(int, int, vector<bool>&);
	Individual(int, int, vector<bool>&, float, int);
	virtual ~Individual();
	Individual makeCorrection();
	string toString();
	int countOnes();

	friend ostream& operator<< (ostream&, Individual&);
	friend bool operator== (Individual&, Individual&);
	friend bool operator!= (Individual&, Individual&);

	/*getters and setters*/

	double getFitness() const {
		return fitness;
	}

	int getOnes() const {
		return nOnes;
	}

	int getSize() const {
		return size;
	}

	const vector<bool>& getChromossome() const {
		return chromossome;
	}

	void setChromossome(const vector<bool>& chromossome) {
		this->chromossome = chromossome;
	}

	void setFitness(double fitness) {
		this->fitness = fitness;
	}

	void setOnes(int ones) {
		nOnes = ones;
	}

	void setSize(int size) {
		this->size = size;
	}

	int getCoverage() const {
		return coverage;
	}

	void setCoverage(int coverage) {
		this->coverage = coverage;
	}
};

#endif /* INDIVIDUAL_H_ */
