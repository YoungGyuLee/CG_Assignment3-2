#include "CThigh.h"
using namespace glm;
CThigh::CThigh()
{
    angle = 0;
    startTick = GetTickCount64();

    //true면 오른쪽이 앞으로 향함.
    direction = true;
}
void CThigh::playerDraw(GLuint program, unsigned int VAO1, unsigned int VBO1, unsigned int VAO2,
    unsigned int VBO2, int type, float positionX, float positionY)
{
    float pX = positionX;
    float pY = positionY;
    float vertices[] = {
-0.2f, -0.2f, -0.2f,  0.0f, 0.0f, 1.0f,
 0.0f, -0.2f, -0.2f,  1.0f, 0.0f, 1.0f,
 0.0f,  0.0f, -0.2f,  1.0f, 1.0f, 1.0f,
 0.0f,  0.0f, -0.2f,  1.0f, 1.0f, 1.0f,
-0.2f,  0.0f, -0.2f,  0.0f, 1.0f, 1.0f,
-0.2f, -0.0f, -0.2f,  0.0f, 0.0f, 1.0f,

-0.2f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,
 0.0f, -0.2f,  0.0f,  1.0f, 0.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
-0.2f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,
-0.2f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,

-0.2f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
-0.2f,  0.0f, -0.1f,  1.0f, 1.0f, 1.0f,
-0.2f, -0.2f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.2f, -0.2f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.2f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,
-0.2f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
 0.0f,  0.0f, -0.2f,  1.0f, 1.0f, 1.0f,
 0.0f, -0.2f, -0.2f,  0.0f, 1.0f, 1.0f,
 0.0f, -0.2f, -0.2f,  0.0f, 1.0f, 1.0f,
 0.0f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

-0.2f, -0.2f, -0.2f,  0.0f, 1.0f, 1.0f,
 0.0f, -0.2f, -0.2f,  1.0f, 1.0f, 1.0f,
 0.0f, -0.2f,  0.0f,  1.0f, 0.0f, 1.0f,
 0.0f, -0.2f,  0.0f,  1.0f, 0.0f, 1.0f,
-0.2f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,
-0.2f, -0.2f, -0.2f,  0.0f, 1.0f, 1.0f,

-0.2f,  0.0f, -0.2f,  0.0f, 1.0f, 1.0f,
 0.0f,  0.0f, -0.2f,  1.0f, 1.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
-0.2f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,
-0.2f,  0.0f, -0.2f,  0.0f, 1.0f, 1.0f
    };

    glUseProgram(program); //draw 3 vertices as triangles 
    if (angle > 45) {
        direction = true;
    }
    if (angle < -45) {
        direction = false;
    }

    if (direction) {
        currentTick = GetTickCount64();
        angle = 45 - ((currentTick - startTick) / (VELORATE - ADJUST * 1));
    }
    else {
        startTick = GetTickCount64();
        angle = -45 - ((currentTick - startTick) / (VELORATE - ADJUST * 1));
    }




    if (type == LEFT) {
        glGenVertexArrays(7, &VAO1);
        glGenBuffers(7, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


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

        glBindVertexArray(VAO1);

        //float angle = 180.0f;
        mat4 model = mat4(1.0f);
        model = translate(model, vec3(pX, pY - 0.3, -1.0));
        model = rotate(model, radians(-angle), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        leftLeg.playerDraw(program, VAO2, VBO2, LEFT, startTick, currentTick, pX, pY);

    }
    else {
        glGenVertexArrays(9, &VAO1);
        glGenBuffers(9, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
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
        int viewLoc = glGetUniformLocation(program, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
        ///한 세트.

        mat4 projection = mat4(1.0f);
        projection = ortho(-3.0f, 3.0f, -2.0f, 2.0f, -2.0f, 2.0f);
        int projectionLoc = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

        //float angle = 45.0f;


        mat4 model = mat4(1.0f);
        model = translate(model, vec3(pX, pY - 0.3, 1.0));
        model = rotate(model, radians(angle), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO1);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        rightLeg.playerDraw(program, VAO2, VBO2, RIGHT, startTick, currentTick, pX, pY);

        //leftForeArm
    }



}

void CThigh::thiefDraw(GLuint program, unsigned int VAO1, unsigned int VBO1, unsigned int VAO2,
    unsigned int VBO2, int type, float positionY)
{
    float pY = positionY;

    float vertices[] = {
-0.2f, -0.2f, -0.2f,  0.0f, 0.0f, 1.0f,
 0.0f, -0.2f, -0.2f,  1.0f, 0.0f, 1.0f,
 0.0f,  0.0f, -0.2f,  1.0f, 1.0f, 1.0f,
 0.0f,  0.0f, -0.2f,  1.0f, 1.0f, 1.0f,
-0.2f,  0.0f, -0.2f,  0.0f, 1.0f, 1.0f,
-0.2f, -0.0f, -0.2f,  0.0f, 0.0f, 1.0f,

-0.2f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,
 0.0f, -0.2f,  0.0f,  1.0f, 0.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
-0.2f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,
-0.2f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,

-0.2f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
-0.2f,  0.0f, -0.1f,  1.0f, 1.0f, 1.0f,
-0.2f, -0.2f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.2f, -0.2f, -0.1f,  0.0f, 1.0f, 1.0f,
-0.2f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,
-0.2f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
 0.0f,  0.0f, -0.2f,  1.0f, 1.0f, 1.0f,
 0.0f, -0.2f, -0.2f,  0.0f, 1.0f, 1.0f,
 0.0f, -0.2f, -0.2f,  0.0f, 1.0f, 1.0f,
 0.0f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

-0.2f, -0.2f, -0.2f,  0.0f, 1.0f, 1.0f,
 0.0f, -0.2f, -0.2f,  1.0f, 1.0f, 1.0f,
 0.0f, -0.2f,  0.0f,  1.0f, 0.0f, 1.0f,
 0.0f, -0.2f,  0.0f,  1.0f, 0.0f, 1.0f,
-0.2f, -0.2f,  0.0f,  0.0f, 0.0f, 1.0f,
-0.2f, -0.2f, -0.2f,  0.0f, 1.0f, 1.0f,

-0.2f,  0.0f, -0.2f,  0.0f, 1.0f, 1.0f,
 0.0f,  0.0f, -0.2f,  1.0f, 1.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
-0.2f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,
-0.2f,  0.0f, -0.2f,  0.0f, 1.0f, 1.0f
    };

    glUseProgram(program); //draw 3 vertices as triangles 
    if (angle > 45) {
        direction = true;
    }
    if (angle < -45) {
        direction = false;
    }

    if (direction) {
        currentTick = GetTickCount64();
        angle = 45 - ((currentTick - startTick) / (VELORATE - ADJUST * 1));
    }
    else {
        startTick = GetTickCount64();
        angle = -45 - ((currentTick - startTick) / (VELORATE - ADJUST * 1));
    }




    if (type == LEFT) {
        glGenVertexArrays(17, &VAO1);
        glGenBuffers(17, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


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

        glBindVertexArray(VAO1);

        //float angle = 180.0f;
        mat4 model = mat4(1.0f);
        model = translate(model, vec3(1.25, pY - 0.3, -1.0));
        model = rotate(model, radians(-angle), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        leftLeg.thiefDraw(program, VAO2, VBO2, LEFT, startTick, currentTick, pY);

    }
    else {
        glGenVertexArrays(19, &VAO1);
        glGenBuffers(19, &VBO1);

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
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
        int viewLoc = glGetUniformLocation(program, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
        ///한 세트.

        mat4 projection = mat4(1.0f);
        projection = ortho(-3.0f, 3.0f, -2.0f, 2.0f, -2.0f, 2.0f);
        int projectionLoc = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

        //float angle = 45.0f;


        mat4 model = mat4(1.0f);
        model = translate(model, vec3(1.25, pY - 0.3, 1.0));
        model = rotate(model, radians(angle), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO1);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        rightLeg.thiefDraw(program, VAO2, VBO2, RIGHT, startTick, currentTick, pY);

        //leftForeArm
    }
}
