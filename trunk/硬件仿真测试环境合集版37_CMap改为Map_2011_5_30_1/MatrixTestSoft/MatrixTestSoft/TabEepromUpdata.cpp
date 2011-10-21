// TabEepromUpdata.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TabEepromUpdata.h"

#define EepromRecPort	0x8700
//----------------------------------------------------------------------------------
//�� ���ֽ�char* ת��Ϊ ���ֽ� wchar*
inline wchar_t* AnsiToUnicode( char* szStr )
{
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );
	return pResult;
}

// CTabEepromUpdata �Ի���

IMPLEMENT_DYNAMIC(CTabEepromUpdata, CDialog)

CTabEepromUpdata::CTabEepromUpdata(CWnd* pParent /*=NULL*/)
	: CDialog(CTabEepromUpdata::IDD, pParent)
	, m_uiEditReadMax(0)
	, m_uiEditReadTotal(0)
	, m_uiEditReadAddr(0)
	, m_uiEditWriteMax(0)
	, m_uiEditWriteTotal(0)
	, m_uiEditWriteAddr(0)
	, m_pInstrumentList(NULL)
{

}

CTabEepromUpdata::~CTabEepromUpdata()
{
}

void CTabEepromUpdata::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_READ_MAX, m_uiEditReadMax);
	DDX_Text(pDX, IDC_EDIT_READ_TOTAL, m_uiEditReadTotal);
	DDX_Text(pDX, IDC_EDIT_READ_ADDR, m_uiEditReadAddr);
	DDX_Text(pDX, IDC_EDIT_WRITE_MAX, m_uiEditWriteMax);
	DDX_Text(pDX, IDC_EDIT_WRITE_TOTAL, m_uiEditWriteTotal);
	DDX_Text(pDX, IDC_EDIT_WRITE_ADDR, m_uiEditWriteAddr);
	DDX_Control(pDX, IDC_LIST_INSTRUMENT, m_ctrlListInstrument);
	DDX_Control(pDX, IDC_LIST_UPDATA, m_ctrlListUpdata);
	DDX_Control(pDX, IDC_LIST_FAIL, m_ctrlListFail);
	DDX_Control(pDX, IDC_LIST_SUCCESS, m_ctrlListSuccess);
	DDX_Control(pDX, IDC_STATIC_INSTRUMENT_NUM, m_ctrlStaticInstrumentNum);
	DDX_Control(pDX, IDC_STATIC_UPDATA_NUM, m_ctrlStaticUpdataNum);
	DDX_Control(pDX, IDC_STATIC_FAIL_NUM, m_ctrlStaticFailNum);
	DDX_Control(pDX, IDC_STATIC_SUCCESS_NUM, m_ctrlStaticSuccessNum);
	DDX_Control(pDX, IDC_BUTTON_MOVERIGHT_ONE, m_ctrlBtnMoveRightOne);
	DDX_Control(pDX, IDC_BUTTON_MOVERIGHT_ALL, m_ctrlBtnMoveRightAll);
	DDX_Control(pDX, IDC_BUTTON_MOVELEFT_ONE, m_ctrlBtnMoveLeftOne);
	DDX_Control(pDX, IDC_BUTTON_MOVELEFT_ALL, m_ctrlBtnMoveLeftAll);
	DDX_Control(pDX, IDC_CHECK_BROADCAST_WRITE, m_ctrlCheckBroadCastWrite);
	DDX_Control(pDX, IDC_LIST_MESSAGE, m_ctrlListMessage);
	DDX_Control(pDX, IDC_BUTTON_UPDATA_INSTRUMENTLIST, m_ctrlBtnUpdataInstrumentList);
	DDX_Control(pDX, IDC_BUTTON_LOADFILE, m_ctrlBtnLoadFile);
	DDX_Control(pDX, IDC_BUTTON_WRITE_EEPROM, m_ctrlBtnWriteEeprom);
	DDX_Control(pDX, IDC_BUTTON_READ_EEPROM, m_ctrlBtnReadEeprom);
	DDX_Control(pDX, IDC_BUTTON_START_CHECK, m_ctrlBtnStartCheck);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_ctrlBtnReset);
	DDX_Control(pDX, IDC_CHECK_CONTINUEWORK, m_ctrlCheckContinueWork);
}


