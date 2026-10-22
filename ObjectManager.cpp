#include "ObjectManager.hpp"

void ObjectManager::addObject(xLeft, xRight, yTop, yBottom, size)
{
	Object newObject = new Object(xLeft, xRight, yTop, yBottom, size);

	objects.push_back(newObject); 
    numObjects++;  // The number of objects is increased by 1
}




bool ObjectManager::noObjects()
{

	return (objects.size() == 0);


}


int ObjectManager::getNumObjects()
{

	return numObjects;


}


float ObjectManager::getSizeOfObject(int objectID)
{
	return objects[objectID].size;
}



void ObjectManager::removeObject(objectID)
{
	objects.erase(objects.begin() + objectID);

    numObjects--;
}



void ObjectManager::drawObjects()
{
	for(int i = 0; i < numObjects; i++)
	{
		objects[i].setup();
		objects[i].draw();
	}
}
