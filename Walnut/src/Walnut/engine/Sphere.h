#pragma once
#include "object.h"
class Sphere :
    public Object
{
public:
	Sphere(unsigned int prec) : Object(), m_prec(prec), col(glm::vec3(0.0f))
	{
		this->createVertices();
	}
	Sphere(unsigned int prec, glm::vec3 col) : Object(), m_prec(prec), col(col)
	{
		this->createVertices();
	}
	void createVertices() override;
	//Performs random translation and orientation when called. There are some hardcoded parameter ranges to keep the output visually reasonable
	void doRandomPositionOrientation();
	void InitializeVertices(unsigned int prec);
	void ComputeVertices(unsigned int prec);
	void ComputeIndices(unsigned int prec);
private:
	unsigned int m_prec;
	glm::vec3 col;
};

