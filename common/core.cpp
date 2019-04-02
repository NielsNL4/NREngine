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

void Core::frameRate(float numsec) {
	static int frames = 0;
	static double time = 0;

	frames++;
	time += _deltaTime;
	if (time >= numsec) {
		printf("%f ms/frame (%f FPS)\n", (numsec * 1000) / double(frames), frames / numsec);
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