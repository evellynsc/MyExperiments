/*
 * Individual.cpp
 *
 *  Created on: 12/09/2014
 *      Author: evellyn
 */

#include "Individual.h"

Individual::Individual(int size, int nOnes) {
	this->size = size;
	this->nOnes = nOnes;
	this->chromossome = create();
	this->fitness = 0;
	this->coverage = 0;
}


Individual::Individual(int size, int nOnes, vector<bool> &chromossome) {
	this->size = size;
	this->nOnes = nOnes;
	this->chromossome = chromossome;
	this->fitness = 0;
	this->coverage = 0;
}

Individual::Individual(int size, int nOnes, vector<bool> &chromossome,
		float fitness, int coverage) {
	this->size = size;
	this->nOnes = nOnes;
	this->chromossome = chromossome;
	this->fitness = fitness;
	this->coverage = coverage;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}


string Individual::toString() {
	string strIndividual = "";
	for(unsigned i = 0; i < chromossome.size(); i++) {
		strIndividual += chromossome[i];
	}
	return strIndividual;
}

vector<bool> Individual::create() {
	vector<bool> chrom;
	int output;
	set<int> setChrom;

	for(int i = 0; i < this->size; i++)
	{
		chrom.push_back(false);
	}

	while((int)setChrom.size() < this->nOnes)
	{
		output = Randomize::generate_long() % this->size;
//		output = rand() % size;
		setChrom.insert(output);
		chrom[output] = true;
	}

//	for(int i = 0; i < chrom.size(); i++) {
//		cout << chrom[i] << ",";
//	}
//	cout << endl;

	return chrom;
}

bool operator==(Individual &ind1, Individual &ind2) {
	vector<bool> chromossome1 = ind1.getChromossome();
	vector<bool> chromossome2 = ind2.getChromossome();

	if(ind1.getFitness() != ind2.getFitness())
		return false;

	for(unsigned i = 0; i < chromossome1.size(); i++) {
		if(chromossome1[i] != chromossome2[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(Individual &ind1, Individual &ind2) {
	if(ind1 == ind2)
		return false;
	return true;
}

ostream& operator<<(ostream& out, Individual &ind) {
	vector<bool> chromossome = ind.getChromossome();

	for(int i = 0; i < ind.getSize(); i++)
	{
		out << chromossome[i];
	}
//	ind.countOnes();
	out << ";" << ind.getFitness() << ";" << ind.getCoverage();
	return out;
}

//TODO: Needs implementation
Individual Individual::makeCorrection() {
	vector<int> onegenes;
	vector<int> zerogenes;
	for(int i = 0; i < size; i++) {
		if(chromossome[i])
			onegenes.push_back(i);
		else
			zerogenes.push_back(i);
	}

	int index;

	while(onegenes.size() != (unsigned) nOnes) {
		if(onegenes.size() > (unsigned) nOnes) {
			index = Randomize::generate_long() % onegenes.size();
//			index = rand() % onegenes.size();
			chromossome[onegenes[index]] = false;
			int last = onegenes.size() - 1;
			onegenes[index] = onegenes[last];
			onegenes.pop_back();
		} else {
			index = Randomize::generate_long() % zerogenes.size();
//			index = rand() % zerogenes.size();
			chromossome[zerogenes[index]] = true;
			onegenes.push_back(zerogenes[index]);
			int last = zerogenes.size() - 1;
			zerogenes[index] = zerogenes[last];
			zerogenes.pop_back();
		}
	}
	Individual individual = Individual(size, nOnes, chromossome);

	return individual;
}


int Individual::countOnes() {
	int count = 0;
	for(unsigned i = 0; i < chromossome.size(); i++) {
		if(chromossome[i] == true)
			count++;
	}
	return count;
}

