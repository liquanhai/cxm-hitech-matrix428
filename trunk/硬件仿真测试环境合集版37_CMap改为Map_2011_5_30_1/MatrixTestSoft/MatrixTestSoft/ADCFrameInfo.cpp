#include "StdAfx.h"
#include "ADCFrameInfo.h"
CADCFrameInfo::CADCFrameInfo(void)
: m_csSaveFilePath(_T(""))
/*, m_pFileSave(NULL)*/
, m_arFileSave(NULL)
{
}

CADCFrameInfo::~CADCFrameInfo(void)
{
}

// ���ļ�
void CADCFrameInfo::OnOpenFile(void)
{
	CString strFileName = _T("");
	CString strTemp = _T("");
//	errno_t err;
	CString str = _T("");
	SYSTEMTIME  sysTime;
	strFileName += m_csSaveFilePath;
	strTemp = _T("\\ADC����֡��Ϣ.txt");
	strFileName += strTemp;
// 	// ��ADC�������ݱ����ANSI��ʽ���ļ�
// 	if((err = fopen_s(&m_pFileSave,strFileName,"w+"))!=NULL)
// 	{
// 		AfxMessageBox(_T("ADC����֡��Ϣ�ļ�����ʧ�ܣ�"));	
// 		return;
// 	}
	//�����UNICODE��ʽ���ļ�
	if(m_FileSave.Open(strFileName, CFile::modeCreate|CFile::modeWrite) == FALSE)
	{
		AfxMessageBox(_T("ADC����֡��Ϣ�ļ�����ʧ�ܣ�"));	
		return;
	}
	m_FileSave.Write("\xff\xfe", 2);    // ����Unicode�����ļ�ͷ
	m_arFileSave = new CArchive(&m_FileSave, CArchive::store);
	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03d��ʼ��¼ADC֡��Ϣ��\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);

//	fprintf(m_pFileSave, _T("%s"), strOutput);
	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
//	WriteCHToCFile(m_arFileSave, str);
	if (m_FileSave.m_hFile != CFile::hFileNull)
	{
		m_arFileSave->WriteString(str);
	}
}

// �����ļ�
void CADCFrameInfo::OnSaveFile(unsigned int uiInstrumentNb, unsigned int uiDataPointNum, unsigned int uiSysTime)
{
	CString strOutput = _T("");

	SYSTEMTIME  sysTime;
	CString str = _T("");
	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d�� %02d:%02d:%02d:%03d\t"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);

	strOutput.Format(_T("�豸ID %d\t֡��PointNum %d\t\t֡���͵�SysTime %d\r\n"), uiInstrumentNb, uiDataPointNum, uiSysTime);
	strOutput = str + strOutput;
//	fprintf(m_pFileSave, _T("%s"), strOutput); 
// 	CArchive ar(&m_FileSave, CArchive::store);
// 	ar.WriteString(strOutput);
// 	ar.Close();
	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
//	WriteCHToCFile(m_arFileSave, strOutput);
	if (m_FileSave.m_hFile != CFile::hFileNull)
	{
		m_arFileSave->WriteString(strOutput);
	}
}

// �ر��ļ�
void CADCFrameInfo::OnCloseFile(void)
{
	if (m_FileSave.m_hFile != CFile::hFileNull)
	{
		m_arFileSave->Close();
		m_FileSave.Close();
		delete m_arFileSave;
	}
}
