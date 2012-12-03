// IC_TESTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IC_TEST.h"
#include "IC_TESTDlg.h"
#include "Parameter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CIC_TESTDlg dialog

// �Ƿ����Ա��½��־λ
bool m_bAdmin;


CIC_TESTDlg::CIC_TESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIC_TESTDlg::IDD, pParent)
	, m_pProData(NULL)
	, m_uiSCRPosition(0)
	, m_uiIRC4MPosition(0)
	, m_uiIRC1KPosition(0)
	, m_strProFilePath(_T(""))
	, m_bModeWrite(false)
	, m_uiRecDataNum(0)
	, m_uiRecDataNeed(0)
	, m_bBusy(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIC_TESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, m_ctrlListMsg);
	DDX_Control(pDX, IDC_EDIT_HEX, m_ctrlEditHex);
	DDX_Control(pDX, IDC_SPIN_SCR, m_ctrlSpinSCR);
	DDX_Control(pDX, IDC_SPIN_IRC4M, m_ctrlSpinIRC4M);
	DDX_Control(pDX, IDC_SPIN_IRC1K, m_ctrlSpinIRC1K);
	DDX_Control(pDX, IDC_COMBO_PROGRAM_MODE, m_ctrlComboProMode);
	DDX_Control(pDX, IDC_EDIT_COMNO, m_ctrlComNo);
	DDX_Control(pDX, IDC_EDIT_SCR, m_ctrlEditSCR);
	DDX_Control(pDX, IDC_COMBO_SCR, m_ctrlComboSCR);
	DDX_Control(pDX, IDC_EDIT_IRC4M, m_ctrlEditIRC4M);
	DDX_Control(pDX, IDC_COMBO_IRC4M, m_ctrlComboIRC4M);
	DDX_Control(pDX, IDC_EDIT_IRC1K, m_ctrlEditIRC1K);
	DDX_Control(pDX, IDC_COMBO_IRC1K, m_ctrlComboIRC1K);
	DDX_Control(pDX, IDC_COMBO_READBACK, m_ctrlComboReadback);
}

BEGIN_MESSAGE_MAP(CIC_TESTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_RESET, &CIC_TESTDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_RESET_MSG, &CIC_TESTDlg::OnBnClickedBtnResetMsg)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CIC_TESTDlg::OnBnClickedBtnOpenfile)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_LANDED, &CIC_TESTDlg::OnBnClickedBtnLanded)
	ON_BN_CLICKED(IDC_BTN_OPENCOM, &CIC_TESTDlg::OnBnClickedBtnOpencom)
	ON_BN_CLICKED(IDC_BTN_CLOSECOM, &CIC_TESTDlg::OnBnClickedBtnClosecom)
	ON_BN_CLICKED(IDC_BTN_READBACK_DO, &CIC_TESTDlg::OnBnClickedBtnReadbackDo)
	ON_BN_CLICKED(IDC_BTN_PROGRAM_DO, &CIC_TESTDlg::OnBnClickedBtnProgramDo)
	ON_BN_CLICKED(IDC_BTN_SCR_DO, &CIC_TESTDlg::OnBnClickedBtnSCRDo)
	ON_BN_CLICKED(IDC_BTN_IRC4M_DO, &CIC_TESTDlg::OnBnClickedBtnIrc4mDo)
	ON_BN_CLICKED(IDC_BTN_IRC1K_DO, &CIC_TESTDlg::OnBnClickedBtnIrc1kDo)
	ON_BN_CLICKED(IDC_BTN_SAVEFILE, &CIC_TESTDlg::OnBnClickedBtnSavefile)
END_MESSAGE_MAP()


// CIC_TESTDlg message handlers

BOOL CIC_TESTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon
	// TODO: Add extra initialization here
	m_olsSendData.RemoveAll();
	m_olsRecData.RemoveAll();
	m_ctrlSpinSCR.SetBuddy(GetDlgItem(IDC_EDIT_SCR));
	m_ctrlSpinSCR.SetRange(0, 255);
	m_ctrlSpinIRC1K.SetBuddy(GetDlgItem(IDC_EDIT_IRC1K));
	m_ctrlSpinIRC1K.SetRange(0, 255);
	m_ctrlSpinIRC4M.SetBuddy(GetDlgItem(IDC_EDIT_IRC4M));
	m_ctrlSpinIRC4M.SetRange(0, 255);
	m_ctrlComNo.SetWindowText(_T("0"));
	GetDlgItem(IDC_BTN_CLOSECOM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_READBACK_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PROGRAM_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SCR_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_IRC1K_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_IRC4M_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SAVEFILE)->EnableWindow(FALSE);
	m_oUart.m_OnUartRead = OnUartRead;
	OnLanded();
	RefreshControls();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIC_TESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIC_TESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIC_TESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// ���ÿؼ�
