// ADCDataRecThread.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "ADCDataRecThread.h"


// CADCDataRecThread

IMPLEMENT_DYNCREATE(CADCDataRecThread, CWinThread)

CADCDataRecThread::CADCDataRecThread()
: m_bclose(false)
, m_bStartSample(FALSE)
, m_uiIPSource(0)
, m_uiTestADCLost(0)
, m_uiADCRetransmissionNb(0)
, m_usudp_count(0)
, m_uiUdpCount(0)
, m_pADCDataSaveToFile(NULL)
, m_pADCFrameInfo(NULL)
, m_pLogFile(NULL)
, m_pSelectObject(NULL)
, m_pSelectObjectNoise(NULL)
, m_ADCDataSocket(INVALID_SOCKET)
, m_uispsSelect(0)
{
	for (int i=0; i<InstrumentNum; i++)
	{
		m_pOScopeCtrl[i] = NULL;
	}
}

CADCDataRecThread::~CADCDataRecThread()
{
}

BOOL CADCDataRecThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int CADCDataRecThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CADCDataRecThread, CWinThread)
END_MESSAGE_MAP()


// CADCDataRecThread 消息处理程序

int CADCDataRecThread::Run()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	DWORD dwFrameCount = 0;
	int icount = 0;
	sockaddr_in SenderAddr;
	int n = sizeof(SenderAddr);
	int iError = 0;
	CString str = _T("");
	// 循环，直到关闭标志为真
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
//		ProcessMessages();
		// 得到网络接收缓冲区数据字节数
		while(SOCKET_ERROR != ioctlsocket(m_ADCDataSocket, FIONREAD, &dwFrameCount))
		{
			if(dwFrameCount > 0) 
			{
				icount = recvfrom(m_ADCDataSocket, (char*)&m_ucUdpBuf, sizeof(m_ucUdpBuf), 0, (sockaddr*)&SenderAddr, &n);
// 				str.Format(_T("从ADC数据接收缓冲区读取数据大小为%d！"), icount);
// 				m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::Run"), str, SuccessStatus);
				if (icount != SOCKET_ERROR)
				{
					OnProcess(icount);
				}
				else if(icount == ADCDataBufSize)
				{
					str.Format(_T("ADC数据接收帧超过缓冲区大小，缓冲区大小为%d！"), ADCDataBufSize);
					m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::Run"), str, ErrorStatus);
				}
				else
				{
					iError = WSAGetLastError();
					str.Format(_T("ADC数据接收帧错误，错误号为%d！"), iError);
					m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::Run"), str, ErrorStatus);
				}
			}
			else
			{
				break;
			}
		}
//		OnADCDataRetransmission();
// 		str.Format(_T("sleep！"));
// 		m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::Run"), str, SuccessStatus);
		if (m_bclose == true)
		{
			break;
		}
		Sleep(ADCDataRecThreadSleepTime);
	}
	::SetEvent(m_hADCDataThreadClose);	// 设置事件对象为有信号状态

	return CWinThread::Run();
}
// 数据处理
//************************************
// Method:    OnProcess
// FullName:  CADCDataRecThread::OnProcess
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iCount
//************************************
void CADCDataRecThread::OnProcess(int iCount)
{
	unsigned short usCRC16 = 0;
	for (int i=0; i<iCount; i++)
	{
//		ProcessMessages();
		switch(m_uiUdpCount)
		{
		case 0:
			if (m_ucUdpBuf[i] == FrameHeadCheck0)
			{
				m_ucudp_buf[m_usudp_count][0] = m_ucUdpBuf[i];
				m_uiUdpCount++;
				break;
			}
			else
			{
				//	m_uiUdpCount = 0;
				m_uiUdpCount++;
				break;
			}

		case 1:
			if (m_ucUdpBuf[i] == FrameHeadCheck1)
			{
				m_ucudp_buf[m_usudp_count][1] = m_ucUdpBuf[i];
				m_uiUdpCount++;
				break;
			}
			else
			{
				//	m_uiUdpCount = 0;
				m_uiUdpCount++;
				break;
			}
		case 2:
			if (m_ucUdpBuf[i] == FrameHeadCheck2)
			{
				m_ucudp_buf[m_usudp_count][2] = m_ucUdpBuf[i];
				m_uiUdpCount++;
				break;
			}
			else
			{
				//	m_uiUdpCount = 0;
				m_uiUdpCount++;
				break;
			}
		case 3:
			if (m_ucUdpBuf[i] == FrameHeadCheck3)
			{
				m_ucudp_buf[m_usudp_count][3] = m_ucUdpBuf[i];
				m_uiUdpCount++;
				break;
			}
			else
			{
				//	m_uiUdpCount = 0;
				m_uiUdpCount++;
				break;
			}
		default:
			if (m_uiUdpCount >=  RcvFrameSize)
			{
				m_uiUdpCount = 0;
				m_usudp_count += 1;
				m_usudp_count = m_usudp_count % RcvBufNum;
				break;
			}
			m_ucudp_buf[m_usudp_count][m_uiUdpCount] = m_ucUdpBuf[i];
			m_uiUdpCount++;
			if (m_uiUdpCount == RcvFrameSize)
			{
				m_uiUdpCount = 0;
				if (m_bStartSample == TRUE)
				{
					memcpy(&usCRC16, &m_ucudp_buf[m_usudp_count][RcvFrameSize - CRCSize], CRCSize);
					if (usCRC16 != get_crc_16(&m_ucudp_buf[m_usudp_count][FrameHeadSize], RcvFrameSize - FrameHeadSize - CRCCheckSize))
					{
						//	continue;
					}
					ReceiveSampleData(&m_ucudp_buf[m_usudp_count][0]);
					/*OnADCDataRetransmission();*/
				}
				m_usudp_count += 1;
				m_usudp_count = m_usudp_count % RcvBufNum;
			}
			break;
		}
	}
}
// 初始化
void CADCDataRecThread::OnInit(void)
{
	m_hADCDataThreadClose = ::CreateEvent(false, false, NULL, NULL);	// 创建事件对象
	if ((m_hADCDataThreadClose == NULL)||(GetLastError() == ERROR_ALREADY_EXISTS))
	{
		AfxMessageBox(_T("创建端口监视发送线程关闭事件出错！"));
	}
	else
	{
		::ResetEvent(m_hADCDataThreadClose);	// 设置事件对象为无信号状态
	}

	for (int i=0; i<InstrumentNum; i++)
	{
//		ProcessMessages();
		memset(&m_dSampleTemp[i], SndFrameBufInit, ADCDataTempDataSize*(sizeof(double)));
		m_uiSampleTempNum[i] = 0;
		memset(&m_dADCSave[i], SndFrameBufInit, ADCDataTempDataSize*(sizeof(double)));
		m_uiADCSaveNum[i] = 0;
	}
	memset(&m_dTemp, SndFrameBufInit, ADCDataTempDataSize*(sizeof(double)));
}

