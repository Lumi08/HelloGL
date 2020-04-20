#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, Texture2D* texture, Vector3* position);
	virtual ~SceneObject();

	virtual void Draw();
	virtual void Update();

	void ClearTexture() { mTexture = nullptr; }

	float GetX() { return mPosition->x; }
	float GetY() { return mPosition->y; }
	float GetZ() { return mPosition->z; }
	void SetX(float x) { mPosition->x = x; }
	void SetY(float y) { mPosition->y = y; }
	void SetZ(float z) { mPosition->z = z; }

	void SetTexture(char* path, int width, int height);

protected:
	Mesh* mMesh;
	Texture2D* mTexture;
	Vector3* mPosition;
};

