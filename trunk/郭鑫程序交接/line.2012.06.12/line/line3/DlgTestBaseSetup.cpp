// DlgTestBaseSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "DlgTestBaseSetup.h"


// CDlgTestBaseSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgTestBaseSetup, CDialog)

CDlgTestBaseSetup::CDlgTestBaseSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTestBaseSetup::IDD, pParent)
{

}

CDlgTestBaseSetup::~CDlgTestBaseSetup()
{
}

void CDlgTestBaseSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTestBaseSetup, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgTestBaseSetup::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgTestBaseSetup::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgTestBaseSetup::OnBnClickedButtonChange)
END_MESSAGE_MAP()

// CDlgTestBaseSetup ��Ϣ�������

/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgTestBaseSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect oRect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	pWnd->GetWindowRect(&oRect);
	ScreenToClient(&oRect);

	m_oTabWnd.Create(CBCGPTabWnd::STYLE_3D, oRect, this, 1, CBCGPTabWnd::LOCATION_TOP);	// ����ҳ����

	m_oTabTestBaseInstrument.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabTestBaseInstrument.m_uiAim = 1;	// ���Զ��� 1-������2-�첨��
	m_oTabTestBaseInstrument.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 1);	// ����ҳ���Ի������ã�����

	m_oTabTestBaseSensor.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabTestBaseSensor.m_uiAim = 2;	// ���Զ��� 1-������2-�첨��
	m_oTabTestBaseSensor.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 2);	// ����ҳ���Ի������ã��첨��

	m_oTabTestLimitInstrument.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabTestLimitInstrument.m_uiAim = 1;	// ���Զ��� 1-������2-�첨��
	m_oTabTestLimitInstrument.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 3);	// ����ҳ�����о����ã�����

	m_oTabTestLimitSensor.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabTestLimitSensor.m_uiAim = 2;	// ���Զ��� 1-������2-�첨��
	m_oTabTestLimitSensor.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 4);	// ����ҳ�����о����ã��첨��

	m_oTabWnd.AddTab(&m_oTabTestBaseInstrument, "    Instrument Base    ");	// ����ҳ���Ի������ã�����
	m_oTabWnd.AddTab(&m_oTabTestBaseSensor, "    Sensor Base    ");	// ����ҳ���Ի������ã��첨��
	m_oTabWnd.AddTab(&m_oTabTestLimitInstrument, "    Instrument Limit    ");	// ����ҳ�����о����ã�����
	m_oTabWnd.AddTab(&m_oTabTestLimitSensor, "    Sensor Limit    ");	// ����ҳ�����о����ã��첨��

	m_oTabWnd.RecalcLayout();
	m_oTabWnd.SetActiveTab(0);

	m_oTabTestBaseInstrument.OnBnClickedButtonReset();
	m_oTabTestBaseSensor.OnBnClickedButtonReset();
	m_oTabTestLimitInstrument.OnBnClickedButtonReset();
	m_oTabTestLimitSensor.OnBnClickedButtonReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/**
* OnClose()
* @param void
* @return void
*/
void CDlgTestBaseSetup::OnClose()
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
void CDlgTestBaseSetup::OnBnClickedButtonApply()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		try
		{
			m_oTabTestBaseInstrument.OnBnClickedButtonApply();
			// Apply���Ի����������ݣ�����
			m_pSiteData->OnApplyTestBaseSetupDataForInstrument();
			// ���Ͳ��Ի����������ݱ仯֪ͨ����֡������
			m_pSiteData->OnSendCMDFrameForApplyTestBaseSetupDataOfInstrument();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}
		break;
	case 1:
		try
		{
			m_oTabTestBaseSensor.OnBnClickedButtonApply();
			// Apply���Ի����������ݣ��첨��
			m_pSiteData->OnApplyTestBaseSetupDataForSensor();
			// ���Ͳ��Ի����������ݱ仯֪ͨ����֡���첨��
			m_pSiteData->OnSendCMDFrameForApplyTestBaseSetupDataOfSensor();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}
		break;
	case 2:
		try
		{
			m_oTabTestLimitInstrument.OnBnClickedButtonApply();
			// Apply�����о��������ݣ�����
			m_pSiteData->OnApplyTestLimitSetupDataForInstrument();
			// ���Ͳ����о��������ݱ仯֪ͨ����֡������
			m_pSiteData->OnSendCMDFrameForApplyTestLimitSetupDataOfInstrument();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}
		break;
	case 3:
		try
		{
			m_oTabTestLimitSensor.OnBnClickedButtonApply();
			// Apply�����о��������ݣ��첨��
			m_pSiteData->OnApplyTestLimitSetupDataForSensor();
			// ���Ͳ����о��������ݱ仯֪ͨ����֡���첨��
			m_pSiteData->OnSendCMDFrameForApplyTestLimitSetupDataOfSensor();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}
		break;
	}
}

/**
* ��ť�����Ӧ��Reset
* @param void
* @return void
*/
void CDlgTestBaseSetup::OnBnClickedButtonReset()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		// ���ز��Ի����������ݣ�����
		m_pSiteData->OnLoadTestBaseSetupDataForInstrument();
		m_oTabTestBaseInstrument.OnBnClickedButtonReset();
		break;
	case 1:
		// ���ز��Ի����������ݣ��첨��
		m_pSiteData->OnLoadTestBaseSetupDataForSensor();
		m_oTabTestBaseSensor.OnBnClickedButtonReset();
		break;
	case 3:
		// ���ز����о��������ݣ�����
		m_pSiteData->OnLoadTestLimitSetupDataForInstrument();
		m_oTabTestLimitInstrument.OnBnClickedButtonReset();
		break;
	case 4:
		// ���ز����о��������ݣ��첨��
		m_pSiteData->OnLoadTestLimitSetupDataForSensor();
		m_oTabTestLimitSensor.OnBnClickedButtonReset();
		break;
	}
}

/**
* ��ť�����Ӧ��Change
* @param void
* @return void
*/
void CDlgTestBaseSetup::OnBnClickedButtonChange()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabTestBaseInstrument.OnBnClickedButtonChange();
		break;
	case 1:
		m_oTabTestBaseSensor.OnBnClickedButtonChange();
		break;
	case 2:
		m_oTabTestLimitInstrument.OnBnClickedButtonChange();
		break;
	case 3:
		m_oTabTestLimitSensor.OnBnClickedButtonChange();
		break;
	}
}
