#include "CFace.h"
using namespace glm;
CFace::CFace()
{
    m_vboIndex = 0;
    radius = 1.0f;
    //angle = 80.0f;
}

void CFace::drawPlayer(GLuint program, float positionX, float positionY, unsigned VAO, unsigned VBO)
{
    //int i, j;

    //0.0f, 0.0f, 1.0f,
    //1.0f, 0.0f, 1.0f,
    //1.0f, 1.0f, 1.0f,

    for (int i = 0; i <= 80; i++) {
        float angle = 4.5f * i;
        float angle2 = 4.5f * (i + 1);

        //윗면
        //x, y, z
        vertices.push_back(radius * cos(radians(angle)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle)));

        //color
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);

        //color
        vertices.push_back(1.0f);
        vertices.push_back(.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);


        //아랫면
        vertices.push_back(radius * cos(radians(angle)));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sin(radians(angle)));

        //color
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);




        //기둥1
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        //기둥2
        //x y z
        vertices.push_back(radius * cos(radians(angle)));
        vertices.push_back(1.0f);
        vertices.push_back(radius * sin(radians(angle)));

        //color
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle)));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sin(radians(angle)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        //x y z
        vertices.push_back(radius * cos(radians(angle2)));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sin(radians(angle2)));

        //color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

    }

    float* verticeArr = &vertices[0];




    glUseProgram(program); //draw 3 vertices as triangles 

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //use the created program 



    //unsigned int VBO, VAO;
    glGenVertexArrays(2, &VAO);
    glGenBuffers(2, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 23328, verticeArr, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    ////////////본격적인 조작은 이 아래에서 부터//////////////////////


    ///이렇게가
    mat4 view = mat4(1.0f);
    //view = translate(view, vec3(1.0f, 1.0f, -0.5f));
    //view = rotate(view, radians(120.0f), vec3(1.0f, 1.0f, 0.0f));
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
    ///한 세트.

    mat4 projection = mat4(1.0f);
    //projection = perspective(radians(45.0f), 1.5f, 0.1f, 100.0f);
    projection = ortho(-3.0f, 3.0f, -2.0f, 2.0f, -2.0f, 2.0f);

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

    glBindVertexArray(VAO);


    mat4 model = mat4(1.0f);
    model = translate(model, vec3(positionX, positionY + 0.4, 0.0));
    model = scale(model, vec3(0.1, 0.25, 0.1));
    //model = rotate(model, radians(45.0f), vec3(1.0f, 0.3f, 0.5f));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 960);

}

void CFace::drawThief(GLuint program, float positionY, unsigned VAO, unsigned VBO)
{
    for (int i = 0; i <= 80; i++) {
        float angle = 4.5f * i;
        float angle2 = 4.5f * (i + 1);

        //윗면
        //x, y, z
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(0.0f);

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);


        //아랫면
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);




        //기둥1
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);

        //기둥2
        //x y z
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(1.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(0.0f);
        verticesThief.push_back(0.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);

        //x y z
        verticesThief.push_back(radius * cos(radians(angle2)));
        verticesThief.push_back(0.0f);
        verticesThief.push_back(radius * sin(radians(angle2)));

        //color
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);
        verticesThief.push_back(1.0f);

    }

    float* verticeArr = &verticesThief[0];


    glUseProgram(program); //draw 3 vertices as triangles 

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //use the created program 

    //unsigned int VBO, VAO;
    glGenVertexArrays(12, &VAO);
    glGenBuffers(12, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 23328, verticeArr, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    ////////////본격적인 조작은 이 아래에서 부터//////////////////////


    ///이렇게가
    mat4 view = mat4(1.0f);
    //view = translate(view, vec3(1.0f, 1.0f, -0.5f));
    //view = rotate(view, radians(120.0f), vec3(1.0f, 1.0f, 0.0f));
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
    ///한 세트.

    mat4 projection = mat4(1.0f);
    //projection = perspective(radians(45.0f), 1.5f, 0.1f, 100.0f);
    projection = ortho(-3.0f, 3.0f, -2.0f, 2.0f, -2.0f, 2.0f);

    int projectionLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

    glBindVertexArray(VAO);


    mat4 model = mat4(1.0f);
    model = translate(model, vec3(1.25, positionY + 0.4, 0.0));
    model = scale(model, vec3(0.1, 0.25, 0.1));
    //model = rotate(model, radians(45.0f), vec3(1.0f, 0.3f, 0.5f));
    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 960);
}
