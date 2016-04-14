#pragma once
#include "IEntity.h"
#include <list>
#include <unordered_map>

enum EMessageType
{
	kMessageInvalid,

	kMessagePlayerInit,
	kMessagePlayerCleanup,

	kMessageProjectileInit,
	kMessageProjectileCleanup
};

struct SMessage
{
	EMessageType type;
	IEntity*     entity;
	int          value;
};

class CMessageQueue
{
public:

	void Send(std::string id, const SMessage& msg);
	void Fetch(std::string id, SMessage& msg);

	//! Gets message queue instance.
	static CMessageQueue* Instance();

private:
	static CMessageQueue mInstance;

	using MessageList = std::list<SMessage>;

	std::unordered_map<std::string, MessageList> mQueue;
};

inline CMessageQueue* CMessageQueue::Instance()
{
	return &mInstance;
}