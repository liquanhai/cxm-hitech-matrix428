
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

}
// ���ضԻ���������
void CNetWinPcapDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	// TODO: �ڴ˴������Ϣ����������
	if(lpwndpos-> flags & SWP_SHOWWINDOW)
	{
		lpwndpos-> flags &= ~SWP_SHOWWINDOW;
		PostMessage(WM_WINDOWPOSCHANGING, 0, (LPARAM)lpwndpos); 
		ShowWindow(SW_HIDE); 
	} 
	else
	{
		CDialog::OnWindowPosChanging(lpwndpos);
	}
}
