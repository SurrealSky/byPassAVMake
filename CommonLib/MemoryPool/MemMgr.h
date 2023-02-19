#pragma once
#include<typedef.h>
using namespace SurrealTypes;
//#include<Windows.h>
//#ifdef _USRDLL
//#define MEMORY_EXPORTS 1
//#else
//#undef  MEMORY_EXPORTS
//#endif

#ifdef MEMORY_EXPORTS
#define MEMORYEXPORTS_API __declspec(dllexport)
#else
#define MEMORYEXPORTS_API __declspec(dllimport)
#endif

namespace SurrealMemMgr
{

	//内存分配类型
	enum MemAllocType
	{
		TypeStdAllocTAlloc,
		TypeSGIAllocTAlloc,
		TypeSGIVirtualAllocTAlloc,
		TypeSGIHeapAllocTAlloc,
		TypeSGIMTAllocatorAlloc
	};

	class /*MEMORYEXPORTS_API*/ MemMgr
	{
	public:
		static MemMgr &GetInstance();
		void SetDebug2File(bool);
	private:
		MemMgr();
		~MemMgr();
		MemMgr(const MemMgr &);
		const MemMgr &operator=(const MemMgr&);
	private:
		class MemManager;
		MemManager * pImpl;
		bool isDebug2File;
	public:
		STu8* CommonAlloc(const MemAllocType, const STu64 dwSize);
		void CommonDeallocate(const MemAllocType, STu8 *p, const STu64 Size = 0);
	};

	template<typename ... Args>
	std::string string_format(const std::string& format, Args ... args)
	{
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}
}