BEGIN_MESSAGE_MAP(CTabEepromUpdata, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_UPDATA_INSTRUMENTLIST, &CTabEepromUpdata::OnBnClickedButtonUpdataInstrumentlist)
	ON_BN_CLICKED(IDC_BUTTON_MOVERIGHT_ONE, &CTabEepromUpdata::OnBnClickedButtonMoverightOne)
	ON_BN_CLICKED(IDC_BUTTON_MOVERIGHT_ALL, &CTabEepromUpdata::OnBnClickedButtonMoverightAll)
	ON_BN_CLICKED(IDC_BUTTON_MOVELEFT_ONE, &CTabEepromUpdata::OnBnClickedButtonMoveleftOne)
	ON_BN_CLICKED(IDC_BUTTON_MOVELEFT_ALL, &CTabEepromUpdata::OnBnClickedButtonMoveleftAll)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CTabEepromUpdata::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_LOADFILE, &CTabEepromUpdata::OnBnClickedButtonLoadfile)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_EEPROM, &CTabEepromUpdata::OnBnClickedButtonWriteEeprom)
	ON_BN_CLICKED(IDC_BUTTON_READ_EEPROM, &CTabEepromUpdata::OnBnClickedButtonReadEeprom)
	ON_BN_CLICKED(IDC_BUTTON_START_CHECK, &CTabEepromUpdata::OnBnClickedButtonStartCheck)
	ON_BN_CLICKED(IDC_CHECK_BROADCAST_WRITE, &CTabEepromUpdata::OnBnClickedCheckBroadcastWrite)
	ON_BN_CLICKED(IDC_CHECK_CONTINUEWORK, &CTabEepromUpdata::OnBnClickedCheckContinuework)
END_MESSAGE_MAP()


// CTabEepromUpdata ��Ϣ�������
BOOL CTabEepromUpdata::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnReset();
	return TRUE;
}
void CTabEepromUpdata::OnBnClickedButtonUpdataInstrumentlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	int icount = 0;
	if (m_pInstrumentList == NULL)
	{
		return;
	}
	if (m_pInstrumentList->m_oInstrumentSNMap.size() == 0)
	{
		str = _T("û���豸�������ߣ�");
		m_ctrlListMessage.AddString(str);
		return;
	}
	icount = m_ctrlListInstrument.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListInstrument.DeleteString(i);
	}
	icount = m_ctrlListUpdata.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListUpdata.DeleteString(i);
	}
	icount = m_ctrlListFail.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListFail.DeleteString(i);
	}
	icount = m_ctrlListSuccess.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListSuccess.DeleteString(i);
	}
	hash_map<unsigned int, CInstrument*>::iterator  iter;

	for(iter = m_pInstrumentList->m_oInstrumentSNMap.begin(); iter!=m_pInstrumentList->m_oInstrumentSNMap.end(); iter++)
	{
		if (NULL != iter->second)
		{
			if (iter->second->m_bIPSetOK == true)
			{
				str.Format(_T("SN = %04x,	IP = %d"), iter->second->m_uiSN, iter->second->m_uiIPAddress);
				m_ctrlListInstrument.AddString(str);
			}
		}
	}
	m_ctrlBtnMoveRightOne.EnableWindow(TRUE);
	m_ctrlBtnMoveRightAll.EnableWindow(TRUE);
	m_ctrlBtnMoveLeftOne.EnableWindow(TRUE);
	m_ctrlBtnMoveLeftAll.EnableWindow(TRUE);
	str.Format(_T("Num = %d"), m_ctrlListInstrument.GetCount());
	m_ctrlStaticInstrumentNum.SetWindowText(str);
	str.Format(_T("Num = %d"), 0);
	m_ctrlStaticUpdataNum.SetWindowText(str);
	m_ctrlStaticFailNum.SetWindowText(str);
	m_ctrlStaticSuccessNum.SetWindowText(str);
	str = _T("�����豸�б�");
	m_ctrlListMessage.AddString(str);
}

