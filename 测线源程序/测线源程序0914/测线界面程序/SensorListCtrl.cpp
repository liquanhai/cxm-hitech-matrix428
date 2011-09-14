// SensorListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "SensorListCtrl.h"

// CSensorListCtrl

IMPLEMENT_DYNAMIC(CSensorListCtrl, CBCGPGridCtrl)

CSensorListCtrl::CSensorListCtrl()
{

}

CSensorListCtrl::~CSensorListCtrl()
{
}

BEGIN_MESSAGE_MAP(CSensorListCtrl, CBCGPGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSensorListCtrl ��Ϣ�������

int CSensorListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	EnableMarkSortedColumn(TRUE);
	EnableHeader(TRUE, BCGP_GRID_HEADER_SORT);
	EnableRowHeader(FALSE);
	EnableLineNumbers(FALSE);
	SetClearInplaceEditOnEnter(FALSE);
	EnableInvertSelOnCtrl();
	SetReadOnly(TRUE);
	SetWholeRowSel(TRUE);

	// �����ֳ�������ݶ���
	OnLoadSiteDataAndFillToChannelList();

	return 0;
}

void CSensorListCtrl::OnDestroy()
{
	CBCGPGridCtrl::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
//	SaveState (_T("BasicGrid"));
}


// �ֳ����ݶ����ʼ��
void CSensorListCtrl::OnSiteDataInit()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_pSiteData = &pMainFrame->m_oSiteData;
}

// �����ֳ�������ݶ���
void CSensorListCtrl::OnLoadSiteDataAndFillToChannelList()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	// ���ɱ��ͷ
	CreateColumTitle();

	CChannelSetupData* pChannelSetupData = NULL;
	CBCGPGridRow* pRow = NULL;
	for (unsigned int nRow = 0; nRow < m_pSiteData->m_oChannelList.m_uiCountUsed; nRow++)
	{
		pRow = CreateRow(GetColumnCount());
		pChannelSetupData = m_pSiteData->m_oChannelList.GetChannelByIndex(nRow);
		// ����һ�е�����
		SetRowData(pRow, pChannelSetupData);
		AddRow(pRow, FALSE);
	}
	//	LoadState (_T("BasicGrid"));
	AdjustLayout ();
}

// ���¼����ֳ��������
void CSensorListCtrl::OnReloadSiteDataCMD()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();

	CChannelSetupData* pChannelSetupData = NULL;
	CBCGPGridRow* pRow = NULL;
	for (unsigned int nRow = 0; nRow < m_pSiteData->m_oChannelList.m_uiCountUsed; nRow++)
	{
		// ��䱾������
		pChannelSetupData = m_pSiteData->m_oChannelList.GetChannelByIndex(nRow);
		pRow = FindRowByData(pChannelSetupData->m_uiIP, FALSE);
		if(NULL != pRow)	// �ҵ���
		{
			SetRowData(pRow, pChannelSetupData);	// ����һ�е�����
		}
		else
		{
			pRow = CreateRow(GetColumnCount());
			// ����һ�е�����
			SetRowData(pRow, pChannelSetupData);
			AddRow(pRow, FALSE);
		}
	}
	// ɾ��û���õ�����
	for(int i = (GetRowCount() - 1); i >= 0; i--)
	{
		pRow = GetRow(i);
		if(NULL != pRow)	// �ҵ���
		{
			if(FALSE == m_pSiteData->m_oChannelList.IfIndexExistInMap(pRow->GetData()))
			{
				RemoveRow(i, FALSE);
			}
		}
		else
		{
			TRACE1("SensorList�в�����%d", i);
		}
	}
	//	LoadState (_T("BasicGrid"));
	AdjustLayout ();
}

// Ϊ�µĲ�������ˢ����ʾ
void CSensorListCtrl::OnRefreshForNewTestValue(int iTestType)
{
	unsigned int uiIP = 0;
	CChannelSetupData* pChannelSetupData = NULL;
	CBCGPGridRow* pRow = NULL;
	while(true)
	{
		if(TRUE == m_pSiteData->m_olsIPSensor.IsEmpty())
		{
			break;
		}
		uiIP = m_pSiteData->m_olsIPSensor.RemoveHead();
		if(TRUE == m_pSiteData->m_oChannelList.m_oChannelMap.Lookup(uiIP, pChannelSetupData))
		{
			pRow = FindRowByData(uiIP, FALSE);
			if(NULL != pRow)	// �ҵ���
			{
				SetRowDataOfTestByTestType(pRow, pChannelSetupData, iTestType);
				// �жϣ������¼Ӽ첨���ĳ�ʼ����
				if(45 != iTestType)
				{
					SetRowDataOfTestByTestType(pRow, pChannelSetupData, 40);
				}
			}
		}
	}	
}

// ���ɱ��ͷ
void CSensorListCtrl::CreateColumTitle()
{
	unsigned int nColumns = 0;
	CString strColumn;

	strColumn = "Serial Nb";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Line Nb";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Point Nb";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Point Index";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Sensor Type";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Segd Code";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "IP";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Jump Channel";
	InsertColumn (nColumns, strColumn, 100);
	nColumns++;

	strColumn = "Mute";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Test";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Auto Test";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Resistance";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Leakage";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Noise";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Tilt";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Tilt Model";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;
}

/**
* ����һ�е�����
* @param CBCGPGridRow* pRow ��ָ��
* @param CChannelSetupData* pChannelSetupData ���ָ��
* @return void
*/
void CSensorListCtrl::SetRowData(CBCGPGridRow* pRow, CChannelSetupData* pChannelSetupData)
{
	SetRowDataOfBase(pRow, pChannelSetupData);
	SetRowDataOfTest(pRow, pChannelSetupData);
}

