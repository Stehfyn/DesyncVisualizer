#include "object.h"

Object::Object()
{
}

// (Part 1): See aforementioned in header comment
void Object::Initialize(GLint posAttribLoc, GLint colAttribLoc) {

	// Set up your VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// setting the Vertex VBO
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Setting the Index VBO
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);


	// (Part 1): decomposed model matrix as translation * rotation * scale, also linearRand is seeded in Initialize() of Engine
	translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
	rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0.0f, .0f));
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	model = translation * rotation * scale;
	
}

Object::~Object()
{
	//RAII 
	Vertices.clear();
	Indices.clear();
}
// (Part 1): See aforementioned in header comment
void Object::Update()
{

	model = translation * rotation * scale;
	//To Do: Extra credit / Grad Only
	//	Make the object move in a circle around the origin
}
void Object::Update(glm::mat4 in)
{

	model = in;

}
// (Part 1): See aforementioned in header comment
glm::mat4 Object::GetModel()
{
	return model;
}
// (Part 1): See aforementioned in header comment
void Object::Render(GLint posAttribLoc, GLint colAttribLoc)
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
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	// disable the vertex attributes
	glDisableVertexAttribArray(posAttribLoc);
	glDisableVertexAttribArray(colAttribLoc);

	// unbind VBO(s) and ElementBuffer(s)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