void CIC_TESTDlg::RefreshControls(void)
{
	if (m_pProData != NULL)
	{
		delete[] m_pProData;
		m_pProData = NULL;
	}
	m_bySCR = 0x00;
	m_byIRC1K = 0x00;
	m_byIRC4M = 0x00;
	SetDlgItemInt(IDC_EDIT_SCR, m_bySCR);
	SetDlgItemInt(IDC_EDIT_IRC1K, m_byIRC1K);
	SetDlgItemInt(IDC_EDIT_IRC4M, m_byIRC4M);
	SetDlgItemText(IDC_COMBO_SCR, _T(""));
	SetDlgItemText(IDC_COMBO_IRC1K, _T(""));
	SetDlgItemText(IDC_COMBO_IRC4M, _T(""));
	SetDlgItemText(IDC_COMBO_PROGRAM_MODE, _T(""));
	m_uiAddrMax = 0;
	m_uiAddrMin = DefaultBufSize;
	m_ctrlEditHex.SetBPR(16);
	m_ctrlEditHex.SetOptions(TRUE, TRUE, FALSE, TRUE);
	m_ctrlEditHex.Clear();
	m_ctrlEditHex.SetData(NULL, 0, 0);
	while(m_ctrlListMsg.GetCount() != 0)
	{
		m_ctrlListMsg.DeleteString(0);
	}
}


void CIC_TESTDlg::OnBnClickedBtnReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RefreshControls();
}


void CIC_TESTDlg::OnBnClickedBtnResetMsg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	while(m_ctrlListMsg.GetCount() != 0)
	{
		m_ctrlListMsg.DeleteString(0);
	}
}


void CIC_TESTDlg::OnBnClickedBtnOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʾ�ļ��򿪶Ի���
	//ͬʱ�򿪶�������ļ�
