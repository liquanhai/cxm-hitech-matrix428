#include "StdAfx.h"
#include "ADCDataSaveToFile.h"

CADCDataSaveToFile::CADCDataSaveToFile(void)
: m_bOpenADCSaveFile(FALSE)
, m_uiADCSaveFileNum(0)
/*, m_pFileSave(NULL)*/
, m_uiADCDataToSaveNum(0)
, m_uiADCFileLength(0)
, m_csSaveFilePath(_T(""))
{
}

CADCDataSaveToFile::~CADCDataSaveToFile(void)
{
}

// ��ADC���ݱ��浽�ļ���
void CADCDataSaveToFile::OnSaveADCToFile(double(* dpADCDataBuf)[ADCDataTempDataSize], unsigned int* upADCDataNum,
										 unsigned int uiADCDataToSaveNum, bool bFinish)
{
	CString strOutput = _T("");
	CString strTemp = _T("");
	unsigned int uiDataLength = 0;

	if(m_bOpenADCSaveFile == FALSE)
	{
		OnOpenADCSaveFile();
	}
	// @@@@@@@@ֹͣ�ɼ�ʱ���ļ������
	// �����������������
	for (unsigned int i=0; i<uiADCDataToSaveNum; i++)
	{
		//		ProcessMessages();
		for (int j=0; j<InstrumentNum; j++)
		{
			//			ProcessMessages();
			uiDataLength = upADCDataNum[j];
			if (uiDataLength == 0 )
			{
				strOutput += _T("\t\t");
				continue;
			}
			if (uiDataLength > i)
			{	
				strTemp.Format(_T("%2.*lf\t"), DecimalPlaces, dpADCDataBuf[j][i]);
				strOutput += strTemp;
			}
			else
			{
				strOutput += _T("\t\t");
			}
		}
		strOutput += _T("\r\n");
	}
	//	fprintf(m_pFileSave, _T("%s"), strOutput); 
// 	CArchive ar(&m_FileSave, CArchive::store);
// 	ar.WriteString(strOutput);
// 	ar.Close();
	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
	int ansiCount=WideCharToMultiByte(CP_ACP,0,strOutput,-1,NULL,0,NULL,NULL);
	char * pTempChar=(char*)malloc(ansiCount*sizeof(char));
	memset(pTempChar,0,ansiCount);
	WideCharToMultiByte(CP_ACP,0,strOutput,-1,pTempChar,ansiCount,NULL,NULL);
	m_FileSave.Write(pTempChar, ansiCount);
	free(pTempChar);

	if (bFinish == false)
	{
		m_uiADCDataToSaveNum += uiADCDataToSaveNum;
		if (m_uiADCDataToSaveNum == m_uiADCFileLength)
		{
			m_uiADCDataToSaveNum = 0;
			OnCloseADCSaveFile();
		}
	}
	else
	{
		OnCloseADCSaveFile();
		m_uiADCDataToSaveNum = 0;
		m_uiADCSaveFileNum = 0;
	}
}
// ��������ADC���������ļ�
void CADCDataSaveToFile::OnOpenADCSaveFile(void)
{
	m_uiADCSaveFileNum++;
	CString strFileName = _T("");
	CString strOutput = _T("");
	CString strTemp = _T("");
	//	errno_t err;
	CString str = _T("");
	SYSTEMTIME  sysTime;
	// ѡ�е�������������
	wchar_t cSelectObjectName[InstrumentNum][RcvFrameSize];
	strFileName += m_csSaveFilePath;
	strTemp.Format(_T("\\%d.text"), m_uiADCSaveFileNum);
	strFileName += strTemp;
	// ��ADC�������ݱ����ANSI��ʽ���ļ�
	// 	if((err = fopen_s(&m_pFileSave,strFileName,"w+"))!=NULL)
	// 	{
	// 		AfxMessageBox(_T("ADC���ݴ洢�ļ�����ʧ�ܣ�"));	
	// 		return;
	// 	}
	//�����UNICODE��ʽ���ļ�
	if(m_FileSave.Open(strFileName, CFile::modeCreate|CFile::modeWrite) == FALSE)
	{
		AfxMessageBox(_T("ADC���ݴ洢�ļ�����ʧ�ܣ�"));	
		return;
	}

	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03d��ʼ��¼ADC�������ݣ�\r\n\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	strOutput += str;

	// ���������ǩ
	for (int i=0; i<InstrumentNum; i++)
	{
		ProcessMessages();
		strTemp.Format(_T("����%d"), i+1);
		wchar_t* pchar = strTemp.GetBuffer(0); 
		_tcscpy_s(cSelectObjectName[i],pchar);
		strTemp.Format(_T("%s\t\t"), cSelectObjectName[i]);
		strOutput += strTemp;
	}

	strOutput += _T("\r\n");
	//	fprintf(m_pFileSave, _T("%s"), strOutput); 
// 	CArchive ar(&m_FileSave, CArchive::store);
// 	ar.WriteString(strOutput);
// 	ar.Close();

	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
	int ansiCount=WideCharToMultiByte(CP_ACP,0,strOutput,-1,NULL,0,NULL,NULL);
	char * pTempChar=(char*)malloc(ansiCount*sizeof(char));
	memset(pTempChar,0,ansiCount);
	WideCharToMultiByte(CP_ACP,0,strOutput,-1,pTempChar,ansiCount,NULL,NULL);
	m_FileSave.Write(pTempChar, ansiCount);
	free(pTempChar);

	m_bOpenADCSaveFile = TRUE;
}
// �ر�ADC���������ļ�
void CADCDataSaveToFile::OnCloseADCSaveFile(void)
{
	// 	if (m_pFileSave == NULL)
	// 	{
	// 		return;
	// 	}
	// 	fclose(m_pFileSave); 
	m_FileSave.Close();
	m_bOpenADCSaveFile = FALSE;
}
// ��ֹ������ѭ���������޷���Ӧ��Ϣ
void CADCDataSaveToFile::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}