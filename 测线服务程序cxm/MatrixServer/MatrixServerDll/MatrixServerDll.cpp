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
// ���ֽ��ַ���ת��Ϊ���ֽ��ַ���
string WideCharToMultiChar(wstring str)
{
	string return_value;
	//��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ֽڼ����
	LPCWSTR lpWideCharStr = str.c_str();
	int iWideCharSize = (int)str.size();
	int len = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, iWideCharSize, NULL, 0, NULL, NULL);
	char *buffer = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, iWideCharSize, buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ
	return_value.append(buffer);
	delete []buffer;
	return return_value;
}
// ��������Ϊstring�����Ǳ�׼C֧�ֵ�����
MATRIXSERVERDLL_API string ConvertCStrToStr(CString str)
{
	CStringW strw;
	wstring wstr;
	strw = str;
	wstr = strw;
	string mstring = WideCharToMultiChar(wstr);
	return mstring;
}
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
	pEnv->m_pLogOutPut = NULL;
	return pEnv;
}
// ������־����ṹ��
MatrixServerDll_API m_oLogOutPutStruct* CreateLogOutPut()
{
	m_oLogOutPutStruct* pLogOutPut = NULL;
	pLogOutPut = new m_oLogOutPutStruct;
	InitializeCriticalSection(&pLogOutPut->m_oSecLogFile);
	pLogOutPut->m_pFile = NULL;
	pLogOutPut->m_uiErrorCount = 0;
	return pLogOutPut;
}
// ����־����ļ�
MatrixServerDll_API void OpenLogOutPutFile(m_oLogOutPutStruct* pLogOutPut)
{
	if (pLogOutPut == NULL)
	{
		return;
	}
	CString str = _T("");
	CString csSaveLogFilePath = _T("");
	SYSTEMTIME  sysTime;
	errno_t err;
	// ��������������־�ļ���
	CreateDirectory(LogFolderPath, NULL);
	csSaveLogFilePath += LogFolderPath;
	GetLocalTime(&sysTime);
	str.Format(_T("\\%04d��%02d��%02d��%02dʱ%02d��%02d��.log"),sysTime.wYear, sysTime.wMonth, 
		sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	csSaveLogFilePath += str;
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	err = fopen_s(&pLogOutPut->m_pFile, ConvertCStrToStr(csSaveLogFilePath).c_str(), "wt+, ccs=UNICODE");
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// ���뵽��־�������
MatrixServerDll_API void AddMsgToLogOutPutList(m_oLogOutPutStruct* pLogOutPut = NULL, 
												byte byErrorType = LogType, 
												unsigned int uiErrorCode = 0, 
												string pFuncName = "", 
												string pVarName = "")
{
	CString cstr = _T("");
	CString strOutPut = _T("");
	string str = "";
	string strTemp = "";
	SYSTEMTIME  sysTime;
	if (pLogOutPut == NULL)
	{
		return;
	}
	if (OutPutSelect == OutPutRelease)
	{
		if (byErrorType != ErrorType)
		{
			return;
		}
	}
	if (pLogOutPut->m_uiErrorCount > OutPutLogErrorLimit)
	{
		return;
	}
	GetLocalTime(&sysTime);
	cstr.Format(_T("%04d��%02d��%02d�� %02d:%02d:%02d:%03d\t"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	if (byErrorType == LogType)
	{
		strOutPut += _T("Log\t");
	}
	else if (byErrorType == WarningType)
	{
		strOutPut += _T("Warning\t");
	}
	else if (byErrorType == ErrorType)
	{
		strOutPut += _T("Error\t");
		cstr.Format(_T("ErrorCode = %d\t"), uiErrorCode);
	}
	else if (byErrorType == ExpandType)
	{
		strOutPut += _T("ExpandType\t");
	}
	strOutPut += cstr;
	str = ConvertCStrToStr(strOutPut);
	if (pFuncName.empty() == false)
	{
		strTemp = "�������е�������";
		str += strTemp;
		str += pFuncName;
		str += '\t';
	}
	if (pVarName.empty() == false)
	{
		strTemp = "��־��Ϣ��";
		str += strTemp;
		str += pVarName;
	}
	str += '\r';
	str += '\n';
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	pLogOutPut->m_oLogOutputList.push_back(str);
	if (byErrorType == ErrorType)
	{
		pLogOutPut->m_uiErrorCount++;
	}
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// ��־���д���ļ�
MatrixServerDll_API void LogOutPutWriteInFile(FILE* pFile, string str)
{
	if (pFile == NULL)
	{
		return;
	}
	size_t strSize = str.length();
	fwrite(str.c_str(), sizeof(byte), strSize, pFile);
}
// д����־����ļ�
MatrixServerDll_API void WriteLogOutPutListToFile(m_oLogOutPutStruct* pLogOutPut)
{
	list<string>::iterator iter;
	string str = "";
	if (pLogOutPut == NULL)
	{
		return;
	}
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	while(pLogOutPut->m_oLogOutputList.empty() == false)
	{
		iter = pLogOutPut->m_oLogOutputList.begin();
		str += *iter;
		pLogOutPut->m_oLogOutputList.pop_front();
	}
	LogOutPutWriteInFile(pLogOutPut->m_pFile, str);
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// �ر���־����ļ�
MatrixServerDll_API void CloseLogOutPutFile(m_oLogOutPutStruct* pLogOutPut)
{
	if (pLogOutPut == NULL)
	{
		return;
	}
	errno_t err;
	WriteLogOutPutListToFile(pLogOutPut);
	err = fclose( pLogOutPut->m_pFile );
}

// ��ʼ����־����ṹ��
MatrixServerDll_API void InitLogOutPut(m_oLogOutPutStruct* pLogOutPut)
{
	if (pLogOutPut == NULL)
	{
		return;
	}
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	// �����־�������
	pLogOutPut->m_oLogOutputList.clear();
	// ����־����ļ�
	OpenLogOutPutFile(pLogOutPut);
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// �ͷ���־����ṹ��
MatrixServerDll_API void FreeLogOutPut(m_oLogOutPutStruct* pLogOutPut)
{
	if (pLogOutPut == NULL)
	{
		return;
	}
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	// �ر���־����ļ�
	CloseLogOutPutFile(pLogOutPut);
	// �����־�������
	pLogOutPut->m_oLogOutputList.clear();
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
	DeleteCriticalSection(&pLogOutPut->m_oSecLogFile);
	delete pLogOutPut;
}
// У��֡��ͬ����
MatrixServerDll_API bool CheckInstrumentFrameHead(byte* pFrameData, m_oConstVarStruct* pConstVar)
{
	if (pFrameData == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, ErrorType, IDS_ERR_PTRISNULL, 
							"CheckInstrumentFrameHead", "pFrameData");
		return false;
	}
	if (pConstVar == NULL)
	{
		return false;
	}
	for (int i=0; i<pConstVar->m_oFrameHeadSize; i++)
	{
		if (pFrameData[i] != pConstVar->m_pFrameHeadCheck[i])
		{
			AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, ErrorType, IDS_ERR_CHECKFRAMEHEAD, 
								"CheckInstrumentFrameHead");
			return false;
		}
	}
	return true;
}
// ����֡��ͬ����
MatrixServerDll_API bool MakeInstrumentFrameHead(byte* pFrameData, m_oConstVarStruct* pConstVar)
{
	if (pFrameData == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, ErrorType, IDS_ERR_PTRISNULL, 
							"MakeInstrumentFrameHead", "pFrameData");
		return false;
	}
	if (pConstVar == NULL)
	{
		return false;
	}
	memcpy(pFrameData, pConstVar->m_pFrameHeadCheck, pConstVar->m_oFrameHeadSize);
	return true;
}
// ����֡���ݽ�������
MatrixServerDll_API bool ResetInstrumentFramePacket(m_oInstrumentCommandStruct* pCommand)
{
	if (pCommand == NULL)
	{
		return false;
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
	// 0x18�������ݸ���
	pCommand->m_usADCSetNum = 0;
	
	return true;
}
// �������豸ͨѶ����֡����
MatrixServerDll_API bool ParseInstrumentFrame(m_oInstrumentCommandStruct* pCommand, byte* pFrameData,
												m_oConstVarStruct* pConstVar)
{
	if (pCommand == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, ErrorType, IDS_ERR_PTRISNULL, 
							"ParseInstrumentFrame", "pCommand");
		return false;
	}
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pFrameData == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, ErrorType, IDS_ERR_PTRISNULL, 
							"ParseInstrumentFrame", "pFrameData");
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
	ResetInstrumentFramePacket(pCommand);
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
MatrixServerDll_API bool MakeInstrumentFrame(m_oInstrumentCommandStruct* pCommand, m_oConstVarStruct* pConstVar,
												byte* pFrameData, byte* pCommandWord, unsigned short usCommandWordNum)
{
	if (pCommand == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, ErrorType, IDS_ERR_PTRISNULL, 
							"MakeInstrumentFrame", "pCommand");
		return false;
	}
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pFrameData == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, ErrorType, IDS_ERR_PTRISNULL, 
							"MakeInstrumentFrame", "pFrameData");
		return false;
	}
	if (pCommandWord == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, ErrorType, IDS_ERR_PTRISNULL, 
							"MakeInstrumentFrame", "pCommandWord");
		return false;
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
	return true;
}
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ
MatrixServerDll_API SOCKET CreateInstrumentSocket(unsigned short usPort, unsigned int uiIP, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	SOCKET oSocket = INVALID_SOCKET;
	sockaddr_in oAddr;
	oSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	oAddr.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	oAddr.sin_port = htons(usPort);
	oAddr.sin_addr.S_un.S_addr = uiIP;
	// �󶨱��ص�ַ
	if (SOCKET_ERROR == bind(oSocket, reinterpret_cast<sockaddr*>(&oAddr), sizeof(oAddr)))
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, WSAGetLastError(), 
							"CreateInstrumentSocket", "bind");
	}
	else
	{
		listen(oSocket, 2);
	}
	return oSocket;
}
// ���ù㲥ģʽ
MatrixServerDll_API void SetInstrumentSocketBroadCast(SOCKET oSocket, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	if (SOCKET_ERROR == setsockopt(oSocket, SOL_SOCKET, SO_BROADCAST, 
									reinterpret_cast<const char *>(&iOptval), iOptlen))
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, WSAGetLastError(), 
							"SetInstrumentSocketBroadCast", "setsockopt");
	}
}
// ���ö˿ڽ��ջ���������֡����
MatrixServerDll_API void SetRcvBufferSize(SOCKET oSocket, int iRcvBufferSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	if (SOCKET_ERROR == setsockopt(oSocket, SOL_SOCKET, SO_RCVBUF,  
								reinterpret_cast<const char *>(&iRcvBufferSize), sizeof(int)))
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, WSAGetLastError(), 
							"SetRcvBufferSize", "setsockopt");
	}
}
// ���ö˿ڷ��ͻ���������֡����
MatrixServerDll_API void SetSndBufferSize(SOCKET oSocket, int iSndBufferSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	if (SOCKET_ERROR == setsockopt(oSocket, SOL_SOCKET, SO_SNDBUF,  
								reinterpret_cast<const char *>(&iSndBufferSize), sizeof(int)))
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, WSAGetLastError(), 
							"SetSndBufferSize", "setsockopt");
	}
}
// �õ�������ջ������յ���֡����
MatrixServerDll_API DWORD GetFrameCount(SOCKET oSocket, int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	DWORD dwFrameCount = 0;
	// �õ�������ջ����������ֽ���
	if (SOCKET_ERROR == ioctlsocket(oSocket, FIONREAD, &dwFrameCount))
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, WSAGetLastError(), 
							"GetFrameCount", "ioctlsocket");
	}
	else
	{
		// �õ�֡����
		dwFrameCount = dwFrameCount / iRcvFrameSize;
	}
	return dwFrameCount;
}
// �õ�֡����
MatrixServerDll_API bool GetFrameData(SOCKET oSocket, byte* pFrameData, int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	bool bReturn = false;
	sockaddr_in AddrFrom;
	int iSize = sizeof(AddrFrom);
	int iCount = recvfrom(oSocket, reinterpret_cast<char *>(pFrameData), iRcvFrameSize, 0, reinterpret_cast<sockaddr*>(&AddrFrom), &iSize);
	if(iCount == iRcvFrameSize)	//֡��С��ȷ
	{
		bReturn = true;
	}
	else if (iCount == SOCKET_ERROR)
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, WSAGetLastError(), 
							"GetFrameData", "recvfrom");
	}
	else
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, IDS_ERR_RCVFRAMESIZE, 
							"GetFrameData", "recvfrom");
	}
	return bReturn;
}
// ����֡
MatrixServerDll_API bool SendFrame(SOCKET oSocket, byte* pFrameData,int iSndFrameSize, 
								unsigned short usPort, unsigned int uiIP, 
								m_oLogOutPutStruct* pLogOutPut = NULL)
{
	bool bReturn = false;
	// ����֡
	sockaddr_in addrSend;
	addrSend.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	addrSend.sin_port = htons(usPort);
	addrSend.sin_addr.S_un.S_addr = uiIP;
	int iCount = sendto(oSocket, reinterpret_cast<const char*>(&pFrameData), iSndFrameSize, 0, 
					reinterpret_cast<sockaddr*>(&addrSend), sizeof(addrSend));
	if (iCount == iSndFrameSize)
	{
		bReturn = true;
	} 
	else if (iCount == SOCKET_ERROR)
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, WSAGetLastError(), 
							"SendFrame", "sendto");
	}
	else
	{
		AddMsgToLogOutPutList(pLogOutPut, ErrorType, IDS_ERR_SNDFRAMESIZE, 
							"SendFrame", "sendto");
	}
	return bReturn;
}
// ����������Ϣ�ṹ��
MatrixServerDll_API m_oConstVarStruct* CreateConstVar(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oConstVarStruct* pConstVar = NULL;
	pConstVar = new m_oConstVarStruct;
	pConstVar->m_pFrameHeadCheck = NULL;
	pConstVar->m_pLogOutPut = pLogOutPut;
//	AddMsgToLogOutPutList(pLogOutPut, LogType, 0, "CreateConstVar", "�ɹ�����������Ϣ�ṹ��");
	return pConstVar;
}
// ����INI�ļ�
MatrixServerDll_API void LoadIniFile(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	CString strSection	= _T("");
	CString strSectionKey = _T("");
	CString strValue = _T("");
	CString strFilePath	= _T("");
	wchar_t strBuff[256];
	CString csTemp = _T("");
	int iDirectionNew = 0;
	int iDirectionOld = 0;
	int iTemp = 0;
	strFilePath = INIFilePath;
	if (_taccess(strFilePath, 0) == -1)
	{
		return;
	}
//	GetFileAttributes(strFilePath);
	try
	{
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
	catch (CMemoryException* e)
	{
		// ���������Ϣ
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
// ��ʼ��������Ϣ�ṹ��
MatrixServerDll_API void InitConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	LoadIniFile(pConstVar);
}
// �ͷų�����Ϣ�ṹ��
MatrixServerDll_API void FreeConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pConstVar->m_pFrameHeadCheck != NULL)
	{
		delete[] pConstVar->m_pFrameHeadCheck;
	}
	delete pConstVar;
}
// ��������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API m_oInstrumentCommInfoStruct* CreateInstrumentCommInfo(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oInstrumentCommInfoStruct* pCommInfo = NULL;
	pCommInfo = new m_oInstrumentCommInfoStruct;
	pCommInfo->m_pLogOutPut = pLogOutPut;
	return pCommInfo;
}
// �򿪳��������ļ�
MatrixServerDll_API BOOL OpenAppIniXMLFile(m_oInstrumentCommInfoStruct* pCommInfo)
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = _T("msxml2.domdocument");
	if (FALSE == pCommInfo->m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError))
	{
		AddMsgToLogOutPutList(pCommInfo->m_pLogOutPut, ErrorType, IDS_ERR_XMLINTERFACE, 
							"OpenAppIniXMLFile", "CreateDispatch");
		return FALSE;
	}
	oVariant = CommXMLFilePath;
	if (_taccess(CommXMLFilePath, 0) == -1)
	{
		AddMsgToLogOutPutList(pCommInfo->m_pLogOutPut, ErrorType, IDS_ERR_FILE_EXIST, 
							"OpenAppIniXMLFile");
		return FALSE;
	}
	return pCommInfo->m_oXMLDOMDocument.load(oVariant);
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
	try
	{
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
		pCommInfo->m_uiSrcIP = inet_addr(ConvertCStrToStr(csSrcIP).c_str());

		strKey = _T("IPLCI");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		pCommInfo->m_uiDstIP = inet_addr(ConvertCStrToStr(csDstIP).c_str());
	}
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//���ض˿���������
MatrixServerDll_API void LoadPortSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	try
	{
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
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
//�������ݻ�������С����
MatrixServerDll_API void LoadBufferSizeSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	try
	{
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
	catch (CMemoryException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
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
	if (TRUE == OpenAppIniXMLFile(pCommInfo))
	{
		//����IP��ַ��������
		LoadIPSetupData(pCommInfo);
		//���ض˿���������
		LoadPortSetupData(pCommInfo);
		//�������ݻ�������С����
		LoadBufferSizeSetupData(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppIniXMLFile(pCommInfo);
}
// ��ʼ������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void InitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	LoadLineServerAppSetupData(pCommInfo);
}
// �ͷ�����ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	delete pCommInfo;
}
// ��������֡��Ϣ�ṹ��
MatrixServerDll_API m_oHeartBeatFrameStruct* CreateInstrumentHeartBeat(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oHeartBeatFrameStruct* pHeartBeatFrame = NULL;
	pHeartBeatFrame = new m_oHeartBeatFrameStruct;
	InitializeCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	pHeartBeatFrame->m_pbySndFrameData = NULL;
	pHeartBeatFrame->m_pbyCommandWord = NULL;
	pHeartBeatFrame->m_pLogOutPut = pLogOutPut;
	return pHeartBeatFrame;
}
// ��ʼ������
MatrixServerDll_API void InitInstrumentHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
													m_oInstrumentCommInfoStruct* pCommInfo,
													m_oConstVarStruct* pConstVar)
{
	if (pHeartBeatFrame == NULL)
	{
		return;
	}
	if (pCommInfo == NULL)
	{
		return;
	}
	if (pConstVar == NULL)
	{
		return;
	}
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	// Դ��ַ
	pHeartBeatFrame->m_oCommandStruct.m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pHeartBeatFrame->m_oCommandStruct.m_uiDstIP = pCommInfo->m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	pHeartBeatFrame->m_oCommandStruct.m_uiAimPort = pCommInfo->m_uiAimPort;
	// �������ض˿�
	pHeartBeatFrame->m_oCommandStruct.m_usReturnPort = pCommInfo->m_usHeartBeatReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pHeartBeatFrame->m_oCommandStruct.m_usCommand = pConstVar->m_oSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pHeartBeatFrame->m_oCommandStruct);
	// ��շ���֡������
	pHeartBeatFrame->m_pbySndFrameData = new byte[pConstVar->m_oSndFrameSize];
	memset(pHeartBeatFrame->m_pbySndFrameData, pConstVar->m_oSndFrameBufInit, pConstVar->m_oSndFrameSize);
	// ������������ּ���
	pHeartBeatFrame->m_pbyCommandWord = new byte[pConstVar->m_oCommandWordMaxNum];
	memset(pHeartBeatFrame->m_pbyCommandWord, pConstVar->m_oSndFrameBufInit, pConstVar->m_oCommandWordMaxNum);
	// ���������ָ���
	pHeartBeatFrame->m_usCommandWordNum = 0;
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// �ͷ�����֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame)
{
	if (pHeartBeatFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	if (pHeartBeatFrame->m_pbySndFrameData != NULL)
	{
		delete[] pHeartBeatFrame->m_pbySndFrameData;
	}
	if (pHeartBeatFrame->m_pbyCommandWord != NULL)
	{
		delete[] pHeartBeatFrame->m_pbyCommandWord;
	}
	delete pHeartBeatFrame;
}
// �����װ�֡��Ϣ�ṹ��
MatrixServerDll_API m_oHeadFrameStruct* CreateInstrumentHeadFrame(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oHeadFrameStruct* pHeadFrame = NULL;
	pHeadFrame = new m_oHeadFrameStruct;
	InitializeCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	pHeadFrame->m_pbyRcvFrameData = NULL;
	pHeadFrame->m_pLogOutPut = pLogOutPut;
	return pHeadFrame;
}
// ��ʼ���װ�
MatrixServerDll_API void InitInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
													m_oInstrumentCommInfoStruct* pCommInfo,
													m_oConstVarStruct* pConstVar)
{
	if (pHeadFrame == NULL)
	{
		return;
	}
	if (pCommInfo == NULL)
	{
		return;
	}
	if (pConstVar == NULL)
	{
		return;
	}
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	// Դ��ַ
	pHeadFrame->m_oCommandStruct.m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pHeadFrame->m_oCommandStruct.m_uiDstIP = pCommInfo->m_uiDstIP;
	// �װ����ջ�����֡���趨Ϊ��������
	pHeadFrame->m_uiRcvBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_oRcvFrameSize;
	// ���ն˿�
	pHeadFrame->m_oCommandStruct.m_usReturnPort = pCommInfo->m_usHeadFramePort;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pHeadFrame->m_oCommandStruct);
	// ��ս���֡������
	pHeadFrame->m_pbyRcvFrameData = new byte[pConstVar->m_oRcvFrameSize];
	memset(pHeadFrame->m_pbyRcvFrameData, pConstVar->m_oSndFrameBufInit, pConstVar->m_oRcvFrameSize);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
}
// �ͷ��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame)
{
	if (pHeadFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	if (pHeadFrame->m_pbyRcvFrameData != NULL)
	{
		delete[] pHeadFrame->m_pbyRcvFrameData;
	}
	delete pHeadFrame;
}
// ����IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API m_oIPSetFrameStruct* CreateInstrumentIPSetFrame(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oIPSetFrameStruct* pIPSetFrame = NULL;
	pIPSetFrame = new m_oIPSetFrameStruct;
	InitializeCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	pIPSetFrame->m_pbySndFrameData = NULL;
	pIPSetFrame->m_pbyCommandWord = NULL;
	pIPSetFrame->m_pbyRcvFrameData = NULL;
	pIPSetFrame->m_pLogOutPut = pLogOutPut;
	return pIPSetFrame;
}
// ��ʼ��IP��ַ����
MatrixServerDll_API void InitInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame,
													m_oInstrumentCommInfoStruct* pCommInfo,
													m_oConstVarStruct* pConstVar)
{
	if (pIPSetFrame == NULL)
	{
		return;
	}
	if (pCommInfo == NULL)
	{
		return;
	}
	if (pConstVar == NULL)
	{
		return;
	}
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// Դ��ַ
	pIPSetFrame->m_oCommandStructSet.m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pIPSetFrame->m_oCommandStructSet.m_uiDstIP = pCommInfo->m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	pIPSetFrame->m_oCommandStructSet.m_uiAimPort = pCommInfo->m_uiAimPort;
	// IP��ַ���÷��ͻ�����֡���趨Ϊ��������
	pIPSetFrame->m_uiSndBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_oSndFrameSize;
	// IP��ַ����Ӧ����ջ�����֡���趨Ϊ��������
	pIPSetFrame->m_uiRcvBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_oRcvFrameSize;
	// IP��ַ���÷��ض˿�
	pIPSetFrame->m_oCommandStructSet.m_usReturnPort = pCommInfo->m_usIPSetReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pIPSetFrame->m_oCommandStructSet.m_usCommand = pConstVar->m_oSendSetCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pIPSetFrame->m_oCommandStructSet);
	// ��շ���֡������
	pIPSetFrame->m_pbySndFrameData = new byte[pConstVar->m_oSndFrameSize];
	memset(pIPSetFrame->m_pbySndFrameData, pConstVar->m_oSndFrameBufInit, pConstVar->m_oSndFrameSize);
	// ���IP��ַ���������ּ���
	pIPSetFrame->m_pbyCommandWord = new byte[pConstVar->m_oCommandWordMaxNum];
	memset(pIPSetFrame->m_pbyCommandWord, pConstVar->m_oSndFrameBufInit, pConstVar->m_oCommandWordMaxNum);
	// IP��ַ���������ָ���
	pIPSetFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	ResetInstrumentFramePacket(&pIPSetFrame->m_oCommandStructReturn);
	// ��ս���֡������
	pIPSetFrame->m_pbyRcvFrameData = new byte[pConstVar->m_oRcvFrameSize];
	memset(pIPSetFrame->m_pbyRcvFrameData, pConstVar->m_oSndFrameBufInit, pConstVar->m_oRcvFrameSize);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// �ͷ�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void FreeInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame)
{
	if (pIPSetFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	if (pIPSetFrame->m_pbySndFrameData != NULL)
	{
		delete[] pIPSetFrame->m_pbySndFrameData;
	}
	if (pIPSetFrame->m_pbyCommandWord != NULL)
	{
		delete[] pIPSetFrame->m_pbyCommandWord;
	}
	if (pIPSetFrame->m_pbyRcvFrameData != NULL)
	{
		delete[] pIPSetFrame->m_pbyRcvFrameData;
	}
	delete pIPSetFrame;
}
// �����̴߳����־λ��Ϣ�ṹ��
MatrixServerDll_API m_oThreadProcFlagStruct* CreateThreadProcFlag()
{
	m_oThreadProcFlagStruct* pThreadProcFlag = NULL;
	pThreadProcFlag = new m_oThreadProcFlagStruct;
	InitializeCriticalSection(&pThreadProcFlag->m_oSecFlag);
	return pThreadProcFlag;
}
// ��ʼ���̴߳����־λ
MatrixServerDll_API void InitThreadProcFlag(m_oThreadProcFlagStruct* pThreadProcFlag)
{
	if (pThreadProcFlag == NULL)
	{
		return;
	}
	EnterCriticalSection(&pThreadProcFlag->m_oSecFlag);
	// ���������߳�ֹͣ��־λ
	pThreadProcFlag->m_bProcHeartBeatStop = false;
	// �װ������߳�ֹͣ��־λ
	pThreadProcFlag->m_bProcHeadFrameStop = false;
	// ����IP��ַ�����߳�ֹͣ��־λ
	pThreadProcFlag->m_bProcIPSetStop = false;
	LeaveCriticalSection(&pThreadProcFlag->m_oSecFlag);
}
// �ͷ��̴߳����־λ��Ϣ�ṹ��
MatrixServerDll_API void FreeThreadProcFlag(m_oThreadProcFlagStruct* pThreadProcFlag)
{
	if (pThreadProcFlag == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pThreadProcFlag->m_oSecFlag);
	delete pThreadProcFlag;
}
// ��ʼ���׽��ֿ�
MatrixServerDll_API void InitSocketLib()
{
	WSADATA data;									// ����ṹ�����
	WORD w = MAKEWORD(2, 2);			// ��ʼ���׽��ְ汾��
	int err = WSAStartup(w, &data);							// ��ʼ���׽��ֿ�
	if (err == 0)
	{
		/*m_oLogFile.OnWriteLogFile(_T("CMatrixTestSoftDlg::OnInitDialog"), _T("��ʼ���׽��ֿ�ɹ���"), SuccessStatus);*/
	}
	else
	{
		WSAGetLastError();
// 		str.Format(_T("��ʼ���׽��ֿ�ʧ�ܣ�������Ϊ%d��"), err);
// 		m_oLogFile.OnWriteLogFile(_T("CMatrixTestSoftDlg::OnInitDialog"), str, ErrorStatus);
	}
}
// �ͷ��׽��ֿ�
MatrixServerDll_API void FreeSocketLib()
{
	// �ͷ��׽��ֿ�
	int err = WSACleanup();	
	if (err == 0)
	{
//		m_oLogFile.OnWriteLogFile(_T("CMatrixTestSoftDlg::OnClose"), _T("�ͷ��׽��ֿ�ɹ���"), SuccessStatus);
	}
	else
	{
		WSAGetLastError();
// 		CString str = _T("");
// 		str.Format(_T("�ͷ��׽��ֿ�ʧ�ܣ�������Ϊ%d��"), err);
// 		m_oLogFile.OnWriteLogFile(_T("CMatrixTestSoftDlg::OnClose"), str, ErrorStatus);
	}
}
// ���������������˿�
MatrixServerDll_API void CreateAndSetHeartBeatSocket(m_oHeartBeatFrameStruct* pHeartBeatFrame)
{
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	// �����׽���
	pHeartBeatFrame->m_oHeartBeatSocket = CreateInstrumentSocket(pHeartBeatFrame->m_oCommandStruct.m_usReturnPort, 
																pHeartBeatFrame->m_oCommandStruct.m_uiSrcIP,
																pHeartBeatFrame->m_pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pHeartBeatFrame->m_oHeartBeatSocket, pHeartBeatFrame->m_pLogOutPut);
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// �����������װ��˿�
MatrixServerDll_API void CreateAndSetHeadFrameSocket(m_oHeadFrameStruct* pHeadFrame)
{
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	// �����׽���
	pHeadFrame->m_oHeadFrameSocket = CreateInstrumentSocket(pHeadFrame->m_oCommandStruct.m_usReturnPort, 
															pHeadFrame->m_oCommandStruct.m_uiSrcIP,
															pHeadFrame->m_pLogOutPut);
	// ���ý��ջ�����
	SetRcvBufferSize(pHeadFrame->m_oHeadFrameSocket, pHeadFrame->m_uiRcvBufferSize, pHeadFrame->m_pLogOutPut);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
}
// ����������IP��ַ���ö˿�
MatrixServerDll_API void CreateAndSetIPSetFrameSocket(m_oIPSetFrameStruct* pIPSetFrame)
{
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// �����׽���
	pIPSetFrame->m_oIPSetFrameSocket = CreateInstrumentSocket(pIPSetFrame->m_oCommandStructSet.m_usReturnPort, 
																pIPSetFrame->m_oCommandStructSet.m_uiSrcIP,
																pIPSetFrame->m_pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_uiSndBufferSize, pIPSetFrame->m_pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_uiRcvBufferSize, pIPSetFrame->m_pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// ��ʼ��ʵ��
MatrixServerDll_API void InitInstance(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	// ������־����ṹ��
	pEnv->m_pLogOutPut = CreateLogOutPut();
	// ����������Ϣ�ṹ��
	pEnv->m_pConstVar = CreateConstVar(pEnv->m_pLogOutPut);
	// ��������ͨѶ��Ϣ�ṹ��
	pEnv->m_pInstrumentCommInfo = CreateInstrumentCommInfo(pEnv->m_pLogOutPut);
	// ��������֡��Ϣ�ṹ��
	pEnv->m_pHeartBeatFrame = CreateInstrumentHeartBeat(pEnv->m_pLogOutPut);
	// �����װ�֡��Ϣ�ṹ��
	pEnv->m_pHeadFrame = CreateInstrumentHeadFrame(pEnv->m_pLogOutPut);
	// ����IP��ַ����֡��Ϣ�ṹ��
	pEnv->m_pIPSetFrame = CreateInstrumentIPSetFrame(pEnv->m_pLogOutPut);
	// �����̴߳����־λ��Ϣ�ṹ��
	pEnv->m_pThreadProcFlag = CreateThreadProcFlag();

	// ��ʼ����־����ṹ��
	InitLogOutPut(pEnv->m_pLogOutPut);
	// ��ʼ���׽��ֿ�
	InitSocketLib();
	// ��ʼ��������Ϣ�ṹ��
	InitConstVar(pEnv->m_pConstVar);
	// ��ʼ������ͨѶ��Ϣ�ṹ��
	InitInstrumentCommInfo(pEnv->m_pInstrumentCommInfo);
	// ��ʼ������
	InitInstrumentHeartBeat(pEnv->m_pHeartBeatFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ���װ�
	InitInstrumentHeadFrame(pEnv->m_pHeadFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��IP��ַ����
	InitInstrumentIPSetFrame(pEnv->m_pIPSetFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ���̴߳����־λ
	InitThreadProcFlag(pEnv->m_pThreadProcFlag);
	// ���������������˿�
	CreateAndSetHeartBeatSocket(pEnv->m_pHeartBeatFrame);
	// �����������װ��˿�
	CreateAndSetHeadFrameSocket(pEnv->m_pHeadFrame);
	// ����������IP��ַ���ö˿�
	CreateAndSetIPSetFrameSocket(pEnv->m_pIPSetFrame);
}
// �ͷ�ʵ����Դ
MatrixServerDll_API void FreeInstance(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	// �ͷ���־����ṹ��
	FreeLogOutPut(pEnv->m_pLogOutPut);
	FreeConstVar(pEnv->m_pConstVar);
	FreeInstrumentCommInfo(pEnv->m_pInstrumentCommInfo);
	FreeInstrumentHeartBeat(pEnv->m_pHeartBeatFrame);
	FreeInstrumentHeadFrame(pEnv->m_pHeadFrame);
	FreeInstrumentIPSetFrame(pEnv->m_pIPSetFrame);
	FreeThreadProcFlag(pEnv->m_pThreadProcFlag);
	delete pEnv;
	pEnv = NULL;
	// �ͷ��׽��ֿ�
	FreeSocketLib();
}
// �����װ�֡
MatrixServerDll_API bool ParseInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame, m_oConstVarStruct* pConstVar)
{
	bool bReturn = false;
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	bReturn = ParseInstrumentFrame(&pHeadFrame->m_oCommandStruct, pHeadFrame->m_pbyRcvFrameData, pConstVar);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	return bReturn;
}
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API bool ParseInstrumentIPSetReturnFrame(m_oIPSetFrameStruct* pIPSetFrame, m_oConstVarStruct* pConstVar)
{
	bool bReturn = false;
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	bReturn = ParseInstrumentFrame(&pIPSetFrame->m_oCommandStructReturn, pIPSetFrame->m_pbyRcvFrameData, pConstVar);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	return bReturn;
}
// ��������֡
MatrixServerDll_API void MakeInstrumentHeartBeatFrame(m_oHeartBeatFrameStruct* pHeartBeatFrame, m_oConstVarStruct* pConstVar)
{
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	MakeInstrumentFrame(&pHeartBeatFrame->m_oCommandStruct,  pConstVar, pHeartBeatFrame->m_pbySndFrameData,
						pHeartBeatFrame->m_pbyCommandWord, pHeartBeatFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// ����IP��ַ����֡
MatrixServerDll_API void MakeInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, m_oConstVarStruct* pConstVar)
{
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	MakeInstrumentFrame(&pIPSetFrame->m_oCommandStructSet, pConstVar, pIPSetFrame->m_pbySndFrameData, 
						pIPSetFrame->m_pbyCommandWord, pIPSetFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}