// 	CFileDialog dlg(TRUE, _T("EC"), _T("*.hex"),
// 		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Hex File(*.hex)|*.hex"));
	CFileDialog dlg(TRUE, _T("EC"), _T("*.hex"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("(*.hex)|*.hex|All Files(*.*)|*.*|"));//ͬʱ�򿪶�������ļ�
	if ( dlg.DoModal()!=IDOK ) return;
	GetDlgItem(IDC_BTN_SAVEFILE)->EnableWindow(FALSE);
	//��ȡ�ļ��ľ���·��
	m_strProFilePath = dlg.GetPathName();
	CString	sFileName = dlg.GetFileName();
	CString strOutput = _T("Open file path: ");
	strOutput += m_strProFilePath;
	m_ctrlListMsg.AddString(strOutput);
	if ((_taccess(m_strProFilePath,0)) != -1)
	{
		size_t sFileName_size = sFileName.GetLength();
		//��׺��
		CString suffix = sFileName.Mid((int)sFileName_size - 4, 4);
		if ((_T(".hex") == suffix) || (_T(".HEX") == suffix))
		{
			CString str = _T("");
			CString strTemp = _T("");
			unsigned int uiDataLength = 0;
			unsigned int uiLoadOffset = 0;
			unsigned int uiRecType = 0;
			unsigned int uiDataTemp = 0;
			LPBYTE lpchar=_T('');
			unsigned int uiDataNum = 0;
			vector <unsigned char> data_vector;
			for (int i=0; i<DefaultBufSize; i++)
			{
				data_vector.push_back(DefaultBufValue);
			}
			CStdioFile file(m_strProFilePath, CFile::modeRead); //ֻ��
			// ÿ����һ�У�ָ����һ�У���������ļ�ĩβ���˳�ѭ��
			while(file.ReadString(str))
			{
				// Mid(string,start,length)
				// ��string�ַ�����start�ַ���ʼȡ��length���ȵ��ַ�����
				// ���ʡ�Ե�����������ʾ��start�ַ���ʼ���ַ�����β���ַ�����
				int iPos = 1;
				strTemp = str.Mid(iPos, 2);
				iPos += 2;
				strTemp = _T("0x") + strTemp;
				swscanf_s(strTemp, _T("%x"), &uiDataLength);
				strTemp = str.Mid(iPos, 4);
				iPos += 4;
				strTemp = _T("0x") + strTemp;
				swscanf_s(strTemp, _T("%x"), &uiLoadOffset);
				strTemp = str.Mid(iPos, 2);
				iPos += 2;
				strTemp = _T("0x") + strTemp;
				swscanf_s(strTemp, _T("%x"), &uiRecType);
				if (uiDataLength > 0)
				{
					if (uiLoadOffset < m_uiAddrMin)
					{
						m_uiAddrMin = uiLoadOffset;
					}
					if (uiLoadOffset > m_uiAddrMax)
					{
						m_uiAddrMax = uiLoadOffset + uiDataLength - 1;
					}
					for (unsigned int i=0; i<uiDataLength; i++)
					{
						strTemp = str.Mid(iPos, 2);
						iPos += 2;
						strTemp = _T("0x") + strTemp;
						swscanf_s(strTemp, _T("%x"), &uiDataTemp);
						data_vector[i + uiLoadOffset] = ((unsigned char)uiDataTemp);
						// ��ǰ����-���з�-У���-�����ݼ���֮������ݳ���
						if (i + uiLoadOffset == SCRAddr)
						{
							m_uiSCRPosition = (unsigned int)file.GetPosition() - (uiDataLength - i) * 2 - 2 - 2;
						}
						else if (i + uiLoadOffset == IRC1KAddr)
						{
							m_uiIRC1KPosition = (unsigned int)file.GetPosition() - (uiDataLength - i) * 2 - 2 - 2;
						}
						else if (i + uiLoadOffset == IRC4MAddr)
						{
							m_uiIRC4MPosition = (unsigned int)file.GetPosition() - (uiDataLength - i) * 2 - 2 - 2;
						}
					}
				}
			}
			file.Close();
			if (m_pProData != NULL)
			{
				delete[] m_pProData;
				m_pProData = NULL;
				m_ctrlEditHex.Clear();
			}
			uiDataNum = m_uiAddrMax - m_uiAddrMin + 1;
			m_pProData = new BYTE[uiDataNum];
			for (unsigned int i=0; i<uiDataNum; i++)
			{
				m_pProData[i] = data_vector[i + m_uiAddrMin];
			}
			data_vector.clear();
			m_ctrlEditHex.SetAddressBase(m_uiAddrMin);
			m_ctrlEditHex.SetData(m_pProData, uiDataNum, uiDataNum);
			m_bySCR = m_pProData[SCRAddr - m_uiAddrMin];
			m_byIRC1K = m_pProData[IRC1KAddr - m_uiAddrMin];
			m_byIRC4M = m_pProData[IRC4MAddr - m_uiAddrMin];
			SetDlgItemInt(IDC_EDIT_SCR, m_bySCR);
			SetDlgItemInt(IDC_EDIT_IRC1K, m_byIRC1K);
			SetDlgItemInt(IDC_EDIT_IRC4M, m_byIRC4M);
			GetDlgItem(IDC_BTN_SAVEFILE)->EnableWindow(TRUE);
		}
		else
		{
			strOutput = _T("The file's type is not ' *.hex ' !");
			AfxMessageBox(strOutput);
			m_ctrlListMsg.AddString(strOutput);
		}
	}
	else
	{
		strOutput = _T("The file is not exit!");
		AfxMessageBox(strOutput);
		m_ctrlListMsg.AddString(strOutput);
	}
}


void CIC_TESTDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	if (m_pProData != NULL)
	{
		delete[] m_pProData;
		m_pProData = NULL;
	}
	if (m_oUart.GetComOpened() == TRUE)
	{
		m_oUart.ClosePort();
	}
}


// ��½
void CIC_TESTDlg::OnLanded(void)
{
	m_bAdmin = false;
	CLandedDlg dlg;
	dlg.DoModal();
	RefreshView();
}


void CIC_TESTDlg::OnBnClickedBtnLanded()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnLanded();
}


// ���ý���
void CIC_TESTDlg::RefreshView(void)
{
	while(m_ctrlComboProMode.GetCount() != 0)
	{
		m_ctrlComboProMode.DeleteString(0);
	}
	m_ctrlComboProMode.AddString(_T("OTP Program with VPP_std"));
	while (m_ctrlComboReadback.GetCount() != 0)
	{
		m_ctrlComboReadback.DeleteString(0);
	}
	m_ctrlComboReadback.AddString(_T("User Mode OTP Read with Vdd_Hi"));
	if (m_bAdmin == true)
	{
		m_ctrlComboProMode.AddString(_T("OTP Program with VPP_Lo"));
		m_ctrlComboReadback.AddString(_T("User Mode OTP Read with Vdd_Lo"));
		m_ctrlComboReadback.AddString(_T("Test Mode OTP Margin-1 Read"));
		m_ctrlComboReadback.AddString(_T("Test Mode OTP Margin-2 Read"));
		m_ctrlComboReadback.AddString(_T("Test Mode OTP off-state Margin Read"));
		ShowControls(SW_SHOW);
	}
	else
	{
		ShowControls(SW_HIDE);
	}
	m_ctrlComboReadback.SetCurSel(0);
	m_ctrlComboSCR.SetCurSel(0);
	m_ctrlComboIRC1K.SetCurSel(0);
	m_ctrlComboIRC4M.SetCurSel(0);
	m_ctrlComboProMode.SetCurSel(0);
}


