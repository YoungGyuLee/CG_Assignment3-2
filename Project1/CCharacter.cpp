#include "CCharacter.h"
using namespace glm;
CCharacter::CCharacter()
{
    playerPositionX = -1.5f;
    playerPositionY = -0.5f;

    theifPositionX = 1.25f;
    theifPositionY = -0.5f;

}
void CCharacter::playerDraw(GLuint program, unsigned int VAO[], unsigned int VBO[])
{


    // world space positions of our cubes
    float vertices[] = {
-0.1f, -0.1f, -0.1f,  0.0f, 0.0f, 1.0f,
 0.1f, -0.1f, -0.1f,  1.0f, 0.0f, 1.0f,
 0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
 0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
-0.1f,  0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.1f, -0.1f, -0.1f,  0.0f, 0.0f, 1.0f,

-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
 0.1f, -0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 1.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 1.0f, 1.0f,
-0.1f,  0.1f,  0.1f,  0.0f, 1.0f, 1.0f,
-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,

-0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
-0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
-0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,

 0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
 0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
 0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
 0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
 0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,

-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
 0.1f, -0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
 0.1f, -0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
 0.1f, -0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,

-0.1f,  0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
 0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
-0.1f,  0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
-0.1f,  0.1f, -0.1f,  0.0f, 1.0f, 1.0f
    };


    //glm::vec3 cubePositions[] = {
    //    glm::vec3(0.0f,  0.0f,  0.0f),
    //    glm::vec3(-1.3f,  1.0f, -1.5f)
    //};

    glUseProgram(program); //draw 3 vertices as triangles 

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //use the created program 

    cout << "size " << sizeof(vertices) << endl;


    //unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    ////////////본격적인 조작은 이 아래에서 부터//////////////////////


    ///이렇게가
    mat4 view = mat4(1.0f);
    //view = translate(view, vec3(0.0f, 0.0f, -0.5f));
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
    ///한 세트.

    mat4 projection = mat4(1.0f);
    //projection = perspective(radians(45.0f), 1.5f, 0.1f, 100.0f);
    projection = ortho(-3.0f, 3.0f, -2.0f, 2.0f, -2.0f, 2.0f);

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

    glBindVertexArray(VAO[0]);


    mat4 model = mat4(1.0f);
    model = translate(model, vec3(playerPositionX, playerPositionY, 0.0));
    model = scale(model, vec3(1.8, 4.0, 1.8));
    //model = rotate(model, radians(45.0f), vec3(1.0f, 0.3f, 0.5f));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //1은 머리
    //cout << "plaer Postion " << playerPositionX << endl;

    face.drawPlayer(program, playerPositionX, playerPositionY, VAO[1], VBO[1]);

    leftArm.playerDraw(program, VAO[2], VBO[2], VAO[3], VBO[3], LEFT, playerPositionX, playerPositionY);
    rightArm.playerDraw(program, VAO[4], VBO[4], VAO[5], VBO[5], RIGHT, playerPositionX, playerPositionY);

    leftThigh.playerDraw(program, VAO[6], VBO[6], VAO[7], VBO[7], LEFT, playerPositionX, playerPositionY);
    rightThigh.playerDraw(program, VAO[8], VBO[8], VAO[9], VBO[9], RIGHT, playerPositionX, playerPositionY);

    //1~9는 플레이어, 10~19는 도둑
    //glutSwapBuffers();
}