void CTabEepromUpdata::OnBnClickedButtonMoverightOne()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_ctrlListInstrument.GetCurSel();
	CString str = _T("");
	if (nIndex == CB_ERR)
	{
		return;
	}

	int n = m_ctrlListInstrument.GetTextLen(nIndex);
	m_ctrlListInstrument.GetText(nIndex, str.GetBuffer(n));
	str.ReleaseBuffer();
	m_ctrlListInstrument.DeleteString(nIndex);
	m_ctrlListUpdata.AddString(str);
	str.Format(_T("Num = %d"), m_ctrlListInstrument.GetCount());
	m_ctrlStaticInstrumentNum.SetWindowText(str);
	str.Format(_T("Num = %d"), m_ctrlListUpdata.GetCount());
	m_ctrlStaticUpdataNum.SetWindowText(str);
}

void CTabEepromUpdata::OnBnClickedButtonMoverightAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	for (int i = 0; i < m_ctrlListInstrument.GetCount(); i++)
	{
		int iSize = m_ctrlListInstrument.GetTextLen(i);
		m_ctrlListInstrument.GetText(i, str.GetBuffer(iSize));
		str.ReleaseBuffer();
		m_ctrlListUpdata.AddString(str);
	}
	int icount = m_ctrlListInstrument.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListInstrument.DeleteString(i);
	}
	str.Format(_T("Num = %d"), m_ctrlListInstrument.GetCount());
	m_ctrlStaticInstrumentNum.SetWindowText(str);
	str.Format(_T("Num = %d"), m_ctrlListUpdata.GetCount());
	m_ctrlStaticUpdataNum.SetWindowText(str);
}

void CTabEepromUpdata::OnBnClickedButtonMoveleftOne()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_ctrlListUpdata.GetCurSel();
	CString str = _T("");
	if (nIndex == CB_ERR)
	{
		return;
	}

	int n = m_ctrlListUpdata.GetTextLen(nIndex);
	m_ctrlListUpdata.GetText(nIndex, str.GetBuffer(n));
	str.ReleaseBuffer();
	m_ctrlListUpdata.DeleteString(nIndex);
	m_ctrlListInstrument.AddString(str);
	str.Format(_T("Num = %d"), m_ctrlListInstrument.GetCount());
	m_ctrlStaticInstrumentNum.SetWindowText(str);
	str.Format(_T("Num = %d"), m_ctrlListUpdata.GetCount());
	m_ctrlStaticUpdataNum.SetWindowText(str);
}

void CTabEepromUpdata::OnBnClickedButtonMoveleftAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	for (int i = 0; i < m_ctrlListUpdata.GetCount(); i++)
	{
		int iSize = m_ctrlListUpdata.GetTextLen(i);
		m_ctrlListUpdata.GetText(i, str.GetBuffer(iSize));
		str.ReleaseBuffer();
		m_ctrlListInstrument.AddString(str);
	}
	int icount = m_ctrlListUpdata.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListUpdata.DeleteString(i);
	}
	str.Format(_T("Num = %d"), m_ctrlListInstrument.GetCount());
	m_ctrlStaticInstrumentNum.SetWindowText(str);
	str.Format(_T("Num = %d"), m_ctrlListUpdata.GetCount());
	m_ctrlStaticUpdataNum.SetWindowText(str);
}

void CTabEepromUpdata::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnReset();
}

void CTabEepromUpdata::OnBnClickedButtonLoadfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ļ�
	CString str = _T("");
	const wchar_t pszFilter[] = _T("�ı��ļ�(*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".txt"), _T("aa.txt"), OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT, pszFilter, this);

	if ( dlg.DoModal()!=IDOK )
	{		
		str = _T("�����ļ��Ի��򴴽�ʧ�ܣ�");
		m_ctrlListMessage.AddString(str);
		return;
	}
	if (FALSE == LoadFile(dlg.GetPathName()))
	{
		str.Format(_T("�����ļ� %s ʧ�ܣ�"), dlg.GetFileName());
		m_ctrlListMessage.AddString(str);
		return;
	}
	else
	{
		str.Format(_T("�����ļ� %s �ɹ���"), dlg.GetFileName());
		m_ctrlListMessage.AddString(str);
	}
	m_ctrlBtnReadEeprom.EnableWindow(TRUE);
	m_ctrlBtnWriteEeprom.EnableWindow(TRUE);
	m_ctrlBtnStartCheck.EnableWindow(TRUE);
}

