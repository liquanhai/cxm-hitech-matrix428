// TabTestSensor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "TabTestSensor.h"


// CTabTestSensor

IMPLEMENT_DYNAMIC(CTabTestSensor, CTabPage)

CTabTestSensor::CTabTestSensor()
{
}

CTabTestSensor::~CTabTestSensor()
{
}


BEGIN_MESSAGE_MAP(CTabTestSensor, CTabPage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_GRID_LIST_LBBUTTONDOWN, OnGridCtrlListLButtonDown)
	ON_COMMAND(IDC_GRID_LIST_DBLCLK, OnGridCtrlListDblClk)
END_MESSAGE_MAP()

// CTabTestSensor ��Ϣ�������

int CTabTestSensor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ɱ༭����
	OnCreateCtrl(lpCreateStruct);

	return 0;
}    
void CTabTestSensor::OnDestroy()
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
void CTabTestSensor::OnCreateCtrl(LPCREATESTRUCT lpCreateStruct)
{
	CRect oRect;
	CString strColumn;
	CBCGPGridRow* pRow = NULL;

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + 46;
	m_oGridCtrlEdit.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_EDIT);	// �첨��
	m_oGridCtrlEdit.m_iRowHeightAdd = 5;
	m_oGridCtrlEdit.EnableColumnAutoSize(TRUE);
	m_oGridCtrlEdit.EnableDragHeaderItems(FALSE);
	m_oGridCtrlEdit.EnableHeader(TRUE, 0);
	strColumn = "Test Nb";
	m_oGridCtrlEdit.InsertColumn (0, strColumn, 50);
	strColumn = "Test Type";
	m_oGridCtrlEdit.InsertColumn (1, strColumn, 80);
	strColumn = "Recorded";
	m_oGridCtrlEdit.InsertColumn (2, strColumn, 30);
	strColumn = "Absolute Spread";
	m_oGridCtrlEdit.InsertColumn (3, strColumn, 100);
	pRow = m_oGridCtrlEdit.CreateRow(m_oGridCtrlEdit.GetColumnCount());
	pRow->GetItem(0)->SetValue("");
	// ��ʼ��TestType����
	InitTestTypeGridItem(pRow->GetItem(1));
	pRow->ReplaceItem (2, new CBCGPGridCheckItem (FALSE));
	pRow->GetItem(3)->SetBackgroundColor(RGB(192, 192, 192));
	m_oGridCtrlEdit.AddRow(pRow, FALSE);

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y + 60;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + lpCreateStruct->cy - 250;
	m_oGridCtrlList.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_LIST);	// �첨���б�
	m_oGridCtrlList.m_iRowHeightAdd = 5;
	m_oGridCtrlList.ShowVertScrollBar();
	m_oGridCtrlList.EnableColumnAutoSize(TRUE);
	m_oGridCtrlList.EnableDragHeaderItems(FALSE);
	m_oGridCtrlList.EnableHeader(FALSE, 0);
	m_oGridCtrlList.SetReadOnly(TRUE);
	m_oGridCtrlList.SetWholeRowSel(TRUE);
	m_oGridCtrlList.SetSingleSel(TRUE);
	strColumn = "Test Nb";
	m_oGridCtrlList.InsertColumn (0, strColumn, 50);
	strColumn = "Test Type";
	m_oGridCtrlList.InsertColumn (1, strColumn, 80);
	strColumn = "Recorded";
	m_oGridCtrlList.InsertColumn (2, strColumn, 30);
	strColumn = "Absolute Spread";
	m_oGridCtrlList.InsertColumn (3, strColumn, 100);

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->cy - 220;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + lpCreateStruct->cy - 45;	
	m_oStaticAbsoluteSpread.Create("Absolute Spread:", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_GROUPBOX | WS_DISABLED, oRect, this, 0);	// �����������
	oRect.left = oRect.left + 10;
	oRect.top = oRect.top + 25;
	oRect.right = oRect.right - 10;
	oRect.bottom = oRect.bottom - 10;
	m_oEditAbsoluteSpread.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		oRect, this, IDC_EDIT_ABSOLUTESPREAD);	// �������б༭��
}

