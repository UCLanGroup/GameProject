#include "IDebug.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdarg>

static std::mutex    s_outputMutex;
static std::ofstream s_outputFile;
static std::vector<IDebug::IMessageEntry>  s_queuedMessages;
/***********************************/
IDebugScope::IDebugScope(const char* filename)
{
	IDebug::Open(filename);
}
IDebugScope::~IDebugScope()
{
	IDebug::Close();
}
/***********************************/
void ClearQueue()
{
	if (!s_outputFile.is_open())
		return;

	for (auto it = s_queuedMessages.begin(); it != s_queuedMessages.end(); )
	{
		Log(*it);
		s_queuedMessages.erase(it);
	}
}

void IDebug::Open(const char* filename)
{
	// Prevent opening the file multiple times.
	if (s_outputFile.is_open())
		return;

	s_outputFile.open(filename, std::fstream::app);

	if (s_outputFile.is_open() && s_queuedMessages.size() > 0)
		ClearQueue();
	else if (!s_outputFile.is_open())
		LogRaw("Failed to open log file.", __FUNCTION__, DebugMessageCode::kMessage_Error);
}

void IDebug::Close()
{
	if (s_outputFile.is_open())
	{
		s_outputFile.close();
	}
}


void IDebug::Log(IDebug::IMessageEntry& entry)
{
	LogRaw(entry.mMessage.c_str(), entry.mOrigin.c_str(), entry.mCode);
}

void IDebug::Log(const char* fmt, ...)
{
	char buffer[1024];

	va_list arguments;
	va_start(arguments, fmt);
	vsprintf_s(buffer, sizeof(buffer), fmt, arguments);
	va_end(arguments);

	// This is disgusting.
	std::string msg(buffer);
	LogRaw(msg.c_str());
}

void IDebug::LogRaw(const char* msg, const char* origin, DebugMessageCode msgCode)
{
	// Stop multiple threads from writing at the same time
	// causing strange console output.
	std::lock_guard<std::mutex> _(s_outputMutex);
	
	// Dispatch any queued messages.
	// Not a fan of this being inside Log, but w/e.
	// -- note: commented out due as the mutex will
	//          probably get stuck in deadlock if the
	//          file fails to open.

	//if (s_queuedMessages.size() > 0)
	//	ClearQueue();

	std::stringstream out;
	out << origin << " " << msg << std::endl;

	std::string out_str;
	out_str = out.str();

	if (s_outputFile.is_open())
		s_outputFile << (char)msgCode << "|" << out_str; // uint8_t

#ifdef _DEBUG
	std::cout << out_str;
#endif
}

void IDebug::Error(const char* msg, IDebug::DebugCode errorType)
{

	Log(msg, "[error]", kMessage_Error);
#ifdef _DEBUG

	switch (errorType)
	{
	case kError_InvalidMemory:
	case kError_OperationFailed:
		std::exit(3);
		break;

	default:
		std::abort();
	}

#else

	std::exit(3);

#endif
}