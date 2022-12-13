#pragma once
#include "object.h"
class Plane : public Object
{
public:
	Plane(glm::vec3 col, bool wireframe = true, float width = 1.0f) : Object(), m_col(col), m_wireframe(wireframe), m_width(width)
	{
		this->createVertices();
	}
	void createVertices() override;
	void Render(GLint posAttribLoc, GLint colAttribLoc) override;

private:
	glm::vec3 m_col;
	bool m_wireframe;
	float m_width;
};