/**
* ����һ�еĻ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CChannelSetupData* pChannelSetupData ���ָ��
* @return void
*/
void CSensorListCtrl::SetRowDataOfBase(CBCGPGridRow* pRow, CChannelSetupData* pChannelSetupData)
{
	pRow->SetData(pChannelSetupData->m_uiIP);

	int nItems = 0;
	pRow->GetItem(nItems)->SetValue(pChannelSetupData->m_uiSN, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pChannelSetupData->m_uiNbLine, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pChannelSetupData->m_uiNbPoint, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pChannelSetupData->m_uiNbChannel, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pChannelSetupData->m_uiSensorNb, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pChannelSetupData->m_uiSegdCode, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pChannelSetupData->m_uiIP, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pChannelSetupData->m_bJumped), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pChannelSetupData->m_bMute), FALSE);
}

/**
* ����һ�еĲ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CSensorListCtrl::SetRowDataOfTest(CBCGPGridRow* pRow, CChannelSetupData* pChannelSetupData)
{
	SetRowDataOfTestByTestType(pRow, pChannelSetupData, 40);
	SetRowDataOfTestByTestType(pRow, pChannelSetupData, 45);
	SetRowDataOfTestByTestType(pRow, pChannelSetupData, 15);
	SetRowDataOfTestByTestType(pRow, pChannelSetupData, 14);
	SetRowDataOfTestByTestType(pRow, pChannelSetupData, 1);
	SetRowDataOfTestByTestType(pRow, pChannelSetupData, 20);
	SetRowDataOfTestByTestType(pRow, pChannelSetupData, 21);
}

/**
* ����һ�еĲ������ݣ����ݲ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CChannelSetupData* pChannelSetupData ���ָ��
* @return void
*/
void CSensorListCtrl::SetRowDataOfTestByTestType(CBCGPGridRow* pRow, CChannelSetupData* pChannelSetupData, int iTestType)
{
	unsigned int nItems = 0;

	switch(iTestType)
	{
		// Ұ�����
	case 15:
		nItems = 11;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byResistanceCheck, pChannelSetupData->m_fResistanceValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byResistanceCheck));
		break;
		// Ұ��©��
	case 14:
		nItems = 12;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byLeakageCheck, pChannelSetupData->m_fLeakageValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byLeakageCheck));
		break;
		// Ұ������
	case 1:
		nItems = 13;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byNoiseCheck, pChannelSetupData->m_fNoiseValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byNoiseCheck));
		break;
		// Ұ����б��
	case 20:
		nItems = 14;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byTiltCheck, pChannelSetupData->m_fTiltValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byTiltCheck));
		break;
		// Ұ����б��ģ��
	case 21:
		nItems = 15;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byTiltModelCheck, pChannelSetupData->m_fTiltModelValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byTiltModelCheck));
		break;
		// ȫ��Ұ�����
	case 40:
		nItems = 9;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byCheck), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byCheck));
		break;
		// �¼Ӽ첨���ĳ�ʼ����
	case 45:
		nItems = 10;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byOnFieldCheck), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byOnFieldCheck));
		break;
	}
}

/**
* �õ�������ɫ�����ݲ��Լ����
* @param byte byCheck �����
* @return void
*/
COLORREF CSensorListCtrl::GetColourByCheck(byte byCheck)
{
	COLORREF m_crColor = RGB(255, 255, 255);	// ��ɫ
	switch(byCheck)
	{
	case 0:	// 0��δ����
		m_crColor = RGB(0, 0, 255);	// ��ɫ
		break;
	case 1:	// 1�����Ժϸ�
		m_crColor = RGB(0, 255, 0);	// ��ɫ
		break;
	case 2:	// 2�����Բ��ϸ�
		m_crColor = RGB(255, 0, 0);	// ��ɫ
		break;
	case 3:	// 3�����ź�
		m_crColor = RGB(255, 255, 0);	// ��ɫ
		break;
	}
	return m_crColor;
}

/**
* �õ�������֣������߼�ֵ
* @param bool bValue �߼�ֵ
* @return COleVariant �������
*/
COleVariant CSensorListCtrl::GetMarkerStringByLogic(bool bValue)
{
	COleVariant oVariant;
	CString strValue = "";
	if(true == bValue)
	{
		strValue = "��";
	}
	oVariant = strValue;
	return oVariant;
}

/**
* �õ����Խ������
* @param byte byValue ���Խ��
* @param float m_fValue ����ֵ
* @return COleVariant ���Խ������
*/
COleVariant CSensorListCtrl::GetTestResultString(byte byValue, float m_fValue)
{
	COleVariant oVariant;
	CString strValue = "";
	switch(byValue)
	{
	case 0:
		strValue = "No Test";
		break;
	case 1:
		strValue.Format("%3.2f", m_fValue);
		break;
	case 2:
		strValue.Format("%3.2f", m_fValue);
		break;
	case 3:
		strValue = "No signal";
		break;
	case 4:
		strValue = "No Judge";
		break;
	}
	oVariant = strValue;
	return oVariant;
}

/**
* �õ����Խ������
* @param byte byValue ���Խ��
* @return COleVariant ���Խ������
*/
COleVariant CSensorListCtrl::GetTestResultString(byte byValue)
{
	COleVariant oVariant;
	CString strValue = "";
	switch(byValue)
	{
	case 0:
		strValue = "No Test";
		break;
	case 1:
		strValue = "OK";
		break;
	case 2:
		strValue = "Fail";
		break;
	case 3:
		strValue = "No signal";
		break;
	case 4:
		strValue = "No Judge";
		break;
	}
	oVariant = strValue;
	return oVariant;
}