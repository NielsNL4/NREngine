#ifndef CORE_H
#define CORE_H

#include <common/renderer.h>
#include <common/scene.h>

#include <string>

class Core
{
public:
	Core();
	virtual ~Core();

	void run(Scene* scene);

	void cleanUp();

	float deltaTime() { return (float)_deltaTime; };

	void frameRate();

private:
	Renderer renderer;

	double calculateDeltaTime();
	double _deltaTime;
};

#endif