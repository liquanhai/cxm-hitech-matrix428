// LostFrameCountDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LostFrameCount.h"
#include "LostFrameCountDlg.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLostFrameCountDlg �Ի���




CLostFrameCountDlg::CLostFrameCountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLostFrameCountDlg::IDD, pParent)
	, m_uiFileStartNb(1)
	, m_uiFileEndNb(0)
	, m_uiSaveADCDataFrameNum(406)
	, m_uiInstrumentTotalNum(48)
	, m_uiInstrumentSampleNum(5)
	, m_uiFrameSize(74)
	, m_csFilePath(_T(""))
	, m_uipLostFrameCount(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CLostFrameCountDlg::~CLostFrameCountDlg()
{
	if (m_uipLostFrameCount != NULL)
	{
		m_uipLostFrameCount = NULL;
		delete m_uipLostFrameCount;
	}
}
void CLostFrameCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILESTARTNB, m_uiFileStartNb);
	DDX_Text(pDX, IDC_EDIT_FILEENDNB, m_uiFileEndNb);
	DDX_Text(pDX, IDC_EDIT_SAVEADCDATANUM, m_uiSaveADCDataFrameNum);
	DDX_Text(pDX, IDC_EDIT_INSTRUMENTTOTALNUM, m_uiInstrumentTotalNum);
	DDX_Text(pDX, IDC_EDIT_INSTRUMENTSAMPLENUM, m_uiInstrumentSampleNum);
	DDX_Text(pDX, IDC_EDIT_FRAMESIZE, m_uiFrameSize);
}

BEGIN_MESSAGE_MAP(CLostFrameCountDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CALLOSTDATAFRAME, &CLostFrameCountDlg::OnBnClickedButtonCallostdataframe)
	ON_BN_CLICKED(IDC_BUTTON_FILEPATH, &CLostFrameCountDlg::OnBnClickedButtonFilepath)
END_MESSAGE_MAP()


// CLostFrameCountDlg ��Ϣ�������

BOOL CLostFrameCountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

void CLostFrameCountDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLostFrameCountDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLostFrameCountDlg::OnBnClickedButtonCallostdataframe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_csFilePath == _T(""))
	{
		AfxMessageBox(_T("��ѡ��������ݴ洢Ŀ¼��"));
		return;
	}
	if (m_uiFileEndNb < m_uiFileStartNb)
	{
		AfxMessageBox(_T("��������ȷ���ļ�������ţ�"));
		return;
	}
	if ((m_uiInstrumentTotalNum < m_uiInstrumentSampleNum) && (m_uiInstrumentSampleNum == 0))
	{
		AfxMessageBox(_T("��������ȷ�Ĳ����豸������"));
		return;
	}
	// ��ս����ʾ
	GetDlgItem(IDC_EDIT_RESULTSHOW)->SetWindowText(_T(""));
	// ���㶪ʧ֡����
	OnCalLostDataFrameNum();
}

void CLostFrameCountDlg::OnBnClickedButtonFilepath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szDir[MAX_PATH];

	BROWSEINFO bi;

	ITEMIDLIST *pidl;

	bi.hwndOwner = this->m_hWnd; // ָ�������ڣ��ڶԻ�����ʾ�ڼ䣬�����ڽ������� 


	bi.pidlRoot = NULL; // ���ָ��NULL�����ԡ����桱Ϊ�� 

	bi.pszDisplayName = szDir; 

	bi.lpszTitle = _T("��ѡ��������ݴ洢Ŀ¼"); // ��һ�н���ʾ�ڶԻ���Ķ��� 

	bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;

	bi.lpfn = NULL;

	bi.lParam = 0;

	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi);

	if(pidl == NULL) 
	{
		return;
	}
	if(!SHGetPathFromIDList(pidl, szDir))
	{	
		return;
	}
	else
	{
		m_csFilePath = szDir;
	}
}

// ���㶪ʧ����֡����
void CLostFrameCountDlg::OnCalLostDataFrameNum(void)
{
	CString strOutput = _T("");
	CString strtmp = _T("");
	m_uipLostFrameCount = NULL;
	m_uipLostFrameCount = new unsigned int[m_uiInstrumentSampleNum];
	// ��ս����ʾ
	GetDlgItem(IDC_EDIT_RESULTSHOW)->SetWindowText(_T(""));
	for (unsigned int i=0; i<m_uiInstrumentSampleNum; i++)
	{
		m_uipLostFrameCount[i] = 0;
	}
	if (m_uiFileStartNb == m_uiFileEndNb)
	{
		// �������һ������������ļ�
		OnCalLastFile(m_uiFileEndNb);
	}
	else if (m_uiFileEndNb > m_uiFileStartNb)
	{
		for (unsigned int i=m_uiFileStartNb; i<m_uiFileEndNb; i++)
		{
			// �����Զ�������������ļ�
			OnCalFinishFile(i);
		}
		// �������һ������������ļ�
		OnCalLastFile(m_uiFileEndNb);
	}
	// ��ӡ������
	for (unsigned int i=0; i<m_uiInstrumentSampleNum; i++)
	{
		strtmp.Format(_T("����%d ��֡����Ϊ%d\r\n"), (i+1), m_uipLostFrameCount[i]);
		strOutput += strtmp;
	}
	GetDlgItem(IDC_EDIT_RESULTSHOW)->SetWindowText(strOutput);
}

