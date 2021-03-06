// Tic_tac_toe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

enum Square {
	EMPTY,
	NOUGHT,
	CROSS
};
enum Row
{
	ROW_1,
	ROW_2,
	ROW_3
};
enum Column
{
	COLUMN_1,
	COLUMN_2,
	COLUMN_3,
};

enum Position_Status {
	USED,
	INVALID,
	WRITE_SUCCESSFULL
};


void showGame(const vector<vector<Square>> &);
void cpu(vector<vector<Square>> &);
Position_Status writePosition(int, vector<vector<Square>> &);
bool playerHasWon(const vector<vector<Square>> &);
int countSquaresInRow(Row, Square, const vector<vector<Square>> &);
int countSquaresInColumn(Column, Square, const vector<vector<Square>> &);
int countSquaresInSecondaryDiagonal(Square, const vector<vector<Square>> &);
int countSquaresInMainDiagonal(Square, const vector<vector<Square>> &);
bool cpuHasWon(const vector<vector<Square>> &);
bool does_exist(const vector<vector<Square>>&, Square);

int main()
{
	vector<Square>row(3, EMPTY);
	vector<vector<Square>>squares(3, row);
	bool mistake = false;
	int input = 0;
	while (true)
	{

		showGame(squares);
		if (playerHasWon(squares))
		{
			cout << "You won!" << endl;
			break;
		}
		if (cpuHasWon(squares))
		{
			cout << "I won!" << endl;
			break;
		}
		if (!playerHasWon(squares) && !cpuHasWon(squares) && !does_exist(squares, EMPTY))
		{
			cout << "It's a tie" << endl;
			break;
		}
		cin >> input;

		switch (writePosition(input, squares))
		{
		case USED:
			cout << "That position has already been used" << endl;
			mistake = true;
			break;
		case INVALID:
			cout << "input must be between between 1 and 9" << endl;
			mistake = true;
			break;
		case WRITE_SUCCESSFULL:
			writePosition(input,squares);
			mistake = false;
			break;
		default:
			break;
		}
		if (!mistake && does_exist(squares, EMPTY))
		{
			cpu(squares);
			system("CLS");
		}

	}


	return 0;
}


void showGame(const vector<vector<Square>> &squares)
{
	for (size_t i = 0; i < squares.size(); i++)
	{
		for (size_t j = 0; j < squares.size(); j++)
		{
			switch (squares[i][j])
			{
			case EMPTY:

				cout << "[?]";
				break;
			case CROSS:
				cout << "[X]";
				break;
			case NOUGHT:

				cout << "[O]";
				break;
			default:
				break;
			}


		}
		cout << endl;
	}
}
Position_Status writePosition(int input, vector<vector<Square>> &squares)
{
	if (input < 1 || 9 < input)
	{
		return INVALID;
	}
	int position = 1;

	for (size_t i = 0; i < squares.size(); i++)
	{
		for (size_t j = 0; j < squares.size(); j++)
		{
			if (position == input && squares[i][j] != EMPTY)
			{

				return USED;
			}
			if (position == input)
			{
				squares[i][j] = CROSS;
				return WRITE_SUCCESSFULL;
			}

			position++;
		}
	}
}
bool playerHasWon(const vector<vector<Square>> &squares)
{
	return countSquaresInRow(ROW_1, CROSS, squares) == 3 || countSquaresInRow(ROW_2, CROSS, squares) == 3 || countSquaresInRow(ROW_3, CROSS, squares) == 3
		|| countSquaresInColumn(COLUMN_1, CROSS, squares) == 3 || countSquaresInColumn(COLUMN_2, CROSS, squares) == 3 || countSquaresInColumn(COLUMN_3, CROSS, squares) == 3
		|| countSquaresInMainDiagonal(CROSS, squares) == 3 || countSquaresInSecondaryDiagonal(CROSS, squares) == 3;
}

bool cpuHasWon(const vector<vector<Square>> &squares)
{
	return countSquaresInRow(ROW_1, NOUGHT, squares) == 3 || countSquaresInRow(ROW_2, NOUGHT, squares) == 3 || countSquaresInRow(ROW_3, NOUGHT, squares) == 3
		|| countSquaresInColumn(COLUMN_1, NOUGHT, squares) == 3 || countSquaresInColumn(COLUMN_2, NOUGHT, squares) == 3 || countSquaresInColumn(COLUMN_3, NOUGHT, squares) == 3
		|| countSquaresInMainDiagonal(NOUGHT, squares) == 3 || countSquaresInSecondaryDiagonal(NOUGHT, squares) == 3;
}
int countSquaresInRow(Row row, Square square, const vector<vector<Square>> &squares)
{
	int no_of_squares = 0;
	for (size_t i = 0; i < squares.size(); i++)
	{
		if (squares[row][i] == square)
		{
			no_of_squares++;
		}
	}
	return no_of_squares;
}

