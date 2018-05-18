#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <climits>
#include <stdlib.h>
#include "node.h"
using namespace std;

/*
This program uses different search methods to find a goal (noted by a dot)
within a maze given a specific starting location.
The different search methods tested are DFS, BFS, GBFS, and A*.

As of right now, the program correctly finds the goal for a single dot.
It incorrectly finds the most efficent path to follow given multiple dots.

*/

//obtain the number of lines to iterate through
int num_lines(char* f)
{
	int num_lines = 0;
	ifstream file;
	file.open(f);
	if(!file)
	{
		cout << "Unable to open file. Please provide another" << endl;
		return -1;
	}
	char c;
	while (!file.eof())
	{
		file.get(c);
		if (c == '\n')
		{
			num_lines++;
		}
	}
	file.close();
	return num_lines;
}


//obtain the width of each line
int width_of_file(char* f)
{
	int num_chars = 0;
	ifstream file;
	file.open(f);
	if(!file)
	{
		cout << "Unable to open file. Please provide another" << endl;
		return -1;
	}
	char c;
	while(!file.eof())
	{
		file.get(c);
		if(c=='\n')
		{
		 	file.close();
			return num_chars;
		}
		else
		{
			num_chars++;
		}
	}
	return num_chars;
}

//use a stack to traverse through the maze in the order Up->Down->Left->Right
void depth_first_search(Maze* maze)
{
	cout << "doing dfs" << endl;
	stack<Maze*> maze_stack = stack<Maze*>();
	Maze* currentMaze = maze;
	int currentX = currentMaze->getX();
	int currentY = currentMaze->getY();
	currentMaze->setPoint(currentX, currentY);
	while(currentMaze->getMaze()[currentX][currentY]!='.')
	{
		currentMaze->getMaze()[currentX][currentY] = 'P';
		if(currentMaze->validUp())
		{
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX, currentY-1, currentMaze->getTraversed(), currentMaze->getCost()+1, -1);
			tempMaze->setPoint(currentX, currentY-1);
			maze_stack.push(tempMaze);
		}
		if(currentMaze->validDown())
		{
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX, currentY+1, currentMaze->getTraversed(), currentMaze->getCost()+1, -1);
			tempMaze->setPoint(currentX, currentY+1);
			maze_stack.push(tempMaze);
		}
		if(currentMaze->validLeft())
		{
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX-1, currentY, currentMaze->getTraversed(), currentMaze->getCost()+1, -1);
			tempMaze->setPoint(currentX-1, currentY);
			maze_stack.push(tempMaze);
		}
		if(currentMaze->validRight())
		{
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX+1, currentY, currentMaze->getTraversed(), currentMaze->getCost()+1, -1);
			tempMaze->setPoint(currentX+1, currentY);
			maze_stack.push(tempMaze);
		}
		currentMaze = maze_stack.top();
		currentX = currentMaze->getX();
		currentY = currentMaze->getY();
		maze_stack.pop();
		Maze::incrementNodes();
	}
	currentMaze->fillMaze();
	currentMaze->printMaze();
	cout << "Nodes Expanded: " << Maze::getNodes() << endl;
	cout << "Path cost: " << currentMaze->getCost() << endl;
	cout << "exiting dfs" << endl;
}

//use a queue to traverse through the maze in the order Up->Down->Left->Right
void breadth_first_search(Maze* maze)
{
	cout << "doing bfs" << endl;
	queue<Maze*> maze_queue = queue<Maze*>();
	Maze* currentMaze = maze;
	int currentX = currentMaze->getX();
	int currentY = currentMaze->getY();
	currentMaze->setPoint(currentX, currentY);
	while(currentMaze->getMaze()[currentX][currentY]!='.')
	{
		currentMaze->getMaze()[currentX][currentY] = 'P';
		if(currentMaze->validUp())
		{
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX, currentY-1, currentMaze->getTraversed(), currentMaze->getCost()+1, -1);
			tempMaze->setPoint(currentX, currentY-1);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validDown())
		{
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX, currentY+1, currentMaze->getTraversed(), currentMaze->getCost()+1, -1);
			tempMaze->setPoint(currentX, currentY+1);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validLeft())
		{
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX-1, currentY, currentMaze->getTraversed(), currentMaze->getCost()+1, -1);
			tempMaze->setPoint(currentX-1, currentY);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validRight())
		{
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX+1, currentY, currentMaze->getTraversed(), currentMaze->getCost()+1, -1);
			tempMaze->setPoint(currentX+1, currentY);
			maze_queue.push(tempMaze);
		}
		currentMaze = maze_queue.front();
		currentX = currentMaze->getX();
		currentY = currentMaze->getY();
		maze_queue.pop();
		Maze::incrementNodes();
	}

	currentMaze->fillMaze();
	currentMaze->printMaze();
	cout << "Nodes Expanded: " << Maze::getNodes() << endl;
	cout << "Path cost: " << currentMaze->getCost() << endl;
	cout << "exiting bfs" << endl;

}

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top()->getCost()+q.top()->getDistance() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int manhattanDistance(Point current, Point end)
{
	return abs(current.getX() - end.getX()) + abs(current.getY() - end.getY());
}


