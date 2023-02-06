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
	bool Protect1A();	//��һ���A���鱾13.3�ڣ�����AddPatch�������������������Ի���
	bool Protect2A();	//�ڶ����A���鱾21�£�EXE���ܣ���ǻ�ԭIAT�������������ν���
	bool Protect3A();	//yoda��
	bool Protect4A();	//�������
	bool test();
public:
	bool WriteCtx2VirMem();
};