// MatrixServerDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "MatrixServerDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
// ����ʵ����������ʵ��ָ��
MatrixServerDll_API m_oEnvironmentStruct* CreateInstance(void)
{
	m_oEnvironmentStruct* pEnv = new m_oEnvironmentStruct;
	pEnv->m_pInstrumentCommInfo = NULL;
	pEnv->m_pHeartBeatFrame = NULL;
	pEnv->m_pHeadFrame = NULL;
	pEnv->m_pIPSetFrame = NULL;
	pEnv->m_pThreadProcFlag = NULL;
	return pEnv;
}
// У��֡��ͬ����
MatrixServerDll_API bool CheckInstrumentFrameHead(byte* pFrameData)
{
	if (pFrameData == NULL)
	{
		return false;
	}
	byte byFrameHeadCheck[] = FrameHeadCheck;
	for (int i=0; i<FrameHeadSize; i++)
	{
		if (pFrameData[i] != byFrameHeadCheck[i])
		{
			return false;
		}
	}
	return true;
}
// ����֡��ͬ����
MatrixServerDll_API void MakeInstrumentFrameHead(byte* pFrameData)
{
	if (pFrameData == NULL)
	{
		return;
	}
	byte byFrameHeadCheck[] = FrameHeadCheck;
	for (int i=0; i<FrameHeadSize; i++)
	{
		pFrameData[i] = byFrameHeadCheck[i];
	}
}
// ����֡���ݽ�������
MatrixServerDll_API void ResetInstrumentFramePacket(m_oInstrumentCommandStruct* pCommand)
{
	if (pCommand == NULL)
	{
		return;
	}
	// SN����8λΪ�������ͣ�0x01Ϊ����վ��0x02Ϊ��Դվ��0x03Ϊ�ɼ�վ
	pCommand->m_uiSN = 0;
	// �װ�ʱ��
	pCommand->m_uiTimeHeadFrame = 0;
	// ����IP��ַ
	pCommand->m_uiInstrumentIP = 0;
	// ����ʱ��
	pCommand->m_uiSysTime = 0;
	// ����ʱ��������λ
	pCommand->m_uiLocalTimeFixedHigh = 0;
	// ����ʱ��������λ
	pCommand->m_usLocalTimeFixedLow = 0;
	// �Զ����ݷ��ص�ַ
	pCommand->m_uiADCDataReturnAddr = 0;
	// �Զ����ݷ��ض˿�
	pCommand->m_usADCDataReturnPort = 0;
	// �Զ����ݷ������ad_cmd(7)=1���˿ڵ�����=0���˿ڲ���
	pCommand->m_usADCDataReturnCmd = 0;
	// �����������λΪ1ʱ�����ض˿��Զ���1��������ʱ���ص��޶˿�
	// �˿ڵ�������
	pCommand->m_usADCDataReturnPortLimitLow = 0;
	// �˿ڵ�������
	pCommand->m_usADCDataReturnPortLimitHigh = 0;
	// ��������ȴ��˿ڣ�ָ���ý�����λ���㲥����Ķ˿�
	pCommand->m_usSetBroadCastPort = 0;
	// �������ݴ������
	pCommand->m_byFDUErrorCodeDataCount = 0;
	// ����������
	pCommand->m_byFDUErrorCodeCmdCount = 0;
	// ʱ�䱨��״̬
	pCommand->m_byTimeStatus = 0;
	// ����״̬
	pCommand->m_byCtrlStatus = 0;
	// TBʱ�̸�λ
	pCommand->m_uiTBHigh = 0;
	// TBʱ�̵�λ
	pCommand->m_usTBLow = 0;
	// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
	pCommand->m_usTBCtrl = 0;
	// work_ctrl���ƽ���վ���պͷ�������ķ���
	// �ɸߵ���λÿλ�ֱ���Ʒ��Ϳڽ�����A��B������A��B�����ն˽�����A��B������A��B
	// =0Ϊ����=1Ϊ��
	pCommand->m_byLAUXRoutOpenQuery = 0;
	// ·�ɿ���
	// �ɸ�λ����λ�ֱ���ƿ�������A����������B��������A��������B
	// =0Ϊ����=1Ϊ��
	pCommand->m_byLAUXRoutOpenSet = 0;
	// β������\����ʱ�̵�λ//����վβ������ʱ�̣���14λ��Ч
	pCommand->m_usTailRecSndTimeLow = 0;
	// �㲥����ȴ��˿�ƥ�䣬������ڵ�һ��������λ�ã�����0x0a�����е�16λ�˿�ƥ����ܽ��չ㲥����
	pCommand->m_usBroadCastPortSet = 0;
	// ����ʱ��
	pCommand->m_uiNetTime = 0;
	// ����վ����Aβ������ʱ��
	pCommand->m_usLAUXTailRecTimeLineA = 0;
	// ����վ����Bβ������ʱ��
	pCommand->m_usLAUXTailRecTimeLineB = 0;
	// ����վ������Aβ������ʱ��
	pCommand->m_usLAUXTailRecTimeLAUXLineA = 0;
	// ����վ������Bβ������ʱ��
	pCommand->m_usLAUXTailRecTimeLAUXLineB = 0;
	// ����վ����A���ݹ���
	pCommand->m_byLAUXErrorCodeDataLineACount = 0;
	// ����վ����B���ݹ���
	pCommand->m_byLAUXErrorCodeDataLineBCount = 0;
	// ����վ������A���ݹ���
	pCommand->m_byLAUXErrorCodeDataLAUXLineACount = 0;
	// ����վ������B���ݹ���
	pCommand->m_byLAUXErrorCodeDataLAUXLineBCount = 0;
	// ����վ����ڹ���
	pCommand->m_byLAUXErrorCodeCmdCount = 0;
	// ����վ�Ϸ�·��IP
	pCommand->m_uiRoutIPTop = 0;
	// ����վ�·�·��IP
	pCommand->m_uiRoutIPDown = 0;
	// ����վ��·��IP
	pCommand->m_uiRoutIPLeft = 0;
	// ����վ�ҷ�·��IP
	pCommand->m_uiRoutIPRight = 0;
	// ·��IP��ַ
	pCommand->m_uiRoutIP = 0;
	// 0x18��������
	memset(pCommand->m_byADCSet, SndFrameBufInit, ADCSetCommandMaxByte);
	// 0x18�������ݸ���
	pCommand->m_usADCSetNum = 0;
}
// �������豸ͨѶ����֡����
MatrixServerDll_API bool ParseInstrumentFrame(m_oInstrumentCommandStruct* pCommand, byte* pFrameData)
{
	if (pCommand == NULL)
	{
		return false;
	}
	if (pFrameData == NULL)
	{
		return false;
	}
	unsigned char	byCommandWord = 0;
	int iPos = 0;
	// У��֡��ͬ����
	if (false == CheckInstrumentFrameHead(pFrameData))
	{
		return false;
	}
	iPos += FrameHeadSize;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pCommand);
	// ԴIP��ַ
	memcpy(&pCommand->m_uiSrcIP, &pFrameData[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pCommand->m_uiDstIP, &pFrameData[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pCommand->m_usReturnPort, &pFrameData[iPos], FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pCommand->m_usCommand, &pFrameData[iPos], FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����֡����

	while(true)
	{
		memcpy(&byCommandWord, &pFrameData[iPos], FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		if (byCommandWord == CmdSn)
		{
			memcpy(&pCommand->m_uiSN, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdHeadFrameTime)
		{
			memcpy(&pCommand->m_uiTimeHeadFrame, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLocalIPAddr)
		{
			memcpy(&pCommand->m_uiInstrumentIP, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLocalSysTime)
		{
			memcpy(&pCommand->m_uiSysTime, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLocalTimeFixedHigh)
		{
			memcpy(&pCommand->m_uiLocalTimeFixedHigh, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLocalTimeFixedLow)
		{
			memcpy(&pCommand->m_usLocalTimeFixedLow, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdADCDataReturnAddr)
		{
			memcpy(&pCommand->m_uiADCDataReturnAddr, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdADCDataReturnPort)
		{
			memcpy(&pCommand->m_usADCDataReturnPort, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnCmd, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdADCDataReturnPortLimit)
		{
			memcpy(&pCommand->m_usADCDataReturnPortLimitLow, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnPortLimitHigh, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdSetBroadCastPort)
		{
			memcpy(&pCommand->m_usSetBroadCastPort, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdFDUErrorCode)
		{
			memcpy(&pCommand->m_byFDUErrorCodeDataCount, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byFDUErrorCodeCmdCount, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byTimeStatus, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byCtrlStatus, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
		}
		else if (byCommandWord == CmdTBHigh)
		{
			memcpy(&pCommand->m_uiTBHigh, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdTbLow)
		{
			memcpy(&pCommand->m_usTBLow, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usTBCtrl, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdLAUXRoutOpenQuery)
		{
			memcpy(&pCommand->m_byLAUXRoutOpenQuery, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLAUXRoutOpenSet)
		{
			memcpy(&pCommand->m_byLAUXRoutOpenSet, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdTailRecSndTimeLow)
		{
			memcpy(&pCommand->m_usTailRecSndTimeLow, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdBroadCastPortSet)
		{
			memcpy(&pCommand->m_usBroadCastPortSet, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdADCSet)
		{
			memcpy(&pCommand->m_byADCSet[pCommand->m_usADCSetNum], &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
			pCommand->m_usADCSetNum += FramePacketSize4B;
		}
		else if (byCommandWord == CmdNetTime)
		{
			memcpy(&pCommand->m_uiNetTime, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLineTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLineA, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLineB, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdLAUTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineA, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineB, &pFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdLAUXErrorCode1)
		{
			memcpy(&pCommand->m_byLAUXErrorCodeDataLineACount, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLineBCount, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLAUXLineACount, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLAUXLineBCount, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
		}
		else if (byCommandWord == CmdLAUXErrorCode2)
		{
			memcpy(&pCommand->m_byLAUXErrorCodeCmdCount, &pFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdReturnRout)
		{
			memcpy(&pCommand->m_uiRoutIP, &pFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdEnd)
		{
			break;
		}
		else
		{
			iPos += FramePacketSize4B;
		}
	}
	return true;
}
// �������豸ͨѶ֡
MatrixServerDll_API void MakeInstrumentFrame(m_oInstrumentCommandStruct* pCommand, byte* pFrameData, byte* pCommandWord, unsigned short usCommandWordNum)
{
	if (pCommand == NULL)
	{
		return;
	}
	if (pFrameData == NULL)
	{
		return;
	}
	if (pCommand == NULL)
	{
		return;
	}
	int iPos = 0;
	// ����֡��ͬ����
	MakeInstrumentFrameHead(pFrameData);
	iPos += FrameHeadSize;
	// ԴIP��ַ
	memcpy(&pFrameData[iPos], &pCommand->m_uiSrcIP, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pFrameData[iPos], &pCommand->m_uiDstIP, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pFrameData[iPos], &pCommand->m_usReturnPort, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pFrameData[iPos], &pCommand->m_usCommand, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ��ʱ��
	iPos += FramePacketSize4B;

	// ����֡����
	for (unsigned short i=0; i<usCommandWordNum; i++)
	{
		memcpy(&pFrameData[iPos], &pCommandWord[i], FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		if (pCommandWord[i] == CmdSn)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiSN, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdHeadFrameTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiTimeHeadFrame, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdLocalIPAddr)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiInstrumentIP, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdLocalSysTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiSysTime, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdLocalTimeFixedHigh)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiLocalTimeFixedHigh, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdLocalTimeFixedLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLocalTimeFixedLow, FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdADCDataReturnAddr)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiADCDataReturnAddr, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdADCDataReturnPort)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPort, FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnCmd, FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (pCommandWord[i] == CmdADCDataReturnPortLimit)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPortLimitLow, FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPortLimitHigh, FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (pCommandWord[i] == CmdSetBroadCastPort)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usSetBroadCastPort, FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdFDUErrorCode)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byFDUErrorCodeDataCount, FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byFDUErrorCodeCmdCount, FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byTimeStatus, FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byCtrlStatus, FramePacketSize1B);
			iPos += FramePacketSize1B;
		}
		else if (pCommandWord[i] == CmdTBHigh)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiTBHigh, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdTbLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usTBLow, FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usTBCtrl, FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (pCommandWord[i] == CmdLAUXRoutOpenQuery)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXRoutOpenQuery, FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdLAUXRoutOpenSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXRoutOpenSet, FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdTailRecSndTimeLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usTailRecSndTimeLow, FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdBroadCastPortSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usBroadCastPortSet, FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdADCSet)
		{
			for(unsigned short j=0; j<pCommand->m_usADCSetNum; j+=FramePacketSize4B)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_byADCSet[j], FramePacketSize4B);
				iPos += FramePacketSize4B;
			}
		}
		else if (pCommandWord[i] == CmdNetTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiNetTime, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdLineTailRecTimeLAUX)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLineA, FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLineB, FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (pCommandWord[i] == CmdLAUTailRecTimeLAUX)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLAUXLineA, FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLAUXLineB, FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (pCommandWord[i] == CmdLAUXErrorCode1)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLineACount, FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLineBCount, FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLAUXLineACount, FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLAUXLineBCount, FramePacketSize1B);
			iPos += FramePacketSize1B;
		}
		else if (pCommandWord[i] == CmdLAUXErrorCode2)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeCmdCount, FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (pCommandWord[i] == CmdReturnRout)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIP, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else
		{
			memset(&pFrameData[iPos], SndFrameBufInit, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
	}
	pFrameData[iPos] = CmdEnd;
}
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ
MatrixServerDll_API SOCKET CreateInstrumentSocket(m_oInstrumentCommandStruct* pCommand)
{
	SOCKET oSocket = INVALID_SOCKET;
	sockaddr_in oAddr;
	oSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	oAddr.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	oAddr.sin_port = htons(pCommand->m_usReturnPort);
	oAddr.sin_addr.S_un.S_addr = pCommand->m_uiSrcIP;
	int iReturn = bind(oSocket, reinterpret_cast<sockaddr*>(&oAddr), sizeof(oAddr));	// �󶨱��ص�ַ
	listen(oSocket, 2);
	if (iReturn == SOCKET_ERROR)
	{

	}
	return oSocket;
}
// ���ù㲥ģʽ
MatrixServerDll_API void SetInstrumentSocketBroadCast(SOCKET oSocket)
{
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	int iReturn = setsockopt(oSocket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&iOptval), iOptlen);
	if (iReturn == SOCKET_ERROR)
	{

	}
}
// ���ö˿ڽ��ջ���������֡����
MatrixServerDll_API void SetRcvBufferSize(SOCKET oSocket, int iFrameCount)
{
	int iOptionValue = iFrameCount * RcvFrameSize;
	int iOptionLen = sizeof(int);
	int iReturn = setsockopt(oSocket, SOL_SOCKET, SO_RCVBUF,  reinterpret_cast<const char *>(&iOptionValue), iOptionLen);
	if (iReturn == SOCKET_ERROR)
	{
	}
}
// ���ö˿ڷ��ͻ���������֡����
MatrixServerDll_API void SetSndBufferSize(SOCKET oSocket, int iFrameCount)
{
	int iOptionValue = iFrameCount * SndFrameSize;
	int iOptionLen = sizeof(int);
	int iReturn = setsockopt(oSocket, SOL_SOCKET, SO_SNDBUF,  reinterpret_cast<const char *>(&iOptionValue), iOptionLen);
	if (iReturn == SOCKET_ERROR)
	{
	}
}
// �õ�������ջ������յ���֡����
MatrixServerDll_API DWORD GetFrameCount(SOCKET oSocket)
{
	DWORD dwFrameCount = 0;
	// �õ�������ջ����������ֽ���
	ioctlsocket(oSocket, FIONREAD, &dwFrameCount);
	// �õ�֡����
	dwFrameCount = dwFrameCount / RcvFrameSize;

	return dwFrameCount;
}
// �õ�֡����
MatrixServerDll_API bool GetFrameData(SOCKET oSocket, byte* pFrameData)
{
	bool bReturn = false;
	sockaddr_in AddrFrom;
	int iSize = sizeof(AddrFrom);
	int iCount = recvfrom(oSocket, reinterpret_cast<char *>(pFrameData), RcvFrameSize, 0, reinterpret_cast<sockaddr*>(&AddrFrom), &iSize);
	if(iCount == RcvFrameSize)	//֡��С��ȷ
	{
		bReturn = true;
	}
	else
	{

	}
	return bReturn;
}
// ����֡
MatrixServerDll_API void SendFrame(SOCKET oSocket, byte* pFrameData, unsigned short usPort, unsigned int uiIP)
{
	// ����֡
	sockaddr_in addrSend;
	addrSend.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	addrSend.sin_port = htons(usPort);
	addrSend.sin_addr.S_un.S_addr = uiIP;
	sendto(oSocket, reinterpret_cast<const char*>(&pFrameData), SndFrameSize, 0, reinterpret_cast<sockaddr*>(&addrSend), sizeof(addrSend));
}
// ��ʼ������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void InitInstrumentCommInfo(m_oEnvironmentStruct* pEnv, m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pEnv == NULL)
	{
		return;
	}
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
	pEnv->m_pInstrumentCommInfo->m_uiDstIP = pCommInfo->m_uiDstIP;
	pEnv->m_pInstrumentCommInfo->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	pEnv->m_pInstrumentCommInfo->m_uiAimPort = pCommInfo->m_uiAimPort;
	pEnv->m_pInstrumentCommInfo->m_usHeartBeatReturnPort = pCommInfo->m_usHeartBeatReturnPort;
	pEnv->m_pInstrumentCommInfo->m_usHeadFramePort = pCommInfo->m_usHeadFramePort;
	pEnv->m_pInstrumentCommInfo->m_usIPSetReturnPort = pCommInfo->m_usIPSetReturnPort;
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
}
// ��������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void CreateInstrumentCommInfo(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	pEnv->m_pInstrumentCommInfo = new m_oInstrumentCommInfoStruct;
	InitializeCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
}
// �ͷ�����ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentCommInfo(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pInstrumentCommInfo != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
		delete pEnv->m_pInstrumentCommInfo;
	}
}

// ��ʼ������
MatrixServerDll_API void InitInstrumentHeartBeat(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
	// Դ��ַ
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_uiSrcIP = pEnv->m_pInstrumentCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_uiDstIP = pEnv->m_pInstrumentCommInfo->m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_uiAimPort = pEnv->m_pInstrumentCommInfo->m_uiAimPort;
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_usReturnPort = pEnv->m_pInstrumentCommInfo->m_usHeartBeatReturnPort;
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_usCommand = SendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_pHeartBeatFrame->m_oCommandStruct);
	// ��շ���֡������
	memset(&pEnv->m_pHeartBeatFrame->m_bySndFrameData, SndFrameBufInit, SndFrameSize);
	// ������������ּ���
	memset(&pEnv->m_pHeartBeatFrame->m_byCommandWord, SndFrameBufInit, CommandWordMaxNum);
	// ���������ָ���
	pEnv->m_pHeartBeatFrame->m_usCommandWordNum = 0;
	LeaveCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
}
// ��������֡��Ϣ�ṹ��
MatrixServerDll_API void CreateInstrumentHeartBeat(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pHeartBeatFrame = new m_oHeartBeatFrameStruct;
	InitializeCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
}
// �ͷ�����֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentHeartBeat(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pHeartBeatFrame != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
		delete pEnv->m_pHeartBeatFrame;
	}
}
// ��ʼ���װ�
MatrixServerDll_API void InitInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
	// ���ն˿�
	pEnv->m_pHeadFrame->m_oCommandStruct.m_usReturnPort = pEnv->m_pInstrumentCommInfo->m_usHeadFramePort;
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_pHeadFrame->m_oCommandStruct);
	// ��ս���֡������
	memset(&pEnv->m_pHeadFrame->m_byRcvFrameData, SndFrameBufInit, RcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
}
// �����װ�֡��Ϣ�ṹ��
MatrixServerDll_API void CreateInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pHeadFrame = new m_oHeadFrameStruct;
	InitializeCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
}
// �ͷ��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pHeadFrame != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
		delete pEnv->m_pHeadFrame;
	}
}
// ��ʼ��IP��ַ����
MatrixServerDll_API void InitInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
	// Դ��ַ
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_uiSrcIP = pEnv->m_pInstrumentCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_uiDstIP = pEnv->m_pInstrumentCommInfo->m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_uiAimPort = pEnv->m_pInstrumentCommInfo->m_uiAimPort;
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_usReturnPort = pEnv->m_pInstrumentCommInfo->m_usIPSetReturnPort;
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_oSecInstrumentCommInfo);
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_usCommand = SendSetCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_pIPSetFrame->m_oCommandStructSet);
	// ��շ���֡������
	memset(&pEnv->m_pIPSetFrame->m_bySndFrameData, SndFrameBufInit, SndFrameSize);
	// ���IP��ַ���������ּ���
	memset(&pEnv->m_pIPSetFrame->m_byCommandWord, SndFrameBufInit, CommandWordMaxNum);
	// IP��ַ���������ָ���
	pEnv->m_pIPSetFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_pIPSetFrame->m_oCommandStructReturn);
	// ��ս���֡������
	memset(&pEnv->m_pIPSetFrame->m_byRcvFrameData, SndFrameBufInit, RcvFrameSize);
	DeleteCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
}
// ����IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void CreateInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pIPSetFrame = new m_oIPSetFrameStruct;
	InitializeCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
}
// �ͷ�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pIPSetFrame != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
		delete pEnv->m_pIPSetFrame;
	}
}
// ��ʼ���̴߳����־λ
MatrixServerDll_API void InitThreadProcFlag(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pThreadProcFlag->m_oSecFlag);
	// ���������߳�ֹͣ��־λ
	pEnv->m_pThreadProcFlag->m_bProcHeartBeatStop = false;
	// �װ������߳�ֹͣ��־λ
	pEnv->m_pThreadProcFlag->m_bProcHeadFrameStop = false;
	// ����IP��ַ�����߳�ֹͣ��־λ
	pEnv->m_pThreadProcFlag->m_bProcIPSetStop = false;
	LeaveCriticalSection(&pEnv->m_pThreadProcFlag->m_oSecFlag);
}
// �����̴߳����־λ��Ϣ�ṹ��
MatrixServerDll_API void CreateThreadProcFlag(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pThreadProcFlag = new m_oThreadProcFlagStruct;
	InitializeCriticalSection(&pEnv->m_pThreadProcFlag->m_oSecFlag);
}
// �ͷ��̴߳����־λ��Ϣ�ṹ��
MatrixServerDll_API void FreeThreadProcFlag(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pThreadProcFlag != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pThreadProcFlag->m_oSecFlag);
		delete pEnv->m_pThreadProcFlag;
	}
}
// ��ʼ��ʵ��
MatrixServerDll_API void InitInstance(m_oEnvironmentStruct* pEnv, m_oInstrumentCommInfoStruct* pCommInfo)
{
	// ��������ͨѶ��Ϣ�ṹ��
	CreateInstrumentCommInfo(pEnv);
	// ��ʼ������ͨѶ��Ϣ�ṹ��
	InitInstrumentCommInfo(pEnv, pCommInfo);
	// ��������֡��Ϣ�ṹ��
	CreateInstrumentHeartBeat(pEnv);
	// ��ʼ������
	InitInstrumentHeartBeat(pEnv);
	// �����װ�֡��Ϣ�ṹ��
	CreateInstrumentHeadFrame(pEnv);
	// ��ʼ���װ�
	InitInstrumentHeadFrame(pEnv);
	// ����IP��ַ����֡��Ϣ�ṹ��
	CreateInstrumentIPSetFrame(pEnv);
	// ��ʼ��IP��ַ����
	InitInstrumentIPSetFrame(pEnv);
	// �����̴߳����־λ��Ϣ�ṹ��
	CreateThreadProcFlag(pEnv);
	// ��ʼ���̴߳����־λ
	InitThreadProcFlag(pEnv);
}
// �ͷ�ʵ����Դ
MatrixServerDll_API void FreeInstance(m_oEnvironmentStruct* pEnv)
{
	if (pEnv != NULL)
	{
		FreeInstrumentCommInfo(pEnv);
		FreeInstrumentHeartBeat(pEnv);
		FreeInstrumentHeadFrame(pEnv);
		FreeInstrumentIPSetFrame(pEnv);
		FreeThreadProcFlag(pEnv);
		delete pEnv;
		pEnv = NULL;
	}
}
// �����װ�֡
MatrixServerDll_API bool ParseInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	bool bReturn = false;
	EnterCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	bReturn = ParseInstrumentFrame(&pEnv->m_pHeadFrame->m_oCommandStruct, pEnv->m_pHeadFrame->m_byRcvFrameData);
	LeaveCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	return bReturn;
}
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API bool ParseInstrumentIPSetReturnFrame(m_oEnvironmentStruct* pEnv)
{
	bool bReturn = false;
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	bReturn = ParseInstrumentFrame(&pEnv->m_pIPSetFrame->m_oCommandStructReturn, pEnv->m_pIPSetFrame->m_byRcvFrameData);
	DeleteCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	return bReturn;
}
// ��������֡
MatrixServerDll_API void MakeInstrumentHeartBeatFrame(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
	MakeInstrumentFrame(&pEnv->m_pHeartBeatFrame->m_oCommandStruct, pEnv->m_pHeartBeatFrame->m_bySndFrameData, pEnv->m_pHeartBeatFrame->m_byCommandWord, pEnv->m_pHeartBeatFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
}
// ����IP��ַ����֡
MatrixServerDll_API void MakeInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	MakeInstrumentFrame(&pEnv->m_pIPSetFrame->m_oCommandStructSet, pEnv->m_pIPSetFrame->m_bySndFrameData, pEnv->m_pIPSetFrame->m_byCommandWord, pEnv->m_pIPSetFrame->m_usCommandWordNum);
	DeleteCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
}