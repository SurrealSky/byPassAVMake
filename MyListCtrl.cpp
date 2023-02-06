// MyListCtrl.cpp : ʵ���ļ�
//

#include "pch.h"
#include "MyListCtrl.h"

// MyListCtrl


IMPLEMENT_DYNAMIC(MyListCtrl, CMFCListCtrl)

MyListCtrl::MyListCtrl()
{

}

MyListCtrl::~MyListCtrl()
{
}

BEGIN_MESSAGE_MAP(MyListCtrl, CMFCListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &MyListCtrl::OnLvnColumnclick)
	ON_NOTIFY_REFLECT(NM_CLICK, &MyListCtrl::OnNMClick)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &MyListCtrl::OnLvnItemchanged)
END_MESSAGE_MAP()

// MyListCtrl ��Ϣ�������

void MyListCtrl::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	LONG   lStyle; 
	lStyle=GetWindowLong(this->m_hWnd,GWL_STYLE);//��ȡ��ǰ�������� 
	lStyle   &=   ~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	lStyle|=(LVS_REPORT);   //������ʾ��ʽΪ����ʽ 
	SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle);//���ô�������

	this->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	CMFCListCtrl::PreSubclassWindow();
}

void MyListCtrl::SetHeaders(TCHAR Array[][MAX_HEADLENGTH],int number)
{
	this->DeleteAllItems();
	CRect rect;
	this->GetWindowRect(&rect);
	for(int i=0;i<number;i++)
	{
		LVCOLUMN co;
		co.mask=LVCF_TEXT|LVCF_FMT|LVCF_WIDTH;
		co.fmt=LVCFMT_CENTER;
		co.cx=rect.Width()/number;
		co.pszText=Array[i];
		co.cchTextMax=sizeof(co.pszText);
		co.iSubItem=i;
		co.iOrder=i;
		this->InsertColumn(i,&co);
	}
}

int CALLBACK MyListCtrl::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	DATA* pV=static_cast<DATA*>((PVOID)lParamSort); 
     
	int col=pV->m_nSortedCol;//���������ݸ�col,�����жϵ���˵ڼ���  
    //ȡ����ַ���  

	int nItem1,nItem2;
	LVFINDINFO FindInfo;
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=lParam1;
	nItem1=pV->Ctrl->FindItem(&FindInfo,-1);
	FindInfo.lParam=lParam2;
	nItem2=pV->Ctrl->FindItem(&FindInfo,-1);

	if((nItem1==-1)||(nItem2==-1))
	{
	   return 0;
	}
    CString strItem1, strItem2;
	strItem1=pV->Ctrl->GetItemText(lParam1,col);  
    strItem2=pV->Ctrl->GetItemText(lParam2,col);//���Ҫ�Ƚϵ��ַ�
    int iCompRes=0;
    switch(pV->m_nSortedCol) 
    { 
		case(1):
		case(2):
			{
				if(strItem1.CompareNoCase(strItem2)>0)
					iCompRes=1;
				else if(strItem1.CompareNoCase(strItem2)==0)
					iCompRes=0;
				else
					iCompRes=-1;
			}break;
		default: 
			{
				//Ĭ������
				if(StrToInt(strItem1)>StrToInt(strItem2))
					iCompRes=1;
				else if(StrToInt(strItem1)==StrToInt(strItem2))
					iCompRes=0;
				else
					iCompRes=-1;
			}
			break; 
    } 
    ////���ݵ�ǰ������ʽ���е��� 
    if(pV->m_fAsc) 
        return iCompRes; 
    else 
        return iCompRes*-1; 
}

void MyListCtrl::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);  
	DATA da={0};
	da.Ctrl=this;
	//��������ʽ
    if( pNMLV->iSubItem == da.m_nSortedCol ) 
        da.m_fAsc = !da.m_fAsc; 
    else 
    { 
        da.m_fAsc = TRUE; 
        da.m_nSortedCol = pNMLV->iSubItem; 
    } 

	int    i=this->GetItemCount();                //   �����亯���ǹؼ�Ŷ��������
    while(i--) this->SetItemData(i,i);   
    //���������� 
    this->SortItems( MyListCtrl::ListCompare,(DWORD_PTR)&da);
	*pResult = 0;
}

void MyListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	*pResult = 0;	
}

void MyListCtrl::Clear()
{
	this->DeleteAllItems();
	//ɾ���ؼ���ͷ
	int cols=this->GetHeaderCtrl().GetItemCount();
	for(int i=cols-1;i>=0;i--)
	{
		this->DeleteColumn(i);
	}
}

void MyListCtrl::SetStyle(DWORD style)
{

	LONG   lStyle; 
	lStyle=GetWindowLong(this->m_hWnd,GWL_STYLE);//��ȡ��ǰ��������  
	lStyle|=(style);
	SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle);//���ô�������
	 
	//this->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
}

void MyListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	*pResult = 0;
}
