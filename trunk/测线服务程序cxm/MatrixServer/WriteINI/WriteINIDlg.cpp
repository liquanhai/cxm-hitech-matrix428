
// WriteINIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WriteINI.h"
#include "WriteINIDlg.h"
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


// CWriteINIDlg �Ի���




CWriteINIDlg::CWriteINIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWriteINIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWriteINIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWriteINIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_GENINI, &CWriteINIDlg::OnBnClickedBtnGenini)
END_MESSAGE_MAP()


// CWriteINIDlg ��Ϣ�������

BOOL CWriteINIDlg::OnInitDialog()
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWriteINIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWriteINIDlg::OnPaint()
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
HCURSOR CWriteINIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWriteINIDlg::OnBnClickedBtnGenini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSection = _T("");
	CString strSectionKey = _T("");
	CString strValue = _T("");
	CString strFilePath = _T("");
	wchar_t strBuff[256];

	GetCurrentDirectory(256,strBuff);		// ��ȡ��ǰ·��
	strFilePath.Format(_T("%s\\MatrixServerDLL.ini"),strBuff);

	strSection = _T("��������");			// ��ȡ��ǰ����

	strSectionKey=_T("InstrumentCountAll");			// ��������
	strValue = _T("20000");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCDataCountAll");			// ADC���ݻ���������
	strValue = _T("200000");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("OptTaskCountAll");			// ʩ���������
	strValue = _T("20");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("OneSleepTime");				// һ�����ߵ�ʱ��
	strValue = _T("50");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("LogOutPutSleepTimes");		// ��־����߳�д��־����ʱ����
	strValue = _T("10");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("HertBeatSleepTimes");			// �����̷߳�������֡��ʱ����
	strValue = _T("5");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("HeadFrameSleepTimes");		// �װ��߳̽����װ���ʱ����
	strValue = _T("10");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("IPSetFrameSleepTimes");		// IP��ַ�����߳���ʱ����
	strValue = _T("10");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("TailFrameSleepTimes");		// β���߳���ʱ����
	strValue = _T("10");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("MonitorSleepTimes");		// ·�ɼ����߳���ʱ����
	strValue = _T("10");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("TimeDelaySleepTimes");		// ʱͳ�����߳���ʱ����
	strValue = _T("4");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCSetSleepTimes");			// ADC���������߳���ʱ����
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ErrorCodeSleepTimes");		// �����ѯ�߳���ʱ����
	strValue = _T("20");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCDataRecSleepTimes");		// ADC���ݽ����߳���ʱ����
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCDataSaveSleepTimes");		// ADC���ݴ洢�߳���ʱ����
	strValue = _T("4");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CloseThreadSleepTimes");		// �ȴ��̹߳رյ���ʱ����
	strValue = _T("20");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("HeadFrameStableNum");		// �װ�����
	strValue = _T("4");
	//д��ini�ļ�����Ӧ�ֶ�
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("IPAddrResetTimes");		// IP��ַ�������
	strValue = _T("3");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("TailFrameStableTimes");	// β���ȶ�����
	strValue = _T("5");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("MonitorStableTime");	// ·�ɼ����ȶ�ʱ��
	strValue = _T("5000");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("LineSysStableTime");		// ����ϵͳ�ﵽ�ȶ�״̬ʱ��
	strValue = _T("5000");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCSetOptNb");			// ADC�������ò������
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCStartSampleOptNb");	// ADC��ʼ�ɼ��������
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCStopSampleOptNb");		// ADCֹͣ�ɼ��������
	strValue = _T("3");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("InstrumentTypeLAUX");		// ��������-����վ
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("InstrumentTypeLAUL");		// ��������-��Դվ
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("InstrumentTypeFDU");		// ��������-�ɼ�վ
	strValue = _T("3");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("InstrumentTypeLCI");		// ��������-LCI
	strValue = _T("4");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("DirectionTop");			// �����Ϸ�
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("DirectionDown");			// �����·�
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("DirectionLeft");			// ������
	strValue = _T("3");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("DirectionRight");			// �����ҷ�
	strValue = _T("4");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("DirectionCenter");		// ��������
	strValue = _T("0");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("IPSetAddrStart");			// IP��ַ���õ���ʼ��ַ
	strValue = _T("71");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("IPSetAddrInterval");		// IP��ַ���õļ��
	strValue = _T("16");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("RoutSetAddrStart");		// ·�ɵ�ַ���õ���ʼ��ַ
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("RoutSetAddrInterval");	// ·�ɵ�ַ���õļ��
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("BroadcastPortStart");		// ���ù㲥�˿���ʼ��ַ
	strValue = _T("16");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("IPBroadcastAddr");		// ����Ϊ�㲥IP
	strValue = _T("4294967295");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCFrameSaveInOneFileNum");	// һ���ļ��ڴ洢�����豸ADC����֡��
	strValue = _T("200");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCSaveHeadLineNum");		// �洢ADC���ݵ��ļ�ͷ����
	strValue = _T("3");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCSaveLeftInfoBytes");	// �洢ADC���ݵ����Ԥ����Ϣ�ֽ���
	strValue = _T("14");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCSaveDataBytes");		// �洢ADC���ݵ��ֽ���
	strValue = _T("10");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCSaveDataIntervalBytes");	// �洢ADC����֮��ļ���ֽ���
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCDataBufSize");			// �豸ADC���ݻ�������С
	strValue = _T("2048");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("TBSleepTimeHigh");			// TB������ʱ��λ
	strValue = _T("16384");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("TBSleepTimeLow");				// TB������ʱ��λ
	strValue = _T("250");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSection = _T("֡��ʽ����");			// ��ȡ��ǰ����

	strSectionKey=_T("FrameHeadSize");		// ֡ͷ����
	strValue = _T("16");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("FrameHeadCheck");		// ͬ��֡ͷ
	strValue = _T("0x11,0x22,0x33,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00");    
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);
	
	strSectionKey=_T("FrameCmdSize1B");		// �����ֳ���1�ֽ�
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("FramePacketSize1B");	// ���������1�ֽ�
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("FramePacketSize2B");	// ���������2�ֽ�
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("FramePacketSize4B");	// ���������4�ֽ�
	strValue = _T("4");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCDataSize3B");		// ADC������ռ�ֽ���
	strValue = _T("3");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCDataInOneFrameNum");	// һ֡��ADC���ݸ���
	strValue = _T("72");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("ADCFramePointLimit");		// ADC����ָ֡��ƫ��������
	strValue = _T("2048");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CommandWordMaxNum");	// �����ָ������ֵ
	strValue = _T("41");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("SndFrameBufInit");	// ����֡��������ֵ�趨
	strValue = _T("0");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("RcvFrameSize");		// ���յ���������֡֡����
	strValue = _T("256");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("SndFrameSize");		// ���͵���������֡֡����
	strValue = _T("128");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	/////////////////////////////////////////////////////////////////////////
	strSection = _T("���������豸����������");		// ��ȡ��ǰ����
	strSectionKey=_T("SendSetCmd");			// ������������
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("SendQueryCmd");		// ���Ͳ�ѯ����
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("SendADCCmd");			// ����ADC���������ط�����
	strValue = _T("3");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdSn");				// ����
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdHeadFrameTime");	// �װ�ʱ��
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLocalIPAddr");		// ����IP��ַ
	strValue = _T("3");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLocalSysTime");	// ����ϵͳʱ��
	strValue = _T("4");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLocalTimeFixedHigh");	// ����ʱ��������λ
	strValue = _T("5");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLocalTimeFixedLow");	// ����ʱ��������λ
	strValue = _T("6");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdADCDataReturnAddr");	// �Զ����ݷ��ص�ַ
	strValue = _T("7");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdADCDataReturnPort");	// �Զ����ݷ��ض˿ں�����
	strValue = _T("8");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdADCDataReturnPortLimit");	// �˿ڵ������޺�����
	strValue = _T("9");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdSetBroadCastPort");	// ��������ȴ��˿ں�����
	strValue = _T("10");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdFDUErrorCode");		// ϵͳӲ��״̬����
	strValue = _T("11");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdTBHigh");				// TBʱ�̸�λ
	strValue = _T("12");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdTbLow");				// TBʱ�̵�λ
	strValue = _T("13");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLAUXRoutOpenQuery");	// work_ctrl ����վ����
	strValue = _T("14");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLAUXRoutOpenSet");		// ·�ɿ���
	strValue = _T("15");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdTailRecSndTimeLow");	// β������\����ʱ�̵�λ
	strValue = _T("22");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdBroadCastPortSet");	// �㲥����ȴ��˿�ƥ��
	strValue = _T("23");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdADCSet");				// ����ADC��������������
	strValue = _T("24");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdNetTime");				// ����ʱ��
	strValue = _T("25");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLineTailRecTimeLAUX");	// ����վ����β������ʱ��
	strValue = _T("27");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLAUTailRecTimeLAUX");	// ����վ������β������ʱ��
	strValue = _T("28");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLAUXErrorCode1");		// ����վ����1
	strValue = _T("29");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLAUXErrorCode2");		// ����վ����2
	strValue = _T("30");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdLAUXSetRout");			// ����վ·�ɷ���
	strValue = _T("31");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdReturnRout");			// ����·��
	strValue = _T("63");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdEnd");					// ���������������
	strValue = _T("0");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdTBCtrlStartSample");		// TB���ؿ���ADC���ݲɼ�����
	strValue = _T("1");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);
	
	strSectionKey=_T("CmdTBLoseCtrlStartSample");	// ����TB���ؿ���ADC���ݲɼ�����
	strValue = _T("2");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdTBCtrlStopSample");		// TB���ؿ���ADC����ֹͣ�ɼ�����
	strValue = _T("0");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);

	strSectionKey=_T("CmdCtrlCloseLed");			// LED����
	strValue = _T("4");
	WritePrivateProfileString(strSection,strSectionKey,strValue,strFilePath);
}
