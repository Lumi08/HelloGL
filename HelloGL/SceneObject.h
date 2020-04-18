#pragma once
#include "Structures.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh);
	virtual ~SceneObject();

	virtual void Draw();
	virtual void Update();
protected:
	Mesh* mMesh;

};

