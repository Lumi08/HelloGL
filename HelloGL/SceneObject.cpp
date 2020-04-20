#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture, Vector3* position)
{
	mMesh = mesh;
	mTexture = texture;
	mPosition = position;
}

SceneObject::~SceneObject()
{
}

void SceneObject::Draw()
{
}

void SceneObject::Update()
{
}

void SceneObject::SetTexture(char* path, int width, int height)
{
	if (mTexture == nullptr)
	{
		mTexture = new Texture2D();
	}

	mTexture->Load(path, width, height);
}
