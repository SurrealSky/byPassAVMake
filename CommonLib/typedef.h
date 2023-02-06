//
// Created by wzh.
//

#ifndef NDKAPPECG_TYPEDEF_H
#define NDKAPPECG_TYPEDEF_H

namespace SurrealTypes
{
#if defined(_MSC_VER)
	//
	// Windows/Visual C++
	//
	typedef unsigned __int8		STbool;
	typedef unsigned __int8     STu8;
	typedef signed __int8		STs8;
	typedef signed __int16      STs16;
	typedef unsigned __int16    STu16;
	typedef signed __int32      STs32;
	typedef unsigned __int32    STu32;
	typedef signed __int64      STs64;
	typedef unsigned __int64    STu64;
	typedef float				STfp32;
	typedef double				STfp64;
#else
	typedef unsigned char  STbool;
	typedef unsigned char  STu8;
	typedef char           STs8;
	typedef unsigned short STu16;
	typedef signed short   STs16;
	typedef unsigned int   STu32;
	typedef signed int     STs32;
	typedef signed long long	STs64;
	typedef unsigned long long	STu64;
	typedef float          STfp32;
	typedef double         STfp64;
#endif

#define TRUE 1
#define FALSE 0

#define STswab64(x) ((x&0x00000000000000ff) << 56|(((x&0x000000000000ff00) << 40)|((x&0x0000000000ff0000) << 24)|((x&0x00000000ff000000) <<  8)|((x&0x000000ff00000000) >>  8)|((x&0x0000ff0000000000) >> 24)|((x&0x00ff000000000000) >> 40)|((x&0xff00000000000000) >> 56)))
#define STswab32(x) ((x&0x000000ff) << 24 | (x&0x0000ff00) << 8 | (x&0x00ff0000) >> 8 | (x&0xff000000) >> 24)
#define STswab16(x) ((x&0x00ff) << 8 | (x&0xff00) >> 8)
}

#endif


