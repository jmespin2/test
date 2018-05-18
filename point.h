class Point
{
	public:
		Point();
		Point(int x, int y);
		int getX() const;
		int getY() const;
		void setX(int x);
		void setY(int y);
		bool operator<(const Point & rhs) const;
	private:
		int _x;
		int _y;
};
