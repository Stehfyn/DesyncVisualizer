#pragma once
#include "object.h"

class Pyramid : public Object
{
public:
	Pyramid() : Object()
	{
		this->createVertices();
	}
	//Necessary to differentiate Pyramid from an Object visually. This creates 5 vertices and a sequence of indices to collectively form a pyramid when GL_TRIANGLES is used to draw.
	void createVertices() override;
	//Performs random translation and orientation when called. There are some hardcoded parameter ranges to keep the output visually reasonable
	void doRandomPositionOrientation();
};

