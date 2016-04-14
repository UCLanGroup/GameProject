#include "MessageQueue.h"

CMessageQueue CMessageQueue::mInstance;

void CMessageQueue::Send(std::string id, const SMessage& msg)
{

	auto list = mQueue.find(id);

	if (list == mQueue.end())
		list = mQueue.insert(std::begin(mQueue), std::make_pair(id, MessageList()));

	list->second.push_back(msg);
}

void CMessageQueue::Fetch(std::string id, SMessage& msg)
{
	auto list = mQueue.find(id);

	if (list == mQueue.end() || list->second.size() == 0)
	{
		msg.type = kMessageInvalid;
		return;
	}

	msg = list->second.front();
	list->second.pop_front();

	if (list->second.size() == 0)
		mQueue.erase(list);
}