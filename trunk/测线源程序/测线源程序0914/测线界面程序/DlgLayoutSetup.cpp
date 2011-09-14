// DlgMarkerSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "DlgLayoutSetup.h"


// CDlgLayoutSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgLayoutSetup, CDialog)

CDlgLayoutSetup::CDlgLayoutSetup(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLayoutSetup::IDD, pParent)
{

}

CDlgLayoutSetup::~CDlgLayoutSetup()
{
}

void CDlgLayoutSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLayoutSetup, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgLayoutSetup::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgLayoutSetup::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgLayoutSetup::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgLayoutSetup::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgLayoutSetup::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlgLayoutSetup::OnBnClickedButtonClear)
END_MESSAGE_MAP()

// CDlgLayoutSetup ��Ϣ�������

/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgLayoutSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �õ�Tab����
	CRect oRect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	pWnd->GetWindowRect(&oRect);
	ScreenToClient(&oRect);

	// ����Tabҳ����
	m_oTabWnd.Create(CBCGPTabWnd::STYLE_3D, oRect, this, 1, CBCGPTabWnd::LOCATION_TOP);

	// ��������ҳ��ǵ�
	m_oTabMarker.m_pSiteData = m_pSiteData;
	m_oTabMarker.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 1);
	// �������ҳ��ǵ�
	m_oTabWnd.AddTab(&m_oTabMarker, "    Marker    ");

	// ��������ҳ������
	m_oTabAux.m_pSiteData = m_pSiteData;
	m_oTabAux.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 2);
	// �������ҳ��ǵ�
	m_oTabWnd.AddTab(&m_oTabAux, "    Aux    ");

	// ��������ҳ�ػص�
	m_oTabDetour.m_pSiteData = m_pSiteData;
	m_oTabDetour.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 3);
	// �������ҳ�ػص�
	m_oTabWnd.AddTab(&m_oTabDetour, "    Detour    ");

	// ��������ҳ�Ƶ�
	m_oTabMute.m_pSiteData = m_pSiteData;
	m_oTabMute.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 4);
	// �������ҳ�Ƶ�
	m_oTabWnd.AddTab(&m_oTabMute, "    Mute    ");

	// ��������ҳ��ը��������
	m_oTabBlastMachine.m_pSiteData = m_pSiteData;
	m_oTabBlastMachine.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 5);
	// �������ҳ��ը��������
	m_oTabWnd.AddTab(&m_oTabBlastMachine, "    BlastMachine    ");

	// ��ʾ
	m_oTabWnd.RecalcLayout();
	m_oTabWnd.SetActiveTab(0);

	// ���ر�ǵ���������
	m_pSiteData->OnLoadLayoutSetupDataOfMarker();
	// ���ظ�������������
	m_pSiteData->OnLoadLayoutSetupDataOfAux();
	// �����ػص���������
	m_pSiteData->OnLoadLayoutSetupDataOfDetour();
	// �����Ƶ���������
	m_pSiteData->OnLoadLayoutSetupDataOfMute();
	// ���ر�ը����������������
	m_pSiteData->OnLoadLayoutSetupDataOfBlastMachine();

	m_oTabMarker.OnBnClickedButtonReset();
	m_oTabAux.OnBnClickedButtonReset();
	m_oTabDetour.OnBnClickedButtonReset();
	m_oTabMute.OnBnClickedButtonReset();
	m_oTabBlastMachine.OnBnClickedButtonReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/**
* OnClose()
* @param void
* @return void
*/
void CDlgLayoutSetup::OnClose()
{
	ShowWindow(SW_HIDE);
}

/**
* ��ť�����Ӧ��Apply
* @param void
* @return void
*/
void CDlgLayoutSetup::OnBnClickedButtonApply()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		try
		{
			m_oTabMarker.OnBnClickedButtonApply();
			// Apply��ǵ���������
			m_pSiteData->OnApplyLayoutSetupDataOfMarker();
			// ���ͱ�ǵ��������ݱ仯֪ͨ����֡
			m_pSiteData->OnSendCMDFrameForApplyLayoutSetupDataOfMarker();
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
			m_oTabAux.OnBnClickedButtonApply();
			// Apply��������������
			m_pSiteData->OnApplyLayoutSetupDataOfAux();
			// ���͸������������ݱ仯֪ͨ����֡
			m_pSiteData->OnSendCMDFrameForApplyLayoutSetupDataOfAux();
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
			m_oTabDetour.OnBnClickedButtonApply();
			// Apply�ػص���������
			m_pSiteData->OnApplyLayoutSetupDataOfDetour();
			// �����ػص��������ݱ仯֪ͨ����֡
			m_pSiteData->OnSendCMDFrameForApplyLayoutSetupDataOfDetour();
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
			m_oTabMute.OnBnClickedButtonApply();
			// Apply�Ƶ���������
			m_pSiteData->OnApplyLayoutSetupDataOfMute();
			// �����Ƶ��������ݱ仯֪ͨ����֡
			m_pSiteData->OnSendCMDFrameForApplyLayoutSetupDataOfMute();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}
		break;
	case 4:
		try
		{
			m_oTabBlastMachine.OnBnClickedButtonApply();
			// Apply��ը����������������
			m_pSiteData->OnApplyLayoutSetupDataOfBlastMachine();
			// ���ͱ�ը���������������ݱ仯֪ͨ����֡
			m_pSiteData->OnSendCMDFrameForApplyLayoutSetupDataOfBlastMachine();
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
void CDlgLayoutSetup::OnBnClickedButtonReset()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		// ���ر�ǵ���������
		m_pSiteData->OnLoadLayoutSetupDataOfMarker();
		m_oTabMarker.OnBnClickedButtonReset();
		break;
	case 1:
		// ���ظ�������������
		m_pSiteData->OnLoadLayoutSetupDataOfAux();
		m_oTabAux.OnBnClickedButtonReset();
		break;
	case 2:
		// �����ػص���������
		m_pSiteData->OnLoadLayoutSetupDataOfDetour();
		m_oTabDetour.OnBnClickedButtonReset();
		break;
	case 3:
		// �����Ƶ���������
		m_pSiteData->OnLoadLayoutSetupDataOfMute();
		m_oTabMute.OnBnClickedButtonReset();
		break;
	case 4:
		// ���ر�ը����������������
		m_pSiteData->OnLoadLayoutSetupDataOfBlastMachine();
		m_oTabBlastMachine.OnBnClickedButtonReset();
		break;
	}
}

