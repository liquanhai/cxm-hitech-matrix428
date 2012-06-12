// TabTestLimit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "TabTestLimit.h"


// CTabTestLimit

IMPLEMENT_DYNAMIC(CTabTestLimit, CTabPage)

CTabTestLimit::CTabTestLimit()
{
}

CTabTestLimit::~CTabTestLimit()
{
}


BEGIN_MESSAGE_MAP(CTabTestLimit, CTabPage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_GRID_LIST_LBBUTTONDOWN, OnGridCtrlListLButtonDown)
	ON_COMMAND(IDC_GRID_LIST_DBLCLK, OnGridCtrlListDblClk)
END_MESSAGE_MAP()

// CTabTestLimit ��Ϣ�������

int CTabTestLimit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ɱ༭����
	OnCreateCtrl(lpCreateStruct);

	return 0;
}    
void CTabTestLimit::OnDestroy()
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
void CTabTestLimit::OnCreateCtrl(LPCREATESTRUCT lpCreateStruct)
{
	CRect oRect;
	CString strColumn;
	CBCGPGridRow* pRow = NULL;

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + 46;
	m_oGridCtrlEdit.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_EDIT);	// �༭��
	m_oGridCtrlEdit.m_iRowHeightAdd = 5;
	m_oGridCtrlEdit.EnableColumnAutoSize(TRUE);
	m_oGridCtrlEdit.EnableDragHeaderItems(FALSE);
	m_oGridCtrlEdit.EnableHeader(TRUE, 0);
	strColumn = "Nb";
	m_oGridCtrlEdit.InsertColumn (0, strColumn, 10);
	strColumn = "Descr";
	m_oGridCtrlEdit.InsertColumn (1, strColumn, 80);
	strColumn = "Unit";
	m_oGridCtrlEdit.InsertColumn (2, strColumn, 80);
	strColumn = "TestType";
	m_oGridCtrlEdit.InsertColumn (3, strColumn, 35);
	strColumn = "Limit";
	m_oGridCtrlEdit.InsertColumn (4, strColumn, 35);

	pRow = m_oGridCtrlEdit.CreateRow(m_oGridCtrlEdit.GetColumnCount());
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(0)->AllowEdit(FALSE);
	pRow->GetItem(0)->SetBackgroundColor(RGB(192, 192, 192));
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(1)->AllowEdit(FALSE);
	pRow->GetItem(1)->SetBackgroundColor(RGB(192, 192, 192));
	pRow->GetItem(2)->SetValue("");
	pRow->GetItem(2)->AllowEdit(FALSE);
	pRow->GetItem(2)->SetBackgroundColor(RGB(192, 192, 192));
	pRow->GetItem(3)->SetValue("");
	pRow->GetItem(3)->AllowEdit(FALSE);
	pRow->GetItem(3)->SetBackgroundColor(RGB(192, 192, 192));
	pRow->GetItem(4)->SetValue("");
	m_oGridCtrlEdit.AddRow(pRow, FALSE);

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y + 60;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
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
	m_oGridCtrlList.InsertColumn (0, strColumn, 10);
	strColumn = "Descr";
	m_oGridCtrlList.InsertColumn (1, strColumn, 80);
	strColumn = "Unit";
	m_oGridCtrlList.InsertColumn (2, strColumn, 80);
	strColumn = "TestType";
	m_oGridCtrlList.InsertColumn (3, strColumn, 35);
	strColumn = "Limit";
	m_oGridCtrlList.InsertColumn (4, strColumn, 35);
}

/**
* ��Ӧ��굥���б�
* @param void
* @return void
*/
void CTabTestLimit::OnGridCtrlListLButtonDown()
{
	OnGridCtrlListDblClkA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥��˫���б�
* @param void
* @return void
*/
void CTabTestLimit::OnGridCtrlListDblClk()
{

}

/**
* ��Ӧ��굥����ť��Apply
* @param void
* @return void
*/
void CTabTestLimit::OnBnClickedButtonApply()
{
	CBCGPGridRow* pRow = NULL;
	CTestLimitList* pTestLimitList = NULL;
	CString strData;
	COleVariant oVariant;
	POSITION pos = NULL;

	if(1 == m_uiAim)	// ���Զ��� 1-������2-�첨��
	{
		pTestLimitList = &m_pSiteData->m_oTestLimitListInstrument;
	}
	else if(2 == m_uiAim)	// ���Զ��� 1-������2-�첨��
	{
		pTestLimitList = &m_pSiteData->m_oTestLimitListSensor;
	}

	for(int i = 0; i < m_oGridCtrlList.GetRowCount(); i++)
	{	
		pRow = m_oGridCtrlList.GetRow(i);

		pos = pTestLimitList->m_olsTestLimit.FindIndex(i);
		CTestLimitData& oTestLimitData = pTestLimitList->m_olsTestLimit.GetAt(pos);		

		strData = pRow->GetItem(4)->GetValue();
		oTestLimitData.m_fLimit = CXMLDOMTool::ConvertStringToFloat(strData);
	}
}

/**
* ��Ӧ��굥����ť��Reset
* @param void
* @return void
*/
void CTabTestLimit::OnBnClickedButtonReset()
{
	CBCGPGridRow* pRow = NULL;
	POSITION pos= NULL;
	CTestLimitList* pTestLimitList = NULL;
	COleVariant oVariant;
	COleVariant oVariantString;

	if(1 == m_uiAim)	// ���Զ��� 1-������2-�첨��
	{
		pTestLimitList = &m_pSiteData->m_oTestLimitListInstrument;
	}
	else if(2 == m_uiAim)	// ���Զ��� 1-������2-�첨��
	{
		pTestLimitList = &m_pSiteData->m_oTestLimitListSensor;
	}

	pRow = m_oGridCtrlEdit.GetRow(0);
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(2)->SetValue("");
	pRow->GetItem(3)->SetValue("");
	pRow->GetItem(4)->SetValue("");

	m_oGridCtrlList.RemoveAll();	// �б�
	int iCount = pTestLimitList->m_olsTestLimit.GetCount();
	for(int i = 0; i < iCount; i++)
	{
		pos = pTestLimitList->m_olsTestLimit.FindIndex(i);
		CTestLimitData& oTestLimitData = pTestLimitList->m_olsTestLimit.GetAt(pos);
		pRow = m_oGridCtrlList.CreateRow(m_oGridCtrlList.GetColumnCount());

		oVariant = (long)oTestLimitData.m_uiNb;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(0)->SetValue(oVariant);

		oVariant = oTestLimitData.m_strDesc;
		pRow->GetItem(1)->SetValue(oVariant);

		oVariant = oTestLimitData.m_strUnit;
		pRow->GetItem(2)->SetValue(oVariant);

		oVariantString = m_pSiteData->GetTestTypeStringByID(oTestLimitData.m_uiType);
		oVariantString.ChangeType(VT_BSTR);
		pRow->GetItem(3)->SetValue(oVariantString);

		oVariant = oTestLimitData.m_fLimit;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(4)->SetValue(oVariant);

		m_oGridCtrlList.AddRow(pRow, FALSE);
	}
	m_oGridCtrlEdit.AdjustLayout();
	m_oGridCtrlList.AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Change
* @param void
* @return void
*/
void CTabTestLimit::OnBnClickedButtonChange()
{
	OnBnClickedButtonChangeB(&m_oGridCtrlEdit, &m_oGridCtrlList);
}