//Row reducing matrices

#include "stdafx.h"				//Comment out if not using Visual Studio.
#include <conio.h>				//Where _getch() is found. If not using Visual Studio, comment out.
#include <iostream>
#include <iomanip>				//setprecision is found here.
using namespace std;

void swap(int x, int y);
void comb(int x, int y, int z);		//Forward declaration of row op functions.
void divi(int x, int y);

int nRows;
int nCols;
double thematrix [8][8];

int main()
{
	cout << "Enter the number of rows :";
	cin >> nRows;

	cout << "Enter the number of columns :";
	cin >> nCols;

	cout << "\n\nEnter matrix elements left-to-right, top-to-bottom: \n";
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			cin >> thematrix[i][j];
		}
	}

	cout << endl;
	cout << endl;									//Making it look cleaner.

	int colCount = 1;								//colCount must start at 1 because matrix value
	for (int i = 0; i < nRows; i++)					//is outputted before the column check.
	{
		for (int j = 0; j < nCols; j++)
		{
			cout << thematrix[i][j] << "\t";		//Outputs matrix before reducing.
			if (colCount == nCols)
			{
				cout << "\n";
				colCount = 0;
			}
			colCount = colCount + 1;
		}
	}
	cout << "Above is the matrix to be reduced.\n\n" << endl;
	
	cout << "Press any key to continue . . . ";
	_getch();										//Asks for input before continuing. Comment out if not using Visual Studio.
	cout << "\n\n";

	////////////////////////////////////////
	//Goes through matrix and determines proper action.
	colCount = 0;
	for (int i = 0; i < nRows; i++)
	{
	emptyCol:					//goto statement label to be returned to
			;					//if a zero column is found.
		bool pivPos = false;
		for (int m = i; m < nRows; m++)			//Checking if values in column aren't 0.
		{
			if (thematrix[m][colCount] != 0)
			{
				pivPos = true;
				swap(m, i);
				if (i == nRows - 1)				//Checking if it's the last row in matrix.
				{
					divi(i, colCount);			//If last row, dividing by value in pivot position.
				}
				else
				{
					for (int n = i + 1; n < nRows; n++)
					{
						comb(i, n, colCount);
						divi(i, colCount);
					}
				}
				goto fin;
			}
		}
		if (pivPos == false)
		{
			colCount = colCount + 1;			//Zero column is found so next column to be tried
			goto emptyCol;						//and process returns to "emptyCol".
		}
		fin:
		colCount = colCount + 1;				//Next column once row operations are done.
	}


	//////////////////////////////////////
	//Row reducing algorithm.
	colCount = 0;
	for (int i = 0; i < nRows; i++)
	{
		aorta:
		if (thematrix[i][colCount] != 0)
		{
			for (int m = i - 1; m > -1; m--)
			{
				comb(i, m, colCount);
			}
		}
		else
		{
			colCount = colCount + 1;
			goto aorta;
		}
		colCount = colCount + 1;
	}


	//////////////////////////////////////
	colCount = 1;									//Same output code as earlier.
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			cout << setprecision(3) << thematrix[i][j] << "\t";		//Outputs reduced echelon form of original matrix.
			if (colCount == nCols)
			{
				cout << "\n";
				colCount = 0;
			}
			colCount = colCount + 1;
		}
	}
	cout << "Above is the row reduced echelon form of your matrix.\n\n" << endl;


	//cout << "Press any key to continue . . . ";
	//_getch();										//Asks for input before continuing. Change _getch() to getch() if not using VS.


	return 0;
}


//Row operation functions
void swap(int x, int y)					//Parameters are rows to be swapped; order doesn't matter.
{
	for (int j = 0; j < nCols; j++)
	{
		double temp = thematrix[x][j];
		thematrix[x][j] = thematrix[y][j];
		thematrix[y][j] = temp;
	}
}

void comb(int x, int y, int z)			//Parameters are row to be multiplied/divided, row to be changed, and
{										//pivot column of the row, respectively.
	double visor = thematrix[y][z] / thematrix[x][z];
	for (int j = z; j < nCols; j++)
	{
		thematrix[y][j] = thematrix[y][j] - (thematrix[x][j] * visor);
	}
}

void divi(int x, int z)					//Parameters are row to be multiplied/divided and pivot column,
{										//respectively.
	double visor = thematrix[x][z];
	for (int j = z; j < nCols; j++)
	{
		thematrix[x][j] = thematrix[x][j] / visor;
	}
}