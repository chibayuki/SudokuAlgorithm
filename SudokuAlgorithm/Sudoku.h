/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Copyright © 2019 chibayuki@foxmail.com

SudokuAlgorithm.Sudoku
Version 20.2.17.0000

This file is part of SudokuAlgorithm

SudokuAlgorithm is released under the GPLv3 license
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#define DEBUG (1)

#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <iostream>

#include "BitOperation.inl"
#include "Random.inl"

using namespace std;

class Sudoku
{
private:
	enum { _Order = 3, _Side = 9, _Count = 81 };
	//enum { _Order = 4, _Side = 16, _Count = 256 };

	int32_t _Data[_Side][_Side];
	uint32_t _ProbableValues[_Side][_Side];

	void _CalcProbableValues();
	bool _Recursion();

	Sudoku();

public:
	Sudoku(initializer_list<initializer_list<int32_t>> data);
	virtual ~Sudoku();
	Sudoku(const Sudoku& sudoku);
	Sudoku& operator=(const Sudoku& sudoku);

	static bool TrySolve(const Sudoku& sudoku, Sudoku& result);
	static Sudoku Question(size_t knownCount);

#if DEBUG
public:
	void Print();
#endif
};