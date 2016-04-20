#include <iostream>

#include "good-creature.h"

Good_Creature::Good_Creature(string n, unsigned int l, unsigned int good_thrsh, Society * soc)
: threshold(good_thrsh), Creature(n, l, soc)
{
	cout << "Good_Creature has been created!" << endl;
}

Good_Creature::Good_Creature(const Good_Creature& gc) 
: threshold(gc.threshold), Creature(gc)
{
	cout << "Good_Creature has been created by copying!" << endl;
}

bool Good_Creature::is_a_good() const{
	return true;
}

bool Good_Creature::is_robust(){
	return (get_life() > threshold);
}

void Good_Creature::bless(){
	Creature::bless();
	if (is_robust())
		society->clone_next(&(*this));
}

void Good_Creature::beat(){
	Creature::beat();
}

Creature * Good_Creature::Clone(){
	return new Good_Creature(*this);
}

Good_Creature::~Good_Creature(){
	cout << "Good_Creature is about to be destroyed!\t";
}
