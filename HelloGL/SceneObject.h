#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Draw();
	virtual void Update();
protected:
	Mesh* mMesh;
	Texture2D* mTexture;
};