// 关闭并结束线程
void CADCDataRecThread::OnClose(void)
{
	OnCloseUDP();
	for (int i=0; i<InstrumentNum; i++)
	{
		m_oADCLostMap[i].clear();
	}
	m_bclose = true;
}
// 接收采样数据
void CADCDataRecThread::ReceiveSampleData(byte* pSampleData)
{
	// uiTestNb表明接收到帧所对应的仪器号
	unsigned int	uiIPAim = 0;
	unsigned short	usDataPointNow = 0; // 接收到帧的数据的序号
	int	iSampleData = 0;
	int iPos = FrameHeadSize;
	unsigned int uiSysTime = 0;				// ADC数据帧发送时仪器的本地时间
	double dSampleDataToV = 0.0;
	unsigned int uitmp = 0;
	DWORD dwADCRetransimission = 0;				// 判断是否为重发帧的标志位
	BOOL bIPSelect = FALSE;								// 判断IP地址是否正确
	double dReceiveData [ReceiveDataSize];			// 接收数据缓存

	// 设m_pFrameData[16]到m_pFrameData[19]为源地址做为通道号
	memcpy(&uiIPAim, &pSampleData[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	for (int i=0; i<InstrumentNum; i++)
	{
//		ProcessMessages();
		if (m_pSelectObject[i] == 1)
		{
			uitmp = IPSetAddrStart + IPSetAddrInterval * (i + 1);
			if (uiIPAim	== uitmp)
			{
				usDataPointNow = 0;
				bIPSelect = TRUE;
				iPos += FramePacketSize4B;
				iPos += FramePacketSize2B;
				iPos += FramePacketSize2B;
				// m_pFrameData[28]到m_pFrameData[29]做为AD数据起始指针
				memcpy(&usDataPointNow, &pSampleData[iPos], FramePacketSize2B);
				iPos += FramePacketSize2B;

				// 如果是72个数一帧，记录本地时间
				memcpy(&uiSysTime, &pSampleData[iPos], FramePacketSize4B);
				iPos += ADCDataSize3B;
				iPos += ADCDataSize3B;

				m_pADCFrameInfo->OnSaveFile(i, usDataPointNow, uiSysTime);
// 				// 用于测试ADC丢帧后补帧
// 				if (usDataPointNow > 0)
// 				{
// 					if (uiIPAim == 81)
// 					{	
// 						m_uiTestADCLost++;
// 						if ((m_uiTestADCLost <5)&&(m_uiTestADCLost > 2))
// 						{
// 							break;
// 						}
// 					}
// 				}
	
				// ADC实际接收数据个数加一
				m_uiADCDataFrameRecCount[i]++;
				// ADC应接收数据个数加一
				m_uiADCDataFrameCount[i]++;

				// 之后为数据区
				for (int j=0; j<ReceiveDataSize; j++)
				{
//					ProcessMessages();
					memcpy(&iSampleData, &pSampleData[iPos], ADCDataSize3B);
					iPos += ADCDataSize3B;

					// 24位数转换为电压值
					dSampleDataToV = iSampleData;
					if (dSampleDataToV < 0x7FFFFF)
					{
						dSampleDataToV = dSampleDataToV/( 0x7FFFFE ) * DrawGraphYAxisUpper;
					}
					else if (dSampleDataToV > 0x800000)
					{
						dSampleDataToV = (0xFFFFFF - dSampleDataToV)/( 0x7FFFFE ) * (DrawGraphYAxisLower);
					}
					else
					{
// 						CString str = _T("");
// 						str.Format(_T("ADC采样数值溢出，溢出值为%d"), dSampleDataToV);
// 						AfxMessageBox(str);
					}
					dReceiveData[j] = dSampleDataToV;
				}
				// 不显示ADC数据改为显示各站实收帧数
//				m_dADCDataShow[i] = dSampleDataToV;
				m_dADCDataShow[i] = m_uiADCDataFrameRecCount[i];

				if (m_uiADCDataFrameCount[i] == 1)
				{
					CString str = _T("");
					m_usDataPointPrevious[i] = usDataPointNow;
					str.Format(_T("设备序号%d，接收到ADC数据帧指针偏移量起始为%d！"), i, usDataPointNow);
					m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::ReceiveSampleData"), str, SuccessStatus);
				}
				else
				{
					dwADCRetransimission = OnCheckFrameIsRetransmission(i, uiIPAim, usDataPointNow);
				}
				if(uiIPAim == m_uiADCGraphIP[i])
				{
					m_pOScopeCtrl[i]->AppendPoint(dReceiveData, ReceiveDataSize);
				}
				// 无数据重发帧或已经全部接收到数据重发帧
				if(m_oADCLostMap[i].size() == 0)
				{
					// 如果该帧为数据重发帧，处理该帧后再处理保存帧
					if (dwADCRetransimission == 2)
					{
						OnRecOkIsRetransimissionFrame(i, uiIPAim, dReceiveData);
					}
					else if(dwADCRetransimission == 1)
					{
						OnRecOkIsNormalFrame(i, uiIPAim, dReceiveData);
					}
				}
				else
				{
					// 如果该帧为数据重发帧
					if (dwADCRetransimission == 2)
					{
						OnRecNotOkIsRetransimissionFrame(i, uiIPAim, dReceiveData);
					}
					else if(dwADCRetransimission == 1)
					{
						// 如果有重发帧，而本帧不是重发帧则先将该帧保存
						OnRecNotOkIsNormalFrame(i, dReceiveData);
					}
				}
				// 将采样数据保存成文件
				OnSaveADCToFile(false);
				break;
			}
		}
	}
	if (bIPSelect == FALSE)
	{
		CString str = _T("");
		CString strtemp = _T("");
		str.Format(_T("ADC接收帧IP地址错误，错误的IP地址为：%d\r\n"), uiIPAim);
		for (int i=0; i<RcvFrameSize; i++)
		{
			strtemp.Format(_T("%02x "), pSampleData[i]);
			str += strtemp;
		}
		m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::ReceiveSampleData"), str, ErrorStatus);
	}
}
// 生成ADC数据重发帧
void CADCDataRecThread::MakeADCDataRetransmissionFrame(unsigned short usDataPointNb, unsigned int uiIPAim)
{
	unsigned int uiIPSource =	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	CString str = _T("");
	int iPos = 0;
	memset(m_ucADCRetransmission, SndFrameBufInit, SndFrameSize);
	m_ucADCRetransmission[0] = FrameHeadCheck0;
	m_ucADCRetransmission[1] = FrameHeadCheck1;
	m_ucADCRetransmission[2] = FrameHeadCheck2;
	m_ucADCRetransmission[3] = FrameHeadCheck3;
	memset(&m_ucADCRetransmission[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	uiIPSource	=	m_uiIPSource;
	usPortAim	=	ADRecPort;
	usCommand	=	SendADCRetransmissionCmd;
	// 源IP地址
	iPos = 16;
	memcpy(&m_ucADCRetransmission[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// 目标IP地址
	memcpy(&m_ucADCRetransmission[iPos], &uiIPAim, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// 目标端口号
	memcpy(&m_ucADCRetransmission[iPos], &usPortAim, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// 命令号 1-设置命令应答；2-查询命令应答；3-AD采样数据重发
	memcpy(&m_ucADCRetransmission[iPos], &usCommand, FramePacketSize2B);
	iPos += FramePacketSize2B;

	iPos = 32;
	memcpy(&m_ucADCRetransmission[iPos], &usDataPointNb, FramePacketSize2B);
	iPos += FramePacketSize2B;
	m_ucADCRetransmission[iPos] = SndFrameBufInit;

	unsigned short usCRC16 = 0;
	usCRC16 = get_crc_16(&m_ucADCRetransmission[FrameHeadSize], SndFrameSize - FrameHeadSize - CRCCheckSize);
	memcpy(&m_ucADCRetransmission[SndFrameSize - CRCSize], &usCRC16, CRCSize);

	int icount = sendto(m_ADCDataSocket, (const char*)&m_ucADCRetransmission, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
}
// ADC数据需要重新发送帧对应的最小个数
unsigned int CADCDataRecThread::OnADCRetransimissionMinNb(unsigned int uiInstrumentNb)
{
	unsigned int uimin = 0;								// 最小值
	unsigned int uiCount = 0;							// 计数

	hash_map<unsigned int, m_structADC>::iterator  iter;
	for(iter = m_oADCLostMap[uiInstrumentNb].begin(); iter != m_oADCLostMap[uiInstrumentNb].end(); iter++)
	{
		uiCount++;
		if (uiCount == 1)
		{
			uimin = iter->second.uiDataCount;
		}
		else
		{
			if (uimin > iter->second.uiDataCount)
			{
				uimin = iter->second.uiDataCount;
			}
		}
	}
	return uimin;
}
// 将ADC数据保存到文件中
void CADCDataRecThread::OnSaveADCToFile(bool bfinish)
{
	unsigned int uiADCDataToSaveNum = 0;
	unsigned int uiMinSize = 0;
	unsigned int uiMaxSize = 0;
	unsigned int uiLostFrameCount = 0;
	CString str = _T("");
	uiMinSize = OnADCRecDataMinNum();
	uiMaxSize = OnADCRecDataMaxNum();
	if (bfinish == false)
	{
		uiADCDataToSaveNum = uiMinSize;
	}
	else
	{
		uiADCDataToSaveNum = uiMaxSize;
	}
	// 如果设备掉线则不影响其它设备ADC数据采集
	if ((uiMinSize == 0) && (uiMaxSize > ADCDataTempDataSize/2))
	{
		uiADCDataToSaveNum  = uiMaxSize;
	}

	if (uiADCDataToSaveNum == 0)
	{
		// 停止ADC数据采集
		if (bfinish == true)
		{
			m_pADCDataSaveToFile->OnCloseADCSaveFile();
			m_pADCDataSaveToFile->m_uiADCDataToSaveNum = 0;
			m_pADCDataSaveToFile->m_uiADCSaveFileNum = 0;

			uiLostFrameCount = 0;
			for (int i=0; i<InstrumentNum; i++)
			{
				unsigned int uiTemp = 0;
				uiTemp = m_uiADCDataFrameCount[i] - m_uiADCDataFrameRecCount[i];
				str.Format(_T("设备序号%d，应收帧数%d，实际接收帧数%d，丢失帧数%d"), i, 
					m_uiADCDataFrameCount[i], m_uiADCDataFrameRecCount[i], uiTemp);
				m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnSaveADCToFile"), str, SuccessStatus);
				uiLostFrameCount += uiTemp;
			}
			str.Format(_T("ADC数据采样丢失帧总数为%d"), uiLostFrameCount);
			m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnSaveADCToFile"), str, SuccessStatus);
		}
		return;
	}
	if (bfinish == false)
	{	
		if ((m_pADCDataSaveToFile->m_uiADCDataToSaveNum + uiADCDataToSaveNum) > m_pADCDataSaveToFile->m_uiADCFileLength)
		{
			uiADCDataToSaveNum = m_pADCDataSaveToFile->m_uiADCFileLength - m_pADCDataSaveToFile->m_uiADCDataToSaveNum;
		}
	}
 	m_pADCDataSaveToFile->OnSaveADCToFile(m_dADCSave, m_uiADCSaveNum, uiADCDataToSaveNum, bfinish);

	// 清除保存过的数据
	for (int j=0; j<InstrumentNum; j++)
	{
//		ProcessMessages();
		if (bfinish == false)
		{
			if (m_pSelectObject[j] == 1)
			{
				if (m_pSelectObjectNoise[j] == 0)
				{
					if (m_uiADCSaveNum[j] >= uiADCDataToSaveNum)
					{
						if (m_uiADCSaveNum[j] - uiADCDataToSaveNum > ADCDataTempDataSize)
						{
							str.Format(_T("设备序号%d的ADC数据缓冲区中数据个数%ud，要保存的数据个数为%ud，"), 
								j, m_uiADCSaveNum[j], uiADCDataToSaveNum);
							str += _T("ADC数据处理过程缓冲区大小不够1！");
							AfxMessageBox(str);
						}
						else
						{
							m_uiADCSaveNum[j] = m_uiADCSaveNum[j] - uiADCDataToSaveNum;
							memcpy(&m_dTemp, &m_dADCSave[j][uiADCDataToSaveNum], m_uiADCSaveNum[j]*(sizeof(double)));
							memcpy(&m_dADCSave[j], &m_dTemp, m_uiADCSaveNum[j]*(sizeof(double)));
						}
					}
				}
			}
		} 
		else
		{
			memset(&m_dADCSave[j], SndFrameBufInit, ADCDataTempDataSize*(sizeof(double)));
			m_uiADCSaveNum[j] = 0;
		}
	}
	if (bfinish == true)
	{
		uiLostFrameCount = 0;
		for (int i=0; i<InstrumentNum; i++)
		{
			unsigned int uiTemp = 0;
			uiTemp = m_uiADCDataFrameCount[i] - m_uiADCDataFrameRecCount[i];
			str.Format(_T("设备序号%d，应收帧数%d，实际接收帧数%d，丢失帧数%d"), i, 
				m_uiADCDataFrameCount[i], m_uiADCDataFrameRecCount[i], uiTemp);
			m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnSaveADCToFile"), str, SuccessStatus);
			uiLostFrameCount += uiTemp;
		}
		str.Format(_T("ADC数据采样丢失帧总数为%d"), uiLostFrameCount);
		m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnSaveADCToFile"), str, SuccessStatus);
	}
}
// 被选择仪器的ADC数据个数的最小值
unsigned int CADCDataRecThread::OnADCRecDataMinNum(void)
{
	unsigned int uiMinSize = 10000;
	bool bSelect = false;
	for (int i=0; i<InstrumentNum; i++)
	{
		//		ProcessMessages();
		if (m_pSelectObject[i] == 1)
		{
			if (m_pSelectObjectNoise[i] == 0)
			{
				if (uiMinSize > m_uiADCSaveNum[i])
				{
					uiMinSize = m_uiADCSaveNum[i];
					bSelect = true;
				}
			}
		}
	}
	if (bSelect == false)
	{
		uiMinSize = 0;
	}
	return uiMinSize;
}
// 被选择仪器的ADC数据个数的最大值
unsigned int CADCDataRecThread::OnADCRecDataMaxNum(void)
{
	unsigned int uiMaxSize = 0;
	for (int i=0; i<InstrumentNum; i++)
	{
		//		ProcessMessages();
		if (m_pSelectObject[i] == 1)
		{
			if (m_pSelectObjectNoise[i] == 0)
			{
				if (uiMaxSize < m_uiADCSaveNum[i])
				{
					uiMaxSize = m_uiADCSaveNum[i];
				}
			}
		}
	}
	return uiMaxSize;
}
// ADC数据重发
void CADCDataRecThread::OnADCDataRetransmission(void)
{
	double dReceiveData[ReceiveDataSize];
	CString str = _T("");
	unsigned int uiTemp = 0;
	memset(&dReceiveData, SndFrameBufInit, ReceiveDataSize * (sizeof(double)));
	hash_map<unsigned int, m_structADC>::iterator  iter;
	for (int i=0; i<InstrumentNum; i++)
	{
		//		ProcessMessages();
		if (m_oADCLostMap[i].size() == 0)
		{
			continue;
		}
		for(iter = m_oADCLostMap[i].begin(); iter != m_oADCLostMap[i].end();)
		{
			if (m_oADCLostMap[i].size() == 0)
			{
				break;
			}
			iter->second.uiRetransmissionNum++;
			// 根据采样率确定超过硬件保存ADC采样数据的时间的一半则对丢失帧补零处理
			uiTemp = (HardwareSaveADCNum * 1000) / (m_uispsSelect * 250 * ADCDataRecThreadSleepTime * 2);
			if (iter->second.uiRetransmissionNum == uiTemp)
			{
				m_uiADCRetransmissionNb = iter->second.uiDataCount;
				str.Format(_T("设备序号%d，ADC数据帧用0补齐丢帧，补齐帧的偏移量为%d！"), i, iter->first);
				m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnADCDataRetransmission"), str, WarningStatus);

				m_oADCLostMap[i].erase(iter++);
				// 已经全部接收到数据重发帧
				if(0 == m_oADCLostMap[i].size())
				{
					OnRecOkIsRetransimissionFrame(i, IPSetAddrStart + IPSetAddrInterval * (i + 1), dReceiveData);
				}
				else
				{
					OnRecNotOkIsRetransimissionFrame(i, IPSetAddrStart + IPSetAddrInterval * (i + 1), dReceiveData);
				}
				// 将采样数据保存成文件
				OnSaveADCToFile(false);
			}
			else
			{
// 				if(iter->second.uiRetransmissionNum == 1)
// 				{
// 					MakeADCDataRetransmissionFrame(iter->first, (IPSetAddrStart + (i + 1) * IPSetAddrInterval));
// 					str.Format(_T("设备序号%d，发送ADC数据帧重发指令，重发帧的偏移量为%d！"), i, iter->first);
// 					m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnADCDataRetransmission"), str, SuccessStatus);
// 				}
				iter++;
			}
		}
	}
}
// ADC数据重发
void CADCDataRecThread::OnADCDataRetransmission(unsigned int uiInstrumentNb)
{
	double dReceiveData[ReceiveDataSize];
	CString str = _T("");
	unsigned int uiTemp = 0;
	memset(&dReceiveData, SndFrameBufInit, ReceiveDataSize * (sizeof(double)));
	hash_map<unsigned int, m_structADC>::iterator  iter;

	if (m_oADCLostMap[uiInstrumentNb].size() == 0)
	{
		return;
	}
	for(iter = m_oADCLostMap[uiInstrumentNb].begin(); iter != m_oADCLostMap[uiInstrumentNb].end();)
	{
		if (m_oADCLostMap[uiInstrumentNb].size() == 0)
		{
			break;
		}
		iter->second.uiRetransmissionNum++;
		// 根据采样率确定超过硬件保存ADC采样数据个数则对丢失帧补零处理
//		uiTemp = (HardwareSaveADCNum * 1000) / (m_uispsSelect * 250 * ADCDataRecThreadSleepTime * 2);
		uiTemp = HardwareSaveADCNum / ReceiveDataSize;
		if (iter->second.uiRetransmissionNum == uiTemp)
		{
			m_uiADCRetransmissionNb = iter->second.uiDataCount;
			str.Format(_T("设备序号%d，ADC数据帧用0补齐丢帧，补齐帧的偏移量为%d！"), uiInstrumentNb, iter->first);
			m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnADCDataRetransmission"), str, WarningStatus);

			m_oADCLostMap[uiInstrumentNb].erase(iter++);
			// 已经全部接收到数据重发帧
			if(0 == m_oADCLostMap[uiInstrumentNb].size())
			{
				OnRecOkIsRetransimissionFrame(uiInstrumentNb, IPSetAddrStart + IPSetAddrInterval * (uiInstrumentNb + 1), dReceiveData);
			}
			else
			{
				OnRecNotOkIsRetransimissionFrame(uiInstrumentNb, IPSetAddrStart + IPSetAddrInterval * (uiInstrumentNb + 1), dReceiveData);
			}
			// 将采样数据保存成文件
			OnSaveADCToFile(false);
		}
		else
		{
			if(iter->second.uiRetransmissionNum == 1)
			{
				MakeADCDataRetransmissionFrame(iter->first, (IPSetAddrStart + (uiInstrumentNb + 1) * IPSetAddrInterval));
				str.Format(_T("设备序号%d，发送ADC数据帧重发指令，重发帧的偏移量为%d！"), uiInstrumentNb, iter->first);
				m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnADCDataRetransmission"), str, SuccessStatus);
			}
			iter++;
		}
	}
}
// 防止程序在循环中运行无法响应消息
void CADCDataRecThread::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}
// 检查接收帧是否为重发帧
DWORD CADCDataRecThread::OnCheckFrameIsRetransmission(unsigned int uiInstrumentNb, unsigned int uiIPAim, unsigned short usDataPointNow)
{
	CString str = _T("");
	unsigned short usLostDataFrameCount = 0;	// 丢失帧计数
	unsigned short usADCDataNb = ReceiveDataSize;	// ADC一帧的数据个数
	unsigned short usDataPointMove = 0;	// 记录指针偏移量
	unsigned short usDataPointNb = 0;
	double dLostRecData[ReceiveDataSize];
	memset(&dLostRecData, SndFrameBufInit, ReceiveDataSize*(sizeof(double)));
	// 接收到的ADC数据不是重发数据
	hash_map<unsigned int, m_structADC>::iterator iter;
	iter = m_oADCLostMap[uiInstrumentNb].find(usDataPointNow);
	if (iter == m_oADCLostMap[uiInstrumentNb].end())
	{
		// 索引中没找到
		if (usDataPointNow > m_usDataPointPrevious[uiInstrumentNb])
		{
			usDataPointMove  = usDataPointNow - m_usDataPointPrevious[uiInstrumentNb];
		}
		else
		{
			usDataPointMove  = ADCFramePointLength + usDataPointNow - m_usDataPointPrevious[uiInstrumentNb];
		}
		// 指针偏移量的差不是指针偏移量的整数倍则认为是过期数据
		if ((usDataPointMove % usADCDataNb) != 0)
		{
			str.Format(_T("设备序号%d，接收到过期重发帧的指针偏移量为%d！"), uiInstrumentNb, usDataPointNow);
			m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnCheckFrameIsRetransmission"), str, WarningStatus);
			return -1;
		}
		else
		{
			usLostDataFrameCount = usDataPointMove/usADCDataNb - 1;
		}
		
		// 有ADC采集数据丢帧则加入ADC数据重发队列
		if (usLostDataFrameCount > 0)
		{
			for (unsigned short m=0; m<usLostDataFrameCount; m++)
			{
//				ProcessMessages();
				m_structADC ADCDataStruct;
				usDataPointNb = (m_usDataPointPrevious[uiInstrumentNb] + (m + 1) * usADCDataNb) % ADCFramePointLength;
				ADCDataStruct.uiDataCount = m_uiADCDataFrameCount[uiInstrumentNb] + m;
				ADCDataStruct.uiRetransmissionNum = 0;
				m_oADCLostMap[uiInstrumentNb].insert(hash_map<unsigned int, m_structADC>::value_type (usDataPointNb, ADCDataStruct)); 
				str.Format(_T("设备序号%d，丢失帧指针偏移量为%d！"), uiInstrumentNb, usDataPointNb);
				m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnCheckFrameIsRetransmission"), str, SuccessStatus);

// 				MakeADCDataRetransmissionFrame(usDataPointNb, (IPSetAddrStart + (uiInstrumentNb + 1) * IPSetAddrInterval));
// 				str.Format(_T("设备序号%d，发送ADC数据帧重发指令，重发帧的偏移量为%d！"), uiInstrumentNb, usDataPointNb);	
// 				m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnCheckFrameIsRetransmission"), str, WarningStatus);

				if ((m_uiSampleTempNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
				{
					str.Format(_T("设备序号%d，丢失帧数%d，保存不连续的数据个数为%d，"),
						uiInstrumentNb, usLostDataFrameCount, m_uiSampleTempNum[uiInstrumentNb]);
					str += _T("ADC数据处理过程缓冲区大小不够2！");
					AfxMessageBox(str);
				}
				else
				{
					memset(&m_dSampleTemp[uiInstrumentNb][m_uiSampleTempNum[uiInstrumentNb]], SndFrameBufInit, ReceiveDataSize*(sizeof(double)));
					m_uiSampleTempNum[uiInstrumentNb] += ReceiveDataSize;
				}
				if(uiIPAim == m_uiADCGraphIP[uiInstrumentNb])
				{
					m_pOScopeCtrl[uiInstrumentNb]->AppendPoint(dLostRecData, ReceiveDataSize);
				}
				OnADCDataRetransmission(uiInstrumentNb);
			}
			m_uiADCDataFrameCount[uiInstrumentNb] += usLostDataFrameCount;
		}
		OnADCDataRetransmission(uiInstrumentNb);
		m_usDataPointPrevious[uiInstrumentNb] = usDataPointNow;
		return 1;
	}
	else
	{
		// 如果为重发数据则ADC应接收数据个数不变 
		m_uiADCDataFrameCount[uiInstrumentNb]--;
		m_uiADCRetransmissionNb = iter->second.uiDataCount;
		str.Format(_T("设备序号%d，接收到ADC的数据重发帧，重发帧的偏移量为%d！"), uiInstrumentNb, iter->first);
		m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::OnCheckFrameIsRetransmission"), str, SuccessStatus);
		m_oADCLostMap[uiInstrumentNb].erase(iter);
		return 2;
	}
}
// 该帧为最后一个数据重发帧
void CADCDataRecThread::OnRecOkIsRetransimissionFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData)
{
	if ((m_uiADCSaveNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
	{
		CString str = _T("");
		str.Format(_T("设备序号%d，保存成文件的数据缓冲区中数据个数%d，"), uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);
		str += _T("ADC保存成文件的缓冲区大小不够3！");
		AfxMessageBox(str);
	}
	else
	{
		memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &pReceiveData[0], ReceiveDataSize*(sizeof(double)));
		m_uiADCSaveNum[uiInstrumentNb] += ReceiveDataSize;
	}
	// 接收到重发帧之前有保存帧
	if (m_uiSampleTempNum[uiInstrumentNb] > ReceiveDataSize)
	{
		// 将除重发帧之外的保存帧复制到文件存储缓冲区
		m_uiSampleTempNum[uiInstrumentNb] = m_uiSampleTempNum[uiInstrumentNb] - ReceiveDataSize;
		if (m_uiADCSaveNum[uiInstrumentNb] + m_uiSampleTempNum[uiInstrumentNb] > ADCDataTempDataSize)
		{
			CString str = _T("");
			str.Format(_T("设备序号%d，保存成文件的数据缓冲区中数据个数%d，预先保留的不连续的数据个数%d，"),
				uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb], m_uiSampleTempNum[uiInstrumentNb]);
			str += _T("ADC保存成文件的缓冲区大小不够5！");
			AfxMessageBox(str);
		}
		else
		{
			memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &m_dSampleTemp[uiInstrumentNb][ReceiveDataSize], m_uiSampleTempNum[uiInstrumentNb]*(sizeof(double)));
			m_uiADCSaveNum[uiInstrumentNb] += m_uiSampleTempNum[uiInstrumentNb];
		}
	}
	memset(&m_dSampleTemp[uiInstrumentNb], SndFrameBufInit, ADCDataTempDataSize*(sizeof(double)));
	m_uiSampleTempNum[uiInstrumentNb] = 0;
}

// 该帧为普通帧且之前没有重发帧
void CADCDataRecThread::OnRecOkIsNormalFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData)
{
	if ((m_uiADCSaveNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
	{
		CString str = _T("");
		str.Format(_T("设备序号%d，保存成文件的数据缓冲区中数据个数%d，"), 
			uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);
		str += _T("ADC保存成文件的缓冲区大小不够6！");
		AfxMessageBox(str);
	}
	else
	{
		memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &pReceiveData[0], ReceiveDataSize * (sizeof(double)));
		m_uiADCSaveNum[uiInstrumentNb] += ReceiveDataSize;
	}
}

// 该帧为重发帧但不是最后一个重发帧
void CADCDataRecThread::OnRecNotOkIsRetransimissionFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData)
{
	unsigned int	uiMinNb = 0;		// 重发帧中的最小位置（个数）
	uiMinNb = OnADCRetransimissionMinNb(uiInstrumentNb);
	// 该重发帧之前各帧均已经收到
	if (uiMinNb > m_uiADCRetransmissionNb)
	{
		if ((m_uiADCSaveNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
		{
			CString str = _T("");
			str.Format(_T("设备序号%d，保存成文件的数据缓冲区中数据个数%d，"), 
				uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);
			str += _T("ADC保存成文件的缓冲区大小不够7！");
			AfxMessageBox(str);
		}
		else
		{
			memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &pReceiveData[0], ReceiveDataSize*(sizeof(double)));
			m_uiADCSaveNum[uiInstrumentNb] += ReceiveDataSize;
		}

		// 将重发帧从数据缓冲区中移除
		m_uiSampleTempNum[uiInstrumentNb] = m_uiSampleTempNum[uiInstrumentNb] - ReceiveDataSize;
		memcpy(&m_dTemp, &m_dSampleTemp[uiInstrumentNb][ReceiveDataSize], m_uiSampleTempNum[uiInstrumentNb]*(sizeof(double)));
		memcpy(&m_dSampleTemp[uiInstrumentNb], &m_dTemp, m_uiSampleTempNum[uiInstrumentNb]*(sizeof(double)));

		// 如果等待重发帧的索引中最小的采样帧位置和接收到的重发帧之间有保存帧
		if (uiMinNb > (m_uiADCRetransmissionNb + 1))
		{
			if ((m_uiADCSaveNum[uiInstrumentNb] + (uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize) > ADCDataTempDataSize)
			{
				CString str = _T("");
				str.Format(_T("设备序号%d，保存成文件的数据缓冲区中数据个数%d，"), 
					uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);
				str += _T("ADC保存成文件的缓冲区大小不够9！");
				AfxMessageBox(str);
			} 
			else
			{
				memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], 
					&m_dSampleTemp[uiInstrumentNb], 
					(uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize*(sizeof(double)));
				m_uiADCSaveNum[uiInstrumentNb] += (uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize;
			}
			// 将绘制完成的保存帧移除
			m_uiSampleTempNum[uiInstrumentNb] = m_uiSampleTempNum[uiInstrumentNb] - (uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize;
			memcpy(&m_dTemp, &m_dSampleTemp[uiInstrumentNb][(uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize], m_uiSampleTempNum[uiInstrumentNb]*(sizeof(double)));
			memcpy(&m_dSampleTemp[uiInstrumentNb], &m_dTemp, m_uiSampleTempNum[uiInstrumentNb]*(sizeof(double)));
		}
	}
	// 该帧之前还有重发帧未收到
	else
	{
		memcpy(&m_dSampleTemp[uiInstrumentNb][(m_uiADCRetransmissionNb - uiMinNb) * ReceiveDataSize], &pReceiveData[0], ReceiveDataSize*(sizeof(double)));
	}
}
// 该帧为普通帧且之前有重发帧
void CADCDataRecThread::OnRecNotOkIsNormalFrame(unsigned int uiInstrumentNb, double* pReceiveData)
{
	if ((m_uiSampleTempNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
	{
		CString str = _T("");
		str.Format(_T("设备序号%d应收帧数%d，实收帧数%d，预先保留不连续的数据个数%d，"), 
			uiInstrumentNb, m_uiADCDataFrameCount[uiInstrumentNb], m_uiADCDataFrameRecCount[uiInstrumentNb], 
			m_uiSampleTempNum[uiInstrumentNb]);
		str += _T("ADC数据处理过程缓冲区大小不够11！");
		AfxMessageBox(str);
	} 
	else
	{
		memcpy(&m_dSampleTemp[uiInstrumentNb][m_uiSampleTempNum[uiInstrumentNb]], &pReceiveData[0], 
			ReceiveDataSize*(sizeof(double)));
		m_uiSampleTempNum[uiInstrumentNb] += ReceiveDataSize;
	}
}
// 重置变量的值
void CADCDataRecThread::OnReset(void)
{
	for (int i=0; i<InstrumentNum; i++)
	{
//		ProcessMessages();
		memset(&m_dSampleTemp[i], SndFrameBufInit, ADCDataTempDataSize*(sizeof(double)));
		m_uiSampleTempNum[i] = 0;
		memset(&m_dADCSave[i], SndFrameBufInit, ADCDataTempDataSize*(sizeof(double)));
		m_uiADCSaveNum[i] = 0;
		m_uiADCDataFrameCount[i] = 0;
		m_uiADCDataFrameRecCount[i] = 0;
		m_dADCDataShow[i] = 0;
		m_oADCLostMap[i].clear();
		m_uiADCGraphIP[i] = 0;
		m_usDataPointPrevious[i] = 0;
		m_pOScopeCtrl[i] = NULL;
	}
	memset(&m_dTemp, SndFrameBufInit, ADCDataTempDataSize*(sizeof(double)));
	m_bStartSample = FALSE;
}
// 关闭UDP套接字
void CADCDataRecThread::OnCloseUDP(void)
{
	shutdown(m_ADCDataSocket, SD_BOTH);
	closesocket(m_ADCDataSocket);
	m_ADCDataSocket = INVALID_SOCKET;
}
