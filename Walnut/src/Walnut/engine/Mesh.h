#pragma once
#include "object.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Mesh : public Object
{
public:
	Mesh(const char* path) : Object()
	{
		this->loadModelFromFile(path);
	}
	Mesh(const char* path, glm::vec3 col) : Object()
	{
		this->loadModelFromFile(path, col);
	}
	void createVertices() override {}
	bool loadModelFromFile(const char* path);
	bool loadModelFromFile(const char* path, glm::vec3 col);
};

