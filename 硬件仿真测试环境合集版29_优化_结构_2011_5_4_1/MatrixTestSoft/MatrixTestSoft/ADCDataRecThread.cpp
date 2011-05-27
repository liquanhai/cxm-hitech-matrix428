// ADCDataRecThread.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "ADCDataRecThread.h"


// CADCDataRecThread

IMPLEMENT_DYNCREATE(CADCDataRecThread, CWinThread)

CADCDataRecThread::CADCDataRecThread()
: m_bclose(false)
, m_pSelectObject(NULL)
, m_pSelectObjectNoise(NULL)
, m_bStartSample(FALSE)
, m_csIPSource(_T(""))
, m_uiSendPort(0)
, m_uiTestADCLost(0)
, m_csSaveFilePath(_T(""))
, m_uiADCFileLength(0)
, m_uiADCRetransmissionNb(0)
, m_usudp_count(0)
, m_uiUdpCount(0)
, m_pADCDataSocket(NULL)
{
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
	// 循环，直到关闭标志为真
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
		ProcessMessages();
		// 得到网络接收缓冲区数据字节数
		while (m_pADCDataSocket->IOCtl(FIONREAD, &dwFrameCount))
		{
			if(dwFrameCount > 0) 
			{
				icount = m_pADCDataSocket->Receive(m_ucUdpBuf, ADCDataBufSize);
				OnProcess(icount);
			}
			else
			{
				break;
			}
		}
//		OnADCDataRetransmission();
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
		ProcessMessages();
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
					ReceiveSampleData(&m_ucudp_buf[m_usudp_count][FrameHeadSize]);
					//	OnADCDataRetransmission();
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
		ProcessMessages();
		memset(&m_dSampleTemp[i], SndFrameBufInit, ADCDataTempDataSize);
		m_uiSampleTempNum[i] = 0;
		memset(&m_dADCSave[i], SndFrameBufInit, ADCDataTempDataSize);
		m_uiADCSaveNum[i] = 0;
	}
	memset(&m_dTemp, SndFrameBufInit, ADCDataTempDataSize);
	m_uiTempNum = 0;
}

