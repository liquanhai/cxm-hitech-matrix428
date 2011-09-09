// OperationServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "OperationServer.h"
#include "OperationServerDlg.h"
#include "..\\common\LineStruct.h"
#include "OperationServerParseXML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��ӵı�ʶֻ����һ�ε�������, �Լ�����һ������ֵ
CString	 g_strProgName = _T("ʩ������");
HANDLE   g_hProgValue = (HANDLE)1;               
// ��EnumWindows�������õĻص��������������Բ��Ҵ���
BOOL CALLBACK EnumWndProc(HWND hwnd,LPARAM lParam)
{
	HANDLE h = GetProp(hwnd,g_strProgName);
	if( h == g_hProgValue)
	{
		*(HWND*)lParam = hwnd;
		return false;
	}
	return true;
}

// COperationServerApp

BEGIN_MESSAGE_MAP(COperationServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// COperationServerApp ����

COperationServerApp::COperationServerApp()
: m_dwFileNumber(SEGDFILENUMBER_INIT)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_dwFDUTime=0;
	m_dwHostIP =0x0100007F;	// 127.0.0.1
	m_dwMainCrossIP = 0xFFFFFFFF;	// 255.255.255.255
	m_wMainCrossPort = 0x5010;
	// ��FTP������������XML�����ļ�
	m_strLocalXMLFile = SERVERDIR_XMLFILE;
	m_strLocalXMLFile += OPERATIONSERVER_XMLFILE;
}


// Ψһ��һ�� COperationServerApp ����

COperationServerApp theApp;


// COperationServerApp ��ʼ��

BOOL COperationServerApp::InitInstance()
{
	HWND oldHWnd = NULL;
	EnumWindows(EnumWndProc,(LPARAM)&oldHWnd);    //ö���������еĴ���
	if(oldHWnd != NULL)
	{		
		::ShowWindow(oldHWnd,SW_SHOWNORMAL);          //�����ҵ���ǰһ������
		::SetForegroundWindow(oldHWnd);                //������Ϊǰ������
		return false;                                  //�˳���������
	}
	
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("Windows OLE library initialization failed!"));
		return FALSE;
	}

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Setting"));

	ParseXMLFile();
	COperationServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int COperationServerApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û��� 
	// ����ȫ�ֵ�SEGD�ļ����
	COperationServerParseXML    ParseXML;	
	ParseXML.WriteLastUsedSEGDFileNumber(m_strLocalXMLFile,GetGlobalFileNumber(FALSE));
	return CWinApp::ExitInstance();
}

BOOL COperationServerApp::ParseXMLFile()
{
	// ---------�������ļ�------------------------------------------
	COperationServerParseXML    ParseXML;
	m_strLocalXMLFile = SERVERDIR_XMLFILE;
	m_strLocalXMLFile += OPERATIONSERVER_XMLFILE;
	if(!ParseXML.ParseServerSetup(m_strLocalXMLFile))
	{		
		return FALSE;
	}	
	// �������ļ��ж�ȡ���ʹ�ã��ϴ�ʹ�ã����ļ���ţ���Ϊ��ǰ��ʼ��SEGD�ļ����
	DWORD dwFileNumber = ParseXML.ParseLastUsedSEGDFileNumber(m_strLocalXMLFile);
	SetGlobalFileNumber(dwFileNumber);
	return TRUE;
}