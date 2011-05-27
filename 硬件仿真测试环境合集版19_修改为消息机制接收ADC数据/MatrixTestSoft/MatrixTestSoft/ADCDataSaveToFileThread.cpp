// ADCDataSaveToFileThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "ADCDataSaveToFileThread.h"


// CADCDataSaveToFileThread

IMPLEMENT_DYNCREATE(CADCDataSaveToFileThread, CWinThread)

CADCDataSaveToFileThread::CADCDataSaveToFileThread()
: m_bclose(false)
, m_pSelectObject(NULL)
, m_pSelectObjectNoise(NULL)
, m_pFileSave(NULL)
, m_bOpenADCSaveFile(FALSE)
, m_uiADCDataToSaveNum(0)
, m_uiADCFileLength(0)
, m_csSaveFilePath(_T(""))
, m_uiADCSaveFileNum(0)
, m_bStopSample(FALSE)
{
}

CADCDataSaveToFileThread::~CADCDataSaveToFileThread()
{
}

BOOL CADCDataSaveToFileThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CADCDataSaveToFileThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CADCDataSaveToFileThread, CWinThread)
END_MESSAGE_MAP()


// CADCDataSaveToFileThread ��Ϣ�������

int CADCDataSaveToFileThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���

	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
		OnProcess();
		if (m_bclose == true)
		{
			break;
		}
//		Sleep(5);
		WaitForSingleObject(m_hADCDataSaveToFileThreadWork, 5); 
		::ResetEvent(m_hADCDataSaveToFileThreadWork); // �����¼�����Ϊ���ź�״̬
	}
	::SetEvent(m_hADCDataSaveToFileThreadClose);	// �����¼�����Ϊ���ź�״̬
	return CWinThread::Run();
}

// ��ʼ��
void CADCDataSaveToFileThread::OnInit(void)
{
	m_hADCDataSaveToFileThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hADCDataSaveToFileThreadClose);	// �����¼�����Ϊ���ź�״̬
	m_hADCDataSaveToFileThreadWork = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hADCDataSaveToFileThreadWork);	// �����¼�����Ϊ���ź�״̬
	for (int i=0; i<GraphViewNum; i++)
	{
		ProcessMessages();
		m_uiADCFrameSaveToFileRecNum[i] = 0;
		m_uiADCFrameSaveToFileProcNum[i] = 0;
		m_uiADCFrameRemain[i] = 0;
		m_uiADCFrameSaved[i] = 0;
		memset(m_dADCSaveToFileProcBuf[i], 0, ADCDataSaveToFileBufSize);
	}
}

// ��ʼ
void CADCDataSaveToFileThread::OnOpen(void)
{
	for (int i=0; i<GraphViewNum; i++)
	{
		ProcessMessages();
		m_uiADCFrameSaveToFileRecNum[i] = 0;
		m_uiADCFrameSaveToFileProcNum[i] = 0;
		m_uiADCFrameRemain[i] = 0;
		m_uiADCFrameSaved[i] = 0;
		memset(m_dADCSaveToFileProcBuf[i], 0, ADCDataSaveToFileBufSize);
	}
}

// ֹͣ
void CADCDataSaveToFileThread::OnStop(void)
{
}

// �ر�
void CADCDataSaveToFileThread::OnClose(void)
{
	m_bclose = true;
}

