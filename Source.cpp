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

using BoardMatrix = std::array<std::array<bool, 8>, 8>;
using Coord = std::pair<unsigned, unsigned>;
using Delta = std::pair<unsigned, unsigned>;

// Valid diagonals is simple, because we can assume only the current row may have created an invalid diagonal
// So we just look at upper left and upper right position.
bool validDiagonals(BoardMatrix &m, int row, int col)
{
	if (row - 1 < 0)
		return true;
	if (col - 1 >= 0)
		if (m[row-1][col - 1])
			return false;
	if ( col + 1 < 8)
		if (m[row-1][col + 1])
			return false;
	return true;
}

bool findSolution(BoardMatrix &m, unsigned row)
{
	if (row >= 8)
		return true;

	// Possible optimzation would be to dynamically add and remove to/from the set ( as opposed to rebuilding it every time)
	set<unsigned> used;
	// Create a set of used indexes
	for (unsigned i = 0; i < row; ++i)
	{
		auto it = find(m[i].begin(), m[i].end(), true);
		used.insert(it - m[i].begin());
	}

	int col = 0;
	// Loop over unused positions in current row, searching
	// for a valid solution
	while ( col < 8)
	{
		// Choose next unused
		set<unsigned>::iterator it;
		for ( ; col < 8; ++col)
		{
			it = used.find( col);
			if (it == used.end())
				break;
		}
		if ( it != used.end())
			return false;

		// Check if this position results in a potential solution
		// If the the solution is not invalid, recursively search
		// for a valid solution for remaining rows
		m[row].fill( false);
		m[row][col] = true;
		if ( validDiagonals( m, row, col))
		{
			if (row == 7)
				return true;
			if (findSolution(m, row + 1))
			{
				return true;
			}
		}
		++col;
	}

	return false;
}

int main()
{
	BoardMatrix m{ false };

	bool found = findSolution(m, 0);
	if (found)
	{
		cout << "Found solution:" << endl;
		for (unsigned i = 0; i < 8; ++i)
		{
			for_each(m[i].begin(), m[i].end(), [](bool b) { cout << (b ? 'Q' : '*'); });
			cout << endl;
		}
	}
}
