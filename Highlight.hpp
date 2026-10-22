#pragma once

#include "Includes.hpp"

class Highlight
{

	private:

		GLuint highlightedCellVBO, highlightedCellVAO; // The memory for the cell to be highlighted when we hover over it in the ADD mode

	public:

		void setup();

		void draw();
};