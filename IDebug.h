#pragma once
#include <vector>
#include <mutex>

//! A really bad helper that calls Open and Close after the scope
// ends.
class IDebugScope
{
public:
	IDebugScope(const char* filename);
	~IDebugScope();
};

namespace IDebug
{

	enum DebugMessageCode
	{
		kMessage_OK =      1 << 0,
		kMessage_Queued =  1 << 1,
		kMessage_Warning = 1 << 2,
		kMessage_Error =   1 << 3

	};

	enum DebugCode
	{
		kError_OperationFailed = 0,
		kError_InvalidMemory,
		kError_IssueNETTIK,
		kError_Unknown,
		
		kWarning_Unknown,
	};

	struct IMessageEntry
	{
		std::string mMessage;
		std::string mOrigin;
		DebugMessageCode mCode;
	};

	//! Initialises the output file.
	void Open(
		const char* filename
	);

	//! Closes the output file.
	void Close();
	
	//! Alias for logging message entries.
	inline void Log(
		IMessageEntry& entry
	);

	//! Prints to console and to file if in debug mode.
	void LogRaw(
		const char* str,
		const char* origin = "[debug]",
		DebugMessageCode msgCode = kMessage_OK
	);

	//! Ouputs a string to file and console.
	//  Don't call this in loops or performance reliant code.
	//  This writes to an output file.
	void Log(
		const char* fmt, ...
	);

	
	//! Prints to console and terminates
	//  current thread from executing.
	void Error(
		const char* str,
		DebugCode errorType = kError_Unknown
	);
};

using IDebug::Log;
using IDebug::Error;