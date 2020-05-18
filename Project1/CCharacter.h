#pragma once
#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fstream> 
#include <vector>
#include "CShaderLoader.h"
#include "CArm.h"
#include "CThigh.h"
#include "CFace.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "global.h"
#include <stack>
using namespace std;
class CCharacter
{
private:
	CArm leftArm;
	CArm rightArm;

	CThigh leftThigh;
	CThigh rightThigh;

	CFace face;

	int theifPose;
	int playerPose;

	float theifPositionX;
	float theifPositionY;

	float playerPositionX;
	float playerPositionY;

public:
	CCharacter();
	void playerDraw(GLuint program, unsigned int VAO[], unsigned int VBO[]);
	void thiefDraw(GLuint program, unsigned int VAO[], unsigned int VBO[]);
	void setPlayerPose(int pose);
	void legMovement();
	float* getVertices();


	void setPlayerPositionX(float positionX);
	void setPlayerPositionY(float positionY);
	float getPlayerPositionX();
	float getPlayerPositionY();
	int getPlayerPose();


	void setThiefPositionX(float positionX);
	void setThiefPositionY(float positionY);
	float getThiefPositionX();
	float getThiefPositionY();
	void setThiefPose(int pose);
	int getThiefPose();

};

