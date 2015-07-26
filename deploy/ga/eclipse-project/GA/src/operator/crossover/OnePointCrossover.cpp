/*
 * OnePointCrossover.cpp
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#include "OnePointCrossover.h"

OnePointCrossover::OnePointCrossover() {
	// TODO Auto-generated constructor stub

}

OnePointCrossover::~OnePointCrossover() {
	// TODO Auto-generated destructor stub
}

vector<Individual> OnePointCrossover::run(Individual parent1, Individual parent2) {
	vector<bool> chromossomeP1 = parent1.getChromossome();
	vector<bool> chromossomeP2 = parent2.getChromossome();
	vector<bool> chromossomeO1;
	vector<bool> chromossomeO2;
	int oneCountO1 = 0;
	int oneCountO2 = 0;

	chromossomeO1.clear();
	chromossomeO2.clear();

	//	vector<int> onePositionsO1;
	//	vector<int> onePositionsO2;

	int position = Randomize::generate_long() % parent1.getSize();
//	position = rand() % parent1.getSize();

	for(int i = 0; i <= position; i++) {
		chromossomeO1.push_back(chromossomeP1[i]);
		chromossomeO2.push_back(chromossomeP2[i]);
		if(chromossomeO1[i])
			oneCountO1++;
		if(chromossomeO2[i])
			oneCountO2++;
		//		if(chromossomeP1[i] == true) {
		//			onePositionsO1.push_back(i);
		//		}
		//		if(chromossomeP2[i] == true) {
		//			onePositionsO2.push_back(i);
		//		}
	}

	for(unsigned i = (position+1); i < chromossomeP1.size(); i++) {
		chromossomeO1.push_back(chromossomeP2[i]);
		chromossomeO2.push_back(chromossomeP1[i]);
		if(chromossomeO1[i])
			oneCountO1++;
		if(chromossomeO2[i])
			oneCountO2++;
		//		if(chromossomeP1[i] == true) {
		//			onePositionsO2.push_back(i);
		//		}
		//		if(chromossomeP2[i] == true) {
		//			onePositionsO1.push_back(i);
		//		}
	}

	Individual offspring1 = Individual(parent1.getSize(), oneCountO1, chromossomeO1);
	Individual offspring2 = Individual(parent1.getSize(), oneCountO2, chromossomeO2);

	//	if((int)onePositionsO1.size() != parent1.getOnes()) {
	//		offspring1.setFitness(-1);
	//	}
	//	if((int)onePositionsO2.size() != parent1.getOnes()) {
	//		offspring2.setFitness(-1);
	//	}

	vector<Individual> offspring;
	offspring.push_back(offspring1);
	offspring.push_back(offspring2);

	return offspring;
}

