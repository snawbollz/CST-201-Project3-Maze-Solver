//Source for MazeSolver

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "myStack.h"
//#include "MyQ.h"
#include "MazeCell.h"


using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define DONE 4
#define SUCCESS 10
#define FAILURE 20

//method headers*******************************************************

//depthFirst header
void depthFirst(MazeCell start, MazeCell end);

//global variables*****************************************************

//# rows and cols in the maze
int rows, cols;
//pointer to the grid (2-d array of ints)
int** grid;
//pointer to the maze cells (2-d array of MazeCell objects)
MazeCell** cells;

int main() {

	//create the Maze from the file
	ifstream fin("maze.in");
	if (!fin) {
		cout << "File not found\n";
		exit(2);
	}

	//read in the rows and cols
	fin >> rows >> cols;

	//create the maze rows
	grid = new int* [rows];

	//add each column
	for (int i = 0; i < rows; i++)
		grid[i] = new int[cols];

	//read in the data from the file to populate
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fin >> grid[i][j];
		}
	}

	//look at it 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] == 3)
				cout << "S" << " ";
			else if (grid[i][j] == 4)
				cout << "E" << " ";
			else
				cout << grid[i][j] << " ";
		}
		cout << endl;
	}

	//make a 2-d array of cells
	cells = new MazeCell * [rows];
	for (int i = 0; i < rows; i++) {
		cells[i] = new MazeCell[cols];
	}

	//all MazeCell in the cells grid has a default init
	//only update those cells that are not walls

	MazeCell start, end;

	//iterate over the grid
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] != 0) {
				cells[i][j].setCoordinates(i, j);
				//look for the start and end cells
				if (grid[i][j] == 3)
					start = cells[i][j];
				if (grid[i][j] == 4)
					end = cells[i][j];

			}

		}
	}

	//testing
	cout << "start: " << start << " end: " << end << endl;

	//solve it!
	depthFirst(start, end);

	return 0;
}


//this function should find a path through the maze
//if found, output the path from start to end
//if not path exists, output a message stating so

void depthFirst(MazeCell start, MazeCell end)	//O(V + E)
{
	int row = start.getRow();
	int col = start.getCol();
	MyStack<MazeCell>myStack;
	myStack.push(cells[row][col]);

	while (cells[row][col] != cells[end.getRow()][end.getCol()]) {

		// Right
		if (cells[row][col + 1].unVisited() == true && cells[row][col + 1].getCol() != -1 && (col + 1) < 6) {
			myStack.push(cells[row][col]);
			cells[row][col].visit();
			col++;


		} // Down
		else if (cells[row + 1][col].unVisited() == true && cells[row + 1][col].getRow() != -1 && (row + 1) < 4) {
			myStack.push(cells[row][col]);
			cells[row][col].visit();
			row++;



		}// Left
		else if (cells[row][col - 1].unVisited() == true && cells[row][col - 1].getCol() != -1 && (col - 1) < 6) {
			myStack.push(cells[row][col]);
			cells[row][col].visit();
			col--;



		} // Up
		else if (cells[row - 1][col].unVisited() == true && cells[row - 1][col].getRow() != -1 && (row + 1) < 4) {
			myStack.push(cells[row][col]);
			cells[row][col].visit();
			row--;


		}
	}
	if (cells[row][col] == cells[end.getRow()][end.getCol()]) {
		myStack.push(cells[row][col]);
		cout << "Exit Found!" <<endl;

		cout << "Path: " << endl;
		while (myStack.empty() != true) {
			cout << myStack.top() << endl;
			myStack.pop();
		}
	}
	else {
		cout << "stuck" << endl;
		while (myStack.top() != cells[start.getRow()][start.getCol()]) {
			myStack.pop();
		}
	}
}
