// DlgSPSSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Config.h"
#include "DlgSPSSetup.h"
#include "..\common\ConfigParseXML.h"

// DlgSPSSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgSPSSetup, CBCGPDialog)

CDlgSPSSetup::CDlgSPSSetup(CWnd* pParent /*=NULL*/)
: CBCGPDialog(CDlgSPSSetup::IDD, pParent)
, m_csSPSRFilePath(_T(""))
, m_csSPSXFilePath(_T(""))
{
	EnableVisualManagerStyle();
	m_csLocalOptXMLFile = CLIENTDIR_XMLFILE;
	m_csLocalOptXMLFile += OPERATION_XMLFILE;
	m_csLocalLineXMLFile = CLIENTDIR_XMLFILE;
	m_csLocalLineXMLFile += MATRIX_XMLFILE;
}

CDlgSPSSetup::~CDlgSPSSetup()
{
}

void CDlgSPSSetup::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSPSSetup, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTNLOADSPS, &CDlgSPSSetup::OnBnClickedBtnloadsps)
	ON_BN_CLICKED(IDC_BTNGENOPTXML, &CDlgSPSSetup::OnBnClickedBtngenoptxml)
	ON_BN_CLICKED(IDC_BTNGENLINEXML, &CDlgSPSSetup::OnBnClickedBtngenlinexml)
END_MESSAGE_MAP()

// DlgSPSSetup ��Ϣ�������

void CDlgSPSSetup::OnBnClickedBtnloadsps()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �������ļ����ҵ�SPS�ļ�Ĭ��·��
	CConfigParseXML  ParseXML;
	ParseXML.ParseSPSFile(theApp.m_strLocalXMLFile, m_csSPSRFilePath, m_csSPSXFilePath);
	// ����·��������ȷ��ȡ�ļ����Ϊ�ֶ�����SPS�ļ�
	if (FALSE == m_oFraseSPSToXML.LoadSPSFile(m_csSPSRFilePath, m_csSPSXFilePath))
	{
		// ����SPS�ļ�·��
		OnSelectSPSRFilePath();
		OnSelectSPSXFilePath();
		if (TRUE == m_oFraseSPSToXML.LoadSPSFile(m_csSPSRFilePath, m_csSPSXFilePath))
		{
			// ��SPS�ļ�·�����浽config�����ļ���
			ParseXML.WriteSPSFile(theApp.m_strLocalXMLFile, m_csSPSRFilePath, m_csSPSXFilePath);
			// �������ļ��ϴ���FTP
			PutMatrixXMLToFTPServer(theApp.m_strFTPServerIP,CONFIG_XMLFILE,theApp.m_strLocalXMLFile);
			// ������Ϣ֪ͨ���ص���������
			::SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_CONFIG,MATRIX_CONFIG_SPSSETUP);
		}
	}
}

void CDlgSPSSetup::OnBnClickedBtngenoptxml()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oFraseSPSToXML.SaveOperationXML(m_csLocalOptXMLFile);
	// �������ļ��ϴ���FTP
	PutMatrixXMLToFTPServer(theApp.m_strFTPServerIP,OPERATION_XMLFILE,m_csLocalOptXMLFile);
	// ������Ϣ֪ͨ���ص���������
	::SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_OPERATION,MATRIX_OPERATION_ALL);
}

void CDlgSPSSetup::OnBnClickedBtngenlinexml()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oFraseSPSToXML.SaveLineXML(m_csLocalLineXMLFile);
	// �������ļ��ϴ���FTP
	PutMatrixXMLToFTPServer(theApp.m_strFTPServerIP,MATRIX_XMLFILE,m_csLocalLineXMLFile);
	// ������Ϣ֪ͨ���ص���������
	::SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_LINE,MATRIX_LINE_ALL);
}

// ����SPS_R�ļ�·��
void CDlgSPSSetup::OnSelectSPSRFilePath(void)
{
	// ���ļ�
	const wchar_t pszFilter[] = _T("SPS_R�ļ�(*.R)|*.R|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".R"), _T("JO.R"), OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT, pszFilter, this);
	if ( dlg.DoModal()!=IDOK )
	{
		return;
	}
	m_csSPSRFilePath = dlg.GetPathName();
}

// ����SPS_X�ļ�·��
void CDlgSPSSetup::OnSelectSPSXFilePath(void)
{
	// ���ļ�
	const wchar_t pszFilter[] = _T("SPS_X�ļ�(*.X)|*.X|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".X"), _T("JO.X"), OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT, pszFilter, this);

	if ( dlg.DoModal()!=IDOK )
	{
		return;
	}
	m_csSPSXFilePath = dlg.GetPathName();
}
