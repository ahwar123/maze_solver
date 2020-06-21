/*
------------------
Description
------------------

Approach taken
	- first created a fix size maze and fill it with wall and create a path from start to end point by setting open points in maze
	- program solve steps
		- First find the starting point index and start from that point
		- after checking the boundary condition we will start from north then check east, south west points accordingly.
		- if point is not stale, not visited before and open. then we will add a Breadcrumb there and start searching next point from there.
		- we will continue until ending point reached.
		- if we stuck at some point, then we will make the point stale and backtrack to the non stale point.

Issues encountered
	- creating a maze with open random points from start to bottom.
	- handle breadcrumb in trail and make them stale.
	- backtracking

Choices made in design and implementation
	- Create a hardcode implementation of maze
	- Find starting point and start from there
	- For handle boundary cases check indexes at each point and determine from there which way to go.
	- First print the maze then after solve show the solved puzzle by merging maze and trail at the end.
	- Milestone 3 is done by comparing previous and next breadcrumb in trail and determing direction from there.
	
Pros: 
	- It handle all the boundery cases and can solve any maze of any dimention.
	- Dynamic memory created and deleted at the end for remove the risk of memory leaks.
	- Code is indented and commented and easy to read.
	- 

Cons:
	- Creating maze is not efficient there are alot of for loops which has major effect on the efficiency.
	- In solving maze, more functions can be used in, for more reusability of code.



*/


#include <iostream>
#include <string>
#include <fstream>

#include "Types.h"
#include "MazeSolver.h"
using namespace std;

