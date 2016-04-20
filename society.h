#ifndef SOCIETY_H
#define SOCIETY_H

#include <string>

#include "creature.h"

using namespace std;

class Creature;

class Society{
	unsigned int seats;
	Creature ** c;
	bool clone(int, int);
	unsigned int get_position(const Creature *);
	void beat(unsigned int);
	void bless(unsigned int);
public:
	Society(unsigned int, unsigned int, unsigned int, unsigned int);
	void action();
	void clone_next(const Creature *);
	void clone_zombies(const Creature *);
	unsigned int no_of_good();
	unsigned int no_of_bad();
	unsigned int no_of_zombies();
	void print(const string);
	~Society();
};

#endif
