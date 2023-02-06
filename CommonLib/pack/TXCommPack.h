#pragma once
#include<pack\ByteBuffer.h>

#define BUFFER_SIZE	0x200
#pragma pack(1)
class CTXCommPack
{
public:
	CTXCommPack(void);
	CTXCommPack(size_t);
	virtual ~CTXCommPack(void);
public:
	void AddByte(STu8);
	void PreAddByte(STu8);
	void AddWord(STu16);
	void PreAddWord(STu16);
	void AddDWord(STu32);
	void PreAddDWord(const STu32);
	void AddDDWord(const STu64);
	void PreAddDDWord(const STu64);
	void AddBuf(const STu8 *,const STu32);
	void PreAddBuf(const STu8 *, const STu32);
	void AddBufLenWord();
	void AddBufLenDWord();
	void AddFieldCode(STu16);
	void ChangeByte(const STu32,const STu8);
	void ChangeWord(const STu32,const STu16);
	void ChangeDWord(const STu32,const STu32);
	void ChangeDDWord(const STu32, const STu64);
	void ChangeBuffer(const STu32,const STu8*,const STu32);
	void GetBufferOut();
public:
	ByteBuffer buffer;
};
