#pragma once
#include "object.h"
class Triangle : public Object
{
public:
	Triangle() : Object() { this->createVertices(); }
	void createVertices() override;
};