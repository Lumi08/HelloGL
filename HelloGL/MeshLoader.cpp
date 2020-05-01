#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void Print(Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	/*void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.ColorCount;
		
		if (mesh.ColorCount > 0)
		{
			mesh.Color = new Color[mesh.ColorCount];
			for (int i = 0; i < mesh.ColorCount; i++)
			{
				inFile >> mesh.Color[i].r;
				inFile >> mesh.Color[i].g;
				inFile >> mesh.Color[i].b;
			}
		}
	}*/

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];
			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];
			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];
			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	void Print(Mesh& mesh)
	{
		std::cout << "Vertices" << std::endl;
		if (mesh.VertexCount > 0)
		{
			std::cout << mesh.VertexCount << std::endl;
			for (int i = 0; i < mesh.VertexCount; i++)
			{
				std::cout << mesh.Vertices[i].x << " " << mesh.Vertices[i].y << " " << mesh.Vertices[i].z << std::endl;
			}
		}

		/*std::cout << "Colors" << std::endl;
		if (mesh.ColorCount > 0)
		{
			std::cout << mesh.ColorCount << std::endl;
			for (int i = 0; i < mesh.ColorCount; i++)
			{
				std::cout << mesh.Color[i].r << " " << mesh.Color[i].g << " " << mesh.Color[i].b << std::endl;
			}
		}*/

		std::cout << "TexCoords" << std::endl;
		if (mesh.TexCoordCount > 0)
		{
			std::cout << mesh.TexCoordCount << std::endl;
			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				std::cout << mesh.TexCoords[i].u << " " << mesh.TexCoords[i].v << std::endl;
			}
		}

		std::cout << "Normals" << std::endl;
		if (mesh.NormalCount > 0)
		{
			std::cout << mesh.NormalCount << std::endl;
			for (int i = 0; i < mesh.NormalCount; i++)
			{
				std::cout << mesh.Normals[i].x << " " << mesh.Normals[i].y << " " << mesh.Normals[i].z << std::endl;
			}
		}

		std::cout << "Indices" << std::endl;
		if (mesh.IndexCount > 0)
		{
			std::cout << mesh.IndexCount << std::endl;
			for (int i = 0; i < mesh.IndexCount; i++)
			{
				std::cout << mesh.Indices[i] << std::endl;
			}
		}
	}

	Mesh* MeshLoader::Load(const char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		//LoadColours(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		//Print(*mesh);

		return mesh;
	}

	Mesh* MeshLoader::LoadSimpleObj(const char* fileName)
	{
		ifstream inFile(fileName, ios::in);
		if (!inFile)
		{
			cerr << "Cant open file: " << fileName << endl;
			return nullptr;
		}

		std::vector<Vertex> vertices;
		std::vector<int> indices;


		string line;
		while (getline(inFile, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				Vertex vertex;
				stringstream ss;
				ss << line;
				ss.ignore(1, 'v');
				ss >> vertex.x >> vertex.y >> vertex.z;
				vertices.push_back(vertex);
			}

			if (line.substr(0, 2) == "f ")
			{
				int indicies1, indicies2, indicies3;
				stringstream ss;
				ss << line;
				ss.ignore(1, 'f ');
				ss >> indicies1 >> indicies2 >> indicies3;
				indices.push_back(indicies1 -1);
				indices.push_back(indicies2 -1);
				indices.push_back(indicies3 -1);
			}
		}

		Mesh* mesh = new Mesh();

		mesh->VertexCount = vertices.size();
		mesh->Vertices = new Vertex[mesh->VertexCount];
		for (int i = 0; i < vertices.size(); i++)
		{
			mesh->Vertices[i] = vertices[i];
		}

		mesh->IndexCount = indices.size();
		mesh->Indices = new GLushort[mesh->IndexCount];
		for (int i = 0; i < indices.size(); i++)
		{
			mesh->Indices[i] = indices[i];
		}

		//Print(*mesh);

		return mesh;
	}
}