// 关闭并结束线程
void CADCDataRecThread::OnClose(void)
{
	m_bclose = true;
}
// 接收采样数据
void CADCDataRecThread::ReceiveSampleData(byte* pSampleData)
{
	// uiTestNb表明接收到帧所对应的仪器号
	unsigned int	uiIPAim = 0;
	unsigned short	usDataPointNow = 0; // 接收到帧的数据的序号
	int	iSampleData = 0;
	int iPos = 0;
	double dSampleDataToV = 0.0;
	unsigned int uitmp = 0;
	BOOL bADCRetransimission = FALSE;			// 判断是否为重发帧的标志位

	// 设m_pFrameData[16]到m_pFrameData[19]为源地址做为通道号
	memcpy(&uiIPAim, &pSampleData[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;

	for (int i=0; i<InstrumentNum; i++)
	{
		ProcessMessages();
		if (m_pSelectObject[i] == 1)
		{
			uitmp = IPSetAddrStart + IPSetAddrInterval * (i + 1);
			if (uiIPAim	== uitmp)
			{
				// 接收数据缓存
				double dReceiveData [ReceiveDataSize]; 
				usDataPointNow = 0;
				iPos += FramePacketSize4B;
				iPos += FramePacketSize2B;
				iPos += FramePacketSize2B;
				// m_pFrameData[28]到m_pFrameData[29]做为AD数据起始指针
				memcpy(&usDataPointNow, &pSampleData[iPos], FramePacketSize2B);
				iPos += FramePacketSize2B;
// 				// 用于测试ADC丢帧后补帧
// 				if (usDataPointNow == 24)
// 				{
// 					if (uiIPAim == 81)
// 					{	
// 						m_uiTestADCLost++;
// 						if (m_uiTestADCLost == 1)
// 						{
// 							break;
// 						}
// 					}
// 				}
				// ADC实际接收数据个数加一
				m_uiADCDataFrameRecCount[i]++;
				// ADC应接收数据个数加一
				m_uiADCDataFrameCount[i]++;

				if (m_uiADCDataFrameCount[i] == 1)
				{
					m_usDataPointPrevious[i] = usDataPointNow;
					TRACE2(_T("设备序号%d, 指针偏移量起始为%d\r\n"), i, usDataPointNow);
				}
				else
				{
					bADCRetransimission = OnCheckFrameIsRetransmission(i, uiIPAim, usDataPointNow);
				}

				// 之后为数据区
				for (int j=0; j<ReceiveDataSize; j++)
				{
					ProcessMessages();
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
				m_dADCDataShow[i] = dSampleDataToV;
				// 无数据重发帧或已经全部接收到数据重发帧
				if(m_oADCLostMap[i].GetCount() == 0)
				{
					// 如果该帧为数据重发帧，处理该帧后再处理保存帧
					if (bADCRetransimission == TRUE)
					{
						OnRecOkIsRetransimissionFrame(i, uiIPAim, dReceiveData);
					}
					else
					{
						OnRecOkIsNormalFrame(i, uiIPAim, dReceiveData);
						TRACE(_T("接收到ADC数据帧的仪器序号为%d\r\n"), i);
					}
				}
				else
				{
					// 如果该帧为数据重发帧
					if (bADCRetransimission == TRUE)
					{
						OnRecNotOkIsRetransimissionFrame(i, uiIPAim, dReceiveData);
					}
					else
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
}
// 生成ADC数据重发帧
void CADCDataRecThread::MakeADCDataRetransmissionFrame(unsigned short usDataPointNb, unsigned int uiIPAim)
{
	unsigned int uiIPSource =	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	int iPos = 0;
	memset(m_ucADCRetransmission, SndFrameBufInit, SndFrameSize);
	m_ucADCRetransmission[0] = FrameHeadCheck0;
	m_ucADCRetransmission[1] = FrameHeadCheck1;
	m_ucADCRetransmission[2] = FrameHeadCheck2;
	m_ucADCRetransmission[3] = FrameHeadCheck3;
	memset(&m_ucADCRetransmission[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	uiIPSource	=	inet_addr(m_csIPSource);
	usPortAim	=	ADRecPort;
	usCommand	=	SendADCRetransmissionCmd;
	// 源IP地址
	iPos = 16;
	memcpy(&m_ucADCRetransmission[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// 目标IP地址
	memcpy(&m_ucADCRetransmission[iPos], &uiIPAim, FramePacketSize4B);
	iPos += FramePacketSize4B;
	TRACE2("ADC数据重发帧-仪器IP地址：%d\t 指针偏移量为%d\r\n", uiIPAim, usDataPointNb);
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
	int icount = m_pADCDataSocket->SendTo(m_ucADCRetransmission, SndFrameSize, m_uiSendPort, IPBroadcastAddr);
}
// ADC数据需要重新发送帧对应的最小个数
unsigned int CADCDataRecThread::OnADCRetransimissionMinNb(unsigned int uiInstrumentNb)
{
	unsigned int uimin = 0;								// 最小值
	POSITION pos = m_oADCLostMap[uiInstrumentNb].GetStartPosition();	// 得到索引表起始位置
	unsigned int uiKey = 0;									// 索引键
	unsigned int uiCount = 0;							// 计数

	while(NULL != pos)
	{
		ProcessMessages();
		m_structADC ADCStructTemp;	
		m_oADCLostMap[uiInstrumentNb].GetNextAssoc(pos, uiKey, ADCStructTemp);	// 得到仪器对象
		uiCount++;
		if (uiCount == 1)
		{
			uimin = ADCStructTemp.uiDataCount;
		}
		else
		{
			if (uimin > ADCStructTemp.uiDataCount)
			{
				uimin = ADCStructTemp.uiDataCount;
			}
		}
	}
	return uimin;
}
// 将ADC数据保存到文件中
void CADCDataRecThread::OnSaveADCToFile(bool bfinish)
{
	unsigned int uiADCDataToSaveNum = 0;
	uiADCDataToSaveNum = m_oADCDataSaveToFile.OnSaveADCToFile(m_dADCSave, m_uiADCSaveNum, 
		m_csSaveFilePath, m_uiADCFileLength, m_pSelectObject, m_pSelectObjectNoise, m_cSelectObjectName, 
		bfinish);

	// 清除保存过的数据
	for (int j=0; j<InstrumentNum; j++)
	{
		ProcessMessages();
		if (bfinish == false)
		{
			if (m_pSelectObject[j] == 1)
			{
				if (m_pSelectObjectNoise[j] == 0)
				{
					if (m_uiADCSaveNum[j] - uiADCDataToSaveNum > ADCDataTempDataSize)
					{
						AfxMessageBox(_T("ADC数据处理过程缓冲区大小不够1！"));
					}
					else
					{
						m_uiADCSaveNum[j] = m_uiADCSaveNum[j] - uiADCDataToSaveNum;
						memcpy(&m_dTemp, &m_dADCSave[j][uiADCDataToSaveNum], m_uiADCSaveNum[j]);
						memcpy(&m_dADCSave[j], &m_dTemp, m_uiADCSaveNum[j]);
					}
				}
			}
		} 
		else
		{
			m_uiADCSaveNum[j] = 0;
		}
	}

}
// ADC数据重发
void CADCDataRecThread::OnADCDataRetransmission(void)
{
	int icount = 0;
	for (int i=0; i<InstrumentNum; i++)
	{
		ProcessMessages();
		POSITION pos = m_oADCLostMap[i].GetStartPosition();	// 得到索引表起始位置
		unsigned int uiKey = 0;									// 索引键	
		while(NULL != pos)
		{
			ProcessMessages();
			m_structADC ADCStructTemp;	
			m_oADCLostMap[i].GetNextAssoc(pos, uiKey, ADCStructTemp);	// 得到仪器对象
			if (NULL != ADCStructTemp.uiDataCount)
			{			
				if (ADCStructTemp.uiRetransmissionNum == 0)
				{
					ADCStructTemp.uiRetransmissionNum++;
					m_oADCLostMap[i].SetAt(uiKey, ADCStructTemp);
	//				MakeADCDataRetransmissionFrame(uiKey, (IPSetAddrStart + (i + 1) * IPSetAddrInterval));
				}
				if (ADCStructTemp.uiRetransmissionNum == ADCFrameRetransmissionNum)
				{
					double dReceiveData[ReceiveDataSize];
					m_uiADCRetransmissionNb = uiKey;
					m_oADCLostMap[i].RemoveKey(uiKey);

					for (int k=0; k<ReceiveDataSize; k++)
					{
						dReceiveData[k] = 0.0;
					}
					// 已经全部接收到数据重发帧
					if(icount == 1)
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
			}
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
BOOL CADCDataRecThread::OnCheckFrameIsRetransmission(unsigned int uiInstrumentNb, unsigned int uiIPAim, unsigned short usDataPointNow)
{
	CString str = _T("");
	unsigned short usLostDataFrameCount = 0;	// 丢失帧计数
	unsigned short usADCDataNb = ReceiveDataSize;	// ADC一帧的数据个数
	unsigned short usDataPointMove = 0;	// 记录指针偏移量
	m_structADC ADCFindFromStruct;

	// 接收到的ADC数据不是重发数据
	if (m_oADCLostMap[uiInstrumentNb].Lookup(usDataPointNow, ADCFindFromStruct) == NULL)
	{
		if (usDataPointNow > m_usDataPointPrevious[uiInstrumentNb])
		{
			usDataPointMove  = usDataPointNow - m_usDataPointPrevious[uiInstrumentNb];
		}
		else
		{
			usDataPointMove  = ADCFramePointLength + usDataPointNow - m_usDataPointPrevious[uiInstrumentNb];
		}

		usLostDataFrameCount = usDataPointMove/usADCDataNb - 1;

		// 有ADC采集数据丢帧则加入ADC数据重发队列
		if (usLostDataFrameCount > 0)
		{
			for (unsigned short m=0; m<usLostDataFrameCount; m++)
			{
				ProcessMessages();
				m_structADC ADCDataStruct;
				unsigned short usDataPointNb = (m_usDataPointPrevious[uiInstrumentNb] + (m + 1) * usADCDataNb) % ADCFramePointLength;
				ADCDataStruct.uiDataCount = m_uiADCDataFrameCount[uiInstrumentNb] + m;
				ADCDataStruct.uiRetransmissionNum = 0;
				m_oADCLostMap[uiInstrumentNb].SetAt(usDataPointNb, ADCDataStruct);
				if ((m_uiSampleTempNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
				{
					AfxMessageBox(_T("ADC数据处理过程缓冲区大小不够2！"));
				}
				else
				{
					memset(&m_dSampleTemp[uiInstrumentNb][m_uiSampleTempNum[uiInstrumentNb]], SndFrameBufInit, ReceiveDataSize);
					m_uiSampleTempNum[uiInstrumentNb] += ReceiveDataSize;
				}
			}
			m_uiADCDataFrameCount[uiInstrumentNb] += usLostDataFrameCount;
		}
		m_usDataPointPrevious[uiInstrumentNb] = usDataPointNow;
		return FALSE;

	}
	else
	{
		// 如果为重发数据则ADC应接收数据个数不变 
		m_uiADCDataFrameCount[uiInstrumentNb]--;
		m_uiADCRetransmissionNb = ADCFindFromStruct.uiDataCount;
		m_oADCLostMap[uiInstrumentNb].RemoveKey(usDataPointNow);
		return TRUE;
	}
}
// 该帧为最后一个数据重发帧
void CADCDataRecThread::OnRecOkIsRetransimissionFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData)
{
	if(uiIPAim == m_uiADCGraphIP[uiInstrumentNb])
	{
		// @@@@@@@@@需要改进
		m_Sec.Lock();
		m_pOScopeCtrl[uiInstrumentNb]->AppendPoint(pReceiveData, ReceiveDataSize);
		m_Sec.Unlock();
	}
	if ((m_uiADCSaveNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
	{
		AfxMessageBox(_T("ADC保存成文件的缓冲区大小不够3！"));
	}
	else
	{
		memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &pReceiveData, ReceiveDataSize);
		m_uiADCSaveNum[uiInstrumentNb] += ReceiveDataSize;
	}
	TRACE(_T("OnRecOkIsRetransimissionFrame函数中仪器%d的m_uiADCSaveNum为%d\r\n"), uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);
	// 接收到重发帧之前有保存帧
	if (m_uiSampleTempNum[uiInstrumentNb] > ReceiveDataSize)
	{
		// 将绘制完成的重发帧从缓冲区中移除
		if ((m_uiSampleTempNum[uiInstrumentNb] - ReceiveDataSize) > ADCDataTempDataSize)
		{
			AfxMessageBox(_T("ADC数据处理过程缓冲区大小不够4！"));
		}
		else
		{
			m_uiSampleTempNum[uiInstrumentNb] = m_uiSampleTempNum[uiInstrumentNb] - ReceiveDataSize;
			memcpy(&m_dTemp, &m_dSampleTemp[uiInstrumentNb][ReceiveDataSize], m_uiSampleTempNum[uiInstrumentNb]);
			memcpy(&m_dSampleTemp[uiInstrumentNb], &m_dTemp, m_uiSampleTempNum[uiInstrumentNb]);
		}

		for (unsigned int m=0; m<(m_uiSampleTempNum[uiInstrumentNb]/ReceiveDataSize);m++)
		{
			ProcessMessages();
			for (int k=0; k<ReceiveDataSize; k++)
			{
				ProcessMessages();
				pReceiveData[k] = m_dSampleTemp[uiInstrumentNb][m * ReceiveDataSize + k];
			}
			if(uiIPAim == m_uiADCGraphIP[uiInstrumentNb])
			{
				// @@@@@@@@@需要改进
				m_Sec.Lock();
				m_pOScopeCtrl[uiInstrumentNb]->AppendPoint(pReceiveData, ReceiveDataSize);
				m_Sec.Unlock();
			}
			if (m_uiADCSaveNum[uiInstrumentNb] + ReceiveDataSize > ADCDataTempDataSize)
			{
				AfxMessageBox(_T("ADC保存成文件的缓冲区大小不够5！"));
			}
			else
			{
				memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &pReceiveData, ReceiveDataSize);
				m_uiADCSaveNum[uiInstrumentNb] += ReceiveDataSize;
			}
			TRACE(_T("OnRecOkIsRetransimissionFrame函数中仪器%d的m_uiADCSaveNum为%d\r\n"), uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);

		}
		m_uiSampleTempNum[uiInstrumentNb] = 0;
	}
}

// 该帧为普通帧且之前没有重发帧
void CADCDataRecThread::OnRecOkIsNormalFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData)
{
	if(uiIPAim == m_uiADCGraphIP[uiInstrumentNb])
	{
		// @@@@@@@@@需要改进
		m_Sec.Lock();
		m_pOScopeCtrl[uiInstrumentNb]->AppendPoint(pReceiveData, ReceiveDataSize);
		m_Sec.Unlock();
	}
	if ((m_uiADCSaveNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
	{
		AfxMessageBox(_T("ADC保存成文件的缓冲区大小不够6！"));
	}
	else
	{
		memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &pReceiveData, ReceiveDataSize);
		m_uiADCSaveNum[uiInstrumentNb] += ReceiveDataSize;
	}
	TRACE(_T("OnRecOkIsNormalFrame函数中仪器%d的m_uiADCSaveNum为%d\r\n"), uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);
}

// 该帧为重发帧但不是最后一个重发帧
void CADCDataRecThread::OnRecNotOkIsRetransimissionFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData)
{
	unsigned int	uiMinNb = 0;		// 重发帧中的最小位置（个数）
	uiMinNb = OnADCRetransimissionMinNb(uiInstrumentNb);
	// 该重发帧之前各帧均已经收到
	if (uiMinNb > m_uiADCRetransmissionNb)
	{
		if(uiIPAim == m_uiADCGraphIP[uiInstrumentNb])
		{
			// @@@@@@@@@需要改进
			m_Sec.Lock();
			m_pOScopeCtrl[uiInstrumentNb]->AppendPoint(pReceiveData, ReceiveDataSize);
			m_Sec.Unlock();
		}
		if ((m_uiADCSaveNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
		{
			AfxMessageBox(_T("ADC保存成文件的缓冲区大小不够7！"));
		}
		else
		{
			memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &pReceiveData, ReceiveDataSize);
			m_uiADCSaveNum[uiInstrumentNb] += ReceiveDataSize;
		}
		TRACE(_T("OnRecNotOkIsRetransimissionFrame函数中仪器%d的m_uiADCSaveNum为%d\r\n"), uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);

		// 将绘制完成的重发帧从缓冲区中移除
		if ((m_uiSampleTempNum[uiInstrumentNb] - ReceiveDataSize) > ADCDataTempDataSize)
		{
			AfxMessageBox(_T("ADC数据处理过程缓冲区大小不够8！"));
		}
		else
		{
			m_uiSampleTempNum[uiInstrumentNb] = m_uiSampleTempNum[uiInstrumentNb] - ReceiveDataSize;
			memcpy(&m_dTemp, &m_dSampleTemp[uiInstrumentNb][ReceiveDataSize], m_uiSampleTempNum[uiInstrumentNb]);
			memcpy(&m_dSampleTemp[uiInstrumentNb], &m_dTemp, m_uiSampleTempNum[uiInstrumentNb]);
		}

		// 如果等待重发帧的队列中最小的采样帧位置和接收到的重发帧之间有保存帧
		if (uiMinNb > (m_uiADCRetransmissionNb + 1))
		{
			if (m_uiSampleTempNum[uiInstrumentNb] > ((uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize - 1))
			{
				for (unsigned int m=0; m<(uiMinNb - m_uiADCRetransmissionNb - 1); m++)
				{
					ProcessMessages();
					for (int k=0; k<ReceiveDataSize; k++)
					{
						ProcessMessages();
						pReceiveData[k] = m_dSampleTemp[uiInstrumentNb][m * ReceiveDataSize+k];
					}
					if(uiIPAim == m_uiADCGraphIP[uiInstrumentNb])
					{
						// @@@@@@@@@需要改进
						m_Sec.Lock();
						m_pOScopeCtrl[uiInstrumentNb]->AppendPoint(pReceiveData, ReceiveDataSize);
						m_Sec.Unlock();
					}
					if ((m_uiADCSaveNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
					{
						AfxMessageBox(_T("ADC保存成文件的缓冲区大小不够9！"));
					} 
					else
					{
						memcpy(&m_dADCSave[uiInstrumentNb][m_uiADCSaveNum[uiInstrumentNb]], &pReceiveData, ReceiveDataSize);
						m_uiADCSaveNum[uiInstrumentNb] += ReceiveDataSize;
					}
					TRACE(_T("OnRecNotOkIsRetransimissionFrame函数中仪器%d的m_uiADCSaveNum为%d\r\n"), uiInstrumentNb, m_uiADCSaveNum[uiInstrumentNb]);
				}
				// 将绘制完成的保存帧移除
				if ((m_uiSampleTempNum[uiInstrumentNb] - (uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize) > ADCDataTempDataSize)
				{
					AfxMessageBox(_T("ADC数据处理过程缓冲区大小不够10！"));
				} 
				else
				{
					m_uiSampleTempNum[uiInstrumentNb] = m_uiSampleTempNum[uiInstrumentNb] - (uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize;
					memcpy(&m_dTemp, &m_dSampleTemp[uiInstrumentNb][(uiMinNb - m_uiADCRetransmissionNb - 1) * ReceiveDataSize], m_uiSampleTempNum[uiInstrumentNb]);
					memcpy(&m_dSampleTemp[uiInstrumentNb], &m_dTemp, m_uiSampleTempNum[uiInstrumentNb]);
				}
			}
		}
	}
	// 该帧之前还有重发帧未收到
	else
	{
		if (m_uiSampleTempNum[uiInstrumentNb] > ((m_uiADCRetransmissionNb - uiMinNb) * ReceiveDataSize + ReceiveDataSize - 1))
		{
			// 将重发帧数据保存到缓冲区
			for (int i=0; i<ReceiveDataSize; i++)
			{
				ProcessMessages();
				m_dSampleTemp[uiInstrumentNb][(m_uiADCRetransmissionNb - uiMinNb) * ReceiveDataSize + i] = pReceiveData[i];
			}
		}
	}
}
// 该帧为普通帧且之前有重发帧
void CADCDataRecThread::OnRecNotOkIsNormalFrame(unsigned int uiInstrumentNb, double* pReceiveData)
{
	if ((m_uiSampleTempNum[uiInstrumentNb] + ReceiveDataSize) > ADCDataTempDataSize)
	{
		AfxMessageBox(_T("ADC数据处理过程缓冲区大小不够11！"));
	} 
	else
	{
		memcpy(&m_dSampleTemp[uiInstrumentNb][m_uiSampleTempNum[uiInstrumentNb]], &pReceiveData, ReceiveDataSize);
		m_uiSampleTempNum[uiInstrumentNb] += ReceiveDataSize;
	}
}
// 重置变量的值
void CADCDataRecThread::OnReset(void)
{
	for (int i=0; i<InstrumentNum; i++)
	{
		ProcessMessages();
		memset(&m_dSampleTemp[i], SndFrameBufInit, ADCDataTempDataSize);
		m_uiSampleTempNum[i] = 0;
		memset(&m_dADCSave[i], SndFrameBufInit, ADCDataTempDataSize);
		m_uiADCSaveNum[i] = 0;
		m_uiADCDataFrameCount[i] = 0;
		m_uiADCDataFrameRecCount[i] = 0;
		m_dADCDataShow[i] = 0;
		m_oADCLostMap[i].RemoveAll();
		m_uiADCGraphIP[i] = 0;
		m_usDataPointPrevious[i] = 0;
		m_pOScopeCtrl[i] = NULL;
	}
	memset(&m_dTemp, SndFrameBufInit, ADCDataTempDataSize);
	m_uiTempNum = 0;
	m_bStartSample = FALSE;
}