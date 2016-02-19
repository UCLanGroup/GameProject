#include "CMeshCache.h"

CMeshCache CMeshCache::mCache;

IMesh* CMeshCache::LoadMesh(string s)
{
	auto mesh = mMeshMap.find(s);
	if (mesh != mMeshMap.end())
	{
		return mesh->second;
	}
	else if (gEngine == 0)
	{
		return 0;
	}
	else
	{
		IMesh* newMesh = gEngine->LoadMesh(s);
		mMeshMap.insert(std::pair<string, IMesh*>{s, newMesh});
		return newMesh;
	}
}

void CMeshCache::Clear()
{
	if (gEngine == 0) return;

	for (auto mesh = mMeshMap.begin(); mesh != mMeshMap.end(); mesh++)
	{
		gEngine->RemoveMesh(mesh->second);
	}
	mMeshMap.clear();
}