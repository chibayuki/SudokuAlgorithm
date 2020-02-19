/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Copyright © 2019 chibayuki@foxmail.com

SudokuAlgorithm.Sudoku
Version 20.2.17.0000

This file is part of SudokuAlgorithm

SudokuAlgorithm is released under the GPLv3 license
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Sudoku.h"

using namespace std;

void Sudoku::_CalcProbableValues()
{
    uint32_t All = 1;

    for (int i = 0; i < _Side; i++)
    {
        All = (All << 1) + 1;
    }

    //

    uint32_t PV_Row[_Side];
    uint32_t PV_Column[_Side];
    uint32_t PV_Matrix[_Order][_Order];

    for (int32_t i = 0; i < _Side; i++)
    {
        PV_Row[i] = All;
        PV_Column[i] = All;
        PV_Matrix[i % _Order][i / _Order] = All;
    }

    //

    for (int32_t Y = 0; Y < _Side; Y++)
    {
        for (int32_t X = 0; X < _Side; X++)
        {
            BitOperation::RemoveBit(PV_Row[Y], _Data[X][Y]);
        }
    }

    for (int32_t X = 0; X < _Side; X++)
    {
        for (int32_t Y = 0; Y < _Side; Y++)
        {
            BitOperation::RemoveBit(PV_Column[X], _Data[X][Y]);
        }
    }

    for (int32_t X = 0; X < _Order; X++)
    {
        for (int32_t Y = 0; Y < _Order; Y++)
        {
            int32_t _X = X * _Order, _Y = Y * _Order;

            for (int32_t y = _Y; y < _Y + _Order; y++)
            {
                for (int32_t x = _X; x < _X + _Order; x++)
                {
                    BitOperation::RemoveBit(PV_Matrix[X][Y], _Data[x][y]);
                }
            }
        }
    }

    //

    for (int32_t X = 0; X < _Side; X++)
    {
        for (int32_t Y = 0; Y < _Side; Y++)
        {
            _ProbableValues[X][Y] = 0;

            if (_Data[X][Y] == 0)
            {
                for (int32_t i = 1; i <= _Side; i++)
                {
                    if (BitOperation::TestBit(PV_Row[Y], i) && BitOperation::TestBit(PV_Column[X], i) && BitOperation::TestBit(PV_Matrix[X / _Order][Y / _Order], i))
                    {
                        BitOperation::AddBit(_ProbableValues[X][Y], i);
                    }
                }
            }
        }
    }
}

