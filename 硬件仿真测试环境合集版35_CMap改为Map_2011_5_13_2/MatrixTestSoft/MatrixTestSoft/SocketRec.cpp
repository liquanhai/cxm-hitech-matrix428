// SocketRec.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "SocketRec.h"


// CSocketRec

CSocketRec::CSocketRec()
: m_usudp_count(0)
, m_iRecPort(0)
, m_iSendPort(0)
, m_csIP(_T(""))
, m_pwnd(NULL)
, m_pWndTab(NULL)
, m_pSaveFile(NULL)
, m_uiHeartBeatNum(0)
, m_uiIPSetNum(0)
, m_uiTailTimeNum(0)
, m_uiDelayTimeSetNum(0)
, m_uiADCSetNum(0)
, m_uiSendFrameNum(0)
{
}

CSocketRec::~CSocketRec()
{
}


// CSocketRec 成员函数

void CSocketRec::OnReceive(int nErrorCode)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	int ret=0;
	unsigned short uiPort = 0;
	ret = Receive(m_ucudp_buf[m_usudp_count],SndFrameSize);

	if(ret == SndFrameSize) 
	{
		CString strTemp = _T("");
		unsigned int uiCommand = 0;
		// 通过端口识别功能
		memcpy(&uiPort, &m_ucudp_buf[m_usudp_count][24], 2);
		if (uiPort == HeartBeatRec)
		{
			m_uiHeartBeatNum ++;
			strTemp.Format(_T("%d"),m_uiHeartBeatNum);
			m_pwnd->GetDlgItem(IDC_STATIC_HEARTBEATFRAMENUM)->SetWindowText(strTemp);
		}
		else if (uiPort == IPSetPort)
		{
			m_uiIPSetNum ++;
			strTemp.Format(_T("%d"),m_uiIPSetNum);
			m_pwnd->GetDlgItem(IDC_STATIC_IPSETNUM)->SetWindowText(strTemp);
		}
		else if (uiPort == TailTimeFramePort)
		{
			m_uiTailTimeNum ++;
			strTemp.Format(_T("%d"),m_uiTailTimeNum);
			m_pwnd->GetDlgItem(IDC_STATIC_TAILTIMESETNUM)->SetWindowText(strTemp);
		}
		else if (uiPort == TimeSetPort)
		{
			m_uiDelayTimeSetNum ++;
			strTemp.Format(_T("%d"),m_uiDelayTimeSetNum);
			m_pwnd->GetDlgItem(IDC_STATIC_DELAYTIMESETNUM)->SetWindowText(strTemp);
		}
		else if (uiPort == ADSetReturnPort)
		{
			m_uiADCSetNum ++;
			strTemp.Format(_T("%d"),m_uiADCSetNum);
			m_pwnd->GetDlgItem(IDC_STATIC_ADCSETNUM)->SetWindowText(strTemp);
		}

		m_uiSendFrameNum ++;
		strTemp.Format(_T("%d"),m_uiSendFrameNum);
		m_pWndTab->GetDlgItem(IDC_STATIC_SENDFRAMENUM)->SetWindowText(strTemp);

		SendTo(m_ucudp_buf[m_usudp_count],SndFrameSize,m_iSendPort,m_csIP);
		m_pSaveFile->OnSaveReceiveData(m_ucudp_buf[m_usudp_count],SndFrameSize);

		m_usudp_count +=1;
		m_usudp_count = m_usudp_count%8;
	}

	CSocket::OnReceive(nErrorCode);
}
// 重置界面
void CSocketRec::OnReset(void)
{
	CString strTemp;
	m_uiHeartBeatNum = 0;
	strTemp.Format(_T("%d"),m_uiHeartBeatNum);
	m_pwnd->GetDlgItem(IDC_STATIC_HEARTBEATFRAMENUM)->SetWindowText(strTemp);

	m_uiIPSetNum = 0;
	strTemp.Format(_T("%d"),m_uiIPSetNum);
	m_pwnd->GetDlgItem(IDC_STATIC_IPSETNUM)->SetWindowText(strTemp);

	m_uiTailTimeNum = 0;
	strTemp.Format(_T("%d"),m_uiTailTimeNum);
	m_pwnd->GetDlgItem(IDC_STATIC_TAILTIMESETNUM)->SetWindowText(strTemp);

	m_uiDelayTimeSetNum = 0;
	strTemp.Format(_T("%d"),m_uiDelayTimeSetNum);
	m_pwnd->GetDlgItem(IDC_STATIC_DELAYTIMESETNUM)->SetWindowText(strTemp);

	m_uiADCSetNum = 0;
	strTemp.Format(_T("%d"),m_uiADCSetNum);
	m_pwnd->GetDlgItem(IDC_STATIC_ADCSETNUM)->SetWindowText(strTemp);

	m_uiSendFrameNum = 0;
	strTemp.Format(_T("%d"),m_uiSendFrameNum);
	m_pWndTab->GetDlgItem(IDC_STATIC_SENDFRAMENUM)->SetWindowText(strTemp);
}
