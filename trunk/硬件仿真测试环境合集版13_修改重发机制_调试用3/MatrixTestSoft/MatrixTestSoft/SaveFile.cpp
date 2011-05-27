#include "StdAfx.h"
#include "SaveFile.h"
#include "Resource.h"
CSaveFile::CSaveFile(void)
: m_csEditShow(_T(""))
, m_csSaveFile(_T(""))
, m_csSaveReceiveFile(_T(""))
, m_csSaveSendFile(_T(""))
, m_csSaveFilePath(_T(""))
, m_iSaveSize(1024)
, m_bStartSave(false)
, m_pWndTab(NULL)
, m_file(NULL)
{
}

CSaveFile::~CSaveFile(void)
{
}

// ��ʼ��
void CSaveFile::OnInit(void)
{
	char cSaveToFilePath[MAX_PATH];
	// �õ���ǰ·��
	GetCurrentDirectory(MAX_PATH, cSaveToFilePath);
	// ����������Ϣ���ļ���
	CreateDirectory(_T("���ݱ���"),NULL);
	m_csSaveFilePath = cSaveToFilePath;
	m_csSaveFilePath += _T("\\���ݱ���");
}

// ��ʼ���ݴ洢
void CSaveFile::OnSaveStart(void)
{
	m_bStartSave = true;
}

// ֹͣ���ݴ洢
void CSaveFile::OnSaveStop(void)
{
	m_bStartSave = false;
	CString strtemp = _T("");
	m_Sec.Lock();
	strtemp = m_csEditShow;
	m_Sec.Unlock();
	m_pWndTab->GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(strtemp);
	OnSaveToFile();
}

// ѡ���ļ��洢·��
void CSaveFile::OnSelectSaveFilePath(void)
{
	char szDir[MAX_PATH];

	BROWSEINFO bi;

	ITEMIDLIST *pidl;

	bi.hwndOwner = m_hWnd; // ָ�������ڣ��ڶԻ�����ʾ�ڼ䣬�����ڽ������� 


	bi.pidlRoot = NULL; // ���ָ��NULL�����ԡ����桱Ϊ�� 

	bi.pszDisplayName = szDir; 

	bi.lpszTitle = "��ѡ�����ݴ洢Ŀ¼"; // ��һ�н���ʾ�ڶԻ���Ķ��� 

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
		m_csSaveFilePath = szDir;
	}
}

// ����
void CSaveFile::OnReset(void)
{
	m_csEditShow = _T("");
	// ����ͨѶ�ļ�
	m_csSaveFile = _T("");
	// ������յ����ݵ��ļ�
	m_csSaveReceiveFile = _T("");
	// ���淢�͵����ݵ��ļ�
	m_csSaveSendFile = _T("");
	m_pWndTab->GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(_T(""));
}

// ���浽�ļ���
void CSaveFile::OnSaveToFile(void)
{
	CString csSaveFileTemp = "";
	CString csSaveReceiveFileTemp = "";
	CString csSaveSendFileTemp = "";
	CString strFileName = "";
	SYSTEMTIME  sysTime;
	m_Sec.Lock();
	csSaveFileTemp = m_csSaveFile;
	csSaveReceiveFileTemp = m_csSaveReceiveFile;
	csSaveSendFileTemp = m_csSaveSendFile;
	m_csSaveFile = "";
	m_csSaveReceiveFile = "";
	m_csSaveSendFile = "";
	m_Sec.Unlock();

	if (csSaveFileTemp.GetLength() == 0)
	{	
		return;
	}
	// �õ���ǰϵͳʱ��
	GetLocalTime(&sysTime);
	strFileName.Format("%s\\%04d%02d%02d%02d%02d%02d%04d.text", m_csSaveFilePath,sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);

	errno_t err;
	//�����ANSI��ʽ���ļ�
	if((err = fopen_s(&m_file,strFileName,"w+"))==NULL)
	{
		fprintf(m_file,_T("%s"),csSaveFileTemp); 
	}
	fclose(m_file);
	// ������յ������ݵ��ļ�
	if (csSaveReceiveFileTemp.GetLength() != 0)
	{
		strFileName.Format("%s\\Rec%04d%02d%02d%02d%02d%02d%04d.text", m_csSaveFilePath,sysTime.wYear,sysTime.wMonth,sysTime.wDay,
			sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);

		errno_t err;
		//�����ANSI��ʽ���ļ�
		if((err = fopen_s(&m_file,strFileName,"w+"))==NULL)
		{
			fprintf(m_file,_T("%s"),csSaveReceiveFileTemp); 
		}
		fclose(m_file);
	}
	// ���淢�͵����ݵ��ļ�
	if (csSaveSendFileTemp.GetLength() != 0)
	{
		strFileName.Format("%s\\Send%04d%02d%02d%02d%02d%02d%04d.text", m_csSaveFilePath,sysTime.wYear,sysTime.wMonth,sysTime.wDay,
			sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);

		errno_t err;
		//�����ANSI��ʽ���ļ�
		if((err = fopen_s(&m_file,strFileName,"w+"))==NULL)
		{
			fprintf(m_file,_T("%s"),csSaveSendFileTemp); 
		}
		fclose(m_file);
	}
}

