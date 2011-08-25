// TestFileOpenSpeedDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�����ļ��򿪶�ȡ�ٶ�.h"
#include "TestFileOpenSpeedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestFileOpenSpeedDlg �Ի���




CTestFileOpenSpeedDlg::CTestFileOpenSpeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestFileOpenSpeedDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pbufRead = NULL;
	m_uiSamplingRate = 2000;
	m_uiFindLineCount = 0;
	m_uiBufSize = 0;
	m_ullPointer = 0;
}

void CTestFileOpenSpeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestFileOpenSpeedDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CTestFileOpenSpeedDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// CTestFileOpenSpeedDlg ��Ϣ�������

BOOL CTestFileOpenSpeedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestFileOpenSpeedDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestFileOpenSpeedDlg::OnPaint()
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
HCURSOR CTestFileOpenSpeedDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestFileOpenSpeedDlg::OnBnClickedButtonTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	CString strOut = _T("");
	CString csOpenFilePath = _T("");
	SYSTEMTIME  sysTime;
	unsigned int uiInstrument = 40;
	unsigned int uiADCDataSize = 10;
	m_uiBufSize = uiInstrument * uiADCDataSize + 2;
	if (m_pbufRead != NULL)
	{
		delete[] m_pbufRead;
	}
	if (m_uiBufSize == 0)
	{
		return;
	}
	m_pbufRead = new wchar_t[m_uiBufSize];
	m_uiFindLineCount = 0;
	m_ullPointer = 0;
	// ���ļ�
	const wchar_t pszFilter[] = _T("�ı��ļ�(*.text)|*.text|�ı��ļ�(*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".text"), _T("1.text"), OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT, pszFilter, this);

	if ( dlg.DoModal()!=IDOK )
	{
		return;
	}
	csOpenFilePath = dlg.GetPathName();
	GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);
	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03d��ʼ����\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	strOut += str;
	for (int i=0; i<1000; i++)
	{
		OpenFile(csOpenFilePath);
	}
	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03dֹͣ����\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	strOut += str;
	GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowText(strOut);
}

// ���ļ���ȡ����
void CTestFileOpenSpeedDlg::OpenFile(CString csOpenFilePath)
{
	if ((_taccess(csOpenFilePath,0)) != -1)
	{
		if(file.Open(csOpenFilePath, CFile::modeRead) == FALSE)
		{
			AfxMessageBox(_T("�����ݲ����ļ�����"));	
			return;
		}
		else
		{
			CString str = _T("");
			CArchive ar(&file, CArchive::load);
			LONGLONG lOffset = 0;
			ULONGLONG lActual;
			unsigned int uiLength = 0;
			unsigned int uiRead = 0;
			file.SeekToBegin();
			ULONGLONG ullEnd = file.SeekToEnd();

			// ����ƶ�Ϊ�ַ�����+2(\n����)
			file.SeekToBegin();
			// ADC���ݲ�����ʼʱ��
			ar.ReadString(str);
			uiLength += (str.GetLength() + 2) * 2;
			lActual = file.Seek(uiLength, CFile::begin);
			// ADC���ݲ�����Ϣ
			ar.ReadString(str);
			uiLength  += (str.GetLength() + 2) * 2;
			lActual = file.Seek(uiLength, CFile::begin);
			// �ɼ�վ�豸��ǩ
			ar.ReadString(str);
			uiLength  += (str.GetLength() + 2) * 2;
			lActual = file.Seek(uiLength, CFile::begin);
			// ����
			lActual = file.Seek(m_uiBufSize * 2* m_ullPointer, CFile::current);
			do 
			{
				if (m_uiFindLineCount == 1915210)
				{
					break;
				}
				else
				{
					// ��1������
					uiRead = file.Read(m_pbufRead, m_uiBufSize * sizeof(wchar_t));
					if (uiRead == 0)
					{
						break;
					}
					else
					{
						m_uiFindLineCount++;
						// ����ƶ�Ϊ�ַ�����+4(\r\n����)
						// ����
						lActual = file.Seek(m_uiBufSize * 2* (m_uiSamplingRate - 1), CFile::current);
					}
				}
			} while (lActual <ullEnd);
			m_ullPointer = (lActual - ullEnd) / (m_uiBufSize * 2); 
	
			file.SeekToEnd();
			ar.Close();
			file.Close();
		}
	}
}
