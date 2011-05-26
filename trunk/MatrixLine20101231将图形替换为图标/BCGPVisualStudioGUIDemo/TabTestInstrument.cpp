// TabTestInstrument.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "TabTestInstrument.h"


// CTabTestInstrument

IMPLEMENT_DYNAMIC(CTabTestInstrument, CTabPage)

CTabTestInstrument::CTabTestInstrument()
{
}

CTabTestInstrument::~CTabTestInstrument()
{
}


BEGIN_MESSAGE_MAP(CTabTestInstrument, CTabPage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_GRID_LIST_LBBUTTONDOWN, OnGridCtrlListLButtonDown)
	ON_COMMAND(IDC_GRID_LIST_DBLCLK, OnGridCtrlListDblClk)
END_MESSAGE_MAP()

// CTabTestInstrument ��Ϣ�������

int CTabTestInstrument::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ɱ༭����
	OnCreateCtrl(lpCreateStruct);

	return 0;
}    
void CTabTestInstrument::OnDestroy()
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
void CTabTestInstrument::OnCreateCtrl(LPCREATESTRUCT lpCreateStruct)
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
	m_oGridCtrlEdit.InsertColumn (0, strColumn, 30);
	strColumn = "Test Type";
	m_oGridCtrlEdit.InsertColumn (1, strColumn, 80);
	strColumn = "Gain";
	m_oGridCtrlEdit.InsertColumn (2, strColumn, 30);
	strColumn = "Record Length";
	m_oGridCtrlEdit.InsertColumn (3, strColumn, 50);
	strColumn = "Recorded";
	m_oGridCtrlEdit.InsertColumn (4, strColumn, 30);
	strColumn = "Auxiliary Descr";
	m_oGridCtrlEdit.InsertColumn (5, strColumn, 50);
	strColumn = "Absolute Spread";
	m_oGridCtrlEdit.InsertColumn (6, strColumn, 50);
	pRow = m_oGridCtrlEdit.CreateRow(m_oGridCtrlEdit.GetColumnCount());
	pRow->GetItem(0)->SetValue("");
	// ��ʼ��TestType����
	InitTestTypeGridItem(pRow->GetItem(1));
	// ��ʼ��Gain��Ԫ��
	InitGainGridItem(pRow->GetItem(2));
	pRow->GetItem(3)->SetValue("");
	pRow->ReplaceItem (4, new CBCGPGridCheckItem (FALSE));
	pRow->GetItem(5)->SetValue("");
	pRow->GetItem(5)->AllowEdit(FALSE);
	pRow->GetItem(5)->SetBackgroundColor(RGB(192, 192, 192));
	pRow->GetItem(6)->SetValue("");
	pRow->GetItem(6)->AllowEdit(FALSE);
	pRow->GetItem(6)->SetBackgroundColor(RGB(192, 192, 192));
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
	m_oGridCtrlList.InsertColumn (0, strColumn, 30);
	strColumn = "Test Type";
	m_oGridCtrlList.InsertColumn (1, strColumn, 80);
	strColumn = "Gain";
	m_oGridCtrlList.InsertColumn (2, strColumn, 30);
	strColumn = "Record Length";
	m_oGridCtrlList.InsertColumn (3, strColumn, 50);
	strColumn = "Recorded";
	m_oGridCtrlList.InsertColumn (4, strColumn, 30);
	strColumn = "Auxiliary Descr";
	m_oGridCtrlList.InsertColumn (5, strColumn, 50);
	strColumn = "Absolute Spread";
	m_oGridCtrlList.InsertColumn (6, strColumn, 50);

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->cy - 220;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx / 2 - 10;
	oRect.bottom = lpCreateStruct->y + lpCreateStruct->cy - 45;	
	m_oStaticAuxiliaryDescr.Create("Auxiliary Descr:", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_GROUPBOX | WS_DISABLED, oRect, this, 0);	// ���������

	oRect.left = oRect.left + 10;
	oRect.top = oRect.top + 25;
	oRect.right = oRect.right - 10;
	oRect.bottom = oRect.bottom - 10;
	m_oEditAuxiliaryDescr.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		oRect, this, IDC_EDIT_AUXILIARYDESCR);	// �������༭��

	oRect.left = lpCreateStruct->x + lpCreateStruct->cx / 2 + 10;
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
void CTabTestInstrument::OnGridCtrlListLButtonDown()
{
	OnGridCtrlListLButtonDownA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥��˫���б�
* @param void
* @return void
*/
void CTabTestInstrument::OnGridCtrlListDblClk()
{
	OnGridCtrlListDblClkA(&m_oGridCtrlEdit, &m_oGridCtrlList);

	CBCGPGridRow* pRow = m_oGridCtrlList.GetCurSel();
	if(NULL != pRow)
	{
		COleVariant oVariant = pRow->GetItem(5)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		CString strAuxiliaryDescr = oVariant;
		GetDlgItem(IDC_EDIT_AUXILIARYDESCR)->SetWindowText(strAuxiliaryDescr);

		oVariant = pRow->GetItem(6)->GetValue();
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
void CTabTestInstrument::OnBnClickedButtonApply()
{
	CBCGPGridRow* pRow = NULL;
	CTestProject* pTestProject = NULL;
	CString strData;

	m_pSiteData->m_oTestProjectListInstrument.OnClose();
	m_pSiteData->m_oTestProjectListInstrument.m_uiCountAll = m_oGridCtrlList.GetRowCount();
	for(int i = 0; i < m_oGridCtrlList.GetRowCount(); i++)
	{
		pRow = m_oGridCtrlList.GetRow(i);

		pTestProject = new CTestProject;
		pTestProject->m_uiProjectType = 1;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		pTestProject->m_uiTestNb = pRow->GetData();

		strData = pRow->GetItem(3)->GetValue();
		pTestProject->m_uiRecordLength = CXMLDOMTool::ConvertStringToUnsignedInt(strData);

		COleVariant oVariant = pRow->GetItem(4)->GetValue();
		oVariant.ChangeType(VT_UINT);
		if(0 == oVariant.uintVal)
		{
			pTestProject->m_uiRecordResult = 0;
		}
		else
		{
			pTestProject->m_uiRecordResult = 1;
		}

		strData = pRow->GetItem(5)->GetValue();
		pTestProject->m_strAuxiliaryDescr = strData;

		strData = pRow->GetItem(6)->GetValue();
		pTestProject->m_strAbsoluteSpread = strData;

		CTestRequest oTestRequest;
		strData = pRow->GetItem(1)->GetValue();
		oTestRequest.m_uiType = m_pSiteData->GetTestTypeIDByString(strData);
		strData = pRow->GetItem(2)->GetValue();
		oTestRequest.m_uiGain = m_pSiteData->GetGainByString(strData);

		pTestProject->m_olsTestRequest.AddTail(oTestRequest);
		pTestProject->m_uiCountAll = 1;

		m_pSiteData->m_oTestProjectListInstrument.m_olsTestProject.AddTail(pTestProject);
	}
}

/**
* ��Ӧ��굥����ť��Reset
* @param void
* @return void
*/
void CTabTestInstrument::OnBnClickedButtonReset()
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
	pRow->GetItem(2)->SetValue("");
	pRow->GetItem(3)->SetValue("");
	oVariantBool = "FALSE";
	oVariantBool.ChangeType(VT_BOOL);
	pRow->GetItem(4)->SetValue(oVariantBool);
	pRow->GetItem(5)->SetValue("");
	pRow->GetItem(6)->SetValue("");

	GetDlgItem(IDC_EDIT_AUXILIARYDESCR)->SetWindowText("");
	GetDlgItem(IDC_EDIT_ABSOLUTESPREAD)->SetWindowText("");

	m_oGridCtrlList.RemoveAll();	// �б�
	int iCount = m_pSiteData->m_oTestProjectListInstrument.m_olsTestProject.GetCount();
	for(int i = 0; i < iCount; i++)
	{
		pos = m_pSiteData->m_oTestProjectListInstrument.m_olsTestProject.FindIndex(i);
		pTestProject = m_pSiteData->m_oTestProjectListInstrument.m_olsTestProject.GetAt(pos);

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

		oVariantString = m_pSiteData->GetGainStringByGainData(oTestRequest.m_uiGain);
		oVariantString.ChangeType(VT_BSTR);
		pRow->GetItem(2)->SetValue(oVariantString);

		oVariantString = (long)pTestProject->m_uiRecordLength;
		oVariantString.ChangeType(VT_BSTR);
		pRow->GetItem(3)->SetValue(oVariantString);

		if(0 == pTestProject->m_uiRecordResult)
		{
			oVariantBool = "FALSE";
		}
		if(1 == pTestProject->m_uiRecordResult)
		{
			oVariantBool = "TRUE";
		}
		oVariantBool.ChangeType(VT_BOOL);
		pRow->GetItem(4)->SetValue(oVariantBool);

		oVariantString = pTestProject->m_strAuxiliaryDescr;
		pRow->GetItem(5)->SetValue(oVariantString);

		oVariantString = pTestProject->m_strAbsoluteSpread;
		pRow->GetItem(6)->SetValue(oVariantString);

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
bool CTabTestInstrument::OnBnClickedButtonGO()
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
void CTabTestInstrument::OnBnClickedButtonAdd()
{
	CString strAuxiliaryDescr;
	GetDlgItem(IDC_EDIT_AUXILIARYDESCR)->GetWindowText(strAuxiliaryDescr);
	COleVariant oVariantString = strAuxiliaryDescr;
	m_oGridCtrlEdit.GetRow(0)->GetItem(5)->SetValue(oVariantString);

	CString strAbsoluteSpread;
	GetDlgItem(IDC_EDIT_ABSOLUTESPREAD)->GetWindowText(strAbsoluteSpread);
	strAbsoluteSpread.Replace("\r\n", ";");
	oVariantString = strAbsoluteSpread;
	m_oGridCtrlEdit.GetRow(0)->GetItem(6)->SetValue(oVariantString);

	OnBnClickedButtonAddA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Change
* @param void
* @return void
*/
void CTabTestInstrument::OnBnClickedButtonChange()
{
	CString strAuxiliaryDescr;
	GetDlgItem(IDC_EDIT_AUXILIARYDESCR)->GetWindowText(strAuxiliaryDescr);
	COleVariant oVariantString = strAuxiliaryDescr;
	m_oGridCtrlEdit.GetRow(0)->GetItem(5)->SetValue(oVariantString);

	CString strAbsoluteSpread;
	GetDlgItem(IDC_EDIT_ABSOLUTESPREAD)->GetWindowText(strAbsoluteSpread);
	strAbsoluteSpread.Replace("\r\n", ";");
	oVariantString = strAbsoluteSpread;
	m_oGridCtrlEdit.GetRow(0)->GetItem(6)->SetValue(oVariantString);

	OnBnClickedButtonChangeA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Delete
* @param void
* @return void
*/
void CTabTestInstrument::OnBnClickedButtonDelete()
{
	OnBnClickedButtonDeleteA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Clear
* @param void
* @return void
*/
void CTabTestInstrument::OnBnClickedButtonClear()
{
	OnBnClickedButtonClearA(&m_oGridCtrlList);
}

/**
* ��ʼ��Gain��Ԫ��
* @param CBCGPGridItem* pItem Gain��Ԫ��
* @return void
*/
void CTabTestInstrument::InitGainGridItem(CBCGPGridItem* pItem)
{
	POSITION pos;
	CString strGain;
	for(int i = 0; i < m_pSiteData->m_olsGain.GetCount(); i++)
	{
		pos = m_pSiteData->m_olsGain.FindIndex(i);
		strGain = m_pSiteData->m_olsGain.GetAt(pos);
		pItem->AddOption(strGain);
	}
}

/**
* // ��ʼ��TestType��Ԫ��
* @param CBCGPGridItem* pItem Gain��Ԫ��
* @return void
*/
void CTabTestInstrument::InitTestTypeGridItem(CBCGPGridItem* pItem)
{
	POSITION pos;
	CString strTestType;
	for(int i = 0; i < m_pSiteData->m_olsTestTypeInstrument.GetCount(); i++)
	{
		pos = m_pSiteData->m_olsTestTypeInstrument.FindIndex(i);
		strTestType = m_pSiteData->m_olsTestTypeInstrument.GetAt(pos);
		pItem->AddOption(strTestType);
	}
}