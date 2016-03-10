#include "ICollider.h"
#include "ICollidable.h"

bool ICollider::CollideSphere(tlx::CVector3& p1, tlx::CVector3& p2, float r1, float r2)
{
	tlx::CVector3 distVec = p1 - p2;

	float sqrdDist = (distVec.x * distVec.x) + (distVec.z * distVec.z);
	float collDist = (r1 * r1) + (r2 * r2);

	return sqrdDist < collDist;
}

bool ICollider::CollideMesh(tle::IMesh* me1, tle::IMesh* me2, float* ma1, float* ma2)
{
	me1->BeginEnumTriangles();

	//Three points of the triangle each with an x,y,z
	float triA[3][3];
	float triB[3][3];

	while (me1->GetTriangle(triA[0], triA[1], triA[2]))
	{
		me2->BeginEnumTriangles();
		while (me2->GetTriangle(triB[0], triB[1], triB[2]))
		{
			//To do
			//Triangle to triangle collision check

			//If triangles collide
			//meshA->EndEnumTriangles();
			//meshB->EndEnumTriangles();
			//return true;
		}
		me2->EndEnumTriangles();
	}
	me1->EndEnumTriangles();
	return false;
}