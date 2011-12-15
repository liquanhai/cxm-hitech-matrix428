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
// ����֡���ݽ�������
MatrixServerDll_API void ResetInstrumentFrame(m_oInstrumentCommand* pCommand)
{
	// Դ��ַ
	pCommand->m_uiSrcIP = 0;
	// Ŀ�ĵ�ַ
	pCommand->m_uiDstIP = 0;
	// �˿�
	pCommand->m_usAimPort = 0;
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pCommand->m_usCommand = 0;
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
}
// �������豸ͨѶ����֡����
MatrixServerDll_API bool ParseInstrumentFrame(m_oInstrumentCommand* pCommand)
{
	unsigned char	byCommandWord = 0;
	int iPos = 0;
	// У��֡��ͬ����
	if (false == CheckInstrumentFrameHead(pCommand->m_byRcvFrameData))
	{
		return false;
	}
	iPos += FrameHeadSize;
	// ����֡���ݽ�������
	ResetInstrumentFrame(pCommand);
	// ԴIP��ַ
	memcpy(&pCommand->m_uiSrcIP, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pCommand->m_uiDstIP, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pCommand->m_usAimPort, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pCommand->m_usCommand, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����֡����

	while(true)
	{
		memcpy(&byCommandWord, &pCommand->m_byRcvFrameData[iPos], FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		if (byCommandWord == CmdSn)
		{
			memcpy(&pCommand->m_uiSN, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdHeadFrameTime)
		{
			memcpy(&pCommand->m_uiTimeHeadFrame, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLocalIPAddr)
		{
			memcpy(&pCommand->m_uiInstrumentIP, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLocalSysTime)
		{
			memcpy(&pCommand->m_uiSysTime, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLocalTimeFixedHigh)
		{
			memcpy(&pCommand->m_uiLocalTimeFixedHigh, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLocalTimeFixedLow)
		{
			memcpy(&pCommand->m_usLocalTimeFixedLow, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdADCDataReturnAddr)
		{
			memcpy(&pCommand->m_uiADCDataReturnAddr, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdADCDataReturnPort)
		{
			memcpy(&pCommand->m_usADCDataReturnPort, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnCmd, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdADCDataReturnPortLimit)
		{
			memcpy(&pCommand->m_usADCDataReturnPortLimitLow, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnPortLimitHigh, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdSetBroadCastPort)
		{
			memcpy(&pCommand->m_usSetBroadCastPort, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdFDUErrorCode)
		{
			memcpy(&pCommand->m_byFDUErrorCodeDataCount, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byFDUErrorCodeCmdCount, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byTimeStatus, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byCtrlStatus, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
		}
		else if (byCommandWord == CmdTBHigh)
		{
			memcpy(&pCommand->m_uiTBHigh, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdTbLow)
		{
			memcpy(&pCommand->m_usTBLow, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usTBCtrl, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdLAUXRoutOpenQuery)
		{
			memcpy(&pCommand->m_byLAUXRoutOpenQuery, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLAUXRoutOpenSet)
		{
			memcpy(&pCommand->m_byLAUXRoutOpenSet, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdTailRecSndTimeLow)
		{
			memcpy(&pCommand->m_usTailRecSndTimeLow, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdBroadCastPortSet)
		{
			memcpy(&pCommand->m_usBroadCastPortSet, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdNetTime)
		{
			memcpy(&pCommand->m_uiNetTime, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdLineTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLineA, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLineB, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdLAUTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineA, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineB, &pCommand->m_byRcvFrameData[iPos], FramePacketSize2B);
			iPos += FramePacketSize2B;
		}
		else if (byCommandWord == CmdLAUXErrorCode1)
		{
			memcpy(&pCommand->m_byLAUXErrorCodeDataLineACount, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLineBCount, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLAUXLineACount, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLAUXLineBCount, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize1B;
		}
		else if (byCommandWord == CmdLAUXErrorCode2)
		{
			memcpy(&pCommand->m_byLAUXErrorCodeCmdCount, &pCommand->m_byRcvFrameData[iPos], FramePacketSize1B);
			iPos += FramePacketSize4B;
		}
		else if (byCommandWord == CmdReturnRout)
		{
			memcpy(&pCommand->m_uiRoutIP, &pCommand->m_byRcvFrameData[iPos], FramePacketSize4B);
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