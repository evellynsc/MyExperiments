/*
 * StatisticCollector.cpp
 *
 *  Created on: 12/09/2014
 *      Author: evellyn
 */

#include "StatisticCollector.h"

StatisticCollector::StatisticCollector(int sample_size, string path) {
	this->sample_size = sample_size;
	this->path = path;
}

StatisticCollector::~StatisticCollector() {
	// TODO Auto-generated destructor stub
}

void StatisticCollector::analyse(vector<Individual> population) {
	this->best.push_back(population[population.size()-1]);
	this->worst.push_back(population[0]);
	float mean_fitness = 0;
	int different = 0;
	for(unsigned i = 0; i < population.size(); i++) {
		mean_fitness += population[i].getFitness();
		if(i != population.size()-1) {
			if(population[i+1]!=population[i])
				different++;
		}
	}
	this->mean.push_back(mean_fitness/population.size());
	this->repeated_individuals.push_back(population.size()-different);
}

void StatisticCollector::write() {
	ofstream ofile;
	ofile.open(this->path.c_str(), ios::app);
	ofile << "geração;melhor;fitness;cobertura;pior;fitness;cobertura;média;ind_repetidos\n";
	for(int i = 0; i < (int)best.size(); i = i + sample_size) {
		ofile << i << ";";
		ofile << best[i] << ";";
		ofile << worst[i] << ";";
		ofile << mean[i] << ";";
		ofile << repeated_individuals[i] << endl;
//			ofile << best[i].toString() << ";";
//			ofile << worst_fitness[i].toString() << ";";
//			ofile << mean_fitness[i] << ";";
//			ofile << best_worst_children[i].first << ";";
//			ofile << best_worst_children[i].second << ";";
//			ofile << repeated_individuals[i];
//			ofile << endl;
	}
	ofile << "=============================================" << endl;
}

void StatisticCollector::empty() {
	best.clear();
	worst.clear();
	mean.clear();
	repeated_individuals.clear();
}
