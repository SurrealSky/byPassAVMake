// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H

#include<PELib/PE/PEMake.h>
#ifdef _DEBUG
#pragma comment(lib, "CommonLib\\PELib\\bind\\PELib.lib")
#else
#pragma comment(lib, "CommonLib\\PELib\\bin\\PELib.lib")
#endif

#include<MemoryPool/MemMgr.h>
using namespace SurrealMemMgr;

#ifdef _DEBUG
#pragma comment(lib, "CommonLib\\MemoryPool\\bind\\MemMgr.lib")
#else
#pragma comment(lib, "CommonLib\\MemoryPool\\bin\\MemMgr.lib")
#endif

#include<CTree.h>
#include<disasm/disasm.h>

typedef struct _AddrNode
{
	ulong ip;
	ulong addrconst;
	ulong offset;
	_AddrNode()
	{
		memset(this, 0, sizeof(_AddrNode));
	}
}AddrNode, * PAddrNode;