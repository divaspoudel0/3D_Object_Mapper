#pragma once

#include "ObjectManager.hpp"

class Object
{

	private:

		GLuint cubeVAO, cubeVBO, cubeEBO;

		float xLeft, xRight, yTop, yBottom, size, height;

		float* cubeVertices;

        unsigned int* cubeIndices;

    friend class ObjectManager;

	public:

		Object(float xLeft, float xRight, float yTop, float yBottom, float size);

		void setup();

		void draw();
};