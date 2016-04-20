#include <iostream>

#include "bad-creature.h"

Bad_Creature::Bad_Creature(string n, unsigned int l, unsigned int bad_thrsh, Society * soc)
: threshold(bad_thrsh), Creature(n, l, soc)
{
	cout << "Bad_Creature has been created!" << endl;
}

Bad_Creature::Bad_Creature(const Bad_Creature& bc) 
: threshold(bc.threshold), Creature(bc)
{
	cout << "Bad_Creature has been created by copying!" << endl;
}

bool Bad_Creature::is_a_good() const{
	return false;
}

bool Bad_Creature::is_robust(){
	return (get_life() > threshold);
}

void Bad_Creature::bless(){
	Creature::bless();
	if (is_robust())
		society->clone_zombies(&(*this));
}

void Bad_Creature::beat(){
	Creature::beat();
}

Creature * Bad_Creature::Clone(){
	return new Bad_Creature(*this);
}

Bad_Creature::~Bad_Creature(){
	cout << "Bad_Creature is about to be destroyed!\t";
}
