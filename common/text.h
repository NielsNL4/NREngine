#ifndef TEXT_H
#define TEXT_H

#include <glad/glad.h>
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <map>
#include <string>

#include "shader.h"
#include "entity.h"
using namespace std;
using namespace glm;

class Text
{
public:
	Text();
	virtual ~Text();

	//virtual void update(float deltatime);

	void RenderText(Shader* shader, string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);

private:
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		ivec2 Size;    // Size of glyph
		ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

	map<GLchar, Character> Characters;
	GLuint VAO, VBO;
};

#endif