// ��ֹ������ѭ���������޷���Ӧ��Ϣ
void CADCDataSaveToFileThread::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// ��ADC���ݱ��浽�ļ�
void CADCDataSaveToFileThread::OnProcess(void)
{
	unsigned int uiSaveLength = 0;
	uiSaveLength = ReceiveDataSize * ADCFrameNumNeedToSave;
	for (int i=0; i<GraphViewNum; i++)
	{
		if (m_uiADCFrameSaveToFileRecNum[i] > 0)
		{
			unsigned int uiPos = 0;
			ProcessMessages();
			// �����ջ����������ݿ������������ջ�������0
			uiPos = m_uiADCFrameSaveToFileProcNum[i];
			m_uiADCFrameSaveToFileProcNum[i] += m_uiADCFrameSaveToFileRecNum[i];
		
			uiPos = uiPos * uiSaveLength;
			
			if (m_uiADCFrameSaveToFileProcNum[i] > ADCDataSaveToFileBufNum)
			{
				//????�������⻺�����������ʱ����
//				m_uiADCFrameSaveToFileProcNum[i] = 0;
				AfxMessageBox(_T("ADC�ļ��洢���������������"));
			}
			else
			{
//				memcpy(&m_dADCSaveToFileProcBuf[i][uiPos], &m_dADCSaveToFileRecBuf[i], m_uiADCFrameSaveToFileRecNum[i] * uiSaveLength);
				for (unsigned int j=0; j<m_uiADCFrameSaveToFileRecNum[i] * uiSaveLength; j++)
				{
					m_dADCSaveToFileProcBuf[i][uiPos + j] = m_dADCSaveToFileRecBuf[i][j];
				}
				memset(m_dADCSaveToFileRecBuf[i], 0, ADCDataSaveToFileBufSize);
				m_uiADCFrameSaveToFileRecNum[i] = 0;
				TRACE2("�洢�߳��豸���%d������֡��%d\r\n", i, m_uiADCFrameSaveToFileProcNum[i]);
			}
		}
	}
	// �����ļ��洢
	OnSaveADCDataFramesToFile();
}
void CADCDataSaveToFileThread::OnSaveADCDataFramesToFile(void)
{
	unsigned int uiMin = 0;
	unsigned int uiMax = 0;
	unsigned int uiSaveDataNum = 0;
	unsigned int uiADCDataToSaveFrameNum = 0;
	uiADCDataToSaveFrameNum = m_uiADCDataToSaveNum;
	uiMin = OnCalMinProcNum();
	if (uiMin > 0)
	{
		uiSaveDataNum = uiMin*ADCFrameNumNeedToSave*ReceiveDataSize;
		if ((uiADCDataToSaveFrameNum + uiSaveDataNum) > m_uiADCFileLength)
		{
			OnSaveADCToFile(m_uiADCFileLength - uiADCDataToSaveFrameNum);
			OnSaveADCToFile(uiSaveDataNum + uiADCDataToSaveFrameNum - m_uiADCFileLength, m_uiADCFileLength - uiADCDataToSaveFrameNum);
		}
		else
		{
			OnSaveADCToFile(uiSaveDataNum);
		}

		OnClearProcData(uiMin);
		for (int i=0; i<GraphViewNum; i++)
		{
			m_uiADCFrameSaved[i] += uiMin * ADCFrameNumNeedToSave;
		}
	}
	if (m_bStopSample == TRUE)
	{
		// ����ʣ�����ݵ��ļ�
		m_bStopSample = FALSE;
		uiADCDataToSaveFrameNum = m_uiADCDataToSaveNum;
		uiMax = OnCalMaxNeedToSaveDataNum();
		if (uiMax > 0)
		{
			if ((uiADCDataToSaveFrameNum + uiMax) > m_uiADCFileLength)
			{
				OnSaveADCToFile(m_uiADCFileLength - uiADCDataToSaveFrameNum);
				OnSaveADCToFile(uiMax + uiADCDataToSaveFrameNum - m_uiADCFileLength, m_uiADCFileLength - uiADCDataToSaveFrameNum);
			}
			else
			{
				OnSaveADCToFile(uiMax);
			}
		}
		OnCloseADCSaveFile();
	}
	
}
// �������С�Ĵ��������
unsigned int CADCDataSaveToFileThread::OnCalMinProcNum(void)
{
	unsigned int uiMin = 0;
	unsigned int uiCount = 0;
	for (unsigned int i=0; i<GraphViewNum; i++)
	{
		ProcessMessages();
		if (m_pSelectObject[i] == 1)
		{
			if (m_pSelectObjectNoise[i] == 0)
			{
				uiCount++;
				if (uiCount == 1)
				{
					uiMin = m_uiADCFrameSaveToFileProcNum[i];
				}
				else
				{
					if (m_uiADCFrameSaveToFileProcNum[i] < uiMin)
					{
						uiMin = m_uiADCFrameSaveToFileProcNum[i];
					}
				}
			}
		}
	}
	return uiMin;
}
// ��������Ĵ��������ݸ���
unsigned int CADCDataSaveToFileThread::OnCalMaxNeedToSaveDataNum(void)
{
	unsigned int uiMax = 0;
	unsigned int uiNum = 0;
	unsigned int uiClearZeroNum = 0;
	for (unsigned int i=0; i<GraphViewNum; i++)
	{
		ProcessMessages();
		if (m_pSelectObject[i] == 1)
		{
			if (m_pSelectObjectNoise[i] == 0)
			{
				uiNum = m_uiADCFrameSaveToFileProcNum[i] * ADCFrameNumNeedToSave + m_uiADCFrameRemain[i];
				uiClearZeroNum = ADCDataSaveToFileBufSize - uiNum * ReceiveDataSize;
				if(uiClearZeroNum > 0)
				{
					memset(&m_dADCSaveToFileProcBuf[i][ADCDataSaveToFileBufSize - uiClearZeroNum], 0, uiClearZeroNum);
				}
				if (uiNum > uiMax)
				{
					uiMax = uiNum;
				}
			}
		}
	}
	for (int i=0; i<GraphViewNum; i++)
	{
		m_uiADCFrameSaved[i] += uiMax;
	}
	uiMax = uiMax * ReceiveDataSize;
	return uiMax;
}
// ��ADC���ݱ��浽�ļ���
void CADCDataSaveToFileThread::OnSaveADCToFile(unsigned int uiADCSaveDataNum)
{
	CString strOutput = "";
	CString strTemp = "";
	if(m_bOpenADCSaveFile == FALSE)
	{
		OnOpenADCSaveFile();
	}

	// �����������������
	for (unsigned int i=0; i<uiADCSaveDataNum; i++)
	{
		ProcessMessages();
		for (int j=0; j<GraphViewNum; j++)
		{
			ProcessMessages();
			
			strTemp.Format(_T("%2.*lf\t"),DecimalPlaces, m_dADCSaveToFileProcBuf[j][i]);
			strOutput += strTemp;
		}
		strOutput += "\r\n";
	}
	for (int i=0; i<GraphViewNum; i++)
	{
		memset(m_dADCSaveToFileProcBuf[i], 0, uiADCSaveDataNum);
	}
	fprintf(m_pFileSave,"%s", strOutput); 

	m_uiADCDataToSaveNum += uiADCSaveDataNum;
	if (m_uiADCDataToSaveNum == m_uiADCFileLength)
	{
		m_uiADCDataToSaveNum = 0;
		OnCloseADCSaveFile();
	}
}
// ��ADC���ݱ��浽�ļ���
void CADCDataSaveToFileThread::OnSaveADCToFile(unsigned int uiADCSaveDataNum, unsigned int uiADCSaveDataPointNb)
{
	CString strOutput = "";
	CString strTemp = "";

	if(m_bOpenADCSaveFile == FALSE)
	{
		OnOpenADCSaveFile();
	}

	// �����������������
	for (unsigned int i=0; i<uiADCSaveDataNum; i++)
	{
		ProcessMessages();
		for (int j=0; j<GraphViewNum; j++)
		{
			ProcessMessages();

			strTemp.Format(_T("%2.*lf\t"),DecimalPlaces, m_dADCSaveToFileProcBuf[j][i + uiADCSaveDataPointNb]);
			strOutput += strTemp;
		}
		strOutput += "\r\n";
	}
	for (int i=0; i<GraphViewNum; i++)
	{
		memset(m_dADCSaveToFileProcBuf[i], 0, uiADCSaveDataNum);
	}
	fprintf(m_pFileSave,"%s", strOutput); 

	m_uiADCDataToSaveNum += uiADCSaveDataNum;
	if (m_uiADCDataToSaveNum == m_uiADCFileLength)
	{
		m_uiADCDataToSaveNum = 0;
		OnCloseADCSaveFile();
	}
}
// �������������
void CADCDataSaveToFileThread::OnClearProcData(unsigned int uiOutDataedProcNum)
{
	unsigned int uiSaveDataNum = 0;
	uiSaveDataNum = uiOutDataedProcNum*ADCFrameNumNeedToSave*ReceiveDataSize;
	for (int i=0; i<GraphViewNum; i++)
	{
		ProcessMessages();
		if (m_uiADCFrameSaveToFileProcNum[i] > 0)
		{
			m_uiADCFrameSaveToFileProcNum[i] -= uiOutDataedProcNum; 
			if (m_uiADCFrameSaveToFileProcNum[i] > 0)
			{
				unsigned int uiPos = 0;
				uiPos = m_uiADCFrameSaveToFileProcNum[i]*ADCFrameNumNeedToSave*ReceiveDataSize;
				for (unsigned int j=0; j< uiPos;j++)
				{
					ProcessMessages();
					m_dADCSaveToFileProcBuf[i][j] = m_dADCSaveToFileProcBuf[i][j+uiSaveDataNum];
				}
				memset(&m_dADCSaveToFileProcBuf[i][uiSaveDataNum], 0, uiPos);	
			}
		}
	}
}

