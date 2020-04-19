#include "Cube.h"
#include <iostream>
#include <fstream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	mPosition = new Vector3{ x, y, z };
}

Cube::~Cube()
{
	delete mMesh;
}

void Cube::Draw()
{
	if (mMesh != nullptr)
	{
		if (mMesh->Vertices != nullptr && mMesh->VertexCount != 0 &&
			mMesh->Color != nullptr && mMesh->ColorCount != 0 &&
			mMesh->Indices != nullptr && mMesh->IndexCount != 0)
		{
			glBindTexture(GL_TEXTURE_2D, mTexture->GetID());
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			//glPushMatrix();
			glTranslatef(mPosition->x, mPosition->y, mPosition->z);																
			//glRotatef(mRotation, 1.0f, 0.0f, 1.0f);

			glVertexPointer(3, GL_FLOAT, 0, mMesh->Vertices);
			glColorPointer(3, GL_FLOAT, 0, mMesh->Color);
			glTexCoordPointer(2, GL_FLOAT, 0, mMesh->TexCoords);

			glPushMatrix();
			glDrawElements(GL_TRIANGLES, mMesh->IndexCount, GL_UNSIGNED_SHORT, mMesh->Indices);
			glPopMatrix();

			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			//glPopMatrix();
		}
	}
}

void Cube::Update()
{
}

