
// MatrixServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "MatrixServerDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMatrixServerDlg �Ի���




CMatrixServerDlg::CMatrixServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMatrixServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatrixServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMatrixServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BN_START, &CMatrixServerDlg::OnBnClickedBnStart)
	ON_BN_CLICKED(IDC_BN_STOP, &CMatrixServerDlg::OnBnClickedBnStop)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BN_STARTSAMPLE_ALL, &CMatrixServerDlg::OnBnClickedButtonStartsampleAll)
	ON_BN_CLICKED(IDC_BN_STOPSAMPLE_ALL, &CMatrixServerDlg::OnBnClickedButtonStopsampleAll)
	ON_BN_CLICKED(IDC_BN_ADCSET_ALL, &CMatrixServerDlg::OnBnClickedBnAdcsetAll)
	ON_BN_CLICKED(IDC_BN_ADCSET_BYROUT, &CMatrixServerDlg::OnBnClickedBnAdcsetByrout)
	ON_BN_CLICKED(IDC_BN_STARTSAMPLE_BYROUT, &CMatrixServerDlg::OnBnClickedBnStartsampleByrout)
	ON_BN_CLICKED(IDC_BN_STOPSAMPLE_BYROUT, &CMatrixServerDlg::OnBnClickedBnStopsampleByrout)
	ON_BN_CLICKED(IDC_BTN_OPENROUTPOWER, &CMatrixServerDlg::OnBnClickedBtnOpenroutpower)
	ON_BN_CLICKED(IDC_BTN_GETROUTINSTRUMENTNUM, &CMatrixServerDlg::OnBnClickedBtnGetroutinstrumentnum)
	ON_BN_CLICKED(IDC_BTN_GETSNBYLOCATION, &CMatrixServerDlg::OnBnClickedBtnGetsnbylocation)
END_MESSAGE_MAP()


// CMatrixServerDlg ��Ϣ�������

BOOL CMatrixServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	// ��ʼ����̬���ӿ�
	m_oMatrixDllCall.OnInit(_T("MatrixServerDll.dll"));
	// ��ʼ����ͻ���ͨѶ����
	m_oCom.OnInit();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMatrixServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMatrixServerDlg::OnPaint()
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
HCURSOR CMatrixServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CMatrixServerDlg::OnBnClickedBnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// DLL��ʼ����
	m_oMatrixDllCall.Dll_Work();
}
void CMatrixServerDlg::OnBnClickedBnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// DLLֹͣ����
	m_oMatrixDllCall.Dll_Stop();
}
void CMatrixServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// �ر���ͻ���ͨѶ����
	m_oCom.OnClose();
	// �رն�̬���ӿ�
	m_oMatrixDllCall.OnClose();
}
void CMatrixServerDlg::OnBnClickedButtonStartsampleAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// DLL��ʼAD���ݲɼ�
	m_oMatrixDllCall.Dll_StartSample(1000);
}
void CMatrixServerDlg::OnBnClickedButtonStopsampleAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// DLLֹͣAD���ݲɼ�
	m_oMatrixDllCall.Dll_StopSample();
}


void CMatrixServerDlg::OnBnClickedBnAdcsetAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// AD��������
	m_oMatrixDllCall.Dll_ADCSet();
}


void CMatrixServerDlg::OnBnClickedBnAdcsetByrout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oMatrixDllCall.Dll_ADCSetPart(GetDlgItemInt(IDC_EDIT_LINEINDEX), GetDlgItemInt(IDC_EDIT_POINTINDEX), 
		GetDlgItemInt(IDC_EDIT_ROUT_DIRECTION), 1);
}


void CMatrixServerDlg::OnBnClickedBnStartsampleByrout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oMatrixDllCall.Dll_ADCSetPart(GetDlgItemInt(IDC_EDIT_LINEINDEX), GetDlgItemInt(IDC_EDIT_POINTINDEX), 
		GetDlgItemInt(IDC_EDIT_ROUT_DIRECTION), 2, 1000);
}


void CMatrixServerDlg::OnBnClickedBnStopsampleByrout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oMatrixDllCall.Dll_ADCSetPart(GetDlgItemInt(IDC_EDIT_LINEINDEX), GetDlgItemInt(IDC_EDIT_POINTINDEX), 
		GetDlgItemInt(IDC_EDIT_ROUT_DIRECTION), 3);
}


void CMatrixServerDlg::OnBnClickedBtnOpenroutpower()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oMatrixDllCall.Dll_OpenLAUXRoutPower_ByHand(GetDlgItemInt(IDC_EDIT_LINEINDEX), 
		GetDlgItemInt(IDC_EDIT_POINTINDEX), static_cast<unsigned char>(GetDlgItemInt(IDC_EDIT_OPENROUTPOWER)));
}


void CMatrixServerDlg::OnBnClickedBtnGetroutinstrumentnum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	unsigned int uiInstrumentNum = m_oMatrixDllCall.Dll_GetRoutInstrumentNum(GetDlgItemInt(IDC_EDIT_LINEINDEX), 
		GetDlgItemInt(IDC_EDIT_POINTINDEX), GetDlgItemInt(IDC_EDIT_ROUT_DIRECTION));
	CString str = _T("");
	str.Format(_T("�÷�����������Ϊ%d"), uiInstrumentNum);
	AfxMessageBox(str);
}


void CMatrixServerDlg::OnBnClickedBtnGetsnbylocation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	pInstrument = m_oMatrixDllCall.Dll_GetInstrumentByLocation(GetDlgItemInt(IDC_EDIT_LINEINDEX), 
		GetDlgItemInt(IDC_EDIT_POINTINDEX));
	if (pInstrument == NULL)
	{
		AfxMessageBox(_T("��δ�ҵ�������"));
	}
	else
	{
		str.Format(_T("����SN = 0x%x"), pInstrument->m_uiSN);
		AfxMessageBox(str);
	}
}
