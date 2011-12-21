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
// // ���ֽ��ַ���ת��Ϊ���ֽ��ַ���
// string WideCharToMultiChar(wstring str)
// {
// 	string return_value;
// 	//��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ֽڼ����
// 	LPCWSTR lpWideCharStr = str.c_str();
// 	int cchWideChar = (int)str.size();
// 	int len = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, cchWideChar, NULL, 0, NULL, NULL);
// 	char *buffer = new char[len+1];
// 	WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, cchWideChar, buffer, len, NULL, NULL);
// 	buffer[len] = '\0';
// 	//ɾ��������������ֵ
// 	return_value.append(buffer);
// 	delete []buffer;
// 	return return_value;
// }
// const char* ConvertCStringToConstCharPointer(CString str)
// {
// 	const char* pChar = NULL;
// 	char pach[2000];
// 	CStringW strw;
// 	wstring wstr;
// 	strw = str;
// 	wstr = strw;
// 	string mstring = WideCharToMultiChar(wstr);
// 	strcpy_s( pach, sizeof(pach), mstring.c_str());
// 	pChar = pach;
// 	return pChar;
// }
// ����ʵ����������ʵ��ָ��
MatrixServerDll_API m_oEnvironmentStruct* CreateInstance(void)
{
	m_oEnvironmentStruct* pEnv = new m_oEnvironmentStruct;
	pEnv->m_pConstVar = NULL;
	pEnv->m_pInstrumentCommInfo = NULL;
	pEnv->m_pHeartBeatFrame = NULL;
	pEnv->m_pHeadFrame = NULL;
	pEnv->m_pIPSetFrame = NULL;
	pEnv->m_pThreadProcFlag = NULL;
	return pEnv;
}
// У��֡��ͬ����
MatrixServerDll_API bool CheckInstrumentFrameHead(byte* pFrameData, m_oConstVarStruct* pConstVar)
{
	if (pFrameData == NULL)
	{
		return false;
	}
	for (int i=0; i<pConstVar->m_oFrameHeadSize; i++)
	{
		if (pFrameData[i] != pConstVar->m_pFrameHeadCheck[i])
		{
			return false;
		}
	}
	return true;
}
// ����֡��ͬ����
MatrixServerDll_API void MakeInstrumentFrameHead(byte* pFrameData, m_oConstVarStruct* pConstVar)
{
	if (pFrameData == NULL)
	{
		return;
	}
	for (int i=0; i<pConstVar->m_oFrameHeadSize; i++)
	{
		pFrameData[i] = pConstVar->m_pFrameHeadCheck[i];
	}
}
// ����֡���ݽ�������
MatrixServerDll_API void ResetInstrumentFramePacket(m_oInstrumentCommandStruct* pCommand, m_oConstVarStruct* pConstVar)
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
// 	if (pCommand->m_pbyADCSet != NULL)
// 	{
// 		memset(pCommand->m_pbyADCSet, pConstVar->m_oSndFrameBufInit, pConstVar->m_oADCSetCommandMaxByte);
// 	}
	// 0x18�������ݸ���
	pCommand->m_usADCSetNum = 0;
}
// �������豸ͨѶ����֡����
MatrixServerDll_API bool ParseInstrumentFrame(m_oInstrumentCommandStruct* pCommand, byte* pFrameData, m_oConstVarStruct* pConstVar)
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
	if (false == CheckInstrumentFrameHead(pFrameData, pConstVar))
	{
		return false;
	}
	iPos += pConstVar->m_oFrameHeadSize;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pCommand, pConstVar);
	// ԴIP��ַ
	memcpy(&pCommand->m_uiSrcIP, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
	iPos += pConstVar->m_oFramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pCommand->m_uiDstIP, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
	iPos += pConstVar->m_oFramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pCommand->m_usReturnPort, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
	iPos += pConstVar->m_oFramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pCommand->m_usCommand, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
	iPos += pConstVar->m_oFramePacketSize2B;
	// ����֡����

	while(true)
	{
		memcpy(&byCommandWord, &pFrameData[iPos], pConstVar->m_oFrameCmdSize1B);
		iPos += pConstVar->m_oFrameCmdSize1B;
		if (byCommandWord == pConstVar->m_oCmdSn)
		{
			memcpy(&pCommand->m_uiSN, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdHeadFrameTime)
		{
			memcpy(&pCommand->m_uiTimeHeadFrame, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLocalIPAddr)
		{
			memcpy(&pCommand->m_uiInstrumentIP, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLocalSysTime)
		{
			memcpy(&pCommand->m_uiSysTime, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLocalTimeFixedHigh)
		{
			memcpy(&pCommand->m_uiLocalTimeFixedHigh, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLocalTimeFixedLow)
		{
			memcpy(&pCommand->m_usLocalTimeFixedLow, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdADCDataReturnAddr)
		{
			memcpy(&pCommand->m_uiADCDataReturnAddr, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdADCDataReturnPort)
		{
			memcpy(&pCommand->m_usADCDataReturnPort, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnCmd, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_oCmdADCDataReturnPortLimit)
		{
			memcpy(&pCommand->m_usADCDataReturnPortLimitLow, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnPortLimitHigh, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_oCmdSetBroadCastPort)
		{
			memcpy(&pCommand->m_usSetBroadCastPort, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdFDUErrorCode)
		{
			memcpy(&pCommand->m_byFDUErrorCodeDataCount, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pCommand->m_byFDUErrorCodeCmdCount, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pCommand->m_byTimeStatus, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pCommand->m_byCtrlStatus, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
		}
		else if (byCommandWord == pConstVar->m_oCmdTBHigh)
		{
			memcpy(&pCommand->m_uiTBHigh, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdTbLow)
		{
			memcpy(&pCommand->m_usTBLow, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pCommand->m_usTBCtrl, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLAUXRoutOpenQuery)
		{
			memcpy(&pCommand->m_byLAUXRoutOpenQuery, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLAUXRoutOpenSet)
		{
			memcpy(&pCommand->m_byLAUXRoutOpenSet, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdTailRecSndTimeLow)
		{
			memcpy(&pCommand->m_usTailRecSndTimeLow, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdBroadCastPortSet)
		{
			memcpy(&pCommand->m_usBroadCastPortSet, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdADCSet)
		{
			memcpy(&pCommand->m_pbyADCSet[pCommand->m_usADCSetNum], &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
			pCommand->m_usADCSetNum += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdNetTime)
		{
			memcpy(&pCommand->m_uiNetTime, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLineTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLineA, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLineB, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLAUTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineA, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineB, &pFrameData[iPos], pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLAUXErrorCode1)
		{
			memcpy(&pCommand->m_byLAUXErrorCodeDataLineACount, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLineBCount, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLAUXLineACount, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLAUXLineBCount, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
		}
		else if (byCommandWord == pConstVar->m_oCmdLAUXErrorCode2)
		{
			memcpy(&pCommand->m_byLAUXErrorCodeCmdCount, &pFrameData[iPos], pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdReturnRout)
		{
			memcpy(&pCommand->m_uiRoutIP, &pFrameData[iPos], pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_oCmdEnd)
		{
			break;
		}
		else
		{
			iPos += pConstVar->m_oFramePacketSize4B;
		}
	}
	return true;
}
// �������豸ͨѶ֡
MatrixServerDll_API void MakeInstrumentFrame(m_oInstrumentCommandStruct* pCommand, byte* pFrameData, byte* pCommandWord, unsigned short usCommandWordNum, m_oConstVarStruct* pConstVar)
{
	if (pCommand == NULL)
	{
		return;
	}
	if (pFrameData == NULL)
	{
		return;
	}
	int iPos = 0;
	// ����֡��ͬ����
	MakeInstrumentFrameHead(pFrameData, pConstVar);
	iPos += pConstVar->m_oFrameHeadSize;
	// ԴIP��ַ
	memcpy(&pFrameData[iPos], &pCommand->m_uiSrcIP, pConstVar->m_oFramePacketSize4B);
	iPos += pConstVar->m_oFramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pFrameData[iPos], &pCommand->m_uiDstIP, pConstVar->m_oFramePacketSize4B);
	iPos += pConstVar->m_oFramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pFrameData[iPos], &pCommand->m_usReturnPort, pConstVar->m_oFramePacketSize2B);
	iPos += pConstVar->m_oFramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pFrameData[iPos], &pCommand->m_usCommand, pConstVar->m_oFramePacketSize2B);
	iPos += pConstVar->m_oFramePacketSize2B;
	// ��ʱ��
	iPos += pConstVar->m_oFramePacketSize4B;

	// ����֡����
	for (unsigned short i=0; i<usCommandWordNum; i++)
	{
		memcpy(&pFrameData[iPos], &pCommandWord[i], pConstVar->m_oFrameCmdSize1B);
		iPos += pConstVar->m_oFrameCmdSize1B;
		if (pCommandWord[i] == pConstVar->m_oCmdSn)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiSN, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdHeadFrameTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiTimeHeadFrame, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLocalIPAddr)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiInstrumentIP, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLocalSysTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiSysTime, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLocalTimeFixedHigh)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiLocalTimeFixedHigh, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLocalTimeFixedLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLocalTimeFixedLow, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdADCDataReturnAddr)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiADCDataReturnAddr, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdADCDataReturnPort)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPort, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnCmd, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdADCDataReturnPortLimit)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPortLimitLow, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPortLimitHigh, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdSetBroadCastPort)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usSetBroadCastPort, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdFDUErrorCode)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byFDUErrorCodeDataCount, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byFDUErrorCodeCmdCount, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byTimeStatus, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byCtrlStatus, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdTBHigh)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiTBHigh, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdTbLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usTBLow, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usTBCtrl, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLAUXRoutOpenQuery)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXRoutOpenQuery, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLAUXRoutOpenSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXRoutOpenSet, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdTailRecSndTimeLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usTailRecSndTimeLow, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdBroadCastPortSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usBroadCastPortSet, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdADCSet)
		{
			for(unsigned short j=0; j<pCommand->m_usADCSetNum; j+=pConstVar->m_oFramePacketSize4B)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_pbyADCSet[j], pConstVar->m_oFramePacketSize4B);
				iPos += pConstVar->m_oFramePacketSize4B;
			}
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdNetTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiNetTime, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLineTailRecTimeLAUX)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLineA, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLineB, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLAUTailRecTimeLAUX)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLAUXLineA, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLAUXLineB, pConstVar->m_oFramePacketSize2B);
			iPos += pConstVar->m_oFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLAUXErrorCode1)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLineACount, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLineBCount, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLAUXLineACount, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLAUXLineBCount, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize1B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdLAUXErrorCode2)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeCmdCount, pConstVar->m_oFramePacketSize1B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_oCmdReturnRout)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIP, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
		else
		{
			memset(&pFrameData[iPos], pConstVar->m_oSndFrameBufInit, pConstVar->m_oFramePacketSize4B);
			iPos += pConstVar->m_oFramePacketSize4B;
		}
	}
	pFrameData[iPos] = pConstVar->m_oCmdEnd;
}
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ
MatrixServerDll_API SOCKET CreateInstrumentSocket(unsigned short usPort, unsigned int uiIP)
{
	SOCKET oSocket = INVALID_SOCKET;
	sockaddr_in oAddr;
	oSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	oAddr.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	oAddr.sin_port = htons(usPort);
	oAddr.sin_addr.S_un.S_addr = uiIP;
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
MatrixServerDll_API void SetRcvBufferSize(SOCKET oSocket, int iRcvBufferSize)
{
	int iOptionLen = sizeof(int);
	int iReturn = setsockopt(oSocket, SOL_SOCKET, SO_RCVBUF,  reinterpret_cast<const char *>(&iRcvBufferSize), iOptionLen);
	if (iReturn == SOCKET_ERROR)
	{
	}
}
// ���ö˿ڷ��ͻ���������֡����
MatrixServerDll_API void SetSndBufferSize(SOCKET oSocket, int iSndBufferSize)
{
	int iOptionLen = sizeof(int);
	int iReturn = setsockopt(oSocket, SOL_SOCKET, SO_SNDBUF,  reinterpret_cast<const char *>(&iSndBufferSize), iOptionLen);
	if (iReturn == SOCKET_ERROR)
	{
	}
}
// �õ�������ջ������յ���֡����
MatrixServerDll_API DWORD GetFrameCount(SOCKET oSocket, int iRcvFrameSize)
{
	DWORD dwFrameCount = 0;
	// �õ�������ջ����������ֽ���
	ioctlsocket(oSocket, FIONREAD, &dwFrameCount);
	// �õ�֡����
	dwFrameCount = dwFrameCount / iRcvFrameSize;

	return dwFrameCount;
}
// �õ�֡����
MatrixServerDll_API bool GetFrameData(SOCKET oSocket, byte* pFrameData, int iRcvFrameSize)
{
	bool bReturn = false;
	sockaddr_in AddrFrom;
	int iSize = sizeof(AddrFrom);
	int iCount = recvfrom(oSocket, reinterpret_cast<char *>(pFrameData), iRcvFrameSize, 0, reinterpret_cast<sockaddr*>(&AddrFrom), &iSize);
	if(iCount == iRcvFrameSize)	//֡��С��ȷ
	{
		bReturn = true;
	}
	else
	{

	}
	return bReturn;
}
// ����֡
MatrixServerDll_API void SendFrame(SOCKET oSocket, byte* pFrameData,int iSndFrameSize, unsigned short usPort, unsigned int uiIP)
{
	// ����֡
	sockaddr_in addrSend;
	addrSend.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	addrSend.sin_port = htons(usPort);
	addrSend.sin_addr.S_un.S_addr = uiIP;
	sendto(oSocket, reinterpret_cast<const char*>(&pFrameData), iSndFrameSize, 0, reinterpret_cast<sockaddr*>(&addrSend), sizeof(addrSend));
}
// ����������Ϣ�ṹ��
MatrixServerDll_API void CreateConstVar(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	pEnv->m_pConstVar = new m_oConstVarStruct;
	pEnv->m_pConstVar->m_pFrameHeadCheck = NULL;
}
// ����INI�ļ�
MatrixServerDll_API void LoadIniFile(m_oConstVarStruct* pConstVar)
{
	CString strSection	= _T("");
	CString strSectionKey = _T("");
	CString strValue = _T("");
	CString strFilePath	= _T("");
	wchar_t strBuff[256];
	CString csTemp = _T("");
	int iDirectionNew = 0;
	int iDirectionOld = 0;
	int iTemp = 0;
	strFilePath = _T("..\\parameter\\MatrixServerDLL.ini");

	//��ȡini�ļ�����Ӧ�ֶε�����
	strSection = _T("֡��ʽ����");			// ��ȡ��ǰ����
	strSectionKey=_T("FrameHeadSize");		// ֡ͷ����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oFrameHeadSize = _ttoi(strValue);

	strSectionKey=_T("FrameHeadCheck");		// ͬ��֡ͷ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_pFrameHeadCheck = new byte[pConstVar->m_oFrameHeadSize];
	for (int i=0; i<pConstVar->m_oFrameHeadSize; i++)
	{
		iDirectionNew = strValue.Find(_T("0x"), iDirectionOld);
		iDirectionNew += 2;
		csTemp = strValue.Mid(iDirectionNew, 2);
		_stscanf_s(csTemp, _T("%x"), &iTemp, sizeof(int));
		pConstVar->m_pFrameHeadCheck[i] = iTemp;
		iDirectionOld = iDirectionNew;
	}
	strSectionKey=_T("FrameCmdSize1B");		// �����ֳ���1�ֽ�
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oFrameCmdSize1B = _ttoi(strValue);

	strSectionKey=_T("FramePacketSize1B");	// ���������1�ֽ�
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oFramePacketSize1B = _ttoi(strValue);

	strSectionKey=_T("FramePacketSize2B");	// ���������2�ֽ�
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oFramePacketSize2B = _ttoi(strValue);

	strSectionKey=_T("FramePacketSize4B");	// ���������4�ֽ�
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oFramePacketSize4B = _ttoi(strValue);

	strSectionKey=_T("ADCDataSize3B");		// ADC������ռ�ֽ���
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oADCDataSize3B = _ttoi(strValue);

	strSectionKey=_T("CommandWordMaxNum");	// �����ָ������ֵ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oCommandWordMaxNum = _ttoi(strValue);
	pConstVar->m_oADCSetCommandMaxByte = pConstVar->m_oCommandWordMaxNum * pConstVar->m_oFramePacketSize4B;
	strSectionKey=_T("SndFrameBufInit");	// ����֡��������ֵ�趨
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oSndFrameBufInit = iTemp;

	strSectionKey=_T("RcvFrameSize");		// ���յ���������֡֡����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oRcvFrameSize = _ttoi(strValue);

	strSectionKey=_T("SndFrameSize");		// ���͵���������֡֡����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	pConstVar->m_oSndFrameSize = _ttoi(strValue);

	/////////////////////////////////////////////////////////////////////////
	strSection = _T("���������豸����������");		// ��ȡ��ǰ����
	strSectionKey=_T("SendSetCmd");			// ������������
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oSendSetCmd = iTemp;

	strSectionKey=_T("SendQueryCmd");		// ���Ͳ�ѯ����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oSendQueryCmd = iTemp;

	strSectionKey=_T("SendADCCmd");			// ����ADC���������ط�����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oSendADCCmd = iTemp;

	strSectionKey=_T("CmdTBCtrl");			// TB��ʼ�ɼ����ؿ�������(TB_L��8λ)
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_oCmdTBCtrl, sizeof(unsigned int));

	strSectionKey=_T("CmdSn");				// ����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdSn = iTemp;

	strSectionKey=_T("CmdHeadFrameTime");	// �װ�ʱ��
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdHeadFrameTime = iTemp;

	strSectionKey=_T("CmdLocalIPAddr");		// ����IP��ַ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_oCmdLocalIPAddr, sizeof(byte));

	strSectionKey=_T("CmdLocalSysTime");	// ����ϵͳʱ��
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLocalSysTime = iTemp;

	strSectionKey=_T("CmdLocalTimeFixedHigh");	// ����ʱ��������λ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLocalTimeFixedHigh = iTemp;

	strSectionKey=_T("CmdLocalTimeFixedLow");	// ����ʱ��������λ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLocalTimeFixedLow = iTemp;

	strSectionKey=_T("CmdADCDataReturnAddr");	// �Զ����ݷ��ص�ַ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdADCDataReturnAddr = iTemp;

	strSectionKey=_T("CmdADCDataReturnPort");	// �Զ����ݷ��ض˿ں�����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdADCDataReturnPort = iTemp;

	strSectionKey=_T("CmdADCDataReturnPortLimit");	// �˿ڵ������޺�����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdADCDataReturnPortLimit = iTemp;

	strSectionKey=_T("CmdSetBroadCastPort");	// ��������ȴ��˿ں�����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdSetBroadCastPort = iTemp;

	strSectionKey=_T("CmdFDUErrorCode");		// ϵͳӲ��״̬����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdFDUErrorCode = iTemp;

	strSectionKey=_T("CmdTBHigh");				// TBʱ�̸�λ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdTBHigh = iTemp;

	strSectionKey=_T("CmdTbLow");				// TBʱ�̵�λ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdTbLow = iTemp;

	strSectionKey=_T("CmdLAUXRoutOpenQuery");	// work_ctrl ����վ����
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLAUXRoutOpenQuery = iTemp;

	strSectionKey=_T("CmdLAUXRoutOpenSet");		// ·�ɿ���
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLAUXRoutOpenSet = iTemp;

	strSectionKey=_T("CmdTailRecSndTimeLow");	// β������\����ʱ�̵�λ
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdTailRecSndTimeLow = iTemp;

	strSectionKey=_T("CmdBroadCastPortSet");	// �㲥����ȴ��˿�ƥ��
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdBroadCastPortSet = iTemp;

	strSectionKey=_T("CmdADCSet");				// ����ADC��������������
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdADCSet = iTemp;

	strSectionKey=_T("CmdNetTime");				// ����ʱ��
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdNetTime = iTemp;

	strSectionKey=_T("CmdLineTailRecTimeLAUX");	// ����վ����β������ʱ��
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLineTailRecTimeLAUX = iTemp;

	strSectionKey=_T("CmdLAUTailRecTimeLAUX");	// ����վ������β������ʱ��
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLAUTailRecTimeLAUX = iTemp;

	strSectionKey=_T("CmdLAUXErrorCode1");		// ����վ����1
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLAUXErrorCode1 = iTemp;

	strSectionKey=_T("CmdLAUXErrorCode2");		// ����վ����2
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLAUXErrorCode2 = iTemp;

	strSectionKey=_T("CmdLAUXSetRout");			// ����վ·�ɷ���
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdLAUXSetRout = iTemp;

	strSectionKey=_T("CmdReturnRout");			// ����·��
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdReturnRout = iTemp;

	strSectionKey=_T("CmdEnd");					// ���������������
	GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff),strFilePath);
	strValue = strBuff;
	_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
	pConstVar->m_oCmdEnd = iTemp;
}
// ��ʼ��������Ϣ�ṹ��
MatrixServerDll_API void InitConstVar(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	LoadIniFile(pEnv->m_pConstVar);
}
// �ͷų�����Ϣ�ṹ��
MatrixServerDll_API void FreeConstVar(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pConstVar != NULL)
	{
		if (pEnv->m_pConstVar->m_pFrameHeadCheck != NULL)
		{
			delete[] pEnv->m_pConstVar->m_pFrameHeadCheck;
		}
		delete pEnv->m_pConstVar;
	}
}
// ��������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void CreateInstrumentCommInfo(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	pEnv->m_pInstrumentCommInfo = new m_oInstrumentCommInfoStruct;
}
// �򿪳��������ļ�
MatrixServerDll_API void OpenAppIniXMLFile(m_oInstrumentCommInfoStruct* pCommInfo)
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = _T("msxml2.domdocument");
	BOOL bData = pCommInfo->m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

	oVariant = _T("..\\parameter\\MatrixLineApp.XML");
	bData = pCommInfo->m_oXMLDOMDocument.load(oVariant);
}
//����IP��ַ��������
MatrixServerDll_API void LoadIPSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	CString csSrcIP = _T("");
	CString csDstIP = _T("");
	// �ҵ�IP��ַ������
	strKey = _T("LineServerAppIPSetup");
	lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	// ���ֳ�����ͨѶ�ı���IP��ַ
	strKey = _T("IPForInstrument");
	csSrcIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
