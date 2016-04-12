#define _USE_MATH_DEFINES
#include "CBlaster.h"
#include "CProjectile.h"


CBlaster::CBlaster(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetMaxLevel(6);
	SetLevel(1);
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
}

CProjectile* CBlaster::CreateBullet()
{
	float matrix[16];
	GetParent()->GetMatrix(matrix);

	CProjectile* bullet = new CProjectile();

	bullet->SetMatrix(matrix);

	//If there's a target then fire directly at the target
	if (GetTarget())
	{
		CVector3 targetPos = GetTarget()->GetCenterPoint();
		CVector3 parentPos = GetParent()->GetCenterPoint();

		CVector3 dif = targetPos - parentPos;

		//Calculate the bearing from north
		float rotation = 90.0f - atan2f(dif.z, dif.x) * (180.0f / static_cast<float>(M_PI));

		bullet->SetRotation(rotation);
	}

	bullet->SetDamage(GetDamage());
	bullet->SetSpeed(GetProjSpeed());
	bullet->SetParent(GetParent());
	bullet->SetExplodeable(true);

	return bullet;
}

void CBlaster::Fire()
{
	float rotation = GetParent()->GetRotation();
	CProjectile* bullet;

	//Create a different set of bullets depending on weapon level
	switch(GetLevel())
	{
	case 1:
		//One bullet centered
		bullet = CreateBullet();
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 2:
		//Two bullets, both slightly off center to either side
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 3:
		//Three bullets, two slightly off center to either side, one centered
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(6.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalZ(3.0f); //Slightly forward
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-6.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 4:
		//Two bullets, both slightly off center to either side
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//Two bullets, one firing to either side
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly forward
		bullet->SetRotation(rotation - 30);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		bullet->SetRotation(rotation + 30);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 5:
		//Two bullets, both slightly off center to either side
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//Two bullets, one firing to either side
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly forward
		bullet->SetRotation(rotation - 30);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		bullet->SetRotation(rotation + 30);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//One bullet, firing backwards
		bullet = CreateBullet();
		bullet->SetRotation(rotation + 180);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 6:
		//Three bullets, two slightly off center to either side, one centered
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(6.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalZ(3.0f); //Slightly forward
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-6.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//Two bullets, one firing to either side
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly forward
		bullet->SetRotation(rotation - 30);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		bullet->SetRotation(rotation + 30);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//One bullet, firing backwards
		bullet = CreateBullet();
		bullet->SetRotation(rotation + 180);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	default:
		break;

	}
}