bool Sudoku::_Recursion()
{
    int32_t MinProbableCnt = _Side + 1;
    int32_t MinProbableID_X = -1, MinProbableID_Y = -1;
    bool SudokuIsFull = true;

    for (int32_t X = 0; X < _Side; X++)
    {
        for (int32_t Y = 0; Y < _Side; Y++)
        {
            if (_Data[X][Y] == 0)
            {
                int32_t Count = BitOperation::GetBit1Count(_ProbableValues[X][Y]);

                if (Count == 0)
                {
                    return false;
                }
                else
                {
                    if (MinProbableCnt > Count)
                    {
                        MinProbableCnt = Count;
                        MinProbableID_X = X;
                        MinProbableID_Y = Y;
                        SudokuIsFull = false;
                    }

                    if (MinProbableCnt == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

    //

    if (SudokuIsFull)
    {
        return true;
    }
    else
    {
        vector<size_t> Values = BitOperation::GetBit1Index(_ProbableValues[MinProbableID_X][MinProbableID_Y]);

        Random rand;

        for (int32_t i = 0; i < Values.size(); i++)
        {
            int32_t Index = rand.Next(Values.size());

            int32_t Temp = Values[i];
            Values[i] = Values[Index];
            Values[Index] = Temp;
        }

        for (int32_t i = 0; i < Values.size(); i++)
        {
            int32_t Num = Values[i];

            _Data[MinProbableID_X][MinProbableID_Y] = Num;

            uint32_t PVT_Row[_Side];
            uint32_t PVT_Column[_Side];
            uint32_t PVT_Matrix[_Order][_Order];

            int32_t X = MinProbableID_X / _Order * _Order, Y = MinProbableID_Y / _Order * _Order;

            for (int32_t j = 0; j < _Side; j++)
            {
                PVT_Row[j] = _ProbableValues[MinProbableID_X][j];
                PVT_Column[j] = _ProbableValues[j][MinProbableID_Y];
                PVT_Matrix[j % _Order][j / _Order] = _ProbableValues[X + j % _Order][Y + j / _Order];
            }

            for (int32_t j = 0; j < _Side; j++)
            {
                BitOperation::RemoveBit(_ProbableValues[MinProbableID_X][j], Num);
                BitOperation::RemoveBit(_ProbableValues[j][MinProbableID_Y], Num);
                BitOperation::RemoveBit(_ProbableValues[X + j % _Order][Y + j / _Order], Num);
            }

            if (_Recursion())
            {
                return true;
            }
            else
            {
                _Data[MinProbableID_X][MinProbableID_Y] = 0;

                for (int32_t j = 0; j < _Side; j++)
                {
                    _ProbableValues[MinProbableID_X][j] = PVT_Row[j];
                    _ProbableValues[j][MinProbableID_Y] = PVT_Column[j];
                    _ProbableValues[X + j % _Order][Y + j / _Order] = PVT_Matrix[j % _Order][j / _Order];
                }
            }
        }

        return false;
    }
}

Sudoku::Sudoku()
{
    memset(&_Data, 0, sizeof(int32_t) * _Count);
}

Sudoku::Sudoku(initializer_list<initializer_list<int32_t>> data) :
    Sudoku()
{
    for (int32_t i = 0; i < _Side && i < data.size(); i++)
    {
        const initializer_list<int32_t>* il = data.begin() + i;

        for (int32_t j = 0; j < _Side && j < il->size(); j++)
        {
            int32_t d = *(il->begin() + j);

            if (d > 0 && d <= _Side)
            {
                _Data[i][j] = d;
            }
        }
    }
}

Sudoku::~Sudoku()
{
}

Sudoku::Sudoku(const Sudoku& sudoku)
{
    memcpy(&_Data, &sudoku._Data, sizeof(int32_t) * _Count);
}

Sudoku& Sudoku::operator=(const Sudoku& sudoku)
{
    memcpy(&_Data, &sudoku._Data, sizeof(int32_t) * _Count);

    return *this;
}

bool Sudoku::TrySolve(const Sudoku& sudoku, Sudoku& result)
{
    Sudoku copy = sudoku;

    copy._CalcProbableValues();

    if (copy._Recursion())
    {
        result = copy;

        return true;
    }

    return false;
}

Sudoku Sudoku::Question(size_t knownCount)
{
    vector<size_t> Values;

    for (int32_t i = 1; i <= _Side; i++)
    {
        Values.push_back(i);
    }

    Random rand;

    for (int32_t i = 0; i < Values.size(); i++)
    {
        int32_t Index = rand.Next(Values.size());

        int32_t Temp = Values[i];
        Values[i] = Values[Index];
        Values[Index] = Temp;
    }

    Sudoku sudoku;

    for (int32_t i = 0; i < _Side; i++)
    {
        int32_t X = i % _Order, Y = i / _Order;

        sudoku._Data[X * _Order + Y][Y * _Order + X] = Values[i];
    }

    //

    TrySolve(sudoku, sudoku);

    //

    int32_t EmptyCount = _Count - knownCount;

    vector<size_t> Zeros;

    while (Zeros.size() < EmptyCount)
    {
        size_t Z = rand.Next(_Count);

        bool Contains = false;

        for (int32_t i = 0; i < Zeros.size(); i++)
        {
            if (Zeros[i] == Z)
            {
                Contains = true;

                break;
            }
        }

        if (!Contains)
        {
            Zeros.push_back(Z);
        }
    }

    for (int32_t i = 0; i < Zeros.size(); i++)
    {
        sudoku._Data[Zeros[i] % _Side][Zeros[i] / _Side] = 0;
    }

    return sudoku;
}

#if DEBUG
void Sudoku::Print()
{
    for (int i = 0; i < _Side; i++)
    {
        for (int j = 0; j < _Side; j++)
        {
            int32_t d = _Data[i][j];

            if (_Side < 10)
            {
                if (d > 0)
                {
                    cout << d;
                }
                else
                {
                    cout << '_';
                }
            }
            else if (_Side < 100)
            {
                if (d >= 10)
                {
                    cout << d;
                }
                else if (d > 0)
                {
                    cout << ' ' << d;
                }
                else
                {
                    cout << "__";
                }
            }

            if (j < _Side - 1)
            {
                cout << ' ';
            }
        }

        cout << endl;
    }
}
#endif
