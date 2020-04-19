#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	mMesh = mesh;
	mTexture = texture;
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
