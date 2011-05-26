// SendThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�˿ڼ�����.h"
#include "SendThread.h"
#include "Parameter.h"

// CSendThread

IMPLEMENT_DYNCREATE(CSendThread, CWinThread)

CSendThread::CSendThread()
: m_uiHeadFrameNum(0)
, m_uiIPSetReturnNum(0)
, m_uiTailFrameNum(0)
, m_uiTailTimeReturnNum(0)
, m_uiDelayTimeReturnNum(0)
, m_uiADCSetReturnNum(0)
, m_csHeadFrameShow(_T(""))
, m_csIPSetReturnShow(_T(""))
, m_csTailFrameShow(_T(""))
, m_csTailTimeReturnShow(_T(""))
, m_csDelayTimeReturnShow(_T(""))
, m_csADCDataRecShow(_T(""))
, m_uiRecFrameNum(0)
, m_uiADCDataRecNum(0)
, m_usADCLastDataPoint(0)
{
	
}

CSendThread::~CSendThread()
{

}

BOOL CSendThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CSendThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSendThread, CWinThread)
END_MESSAGE_MAP()


// ��ʼ��

void CSendThread::Init()
{
	udp_count = 0;
	m_close = false;
	m_hSendThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hSendThreadClose);	// �����¼�����Ϊ���ź�״̬
	int flag =  m_hSocket2.Create(RcvPort2,SOCK_DGRAM);
	m_hSocket2.SetSockOpt(NULL,&m_hSocket2,65536,SOL_SOCKET);
}
// �̺߳�����Run��ִ��
int CSendThread::Run()
{
	unsigned short uiPort = 0;
	DWORD dwFrameCount = 0;
	int icount = 0;
	unsigned short usADCDataPoint = 0;
	unsigned short usADCDataPointMove = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if (m_close == true)
		{
			break;
		}

		DWORD dwFrameCount = 0;

		// �õ�������ջ����������ֽ���
		m_hSocket2.IOCtl(FIONREAD, &dwFrameCount);
		dwFrameCount = dwFrameCount/256;
		if(0 != dwFrameCount)	
		{
			for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{

				icount = m_hSocket2.Receive(udp_buf[udp_count],256);
				if (icount == 256)
				{
					CString strTemp = _T("");
					unsigned int uiCommand = 0;
					// ����˿ڷַ�����
					memcpy(&uiPort, &udp_buf[udp_count][24], 2);
					if (uiPort == HeadFramePort)
					{
						memcpy(&uiCommand, &udp_buf[udp_count][28], 1);
						if (uiCommand == 0x01)
						{
							// ��ʾSN
							strTemp.Format(_T("%02x "),udp_buf[udp_count][29]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][30]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][31]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][32]);
							m_csHeadFrameShow += strTemp;
							m_csHeadFrameShow += _T("\t");
							// ��ʾ�װ�ʱ��
							strTemp.Format(_T("%02x "),udp_buf[udp_count][34]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][35]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][36]);
							m_csHeadFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][37]);
							m_csHeadFrameShow += strTemp;
							m_csHeadFrameShow += _T("\r\n");

							pDlg->GetDlgItem(IDC_EDIT_HEADFRAMESHOW)->SetWindowText(m_csHeadFrameShow);
							m_uiHeadFrameNum++;
							strTemp.Format(_T("%d"),m_uiHeadFrameNum);
							pDlg->GetDlgItem(IDC_STATIC_HEADFRAMENUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == IPSetPort)
					{
						memcpy(&uiCommand, &udp_buf[udp_count][28], 1);
						if (uiCommand == 0x01)
						{
							// ��ʾSN
							strTemp.Format(_T("%02x "),udp_buf[udp_count][29]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][30]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][31]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][32]);
							m_csIPSetReturnShow += strTemp;
							m_csIPSetReturnShow += _T("\t");
							// ��ʾIP
							strTemp.Format(_T("%02x "),udp_buf[udp_count][34]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][35]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][36]);
							m_csIPSetReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][37]);
							m_csIPSetReturnShow += strTemp;
							m_csIPSetReturnShow += _T("\r\n");
							pDlg->GetDlgItem(IDC_EDIT_IPSETRETURNSHOW)->SetWindowText(m_csIPSetReturnShow);
							m_uiIPSetReturnNum++;
							strTemp.Format(_T("%d"),m_uiIPSetReturnNum);
							pDlg->GetDlgItem(IDC_STATIC_IPSETRETURNNUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == TailFramePort)
					{
						memcpy(&uiCommand, &udp_buf[udp_count][33], 1);
						if (uiCommand == 0x01)
						{
							// ��ʾSN
							strTemp.Format(_T("%02x "),udp_buf[udp_count][34]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][35]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][36]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][37]);
							m_csTailFrameShow += strTemp;
							m_csTailFrameShow += _T("\t");

							// ��ʾIP
							strTemp.Format(_T("%02x "),udp_buf[udp_count][29]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][30]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][31]);
							m_csTailFrameShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][32]);
							m_csTailFrameShow += strTemp;
							m_csTailFrameShow += _T("\r\n");

							pDlg->GetDlgItem(IDC_EDIT_TAILFRAMESHOW)->SetWindowText(m_csTailFrameShow);
							m_uiTailFrameNum++;
							strTemp.Format(_T("%d"),m_uiTailFrameNum);
							pDlg->GetDlgItem(IDC_STATIC_TAILFRAMENUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == TailTimeFramePort)
					{
						memcpy(&uiCommand, &udp_buf[udp_count][28], 1);
						if (uiCommand == 0x01)
						{	// ��ʾSN
							strTemp.Format(_T("%02x "),udp_buf[udp_count][29]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][30]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][31]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][32]);
							m_csTailTimeReturnShow += strTemp;
							m_csTailTimeReturnShow += _T("\t");
							// ��ʾ����ʱ��
							strTemp.Format(_T("%02x "),udp_buf[udp_count][34]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][35]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][36]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][37]);
							m_csTailTimeReturnShow += strTemp;
							m_csTailTimeReturnShow += _T("\t");
							// ��ʾ����ʱ��
							strTemp.Format(_T("%02x "),udp_buf[udp_count][39]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][40]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][41]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][42]);
							m_csTailTimeReturnShow += strTemp;
							m_csTailTimeReturnShow += _T("\t");
							// ��ʾβ�����շ���ʱ�̣�ǰ14λ��Ч��
							strTemp.Format(_T("%02x "),udp_buf[udp_count][44]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][45]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][46]);
							m_csTailTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][47]);
							m_csTailTimeReturnShow += strTemp;
							m_csTailTimeReturnShow += _T("\r\n");
							pDlg->GetDlgItem(IDC_EDIT_TAILTIMERETURNSHOW)->SetWindowText(m_csTailTimeReturnShow);
							m_uiTailTimeReturnNum++;
							strTemp.Format(_T("%d"),m_uiTailTimeReturnNum);
							pDlg->GetDlgItem(IDC_STATIC_TAILTIMERETURNNUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == TimeSetPort)
					{
						memcpy(&uiCommand, &udp_buf[udp_count][28], 1);
						if (uiCommand == 0x05)
						{
							// ��ʾIP
							strTemp.Format(_T("%02x "),udp_buf[udp_count][16]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][17]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][18]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][19]);
							m_csDelayTimeReturnShow += strTemp;
							m_csDelayTimeReturnShow += _T("\t");

							// ��ʾ��ʱ������λ
							strTemp.Format(_T("%02x "),udp_buf[udp_count][29]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][30]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][31]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][32]);
							m_csDelayTimeReturnShow += strTemp;
							m_csDelayTimeReturnShow += _T("\t");

							// ��ʾ��ʱ������λ
							strTemp.Format(_T("%02x "),udp_buf[udp_count][34]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][35]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][36]);
							m_csDelayTimeReturnShow += strTemp;
							strTemp.Format(_T("%02x "),udp_buf[udp_count][37]);
							m_csDelayTimeReturnShow += strTemp;
							m_csDelayTimeReturnShow += _T("\r\n");

							pDlg->GetDlgItem(IDC_EDIT_DELAYTIMERETURNSHOW)->SetWindowText(m_csDelayTimeReturnShow);
							m_uiDelayTimeReturnNum++;
							strTemp.Format(_T("%d"),m_uiDelayTimeReturnNum);
							pDlg->GetDlgItem(IDC_STATIC_DELAYTIMERETURNNUM)->SetWindowText(strTemp);
						}
					}
					else if (uiPort == ADSetReturnPort)
					{
						// ÿ�βɼ�ֻ��һ��ADC����Ӧ��֡
						m_uiADCSetReturnNum++;
						strTemp.Format(_T("%d"),m_uiADCSetReturnNum);
						pDlg->GetDlgItem(IDC_STATIC_ADCSETRETURNNUM)->SetWindowText(strTemp);
					}
					else if (uiPort == ADRecPort)
					{
						// ��ʾIP
						strTemp.Format(_T("%02x "),udp_buf[udp_count][16]);
						m_csADCDataRecShow += strTemp;
						strTemp.Format(_T("%02x "),udp_buf[udp_count][17]);
						m_csADCDataRecShow += strTemp;
						strTemp.Format(_T("%02x "),udp_buf[udp_count][18]);
						m_csADCDataRecShow += strTemp;
						strTemp.Format(_T("%02x "),udp_buf[udp_count][19]);
						m_csADCDataRecShow += strTemp;
						m_csADCDataRecShow += _T(" ");

						// ��ʾADC���ݲ���֡����
						m_uiADCDataRecNum++;
						strTemp.Format(_T("%d"),m_uiADCDataRecNum);
						pDlg->GetDlgItem(IDC_STATIC_ADCDATARECNUM)->SetWindowText(strTemp);
						m_csADCDataRecShow += strTemp;
						m_csADCDataRecShow += _T("\t");

						memcpy(&usADCDataPoint, &udp_buf[udp_count][28], 2);
						strTemp.Format(_T("%d"),usADCDataPoint);
						m_csADCDataRecShow += strTemp;
						m_csADCDataRecShow += _T("\t");

						usADCDataPointMove = usADCDataPoint - m_usADCLastDataPoint;
						strTemp.Format(_T("%d"),usADCDataPointMove);
						m_csADCDataRecShow += strTemp;
						m_csADCDataRecShow += _T("\r\n");
						pDlg->GetDlgItem(IDC_EDIT_ADCDATARECSHOW)->SetWindowText(m_csADCDataRecShow);
						m_usADCLastDataPoint = usADCDataPoint;
					}
					else
					{
						
					}
					m_uiRecFrameNum++;
					strTemp.Format(_T("%d"),m_uiRecFrameNum);
					pDlg->GetDlgItem(IDC_STATIC_RECFRAMENUM)->SetWindowText(strTemp);

					m_hSocket2.SendTo(udp_buf[udp_count],256,uiPort,pDlg->m_strSendIP);
					//m_hSocket2.SendTo(udp_buf[udp_count],256,SendPort2,pDlg->m_strSendIP);
					pDlg->OnSaveSendData(udp_buf[udp_count],256);
					udp_count +=1;
					udp_count = udp_count%8;
				}
				else
				{
					break;
				}
			}
		}

		if (m_close == true)
		{
			break;
		}
		Sleep(50);
	}
	::SetEvent(m_hSendThreadClose);	// �����¼�����Ϊ���ź�״̬
	// ����
	return CWinThread::Run();
}
void CSendThread::OnClose()
{
	m_hSocket2.ShutDown(2);
	m_hSocket2.Close();
	m_close = true;
}
void CSendThread::OnReset()
{
	CString strTemp;

	// �װ�����
	m_uiHeadFrameNum = 0;
	strTemp.Format(_T("%d"),m_uiHeadFrameNum);
	pDlg->GetDlgItem(IDC_STATIC_HEADFRAMENUM)->SetWindowText(strTemp);

	// IP��ַ���ü���
	m_uiIPSetReturnNum = 0;
	strTemp.Format(_T("%d"),m_uiIPSetReturnNum);
	pDlg->GetDlgItem(IDC_STATIC_IPSETRETURNNUM)->SetWindowText(strTemp);

	// β������
	m_uiTailFrameNum = 0;
	strTemp.Format(_T("%d"),m_uiTailFrameNum);
	pDlg->GetDlgItem(IDC_STATIC_TAILFRAMENUM)->SetWindowText(strTemp);

	// β��ʱ�̲�ѯӦ�����
	m_uiTailTimeReturnNum = 0;
	strTemp.Format(_T("%d"),m_uiTailTimeReturnNum);
	pDlg->GetDlgItem(IDC_STATIC_TAILTIMERETURNNUM)->SetWindowText(strTemp);

	// ʱ������Ӧ�����
	m_uiDelayTimeReturnNum = 0;
	strTemp.Format(_T("%d"),m_uiDelayTimeReturnNum);
	pDlg->GetDlgItem(IDC_STATIC_DELAYTIMERETURNNUM)->SetWindowText(strTemp);

	// ADC����Ӧ�����
	m_uiADCSetReturnNum = 0;
	strTemp.Format(_T("%d"),m_uiADCSetReturnNum);
	pDlg->GetDlgItem(IDC_STATIC_ADCSETRETURNNUM)->SetWindowText(strTemp);

	// ADC���ݲɼ�֡����
	m_uiADCDataRecNum = 0;
	strTemp.Format(_T("%d"),m_uiADCDataRecNum);
	pDlg->GetDlgItem(IDC_STATIC_ADCDATARECNUM)->SetWindowText(strTemp);

	// ����֡��
	m_uiRecFrameNum = 0;
	strTemp.Format(_T("%d"),m_uiRecFrameNum);
	pDlg->GetDlgItem(IDC_STATIC_RECFRAMENUM)->SetWindowText(strTemp);

	// ADC���ݲɼ���һ֡������ָ��ƫ����
	m_usADCLastDataPoint = 0;

	// ��ʾ�װ�֡������SN���װ�ʱ��
	m_csHeadFrameShow = _T("");
	pDlg->GetDlgItem(IDC_EDIT_HEADFRAMESHOW)->SetWindowText(_T(""));

	// ��ʾIP��ַ����Ӧ��֡������SN�����õ�IP��ַ
	m_csIPSetReturnShow = _T("");
	pDlg->GetDlgItem(IDC_EDIT_IPSETRETURNSHOW)->SetWindowText(_T(""));

	// ��ʾβ��֡������SN
	m_csTailFrameShow = _T("");
	pDlg->GetDlgItem(IDC_EDIT_TAILFRAMESHOW)->SetWindowText(_T(""));

	// ��ʾβ��ʱ�̲�ѯӦ��֡������IP��ַ�Ͳ�ѯ���
	m_csTailTimeReturnShow = _T("");
	pDlg->GetDlgItem(IDC_EDIT_TAILTIMERETURNSHOW)->SetWindowText(_T(""));

	// ��ʾʱ������Ӧ��֡������IP��ַ����������
	m_csDelayTimeReturnShow = _T("");
	pDlg->GetDlgItem(IDC_EDIT_DELAYTIMERETURNSHOW)->SetWindowText(_T(""));

	// ��ʾADC��������֡������IP��ַ��֡�����Ͳ�������֡����
	m_csADCDataRecShow = _T("");
	pDlg->GetDlgItem(IDC_EDIT_ADCDATARECSHOW)->SetWindowText(_T(""));

}