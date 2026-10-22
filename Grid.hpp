#pragma once

#include "Includes.hpp"

class Grid
{

	private:

    // The variables xNorm and yNorm are the coordinates of the cursor in normalized coordinates. They were to be sent
	// between the mouse_button_callback and the cursor_position_callback, so they are defined here
	float xNorm, yNorm;

	// The memory to hold the vertices of the grid
	// This is the initialisation for the Grid object
    GLuint gridVAO, gridVBO, gridEBO;

	public:


		void setup();

		void draw();
};