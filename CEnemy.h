#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "CWeapon.h"
#include "ICollidable.h"
#include "IResource.h"

using Path = std::vector<Vector3>;

class CEnemy : public ICollidable, public IResource
{
private:
	//Stats
	int mHealth;
	float mSpeed;
	std::vector<CWeapon> mWeapons;
	int mValue;

	IMesh* mMesh;
	IModel* mModel;

	//Pathing
	Path* mpPath;
	Vector3 mOffset;
	int mPathPos;
	float mMoveTimer;
	bool mFinished;

public:
	CEnemy();
	CEnemy(Path* path, Vector3& offset);

	//Updates
	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void TakeDamage(int damage);

	//Sets
	void SetHealth(int health);
	void SetSpeed(float speed);
	void AddWeapon(CWeapon w);
	void SetValue(int value);
	void SetPath(Path* path, Vector3& offset);

	//Gets
	int GetHealth();
	float GetSpeed();
	std::vector<CWeapon>* GetWeapons();
	int GetValue();
	bool IsFinished();

	//Inherited from ICollidable
	virtual Vector3 GetCenterPoint();
	virtual bool GetMeshAndMatrix(tle::IMesh* mesh, float* matrix);

	//Inherited from IResource
	virtual void Hide();
	virtual void Reset();

	~CEnemy();
};