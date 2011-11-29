// SocketADCDataRec.cpp : 实现文件
//

#include "stdafx.h"
#include "绘图程序.h"
#include "SocketADCDataRec.h"


// CSocketADCDataRec

CSocketADCDataRec::CSocketADCDataRec()
: m_uipRecFrameNb(NULL)
, m_uiInstrumentNb(NULL)
//, m_uiDrawPointXNb(0)
, m_uiInstrumentADCNum(0)
, m_bRecADCSetInfoFrame(FALSE)
, m_uiSamplingRate(1)
//, m_uiInstrumentRecFrameNum(0)
, m_pParameterSet(NULL)
{
}

CSocketADCDataRec::~CSocketADCDataRec()
{
	// 记录X轴坐标点信息
/*	m_DrawPoint_X.clear();*/
	if (m_uiInstrumentNb != NULL)
	{
		delete[] m_uiInstrumentNb;
	}
}


// CSocketADCDataRec 成员函数

void CSocketADCDataRec::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	int ret=0;
	ret = Receive(m_oADCRecFrameBuf, ADCRecFrameBufSize);
	if(ret == ADCRecFrameBufSize) 
	{
		// 单个帧处理
		ProcFrameOne();
	}

	CSocket::OnReceive(nErrorCode);
}

// 单个帧处理
void CSocketADCDataRec::ProcFrameOne(void)
{
	// uiNb表明接收到帧所对应的仪器号
	unsigned int	uiNb = 0;
	// 设备标记点号
	unsigned int uiLocation = 0;
	unsigned short usCommand = 0;
	int iPos = FrameHeadSize;
	unsigned short usInstrumentNum = 0;
	int	iSampleData = 0;
	double dSampleDataToV = 0.0;
	unsigned int uiFrameNb = 0;									// 接收的帧的序号
	double dbReceiveData [ReceiveDataNum];			// 接收数据缓存
	// [16]到[19]为采样设备绘图序号（从0开始）
	memcpy(&uiNb, &m_oADCRecFrameBuf[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	// [20]到[23]为采样设备标记点号
	memcpy(&uiLocation, &m_oADCRecFrameBuf[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	iPos += FramePacketSize2B;
	// 设m_oADCRecFrameBuf[26]到m_oADCRecFrameBuf[27]为命令字
	memcpy(&usCommand, &m_oADCRecFrameBuf[iPos], FramePacketSize2B);
	iPos += FramePacketSize2B;
	if (usCommand == SendSetCmd)
	{
		// 为1则28~29为参与采样的设备个数
		memcpy(&usInstrumentNum, &m_oADCRecFrameBuf[iPos], FramePacketSize2B);
		iPos += FramePacketSize2B;
		if (usInstrumentNum == 0)
		{
			AfxMessageBox(_T("采样设备个数为0！"));
			return;
		}
		m_bRecADCSetInfoFrame = TRUE;
		// 创建图形显示数据缓冲区
		OnPrepareToShow(usInstrumentNum);
	}
	else if (usCommand == SendADCCmd)
	{
		if (m_bRecADCSetInfoFrame == FALSE)
		{
			return;
		}
		// 为3则36开始为ADC数据，30~33为接收帧序号（从0开始），从而计算出每个点对应的X坐标值
		iPos += FramePacketSize2B;
		memcpy(&uiFrameNb, &m_oADCRecFrameBuf[iPos], FramePacketSize4B);
		iPos += FramePacketSize4B;
		iPos += FramePacketSize2B;
		m_uiInstrumentNb[uiNb] = uiLocation;
		m_uipRecFrameNb[uiNb].push_back(uiFrameNb);
// 		if (uiNb == m_uiDrawPointXNb)
// 		{
// 			m_uiInstrumentRecFrameNum++;
// 		}
		// 之后为数据区
		for (int j=0; j<ReceiveDataNum; j++)
		{
			memcpy(&iSampleData, &m_oADCRecFrameBuf[iPos], ADCDataSize3B);
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
			dbReceiveData[j] = dSampleDataToV;
		}
		// 将数据复制到图形显示缓冲区
// 		if (m_uipRecFrameNum[uiNb] < ADCRecFrameShowNum)
// 		{
			for (int j=0; j<ReceiveDataNum; j++)
			{
				m_dbFduData[uiNb].push_back(dbReceiveData[j]);
// 				if (uiNb == m_uiDrawPointXNb)
// 				{
// 					if (m_uiInstrumentRecFrameNum == 1)
// 					{
// 						m_DrawPoint_X.push_back((uiFrameNb * ReceiveDataNum + j) * m_uiSamplingRate);
// 					}
// 					else
// 					{
// 						int iSize = m_DrawPoint_X.size();
// 						double dbPointX = m_DrawPoint_X[iSize - 1];
// 						m_DrawPoint_X.push_back(dbPointX + m_uiSamplingRate);
// 					}
// 				}
			}
//		}
// 		else
// 		{
// 			// 删除vector中部分元素可以用erase
// 			m_dbFduData[uiNb].erase(m_dbFduData[uiNb].begin(), m_dbFduData[uiNb].begin() + ReceiveDataNum);
// 			for (int i=0; i<ReceiveDataNum; i++)
// 			{
// 				m_dbFduData[uiNb].push_back(dbReceiveData[i]);
// 			}
// 			if (uiNb == m_uiDrawPointXNb)
// 			{
// 				m_DrawPoint_X.erase(m_DrawPoint_X.begin(), m_DrawPoint_X.begin() + ReceiveDataNum);
// 				for (int j=0; j<ReceiveDataNum; j++)
// 				{
// //					m_DrawPoint_X.push_back((uiFrameNb * ReceiveDataNum + j) * m_uiSamplingRate);
// 					int iSize = m_DrawPoint_X.size();
// 					double dbPointX = m_DrawPoint_X[iSize - 1];
// 					m_DrawPoint_X.push_back(dbPointX + m_uiSamplingRate);
// 				}
// 			}
// 		}
// 		m_uipRecFrameNum[uiNb]++;
	}
}

// ADC数据绘图准备
void CSocketADCDataRec::OnPrepareToShow(unsigned short usInstrumentNum)
{
	// 初始化变量
/*	m_DrawPoint_X.clear();*/
	if (m_dbFduData != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduData[i].clear();
		}
		delete[] m_dbFduData;
		m_dbFduData = NULL;
	}
	if (m_dbFduShow != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduShow[i].clear();
		}
		delete[] m_dbFduShow;
		m_dbFduShow = NULL;
	}
	if (m_uipRecFrameNb != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_uipRecFrameNb[i].clear();
		}
		delete[] m_uipRecFrameNb;
		m_uipRecFrameNb = NULL;
	}
	if (m_uiInstrumentNb != NULL)
	{
		delete[] m_uiInstrumentNb;
		m_uiInstrumentNb = NULL;
	}

	if (usInstrumentNum == 0)
	{
		return;
	}
	m_uiInstrumentADCNum = usInstrumentNum;
	m_dbFduData = new vector<double>[m_uiInstrumentADCNum];
	m_dbFduShow = new vector<double>[m_uiInstrumentADCNum];
	m_uipRecFrameNb = new vector<unsigned int>[m_uiInstrumentADCNum];
	m_uiInstrumentNb = new unsigned int[m_uiInstrumentADCNum];
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		m_uiInstrumentNb[i] = 0;
	}
}

