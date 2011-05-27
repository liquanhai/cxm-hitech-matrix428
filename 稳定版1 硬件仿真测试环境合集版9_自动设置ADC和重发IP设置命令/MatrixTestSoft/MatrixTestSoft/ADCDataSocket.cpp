// ADCDataSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "ADCDataSocket.h"

// CADCDataSocket

CADCDataSocket::CADCDataSocket()
: m_pSelectObject(NULL)
, m_pSelectObjectNoise(NULL)
//, m_pwnd(NULL)
, m_bStartSample(FALSE)
, m_csIPSource(_T(""))
, m_uiSendPort(0)
, m_uiTestADCLost(0)
, m_csSaveFilePath(_T(""))
, m_uiADCSaveFileNum(0)
, m_pFileSave(NULL)
, m_bOpenADCSaveFile(FALSE)
, m_uiADCDataToSaveNum(0)
, m_uiADCFileLength(0)
{
}

CADCDataSocket::~CADCDataSocket()
{
}

// CADCDataSocket 成员函数

void CADCDataSocket::OnReceive(int nErrorCode)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	int ret = 0;
	int icount = 0;
	unsigned short uiPort = 0;
	ret = Receive(ADCData,256);

	if(ret == 256) 
	{
		if (m_bStartSample == TRUE)
		{
			byte* pSampleData = &(ADCData[16]);
			ReceiveSampleData(pSampleData);
		}
	}
	icount = m_listADC.GetCount();
	if (icount>0)
	{
		m_structADC ADCStructTemp;
		POSITION pos = m_listADC.GetHeadPosition();
		for (int i = 0; i < icount; i++)
		{
			ADCStructTemp = m_listADC.GetNext(pos);
			MakeADCDataRetransmissionFrame(ADCStructTemp.usDataPointNb, ADCStructTemp.uiIPAim);
		}    
	}

	CSocket::OnReceive(nErrorCode);
}
// 接收采样数据
void CADCDataSocket::ReceiveSampleData(byte* pSampleData)
{
	// uiTestNb表明接收到帧所对应的仪器号
	unsigned int	uiIPAim = 0;
	unsigned short	usDataPointNow = 0; // 接收到帧的数据的序号
	unsigned int	uiMinNb = 0;		// 重发帧中的最小位置（个数）
	int	iSampleData = 0;
	int pos = 0;
	double dSampleDataToV = 0.0;
	unsigned int uitmp = 0;
	CString str = "";
	unsigned short usLostDataFrameCount = 0;	// 丢失帧计数
	unsigned short usADCDataNb = ReceiveDataSize;	// ADC一帧的数据个数
	BOOL bADCRetransimission = FALSE;			// 判断是否为重发帧的标志位
	unsigned int uiADCRetransimissionNb = 0;	// 接收到的重发帧所处位置

	// 设m_pFrameData[16]到m_pFrameData[19]为源地址做为通道号
	memcpy(&uiIPAim, &pSampleData[pos], 4);
	pos += 4;

	for (int i=0; i<GraphViewNum; i++)
	{
		if (m_pSelectObject[i] == 1)
		{
			uitmp = 81 + 10*i;
			if (uiIPAim	== uitmp)
			{
				// 接收数据缓存
				double dReceiveData [ReceiveDataSize]; 
				pos += 8;
				// m_pFrameData[28]到m_pFrameData[29]做为采样个数的序号，暂时不用
				memcpy(&usDataPointNow, &pSampleData[pos], 2);
				pos += 2;
				// 用于测试ADC丢帧后补帧
				// 			if (usDataPointNow == 24)
				// 			{
				// 				if (uiIPAim == 101)
				// 				{	
				// 					m_uiTestADCLost++;
				// 					if (m_uiTestADCLost == 1)
				// 					{
				// 						break;
				// 					}
				// 				}
				// 			
				// 			}
				// ADC应接收数据个数加一
				m_uiADCDataFrameCount[i]++;

				if (m_uiADCDataFrameCount[i] == 1)
				{
					m_usDataPointPrevious[i] = usDataPointNow;
				}
				else
				{
					m_structADC ADCFindFromStruct;
					POSITION pos;
					ADCFindFromStruct.uiIPAim = uiIPAim;
					ADCFindFromStruct.usDataPointNb = usDataPointNow;
					pos = m_listADC.Find(ADCFindFromStruct, NULL);
					// 接收到的ADC数据不是重发数据
					if (pos == NULL)
					{
						uitmp = m_uiADCDataFrameCount[i] % 10000;
						if (usDataPointNow > m_usDataPointPrevious[i])
						{
							m_usDataPointMove[i][uitmp]  = usDataPointNow - m_usDataPointPrevious[i];
						}
						else
						{
							m_usDataPointMove[i][uitmp]  = 2048 + usDataPointNow - m_usDataPointPrevious[i];
						}
						usLostDataFrameCount = m_usDataPointMove[i][uitmp] /usADCDataNb - 1;
						// 有ADC采集数据丢帧则加入ADC数据重发队列
						if (usLostDataFrameCount > 0)
						{
							for (unsigned short m=0; m<usLostDataFrameCount; m++)
							{
								m_structADC ADCDataStruct;
								ADCDataStruct.uiIPAim = uiIPAim;
								ADCDataStruct.usDataPointNb = (m_usDataPointPrevious[i] + (m+1)*usADCDataNb)%2048;
								ADCDataStruct.uiDataCount = m_uiADCDataFrameCount[i] + m;
								m_listADC.AddTail(ADCDataStruct);
							}
							m_uiADCDataFrameCount[i] += usLostDataFrameCount;
						}

						m_usDataPointPrevious[i] = usDataPointNow;

					}
					else
					{
						// 如果为重发数据则ADC应接收数据个数不变 
						m_uiADCDataFrameCount[i]--;
						bADCRetransimission = TRUE;
						ADCFindFromStruct = m_listADC.GetAt(pos);
						uiADCRetransimissionNb = ADCFindFromStruct.uiDataCount;
						m_listADC.RemoveAt(pos);
					}
				}

				// 之后为数据区
				for (int j=0; j<ReceiveDataSize; j++)
				{
					memcpy(&iSampleData, &pSampleData[pos], 3);
					pos += 3;

					// 24位数转换为电压值
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
						str.Format("ADC采样数值溢出，溢出值为%d", dSampleDataToV);
						AfxMessageBox(str);
					}
					dReceiveData[j] = dSampleDataToV;
				}
				// 无数据重发帧或已经全部接收到数据重发帧
				if(m_listADC.GetCount() == 0)
				{
					// 如果该帧为数据重发帧，处理该帧后再处理保存帧
					if (bADCRetransimission == TRUE)
					{
						m_Sec.Lock();
						m_pOScopeCtrl[i]->AppendPoint(dReceiveData, ReceiveDataSize);
						for (int t=0; t<ReceiveDataSize; t++)
						{
							m_dADCSave[i].push_back(dReceiveData[t]);
						}
						m_Sec.Unlock();
						m_uiADCRecCompleteCount[i]++;
						// 接收到重发帧之前有保存帧
						if (m_dSampleTemp[i].size() > 0)
						{
							for (unsigned int m=0; m<(m_dSampleTemp[i].size()/usADCDataNb);m++)
							{
								for (int k=0; k<ReceiveDataSize; k++)
								{
									dReceiveData[k] = m_dSampleTemp[i][m*usADCDataNb+k];
								}
								m_Sec.Lock();
								m_pOScopeCtrl[i]->AppendPoint(dReceiveData, ReceiveDataSize);
								for (int t=0; t<ReceiveDataSize; t++)
								{
									m_dADCSave[i].push_back(dReceiveData[t]);
								}
								m_Sec.Unlock();
								m_uiADCRecCompleteCount[i]++;
							}
							m_dSampleTemp[i].clear();
						}
					}
					else
					{
						m_Sec.Lock();
						m_pOScopeCtrl[i]->AppendPoint(dReceiveData, ReceiveDataSize);
						for (int t=0; t<ReceiveDataSize; t++)
						{
							m_dADCSave[i].push_back(dReceiveData[t]);
						}
						m_Sec.Unlock();
						m_uiADCRecCompleteCount[i]++;
					}
				}
				else
				{
					// 如果该帧为数据重发帧
					if (bADCRetransimission == TRUE)
					{
						m_Sec.Lock();
						m_pOScopeCtrl[i]->AppendPoint(dReceiveData, ReceiveDataSize);
						for (int t=0; t<ReceiveDataSize; t++)
						{
							m_dADCSave[i].push_back(dReceiveData[t]);
						}
						m_Sec.Unlock();
						m_uiADCRecCompleteCount[i]++;
						uiMinNb = OnADCRetransimissionMinNb();
						// 如果等待重发帧的队列中最小的采样帧位置和接收到的重发帧之间有保存帧
						if (uiMinNb > (m_uiADCRecCompleteCount[i]+1))
						{
							for (unsigned int m=0; m<(uiMinNb - m_uiADCRecCompleteCount[i] - 1); m++)
							{
								for (int k=0; k<ReceiveDataSize; k++)
								{
									dReceiveData[k] = m_dSampleTemp[i][m*usADCDataNb+k];
								}
								m_Sec.Lock();
								m_pOScopeCtrl[i]->AppendPoint(dReceiveData, ReceiveDataSize);
								for (int t=0; t<ReceiveDataSize; t++)
								{
									m_dADCSave[i].push_back(dReceiveData[t]);
								}
								m_Sec.Unlock();
								m_uiADCRecCompleteCount[i]++;
							}
							// 将绘制完成的保存帧移除
							vector<double> dTemp;
							for (unsigned int n=(uiMinNb - m_uiADCRecCompleteCount[i] - 1)*usADCDataNb; n<m_dSampleTemp[i].size(); n++)
							{
								dTemp.push_back(m_dSampleTemp[i][n]);
							}
							m_dSampleTemp[i].clear();
							for (unsigned int p=0; p<dTemp.size();p++)
							{
								m_dSampleTemp[i].push_back(dTemp[p]);
							}
							dTemp.clear();
						}
					}
					else
					{
						// 如果有重发帧，而本帧不是重发帧则先将该帧保存
						for (int k=0; k<ReceiveDataSize; k++)
						{
							m_dSampleTemp[i].push_back(dReceiveData[k]);
						}
					}
				}
				OnSaveADCToFile();
				break;
			}
		}
	}
}
// 生成ADC数据重发帧
void CADCDataSocket::MakeADCDataRetransmissionFrame(unsigned short usDataPointNb, unsigned int uiIPAim)
{
	unsigned int uiIPSource =	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	m_ucADCRetransmission[0] = 0x11;
	m_ucADCRetransmission[1] = 0x22;
	m_ucADCRetransmission[2] = 0x33;
	m_ucADCRetransmission[3] = 0x44;
	m_ucADCRetransmission[4] = 0x00;
	m_ucADCRetransmission[5] = 0x00;
	m_ucADCRetransmission[6] = 0x00;
	m_ucADCRetransmission[7] = 0x00;
	m_ucADCRetransmission[8] = 0x00;
	m_ucADCRetransmission[9] = 0x00;
	m_ucADCRetransmission[10] = 0x00;
	m_ucADCRetransmission[11] = 0x00;
	m_ucADCRetransmission[12] = 0x00;
	m_ucADCRetransmission[13] = 0x00;
	m_ucADCRetransmission[14] = 0x00;
	m_ucADCRetransmission[15] = 0x00;

	uiIPSource	=	inet_addr(m_csIPSource);
	usPortAim	=	ADRecPort;
	usCommand	=	3;
	// 源IP地址
	memcpy(&m_ucADCRetransmission[16], &uiIPSource, 4);
	// 目标IP地址
	memcpy(&m_ucADCRetransmission[20], &uiIPAim, 4);
	TRACE1("尾包时刻查询帧-仪器IP地址：%d\r\n", uiIPAim);
	// 目标端口号
	memcpy(&m_ucADCRetransmission[24], &usPortAim, 2);
	// 命令号 1-设置命令应答；2-查询命令应答；3-AD采样数据重发
	memcpy(&m_ucADCRetransmission[26], &usCommand, 2);

	int iPos = 32;

	memmove(m_ucADCRetransmission + iPos, &usDataPointNb, 2);
	iPos = iPos + 2;
	m_ucADCRetransmission[iPos] = 0x00;

	int icount = SendTo(m_ucADCRetransmission, 128, m_uiSendPort, IPBroadcastAddr);
}
// ADC数据需要重新发送帧对应的最小个数
unsigned int CADCDataSocket::OnADCRetransimissionMinNb(void)
{
	POSITION pos = m_listADC.GetHeadPosition();
	int icount = m_listADC.GetCount();
	unsigned int uimin = 0;
	m_structADC ADCStructTemp;

	ADCStructTemp = m_listADC.GetNext(pos);
	uimin = ADCStructTemp.uiDataCount;

	for (int i = 1; i < icount; i++)
	{
		ADCStructTemp = m_listADC.GetNext(pos);
		if (uimin > ADCStructTemp.uiDataCount)
		{
			uimin = ADCStructTemp.uiDataCount;
		}
	} 
	return uimin;
}
// 创建并打开ADC保存数据文件
void CADCDataSocket::OnOpenADCSaveFile(void)
{
	m_uiADCSaveFileNum++;

 	CString strFileName = "";
	CString strOutput = "";
	CString strTemp = "";
	strFileName.Format("%s\\%d.text", m_csSaveFilePath,m_uiADCSaveFileNum);
 	// 将ADC采样数据保存成ANSI格式的文件
 	errno_t err;
 	if((err = fopen_s(&m_pFileSave,strFileName,"w+"))!=NULL)
 	{
		AfxMessageBox(_T("ADC数据存储文件创建失败！"));	
		return;
 	}
	// 创建本次ADC数据采集数据存储文件夹
	CString str = "";
	SYSTEMTIME  sysTime;
	unsigned int uiADCDataFrameCount = 0;
	GetLocalTime(&sysTime);
	for (int i=0; i<GraphViewNum; i++)
	{
		if (m_pSelectObject[i] == 1)
		{
			if (m_pSelectObjectNoise[i] == 0)
			{
				uiADCDataFrameCount = m_uiADCDataFrameCount[i];
				break;
			}
		}
	}
	str.Format(_T("%04d年%02d月%02d日%02d:%02d:%02d:%04d 由第%d个数据包开始记录ADC采样数据：\r\n\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds, uiADCDataFrameCount);
	strOutput += str;

	// 输出仪器标签
	for (int i=0; i<GraphViewNum; i++)
	{
		strTemp.Format("%s\t\t",m_cSelectObjectName[i]);
		strOutput += strTemp;
	}
	strOutput += "\r\n";

	fprintf(m_pFileSave,"%s", strOutput); 
	m_bOpenADCSaveFile = TRUE;
}
// 关闭ADC保存数据文件
void CADCDataSocket::OnCloseADCSaveFile(void)
{
	if (m_pFileSave == NULL)
	{
		return;
	}
	fclose(m_pFileSave); 
	m_bOpenADCSaveFile = FALSE;
}
// 将ADC数据保存到文件中
void CADCDataSocket::OnSaveADCToFile(void)
{
	CString strOutput = "";
	CString strTemp = "";
	unsigned int uiADCDataToSaveNum = 0;
	vector<double> dTemp;

	if(m_bOpenADCSaveFile == FALSE)
	{
		OnOpenADCSaveFile();
	}
	uiADCDataToSaveNum = OnADCRecDataMinNum();

	if (uiADCDataToSaveNum == 0)
	{
		return;
	}
	if ((m_uiADCDataToSaveNum + uiADCDataToSaveNum) > m_uiADCFileLength)
	{
		uiADCDataToSaveNum = m_uiADCFileLength - m_uiADCDataToSaveNum;
	}


	// 输出各仪器采样数据
	for (unsigned int i=0; i<uiADCDataToSaveNum; i++)
	{
		for (int j=0; j<GraphViewNum; j++)
		{
			if (m_pSelectObject[j] == 1)
			{
				if (m_pSelectObjectNoise[j] == 0)
				{
					strTemp.Format("%2.9f\t",m_dADCSave[j][i]);
					strOutput += strTemp;
				}
				else
				{
					strOutput += "\t\t";
				}
			}
			else
			{
				strOutput += "\t\t";
			}
		}
		strOutput += "\r\n";
	}
	fprintf(m_pFileSave,"%s", strOutput); 

	// 清除保存过的数据
	for (int j=0; j<GraphViewNum; j++)
	{
		if (m_pSelectObject[j] == 1)
		{
			if (m_pSelectObjectNoise[j] == 0)
			{
				for (unsigned int i=uiADCDataToSaveNum; i<m_dADCSave[j].size(); i++)
				{
					dTemp.push_back(m_dADCSave[j][i]);
				}
				m_dADCSave[j].clear();
				for (unsigned int k=0; k<dTemp.size();k++)
				{
					m_dADCSave[j].push_back(dTemp[k]);
				}
				dTemp.clear();
			}
		}
	}
	m_uiADCDataToSaveNum += uiADCDataToSaveNum;
	if (m_uiADCDataToSaveNum == m_uiADCFileLength)
	{
		m_uiADCDataToSaveNum = 0;
		OnCloseADCSaveFile();
	}
}
unsigned int CADCDataSocket::OnADCRecDataMinNum(void)
{
	unsigned int uiMinSize = 10000;
	bool bSelect = false;
	for (int i=0; i<GraphViewNum; i++)
	{
		if (m_pSelectObject[i] == 1)
		{
			if (m_pSelectObjectNoise[i] == 0)
			{
				if (uiMinSize > m_dADCSave[i].size())
				{
					uiMinSize = m_dADCSave[i].size();
				}
				bSelect = true;
			}
		}
	}
	if (bSelect == false)
	{
		uiMinSize = 0;
	}
	return uiMinSize;
}

// 关闭采样后保存剩余数据
void CADCDataSocket::OnSaveRemainADCData(unsigned int uiADCDataNeedToSave)
{
	unsigned int uiDataLength = 0;
	CString strOutput = "";
	CString strTemp ="";
	if (m_pFileSave == NULL)
	{
		return;
	}
	for (unsigned int i=0; i<uiADCDataNeedToSave; i++)
	{
		for (int j=0; j<GraphViewNum; j++)
		{
			if (m_pSelectObject[j] == 1)
			{
				if (m_pSelectObjectNoise[j] == 0)
				{
					uiDataLength = m_dADCSave[j].size();
					if (uiDataLength == 0 )
					{
						strOutput += "\t\t";
						continue;
					}
					if (uiDataLength > i)
					{	
						strTemp.Format("%2.9f\t",m_dADCSave[j][i]);
						strOutput += strTemp;
					}
					else
					{
						strOutput += "\t\t";
					}
				}
				else
				{
					strOutput += "\t\t";
				}
			}
			else
			{
				strOutput += "\t\t";
			}
		}
		strOutput += "\r\n";
	}
	fprintf(m_pFileSave,"%s", strOutput); 
	// 清空接收缓冲区

	for (unsigned int i=0; i<GraphViewNum; i++)
	{
		m_dADCSave[i].clear();
	}
	OnCloseADCSaveFile();
}