/*
 * Randomize.h
 *
 *  Created on: 01/10/2014
 *      Author: evellyn
 */

#ifndef RANDOMIZE_H_
#define RANDOMIZE_H_

#include <climits>
#include <tr1/random>

using namespace std;

static int random_seed[2] = {860361247, 331938605};//{123, 123}; //
static tr1::variate_generator<tr1::mt19937, tr1::uniform_real<double> > mt_rand_double( tr1::mt19937(random_seed[0]), tr1::uniform_real<double>(0, 1) );
static tr1::variate_generator<tr1::mt19937, tr1::uniform_int<long> > mt_rand_long( tr1::mt19937(random_seed[1]), tr1::uniform_int<long>(0, INT_MAX) );


// C++11 (old TR1) random number generator (using mersenne-twister core engine)
class Randomize
{
public:
	static long generate_long() {return mt_rand_long();}
	static double generate_double() {return mt_rand_double();}
};

#endif /* RANDOMIZE_H_ */