//pick the location closest to the goal (determined by Manhattan Distance)
void greedy(Maze* maze)
{
	cout << "doing greedy search" << endl;
	auto cmp = [](Maze* left, Maze* right){return left->getDistance() > right->getDistance();};
	priority_queue<Maze*, std::vector<Maze*>, decltype(cmp)> maze_queue(cmp);
	Maze* currentMaze = maze;
	int currentX = currentMaze->getX();
	int currentY = currentMaze->getY();
	currentMaze->setPoint(currentX, currentY);
	while(currentMaze->getMaze()[currentX][currentY]!='.')
	{
		currentMaze->getMaze()[currentX][currentY] = 'P';
		if(currentMaze->validUp())
		{
			int distance = manhattanDistance(Point(currentX, currentY-1), Maze::getEnd());
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX, currentY-1, currentMaze->getTraversed(), currentMaze->getCost()+1, distance);
			tempMaze->setPoint(currentX, currentY-1);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validDown())
		{
			int distance = manhattanDistance(Point(currentX, currentY+1), Maze::getEnd());
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX, currentY+1, currentMaze->getTraversed(), currentMaze->getCost()+1, distance);
			tempMaze->setPoint(currentX, currentY+1);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validLeft())
		{
			int distance = manhattanDistance(Point(currentX-1, currentY), Maze::getEnd());
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX-1, currentY, currentMaze->getTraversed(), currentMaze->getCost()+1, distance);
			tempMaze->setPoint(currentX-1, currentY);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validRight())
		{
			int distance = manhattanDistance(Point(currentX+1, currentY), Maze::getEnd());
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX+1, currentY, currentMaze->getTraversed(), currentMaze->getCost()+1, distance);
			tempMaze->setPoint(currentX+1, currentY);
			maze_queue.push(tempMaze);
		}
		currentMaze = maze_queue.top();
		currentX = currentMaze->getX();
		currentY = currentMaze->getY();
		maze_queue.pop();
		Maze::incrementNodes();
	}
	cout << "found solution" << endl;
	currentMaze->fillMaze();
	currentMaze->printMaze();
	cout << "Nodes Expanded: " << Maze::getNodes() << endl;
	cout << "Path cost: " << currentMaze->getCost() << endl;
	cout << "exiting greedy" << endl;

}

//use a priority queue for A* search
INFO a_star(Maze* maze)
{
	cout << "doing a_star" << endl;
	auto cmp = [](Maze* left, Maze* right){
		return (left->getCost()+left->getDistance())==(right->getCost()+right->getDistance()) ? left->getCost() > right->getCost() : (left->getCost()+left->getDistance())>(right->getCost()+right->getDistance()); //all return optimal cost

	};
	priority_queue<Maze*, std::vector<Maze*>, decltype(cmp)> maze_queue(cmp);
	Maze* currentMaze = maze;
	int currentX = currentMaze->getX();
	int currentY = currentMaze->getY();
	currentMaze->setPoint(currentX, currentY);
	while(currentMaze->getMaze()[currentX][currentY]!='.')
	{
		currentMaze->getMaze()[currentX][currentY] = 'P';
		if(currentMaze->validUp())
		{
			int distance = manhattanDistance(Point(currentX, currentY-1), Maze::getEnd());
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX, currentY-1, currentMaze->getTraversed(), currentMaze->getCost()+1, distance);
			tempMaze->setPoint(currentX, currentY-1);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validRight())
		{
			int distance = manhattanDistance(Point(currentX+1, currentY), Maze::getEnd());
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX+1, currentY, currentMaze->getTraversed(), currentMaze->getCost()+1, distance);
			tempMaze->setPoint(currentX+1, currentY);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validDown())
		{
			int distance = manhattanDistance(Point(currentX, currentY+1), Maze::getEnd());
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX, currentY+1, currentMaze->getTraversed(), currentMaze->getCost()+1, distance);
			tempMaze->setPoint(currentX, currentY+1);
			maze_queue.push(tempMaze);
		}
		if(currentMaze->validLeft())
		{
			int distance = manhattanDistance(Point(currentX-1, currentY), Maze::getEnd());
			Maze* tempMaze = new Maze(currentMaze->getMaze(), currentX-1, currentY, currentMaze->getTraversed(), currentMaze->getCost()+1, distance);
			tempMaze->setPoint(currentX-1, currentY);
			maze_queue.push(tempMaze);
		}
		currentMaze = maze_queue.top();
		currentX = currentMaze->getX();
		currentY = currentMaze->getY();
		maze_queue.pop();
		Maze::incrementNodes();
	}

	currentMaze->fillMaze();
	currentMaze->printMaze();
	cout << "Nodes Expanded: " << Maze::getNodes() << endl;
	cout << "Path cost: " << currentMaze->getCost() << endl;
	cout << "exiting a_star" << endl;
	struct INFO return_info;
	return_info.cost = currentMaze->getCost();
	return_info.traveled = currentMaze->getTraversed();
	//print_queue(maze_queue);
	return return_info;

}

