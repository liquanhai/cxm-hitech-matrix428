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
	m_oEnvironmentStruct* ptr = new m_oEnvironmentStruct;
	return ptr;
}
// �ͷ�ʵ����Դ
MatrixServerDll_API void FreeInstance(m_oEnvironmentStruct* ptr)
{
	if (ptr != NULL)
	{
		delete ptr;
		ptr = NULL;
	}
}
// У��֡��ͬ����
MatrixServerDll_API bool CheckInstrumentFrameHead(byte* pFrameData)
{
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
	byte byFrameHeadCheck[] = FrameHeadCheck;
	for (int i=0; i<FrameHeadSize; i++)
	{
		pFrameData[i] = byFrameHeadCheck[i];
	}
}
// ����֡���ݽ�������
MatrixServerDll_API void ResetInstrumentFramePacket(m_oInstrumentCommandStruct* pCommand)
{
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
		else if (pCommandWord[i] == CmdEnd)
		{
			break;
		}
		else
		{
			memset(&pFrameData[iPos], SndFrameBufInit, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
	}
}
// ����֡��ͨѶ��Ϣ
MatrixServerDll_API void ResetInstrumentFrameComm(m_oInstrumentCommandStruct* pCommand, m_oEnvironmentStruct* pEnv)
{
	// Դ��ַ
	pCommand->m_csSrcIP = pEnv->m_csSrcIP;
	pCommand->m_uiSrcIP = pEnv->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pCommand->m_csDstIP = pEnv->m_csDstIP;
	pCommand->m_uiDstIP = pEnv->m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	pCommand->m_uiAimPort = pEnv->m_uiAimPort;
}
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ
MatrixServerDll_API BOOL CreateInstrumentSocket(m_oInstrumentCommandStruct* pCommand, CSocket* pCSocket)
{
	BOOL bReturn = FALSE;
	// ��������˿�
	bReturn = pCSocket->Create(pCommand->m_usReturnPort, SOCK_DGRAM, pCommand->m_csSrcIP);
	pCSocket->Bind(pCommand->m_usReturnPort,pCommand->m_csSrcIP);
	return bReturn;
}
// ���ù㲥ģʽ
MatrixServerDll_API BOOL SetInstrumentSocketBroadCast(CSocket* pCSocket)
{
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	return pCSocket->SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
}
// ���ö˿ڽ��ջ���������֡����
MatrixServerDll_API BOOL SetRcvBufferSize(CSocket* pCSocket, int iFrameCount)
{
	int iOptionValue = iFrameCount * RcvFrameSize;
	int iOptionLen = sizeof(int);
	return pCSocket->SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
}
// ���ö˿ڷ��ͻ���������֡����
MatrixServerDll_API BOOL SetSndBufferSize(CSocket* pCSocket, int iFrameCount)
{
	int iOptionValue = iFrameCount * SndFrameSize;
	int iOptionLen = sizeof(int);
	return pCSocket->SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
}
// �õ�������ջ������յ���֡����
MatrixServerDll_API DWORD GetFrameCount(CSocket* pCSocket)
{
	DWORD dwFrameCount = 0;

	// �õ�������ջ����������ֽ���
	pCSocket->IOCtl(FIONREAD, &dwFrameCount);
	// �õ�֡����
	dwFrameCount = dwFrameCount / RcvFrameSize;

	return dwFrameCount;
}
// �õ�֡����
MatrixServerDll_API BOOL GetFrameData(CSocket* pCSocket, byte* pFrameData)
{
	BOOL bReturn = FALSE;
	// �õ�֡����
	int iCount = pCSocket->Receive(pFrameData, RcvFrameSize);
	if(iCount == RcvFrameSize)	//֡��С��ȷ
	{
		bReturn = TRUE;
	}
	return bReturn;
}
// ��������IP��ַ����֡
MatrixServerDll_API BOOL SendFrame(CSocket* pCSocket, byte* pFrameData, unsigned int uiPort, CString strIP)
{
	BOOL bReturn = FALSE;
	// ����֡
	int iCount = pCSocket->SendTo(pFrameData, SndFrameSize, uiPort, strIP);
	if(iCount == SndFrameSize)	//֡��С��ȷ
	{
		bReturn = TRUE;
	}
	return bReturn;
}
// ��ʼ������
MatrixServerDll_API void InitInstrumentHeartBeat(m_oEnvironmentStruct* pEnv)
{
	// ����֡��ͨѶ��Ϣ
	ResetInstrumentFrameComm(&pEnv->m_oHeartBeatFrame.m_oCommandStruct, pEnv);
	// Ӧ��˿�
	pEnv->m_oHeartBeatFrame.m_oCommandStruct.m_usReturnPort = pEnv->m_usHeartBeatReturnPort;
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pEnv->m_oHeartBeatFrame.m_oCommandStruct.m_usCommand = SendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_oHeartBeatFrame.m_oCommandStruct);
	// ��շ���֡������
	memset(&pEnv->m_oHeartBeatFrame.m_bySndFrameData, SndFrameBufInit, SndFrameSize);
	// ������������ּ���
	memset(&pEnv->m_oHeartBeatFrame.m_byCommandWord, SndFrameBufInit, CommandWordMaxNum);
	// ���������ָ���
	pEnv->m_oHeartBeatFrame.m_usCommandWordNum = 0;
}
// ��ʼ���װ�
MatrixServerDll_API void InitInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	// ����֡��ͨѶ��Ϣ
	ResetInstrumentFrameComm(&pEnv->m_oHeadFrame.m_oCommandStruct, pEnv);
	// Ӧ��˿�
	pEnv->m_oHeadFrame.m_oCommandStruct.m_usReturnPort = pEnv->m_usHeadFramePort;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_oHeadFrame.m_oCommandStruct);
	// ��շ���֡������
	memset(&pEnv->m_oHeadFrame.m_byRcvFrameData, SndFrameBufInit, RcvFrameSize);
}
// ��ʼ��IP��ַ����
MatrixServerDll_API void InitInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	// ����֡��ͨѶ��Ϣ
	ResetInstrumentFrameComm(&pEnv->m_oIPSetFrame.m_oCommandStruct, pEnv);
	// Ӧ��˿�
	pEnv->m_oIPSetFrame.m_oCommandStruct.m_usReturnPort = pEnv->m_usIPSetReturnPort;
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pEnv->m_oIPSetFrame.m_oCommandStruct.m_usCommand = SendSetCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_oIPSetFrame.m_oCommandStruct);
	// ��շ���֡������
	memset(&pEnv->m_oIPSetFrame.m_bySndFrameData, SndFrameBufInit, SndFrameSize);
	// ������������ּ���
	memset(&pEnv->m_oIPSetFrame.m_byCommandWord, SndFrameBufInit, CommandWordMaxNum);
	// ���������ָ���
	pEnv->m_oIPSetFrame.m_usCommandWordNum = 0;
}
// ��ʼ��IP��ַ����Ӧ��
MatrixServerDll_API void InitInstrumentIPSetReturnFrame(m_oEnvironmentStruct* pEnv)
{
	// ����֡��ͨѶ��Ϣ
	ResetInstrumentFrameComm(&pEnv->m_oIPSetReturnFrame.m_oCommandStruct, pEnv);
	// Ӧ��˿�
	pEnv->m_oIPSetReturnFrame.m_oCommandStruct.m_usReturnPort = pEnv->m_usHeadFramePort;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_oIPSetReturnFrame.m_oCommandStruct);
	// ��շ���֡������
	memset(&pEnv->m_oIPSetReturnFrame.m_byRcvFrameData, SndFrameBufInit, RcvFrameSize);
}
// �����װ�֡
MatrixServerDll_API bool ParseInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	return ParseInstrumentFrame(&pEnv->m_oHeadFrame.m_oCommandStruct, pEnv->m_oHeadFrame.m_byRcvFrameData);
}
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API bool ParseInstrumentIPSetReturnFrame(m_oEnvironmentStruct* pEnv)
{
	return ParseInstrumentFrame(&pEnv->m_oIPSetReturnFrame.m_oCommandStruct, pEnv->m_oHeadFrame.m_byRcvFrameData);
}
// ��������֡
MatrixServerDll_API void MakeInstrumentHeartBeatFrame(m_oEnvironmentStruct* pEnv)
{
	MakeInstrumentFrame(&pEnv->m_oHeartBeatFrame.m_oCommandStruct, pEnv->m_oHeartBeatFrame.m_bySndFrameData, pEnv->m_oHeartBeatFrame.m_byCommandWord, pEnv->m_oHeartBeatFrame.m_usCommandWordNum);
}
// ����IP��ַ����֡
MatrixServerDll_API void MakeInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	MakeInstrumentFrame(&pEnv->m_oIPSetFrame.m_oCommandStruct, pEnv->m_oIPSetFrame.m_bySndFrameData, pEnv->m_oIPSetFrame.m_byCommandWord, pEnv->m_oIPSetFrame.m_usCommandWordNum);
}
