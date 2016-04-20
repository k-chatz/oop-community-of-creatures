#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <cstdlib>
#include <string>

#include "society.h"

using namespace std;

class Society;

class Creature{
	string name;
	unsigned int life;
	bool updated;
protected:
	Society * society;
public:
	/*Constructor*/
	Creature(string n, unsigned int, Society *);

	/*Copy constructor*/
	Creature(const Creature&);

	/*Virtual Copy Constructor*/
	virtual Creature * Clone() = 0;
	virtual bool is_robust() = 0;
	bool is_updated();
	string get_name() const;
	unsigned int get_life() const;
	virtual void bless();
	virtual void beat();
	bool is_a_zombie() const;
	virtual bool is_a_good() const;

	/*Destructor*/
	virtual ~Creature();
};

#endif
