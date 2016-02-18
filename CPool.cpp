#include "CPool.h"
#include "CEnemy.h"

template class CPool<CEnemy>;

template <class T>
std::mutex CPool<T>::mPoolMutex;

template <class T>
std::shared_ptr<CPool<T>> CPool<T>::mPool(0);

template <class T>
CPool<T>* CPool<T>::GetInstance()
{
	if (!(mPool.get())) //Check if exists
	{
		Lock lock(mPoolMutex); //Lock to prevent duplicates
		if (!(mPool.get())) //Create if doesn't exist
		{
			mPool.reset(new CPool);
		}
	}
	return mPool.get();
}

template <class T>
void CPool<T>::Init(int size)
{
	for (int i = 0; i < size; i++)
	{
		AddRes(new T);
	}
}

template <class T>
void CPool<T>::Clear()
{
	mResources.clear(); //Unique pointers will handle the deletion
}

template <class T>
typename CPool<T>::resource_ptr CPool<T>::GetRes()
{
	if (mResources.empty())
	{
		AddRes(new T);
	}
	resource_ptr ptr(mResources.back().release(),
		ResourceDeleter{std::weak_ptr<CPool>(mPool)});
	ptr.get()->Reset();
	mResources.pop_back();
	return move(ptr);
}

template <class T>
void CPool<T>::AddRes(T* resource)
{
	resource->Hide();
	unique_ptr<T> res(resource);
	mResources.push_back(move(res));
}

template <class T>
CPool<T>::~CPool()
{
	mResources.clear(); //Unique pointers will handle the deletion
}