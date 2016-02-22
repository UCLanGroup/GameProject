#define _USE_MATH_DEFINES
#include "IEntity.h"
#include "Globals.h"
#include "CMeshCache.h"


////////////////////Update////////////////////


//Movement function for the entity, should only contain movement
void IEntity::Move(float delta)
{
	//No movement
}

//Update function for the entity
void IEntity::Update(float delta)
{
	Move(delta);
}


/////////////////////Sets/////////////////////


//Sets the name of the enitty
void IEntity::SetName(string& name)
{
	name = name;
}

//Sets the entity's mesh and model
void IEntity::SetMesh(string meshFile)
{
	SetMesh( CMeshCache::GetInstance()->LoadMesh(meshFile) );
}

//Sets the entity's mesh and model
void IEntity::SetMesh(IMesh* mesh)
{
	if (mesh != 0) //Check if valid mesh
	{
		if (mMesh != mesh) //Check if mesh has been changed
		{
			if (mModel) //If an existing model exists then remove it but preserve the location
			{
				Vector3 pos(mModel->GetX(), mModel->GetY(), mModel->GetZ());
				mMesh->RemoveModel(mModel);
				mMesh = mesh; //Set the new mesh
				mModel = mMesh->CreateModel();
				mModel->SetPosition(pos.GetX(), pos.GetY(), pos.GetZ());
			}
			else //If no existing model exists then create one
			{
				mMesh = mesh; //Set the new mesh
				mModel = mMesh->CreateModel();
			}
		}
		else //No change of mesh
		{
			if (!mModel) //Check if no model exists, create one if not
			{
				mModel = mMesh->CreateModel();
			}
		}
	}
}

//Sets the entity's position
void IEntity::SetPosition(Vector3& pos)
{
	if (mModel)
	{
		mModel->SetPosition(pos.GetX(), pos.GetY(), pos.GetZ());
	}
}

//Sets the Y rotation of the entity's model in degrees
void IEntity::SetRotation(float rotation)
{
	if (mModel)
	{
		mModel->ResetOrientation();
		mModel->RotateY(rotation);
	}
}

void IEntity::SetDead(bool dead)
{
	mIsDead = dead;
}


/////////////////////Gets/////////////////////


//Get the entity's name
string& IEntity::GetName()
{
	return name;
}

//Get the entity's model
//Zero is returned if there is no model
IModel* IEntity::GetModel()
{
	return mModel;
}

//Gets the entity's rotation
float IEntity::GetRotation()
{
	float matrix[16];
	mModel->GetMatrix(&(matrix[0]));

	return (atan2f(matrix[2], matrix[0]) * (180.0f / static_cast<float>(M_PI)));
}

//Checks if the entity's model is out of bounds
//Returns false if there is no model
bool IEntity::IsOutOfBounds()
{
	if (mModel)
		return  mModel->GetX() < AREA_BOUNDS_LEFT ||
				mModel->GetX() > AREA_BOUNDS_RIGHT ||
				mModel->GetZ() > AREA_BOUNDS_TOP ||
				mModel->GetZ() < AREA_BOUNDS_BOTTOM;
	else
		return false;
}

//Returns whether the entity is dead
bool IEntity::IsDead()
{
	return mIsDead;
}


//////////Inherited from ICollidable//////////


//Get the center point of the entity's model
Vector3 IEntity::GetCenterPoint()
{
	if (mModel)
		return Vector3(mModel->GetX(), mModel->GetY(), mModel->GetZ());
	else
		return Vector3();
}

//Get the entity's mesh
IMesh* IEntity::GetMesh()
{
	return mMesh;
}

//Get the matrix of the entity's model
bool IEntity::GetMatrix(float* matrix)
{
	if (mModel)
	{
		mModel->GetMatrix(matrix);
		return true;
	}
	return false;
}


///////////Inherited from ICollider///////////


//Checks if the collidables bounding spheres collide
bool IEntity::CollidesSphere(ICollidable* c)
{
	return CollideSphere(this->GetCenterPoint(), c->GetCenterPoint(), this->GetRadius(), c->GetRadius());
}

//Expensive Mesh to Mesh collision detection
bool IEntity::CollidesMesh(ICollidable* collidable)
{
	tle::IMesh* meshA = GetMesh();
	tle::IMesh* meshB = collidable->GetMesh();

	float matrixA[16];
	float matrixB[16];

	//Get meshes and matrixes, return false if they can't be obtained
	if (!meshA || !meshB) return false;
	if (!GetMatrix(matrixA)) return false;
	if (!collidable->GetMatrix(matrixB)) return false;

	return CollideMesh(meshA, meshB, matrixA, matrixB);
}


///////////Inherited from IResource///////////


//Hide the entity's model off screen
void IEntity::Hide()
{
	if (mModel)
	{
		mModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
	}
}


//////////////////Destructor//////////////////


IEntity::~IEntity()
{
	if (mModel && mMesh && gEngine)
	{
		mMesh->RemoveModel(mModel);
	}
}