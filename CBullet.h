#include "CBaseProjectile.h"

class CBullet : public CBaseProjectile
{
public:
	void Init();
	void Cleanup();

	CBullet();
	virtual ~CBullet();
};