#pragma once
#include "Object.h"
class MovableObject : public Object
{
public:
	MovableObject(D2D1_POINT_2F center, float width, float height) : Object(center, width, height) {};
	virtual void move(D2D1_POINT_2F) = 0;
};

