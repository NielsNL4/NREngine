#include "myscene.h" 
 
Myscene::Myscene() : Scene(){
	myentity = new Myentity();
	myentity->position = vec3(0.0f, 0.0f, -5.0f);
	myentity->scale = vec3(0.3, 0.3, 0.3);

	myentity->rotation.x += 90;

	lamp = new Lamp();
	lamp->position = vec3(0.0f, -1.0f, -5.0f);

	this->AddChild(myentity);

	this->AddChild(lamp);
}
 
Myscene::~Myscene(){
	this->RemoveChild(myentity);
	this->RemoveChild(lamp);

	delete lamp;
	delete myentity;
}

void Myscene::update(float deltatime) {

}