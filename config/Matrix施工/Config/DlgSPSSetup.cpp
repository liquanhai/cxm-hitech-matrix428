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
, m_csSPSFilePath(_T(""))
{
	EnableVisualManagerStyle();
	m_csLocalOptXMLFile = CLIENTDIR_XMLFILE;
	m_csLocalOptXMLFile += OPERATION_XMLFILE;
	m_csLocalLineXMLFile = CLIENTDIR_XMLFILE;
	m_csLocalLineXMLFile += MATRIX_XMLFILE;
	m_csLocalLineInitTXTFile = CLIENTDIR_XMLFILE;
	m_csLocalLineInitTXTFile += LINEINIT_TXTFILE;
	GetCurrentDirectory(MAX_PATH, m_wcExeCurrentPath);
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
END_MESSAGE_MAP()

// DlgSPSSetup ��Ϣ�������

void CDlgSPSSetup::OnBnClickedBtnloadsps()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CConfigParseXML  ParseXML;
	// ����SPS�ļ�·��
	OnSelectSPSFilePath();
	// ���ص�����ǰ·��
	SetCurrentDirectory(m_wcExeCurrentPath);
	// �ֶ�����SPS�ļ�������ȷ��ȡ�ļ����ΪĬ��·���²���
	if (FALSE == m_oFraseSPSToXML.LoadSPSFile(m_csSPSFilePath + _T(".R"), m_csSPSFilePath + _T(".X")))
	{
		// �������ļ����ҵ�SPS�ļ�Ĭ��·��
		ParseXML.ParseSPSFile(theApp.m_strLocalXMLFile, m_csSPSFilePath);
		if (FALSE == m_oFraseSPSToXML.LoadSPSFile(m_csSPSFilePath + _T(".R"), m_csSPSFilePath + _T(".X")))
		{
			AfxMessageBox(_T("Please push this button again to find the correct sps file Path!"));
		}
		else
		{
			AfxMessageBox(_T("Open the sps file by default path!"));
		}
	}
	else
	{
		// ��SPS�ļ�·�����浽config�����ļ���
		ParseXML.WriteSPSFile(theApp.m_strLocalXMLFile, m_csSPSFilePath);
		// �������ļ��ϴ���FTP
		PutMatrixXMLToFTPServer(theApp.m_strFTPServerIP,CONFIG_XMLFILE,theApp.m_strLocalXMLFile);
		// ������Ϣ֪ͨ���ص���������
		::SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_CONFIG,MATRIX_CONFIG_SPSSETUP);
	}
	OnGenLineInitTXT();
	OnGenOptXML();
	OnGenLineXML();
}
// ����ʩ��XML
void CDlgSPSSetup::OnGenOptXML()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oFraseSPSToXML.SaveOperationXML(m_csLocalOptXMLFile);
	// �������ļ��ϴ���FTP
	PutMatrixXMLToFTPServer(theApp.m_strFTPServerIP,OPERATION_XMLFILE,m_csLocalOptXMLFile);
	// ������Ϣ֪ͨ���ص���������
	::SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_OPERATION,MATRIX_OPERATION_ALL);
}
// ���ɲ���XML
void CDlgSPSSetup::OnGenLineXML()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oFraseSPSToXML.SaveLineXML(m_csLocalLineXMLFile);
	// �������ļ��ϴ���FTP
	PutMatrixXMLToFTPServer(theApp.m_strFTPServerIP,MATRIX_XMLFILE,m_csLocalLineXMLFile);
	// ������Ϣ֪ͨ���ص���������
	::SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_LINE,MATRIX_LINE_ALL);
}

// ����SPS�ļ�·��
void CDlgSPSSetup::OnSelectSPSFilePath(void)
{
	// ���ļ�
	CString str = _T("");
	const wchar_t pszFilter[] = _T("SPS�ļ�(*.R)|*.R|SPS�ļ�(*.X)|*.X|SPS�ļ�(*.S)|*.S|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".R"), _T(""), OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT, pszFilter, this);
	m_csSPSFilePath = _T("");
	if ( dlg.DoModal()!=IDOK )
	{
		return;
	}
	str = dlg.GetPathName();
	int iFind = str.ReverseFind(_T('.'));
	m_csSPSFilePath = str.Left(iFind);
}
// ���ɲ��߷��������ļ�
void CDlgSPSSetup::OnGenLineInitTXT()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oFraseSPSToXML.GenLineInitTXT(m_csLocalLineInitTXTFile);
}
