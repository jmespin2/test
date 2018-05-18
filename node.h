//#include <vector>
//#include <map>
#include "maze.h"
//#include "point.h"
using namespace std;

struct INFO
{
	int cost;
	vector<Point> traveled;
};


class Node
{

	public:

		Node(int number, map<int, bool> visited, int costToGetHere, int numberOfNodes); 

		int getNumber();
		int getCostToGetHere();
		void markAsVisited();
		int getNumberOfNodes();
		map<int, bool> getVisited();
		static void incrementOverall();
		static int getOverall();
		static vector<vector<INFO>> getInformation();
		static void setInformation(vector<vector<INFO>> info);

	private:
		static int overallNodes;
		int numNodes;
		map<int, bool> _visited;
		int nodeNumber;
		int _costToGetHere;
		static vector<vector<INFO>> information;
};
