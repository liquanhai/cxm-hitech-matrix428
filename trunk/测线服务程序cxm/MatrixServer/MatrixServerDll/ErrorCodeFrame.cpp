#include "stdafx.h"
#include "MatrixServerDll.h"

// 创建误码查询帧信息结构体
m_oErrorCodeFrameStruct* OnCreateInstrumentErrorCodeFrame(void)
{
	m_oErrorCodeFrameStruct* pErrorCodeFrame = NULL;
	pErrorCodeFrame = new m_oErrorCodeFrameStruct;
	InitializeCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	pErrorCodeFrame->m_cpRcvFrameData = NULL;
	pErrorCodeFrame->m_cpSndFrameData = NULL;
	pErrorCodeFrame->m_oErrorCodeFrameSocket = INVALID_SOCKET;
	pErrorCodeFrame->m_cpCommandWord = NULL;
	pErrorCodeFrame->m_pCommandStructSet = NULL;
	pErrorCodeFrame->m_pCommandStructReturn = NULL;
	return pErrorCodeFrame;
}
// 初始化误码查询帧
void OnInitInstrumentErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pErrorCodeFrame == NULL) || (pCommInfo == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitInstrumentErrorCodeFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	if (pErrorCodeFrame->m_pCommandStructSet != NULL)
	{
		delete pErrorCodeFrame->m_pCommandStructSet;
		pErrorCodeFrame->m_pCommandStructSet = NULL;
	}
	pErrorCodeFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// 源地址
	pErrorCodeFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// 目的地址
	pErrorCodeFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// 目标IP地址端口号
	pErrorCodeFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort;
	// 误码查询发送缓冲区帧数设定为仪器个数
	pErrorCodeFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// 误码查询应答接收缓冲区帧数设定为仪器个数
	pErrorCodeFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// 误码查询返回端口
	pErrorCodeFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usErrorCodeReturnPort;
	// 重置帧内通讯信息
	// 命令，为1则设置命令应答，为2查询命令应答，为3AD采样数据重发
	pErrorCodeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// 重置帧内容解析变量
	ResetInstrumentFramePacket(pErrorCodeFrame->m_pCommandStructSet);
	// 清空发送帧缓冲区
	if (pErrorCodeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pErrorCodeFrame->m_cpSndFrameData;
		pErrorCodeFrame->m_cpSndFrameData = NULL;
	}
	pErrorCodeFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pErrorCodeFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iSndFrameSize);
	// 清空误码查询命令字集合
	if (pErrorCodeFrame->m_cpCommandWord != NULL)
	{
		delete[] pErrorCodeFrame->m_cpCommandWord;
		pErrorCodeFrame->m_cpCommandWord = NULL;
	}
	pErrorCodeFrame->m_cpCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pErrorCodeFrame->m_cpCommandWord, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iCommandWordMaxNum);
	// 误码查询命令字个数
	pErrorCodeFrame->m_usCommandWordNum = 0;

	// 重置帧内容解析变量
	if (pErrorCodeFrame->m_pCommandStructReturn != NULL)
	{
		delete pErrorCodeFrame->m_pCommandStructReturn;
		pErrorCodeFrame->m_pCommandStructReturn = NULL;
	}
	pErrorCodeFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pErrorCodeFrame->m_pCommandStructReturn);
	pErrorCodeFrame->m_pCommandStructReturn->m_cpADCSet = new char[pConstVar->m_iSndFrameSize];
	// 清空接收帧缓冲区
	if (pErrorCodeFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pErrorCodeFrame->m_cpRcvFrameData;
		pErrorCodeFrame->m_cpRcvFrameData = NULL;
	}
	pErrorCodeFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pErrorCodeFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
}
// 关闭误码查询帧信息结构体
void OnCloseInstrumentErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame)
{
	if (pErrorCodeFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	if (pErrorCodeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pErrorCodeFrame->m_cpSndFrameData;
		pErrorCodeFrame->m_cpSndFrameData = NULL;
	}
	if (pErrorCodeFrame->m_cpCommandWord != NULL)
	{
		delete[] pErrorCodeFrame->m_cpCommandWord;
		pErrorCodeFrame->m_cpCommandWord = NULL;
	}
	if (pErrorCodeFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pErrorCodeFrame->m_cpRcvFrameData;
		pErrorCodeFrame->m_cpRcvFrameData = NULL;
	}
	if (pErrorCodeFrame->m_pCommandStructSet != NULL)
	{
		delete pErrorCodeFrame->m_pCommandStructSet;
		pErrorCodeFrame->m_pCommandStructSet = NULL;
	}
	if (pErrorCodeFrame->m_pCommandStructReturn != NULL)
	{
		delete pErrorCodeFrame->m_pCommandStructReturn;
		pErrorCodeFrame->m_pCommandStructReturn = NULL;
	}
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
}
// 释放误码查询帧信息结构体
void OnFreeInstrumentErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame)
{
	if (pErrorCodeFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	delete pErrorCodeFrame;
	pErrorCodeFrame = NULL;
}
// 创建并设置误码查询端口
void OnCreateAndSetErrorCodeFrameSocket(m_oErrorCodeFrameStruct* pErrorCodeFrame, m_oLogOutPutStruct* pLogOutPut)
{
	if (pErrorCodeFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	// 创建套接字
	pErrorCodeFrame->m_oErrorCodeFrameSocket = CreateInstrumentSocket(pErrorCodeFrame->m_pCommandStructSet->m_usReturnPort + NetedPortMove, 
		pErrorCodeFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// 设置为广播端口
	SetInstrumentSocketBroadCast(pErrorCodeFrame->m_oErrorCodeFrameSocket, pLogOutPut);
	// 设置发送缓冲区
	SetSndBufferSize(pErrorCodeFrame->m_oErrorCodeFrameSocket, 
		pErrorCodeFrame->m_uiSndBufferSize, pLogOutPut);
	// 设置接收缓冲区大小
	SetRcvBufferSize(pErrorCodeFrame->m_oErrorCodeFrameSocket, 
		pErrorCodeFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetErrorCodeFrameSocket", "创建并设置误码查询帧端口！");
}
// 解析误码查询应答帧
bool ParseInstrumentErrorCodeReturnFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pErrorCodeFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentErrorCodeReturnFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	bool bReturn = false;
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	bReturn = ParseInstrumentFrame(pErrorCodeFrame->m_pCommandStructReturn,
		pErrorCodeFrame->m_cpRcvFrameData, pConstVar);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	return bReturn;
}
// 广播查询误码
void MakeInstrumentErrorCodeQueryFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pErrorCodeFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentErrorCodeQueryFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	unsigned short usPos = 0;
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	// 仪器IP地址
	pErrorCodeFrame->m_pCommandStructSet->m_uiDstIP = pConstVar->m_uiIPBroadcastAddr;
	// 查询命令
	pErrorCodeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// 广播端口
	pErrorCodeFrame->m_pCommandStructSet->m_uiBroadCastPortSeted = uiBroadCastPort;
	// 查询命令字内容
	// 广播端口
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdBroadCastPortSeted;
	usPos ++;
	// 交叉站交叉线尾包接收时刻
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdFDUErrorCode;
	usPos ++;
	// 交叉站大线尾包接收时刻
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXErrorCode1;
	usPos ++;
	// 尾包接收/发送时刻
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXErrorCode2;
	usPos ++;
	// 查询命令字个数
	pErrorCodeFrame->m_usCommandWordNum = usPos;
	MakeInstrumentFrame(pErrorCodeFrame->m_pCommandStructSet, pConstVar, 
		pErrorCodeFrame->m_cpSndFrameData, pErrorCodeFrame->m_cpCommandWord, 
		pErrorCodeFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
}
// 发送误码查询帧
void SendInstrumentErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pErrorCodeFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SendInstrumentErrorCodeFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	SendFrame(pErrorCodeFrame->m_oErrorCodeFrameSocket, pErrorCodeFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pErrorCodeFrame->m_pCommandStructSet->m_usAimPort, 
		pErrorCodeFrame->m_pCommandStructSet->m_uiAimIP, pConstVar->m_pLogOutPut);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
}