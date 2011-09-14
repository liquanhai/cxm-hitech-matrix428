// InstrumentListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "InstrumentListCtrl.h"

// CInstrumentListCtrl

IMPLEMENT_DYNCREATE(CInstrumentListCtrl, CBCGPGridCtrl)

CInstrumentListCtrl::CInstrumentListCtrl()
{

}

CInstrumentListCtrl::~CInstrumentListCtrl()
{
}

BEGIN_MESSAGE_MAP(CInstrumentListCtrl, CBCGPGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CInstrumentListCtrl ��Ϣ�������

int CInstrumentListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	// �����ֳ��������ݶ���
	OnLoadSiteDataAndFillToInstrumentList();

	return 0;
}

void CInstrumentListCtrl::OnDestroy()
{
	CBCGPGridCtrl::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	//	SaveState (_T("BasicGrid"));
}


// �ֳ����ݶ����ʼ��
void CInstrumentListCtrl::OnSiteDataInit()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_pSiteData = &pMainFrame->m_oSiteData;
}

// �����ֳ��������ݶ���
void CInstrumentListCtrl::OnLoadSiteDataAndFillToInstrumentList()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	// ���ɱ��ͷ
	CreateColumTitle();

	CInstrument* pInstrument = NULL;
	CBCGPGridRow* pRow = NULL;
	POSITION pos = m_pSiteData->m_oInstrumentList.GetFirstInstrumentPosition();
	while(NULL != pos)
	{
		m_pSiteData->m_oInstrumentList.GetNextInstrumentByPosition(pos, pInstrument);
		if(NULL != pInstrument)
		{
			pRow = CreateRow(GetColumnCount());
			// ����һ�е�����
			SetRowData(pRow, pInstrument);
			AddRow(pRow, FALSE);
		}		
	}
	//	LoadState (_T("BasicGrid"));
	AdjustLayout ();
}

// ���¼����ֳ���������
void CInstrumentListCtrl::OnReloadSiteDataCMD()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();

	CInstrument* pInstrument = NULL;
	CBCGPGridRow* pRow = NULL;
	POSITION pos = m_pSiteData->m_oInstrumentList.GetFirstInstrumentPosition();
	while(NULL != pos)
	{
		// ��䱾������
		m_pSiteData->m_oInstrumentList.GetNextInstrumentByPosition(pos, pInstrument);
		if(NULL != pInstrument)
		{
			pRow = FindRowByData(pInstrument->m_uiSN, FALSE);
			if(NULL != pRow)	// �ҵ���
			{
				SetRowData(pRow, pInstrument);	// ����һ�е�����
			}
			else
			{
				pRow = CreateRow(GetColumnCount());
				// ����һ�е�����
				SetRowData(pRow, pInstrument);
				AddRow(pRow, FALSE);
			}
		}
	}
	// ɾ��û���õ�����
	for(int i = (GetRowCount() - 1); i >= 0; i--)
	{
		pRow = GetRow(i);
		if(NULL != pRow)	// �ҵ���
		{
			if(FALSE == m_pSiteData->m_oInstrumentList.m_oSNInstrumentMap.IfIndexExistInMap(pRow->GetData()))
			{
				RemoveRow(i, FALSE);
			}
		}
		else
		{
			TRACE1("Instrument�в�����%d\r\n", i);
		}

	}
	//	LoadState (_T("BasicGrid"));
	AdjustLayout ();
}

// Ϊ�µĲ�������ˢ����ʾ
void CInstrumentListCtrl::OnRefreshForNewTestValue(int iTestType)
{
	unsigned int uiIP = 0;
	CInstrument* pInstrument = NULL;
	CBCGPGridRow* pRow = NULL;
	while(true)
	{
		if(TRUE == m_pSiteData->m_olsIPInstrument.IsEmpty())
		{
			break;
		}
		uiIP = m_pSiteData->m_olsIPInstrument.RemoveHead();
		if(TRUE == m_pSiteData->m_oInstrumentList.m_oIPInstrumentMap.GetInstrument(uiIP, pInstrument))
		{
			pRow = FindRowByData(pInstrument->m_uiSN, FALSE);
			if(NULL != pRow)	// �ҵ���
			{
				SetRowDataOfTestByTestType(pRow, pInstrument, iTestType);
				SetRowDataOfTestByTestType(pRow, pInstrument, 30);
			}
		}
	}	
}

// ���ɱ��ͷ
void CInstrumentListCtrl::CreateColumTitle()
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

	strColumn = "Type";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "IP";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Test";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Noise";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Distortion";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Crosstalk";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Gain";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Phase";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Gain/Phase";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "CMRR";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Rout IP";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Direction";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Rout Top";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Rout Down";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Rout Left";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Rout Right";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Time Head";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Time Delay";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Jump Channel";
	InsertColumn (nColumns, strColumn, 100);
	nColumns++;

	strColumn = "Sensor";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Blast";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Aux";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Detour";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Detour L";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Detour H";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	strColumn = "Marker";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;
}