// Helper test functions
void testBreadcrumb();
void testTrail();
void showDirections(Trail* solution);

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    //std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    //testBreadcrumb();
    //testTrail();
    //std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Maze from stdin
    Maze maze;
    readMazeStdin(maze);
	ofstream mazeToSolve("sample_test/maze.txt", ios::out);
	ofstream programOutput("sample_test/program_output.txt", ios::out);

	
	if (mazeToSolve.is_open())
	{
		for (int a = 0; a < MAZE_DIM; a++) {
			for (int b = 0; b < MAZE_DIM; b++) {
				mazeToSolve << maze[a][b];
			}
			mazeToSolve << "\n";
		}
		mazeToSolve.close();
	}

    // Solve using MazeSolver
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    MazeSolver* solver = new MazeSolver();
    Trail* solution = nullptr;
    solver->solve(maze);
    solution = solver->getSolution();

    // Print Maze to stdout
    printMazeStdout(maze, solution);

	if (programOutput.is_open())
	{
		for (int a = 0; a < MAZE_DIM; a++) {
			for (int b = 0; b < MAZE_DIM; b++) {
				programOutput << maze[a][b];
			}
			programOutput << "\n";
		}
		programOutput.close();
	}
	
	// compare files
	
	// get files in input mode
	ifstream expectedOutputToCompare("sample_test/expected_output.txt", ios::in);
	ifstream programOutputToCompare("sample_test/program_output.txt", ios::in);
	
	char file1, file2;
	bool isFileSame = true;

	//if both files opens
	if (expectedOutputToCompare.is_open() && programOutputToCompare.is_open())
	{
		while (1) {
			// get files character by character and compare
			file1 = expectedOutputToCompare.get();
			file2 = programOutputToCompare.get();
			
			//if any of the character is not same then set flag to false
			if (file1 != file2) {
				isFileSame = false;
				break;
			}
			// if reached end of file then break
			if ((file1 == EOF) || (file2 == EOF)) {
				break;
			}
		}
		// close files
		expectedOutputToCompare.close();
		programOutputToCompare.close();



		cout << '\n';
		cout << "\n------------------------";
		cout << "\n----- Milestone 1 ------";
		cout << "\n------------------------";
		cout << "\n";

		//if flag is true
		if (isFileSame) {
			cout << "\nExpected and program output is same.\n";
		}
		else {
			cout << "\nExpected and program output is not same.\n";
		}
	}


    delete solver;
	system("pause");
    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze) {
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).
	
	// Create maze

	cout << "\n------------------------";
	cout << "\n--------- MAZE ---------";
	cout << "\n------------------------";
	cout << "\n\n";


	for (int i = 0; i < MAZE_DIM; i++)
	{
		for (int j = 0; j < MAZE_DIM; j++)
		{
			// set walls 
			maze[i][j] = WALL;

			// add a starting point
			maze[1][0] = 'S';

			// add open points on different indexes
			for (int x = 1; x < 2; x++)
			{
				for (int y = 1; y < MAZE_DIM - 1; y++)
				{
					maze[x][y] = OPEN;
				}
			}
			
			for (int x = 2; x < MAZE_DIM / 2 + 2; x++)
			{
				for (int y = MAZE_DIM - 2; y > MAZE_DIM - 3; y--)
				{
					maze[x][y] = OPEN;
				}
			}
			for (int x = MAZE_DIM / 2 - 4; x < MAZE_DIM / 2 - 3; x++)
			{
				for (int y = 1; y < MAZE_DIM - 5; y++)
				{
					maze[x][y] = OPEN;

				}
			}

			for (int x = MAZE_DIM / 2 - 3; x < MAZE_DIM / 2 + 1; x++)
			{
				for (int y = MAZE_DIM / 2 + 4; y < MAZE_DIM / 2 + 5; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM / 2 + 1; x < MAZE_DIM / 2 + 2; x++)
			{
				for (int y = MAZE_DIM - 3; y > MAZE_DIM / 2 + 3; y--)
				{
					maze[x][y] = OPEN;
				}
			}


			for (int x = MAZE_DIM / 2 + 1; x < MAZE_DIM / 2 + 2; x++)
			{
				for (int y = 1; y < 3; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM / 2 + 1; x < MAZE_DIM / 2 + 2; x++)
			{
				for (int y = MAZE_DIM / 2 - 2; y < MAZE_DIM / 2 + 1; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM / 2 - 3; x < MAZE_DIM / 2 + 1; x++)
			{
				for (int y = (MAZE_DIM / 2) - 2; y < (MAZE_DIM / 2) - 1; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM / 2 - 3; x < MAZE_DIM / 2 + 1; x++)
			{
				for (int y = 2; y < 3; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM / 2 + 2; x < MAZE_DIM - 2; x++)
			{
				for (int y = 1; y < 2; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			//a//				
			for (int x = MAZE_DIM / 2 + 2; x < MAZE_DIM - 1; x++)
			{
				for (int y = (MAZE_DIM / 2); y < (MAZE_DIM / 2) + 1; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM / 2 + 2; x < MAZE_DIM - 3; x++)
			{
				for (int y = MAZE_DIM / 2 + 5; y < MAZE_DIM / 2 + 6; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM - 3; x < MAZE_DIM - 2; x++)
			{
				for (int y = MAZE_DIM - 5; y < MAZE_DIM - 1; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM - 3; x < MAZE_DIM - 1; x++)
			{
				for (int y = MAZE_DIM - 2; y < MAZE_DIM - 1; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM - 3; x < MAZE_DIM - 1; x++)
			{
				for (int y = MAZE_DIM - 2; y < MAZE_DIM - 1; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			for (int x = MAZE_DIM - 2; x < MAZE_DIM - 1; x++)
			{
				for (int y = 1; y < MAZE_DIM / 2 - 5; y++)
				{
					maze[x][y] = OPEN;
				}
			}

			// add an ending point

			maze[MAZE_DIM - 1][MAZE_DIM / 2] = 'E';

			cout << maze[i][j] << " ";
		}
		cout << '\n';
	}

}


void printMazeStdout(Maze maze, Trail* solution) {
    
	cout << '\n';
	cout << "\n------------------------";
	cout << "\n----- Milestone 2 ------";
	cout << "\n------------------------";
	cout << "\n";
	cout << "\n";

	// get indexes from solution trail and set * on those indexes in maze
	Breadcrumb* breadcrumb;
	for (int s = 0; s < solution->size(); s++) {
		breadcrumb = solution->getPtr(s);
		int x = breadcrumb->getX();
		int y = breadcrumb->getY();

		// if point is not stale
		if (!breadcrumb->isStale()) {
			maze[x][y] = '*';
		}
	}

	// print maze
	for (int a = 0; a < MAZE_DIM; a++) {
		for (int b = 0; b < MAZE_DIM; b++) {
			cout << maze[a][b] << " ";
		}
		cout << "\n";
	}

	// show direction from start to end
	showDirections(solution);
}

void testBreadcrumb() {
    std::cout << "TESTING BREADCRUMB" << std::endl;

    // Make a breadcrumb and print out the contents
    Breadcrumb* breadcrumb = new Breadcrumb(1, 1, false);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

    // Change breadcrumb stale-ness and print again
    breadcrumb->setStale(true);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

	delete breadcrumb;

}

void testTrail() {
    std::cout << "TESTING TRAIL" << std::endl;

    // Make a simple trail, should be empty size
    Trail* trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a breadcrumb to the trail, print size, check contains
    Breadcrumb* b1 = new Breadcrumb(1, 1, false);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Add second breadcrumb
    Breadcrumb* b2 = new Breadcrumb(0, 0, true);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Test Get-ith - should be 0,0,true
    Breadcrumb* getB = trail->getPtr(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->isStale() << std::endl;

    // Print out the trail
    std::cout << "PRINTING OUT A TRAIL IS AN EXERCISE FOR YOU TO DO" << std::endl;

	delete getB;
	delete b2;
	delete b1;
	delete trail;
}


void showDirections(Trail* solution) {
	cout << "\n------------------------";
	cout << "\n----- Milestone 3 ------";
	cout << "\n------------------------";
	cout << "\n";
	cout << "\n";


	Breadcrumb* breadcrumb;
	Breadcrumb* breadcrumbNext;

	// get starting point of trail
	breadcrumb = solution->getPtr(0);
	
	cout << "START\n";
	
	for (int d = 1; d < solution->size(); d++) {
		// get next point in trail
		breadcrumbNext = solution->getPtr(d);
		int x1 = breadcrumb->getX();
		int y1 = breadcrumb->getY();
		int x2 = breadcrumbNext->getX();
		int y2 = breadcrumbNext->getY();

		// compare the points of previous and next point and determine the direction
		if (x1 > x2 && y1 == y2) {
			cout << "NORTH";
		}
		else if (x1 == x2 && y1 < y2) {
			cout << "EAST";
		}
		else if (x1 < x2 && y1 == y2) {
			cout << "SOUTH";
		}
		else if (x1 == x2 && y1 > y2) {
			cout << "WEST";
		}
		else {
			cout << "STALE";
		}
		cout << "\n";
		
		// set new previous Breadcrumb
		breadcrumb = solution->getPtr(d);

	}
	cout << "END\n";
}