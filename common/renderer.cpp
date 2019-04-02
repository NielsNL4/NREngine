#include "renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Renderer::Renderer() {

	objectShader = NULL;
	window = NULL;

	this->init();
}

Renderer::~Renderer() {

}

int Renderer::init() {
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SWIDTH, SHEIGHT, "NREngine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	//glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	objectShader = new Shader("../common/shaders/modelVertex.vs", "../common/shaders/modelFrag.fs");
	skyboxShader = new Shader("../common/shaders/skyboxVertex.vs", "../common/shaders/skyboxFrag.fs");
	lightShader = new Shader("../common/shaders/lampVertex.vs", "../common/shaders/lampFrag.fs");

	cubeMap = skybox.loadSkybox(faces);

	makeTriangle();
	DrawSkybox();

	skyboxShader->use();
	skyboxShader->setInt("skybox", 0);

	printf("Renderer::init() done\n");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return 0;
}

void Renderer::processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Renderer::makeTriangle() {
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//light attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Renderer::draw() {
	glBindVertexArray(cubeVAO);
}

void Renderer::DrawSkybox() {
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox.skyboxVertices), &skybox.skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Renderer::renderScene(Scene* scene){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_viewMatrix = scene->camera->GetViewMatrix();

	_projectionMatrix = perspective(45.0f, (float)SWIDTH / (float)SHEIGHT, 0.1f, 10000.0f);

	mat4 modelMatrix = mat4(1.0f);

	this->renderEntity(modelMatrix, scene, scene->camera);

	renderSkybox();

	glfwSwapBuffers(window);
}

void Renderer::renderEntity(mat4 modelMatrix, Entity* entity, Camera* camera) {
	vec3 position = vec3(entity->position.x, entity->position.y, entity->position.z);
	vec3 rotation = vec3(entity->rotation.x, entity->rotation.y, entity->rotation.z);
	vec3 scale = vec3(entity->scale.x, entity->scale.y, entity->scale.y);

	mat4 transformMatrix = translate(mat4(1.0f), position);
	mat4 rotationMatrix = eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
	mat4 scaleMatrix = glm::scale(mat4(1.0f), scale);

	mat4 mm = transformMatrix * rotationMatrix * scaleMatrix;

	modelMatrix *= mm;

	Model* model = entity->_model;
	if (model != NULL) {
		this->renderObject(modelMatrix, model);
	}

	Model* lightModel = entity->lightModel;
	if (entity->light) {
		this->renderLight(modelMatrix, lightModel);
	}

	vector<Entity*> children = entity->children;
	vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->renderEntity(modelMatrix, *child, camera);
	}
	
}

void Renderer::renderObject(const mat4 modelMatrix, Model* model) {
	Shader* shader = objectShader;

	shader->use();

	shader->setVec3("light.position", vec3(0.0f, 0.0f, -3.0f));
	shader->setVec3("viewPos", vec3(0.0f, 0.0f, 0.0f));

	shader->setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
	shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	shader->setFloat("material.shininess", 8.0f);

	shader->setMat4("projection", _projectionMatrix);
	shader->setMat4("view", _viewMatrix);
	shader->setMat4("model", modelMatrix);
	
	model->Draw(*shader);
}

void Renderer::renderLight(const mat4 modelMatrix, Model* model) {
	Shader* shader = lightShader;

	shader->use();

	shader->setMat4("projection", _projectionMatrix);
	shader->setMat4("view", _viewMatrix);
	shader->setMat4("model", modelMatrix);

	model->Draw(*shader);
}

void Renderer::renderSkybox(){
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	skyboxShader->use();
	
	skyboxShader->setMat4("view", _viewMatrix);
	skyboxShader->setMat4("projection", _projectionMatrix);

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void Renderer::cleanUp() {
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &skyboxVBO);
	glDeleteBuffers(1, &EBO);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
