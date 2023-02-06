#pragma once
#ifdef PELIB_EXPORTS
#define PELIB_EXPORTS_API __declspec(dllexport)
#else
#define PELIB_EXPORTS_API __declspec(dllimport)
#endif

#include"PEStruct.h"
#include<pack\ByteBuffer.h>

extern class PeProtect;

class PELIB_EXPORTS_API PEMake {
public:
	PEMake(void);
	virtual ~PEMake(void);
private:
	PeProtect *ptrPeProtect;
public:
	pe_ctx_t	mPeCtx;
public:
	bool isAnalysised();
	bool PELoadFile(const char *lpPath,const char *lpModel);
	void PEUnload();
	bool CheckPESig();
	bool Analysis();
	void SetAnalysised(bool isAnalysised);
public:
	unsigned int RvaToFoa(unsigned int rva);
	unsigned int FoaToRva(unsigned int foa);
	STu32 SectionAlignmentSize(STu32);
	STu32 FileAlignmentSize(STu32);
	bool ClsRelocDataDirectory();
	bool AddSectionToEnd(const STu8*, const STu8*, const STu32,const STu32);
	bool EncryptImportTable();
	bool FindCodeByPeFile(const STu8*, const STu32, ByteBuffer&);
public:
	bool AddPatch(const STu8 *pName, const void *pPatch, const STu32 dwSize, const STu32 mOffset, const STu32 nopbytes);
	bool AddPatchAuto2OEP(const STu8*, const void *, const STu32, const STu32 nopbytes);
public:
	bool Protect1A();	//第一类壳A（书本13.3节）调用AddPatch函数，补丁技术，弹对话框
	bool Protect2A();	//第二类壳A（书本21章）EXE加密，外壳还原IAT，并对所有区段解密
	bool Protect3A();	//yoda壳
	bool Protect4A();	//虚拟机壳
	bool test();
public:
	bool WriteCtx2VirMem();
};