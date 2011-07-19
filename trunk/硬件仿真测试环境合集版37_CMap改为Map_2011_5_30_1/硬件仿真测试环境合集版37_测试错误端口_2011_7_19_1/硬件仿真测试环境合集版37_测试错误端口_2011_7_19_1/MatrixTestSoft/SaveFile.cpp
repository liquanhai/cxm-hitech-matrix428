#include "StdAfx.h"
#include "SaveFile.h"
#include "Resource.h"
#include "Parameter.h"

CSaveFile::CSaveFile(void)
: m_csEditShow(_T(""))
, m_csSaveFile(_T(""))
, m_csSaveReceiveFile(_T(""))
, m_csSaveSendFile(_T(""))
, m_csSaveFilePath(_T(""))
, m_iSaveSize(0)
, m_bStartSave(false)
, m_pWndTab(NULL)
{
}

CSaveFile::~CSaveFile(void)
{
}

// ��ʼ��
//************************************
// Method:    OnInit
// FullName:  CSaveFile::OnInit
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSaveFile::OnInit(void)
{
	// ����������Ϣ���ļ���
	m_csSaveFilePath += _T("\\���ݱ���");
	CreateDirectory(m_csSaveFilePath, NULL);
}

// ��ʼ���ݴ洢
//************************************
// Method:    OnSaveStart
// FullName:  CSaveFile::OnSaveStart
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSaveFile::OnSaveStart(void)
{
	m_bStartSave = true;
}

// ֹͣ���ݴ洢
//************************************
// Method:    OnSaveStop
// FullName:  CSaveFile::OnSaveStop
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSaveFile::OnSaveStop(void)
{
	m_bStartSave = false;
	CString strtemp = _T("");
	m_Sec_SavePortMonitorFrame.Lock();
	strtemp = m_csEditShow;
	m_Sec_SavePortMonitorFrame.Unlock();
	m_pWndTab->GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(strtemp);
	OnSaveToFile();
}

