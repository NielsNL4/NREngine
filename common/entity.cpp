#include "entity.h" 

int Entity::nextid = 0;

Entity::Entity(){
	parent = nullptr;

	id = nextid;
	nextid++;

	position = vec3(0.0f, 0.0f, 0.0f);
	rotation = vec3(0.0f, 0.0f, 0.0f);
	scale = vec3(1.0f, 1.0f, 1.0f);

	bool light = false;
}
 
Entity::~Entity(){

}

void Entity::AddChild(Entity* child) {
	if (child->parent != NULL) {
		child->parent->RemoveChild(child);
	}
	child->parent = this;
	this->children.push_back(child);
}

void Entity::RemoveChild(Entity* child) {
	std::vector< Entity* >::iterator it = children.begin();
	while (it != children.end()) {
		if ((*it)->id == child->id) {
			child->parent = NULL;
			it = children.erase(it);
		}
		else {
			++it;
		}
	}
}

void Entity::AddModel(GLchar *path) {
	_model = new Model(path);
}

void Entity::AddLight() {
	bool light = true;
}