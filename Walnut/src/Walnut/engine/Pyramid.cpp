#include "Pyramid.h"

void Pyramid::createVertices()
{
	Vertices = {
				{{.0f, 2.f, .0f}, {1.0f, 1.0f, 1.0f}},
				{{1.f, .0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
				{{-1.f, .0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
				{{-1.f, 0.f, -1.0f}, {1.0f, .0f, 0.0f}},
				{{1.0f, .0f, -1.0f}, {.0f, .0f, 1.0f}}
	};

	Indices = {
	  0, 1, 2,
	  0, 2, 3,
	  0, 3, 4,
	  0, 4, 1,
	  1, 2, 3,
	  3, 4, 1
	};
}
//OpenGL and GLM are column-major by default, so instead of transposition we just do t*r*s
void Pyramid::doRandomPositionOrientation()
{
	//(Part 2): random translation 
	float tvec1 = glm::linearRand(-2.f, 2.f);
	float tvec2 = glm::linearRand(-2.f, 2.f);
	float tvec3 = glm::linearRand(-2.f, 2.f);

	translation = glm::translate(translation, glm::vec3(tvec1, tvec2, tvec3));
	//(Part 2): random rotation based off these params
	float rangle = glm::linearRand(0.25, 0.75); //in radians ~15 => ~45 degrees
	float rorientationx = glm::linearRand(-.5f, .5f); 
	float rorientationy = glm::linearRand(-.5f, .5f);
	float rorientationz = glm::linearRand(-.5f, .5f);
	rotation = glm::rotate(glm::mat4(1.0f), rangle, glm::vec3(rorientationx, rorientationy, rorientationz));
}
