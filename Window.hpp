#pragma once

#include "Includes.hpp"

class Window
{
	private:

		GLFWwindow* windowPointer;

		int mode = -1;

        int size = -1;

		bool topView = false;

        glm::mat4 projection, view, model;

        int selectedObject;

        bool wasMoved = false;

	public:

		void start();

        void setup();

        float roundToDecimalPlaces(float number, int decimalPlaces);

        bool doRectanglesOverlap(float x1Left, float x1Right, float y1Bottom, float y1Top,
                         float x2Left, float x2Right, float y2Bottom, float y2Top);

        bool checkForOccupiedSpace(float xLeft, float xRight, float yBottom, float yTop);

		void cursorCallback(GLFWwindow* window, double xpos, double ypos);

		void setCursorCallback();

		void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		void setMouseButtonCallback();

        bool isActive();

        void clearColor();

        void clearBuffer();

        void swapBuffers();

        int getMode();

        bool isTopView();
  
};