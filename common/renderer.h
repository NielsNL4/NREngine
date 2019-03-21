#ifndef RENDERER_H
#define RENDERER_H

#include <Glad/glad.h>
#include <glfw3.h>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "skybox.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
using namespace std;

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();
	GLFWwindow* window;

	void processInput(GLFWwindow* window);
	void makeTriangle();
	void cleanUp();
	void draw();
	void DrawSkybox();
	void renderScene(Shader modelShader, Shader lampShader, mat4 view, mat4 projection, vec3 lightPos, Model slampModel, Model objectModel);
	void renderSkybox(Shader skyboxShader, mat4 view, mat4 projection, Camera camera);

	Skybox skybox;

	vector<string> faces{
		"assets/skybox/right.png",
		"assets/skybox/left.png",
		"assets/skybox/top.png",
		"assets/skybox/bottom.png",
		"assets/skybox/front.png",
		"assets/skybox/back.png"
	};
	
	unsigned int vertexShader;
	unsigned int fragmentShader;

	int SWIDTH = 1280;
	int SHEIGHT = 800;

	float lastX;
	float lastY;
	bool firstMouse;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	unsigned int VBO, cubeVAO, lightVAO, EBO, skyboxVAO, skyboxVBO;

private:


};

#endif