//	pCommInfo->m_uiSrcIP = inet_addr(ConvertCStringToConstCharPointer(csSrcIP));
	pCommInfo->m_uiSrcIP = inet_addr("192.168.0.19");
	strKey = _T("IPLCI");
	csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
//	pCommInfo->m_uiDstIP = inet_addr(ConvertCStringToConstCharPointer(csDstIP));
	pCommInfo->m_uiDstIP = inet_addr("255.255.255.255");
}
//���ض˿���������
MatrixServerDll_API void LoadPortSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�IP��ַ������
	strKey = _T("LineServerAppPortSetup");
	lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	strKey = _T("PortLCI");
	pCommInfo->m_uiAimPort = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForHeartBeat");
	pCommInfo->m_usHeartBeatReturnPort = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForHeadFrame");
	pCommInfo->m_usHeadFramePort = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForIPSet");
	pCommInfo->m_usIPSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
}
//�������ݻ�������С����
MatrixServerDll_API void LoadBufferSizeSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ����ݻ�������С������
	strKey = _T("LineServerAppBufferSizeSetup");
	lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	strKey = _T("InstrumentCountAll");
	pCommInfo->m_uiInstrumentNum = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
}
// �رճ��������ļ�
MatrixServerDll_API void CloseAppIniXMLFile(m_oInstrumentCommInfoStruct* pCommInfo)
{
	pCommInfo->m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}
