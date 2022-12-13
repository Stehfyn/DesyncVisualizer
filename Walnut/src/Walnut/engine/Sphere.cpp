#include "Sphere.h"

void Sphere::createVertices()
{
	InitializeVertices(m_prec);
	ComputeVertices(m_prec);
	ComputeIndices(m_prec);
}

void Sphere::doRandomPositionOrientation()
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

void Sphere::InitializeVertices(unsigned int prec)
{
	unsigned int numVertices = (prec + 1) * (prec + 1);
	unsigned int numIndices = prec * prec * 6;
	for (int i = 0; i < numVertices; i++) { Vertices.push_back({ glm::vec3(), glm::vec3() }); }
	//for (int i = 0; i < numVertices; i++) { colors.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
	for (int i = 0; i < numIndices; i++) { Indices.push_back(0); }
}

void Sphere::ComputeVertices(unsigned int prec)
{
	float pi = 3.14159f;
	for (int i = 0; i <= prec; i++)
		for (int j = 0; j <= prec; j++)
		{
			float y = (float)cos((pi / 180.f) * (180.f - i * 180.f / prec));
			float x = -(float)cos((pi / 180.f) * (j * 360.f / prec)) * (float)abs(cos(asin(y)));
			float z = (float)sin((pi / 180.f) * (j * 360.f / prec)) * (float)abs(cos(asin(y)));

			if(col != glm::vec3(0.0f)) Vertices[i * (prec + 1) + j] = { glm::vec3(x, y, z), 
				glm::vec3(glm::linearRand(col.x - .2f, col.x), glm::linearRand(col.y - .2f, col.y), 0.0f) };
			else Vertices[i * (prec + 1) + j] = { glm::vec3(x, y, z), glm::vec3(x, y, z) };
			normals[i * (prec + 1) + j] = glm::vec3(x, y, z);
		}
}
void Sphere::ComputeIndices(unsigned int prec)
{
	for (int i = 0; i < prec; i++)
	{
		for (int j = 0; j < prec; j++)
		{
			Indices.at(6 * (i * prec + j) + 0) = i * (prec + 1) + j;
			Indices.at(6 * (i * prec + j) + 1) = i * (prec + 1) + j + 1;
			Indices.at(6 * (i * prec + j) + 2) = (i + 1) * (prec + 1) + j;
			Indices.at(6 * (i * prec + j) + 3) = i * (prec + 1) + j + 1;
			Indices.at(6 * (i * prec + j) + 4) = (i + 1) * (prec+1) + j + 1;
			Indices.at(6 * (i * prec + j) + 5) = (i + 1) * (prec+1) + j;
		}
	}
}
