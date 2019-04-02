#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "entity.h"

class Scene : public Entity
{
public:
	Scene();
	virtual ~Scene();

	void UpdateScene(float deltatime);
	void UpdateEntity(Entity* entity, float deltatime);

	Camera* camera;

	bool isRunning;

	void start() { isRunning = true; };
	void stop() { isRunning = false; };

private:

};

#endif