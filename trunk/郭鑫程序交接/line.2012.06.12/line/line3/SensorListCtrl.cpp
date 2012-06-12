// SensorListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "SensorListCtrl.h"

// CSensorListCtrl

IMPLEMENT_DYNAMIC(CSensorListCtrl, CBCGPGridCtrl)

CSensorListCtrl::CSensorListCtrl():data_base_helper_(NULL)
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
	data_base_helper_ = ((CLineApp*)AfxGetApp())->get_data_base_helper();
}

// �����ֳ�������ݶ���
void CSensorListCtrl::OnLoadSiteDataAndFillToChannelList()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	// ���ɱ��ͷ
	CreateColumTitle();

	matrix_data::data_base_helper::device_info_map& map = data_base_helper_->get_devices_info();
	matrix_data::data_base_helper::device_info_map::const_iterator itr;
	CBCGPGridRow* pRow = NULL;

	data_base_helper_->devices_info_lock();
	for(itr = map.begin(); itr != map.end(); ++itr){
		pRow = CreateRow(GetColumnCount());
		SetRowData(pRow, itr->second);
		AddRow(pRow, FALSE);
	}
	data_base_helper_->devices_info_unlock();
	AdjustLayout ();
}

// ���¼����ֳ��������
void CSensorListCtrl::OnReloadSiteDataCMD()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();

	matrix_data::data_base_helper::device_info_map& map = data_base_helper_->get_devices_info();
	matrix_data::data_base_helper::device_info_map::const_iterator itr;
	matrix_data::data_base_helper::device_info di;
	CBCGPGridRow* pRow = NULL;

	data_base_helper_->devices_info_lock();
	for(itr = map.begin(); itr != map.end(); ++itr){

		pRow = FindRowByData(itr->second.ip_, FALSE);
		// ��䱾������
		if(pRow != NULL){
			SetRowData(pRow, itr->second);	// ����һ�е�����
		}
		else{
			pRow = CreateRow(GetColumnCount());
			SetRowData(pRow, itr->second);
			AddRow(pRow, FALSE);
		}
	}
	// ɾ��û���õ�����
	for(int i = (GetRowCount() - 1); i >= 0; i--){
		pRow = GetRow(i);
		if(pRow != NULL){	// �ҵ���
			di.ip_ = pRow->GetData();
			if(data_base_helper_->find_device(di.ip_, di))	RemoveRow(i, FALSE);
		}
	}
	data_base_helper_->devices_info_unlock();
	AdjustLayout ();
}

// Ϊ�µĲ�������ˢ����ʾ
void CSensorListCtrl::OnRefreshForNewTestValue(int iTestType)
{
	CBCGPGridRow* pRow = NULL;
	matrix_data::data_base_helper::device_info_map map = data_base_helper_->get_devices_info();
	matrix_data::data_base_helper::device_info_map::const_iterator itr;
	for(itr = map.begin(); itr != map.end(); ++itr){
		pRow = FindRowByData(itr->second.ip_, FALSE);
		if(pRow != NULL){	// �ҵ���
			SetRowDataOfTestByTestType(pRow, itr->second, iTestType);
			// �жϣ������¼Ӽ첨���ĳ�ʼ����
			if(iTestType != 45)		SetRowDataOfTestByTestType(pRow, itr->second, 40);
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
void CSensorListCtrl::SetRowData(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di)
{
	SetRowDataOfBase(pRow, di);
	SetRowDataOfTest(pRow, di);
}

/**
* ����һ�еĻ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CChannelSetupData* pChannelSetupData ���ָ��
* @return void
*/
void CSensorListCtrl::SetRowDataOfBase(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di)
{
	pRow->SetData(di.ip_);

	matrix_data::data_base_helper::sensor_type st;
	st.nb_ = di.sensors_.begin()->type_;
	data_base_helper_->find_sensor_type(st);

	int nItems = 0;
	pRow->GetItem(nItems)->SetValue(di.sn_, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(di.line_index_, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(di.m_uiPointNb, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(di.m_uiLineNb, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(st.nb_, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(st.segd_code_, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(di.ip_, FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bJumpedChannel), FALSE);
	nItems++;
	pRow->GetItem(nItems)->SetValue(GetMarkerStringByLogic(di.m_bMute), FALSE);
}

/**
* ����һ�еĲ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CSensorListCtrl::SetRowDataOfTest(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di)
{
	SetRowDataOfTestByTestType(pRow, di, 40);
	SetRowDataOfTestByTestType(pRow, di, 45);
	SetRowDataOfTestByTestType(pRow, di, 15);
	SetRowDataOfTestByTestType(pRow, di, 14);
	SetRowDataOfTestByTestType(pRow, di, 1);
	SetRowDataOfTestByTestType(pRow, di, 20);
	SetRowDataOfTestByTestType(pRow, di, 21);
}

/**
* ����һ�еĲ������ݣ����ݲ�������
* @param CBCGPGridRow* pRow ��ָ��
* @param CChannelSetupData* pChannelSetupData ���ָ��
* @return void
*/
void CSensorListCtrl::SetRowDataOfTestByTestType(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di, int iTestType)
{
	unsigned int nItems = 0;
	switch(iTestType)
	{
		// Ұ�����
	case 15:
		nItems = 11;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.sensors_[0].resistance_check_, di.sensors_[0].resistance_), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.sensors_[0].resistance_check_));
		break;
		// Ұ��©��
	case 14:
		nItems = 12;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.sensors_[0].leakage_check_, di.sensors_[0].leakage_), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.sensors_[0].leakage_check_));
		break;
		// Ұ������
	case 1:
		nItems = 13;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.sensors_[0].noise_check_, di.sensors_[0].noise_), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.sensors_[0].noise_check_));
		break;
		// Ұ����б��
	case 20:
		nItems = 14;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.sensors_[0].tilt_check_, di.sensors_[0].tilt_), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.sensors_[0].tilt_check_));
		break;
		// Ұ����б��ģ��
	case 21:
		nItems = 15;
		pRow->GetItem(nItems)->SetValue(GetTestResultString(di.sensors_[0].tilt_model_check_, di.sensors_[0].tilt_model_), FALSE);
		pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(di.sensors_[0].tilt_model_check_));
		break;
		// ȫ��Ұ�����
	//case 40:
	//	nItems = 9;
	//	pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byCheck), FALSE);
	//	pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byCheck));
	//	break;
	//	// �¼Ӽ첨���ĳ�ʼ����
	//case 45:
	//	nItems = 10;
	//	pRow->GetItem(nItems)->SetValue(GetTestResultString(pChannelSetupData->m_byOnFieldCheck), FALSE);
	//	pRow->GetItem(nItems)->SetBackgroundColor(GetColourByCheck(pChannelSetupData->m_byOnFieldCheck));
	//	break;
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