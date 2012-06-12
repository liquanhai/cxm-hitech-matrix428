// InstrumentListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "InstrumentListCtrl.h"

// CInstrumentListCtrl

IMPLEMENT_DYNCREATE(CInstrumentListCtrl, CBCGPGridCtrl)

CInstrumentListCtrl::CInstrumentListCtrl()
{
	helper_ = NULL;
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
	helper_ = ((CLineApp*)AfxGetApp())->get_data_base_helper();
}

// �����ֳ��������ݶ���
void CInstrumentListCtrl::OnLoadSiteDataAndFillToInstrumentList()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	if(helper_ == NULL) return;

	CBCGPGridRow* pRow = NULL;
	matrix_data::data_base_helper::const_device_info_map_reference& map = helper_->get_devices_info();
	matrix_data::data_base_helper::device_info_map::const_iterator itr;

	// ���ɱ��ͷ
	CreateColumTitle();
	
	helper_->devices_info_lock();
	if(map.size() > 0){
		for(itr = map.begin(); itr != map.end(); ++itr){
			pRow = CreateRow(GetColumnCount());
			// ����һ�е�����
			SetRowData(pRow, itr->second);
			AddRow(pRow, FALSE);
		}
	}
	helper_->devices_info_unlock();
	
	AdjustLayout ();
}

// ���¼����ֳ���������
void CInstrumentListCtrl::OnReloadSiteDataCMD()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	if(helper_ == NULL) return;

	unsigned int sn = 0x0;
	matrix_data::data_base_helper::const_device_info_map_reference map = helper_->get_devices_info();
	matrix_data::data_base_helper::device_info_map::const_iterator itr;
	CBCGPGridRow* pRow = NULL;
	
	helper_->devices_info_lock();
	if(map.size() > 0){
		for(itr = map.begin(); itr != map.end(); ++itr){
			pRow = FindRowByData(itr->second.sn_, FALSE);
			if(pRow != NULL){ 
				SetRowData(pRow, itr->second);	
			}
			else{
				pRow = CreateRow(GetColumnCount());
				// ����һ�е�����
				SetRowData(pRow, itr->second);
				AddRow(pRow, FALSE);
			}
		}
	}
	helper_->devices_info_unlock();

	// ɾ��û���õ�����
	for(int i = (GetRowCount() - 1); i >= 0; i--){
		pRow = GetRow(i);
		if(pRow != NULL){	// �ҵ���
			sn = pRow->GetData();
			helper_->devices_info_lock();
			itr = map.find(sn);
			helper_->devices_info_unlock();
			if(itr == map.end())	RemoveRow(i, FALSE);
		}
		else{
			TRACE1("Instrument�в�����%d\r\n", i);
		}
	}	
	AdjustLayout ();
}