/**
* ����һ�е�����
* @param CBCGPGridRow* pRow ��ָ��
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CInstrumentListCtrl::SetRowData(CBCGPGridRow* pRow, CInstrument* pInstrument)
{
	SetRowDataOfBase(pRow, pInstrument);
	SetRowDataOfTest(pRow, pInstrument);
}

/**
* ����һ�еĻ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CInstrumentListCtrl::SetRowDataOfBase(CBCGPGridRow* pRow, CInstrument* pInstrument)
{
	pRow->SetData(pInstrument->m_uiSN);

	unsigned int nItems = 0;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiSN, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiLineNb, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiPointNb, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiChannelNb, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetInstrumentTypeStringByInstrumentType(pInstrument->m_uiInstrumentType), FALSE);
	nItems++;

	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiIP, FALSE);
	nItems = 14;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiRoutIP, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetDirectionStringByRoutDirection(pInstrument->m_uiRoutDirection), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiRoutIPTop, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiRoutIPDown, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiRoutIPLeft, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiRoutIPRight, FALSE);
	nItems++;

	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiTimeHeadFrame, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(pInstrument->m_uiTimeDelay, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pInstrument->m_bJumpedChannel), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pInstrument->m_bSensor), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pInstrument->m_bBlastMachine), FALSE);

	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pInstrument->m_bAux), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pInstrument->m_bDetour), FALSE);
	nItems++;

	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pInstrument->m_bDetourMarkerLow), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pInstrument->m_bDetourMarkerHigh), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(pInstrument->m_bMarker), FALSE);
	nItems++;
}

/**
* ����һ�еĲ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CInstrumentListCtrl::SetRowDataOfTest(CBCGPGridRow* pRow, CInstrument* pInstrument)
{
	SetRowDataOfTestByTestType(pRow, pInstrument, 30);
	SetRowDataOfTestByTestType(pRow, pInstrument, 4);
	SetRowDataOfTestByTestType(pRow, pInstrument, 5);
	SetRowDataOfTestByTestType(pRow, pInstrument, 7);
	SetRowDataOfTestByTestType(pRow, pInstrument, 6);
	SetRowDataOfTestByTestType(pRow, pInstrument, 8);
}

/**
* ����һ�еĲ������ݣ����ݲ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CInstrumentListCtrl::SetRowDataOfTestByTestType(CBCGPGridRow* pRow, CInstrument* pInstrument, int iTestType)
{
	unsigned int nItems = 0;
	
	switch(iTestType)
	{
	case 4:	// ��������
		nItems = 7;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pInstrument->m_byNoiseCheck, pInstrument->m_fNoiseValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pInstrument->m_byNoiseCheck));
		break;
	case 5:	// ��������
		nItems = 8;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pInstrument->m_byDistortionCheck, pInstrument->m_fDistortionValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pInstrument->m_byDistortionCheck));
		break;
	case 7:	// ��������
		nItems = 9;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pInstrument->m_byCrosstalkCheck, pInstrument->m_fCrosstalkValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pInstrument->m_byCrosstalkCheck));
		break;
	case 6:	// ��������/��λ
		nItems = 10;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pInstrument->m_byGainCheck, pInstrument->m_fGainValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pInstrument->m_byGainCheck));
		nItems++;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pInstrument->m_byPhaseCheck, pInstrument->m_fPhaseValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pInstrument->m_byPhaseCheck));
		nItems++;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pInstrument->m_byGainAndPhaseCheck), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pInstrument->m_byGainAndPhaseCheck));
		break;
	case 8:	// ������ģ
		nItems = 13;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pInstrument->m_byCMRRCheck, pInstrument->m_fCMRRValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pInstrument->m_byCMRRCheck));
		break;
	case 30:	// ������������
		nItems = 6;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(pInstrument->m_byCheck), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pInstrument->m_byCheck));
		break;
	}
}

/**
* �õ�������ɫ�����ݲ��Լ����
* @param byte byCheck �����
* @return void
*/
COLORREF CInstrumentListCtrl::GetColourByCheck(byte byCheck)
{
	COLORREF crColor = RGB(255, 255, 255);	// ��ɫ
	switch(byCheck)
	{
	case 0:	// 0��δ����
		crColor = RGB(0, 0, 255);	// ��ɫ
		break;
	case 1:	// 1�����Ժϸ�
		crColor = RGB(0, 255, 0);	// ��ɫ
		break;
	case 2:	// 2�����Բ��ϸ�
		crColor = RGB(255, 0, 0);	// ��ɫ
		break;
	case 3:	// 3�����ź�
		crColor = RGB(255, 255, 0);	// ��ɫ
		break;
	}
	return crColor;
}

/**
* �õ�������֣������߼�ֵ
* @param bool bValue �߼�ֵ
* @return COleVariant �������
*/
COleVariant CInstrumentListCtrl::GetMarkerStringByLogic(bool bValue)
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
* �õ��������֣����ݷ���ֵ
* @param unsigned int uiRoutDirection ����ֵ
* @return COleVariant ��������
*/
COleVariant CInstrumentListCtrl::GetDirectionStringByRoutDirection(unsigned int uiRoutDirection)
{
	COleVariant oVariant;
	CString strValue = "";
	// �жϷ���
	switch(uiRoutDirection)
	{
	case 1:	// ��
		{
			strValue = "��";
			break;
		}
	case 2:	// ��
		{
			strValue = "��";
			break;
		}
	case 3:	// ��
		{
			strValue = "��";
			break;
		}
	case 4:	// ��
		{
			strValue = "��";
			break;
		}
	}
	oVariant = strValue;
	return oVariant;
}

/**
* �õ������������֣�������������ֵ
* @param unsigned int uiInstrumentType ��������
* @return COleVariant ������������
*/
COleVariant CInstrumentListCtrl::GetInstrumentTypeStringByInstrumentType(unsigned int uiInstrumentType)
{
	COleVariant oVariant;
	CString strValue = "";
	// �жϷ���
	switch(uiInstrumentType)
	{
	case 1:	// ����վ
		{
			strValue = "��";
			break;
		}
	case 2:	// ��Դվ
		{
			strValue = "��";
			break;
		}
	case 3:	// �ɼ�վ
		{
			strValue = "��";
			break;
		}
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
COleVariant CInstrumentListCtrl::GetTestResultString(byte byValue, float m_fValue)
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
COleVariant CInstrumentListCtrl::GetTestResultString(byte byValue)
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