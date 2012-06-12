// DlgTestSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "DlgTestSetup.h"


// CDlgTestSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgTestSetup, CDialog)

CDlgTestSetup::CDlgTestSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTestSetup::IDD, pParent)
{

}

CDlgTestSetup::~CDlgTestSetup()
{
	delete []m_pTabTestMultiple;
}

void CDlgTestSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTestSetup, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgTestSetup::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgTestSetup::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CDlgTestSetup::OnBnClickedButtonGO)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgTestSetup::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgTestSetup::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgTestSetup::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlgTestSetup::OnBnClickedButtonClear)
END_MESSAGE_MAP()

// CDlgTestSetup ��Ϣ�������

/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgTestSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect oRect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	pWnd->GetWindowRect(&oRect);
	ScreenToClient(&oRect);

	m_oTabWnd.Create(CBCGPTabWnd::STYLE_3D, oRect, this, 1, CBCGPTabWnd::LOCATION_TOP);	// ����ҳ����

	m_oTabTestInstrument.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabTestInstrument.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 1);	// ����ҳTestInstrument
	m_oTabTestSensor.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabTestSensor.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 2);	// ����ҳTestSensor
	m_oTabWndTestMultiple.Create(CBCGPTabWnd::STYLE_3D, oRect, &m_oTabWnd, 3, CBCGPTabWnd::LOCATION_TOP);	// ����ҳ���ϲ�������
	m_oTabTestSeisMonitor.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabTestSeisMonitor.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 2);	// ����ҳTestSeisMonitor

	m_oTabWnd.AddTab(&m_oTabTestInstrument, "    Instrument    ");	// ����ҳTestInstrument
	m_oTabWnd.AddTab(&m_oTabTestSensor, "    Sensor    ");	// ����ҳTestSensor
	m_oTabWnd.AddTab(&m_oTabWndTestMultiple, "    Multiple    ");	// ����ҳ���ϲ�������
	m_oTabWnd.AddTab(&m_oTabTestSeisMonitor, "    SeisMonitor    ");	// ����ҳTestSeisMonitor

	m_oTabWnd.RecalcLayout();
	m_oTabWnd.SetActiveTab(0);

	// ���ز����������ݣ���������
	m_pSiteData->OnLoadTestSetupDataForInstrument();
	// ���ز����������ݣ��첨������
	m_pSiteData->OnLoadTestSetupDataForSensor();
	// ���ز����������ݣ����ϲ���
	m_pSiteData->OnLoadTestSetupDataForMultiple();
	// ���ز����������ݣ��������
	m_pSiteData->OnLoadTestSetupDataForSeisMonitor();

	m_pTabTestMultiple = new CTabTestMultiple[m_pSiteData->m_oTestProjectListMultiple.m_uiCountAll];
	POSITION pos = NULL;
	CTestProject* pTestProject;
	for(unsigned int i = 0; i < m_pSiteData->m_oTestProjectListMultiple.m_uiCountAll; i++)
	{
		pos = m_pSiteData->m_oTestProjectListMultiple.m_olsTestProject.FindIndex(i);
		pTestProject = m_pSiteData->m_oTestProjectListMultiple.m_olsTestProject.GetAt(pos);
		m_pTabTestMultiple[i].m_pSiteData = m_pSiteData;
		m_pTabTestMultiple[i].m_uiTestNb = pTestProject->m_uiTestNb;
		m_pTabTestMultiple[i].Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWndTestMultiple, m_pTabTestMultiple->m_uiTestNb);	// ����ҳTestMultiple
		CString strTabName;
		strTabName.Format("  %s  ", pTestProject->m_strTestName);
		m_oTabWndTestMultiple.AddTab(&m_pTabTestMultiple[i], strTabName);	// ����ҳTestInstrument
	}
	m_oTabWndTestMultiple.RecalcLayout();
	m_oTabWndTestMultiple.SetActiveTab(0);

	// cxm 2011-09-20 �Ƚ���ҳ������
	m_oTabWndTestMultiple.ShowWindow(SW_HIDE);

	m_oTabTestInstrument.OnBnClickedButtonReset();
	m_oTabTestSensor.OnBnClickedButtonReset();
	for(unsigned int i = 0; i < m_pSiteData->m_oTestProjectListMultiple.m_uiCountAll; i++)
	{
		m_pTabTestMultiple[i].OnBnClickedButtonReset();
	}
	m_oTabTestSeisMonitor.OnBnClickedButtonReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/**
* OnClose()
* @param void
* @return void
*/
void CDlgTestSetup::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE);
//	CDialog::OnClose();
}

/**
* ��ť�����Ӧ��Apply
* @param void
* @return void
*/
void CDlgTestSetup::OnBnClickedButtonApply()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		try
		{
			m_oTabTestInstrument.OnBnClickedButtonApply();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}

		// Apply�����������ݣ���������
		m_pSiteData->OnApplyTestSetupDataForInstrument();
		// ���Ͳ����������ݱ仯֪ͨ����֡����������
		m_pSiteData->OnSendCMDFrameForApplyTestSetupDataOfInstrument();
		break;
	case 1:
		try
		{
			m_oTabTestSensor.OnBnClickedButtonApply();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}

		// Apply�����������ݣ��첨������
		m_pSiteData->OnApplyTestSetupDataForSensor();
		// ���Ͳ����������ݱ仯֪ͨ����֡���첨������
		m_pSiteData->OnSendCMDFrameForApplyTestSetupDataOfSensor();
		break;
	case 2:
		try
		{
			for(unsigned int i = 0; i < m_pSiteData->m_oTestProjectListMultiple.m_uiCountAll; i++)
			{
				m_pTabTestMultiple[i].OnBnClickedButtonApply();
			}
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}

		// Apply�����������ݣ����ϲ���
		m_pSiteData->OnApplyTestSetupDataForMultiple();
		// ���Ͳ����������ݱ仯֪ͨ����֡�����ϲ���
		m_pSiteData->OnSendCMDFrameForApplyTestSetupDataOfMultiple();
		break;
	case 3:
		try
		{
			if(false == m_oTabTestSeisMonitor.OnBnClickedButtonApply())
			{
				return;
			}
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}

		// Apply�����������ݣ��������
		m_pSiteData->OnApplyTestSetupDataForSeisMonitor();
		// ���Ͳ����������ݱ仯֪ͨ����֡���������
		m_pSiteData->OnSendCMDFrameForApplyTestSetupDataOfSeisMonitor();
		break;
	}
}