void CTabEepromUpdata::OnBnClickedButtonWriteEeprom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned int uiSN = 0, uiIP = 0;
	CString str = _T("");
	CString strOut = _T("");
	UpdateData(TRUE);
	if (0 == m_ctrlListUpdata.GetCount())
	{
		return;
	}
	int iCheckContinueWork = m_ctrlCheckContinueWork.GetCheck();
	int iCheckBroadCast = m_ctrlCheckBroadCastWrite.GetCheck();
	if (iCheckContinueWork == 0)
	{
		if (iCheckBroadCast == 1)
		{
			OnWriteEeprom(0xffffffff, 1);
			strOut = _T("�㲥д��EEPROM��");
			m_ctrlListMessage.AddString(strOut);
		} 
		else
		{
			int nIndex = m_ctrlListUpdata.GetCurSel();
			if (nIndex == CB_ERR)
			{
				return;
			}

			int n = m_ctrlListUpdata.GetTextLen(nIndex);
			m_ctrlListUpdata.GetText(nIndex, str.GetBuffer(n));
			str.ReleaseBuffer();
			_stscanf_s(str, _T("SN = %04x,	IP = %d"), uiSN, uiIP);
			OnWriteEeprom(uiIP, 0);
			strOut.Format(_T("��%s������д��EEPROM��"), str);
			m_ctrlListMessage.AddString(strOut);
		}
	} 
	else
	{
		strOut = _T("��ʼ����д��������EEPROM��");
		m_ctrlListMessage.AddString(strOut);
		for (int i = 0; i < m_ctrlListUpdata.GetCount(); i++)
		{
			int n = m_ctrlListUpdata.GetTextLen(i);
			m_ctrlListUpdata.GetText(i, str.GetBuffer(n));
			str.ReleaseBuffer();
			_stscanf_s(str, _T("SN = %04x,	IP = %d"), uiSN, uiIP);
			OnWriteEeprom(uiIP, 0);
		}
		strOut = _T("�������д��������EEPROM��");
		m_ctrlListMessage.AddString(strOut);
	}
}

void CTabEepromUpdata::OnBnClickedButtonReadEeprom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned int uiSN = 0, uiIP = 0;
	CString str = _T("");
	CString strOut = _T("");
	int nIndex = m_ctrlListUpdata.GetCurSel();
	if (nIndex == CB_ERR)
	{
		return;
	}

	int n = m_ctrlListUpdata.GetTextLen(nIndex);
	m_ctrlListUpdata.GetText(nIndex, str.GetBuffer(n));
	str.ReleaseBuffer();
	_stscanf_s(str, _T("SN = %04x,	IP = %d"), uiSN, uiIP);
	OnReadEeprom(uiIP);
	strOut.Format(_T("��ȡ%s������EEPROM"), str);
	m_ctrlListMessage.AddString(strOut);
}

void CTabEepromUpdata::OnBnClickedButtonStartCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

