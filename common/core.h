#ifndef CORE_H
#define CORE_H

#include <common/renderer.h>
#include <common/scene.h>

class Core
{
public:
	Core();
	virtual ~Core();

	void run(Scene* scene);

	void cleanUp();

	float deltaTime() { return (float)_deltaTime; };

	void frameRate(float numsec);

private:
	Renderer renderer;

	double calculateDeltaTime();
	double _deltaTime;
};

#endif