// TabSensor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "TabSensor.h"


// CTabSensor

IMPLEMENT_DYNAMIC(CTabSensor, CTabPage)

CTabSensor::CTabSensor()
{
}

CTabSensor::~CTabSensor()
{
}


BEGIN_MESSAGE_MAP(CTabSensor, CTabPage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_GRID_LIST_LBBUTTONDOWN, OnGridCtrlListLButtonDown)
	ON_COMMAND(IDC_GRID_LIST_DBLCLK, OnGridCtrlListDblClk)
END_MESSAGE_MAP()

// CTabSensor ��Ϣ�������

int CTabSensor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ɱ༭����
	OnCreateCtrl(lpCreateStruct);

	return 0;
}    
void CTabSensor::OnDestroy()
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
void CTabSensor::OnCreateCtrl(LPCREATESTRUCT lpCreateStruct)
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
	strColumn = "Nb";
	m_oGridCtrlEdit.InsertColumn (0, strColumn, 50);
	strColumn = "Label";
	m_oGridCtrlEdit.InsertColumn (1, strColumn, 50);
	strColumn = "Min Continuity";
	m_oGridCtrlEdit.InsertColumn (2, strColumn, 50);
	strColumn = "Max Continuity";
	m_oGridCtrlEdit.InsertColumn (3, strColumn, 50);
	strColumn = "Tilt(%)";
	m_oGridCtrlEdit.InsertColumn (4, strColumn, 50);
	strColumn = "Noise(uV)";
	m_oGridCtrlEdit.InsertColumn (5, strColumn, 50);
	strColumn = "LeaKage(Mo)";
	m_oGridCtrlEdit.InsertColumn (6, strColumn, 50);
	strColumn = "SegdCode";
	m_oGridCtrlEdit.InsertColumn (7, strColumn, 150);
	pRow = m_oGridCtrlEdit.CreateRow(m_oGridCtrlEdit.GetColumnCount());
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(2)->SetValue("");
	pRow->GetItem(3)->SetValue("");
	pRow->GetItem(4)->SetValue("");
	pRow->GetItem(5)->SetValue("");
	pRow->GetItem(6)->SetValue("");
	pRow->GetItem(7)->SetValue("");
	// ��ʼ��SegdCode����
	InitSegdCodeGridItem(pRow->GetItem(7));
	m_oGridCtrlEdit.AddRow(pRow, FALSE);

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y + 60;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + lpCreateStruct->cy - 45;
	m_oGridCtrlList.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_LIST);	// �첨���б�
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
	m_oGridCtrlList.InsertColumn (1, strColumn, 50);
	strColumn = "Continuity Min";
	m_oGridCtrlList.InsertColumn (2, strColumn, 50);
	strColumn = "Continuity Max";
	m_oGridCtrlList.InsertColumn (3, strColumn, 50);
	strColumn = "Tilt(%)";
	m_oGridCtrlList.InsertColumn (4, strColumn, 50);
	strColumn = "Noise(uV)";
	m_oGridCtrlList.InsertColumn (5, strColumn, 50);
	strColumn = "LeaKage(Mo)";
	m_oGridCtrlList.InsertColumn (6, strColumn, 50);
	strColumn = "SegdCode";
	m_oGridCtrlList.InsertColumn (7, strColumn, 150);
}

