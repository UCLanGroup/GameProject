#include "ICollidable.h"


float ICollidable::GetBoundingRadius()
{
	return mRadius;
}

//Checks if the collidables bounding spheres collide
bool ICollidable::CollidesSphere(ICollidable* c)
{
	Vector3 distVec = GetCenterPoint() - c->GetCenterPoint();

	float sqrdDist = distVec.GetX() * distVec.GetX() + distVec.GetZ() * distVec.GetZ();
	float collDist = mRadius * mRadius + c->GetBoundingRadius() * c->GetBoundingRadius();

	return sqrdDist < collDist;
}

//Expensive Mesh to Mesh collision detection
bool ICollidable::CollidesMesh(ICollidable* collidable)
{
	tle::IMesh* meshA;
	tle::IMesh* meshB;

	float matrixA[16];
	float matrixB[16];

	//Get meshes and matrixes, return false if they can't be obtained
	if (!GetMeshAndMatrix(meshA, matrixA)) return false;
	if (!GetMeshAndMatrix(meshB, matrixB)) return false;

	meshA->BeginEnumTriangles();

	//Three points of the triangle each with an x,y,z
	float triA[3][3];
	float triB[3][3];

	while (meshA->GetTriangle(triA[0], triA[1], triA[2]))
	{
		meshB->BeginEnumTriangles();
		while (meshB->GetTriangle(triB[0], triB[1], triB[2]))
		{
			//To do
			//Triangle to triangle collision check

			//If triangles collide
			//meshA->EndEnumTriangles();
			//meshB->EndEnumTriangles();
			//return true;
		}
		meshB->EndEnumTriangles();
	}
	meshA->EndEnumTriangles();
	return false;
}