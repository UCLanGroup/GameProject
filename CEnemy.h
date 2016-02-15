#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "CWeapon.h"
#include "ICollidable.h"

using Path = std::vector<Vector3>;

class CEnemy : public ICollidable
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
	CEnemy(Path* path, Vector3& offset);

	virtual void Move(float delta);
	virtual void Update(float delta);

	void SetHealth(int health);
	void SetSpeed(float speed);
	void AddWeapon(CWeapon w);
	void SetValue(int value);

	int GetHealth();
	float GetSpeed();
	std::vector<CWeapon>* GetWeapons();
	int GetValue();
	bool IsFinished();

	//Inherited from ICollidable
	virtual Vector3 GetCenterPoint();
	virtual bool GetMeshAndMatrix(tle::IMesh* mesh, float* matrix);

	~CEnemy();
};