// ShowThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�˿ڼ�����.h"
#include "ShowThread.h"
#include "Parameter.h"

// CShowThread

IMPLEMENT_DYNCREATE(CShowThread, CWinThread)

CShowThread::CShowThread()
{
}

CShowThread::~CShowThread()
{
}

BOOL CShowThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CShowThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CShowThread, CWinThread)
END_MESSAGE_MAP()


// CShowThread ��Ϣ�������
// ��ʼ��

void CShowThread::Init()
{
	m_close = false;
	m_icsEditShowLength = 0;
}
// �̺߳�����Run��ִ��
int CShowThread::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_close == true)
		{
			break;
		}
		CString strtemp1;
		CString strtemp2;
// 		strtemp1 = m_csEditShow;
// 		if (m_icsEditShowLength < strtemp1.GetLength())
// 		{
// 			m_icsEditShowLength = strtemp1.GetLength();
// 			pDlg->GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(strtemp1);
// 		}
		strtemp2 = m_csSaveFile;
		if (strtemp2.GetLength()> (pDlg->m_iSaveSize*1024))
		{	
			pDlg->OnSaveToFile();
		}
		if (m_close == true)
		{
			break;
		}
		Sleep(250);
	}


	// ����
	return CWinThread::Run();
}
void CShowThread::OnClose()
{
	m_close = true;
}