//���ز��߷�����������������
MatrixServerDll_API void LoadLineServerAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	// �򿪳��������ļ�
	OpenAppIniXMLFile(pCommInfo);

	//����IP��ַ��������
	LoadIPSetupData(pCommInfo);
	//���ض˿���������
	LoadPortSetupData(pCommInfo);
	//�������ݻ�������С����
	LoadBufferSizeSetupData(pCommInfo);

	// �رճ��������ļ�
	CloseAppIniXMLFile(pCommInfo);
}
// ��ʼ������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void InitInstrumentCommInfo(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	LoadLineServerAppSetupData(pEnv->m_pInstrumentCommInfo);
// 	pEnv->m_pInstrumentCommInfo->m_uiDstIP = pCommInfo->m_uiDstIP;
// 	pEnv->m_pInstrumentCommInfo->m_uiSrcIP = pCommInfo->m_uiSrcIP;
// 	pEnv->m_pInstrumentCommInfo->m_uiAimPort = pCommInfo->m_uiAimPort;
// 	pEnv->m_pInstrumentCommInfo->m_usHeartBeatReturnPort = pCommInfo->m_usHeartBeatReturnPort;
// 	pEnv->m_pInstrumentCommInfo->m_usHeadFramePort = pCommInfo->m_usHeadFramePort;
// 	pEnv->m_pInstrumentCommInfo->m_usIPSetReturnPort = pCommInfo->m_usIPSetReturnPort;
}
// �ͷ�����ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentCommInfo(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pInstrumentCommInfo != NULL)
	{
		delete pEnv->m_pInstrumentCommInfo;
	}
}
// ��������֡��Ϣ�ṹ��
MatrixServerDll_API void CreateInstrumentHeartBeat(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pHeartBeatFrame = new m_oHeartBeatFrameStruct;
	InitializeCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
	pEnv->m_pHeartBeatFrame->m_pbySndFrameData = NULL;
	pEnv->m_pHeartBeatFrame->m_pbyCommandWord = NULL;
}
// ��ʼ������
MatrixServerDll_API void InitInstrumentHeartBeat(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
	// Դ��ַ
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_uiSrcIP = pEnv->m_pInstrumentCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_uiDstIP = pEnv->m_pInstrumentCommInfo->m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_uiAimPort = pEnv->m_pInstrumentCommInfo->m_uiAimPort;
	// �������ض˿�
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_usReturnPort = pEnv->m_pInstrumentCommInfo->m_usHeartBeatReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_usCommand = pEnv->m_pConstVar->m_oSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_pHeartBeatFrame->m_oCommandStruct, pEnv->m_pConstVar);
	// ��շ���֡������
	pEnv->m_pHeartBeatFrame->m_pbySndFrameData = new byte[pEnv->m_pConstVar->m_oSndFrameSize];
	memset(pEnv->m_pHeartBeatFrame->m_pbySndFrameData, pEnv->m_pConstVar->m_oSndFrameBufInit, pEnv->m_pConstVar->m_oSndFrameSize);
	// ������������ּ���
	pEnv->m_pHeartBeatFrame->m_pbyCommandWord = new byte[pEnv->m_pConstVar->m_oCommandWordMaxNum];
	memset(pEnv->m_pHeartBeatFrame->m_pbyCommandWord, pEnv->m_pConstVar->m_oSndFrameBufInit, pEnv->m_pConstVar->m_oCommandWordMaxNum);
	// ���������ָ���
	pEnv->m_pHeartBeatFrame->m_usCommandWordNum = 0;
	LeaveCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
}
// �ͷ�����֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentHeartBeat(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pHeartBeatFrame != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
		if (pEnv->m_pHeartBeatFrame->m_pbySndFrameData != NULL)
		{
			delete[] pEnv->m_pHeartBeatFrame->m_pbySndFrameData;
		}
		if (pEnv->m_pHeartBeatFrame->m_pbyCommandWord != NULL)
		{
			delete[] pEnv->m_pHeartBeatFrame->m_pbyCommandWord;
		}
		delete pEnv->m_pHeartBeatFrame;
	}
}
// �����װ�֡��Ϣ�ṹ��
MatrixServerDll_API void CreateInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pHeadFrame = new m_oHeadFrameStruct;
	InitializeCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	pEnv->m_pHeadFrame->m_pbyRcvFrameData = NULL;
}
// ��ʼ���װ�
MatrixServerDll_API void InitInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	// �װ����ջ�����֡���趨Ϊ��������
	pEnv->m_pHeadFrame->m_uiRcvFrameNum = pEnv->m_pInstrumentCommInfo->m_uiInstrumentNum;
	// ���ն˿�
	pEnv->m_pHeadFrame->m_oCommandStruct.m_usReturnPort = pEnv->m_pInstrumentCommInfo->m_usHeadFramePort;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_pHeadFrame->m_oCommandStruct, pEnv->m_pConstVar);
	// ��ս���֡������
	pEnv->m_pHeadFrame->m_pbyRcvFrameData = new byte[pEnv->m_pConstVar->m_oRcvFrameSize];
	memset(pEnv->m_pHeadFrame->m_pbyRcvFrameData, pEnv->m_pConstVar->m_oSndFrameBufInit, pEnv->m_pConstVar->m_oRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
}
// �ͷ��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentHeadFrame(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pHeadFrame != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
		if (pEnv->m_pHeadFrame->m_pbyRcvFrameData != NULL)
		{
			delete[] pEnv->m_pHeadFrame->m_pbyRcvFrameData;
		}
		delete pEnv->m_pHeadFrame;
	}
}
// ����IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void CreateInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pIPSetFrame = new m_oIPSetFrameStruct;
	InitializeCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	pEnv->m_pIPSetFrame->m_pbySndFrameData = NULL;
	pEnv->m_pIPSetFrame->m_pbyCommandWord = NULL;
	pEnv->m_pIPSetFrame->m_pbyRcvFrameData = NULL;
}
// ��ʼ��IP��ַ����
MatrixServerDll_API void InitInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	// Դ��ַ
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_uiSrcIP = pEnv->m_pInstrumentCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_uiDstIP = pEnv->m_pInstrumentCommInfo->m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_uiAimPort = pEnv->m_pInstrumentCommInfo->m_uiAimPort;
	// IP��ַ���÷��ͻ�����֡���趨Ϊ��������
	pEnv->m_pIPSetFrame->m_uiSndFrameNum = pEnv->m_pInstrumentCommInfo->m_uiInstrumentNum;
	// IP��ַ����Ӧ����ջ�����֡���趨Ϊ��������
	pEnv->m_pIPSetFrame->m_uiRcvFrameNum = pEnv->m_pInstrumentCommInfo->m_uiInstrumentNum;
	// IP��ַ���÷��ض˿�
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_usReturnPort = pEnv->m_pInstrumentCommInfo->m_usIPSetReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pEnv->m_pIPSetFrame->m_oCommandStructSet.m_usCommand = pEnv->m_pConstVar->m_oSendSetCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_pIPSetFrame->m_oCommandStructSet, pEnv->m_pConstVar);
	// ��շ���֡������
	pEnv->m_pIPSetFrame->m_pbySndFrameData = new byte[pEnv->m_pConstVar->m_oSndFrameSize];
	memset(pEnv->m_pIPSetFrame->m_pbySndFrameData, pEnv->m_pConstVar->m_oSndFrameBufInit, pEnv->m_pConstVar->m_oSndFrameSize);
	// ���IP��ַ���������ּ���
	pEnv->m_pIPSetFrame->m_pbyCommandWord = new byte[pEnv->m_pConstVar->m_oCommandWordMaxNum];
	memset(pEnv->m_pIPSetFrame->m_pbyCommandWord, pEnv->m_pConstVar->m_oSndFrameBufInit, pEnv->m_pConstVar->m_oCommandWordMaxNum);
	// IP��ַ���������ָ���
	pEnv->m_pIPSetFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pEnv->m_pIPSetFrame->m_oCommandStructReturn, pEnv->m_pConstVar);
	// ��ս���֡������
	pEnv->m_pIPSetFrame->m_pbyRcvFrameData = new byte[pEnv->m_pConstVar->m_oRcvFrameSize];
	memset(pEnv->m_pIPSetFrame->m_pbyRcvFrameData, pEnv->m_pConstVar->m_oSndFrameBufInit, pEnv->m_pConstVar->m_oRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
}
// �ͷ�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pIPSetFrame != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
		if (pEnv->m_pIPSetFrame->m_pbySndFrameData != NULL)
		{
			delete[] pEnv->m_pIPSetFrame->m_pbySndFrameData;
		}
		if (pEnv->m_pIPSetFrame->m_pbyCommandWord != NULL)
		{
			delete[] pEnv->m_pIPSetFrame->m_pbyCommandWord;
		}
		if (pEnv->m_pIPSetFrame->m_pbyRcvFrameData != NULL)
		{
			delete[] pEnv->m_pIPSetFrame->m_pbyRcvFrameData;
		}
		delete pEnv->m_pIPSetFrame;
	}
}
// �����̴߳����־λ��Ϣ�ṹ��
MatrixServerDll_API void CreateThreadProcFlag(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pThreadProcFlag = new m_oThreadProcFlagStruct;
	InitializeCriticalSection(&pEnv->m_pThreadProcFlag->m_oSecFlag);
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
// �ͷ��̴߳����־λ��Ϣ�ṹ��
MatrixServerDll_API void FreeThreadProcFlag(m_oEnvironmentStruct* pEnv)
{
	if (pEnv->m_pThreadProcFlag != NULL)
	{
		DeleteCriticalSection(&pEnv->m_pThreadProcFlag->m_oSecFlag);
		delete pEnv->m_pThreadProcFlag;
	}
}
// ���������������˿�
MatrixServerDll_API void CreateAndSetHeartBeatSocket(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
	// �����׽���
	pEnv->m_pHeartBeatFrame->m_oHeartBeatSocket = CreateInstrumentSocket(pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_usReturnPort, pEnv->m_pHeartBeatFrame->m_oCommandStruct.m_uiSrcIP);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pEnv->m_pHeartBeatFrame->m_oHeartBeatSocket);
	LeaveCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
}
// �����������װ��˿�
MatrixServerDll_API void CreateAndSetHeadFrameSocket(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	// �����׽���
	pEnv->m_pHeadFrame->m_oHeadFrameSocket = CreateInstrumentSocket(pEnv->m_pHeadFrame->m_oCommandStruct.m_usReturnPort, pEnv->m_pHeadFrame->m_oCommandStruct.m_uiSrcIP);
	// ���ý��ջ�����
	SetRcvBufferSize(pEnv->m_pHeadFrame->m_oHeadFrameSocket, pEnv->m_pHeadFrame->m_uiRcvFrameNum * pEnv->m_pConstVar->m_oRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
}
// ����������IP��ַ���ö˿�
MatrixServerDll_API void CreateAndSetIPSetFrameSocket(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	// �����׽���
	pEnv->m_pIPSetFrame->m_oIPSetFrameSocket = CreateInstrumentSocket(pEnv->m_pIPSetFrame->m_oCommandStructSet.m_usReturnPort, pEnv->m_pIPSetFrame->m_oCommandStructSet.m_uiSrcIP);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket);
	// ���÷��ͻ�����
	SetSndBufferSize(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket, pEnv->m_pIPSetFrame->m_uiSndFrameNum * pEnv->m_pConstVar->m_oSndFrameSize);
	// ���ý��ջ�������С
	SetRcvBufferSize(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket, pEnv->m_pIPSetFrame->m_uiRcvFrameNum * pEnv->m_pConstVar->m_oRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
}
// ��ʼ��ʵ��
MatrixServerDll_API void InitInstance(m_oEnvironmentStruct* pEnv)
{
	// ����������Ϣ�ṹ��
	CreateConstVar(pEnv);
	// ��ʼ��������Ϣ�ṹ��
	InitConstVar(pEnv);
	// ��������ͨѶ��Ϣ�ṹ��
	CreateInstrumentCommInfo(pEnv);
	// ��ʼ������ͨѶ��Ϣ�ṹ��
	InitInstrumentCommInfo(pEnv);
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
	// ���������������˿�
	CreateAndSetHeartBeatSocket(pEnv);
	// �����������װ��˿�
	CreateAndSetHeadFrameSocket(pEnv);
	// ����������IP��ַ���ö˿�
	CreateAndSetIPSetFrameSocket(pEnv);
}
// �ͷ�ʵ����Դ
MatrixServerDll_API void FreeInstance(m_oEnvironmentStruct* pEnv)
{
	if (pEnv != NULL)
	{
		FreeConstVar(pEnv);
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
	bReturn = ParseInstrumentFrame(&pEnv->m_pHeadFrame->m_oCommandStruct, pEnv->m_pHeadFrame->m_pbyRcvFrameData,
		pEnv->m_pConstVar);
	LeaveCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	return bReturn;
}
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API bool ParseInstrumentIPSetReturnFrame(m_oEnvironmentStruct* pEnv)
{
	bool bReturn = false;
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	bReturn = ParseInstrumentFrame(&pEnv->m_pIPSetFrame->m_oCommandStructReturn, pEnv->m_pIPSetFrame->m_pbyRcvFrameData, pEnv->m_pConstVar);
	LeaveCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	return bReturn;
}
// ��������֡
MatrixServerDll_API void MakeInstrumentHeartBeatFrame(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
	MakeInstrumentFrame(&pEnv->m_pHeartBeatFrame->m_oCommandStruct, pEnv->m_pHeartBeatFrame->m_pbySndFrameData,
		pEnv->m_pHeartBeatFrame->m_pbyCommandWord, pEnv->m_pHeartBeatFrame->m_usCommandWordNum, pEnv->m_pConstVar);
	LeaveCriticalSection(&pEnv->m_pHeartBeatFrame->m_oSecHeartBeat);
}
// ����IP��ַ����֡
MatrixServerDll_API void MakeInstrumentIPSetFrame(m_oEnvironmentStruct* pEnv)
{
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	MakeInstrumentFrame(&pEnv->m_pIPSetFrame->m_oCommandStructSet, pEnv->m_pIPSetFrame->m_pbySndFrameData, 
		pEnv->m_pIPSetFrame->m_pbyCommandWord, pEnv->m_pIPSetFrame->m_usCommandWordNum, pEnv->m_pConstVar);
	LeaveCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
}