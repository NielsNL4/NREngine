#include "core.h" 
 
Core::Core(){
	_deltaTime = 0;
}
 
Core::~Core(){

}

void Core::run(Scene* scene) {
	renderer.processInput(renderer.window);
	scene->camera->processInput(renderer.window, (float)_deltaTime);
	calculateDeltaTime();

	scene->UpdateScene((float)_deltaTime);

	renderer.renderScene(scene);
	if (glfwWindowShouldClose(renderer.window)) { scene->stop(); }
}

void Core::frameRate() {
	static int frames = 0;
	static double time = glfwGetTime();

	frames++;
	time += _deltaTime;
	if (time - _deltaTime >= 0.04) {
		float fpss = frames / time;
		renderer.fps = "FPS: " + to_string(llround(fpss));
		frames = 0;
		time = 0;
	}
}

double Core::calculateDeltaTime() {
	static double lastTime = glfwGetTime();
	double startTime = glfwGetTime();
	_deltaTime = startTime - lastTime;
	lastTime = startTime;

	return _deltaTime;
}

void Core::cleanUp() {
	renderer.cleanUp();
}