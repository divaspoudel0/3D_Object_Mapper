#include "Object.hpp"

Object::Object(float xLeft, float xRight, float yTop, float yBottom, float size)
{

    if(size == 1.0) // This is a tree
    {
        height = 0.2;
    }

    if(size == 2.0) // This is a vehicle
    {
        height = 0.05;
    }

    if(size == 3.0) // This is a house
    {
        height = 0.1;
    }

    // Define the vertices for the current object
    cubeVertices[] = {
        // Front face
        xLeft, yBottom, 0.0f,
        xRight, yBottom, 0.0f,
        xLeft, yTop, 0.0f,
        xRight, yTop, 0.0f,

        // Back face
        xLeft, yBottom, height,
        xRight, yBottom, height,
        xLeft, yTop, height,
        xRight, yTop, height,

        // Left face
        xLeft, yBottom, 0.0f,
        xLeft, yBottom, height,
        xLeft, yTop, height,
        xLeft, yTop, 0.0f,

        // Right face
        xRight, yBottom, 0.0f,
        xRight, yBottom, height,
        xRight, yTop, height,
        xRight, yTop, 0.0f,

        // Top face
        xLeft, yTop, 0.0f,
        xRight, yTop, 0.0f,
        xRight, yTop, height,
        xLeft, yTop, height,

        // Bottom face
        xLeft, yBottom, 0.0f,
        xRight, yBottom, 0.0f,
        xRight, yBottom, height,
        xLeft, yBottom, height
    };



    cubeIndices[] = {
        // Front face
        0, 1, 2,
        1, 3, 2,

        // Back face
        4, 5, 6,
        5, 7, 6,

        // Left face
        8, 9, 10,
        9, 11, 10,

        // Right face
        12, 13, 14,
        13, 15, 14,

        // Top face
        16, 17, 18,
        17, 19, 18,

        // Bottom face
        20, 21, 22,
        20, 22, 23
    };

}


void Object::setup()
{
	// Generate and bind VAO, VBO, and EBO for each object
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO); // Added EBO generation

    // Bind the VAO, VBO, and EBO for the current object
    glBindVertexArray(cubeVAO);

    // Update the VBO with vertex data
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeVertices), cubeVertices);

    // Update the EBO with index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(cubeIndices), cubeIndices);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void Object::draw()
{
	glClear(GL_DEPTH_BUFFER_BIT);

    // Set model matrix for the cube
    glm::mat4 cubeModel = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));

    glUniform1i(modeLoc, int(size));
    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // Use glDrawElements to draw the cube
    glBindVertexArray(0);
}