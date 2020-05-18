#pragma once
#include <vector>
#include "CShaderLoader.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "global.h"

using namespace std;
class CForeArm
{
private:
	//player
	float leftAngle;
	float rightAngle;

	float leftPreviousAngle;
	float rightPreviousAngle;

	float leftRotateAngle;
	float rightRotateAngle;


	//Thief
	float leftAngleT;
	float rightAngleT;

	float leftPreviousAngleT;
	float rightPreviousAngleT;

	float leftRotateAngleT;
	float rightRotateAngleT;


public:
	void playerDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, float angle, float positionX, float positionY);
	void thiefDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, float angle, float positionY);
	void setMotion(int pose);
	void setTMotion(int pose);

};