// ��ʾ�ؼ�
void CIC_TESTDlg::ShowControls(int iStyle)
{
	GetDlgItem(IDC_STATIC_SCR)->ShowWindow(iStyle);
	GetDlgItem(IDC_STATIC_SCR_VALUE)->ShowWindow(iStyle);
	GetDlgItem(IDC_STATIC_SCR_MODE)->ShowWindow(iStyle);
	GetDlgItem(IDC_BTN_SCR_DO)->ShowWindow(iStyle);
	m_ctrlSpinSCR.ShowWindow(iStyle);
	m_ctrlEditSCR.ShowWindow(iStyle);
	m_ctrlComboSCR.ShowWindow(iStyle);

	GetDlgItem(IDC_STATIC_IRC1K)->ShowWindow(iStyle);
	GetDlgItem(IDC_STATIC_IRC1K_VALUE)->ShowWindow(iStyle);
	GetDlgItem(IDC_STATIC_IRC1K_MODE)->ShowWindow(iStyle);
	GetDlgItem(IDC_BTN_IRC1K_DO)->ShowWindow(iStyle);
	m_ctrlSpinIRC1K.ShowWindow(iStyle);
	m_ctrlEditIRC1K.ShowWindow(iStyle);
	m_ctrlComboIRC1K.ShowWindow(iStyle);

	GetDlgItem(IDC_STATIC_IRC4M)->ShowWindow(iStyle);
	GetDlgItem(IDC_STATIC_IRC4M_VALUE)->ShowWindow(iStyle);
	GetDlgItem(IDC_STATIC_IRC4M_MODE)->ShowWindow(iStyle);
	GetDlgItem(IDC_BTN_IRC4M_DO)->ShowWindow(iStyle);
	m_ctrlSpinIRC4M.ShowWindow(iStyle);
	m_ctrlEditIRC4M.ShowWindow(iStyle);
	m_ctrlComboIRC4M.ShowWindow(iStyle);

	GetDlgItem(IDC_BTN_SAVEFILE)->ShowWindow(iStyle);
}
// ���ڽ������ݻص�����
void CALLBACK CIC_TESTDlg::OnUartRead(void* pFatherPtr, BYTE buf)
{
	BYTE byMatch = 0;
	// �õ�������ָ��
	CIC_TESTDlg* pThis = (CIC_TESTDlg*)pFatherPtr;
	CString str = _T("");
	if (pThis->m_bModeWrite == true)
	{
		if (m_bAdmin == true)
		{
			str.Format(_T("%c."), &buf);
			str = _T("Receive the data ") + str;
			pThis->m_ctrlListMsg.AddString(str);
		}
		if (buf == pThis->m_olsSendData.GetHead())
		{
			byMatch = MatchCmd;
			pThis->m_olsSendData.RemoveHead();
		}
		else
		{
			byMatch = NoMatchCmd;
			if (m_bAdmin == true)
			{
				str = _T("Retry!");
				pThis->m_ctrlListMsg.AddString(str);
			}
		}
		pThis->m_oUart.WriteSyncPort(&byMatch, 1);
		if (pThis->m_olsSendData.GetCount() != 0)
		{
			pThis->m_oUart.WriteSyncPort(&pThis->m_olsSendData.GetHead(), 1);
			if (m_bAdmin == true)
			{
				str.Format(_T("%c."), &pThis->m_olsSendData.GetHead());
				str = _T("Write the data ") + str;
				pThis->m_ctrlListMsg.AddString(str);
			}
		}
		else
		{
			// ��д�������
			str = _T("Program task finished!");
			pThis->m_ctrlListMsg.AddString(str);
			pThis->m_bBusy = false;
		}
	}
	else
	{
		if (pThis->m_uiRecDataNum % 2 == 0)
		{
			pThis->m_olsRecData.AddTail(buf);
			pThis->m_oUart.WriteSyncPort(&buf, 1);
			if (m_bAdmin == true)
			{
				str.Format(_T("%c."), &buf);
				str = _T("Read the data ") + str;
				pThis->m_ctrlListMsg.AddString(str);
			}
		}
		else
		{
			if (buf == NoMatchCmd)
			{
				pThis->m_olsRecData.RemoveTail();
				if (m_bAdmin == true)
				{
					str = _T("Retry!");
					pThis->m_ctrlListMsg.AddString(str);
				}
			}
			else
			{
				if (pThis->m_uiRecDataNeed == pThis->m_olsRecData.GetCount())
				{
					// ���������
					str = _T("Read task finished!");
					pThis->m_ctrlListMsg.AddString(str);
					pThis->m_bBusy = false;
				}
			}
		}
		pThis->m_uiRecDataNum ++;
	}
}



