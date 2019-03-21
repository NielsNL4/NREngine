#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

#include <external/assimp/include/Importer.hpp>
#include <external/assimp/include/Scene.h>
#include <external/assimp/include/postprocess.h>

#include "external/stb_image.h"
#include "shader.h"

class Texture {
public: 
	Texture();
	virtual ~Texture();
	GLint TextureFromFile(const char *path, std::string directory);

	GLuint id;
	std::string type;
	aiString path;

private:

};

#endif