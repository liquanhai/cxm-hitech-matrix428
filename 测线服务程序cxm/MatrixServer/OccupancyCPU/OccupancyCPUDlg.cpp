
// OccupancyCPUDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OccupancyCPU.h"
#include "OccupancyCPUDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COccupancyCPUDlg �Ի���




COccupancyCPUDlg::COccupancyCPUDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COccupancyCPUDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pThreadArray = NULL;
	m_uiThreadNum = 1;
}

void COccupancyCPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COccupancyCPUDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_START, &COccupancyCPUDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &COccupancyCPUDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// COccupancyCPUDlg ��Ϣ�������

BOOL COccupancyCPUDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetDlgItemInt(IDC_COMBO_THREAD_NUM, m_uiThreadNum);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COccupancyCPUDlg::OnPaint()
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
HCURSOR COccupancyCPUDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COccupancyCPUDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnBnClickedButtonStop();
	CDialogEx::OnClose();
}


void COccupancyCPUDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_uiThreadNum = GetDlgItemInt(IDC_COMBO_THREAD_NUM);
	if (m_uiThreadNum == 0)
	{
		return;
	}
	m_pThreadArray = new CThread[m_uiThreadNum];
	for (int i=0; i<m_uiThreadNum; i++)
	{
		m_pThreadArray[i].CreateThread();
	}
}


void COccupancyCPUDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pThreadArray != NULL)
	{
		for (int i=0; i<m_uiThreadNum; i++)
		{
			m_pThreadArray[i].Close();
		}
		Sleep(100);
		delete[] m_pThreadArray;
		m_pThreadArray = NULL;
	}
}
