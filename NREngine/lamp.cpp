#include "lamp.h" 
 
Lamp::Lamp() : Entity() {
	this->AddModel("../NREngine/assets/plane.obj");
}
 
Lamp::~Lamp(){

}

void Lamp::update(float deltatime) {
	
}