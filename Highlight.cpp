#include "Highlight.hpp"

void Highlight::setup()
{
	// Initialize VBO and VAO for the highlighted cell
	// This is the initialisation portion for the Highlight object
	glGenVertexArrays(1, &highlightedCellVAO);
	glGenBuffers(1, &highlightedCellVBO);

	glBindVertexArray(highlightedCellVAO);
	glBindBuffer(GL_ARRAY_BUFFER, highlightedCellVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, nullptr, GL_DYNAMIC_DRAW); // Reserve space

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



void Highlight::draw()
{
	// Draw the highlighted cell (if any)
        //glUseProgram(shaderProgram);
        if(window.getMode() == 0 && window.isTopView() == true) // I want to add the object
        {
            if (modeLoc != -1) {
            glUniform1i(modeLoc, 10*int(size)); // Example: setting to 2 for green color
        }
        glBindVertexArray(highlightedCellVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Drawing the highlighted cell
        glBindVertexArray(0);

        }

        glClear(GL_DEPTH_BUFFER_BIT);
}