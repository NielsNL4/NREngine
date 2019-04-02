#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include "model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
using namespace std;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(float deltatime) = 0;

	void AddChild(Entity* child);
	void RemoveChild(Entity* child);

	void AddModel(GLchar *path);
	void AddLight();

	vec3 position;
	vec3 rotation;
	vec3 scale;

	Entity* parent;
	vector<Entity*> children;

	Model* _model = NULL;
	Model* lightModel = new Model("../NREngine/assets/lamps/Lamp.obj");
	bool light = false;

private:

	int id;
	static int nextid;
};

#endif