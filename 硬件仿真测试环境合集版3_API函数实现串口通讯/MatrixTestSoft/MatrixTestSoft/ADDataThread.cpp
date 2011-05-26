// ADDataThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "ADDataThread.h"
#include "Parameter.h"

// ADDataThread

IMPLEMENT_DYNCREATE(CADDataThread, CWinThread)

CADDataThread::CADDataThread()
: m_bclose(false)
, m_pSelectObject(NULL)
, m_pSelectObjectNoise(NULL)
{
}

CADDataThread::~CADDataThread()
{
}

BOOL CADDataThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CADDataThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CADDataThread, CWinThread)
END_MESSAGE_MAP()


// ADDataThread ��Ϣ�������
// ��ʼ��
void CADDataThread::OnInit(void)
{
	m_hADDDataThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hADDDataThreadClose);	// �����¼�����Ϊ���ź�״̬
}
// �̺߳�����Run��ִ��
int CADDataThread::Run()
{
	DWORD dwFrameCount = 0;
	int icount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}

		// �õ�������ջ����������ֽ���
		m_ADDataSocket.IOCtl(FIONREAD, &dwFrameCount);
		dwFrameCount = dwFrameCount/256;
		if(0 != dwFrameCount)	
		{
			for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{
				icount = m_ADDataSocket.Receive(ADData,256);
				if (icount == 256)
				{
					byte* pSampleData = &(ADData[16]);
					
					ReceiveSampleData(pSampleData);
				}
				else
				{
					break;
				}
			}
		}

		if (m_bclose == true)
		{
			break;
		}
		Sleep(50);
	}
	::SetEvent(m_hADDDataThreadClose);	// �����¼�����Ϊ���ź�״̬
	// ����
	return CWinThread::Run();
}
// �رղ������߳�
void CADDataThread::OnClose(void)
{
	m_ADDataSocket.ShutDown(2);
	m_ADDataSocket.Close();
	m_bclose = true;
}

// ��
void CADDataThread::OnOpen(void)
{
	m_ADDataSocket.Close();
	BOOL flag = FALSE; 
	flag =  m_ADDataSocket.Create(ADRecPort,SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("���ն˿ڴ���ʧ�ܣ�"));
	}
}

// ֹͣ
void CADDataThread::OnStop(void)
{
	m_ADDataSocket.ShutDown(2);
	m_ADDataSocket.Close();
}
// ���ղ�������
void CADDataThread::ReceiveSampleData(byte* pSampleData)
{
		// uiTestNb�������յ�֡����Ӧ��������
	unsigned int	uiTestNb = 0;
	unsigned short	uisDataNb = 0; // ���յ�֡�����ݵ����
	int	iSampleData = 0;
	int pos = 0;
	double dSampleDataToV = 0.0;
	// ��m_pFrameData[16]��m_pFrameData[19]ΪԴ��ַ��Ϊͨ����
	memcpy(&uiTestNb, &pSampleData[pos], 4);
	pos += 4;
	// ��ͨ��1,2,3,4�ֱ��Ӧ�ĸ�����IP��ַ
	if (uiTestNb == 111)
	{
		uiTestNb = 1;
	}
	else if (uiTestNb == 101)
	{
		uiTestNb = 2;
	}
	else if (uiTestNb == 91)
	{
		uiTestNb = 4;
	}
	else if (uiTestNb == 81)
	{
		uiTestNb = 8;
	}
	// append the new value to the plot
	for (UINT32 i=0; i<GraphViewNum; i++)
	{
		if (uiTestNb == (UINT32)(1 << i))
		{
			// �������ݻ���
			double m_dpReceiveData [ReceiveDataSize]; 
			pos += 8;
			// m_pFrameData[28]��m_pFrameData[29]��Ϊ������������ţ���ʱ����
			memcpy(&uisDataNb, &pSampleData[pos], 2);
			pos += 2;

			// ֮��Ϊ������
			for (int j=0; j<ReceiveDataSize; j++)
			{
				memcpy(&iSampleData, &pSampleData[pos], 3);
				pos += 3;

				// 24λ��ת��Ϊ��ѹֵ
				dSampleDataToV = iSampleData;
				if (dSampleDataToV < 0x7FFFFF)
				{
					dSampleDataToV = dSampleDataToV/( 0x7FFFFE )*2.5;
				}
				else if (dSampleDataToV > 0x800000)
				{
					dSampleDataToV = -(0xFFFFFF - dSampleDataToV)/( 0x7FFFFE )*2.5;
				}
				else
				{
					CString str;
					str.Format("ADC������ֵ��������ֵΪ%d", dSampleDataToV);
					AfxMessageBox(str);
				}
				m_dpReceiveData[j] = dSampleDataToV;

				if (m_pSelectObject[i] == 1)
				{
					if (m_pSelectObjectNoise[i] == 0)
					{
 						m_Sec.Lock();
						m_pSampleData[i]->push_back(dSampleDataToV);
 						m_Sec.Unlock();
					}
				}
			}
			m_Sec.Lock();
 			m_pOScopeCtrl[i]->AppendPoint(m_dpReceiveData, ReceiveDataSize);
 			m_Sec.Unlock();
		}
	}
}
