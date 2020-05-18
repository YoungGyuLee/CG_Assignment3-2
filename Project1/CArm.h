#pragma once
#include <vector>
#include "CShaderLoader.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "global.h"
#include "CForeArm.h"
using namespace std;
class CArm
{
private:
	CForeArm leftForeArm;
	CForeArm rightForeArm;


	//Play
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

	float length;
public:
	void playerDraw(GLuint program, unsigned int VAO1, unsigned int VBO1, unsigned int VAO2, unsigned int VBO2, int type, float positionX, float positionY);
	void thiefDraw(GLuint program, unsigned int VAO1, unsigned int VBO1, unsigned int VAO2, unsigned int VBO2, int type, float positionY);
	void setMotion(int pose);
	void setTMotion(int pose);



};

