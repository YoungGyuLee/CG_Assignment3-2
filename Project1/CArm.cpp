#include "CArm.h"

using namespace glm;
void CArm::playerDraw(GLuint program, unsigned int VAO1, unsigned int VBO1, unsigned int VAO2, unsigned int VBO2, int type, float positionX, float positionY)
{
    cout << "positionX " << positionX << endl;
    float pX = positionX;
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
        glGenVertexArrays(3, &VAO1);
        glGenBuffers(3, &VBO1);

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

        float angle = 180.0f;

        mat4 model = mat4(1.0f);
        model = translate(model, vec3(pX, positionY + 0.3, -1.0));
        //cout << "positionX " << positionX << endl;
        model = rotate(model, radians(leftRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        leftForeArm.playerDraw(program, VAO2, VBO2, LEFT, angle, pX, positionY);

    }
    else {
        glGenVertexArrays(5, &VAO1);
        glGenBuffers(5, &VBO1);

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

        float angle = 45.0f;


        mat4 model = mat4(1.0f);
        model = translate(model, vec3(pX, positionY + 0.3, 1.0));
        model = rotate(model, radians(rightRotateAngle), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
        glBindVertexArray(VAO1);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        rightForeArm.playerDraw(program, VAO2, VBO2, RIGHT, angle, pX, positionY);

        //leftForeArm
    }
}

void CArm::thiefDraw(GLuint program, unsigned int VAO1, unsigned int VBO1, unsigned int VAO2,
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

    if (leftRotateAngleT != leftAngleT)
        leftRotateAngleT = leftPreviousAngleT += (leftAngleT - leftPreviousAngleT) * 0.1;

    if (rightRotateAngleT != rightAngleT)
        rightRotateAngleT = rightPreviousAngleT += (rightAngleT - rightPreviousAngleT) * 0.1;



    if (type == LEFT) {
        glGenVertexArrays(13, &VAO1);
        glGenBuffers(13, &VBO1);

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

        float angle = 180.0f;
        mat4 model = mat4(1.0f);
        model = translate(model, vec3(1.25, pY + 0.3, -1.0));
        model = rotate(model, radians(leftRotateAngleT), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        leftForeArm.thiefDraw(program, VAO2, VBO2, LEFT, angle, pY);

    }
    else {
        glGenVertexArrays(15, &VAO1);
        glGenBuffers(15, &VBO1);

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

        float angle = 45.0f;


        mat4 model = mat4(1.0f);
        model = translate(model, vec3(1.25, pY + 0.3, 1.0));
        model = rotate(model, radians(rightRotateAngleT), vec3(0.0f, 0.0f, 1.0f));
        model = scale(model, vec3(0.5, 1.5, 0.5));
        int modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(VAO1);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        rightForeArm.thiefDraw(program, VAO2, VBO2, RIGHT, angle, pY);

        //leftForeArm
    }












}

void CArm::setMotion(int pose)
{
    leftPreviousAngle = leftAngle;
    rightPreviousAngle = rightAngle;
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

    leftForeArm.setMotion(pose);
    rightForeArm.setMotion(pose);

}

void CArm::setTMotion(int pose)
{
    leftPreviousAngleT = leftAngleT;
    rightPreviousAngleT = rightAngleT;
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

    leftForeArm.setTMotion(pose);
    rightForeArm.setTMotion(pose);
}
