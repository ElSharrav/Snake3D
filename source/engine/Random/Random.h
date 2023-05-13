#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
	static std::random_device rd;
	static std::default_random_engine e;

public:
	// generate random int in range [min,max)
	static int randInt(int min, int max);
	static float randFloat(float min, float max);

	// recommend using for small ranges max-min
	static int* randArrayWithoutRepetitions(int min, int max, int n);
};

#endif