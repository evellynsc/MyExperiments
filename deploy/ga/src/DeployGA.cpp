/*
 * DeployGA.cpp
 *
 *  Created on: 22/09/2014
 *      Author: evellyn
 */

#include "DeployGA.h"

DeployGA::DeployGA(StatisticCollector* statistic, DeployProblem* problem, PopulationInitialization* popInit, Selection* selection,
		Crossover* crossover, Mutation* mutation, LocalSearch* local_search) {
	this->problem = problem;
	this->popInit = popInit;
	this->selection = selection;
	this->crossover = crossover;
	this->mutation = mutation;
	this->statistic = statistic;
	this->localsearch = local_search;
	ngeneration = 10;
	probMutation = 0.1;
	probCrossover = 0.8;
	probLocalSearch = 0.5;
	tolerance = 0.001;
	nones = problem->getNrsu();
}

DeployGA::~DeployGA() {
	delete problem;
	delete popInit;
	delete selection;
	delete crossover;
	delete mutation;
	delete statistic;
}

/*
 * Preservar 5% melhores da população antiga
 */
void DeployGA::prune_population(vector<Individual> newpopulation) {
//	int npop = popInit->get_size();
//	int replace = 0.05*npop;
//	int j = npop;
	vector<Individual> oldpopulation = this->population;
	this->population.clear();
	this->population = newpopulation;
	evaluate();
//	population[0] = oldpopulation[npop-1];
//	float prob;
//	for(int i = 0; i < replace; i++) {
//		prob = Randomize::generate_double();
//		j--;
//		if(!exist_individual(oldpopulation[j])) {
//			population[i] = oldpopulation[j];
//		} else {
//			if(prob <= 0.1) {
//				population[i] = oldpopulation[j];
//			}
//		}
//
//	}
	sort(population.begin(), population.end(), individual_sort);
}

bool DeployGA::exist_individual(Individual individual) {
	int npop = popInit->get_size();
	for(int i = 0; i < npop; i++) {
		if(individual == population[i])
			return true;
	}
	return false;
}

void DeployGA::set_parameters(int ngen, float probCross, float probMut, float probLocalsearch,
		float tol) {
	this->ngeneration = ngen;
	this->probCrossover = probCross;
	this->probMutation = probMut;
	this->probLocalSearch = probLocalsearch;
	this->tolerance = tol;
	population = popInit->run();
}

Individual DeployGA::get_best() {
	return Individual(0,0);
}

Individual DeployGA::get_worst() {
	return Individual(0,0);
}

void DeployGA::run() {
	vector<Individual> newPopulation;
	vector<Individual> offspring;
	int currentGeneration = 0;
	int sample_size = this->statistic->getSampleSize();
	int npop = popInit->get_size();

	evaluate();
	statistic->analyse(this->population);

	//	TODO: Acrescentar outro método de parada
	while(currentGeneration != ngeneration) {
		cout << "g" << currentGeneration << " ";

		newPopulation.clear();
		offspring.clear();

		while((int) newPopulation.size() < npop) {
			//			cout << "selection...";
			Individual parent1 = selection->run(population);
			Individual parent2 = selection->run(population);

			float prob = Randomize::generate_double();
			//			prob = (float)rand() / RAND_MAX;

			//			cout << "crossover...";
			if(prob <= this->probCrossover) {
				offspring = crossover->run(parent1, parent2);
				for(unsigned i = 0; i < offspring.size(); i++) {
					if(offspring[i].getOnes() != problem->getNrsu()) {
						offspring[i].setOnes(problem->getNrsu());
						offspring[i] = offspring[i].makeCorrection();
					}
					//					cout << "mutation...";
					prob = Randomize::generate_double();
					//					prob = (float)rand() / RAND_MAX;

					if(prob <= this->probMutation) {
						offspring[i] = mutation->run(offspring[i]);
					}

					prob = Randomize::generate_double();
					//					prob = (float)rand() / RAND_MAX;

					if(prob <= this->probLocalSearch) {
						offspring[i] = localsearch->run(offspring[i]);
					}
					newPopulation.push_back(offspring[i]);
				}
			}
		}
		prune_population(newPopulation);
		currentGeneration++;
		if(!(currentGeneration%sample_size)) {
			statistic->analyse(this->population);
		}
	}
//	for(int i = 0; i < npop; i++) {
//		cout << "last " << population[i] << endl;
//	}
	cout << endl;
}

void DeployGA::evaluate() {
	//	cout << "evaluate..." << endl;
	vector<int> genes;
	float fitness;
	int coverage;
	int npop = popInit->get_size();
	int ind_size = problem->getNintersections();
	for(int i = 0; i < npop; i++) {
		genes.clear();
		vector<bool> chromossome = population[i].getChromossome();
		if(population[i].getOnes() == nones) {
			for(int j = 0; j < ind_size; j++) {
				if(chromossome[j]){
					genes.push_back(j);
				}
			}
			coverage = problem->getCoverage(genes);
			fitness = (float)coverage/problem->getNvehicles();
		} else {
			fitness = 0;
			coverage = 0;
		}
		population[i].setFitness(fitness);
		population[i].setCoverage(coverage);
	}
	sort(population.begin(), population.end(), individual_sort);
}
//n this basic framework, you can't end up with an empty population.
//You'll always have N individuals in the population and you'll always
//generate N offspring. At the end of each generation, you'll take those
//2N individuals and prune them down to N again. You can either throw
//all the parents away and just do P = C (generational replacement),
//you can keep a few members of P and replace the rest with members
//of C (elitist replacement), you can merge them together and take the
//best N of the 2N total (truncation replacement), or whatever other
//scheme you come up with.
