#include "Mesh.h"

bool Mesh::loadModelFromFile(const char* path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
	if (!scene)
	{
		printf("couldn't open the .obj file.\n");
		return false;
	}
	if (scene && scene->HasMeshes())
	{
		aiMesh* mesh = scene->mMeshes[0];

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertices.push_back({glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z), 
				glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z)});
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for(unsigned int j = 0; j < face.mNumIndices; j++) Indices.push_back(face.mIndices[j]);
		}
	}
	return true;
}
bool Mesh::loadModelFromFile(const char* path, glm::vec3 col)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
	if (!scene)
	{
		printf("couldn't open the .obj file.\n");
		return false;
	}
	if (scene && scene->HasMeshes())
	{
		aiMesh* mesh = scene->mMeshes[0];

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertices.push_back({ glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
				glm::vec3(glm::linearRand(col.x -.2f, col.x +.2f), glm::linearRand(col.y - .2f, col.y + .2f), glm::linearRand(col.z - .2f, col.z + .2f))});
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) Indices.push_back(face.mIndices[j]);
		}
	}
	return true;
}
