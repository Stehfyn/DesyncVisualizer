#include "Cube.h"
Cube::Cube() : Object()
{
	this->createVertices();
}
void Cube::createVertices()
{	//6 floats, 2 vertex per indiex, [0] pos [1] col
	Vertices = {
				//8 vertices 
				{{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
				{{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
				{{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
				{{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},

				{ {1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
				{ {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
				{ {-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
				{{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
	};
	//6 faces, 2 triangles per
	Indices =  
	{
	  2,3,4,
	  8,7,6,
	  1,5,6,
	  2,6,7,
	  7,8,4,
	  1,4,8,
	  1,2,4,
	  5,8,6,
	  2,1,6,
	  3,2,7,
	  3,7,4,
	  5,1,8

	};
	for (unsigned int i = 0; i < Indices.size(); i++)
	{
		Indices[i] = Indices[i] - 1;
	}
	//doRandomPositionOrientation();
}

void Cube::doRandomPositionOrientation()
{
	//(Part 2): random translation 
	float tvec1 = glm::linearRand(-5.f, 5.f);
	float tvec2 = glm::linearRand(-5.f, 5.f);
	float tvec3 = glm::linearRand(-5.f, 5.f);

	translation = glm::translate(translation, glm::vec3(tvec1, tvec2, tvec3));
	//(Part 2): random rotation based off these params
	float rangle = glm::linearRand(0.0f, 2.0f);
	float rorientationx = glm::linearRand(0.0f, 1.0f);
	float rorientationz = glm::linearRand(0.0f, 1.0f);
	float rorientationy = glm::linearRand(0.0f, 1.0f);
	rotation = glm::rotate(glm::mat4(1.0f), rangle, glm::vec3(rorientationx, rorientationy, rorientationz));
}