// Ϊ�µĲ�������ˢ����ʾ
void CInstrumentListCtrl::OnRefreshForNewTestValue(int iTestType)
{
	unsigned int sn = 0x0;
	matrix_data::data_base_helper::const_device_info_map_reference map = helper_->get_devices_info();
	matrix_data::data_base_helper::device_info_map::const_iterator itr;
	CBCGPGridRow* pRow = NULL;

	helper_->devices_info_lock();
	if(map.size() > 0){
		for(itr = map.begin(); itr != map.end(); ++itr){
			pRow = FindRowByData(itr->second.sn_, FALSE);
			if(pRow != NULL){ 
				SetRowDataOfTestByTestType(pRow, itr->second, iTestType);
				SetRowDataOfTestByTestType(pRow, itr->second, 30);
			}
		}
	}
	helper_->devices_info_unlock();
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

	strColumn = "CMRR";
	InsertColumn (nColumns, strColumn, 80);
	nColumns++;

	//strColumn = "Rout IP";
	//InsertColumn (nColumns, strColumn, 80);
	//nColumns++;

	//strColumn = "Direction";
	//InsertColumn (nColumns, strColumn, 80);
	//nColumns++;

	//strColumn = "Rout Top";
	//InsertColumn (nColumns, strColumn, 80);
	//nColumns++;

	//strColumn = "Rout Down";
	//InsertColumn (nColumns, strColumn, 80);
	//nColumns++;

	//strColumn = "Rout Left";
	//InsertColumn (nColumns, strColumn, 80);
	//nColumns++;

	//strColumn = "Rout Right";
	//InsertColumn (nColumns, strColumn, 80);
	//nColumns++;

	//strColumn = "Time Head";
	//InsertColumn (nColumns, strColumn, 80);
	//nColumns++;

	//strColumn = "Time Delay";
	//InsertColumn (nColumns, strColumn, 80);
	//nColumns++;

	//strColumn = "Jump Channel";
	//InsertColumn (nColumns, strColumn, 100);
	//nColumns++;

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
* @param matrix_data::data_base_helper::device_info& di ��������
* @return void
*/
void CInstrumentListCtrl::SetRowData(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di)
{
	SetRowDataOfBase(pRow, di);
	SetRowDataOfTest(pRow, di);
}

/**
* ����һ�еĻ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param matrix_data::data_base_helper::device_info& di ��������
* @return void
*/
void CInstrumentListCtrl::SetRowDataOfBase(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di)
{
	pRow->SetData(di.sn_);

	unsigned int nItems = 0;
	pRow->GetItem(nItems)->SetValue(di.sn_, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(di.line_index_, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(di.m_uiPointNb, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(1, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetInstrumentTypeStringByInstrumentType(di.sn_), FALSE);
	nItems++;

	pRow->GetItem(nItems)->SetValue(di.ip_, FALSE);
	nItems = 6;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bJumpedChannel), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bSensor), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bBlastMachine), FALSE);

	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bAux), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bDetour), FALSE);
	nItems++;

	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bDetourMarkerLow), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bDetourMarkerHigh), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bMarker), FALSE);
	nItems++;
}

/**
* ����һ�еĲ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CInstrumentListCtrl::SetRowDataOfTest(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di)
{
	SetRowDataOfTestByTestType(pRow, di, 30);
	SetRowDataOfTestByTestType(pRow, di, 4);
	SetRowDataOfTestByTestType(pRow, di, 5);
	SetRowDataOfTestByTestType(pRow, di, 7);
	SetRowDataOfTestByTestType(pRow, di, 6);
	SetRowDataOfTestByTestType(pRow, di, 8);
}

/**
* ����һ�еĲ������ݣ����ݲ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CInstrumentListCtrl::SetRowDataOfTestByTestType(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di, int iTestType)
{
	unsigned int nItems = 0;
	
	switch(iTestType)
	{
	case 4:	// ��������
		nItems = 7;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.m_byNoiseCheck, di.m_fNoiseValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.m_byNoiseCheck));
		break;
	case 5:	// ��������
		nItems = 8;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.m_byDistortionCheck, di.m_fDistortionValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.m_byDistortionCheck));
		break;
	case 7:	// ��������
		nItems = 9;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.m_byCrosstalkCheck, di.m_fCrosstalkValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.m_byCrosstalkCheck));
		break;
	case 6:	// ��������/��λ
		nItems = 10;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.m_byGainCheck, di.m_fGainValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.m_byGainCheck));
		nItems++;
		break;
	case 8:	// ������ģ
		nItems = 11;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.m_byCMRRCheck, di.m_fCMRRValue), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.m_byCMRRCheck));
		break;
	case 30:	// ������������
		nItems = 6;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.m_byCheck), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.m_byCheck));
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
COleVariant CInstrumentListCtrl::GetInstrumentTypeStringByInstrumentType(unsigned int sn)
{
	COleVariant oVariant;
	CString strValue = "";
	// �жϷ���
	switch(sn & 0x3)
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