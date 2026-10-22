#pragma once

#include "Includes.hpp"

#include "Object.hpp"

class ObjectManager
{

	private:

		int numObjects = 0;

		std::vector <Object> objects;

	public:

		void addObject();

		void moveObject();

		void removeObject();

		void drawObjects();

		bool noObjects();

		int getNumObjects();

		float getSizeOfObject(int objectID);
};