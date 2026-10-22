#pragma once

#include "Includes.hpp"

class ImGUI
{
	public:

		void setup();

		void onAddObjectSelection(int selectedItem);

		void onMoveObjectClick();

		void onRemoveObjectClick();

		void render();
};