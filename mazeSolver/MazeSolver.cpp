
#include "MazeSolver.h"
 
using namespace std;

MazeSolver::MazeSolver() {
}

MazeSolver::~MazeSolver() {
   // TODO delete solution;
	delete solution;

}

void MazeSolver::solve(Maze maze) {
	
	solution = new Trail();
	Breadcrumb* getBForStale;

	for (int a = 0; a < MAZE_DIM; a++) {
		for (int b = 0; b < MAZE_DIM; b++) {
			// first find the starting point
			if (maze[a][b] == 'S') {
				// initialize indexes from start
				int i = a;
				int j = b;

				for (int r = a; r < MAZE_DIM; r++) {
					for (int c = b; c < MAZE_DIM; c++) {

						bool isStale = false;
						bool isVisited = false;
						// if row not at top boundary
						if (i > 0) {
							// if ending point reached
							if (maze[i-1][j] == 'E') {
								return;
							}

							// check if next point is stale 
							isStale = checkStaleInTrail(i - 1, j);
							
							// check if next point is already visited
							isVisited = isOpenVisited(i - 1, j);
							
							// if next point is open and not stale and also not visited then go there

							//check north
							if (maze[i - 1][j] == OPEN && isStale == false && isVisited == false) {
								i = i - 1;
								addBreadCrumbToTrail( i, j);
							}
							else if (j < MAZE_DIM - 1) {
								if (maze[i][j+1] == 'E') {
									return;
								}
								isStale = checkStaleInTrail( i, j + 1);
								isVisited = isOpenVisited(i, j + 1);

								// check east
								if (maze[i][j + 1] == OPEN && isStale == false && isVisited == false) {
									j = j + 1;
									addBreadCrumbToTrail( i, j);
								}
								else if (i < MAZE_DIM - 1) {
									if (maze[i+1][j] == 'E') {
										 
										return;
									}
									isStale = checkStaleInTrail(i + 1, j);
									isVisited = isOpenVisited(i + 1, j);
									
									// check south
									if (maze[i + 1][j] == OPEN && isStale == false && isVisited == false) {
										i = i + 1;
										addBreadCrumbToTrail( i, j);
									}
									else if (j > 0) {
										if (maze[i][j-1] == 'E') {
											return;
										}
										isStale = checkStaleInTrail( i, j - 1);
										isVisited = isOpenVisited(i, j - 1);
									
										//check west
										if (maze[i][j - 1] == OPEN && isStale == false && isVisited == false) {
											j = j - 1;
											addBreadCrumbToTrail(i, j);
										}
										else {
											// if all the paths are blocked then set current point to stale and backtrack
											setBreadCrumbStale(i, j, maze);
											for (int s = solution->size() - 1; s > 0; s--) {
												getBForStale = solution->getPtr(s);

												// go to the non stale point 
												if (!getBForStale->isStale()) {
													// set current indexes to last non stale point
													i = getBForStale->getX();
													j = getBForStale->getY();
													break;
												}
											}
										}
									}
									


								}

							}
						}

						// if at top boundary then ignore north and check east
						else if (j < MAZE_DIM - 1) {
							if (maze[i][j+1] == 'E') {
								return;
							}
							isStale = checkStaleInTrail( i, j + 1);
							isVisited = isOpenVisited(i, j + 1);
							// check east
							if (maze[i][j + 1] == OPEN && isStale == false && isVisited == false) {
								j = j + 1;
								addBreadCrumbToTrail( i, j);
							}

							else if (i < MAZE_DIM - 1) {
								if (maze[i+1][j] == 'E') {
									return;
								}
								isStale = checkStaleInTrail( i + 1, j);
								isVisited = isOpenVisited(i + 1, j);
								// check south
								if (maze[i + 1][j] == OPEN && isStale == false && isVisited == false) {
									i = i + 1;
									addBreadCrumbToTrail( i, j);
								}

								else if (j > 0) {
									if (maze[i][j-1] == 'E') {
										return;
									}
									isStale = checkStaleInTrail( i, j - 1);
									isVisited = isOpenVisited(i, j - 1);
									
									//check west
									if (maze[i][j - 1] == OPEN && isStale == false && isVisited == false) {
										j = j - 1;
										addBreadCrumbToTrail( i, j);
									}
									else {
										// stale and backtrack
										setBreadCrumbStale( i, j, maze);

										for (int s = solution->size() - 1; s > 0; s--) {
											getBForStale = solution->getPtr(s);
											if (!getBForStale->isStale()) {
												i = getBForStale->getX();
												j = getBForStale->getY();
												break;
											}
										}
									}
								}


							}

						}
						// if we cannot go to north and south then ignore and start from south
						else if (i < MAZE_DIM - 1) {
							if (maze[i+1][j] == 'E') {	 
								return;
							}
							isStale = checkStaleInTrail( i + 1, j);
							isVisited = isOpenVisited(i + 1, j);
							// check south
							if (maze[i + 1][j] == OPEN && isStale == false && isVisited == false) {
								i = i + 1;
								addBreadCrumbToTrail( i, j);
							}

							else if (j > 0) {
								if (maze[i][j-1] == 'E') {
									return;
								}
								isStale = checkStaleInTrail( i, j - 1);
								isVisited = isOpenVisited(i, j - 1);
								// check west
								if (maze[i][j - 1] == OPEN && isStale == false && isVisited == false) {
									j = j - 1;
									addBreadCrumbToTrail( i, j);
								}
								else {
									//stale and backtrack
									setBreadCrumbStale( i, j, maze);
									for (int s = solution->size() - 1; s > 0; s--) {
										getBForStale = solution->getPtr(s);
										if (!getBForStale->isStale()) {
											i = getBForStale->getX();
											j = getBForStale->getY();
											break;
										}
									}
								}

							}

						}
						// if north, east and south are at bounderies then start from west
						else if (j > 0) {
							if (maze[i][j-1] == 'E') {
								 
								return;
							}
							isStale = checkStaleInTrail( i, j - 1);
							isVisited = isOpenVisited(i, j - 1);
							if (maze[i][j - 1] == OPEN && isStale == false && isVisited == false) {
								j = j - 1;
								// set breadcrumb
								addBreadCrumbToTrail( i, j);
							}
							else {
								// stale and backtrack
								setBreadCrumbStale( i, j, maze);
								
								for (int s = solution->size() - 1; s > 0; s--) {
									getBForStale = solution->getPtr(s);
									if (!getBForStale->isStale()) {
										i = getBForStale->getX();
										j = getBForStale->getY();
										break;
									}
								}

							}
						}
						else {
							// if all of the above fail then stale and backtrack
							setBreadCrumbStale( i, j, maze);

							for (int s = solution->size() - 1; s > 0; s--) {
								getBForStale = solution->getPtr(s);
								if (!getBForStale->isStale()) {
									i = getBForStale->getX();
									j = getBForStale->getY();
									break;
								}
							}

						}

					}
				}
			
				break;
			}
			break;

		}
	}

 
	

}

