#ifndef RENDERER_H
#define RENDERER_H

#include <Glad/glad.h>
#include <glfw3.h>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "skybox.h"
#include "scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;
using namespace std;

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();
	GLFWwindow* window;

	Shader* objectShader;
	Shader* skyboxShader;
	Shader* lightShader;

	void processInput(GLFWwindow* window);
	void makeTriangle();
	void cleanUp();
	void draw();
	void DrawSkybox();
	void renderScene(Scene* scene);
	void renderSkybox();
	void renderEntity(mat4 modelMatrix, Entity* entity, Camera* camera);
	void renderObject(const mat4 modelMatrix, Model* model);
	void renderLight(const mat4 modelMatrix, Model* model);

	int init();

	Skybox skybox;
	GLuint cubeMap;
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

	mat4 _projectionMatrix;
	mat4 _viewMatrix;

};

#endif
