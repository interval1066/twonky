/**
 * tgrid class def, see header file for details
 *
 */
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <tgrid.h>

using namespace std;
using namespace hellotechie;

TwonkyGrid::TwonkyGrid()
{
	srand((unsigned)time(0));
	initGrid();
	uOldSq1 = NOTHING;
}

TwonkyGrid::~TwonkyGrid()
{
	if(pUser) {  delete pUser; pUser =  nullptr; }
	if(pExit) { delete pExit; pExit = nullptr; }
}

void
TwonkyGrid::initGrid()
{
	unsigned int gridx;
	unsigned int gridy;
	bool bPopulated = true;

	for (int row = 0; row < 16; row++) {
		for (int col = 0; col < 16; col++) {
			grid[row][col] = NOTHING;

			unsigned int glyph = rand() % 9;
			if(glyph > 6)
				 grid[row][col] = WALL;
		}
	}

	for(int n = 0; n < 2; n++) {
		gridx = rand() % 16;
		gridy = rand() % 16;
		grid[gridx][gridy] = SUPERTRAP;
	}

	for(int n = 0; n < 2; n++) {
		gridx = rand() % 16;
		gridy = rand() % 16;
		grid[gridx][gridy] = PIT;
	}

	gridx = rand() % 16;
	gridy = rand() % 16;

	pTwonky = new Point(static_cast<double>(gridx),
		static_cast<double>(gridy));
	grid[gridx][gridy] = TWONKY;

	while(bPopulated) {
		gridx = rand() % 16;
		gridy = rand() % 16;
		pUser = new Point(static_cast<double>(gridx),
			static_cast<double>(gridy));

		if(grid[gridx][gridy] == NOTHING) {
			grid[gridx][gridy] = PLAYER;
			bPopulated = false;
		}
		else
			bPopulated = true;
	}

	bPopulated = true;
	while(bPopulated) {
		gridx = rand() % 16;
		gridy = rand() % 16;

		if(grid[gridx][gridy] == NOTHING) {
			pExit = new Point(static_cast<double>(gridx),
				static_cast<double>(gridy));

			grid[gridx][gridy] = QUIT;
			bPopulated = false;
		}
	}
}

void
TwonkyGrid::DisplayGrid()
{
	for(int n = 0; n < 16; n++)
		cout << "|---";

	cout << "|" << endl;

	for (int row = 0; row < 16; row++) {
		for (int col = 0; col < 16; col++) {
			switch(grid[row][col]) {
				case NOTHING: cout << "|   ";
				break;

				case WALL: cout << "| W ";
				break;

				case SUPERTRAP: cout << "| S ";
				break;

				case PIT: cout << "| P ";
				break;

				case TWONKY: cout << "| T ";
				break;

				case PLAYER: cout << "| * ";
				break;

				case QUIT: cout << "| E ";
				break;
			}
		}
		cout << "|" << endl;
		for(int n = 0; n < 16; n++)
			cout << "|---";

		cout << "|" << endl;
	}
}

void
TwonkyGrid::PlayerView(void)
{
	int x2, y2, x3, y3;
	int x = static_cast<int>(pUser->x());
	int y = static_cast<int>(pUser->y());
	((x < X_MIN + 1) || (x > X_MAX - 1))? x2 = 1 : x2 = 0;
	((y < X_MIN + 1) || (y > X_MAX - 1))? y2 = 1 : y2 = 0;

	for(int n = y2; n < 3; n++)
		cout << "|---";

	cout << "|" << endl;

	for(int m = x2; m < 3; m++) {
		for(int n = y2; n < 3; n++) {
			(x > X_MAX - 1)? x3 = x + m - 2 : x3 = x + m - 1;
			(y > X_MAX - 1)? y3 = y + n - 2 : y3 = y + n - 1;

			switch(grid[x3][y3]) {

				case NOTHING: cout << "|   ";
				break;

				case WALL: cout << "| W ";
				break;

				case SUPERTRAP: cout << "| S ";
				break;

				case PIT: cout << "| P ";
				break;

				case TWONKY: cout << "| T ";
				break;

				case PLAYER: cout << "| * ";
				break;

				case QUIT: cout << "| E ";
				break;

				case EDGE: cout << "";
				break;
			}
		}
		cout << "|" << endl;

		for(int o = y2; o < 3; o++)
			cout << "|---";

		cout << "|" << endl;
	}
}

