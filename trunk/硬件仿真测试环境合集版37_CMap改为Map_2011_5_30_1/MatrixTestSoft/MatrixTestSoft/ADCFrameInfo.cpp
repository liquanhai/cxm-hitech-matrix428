#include "StdAfx.h"
#include "ADCFrameInfo.h"
CADCFrameInfo::CADCFrameInfo(void)
: m_csSaveFilePath(_T(""))
/*, m_pFileSave(NULL)*/
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

	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03d��ʼ��¼ADC֡��Ϣ��\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);

//	fprintf(m_pFileSave, _T("%s"), strOutput);
	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
	WriteCHToCFile(&m_FileSave, str);
}

// �����ļ�
void CADCFrameInfo::OnSaveFile(unsigned int uiInstrumentNb, unsigned int uiDataPointNum, unsigned int uiSysTime)
{
	CString strOutput = _T("");
	strOutput.Format(_T("�豸ID %d\t֡��PointNum %d\t\t֡���͵�SysTime %d\n"), uiInstrumentNb, uiDataPointNum, uiSysTime);
//	fprintf(m_pFileSave, _T("%s"), strOutput); 
// 	CArchive ar(&m_FileSave, CArchive::store);
// 	ar.WriteString(strOutput);
// 	ar.Close();
	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
	WriteCHToCFile(&m_FileSave, strOutput);
}

// �ر��ļ�
void CADCFrameInfo::OnCloseFile(void)
{
// 	if (m_pFileSave == NULL)
// 	{
// 		return;
// 	}
// 	fclose(m_pFileSave); 
	m_FileSave.Close();
}
