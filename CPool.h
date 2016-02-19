#pragma once
#include <vector>
#include <list>
#include <mutex>

template <class T>
class CPool
{
private:
	//Custom deleter for the unique_ptr that will return the resource back to the pool if the pool exists, otherwise deletes it.
	struct ResourceDeleter
	{
	private:
		std::weak_ptr<CPool<T>> mPool;

	public:
		explicit ResourceDeleter(std::weak_ptr<CPool<T>> pool) : mPool(pool) {}
		explicit ResourceDeleter() {}

		void operator()(T* ptr) //Deletion function
		{
			if (std::shared_ptr<CPool<T>> pool_ptr = mPool.lock())
			{
				(pool_ptr).get()->AddRes(ptr);	//Add the resource back to the pool if the pool exist
			}
			else
			{
				std::default_delete<T>{}(ptr);	//Delete the resource if there is no pool to return it to
			}
		}
	};

	using Lock = std::lock_guard<std::mutex>;

	static std::mutex mPoolMutex;
	static std::shared_ptr<CPool<T>> mPool;

	std::list<std::unique_ptr<T>> mResources;

	CPool() {}
public:
	//Pointer type
	using resource_ptr = std::unique_ptr<T, ResourceDeleter>;

	//Create pool's objects
	void Init(int size);
	void Clear();

	resource_ptr GetRes();
	void AddRes(T* resource);

	static CPool<T>* GetInstance();

	~CPool();
};

//A more short form type name to avoid having to put the CPool<T>::
//Also makes it written in the same way a unique_ptr
// eg. res_ptr<T> is more comparable to unique_ptr<T> than CPool<T>::resource_ptr
template<class T>
using res_ptr = typename CPool<T>::resource_ptr; 