#ifndef BADCREATURE_H
#define BADCREATURE_H

#include <string>

#include "creature.h"

class Bad_Creature : public Creature{
	const unsigned int threshold;
public:
	Bad_Creature(string, unsigned int, unsigned int, Society *);
	Bad_Creature(const Bad_Creature&);
	bool is_a_good() const;
	bool is_robust();
	void bless();
	void beat();
	Creature * Clone();
	~Bad_Creature();
};

#endif