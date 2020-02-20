/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Copyright © 2020 chibayuki@foxmail.com

SudokuAlgorithm.BitOperation
Version 20.2.20.0000

This file is part of SudokuAlgorithm

SudokuAlgorithm is released under the GPLv3 license
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include <cstdint>
#include <vector>

using namespace std;

class BitOperation
{
private:
	inline BitOperation() { }

	inline virtual ~BitOperation() { }

	inline BitOperation(const BitOperation&) { }

	inline BitOperation& operator=(const BitOperation&) 
	{ 
		return *this; 
	}

public:
	inline static void AddBit(uint32_t& bin, size_t bit)
	{
		bin |= (1U << bit);
	}

	inline static void RemoveBit(uint32_t& bin, size_t bit)
	{
		bin &= (~(1U << bit));
	}

	inline static void InverseBit(uint32_t& bin, size_t bit)
	{
		bin ^= (1U << bit);
	}

	inline static bool TestBit(uint32_t bin, size_t bit)
	{
		return ((bin & (1U << bit)) != 0);
	}

	inline static size_t GetBit1Count(uint32_t bin)
	{
		size_t count = 0;

		while (bin > 0)
		{
			bin &= (bin - 1);

			count++;
		}

		return count;
	}

	inline static vector<size_t> GetBit1Index(uint32_t bin)
	{
		vector<size_t> result;

		for (size_t i = 0; i < 32; i++)
		{
			if ((bin & 1) != 0)
			{
				result.push_back(i);
			}

			bin >>= 1;
		}

		return result;
	}
};
