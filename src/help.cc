#include <iostream>

using namespace std;

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

