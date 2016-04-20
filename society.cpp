#include <iostream>
#include <sstream>	/*For ostringstream*/

#include "society.h"
#include "good-creature.h"
#include "bad-creature.h"

/*COLOR*/
#define GRAY  "\x1B[90m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"

/*BOLD-UNDERLINE-COLOR*/
#define B_U_GRAY  "\x1B[1m\x1B[4m\x1B[90m"
#define B_U_RED  "\x1B[1m\x1B[4m\x1B[31m"
#define B_U_GREEN  "\x1B[1m\x1B[4m\x1B[32m"

/*RESET COLOR*/
#define RESET  "\x1B[0m"

/*
 * BLACK CIRCLE CHARACTER
 * http://www.fileformat.info/info/unicode/char/25CF/index.htm
 */
#define BLACK_CIRCLE "\u25CF"

string good[10] = { "Duck", "Zebra", "Chicken", "Goat", "Fish",
"Snail", "Cow", "Horse", "Hare", "Frog" };

string bad[10] = { "Aswang", "Adlet", "Duende", "Doppelganger",
"Kikiyaon", "Banshee", "Tikbalang", "Jinn", "Harpy", "Warg" };

/*Private*/

bool Society::clone(int source, int target){
	if (target == source) return false;
	delete c[target];
	c[target] = c[source]->Clone();
	return true;
}

unsigned int Society::get_position(const Creature * cr){
	unsigned int p = -1;
	for (unsigned int i = 0; i < seats; i++){
		if (cr == c[i]){
			p = i;
			break;
		}
	}
	return p;
}

void Society::beat(unsigned int i){
	if (i >= 0 && i < seats){
		cout << "Beat " << i + 1 << " {" << c[i]->get_life() << "} " << c[i]->get_name() << endl;
		c[i]->beat();
	}
	else
		cerr << "Error: [Class Society::beat()]\tThe seat " << i << " is out of limits array!" << endl;
}

void Society::bless(unsigned int i){
	if (i >= 0 && i < seats){
		cout << "Bless " << i + 1 << " {" << c[i]->get_life() << "} " << c[i]->get_name() << endl;
		c[i]->bless();
	}
	else
		cerr << "Error: [Class Society::bless()]\tThe seat " << i << " is out of limits array!" << endl;
}

/*Public*/

/*Constructor*/
Society::Society(unsigned int N, unsigned int L, unsigned int good_thrsh, unsigned int bad_thrsh)
: seats(N)
{
	ostringstream name;
	c = new Creature*[seats];
	for (unsigned int i = 0; i < seats; i++){
		if (rand() % 2 == 1){
			name << good[rand() % 10] << i + 1 << std::ends;
			c[i] = new Good_Creature(name.str(), L, good_thrsh, &(*this));
		}
		else{
			name << bad[rand() % 10] << i + 1 << std::ends;
			c[i] = new Bad_Creature(name.str(), L, bad_thrsh, &(*this));
		}
		name.str("");
	}
	cout
		<< "Society created with " << no_of_good()
		<< " good creatures and " << N - no_of_good()
		<< " bad creatures " << endl;
}

void Society::action(){
	while (no_of_zombies() < seats){
		unsigned int i = rand() % seats;
		if (!c[i]->is_a_zombie()){
			if (rand() % 2 == 1)
				bless(i);
			else
				beat(i);
			break;
		}
	}
}

void Society::clone_next(const Creature * cr){
	unsigned int i = get_position(cr);
	if (i >= 0 && i < seats){
		const unsigned int next = (i + 1) % seats;
		if (clone(i, next)){
			cout
				<< "Clone next: "
				<< next + 1
				<< " {"
				<< c[next]->get_life()
				<< "} "
				<< c[next]->get_name()
				<< endl;
		}
		else
			cerr << "Cannot become clone with himself!" << endl;
	}
	else
		cerr << "Error: [Class Society::clone_next()]\tThe seat " << i << " is out of limits array!" << endl;
}

void Society::clone_zombies(const Creature * cr){
	unsigned int i = get_position(cr);
	if (i >= 0 && i < seats){
		for (unsigned int j = i + 1; j < seats; j++){
			if (c[j]->is_a_zombie()){
				clone(i, j);
				cout
					<< "Clone zombie: "
					<< j + 1
					<< " {"
					<< c[j]->get_life()
					<< "} "
					<< c[j]->get_name()
					<< endl;
			}
		}
	}
	else
		cerr << "Error: [Class Society::clone_zombies()]\tThe seat " << i << " is out of limits array!" << endl;
}

unsigned int Society::no_of_good(){
	int g = 0;
	for (unsigned int i = 0; i < seats; i++)
	if (c[i]->is_a_good() && !c[i]->is_a_zombie()){
		g++;
	}
	return g;
}

unsigned int Society::no_of_bad(){
	return seats - no_of_good() - no_of_zombies();
}

unsigned int Society::no_of_zombies(){
	int z = 0;
	for (unsigned int i = 0; i < seats; i++){
		if (c[i]->is_a_zombie())
			z++;
	}
	return z;
}

/*Print*/
void Society::print(const string description){
        cout
                << "\n" << description
                << "\t(Good: " << no_of_good()
                << ", Bad: " << no_of_bad()
                << ", Zombies: " << no_of_zombies()
                << ")"
                << endl;

        for (unsigned int i = 0; i < seats; i++){
                const unsigned int life = c[i]->get_life();
                const bool good = c[i]->is_a_good();
                const bool zombie = c[i]->is_a_zombie();
                const bool updated = c[i]->is_updated();
                cout
                        << (zombie ? (updated ? B_U_GRAY : GRAY) : (good ? (updated ? B_U_GREEN : GREEN) : (updated ? B_U_RED : RED)))
                        << " " //"{"
                        << BLACK_CIRCLE //life
                        << " " //"}"
                        << RESET;
        }
        cout << endl;
}

Society::~Society(){
	cout << "Society is about to be destroyed!" << endl;
	for (unsigned int i = 0; i < seats; i++)
		delete c[i];
	delete[] c;
}
