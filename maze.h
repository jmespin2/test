#include "point.h"
#include <map>
#include <vector>
using namespace std;
/**
 * Represents an snapshot of maze
 */
class Maze
{
    public:
	/**
	 * Creates a maze based on parameters to be determined.
	*/
	Maze(char** maze, int x, int y, vector<Point> traveled, int cost, int distance);

	static void incrementNodes();
	static void setHeight(int h);
	static void setWidth(int w);
	static int getWidth();
	static int getHeight();
	static int getNodes();
	static void setEnd(Point p);
	static Point getEnd();	
	
	bool validUp();
	bool validDown();
	bool validLeft();
	bool validRight();

	int getX();
	int getY();
	int getDistance();
	vector<Point> getTraversed();
	int getCost();
	char** getMaze();
	void printMaze();
	void setPoint(int x, int y);
	void clearMaze();
	void fillMaze();
	void reset();

    private:
        char** _maze;
	int _x;
	int _y;
	int _cost; // represents cost to get to this point
	int _distance; //some approximate distance to goal 
	vector<Point> _traveled;
	
	static Point _end;
	static int _nodes;
	static int _width;
	static int _height;
	static map<Point, bool> _visited;
};
