#pragma once

#include "Shader.h"

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>

using namespace std;

class Object
{

public:

	Object() {};
	~Object() {};

	void initialize();
	void update();
	void draw();

	inline void setPosition(glm::vec3 position) { this->position = position; }
	inline void setDimensions(glm::vec3 scale) { this->scale = scale; }
	inline void setAngle(float angle) { this->angle = angle; }
	inline void setTexture(GLuint texID) { this->texID = texID; }
	inline void setShader(Shader* shader) { this->shader = shader; }
	inline glm::vec3 getPosition() { return position; }

protected:

	void setRotation(float angle, glm::vec3 axis, bool reset = false);
	void setTranslation(glm::vec3 displacements, bool reset = false);
	void setScale(glm::vec3 scaleFactors, bool reset = false);
	
	GLuint VAO;
	glm::mat4 transform;
	GLuint texID;

	Shader* shader;

	glm::vec3 position, scale;
	float angle;

	bool first;
};