bool
TwonkyGrid::MoveTwonk(void)
{
	if(pUser->dist(pTwonky) < TERMINAL_DIST)
		return true;

	grid[static_cast<int>(pTwonky->x())][static_cast<int>(pTwonky->y())] = uOldSq1;
	Point hold = (*pTwonky);

	int x = static_cast<int>(pTwonky->x());
	hold.setx(x += 1);

	uOldSq1 = grid[static_cast<int>(hold.x())][static_cast<int>(hold.y())];
	if(pUser->dist(&hold) <= pUser->dist(pTwonky))
		pTwonky->setx(hold.x());

	hold = (*pTwonky);
	x = static_cast<int>(pTwonky->x());
	hold.setx(x -= 1);
	uOldSq1 = grid[static_cast<int>(hold.x())][static_cast<int>(hold.y())];
	if(pUser->dist(&hold) <= pUser->dist(pTwonky))
		pTwonky->setx(hold.x());

	hold = (*pTwonky);
	int y = static_cast<int>(pTwonky->y());
	hold.sety(y += 1);

	uOldSq1 = grid[static_cast<int>(hold.x())][static_cast<int>(hold.y())];
	if(pUser->dist(&hold) <= pUser->dist(pTwonky))
		pTwonky->sety(hold.y());

	hold = (*pTwonky);
	y = static_cast<int>(pTwonky->y());
	hold.sety(y -= 1);

	uOldSq1 = grid[static_cast<int>(hold.x())][static_cast<int>(hold.y())];
	if(pUser->dist(&hold) <= pUser->dist(pTwonky))
		pTwonky->sety(hold.y());

	grid[static_cast<int>(pTwonky->x())][static_cast<int>(pTwonky->y())] = TWONKY;

	return false;
}

int
TwonkyGrid::MoveUser(char& m)
{
	int nStat = EDGE;

	switch(m) {
		case 'n':
			if((grid[static_cast<int>(pUser->x()) - 1][static_cast<int>(pUser->y())] == NOTHING) && (pUser->x() > X_MIN)) {
				grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y())] = NOTHING;
				nStat = NOTHING;
				pUser->setx(pUser->x() - 1);
				grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y())] = PLAYER;
			}
			else {
				if(pUser->x() <= X_MIN)
					nStat = EDGE;
				else
					nStat = grid[static_cast<int>(pUser->x()) - 1][static_cast<int>(pUser->y())];
			}
		break;

		case 's':
			if((grid[static_cast<int>(pUser->x()) + 1][static_cast<int>(pUser->y())] == NOTHING) && (pUser->x() < X_MAX)) {
				grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y())] = NOTHING;
				nStat = NOTHING;
				pUser->setx(pUser->x() + 1);
				grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y())] = PLAYER;
			}
			else {
				if(pUser->x() >= X_MAX)
					nStat = EDGE;
				else
					nStat = grid[static_cast<int>(pUser->x()) + 1][static_cast<int>(pUser->y())];
			}
		break;

		case 'e':
			if((grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y()) + 1] ==
                NOTHING) && (pUser->y() < X_MAX)) {
				grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y())] = NOTHING;
				nStat = NOTHING;
				pUser->sety(pUser->y() + 1);
				grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y())] = PLAYER;
			}
			else {
				if(pUser->y() >= X_MAX)
					nStat = EDGE;
				else
					nStat = grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y()) + 1];
			}
		break;

		case 'w':
			if((grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y()) - 1] ==
                NOTHING) && (pUser->y() > X_MIN)) {
				grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y())] = NOTHING;
				nStat = NOTHING;
				pUser->sety(pUser->y() - 1);
				grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y())] = PLAYER;
			}
			else {
				if(pUser->y() <= X_MIN)
					nStat = EDGE;
				else
					nStat = grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y()) - 1];
			}
		break;
	}
	return nStat;
}

unsigned int
TwonkyGrid::ShootRaygun(char& m)
{
	unsigned int nGlyph = NOTHING;
	int nAx = 0;
	switch(m) {
		case 'n':
			while((nGlyph == NOTHING) && (nAx < X_MAX)) {
				nGlyph = grid[static_cast<int>(pUser->x()) - (++nAx)][static_cast<int>(pUser->y())];
				cout << "ZAP... ";
			}
		break;

		case 's':
			while((nGlyph == NOTHING) && (nAx < X_MAX)) {
				nGlyph = grid[static_cast<int>(pUser->x()) + (++nAx)][static_cast<int>(pUser->y())];
				cout << "ZAP... ";
			}
		break;

		case 'e':
			while((nGlyph == NOTHING) && (nAx < X_MAX)) {
				nGlyph = grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y()) + (++nAx)];
				cout << "ZAP... ";
			}
		break;

		case 'w':
			while((nGlyph == NOTHING) && (nAx > X_MIN)) {
				nGlyph = grid[static_cast<int>(pUser->x())][static_cast<int>(pUser->y()) - (++nAx)];
				cout << "ZAP... ";
			}
		break;
	}
	return nGlyph;
}

