/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Copyright © 2020 chibayuki@foxmail.com

SudokuAlgorithm.Demo
Version 20.2.20.0000

This file is part of SudokuAlgorithm

SudokuAlgorithm is released under the GPLv3 license
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>

#include "Sudoku.h"

using namespace std;

int main()
{
	Sudoku s = Sudoku::Question(24);
	s.Print();

	cout << endl;

	if (s.TrySolve())
	{
		s.Print();

		cout << endl;
	}
}
