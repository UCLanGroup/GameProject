#pragma once
#include "Vector3.h"
#include "ICollidable.h"
#include "ICollider.h"
#include "IResource.h"

using namespace tle;

class IEntity : public ICollidable, public ICollider, public IResource
{
private:
	string name = "Null";
	IMesh* mMesh = 0;

protected:
	IModel* mModel = 0;

public:
	//Update
	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void CheckCollision() = 0;

	//Sets
	void SetName(string& name);
	void SetMesh(string meshFile);
	void SetMesh(IMesh* mesh);
	void SetPosition(Vector3& pos);

	//Gets
	string& GetName();
	IModel* GetModel();
	bool IsOutOfBounds();

	//Inherited from ICollidable
	virtual Vector3 GetCenterPoint();
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