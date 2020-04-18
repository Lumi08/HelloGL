#include "Cube.h"
#include <iostream>
#include <fstream>

Cube::Cube(Mesh* mesh, float x, float y, float z)
{
	mPosition = new Vector3{ x, y, z };
	mMesh = mesh;
}

Cube::~Cube()
{
	delete mMesh;
}

void Cube::Draw()
{
	if (mMesh->Vertices != nullptr && mMesh->VertexCount != 0 &&
		mMesh->Color != nullptr && mMesh->ColorCount != 0 &&
		mMesh->Indices != nullptr && mMesh->IndexCount != 0)
	{
		
		glPushMatrix();
		glTranslatef(mPosition->x, mPosition->y, mPosition->z);
		//glRotatef(mRotation, 1.0f, 0.0f, 1.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mMesh->Vertices);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, mMesh->Color);

		glPushMatrix();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, mMesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}
}

void Cube::Update()
{
}

