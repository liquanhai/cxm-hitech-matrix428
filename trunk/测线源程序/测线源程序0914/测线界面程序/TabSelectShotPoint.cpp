#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "TabSelectShotPoint.h"


// CTabSpreadAbsolute

IMPLEMENT_DYNAMIC(CTabSelectShotPoint, CTabPage)

CTabSelectShotPoint::CTabSelectShotPoint()
{
	m_pSiteData = NULL;
	m_pTabSpreadAbsolute = NULL;
	m_uiTestNb = 0;
}

CTabSelectShotPoint::~CTabSelectShotPoint()
{
}


BEGIN_MESSAGE_MAP(CTabSelectShotPoint, CTabPage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_GRID_LIST_LBBUTTONDOWN, OnGridCtrlListLButtonDown)
	ON_COMMAND(IDC_GRID_LIST_DBLCLK, OnGridCtrlListDblClk)
END_MESSAGE_MAP()

// CTabSpreadAbsolute ��Ϣ�������

int CTabSelectShotPoint::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ɱ༭����
	OnCreateCtrl(lpCreateStruct);

	return 0;
}    
void CTabSelectShotPoint::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_oGridCtrlEdit.RemoveAll();	// ������
	m_oGridCtrlList.RemoveAll();	// �б�
	// ɾ��������
	m_oGridCtrlEdit.DeleteAllColumns();
	m_oGridCtrlList.DeleteAllColumns();
}

/**
* ���ɱ༭����
* @param LPCREATESTRUCT lpCreateStruct
* @return void
*/
void CTabSelectShotPoint::OnCreateCtrl(LPCREATESTRUCT lpCreateStruct)
{
	CRect oRect;
	CString strColumn;
	CBCGPGridRow* pRow = NULL;

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = oRect.top + 46;
	m_oGridCtrlEdit.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_EDIT);	// �༭��
	m_oGridCtrlEdit.m_iRowHeightAdd = 5;
	m_oGridCtrlEdit.EnableColumnAutoSize(TRUE);
	m_oGridCtrlEdit.EnableDragHeaderItems(FALSE);
	m_oGridCtrlEdit.EnableHeader(TRUE, 0);
	strColumn = "Shot Point ID";
	m_oGridCtrlEdit.InsertColumn (0, strColumn, 50);
	strColumn = "Shot Point Nb";
	m_oGridCtrlEdit.InsertColumn (1, strColumn, 80);
	pRow = m_oGridCtrlEdit.CreateRow(m_oGridCtrlEdit.GetColumnCount());
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(1)->SetBackgroundColor(RGB(192, 192, 192));
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
	strColumn = "Shot Point ID";
	m_oGridCtrlList.InsertColumn (0, strColumn, 50);
	strColumn = "Shot Point Nb";
	m_oGridCtrlList.InsertColumn (1, strColumn, 80);
}

/**
* ��Ӧ��굥���б�
* @param void
* @return void
*/
void CTabSelectShotPoint::OnGridCtrlListLButtonDown()
{
	OnGridCtrlListLButtonDownA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥��˫���б�
* @param void
* @return void
*/
void CTabSelectShotPoint::OnGridCtrlListDblClk()
{
	OnGridCtrlListDblClkA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}
// ����
void CTabSelectShotPoint::OnReset(void)
{
	CBCGPGridRow* pRow = NULL;
	COleVariant oVariantBool;
	COleVariant oVariantString;
	map<unsigned int, unsigned int>::iterator  iter;
	pRow = m_oGridCtrlEdit.GetRow(0);
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");

	m_oGridCtrlList.RemoveAll();	// �б�
	for (iter = m_pSiteData->m_oShotPointMap.m_oShotPointMap.begin();
		iter != m_pSiteData->m_oShotPointMap.m_oShotPointMap.end(); iter++)
	{
		pRow = m_oGridCtrlList.CreateRow(m_oGridCtrlList.GetColumnCount());
		pRow->SetData(iter->second);

		oVariantString = (ULONGLONG)iter->second;
		oVariantString.ChangeType(VT_BSTR);
		pRow->GetItem(0)->SetValue(oVariantString);

		oVariantString = (ULONGLONG)iter->first;
		oVariantString.ChangeType(VT_BSTR);
		pRow->GetItem(1)->SetValue(oVariantString);

		m_oGridCtrlList.AddRow(pRow, FALSE);
	}
	m_oGridCtrlEdit.AdjustLayout();
	m_oGridCtrlList.AdjustLayout();
}
