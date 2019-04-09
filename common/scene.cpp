#include "scene.h" 
 
Scene::Scene() : Entity() {
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f));

	isRunning = true;
}
 
Scene::~Scene(){
	delete camera;
}

void Scene::UpdateScene(float deltatime) {
	this->UpdateEntity(this, deltatime);
}

void Scene::UpdateEntity(Entity* entity, float deltatime) {
	entity->update(deltatime);

	vector<Entity*> children = entity->children;
	vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->UpdateEntity(*child, deltatime);
	}
}