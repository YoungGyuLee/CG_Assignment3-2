#pragma once
#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fstream> 
#include <vector>
#include "CShaderLoader.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "global.h"

class CWall
{
private:
	float positionX;
	float positionY;
	int color;
	float width;
	float height;
	int front;

	int verticesSize;

	float* vertices;
public:
	CWall();
	~CWall();

	void setWallPositionX(float positionX);
	float getWallPositionX();

	void setWallPositionY(float positionY);
	float getWallPositionY();

	void setWallColor(int color);
	int getWallColor();

	float getWallWidth();
	float getWallHeight();

	void setFront(int front);
	int getFront();
	void draw(GLuint program, unsigned int VAO, unsigned int VBO);

	void setVertices(int size);
	float* getVertices();
	void setWall(int pose);
};

