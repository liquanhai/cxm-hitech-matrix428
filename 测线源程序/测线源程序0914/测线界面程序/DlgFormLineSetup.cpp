// DlgFormLineSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "DlgFormLineSetup.h"


// CDlgFormLineSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgFormLineSetup, CDialog)

CDlgFormLineSetup::CDlgFormLineSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFormLineSetup::IDD, pParent)
{

}

CDlgFormLineSetup::~CDlgFormLineSetup()
{
}

void CDlgFormLineSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFormLineSetup, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgFormLineSetup::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgFormLineSetup::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CDlgFormLineSetup::OnBnClickedButtonGO)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgFormLineSetup::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgFormLineSetup::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgFormLineSetup::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

// CDlgFormLineSetup ��Ϣ�������

/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgFormLineSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect oRect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	pWnd->GetWindowRect(&oRect);
	ScreenToClient(&oRect);

	m_oTabWnd.Create(CBCGPTabWnd::STYLE_3D, oRect, this, 1, CBCGPTabWnd::LOCATION_TOP);	// ����ҳ����

	m_oTabFormLine.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabFormLine.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 1);	// ����ҳFormLine

	m_oTabWnd.AddTab(&m_oTabFormLine, "    FormLine    ");	// ����ҳFormLine

	m_oTabWnd.RecalcLayout();
	m_oTabWnd.HideSingleTab(TRUE);

	OnBnClickedButtonReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/**
* OnClose()
* @param void
* @return void
*/
void CDlgFormLineSetup::OnClose()
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
void CDlgFormLineSetup::OnBnClickedButtonApply()
{
	try
	{
		m_oTabFormLine.OnBnClickedButtonApply();
	}
	catch (CException* e)
	{
		AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
		return;
	}

	// ����FormLine�������ݣ�Apply
	m_pSiteData->OnApplyFormLineSetupData();
}

/**
* ��ť�����Ӧ��Reset
* @param void
* @return void
*/
void CDlgFormLineSetup::OnBnClickedButtonReset()
{
	// ����FormLine��������
	m_pSiteData->OnLoadFormLineSetupData();
	m_oTabFormLine.OnBnClickedButtonReset();
}

/**
* ��ť�����Ӧ��GO
* @param void
* @return void
*/
void CDlgFormLineSetup::OnBnClickedButtonGO()
{
	try
	{
		if(false == m_oTabFormLine.OnBnClickedButtonGO())
		{
			return;
		}
	}
	catch (CException* e)
	{
		AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
		return;
	}	
	// ����FormLine����GO֪ͨ����֡
	m_pSiteData->OnSendFormLineCMDFrameGO(m_oTabFormLine.m_oFormLineData.m_uiSN);
}

/**
* ��ť�����Ӧ��Add
* @param void
* @return void
*/
void CDlgFormLineSetup::OnBnClickedButtonAdd()
{

	m_oTabFormLine.OnBnClickedButtonAdd();
}

/**
* ��ť�����Ӧ��Change
* @param void
* @return void
*/
void CDlgFormLineSetup::OnBnClickedButtonChange()
{
	m_oTabFormLine.OnBnClickedButtonChange();
}

/**
* ��ť�����Ӧ��Delete
* @param void
* @return void
*/
void CDlgFormLineSetup::OnBnClickedButtonDelete()
{
	m_oTabFormLine.OnBnClickedButtonDelete();
}

/**
*  ��Ӧ����ͼ����ͼ�����˵�FormLine����
* @param unsigned int uiInstrumentType �������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �����豸��
* @return void
*/
void CDlgFormLineSetup::OnGraphViewInstrumentFormLine(unsigned int uiInstrumentType, unsigned int uiSN)
{
	m_oTabFormLine.OnGraphViewInstrumentFormLine(uiInstrumentType, uiSN);
}