// 得到当前ADC数据接收帧起始序号中的最大值，并返回
unsigned int CSocketADCDataRec::GetRecFrameBeginMaxNb(void)
{
	if (m_uipRecFrameNb[0].size() == 0)
	{
		return 0;
	}
	unsigned int uiMax = m_uipRecFrameNb[0][0];
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		if (m_uipRecFrameNb[i].size() == 0)
		{
			return 0;
		}
		if (uiMax < m_uipRecFrameNb[i][0])
		{
			uiMax = m_uipRecFrameNb[i][0];
		}
	}
	return uiMax;
}

// 得到当前ADC数据接收帧最后一个序号中的最小值，并返回
unsigned int CSocketADCDataRec::GetRecFrameEndMinNb(void)
{
	if (m_uipRecFrameNb[0].size() == 0)
	{
		return 0;
	}
	unsigned int uiMin = m_uipRecFrameNb[0][m_uipRecFrameNb[0].size() - 1];
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		if (m_uipRecFrameNb[i].size() == 0)
		{
			return 0;
		}
		if (uiMin > m_uipRecFrameNb[i][m_uipRecFrameNb[i].size() - 1])
		{
			uiMin = m_uipRecFrameNb[i][m_uipRecFrameNb[i].size() - 1];
		}
	}
	return uiMin;
}
// 得到要清除的仪器个数并返回
unsigned int CSocketADCDataRec::GetRecFrameBeginToEndNum(unsigned int uiInstrumentNb, unsigned int uiRecFrameEndMinNb)
{
	return ((uiRecFrameEndMinNb - m_uipRecFrameNb[uiInstrumentNb][0]) / m_uiSamplingRate + 1);
}
// 发送采样参数设置命令
void CSocketADCDataRec::OnMakeAndSendSetFrame(unsigned short usSetOperation)
{
	int iPos = 0;
	CString str = _T("");
	byte ucCommand = 0;
	memset(m_oADCGraphSetFrameBuf, SndFrameBufInit, ADCSendFrameBufSize);
	m_oADCGraphSetFrameBuf[0] = FrameHeadCheck0;
	m_oADCGraphSetFrameBuf[1] = FrameHeadCheck1;
	m_oADCGraphSetFrameBuf[2] = FrameHeadCheck2;
	m_oADCGraphSetFrameBuf[3] = FrameHeadCheck3;
	memset(&m_oADCGraphSetFrameBuf[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	// 源IP地址
	iPos = FrameHeadSize;
	iPos += FramePacketSize4B;
	// 目标IP地址
	iPos += FramePacketSize4B;
	// 目标端口号
	iPos += FramePacketSize2B;
	// 命令号 1-开始图形化显示；2-停止图形化显示
	memcpy(&m_oADCGraphSetFrameBuf[iPos], &usSetOperation, FramePacketSize2B);
	iPos += FramePacketSize2B;
	if (usSetOperation == StartGraphShow)
	{
		// 设置抽样率命令字
		ucCommand = CmdADCDataSamplingRate;
		memcpy(&m_oADCGraphSetFrameBuf[iPos], &ucCommand, FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		// 设置抽样率
		memcpy(&m_oADCGraphSetFrameBuf[iPos], &m_uiSamplingRate, FramePacketSize4B);
		iPos += FramePacketSize4B;
	}
	m_oADCGraphSetFrameBuf[iPos] = SndFrameBufInit;
	unsigned int uiSendPort = 0;
	_stscanf_s(m_pParameterSet->m_csSendPort,_T("%x"), &uiSendPort);
	SendTo(&m_oADCGraphSetFrameBuf, ADCSendFrameBufSize, uiSendPort, m_pParameterSet->m_csIPAddrAim);
}
