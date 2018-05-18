#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/* This program is designed to solve a maze using recursion and backtracking.
 * The maze will first be created from a user given text file. Memory will
 * then be allocated for all of the spaces in the maze via malloc functions.
 * After printing out the maze character array[1]<array[0] && array[1]<array[2] && array[1]<array[3]by character, the program uses
 * DFS and Manhattan Distance algorithms in order to find the shortest path
 * to the end of the maze. The program marks the correct path using '.' and
 * marks visited paths with '~'.
 */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
int i,j;	//counter for cell row and column
int row,col;

//open the file for reading
FILE *mazeName;

mazeName = fopen(fileName, "r");

//allocate memory for the maze array pointers
maze_t *newMaze;
newMaze = (maze_t*)malloc(sizeof(maze_t));

//assign the maze height and width values
fscanf(mazeName,"%d %d",&newMaze->width,&newMaze->height);

row = newMaze->height+1;
col = newMaze->width+1;

//allocate memory for the cells assigned to the array pointers
newMaze->cells = malloc(row * sizeof(int *));

for (i=0; i<row; i++) 
{ 	
	newMaze->cells[i] = malloc(col * sizeof(int *));
}

//read the characters from the file
int r;

for(i=0;i<row;i++)
{
	for(j=0;j<col;j++)
	{
		r = fgetc(mazeName);
		if(r!='\n')
			newMaze->cells[i][j] = r;
		if(r == 'E')
		{
			newMaze->endRow = i;
			newMaze->endColumn = j;
		}
		if(r == 'S')
		{
			newMaze->startRow = i;
			newMaze->startColumn = j;
		}


	}
}

fclose(mazeName);	//close the file

return newMaze;		//return the filled maze structure
}
/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{

int i;

//free memory for the pointers
for(i=0;i<maze->height+1;i++)
{
	free(maze->cells[i]);
}

//free the memory of the structure and the cells
	free(maze->cells);
	free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
  
int r,c;	//rows and columns

//print width and height of maze
printf("%d %d\n",maze->width,maze->height);

//print individual cells within maze
for(r=0;r<maze->height;r++)
{
	for(c=0;c<maze->width+1;c++)
	{
		printf("%c",maze->cells[r][c]);
	}
	printf("\n");
}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{

int mdL,mdU,mdR,mdD;
int cell;

cell = maze->cells[row][col];

	//base case - if outside of the bounds, return false
	if(row<0 || row>maze->height || col<0 || col>maze->width)
		return 0;

	//base case - if an invalid cell is reached, return false
	if(maze->cells[row][col] != ' ' && maze->cells[row][col] != 'S' && maze->cells[row][col] !='E')
		return 0;

	//base case - if end is reached, stop recursing
	if(maze->cells[row][col] == maze->cells[maze->endRow][maze->endColumn])
	{
		maze->cells[maze->startRow][maze->startColumn] = 'S';	
		maze->cells[maze->endRow][maze->endColumn] = 'E';
		return 1;
	}
	//assign the current cell as part of the solution
	if(cell != 'S' && cell!='E')
		maze->cells[row][col] = '.';
	
	//determine the Manhattan Distance of each direction
	mdL = abs(row-maze->endRow) + abs(col-1-maze->endColumn);
	mdU = abs(row-1-maze->endRow) + abs(col-maze->endColumn);
	mdR = abs(row-maze->endRow) + abs(col+1-maze->endColumn);
	mdD = abs(row+1-maze->endRow) + abs(col-maze->endColumn);
	

int i;
int j;
int tmp;
int array[4];

array[0] = mdL;
array[1] = mdU;
array[2] = mdR;
array[3] = mdD;

	//sort the Manhattan Distances from least to greatest using an array
	for(i=0;i<4;i++)
	{
		for(j=0;j<(4-i-1);j++)
		{
			if(array[j]>array[j+1])
			{
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
		}
	}
	
	//check all directions for the next path
	if(array[0] == mdL)
	{
		if(solveMazeManhattanDFS(maze,col-1,row))
			return 1;
	}
	if(array[0] == mdU)
	{
		if(solveMazeManhattanDFS(maze,col,row-1))
			return 1;
	}
	if(array[0] == mdR)
	{
		if(solveMazeManhattanDFS(maze,col+1,row))
			return 1;
	}
	if(array[0] == mdD)
	{
		if(solveMazeManhattanDFS(maze,col,row+1))
			return 1;
	}
	if(array[1] == mdL)
	{
		if(solveMazeManhattanDFS(maze,col-1,row))
			return 1;
	}
	if(array[1] == mdU)
	{
		if(solveMazeManhattanDFS(maze,col,row-1))
			return 1;
	}
	if(array[1] == mdR)
	{
		if(solveMazeManhattanDFS(maze,col+1,row))
			return 1;
	}
	if(array[1] == mdD)
	{
		if(solveMazeManhattanDFS(maze,col,row+1))
			return 1;
	}
	if(array[2] == mdL)
	{
		if(solveMazeManhattanDFS(maze,col-1,row))
			return 1;
	}
	if(array[2] == mdU)
	{
		if(solveMazeManhattanDFS(maze,col,row-1))
			return 1;
	}
	if(array[2] == mdR)
	{
		if(solveMazeManhattanDFS(maze,col+1,row))
			return 1;
	}
	if(array[2] == mdD)
	{
		if(solveMazeManhattanDFS(maze,col,row+1))
			return 1;
	}
	if(array[3] == mdL)
	{
		if(solveMazeManhattanDFS(maze,col-1,row))
			return 1;
	}
	if(array[3] == mdU)
	{
		if(solveMazeManhattanDFS(maze,col,row-1))
			return 1;
	}
	if(array[3] == mdR)
	{
		if(solveMazeManhattanDFS(maze,col+1,row))
			return 1;
	}
	if(array[3] == mdD)
	{
		if(solveMazeManhattanDFS(maze,col,row+1))
			return 1;
	}
	

	//assign the current cell as explored
	if(maze->cells[row][col] == '.')
		maze->cells[row][col] = '~';

    return 0;
}
