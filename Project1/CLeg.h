#pragma once
#include <vector>
#include "CShaderLoader.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "global.h"

using namespace std;
class CLeg
{
private:
	float angle;
	long startTick;
	long currentTick;
	bool direction;

public:
	CLeg();
	void playerDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, long start, long current, float positionX, float positionY);
	void thiefDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, long start, long current, float positionY);
};

