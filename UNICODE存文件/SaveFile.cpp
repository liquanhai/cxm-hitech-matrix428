#include "StdAfx.h"
#include "SaveFile.h"
#include "Resource.h"
CSaveFile::CSaveFile(void)
: m_csEditShow(_T(""))
, m_csSaveReceiveFile(_T(""))
, m_csSaveFilePath(_T(""))
, m_iSaveSize(1024)
, m_bStartSave(false)
//, m_file(NULL)
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
	GetCurrentDirectory(MAX_PATH, (LPWSTR )cSaveToFilePath);
	// ����������Ϣ���ļ���
	//CreateDirectory(_T("data"),NULL);
	m_csSaveFilePath = cSaveToFilePath;
	m_csSaveFilePath += _T("\\..\\data");
}


// ����
void CSaveFile::OnReset(void)
{
	// ������յ����ݵ��ļ�
	m_csSaveReceiveFile = _T("");
}

// ���浽�ļ���
void CSaveFile::OnSaveToFile(void)
{
	CString csSaveFileTemp ;
	CString csSaveReceiveFileTemp ;
	CString csSaveSendFileTemp;
	CString strFileName ;
	SYSTEMTIME  sysTime;
	m_Sec.Lock();
	csSaveReceiveFileTemp = m_csSaveReceiveFile;
	m_csSaveReceiveFile = "";
	m_Sec.Unlock();

	if (csSaveFileTemp.GetLength() == 0)
	{	
		return;
	}
	// �õ���ǰϵͳʱ��
	GetLocalTime(&sysTime);
	strFileName.Format("%s\\%04d%02d%02d%02d%02d%02d%04d.text", m_csSaveFilePath,sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);

//	errno_t err;
//	//�����ANSI��ʽ���ļ�
//	if((err = fopen_s(&m_file,strFileName,"w+"))==NULL)
//	{
//		fprintf(m_file,_T("%s"),csSaveFileTemp); 
//	}
//	fclose(m_file);

	//�����UNICODE��ʽ���ļ�
	m_file.Open(strFileName, CFile::modeCreate|CFile::modeWrite);	
	CArchive ar(&m_file, CArchive::store);
	ar.WriteString(csSaveFileTemp);
	ar.Close();
	m_file.Close();

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
/*	m_Sec.Lock();
	m_csSaveReceiveFile += strtemp;
	icsSaveFileLength = m_csSaveFile.GetLength();
	m_Sec.Unlock();
*/	//	GetDlgItem(IDC_EDIT_RECEIVE)->SetWindowText(m_cseditshow);
	//	UpdateData(FALSE);
	if (icsSaveFileLength> (m_iSaveSize*1024))
	{	
		OnSaveToFile();
	}
}

