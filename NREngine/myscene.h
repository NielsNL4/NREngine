#ifndef MYSCENE_H
#define MYSCENE_H

#include <common/scene.h>

#include "myentity.h"
#include "lamp.h"

class Myscene : public Scene
{
public:
	Myscene();
	virtual ~Myscene();

	virtual void update(float deltatime);

private:
	Myentity* myentity;
	Lamp* lamp;
};

#endif