int countSquaresInColumn(Column column, Square square, const vector<vector<Square>> &squares)
{
	int no_of_squares = 0;
	for (size_t i = 0; i < squares.size(); i++)
	{
		if (squares[i][column] == square)
		{
			no_of_squares++;
		}
	}
	return no_of_squares;
}



int countSquaresInMainDiagonal(Square square, const vector<vector<Square>> &squares)
{
	int no_of_squares = 0;
	for (size_t i = 0; i < squares.size(); i++)
	{
		if (squares[i][i] == square)
		{
			no_of_squares++;
		}
	}
	return no_of_squares;
}

int countSquaresInSecondaryDiagonal(Square square, const vector<vector<Square>> &squares)
{
	int no_of_squares = 0;
	for (size_t i = 0; i < squares.size(); i++)
	{
		if (squares[i][2 - i] == square)
		{
			no_of_squares++;
		}
	}
	return no_of_squares;
}



void cpu(vector<vector<Square>> &squares)
{

	if (countSquaresInColumn(COLUMN_1, CROSS, squares) == 2)
	{
		for (size_t i = 0; i < squares.size(); i++)
		{

			if (squares[i][COLUMN_1] == EMPTY)
			{
				squares[i][COLUMN_1] = NOUGHT;
				return;
			}

		}
	}

	if (countSquaresInColumn(COLUMN_2, CROSS, squares) == 2)
	{
		for (size_t i = 0; i < squares.size(); i++)
		{

			if (squares[i][COLUMN_2] == EMPTY)
			{
				squares[i][COLUMN_2] = NOUGHT;
				return;
			}

		}
	}

	if (countSquaresInColumn(COLUMN_3, CROSS, squares) == 2)
	{
		for (size_t i = 0; i < squares.size(); i++)
		{

			if (squares[i][COLUMN_3] == EMPTY)
			{
				squares[i][COLUMN_3] = NOUGHT;
				return;
			}

		}
	}

	if (countSquaresInRow(ROW_1, CROSS, squares) == 2)
	{
		for (size_t i = 0; i < squares.size(); i++)
		{
			if (squares[ROW_1][i] == EMPTY)
			{
				squares[ROW_1][i] = NOUGHT;
				return;
			}
		}
	}

	if (countSquaresInRow(ROW_2, CROSS, squares) == 2)
	{
		for (size_t i = 0; i < squares.size(); i++)
		{
			if (squares[ROW_2][i] == EMPTY)
			{
				squares[ROW_2][i] = NOUGHT;
				return;
			}
		}
	}

	if (countSquaresInRow(ROW_3, CROSS, squares) == 2)
	{
		for (size_t i = 0; i < squares.size(); i++)
		{
			if (squares[ROW_3][i] == EMPTY)
			{
				squares[ROW_3][i] = NOUGHT;
				return;
			}
		}
	}
	if (countSquaresInMainDiagonal(CROSS, squares) == 2)
	{
		for (size_t i = 0; i < squares.size(); i++)
		{
			if (squares[i][i] == EMPTY)
			{
				squares[i][i] = NOUGHT;
				return;
			}
		}
	}

	if (countSquaresInSecondaryDiagonal(CROSS, squares) == 2)
	{
		for (size_t i = 0; i < squares.size(); i++)
		{
			if (squares[i][2 - i] == EMPTY)
			{
				squares[i][2 - i] = NOUGHT;
				return;
			}
		}
	}
	srand(time(NULL));
	int x, counter;
	bool found = false;
	while (found == false)
	{
		x = rand() % 9 + 1;
		counter = 1;
		for (int i = 0; i < squares.size(); i++)
		{
			for (int j = 0; j < squares.size(); j++)
			{
				if (counter == x)
				{//squares[i][j] != CROSS && squares[i][j] != NOUGHT
					if (squares[i][j]==EMPTY)
					{
						squares[i][j] = NOUGHT;
						found = true;
					}
				}
				counter++;
			}
		}
	}


}

bool does_exist(const vector<vector<Square>>&  v, Square item) {

	vector< vector<Square>>::const_iterator row;

	for (row = v.begin(); row != v.end(); row++) {
		if (find(row->begin(), row->end(), item) != row->end())
			return true;
	}

	return false;
}

