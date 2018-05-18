#include "maze.h"
#include <iostream>
using namespace std;
int Maze::_nodes = 0;
int Maze::_width = 0;
int Maze::_height = 0; 
Point Maze::_end = Point();
map<Point, bool> Maze::_visited = map<Point, bool>();
Maze::Maze(char** maze, int x, int y, vector<Point> traveled, int cost, int distance)
{
	_maze = maze;
	_x = x;
	_y = y;
	_cost = cost;
	_distance = distance;
	_traveled = traveled;
}

void Maze::reset()
{
	_nodes = 0;
	_traveled = vector<Point>();
	_visited = map<Point, bool>();
	clearMaze();
	_maze[_end.getX()][_end.getY()]='.';
}

void Maze::setEnd(Point p)
{
	_end.setX(p.getX());
	_end.setY(p.getY());
}

Point Maze::getEnd()
{
	return _end;
}

void Maze::incrementNodes()
{
	_nodes++;
}

int Maze::getX()
{
	return _x;
}
int Maze::getY()
{
	return _y;
}
int Maze::getDistance()
{
	return _distance;
}

vector<Point> Maze::getTraversed()
{
	return _traveled;
}

int Maze::getCost()
{
	return _cost;
}
char** Maze::getMaze()
{
	return _maze;
}

void Maze::setHeight(int h)
{
	_height = h;
}

void Maze::setWidth(int w)
{
	_width = w;
}

void Maze::setPoint(int x, int y)
{
	_traveled.push_back(Point(x,y));
	_visited[Point(x,y)] = true;
}

int Maze::getHeight()
{
	return _height;
}

int Maze::getWidth()
{
	return _width;
}

int Maze::getNodes()
{
	return _nodes;
}

bool Maze::validUp()
{	
	Point toCheck(_x, _y-1);
	if(_y>0 && _maze[_x][_y-1]!='%' && !_visited[toCheck])
	{
		return true;
	}
	return false;
}

bool Maze::validDown()
{
	Point toCheck(_x, _y+1);
	if(_y>0 && _maze[_x][_y+1]!='%' && !_visited[toCheck])
	{
		return true;
	}
	return false;
}

bool Maze::validLeft()
{
	Point toCheck(_x-1, _y);
	if(_y>0 && _maze[_x-1][_y]!='%' && !_visited[toCheck])
	{
		return true;
	}
	return false;
}

bool Maze::validRight()
{

	Point toCheck(_x+1, _y);
	if(_y>0 && _maze[_x+1][_y]!='%' && !_visited[toCheck])
	{	
		return true;
	}
	return false;
}



void Maze::printMaze()
{
	for(int i=0; i<getWidth(); i++)
    {
		for(int j=0; j<getHeight(); j++)
		{
			cout << _maze[i][j];
		}
		cout << endl;
	}
}

void Maze::clearMaze()
{
	for(int i=0; i<Maze::getWidth(); i++)
		{
			for(int j=0; j<Maze::getHeight(); j++)
			{
				if(_maze[i][j]!='%')
				{
					_maze[i][j] = ' ';
				}
			}
		}
}
void Maze::fillMaze()
{
	clearMaze();
	for(int i=0; i<_traveled.size(); i++)
	{
		//cout << "x: " << _traveled[i].getX() << " y: " << _traveled[_cost].getY() << endl;
		if(i==0)
		{
			_maze[_traveled.at(i).getX()][_traveled.at(i).getY()] = 'P';
		}
		else
		{
			_maze[_traveled.at(i).getX()][_traveled.at(i).getY()] = '.';
		}
	}
}







