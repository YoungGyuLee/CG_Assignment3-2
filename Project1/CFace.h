#pragma once
#include <vector>
#include "CShaderLoader.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
using namespace std;
class CFace
{
private:
	int lats;
	int longs;
	unsigned int m_vboIndex;
	float radius;
	//float angle;
	vector<float> vertices;


	vector<float> verticesThief;



	vector<GLfloat> color;
	vector<GLuint> indices;

public:
	CFace();
	void drawPlayer(GLuint program, float positionX, float positionY, unsigned VAO, unsigned VBO);
	void drawThief(GLuint program, float positionY, unsigned VAO, unsigned VBO);
};