void CCharacter::thiefDraw(GLuint program, unsigned int VAO[], unsigned int VBO[])
{
    float vertices[] = {
-0.1f, -0.1f, -0.1f,  0.0f, 0.0f, 1.0f,
 0.1f, -0.1f, -0.1f,  1.0f, 0.0f, 1.0f,
 0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
 0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
-0.1f,  0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.1f, -0.1f, -0.1f,  0.0f, 0.0f, 1.0f,

-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
 0.1f, -0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 1.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 1.0f, 1.0f,
-0.1f,  0.1f,  0.1f,  0.0f, 1.0f, 1.0f,
-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,

-0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
-0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
-0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,

 0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
 0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
 0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
 0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
 0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,

-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
 0.1f, -0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
 0.1f, -0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
 0.1f, -0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
-0.1f, -0.1f, -0.1f,  0.0f, 1.0f, 1.0f,

-0.1f,  0.1f, -0.1f,  0.0f, 1.0f, 1.0f,
 0.1f,  0.1f, -0.1f,  1.0f, 1.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
 0.1f,  0.1f,  0.1f,  1.0f, 0.0f, 1.0f,
-0.1f,  0.1f,  0.1f,  0.0f, 0.0f, 1.0f,
-0.1f,  0.1f, -0.1f,  0.0f, 1.0f, 1.0f
    };


    //glm::vec3 cubePositions[] = {
    //    glm::vec3(0.0f,  0.0f,  0.0f),
    //    glm::vec3(-1.3f,  1.0f, -1.5f)
    //};

    glUseProgram(program); //draw 3 vertices as triangles 

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //use the created program 



    //unsigned int VBO, VAO;
    glGenVertexArrays(11, &VAO[10]);
    glGenBuffers(11, &VBO[10]);

    glBindVertexArray(VAO[10]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    ////////////본격적인 조작은 이 아래에서 부터//////////////////////


    ///이렇게가
    mat4 view = mat4(1.0f);
    //view = translate(view, vec3(0.0f, 0.0f, -0.5f));
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
    ///한 세트.

    mat4 projection = mat4(1.0f);
    //projection = perspective(radians(45.0f), 1.5f, 0.1f, 100.0f);
    projection = ortho(-3.0f, 3.0f, -2.0f, 2.0f, -2.0f, 2.0f);

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

    glBindVertexArray(VAO[10]);


    mat4 model = mat4(1.0f);
    model = translate(model, vec3(1.25, theifPositionY + 0.0, 0.0));
    model = scale(model, vec3(1.8, 4.0, 1.8));
    //model = rotate(model, radians(45.0f), vec3(1.0f, 0.3f, 0.5f));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //11는 머리

    face.drawThief(program, theifPositionY, VAO[11], VBO[11]);

    leftArm.thiefDraw(program, VAO[12], VBO[12], VAO[13], VBO[13], LEFT, theifPositionY);
    rightArm.thiefDraw(program, VAO[14], VBO[14], VAO[15], VBO[15], RIGHT, theifPositionY);

    leftThigh.thiefDraw(program, VAO[16], VBO[16], VAO[17], VBO[17], LEFT, theifPositionY);
    rightThigh.thiefDraw(program, VAO[18], VBO[18], VAO[19], VBO[19], RIGHT, theifPositionY);

    //10~19는 도둑
    //glutSwapBuffers();







}

void CCharacter::setPlayerPose(int pose)
{
    this->playerPose = pose;
    leftArm.setMotion(pose);
    rightArm.setMotion(pose);
}

void CCharacter::legMovement()
{

}







float* CCharacter::getVertices()
{
    float vertices[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
    };
    return vertices;
}

void CCharacter::setPlayerPositionX(float positionX)
{
    this->playerPositionX = positionX;
}

void CCharacter::setPlayerPositionY(float positionY)
{
    this->playerPositionY = positionY;

}

float CCharacter::getPlayerPositionX()
{
    return this->playerPositionX;
}

float CCharacter::getPlayerPositionY()
{
    return this->playerPositionY;
}

int CCharacter::getPlayerPose()
{
    return this->playerPose;
}

void CCharacter::setThiefPositionX(float positionX)
{
    this->theifPositionX = positionX;
}

void CCharacter::setThiefPositionY(float positionY)
{
    this->theifPositionY = positionY;
}

float CCharacter::getThiefPositionX()
{
    return this->theifPositionX;
}

float CCharacter::getThiefPositionY()
{
    return this->theifPositionY;
}

void CCharacter::setThiefPose(int pose)
{
    this->theifPose = pose;
    leftArm.setTMotion(pose);
    rightArm.setTMotion(pose);
}

int CCharacter::getThiefPose()
{
    return this->theifPose;
}