void CIC_TESTDlg::OnBnClickedBtnOpencom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	if (m_oUart.OpenPort(this, GetDlgItemInt(IDC_EDIT_COMNO), 38400, NOPARITY, 8, ONESTOPBIT))
	{
		str = _T("Open the serial port successfully��");
		AfxMessageBox(str);
		m_ctrlListMsg.AddString(str);
		GetDlgItem(IDC_BTN_OPENCOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CLOSECOM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_READBACK_DO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PROGRAM_DO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SCR_DO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IRC1K_DO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IRC4M_DO)->EnableWindow(TRUE);
	}
	else
	{
		str = _T("Open the serial port failed��");
		AfxMessageBox(str);
		m_ctrlListMsg.AddString(str);
	}
}


void CIC_TESTDlg::OnBnClickedBtnClosecom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("Close the serial port!");
	m_ctrlListMsg.AddString(str);
	m_oUart.ClosePort();
	GetDlgItem(IDC_BTN_OPENCOM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CLOSECOM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_READBACK_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PROGRAM_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SCR_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_IRC1K_DO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_IRC4M_DO)->EnableWindow(FALSE);
}


void CIC_TESTDlg::OnBnClickedBtnReadbackDo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CIC_TESTDlg::OnBnClickedBtnProgramDo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CIC_TESTDlg::OnBnClickedBtnSCRDo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPos = m_ctrlComboSCR.GetCurSel();
	if (iPos == ReadMode)
	{

	}
	else if (iPos == WriteMode)
	{

	}
}


void CIC_TESTDlg::OnBnClickedBtnIrc4mDo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPos = m_ctrlComboIRC4M.GetCurSel();
	if (iPos == ReadMode)
	{

	}
	else if (iPos == WriteMode)
	{

	}
}


void CIC_TESTDlg::OnBnClickedBtnIrc1kDo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPos = m_ctrlComboIRC1K.GetCurSel();
	if (iPos == ReadMode)
	{

	}
	else if (iPos == WriteMode)
	{

	}
}


void CIC_TESTDlg::OnBnClickedBtnSavefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	string strA = "";
	str = _T("Save in file!");
	UpdateData(TRUE);
	m_bySCR = (BYTE)GetDlgItemInt(IDC_EDIT_SCR);
	m_byIRC1K = (BYTE)GetDlgItemInt(IDC_EDIT_IRC1K);
	m_byIRC4M = (BYTE)GetDlgItemInt(IDC_EDIT_IRC4M);
	m_ctrlListMsg.AddString(str);
	CStdioFile file(m_strProFilePath, CFile::modeWrite); // д�ļ�
	file.Seek(m_uiIRC1KPosition, CFile::begin);
	str.Format(_T("%02X"), m_byIRC1K);
	strA = (CStringA)str;
	file.Write(strA.c_str(), 2);

	file.Seek(m_uiIRC4MPosition, CFile::begin);
	str.Format(_T("%02X"), m_byIRC4M);
	strA = (CStringA)str;
	file.Write(strA.c_str(), 2);

	file.Seek(m_uiSCRPosition, CFile::begin);
	str.Format(_T("%02X"), m_bySCR);
	strA = (CStringA)str;
	file.Write(strA.c_str(), 2);
	file.Close();
	m_pProData[SCRAddr - m_uiAddrMin] = m_bySCR;
	m_pProData[IRC1KAddr - m_uiAddrMin] = m_byIRC1K;
	m_pProData[IRC4MAddr - m_uiAddrMin] = m_byIRC4M;

	unsigned int uiDataNum = m_uiAddrMax - m_uiAddrMin + 1;
	m_ctrlEditHex.SetData(m_pProData, uiDataNum, uiDataNum);
}
