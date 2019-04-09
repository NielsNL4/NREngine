#ifndef LAMP_H
#define LAMP_H

#include <common/entity.h>

class Lamp : public Entity
{
public:
	Lamp();
	virtual ~Lamp();

	virtual void update(float deltatime);

private:

};

#endif