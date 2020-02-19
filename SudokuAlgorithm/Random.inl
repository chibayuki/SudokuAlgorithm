/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Copyright © 2019 chibayuki@foxmail.com

SudokuAlgorithm.Random
Version 20.2.17.0000

This file is part of SudokuAlgorithm

SudokuAlgorithm is released under the GPLv3 license
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <ctime>

class Random
{
public:
	inline Random()
	{
		srand((uint32_t)time(nullptr));
	}
	
	inline Random(uint32_t seed) 
	{
		srand(seed);
	}

	inline virtual ~Random() { }

	inline Random(const Random&) { }

	inline Random& operator=(const Random&) 
	{
		return *this;
	}

	inline int32_t Next()
	{
		return rand();
	}

	inline int32_t Next(int32_t max)
	{
		return rand() % max;
	}

	inline int32_t Next(int32_t min, int32_t max)
	{
		return min + rand() % (max - min);
	}
};
