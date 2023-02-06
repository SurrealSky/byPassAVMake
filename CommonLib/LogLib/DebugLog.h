#pragma once
#include<Windows.h>
#include <typedef.h>
#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

namespace SurrealDebugLog
{
	//
	//NOTICE
	//
	template<typename ... Args>
	std::string string_format(const std::string& format, Args ... args)
	{
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}

//#define Dbg

	void DebugLog(const std::string &OutputString);

	void DebugLog(const std::string& lpTag, const std::string OutputString);

	void DebugLogHex(const std::string &lpTag, std::string &OutputString, SurrealTypes::STu32 lpOutputStringLen);


}

