#include "Object.h"

bool Object::collideWith(Object* other) {
	if (other->x + other->sizeX < x)	return false;
	if (other->x > x + sizeX)		    return false;
			
	if (other->y + other->sizeY < y)	return false;
	if (other->y > y + sizeY)		    return false;

	return true;
}