// ѡ���ļ��洢·��
//************************************
// Method:    OnSelectSaveFilePath
// FullName:  CSaveFile::OnSelectSaveFilePath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSaveFile::OnSelectSaveFilePath(void)
{
	wchar_t szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;

	bi.hwndOwner = m_hWnd;	// ָ�������ڣ��ڶԻ�����ʾ�ڼ䣬�����ڽ������� 
	bi.pidlRoot = NULL;				// ���ָ��NULL�����ԡ����桱Ϊ�� 
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = _T("��ѡ�����ݴ洢Ŀ¼");	// ��һ�н���ʾ�ڶԻ���Ķ��� 
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
//************************************
// Method:    OnReset
// FullName:  CSaveFile::OnReset
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSaveFile::OnReset(void)
{
	m_csEditShow.Empty();
	// ����ͨѶ�ļ�
	m_csSaveFile.Empty();
	// ������յ����ݵ��ļ�
	m_csSaveReceiveFile.Empty();
	// ���淢�͵����ݵ��ļ�
	m_csSaveSendFile.Empty();
	m_pWndTab->GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(_T(""));
}

// ���浽�ļ���
//************************************
// Method:    OnSaveToFile
// FullName:  CSaveFile::OnSaveToFile
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSaveFile::OnSaveToFile(void)
{
	CString csSaveFileTemp = _T("");
	CString csSaveReceiveFileTemp = _T("");
	CString csSaveSendFileTemp = _T("");
	CString strFileName = _T("");
	CString str = _T("");
	SYSTEMTIME  sysTime;
//	errno_t err;
	m_Sec_SavePortMonitorFrame.Lock();
	csSaveFileTemp = m_csSaveFile;
	csSaveReceiveFileTemp = m_csSaveReceiveFile;
	csSaveSendFileTemp = m_csSaveSendFile;
	m_csSaveFile.Empty();
	m_csSaveReceiveFile.Empty();
	m_csSaveSendFile.Empty();
	m_Sec_SavePortMonitorFrame.Unlock();

	if (csSaveFileTemp.GetLength() == 0)
	{	
		return;
	}
	// �õ���ǰϵͳʱ��
	GetLocalTime(&sysTime);
	strFileName.Empty();
	strFileName += m_csSaveFilePath;
	str.Format(_T("\\%04d%02d%02d%02d%02d%02d%03d.text"),sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	strFileName += str;
	//	m_file = NULL;
	//�����ANSI��ʽ���ļ�
	// 	if((err = fopen_s(&m_file,strFileName,"w+"))==NULL)
	// 	{
	// 		if (m_file != NULL)
	// 		{
	// 			fprintf(m_file,_T("%s"),csSaveFileTemp); 
	// 			fclose(m_file);
	// 		}
	// 	}
	//�����UNICODE��ʽ���ļ�
	if(m_file.Open(strFileName, CFile::modeCreate|CFile::modeWrite) == TRUE)
	{
// 		CArchive ar(&m_file, CArchive::store);
// 		ar.WriteString(csSaveFileTemp);
// 		ar.Close();
		//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
		WriteCHToCFile(&m_file, csSaveFileTemp);
		m_file.Close();
	}
	// ������յ������ݵ��ļ�
	if (csSaveReceiveFileTemp.GetLength() != 0)
	{
		strFileName.Empty();
		strFileName += m_csSaveFilePath;
		str.Format(_T("\\Rec%04d%02d%02d%02d%02d%02d%03d.text"),sysTime.wYear,sysTime.wMonth,sysTime.wDay,
			sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
		strFileName += str;
		// 		m_file = NULL;
		// 		//�����ANSI��ʽ���ļ�
		// 		if((err = fopen_s(&m_file,strFileName,"w+"))==NULL)
		// 		{
		// 			if (m_file != NULL)
		// 			{
		// 				fprintf(m_file,_T("%s"),csSaveReceiveFileTemp); 
		// 				fclose(m_file);
		// 			}
		// 		}
		//�����UNICODE��ʽ���ļ�
		if(m_file.Open(strFileName, CFile::modeCreate|CFile::modeWrite) == TRUE)
		{
// 			CArchive ar(&m_file, CArchive::store);
// 			ar.WriteString(csSaveReceiveFileTemp);
// 			ar.Close();
			//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
			WriteCHToCFile(&m_file, csSaveReceiveFileTemp);
			m_file.Close();
		}
	}
	// ���淢�͵����ݵ��ļ�
	if (csSaveSendFileTemp.GetLength() != 0)
	{
		strFileName.Empty();
		strFileName += m_csSaveFilePath;
		str.Format(_T("\\Send%04d%02d%02d%02d%02d%02d%03d.text"),sysTime.wYear,sysTime.wMonth,sysTime.wDay,
			sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
		strFileName += str;
		// 		m_file = NULL;
		// 		//�����ANSI��ʽ���ļ�
		// 		if((err = fopen_s(&m_file,strFileName,"w+"))==NULL)
		// 		{
		// 			if (m_file != NULL)
		// 			{
		// 					fprintf(m_file,_T("%s"),csSaveSendFileTemp); 
		// 					fclose(m_file);
		// 			}
		// 		}
		//�����UNICODE��ʽ���ļ�
		if(m_file.Open(strFileName, CFile::modeCreate|CFile::modeWrite) == TRUE)
		{
// 			CArchive ar(&m_file, CArchive::store);
// 			ar.WriteString(csSaveSendFileTemp);
// 			ar.Close();
			//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
			WriteCHToCFile(&m_file, csSaveSendFileTemp);
			m_file.Close();
		}
	}
}

// �����������
//************************************
// Method:    OnSaveReceiveData
// FullName:  CSaveFile::OnSaveReceiveData
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned char * buf
// Parameter: int iRecLength
//************************************
void CSaveFile::OnSaveReceiveData(unsigned char* buf, int iRecLength)
{
	if (m_bStartSave == FALSE)
	{
		return;
	}

	CString str = _T("");
	CString strtemp = _T("");
	int icsSaveFileLength = 0;
	wchar_t buffer[_CVTBUFSIZE];

	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);

	str.Format(_T("%04d.%02d.%02d %02d:%02d:%02d:%03d �������� ���ݰ���СΪ %d ����Ϊ��\r\n"),sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds, iRecLength);
	strtemp += str;

	for (int i=0; i<iRecLength; i++)
	{
		// ����2������_stprintf_s�����ķ�����CPUռ���ʴﵽ10%
		_stprintf_s(buffer, _CVTBUFSIZE, _T("%02x "), buf[i]);
		strtemp += buffer;
// 		str.Format(_T("%02x "),buf[i]);
// 		strtemp += str;
	}

	strtemp += _T("\r\n");
	m_Sec_SavePortMonitorFrame.Lock();
	m_csSaveFile += strtemp;
	m_csSaveReceiveFile += strtemp;
	m_csEditShow += strtemp;
	icsSaveFileLength = m_csSaveFile.GetLength();
	m_Sec_SavePortMonitorFrame.Unlock();
	if (icsSaveFileLength> (m_iSaveSize*1024))
	{	
		OnSaveToFile();
	}
}

// ���淢������
//************************************
// Method:    OnSaveSendData
// FullName:  CSaveFile::OnSaveSendData
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned char * buf
// Parameter: int iSendLength
//************************************
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
	wchar_t buffer[_CVTBUFSIZE];

	str.Format(_T("%04d.%02d.%02d %02d:%02d:%02d:%03d �������� ���ݰ���СΪ %d ����Ϊ��\r\n"),sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds, iSendLength);
	strtemp += str;

	for (int i=0; i<iSendLength; i++)
	{
		// ����2������_stprintf_s�����ķ�����CPUռ���ʴﵽ10%
		_stprintf_s(buffer, _CVTBUFSIZE, _T("%02x "), buf[i]);
		strtemp += buffer;
// 		str.Format(_T("%02x "),buf[i]);
// 		strtemp += str;
	}

	strtemp += _T("\r\n");
	m_Sec_SavePortMonitorFrame.Lock();
	m_csSaveFile += strtemp;
	m_csSaveSendFile += strtemp;
	m_csEditShow += strtemp;
	icsSaveFileLength = m_csSaveFile.GetLength();
	m_Sec_SavePortMonitorFrame.Unlock();
	//	GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(m_cseditshow);
	// ��UpdateData(FALSE)���ٷ���ˢ�½����ռ�ô�����Դ�������ٶ�
	//	UpdateData(FALSE);
	if (icsSaveFileLength > (m_iSaveSize*1024))
	{
		OnSaveToFile();
	}
}

// ��ֹ������ѭ���������޷���Ӧ��Ϣ
//************************************
// Method:    ProcessMessages
// FullName:  CSaveFile::ProcessMessages
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSaveFile::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}
