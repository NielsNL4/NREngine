#include "myentity.h" 
 
Myentity::Myentity() : Entity() {
	this->AddModel("assets/Spaceship/spaceship.obj");
}
 
Myentity::~Myentity(){

}

void Myentity::update(float deltatime) {
	
}