// ����
void CTabEepromUpdata::OnReset(void)
{
	CString str = _T("");
	int icount = 0;
	
	m_ovecProgram.clear();
	m_ovecProgram.reserve(8192);

	m_uiEditReadAddr = 0;
	m_uiEditReadMax = 0;
	m_uiEditReadTotal = 0;
	m_uiEditWriteAddr = 0;
	m_uiEditWriteMax = 0;
	m_uiEditWriteTotal = 0;

	icount = m_ctrlListInstrument.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListInstrument.DeleteString(i);
	}
	icount = m_ctrlListUpdata.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListUpdata.DeleteString(i);
	}
	icount = m_ctrlListFail.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListFail.DeleteString(i);
	}
	icount = m_ctrlListSuccess.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListSuccess.DeleteString(i);
	}
	icount = m_ctrlListMessage.GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		m_ctrlListMessage.DeleteString(i);
	}

	str.Format(_T("Num = %d"), 0);
	m_ctrlStaticInstrumentNum.SetWindowText(str);
	m_ctrlStaticUpdataNum.SetWindowText(str);
	m_ctrlStaticFailNum.SetWindowText(str);
	m_ctrlStaticSuccessNum.SetWindowText(str);

	m_ctrlCheckBroadCastWrite.SetCheck(0);
	m_ctrlCheckContinueWork.SetCheck(0);

	m_ctrlBtnMoveRightOne.EnableWindow(FALSE);
	m_ctrlBtnMoveRightAll.EnableWindow(FALSE);
	m_ctrlBtnMoveLeftOne.EnableWindow(FALSE);
	m_ctrlBtnMoveLeftAll.EnableWindow(FALSE);
	m_ctrlBtnUpdataInstrumentList.EnableWindow(TRUE);
	m_ctrlBtnLoadFile.EnableWindow(TRUE);
	m_ctrlBtnWriteEeprom.EnableWindow(FALSE);
	m_ctrlBtnReadEeprom.EnableWindow(FALSE);
	m_ctrlBtnStartCheck.EnableWindow(FALSE);
	m_ctrlBtnReset.EnableWindow(TRUE);
	UpdateData(FALSE);
	
	OnCreateEepromSocket();
}

// ��������ļ�
// ��UNICODE�����¶�ȡANSI�ļ�
BOOL CTabEepromUpdata::LoadFile(CString strPath)
{
	if ((_taccess(strPath, 0)) != -1)
	{
		CFile file;
		if(file.Open(strPath, CFile::modeRead) == FALSE)
		{
			return FALSE;
		}
		else
		{
			const int LeftGiveUpNum = 1;
			unsigned int uiTemp = 0;
			char ucTemp[2];
			wchar_t* wchTemp;
			ULONGLONG ullEnd = 0;
			ULONGLONG lActual = 0;
			m_ovecProgram.clear();
			file.SeekToBegin();
			ullEnd = file.SeekToEnd();
			file.SeekToBegin();
			while (lActual < ullEnd)
			{
				file.Seek(LeftGiveUpNum, CFile::current);
				file.Read(ucTemp, 2);
				wchTemp = AnsiToUnicode(ucTemp);
				_stscanf_s(wchTemp, _T("%x"), &uiTemp);
				m_ovecProgram.push_back(uiTemp);
				file.Read(ucTemp, 2);
				wchTemp = AnsiToUnicode(ucTemp);
				_stscanf_s(wchTemp, _T("%x"), &uiTemp);
				m_ovecProgram.push_back(uiTemp);
				lActual = file.Seek(2, CFile::current);
			}
			file.Close();
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

// ����EEPROM��Socket
void CTabEepromUpdata::OnCreateEepromSocket(void)
{
	m_oEepromSocket.Close();
	unsigned int uiRcvPort = EepromRecPort;
	BOOL bReturn = m_oEepromSocket.Create(uiRcvPort, SOCK_DGRAM, NULL);
}

// �ر�
void CTabEepromUpdata::OnClose(void)
{
	m_oEepromSocket.Close();
}

// дEEPROM
void CTabEepromUpdata::OnWriteEeprom(unsigned int uiIPAim, int iBroadCast)
{

}

void CTabEepromUpdata::OnBnClickedCheckBroadcastWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bStatus = (BOOL)::SendMessage(GetDlgItem(IDC_CHECK_BROADCAST_WRITE)->GetSafeHwnd(),   BM_GETCHECK,   0,   0);
	if (bStatus == TRUE)
	{
		m_ctrlCheckContinueWork.SetCheck(0);
	}
}

void CTabEepromUpdata::OnBnClickedCheckContinuework()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bStatus = (BOOL)::SendMessage(GetDlgItem(IDC_CHECK_CONTINUEWORK)->GetSafeHwnd(),   BM_GETCHECK,   0,   0);
	if (bStatus == TRUE)
	{
		m_ctrlCheckBroadCastWrite.SetCheck(0);
	}
}

// ��EEPROM
void CTabEepromUpdata::OnReadEeprom(unsigned int uiIPAim)
{
}
