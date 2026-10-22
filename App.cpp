#include "Includes.hpp"

Window window;

Shader shader;

ImGUI imgui;

Grid grid;

Highlight highlightCell;

ObjectManager manager;


int main()
{

	window.start();

	window.setCursorCallback();

	window.setMouseButtonCallback();

	grid.setup();

	highlightCell.setup();

	shader.createProgram("vertex_shader.glsl", "fragment_shader.glsl");


	while(window.isActive())
	{


		imgui.setup();

		shader.useProgram();

		window.setup();

		grid.draw();

		highlightCell.draw();

		manager.drawObjects();

		imgui.render();

		window.swapBuffers();


	}

	return 0;


}

