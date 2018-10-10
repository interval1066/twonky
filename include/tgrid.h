/**
 * Twonky Grid class - contains the positions of our
 * player, the twonky, and all the various maze sqaures.
 * Also defines the behavior of the twonky, which is simple
 * enough that it can be an member of the grid rather than
 * its own class.
 *
 * t.o.
 */

#ifndef TGRID_H_
#define TGRID_H_

#include <cmath>

// A maze square contians one of
const int NOTHING =         0;
const int WALL =	 		1;
const int SUPERTRAP	=		2;
const int PIT =				3;
const int TWONKY =			4;
const int PLAYER =			5;
const int QUIT =			6;
const int EDGE = 			7;

// Min & max dimensions of maze
#define X_MIN 				0
#define X_MAX 				15

// Terminal distance from the twonky
#define TERMINAL_DIST	1

// Distance from exit for victory
#define WIN_DIST			.9

namespace hellotechie
{
	// Point - your basic poco
	// Compiler-supplied ctor/dtor good enough
	class Point
	{
		double xval, yval;

	public:
		Point(double x = 0.0, double y = 0.0)
		{
			xval = x;
			yval = y;
		}
		// Not too sure if these are nessessary
		Point(const Point& p)
		{
			xval = p.xval;
			yval = p.yval;
		}

		Point& operator=(const Point& p)
		{
	      xval = p.xval;
	      yval = p.yval;

	      return *this;
		}

		double x() { return xval; }
		double y() { return yval; }
		void setx(double x) { xval = x; }
		void sety(double y) { yval = y; }

		// Embed Pythagorean theorem so we can calulate distance to other points
		inline unsigned int dist(Point* other)
		{
			double xd = abs(xval - other->xval);
			double yd = abs(yval - other->yval);
			return abs(sqrt((xd * xd) + (yd * yd)));
		}
	};

	class TwonkyGrid
	{
		unsigned int grid[16][16];
		unsigned int uOldSq1;
		void initGrid();

	public:
		TwonkyGrid();
		virtual ~TwonkyGrid();

		// Displays the entire grid
		void DisplayGrid(void);
		int MoveUser(char&);
		// The player is armed!
		unsigned int ShootRaygun(char&);

		// Displays the area around the player in a 3x3 view
		void PlayerView(void);

		// This moves the twonky using a very simple strategy
		bool MoveTwonk(void);

		// Has the player won yet?
		inline bool CheckExit()
		{
			bool bRet;
			(pUser->dist(pExit) <= WIN_DIST)? bRet = true : bRet = false;
			return bRet;
		}

		// Our mobile objects
		Point* pTwonky;
		Point* pUser;
		Point* pExit;
	};
}

#endif

