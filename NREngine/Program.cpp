#include <Glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
using namespace std;

#include "common/renderer.h"
#include "common/shader.h"
#include "common/camera.h"

Camera camera(vec3(0.0f, 3.0f, 1.0f));
vec3 lightPos(1.2f, 1.0f, 2.0f);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	Renderer renderer;

	Shader modelShader("../common/shaders/modelVertex.vs", "../common/shaders/modelFrag.fs");
	Shader lightingShader("../common/shaders/modelVertex.vs", "../common/shaders/modelFrag.fs");
	Shader lampShader("../common/shaders/lampVertex.vs", "../common/shaders/lampFrag.fs");
	Shader skyboxShader("../common/shaders/skyboxVertex.vs", "../common/shaders/skyboxFrag.fs");

	Model myModel("assets/spaceship/spaceship.obj");
	Model myLamp("assets/lamps/Lamp.obj");

	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// render loop
	while (!glfwWindowShouldClose(renderer.window)) {
		renderer.processInput(renderer.window);
		camera.processInput(renderer.window);

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		modelShader.use();
		modelShader.setVec3("light.position", lightPos);
		modelShader.setVec3("viewPos", camera.Position);

		modelShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
		modelShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		modelShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		// material properties
		modelShader.setFloat("material.shininess", 8.0f);

		mat4 view = camera.GetViewMatrix();
		mat4 projection = perspective(camera.Zoom, (float)1280 / (float)720, 0.1f, 100.0f);
		modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);

		renderer.renderScene(lightingShader, lampShader, view, projection, lightPos, myLamp, myModel);
		renderer.renderSkybox(skyboxShader, view, projection, camera);

		glfwSwapBuffers(renderer.window);
		glfwPollEvents();
	}

	renderer.cleanUp();
	glfwTerminate();
	return 0;
}