int main(int argc, char** argv)
{
	if(argc==3)// multiple dot case
	{
		cout << "multiple dot maze input provided" << endl;
		ifstream file;
		file.open(argv[1]);
		if(!file)
		{
			cout << "Unable to open file. Please provide another" << endl;
			return -1;
		}
		int width = num_lines(argv[1]);
		int height = width_of_file(argv[1]);
		char** test_maze = new char*[width];
		for(int i=0; i<width; i++)
		{
			test_maze[i] = new char[height];

		}
		Maze::setWidth(width);
		Maze::setHeight(height);
		int i=0;
		int j=0;
		char c;
		Point pacman;
		int pacmanIndex;
		vector<Point> dots;

		while (!file.eof() ) {
			file.get(c);

			if(c=='P')
			{
				pacman.setX(i);
				pacman.setY(j);
				pacmanIndex = dots.size();
				dots.push_back(pacman);
			}
			if(c=='.')
			{

				dots.push_back(Point(i,j));
			}
			if(c!='\n')
			{
				test_maze[i][j]=c;
				j++;
			}
		 	else
			{
				i++;
				j=0;
			}

		}
		int size = dots.size();
		file.close();
		cout << "number of dots to find: " << dots.size() << endl;

		vector<vector<INFO>> costs;
		for(int i=0; i<size; i++)
		{
			costs.push_back(vector<INFO>());
		}
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				struct INFO temp;
				costs[i].push_back(temp);
			}

		}
		for(int i=0; i<size; i++)
	    {
			Maze* current = new Maze(test_maze, dots.at(i).getX(), dots.at(i).getY(), vector<Point>(), 0, width+height);
			for(int j=i+1; j<size; j++)
			{
				Maze::setEnd(dots.at(j));
				current->reset();
				costs[i][j] = a_star(current);
				costs[j][i] = costs[i][j];
			}
		}
		Node::setInformation(costs);
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				cout << costs[i][j].cost << " ";
			}
			cout << endl;
		}
		cout << "pacman index: " << pacmanIndex << endl;
		Node* current = new Node(pacmanIndex, map<int, bool>(), 0, 1);
		auto cmp = [](Node* left, Node* right){
			bool visitedLeft;
			bool visitedRight;
			vector<vector<INFO>> temp = Node::getInformation();
			for(int i=0; i<temp.size(); i++)
			{
				if(left->getVisited()[i])
				{

				}
			}
			for(int i=0; i<temp.size(); i++)
			{
				if(right->getVisited()[i])
				{

				}
			}
			return left->getCostToGetHere() > right->getCostToGetHere();
		};

		priority_queue<Node*, std::vector<Node*>, decltype(cmp)> node_queue(cmp);
		while(current->getNumberOfNodes()!=size)
		{

			current->markAsVisited();
			for(int i=0; i<size; i++)
			{
				if(!current->getVisited()[i])
				{
					node_queue.push(new Node(i, current->getVisited(), current->getCostToGetHere()+costs[current->getNumber()][i].cost, current->getNumberOfNodes()+1));
				}
			}
			current = node_queue.top();
			node_queue.pop();
			Node::incrementOverall();
		}
		cout << "cost: " << current->getCostToGetHere() << endl;
		cout << "Nodes expanded in second layer: " << Node::getOverall() << endl;
		cout << "finished multi dot search" << endl;
	}
	else if(argc!=2)
	{
		cout << "Please provide 1 maze file" << endl;
	}
	else //single dot case
	{

		ifstream file;
		file.open(argv[1]);
		if(!file)
		{
			cout << "Unable to open file. Please provide another" << endl;
			return -1;
		}
		int width = num_lines(argv[1]);
		int height = width_of_file(argv[1]);
		Maze::setWidth(width);
		Maze::setHeight(height);

		char** test_maze = new char*[width];
		for(int i=0; i<width; i++)
		{
			test_maze[i] = new char[height];

		}
		int i=0;
		int j=0;
		char c;
		int x=0, y=0;
		Point end;

		while (!file.eof() ) {
			file.get(c);

			if(c=='P')
			{
			  x = i;
			  y = j;
			}
			if(c=='.')
			{
			  end.setX(i);
			  end.setY(j);
			}
			if(c!='\n')
			{
				test_maze[i][j]=c;

				j++;
			}
		 	else
			{
				i++;
				j=0;
			}

		}
		file.close();
		Maze* start = new Maze(test_maze, x, y, vector<Point>(),0, width+height);
		Maze::setEnd(end);
		depth_first_search(start);
		start->reset();
		breadth_first_search(start);
		start->reset();
		greedy(start);
		start->reset();
		a_star(start);
	}
	return 0;
}
