#include "TXCommPack.h"
#include<stdlib.h>
#include<WinSock.h>
#include<ObjBase.h>
#include<shlobj.h>   
#include<Windows.h>
#include<WinIoCtl.h>

#pragma   comment(lib,"shell32.lib") 


CTXCommPack::CTXCommPack(void)
{
}

CTXCommPack::CTXCommPack(size_t size)
{
}

CTXCommPack::~CTXCommPack(void)
{
}

void CTXCommPack::AddByte(const STu8 b)
{
	buffer.append(b);
}

void CTXCommPack::PreAddByte(const STu8 b)
{
	buffer.insert(0, b);
}

void CTXCommPack::AddWord(const STu16 data)
{
	buffer.append<STu16>(data);
}

void CTXCommPack::PreAddWord(const STu16 data)
{
	buffer.insert<STu16>(0, data);
}

void CTXCommPack::AddDWord(const STu32 data)
{
	buffer.append<STu32>(data);
}

void CTXCommPack::PreAddDWord(const STu32 data)
{
	buffer.insert<STu32>(0,data);
}

void CTXCommPack::AddDDWord(const STu64 data)
{
	buffer.append<STu64>(data);
}

void CTXCommPack::PreAddDDWord(const STu64 data)
{
	buffer.insert<STu64>(0, data);
}

void CTXCommPack::AddBuf(const STu8 *buf,const STu32 buflen)
{
	buffer.append((STu8*)buf,buflen);
}

void CTXCommPack::PreAddBuf(const STu8 *buf, const STu32 buflen)
{
	buffer.insert(0,(STu8*)buf, buflen);
}

void CTXCommPack::AddBufLenWord()
{
	STu16 len=buffer.size();
	//应该前置插入
	buffer.insert<STu16>(0, buffer.reverse(len));
}

void CTXCommPack::AddBufLenDWord()
{
	STu32 len = buffer.size();
	//应该前置插入
	buffer.insert<STu32>(0, buffer.reverse(len));
}

//插入前置特征码
void CTXCommPack::AddFieldCode(STu16 value)
{
	buffer.insert<STu16>(0,value);
}

void CTXCommPack::GetBufferOut()
{
	buffer.clear();
}

void CTXCommPack::ChangeByte(const STu32 pos,const STu8 byte)
{
	buffer.put<STu8>(pos, (STu8)byte);
}

void CTXCommPack::ChangeWord(const STu32 pos, const STu16 s)
{
	buffer.put<STu16>(pos, s);
}

void CTXCommPack::ChangeDWord(const STu32 pos, const STu32 s)
{
	buffer.put<STu32>(pos, s);
}

void CTXCommPack::ChangeDDWord(const STu32 pos, const STu64 v)
{
	buffer.put<STu64>(pos, v);
}

void CTXCommPack::ChangeBuffer(const STu32 pos, const STu8 *b,const STu32 s)
{
	buffer.put(pos, (STu8*)b,s);
}