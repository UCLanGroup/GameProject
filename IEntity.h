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

	void SetPosition(const tlx::CVector3& pos);
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

	//Returns the center point of the model
	virtual tlx::CVector3 GetCenterPoint();

	//Returns a pointer to the mesh of the entity's model
	virtual IMesh* GetMesh();

	//Fills in a 16 size float array with the model's matrix data
	virtual bool GetMatrix(float* matrix);

	//Inherited from ICollider

	//Returns true if there is a collision between the two entities, else false
	//If either entity is dead then the result is always false
	virtual bool CollidesSphere(ICollidable* collidable);

	//Returns true if there is a collision between the two entities, else false
	//If either entity is dead then the result is always false
	virtual bool CollidesMesh(ICollidable* collidable);

	//Inherited from IResource

	//Places the entity off screen
	virtual void Hide();

	//No longer used or supported
	virtual void Reset() = 0;

	//Nick Cage Mode
	virtual void ActivateTheCage();

	//Destructor
	~IEntity();
};