/**
* ��Ӧ��굥���б�
* @param void
* @return void
*/
void CTabSensor::OnGridCtrlListLButtonDown()
{
	OnGridCtrlListLButtonDownA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥��˫���б�
* @param void
* @return void
*/
void CTabSensor::OnGridCtrlListDblClk()
{
	OnGridCtrlListDblClkA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥����ť��ApplyAll
* @param void
* @return void
*/
void CTabSensor::OnBnClickedButtonApplyAll()
{
	CBCGPGridRow* pRow = NULL;
	CSensorData oSensorData;
	CString strData;

	m_pSiteData->m_oSensorList.m_olsSensor.RemoveAll();
	m_pSiteData->m_oSensorList.m_uiCountAll = m_oGridCtrlList.GetRowCount();
	for(int i = 0; i < m_oGridCtrlList.GetRowCount(); i++)
	{
		pRow = m_oGridCtrlList.GetRow(i);
		oSensorData.m_uiNb = pRow->GetData();
		
		strData = pRow->GetItem(1)->GetValue();;
		oSensorData.m_strLabel = strData;

		strData = pRow->GetItem(2)->GetValue();
		oSensorData.m_fContinuityMin = CXMLDOMTool::ConvertStringToFloat(strData);

		strData = pRow->GetItem(3)->GetValue();
		oSensorData.m_fContinuityMax = CXMLDOMTool::ConvertStringToFloat(strData);

		strData = pRow->GetItem(4)->GetValue();
		oSensorData.m_fTilt = CXMLDOMTool::ConvertStringToFloat(strData);

		strData = pRow->GetItem(5)->GetValue();
		oSensorData.m_fNoise = CXMLDOMTool::ConvertStringToFloat(strData);

		strData = pRow->GetItem(6)->GetValue();
		oSensorData.m_fLeaKage = CXMLDOMTool::ConvertStringToFloat(strData);

		strData = pRow->GetItem(7)->GetValue();
		// �õ�SegdCodeID
		oSensorData.m_uiSegdCode = m_pSiteData->GetSegdCodeIDByString(strData);

		m_pSiteData->m_oSensorList.m_olsSensor.AddTail(oSensorData);
	}
}

/**
* ��Ӧ��굥����ť��ApplySensor
* @param void
* @return void
*/
void CTabSensor::OnBnClickedButtonApplySensor()
{
	OnBnClickedButtonApplyAll();
}

/**
* ��Ӧ��굥����ť��Reset
* @param void
* @return void
*/
void CTabSensor::OnBnClickedButtonReset()
{
	CBCGPGridRow* pRow = NULL;
	POSITION pos= NULL;
	CSensorData oSensorData;
	COleVariant oVariant;

	pRow = m_oGridCtrlEdit.GetRow(0);
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(2)->SetValue("");
	pRow->GetItem(3)->SetValue("");
	pRow->GetItem(4)->SetValue("");
	pRow->GetItem(5)->SetValue("");
	pRow->GetItem(6)->SetValue("");
	pRow->GetItem(7)->SetValue("");

	m_oGridCtrlList.RemoveAll();	// �б�
	int iCount = m_pSiteData->m_oSensorList.m_olsSensor.GetCount();
	for(int i = 0; i < iCount; i++)
	{
		pos = m_pSiteData->m_oSensorList.m_olsSensor.FindIndex(i);
		oSensorData = m_pSiteData->m_oSensorList.m_olsSensor.GetAt(pos);
		pRow = m_oGridCtrlList.CreateRow(m_oGridCtrlList.GetColumnCount());
		pRow->SetData(oSensorData.m_uiNb);
		pRow->GetItem(0)->SetValue((int)oSensorData.m_uiNb);

		oVariant = oSensorData.m_strLabel;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(1)->SetValue(oVariant);

		oVariant = oSensorData.m_fContinuityMin;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(2)->SetValue(oVariant);

		oVariant = oSensorData.m_fContinuityMax;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(3)->SetValue(oVariant);

		oVariant = oSensorData.m_fTilt;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(4)->SetValue(oVariant);

		oVariant = oSensorData.m_fNoise;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(5)->SetValue(oVariant);

		oVariant = oSensorData.m_fLeaKage;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(6)->SetValue(oVariant);

		// �õ�SegdCode�ַ���
		CString strSegdCode = m_pSiteData->GetSegdCodeStringByID(oSensorData.m_uiSegdCode);
		oVariant = strSegdCode;
		pRow->GetItem(7)->SetValue(oVariant);

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
void CTabSensor::OnBnClickedButtonAdd()
{
	OnBnClickedButtonAddA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Change
* @param void
* @return void
*/
void CTabSensor::OnBnClickedButtonChange()
{
	OnBnClickedButtonChangeA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Delete
* @param void
* @return void
*/
void CTabSensor::OnBnClickedButtonDelete()
{
	OnBnClickedButtonDeleteA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Reverse
* @param void
* @return void
*/
void CTabSensor::OnBnClickedButtonReverse()
{
	OnBnClickedButtonReverseA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��ʼ��SegdCode��Ԫ��
* @param CBCGPGridItem* pItem SegdCode��Ԫ��
* @return void
*/
void CTabSensor::InitSegdCodeGridItem(CBCGPGridItem* pItem)
{
	POSITION pos;
	CString strSegdCode;
	for(int i = 0; i < m_pSiteData->m_olsSegdCode.GetCount(); i++)
	{
		pos = m_pSiteData->m_olsSegdCode.FindIndex(i);
		strSegdCode = m_pSiteData->m_olsSegdCode.GetAt(pos);
		pItem->AddOption(strSegdCode);
	}
}