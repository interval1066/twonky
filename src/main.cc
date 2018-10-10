#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <string>
#include <memory>
#include <twonky.h>
#include <tgrid.h>

using namespace std;
using namespace hellotechie;

int
main()
{
	bool bQuit = false;
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

    g->DisplayGrid();

	return EXIT_SUCCESS;
}

void
DisplayHelp(void)
{
	cout << endl << "Twonky Hunt" << endl;
	cout << "====== ====" << endl << endl;
	cout << "Twonky Hunt is a simple single-player game with the goal of escaping a " << endl;
	cout << "maze populated by a murderous monster called the Twonky. The maze is a " << endl;
	cout << "simple 15 x 15 grid filled with pits, \'supertraps\', the Twonky, and " << endl;
	cout << "an exit. Your goal is to get out of the maze by reaching a square " << endl;
	cout << "marked by a large \'E\' (the exit). You've some tools at your disposal " << endl;
	cout << "to help you get to the exit (the goal); one is a raygun that will kill " << endl;
	cout << "the Twonky, but the Twonky will re-spawn, buying you only a little time. " << endl;
	cout << "You may only shoot at the four cardinal directions (N, S, E, W). You " << endl;
	cout << "can also look at a 3 x 3 section of the maze at any time, at the cost " << endl;
	cout << "of allowing the Twonky an extra move. The maze is populated with walls, " << endl;
	cout << "pits, and traps, and while you're subject to falling into these traps " << endl;
	cout << "or losing a turn by being blocked by walls, the Twonky can walk right " << endl;
	cout << "through any such obsticles." << endl << endl;
	cout << "Command List:" << endl << endl;
	cout << "m(d) - move, d can be any cardinal compass point (n, s, e, w)" << endl;
	cout << "l    - look; presents a 3 x 3 view of the maze" << endl;
	cout << "s(d) - shoot, again, in any of the 4 cardinal compass points" << endl;
	cout << "q    - quit the game" << endl << endl;
	cout << "Avoid the pits, traps, and twonky, get to the exit, and win the game." << endl;
	cout << "See the man page for more information." << endl << endl;
}

