// eightqueens.cpp
//

/*
	Using recursion, and sets, find a solution to the eight queen's problem.
*/

#include <iostream>
#include <algorithm>
#include <utility>
#include <set>
#include <array>
#include <cassert>

using namespace std;

const unsigned MaxRows = 8;
const unsigned MaxCols = 8;

using BoardMatrix = std::array<std::array<bool, MaxRows>, MaxCols>;
using Coord = std::pair<unsigned, unsigned>;
using Delta = std::pair<unsigned, unsigned>;
using IndexSet = set<unsigned>;

bool validDiagonal(BoardMatrix &b, int row, int col,
	int deltaRow, int deltaCol)
{
	while (row >= 0 && col >= 0 && col < MaxCols)
	{
		if ( b[row][col])
			return false;
		row += deltaRow;
		col += deltaCol;
	}

	return true;
}

// Check left and right digaonal starting from (row, col)
bool validDiagonals(BoardMatrix &b, int row, int col)
{
	if (!validDiagonal(b, row - 1, col - 1, -1, -1))
		return false;
	if (!validDiagonal(b, row - 1, col + 1, -1, 1))
		return false;

	return true;
}

bool findSolution( BoardMatrix &b, IndexSet &used, unsigned row)
{
	if (row >= MaxRows)
		return true;

	int col = 0;
	// Loop over unused positions in current row, searching
	// for a valid solution
	while (col < MaxCols)
	{
		// Choose next unused
		set<unsigned>::iterator it;
		for (; col < MaxCols; ++col)
		{
			it = used.find(col);
			if (it == used.end())
				break;
		}
		if (it != used.end())
			return false;

		// Check if this position results in a potential solution
		// If the the solution is not invalid, recursively search
		// for a valid solution for remaining rows
		b[row].fill(false);
		b[row][col] = true;
		if (validDiagonals(b, row, col))
		{
			if (row == MaxRows - 1)
				return true;
			used.insert( col);
			if (findSolution(b, used, row + 1))
			{
				return true;
			}
			used.erase( col);
		}
		++col;
	}

	return false;
}

int main()
{
	BoardMatrix b { false };
	IndexSet used; // Used indexes

	bool found = findSolution( b, used, 0);
	if (found)
	{
		cout << "Found solution:" << endl;
		for (unsigned i = 0; i < MaxRows; ++i)
		{
			for_each( b[i].begin(), b[i].end(), [](bool b) { cout << (b ? 'Q' : '*'); });
			cout << endl;
		}
	}
}
