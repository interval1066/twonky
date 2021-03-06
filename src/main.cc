#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <string>
#include <memory>
#include <twonky.h>
#include <tgrid.h>
#include <cstring>

using namespace std;
using namespace hellotechie;

int
main(int argc, char** argv)
{
	bool bQuit = false, bDraw = true;

	if((argv[1]) && strcmp(argv[1], "-n") == 0)
			bDraw = false;

	char a;
	string uin;

	queue<char> q;
	unique_ptr<TwonkyGrid> g(new TwonkyGrid());
	cout << "Welcome to Twonky Hunt. Type \'h\' for help. Good luck." << endl << endl;

	do
	{
		cout << "The Twonky is " << g->pUser->dist(g->pTwonky) << " grid units from you." << endl;
		bQuit = g->MoveTwonk();

		if(bQuit) {
			cout << "SLUURRPP!! Sorry, the Twonky got you!" << endl;
			break;
		}

		cout << "You are " << g->pUser->dist(g->pExit) << " grid units from the exit." << endl;
		bQuit = g->CheckExit();

		if(bQuit) {
			cout << "You ESCAPED!!! You WON!!! Good Job!" << endl;
			break;
		}

		cout << "Your move: ";
		getline(cin, uin);

		uin = trimAll(uin);
		string::iterator it = uin.begin();

		while (it != uin.end()) {
			a = tolower(*it++);

			if(a == 'q') {
				bQuit = true;
				break;
			}
			q.push(a);
		}
		uin.clear();
		unsigned int uTarget;
		while(q.size() > 0)
		{
			a = q.front();
			if(!q.empty()) q.pop();
			char dir;

			switch(a) {
				case 'm': dir = q.front();
				if(chckDir(dir) == false) {
					cout << "Unknown direction" << endl;
					break;
				}

				if(g->MoveUser(dir) != NOTHING) {
					switch(g->MoveUser(dir)) {
						case EDGE:
						cout << "You can't go that way." << endl;
						break;

						case WALL: cout << "Your way is blocked by a wall." << endl;
						break;

						case SUPERTRAP:
						cout << "You\'ve stepped on a SUPERTRAP! The entire maze is re-arranged." << endl;
						g.reset(new TwonkyGrid());
						break;

						case QUIT:
						cout << "You escaped! You've won the game!" << endl;
						bQuit = true;
						break;

						case PIT:
						cout << "Sorry! You've fallen in to a pit and died!" << endl;
						bQuit = true;
						break;

						case TWONKY:
						cout << "You deliberately ran into the Twonky! You're DEAD!" << endl;
						bQuit = true;

						default:
						break;
					}
				}
				break;

				case 's': dir = q.front();
				if(chckDir(dir) == false) {
					cout << "Unknown direction" << endl;
					break;
				}
				uTarget = g->ShootRaygun(dir);
				if(uTarget == TWONKY) {
					cout << endl << "You shot the Twonky!" << endl;
					cout << "You get a one turn reprieve while a new one enters the maze..." << endl;
					unsigned int x = rand() % 16;
					unsigned int y = rand() % 16;

					g->pTwonky->setx(x);
					g->pTwonky->sety(y);
				}
				if(uTarget == WALL)
					cout << endl << "*BLAM* Your shot hit a wall." << endl;

				if(uTarget == EDGE)
					cout << "~Fizzle~ Sorry, your shot left the maze." << endl;
				break;

				case 'l':
				g->PlayerView();
				break;

				case 'd':
				g->DisplayGrid();
				break;

				case '?':
				case 'h': DisplayHelp();
				break;

				default: cout << "Unrecognized command" << endl;
				break;
			}
			while(!q.empty()) q.pop();
		}
	} while(!bQuit);

	if(bDraw) g->DisplayGrid();

	return EXIT_SUCCESS;
}

