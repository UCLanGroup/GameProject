#pragma once
#include "CVector3.h"
#include "ICollidable.h"
#include "ICollider.h"
#include "IResource.h"

using namespace tle;

const string kDefaultTexture = "";

class IEntity : public ICollidable, public ICollider, public IResource
{
private:
	string name = "Null";
	string mModelTexture = kDefaultTexture;
	IMesh* mMesh = 0;
	bool mIsDead = false;
	bool mIsExplodeable = true;

protected:
	IModel* mModel = 0;

public:
	//Update
	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void CheckCollision() = 0;

	//Sets
	void SetName(string& name);

	//Loads the mesh and creates a model from it with the given texture
	void SetMesh(const string& meshFile, const string& textureFile = kDefaultTexture);

	//Sets the mesh and creates a model from it with the given texture if the existing model is not of the mesh
	void SetMesh(IMesh* mesh, const string& textureFile);

	void SetPosition(tlx::CVector3& pos);
	void SetRotation(float degrees);
	void SetDead(bool dead);
	void SetExplodeable(bool explodeable);

	//Gets
	string& GetName();
	IModel* GetModel();
	float GetRotation();
	bool IsOutOfBounds();
	bool IsDead();
	bool IsExplodeable();

	//Inherited from ICollidable
	virtual tlx::CVector3 GetCenterPoint();
	virtual IMesh* GetMesh();
	virtual bool GetMatrix(float* matrix);

	//Inherited from ICollider
	virtual bool CollidesSphere(ICollidable* collidable);
	virtual bool CollidesMesh(ICollidable* collidable);

	//Inherited from IResource
	virtual void Hide();
	virtual void Reset() = 0;

	//Destructor
	~IEntity();
};