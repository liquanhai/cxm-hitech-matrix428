// DlgSurveySetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "DlgSurveySetup.h"


// CDlgSurveySetup �Ի���

IMPLEMENT_DYNAMIC(CDlgSurveySetup, CDialog)

CDlgSurveySetup::CDlgSurveySetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSurveySetup::IDD, pParent)
{

}

CDlgSurveySetup::~CDlgSurveySetup()
{
}

void CDlgSurveySetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSurveySetup, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_APPLYALL, &CDlgSurveySetup::OnBnClickedButtonApplyAll)
	ON_BN_CLICKED(IDC_BUTTON_APPLYSENSOR, &CDlgSurveySetup::OnBnClickedButtonApplySensor)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgSurveySetup::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgSurveySetup::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgSurveySetup::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgSurveySetup::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_REVERSE, &CDlgSurveySetup::OnBnClickedButtonReverse)
END_MESSAGE_MAP()

// CDlgSurveySetup ��Ϣ�������

/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgSurveySetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect oRect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	pWnd->GetWindowRect(&oRect);
	ScreenToClient(&oRect);

	m_oTabWnd.Create(CBCGPTabWnd::STYLE_3D, oRect, this, 1, CBCGPTabWnd::LOCATION_TOP);	// ����ҳ����

	m_oTabSurvey.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabSurvey.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 1);	// ����ҳ����
	m_oTabPointCode.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabPointCode.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 2);	// ����ҳ�����
	m_oTabSensor.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabSensor.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 3);	// ����ҳ�첨��

	m_oTabWnd.AddTab(&m_oTabSurvey, "    Survey    ");	// ����ҳ����
	m_oTabWnd.AddTab(&m_oTabPointCode, "    Point Code    ");	// ����ҳ����
	m_oTabWnd.AddTab(&m_oTabSensor, "    Sensor    ");	// ����ҳ����

	m_oTabWnd.RecalcLayout();
	m_oTabWnd.SetActiveTab(0);

	OnBnClickedButtonReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/**
* OnClose()
* @param void
* @return void
*/
void CDlgSurveySetup::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE);
//	CDialog::OnClose();
}

/**
* ��ť�����Ӧ��ApplyAll
* @param void
* @return void
*/
void CDlgSurveySetup::OnBnClickedButtonApplyAll()
{
	try
	{
		m_oTabSurvey.OnBnClickedButtonApplyAll();
		m_oTabPointCode.OnBnClickedButtonApplyAll();
		m_oTabSensor.OnBnClickedButtonApplyAll();
	}
	catch (CException* e)
	{
		AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
		return;
	}

	// ��������������ݣ�ApplyAll
	m_pSiteData->OnApplyAllSurveySetupData();
	// ���͵�������ApplyAll֪ͨ����֡
	m_pSiteData->OnSendCMDFrameForApplyAllSurveySetupData();
}

/**
* ��ť�����Ӧ��ApplySensor
* @param void
* @return void
*/
void CDlgSurveySetup::OnBnClickedButtonApplySensor()
{
	try
	{
		m_oTabSensor.OnBnClickedButtonApplySensor();
	}
	catch (CException* e)
	{
		AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
		return;
	}	
	// ��������������ݣ�ApplySensor
	m_pSiteData->OnApplySensorSurveySetupData();
	// ���͵�������ApplyAll֪ͨ����֡
	m_pSiteData->OnSendCMDFrameForApplySensorSurveySetupData();
}

/**
* ��ť�����Ӧ��Reset
* @param void
* @return void
*/
void CDlgSurveySetup::OnBnClickedButtonReset()
{
	// ���ص�����������
	m_pSiteData->OnLoadSurveySetupData();
	m_oTabSurvey.OnBnClickedButtonReset();
	m_oTabPointCode.OnBnClickedButtonReset();
	m_oTabSensor.OnBnClickedButtonReset();
}

/**
* ��ť�����Ӧ��Add
* @param void
* @return void
*/
void CDlgSurveySetup::OnBnClickedButtonAdd()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabSurvey.OnBnClickedButtonAdd();
		break;
	case 1:
		m_oTabPointCode.OnBnClickedButtonAdd();
		break;
	case 2:
		m_oTabSensor.OnBnClickedButtonAdd();
		break;
	}
}

/**
* ��ť�����Ӧ��Change
* @param void
* @return void
*/
void CDlgSurveySetup::OnBnClickedButtonChange()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabSurvey.OnBnClickedButtonChange();
		break;
	case 1:
		m_oTabPointCode.OnBnClickedButtonChange();
		break;
	case 2:
		m_oTabSensor.OnBnClickedButtonChange();
		break;
	}
}

/**
* ��ť�����Ӧ��Delete
* @param void
* @return void
*/
void CDlgSurveySetup::OnBnClickedButtonDelete()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabSurvey.OnBnClickedButtonDelete();
		break;
	case 1:
		m_oTabPointCode.OnBnClickedButtonDelete();
		break;
	case 2:
		m_oTabSensor.OnBnClickedButtonDelete();
		break;
	}
}

/**
* ��ť�����Ӧ��Reverse
* @param void
* @return void
*/
void CDlgSurveySetup::OnBnClickedButtonReverse()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabSurvey.OnBnClickedButtonReverse();
		break;
	case 1:
		m_oTabPointCode.OnBnClickedButtonReverse();
		break;
	case 2:
		m_oTabSensor.OnBnClickedButtonReverse();
		break;
	}
}