// set the stale true of specific breadcrumb
void MazeSolver::setBreadCrumbStale(int i, int j, Maze maze) {
	Breadcrumb* getBForStale;

	// check if indexes exists in trail and return the trail index
	int isContain = solution->getBreadCrumbIndex(i, j);
	if (isContain != -1) {
		// Breadcrumb exists
		getBForStale = solution->getPtr(isContain);
		getBForStale->setStale(true);
		
		// convert ROUTE back to OPEN
		// maze[i][j] = OPEN;

	}
}

void MazeSolver::addBreadCrumbToTrail(int i, int j) {
	// add a breadcrumb in trail
	Breadcrumb* breadcrumb = new Breadcrumb(i, j, false);
	solution->addCopy(breadcrumb);
}


Trail* MazeSolver::getSolution() {
   return solution;
}

//check if breadcrumb stale or not
bool MazeSolver::checkStaleInTrail(int i, int j) {

	int isContain = solution->getBreadCrumbIndex(i, j);
	if (isContain != -1) {
		Breadcrumb* breadCrumb;
		breadCrumb = solution->getPtr(isContain);
		if (breadCrumb->isStale() == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}

//check if breadcrumb visited or not
bool MazeSolver::isOpenVisited(int i, int j) {
	int isContain = solution->getBreadCrumbIndex(i, j);
	if (isContain != -1) {
		return true;
	}
	return false;
}