// �������һ������������ļ�
void CLostFrameCountDlg::OnCalLastFile(unsigned int uiLastFileNb)
{
	CString strtmp = _T("");
	CString strFilePath = _T("");
// 	strtmp.Format(_T("\\%d.text"), uiLastFileNb);
// 	strFilePath = m_csFilePath + strtmp;
	ifstream fp_str;
	double datatemp = 0.0;
	strtmp.Format(_T("\\%d.text"), uiLastFileNb);
	strFilePath = m_csFilePath + strtmp;
	setlocale(LC_ALL,"Chinese-simplified");//�������Ļ���
	fp_str.open(strFilePath, ios::in);

	if(fp_str.fail())
	{
		::AfxMessageBox(_T("�����ݴ洢�ļ�����"));
		return;
	}
	else
	{
		char wholeline[1024];
		unsigned int * uipZeroCount = NULL;
		uipZeroCount = new unsigned int[m_uiInstrumentSampleNum];
		unsigned int uiDataNum = 0;
		unsigned int uitmp = 0;
		for (unsigned int i=0; i<m_uiInstrumentSampleNum; i++)
		{
			uipZeroCount[i] = 0;
		}
		uiDataNum = m_uiInstrumentSampleNum * m_uiFrameSize * m_uiSaveADCDataFrameNum; 
		fp_str.getline(wholeline, 1024, '\n');
		fp_str.getline(wholeline, 1024, '\n');
		fp_str.getline(wholeline, 1024, '\n');
		for (unsigned int m=0; m<uiDataNum; m++)
		{
			fp_str >>datatemp;
			uitmp = m % m_uiInstrumentSampleNum;
			if (datatemp == 0)
			{
				uipZeroCount[uitmp]++;
			}
			else
			{
				uipZeroCount[uitmp] = 0;
			}
			if (uipZeroCount[uitmp] == m_uiFrameSize)
			{
				uipZeroCount[uitmp] = 0;
				m_uipLostFrameCount[uitmp]++;
			}
		}
		fp_str.close();
		uipZeroCount = NULL;
		delete uipZeroCount;
	}
}

// �����Զ�������������ļ�
void CLostFrameCountDlg::OnCalFinishFile(unsigned int uiFinishFileNb)
{
	CString strtmp = _T("");
	CString strFilePath = _T("");
	ifstream fp_str;
	double datatemp = 0.0;
	strtmp.Format(_T("\\%d.text"), uiFinishFileNb);
	strFilePath = m_csFilePath + strtmp;
	setlocale(LC_ALL,"Chinese-simplified");//�������Ļ���
	fp_str.open(strFilePath, ios::in);

	if(fp_str.fail())
	{
		::AfxMessageBox(_T("�����ݴ洢�ļ�����"));
		return;
	}
	else
	{
		char wholeline[1024];
		unsigned int * uipZeroCount = NULL;
		uipZeroCount = new unsigned int[m_uiInstrumentSampleNum];
		unsigned int uiDataNum = 0;
		unsigned int uitmp = 0;
		for (unsigned int i=0; i<m_uiInstrumentSampleNum; i++)
		{
			uipZeroCount[i] = 0;
		}
		uiDataNum = m_uiInstrumentSampleNum * m_uiFrameSize * m_uiSaveADCDataFrameNum; 
		fp_str.getline(wholeline, 1024, '\n');
		fp_str.getline(wholeline, 1024, '\n');
		fp_str.getline(wholeline, 1024, '\n');
		for (unsigned int m=0; m<uiDataNum; m++)
		{
			fp_str >>datatemp;
			uitmp = m % m_uiInstrumentSampleNum;
			if (datatemp == 0)
			{
				uipZeroCount[uitmp]++;
			}
			else
			{
				uipZeroCount[uitmp] = 0;
			}
			if (uipZeroCount[uitmp] == m_uiFrameSize)
			{
				uipZeroCount[uitmp] = 0;
				m_uipLostFrameCount[uitmp]++;
			}
		}
		fp_str.close();
		uipZeroCount = NULL;
		delete uipZeroCount;
	}
}
