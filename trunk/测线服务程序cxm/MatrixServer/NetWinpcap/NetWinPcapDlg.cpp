
// NetWinPcapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetWinPcap.h"
#include "NetWinPcapDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetWinPcapDlg �Ի���




CNetWinPcapDlg::CNetWinPcapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetWinPcapDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetWinPcapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetWinPcapDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CNetWinPcapDlg ��Ϣ�������

BOOL CNetWinPcapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_oNetPcapComm.OnInit();
	m_oPcapRcvThread.m_pNetPcapComm = &m_oNetPcapComm;
	m_oPcapRcvThread.OnInit();
	m_oPcapSndThread.m_pNetPcapComm = &m_oNetPcapComm;
	m_oPcapSndThread.OnInit();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetWinPcapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNetWinPcapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// �����в�������
void CNetWinPcapDlg::PhraseCommandLine(CString str)
{
	int iPos = 0;
	int iCount = 0;
	CString strCmd = _T("");
	CString strTemp = _T("");
	iPos = str.Find('=');
	strCmd = str.Left(iPos);
	strTemp = str.Right(str.GetLength() - (iPos + 1));
	if (strCmd == _T("NetCardId"))	// ������ţ���0��ʼ
	{
		m_oNetPcapComm.m_uiNetCardId = _ttoi(strTemp);
	}
	else if (strCmd == _T("DownStreamRcvSndPort"))
	{
		str = strTemp;
		while(1)
		{
			iPos = str.Find(',');
			if (iPos == -1)
			{
				m_oNetPcapComm.PhraseRcvSndPort(str, &m_oNetPcapComm.m_oDownStreamRcvSndPortMap);
				break;
			}
			strTemp = str.Left(iPos);

			m_oNetPcapComm.PhraseRcvSndPort(strTemp, &m_oNetPcapComm.m_oDownStreamRcvSndPortMap);
			str = str.Right(str.GetLength() - (iPos + 1));
		}
	}
	else if (strCmd == _T("UpStreamRcvSndPort"))
	{
		str = strTemp;
		while(1)
		{
			iPos = str.Find(',');
			if (iPos == -1)
			{
				m_oNetPcapComm.PhraseRcvSndPort(str, &m_oNetPcapComm.m_oUpStreamRcvSndPortMap);
				break;
			}
			strTemp = str.Left(iPos);

			m_oNetPcapComm.PhraseRcvSndPort(strTemp, &m_oNetPcapComm.m_oUpStreamRcvSndPortMap);
			str = str.Right(str.GetLength() - (iPos + 1));
		}
	}
	else if (strCmd == _T("NetDownStreamSrcPort"))
	{
		m_oNetPcapComm.m_usPcapDownStreamSrcPort = htons(_ttoi(strTemp));
	}
	else if (strCmd == _T("NetUpStreamSrcPort"))
	{
		m_oNetPcapComm.m_usPcapUpStreamSrcPort = htons(_ttoi(strTemp));
	}
	else if (strCmd == _T("WinpcapBufSize"))
	{
		m_oNetPcapComm.m_uiPcapBufSize = _ttoi(strTemp);
	}
	else if (strCmd == _T("DownStreamIP"))
	{
		m_oNetPcapComm.m_uiDownStreamIP = inet_addr((CStringA)strTemp);
	}
	else if (strCmd == _T("UpStreamIP"))
	{
		m_oNetPcapComm.m_uiUpStreamIP = inet_addr((CStringA)strTemp);
	}
	else if (strCmd == _T("NetIP"))
	{
		m_oNetPcapComm.m_uiNetIP = inet_addr((CStringA)strTemp);
	}
	else if (strCmd == _T("DownStreamMacAddr"))
	{
		str = strTemp;
		while(1)
		{
			iPos = str.Find(',');
			if (iPos == -1)
			{
				m_oNetPcapComm.m_ucDownStreamMacAddr[iCount] = _ttoi(str);
				break;
			}
			strTemp = str.Left(iPos);
			m_oNetPcapComm.m_ucDownStreamMacAddr[iCount] = _ttoi(strTemp);
			str = str.Right(str.GetLength() - (iPos + 1));
			iCount++;
		}
	}
	else if (strCmd == _T("UpStreamMacAddr"))
	{
		str = strTemp;
		while(1)
		{
			iPos = str.Find(',');
			if (iPos == -1)
			{
				m_oNetPcapComm.m_ucUpStreamMacAddr[iCount] = _ttoi(str);
				break;
			}
			strTemp = str.Left(iPos);
			m_oNetPcapComm.m_ucUpStreamMacAddr[iCount] = _ttoi(strTemp);
			str = str.Right(str.GetLength() - (iPos + 1));
			iCount++;
		}
	}
	else if (strCmd == _T("NetMacAddr"))
	{
		str = strTemp;
		while(1)
		{
			iPos = str.Find(',');
			if (iPos == -1)
			{
				m_oNetPcapComm.m_ucNetMacAddr[iCount] = _ttoi(str);
				break;
			}
			strTemp = str.Left(iPos);
			m_oNetPcapComm.m_ucNetMacAddr[iCount] = _ttoi(strTemp);
			str = str.Right(str.GetLength() - (iPos + 1));
			iCount++;
		}
	}
	else if (strCmd == _T("MaxPackageSize"))
	{
		m_oNetPcapComm.m_uiPcapPacketMaxSize = _ttoi(strTemp);
	}
	else if (strCmd == _T("PcapTimeOut"))
	{
		m_oNetPcapComm.m_uiPcapTimeOut = _ttoi(strTemp);
	}
	else if (strCmd == _T("PcapQueueSize"))
	{
		m_oNetPcapComm.m_uiPcapQueueSize = _ttoi(strTemp);
	}
	else if (strCmd == _T("PcapSndWaitTime"))
	{
		m_oPcapSndThread.m_uiThreadSleepTime = _ttoi(strTemp);
	}
	else if (strCmd == _T("PcapRcvWaitTime"))
	{
		m_oPcapRcvThread.m_uiThreadSleepTime = _ttoi(strTemp);
	}
}
// ���ضԻ���������
void CNetWinPcapDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	// TODO: �ڴ˴������Ϣ����������
// 	if(lpwndpos-> flags & SWP_SHOWWINDOW)
// 	{
// 		lpwndpos-> flags &= ~SWP_SHOWWINDOW;
// 		PostMessage(WM_WINDOWPOSCHANGING, 0, (LPARAM)lpwndpos); 
// 		ShowWindow(SW_HIDE); 
// 	} 
// 	else
// 	{
		CDialogEx::OnWindowPosChanging(lpwndpos);
//	}
}


void CNetWinPcapDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_oPcapRcvThread.OnClose();
	m_oPcapSndThread.OnClose();
	m_oNetPcapComm.OnClose();
	CDialogEx::OnClose();
}
