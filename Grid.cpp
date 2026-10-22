#include "Grid.hpp"

void Grid::setup()
{

	// Set up Grid VAO, VBO, and EBO
    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);
    glGenBuffers(1, &gridEBO);
    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertices3D), gridVertices3D, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gridIndices), gridIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // Position
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}



void Grid::draw()
{
    	GLint modeLoc = glGetUniformLocation(shader.shaderID, "typeToPaint");
    	if (modeLoc != -1) {
        	glUniform1i(modeLoc, 0); // No special mode for the grid
    	}
    	glBindVertexArray(gridVAO);
    	glDrawElements(GL_LINES, 56, GL_UNSIGNED_INT, 0);
    	glBindVertexArray(0);
}