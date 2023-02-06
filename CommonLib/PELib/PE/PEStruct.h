#pragma once
#include<Windows.h>
#include<string>
#include<map>
#include<vector>
#include<DelayImp.h>
#include<typedef.h>
using namespace SurrealTypes;

#define PE_MODEL
//#define PE_PLUS_MODEL

#define	DosHeader	IMAGE_DOS_HEADER

#ifdef PE_MODEL
#define	NtHeader	IMAGE_NT_HEADERS32
#else
#define	NtHeader	IMAGE_NT_HEADERS64
#endif

#define	MagicValue			WORD
#define SectionHeader		IMAGE_SECTION_HEADER
#define ExportDirectory		IMAGE_EXPORT_DIRECTORY

#ifdef PE_MODEL
#define	ThunkData		IMAGE_THUNK_DATA32
#define	SnapByOrdinal	IMAGE_SNAP_BY_ORDINAL32
#define OrdinalFlag		IMAGE_ORDINAL_FLAG32
#else
#define	ThunkData		IMAGE_THUNK_DATA64
#define	SnapByOrdinal	IMAGE_SNAP_BY_ORDINAL64
#define OrdinalFlag		IMAGE_ORDINAL_FLAG64
#endif

#define	ImportByName	IMAGE_IMPORT_BY_NAME
#define	ImportDescriptor	IMAGE_IMPORT_DESCRIPTOR
#define BaseRelocation		IMAGE_BASE_RELOCATION

#define ResourceDirectory		IMAGE_RESOURCE_DIRECTORY
#define ResourceDirectoryEntry	IMAGE_RESOURCE_DIRECTORY_ENTRY
#define	ResourceDataEntry		IMAGE_RESOURCE_DATA_ENTRY

#ifdef PE_MODEL
#define	TlsDirectory	IMAGE_TLS_DIRECTORY32
#else
#define	TlsDirectory	IMAGE_TLS_DIRECTORY64
#endif

#ifdef PE_MODEL
#define	LoadConfigDirctory	IMAGE_LOAD_CONFIG_DIRECTORY32
#else
#define	LoadConfigDirctory	IMAGE_LOAD_CONFIG_DIRECTORY64
#endif

#define	BoundImportDescriptor	IMAGE_BOUND_IMPORT_DESCRIPTOR
#define	BoundForwarderRef		IMAGE_BOUND_FORWARDER_REF
#define	DebugDirectoryItem		IMAGE_DEBUG_DIRECTORY

#define DEFAULT_FILEALIGNMENT	0x200


//��������
typedef struct _OrdinalFuncs
{
#ifdef PE_MODEL
	DWORD Func;						//RVAi(���⣬������ַ��Զ��4�ֽ�?)
#else
	ULONGLONG Func;	
#endif
	std::string	strFuncName;
}OrdinalFuncs,*POrdinalFuncs;

typedef struct _Export
{
	std::vector<OrdinalFuncs>		mOrdinalFuncsVector;
	std::string						strDllName;
	ExportDirectory					mDirectorys;
}Export,*PExport;

//�������
typedef struct _ThunkItem{
	DWORD	ThunkRVA;
	DWORD	ThunkFOA;
    std::string strFuncName;   
    WORD Ordinal;       //��������
#ifdef PE_MODEL
	DWORD AddrFunc;           //��ź�����ַRVA
#else
	ULONGLONG AddrFunc;	
#endif
	
}ThunkItem,*PThunkItem;

typedef struct _ImportItem
{
	ImportDescriptor	mDescriptor;
	std::string			strDllName;
	std::vector<ThunkItem>	mThunksVector;
}ImportItem,*PImportItem;

//�ض�λ��
typedef struct _ElementItem
{
	WORD	cType:4;
	WORD	wValue:12;
}ElementItem,*PElementItem;

typedef struct _RelocItem
{
	BaseRelocation				mBaseRelocation;
	std::vector<ElementItem>	mSnVector;
}RelocItem,* PRelocItem;

//��Դ��
typedef struct _EntryDataItem
{
	WORD				wId;       //��׼ID
	std::wstring		wstrId;    //�Ǳ�׼�������ַ���
	WORD				wLua;     //��׼����������
	std::wstring		wstrLua;         //�Ǳ�׼�������ַ���
	ResourceDataEntry	mDataEntry;
}EntryDataItem,*PEntryDataItem;

typedef struct _ResourceItem
{
	WORD					dwType;			//��׼��Դ���ͣ�0����Ǳ�׼��Դ����0�����׼��Դ��ʾ��
	std::wstring			wstrType;		//�Ǳ�׼��Դ�����ַ���
	std::vector<EntryDataItem>	mEntryDatasVector;
}ResourceItem,*PResourceItem;

//�ӳ��������
typedef struct _DelayItem
{
	ImgDelayDescr mDescriptor;
	std::vector<ThunkItem>	mThunksVector;
	std::string			strDllName; 
}DelayItem,*PDelayItem;

//�󶨵������
typedef struct _BoundForwarderRefItem
{
	std::string			strDllName;
	BoundForwarderRef	mBoundForwarderRef;
}BoundForwarderRefItem,*PBoundForwarderRefItem;

typedef struct _BoundItem
{
	BoundImportDescriptor mBoundImportDescriptor;
	std::string	strDllName;
	std::vector<BoundForwarderRefItem>	mBoundForwarderRefsVector;
}BoundItem,*PBoundItem;

//�������ݽṹ����
typedef struct _Overlay
{
	bool		isExist;    //�Ƿ���ڸ�������
	ULONGLONG	dwOffset;		//��������ƫ��(FOA)
	size_t		dwSize;    //�������ݴ�С
}Overlay,*POverlay;

//PEͷ����
typedef struct {
	//�ļ��洢ӳ��
	DosHeader	mDosHeader;
	NtHeader	mNtHeader;
	MagicValue	wMagic;
	std::vector<SectionHeader> mSectionsVector;
	Overlay			mOverlay;

	//�ṹ������
	Export						mExport;			//������     
	std::vector<ImportItem>		mImportsVector;		//�����
	std::vector<ResourceItem>	mResourcesVector;	//��Դ��
	std::vector<RelocItem>		mRelocsVector;		//�ض�λ��
	
	std::vector<DelayItem>		mDelaysVector;		//�ӳٵ����
	TlsDirectory				mTlsDirrctory;		//TLS��
	LoadConfigDirctory			mLoadConfigDirctory;	//�������ñ�
	std::vector<BoundItem>		mBoundsVector;			//�󶨵����
	std::vector<DebugDirectoryItem>	mDebugDirectorysVector;//������Ϣ��
} pe_file_t;

typedef struct {
	std::string path;
	STu8 *pVirMem;
	size_t size;
	pe_file_t pe;
} pe_ctx_t;