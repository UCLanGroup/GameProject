#pragma once
#include <unordered_map>
#include <TL-Engine.h>
#include "Globals.h"

class CMeshCache
{
private:
	static CMeshCache mCache;

	std::unordered_map<string, tle::IMesh*> mMeshMap;

	CMeshCache() {}
public:

	IMesh* LoadMesh(string s);

	void Clear();

	static CMeshCache* GetInstance()
	{
		return &mCache;
	}
};