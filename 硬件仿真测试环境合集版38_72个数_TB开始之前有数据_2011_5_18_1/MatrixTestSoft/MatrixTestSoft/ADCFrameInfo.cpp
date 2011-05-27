#include "StdAfx.h"
#include "ADCFrameInfo.h"

CADCFrameInfo::CADCFrameInfo(void)
: m_pFileSave(NULL)
, m_csSaveFilePath(_T(""))
{
}

CADCFrameInfo::~CADCFrameInfo(void)
{
}

// ���ļ�
void CADCFrameInfo::OnOpenFile(void)
{
	CString strFileName = _T("");
	CString strOutput = _T("");
	CString strTemp = _T("");
	errno_t err;
	CString str = _T("");
	SYSTEMTIME  sysTime;
	strFileName += m_csSaveFilePath;
	strTemp = _T("\\ADC����֡��Ϣ.txt");
	strFileName += strTemp;
	// ��ADC�������ݱ����ANSI��ʽ���ļ�
	if((err = fopen_s(&m_pFileSave,strFileName,"w+"))!=NULL)
	{
		AfxMessageBox(_T("ADC����֡��Ϣ�ļ�����ʧ�ܣ�"));	
		return;
	}

	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03d��ʼ��¼ADC֡��Ϣ��\r\n\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	strOutput += str;

	strOutput += _T("\r\n");
	fprintf(m_pFileSave, _T("%s"), strOutput); 
}

// �����ļ�
void CADCFrameInfo::OnSaveFile(unsigned int uiInstrumentNb, unsigned int uiDataPointNum, unsigned int uiSysTime)
{
	CString strOutput = _T("");
	CString strTemp = _T("");
	unsigned int uiDataLength = 0;
	strOutput.Format(_T("�豸ID %d\t֡��PointNum %d\t\t֡���͵�SysTime %d\n"), uiInstrumentNb, uiDataPointNum, uiSysTime);
	fprintf(m_pFileSave, _T("%s"), strOutput); 
}

// �ر��ļ�
void CADCFrameInfo::OnCloseFile(void)
{
	if (m_pFileSave == NULL)
	{
		return;
	}
	fclose(m_pFileSave); 
}
