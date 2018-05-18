#include "node.h"
using namespace std;
int Node::overallNodes = 0;
vector<vector<INFO>> Node::information = vector<vector<INFO>>();
Node::Node(int number, map<int, bool> visited, int costToGetHere, int numberOfNodes)
{
	_visited = visited;
	nodeNumber = number;
	_costToGetHere = costToGetHere;
	numNodes = numberOfNodes;
}

void Node::setInformation(vector<vector<INFO>> _information)
{
	information = _information;
}

vector<vector<INFO>> Node::getInformation()
{
	return information;
}


int Node::getNumber()
{
	return nodeNumber;
}

int Node::getCostToGetHere()
{
	return _costToGetHere;
}

void Node::incrementOverall()
{
	overallNodes++;
}

int Node::getOverall()
{
	return overallNodes;
}

int Node::getNumberOfNodes()
{
	return numNodes;
}
void Node::markAsVisited()
{
	_visited[nodeNumber] = true;
}
map<int, bool> Node::getVisited()
{
	return _visited;
}


