#ifndef GOODCREATURE_H
#define GOODCREATURE_H

#include <string>

#include "creature.h"

class Good_Creature : public Creature{
	const unsigned int threshold;
public:
	Good_Creature(string, unsigned int, unsigned int, Society *);
	Good_Creature(const Good_Creature&);
	bool is_a_good() const;
	bool is_robust();
	void bless();
	void beat();
	Creature * Clone();
	~Good_Creature();
};

#endif
