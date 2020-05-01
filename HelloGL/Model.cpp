#include "Model.h"
#include <iostream>
#include <fstream>

Model::Model(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture, new Vector3{ x, y, z })
{
	mMaterial = new Material();
	mMaterial->Ambient = Vector4{ 1.0, 1.0, 1.0, 1.0 };
	mMaterial->Diffuse = Vector4{ 1.0, 1.0, 1.0, 1.0 };
	mMaterial->Specular = Vector4{ 1.0, 1.0, 1.0, 1.0 };
	mMaterial->Shininess = 100.0f;
}

Model::~Model()
{
	delete mMesh;
}

void Model::Draw()
{
	if (mMesh != nullptr)
	{
		if (mMesh->Vertices != nullptr && mMesh->VertexCount != 0 &&
			mMesh->Normals != nullptr && mMesh->NormalCount != 0 &&
			mMesh->Indices != nullptr && mMesh->IndexCount != 0)
		{
			
		}

		glPushMatrix();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		if (mTexture != nullptr && mMesh->TexCoordCount > 0)
		{
			glBindTexture(GL_TEXTURE_2D, mTexture->GetID());
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, mMesh->TexCoords);

		}

		glTranslatef(mPosition->x, mPosition->y, mPosition->z);
		//glRotatef(mRotationValue, mRotation.x, mRotation.y, mRotation.z);
		/*glMaterialfv(GL_FRONT, GL_AMBIENT, &(mMaterial->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(mMaterial->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(mMaterial->Specular.x));
		glMaterialfv(GL_FRONT, GL_SHININESS, &mMaterial->Shininess);*/
		//glRotatef(mRotation, 1.0f, 0.0f, 1.0f);

		glVertexPointer(3, GL_FLOAT, 0, mMesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, mMesh->Normals);

		glPushMatrix();
		glDrawElements(GL_TRIANGLES, mMesh->IndexCount, GL_UNSIGNED_SHORT, mMesh->Indices);
		glPopMatrix();

		//glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glPopMatrix();
	}
}

void Model::Update()
{
	
}

