// TabSpreadAbsolute.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "TabSpreadAbsolute.h"


// CTabSpreadAbsolute

IMPLEMENT_DYNAMIC(CTabSpreadAbsolute, CTabPage)

CTabSpreadAbsolute::CTabSpreadAbsolute()
{
}

CTabSpreadAbsolute::~CTabSpreadAbsolute()
{
}


BEGIN_MESSAGE_MAP(CTabSpreadAbsolute, CTabPage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_GRID_LIST_LBBUTTONDOWN, OnGridCtrlListLButtonDown)
	ON_COMMAND(IDC_GRID_LIST_DBLCLK, OnGridCtrlListDblClk)
END_MESSAGE_MAP()

// CTabSpreadAbsolute ��Ϣ�������

int CTabSpreadAbsolute::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ɱ༭����
	OnCreateCtrl(lpCreateStruct);

	return 0;
}    
void CTabSpreadAbsolute::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_oGridCtrlEdit.RemoveAll();	// ������
	m_oGridCtrlList.RemoveAll();	// �б�
	m_olsNb.RemoveAll();	// �����Ŷ���
}

/**
* ���ɱ༭����
* @param LPCREATESTRUCT lpCreateStruct
* @return void
*/
void CTabSpreadAbsolute::OnCreateCtrl(LPCREATESTRUCT lpCreateStruct)
{
	CRect oRect;
	CString strColumn;
	CBCGPGridRow* pRow = NULL;

	oRect.left = lpCreateStruct->x;
	oRect.top = 160;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = oRect.top + 46;
	m_oGridCtrlEdit.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_EDIT);	// �༭��
	m_oGridCtrlEdit.m_iRowHeightAdd = 5;
	m_oGridCtrlEdit.EnableColumnAutoSize(TRUE);
	m_oGridCtrlEdit.EnableDragHeaderItems(FALSE);
	m_oGridCtrlEdit.EnableHeader(TRUE, 0);
	strColumn = "Nb";
	m_oGridCtrlEdit.InsertColumn (0, strColumn, 50);
	strColumn = "Label";
	m_oGridCtrlEdit.InsertColumn (1, strColumn, 80);
	strColumn = "Absolute Spread";
	m_oGridCtrlEdit.InsertColumn (2, strColumn, 100);
	pRow = m_oGridCtrlEdit.CreateRow(m_oGridCtrlEdit.GetColumnCount());
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(2)->SetBackgroundColor(RGB(192, 192, 192));
	m_oGridCtrlEdit.AddRow(pRow, FALSE);

	oRect.top = oRect.bottom + 14;
	oRect.bottom = lpCreateStruct->y + lpCreateStruct->cy - 45;	
	m_oGridCtrlList.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_LIST);	// �б�
	m_oGridCtrlList.m_iRowHeightAdd = 5;
	m_oGridCtrlList.ShowVertScrollBar();
	m_oGridCtrlList.EnableColumnAutoSize(TRUE);
	m_oGridCtrlList.EnableDragHeaderItems(FALSE);
	m_oGridCtrlList.EnableHeader(FALSE, 0);
	m_oGridCtrlList.SetReadOnly(TRUE);
	m_oGridCtrlList.SetWholeRowSel(TRUE);
	m_oGridCtrlList.SetSingleSel(TRUE);
	strColumn = "Nb";
	m_oGridCtrlList.InsertColumn (0, strColumn, 50);
	strColumn = "Label";
	m_oGridCtrlList.InsertColumn (1, strColumn, 80);
	strColumn = "Absolute Spread";
	m_oGridCtrlList.InsertColumn (2, strColumn, 100);

	oRect.top = lpCreateStruct->y;
	oRect.bottom = 150;
	m_oEditAbsoluteSpread.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		oRect, this, 1);	// �������б༭��
}

