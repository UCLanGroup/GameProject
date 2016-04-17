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
	SetFireSound(gEngine->CreateSound(SOUND_SHOOT));
	SetTarget(0);
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
		bullet = CreateProjectile<CProjectile>();
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 2:
		//Two bullets, both slightly off center to either side
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 3:
		//Three bullets, two slightly off center to either side, one centered
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(6.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalZ(3.0f); //Slightly forward
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(-6.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 4:
		//Two bullets, both slightly off center to either side
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//Two bullets, one firing to either side
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly forward
		bullet->GetModel()->RotateY(-30.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		bullet->GetModel()->RotateY(30.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 5:
		//Two bullets, both slightly off center to either side
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//Two bullets, one firing to either side
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly forward
		bullet->GetModel()->RotateY(-30.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		bullet->GetModel()->RotateY(30.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//One bullet, firing backwards
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->RotateY(180);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 6:
		//Three bullets, two slightly off center to either side, one centered
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(6.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalZ(3.0f); //Slightly forward
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(-6.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//Two bullets, one firing to either side
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly forward
		bullet->GetModel()->RotateY(-30.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		bullet->GetModel()->RotateY(30.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//One bullet, firing backwards
		bullet = CreateProjectile<CProjectile>();
		bullet->GetModel()->RotateY(180);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	default:
		break;

	}
}