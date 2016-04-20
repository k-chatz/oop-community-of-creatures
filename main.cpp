#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include <sys/ioctl.h>
#include <unistd.h>

#include "society.h"

using namespace std;

void separate(){
        int col;
        /*The following code is from:
        * http://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
        */
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        col = w.ws_col;
        for (int i = 1; i <= col; i++)
                (i == 1 || i == col) ? cout << '+' : cout << '-';
        cout << endl;
}

int main(int argc, char * argv[]){

	srand((unsigned int) time(NULL));

	if (argc < 5){
		cerr << "Error: Invalid arguments!\n"
			<< "Run again with these integer values: [N] [M] [L] [good threshold] [bad threshold]" << endl;
		cin.get();
		exit(1);
	}

	/*The following variables will take values from the command line:*/
	unsigned int N = atoi(argv[1]);
	unsigned int M = atoi(argv[2]);
	unsigned int L = atoi(argv[3]);
	unsigned int good_thrsh = atoi(argv[4]);
	unsigned int bad_thrsh = atoi(argv[5]);

	N = (N >= 0) ? N : 0;
	M = (M >= 0) ? M : 0;
	L = (L >= 0) ? L : 0;
	good_thrsh = (good_thrsh >= 0) ? good_thrsh : 0;
	bad_thrsh = (bad_thrsh >= 0) ? bad_thrsh : 0;

	cout << "Start community of creatures simulation with:\n"
		<< N << " creatures, "
		<< M << " actions (Bless, beat), "
		<< L << " points common life, "
		<< good_thrsh << " good threshold, "
		<< bad_thrsh << " bad threshold, "
		<< endl;
	separate();

	if (N > 0){
		Society c(N, L, good_thrsh, bad_thrsh);

		/*Print society before any action*/
		c.print("Society before any action:");
		separate();
		cout << "Press enter to start simulation.." << endl;
		cin.get();

		for (unsigned int i = 0; i < M; i++){
			cout << "Action " << i + 1 << ": ";
			c.action();

			/*Print society after action*/
			c.print("Society after action:");
			separate();
			cin.get();

			/*Check if all creatures are either zombies or good or bad to finish the simulation*/
			if(c.no_of_zombies() == N || c.no_of_good() == N || c.no_of_bad() == N)
				break;
		}

		if (c.no_of_zombies() != N){
			if (c.no_of_good() == N)
				cout << "Good Dominates in the world!" << endl;
			else
				cout << "Try again to improve the world" << endl;
		}
		else
			cout << "This is a dead society" << endl;
	}
	else
		cout << "To create the society needs at least one creature!" << endl;

	cin.get();
	return 0;
}
