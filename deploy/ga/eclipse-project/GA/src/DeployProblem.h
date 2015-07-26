/*
 * DeployProblem.h
 *
 *  Created on: 25/09/2014
 *      Author: evellyn
 */

#ifndef DEPLOYPROBLEM_H_
#define DEPLOYPROBLEM_H_

#include "Individual.h"
#include "utils/Sort.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <utility>
#include <cmath>
#include <map>

class DeployProblem {
	vector< vector<int> > table;
	vector< pair<int, int> > vehicles_through_intersection;
	vector< pair<int, int> > time_at_intersection;
	vector< pair<int, float> > mean_time_at_intersection;
	float mean_time;
	float mean_vehicles;
	int nintersections;
	int nvehicles;
	int requiredTime;
	int nrsu;
	void loadData(string);
	void processData();

public:
	DeployProblem(int, int, string);
	virtual ~DeployProblem();
	int getCoverage(vector<int>);
	float analyse(Individual);

	vector< vector<int> > getTable() const {
		return table;
	}

	int getNintersections() const {
		return this->nintersections;
	}

	void setNintersections(int nintersections) {
		this->nintersections = nintersections;
	}

	int getNrsu() const {
		return nrsu;
	}

	void setNrsu(int nrsu) {
		this->nrsu = nrsu;
	}

	int getNvehicles() const {
		return nvehicles;
	}

	void setNvehicles(int nvehicles) {
		this->nvehicles = nvehicles;
	}

	int getRequiredTime() const {
		return requiredTime;
	}

	void setRequiredTime(int requiredTime) {
		this->requiredTime = requiredTime;
	}

	float getMeanTime() const {
		return mean_time;
	}

	const vector<pair<int, float> >& getMeanTimeAtIntersection() const {
		return mean_time_at_intersection;
	}

	float getMeanVehicles() const {
		return mean_vehicles;
	}

	const vector<pair<int, int> >& getTimeAtIntersection() const {
		return time_at_intersection;
	}

	const vector<pair<int, int> >& getVehiclesThroughIntersection() const {
		return vehicles_through_intersection;
	}
};

#endif /* DEPLOYPROBLEM_H_ */
