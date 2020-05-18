#include "CForeArm.h"
using namespace glm;

void CForeArm::playerDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, float angle, float positionX, float positionY)
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


    if (leftRotateAngle != leftAngle)
        leftRotateAngle = leftPreviousAngle += (leftAngle - leftPreviousAngle) * 0.1;

    if (rightRotateAngle != rightAngle)
        rightRotateAngle = rightPreviousAngle += (rightAngle - rightPreviousAngle) * 0.1;






    if (type == LEFT) {
        glGenVertexArrays(4, &VAO);
        glGenBuffers(4, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
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


        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(pX, pY + 0.3, -1.0));
        model2 = rotate(model2, radians(leftRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        model2 = scale(model2, vec3(0.5, 1.5, 0.5));


        mat4 model = model2;
        //model = mat4(1.0f);

        model = translate(model, vec3(0.0, -0.2, -1.0));
        model = rotate(model, radians(0.0f), vec3(0.0f, 0.0f, 1.0f));

        //mat4 model = mat4(1.0f);
        //model = translate(model, vec3(-1.5, 0.3, -1.0));
        //model = rotate(model, radians(180.0f), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO);



        glDrawArrays(GL_TRIANGLES, 0, 36);

        //leftForeArm.playerDraw(program, VAO2, VBO2, LEFT);

    }
    else {
        glGenVertexArrays(6, &VAO);
        glGenBuffers(6, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
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

        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(pX, pY + 0.3, 1.0));
        model2 = rotate(model2, radians(rightRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        model2 = scale(model2, vec3(0.5, 1.5, 0.5));


        mat4 model = model2;
        //model = mat4(1.0f);

        model = translate(model, vec3(0.0, -0.2, 1.0));
        model = rotate(model, radians(0.0f), vec3(0.0f, 0.0f, 1.0f));
        //model = rotate(model, radians(0.0f), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));

        //model = rotate(model, radians(90.0f), vec3(0.0f, 0.0f, 1.0f));

        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CForeArm::thiefDraw(GLuint program, unsigned int VAO, unsigned int VBO, int type, float angle, float positionY)
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


    if (leftRotateAngleT != leftAngleT)
        leftRotateAngleT = leftPreviousAngleT += (leftAngleT - leftPreviousAngleT) * 0.1;

    if (rightRotateAngleT != rightAngleT)
        rightRotateAngleT = rightPreviousAngleT += (rightAngleT - rightPreviousAngleT) * 0.1;






    if (type == LEFT) {
        glGenVertexArrays(14, &VAO);
        glGenBuffers(14, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
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


        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(1.25, pY + 0.3, -1.0));
        model2 = rotate(model2, radians(leftRotateAngleT), vec3(0.0f, 0.0f, 1.0f));
        model2 = scale(model2, vec3(0.5, 1.5, 0.5));


        mat4 model = model2;
        //model = mat4(1.0f);

        model = translate(model, vec3(0.0, -0.2, -1.0));
        model = rotate(model, radians(0.0f), vec3(0.0f, 0.0f, 1.0f));

        //mat4 model = mat4(1.0f);
        //model = translate(model, vec3(-1.5, 0.3, -1.0));
        //model = rotate(model, radians(180.0f), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO);



        glDrawArrays(GL_TRIANGLES, 0, 36);

        //leftForeArm.playerDraw(program, VAO2, VBO2, LEFT);

    }
    else {
        glGenVertexArrays(16, &VAO);
        glGenBuffers(16, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
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

        mat4 model2 = mat4(1.0f);
        model2 = translate(model2, vec3(1.25, pY + 0.3, 1.0));
        model2 = rotate(model2, radians(rightRotateAngleT), vec3(0.0f, 0.0f, 1.0f));
        model2 = scale(model2, vec3(0.5, 1.5, 0.5));


        mat4 model = model2;
        //model = mat4(1.0f);

        model = translate(model, vec3(0.0, -0.2, 1.0));
        model = rotate(model, radians(0.0f), vec3(0.0f, 0.0f, 1.0f));
        //model = rotate(model, radians(0.0f), vec3(0.0f, 0.0f, 1.0f));
        //model = scale(model, vec3(0.5, 1.5, 0.5));

        //model = rotate(model, radians(90.0f), vec3(0.0f, 0.0f, 1.0f));

        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }




}

void CForeArm::setMotion(int pose)
{
    leftPreviousAngle = leftAngle;
    rightPreviousAngle = rightAngle;
    /*
    switch (pose) {
    case RED:
        //왼쪽 90, 오른쪽 90
        leftAngle = 90;
        rightAngle = 90;
        break;
    case BLUE:
        //왼쪽 180, 오른쪽 90
        leftAngle = 0;
        rightAngle = 0;
        break;
    case GREEN:
        //왼쪽 180, 오른쪽 180
        leftAngle = -45;
        rightAngle = 45;
        break;
    case YELLOW:
        //왼쪽 90, 오른쪽 -90
        leftAngle = 90;
        rightAngle = -90;
        break;
    default:
        //RED
        leftAngle = 0;
        rightAngle = 0;
        break;
    }
    */

    switch (pose) {
    case RED:
        //왼쪽 0, 오른쪽 0
        leftAngle = 0;
        rightAngle = 0;
        break;
    case BLUE:
        //왼쪽 180, 오른쪽 90
        leftAngle = 180;
        rightAngle = 90;
        break;
    case GREEN:
        //왼쪽 180, 오른쪽 180
        leftAngle = 180;
        rightAngle = 180;
        break;
    case YELLOW:
        //왼쪽 90, 오른쪽 -90
        leftAngle = 90;
        rightAngle = -90;
        break;
    default:
        //RED
        leftAngle = 0;
        rightAngle = 0;
        break;
    }
}

void CForeArm::setTMotion(int pose)
{
    leftPreviousAngleT = leftAngleT;
    rightPreviousAngleT = rightAngleT;
    /*
    switch (pose) {
    case RED:
        //왼쪽 90, 오른쪽 90
        leftAngle = 90;
        rightAngle = 90;
        break;
    case BLUE:
        //왼쪽 180, 오른쪽 90
        leftAngle = 0;
        rightAngle = 0;
        break;
    case GREEN:
        //왼쪽 180, 오른쪽 180
        leftAngle = -45;
        rightAngle = 45;
        break;
    case YELLOW:
        //왼쪽 90, 오른쪽 -90
        leftAngle = 90;
        rightAngle = -90;
        break;
    default:
        //RED
        leftAngle = 0;
        rightAngle = 0;
        break;
    }
    */

    switch (pose) {
    case RED:
        //왼쪽 0, 오른쪽 0
        leftAngleT = 0;
        rightAngleT = 0;
        break;
    case BLUE:
        //왼쪽 180, 오른쪽 90
        leftAngleT = 180;
        rightAngleT = 90;
        break;
    case GREEN:
        //왼쪽 180, 오른쪽 180
        leftAngleT = 180;
        rightAngleT = 180;
        break;
    case YELLOW:
        //왼쪽 90, 오른쪽 -90
        leftAngleT = 90;
        rightAngleT = -90;
        break;
    default:
        //RED
        leftAngleT = 0;
        rightAngleT = 0;
        break;
    }
}