/**
* ��ť�����Ӧ��Reset
* @param void
* @return void
*/
void CDlgTestSetup::OnBnClickedButtonReset()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		// ���ز����������ݣ���������
		m_pSiteData->OnLoadTestSetupDataForInstrument();
		m_oTabTestInstrument.OnBnClickedButtonReset();
		break;
	case 1:
		// ���ز����������ݣ��첨������
		m_pSiteData->OnLoadTestSetupDataForSensor();
		m_oTabTestSensor.OnBnClickedButtonReset();
		break;
	case 2:
		// ���ز����������ݣ����ϲ���
		m_pSiteData->OnLoadTestSetupDataForMultiple();
		for(unsigned int i = 0; i < m_pSiteData->m_oTestProjectListMultiple.m_uiCountAll; i++)
		{
			m_pTabTestMultiple[i].OnBnClickedButtonReset();
		}
		break;
	case 3:
		// ���ز����������ݣ��������
		m_pSiteData->OnApplyTestSetupDataForSeisMonitor();
		m_oTabTestSeisMonitor.OnBnClickedButtonReset();
		break;
	}
}

/**
* ��ť�����Ӧ��GO
* @param void
* @return void
*/
void CDlgTestSetup::OnBnClickedButtonGO()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	int iActiveTabMultiple;
	switch(iActiveTab)
	{
	case 0:
		try
		{
			if(false == m_oTabTestInstrument.OnBnClickedButtonGO())
			{
				return;
			}
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}	
		// ����TestSetup����GO֪ͨ����֡����������
		m_pSiteData->OnSendCMDFrameForTestSetupGO(4, m_oTabTestInstrument.m_uiTestNb);
		break;
	case 1:
		try
		{
			if(false == m_oTabTestSensor.OnBnClickedButtonGO())
			{
				return;
			}
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}	
		// ����TestSetup����GO֪ͨ����֡���첨������
		m_pSiteData->OnSendCMDFrameForTestSetupGO(5, m_oTabTestSensor.m_uiTestNb);
		break;
	case 2:
		iActiveTabMultiple = m_oTabWndTestMultiple.GetActiveTab();
		// ����TestSetup����GO֪ͨ����֡���첨������
		m_pSiteData->OnSendCMDFrameForTestSetupGO(6, m_pTabTestMultiple[iActiveTabMultiple].m_uiTestNb);
		break;
	case 3:
		try
		{
			if(false == m_oTabTestSeisMonitor.OnBnClickedButtonGO())
			{
				return;
			}
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}	
		// ����TestSetup����GO֪ͨ����֡���������
		m_pSiteData->OnSendCMDFrameForTestSetupGO(7, 4000);
		break;
	}
}

/**
* ��ť�����Ӧ��Add
* @param void
* @return void
*/
void CDlgTestSetup::OnBnClickedButtonAdd()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabTestInstrument.OnBnClickedButtonAdd();
		break;
	case 1:
		m_oTabTestSensor.OnBnClickedButtonAdd();
		break;
	case 2:
		int iActiveTabMultiple = m_oTabWndTestMultiple.GetActiveTab();
		m_pTabTestMultiple[iActiveTabMultiple].OnBnClickedButtonAdd();
		break;
	}	
}

/**
* ��ť�����Ӧ��Change
* @param void
* @return void
*/
void CDlgTestSetup::OnBnClickedButtonChange()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabTestInstrument.OnBnClickedButtonChange();
		break;
	case 1:
		m_oTabTestSensor.OnBnClickedButtonChange();
		break;
	case 2:
		int iActiveTabMultiple = m_oTabWndTestMultiple.GetActiveTab();
		m_pTabTestMultiple[iActiveTabMultiple].OnBnClickedButtonChange();
		break;
	}
}

/**
* ��ť�����Ӧ��Delete
* @param void
* @return void
*/
void CDlgTestSetup::OnBnClickedButtonDelete()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabTestInstrument.OnBnClickedButtonDelete();
		break;
	case 1:
		m_oTabTestSensor.OnBnClickedButtonDelete();
		break;
	case 2:
		int iActiveTabMultiple = m_oTabWndTestMultiple.GetActiveTab();
		m_pTabTestMultiple[iActiveTabMultiple].OnBnClickedButtonDelete();
		break;
	}
}

/**
* ��ť�����Ӧ��Clear
* @param void
* @return void
*/
void CDlgTestSetup::OnBnClickedButtonClear()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	int iActiveTabMultiple;
	switch(iActiveTab)
	{
	case 0:
		m_oTabTestInstrument.OnBnClickedButtonClear();
		break;
	case 1:
		m_oTabTestSensor.OnBnClickedButtonClear();
		break;
	case 2:
		iActiveTabMultiple = m_oTabWndTestMultiple.GetActiveTab();
		m_pTabTestMultiple[iActiveTabMultiple].OnBnClickedButtonClear();
		break;
	case 3:
		m_oTabTestSeisMonitor.OnBnClickedButtonClear();
		break;
	}
}