#include "creature.h"

/*Constructor*/
Creature::Creature(string n, unsigned int L, Society * soc)
:name(n), life(L), updated(false), society(soc)
{
	cout << "Creature with name: '" << name << "' and life: " << life << " has been created!\t";
}

/*Copy constructor*/
Creature::Creature(const Creature& c)
: name(c.name), life(c.life), updated(true), society(c.society)
{
	cout << "Creature with name: '" << name << "' and life: " << life << " has been created by copying!\t";
}

bool Creature::is_updated(){
	if(updated){
		updated = false;
		return true;
	}
	else
		return false;
}

string Creature::get_name() const{
	return this->name;
}

unsigned int Creature::get_life() const{
	return this->life;
}

void Creature::bless(){
	if (!is_a_zombie()){
		life++;
		updated = true;
	}
}

void Creature::beat(){
	if (!is_a_zombie()){
		life--;
		updated = true;
	}
}

bool Creature::is_a_zombie() const{
	return (life == 0);
}

bool Creature::is_a_good() const{
	return this->is_a_good();
}


/*Destructor*/
Creature::~Creature(){
	cout << "Creature: " << name << " with and life: " << life << " is about to be destroyed!" <<  endl;
}