// ��������ADC���������ļ�
void CADCDataSaveToFileThread::OnOpenADCSaveFile(void)
{
	m_uiADCSaveFileNum++;

	CString strFileName = "";
	CString strOutput = "";
	CString strTemp = "";
	strFileName.Format("%s\\%d.text", m_csSaveFilePath,m_uiADCSaveFileNum);
	// ��ADC�������ݱ����ANSI��ʽ���ļ�
	errno_t err;
	if((err = fopen_s(&m_pFileSave,strFileName,"w+"))!=NULL)
	{
		AfxMessageBox(_T("ADC���ݴ洢�ļ�����ʧ�ܣ�"));	
		return;
	}

	CString str = "";
	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);

	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%04d ��ʼ��¼ADC�������ݣ�\r\n\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	strOutput += str;

	// ���������ǩ
	for (int i=0; i<GraphViewNum; i++)
	{
		ProcessMessages();
		strTemp.Format("%s\t\t",m_cSelectObjectName[i]);
		strOutput += strTemp;
	}
	strOutput += "\r\n";

	fprintf(m_pFileSave,"%s", strOutput); 
	m_bOpenADCSaveFile = TRUE;
}
// �ر�ADC���������ļ�
void CADCDataSaveToFileThread::OnCloseADCSaveFile(void)
{
	if (m_pFileSave == NULL)
	{
		return;
	}
	fclose(m_pFileSave); 
	m_bOpenADCSaveFile = FALSE;
}