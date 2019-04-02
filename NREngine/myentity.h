#ifndef MYENTITY_H
#define MYENTITY_H

#include <common/entity.h>

class Myentity : public Entity
{
public:
	Myentity();
	virtual ~Myentity();

	virtual void update(float deltatime);

private:

};

#endif