/**
* ��Ӧ��굥���б�
* @param void
* @return void
*/
void CTabTestSensor::OnGridCtrlListLButtonDown()
{
	OnGridCtrlListLButtonDownA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥��˫���б�
* @param void
* @return void
*/
void CTabTestSensor::OnGridCtrlListDblClk()
{
	OnGridCtrlListDblClkA(&m_oGridCtrlEdit, &m_oGridCtrlList);

	CBCGPGridRow* pRow = m_oGridCtrlList.GetCurSel();
	if(NULL != pRow)
	{
		COleVariant oVariant = pRow->GetItem(3)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		CString AbsoluteSpread = oVariant;
		AbsoluteSpread.Replace(";", "\r\n");
		GetDlgItem(IDC_EDIT_ABSOLUTESPREAD)->SetWindowText(AbsoluteSpread);
	}
}

/**
* ��Ӧ��굥����ť��Apply
* @param void
* @return void
*/
void CTabTestSensor::OnBnClickedButtonApply()
{
	CBCGPGridRow* pRow = NULL;
	CTestProject* pTestProject = NULL;
	CString strData;

	m_pSiteData->m_oTestProjectListSensor.OnClose();
	m_pSiteData->m_oTestProjectListSensor.m_uiCountAll = m_oGridCtrlList.GetRowCount();
	for(int i = 0; i < m_oGridCtrlList.GetRowCount(); i++)
	{
		pRow = m_oGridCtrlList.GetRow(i);

		pTestProject = new CTestProject;
		pTestProject->m_uiProjectType = 2;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		pTestProject->m_uiTestNb = pRow->GetData();

		COleVariant oVariant = pRow->GetItem(2)->GetValue();
		oVariant.ChangeType(VT_UINT);
		if(0 == oVariant.uintVal)
		{
			pTestProject->m_uiRecordResult = 0;
		}
		else
		{
			pTestProject->m_uiRecordResult = 1;
		}

		strData = pRow->GetItem(3)->GetValue();
		pTestProject->m_strAbsoluteSpread = strData;

		CTestRequest oTestRequest;
		strData = pRow->GetItem(1)->GetValue();
		oTestRequest.m_uiType = m_pSiteData->GetTestTypeIDByString(strData);

		pTestProject->m_olsTestRequest.AddTail(oTestRequest);
		pTestProject->m_uiCountAll = 1;

		m_pSiteData->m_oTestProjectListSensor.m_olsTestProject.AddTail(pTestProject);
	}
}

/**
* ��Ӧ��굥����ť��Reset
* @param void
* @return void
*/
void CTabTestSensor::OnBnClickedButtonReset()
{
	CBCGPGridRow* pRow = NULL;
	POSITION pos = NULL;
	CTestProject* pTestProject = NULL;
	CTestRequest oTestRequest;
	COleVariant oVariantBool;
	COleVariant oVariantString;

	pRow = m_oGridCtrlEdit.GetRow(0);
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	oVariantBool = "FALSE";
	oVariantBool.ChangeType(VT_BOOL);
	pRow->GetItem(2)->SetValue(oVariantBool);
	pRow->GetItem(3)->SetValue("");

	GetDlgItem(IDC_EDIT_ABSOLUTESPREAD)->SetWindowText("");

	m_oGridCtrlList.RemoveAll();	// �б�
	int iCount = m_pSiteData->m_oTestProjectListSensor.m_olsTestProject.GetCount();
	for(int i = 0; i < iCount; i++)
	{
		pos = m_pSiteData->m_oTestProjectListSensor.m_olsTestProject.FindIndex(i);
		pTestProject = m_pSiteData->m_oTestProjectListSensor.m_olsTestProject.GetAt(pos);

		pos = pTestProject->m_olsTestRequest.FindIndex(0);
		oTestRequest = pTestProject->m_olsTestRequest.GetAt(pos);

		pRow = m_oGridCtrlList.CreateRow(m_oGridCtrlList.GetColumnCount());
		pRow->SetData(pTestProject->m_uiTestNb);

		oVariantString = (long)pTestProject->m_uiTestNb;
		oVariantString.ChangeType(VT_BSTR);
		pRow->GetItem(0)->SetValue(oVariantString);

		oVariantString = m_pSiteData->GetTestTypeStringByID(oTestRequest.m_uiType);
		oVariantString.ChangeType(VT_BSTR);
		pRow->GetItem(1)->SetValue(oVariantString);

		if(0 == pTestProject->m_uiRecordResult)
		{
			oVariantBool = "FALSE";
		}
		if(1 == pTestProject->m_uiRecordResult)
		{
			oVariantBool = "TRUE";
		}
		oVariantBool.ChangeType(VT_BOOL);
		pRow->GetItem(2)->SetValue(oVariantBool);

		oVariantString = pTestProject->m_strAbsoluteSpread;
		pRow->GetItem(3)->SetValue(oVariantString);

		m_oGridCtrlList.AddRow(pRow, FALSE);
	}
	m_oGridCtrlEdit.AdjustLayout();
	m_oGridCtrlList.AdjustLayout();
}

/**
* ��Ӧ��굥����ť��GO
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CTabTestSensor::OnBnClickedButtonGO()
{
	CBCGPGridRow* pRow = m_oGridCtrlList.GetCurSel();
	if(NULL != pRow)
	{
		CString strData;
		m_uiTestNb = pRow->GetData();
		return true;
	}
	AfxMessageBox("Please Select A Record.", MB_OK | MB_ICONSTOP);
	return false;
}

/**
* ��Ӧ��굥����ť��Add
* @param void
* @return void
*/
void CTabTestSensor::OnBnClickedButtonAdd()
{
	CString strAbsoluteSpread;
	GetDlgItem(IDC_EDIT_ABSOLUTESPREAD)->GetWindowText(strAbsoluteSpread);
	strAbsoluteSpread.Replace("\r\n", ";");
	COleVariant oVariantString = strAbsoluteSpread;
	m_oGridCtrlEdit.GetRow(0)->GetItem(3)->SetValue(oVariantString);

	OnBnClickedButtonAddA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Change
* @param void
* @return void
*/
void CTabTestSensor::OnBnClickedButtonChange()
{
	CString strAbsoluteSpread;
	GetDlgItem(IDC_EDIT_ABSOLUTESPREAD)->GetWindowText(strAbsoluteSpread);
	strAbsoluteSpread.Replace("\r\n", ";");
	COleVariant oVariantString = strAbsoluteSpread;
	m_oGridCtrlEdit.GetRow(0)->GetItem(3)->SetValue(oVariantString);

	OnBnClickedButtonChangeA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Delete
* @param void
* @return void
*/
void CTabTestSensor::OnBnClickedButtonDelete()
{
	OnBnClickedButtonDeleteA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Clear
* @param void
* @return void
*/
void CTabTestSensor::OnBnClickedButtonClear()
{
	OnBnClickedButtonClearA(&m_oGridCtrlList);
}

/**
* // ��ʼ��TestType��Ԫ��
* @param CBCGPGridItem* pItem Gain��Ԫ��
* @return void
*/
void CTabTestSensor::InitTestTypeGridItem(CBCGPGridItem* pItem)
{
	POSITION pos;
	CString strTestType;
	for(int i = 0; i < m_pSiteData->m_olsTestTypeSensor.GetCount(); i++)
	{
		pos = m_pSiteData->m_olsTestTypeSensor.FindIndex(i);
		strTestType = m_pSiteData->m_olsTestTypeSensor.GetAt(pos);
		pItem->AddOption(strTestType);
	}
}