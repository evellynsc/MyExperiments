/*
 * FusionCrossover.cpp
 *
 *  Created on: 24/09/2014
 *      Author: evellyn
 */

#include "FusionCrossover.h"

FusionCrossover::FusionCrossover() {
	// TODO Auto-generated constructor stub

}

FusionCrossover::~FusionCrossover() {
	// TODO Auto-generated destructor stub
}

vector<Individual> FusionCrossover::run(Individual parent1, Individual parent2) {
	vector<bool> chromossomeP1 = parent1.getChromossome();
	vector<bool> chromossomeP2 = parent2.getChromossome();
	vector<bool> chromossomeO;
	int oneCount = 0;

	for(unsigned int i = 0; i < chromossomeP1.size(); i++) {
		if(chromossomeP1[i] == chromossomeP2[i]) {
			chromossomeO.push_back(chromossomeP1[i]);
			if(chromossomeO[i])
				oneCount++;
		} else {
			float probP1 = parent2.getFitness()/(parent1.getFitness() + parent2.getFitness());
			float output = Randomize::generate_double();
//			output = (float) rand() / RAND_MAX;

			if(output <= probP1) {
				chromossomeO.push_back(chromossomeP1[i]);
			} else {
				chromossomeO.push_back(chromossomeP2[i]);
			}
			if(chromossomeO[i])
				oneCount++;
		}
	}

//	set<int> onePositionsP1;
//	set<int> onePositionsP2;
//	set<int> testDuplicated;
//	int sizeSet = 0;

//	for(int i = 0; i < chromossomeP1.size(); i++) {
//		chromossomeO[i] = false;
//	}

	/*
	 * Verifica se há genes 1's numa mesma posição em ambos os pais para
	 * transmiti-los ao filho diretamente.
	 */

//	for(int i = 0; i < chromossomeP1.size(); i++) {
//		if(chromossomeP1[i]) {
//			onePositionsP1.insert(i);
//			testDuplicated.insert(i);
//			if(testDuplicated.size() == sizeSet) {
//				testDuplicated.erase(i);
//				chromossomeO[i] = true;
//				sizeSet--;
//			} else {
//				sizeSet++;
//			}
//		}
//		if(chromossomeP2[i]) {
//			onePositionsP2.insert(i);
//			testDuplicated.insert(i);
//			if(testDuplicated.size() == sizeSet) {
//				testDuplicated.erase(i);
//				chromossomeO[i] = true;
//				sizeSet--;
//			} else {
//				sizeSet++;
//			}
//		}
//	}

//	for(int i = 0; i < onePositionsP1.size(); i++) {
//		float probP1 = parent2.getFitness()/(parent1.getFitness() + parent2.getFitness());
//		float output = ((double) rand() / (RAND_MAX));
//
//		if(output <= probP1) {
//			chromossomeO[onePositionsP1[i]] = true;
//		} else {
//			chromossomeO[onePositionsP2[i]] = true;
//		}
//	}
//
	Individual offspring1 = Individual(chromossomeO.size(), oneCount, chromossomeO);
	vector<Individual> offspring;
	offspring.push_back(offspring1);

	return offspring;
}