/**
* ��ť�����Ӧ��Add
* @param void
* @return void
*/
void CDlgLayoutSetup::OnBnClickedButtonAdd()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabMarker.OnBnClickedButtonAdd();
		break;
	case 1:
		m_oTabAux.OnBnClickedButtonAdd();
		break;
	case 2:
		m_oTabDetour.OnBnClickedButtonAdd();
		break;
	case 3:
		m_oTabMute.OnBnClickedButtonAdd();
		break;
	case 4:
		m_oTabBlastMachine.OnBnClickedButtonAdd();
		break;
	}
}

/**
* ��ť�����Ӧ��Change
* @param void
* @return void
*/
void CDlgLayoutSetup::OnBnClickedButtonChange()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabMarker.OnBnClickedButtonChange();
		break;
	case 1:
		m_oTabAux.OnBnClickedButtonChange();
		break;
	case 2:
		m_oTabDetour.OnBnClickedButtonChange();
		break;
	case 3:
		m_oTabMute.OnBnClickedButtonChange();
		break;
	case 4:
		m_oTabBlastMachine.OnBnClickedButtonChange();
		break;
	}
}

/**
* ��ť�����Ӧ��Delete
* @param void
* @return void
*/
void CDlgLayoutSetup::OnBnClickedButtonDelete()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabMarker.OnBnClickedButtonDelete();
		break;
	case 1:
		m_oTabAux.OnBnClickedButtonDelete();
		break;
	case 2:
		m_oTabDetour.OnBnClickedButtonDelete();
		break;
	case 3:
		m_oTabMute.OnBnClickedButtonDelete();
		break;
	case 4:
		m_oTabBlastMachine.OnBnClickedButtonDelete();
		break;
	}
}

/**
* ��ť�����Ӧ��Clear
* @param void
* @return void
*/
void CDlgLayoutSetup::OnBnClickedButtonClear()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabMarker.OnBnClickedButtonClear();
		break;
	case 1:
		m_oTabAux.OnBnClickedButtonClear();
		break;
	case 2:
		m_oTabDetour.OnBnClickedButtonClear();
		break;
	case 3:
		m_oTabMute.OnBnClickedButtonClear();
		break;
	case 4:
		m_oTabBlastMachine.OnBnClickedButtonClear();
		break;
	}
}

/**
* ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
* @param unsigned int uiInstrumentType �������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �����豸��
* @return void
*/
void CDlgLayoutSetup::OnGraphViewInstrumentSetMarker(unsigned int uiInstrumentType, unsigned int uiSN)
{
	m_oTabMarker.OnGraphViewInstrumentSetMarker(uiInstrumentType, uiSN);
}

/**
* ��Ӧ����ͼ����ͼ�����˵����ø�����
* @param unsigned int uiInstrumentType �������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �����豸��
* @return void
*/
void CDlgLayoutSetup::OnGraphViewInstrumentSetAuxiliary(unsigned int uiInstrumentType, unsigned int uiSN)
{
	m_oTabAux.OnGraphViewInstrumentSetAuxiliary(uiInstrumentType, uiSN);
}

/**
* ��Ӧ����ͼ����ͼ�����˵������ػص�
* @param unsigned int uiInstrumentType �Ͷ��������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �Ͷ������豸��
* @param unsigned int uiInstrumentType �߶��������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �߶������豸��
* @return void
*/
void CDlgLayoutSetup::OnGraphViewInstrumentSetDetour(unsigned int uiInstrumentTypeLow, unsigned int uiSNLow, unsigned int uiInstrumentTypeHigh, unsigned int uiSNHight)
{
	m_oTabDetour.OnGraphViewInstrumentSetDetour(uiInstrumentTypeLow, uiSNLow, uiInstrumentTypeHigh, uiSNHight);
}

/**
* ��Ӧ�첨��ͼ����ͼ�����˵�Mute����
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint	����
* @return void
*/
void CDlgLayoutSetup::OnGraphViewSensorSetMute(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	m_oTabMute.OnGraphViewSensorSetMute(uiNbLine, uiNbPoint);
}