// �����������
void CSaveFile::OnSaveReceiveData(unsigned char* buf, int iRecLength)
{
	if (m_bStartSave == FALSE)
	{
		return;
	}

	CString str = _T("");
	CString strtemp = _T("");
	int icsSaveFileLength = 0;

	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);

	str.Format(_T("%04d.%02d.%02d %02d:%02d:%02d:%04d �������� ���ݰ���СΪ %d ����Ϊ��\r\n"),sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds, iRecLength);
	strtemp += str;

	for (int i=0; i<iRecLength; i++)
	{
		str.Format(_T("%02x "),buf[i]);
		strtemp += str;
	}

	strtemp += _T("\r\n");
	m_Sec.Lock();
	m_csSaveFile += strtemp;
	m_csSaveReceiveFile += strtemp;
	m_csEditShow += strtemp;
	icsSaveFileLength = m_csSaveFile.GetLength();
	m_Sec.Unlock();
	//	GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(m_cseditshow);
	//	UpdateData(FALSE);
	if (icsSaveFileLength> (m_iSaveSize*1024))
	{	
		OnSaveToFile();
	}
}

// ���淢������
void CSaveFile::OnSaveSendData(unsigned char* buf, int iSendLength)
{
	if (m_bStartSave == FALSE)
	{
		return;
	}
	CString str = _T("");
	CString strtemp = _T("");
	int icsSaveFileLength = 0;
	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);

	str.Format(_T("%04d.%02d.%02d %02d:%02d:%02d:%04d �������� ���ݰ���СΪ %d ����Ϊ��\r\n"),sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds, iSendLength);
	strtemp += str;

	for (int i=0; i<iSendLength; i++)
	{
		str.Format(_T("%02x "),buf[i]);
		strtemp += str;

	}

	strtemp += _T("\r\n");
	m_Sec.Lock();
	m_csSaveFile += strtemp;
	m_csSaveSendFile += strtemp;
	m_csEditShow += strtemp;
	icsSaveFileLength = m_csSaveFile.GetLength();
	m_Sec.Unlock();
	//	GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(m_cseditshow);
	// ��UpdateData(FALSE)���ٷ���ˢ�½����ռ�ô�����Դ�������ٶ�
	//	UpdateData(FALSE);
	if (icsSaveFileLength > (m_iSaveSize*1024))
	{
// 		CWnd* pwnd = AfxGetMainWnd();
// 		m_oThreadManage.m_SendThread.m_csTailFrameShow = _T("");
// 		pwnd->GetDlgItem(IDC_EDIT_TAILFRAMESHOW)->SetWindowText(_T(""));
// 		m_oThreadManage.m_SendThread.m_csTailTimeReturnShow = _T("");
// 		pwnd->GetDlgItem(IDC_EDIT_TAILTIMERETURNSHOW)->SetWindowText(_T(""));
// 		m_oThreadManage.m_SendThread.m_csDelayTimeReturnShow = _T("");
// 		pwnd->GetDlgItem(IDC_EDIT_DELAYTIMERETURNSHOW)->SetWindowText(_T(""));
// 		m_oThreadManage.m_SendThread.m_csADCDataRecShow = _T("");
// 		pwnd->GetDlgItem(IDC_EDIT_ADCDATARECSHOW)->SetWindowText(_T(""));
		OnSaveToFile();
	}
}
