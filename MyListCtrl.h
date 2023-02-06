#pragma once
#define MAX_HEADLENGTH 128

// MyListCtrl

class MyListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(MyListCtrl)

public:
	MyListCtrl();
	virtual ~MyListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	void SetStyle(DWORD);
	void SetHeaders(TCHAR [][MAX_HEADLENGTH],int);
	void Clear();
	static int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

struct DATA
{
	BOOL m_fAsc;//是否顺序排序 
    int m_nSortedCol;//当前排序的列
	MyListCtrl *Ctrl;//当前的控件
};

