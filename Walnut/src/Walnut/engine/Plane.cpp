#include "Plane.h"
void Plane::createVertices()
{
	Vertices = {
				{{-.5f, 0.f, -.5f}, {m_col.x, m_col.y, m_col.z}},
				{{-.5f, 0.f, .5f}, {m_col.x, m_col.y, m_col.z}},
				{{.5f, 0.f, .5f}, {m_col.x, m_col.y, m_col.z}},
				{{.5f, 0.f, -.5f}, {m_col.x, m_col.y, m_col.z}},
	};

	Indices = {
	  0, 1, 2,
	  0, 2, 3,
	};
}

void Plane::Render(GLint posAttribLoc, GLint colAttribLoc)
{
	// Bind VAO
	glBindVertexArray(vao);

	// Bind VBO(s)
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	// enable the vertex attribute arrays 
	// this is the poistion attrib in the vertex shader
	glEnableVertexAttribArray(posAttribLoc);
	// this is the color attribe in the vertex shader
	glEnableVertexAttribArray(colAttribLoc);

	// Draw call to OpenGL

	glLineWidth(m_width);

	if (m_wireframe) glDrawArrays(GL_LINE_LOOP, 0, 4);
	else glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	

	// disable the vertex attributes
	glDisableVertexAttribArray(posAttribLoc);
	glDisableVertexAttribArray(colAttribLoc);

	// unbind VBO(s) and ElementBuffer(s)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}