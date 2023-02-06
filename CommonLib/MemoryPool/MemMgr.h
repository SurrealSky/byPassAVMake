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
		int GetState();
	private:
		MemMgr();
		~MemMgr();
		MemMgr(const MemMgr &);
		const MemMgr &operator=(const MemMgr&);
	private:
		class MemManager;
		MemManager * pImpl;
	public:
		STu8* CommonAlloc(const MemAllocType, const STu64 dwSize);
		void CommonDeallocate(const MemAllocType, STu8 *p, const STu64 Size = 0);
	};
}
