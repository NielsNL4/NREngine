#include "myentity.h" 
 
Myentity::Myentity() : Entity() {
	this->AddModel("../NREngine/assets/spaceship/spaceship.obj");
}
 
Myentity::~Myentity(){

}

void Myentity::update(float deltatime) {
	//this->AddText("Hello");
}