/**
* ��Ӧ��굥���б�
* @param void
* @return void
*/
void CTabSpreadAbsolute::OnGridCtrlListLButtonDown()
{
	OnGridCtrlListLButtonDownA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥��˫���б�
* @param void
* @return void
*/
void CTabSpreadAbsolute::OnGridCtrlListDblClk()
{
	OnGridCtrlListDblClkA(&m_oGridCtrlEdit, &m_oGridCtrlList);

	CBCGPGridRow* pRow = m_oGridCtrlList.GetCurSel();
	if(NULL != pRow)
	{
		COleVariant oVariant = pRow->GetItem(2)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		CString AbsoluteSpread = oVariant;
		AbsoluteSpread.Replace(";", "\r\n");
		m_oEditAbsoluteSpread.SetWindowText(AbsoluteSpread);
	}
}

/**
* ��Ӧ��굥����ť��Apply
* @param void
* @return void
*/
void CTabSpreadAbsolute::OnBnClickedButtonApply()
{
	CBCGPGridRow* pRow = NULL;
	CSpreadAbsoluteData oSpread;
	CString strData;

	m_pSiteData->m_oSpreadAbsoluteList.OnClose();
	m_pSiteData->m_oSpreadAbsoluteList.m_uiCountAll = m_oGridCtrlList.GetRowCount();
	for(int i = 0; i < m_oGridCtrlList.GetRowCount(); i++)
	{
		pRow = m_oGridCtrlList.GetRow(i);

		oSpread.m_uiNb = pRow->GetData();
		strData = pRow->GetItem(1)->GetValue();
		oSpread.m_strLabel = strData;

		strData = pRow->GetItem(2)->GetValue();
		oSpread.m_strSpread = strData;

		m_pSiteData->m_oSpreadAbsoluteList.m_olsSpreadAbsolute.AddTail(oSpread);
	}
}

/**
* ��Ӧ��굥����ť��Reset
* @param void
* @return void
*/
void CTabSpreadAbsolute::OnBnClickedButtonReset()
{
	CBCGPGridRow* pRow = NULL;
	POSITION pos = NULL;
	CSpreadAbsoluteData oSpread;
	COleVariant oVariantBool;
	COleVariant oVariantString;

	pRow = m_oGridCtrlEdit.GetRow(0);
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(2)->SetValue("");

	m_oEditAbsoluteSpread.SetWindowText("");

	m_oGridCtrlList.RemoveAll();	// �б�
	int iCount = m_pSiteData->m_oSpreadAbsoluteList.m_olsSpreadAbsolute.GetCount();
	for(int i = 0; i < iCount; i++)
	{
		pos = m_pSiteData->m_oSpreadAbsoluteList.m_olsSpreadAbsolute.FindIndex(i);
		oSpread = m_pSiteData->m_oSpreadAbsoluteList.m_olsSpreadAbsolute.GetAt(pos);

		pRow = m_oGridCtrlList.CreateRow(m_oGridCtrlList.GetColumnCount());
		pRow->SetData(oSpread.m_uiNb);

		oVariantString = (long)oSpread.m_uiNb;
		oVariantString.ChangeType(VT_BSTR);
		pRow->GetItem(0)->SetValue(oVariantString);

		oVariantString = oSpread.m_strLabel;
		pRow->GetItem(1)->SetValue(oVariantString);

		oVariantString = oSpread.m_strSpread;
		pRow->GetItem(2)->SetValue(oVariantString);

		m_oGridCtrlList.AddRow(pRow, FALSE);
	}
	m_oGridCtrlEdit.AdjustLayout();
	m_oGridCtrlList.AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Add
* @param void
* @return void
*/
void CTabSpreadAbsolute::OnBnClickedButtonAdd()
{
	CString strAbsoluteSpread;
	m_oEditAbsoluteSpread.GetWindowText(strAbsoluteSpread);
	strAbsoluteSpread.Replace("\r\n", ";");
	COleVariant oVariantString = strAbsoluteSpread;
	m_oGridCtrlEdit.GetRow(0)->GetItem(2)->SetValue(oVariantString);

	OnBnClickedButtonAddA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Change
* @param void
* @return void
*/
void CTabSpreadAbsolute::OnBnClickedButtonChange()
{
	CString strAbsoluteSpread;
	m_oEditAbsoluteSpread.GetWindowText(strAbsoluteSpread);
	strAbsoluteSpread.Replace("\r\n", ";");
	COleVariant oVariantString = strAbsoluteSpread;
	m_oGridCtrlEdit.GetRow(0)->GetItem(2)->SetValue(oVariantString);

	OnBnClickedButtonChangeA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Delete
* @param void
* @return void
*/
void CTabSpreadAbsolute::OnBnClickedButtonDelete()
{
	OnBnClickedButtonDeleteA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}