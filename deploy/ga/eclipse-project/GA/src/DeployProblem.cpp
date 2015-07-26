/*
 * DeployProblem.cpp
 *
 *  Created on: 25/09/2014
 *      Author: evellyn
 */

#include "DeployProblem.h"

DeployProblem::DeployProblem(int nrsu, int requiredTime, string path) {
	loadData(path);
	nvehicles = table[0].size();
	nintersections = table.size();
	this->requiredTime = requiredTime;
	this->nrsu = nrsu;
	processData();
}

DeployProblem::~DeployProblem() {
}

void DeployProblem::loadData(string path) {
	ifstream file(path.c_str());
	if(file.fail()) {
		cerr << "Falha na abertura do arquivo de dados.\n";
		exit(1);
	}
	while(!file.eof())
	{
		string line;
		getline(file, line);
		if(file.eof()) break;
		istringstream is(line);
		vector<int> row;
		while (is)
		{
			int data;
			is >> data;
			row.push_back(data);
			if(is.eof()) break;
		}
		table.push_back(row);
	}
//	cout << table.size() << " linhas/interseções" << endl;
//	cout << table[1].size() << " colunas/veículos" << endl;
//	cout << "Read.\n";
}

void DeployProblem::processData() {
	int total_time = 0;
	int total_vehicles = 0;
	for(unsigned i = 0; i < table.size(); i++) {
		vector<int> row = table[i];
		int tvehicle = 0;
		int ttime = 0;
		for(unsigned j = 0; j < row.size(); j++) {
			if(row[j] != 0) {
				tvehicle++;
				ttime += row[j];
			}
		}
		total_time += ttime;
		total_vehicles += tvehicle;
		pair<int, int> vehicle(i,tvehicle);
		pair<int, int> time(i,ttime);
		pair<int, float> mean(i, (float)ttime/tvehicle);
		vehicles_through_intersection.push_back(vehicle);
		time_at_intersection.push_back(time);
		mean_time_at_intersection.push_back(mean);
	}
	mean_time = (float)total_time/(float)nintersections;
	mean_vehicles = (float)total_vehicles/(float)nintersections;

	sort(vehicles_through_intersection.begin(), vehicles_through_intersection.end(), decreased_pair_sort);
	sort(time_at_intersection.begin(), time_at_intersection.end(), decreased_pair_sort);
	sort(mean_time_at_intersection.begin(), mean_time_at_intersection.end(), decreased_pair_sort);

	//	for(unsigned i = 0; i < vehiclesThroughIntersections.size(); i++) {
	//		cout << "(" << vehiclesThroughIntersections[i].first << "," << vehiclesThroughIntersections[i].second << ") ";
	//		cout << "(" << timeAtIntersections[i].first << "," << timeAtIntersections[i].second << ") ";
	//		cout << "(" << meanTimeAtIntersection[i].first << "," << meanTimeAtIntersection[i].second << ")" << endl ;
	//	}
}

int DeployProblem::getCoverage(vector<int> intersections) {
	int coveredVehicles = 0;
	int sum = 0;

	for(int i = 0; i < nvehicles; i++) {
		sum = 0;
		for(unsigned j = 0; j < intersections.size(); j++) {
			sum += table[intersections[j]][i];
			if(sum >= this->requiredTime){
				coveredVehicles++;
				break;
			}
		}
	}
	//	coverage = (float) coveredVehicles/nvehicles;
	return coveredVehicles;
}




