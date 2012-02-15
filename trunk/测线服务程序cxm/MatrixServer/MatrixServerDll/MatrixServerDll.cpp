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
// ����INI�ļ����鳣��
MATRIXSERVERDLL_API void ParseCStringToArray(char** pData, int iSize, CString str)
{
	if ((*pData) != NULL)
	{
		delete[] (*pData);
	}
	*pData = new char[iSize];
	int iDirectionOld = 0;
	int iDirectionNew = 0;
	CString csTemp = _T("");
	int iTemp = 0;
	for (int i=0; i<iSize; i++)
	{
		iDirectionNew = str.Find(_T("0x"), iDirectionOld);
		iDirectionNew += 2;
		csTemp = str.Mid(iDirectionNew, 2);
		_stscanf_s(csTemp, _T("%x"), &iTemp, sizeof(int));
		(*pData)[i] = static_cast<char>(iTemp);
		iDirectionOld = iDirectionNew;
	}
}
// ����ʵ����������ʵ��ָ��
MatrixServerDll_API m_oEnvironmentStruct* OnCreateInstance(void)
{
	m_oEnvironmentStruct* pEnv = new m_oEnvironmentStruct;
	pEnv->m_pConstVar = NULL;
	pEnv->m_pInstrumentCommInfo = NULL;
	pEnv->m_pHeartBeatFrame = NULL;
	pEnv->m_pHeadFrame = NULL;
	pEnv->m_pIPSetFrame = NULL;
	pEnv->m_pTailFrame = NULL;
	pEnv->m_pTailTimeFrame = NULL;
	pEnv->m_pTimeDelayFrame = NULL;
	pEnv->m_pADCSetFrame = NULL;
	pEnv->m_pLogOutPutOpt = NULL;
	pEnv->m_pLogOutPutTimeDelay = NULL;
	pEnv->m_pLogOutPutErrorCode = NULL;
	pEnv->m_pLogOutPutADCFrameTime = NULL;
	pEnv->m_pInstrumentList = NULL;
	pEnv->m_pRoutList = NULL;
	pEnv->m_pLogOutPutThread = NULL;
	pEnv->m_pHeartBeatThread = NULL;
	pEnv->m_pHeadFrameThread = NULL;
	pEnv->m_pIPSetFrameThread = NULL;
	pEnv->m_pTailFrameThread = NULL;
	pEnv->m_pMonitorRoutThread = NULL;
	pEnv->m_pTimeDelayThread = NULL;
	pEnv->m_pADCSetThread = NULL;
	return pEnv;
}
// ������־����ṹ��
MatrixServerDll_API m_oLogOutPutStruct* OnCreateLogOutPut()
{
	m_oLogOutPutStruct* pLogOutPut = NULL;
	pLogOutPut = new m_oLogOutPutStruct;
	InitializeCriticalSection(&pLogOutPut->m_oSecLogFile);

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
	errno_t err;
	// ��������������־�ļ���
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	CreateDirectory(pLogOutPut->m_csSaveLogFilePath, NULL);
	pLogOutPut->m_uiLogFileNb++;
	str.Format(_T("\\%d.log"),pLogOutPut->m_uiLogFileNb);
	pLogOutPut->m_uiLogInfoCount = 0;
	err = fopen_s(&pLogOutPut->m_pFile, ConvertCStrToStr(pLogOutPut->m_csSaveLogFilePath + str).c_str(), "wt+, ccs=UNICODE");
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// ���뵽��־�������
MatrixServerDll_API void AddMsgToLogOutPutList(m_oLogOutPutStruct* pLogOutPut = NULL, 
	string pFuncName = "", 
	string pVarName = "", 
	byte byErrorType = LogType, 
	unsigned int uiErrorCode = 0)
{
	CString cstrTime = _T("");
	CString cstrErrorCode = _T("");
	CString strOutPut = _T("");
	string str = "";
	string strTemp = "";
	SYSTEMTIME  sysTime;
	if (pLogOutPut == NULL)
	{
		return;
	}
	if (OutPutSelect == 1)
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
	cstrTime.Format(_T("%04d��%02d��%02d�� %02d:%02d:%02d:%03d\t"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
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
		cstrErrorCode.Format(_T("ErrorCode = %d\t"), uiErrorCode);
		strOutPut += cstrErrorCode;
	}
	else if (byErrorType == ExpandType)
	{
		strOutPut += _T("ExpandType\t");
	}
	strOutPut += cstrTime;
	str = ConvertCStrToStr(strOutPut);
	if (pFuncName.empty() == false)
	{
		strTemp = "�������е�������";
		str += strTemp;
		str += pFuncName;
		str += '\t';
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
	fwrite(str.c_str(), sizeof(char), strSize, pFile);
	fflush(pFile);
}
// д����־����ļ�
MatrixServerDll_API void WriteLogOutPutListToFile(m_oLogOutPutStruct* pLogOutPut)
{
	list<string>::iterator iter;
	string str = "";
	errno_t err;
	bool bOpenNewFile = false;
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
		pLogOutPut->m_uiLogInfoCount++;
	}
	LogOutPutWriteInFile(pLogOutPut->m_pFile, str);
	if (pLogOutPut->m_uiLogInfoCount > OutPutLogFileInfoNumLimit)
	{
		err = fclose( pLogOutPut->m_pFile );
		bOpenNewFile = true;
	}
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
	if (bOpenNewFile == true)
	{
		OpenLogOutPutFile(pLogOutPut);
	}
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
MatrixServerDll_API void OnInitLogOutPut(m_oLogOutPutStruct* pLogOutPut)
{
	if (pLogOutPut == NULL)
	{
		return;
	}
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	// ��־�ļ�ָ��Ϊ��
	pLogOutPut->m_pFile = NULL;
	// ��־�����������
	pLogOutPut->m_uiErrorCount = 0;
	// �����־�������
	pLogOutPut->m_oLogOutputList.clear();
	// ��־�ļ�����趨
	pLogOutPut->m_uiLogFileNb = 0;
	// ��־�ļ��洢��Ϣ��������
	pLogOutPut->m_uiLogInfoCount = 0;
	// ����־����ļ�
	OpenLogOutPutFile(pLogOutPut);
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// �ر���־����ṹ��
MatrixServerDll_API void OnCloseLogOutPut(m_oLogOutPutStruct* pLogOutPut)
{
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	// �ر���־����ļ�
	CloseLogOutPutFile(pLogOutPut);
	// �����־�������
	pLogOutPut->m_oLogOutputList.clear();
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// �ͷ���־����ṹ��
MatrixServerDll_API void OnFreeLogOutPut(m_oLogOutPutStruct* pLogOutPut)
{
	if (pLogOutPut == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pLogOutPut->m_oSecLogFile);
	delete pLogOutPut;
}
// У��֡��ͬ����
MatrixServerDll_API bool CheckInstrumentFrameHead(char* pFrameData, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pFrameData == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "CheckInstrumentFrameHead", "pFrameData", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	// @@@@@@@@ͬ��ͷĿǰֻ��ǰ4λ��Ч������12λ������������
	for (int i=0; i<4; i++)
	{
		if (pFrameData[i] != pConstVar->m_pFrameHeadCheck[i])
		{
			AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "CheckInstrumentFrameHead", "",
				ErrorType, IDS_ERR_CHECKFRAMEHEAD);
			return false;
		}
	}
	return true;
}
// ����֡��ͬ����
MatrixServerDll_API bool MakeInstrumentFrameHead(char* pFrameData, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pFrameData == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentFrameHead", "pFrameData", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	memcpy(pFrameData, pConstVar->m_pFrameHeadCheck, pConstVar->m_iFrameHeadSize);
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
	pCommand->m_uiLocalTimeFixedLow = 0;
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
	pCommand->m_uiBroadCastPortSet = 0;
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
	// β������ʱ�̣���14λ��Ч
	pCommand->m_usTailRecTime = 0;
	// β������ʱ��//����վβ������ʱ�̣���14λ��Ч
	pCommand->m_usTailSndTime = 0;
	// �㲥����ȴ��˿�ƥ�䣬������ڵ�һ��������λ�ã�����0x0a�����е�16λ�˿�ƥ����ܽ��չ㲥����
	pCommand->m_uiBroadCastPortSeted = 0;
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
	pCommand->m_iADCSetNum = 0;
	return true;
}
// �������豸ͨѶ����֡����
MatrixServerDll_API bool ParseInstrumentFrame(m_oInstrumentCommandStruct* pCommand, char* pFrameData,
	m_oConstVarStruct* pConstVar)
{
	if (pCommand == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentFrame", "pCommand", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pFrameData == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentFrame", "pFrameData", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	unsigned char	byCommandWord = 0;
	int iPos = 0;
	// У��֡��ͬ����
	if (false == CheckInstrumentFrameHead(pFrameData, pConstVar))
	{
		return false;
	}
	iPos += pConstVar->m_iFrameHeadSize;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pCommand);
	// ԴIP��ַ
	memcpy(&pCommand->m_uiSrcIP, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
	iPos += pConstVar->m_iFramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pCommand->m_uiDstIP, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
	iPos += pConstVar->m_iFramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pCommand->m_usReturnPort, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
	iPos += pConstVar->m_iFramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pCommand->m_usCommand, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
	iPos += pConstVar->m_iFramePacketSize2B;
	// ����֡����
	unsigned int uiRoutAddrNum = 0;
	while(true)
	{
		memcpy(&byCommandWord, &pFrameData[iPos], pConstVar->m_iFrameCmdSize1B);
		iPos += pConstVar->m_iFrameCmdSize1B;
		if (byCommandWord == pConstVar->m_byCmdSn)
		{
			memcpy(&pCommand->m_uiSN, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdHeadFrameTime)
		{
			memcpy(&pCommand->m_uiTimeHeadFrame, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLocalIPAddr)
		{
			memcpy(&pCommand->m_uiInstrumentIP, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLocalSysTime)
		{
			memcpy(&pCommand->m_uiSysTime, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLocalTimeFixedHigh)
		{
			memcpy(&pCommand->m_uiLocalTimeFixedHigh, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLocalTimeFixedLow)
		{
			memcpy(&pCommand->m_uiLocalTimeFixedLow, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdADCDataReturnAddr)
		{
			memcpy(&pCommand->m_uiADCDataReturnAddr, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdADCDataReturnPort)
		{
			memcpy(&pCommand->m_usADCDataReturnPort, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnCmd, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_byCmdADCDataReturnPortLimit)
		{
			memcpy(&pCommand->m_usADCDataReturnPortLimitLow, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnPortLimitHigh, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_byCmdBroadCastPortSet)
		{
			memcpy(&pCommand->m_uiBroadCastPortSet, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdFDUErrorCode)
		{
			memcpy(&pCommand->m_byFDUErrorCodeDataCount, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pCommand->m_byFDUErrorCodeCmdCount, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pCommand->m_byTimeStatus, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pCommand->m_byCtrlStatus, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
		}
		else if (byCommandWord == pConstVar->m_byCmdTBHigh)
		{
			memcpy(&pCommand->m_uiTBHigh, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdTbLow)
		{
			memcpy(&pCommand->m_usTBLow, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pCommand->m_usTBCtrl, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLAUXRoutOpenQuery)
		{
			memcpy(&pCommand->m_byLAUXRoutOpenQuery, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLAUXRoutOpenSet)
		{
			memcpy(&pCommand->m_byLAUXRoutOpenSet, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdTailRecSndTime)
		{
			memcpy(&pCommand->m_usTailRecTime, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			pCommand->m_usTailRecTime &= 0x3fff;
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pCommand->m_usTailSndTime, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			pCommand->m_usTailSndTime &= 0x3fff;
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_byCmdBroadCastPortSeted)
		{
			memcpy(&pCommand->m_uiBroadCastPortSeted, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdADCSet)
		{
			memcpy(&pCommand->m_pcADCSet[pCommand->m_iADCSetNum], &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
			pCommand->m_iADCSetNum += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdNetTime)
		{
			memcpy(&pCommand->m_uiNetTime, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLineTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLineA, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			pCommand->m_usLAUXTailRecTimeLineA &= 0x3fff;
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLineB, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			pCommand->m_usLAUXTailRecTimeLineB &= 0x3fff;
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLAUTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineA, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			pCommand->m_usLAUXTailRecTimeLAUXLineA &= 0x3fff;
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineB, &pFrameData[iPos], pConstVar->m_iFramePacketSize2B);
			pCommand->m_usLAUXTailRecTimeLAUXLineB &= 0x3fff;
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLAUXErrorCode1)
		{
			memcpy(&pCommand->m_byLAUXErrorCodeDataLineACount, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLineBCount, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLAUXLineACount, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pCommand->m_byLAUXErrorCodeDataLAUXLineBCount, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLAUXErrorCode2)
		{
			memcpy(&pCommand->m_byLAUXErrorCodeCmdCount, &pFrameData[iPos], pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdLAUXSetRout)
		{
			if (uiRoutAddrNum == 0)
			{
				memcpy(&pCommand->m_uiRoutIPRight, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 1)
			{
				memcpy(&pCommand->m_uiRoutIPLeft, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 2)
			{
				memcpy(&pCommand->m_uiRoutIPTop, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 3)
			{
				memcpy(&pCommand->m_uiRoutIPDown, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			uiRoutAddrNum++;
		}
		else if (byCommandWord == pConstVar->m_byCmdReturnRout)
		{
			memcpy(&pCommand->m_uiRoutIP, &pFrameData[iPos], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_byCmdEnd)
		{
			break;
		}
		else
		{
			iPos += pConstVar->m_iFramePacketSize4B;
		}
	}
	return true;
}
// �������豸ͨѶ֡
MatrixServerDll_API bool MakeInstrumentFrame(m_oInstrumentCommandStruct* pCommand, m_oConstVarStruct* pConstVar,
	char* pFrameData, char* pCommandWord, unsigned short usCommandWordNum)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pCommand == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentFrame", "pCommand", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	if (pFrameData == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentFrame", "pFrameData", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	if (pCommandWord == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentFrame", "pCommandWord", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	int iPos = 0;
	unsigned int uiRoutAddrNum = 0;
	// ����֡��ͬ����
	MakeInstrumentFrameHead(pFrameData, pConstVar);
	iPos += pConstVar->m_iFrameHeadSize;
	// ԴIP��ַ
	memcpy(&pFrameData[iPos], &pCommand->m_uiSrcIP, pConstVar->m_iFramePacketSize4B);
	iPos += pConstVar->m_iFramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pFrameData[iPos], &pCommand->m_uiDstIP, pConstVar->m_iFramePacketSize4B);
	iPos += pConstVar->m_iFramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pFrameData[iPos], &pCommand->m_usReturnPort, pConstVar->m_iFramePacketSize2B);
	iPos += pConstVar->m_iFramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pFrameData[iPos], &pCommand->m_usCommand, pConstVar->m_iFramePacketSize2B);
	iPos += pConstVar->m_iFramePacketSize2B;
	// ��ʱ��
	iPos += pConstVar->m_iFramePacketSize4B;

	// ����֡����
	for (unsigned short i=0; i<usCommandWordNum; i++)
	{
		memcpy(&pFrameData[iPos], &pCommandWord[i], pConstVar->m_iFrameCmdSize1B);
		iPos += pConstVar->m_iFrameCmdSize1B;
		if (pCommandWord[i] == pConstVar->m_byCmdSn)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiSN, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdHeadFrameTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiTimeHeadFrame, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLocalIPAddr)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiInstrumentIP, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLocalSysTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiSysTime, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLocalTimeFixedHigh)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiLocalTimeFixedHigh, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLocalTimeFixedLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiLocalTimeFixedLow, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdADCDataReturnAddr)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiADCDataReturnAddr, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdADCDataReturnPort)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPort, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnCmd, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdADCDataReturnPortLimit)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPortLimitLow, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPortLimitHigh, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdBroadCastPortSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiBroadCastPortSet, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdFDUErrorCode)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byFDUErrorCodeDataCount, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byFDUErrorCodeCmdCount, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byTimeStatus, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byCtrlStatus, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdTBHigh)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiTBHigh, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdTbLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usTBLow, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usTBCtrl, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLAUXRoutOpenQuery)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXRoutOpenQuery, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLAUXRoutOpenSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXRoutOpenSet, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdTailRecSndTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usTailRecTime, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usTailSndTime, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdBroadCastPortSeted)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiBroadCastPortSeted, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdADCSet)
		{
			if (pCommand->m_iADCSetNum == pConstVar->m_iFramePacketSize4B)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_pcADCSet[0], pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			else
			{
				memcpy(&pFrameData[iPos], &pCommand->m_pcADCSet[0], pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
				for (int j = pConstVar->m_iFramePacketSize4B; j < pCommand->m_iADCSetNum; j += pConstVar->m_iFramePacketSize4B)
				{
					memcpy(&pFrameData[iPos], &pConstVar->m_byCmdADCSet, pConstVar->m_iFrameCmdSize1B);
					iPos += pConstVar->m_iFrameCmdSize1B;
					memcpy(&pFrameData[iPos], &pCommand->m_pcADCSet[j], pConstVar->m_iFramePacketSize4B);
					iPos += pConstVar->m_iFramePacketSize4B;
				}
			}
			memcpy(&pFrameData[iPos], &pCommand->m_pcADCSet[pCommand->m_iADCSetNum], pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
			pCommand->m_iADCSetNum += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdNetTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiNetTime, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLineTailRecTimeLAUX)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLineA, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLineB, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLAUTailRecTimeLAUX)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLAUXLineA, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLAUXLineB, pConstVar->m_iFramePacketSize2B);
			iPos += pConstVar->m_iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLAUXErrorCode1)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLineACount, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLineBCount, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLAUXLineACount, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeDataLAUXLineBCount, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize1B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLAUXErrorCode2)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_byLAUXErrorCodeCmdCount, pConstVar->m_iFramePacketSize1B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdLAUXSetRout)
		{
			if (uiRoutAddrNum == 0)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIPLeft, pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 1)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIPRight, pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 2)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIPTop, pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 3)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIPDown, pConstVar->m_iFramePacketSize4B);
				iPos += pConstVar->m_iFramePacketSize4B;
			}
			uiRoutAddrNum++;
		}
		else if (pCommandWord[i] == pConstVar->m_byCmdReturnRout)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIP, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
		else
		{
			memset(&pFrameData[iPos], pConstVar->m_bySndFrameBufInit, pConstVar->m_iFramePacketSize4B);
			iPos += pConstVar->m_iFramePacketSize4B;
		}
	}
	pFrameData[iPos] = pConstVar->m_byCmdEnd;
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
		AddMsgToLogOutPutList(pLogOutPut, "CreateInstrumentSocket", "bind", 
			ErrorType, WSAGetLastError());
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
		AddMsgToLogOutPutList(pLogOutPut, "SetInstrumentSocketBroadCast", "setsockopt", 
			ErrorType, WSAGetLastError());
	}
}
// ���ö˿ڽ��ջ���������֡����
MatrixServerDll_API void SetRcvBufferSize(SOCKET oSocket, int iRcvBufferSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	if (SOCKET_ERROR == setsockopt(oSocket, SOL_SOCKET, SO_RCVBUF,  
		reinterpret_cast<const char *>(&iRcvBufferSize), sizeof(int)))
	{
		AddMsgToLogOutPutList(pLogOutPut, "SetRcvBufferSize", "setsockopt", 
			ErrorType, WSAGetLastError());
	}
}
// ���ö˿ڷ��ͻ���������֡����
MatrixServerDll_API void SetSndBufferSize(SOCKET oSocket, int iSndBufferSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	if (SOCKET_ERROR == setsockopt(oSocket, SOL_SOCKET, SO_SNDBUF,  
		reinterpret_cast<const char *>(&iSndBufferSize), sizeof(int)))
	{
		AddMsgToLogOutPutList(pLogOutPut, "SetSndBufferSize", "setsockopt", 
			ErrorType, WSAGetLastError());
	}
}
// �õ�������ջ������յ���֡����
MatrixServerDll_API DWORD GetFrameCount(SOCKET oSocket, int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	DWORD dwFrameCount = 0;
	// �õ�������ջ����������ֽ���
	if (SOCKET_ERROR == ioctlsocket(oSocket, FIONREAD, &dwFrameCount))
	{
		AddMsgToLogOutPutList(pLogOutPut, "GetFrameCount", "ioctlsocket", 
			ErrorType, WSAGetLastError());
	}
	else
	{
		// �õ�֡����
		dwFrameCount = dwFrameCount / iRcvFrameSize;
	}
	return dwFrameCount;
}
// �õ�֡����
MatrixServerDll_API bool GetFrameData(SOCKET oSocket, char* pFrameData, int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	bool bReturn = false;
	sockaddr_in AddrFrom;
	int iSize = sizeof(AddrFrom);
	int iCount = recvfrom(oSocket, pFrameData, iRcvFrameSize, 0, reinterpret_cast<sockaddr*>(&AddrFrom), &iSize);
	if(iCount == iRcvFrameSize)	//֡��С��ȷ
	{
		bReturn = true;
	}
	else if (iCount == SOCKET_ERROR)
	{
		AddMsgToLogOutPutList(pLogOutPut, "GetFrameData", "recvfrom", 
			ErrorType, WSAGetLastError());
	}
	else
	{
		AddMsgToLogOutPutList(pLogOutPut, "GetFrameData", "recvfrom", 
			ErrorType, IDS_ERR_RCVFRAMESIZE);
	}
	return bReturn;
}
// ��ս���֡������
MatrixServerDll_API void ClearRcvFrameBuf(SOCKET oSocket, char* pFrameData, int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut = NULL)
{
	sockaddr_in AddrFrom;
	int iSize = sizeof(AddrFrom);
	DWORD dwFrameCount = 0;
	int iCount = 0;
	while (true)
	{
		// �õ�������ջ����������ֽ���
		if (SOCKET_ERROR == ioctlsocket(oSocket, FIONREAD, &dwFrameCount))
		{
			AddMsgToLogOutPutList(pLogOutPut, "ClearRcvFrameBuf", "ioctlsocket", 
				ErrorType, WSAGetLastError());
			break;
		}
		else
		{
			if(dwFrameCount > 0) 
			{
				iCount = recvfrom(oSocket, pFrameData, iRcvFrameSize, 0, reinterpret_cast<sockaddr*>(&AddrFrom), &iSize);
				if (iCount == SOCKET_ERROR)
				{
					AddMsgToLogOutPutList(pLogOutPut, "ClearRcvFrameBuf", "recvfrom", 
						ErrorType, WSAGetLastError());
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}
// ����֡
MatrixServerDll_API bool SendFrame(SOCKET oSocket, char* pFrameData,int iSndFrameSize, 
	unsigned short usPort, unsigned int uiIP, 
	m_oLogOutPutStruct* pLogOutPut = NULL)
{
	bool bReturn = false;
	// ����֡
	sockaddr_in addrSend;
	addrSend.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	addrSend.sin_port = htons(usPort);
	addrSend.sin_addr.S_un.S_addr = uiIP;
	int iCount = sendto(oSocket, pFrameData, iSndFrameSize, 0, 
		reinterpret_cast<sockaddr*>(&addrSend), sizeof(addrSend));
	if (iCount == iSndFrameSize)
	{
		bReturn = true;
	} 
	else if (iCount == SOCKET_ERROR)
	{
		AddMsgToLogOutPutList(pLogOutPut, "SendFrame", "sendto", ErrorType, WSAGetLastError());
	}
	else
	{
		AddMsgToLogOutPutList(pLogOutPut, "SendFrame", "sendto", ErrorType, IDS_ERR_SNDFRAMESIZE);
	}
	return bReturn;
}
// ����������Ϣ�ṹ��
MatrixServerDll_API m_oConstVarStruct* OnCreateConstVar(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oConstVarStruct* pConstVar = NULL;
	pConstVar = new m_oConstVarStruct;
	pConstVar->m_pFrameHeadCheck = NULL;
	pConstVar->m_pSetADCSetSine = NULL;
	pConstVar->m_pSetADCStopSample = NULL;
	pConstVar->m_pSetADCOpenTBPowerLow = NULL;
	pConstVar->m_pSetADCOpenTBPowerHigh = NULL;
	pConstVar->m_pSetADCOpenSwitchTBLow = NULL;
	pConstVar->m_pSetADCOpenSwitchTBHigh = NULL;
	pConstVar->m_pSetADCRegisterRead = NULL;
	pConstVar->m_pSetADCRegisterWrite = NULL;
	pConstVar->m_pSetADCTBSwitchOpen = NULL;
	pConstVar->m_pSetADCSample = NULL;
	pConstVar->m_pSetADCReadContinuous = NULL;
	pConstVar->m_pLogOutPut = pLogOutPut;
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
	int iTemp = 0;
	strFilePath = INIFilePath;
	if (_taccess(strFilePath, 0) == -1)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "LoadIniFile", "", 
			ErrorType, IDS_ERR_FILE_EXIST);
		return;
	}
	//	GetFileAttributes(strFilePath);
	try
	{
		//��ȡini�ļ�����Ӧ�ֶε�����
		strSection = _T("��������");					// ��ȡ��ǰ����

		strSectionKey=_T("OneSleepTime");				// һ�����ߵ�ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iOneSleepTime = _ttoi(strValue);

		strSectionKey=_T("LogOutPutSleepTimes");		// ��־����߳�д��־����ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iLogOutPutSleepTimes = _ttoi(strValue);

		strSectionKey=_T("HertBeatSleepTimes");			// �����̷߳�������֡��ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iHeartBeatSleepTimes = _ttoi(strValue);

		strSectionKey=_T("HeadFrameSleepTimes");		// �װ��߳̽����װ���ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iHeadFrameSleepTimes = _ttoi(strValue);

		strSectionKey=_T("IPSetFrameSleepTimes");		// IP��ַ�����߳���ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iIPSetFrameSleepTimes = _ttoi(strValue);

		strSectionKey=_T("TailFrameSleepTimes");		// β���߳���ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iTailFrameSleepTimes = _ttoi(strValue);

		strSectionKey=_T("MonitorRoutSleepTimes");		// ·�ɼ����߳���ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iMonitorRoutSleepTimes = _ttoi(strValue);

		strSectionKey=_T("TimeDelaySleepTimes");		// ʱͳ�����߳���ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iTimeDelaySleepTimes = _ttoi(strValue);

		strSectionKey=_T("ADCSetSleepTimes");			// ADC���������߳���ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iADCSetSleepTimes = _ttoi(strValue);

		strSectionKey=_T("CloseThreadSleepTimes");		// �ȴ��̹߳رյ���ʱ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iCloseThreadSleepTimes = _ttoi(strValue);

		strSectionKey=_T("HeadFrameStableNum");			// �װ��ȶ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iHeadFrameStableTimes = _ttoi(strValue);

		strSectionKey=_T("IPAddrResetTimes");		// IP��ַ�������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iIPAddrResetTimes = _ttoi(strValue);

		strSectionKey=_T("TailFrameStableTimes");		// β���ȶ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iTailFrameStableTimes = _ttoi(strValue);

		strSectionKey=_T("MonitorRoutStableTime");		// ·�ɼ����ȶ�ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iMonitorRoutStableTime = _ttoi(strValue);

		strSectionKey=_T("LineSysStableTime");		// ����ϵͳ�ﵽ�ȶ�״̬ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iLineSysStableTime = _ttoi(strValue);

		strSectionKey=_T("ADCSetOptNb");			// ADC�������ò������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iADCSetOptNb = _ttoi(strValue);

		strSectionKey=_T("ADCStartSampleOptNb");	// ADC��ʼ�ɼ��������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iADCStartSampleOptNb = _ttoi(strValue);

		strSectionKey=_T("ADCStopSampleOptNb");		// ADCֹͣ�ɼ��������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iADCStopSampleOptNb = _ttoi(strValue);

		strSectionKey=_T("InstrumentTypeLAUX");		// ��������-����վ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iInstrumentTypeLAUX = _ttoi(strValue);

		strSectionKey=_T("InstrumentTypeLAUL");		// ��������-��Դվ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iInstrumentTypeLAUL = _ttoi(strValue);

		strSectionKey=_T("InstrumentTypeFDU");		// ��������-�ɼ�վ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iInstrumentTypeFDU = _ttoi(strValue);

		strSectionKey=_T("InstrumentTypeLCI");		// ��������-LCI
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iInstrumentTypeLCI= _ttoi(strValue);

		strSectionKey=_T("DirectionTop");			// �����Ϸ�
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iDirectionTop = _ttoi(strValue);

		strSectionKey=_T("DirectionDown");			// �����·�
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iDirectionDown = _ttoi(strValue);

		strSectionKey=_T("DirectionLeft");			// ������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iDirectionLeft = _ttoi(strValue);

		strSectionKey=_T("DirectionRight");			// �����ҷ�
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iDirectionRight = _ttoi(strValue);

		strSectionKey=_T("DirectionCenter");		// ��������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iDirectionCenter = _ttoi(strValue);

		strSectionKey=_T("IPSetAddrStart");			// IP��ַ���õ���ʼ��ַ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iIPSetAddrStart = _ttoi(strValue);

		strSectionKey=_T("IPSetAddrInterval");		// IP��ַ���õļ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iIPSetAddrInterval = _ttoi(strValue);

		strSectionKey=_T("RoutSetAddrStart");		// ·�ɵ�ַ���õ���ʼ��ַ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iRoutSetAddrStart = _ttoi(strValue);

		strSectionKey=_T("RoutSetAddrInterval");	// ·�ɵ�ַ���õļ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iRoutSetAddrInterval = _ttoi(strValue);

		strSectionKey=_T("BroadcastPortStart");		// ���ù㲥�˿���ʼ��ַ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_iBroadcastPortStart, sizeof(int));

		strSectionKey=_T("IPBroadcastAddr");		// ����Ϊ�㲥IP
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_iIPBroadcastAddr, sizeof(int));

		//��ȡini�ļ�����Ӧ�ֶε�����
		strSection = _T("֡��ʽ����");			// ��ȡ��ǰ����
		strSectionKey=_T("FrameHeadSize");		// ֡ͷ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iFrameHeadSize = _ttoi(strValue);

		strSectionKey=_T("FrameHeadCheck");		// ͬ��֡ͷ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pFrameHeadCheck, pConstVar->m_iFrameHeadSize, strValue);

		strSectionKey=_T("FrameCmdSize1B");		// �����ֳ���1�ֽ�
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iFrameCmdSize1B = _ttoi(strValue);

		strSectionKey=_T("FramePacketSize1B");	// ���������1�ֽ�
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iFramePacketSize1B = _ttoi(strValue);

		strSectionKey=_T("FramePacketSize2B");	// ���������2�ֽ�
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iFramePacketSize2B = _ttoi(strValue);

		strSectionKey=_T("FramePacketSize4B");	// ���������4�ֽ�
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iFramePacketSize4B = _ttoi(strValue);

		strSectionKey=_T("ADCDataSize3B");		// ADC������ռ�ֽ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iADCDataSize3B = _ttoi(strValue);

		strSectionKey=_T("CommandWordMaxNum");	// �����ָ������ֵ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iCommandWordMaxNum = _ttoi(strValue);
		pConstVar->m_iADCSetCommandMaxByte = pConstVar->m_iCommandWordMaxNum * pConstVar->m_iFramePacketSize4B;
		strSectionKey=_T("SndFrameBufInit");	// ����֡��������ֵ�趨
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_bySndFrameBufInit = static_cast<char>(iTemp);

		strSectionKey=_T("RcvFrameSize");		// ���յ���������֡֡����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iRcvFrameSize = _ttoi(strValue);

		strSectionKey=_T("SndFrameSize");		// ���͵���������֡֡����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSndFrameSize = _ttoi(strValue);

		/////////////////////////////////////////////////////////////////////////
		strSection = _T("���������豸����������");		// ��ȡ��ǰ����
		strSectionKey=_T("SendSetCmd");			// ������������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usSendSetCmd = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("SendQueryCmd");		// ���Ͳ�ѯ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usSendQueryCmd = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("SendADCCmd");			// ����ADC���������ط�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usSendADCCmd = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdSn");				// ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdSn = static_cast<char>(iTemp);

		strSectionKey=_T("CmdHeadFrameTime");	// �װ�ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdHeadFrameTime = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLocalIPAddr");		// ����IP��ַ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_byCmdLocalIPAddr, sizeof(char));

		strSectionKey=_T("CmdLocalSysTime");	// ����ϵͳʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLocalSysTime = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLocalTimeFixedHigh");	// ����ʱ��������λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLocalTimeFixedHigh = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLocalTimeFixedLow");	// ����ʱ��������λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLocalTimeFixedLow = static_cast<char>(iTemp);

		strSectionKey=_T("CmdADCDataReturnAddr");	// �Զ����ݷ��ص�ַ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdADCDataReturnAddr = static_cast<char>(iTemp);

		strSectionKey=_T("CmdADCDataReturnPort");	// �Զ����ݷ��ض˿ں�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdADCDataReturnPort = static_cast<char>(iTemp);

		strSectionKey=_T("CmdADCDataReturnPortLimit");	// �˿ڵ������޺�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdADCDataReturnPortLimit = static_cast<char>(iTemp);

		strSectionKey=_T("CmdSetBroadCastPort");	// ��������ȴ��˿ں�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdBroadCastPortSet = static_cast<char>(iTemp);

		strSectionKey=_T("CmdFDUErrorCode");		// ϵͳӲ��״̬����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdFDUErrorCode = static_cast<char>(iTemp);

		strSectionKey=_T("CmdTBHigh");				// TBʱ�̸�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdTBHigh = static_cast<char>(iTemp);

		strSectionKey=_T("CmdTbLow");				// TBʱ�̵�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdTbLow = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXRoutOpenQuery");	// work_ctrl ����վ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLAUXRoutOpenQuery = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXRoutOpenSet");		// ·�ɿ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLAUXRoutOpenSet = static_cast<char>(iTemp);

		strSectionKey=_T("CmdTailRecSndTimeLow");	// β������\����ʱ�̵�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdTailRecSndTime = static_cast<char>(iTemp);

		strSectionKey=_T("CmdBroadCastPortSet");	// �㲥����ȴ��˿�ƥ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdBroadCastPortSeted = static_cast<char>(iTemp);

		strSectionKey=_T("CmdADCSet");				// ����ADC��������������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdADCSet = static_cast<char>(iTemp);

		strSectionKey=_T("CmdNetTime");				// ����ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdNetTime = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLineTailRecTimeLAUX");	// ����վ����β������ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLineTailRecTimeLAUX = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUTailRecTimeLAUX");	// ����վ������β������ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLAUTailRecTimeLAUX = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXErrorCode1");		// ����վ����1
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLAUXErrorCode1 = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXErrorCode2");		// ����վ����2
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLAUXErrorCode2 = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXSetRout");			// ����վ·�ɷ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdLAUXSetRout = static_cast<char>(iTemp);

		strSectionKey=_T("CmdReturnRout");			// ����·��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdReturnRout = static_cast<char>(iTemp);

		strSectionKey=_T("CmdEnd");					// ���������������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_byCmdEnd = static_cast<char>(iTemp);

		//��ȡini�ļ�����Ӧ�ֶε�����
		strSection = _T("ADC��������");			// ��ȡ��ǰ����
		strSectionKey=_T("SetADCSetSineSize");	// ADC�������Ҳ������С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCSetSineSize = _ttoi(strValue);

		strSectionKey=_T("SetADCSetSine");		// ADC�������Ҳ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCSetSine, pConstVar->m_iSetADCSetSineSize, strValue);

		strSectionKey=_T("SetADCStopSampleSize");	// ADC����ֹͣ���������С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCStopSampleSize = _ttoi(strValue);

		strSectionKey=_T("SetADCStopSample");		// ADC����ֹͣ��������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCStopSample, pConstVar->m_iSetADCStopSampleSize, strValue);

		strSectionKey=_T("SetADCOpenTBPowerLowSize");	// ADC���ô�TB��Դ��λ��С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCOpenTBPowerLowSize = _ttoi(strValue);

		strSectionKey=_T("SetADCOpenTBPowerLow");		// ADC���ô�TB��Դ��λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCOpenTBPowerLow, pConstVar->m_iSetADCOpenTBPowerLowSize, strValue);

		strSectionKey=_T("m_iSetADCOpenTBPowerHighSize");	// ADC���ô�TB��Դ��λ��С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCOpenTBPowerHighSize = _ttoi(strValue);

		strSectionKey=_T("m_iSetADCOpenTBPowerHigh");		// ADC���ô�TB��Դ��λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCOpenTBPowerHigh, pConstVar->m_iSetADCOpenTBPowerHighSize, strValue);

		strSectionKey=_T("SetADCOpenSwitchTBLowSize");	// ADC���ô�TB���ص�λ��С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCOpenSwitchTBLowSize = _ttoi(strValue);

		strSectionKey=_T("SetADCOpenSwitchTBLow");		// ADC���ô�TB���ص�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCOpenSwitchTBLow, pConstVar->m_iSetADCOpenSwitchTBLowSize, strValue);

		strSectionKey=_T("SetADCOpenSwitchTBHighSize");	// ADC���ô�TB���ظ�λ��С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCOpenSwitchTBHighSize = _ttoi(strValue);

		strSectionKey=_T("SetADCOpenSwitchTBHigh");		// ADC���ô�TB���ظ�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCOpenSwitchTBHigh, pConstVar->m_iSetADCOpenSwitchTBHighSize, strValue);

		strSectionKey=_T("SetADCRegisterReadSize");	// ADC���ö��Ĵ�����С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCRegisterReadSize = _ttoi(strValue);

		strSectionKey=_T("SetADCRegisterRead");		// ADC���ö��Ĵ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCRegisterRead, pConstVar->m_iSetADCRegisterReadSize, strValue);

		strSectionKey=_T("SetADCRegisterWriteSize");	// ADC����д�Ĵ�����С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCRegisterWriteSize = _ttoi(strValue);

		strSectionKey=_T("SetADCRegisterWrite");		// ADC����д�Ĵ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCRegisterWrite, pConstVar->m_iSetADCRegisterWriteSize, strValue);

		strSectionKey=_T("SetADCTBSwitchOpenSize");	// ADC���ô�TB���ش�С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCTBSwitchOpenSize = _ttoi(strValue);

		strSectionKey=_T("SetADCTBSwitchOpen");		// ADC���ô�TB����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCTBSwitchOpen, pConstVar->m_iSetADCTBSwitchOpenSize, strValue);

		strSectionKey=_T("SetADCSampleSize");	// ADC�������ô�С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCSampleSize = _ttoi(strValue);

		strSectionKey=_T("SetADCSample");		// ADC��������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCSample, pConstVar->m_iSetADCSampleSize, strValue);

		strSectionKey=_T("SetADCReadContinuousSize");	// ADC��������������С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCReadContinuousSize = _ttoi(strValue);

		strSectionKey=_T("SetADCReadContinuous");		// ADC������������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_pSetADCReadContinuous, pConstVar->m_iSetADCReadContinuousSize, strValue);

		strSectionKey=_T("TBSleepTimeHigh");			// TB������ʱ��λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_uiTBSleepTimeHigh, sizeof(int));

		strSectionKey=_T("TBSleepTimeLow");				// TB������ʱ��λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usTBSleepTimeLow = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdTBCtrlStartSample");		// TB���ؿ���ADC���ݲɼ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usCmdTBCtrlStartSample = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdTBLoseCtrlStartSample");	// ����TB���ؿ���ADC���ݲɼ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usCmdTBLoseCtrlStartSample = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdTBCtrlStopSample");		// TB���ؿ���ADC����ֹͣ�ɼ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usCmdTBCtrlStopSample = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdCtrlCloseLed");			// LED����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usCmdCtrlCloseLed = static_cast<unsigned short>(iTemp);
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
MatrixServerDll_API void OnInitConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	LoadIniFile(pConstVar);
}
// �رճ�����Ϣ�ṹ��
MatrixServerDll_API void OnCloseConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar->m_pFrameHeadCheck != NULL)
	{
		delete[] pConstVar->m_pFrameHeadCheck;
	}
	if (pConstVar->m_pSetADCSetSine != NULL)
	{
		delete[] pConstVar->m_pSetADCSetSine;
	}
	if (pConstVar->m_pSetADCStopSample != NULL)
	{
		delete[] pConstVar->m_pSetADCStopSample;
	}
	if (pConstVar->m_pSetADCOpenTBPowerLow != NULL)
	{
		delete[] pConstVar->m_pSetADCOpenTBPowerLow;
	}
	if (pConstVar->m_pSetADCOpenTBPowerHigh != NULL)
	{
		delete[] pConstVar->m_pSetADCOpenTBPowerHigh;
	}
	if (pConstVar->m_pSetADCOpenSwitchTBLow != NULL)
	{
		delete[] pConstVar->m_pSetADCOpenSwitchTBLow;
	}
	if (pConstVar->m_pSetADCOpenSwitchTBHigh != NULL)
	{
		delete[] pConstVar->m_pSetADCOpenSwitchTBHigh;
	}
	if (pConstVar->m_pSetADCRegisterRead != NULL)
	{
		delete[] pConstVar->m_pSetADCRegisterRead;
	}
	if (pConstVar->m_pSetADCRegisterWrite != NULL)
	{
		delete[] pConstVar->m_pSetADCRegisterWrite;
	}
	if (pConstVar->m_pSetADCTBSwitchOpen != NULL)
	{
		delete[] pConstVar->m_pSetADCTBSwitchOpen;
	}
	if (pConstVar->m_pSetADCSample != NULL)
	{
		delete[] pConstVar->m_pSetADCSample;
	}
	if (pConstVar->m_pSetADCReadContinuous != NULL)
	{
		delete[] pConstVar->m_pSetADCReadContinuous;
	}
}
// �ͷų�����Ϣ�ṹ��
MatrixServerDll_API void OnFreeConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	delete pConstVar;
}
// ��������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(m_oLogOutPutStruct* pLogOutPut = NULL)
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
		AddMsgToLogOutPutList(pCommInfo->m_pLogOutPut, "OpenAppIniXMLFile", "CreateDispatch",
			ErrorType, IDS_ERR_XMLINTERFACE);
		return FALSE;
	}
	oVariant = CommXMLFilePath;
	if (_taccess(CommXMLFilePath, 0) == -1)
	{
		AddMsgToLogOutPutList(pCommInfo->m_pLogOutPut, "OpenAppIniXMLFile", "",
			ErrorType, IDS_ERR_FILE_EXIST);
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
		// LCI��IP��ַ
		strKey = _T("IPLCI");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		pCommInfo->m_uiAimIP = inet_addr(ConvertCStrToStr(csDstIP).c_str());
		// ADC���ݷ��ص�ַ
		strKey = _T("IPForADCData");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		pCommInfo->m_uiADCDataReturnAddr = inet_addr(ConvertCStrToStr(csDstIP).c_str());
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
		pCommInfo->m_usAimPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForHeartBeat");
		pCommInfo->m_usHeartBeatReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForHeadFrame");
		pCommInfo->m_usHeadFramePort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForIPSet");
		pCommInfo->m_usIPSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTailFrame");
		pCommInfo->m_usTailFramePort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTailTimeFrame");
		pCommInfo->m_usTailTimeReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTimeSet");
		pCommInfo->m_usTimeDelayReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCSet");
		pCommInfo->m_usADCSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCData");
		pCommInfo->m_usADCDataReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
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
MatrixServerDll_API void OnInitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	LoadLineServerAppSetupData(pCommInfo);
}
// �ͷ�����ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	delete pCommInfo;
}
// ��������֡��Ϣ�ṹ��
MatrixServerDll_API m_oHeartBeatFrameStruct* OnCreateInstrumentHeartBeat(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oHeartBeatFrameStruct* pHeartBeatFrame = NULL;
	pHeartBeatFrame = new m_oHeartBeatFrameStruct;
	InitializeCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	pHeartBeatFrame->m_pcSndFrameData = NULL;
	pHeartBeatFrame->m_pcCommandWord = NULL;
	pHeartBeatFrame->m_oHeartBeatSocket = INVALID_SOCKET;
	pHeartBeatFrame->m_pCommandStruct = NULL;
	pHeartBeatFrame->m_pLogOutPut = pLogOutPut;
	return pHeartBeatFrame;
}
// ��ʼ������
MatrixServerDll_API void OnWorkInstrumentHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pHeartBeatFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentHeartBeat", "pHeartBeatFrame",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentHeartBeat", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	if (pHeartBeatFrame->m_pCommandStruct != NULL)
	{
		delete pHeartBeatFrame->m_pCommandStruct;
	}
	pHeartBeatFrame->m_pCommandStruct = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pHeartBeatFrame->m_pCommandStruct->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pHeartBeatFrame->m_pCommandStruct->m_uiAimIP = pCommInfo->m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pHeartBeatFrame->m_pCommandStruct->m_usAimPort = pCommInfo->m_usAimPort;
	// �������ض˿�
	pHeartBeatFrame->m_pCommandStruct->m_usReturnPort = pCommInfo->m_usHeartBeatReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pHeartBeatFrame->m_pCommandStruct->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pHeartBeatFrame->m_pCommandStruct);
	// ��շ���֡������
	if (pHeartBeatFrame->m_pcSndFrameData != NULL)
	{
		delete[] pHeartBeatFrame->m_pcSndFrameData;
	}
	pHeartBeatFrame->m_pcSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pHeartBeatFrame->m_pcSndFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iSndFrameSize);
	// ������������ּ���
	if (pHeartBeatFrame->m_pcCommandWord != NULL)
	{
		delete pHeartBeatFrame->m_pcCommandWord;
	}
	pHeartBeatFrame->m_pcCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pHeartBeatFrame->m_pcCommandWord, pConstVar->m_bySndFrameBufInit, pConstVar->m_iCommandWordMaxNum);
	// ���������ָ���
	pHeartBeatFrame->m_usCommandWordNum = 0;
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// �ر�����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame)
{
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	if (pHeartBeatFrame->m_pcSndFrameData != NULL)
	{
		delete[] pHeartBeatFrame->m_pcSndFrameData;
	}
	if (pHeartBeatFrame->m_pcCommandWord != NULL)
	{
		delete[] pHeartBeatFrame->m_pcCommandWord;
	}
	if (pHeartBeatFrame->m_pCommandStruct != NULL)
	{
		delete pHeartBeatFrame->m_pCommandStruct;
	}
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// �ͷ�����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame)
{
	if (pHeartBeatFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	delete pHeartBeatFrame;
}
// �����װ�֡��Ϣ�ṹ��
MatrixServerDll_API m_oHeadFrameStruct* OnCreateInstrumentHeadFrame(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oHeadFrameStruct* pHeadFrame = NULL;
	pHeadFrame = new m_oHeadFrameStruct;
	InitializeCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	pHeadFrame->m_pcRcvFrameData = NULL;
	pHeadFrame->m_oHeadFrameSocket = INVALID_SOCKET;
	pHeadFrame->m_pCommandStruct = NULL;
	pHeadFrame->m_pLogOutPut = pLogOutPut;
	return pHeadFrame;
}
// ��ʼ���װ�
MatrixServerDll_API void OnWorkInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pHeadFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentHeadFrame", "pHeadFrame",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentHeadFrame", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	if (pHeadFrame->m_pCommandStruct != NULL)
	{
		delete pHeadFrame->m_pCommandStruct;
	}
	pHeadFrame->m_pCommandStruct = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pHeadFrame->m_pCommandStruct->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pHeadFrame->m_pCommandStruct->m_uiAimIP = pCommInfo->m_uiAimIP;
	// �װ����ջ�����֡���趨Ϊ��������
	pHeadFrame->m_uiRcvBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ���ն˿�
	pHeadFrame->m_pCommandStruct->m_usReturnPort = pCommInfo->m_usHeadFramePort;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pHeadFrame->m_pCommandStruct);
	// ��ս���֡������
	if (pHeadFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pHeadFrame->m_pcRcvFrameData;
	}
	pHeadFrame->m_pcRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pHeadFrame->m_pcRcvFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
}
// �ر��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame)
{
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	if (pHeadFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pHeadFrame->m_pcRcvFrameData;
	}
	if (pHeadFrame->m_pCommandStruct != NULL)
	{
		delete pHeadFrame->m_pCommandStruct;
	}
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
}
// �ͷ��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame)
{
	if (pHeadFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	delete pHeadFrame;
}
// ����IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API m_oIPSetFrameStruct* OnCreateInstrumentIPSetFrame(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oIPSetFrameStruct* pIPSetFrame = NULL;
	pIPSetFrame = new m_oIPSetFrameStruct;
	InitializeCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	pIPSetFrame->m_pcSndFrameData = NULL;
	pIPSetFrame->m_pcCommandWord = NULL;
	pIPSetFrame->m_pcRcvFrameData = NULL;
	pIPSetFrame->m_oIPSetFrameSocket = INVALID_SOCKET;
	pIPSetFrame->m_pCommandStructSet = NULL;
	pIPSetFrame->m_pCommandStructReturn = NULL;
	pIPSetFrame->m_pLogOutPut = pLogOutPut;
	return pIPSetFrame;
}
// ��ʼ��IP��ַ����
MatrixServerDll_API void OnWorkInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pIPSetFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentIPSetFrame", "pIPSetFrame",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentIPSetFrame", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	if (pIPSetFrame->m_pCommandStructSet != NULL)
	{
		delete pIPSetFrame->m_pCommandStructSet;
	}
	pIPSetFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pIPSetFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pIPSetFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pIPSetFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_usAimPort;
	// IP��ַ���÷��ͻ�����֡���趨Ϊ��������
	pIPSetFrame->m_uiSndBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iSndFrameSize;
	// IP��ַ����Ӧ����ջ�����֡���趨Ϊ��������
	pIPSetFrame->m_uiRcvBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iRcvFrameSize;
	// IP��ַ���÷��ض˿�
	pIPSetFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_usIPSetReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pIPSetFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pIPSetFrame->m_pcSndFrameData != NULL)
	{
		delete[] pIPSetFrame->m_pcSndFrameData;
	}
	pIPSetFrame->m_pcSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pIPSetFrame->m_pcSndFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iSndFrameSize);
	// ���IP��ַ���������ּ���
	if (pIPSetFrame->m_pcCommandWord != NULL)
	{
		delete[] pIPSetFrame->m_pcCommandWord;
	}
	pIPSetFrame->m_pcCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pIPSetFrame->m_pcCommandWord, pConstVar->m_bySndFrameBufInit, pConstVar->m_iCommandWordMaxNum);
	// IP��ַ���������ָ���
	pIPSetFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pIPSetFrame->m_pCommandStructReturn != NULL)
	{
		delete pIPSetFrame->m_pCommandStructReturn;
	}
	pIPSetFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pIPSetFrame->m_pCommandStructReturn);
	// ��ս���֡������
	if (pIPSetFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pIPSetFrame->m_pcRcvFrameData;
	}
	pIPSetFrame->m_pcRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pIPSetFrame->m_pcRcvFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// �ر�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame)
{
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	if (pIPSetFrame->m_pcSndFrameData != NULL)
	{
		delete[] pIPSetFrame->m_pcSndFrameData;
	}
	if (pIPSetFrame->m_pcCommandWord != NULL)
	{
		delete[] pIPSetFrame->m_pcCommandWord;
	}
	if (pIPSetFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pIPSetFrame->m_pcRcvFrameData;
	}
	if (pIPSetFrame->m_pCommandStructSet != NULL)
	{
		delete pIPSetFrame->m_pCommandStructSet;
	}
	if (pIPSetFrame->m_pCommandStructReturn != NULL)
	{
		delete pIPSetFrame->m_pCommandStructReturn;
	}
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// �ͷ�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame)
{
	if (pIPSetFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	delete pIPSetFrame;
}
// ����β��֡��Ϣ�ṹ��
MatrixServerDll_API m_oTailFrameStruct* OnCreateInstrumentTailFrame(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oTailFrameStruct* pTailFrame = NULL;
	pTailFrame = new m_oTailFrameStruct;
	InitializeCriticalSection(&pTailFrame->m_oSecTailFrame);
	pTailFrame->m_pcRcvFrameData = NULL;
	pTailFrame->m_oTailFrameSocket = INVALID_SOCKET;
	pTailFrame->m_pCommandStruct = NULL;
	pTailFrame->m_pLogOutPut = pLogOutPut;
	return pTailFrame;
}
// ��ʼ��β��
MatrixServerDll_API void OnWorkInstrumentTailFrame(m_oTailFrameStruct* pTailFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pTailFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentTailFrame", "pTailFrame",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentTailFrame", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pTailFrame->m_oSecTailFrame);
	if (pTailFrame->m_pCommandStruct != NULL)
	{
		delete pTailFrame->m_pCommandStruct;
	}
	pTailFrame->m_pCommandStruct = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pTailFrame->m_pCommandStruct->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pTailFrame->m_pCommandStruct->m_uiAimIP = pCommInfo->m_uiAimIP;
	// β�����ջ�����֡���趨Ϊ��������
	pTailFrame->m_uiRcvBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ���ն˿�
	pTailFrame->m_pCommandStruct->m_usReturnPort = pCommInfo->m_usTailFramePort;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pTailFrame->m_pCommandStruct);
	// ��ս���֡������
	if (pTailFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pTailFrame->m_pcRcvFrameData;
	}
	pTailFrame->m_pcRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pTailFrame->m_pcRcvFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pTailFrame->m_oSecTailFrame);
}
// �ر�β��֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentTailFrame(m_oTailFrameStruct* pTailFrame)
{
	EnterCriticalSection(&pTailFrame->m_oSecTailFrame);
	if (pTailFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pTailFrame->m_pcRcvFrameData;
	}
	if (pTailFrame->m_pCommandStruct != NULL)
	{
		delete pTailFrame->m_pCommandStruct;
	}
	LeaveCriticalSection(&pTailFrame->m_oSecTailFrame);
}
// �ͷ�β��֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentTailFrame(m_oTailFrameStruct* pTailFrame)
{
	if (pTailFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pTailFrame->m_oSecTailFrame);
	delete pTailFrame;
}
// ����β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API m_oTailTimeFrameStruct* OnCreateInstrumentTailTimeFrame(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oTailTimeFrameStruct* pTailTimeFrame = NULL;
	pTailTimeFrame = new m_oTailTimeFrameStruct;
	InitializeCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	pTailTimeFrame->m_pcRcvFrameData = NULL;
	pTailTimeFrame->m_pcSndFrameData = NULL;
	pTailTimeFrame->m_pcCommandWord = NULL;
	pTailTimeFrame->m_oTailTimeFrameSocket = INVALID_SOCKET;
	pTailTimeFrame->m_pCommandStructSet = NULL;
	pTailTimeFrame->m_pCommandStructReturn = NULL;
	pTailTimeFrame->m_pLogOutPut = pLogOutPut;
	return pTailTimeFrame;
}
// ��ʼ��β��ʱ��֡
MatrixServerDll_API void OnWorkInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pTailTimeFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentTailTimeFrame", "pTailTimeFrame",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentTailTimeFrame", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	if (pTailTimeFrame->m_pCommandStructSet != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructSet;
	}
	pTailTimeFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pTailTimeFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_usAimPort;
	// β��ʱ�̷��ͻ�����֡���趨Ϊ��������
	pTailTimeFrame->m_uiSndBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iSndFrameSize;
	// β��ʱ��Ӧ����ջ�����֡���趨Ϊ��������
	pTailTimeFrame->m_uiRcvBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iRcvFrameSize;
	// β��ʱ�̲�ѯ���ض˿�
	pTailTimeFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_usTailTimeReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pTailTimeFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pTailTimeFrame->m_pcSndFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_pcSndFrameData;
	}
	pTailTimeFrame->m_pcSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pTailTimeFrame->m_pcSndFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iSndFrameSize);
	// ���β��ʱ�̲�ѯ�����ּ���
	if (pTailTimeFrame->m_pcCommandWord != NULL)
	{
		delete[] pTailTimeFrame->m_pcCommandWord;
	}
	pTailTimeFrame->m_pcCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pTailTimeFrame->m_pcCommandWord, pConstVar->m_bySndFrameBufInit, pConstVar->m_iCommandWordMaxNum);
	// β��ʱ�̲�ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pTailTimeFrame->m_pCommandStructReturn != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructReturn;
	}
	pTailTimeFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pTailTimeFrame->m_pCommandStructReturn);
	// ��ս���֡������
	if (pTailTimeFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_pcRcvFrameData;
	}
	pTailTimeFrame->m_pcRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pTailTimeFrame->m_pcRcvFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// �ر�β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame)
{
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	if (pTailTimeFrame->m_pcSndFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_pcSndFrameData;
	}
	if (pTailTimeFrame->m_pcCommandWord != NULL)
	{
		delete[] pTailTimeFrame->m_pcCommandWord;
	}
	if (pTailTimeFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_pcRcvFrameData;
	}
	if (pTailTimeFrame->m_pCommandStructSet != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructSet;
	}
	if (pTailTimeFrame->m_pCommandStructReturn != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructReturn;
	}
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// �ͷ�β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame)
{
	if (pTailTimeFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	delete pTailTimeFrame;
}
// ����ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API m_oTimeDelayFrameStruct* OnCreateInstrumentTimeDelayFrame(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oTimeDelayFrameStruct* pTimeDelayFrame = NULL;
	pTimeDelayFrame = new m_oTimeDelayFrameStruct;
	InitializeCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	pTimeDelayFrame->m_pcRcvFrameData = NULL;
	pTimeDelayFrame->m_pcSndFrameData = NULL;
	pTimeDelayFrame->m_pcCommandWord = NULL;
	pTimeDelayFrame->m_oTimeDelayFrameSocket = INVALID_SOCKET;
	pTimeDelayFrame->m_pCommandStructSet = NULL;
	pTimeDelayFrame->m_pCommandStructReturn = NULL;
	pTimeDelayFrame->m_pLogOutPut = pLogOutPut;
	return pTimeDelayFrame;
}
// ��ʼ��ʱͳ����֡
MatrixServerDll_API void OnWorkInstrumentTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame,
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pTimeDelayFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentTimeDelayFrame", "pTimeDelayFrame",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentTimeDelayFrame", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	if (pTimeDelayFrame->m_pCommandStructSet != NULL)
	{
		delete pTimeDelayFrame->m_pCommandStructSet;
	}
	pTimeDelayFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pTimeDelayFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pTimeDelayFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pTimeDelayFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_usAimPort;
	// ʱͳ���÷��ͻ�����֡���趨Ϊ��������
	pTimeDelayFrame->m_uiSndBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iSndFrameSize;
	// ʱͳ����Ӧ����ջ�����֡���趨Ϊ��������
	pTimeDelayFrame->m_uiRcvBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ʱͳ���÷��ض˿�
	pTimeDelayFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_usTimeDelayReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pTimeDelayFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pTimeDelayFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pTimeDelayFrame->m_pcSndFrameData != NULL)
	{
		delete[] pTimeDelayFrame->m_pcSndFrameData;
	}
	pTimeDelayFrame->m_pcSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pTimeDelayFrame->m_pcSndFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iSndFrameSize);
	// ���ʱͳ���������ּ���
	if (pTimeDelayFrame->m_pcCommandWord != NULL)
	{
		delete[] pTimeDelayFrame->m_pcCommandWord;
	}
	pTimeDelayFrame->m_pcCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pTimeDelayFrame->m_pcCommandWord, pConstVar->m_bySndFrameBufInit, pConstVar->m_iCommandWordMaxNum);
	// ʱͳ���������ָ���
	pTimeDelayFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pTimeDelayFrame->m_pCommandStructReturn != NULL)
	{
		delete pTimeDelayFrame->m_pCommandStructReturn;
	}
	pTimeDelayFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pTimeDelayFrame->m_pCommandStructReturn);
	// ��ս���֡������
	if (pTimeDelayFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pTimeDelayFrame->m_pcRcvFrameData;
	}
	pTimeDelayFrame->m_pcRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pTimeDelayFrame->m_pcRcvFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
}
// �ر�ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame)
{
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	if (pTimeDelayFrame->m_pcSndFrameData != NULL)
	{
		delete[] pTimeDelayFrame->m_pcSndFrameData;
	}
	if (pTimeDelayFrame->m_pcCommandWord != NULL)
	{
		delete[] pTimeDelayFrame->m_pcCommandWord;
	}
	if (pTimeDelayFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pTimeDelayFrame->m_pcRcvFrameData;
	}
	if (pTimeDelayFrame->m_pCommandStructSet != NULL)
	{
		delete pTimeDelayFrame->m_pCommandStructSet;
	}
	if (pTimeDelayFrame->m_pCommandStructReturn != NULL)
	{
		delete pTimeDelayFrame->m_pCommandStructReturn;
	}
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
}
// �ͷ�ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame)
{
	if (pTimeDelayFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	delete pTimeDelayFrame;
}
// ����ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API m_oADCSetFrameStruct* OnCreateInstrumentADCSetFrame(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oADCSetFrameStruct* pADCSetFrame = NULL;
	pADCSetFrame = new m_oADCSetFrameStruct;
	InitializeCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	pADCSetFrame->m_pcRcvFrameData = NULL;
	pADCSetFrame->m_pcSndFrameData = NULL;
	pADCSetFrame->m_pcCommandWord = NULL;
	pADCSetFrame->m_oADCSetFrameSocket = INVALID_SOCKET;
	pADCSetFrame->m_pCommandStructSet = NULL;
	pADCSetFrame->m_pCommandStructReturn = NULL;
	pADCSetFrame->m_pLogOutPut = pLogOutPut;
	return pADCSetFrame;
}
// ��ʼ��ADC��������֡
MatrixServerDll_API void OnWorkInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pADCSetFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentADCSetFrame", "pADCSetFrame",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnWorkInstrumentADCSetFrame", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	if (pADCSetFrame->m_pCommandStructSet != NULL)
	{
		delete pADCSetFrame->m_pCommandStructSet;
	}
	pADCSetFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pADCSetFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pADCSetFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pADCSetFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_usAimPort;
	// ADC�������÷��ͻ�����֡���趨Ϊ��������
	pADCSetFrame->m_uiSndBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iSndFrameSize;
	// ADC��������Ӧ����ջ�����֡���趨Ϊ��������
	pADCSetFrame->m_uiRcvBufferSize = pCommInfo->m_uiInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ADC�������÷��ض˿�
	pADCSetFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_usADCSetReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pADCSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pADCSetFrame->m_pCommandStructSet);
	// ADC���ݷ��ص�ַ
	pADCSetFrame->m_pCommandStructSet->m_uiADCDataReturnAddr = pCommInfo->m_uiADCDataReturnAddr;
	// ADC���ݷ��ض˿�
	pADCSetFrame->m_pCommandStructSet->m_usADCDataReturnPort = pCommInfo->m_usADCDataReturnPort;
	// �Զ����ݷ������ad_cmd(7)=1���˿ڵ�����=0���˿ڲ���
	pADCSetFrame->m_pCommandStructSet->m_usADCDataReturnCmd = pConstVar->m_usSendADCCmd;
	// �˿ڵ�������
	pADCSetFrame->m_pCommandStructSet->m_usADCDataReturnPortLimitLow = pCommInfo->m_usADCDataReturnPort;
	// �˿ڵ�������
	pADCSetFrame->m_pCommandStructSet->m_usADCDataReturnPortLimitHigh = pCommInfo->m_usADCDataReturnPort;
	// ��շ���֡������
	if (pADCSetFrame->m_pcSndFrameData != NULL)
	{
		delete[] pADCSetFrame->m_pcSndFrameData;
	}
	pADCSetFrame->m_pcSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pADCSetFrame->m_pcSndFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iSndFrameSize);
	// ���ʱͳ���������ּ���
	if (pADCSetFrame->m_pcCommandWord != NULL)
	{
		delete[] pADCSetFrame->m_pcCommandWord;
	}
	pADCSetFrame->m_pcCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pADCSetFrame->m_pcCommandWord, pConstVar->m_bySndFrameBufInit, pConstVar->m_iCommandWordMaxNum);
	// ADC�������������ָ���
	pADCSetFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pADCSetFrame->m_pCommandStructReturn != NULL)
	{
		delete pADCSetFrame->m_pCommandStructReturn;
	}
	pADCSetFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pADCSetFrame->m_pCommandStructReturn);
	pADCSetFrame->m_pCommandStructReturn->m_pcADCSet = new char[pConstVar->m_iSndFrameSize];
	// ��ս���֡������
	if (pADCSetFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pADCSetFrame->m_pcRcvFrameData;
	}
	pADCSetFrame->m_pcRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pADCSetFrame->m_pcRcvFrameData, pConstVar->m_bySndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
}
// �ر�ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame)
{
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	if (pADCSetFrame->m_pcSndFrameData != NULL)
	{
		delete[] pADCSetFrame->m_pcSndFrameData;
	}
	if (pADCSetFrame->m_pcCommandWord != NULL)
	{
		delete[] pADCSetFrame->m_pcCommandWord;
	}
	if (pADCSetFrame->m_pcRcvFrameData != NULL)
	{
		delete[] pADCSetFrame->m_pcRcvFrameData;
	}
	if (pADCSetFrame->m_pCommandStructSet != NULL)
	{
		delete pADCSetFrame->m_pCommandStructSet;
	}
	if (pADCSetFrame->m_pCommandStructReturn->m_pcADCSet != NULL)
	{
		delete[] pADCSetFrame->m_pCommandStructReturn->m_pcADCSet;
	}
	if (pADCSetFrame->m_pCommandStructReturn != NULL)
	{
		delete pADCSetFrame->m_pCommandStructReturn;
	}
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
}
// �ͷ�ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame)
{
	if (pADCSetFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	delete pADCSetFrame;
}
// ��ʼ���׽��ֿ�
MatrixServerDll_API void OnInitSocketLib(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	WSADATA data;									// ����ṹ�����
	WORD w = MAKEWORD(2, 2);			// ��ʼ���׽��ְ汾��
	int err = WSAStartup(w, &data);							// ��ʼ���׽��ֿ�
	if (err == 0)
	{
		AddMsgToLogOutPutList(pLogOutPut, "InitSocketLib", "��ʼ���׽��ֿ�ɹ���");
	}
	else
	{
		AddMsgToLogOutPutList(pLogOutPut, "InitSocketLib", "��ʼ���׽��ֿ�ʧ�ܣ�",
			ErrorType, WSAGetLastError());
	}
}
// �ͷ��׽��ֿ�
MatrixServerDll_API void OnCloseSocketLib(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	// �ͷ��׽��ֿ�
	int err = WSACleanup();	
	if (err == 0)
	{
		AddMsgToLogOutPutList(pLogOutPut, "FreeSocketLib", "�ͷ��׽��ֿ�ɹ���");
	}
	else
	{
		AddMsgToLogOutPutList(pLogOutPut, "FreeSocketLib", "�ͷ��׽��ֿ�ʧ�ܣ�",
			ErrorType, WSAGetLastError());
	}
}
// �ر�Socket�׽���
MatrixServerDll_API void OnCloseSocket(SOCKET oSocket)
{
	if (oSocket == INVALID_SOCKET)
	{
		return;
	}
	shutdown(oSocket, SD_BOTH);
	closesocket(oSocket);
	oSocket = INVALID_SOCKET;
}
// ���������������˿�
MatrixServerDll_API void OnCreateAndSetHeartBeatSocket(m_oHeartBeatFrameStruct* pHeartBeatFrame)
{
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	// �����׽���
	pHeartBeatFrame->m_oHeartBeatSocket = CreateInstrumentSocket(pHeartBeatFrame->m_pCommandStruct->m_usReturnPort, 
		pHeartBeatFrame->m_pCommandStruct->m_uiSrcIP,
		pHeartBeatFrame->m_pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pHeartBeatFrame->m_oHeartBeatSocket, pHeartBeatFrame->m_pLogOutPut);
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	AddMsgToLogOutPutList(pHeartBeatFrame->m_pLogOutPut, "OnCreateAndSetHeartBeatSocket", "���������������˿ڣ�");
}

// �����������װ��˿�
MatrixServerDll_API void OnCreateAndSetHeadFrameSocket(m_oHeadFrameStruct* pHeadFrame)
{
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	// �����׽���
	pHeadFrame->m_oHeadFrameSocket = CreateInstrumentSocket(pHeadFrame->m_pCommandStruct->m_usReturnPort, 
		pHeadFrame->m_pCommandStruct->m_uiSrcIP,
		pHeadFrame->m_pLogOutPut);
	// ���ý��ջ�����
	SetRcvBufferSize(pHeadFrame->m_oHeadFrameSocket, pHeadFrame->m_uiRcvBufferSize, pHeadFrame->m_pLogOutPut);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	AddMsgToLogOutPutList(pHeadFrame->m_pLogOutPut, "OnCreateAndSetHeadFrameSocket", "�����������װ��˿ڣ�");
}
// ����������IP��ַ���ö˿�
MatrixServerDll_API void OnCreateAndSetIPSetFrameSocket(m_oIPSetFrameStruct* pIPSetFrame)
{
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// �����׽���
	pIPSetFrame->m_oIPSetFrameSocket = CreateInstrumentSocket(pIPSetFrame->m_pCommandStructSet->m_usReturnPort, 
		pIPSetFrame->m_pCommandStructSet->m_uiSrcIP,
		pIPSetFrame->m_pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_uiSndBufferSize, pIPSetFrame->m_pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_uiRcvBufferSize, pIPSetFrame->m_pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	AddMsgToLogOutPutList(pIPSetFrame->m_pLogOutPut, "OnCreateAndSetIPSetFrameSocket", "����������IP��ַ���ö˿ڣ�");
}
// ����������β���˿�
MatrixServerDll_API void OnCreateAndSetTailFrameSocket(m_oTailFrameStruct* pTailFrame)
{
	EnterCriticalSection(&pTailFrame->m_oSecTailFrame);
	// �����׽���
	pTailFrame->m_oTailFrameSocket = CreateInstrumentSocket(pTailFrame->m_pCommandStruct->m_usReturnPort, 
		pTailFrame->m_pCommandStruct->m_uiSrcIP,
		pTailFrame->m_pLogOutPut);
	// ���ý��ջ�����
	SetRcvBufferSize(pTailFrame->m_oTailFrameSocket, pTailFrame->m_uiRcvBufferSize, pTailFrame->m_pLogOutPut);
	LeaveCriticalSection(&pTailFrame->m_oSecTailFrame);
	AddMsgToLogOutPutList(pTailFrame->m_pLogOutPut, "OnCreateAndSetTailFrameSocket", "����������β���˿ڣ�");
}
// ����������β��ʱ�̶˿�
MatrixServerDll_API void OnCreateAndSetTailTimeFrameSocket(m_oTailTimeFrameStruct* pTailTimeFrame)
{
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	// �����׽���
	pTailTimeFrame->m_oTailTimeFrameSocket = CreateInstrumentSocket(pTailTimeFrame->m_pCommandStructSet->m_usReturnPort, 
		pTailTimeFrame->m_pCommandStructSet->m_uiSrcIP,
		pTailTimeFrame->m_pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pTailTimeFrame->m_oTailTimeFrameSocket, pTailTimeFrame->m_pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pTailTimeFrame->m_oTailTimeFrameSocket, pTailTimeFrame->m_uiSndBufferSize, pTailTimeFrame->m_pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pTailTimeFrame->m_oTailTimeFrameSocket, pTailTimeFrame->m_uiRcvBufferSize, pTailTimeFrame->m_pLogOutPut);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	AddMsgToLogOutPutList(pTailTimeFrame->m_pLogOutPut, "OnCreateAndSetTailTimeFrameSocket", "����������β��ʱ�̲�ѯ֡�˿ڣ�");
}
// ����������ʱͳ���ö˿�
MatrixServerDll_API void OnCreateAndSetTimeDelayFrameSocket(m_oTimeDelayFrameStruct* pTimeDelayFrame)
{
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	// �����׽���
	pTimeDelayFrame->m_oTimeDelayFrameSocket = CreateInstrumentSocket(pTimeDelayFrame->m_pCommandStructSet->m_usReturnPort, 
		pTimeDelayFrame->m_pCommandStructSet->m_uiSrcIP,
		pTimeDelayFrame->m_pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pTimeDelayFrame->m_oTimeDelayFrameSocket, pTimeDelayFrame->m_pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pTimeDelayFrame->m_oTimeDelayFrameSocket, pTimeDelayFrame->m_uiSndBufferSize, pTimeDelayFrame->m_pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pTimeDelayFrame->m_oTimeDelayFrameSocket, pTimeDelayFrame->m_uiRcvBufferSize, pTimeDelayFrame->m_pLogOutPut);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	AddMsgToLogOutPutList(pTimeDelayFrame->m_pLogOutPut, "OnCreateAndSetTimeDelayFrameSocket", "����������ʱͳ����֡�˿ڣ�");
}
// ����������ADC�������ö˿�
MatrixServerDll_API void OnCreateAndSetADCSetFrameSocket(m_oADCSetFrameStruct* pADCSetFrame)
{
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	// �����׽���
	pADCSetFrame->m_oADCSetFrameSocket = CreateInstrumentSocket(pADCSetFrame->m_pCommandStructSet->m_usReturnPort, 
		pADCSetFrame->m_pCommandStructSet->m_uiSrcIP,
		pADCSetFrame->m_pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pADCSetFrame->m_oADCSetFrameSocket, pADCSetFrame->m_pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pADCSetFrame->m_oADCSetFrameSocket, pADCSetFrame->m_uiSndBufferSize, pADCSetFrame->m_pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pADCSetFrame->m_oADCSetFrameSocket, pADCSetFrame->m_uiRcvBufferSize, pADCSetFrame->m_pLogOutPut);
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	AddMsgToLogOutPutList(pADCSetFrame->m_pLogOutPut, "OnCreateAndSetADCSetFrameSocket", "����������ADC��������֡�˿ڣ�");
}
// ��ս��ջ�����
MatrixServerDll_API void OnClearSocketRcvBuf(SOCKET oSocket, m_oConstVarStruct* pConstVar)
{
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// ���ջ�����
	char* pcRcvFrameData = NULL;
	pcRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(oSocket,pConstVar->m_iRcvFrameSize);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			GetFrameData(oSocket, pcRcvFrameData, pConstVar->m_iRcvFrameSize);		
		}		
	}
	delete[] pcRcvFrameData;
}

// ������Ϣ����
MatrixServerDll_API void OnInstrumentReset(m_oInstrumentStruct* pInstrument)
{
	// �����Ƿ�ʹ����
	pInstrument->m_bInUsed = false;
	// �����豸��
	pInstrument->m_uiSN = 0;
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	pInstrument->m_iInstrumentType = 0;
	// 	// ����IP��ַ
	// 	pInstrument->m_uiIP = 0;
	// ����·��IP��ַ
	pInstrument->m_uiRoutIP = 0;
	// ·�ɷ��� 1-�ϣ�2-�£�3-��4��
	pInstrument->m_iRoutDirection = 0;
	// ·�ɵ�ַ �����߷��� �Ϸ�
	pInstrument->m_uiRoutIPTop = 0;
	// ·�ɵ�ַ �����߷��� �·�
	pInstrument->m_uiRoutIPDown = 0;
	// ·�ɵ�ַ �����߷��� ��
	pInstrument->m_uiRoutIPLeft = 0;
	// ·�ɵ�ַ �����߷��� �ҷ�
	pInstrument->m_uiRoutIPRight = 0;
	// ·�ɿ���
	pInstrument->m_byLAUXRoutOpenSet = 0;
	// ���ӵ����� �Ϸ�
	pInstrument->m_pInstrumentTop = NULL;
	// ���ӵ����� �·�
	pInstrument->m_pInstrumentDown = NULL;
	// ���ӵ����� ��
	pInstrument->m_pInstrumentLeft = NULL;
	// ���ӵ����� �ҷ�
	pInstrument->m_pInstrumentRight = NULL;

	/** ��������ϵͳʱ��*/
	pInstrument->m_uiSystemTime = 0;
	/** ��������ʱ��*/
	pInstrument->m_uiNetTime = 0;
	/** ��������״̬*/
	pInstrument->m_uiNetState = 0;
	/** ������������1*/
	pInstrument->m_uiNetOrder = 0;

	// �װ�ʱ��
	pInstrument->m_uiTimeHeadFrame = 0;
// 	// β��ʱ��
// 	pInstrument->m_uiTailSysTime = 0;
	// β������
	pInstrument->m_iTailFrameCount = 0;
	// ����ʱ��
	pInstrument->m_uiDelayTime = 0;

	pInstrument->m_usReceiveTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ
	pInstrument->m_usSendTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ

	pInstrument->m_usLineLeftReceiveTime = 0;	// 16bits ���߷�������β������ʱ��
	pInstrument->m_usLineRightReceiveTime = 0;	// 16bits ���߷�������β������ʱ��

	pInstrument->m_usCrossTopReceiveTime = 0;	// 16bits �����߷�������β������ʱ��
	pInstrument->m_usCrossDownReceiveTime = 0;	// 16bits �����߷�����β������ʱ��

	pInstrument->m_uiBroadCastPort = 0;			// �ɼ�վ���Դվ�Ĺ㲥�˿�
	// ����
	pInstrument->m_iLineNb = 0;
	// ��ǵ��
	pInstrument->m_uiPointNb = 0;
	/** ����*/
	pInstrument->m_iPointIndex = 0;
	// 	// ���
	// 	m_uiChannelNb = 0;

	// �Ƿ�������
	pInstrument->m_bJumpedChannel = false;
	// �Ƿ����Ӽ첨��
	pInstrument->m_bSensor = false;
	// �Ƿ�����
	pInstrument->m_bAux = false;
	// �Ƿ����ӱ�ը��
	pInstrument->m_bBlastMachine = false;
	// �Ƿ��ػص�
	pInstrument->m_bDetour = false;
	// �Ƿ��ػص��Ͷ˱�ǵ�
	pInstrument->m_bDetourMarkerLow = false;
	// �Ƿ��ػص��߶˱�ǵ�
	pInstrument->m_bDetourMarkerHigh = false;
	// �Ƿ��ػص�ֹͣ���
	pInstrument->m_uiStopMarking = false;
	// �Ƿ��ǵ�
	pInstrument->m_bMarker = false;
	// �װ�λ���ȶ�����
	pInstrument->m_iHeadFrameStableNum = 0;
	// �ڼ�������IP��ַ
	pInstrument->m_iIPSetCount = 0;
	// IP��ַ�����Ƿ�ɹ�
	pInstrument->m_bIPSetOK = false;

	// 	// �ڼ���β��ʱ�̲�ѯ
	// 	pInstrument->m_iTailTimeQueryCount = 0;
	// β��ʱ�̲�ѯ�Ƿ�ɹ�
	pInstrument->m_bTailTimeQueryOK = false;

	// ����ʱ��������λ
	pInstrument->m_uiTimeHigh = 0;
	// ����ʱ��������λ
	pInstrument->m_uiTimeLow = 0;
	// �ڼ�����������ʱ��
	pInstrument->m_iTimeSetCount = 0;
	// ����ʱ�������Ƿ�ɹ�
	pInstrument->m_bTimeSetOK = false;
	// ADC���������Ƿ�Ӧ��
	pInstrument->m_bADCSetReturn = false;
	// �����Ƿ������ADC��������
	pInstrument->m_bADCSet = false;
	// ������ʼADC���ݲɼ����óɹ�
	pInstrument->m_bADCStartSample = false;
	// ����ֹͣADC���ݲɼ����óɹ�
	pInstrument->m_bADCStopSample = false;
}
// �����������нṹ��
MatrixServerDll_API m_oInstrumentListStruct* OnCreateInstrumentList(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oInstrumentListStruct* pInstrumentList = NULL;
	pInstrumentList = new m_oInstrumentListStruct;
	InitializeCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	pInstrumentList->m_pArrayInstrument = NULL;
	pInstrumentList->m_pLogOutPut = pLogOutPut;
	return pInstrumentList;
}
// ��ʼ���������нṹ��
MatrixServerDll_API void OnWorkInstrumentList(m_oInstrumentListStruct* pInstrumentList,
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pInstrumentList == NULL)
	{
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pInstrumentList->m_pLogOutPut, "InitInstrumentList", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pConstVar == NULL)
	{
		AddMsgToLogOutPutList(pInstrumentList->m_pLogOutPut, "InitInstrumentList", "pConstVar",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	// ���SN����������
	pInstrumentList->m_oSNInstrumentMap.clear();
	// ���IP��ַ����������
	pInstrumentList->m_oIPInstrumentMap.clear();
	// ��տ�����������
	pInstrumentList->m_olsInstrumentFree.clear();
	// ���IP��ַ��������������
	pInstrumentList->m_oIPSetMap.clear();
	// ���δ���ADC�������õ���������
	pInstrumentList->m_oADCSetInstrumentMap.clear();
	// ����ϵͳ�����仯��ʱ��
	pInstrumentList->m_ullLineChangeTime = 0;
	// ����״̬�ɲ��ȶ���Ϊ�ȶ�
	pInstrumentList->m_bLineStableChange = false;
	// ������������������
	pInstrumentList->m_uiCountAll = pCommInfo->m_uiInstrumentNum;
	// ������������
	if (pInstrumentList->m_pArrayInstrument != NULL)
	{
		delete[] pInstrumentList->m_pArrayInstrument;
	}
	pInstrumentList->m_pArrayInstrument = new m_oInstrumentStruct[pInstrumentList->m_uiCountAll];
	// ������������
	pInstrumentList->m_uiCountFree = pInstrumentList->m_uiCountAll;
	for(unsigned int i = 0; i < pInstrumentList->m_uiCountAll; i++)
	{
		// ���������������е�λ��
		pInstrumentList->m_pArrayInstrument[i].m_uiIndex = i;
		pInstrumentList->m_pArrayInstrument[i].m_uiIP = pConstVar->m_iIPSetAddrStart + i * pConstVar->m_iIPSetAddrInterval;
		// ��������
		OnInstrumentReset(&pInstrumentList->m_pArrayInstrument[i]);
		// �������ڿ�����������β��
		pInstrumentList->m_olsInstrumentFree.push_back(&pInstrumentList->m_pArrayInstrument[i]);
	}
	LeaveCriticalSection(&pInstrumentList->m_oSecInstrumentList);
}
// �ر��������нṹ��
MatrixServerDll_API void OnCloseInstrumentList(m_oInstrumentListStruct* pInstrumentList)
{
	EnterCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	// ���SN����������
	pInstrumentList->m_oSNInstrumentMap.clear();
	// ���IP��ַ����������
	pInstrumentList->m_oIPInstrumentMap.clear();
	// ��տ�����������
	pInstrumentList->m_olsInstrumentFree.clear();
	// ���IP��ַ��������������
	pInstrumentList->m_oIPSetMap.clear();
	// ���δ���ADC�������õ���������
	pInstrumentList->m_oADCSetInstrumentMap.clear();
	// ɾ����������
	if (pInstrumentList->m_pArrayInstrument != NULL)
	{
		delete[] pInstrumentList->m_pArrayInstrument;
	}
	LeaveCriticalSection(&pInstrumentList->m_oSecInstrumentList);
}
// �ͷ��������нṹ��
MatrixServerDll_API void OnFreeInstrumentList(m_oInstrumentListStruct* pInstrumentList)
{
	if (pInstrumentList == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	delete pInstrumentList;
}

// �õ�һ����������
MatrixServerDll_API m_oInstrumentStruct* GetFreeInstrument(m_oInstrumentListStruct* pInstrumentList)
{
	m_oInstrumentStruct* pInstrument = NULL;
	list <m_oInstrumentStruct*>::iterator iter;
	if(pInstrumentList->m_uiCountFree > 0)	//�п�������
	{
		// �ӿ��ж����еõ�һ������
		iter = pInstrumentList->m_olsInstrumentFree.begin();
		pInstrument = *iter;
		pInstrumentList->m_olsInstrumentFree.pop_front();	
		pInstrument->m_bInUsed = true;	// ��������Ϊʹ����
		pInstrumentList->m_uiCountFree--;	// ��������������1
	}
	return pInstrument;
}


// ����һ����������
MatrixServerDll_API void AddFreeInstrument(m_oInstrumentStruct* pInstrument, m_oInstrumentListStruct* pInstrumentList)
{
	//��ʼ������
	OnInstrumentReset(pInstrument);
	//������ж���
	pInstrumentList->m_olsInstrumentFree.push_back(pInstrument);
	pInstrumentList->m_uiCountFree++;	// ��������������1
}
// �ж������������Ƿ��Ѽ���������
MatrixServerDll_API BOOL IfIndexExistInMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter != pMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// ����һ��IP��ַ��������
MatrixServerDll_API void AddInstrumentToMap(unsigned int uiIndex, m_oInstrumentStruct* pInstrument, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	if (false == IfIndexExistInMap(uiIndex, pMap))
	{
		pMap->insert(hash_map<unsigned int, m_oInstrumentStruct*>::value_type (uiIndex, pInstrument));
	}
}
// �������������ţ���������õ�����ָ��
MatrixServerDll_API m_oInstrumentStruct* GetInstrumentFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	return iter->second;
}
// ��������ɾ��������ָ�������ָ��
MatrixServerDll_API BOOL DeleteInstrumentFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter != pMap->end())
	{
		pMap->erase(iter);
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// ����·����Ϣ
MatrixServerDll_API void OnRoutReset(m_oRoutStruct* pRout)
{
	// �����Ƿ�ʹ����
	pRout->m_bInUsed = false;
	// ·�ɷ��� 1-�ϣ�2-�£�3-��4��
	pRout->m_iRoutDirection = 0;
	// ·��ͷ����
	pRout->m_pHead = NULL;
	// ·��β����
	pRout->m_pTail = NULL;
	// ·��ʱ��
	pRout->m_ullRoutTime = 0xFFFFFFFF00000000;
	// ·���Ƿ�Ϊ������·��
	pRout->m_bRoutLaux = false;
	// ·���Ƿ���յ�ADC���ò���Ӧ��
	pRout->m_bADCSetReturn = false;
	// ·���Ƿ���ADC��������֡
	pRout->m_bADCSetRout = true;
	// ��·�ɷ����������ĸ���
	pRout->m_uiInstrumentNum = 0;
}
// ����·�ɶ����·��ʱ��
MatrixServerDll_API void UpdateRoutTime(m_oRoutStruct* pRout)
{
	// ·��ʱ��
	pRout->m_ullRoutTime = GetTickCount64();
}

// �����ϴβ���ϵͳ�仯ʱ��
MatrixServerDll_API void UpdateLineChangeTime(m_oInstrumentListStruct* pInstrumentList)
{
	// �ϴβ���ϵͳ�仯ʱ��
	pInstrumentList->m_ullLineChangeTime = GetTickCount64();
}
// ����·�ɶ��нṹ��
MatrixServerDll_API m_oRoutListStruct* OnCreateRoutList(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oRoutListStruct* pRoutList = NULL;
	pRoutList = new m_oRoutListStruct;
	InitializeCriticalSection(&pRoutList->m_oSecRoutList);
	pRoutList->m_pArrayRout = NULL;
	pRoutList->m_pLogOutPut = pLogOutPut;
	return pRoutList;
}
// ��ʼ��·�ɶ��нṹ��
MatrixServerDll_API void OnWorkRoutList(m_oRoutListStruct* pRoutList,
	m_oInstrumentCommInfoStruct* pCommInfo,
	m_oConstVarStruct* pConstVar)
{
	if (pRoutList == NULL)
	{
		return;
	}
	if (pCommInfo == NULL)
	{
		AddMsgToLogOutPutList(pRoutList->m_pLogOutPut, "InitRoutList", "pCommInfo",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pRoutList->m_oSecRoutList);
	// ���·�ɵ�ַ����
	pRoutList->m_oRoutMap.clear();
	// �����Ҫɾ����·�ɵ�ַ����
	pRoutList->m_oRoutDeleteMap.clear();
	// ���ADC����������������
	pRoutList->m_oADCSetRoutMap.clear();
	// ��տ���·�ɶ���
	pRoutList->m_olsRoutFree.clear();
	// �������ʱͳ���������
	pRoutList->m_olsTimeDelayTaskQueue.clear();
	pRoutList->m_olsTimeDelayTemp.clear();
	// ·�ɶ�����·�ɸ���
	pRoutList->m_uiCountAll = pCommInfo->m_uiInstrumentNum;
	// ����·������
	pRoutList->m_uiCountFree = pRoutList->m_uiCountAll;
	// ����·������
	if (pRoutList->m_pArrayRout != NULL)
	{
		delete[] pRoutList->m_pArrayRout;
	}
	pRoutList->m_pArrayRout = new m_oRoutStruct[pRoutList->m_uiCountAll];

	// �������·�ɶ���
	for(unsigned int i = 0; i < pRoutList->m_uiCountAll; i++)
	{
		// ����·��IP��ַ
		pRoutList->m_pArrayRout[i].m_uiRoutIP = pConstVar->m_iRoutSetAddrStart + i * pConstVar->m_iRoutSetAddrInterval;
		// ·����·�������е�λ��
		pRoutList->m_pArrayRout[i].m_uiIndex = i;
		// ����·��
		OnRoutReset(&pRoutList->m_pArrayRout[i]);
		// ·�ɼ��ڿ���·�ɶ���β��
		pRoutList->m_olsRoutFree.push_back(&pRoutList->m_pArrayRout[i]);
	}
	LeaveCriticalSection(&pRoutList->m_oSecRoutList);
}
// �ر��������нṹ��
MatrixServerDll_API void OnCloseRoutList(m_oRoutListStruct* pRoutList)
{
	EnterCriticalSection(&pRoutList->m_oSecRoutList);
	// ���·�ɵ�ַ����
	pRoutList->m_oRoutMap.clear();
	// �����Ҫɾ����·�ɵ�ַ����
	pRoutList->m_oRoutDeleteMap.clear();
	// ���ADC����������������
	pRoutList->m_oADCSetRoutMap.clear();
	// ��տ���·�ɶ���
	pRoutList->m_olsRoutFree.clear();
	// �������ʱͳ���������
	pRoutList->m_olsTimeDelayTaskQueue.clear();
	pRoutList->m_olsTimeDelayTemp.clear();
	// ɾ��·������
	if (pRoutList->m_pArrayRout != NULL)
	{
		delete[] pRoutList->m_pArrayRout;
	}
	LeaveCriticalSection(&pRoutList->m_oSecRoutList);
}
// �ͷ��������нṹ��
MatrixServerDll_API void OnFreeRoutList(m_oRoutListStruct* pRoutList)
{
	if (pRoutList == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pRoutList->m_oSecRoutList);
	delete pRoutList;
}
// �õ�һ������·��
MatrixServerDll_API m_oRoutStruct* GetFreeRout(m_oRoutListStruct* pRoutList)
{
	m_oRoutStruct* pRout = NULL;
	list <m_oRoutStruct*>::iterator iter;
	if(pRoutList->m_uiCountFree > 0)	//�п���·��
	{
		// �ӿ���·�ɶ���ͷ���õ�һ������·��
		iter = pRoutList->m_olsRoutFree.begin();
		pRout = *iter;
		pRoutList->m_olsRoutFree.pop_front();	
		// ·���Ƿ�ʹ����
		pRout->m_bInUsed = true;	
		// ����·�ɼ�����1
		pRoutList->m_uiCountFree--;
	}
	return pRout;
}
// ����һ������·��
MatrixServerDll_API void AddFreeRout(m_oRoutStruct* pRout, m_oRoutListStruct* pRoutList)
{
	//��ʼ��·��
	OnRoutReset(pRout);
	//������ж���
	pRoutList->m_olsRoutFree.push_back(pRout);
	// ����·�ɼ�����1
	pRoutList->m_uiCountFree++;
}
// ·�ɵ�ַ�Ƿ��Ѽ���������
MatrixServerDll_API BOOL IfIndexExistInRoutMap(unsigned int uiRoutIP, hash_map<unsigned int, m_oRoutStruct*>* pRoutMap)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oRoutStruct*>::iterator iter;
	iter = pRoutMap->find(uiRoutIP);
	if (iter != pRoutMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// ����һ��·��
MatrixServerDll_API void AddRout(unsigned int uiIndex, 
	m_oRoutStruct* pRout, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap)
{
	if (false == IfIndexExistInRoutMap(uiIndex, pRoutMap))
	{
		pRoutMap->insert(hash_map<unsigned int, m_oRoutStruct*>::value_type (uiIndex, pRout));
	}
}
// �������������ţ���������õ�һ��·��ָ��
MatrixServerDll_API m_oRoutStruct* GetRout(unsigned int uiIndex, hash_map<unsigned int, m_oRoutStruct*>* pRoutMap)
{
	hash_map<unsigned int, m_oRoutStruct*>::iterator iter;
	iter = pRoutMap->find(uiIndex);
	return iter->second;
}

// �������������ţ�����������ɾ��һ��·��
MatrixServerDll_API void DeleteRout(unsigned int uiIndex, hash_map<unsigned int, m_oRoutStruct*>* pRoutMap)
{
	hash_map<unsigned int, m_oRoutStruct*>::iterator iter;
	iter = pRoutMap->find(uiIndex);
	if (iter != pRoutMap->end())
	{
		pRoutMap->erase(iter);
	}
}
// �����װ�֡
MatrixServerDll_API bool ParseInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame, m_oConstVarStruct* pConstVar)
{
	bool bReturn = false;
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	bReturn = ParseInstrumentFrame(pHeadFrame->m_pCommandStruct, pHeadFrame->m_pcRcvFrameData, pConstVar);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	return bReturn;
}
// ����β��֡
MatrixServerDll_API bool ParseInstrumentTailFrame(m_oTailFrameStruct* pTailFrame, m_oConstVarStruct* pConstVar)
{
	bool bReturn = false;
	EnterCriticalSection(&pTailFrame->m_oSecTailFrame);
	bReturn = ParseInstrumentFrame(pTailFrame->m_pCommandStruct, pTailFrame->m_pcRcvFrameData, pConstVar);
	LeaveCriticalSection(&pTailFrame->m_oSecTailFrame);
	return bReturn;
}
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API bool ParseInstrumentIPSetReturnFrame(m_oIPSetFrameStruct* pIPSetFrame, m_oConstVarStruct* pConstVar)
{
	bool bReturn = false;
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	bReturn = ParseInstrumentFrame(pIPSetFrame->m_pCommandStructReturn, pIPSetFrame->m_pcRcvFrameData, pConstVar);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	return bReturn;
}
// ����β��ʱ�̲�ѯ֡
MatrixServerDll_API bool ParseInstrumentTailTimeReturnFrame(m_oTailTimeFrameStruct* pTailTimeFrame, m_oConstVarStruct* pConstVar)
{
	bool bReturn = false;
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	bReturn = ParseInstrumentFrame(pTailTimeFrame->m_pCommandStructReturn, pTailTimeFrame->m_pcRcvFrameData, pConstVar);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	return bReturn;
}
// ����ʱͳ����Ӧ��֡
MatrixServerDll_API bool ParseInstrumentTimeDelayReturnFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, m_oConstVarStruct* pConstVar)
{
	bool bReturn = false;
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	bReturn = ParseInstrumentFrame(pTimeDelayFrame->m_pCommandStructReturn, pTimeDelayFrame->m_pcRcvFrameData, pConstVar);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	return bReturn;
}
// ����ADC��������Ӧ��֡
MatrixServerDll_API bool ParseInstrumentADCSetReturnFrame(m_oADCSetFrameStruct* pADCSetFrame, m_oConstVarStruct* pConstVar)
{
	bool bReturn = false;
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	bReturn = ParseInstrumentFrame(pADCSetFrame->m_pCommandStructReturn, pADCSetFrame->m_pcRcvFrameData, pConstVar);
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	return bReturn;
}
// ��������֡
MatrixServerDll_API void MakeInstrumentHeartBeatFrame(m_oHeartBeatFrameStruct* pHeartBeatFrame, m_oConstVarStruct* pConstVar)
{
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	pHeartBeatFrame->m_pCommandStruct->m_uiDstIP = pConstVar->m_iIPBroadcastAddr;
	MakeInstrumentFrame(pHeartBeatFrame->m_pCommandStruct,  pConstVar, pHeartBeatFrame->m_pcSndFrameData,
		pHeartBeatFrame->m_pcCommandWord, pHeartBeatFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// ��������֡
MatrixServerDll_API void SendInstrumentHeartBeatFrame(m_oHeartBeatFrameStruct* pHeartBeatFrame, m_oConstVarStruct* pConstVar)
{
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	SendFrame(pHeartBeatFrame->m_oHeartBeatSocket, pHeartBeatFrame->m_pcSndFrameData, pConstVar->m_iSndFrameSize,
		pHeartBeatFrame->m_pCommandStruct->m_usAimPort, pHeartBeatFrame->m_pCommandStruct->m_uiAimIP, 
		pHeartBeatFrame->m_pLogOutPut);
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// ����IP��ַ��ѯ֡
MatrixServerDll_API void MakeInstrumentIPQueryFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP)
{
	CString str = _T("");
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// ����IP��ַ
	pIPSetFrame->m_pCommandStructSet->m_uiDstIP = uiInstrumentIP;
	// IP��ַ��ѯ����
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ��ѯ����������
	pIPSetFrame->m_pcCommandWord[0] = pConstVar->m_byCmdLocalIPAddr;
	// ��ѯ�����ָ���
	pIPSetFrame->m_usCommandWordNum = 1;
	MakeInstrumentFrame(pIPSetFrame->m_pCommandStructSet, pConstVar, pIPSetFrame->m_pcSndFrameData, 
		pIPSetFrame->m_pcCommandWord, pIPSetFrame->m_usCommandWordNum);
	str.Format(_T("������IP��ַ = 0x%x ����������IP��ַ��ѯ֡"), pIPSetFrame->m_pCommandStructSet->m_uiDstIP);
	AddMsgToLogOutPutList(pIPSetFrame->m_pLogOutPut, "MakeInstrumentIPQueryFrame", ConvertCStrToStr(str));
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// ����IP��ַ����֡
MatrixServerDll_API void MakeInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument)
{
	CString str = _T("");
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// ����SN��
	pIPSetFrame->m_pCommandStructSet->m_uiSN = pInstrument->m_uiSN;
	// ��������IP
	pIPSetFrame->m_pCommandStructSet->m_uiInstrumentIP = pInstrument->m_uiIP;
	// ���ù㲥�˿�
	pIPSetFrame->m_pCommandStructSet->m_uiBroadCastPortSet = pInstrument->m_uiBroadCastPort;
	// ·��IP��ַ��·�ɷ��� 1-��
	pIPSetFrame->m_pCommandStructSet->m_uiRoutIPTop = pInstrument->m_uiRoutIPTop;
	// ·��IP��ַ��·�ɷ��� 2-��
	pIPSetFrame->m_pCommandStructSet->m_uiRoutIPDown = pInstrument->m_uiRoutIPDown;
	// ·��IP��ַ��·�ɷ��� 3-��
	pIPSetFrame->m_pCommandStructSet->m_uiRoutIPLeft = pInstrument->m_uiRoutIPLeft;
	// ·��IP��ַ��·�ɷ��� 4-��
	pIPSetFrame->m_pCommandStructSet->m_uiRoutIPRight = pInstrument->m_uiRoutIPRight;
	// ·�ɿ��ش�
	pIPSetFrame->m_pCommandStructSet->m_byLAUXRoutOpenSet = pInstrument->m_byLAUXRoutOpenSet;
	// �㲥IP��ַ
	pIPSetFrame->m_pCommandStructSet->m_uiDstIP = pConstVar->m_iIPBroadcastAddr;
	// ʱ��������λ
	pIPSetFrame->m_pCommandStructSet->m_uiLocalTimeFixedHigh = pInstrument->m_uiTimeHigh;
	// ʱ��������λ
	pIPSetFrame->m_pCommandStructSet->m_uiLocalTimeFixedLow = pInstrument->m_uiTimeLow;

	// ����SN������
	pIPSetFrame->m_pcCommandWord[0] = pConstVar->m_byCmdSn;
	// ����IP������
	pIPSetFrame->m_pcCommandWord[1] = pConstVar->m_byCmdLocalIPAddr;
	// ʱ��������λ������
	pIPSetFrame->m_pcCommandWord[2] = pConstVar->m_byCmdLocalTimeFixedHigh;
	// ʱ��������λ������
	pIPSetFrame->m_pcCommandWord[3] = pConstVar->m_byCmdLocalTimeFixedLow;
	// �����㲥�˿�������
	pIPSetFrame->m_pcCommandWord[4] = pConstVar->m_byCmdBroadCastPortSet;

	// ����IP��ַ����֡
	if((pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeFDU)
		|| (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLAUL))
	{
		// �����ָ���
		pIPSetFrame->m_usCommandWordNum = 5;
	}
	// LCI�ͽ���վ��Ҫ����·��IP��ַ
	else
	{
		// ����·��IP������
		pIPSetFrame->m_pcCommandWord[5] = pConstVar->m_byCmdLAUXSetRout;
		// ����·��IP������
		pIPSetFrame->m_pcCommandWord[6] = pConstVar->m_byCmdLAUXSetRout;
		// ����·��IP������
		pIPSetFrame->m_pcCommandWord[7] = pConstVar->m_byCmdLAUXSetRout;
		// ����·��IP������
		pIPSetFrame->m_pcCommandWord[8] = pConstVar->m_byCmdLAUXSetRout;
		// ������·��������
		pIPSetFrame->m_pcCommandWord[9] = pConstVar->m_byCmdLAUXRoutOpenSet;
		// �����ָ���
		pIPSetFrame->m_usCommandWordNum = 10;
	}
	// IP��ַ��������
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	MakeInstrumentFrame(pIPSetFrame->m_pCommandStructSet, pConstVar, pIPSetFrame->m_pcSndFrameData, 
		pIPSetFrame->m_pcCommandWord, pIPSetFrame->m_usCommandWordNum);
	str.Format(_T("������SN = 0x%x��IP��ַ = 0x%x ����������IP��ַ����֡"), 
		pIPSetFrame->m_pCommandStructSet->m_uiSN, pIPSetFrame->m_pCommandStructSet->m_uiInstrumentIP);
	AddMsgToLogOutPutList(pIPSetFrame->m_pLogOutPut, "MakeInstrumentIPSetFrame", ConvertCStrToStr(str));
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// ����IP��ַ����֡
MatrixServerDll_API void SendInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, m_oConstVarStruct* pConstVar)
{
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	SendFrame(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_pcSndFrameData, pConstVar->m_iSndFrameSize,
		pIPSetFrame->m_pCommandStructSet->m_usAimPort, pIPSetFrame->m_pCommandStructSet->m_uiAimIP, 
		pIPSetFrame->m_pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// ��IP��ַ��ѯβ��ʱ��֡
MatrixServerDll_API void MakeInstrumentTailTimeQueryFramebyIP(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP)
{
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	// ����IP��ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiDstIP = uiInstrumentIP;
	// ��ѯ����
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ��ѯ����������
	// ����վ������β������ʱ��
	pTailTimeFrame->m_pcCommandWord[0] = pConstVar->m_byCmdLAUTailRecTimeLAUX;
	// ����վ����β������ʱ��
	pTailTimeFrame->m_pcCommandWord[1] = pConstVar->m_byCmdLineTailRecTimeLAUX;
	// β������/����ʱ��
	pTailTimeFrame->m_pcCommandWord[2] = pConstVar->m_byCmdTailRecSndTime;
	// ��ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = 3;
	MakeInstrumentFrame(pTailTimeFrame->m_pCommandStructSet, pConstVar, pTailTimeFrame->m_pcSndFrameData, 
		pTailTimeFrame->m_pcCommandWord, pTailTimeFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// �㲥��ѯβ��ʱ��֡
MatrixServerDll_API void MakeInstrumentTailTimeQueryFramebyBroadCast(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort)
{
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	// ����IP��ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiDstIP = pConstVar->m_iIPBroadcastAddr;
	// ��ѯ����
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// �㲥�˿�
	pTailTimeFrame->m_pCommandStructSet->m_uiBroadCastPortSeted = uiBroadCastPort;
	// ��ѯ����������
	// �㲥�˿�
	pTailTimeFrame->m_pcCommandWord[0] = pConstVar->m_byCmdBroadCastPortSeted;
	// ����վ������β������ʱ��
	pTailTimeFrame->m_pcCommandWord[1] = pConstVar->m_byCmdLAUTailRecTimeLAUX;
	// ����վ����β������ʱ��
	pTailTimeFrame->m_pcCommandWord[2] = pConstVar->m_byCmdLineTailRecTimeLAUX;
	// β������/����ʱ��
	pTailTimeFrame->m_pcCommandWord[3] = pConstVar->m_byCmdTailRecSndTime;
	// ��ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = 4;
	MakeInstrumentFrame(pTailTimeFrame->m_pCommandStructSet, pConstVar, pTailTimeFrame->m_pcSndFrameData, 
		pTailTimeFrame->m_pcCommandWord, pTailTimeFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// ����β��ʱ�̲�ѯ֡
MatrixServerDll_API void SendInstrumentTailTimeQueryFrame(m_oTailTimeFrameStruct* pTailTimeFrame, m_oConstVarStruct* pConstVar)
{
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	SendFrame(pTailTimeFrame->m_oTailTimeFrameSocket, pTailTimeFrame->m_pcSndFrameData, pConstVar->m_iSndFrameSize,
		pTailTimeFrame->m_pCommandStructSet->m_usAimPort, pTailTimeFrame->m_pCommandStructSet->m_uiAimIP, 
		pTailTimeFrame->m_pLogOutPut);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// ����ʱͳ����֡
MatrixServerDll_API void MakeInstrumentDelayTimeFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument)
{
	CString str = _T("");
	// ���յ�ʱͳ����Ӧ���־λ
	pInstrument->m_bTimeSetOK = false;
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	// ����IP��ַ
	pTimeDelayFrame->m_pCommandStructSet->m_uiDstIP = pInstrument->m_uiIP;
	// ��������
	pTimeDelayFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// ʱͳ���ø�λ
	pTimeDelayFrame->m_pCommandStructSet->m_uiLocalTimeFixedHigh = pInstrument->m_uiTimeHigh;
	// ʱͳ���õ�λ
	pTimeDelayFrame->m_pCommandStructSet->m_uiLocalTimeFixedLow = pInstrument->m_uiTimeLow;
	// ��������������
	// ʱͳ���ø�λ
	pTimeDelayFrame->m_pcCommandWord[0] = pConstVar->m_byCmdLocalTimeFixedHigh;
	// ʱͳ���õ�λ
	pTimeDelayFrame->m_pcCommandWord[1] = pConstVar->m_byCmdLocalTimeFixedLow;
	// ���������ָ���
	pTimeDelayFrame->m_usCommandWordNum = 2;
	MakeInstrumentFrame(pTimeDelayFrame->m_pCommandStructSet, pConstVar, pTimeDelayFrame->m_pcSndFrameData, 
		pTimeDelayFrame->m_pcCommandWord, pTimeDelayFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
}
// ����ʱͳ����֡
MatrixServerDll_API void SendInstrumentDelayTimeFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, m_oConstVarStruct* pConstVar)
{
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	SendFrame(pTimeDelayFrame->m_oTimeDelayFrameSocket, pTimeDelayFrame->m_pcSndFrameData, pConstVar->m_iSndFrameSize,
		pTimeDelayFrame->m_pCommandStructSet->m_usAimPort, pTimeDelayFrame->m_pCommandStructSet->m_uiAimIP, 
		pTimeDelayFrame->m_pLogOutPut);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
}
// ����ADC��������֡
MatrixServerDll_API void SendInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame, m_oConstVarStruct* pConstVar)
{
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	SendFrame(pADCSetFrame->m_oADCSetFrameSocket, pADCSetFrame->m_pcSndFrameData, pConstVar->m_iSndFrameSize,
		pADCSetFrame->m_pCommandStructSet->m_usAimPort, pADCSetFrame->m_pCommandStructSet->m_uiAimIP, 
		pADCSetFrame->m_pLogOutPut);
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
}
// ������־����߳�
MatrixServerDll_API m_oLogOutPutThreadStruct* OnCreateLogOutPutThread(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oLogOutPutThreadStruct* pLogOutPutThread = NULL;
	pLogOutPutThread = new m_oLogOutPutThreadStruct;
	pLogOutPutThread->m_pThread = new m_oThreadStruct;
	pLogOutPutThread->m_pThread->m_pLogOutPut = pLogOutPut;
	pLogOutPutThread->m_pThread->m_hThread = INVALID_HANDLE_VALUE;
	pLogOutPutThread->m_pThread->m_hThreadClose = INVALID_HANDLE_VALUE;
	pLogOutPutThread->m_pThread->m_dwThreadID = 0;
	pLogOutPutThread->m_pLogOutPutTimeDelay = NULL;
	pLogOutPutThread->m_pLogOutPutErrorCode = NULL;
	pLogOutPutThread->m_pLogOutPutADCFrameTime = NULL;
	return pLogOutPutThread;
}
// �̵߳ȴ�����
MatrixServerDll_API void WaitLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pLogOutPutThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pLogOutPutThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pLogOutPutThread->m_pThread->m_pConstVar->m_iLogOutPutSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	while(true)
	{
		if (pLogOutPutThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pLogOutPutThread->m_pThread->m_bWork == true)
		{
			WriteLogOutPutListToFile(pLogOutPutThread->m_pThread->m_pLogOutPut);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutTimeDelay);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutErrorCode);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutADCFrameTime);
		}
		if (pLogOutPutThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitLogOutPutThread(pLogOutPutThread);
	}
	::SetEvent(pLogOutPutThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ����־����߳�
MatrixServerDll_API bool OnInitLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	if (pLogOutPutThread == NULL)
	{
		return false;
	}
	pLogOutPutThread->m_pThread->m_bClose = false;
	pLogOutPutThread->m_pThread->m_bWork = false;
	pLogOutPutThread->m_pThread->m_hThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if (pLogOutPutThread->m_pThread->m_hThreadClose == NULL)
	{
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnInitLogOutPutThread", 
			"pLogOutPutThread->m_pThread->m_hThreadClose", ErrorType, IDS_ERR_CREATE_EVENT);
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnInitLogOutPutThread", 
			"pLogOutPutThread->m_pThread->m_hThreadClose", ErrorType, ERROR_ALREADY_EXISTS);
	}
	::ResetEvent(pLogOutPutThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pLogOutPutThread->m_pThread->m_hThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunLogOutPutThread,
		pLogOutPutThread, 
		0, 
		&pLogOutPutThread->m_pThread->m_dwThreadID);
	if (pLogOutPutThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnInitLogOutPutThread", 
			"pLogOutPutThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnInitLogOutPutThread", "��־����̴߳����ɹ�");
	return true;
}
// �ر���־����߳�
MatrixServerDll_API bool OnCloseLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	if (pLogOutPutThread == NULL)
	{
		return false;
	}
	int iResult = WaitForSingleObject(pLogOutPutThread->m_pThread->m_hThreadClose, 
		pLogOutPutThread->m_pThread->m_pConstVar->m_iCloseThreadSleepTimes
		* pLogOutPutThread->m_pThread->m_pConstVar->m_iOneSleepTime);
	if (iResult != WAIT_OBJECT_0)
	{
		::TerminateThread(pLogOutPutThread->m_pThread->m_hThread, 0);
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnCloseLogOutPutThread", 
			"��־����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnCloseLogOutPutThread", "��־����̳߳ɹ��ر�");
	return true;
}
// �ͷ���־����߳�
MatrixServerDll_API void OnFreeLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	if (pLogOutPutThread == NULL)
	{
		return;
	}
	if (pLogOutPutThread->m_pThread != NULL)
	{
		delete pLogOutPutThread->m_pThread;
	}
	delete pLogOutPutThread;
}
// ���������߳�
MatrixServerDll_API m_oHeartBeatThreadStruct* OnCreateHeartBeatThread(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oHeartBeatThreadStruct* pHeartBeatThread = NULL;
	pHeartBeatThread = new m_oHeartBeatThreadStruct;
	pHeartBeatThread->m_pThread = new m_oThreadStruct;
	pHeartBeatThread->m_pThread->m_pLogOutPut = pLogOutPut;
	pHeartBeatThread->m_pThread->m_hThread = INVALID_HANDLE_VALUE;
	pHeartBeatThread->m_pThread->m_hThreadClose = INVALID_HANDLE_VALUE;
	pHeartBeatThread->m_pThread->m_dwThreadID = 0;
	return pHeartBeatThread;
}
// �̵߳ȴ�����
MatrixServerDll_API void WaitHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pHeartBeatThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pHeartBeatThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pHeartBeatThread->m_pThread->m_pConstVar->m_iHeartBeatSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pHeartBeatThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pHeartBeatThread->m_pThread->m_bWork == true)
		{
			MakeInstrumentHeartBeatFrame(pHeartBeatThread->m_pHeartBeatFrame, pHeartBeatThread->m_pThread->m_pConstVar);
			SendInstrumentHeartBeatFrame(pHeartBeatThread->m_pHeartBeatFrame, pHeartBeatThread->m_pThread->m_pConstVar);
		}
		if (pHeartBeatThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitHeartBeatThread(pHeartBeatThread);
	}
	::SetEvent(pHeartBeatThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ�������߳�
MatrixServerDll_API bool OnInitHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return false;
	}
	pHeartBeatThread->m_pThread->m_bClose = false;
	pHeartBeatThread->m_pThread->m_bWork = false;
	pHeartBeatThread->m_pThread->m_hThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if (pHeartBeatThread->m_pThread->m_hThreadClose == NULL)
	{
		AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnInitHeartBeatThread", 
			"pHeartBeatThread->m_pThread->m_hThreadClose", ErrorType, IDS_ERR_CREATE_EVENT);
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnInitHeartBeatThread", 
			"pHeartBeatThread->m_pThread->m_hThreadClose", ErrorType, ERROR_ALREADY_EXISTS);
	}
	::ResetEvent(pHeartBeatThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pHeartBeatThread->m_pThread->m_hThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunHeartBeatThread,
		pHeartBeatThread, 
		0, 
		&pHeartBeatThread->m_pThread->m_dwThreadID);
	if (pHeartBeatThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnInitHeartBeatThread", 
			"pHeartBeatThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnInitHeartBeatThread", "�����̴߳����ɹ�");
	return true;
}
// �ر������߳�
MatrixServerDll_API bool OnCloseHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return false;
	}
	int iResult = WaitForSingleObject(pHeartBeatThread->m_pThread->m_hThreadClose, 
		pHeartBeatThread->m_pThread->m_pConstVar->m_iCloseThreadSleepTimes
		* pHeartBeatThread->m_pThread->m_pConstVar->m_iOneSleepTime);
	if (iResult != WAIT_OBJECT_0)
	{
		::TerminateThread(pHeartBeatThread->m_pThread->m_hThread, 0);
		AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnCloseHeartBeatThread", 
			"�����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnCloseHeartBeatThread", "�����̳߳ɹ��ر�");
	return true;
}
// �ͷ������߳�
MatrixServerDll_API void OnFreeHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return;
	}
	if (pHeartBeatThread->m_pThread != NULL)
	{
		delete pHeartBeatThread->m_pThread;
	}
	delete pHeartBeatThread;
}
// �����װ������߳�
MatrixServerDll_API m_oHeadFrameThreadStruct* OnCreateHeadFrameThread(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oHeadFrameThreadStruct* pHeadFrameThread = NULL;
	pHeadFrameThread = new m_oHeadFrameThreadStruct;
	pHeadFrameThread->m_pThread = new m_oThreadStruct;
	pHeadFrameThread->m_pThread->m_pLogOutPut = pLogOutPut;
	pHeadFrameThread->m_pThread->m_hThread = INVALID_HANDLE_VALUE;
	pHeadFrameThread->m_pThread->m_hThreadClose = INVALID_HANDLE_VALUE;
	pHeadFrameThread->m_pThread->m_dwThreadID = 0;
	return pHeadFrameThread;
}
/**
* �������ӷ��򣬵õ����ӵ���һ������
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return CInstrument* ����ָ�� NLLL�����ӵ���һ������������
*/
MatrixServerDll_API m_oInstrumentStruct* GetNextInstrument(int iRoutDirection, 
	m_oInstrumentStruct* pInstrument,
	m_oConstVarStruct* pConstVar)
{
	m_oInstrumentStruct* pInstrumentNext = NULL;
	// �жϷ���
	if (iRoutDirection == pConstVar->m_iDirectionTop)
	{
		pInstrumentNext = pInstrument->m_pInstrumentTop;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionDown)
	{
		pInstrumentNext = pInstrument->m_pInstrumentDown;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionLeft)
	{
		pInstrumentNext = pInstrument->m_pInstrumentLeft;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionRight)
	{
		pInstrumentNext = pInstrument->m_pInstrumentRight;
	}
	else
	{
		pInstrumentNext = pInstrument;
	}
	if (pInstrumentNext != NULL)
	{
		if (pInstrumentNext->m_bInUsed == false)
		{
			return NULL;
		}
	}
	return pInstrumentNext;
}
/**
* �������ӷ��򣬵õ����ӵ�ǰһ������
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return CInstrument* ����ָ�� NLLL�����ӵ�ǰһ������������
*/
MatrixServerDll_API m_oInstrumentStruct* GetPreviousInstrument(int iRoutDirection, 
	m_oInstrumentStruct* pInstrument,
	m_oConstVarStruct* pConstVar)
{
	m_oInstrumentStruct* pInstrumentPrevious = NULL;
	// �жϷ���
	if (iRoutDirection == pConstVar->m_iDirectionTop)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentDown;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionDown)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentTop;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionLeft)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentRight;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionRight)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentLeft;
	}
	else
	{
		pInstrumentPrevious = pInstrument;
	}
	if (pInstrumentPrevious != NULL)
	{
		if (pInstrumentPrevious->m_bInUsed == false)
		{
			return NULL;
		}
	}
	return pInstrumentPrevious;
}
// ����λ�ð����װ�ʱ������
MatrixServerDll_API void InstrumentLocationSortTop(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	bool bLocation = false;
	bool bStable = true;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	m_oInstrumentStruct* pInstrumentTop = NULL;
	m_oInstrumentStruct* pInstrumentDown = NULL;
	if (pConstVar == NULL)
	{
		return;
	}
	if (pInstrument == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSortLeft", "pInstrument", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSortLeft", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ��·�ɷ���β����Ϊ��
	if (pRout->m_pTail == NULL)
	{
		pInstrument->m_iLineNb = pRout->m_pHead->m_iLineNb - 1;
		pRout->m_pTail = pInstrument;
		pRout->m_pHead->m_pInstrumentTop = pInstrument;
		pInstrument->m_pInstrumentDown = pRout->m_pHead;
		pInstrument->m_iHeadFrameStableNum++;
		
	}
	else
	{
		// ��·�ɷ���β�����װ�ʱ��С�ڸ��������װ�ʱ��
		if (pRout->m_pTail->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
		{
			pInstrument->m_iLineNb = pRout->m_pTail->m_iLineNb - 1;
			pRout->m_pTail->m_pInstrumentTop = pInstrument;
			pInstrument->m_pInstrumentDown = pRout->m_pTail;
			pRout->m_pTail = pInstrument;
			pInstrument->m_iHeadFrameStableNum++;
			
		} 
		// ����λ��·������
		else
		{
			pInstrumentNext = pRout->m_pHead;
			pInstrumentDown = pRout->m_pHead;
			while(pInstrumentNext != NULL)
			{
				if (pInstrumentNext->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
				{
					pInstrumentDown = pInstrumentNext;
				}
				else
				{
					// �ҵ�·�ɱ��һ���װ�ʱ�̴��ڵ��������װ�ʱ�̵�����
					if (bLocation == false)
					{
						bLocation = true;
						pInstrumentTop = pInstrumentNext;
						if (pInstrumentTop == pInstrument)
						{
							pInstrument->m_iHeadFrameStableNum++;
							pInstrument->m_iLineNb = pInstrumentDown->m_iLineNb - 1;
						}
						// ��·�ɱ������������м��������
						else
						{
							pInstrumentDown->m_pInstrumentTop = pInstrument;
							pInstrument->m_pInstrumentDown = pInstrumentDown;
							pInstrumentTop->m_pInstrumentDown = pInstrument;
							pInstrument->m_pInstrumentTop = pInstrumentTop;
							pInstrumentTop->m_iHeadFrameStableNum = 0;
							pInstrument->m_iHeadFrameStableNum = 0;
							pInstrument->m_iLineNb = pInstrumentDown->m_iLineNb - 1;
							pInstrumentTop->m_iLineNb--;
							bStable = false;	
						}
					}
					else
					{
						if (bStable == false)
						{
							pInstrumentNext->m_iHeadFrameStableNum = 0;
							pInstrumentNext->m_iLineNb--;
						}
					}
				}
				pInstrumentNext = GetNextInstrument(pConstVar->m_iDirectionTop, pInstrumentNext, pConstVar);
			}
		}
	}
}
// ����λ�ð����װ�ʱ������
MatrixServerDll_API void InstrumentLocationSortDown(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	bool bLocation = false;
	bool bStable = true;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	m_oInstrumentStruct* pInstrumentTop = NULL;
	m_oInstrumentStruct* pInstrumentDown = NULL;
	if (pConstVar == NULL)
	{
		return;
	}
	if (pInstrument == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSortRight", "pInstrument", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSortRight", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ��·�ɷ���β����Ϊ��
	if (pRout->m_pTail == NULL)
	{
		pInstrument->m_iLineNb = pRout->m_pHead->m_iLineNb + 1;
		pRout->m_pTail = pInstrument;
		pRout->m_pHead->m_pInstrumentDown = pInstrument;
		pInstrument->m_pInstrumentTop = pRout->m_pHead;
		pInstrument->m_iHeadFrameStableNum++;
	}
	else
	{
		// ��·�ɷ���β�����װ�ʱ��С�ڸ��������װ�ʱ��
		if (pRout->m_pTail->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
		{
			pInstrument->m_iLineNb = pRout->m_pTail->m_iLineNb + 1;
			pRout->m_pTail->m_pInstrumentDown = pInstrument;
			pInstrument->m_pInstrumentTop = pRout->m_pTail;
			pRout->m_pTail = pInstrument;
			pInstrument->m_iHeadFrameStableNum++;
		} 
		// ����λ��·������
		else
		{
			pInstrumentNext = pRout->m_pHead;
			pInstrumentTop = pRout->m_pHead;
			while(pInstrumentNext != NULL)
			{
				if (pInstrumentNext->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
				{
					pInstrumentTop = pInstrumentNext;
				}
				else
				{
					// �ҵ�·�ɱ��һ���װ�ʱ�̴��ڵ��������װ�ʱ�̵�����
					if (bLocation == false)
					{
						bLocation = true;
						pInstrumentDown = pInstrumentNext;
						if (pInstrumentDown == pInstrument)
						{
							pInstrument->m_iHeadFrameStableNum++;
							pInstrument->m_iLineNb = pInstrumentTop->m_iLineNb + 1;
						}
						// ��·�ɱ������������м��������
						else
						{
							pInstrumentDown->m_pInstrumentTop = pInstrument;
							pInstrument->m_pInstrumentDown = pInstrumentDown;
							pInstrumentTop->m_pInstrumentDown = pInstrument;
							pInstrument->m_pInstrumentTop = pInstrumentTop;
							pInstrumentDown->m_iHeadFrameStableNum = 0;
							pInstrument->m_iHeadFrameStableNum = 0;
							pInstrument->m_iLineNb = pInstrumentTop->m_iLineNb + 1;
							pInstrumentDown->m_iLineNb++;
							bStable = false;	
						}
					}
					else
					{
						if (bStable == false)
						{
							pInstrumentNext->m_iHeadFrameStableNum = 0;
							pInstrumentNext->m_iLineNb++;
						}
					}
				}
				pInstrumentNext = GetNextInstrument(pConstVar->m_iDirectionDown, pInstrumentNext, pConstVar);
			}
		}
	}
}
// ����λ�ð����װ�ʱ������
MatrixServerDll_API void InstrumentLocationSortLeft(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	bool bLocation = false;
	bool bStable = true;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	m_oInstrumentStruct* pInstrumentLeft = NULL;
	m_oInstrumentStruct* pInstrumentRight = NULL;
	if (pConstVar == NULL)
	{
		return;
	}
	if (pInstrument == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSortLeft", "pInstrument", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSortLeft", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ��·�ɷ���β����Ϊ��
	if (pRout->m_pTail == NULL)
	{
		pInstrument->m_iPointIndex = pRout->m_pHead->m_iPointIndex - 1;
		pRout->m_pTail = pInstrument;
		pRout->m_pHead->m_pInstrumentLeft = pInstrument;
		pInstrument->m_pInstrumentRight = pRout->m_pHead;
		pInstrument->m_iHeadFrameStableNum++;
	}
	else
	{
		// ��·�ɷ���β�����װ�ʱ��С�ڸ��������װ�ʱ��
		if (pRout->m_pTail->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
		{
			pInstrument->m_iPointIndex = pRout->m_pTail->m_iPointIndex - 1;
			pRout->m_pTail->m_pInstrumentLeft = pInstrument;
			pInstrument->m_pInstrumentRight = pRout->m_pTail;
			pRout->m_pTail = pInstrument;
			pInstrument->m_iHeadFrameStableNum++;
		} 
		// ����λ��·������
		else
		{
			pInstrumentNext = pRout->m_pHead;
			pInstrumentRight = pRout->m_pHead;
			while(pInstrumentNext != NULL)
			{
				if (pInstrumentNext->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
				{
					pInstrumentRight = pInstrumentNext;
				}
				else
				{
					// �ҵ�·�ɱ��һ���װ�ʱ�̴��ڵ��������װ�ʱ�̵�����
					if (bLocation == false)
					{
						bLocation = true;
						pInstrumentLeft = pInstrumentNext;
						if (pInstrumentLeft == pInstrument)
						{
							pInstrument->m_iHeadFrameStableNum++;
							pInstrument->m_iPointIndex = pInstrumentRight->m_iPointIndex - 1;
						}
						// ��·�ɱ������������м��������
						else
						{
							pInstrumentRight->m_pInstrumentLeft = pInstrument;
							pInstrument->m_pInstrumentRight = pInstrumentRight;
							pInstrumentLeft->m_pInstrumentRight = pInstrument;
							pInstrument->m_pInstrumentLeft = pInstrumentLeft;
							pInstrumentLeft->m_iHeadFrameStableNum = 0;
							pInstrument->m_iHeadFrameStableNum = 0;
							pInstrument->m_iPointIndex = pInstrumentRight->m_iPointIndex - 1;
							pInstrumentLeft->m_iPointIndex--;
							bStable = false;	
						}
					}
					else
					{
						if (bStable == false)
						{
							pInstrumentNext->m_iHeadFrameStableNum = 0;
							pInstrumentNext->m_iPointIndex--;
						}
					}
				}
				pInstrumentNext = GetNextInstrument(pConstVar->m_iDirectionLeft, pInstrumentNext, pConstVar);
			}
		}
	}
}
// ����λ�ð����װ�ʱ������
MatrixServerDll_API void InstrumentLocationSortRight(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	bool bLocation = false;
	bool bStable = true;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	m_oInstrumentStruct* pInstrumentLeft = NULL;
	m_oInstrumentStruct* pInstrumentRight = NULL;
	if (pConstVar == NULL)
	{
		return;
	}
	if (pInstrument == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSortRight", "pInstrument", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSortRight", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ��·�ɷ���β����Ϊ��
	if (pRout->m_pTail == NULL)
	{
		pInstrument->m_iPointIndex = pRout->m_pHead->m_iPointIndex + 1;
		pRout->m_pTail = pInstrument;
		pRout->m_pHead->m_pInstrumentRight = pInstrument;
		pInstrument->m_pInstrumentLeft = pRout->m_pHead;
		pInstrument->m_iHeadFrameStableNum++;
	}
	else
	{
		// ��·�ɷ���β�����װ�ʱ��С�ڸ��������װ�ʱ��
		if (pRout->m_pTail->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
		{
			pInstrument->m_iPointIndex = pRout->m_pTail->m_iPointIndex + 1;
			pRout->m_pTail->m_pInstrumentRight = pInstrument;
			pInstrument->m_pInstrumentLeft = pRout->m_pTail;
			pRout->m_pTail = pInstrument;
			pInstrument->m_iHeadFrameStableNum++;
		} 
		// ����λ��·������
		else
		{
			pInstrumentNext = pRout->m_pHead;
			pInstrumentLeft = pRout->m_pHead;
			while(pInstrumentNext != NULL)
			{
				if (pInstrumentNext->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
				{
					pInstrumentLeft = pInstrumentNext;
				}
				else
				{
					// �ҵ�·�ɱ��һ���װ�ʱ�̴��ڵ��������װ�ʱ�̵�����
					if (bLocation == false)
					{
						bLocation = true;
						pInstrumentRight = pInstrumentNext;
						if (pInstrumentRight == pInstrument)
						{
							pInstrument->m_iHeadFrameStableNum++;
							pInstrument->m_iPointIndex = pInstrumentLeft->m_iPointIndex + 1;
						}
						// ��·�ɱ������������м��������
						else
						{
							pInstrumentRight->m_pInstrumentLeft = pInstrument;
							pInstrument->m_pInstrumentRight = pInstrumentRight;
							pInstrumentLeft->m_pInstrumentRight = pInstrument;
							pInstrument->m_pInstrumentLeft = pInstrumentLeft;
							pInstrumentRight->m_iHeadFrameStableNum = 0;
							pInstrument->m_iHeadFrameStableNum = 0;
							pInstrument->m_iPointIndex = pInstrumentLeft->m_iPointIndex + 1;
							pInstrumentRight->m_iPointIndex++;
							bStable = false;	
						}
					}
					else
					{
						if (bStable == false)
						{
							pInstrumentNext->m_iHeadFrameStableNum = 0;
							pInstrumentNext->m_iPointIndex++;
						}
					}
				}
				pInstrumentNext = GetNextInstrument(pConstVar->m_iDirectionRight, pInstrumentNext, pConstVar);
			}
		}
	}
}
// ����������λ��
MatrixServerDll_API void SetInstrumentLocation(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pInstrument == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SetInstrumentLocation", "pInstrument", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SetInstrumentLocation", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}

	// �Ϸ�
	if (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionTop)
	{
		pInstrument->m_iPointIndex = pRout->m_pHead->m_iPointIndex;
		InstrumentLocationSortTop(pInstrument, pRout, pConstVar);
		pRout->m_uiInstrumentNum = pRout->m_pHead->m_iLineNb - pRout->m_pTail->m_iLineNb;
	}
	// �·�
	else if (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionDown)
	{
		pInstrument->m_iPointIndex = pRout->m_pHead->m_iPointIndex;
		InstrumentLocationSortDown(pInstrument, pRout, pConstVar);
		pRout->m_uiInstrumentNum = pRout->m_pTail->m_iLineNb - pRout->m_pHead->m_iLineNb;
	}
	// ������
	else if (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionLeft)
	{
		pInstrument->m_iLineNb = pRout->m_pHead->m_iLineNb;
		InstrumentLocationSortLeft(pInstrument, pRout, pConstVar);
		pRout->m_uiInstrumentNum = pRout->m_pHead->m_iPointIndex - pRout->m_pTail->m_iPointIndex;
	}
	// �����ҷ�
	else if (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionRight)
	{
		pInstrument->m_iLineNb = pRout->m_pHead->m_iLineNb;
		InstrumentLocationSortRight(pInstrument, pRout, pConstVar);
		pRout->m_uiInstrumentNum = pRout->m_pTail->m_iPointIndex - pRout->m_pHead->m_iPointIndex;
	}
	// LCI
	else
	{
		pInstrument->m_iHeadFrameStableNum++;
		pRout->m_uiInstrumentNum = 1;
	}
}
/**
* ���ý���վĳ�������·��
* @param CInstrument* &pInstrument ����ָ��
* @param unsigned int uiRoutDirection ·�ɷ���
* @return void
*/
MatrixServerDll_API void SetCrossRout(m_oInstrumentStruct* pInstrument,  
	int iRoutDirection, 
	m_oConstVarStruct* pConstVar,
	m_oRoutListStruct* pRoutList)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pInstrument == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SetCrossRout", "pInstrument", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pRoutList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SetCrossRout", "pRoutList", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	m_oRoutStruct* pRout = NULL;
	pRout = GetFreeRout(pRoutList);
	// �жϷ�����������·�ɵ�ַ
	if (iRoutDirection == pConstVar->m_iDirectionTop)
	{
		pInstrument->m_uiRoutIPTop = pRout->m_uiRoutIP;
		// ·��Ϊ�����߷���·��
		pRout->m_bRoutLaux = true;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionDown)
	{
		pInstrument->m_uiRoutIPDown = pRout->m_uiRoutIP;
		// ·��Ϊ�����߷���·��
		pRout->m_bRoutLaux = true;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionLeft)
	{
		pInstrument->m_uiRoutIPLeft = pRout->m_uiRoutIP;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionRight)
	{
		pInstrument->m_uiRoutIPRight = pRout->m_uiRoutIP;
	}
	// ���ý���վ·�ɷ���
	pRout->m_iRoutDirection = iRoutDirection;
	// ����·��ͷ
	pRout->m_pHead = pInstrument;
	if (iRoutDirection == pConstVar->m_iDirectionCenter)
	{
		// ����LCI·��
		pRout->m_uiRoutIP = 0;
		// ����·��β
		pRout->m_pTail = pInstrument;
		// ·��Ϊ�����߷���·��
		pRout->m_bRoutLaux = true;
	}
	else
	{
		// ����·��β
		pRout->m_pTail = NULL;
	}
	// ����·�ɶ����·��ʱ��
	UpdateRoutTime(pRout);
	// ·�ɶ������·��������
	AddRout(pRout->m_uiRoutIP, pRout,&pRoutList->m_oRoutMap);
}
// �������װ�֡
MatrixServerDll_API void ProcHeadFrameOne(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return;
	}
	// ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrument = NULL;
	m_oRoutStruct* pRout = NULL;
	CString str = _T("");
	// �ж�����SN�Ƿ���SN��������
	if(TRUE == IfIndexExistInMap(pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiSN, 
		&pHeadFrameThread->m_pInstrumentList->m_oSNInstrumentMap))
	{
		// �������������ҵ�������,�õ�������ָ��
		pInstrument = GetInstrumentFromMap(pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiSN, 
			&pHeadFrameThread->m_pInstrumentList->m_oSNInstrumentMap);
		if (TRUE == IfIndexExistInRoutMap(pInstrument->m_uiRoutIP, &pHeadFrameThread->m_pRoutList->m_oRoutMap))
		{
			pRout = GetRout(pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiRoutIP,
				&pHeadFrameThread->m_pRoutList->m_oRoutMap);
			// ����·�ɶ����·��ʱ��
			UpdateRoutTime(pRout);
			// �������������װ�ʱ��
			pInstrument->m_uiTimeHeadFrame = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiTimeHeadFrame;
			// ����������λ����Ϣ
			SetInstrumentLocation(pInstrument, pRout, pHeadFrameThread->m_pThread->m_pConstVar);
		}
		// �����������·�ɷ�����λ���ȶ����������趨����
		// �򽫸���������IP��ַ���ö���
		if (pInstrument->m_iHeadFrameStableNum >= pHeadFrameThread->m_pThread->m_pConstVar->m_iHeadFrameStableTimes)
		{
			if (FALSE == IfIndexExistInMap(pInstrument->m_uiIP, &pHeadFrameThread->m_pInstrumentList->m_oIPSetMap))
			{
				AddInstrumentToMap(pInstrument->m_uiIP, pInstrument, &pHeadFrameThread->m_pInstrumentList->m_oIPSetMap);
			}
		}
	}
	else
	{
		int iDirection = 0;
		// �õ�������
		pInstrument = GetFreeInstrument(pHeadFrameThread->m_pInstrumentList);
		//������������SN
		pInstrument->m_uiSN = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiSN;
		// ��������
		pInstrument->m_iInstrumentType = pInstrument->m_uiSN & 0xff;
		//������������·��IP��ַ
		pInstrument->m_uiRoutIP = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiRoutIP;
		// ��������������������
		// ·�ɵ�ַΪ0ΪLCI
		if (pInstrument->m_uiRoutIP == 0)
		{
			pInstrument->m_iInstrumentType = pHeadFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI;
			pInstrument->m_iRoutDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionCenter;
			// �õ�����·�ɶ���
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionCenter;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
		}
		else
		{
			if (TRUE == IfIndexExistInRoutMap(pInstrument->m_uiRoutIP,
				&pHeadFrameThread->m_pRoutList->m_oRoutMap))
			{
				pRout = GetRout(pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiRoutIP,
					&pHeadFrameThread->m_pRoutList->m_oRoutMap);
				// ����·�ɶ����·��ʱ��
				UpdateRoutTime(pRout);
				pInstrument->m_iRoutDirection = pRout->m_iRoutDirection;
			}
			else
			{
				str.Format(_T("����SN = 0x%x��·��IP = 0x%x"), pInstrument->m_uiSN, pInstrument->m_uiRoutIP);
				// ����LCIȴ���Ҳ���·�����¼��־
				AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", 
					ConvertCStrToStr(str), ErrorType, IDS_ERR_ROUT_NOTEXIT);
			}
		}

		if ((pInstrument->m_iInstrumentType == pHeadFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pHeadFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLAUX))
		{
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionTop;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionDown;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionLeft;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionRight;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
		}
		pInstrument->m_uiBroadCastPort = pHeadFrameThread->m_pThread->m_pConstVar->m_iBroadcastPortStart + pInstrument->m_uiRoutIP;
		// ����������SN������
		AddInstrumentToMap(pInstrument->m_uiSN, pInstrument, &pHeadFrameThread->m_pInstrumentList->m_oSNInstrumentMap);
	}
	str.Format(_T("���յ�SN = 0x%x�������װ�֡���װ�ʱ�� = 0x%x��·��IP = 0x%x, ���ߺ� = %d�������� = %d"), 
		pInstrument->m_uiSN, pInstrument->m_uiTimeHeadFrame, pInstrument->m_uiRoutIP, pInstrument->m_iLineNb, pInstrument->m_iPointIndex);
	AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", ConvertCStrToStr(str));
}
// �����װ�֡
MatrixServerDll_API void ProcHeadFrame(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pHeadFrameThread->m_pHeadFrame->m_oHeadFrameSocket,
		pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pHeadFrameThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pHeadFrameThread->m_pHeadFrame->m_oHeadFrameSocket,
				pHeadFrameThread->m_pHeadFrame->m_pcRcvFrameData, 
				pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pHeadFrameThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentHeadFrame(pHeadFrameThread->m_pHeadFrame, 
					pHeadFrameThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ParseInstrumentHeadFrame", 
						"", ErrorType, IDS_ERR_PARSE_HEADFRAME);
				}
				else
				{
					EnterCriticalSection(&pHeadFrameThread->m_pInstrumentList->m_oSecInstrumentList);
					EnterCriticalSection(&pHeadFrameThread->m_pRoutList->m_oSecRoutList);
					// �������װ�֡
					ProcHeadFrameOne(pHeadFrameThread);
					// ϵͳ�����仯��ʱ��
					UpdateLineChangeTime(pHeadFrameThread->m_pInstrumentList);
					LeaveCriticalSection(&pHeadFrameThread->m_pRoutList->m_oSecRoutList);
					LeaveCriticalSection(&pHeadFrameThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
}
// �̵߳ȴ�����
MatrixServerDll_API void WaitHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pHeadFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pHeadFrameThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pHeadFrameThread->m_pThread->m_pConstVar->m_iHeadFrameSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pHeadFrameThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pHeadFrameThread->m_pThread->m_bWork == true)
		{
			// �����װ�֡
			ProcHeadFrame(pHeadFrameThread);
		}
		if (pHeadFrameThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitHeadFrameThread(pHeadFrameThread);
	}
	::SetEvent(pHeadFrameThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ���װ������߳�
MatrixServerDll_API bool OnInitHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return false;
	}
	pHeadFrameThread->m_pThread->m_bClose = false;
	pHeadFrameThread->m_pThread->m_bWork = false;
	pHeadFrameThread->m_pThread->m_hThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if (pHeadFrameThread->m_pThread->m_hThreadClose == NULL)
	{
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnInitHeadFrameThread", 
			"pHeadFrameThread->m_pThread->m_hThreadClose", ErrorType, IDS_ERR_CREATE_EVENT);
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnInitHeadFrameThread", 
			"pHeadFrameThread->m_pThread->m_hThreadClose", ErrorType, ERROR_ALREADY_EXISTS);
	}
	::ResetEvent(pHeadFrameThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pHeadFrameThread->m_pThread->m_hThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunHeadFrameThread,
		pHeadFrameThread, 
		0, 
		&pHeadFrameThread->m_pThread->m_dwThreadID);
	if (pHeadFrameThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnInitHeadFrameThread", 
			"pHeadFrameThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnInitHeadFrameThread", "�װ������̴߳����ɹ�");
	return true;
}
// �ر��װ������߳�
MatrixServerDll_API bool OnCloseHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return false;
	}
	int iResult = WaitForSingleObject(pHeadFrameThread->m_pThread->m_hThreadClose, 
		pHeadFrameThread->m_pThread->m_pConstVar->m_iCloseThreadSleepTimes
		* pHeadFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
	if (iResult != WAIT_OBJECT_0)
	{
		::TerminateThread(pHeadFrameThread->m_pThread->m_hThread, 0);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnCloseHeadFrameThread", 
			"�װ��߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnCloseHeadFrameThread", "�װ��̳߳ɹ��ر�");
	return true;
}
// �ͷ��װ������߳�
MatrixServerDll_API void OnFreeHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return;
	}
	if (pHeadFrameThread->m_pThread != NULL)
	{
		delete pHeadFrameThread->m_pThread;
	}
	delete pHeadFrameThread;
}
// ����IP��ַ�����߳�
MatrixServerDll_API m_oIPSetFrameThreadStruct* OnCreateIPSetFrameThread(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oIPSetFrameThreadStruct* pIPSetFrameThread = NULL;
	pIPSetFrameThread = new m_oIPSetFrameThreadStruct;
	pIPSetFrameThread->m_pThread = new m_oThreadStruct;
	pIPSetFrameThread->m_pThread->m_pLogOutPut = pLogOutPut;
	pIPSetFrameThread->m_pThread->m_hThread = INVALID_HANDLE_VALUE;
	pIPSetFrameThread->m_pThread->m_hThreadClose = INVALID_HANDLE_VALUE;
	pIPSetFrameThread->m_pThread->m_dwThreadID = 0;
	return pIPSetFrameThread;
}
// ������IP��ַ����Ӧ��֡
MatrixServerDll_API void  ProcIPSetReturnFrameOne(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	unsigned short usCommand = 0;
	CString str = _T("");
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	// �õ�����IP
	uiIPInstrument = pIPSetFrameThread->m_pIPSetFrame->m_pCommandStructReturn->m_uiInstrumentIP;
	// ��������������
	if (TRUE == IfIndexExistInMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap))
	{
		pInstrument = GetInstrumentFromMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap);
		// ��IP��ַ������������ɾ������
		DeleteInstrumentFromMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap);
		// ����������IP��ַ������
		pInstrument->m_bIPSetOK = true;
		AddInstrumentToMap(uiIPInstrument, pInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPInstrumentMap);
		usCommand = pIPSetFrameThread->m_pIPSetFrame->m_pCommandStructReturn->m_usCommand;
		if (usCommand == pIPSetFrameThread->m_pThread->m_pConstVar->m_usSendSetCmd)
		{
			str.Format(_T("���յ�SN = 0x%x��IP��ַ = 0x%x������IP��ַ����Ӧ��"), 
				pInstrument->m_uiSN, uiIPInstrument);
		}
		else if (usCommand == pIPSetFrameThread->m_pThread->m_pConstVar->m_usSendQueryCmd)
		{
			str.Format(_T("���յ�SN = 0x%x��IP��ַ = 0x%x������IP��ַ��ѯӦ��"), 
				pInstrument->m_uiSN, uiIPInstrument);
		}
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetReturnFrameOne", ConvertCStrToStr(str));
	}
	else
	{
		str.Format(_T("���յ�IP��ַ = 0x%x��IP��ַӦ��"), uiIPInstrument);
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetReturnFrameOne", ConvertCStrToStr(str),
			ErrorType, IDS_ERR_IPSETMAP_NOTEXIT);
	}
}
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API void ProcIPSetReturnFrame(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pIPSetFrameThread->m_pIPSetFrame->m_oIPSetFrameSocket,
		pIPSetFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pIPSetFrameThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pIPSetFrameThread->m_pIPSetFrame->m_oIPSetFrameSocket,
				pIPSetFrameThread->m_pIPSetFrame->m_pcRcvFrameData, 
				pIPSetFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pIPSetFrameThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentIPSetReturnFrame(pIPSetFrameThread->m_pIPSetFrame, 
					pIPSetFrameThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ParseInstrumentIPSetReturnFrame",
						"", ErrorType, IDS_ERR_PARSE_IPSETRETURNFRAME);
				}
				else
				{
					EnterCriticalSection(&pIPSetFrameThread->m_pInstrumentList->m_oSecInstrumentList);
					// ������IP��ַ����Ӧ��֡
					ProcIPSetReturnFrameOne(pIPSetFrameThread);
					LeaveCriticalSection(&pIPSetFrameThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
}
// ����IP��ַ������������IP��ַ����֡
MatrixServerDll_API void ProcIPSetFrame(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	CString str = _T("");
	EnterCriticalSection(&pIPSetFrameThread->m_pInstrumentList->m_oSecInstrumentList);
	// hash_map������
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator  iter;
	// IP��ַ����������Ϊ��
	if (false == pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap.empty())
	{
		// �������������豸��IP��ַ����֡
		for(iter = pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap.begin(); iter != pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap.end();)
		{
			// IP��ַ���ô���Ϊ0
			if (iter->second->m_iIPSetCount == 0)
			{
				// ����IP��ַ����֡
				MakeInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, pIPSetFrameThread->m_pThread->m_pConstVar, iter->second);
				// ����IP��ַ����֡
				SendInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, pIPSetFrameThread->m_pThread->m_pConstVar);
				// �ڼ�������IP��ַ
				iter->second->m_iIPSetCount++;
				iter++;
			}
			// IP��ַ���ô���������ָ����������������IP��ַ�Ͳ�ѯIP��ַ
			else if (iter->second->m_iIPSetCount <= pIPSetFrameThread->m_pThread->m_pConstVar->m_iIPAddrResetTimes)
			{
				// ����IP��ַ��ѯ֡
				MakeInstrumentIPQueryFrame(pIPSetFrameThread->m_pIPSetFrame, pIPSetFrameThread->m_pThread->m_pConstVar, iter->second->m_uiIP);
				// ����IP��ַ��ѯ֡
				SendInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, pIPSetFrameThread->m_pThread->m_pConstVar);

				// ����IP��ַ����֡
				MakeInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, pIPSetFrameThread->m_pThread->m_pConstVar, iter->second);
				// ����IP��ַ����֡
				SendInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, pIPSetFrameThread->m_pThread->m_pConstVar);
				// �ڼ�������IP��ַ
				iter->second->m_iIPSetCount++;
				iter++;
				AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetFrame",
					"�ط�IP��ַ����֡��IP��ַ��ѯ֡", WarningType);
			}
			// IP��ַ���ô�������ָ�����������������ɾ��������ָ��
			else
			{
				str.Format(_T("����SN = 0x%x��IP��ַ = 0x%x ����������IP��ַ����֡����ָ������"), 
					iter->second->m_uiSN, iter->second->m_uiIP);
				// ���������־
				AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetFrame",
					ConvertCStrToStr(str), WarningType);
				iter->second->m_iIPSetCount = 0;
				pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap.erase(iter++);
			}
		}
	}
	LeaveCriticalSection(&pIPSetFrameThread->m_pInstrumentList->m_oSecInstrumentList);
}
// �̵߳ȴ�����
MatrixServerDll_API void WaitIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pIPSetFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pIPSetFrameThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pIPSetFrameThread->m_pThread->m_pConstVar->m_iIPSetFrameSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pIPSetFrameThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pIPSetFrameThread->m_pThread->m_bWork == true)
		{
			// ����IP��ַ����Ӧ��֡
			ProcIPSetReturnFrame(pIPSetFrameThread);
			// ����IP��ַ������������IP��ַ����֡
			ProcIPSetFrame(pIPSetFrameThread);
		}
		if (pIPSetFrameThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitIPSetFrameThread(pIPSetFrameThread);
	}
	::SetEvent(pIPSetFrameThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ��IP��ַ�����߳�
MatrixServerDll_API bool OnInitIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return false;
	}
	pIPSetFrameThread->m_pThread->m_bClose = false;
	pIPSetFrameThread->m_pThread->m_bWork = false;
	pIPSetFrameThread->m_pThread->m_hThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if (pIPSetFrameThread->m_pThread->m_hThreadClose == NULL)
	{
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnInitIPSetFrameThread",
			"pIPSetFrameThread->m_pThread->m_hThreadClose", ErrorType, IDS_ERR_CREATE_EVENT);
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnInitIPSetFrameThread", 
			"pIPSetFrameThread->m_pThread->m_hThreadClose", ErrorType, ERROR_ALREADY_EXISTS);
	}
	::ResetEvent(pIPSetFrameThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pIPSetFrameThread->m_pThread->m_hThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunIPSetFrameThread,
		pIPSetFrameThread, 
		0, 
		&pIPSetFrameThread->m_pThread->m_dwThreadID);
	if (pIPSetFrameThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnInitIPSetFrameThread", 
			"pIPSetFrameThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnInitIPSetFrameThread", "IP��ַ�����̴߳����ɹ�");
	return true;
}
// �ر�IP��ַ�����߳�
MatrixServerDll_API bool OnCloseIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return false;
	}
	int iResult = WaitForSingleObject(pIPSetFrameThread->m_pThread->m_hThreadClose, 
		pIPSetFrameThread->m_pThread->m_pConstVar->m_iCloseThreadSleepTimes
		* pIPSetFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
	if (iResult != WAIT_OBJECT_0)
	{
		::TerminateThread(pIPSetFrameThread->m_pThread->m_hThread, 0);
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnCloseIPSetFrameThread", 
			"IP��ַ�����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnCloseIPSetFrameThread", "IP��ַ�����̳߳ɹ��ر�");
	return true;
}
// �ͷ�IP��ַ�����߳�
MatrixServerDll_API void OnFreeIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	if (pIPSetFrameThread->m_pThread != NULL)
	{
		delete pIPSetFrameThread->m_pThread;
	}
	delete pIPSetFrameThread;
}
// ����β�������߳�
MatrixServerDll_API m_oTailFrameThreadStruct* OnCreateTailFrameThread(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oTailFrameThreadStruct* pTailFrameThread = NULL;
	pTailFrameThread = new m_oTailFrameThreadStruct;
	pTailFrameThread->m_pThread = new m_oThreadStruct;
	pTailFrameThread->m_pThread->m_pLogOutPut = pLogOutPut;
	pTailFrameThread->m_pThread->m_hThread = INVALID_HANDLE_VALUE;
	pTailFrameThread->m_pThread->m_hThreadClose = INVALID_HANDLE_VALUE;
	pTailFrameThread->m_pThread->m_dwThreadID = 0;
	return pTailFrameThread;
}
// �̵߳ȴ�����
MatrixServerDll_API void WaitTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pTailFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pTailFrameThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pTailFrameThread->m_pThread->m_pConstVar->m_iTailFrameSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// ����������·�ɷ�����ͬ��֮ǰ������β������
MatrixServerDll_API void OnClearSameRoutTailCount(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	if (pInstrument == NULL)
	{
		return;
	}
	if (pRout == NULL)
	{
		return;
	}
	// ��һ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrumentNext = NULL;
	pInstrumentNext = GetNextInstrument(pInstrument->m_iRoutDirection, pRout->m_pHead, pConstVar);
	while(pInstrument != pInstrumentNext)
	{
		if (pInstrumentNext == NULL)
		{
			break;
		}
		pInstrumentNext->m_iTailFrameCount = 0;
		pInstrumentNext = GetNextInstrument(pInstrumentNext->m_iRoutDirection, pInstrumentNext, pConstVar);
	}
}
// ����һ��·��
MatrixServerDll_API void FreeRoutFromMap(unsigned int uiRoutIP, m_oRoutListStruct* pRoutList)
{
	m_oRoutStruct* pRout = NULL;
	CString str = _T("");
	pRout = GetRout(uiRoutIP, &pRoutList->m_oRoutMap);
	AddRout(uiRoutIP, pRout, &pRoutList->m_oRoutDeleteMap);
}
// ����һ������
MatrixServerDll_API void FreeInstrumentFromMap(m_oInstrumentStruct* pInstrument, 
	m_oInstrumentListStruct* pInstrumentList, 
	m_oRoutListStruct* pRoutList, 
	m_oConstVarStruct* pConstVar)
{
	if (pInstrument == NULL)
	{
		return;
	}
	if (pInstrumentList == NULL)
	{
		return;
	}
	CString str = _T("");
	// ��SN��������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiSN, &pInstrumentList->m_oSNInstrumentMap);
	// ��IP��ַ������������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pInstrumentList->m_oIPSetMap);
	// ��IP��ַ��������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pInstrumentList->m_oIPInstrumentMap);
	// ��ADC����������������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pInstrumentList->m_oADCSetInstrumentMap);
	str.Format(_T("ɾ��������SN = 0x%x��·�� = 0x%x"), pInstrument->m_uiSN, pInstrument->m_uiRoutIP);
	AddMsgToLogOutPutList(pInstrumentList->m_pLogOutPut, "FreeInstrumentFromMap", ConvertCStrToStr(str));

	// ɾ������������ΪLCI�򽻲�վ
	if ((pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLCI)
		|| (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLAUX))
	{
		if (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLCI)
		{
			FreeRoutFromMap(pInstrument->m_uiRoutIP, pRoutList);
		}
		// �����Ϸ�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPTop, pRoutList);
		// �����·�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPDown, pRoutList);
		// ������·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPLeft, pRoutList);
		// �����ҷ�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPRight, pRoutList);
	}
	// ���������뵽������������
	AddFreeInstrument(pInstrument, pInstrumentList);
	// ϵͳ�����仯��ʱ��
	UpdateLineChangeTime(pInstrumentList);
}
// ɾ����·�ɷ���ָ������֮�������
MatrixServerDll_API void DeleteInstrumentAlongRout(m_oInstrumentStruct* pInstrument, 
	m_oRoutStruct* pRout, 
	m_oInstrumentListStruct* pInstrumentList, 
	m_oRoutListStruct* pRoutList, 
	m_oConstVarStruct* pConstVar)
{
	if (pInstrumentList == NULL)
	{
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pInstrumentList->m_pLogOutPut, "DeleteInstrumentAlongRout", 
			"pRout", ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pConstVar == NULL)
	{
		AddMsgToLogOutPutList(pInstrumentList->m_pLogOutPut, "DeleteInstrumentAlongRout", 
			"pConstVar", ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ǰһ������ָ��Ϊ·��β����
	m_oInstrumentStruct* pInstrumentPrevious = pRout->m_pTail;
	m_oInstrumentStruct* pInstrumentDelete = NULL;
	CString str = _T("");
	while (pInstrument != pInstrumentPrevious)
	{
		if (pInstrumentPrevious == NULL)
		{
			break;
		}
		pInstrumentDelete = pInstrumentPrevious;
		// �õ�Ҫɾ����������·�ɷ����ǰһ��������ָ��
		pInstrumentPrevious = GetPreviousInstrument(pInstrumentDelete->m_iRoutDirection, pInstrumentDelete, pConstVar);
		pRout->m_pTail = pInstrumentPrevious;
		if (pRout->m_pTail == pRout->m_pHead)
		{
			pRout->m_pTail = NULL;
		}
		// ����һ������
		FreeInstrumentFromMap(pInstrumentDelete, pInstrumentList, pRoutList, pConstVar);
		pRout->m_uiInstrumentNum--;
	}
}
// ������β��֡
MatrixServerDll_API void ProcTailFrameOne(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return;
	}
	// ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrument = NULL;
	m_oRoutStruct* pRout = NULL;
	hash_map <unsigned int, m_oRoutStruct*> :: iterator iter;
	CString str = _T("");
	str.Format(_T("���յ�SN = 0x%x��·�� = 0x%x ��������β��"),
		pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiSN,pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiRoutIP);
	// �ж�����SN�Ƿ���SN��������
	if(TRUE == IfIndexExistInMap(pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiSN, 
		&pTailFrameThread->m_pInstrumentList->m_oSNInstrumentMap))
	{
		// �������������ҵ�������,�õ�������ָ��
		pInstrument = GetInstrumentFromMap(pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiSN, 
			&pTailFrameThread->m_pInstrumentList->m_oSNInstrumentMap);
		// β����������һ
		pInstrument->m_iTailFrameCount++;
// 		// ����β��������β��ʱ��
// 		pInstrument->m_uiTailSysTime = pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiSysTime;
		// ��·�����������ҵ���β�����ڵ�·��
		if (TRUE == IfIndexExistInRoutMap(pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiRoutIP,
			&pTailFrameThread->m_pRoutList->m_oRoutMap))
		{
			AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne", ConvertCStrToStr(str));
			// ��·��IP�õ�·�ɶ���
			pRout = GetRout(pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiRoutIP,
				&pTailFrameThread->m_pRoutList->m_oRoutMap);
			// ����·�ɶ����·��ʱ��
			UpdateRoutTime(pRout);
			// ����������·�ɷ�����ͬ��֮ǰ������β������
			OnClearSameRoutTailCount(pInstrument, pRout, pTailFrameThread->m_pThread->m_pConstVar);
			// �ж�β���������ﵽ�趨ֵ��ɾ����ͬ·��֮�������
			if (pInstrument->m_iTailFrameCount > pTailFrameThread->m_pThread->m_pConstVar->m_iTailFrameStableTimes)
			{
				if (pRout->m_pTail != NULL)
				{
					DeleteInstrumentAlongRout(pInstrument, pRout, pTailFrameThread->m_pInstrumentList, 
						pTailFrameThread->m_pRoutList, pTailFrameThread->m_pThread->m_pConstVar);
					while(true)
					{
						if (pTailFrameThread->m_pRoutList->m_oRoutDeleteMap.empty() == true)
						{
							break;
						}
						iter = pTailFrameThread->m_pRoutList->m_oRoutDeleteMap.begin();
						DeleteInstrumentAlongRout(iter->second->m_pHead, iter->second, pTailFrameThread->m_pInstrumentList, 
							pTailFrameThread->m_pRoutList, pTailFrameThread->m_pThread->m_pConstVar);
						// ·�����������·��
						DeleteRout(iter->first, &pTailFrameThread->m_pRoutList->m_oRoutMap);
						str.Format(_T("����·��IP = 0x%x�Ĺ���·��"), iter->first);
						AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne", ConvertCStrToStr(str));
						// ������·�ɻ��յ�����·�ɶ���
						AddFreeRout(iter->second, pTailFrameThread->m_pRoutList);
						// ·��ɾ�����������·��
						DeleteRout(iter->first, &pTailFrameThread->m_pRoutList->m_oRoutDeleteMap);
						// ADC�����������������·��
						DeleteRout(iter->first, &pTailFrameThread->m_pRoutList->m_oADCSetRoutMap);
					}
				}
				pInstrument->m_iTailFrameCount = 0;
			}
		}
		else
		{
			AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne", ConvertCStrToStr(str), 
				ErrorType, IDS_ERR_ROUT_NOTEXIT);
		}
	}
	else
	{
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne", ConvertCStrToStr(str));
	}
}
// ����β��֡
MatrixServerDll_API void ProcTailFrame(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTailFrameThread->m_pTailFrame->m_oTailFrameSocket,
		pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTailFrameThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pTailFrameThread->m_pTailFrame->m_oTailFrameSocket,
				pTailFrameThread->m_pTailFrame->m_pcRcvFrameData, 
				pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTailFrameThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentTailFrame(pTailFrameThread->m_pTailFrame, 
					pTailFrameThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ParseInstrumentTailFrame", 
						"", ErrorType, IDS_ERR_PARSE_HEADFRAME);
				}
				else
				{
					EnterCriticalSection(&pTailFrameThread->m_pInstrumentList->m_oSecInstrumentList);
					EnterCriticalSection(&pTailFrameThread->m_pRoutList->m_oSecRoutList);
					// ������β��֡
					ProcTailFrameOne(pTailFrameThread);
					LeaveCriticalSection(&pTailFrameThread->m_pRoutList->m_oSecRoutList);
					LeaveCriticalSection(&pTailFrameThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
}
// �̺߳���
DWORD WINAPI RunTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pTailFrameThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pTailFrameThread->m_pThread->m_bWork == true)
		{
			// ����β������
			ProcTailFrame(pTailFrameThread);
		}
		if (pTailFrameThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitTailFrameThread(pTailFrameThread);
	}
	::SetEvent(pTailFrameThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ��β�������߳�
MatrixServerDll_API bool OnInitTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return false;
	}
	pTailFrameThread->m_pThread->m_bClose = false;
	pTailFrameThread->m_pThread->m_bWork = false;
	pTailFrameThread->m_pThread->m_hThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if (pTailFrameThread->m_pThread->m_hThreadClose == NULL)
	{
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnInitTailFrameThread",
			"pTailFrameThread->m_pThread->m_hThreadClose", ErrorType, IDS_ERR_CREATE_EVENT);
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnInitTailFrameThread", 
			"pTailFrameThread->m_pThread->m_hThreadClose", ErrorType, ERROR_ALREADY_EXISTS);
	}
	::ResetEvent(pTailFrameThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pTailFrameThread->m_pThread->m_hThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunTailFrameThread,
		pTailFrameThread, 
		0, 
		&pTailFrameThread->m_pThread->m_dwThreadID);
	if (pTailFrameThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnInitTailFrameThread", 
			"pTailFrameThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnInitTailFrameThread", "β�������̴߳����ɹ�");
	return true;
}
// �ر�β�������߳�
MatrixServerDll_API bool OnCloseTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return false;
	}
	int iResult = WaitForSingleObject(pTailFrameThread->m_pThread->m_hThreadClose, 
		pTailFrameThread->m_pThread->m_pConstVar->m_iCloseThreadSleepTimes
		* pTailFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
	if (iResult != WAIT_OBJECT_0)
	{
		::TerminateThread(pTailFrameThread->m_pThread->m_hThread, 0);
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnCloseTailFrameThread", 
			"β�������߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnCloseTailFrameThread", "β�������̳߳ɹ��ر�");
	return true;
}
// �ͷ�β�������߳�
MatrixServerDll_API void OnFreeTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return;
	}
	if (pTailFrameThread->m_pThread != NULL)
	{
		delete pTailFrameThread->m_pThread;
	}
	delete pTailFrameThread;
}
// ����·�ɼ����߳�
MatrixServerDll_API m_oMonitorRoutThreadStruct* OnCreateMonitorRoutThread(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oMonitorRoutThreadStruct* pMonitorRoutThread = NULL;
	pMonitorRoutThread = new m_oMonitorRoutThreadStruct;
	pMonitorRoutThread->m_pThread = new m_oThreadStruct;
	pMonitorRoutThread->m_pThread->m_pLogOutPut = pLogOutPut;
	pMonitorRoutThread->m_pThread->m_hThread = INVALID_HANDLE_VALUE;
	pMonitorRoutThread->m_pThread->m_hThreadClose = INVALID_HANDLE_VALUE;
	pMonitorRoutThread->m_pThread->m_dwThreadID = 0;
	pMonitorRoutThread->m_pTimeDelayThread = NULL;
	pMonitorRoutThread->m_pADCSetThread = NULL;
	return pMonitorRoutThread;
}
// �̵߳ȴ�����
MatrixServerDll_API void WaitMonitorRoutThread(m_oMonitorRoutThreadStruct* pMonitorRoutThread)
{
	if (pMonitorRoutThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pMonitorRoutThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pMonitorRoutThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pMonitorRoutThread->m_pThread->m_pConstVar->m_iMonitorRoutSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// ����·�ɷ���õ�ʱͳ����
MatrixServerDll_API void GetTimeDelayTaskAlongRout(m_oRoutStruct* pRout, m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar)
{
	m_oInstrumentStruct* pInstrumentNext = NULL;
	m_oInstrumentStruct* pInstrument = NULL;
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pConstVar);
		pInstrument = pInstrumentNext;
		// �������Ϊ����վ
		if ((pInstrumentNext->m_iInstrumentType == pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrumentNext->m_iInstrumentType == pConstVar->m_iInstrumentTypeLAUX))
		{
			// �������ĸ������·�ɼ�����ʱ����
			pRoutList->m_olsTimeDelayTemp.push_back(pInstrumentNext->m_uiRoutIPTop);
			pRoutList->m_olsTimeDelayTemp.push_back(pInstrumentNext->m_uiRoutIPDown);
			pRoutList->m_olsTimeDelayTemp.push_back(pInstrumentNext->m_uiRoutIPLeft);
			pRoutList->m_olsTimeDelayTemp.push_back(pInstrumentNext->m_uiRoutIPRight);
		}
	} while (pInstrumentNext != pRout->m_pTail);
}
// �õ�ʱͳ����
MatrixServerDll_API void GetTimeDelayTask(m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pRoutList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetTimeDelayTask", "pRoutList", ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	m_oRoutStruct* pRout = NULL;
	unsigned int uiRoutIP = 0;
	CString str = _T("");
	while(false == pRoutList->m_olsTimeDelayTemp.empty())
	{
		uiRoutIP = *pRoutList->m_olsTimeDelayTemp.begin();
		pRoutList->m_olsTimeDelayTemp.pop_front();
		// �жϸ�·���Ƿ���·����������
		if (TRUE == IfIndexExistInRoutMap(uiRoutIP, &pRoutList->m_oRoutMap))
		{
			// �õ�·��ָ��
			pRout = GetRout(uiRoutIP, &pRoutList->m_oRoutMap);
			if (pRout->m_pTail != NULL)
			{
				// ����LCI
				if (uiRoutIP != 0)
				{
					// ����·��IP�����������
					pRoutList->m_olsTimeDelayTaskQueue.push_back(uiRoutIP);
					str.Format(_T("��·��IP = 0x%x ����ʱͳ�������"), uiRoutIP);
					AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetTimeDelayTask", ConvertCStrToStr(str));
				}
				// ����·�ɷ���õ�ʱͳ����
				GetTimeDelayTaskAlongRout(pRout, pRoutList, pConstVar);
			}
		}
	}
}
// ����ʱͳ�������
MatrixServerDll_API void GenTimeDelayTaskQueue(m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pRoutList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GenTimeDelayTaskQueue", "pRoutList", ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ����������
	pRoutList->m_olsTimeDelayTaskQueue.clear();
	pRoutList->m_olsTimeDelayTemp.clear();
	// ��LCI·�ɼ�����ʱ����
	pRoutList->m_olsTimeDelayTemp.push_back(0);
	AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GenTimeDelayTaskQueue", "��ǰϵͳ�ȶ�������ʱͳ�������");
	// �õ�ʱͳ����
	GetTimeDelayTask(pRoutList, pConstVar);
}
// �ж�·�ɷ������Ƿ��вɼ�վ
MatrixServerDll_API void GetADCTaskQueueByRout(m_oADCSetThreadStruct* pADCSetThread, 
	m_oRoutStruct* pRout, int iOpt)
{
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	bool bRoutADCSet = true;
	bool bADCSet = true;
	if (pRout->m_pTail == NULL)
	{
		return;
	}
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, 
			pADCSetThread->m_pThread->m_pConstVar);
		if (pInstrumentNext->m_iInstrumentType == pADCSetThread->m_pThread->m_pConstVar->m_iInstrumentTypeFDU)
		{
			if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCSetOptNb)
			{
				if (false == pInstrumentNext->m_bADCSet)
				{
					bADCSet = false;
				}
				else
				{
					bADCSet = true;
				}
			}
			else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleOptNb)
			{
				if ((true == pADCSetThread->m_bADCStartSample)
					&& (false == pInstrumentNext->m_bADCStartSample))
				{
					bADCSet = false;
				}
				else
				{
					bADCSet = true;
				}
			}
			else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleOptNb)
			{
				if ((true == pADCSetThread->m_bADCStopSample)
					&& (false == pInstrumentNext->m_bADCStopSample))
				{
					bADCSet = false;
				}
				else
				{
					bADCSet = true;
				}
			}
			if (bADCSet == false)
			{
				pInstrumentNext->m_bADCSetReturn = false;
				AddInstrumentToMap(pInstrumentNext->m_uiIP, pInstrumentNext, &pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
			}
			else
			{
				DeleteInstrumentFromMap(pInstrumentNext->m_uiIP, &pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
				bRoutADCSet = false;
			}
		}
		pInstrument = pInstrumentNext;
	} while (pInstrumentNext != pRout->m_pTail);
	if (bRoutADCSet == true)
	{
		// ��·�ɼ�������
		pRout->m_bADCSetReturn = false;
		pRout->m_bADCSetRout = true;
		AddRout(pRout->m_uiRoutIP, pRout, &pADCSetThread->m_pRoutList->m_oADCSetRoutMap);
		// ������������ɾ����·�ɵ�����
		pInstrument = pRout->m_pHead;
		do 
		{
			pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pADCSetThread->m_pThread->m_pConstVar);
			if (pInstrumentNext->m_iInstrumentType == pADCSetThread->m_pThread->m_pConstVar->m_iInstrumentTypeFDU)
			{
				DeleteInstrumentFromMap(pInstrumentNext->m_uiIP, &pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
			}
			pInstrument = pInstrumentNext;
		} while (pInstrumentNext != pRout->m_pTail);
	}
	else
	{
		DeleteRout(pRout->m_uiRoutIP, &pADCSetThread->m_pRoutList->m_oADCSetRoutMap);
	}
}
// ����ADC���������������
MatrixServerDll_API void GetADCTaskQueue(m_oADCSetThreadStruct* pADCSetThread, int iOpt)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	// ����·�ɵ�ַ������
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	for (iter = pADCSetThread->m_pRoutList->m_oRoutMap.begin(); iter != pADCSetThread->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		// ��·���������еĴ��߷���·�ɼ��뵽ADC����������������
		if (iter->second->m_bRoutLaux == false)
		{
			GetADCTaskQueueByRout(pADCSetThread, iter->second, iOpt);
		}
	}
}
MatrixServerDll_API void OnADCCmdAuto(m_oADCSetThreadStruct* pADCSetThread, int iOpt)
{
	// ����ADC���������������
	GetADCTaskQueue(pADCSetThread, iOpt);
	if ((false == pADCSetThread->m_pRoutList->m_oADCSetRoutMap.empty())
		|| (false == pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.empty()))
	{
		// ����ADC��������
		pADCSetThread->m_uiCounter = 0;
		if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCSetOptNb)
		{
			pADCSetThread->m_uiADCSetOperationNb = 1;
		}
		else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleOptNb)
		{
			pADCSetThread->m_uiADCSetOperationNb = 12;
		}
		else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleOptNb)
		{
			pADCSetThread->m_uiADCSetOperationNb = 19;
		}
		// ADC���������߳̿�ʼ����
		pADCSetThread->m_pThread->m_bWork = true;
	}
}
// ADC��������
MatrixServerDll_API void OnADCSetAuto(m_oADCSetThreadStruct* pADCSetThread)
{
	OnADCCmdAuto(pADCSetThread, pADCSetThread->m_pThread->m_pConstVar->m_iADCSetOptNb);
}
// ADC��ʼ�ɼ�����
MatrixServerDll_API void OnADCStartSampleAuto(m_oADCSetThreadStruct* pADCSetThread)
{
	OnADCCmdAuto(pADCSetThread, pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleOptNb);
}
// ADCֹͣ�ɼ�����
MatrixServerDll_API void OnADCStopSampleAuto(m_oADCSetThreadStruct* pADCSetThread)
{
	OnADCCmdAuto(pADCSetThread, pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleOptNb);
}
// ��·������ADC�������ñ�־λ
MatrixServerDll_API void OnResetADCSetLableByRout(m_oRoutStruct* pRout, int iOpt, m_oConstVarStruct* pConstVar)
{
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	if (pRout->m_pTail == NULL)
	{
		return;
	}
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pConstVar);
		if (pInstrumentNext->m_iInstrumentType == pConstVar->m_iInstrumentTypeFDU)
		{
			if (iOpt == pConstVar->m_iADCSetOptNb)
			{
				pInstrumentNext->m_bADCSet = false;
			}
			else if (iOpt == pConstVar->m_iADCStartSampleOptNb)
			{
				pInstrumentNext->m_bADCStartSample = false;
			}
			else if (iOpt == pConstVar->m_iADCStopSampleOptNb)
			{
				pInstrumentNext->m_bADCStopSample = false;
			}
		}
		pInstrument = pInstrumentNext;
	} while (pInstrumentNext != pRout->m_pTail);

}
// ����ADC�������ñ�־λ
MatrixServerDll_API void OnResetADCSetLable(m_oRoutListStruct* pRoutList, int iOpt, m_oConstVarStruct* pConstVar)
{
	if (pRoutList == NULL)
	{
		return;
	}
	EnterCriticalSection(&pRoutList->m_oSecRoutList);
	// ����·�ɵ�ַ������
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	for (iter = pRoutList->m_oRoutMap.begin(); iter != pRoutList->m_oRoutMap.end(); iter++)
	{
		// ��·���������еĴ��߷���·�ɼ��뵽ADC����������������
		if (iter->second->m_bRoutLaux == false)
		{
			OnResetADCSetLableByRout(iter->second, iOpt, pConstVar);
		}
	}
	LeaveCriticalSection(&pRoutList->m_oSecRoutList);
}
// ADC��������
MatrixServerDll_API void OnADCSet(m_oEnvironmentStruct* pEnv)
{
	// ����ADC�������óɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pRoutList, pEnv->m_pConstVar->m_iADCSetOptNb, pEnv->m_pConstVar);
}

// ADC��ʼ�ɼ�����
MatrixServerDll_API void OnADCStartSample(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pADCSetThread->m_bADCStartSample = true;
	pEnv->m_pADCSetThread->m_bADCStopSample = false;
	pEnv->m_pTimeDelayThread->m_bADCStartSample = true;
	// ����ADC��ʼ�ɼ�����ɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pRoutList, pEnv->m_pConstVar->m_iADCStartSampleOptNb, pEnv->m_pConstVar);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnADCStartSample", "��ʼADC���ݲɼ�");
}
// ADCֹͣ�ɼ�����
MatrixServerDll_API void OnADCStopSample(m_oEnvironmentStruct* pEnv)
{
	pEnv->m_pADCSetThread->m_bADCStartSample = false;
	pEnv->m_pADCSetThread->m_bADCStopSample = true;
	pEnv->m_pTimeDelayThread->m_bADCStartSample = false;
	// ����ADCֹͣ�ɼ�����ɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pRoutList, pEnv->m_pConstVar->m_iADCStopSampleOptNb, pEnv->m_pConstVar);
	pEnv->m_pTimeDelayThread->m_uiCounter = 0;
	// ���β��ʱ�̲�ѯ֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTailTimeFrame->m_oTailTimeFrameSocket, pEnv->m_pConstVar);
	// ���ʱͳ����Ӧ��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTimeDelayFrame->m_oTimeDelayFrameSocket, pEnv->m_pConstVar);
	// ʱͳ�����߳̿�ʼ����
	pEnv->m_pTimeDelayThread->m_pThread->m_bWork = true;
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnADCStopSample", "ֹͣADC���ݲɼ�");
}

// ���ӹ���·�ɼ�����
MatrixServerDll_API void MonitorRoutAndInstrument(m_oMonitorRoutThreadStruct* pMonitorRoutThread)
{
	if (pMonitorRoutThread == NULL)
	{
		return;
	}
	// �õ���ǰϵͳʱ��
	ULONGLONG ullTimeNow = 0;
	ullTimeNow = GetTickCount64();
	// hash_map������
	hash_map<unsigned int, m_oRoutStruct*>::iterator  iter;
	CString str = _T("");
	// ɾ������������������·�ɼ���·��ɾ��������
	for(iter = pMonitorRoutThread->m_pRoutList->m_oRoutMap.begin(); iter != pMonitorRoutThread->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		if ((ullTimeNow > (iter->second->m_ullRoutTime + pMonitorRoutThread->m_pThread->m_pConstVar->m_iMonitorRoutStableTime))
			&& (iter->second->m_pTail != NULL))
		{
			str.Format(_T("·��IP = 0x%x��·��ʱ����ڣ�ɾ����·�ɷ����ϵ�����"), iter->second->m_uiRoutIP);
			AddMsgToLogOutPutList(pMonitorRoutThread->m_pThread->m_pLogOutPut, "ProcMonitorRout", ConvertCStrToStr(str));
			// ���·��β����ΪLCI�����Ҫɾ������LCI����
			if (iter->second->m_pTail->m_iInstrumentType == pMonitorRoutThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			{
				// ����һ������
				FreeInstrumentFromMap(iter->second->m_pHead, pMonitorRoutThread->m_pInstrumentList, 
					pMonitorRoutThread->m_pRoutList, pMonitorRoutThread->m_pThread->m_pConstVar);
				iter->second->m_uiInstrumentNum = 0;
			}
			else
			{
				DeleteInstrumentAlongRout(iter->second->m_pHead, iter->second, pMonitorRoutThread->m_pInstrumentList, 
					pMonitorRoutThread->m_pRoutList, pMonitorRoutThread->m_pThread->m_pConstVar);
			}
		}
	}
	// ɾ��·��ɾ���������е�����
	while(1)
	{
		if (pMonitorRoutThread->m_pRoutList->m_oRoutDeleteMap.empty() == true)
		{
			break;
		}
		iter = pMonitorRoutThread->m_pRoutList->m_oRoutDeleteMap.begin();
		DeleteInstrumentAlongRout(iter->second->m_pHead, iter->second, pMonitorRoutThread->m_pInstrumentList, 
			pMonitorRoutThread->m_pRoutList, pMonitorRoutThread->m_pThread->m_pConstVar);
		// ·�����������·��
		DeleteRout(iter->first, &pMonitorRoutThread->m_pRoutList->m_oRoutMap);
		str.Format(_T("����·��IP = 0x%x�Ĺ���·��"), iter->first);
		AddMsgToLogOutPutList(pMonitorRoutThread->m_pThread->m_pLogOutPut, "ProcMonitorRout", ConvertCStrToStr(str));
		// ������·�ɻ��յ�����·�ɶ���
		AddFreeRout(iter->second, pMonitorRoutThread->m_pRoutList);
		// ·��ɾ�����������·��
		DeleteRout(iter->first, &pMonitorRoutThread->m_pRoutList->m_oRoutDeleteMap);
		// ADC�����������������·��
		DeleteRout(iter->first, &pMonitorRoutThread->m_pRoutList->m_oADCSetRoutMap);
	}
}
// ���ʱͳ����Ӧ���Ƿ������ȫ
MatrixServerDll_API bool CheckTimeDelayReturnByRout(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread, bool bSample)
{
	if (pTimeDelayThread == NULL)
	{
		return false;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTimeDelayReturnByRout", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	if (pRout->m_pTail == NULL)
	{
		return true;
	}
	// LCI
	if (pRout->m_pTail == pRout->m_pHead)
	{
		return true;
	}
	m_oInstrumentStruct* pInstrumentNext = NULL;
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pTimeDelayThread->m_pThread->m_pConstVar);
		pInstrument = pInstrumentNext;
		if (bSample == true)
		{
			if (pInstrumentNext->m_iTimeSetCount == 0)
			{
				str.Format(_T("���ݲ��������У�·��IP = 0x%x��������û��ȫ��ʵ��ʱͳ"), pRout->m_uiRoutIP);
				AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTimeDelayReturnByRout", ConvertCStrToStr(str), WarningType);
				return false;
			}
		}
		else
		{
			/** ʱͳ�����Ƿ�ɹ�*/
			if (pInstrumentNext->m_bTimeSetOK == false)
			{
				str.Format(_T("·��IP = 0x%x��������ʱͳ����Ӧ����ղ���ȫ"), pRout->m_uiRoutIP);
				AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTimeDelayReturnByRout", ConvertCStrToStr(str));
				return false;
			}
		}
	} while (pInstrumentNext != pRout->m_pTail);
	if (bSample == false)
	{
		str.Format(_T("·��IP = 0x%x��������ʱͳ����Ӧ�������ȫ"), pRout->m_uiRoutIP);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTimeDelayReturnByRout", ConvertCStrToStr(str));
	}
	return true;
}
// ��������Ƿ������ʱͳ
MatrixServerDll_API bool CheckTimeDelayReturn(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return false;
	}
	// hash_map������
	hash_map<unsigned int, m_oRoutStruct*>::iterator  iter;
	for(iter = pTimeDelayThread->m_pRoutList->m_oRoutMap.begin(); iter != pTimeDelayThread->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		if (false == CheckTimeDelayReturnByRout(iter->second, pTimeDelayThread, true))
		{
			return false;
		}
	}
	return true;
}
// ����ʱͳ
MatrixServerDll_API void MonitorTimeDelay(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// �õ���ǰϵͳʱ��
	ULONGLONG ullTimeNow = 0;
	ullTimeNow = GetTickCount64();
	// �ж�ϵͳ�ȶ�
	if (ullTimeNow > (pTimeDelayThread->m_pInstrumentList->m_ullLineChangeTime 
		+ pTimeDelayThread->m_pThread->m_pConstVar->m_iLineSysStableTime))
	{
		// ����״̬�ɲ��ȶ���Ϊ�ȶ�
		if (pTimeDelayThread->m_pInstrumentList->m_bLineStableChange == false)
		{
			pTimeDelayThread->m_pInstrumentList->m_bLineStableChange = true;
			// ����ʱͳ�������
			GenTimeDelayTaskQueue(pTimeDelayThread->m_pRoutList, pTimeDelayThread->m_pThread->m_pConstVar);
			pTimeDelayThread->m_uiCounter = 0;
			// ���β��ʱ�̲�ѯ֡���ջ�����
			OnClearSocketRcvBuf(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket, 
				pTimeDelayThread->m_pThread->m_pConstVar);
			// ���ʱͳ����Ӧ��֡���ջ�����
			OnClearSocketRcvBuf(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket, 
				pTimeDelayThread->m_pThread->m_pConstVar);
			// ʱͳ�����߳̿�ʼ����
			pTimeDelayThread->m_pThread->m_bWork = true;
		}
		else
		{
			// �ɼ������У���������������ʱͳ��ֹͣʱͳ�߳�
			if (pTimeDelayThread->m_bADCStartSample == true)
			{
				if (true == CheckTimeDelayReturn(pTimeDelayThread))
				{
					// ʱͳ�����߳�ֹͣ����
					pTimeDelayThread->m_pThread->m_bWork = false;
				}
			}
		}
	} 
	else
	{
		// ʱͳ�����߳�ֹͣ����
		pTimeDelayThread->m_pThread->m_bWork = false;
		// ����״̬Ϊ���ȶ�
		pTimeDelayThread->m_pInstrumentList->m_bLineStableChange = false;
	}
}
// ����������ADC��������
MatrixServerDll_API void MonitorADCSet(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	// �õ���ǰϵͳʱ��
	ULONGLONG ullTimeNow = 0;
	ullTimeNow = GetTickCount64();
	// �ж�ϵͳ�ȶ�
	if (ullTimeNow > (pADCSetThread->m_pInstrumentList->m_ullLineChangeTime 
		+ pADCSetThread->m_pThread->m_pConstVar->m_iLineSysStableTime))
	{
		// �Զ�����δ��ɵ�ADC��������
		if (pADCSetThread->m_uiADCSetOperationNb == 0)
		{
			OnADCSetAuto(pADCSetThread);
		}
		// �Զ�����δ��ɵĿ�ʼADC���ݲɼ�
		if (pADCSetThread->m_uiADCSetOperationNb == 0)
		{
			OnADCStartSampleAuto(pADCSetThread);
		}
		// �Զ�����δ��ɵ�ֹͣADC���ݲɼ�
		if (pADCSetThread->m_uiADCSetOperationNb == 0)
		{
			OnADCStopSampleAuto(pADCSetThread);
		}
	}
}
// ����·�ɼ���
MatrixServerDll_API void ProcMonitorRout(m_oMonitorRoutThreadStruct* pMonitorRoutThread)
{
	if (pMonitorRoutThread == NULL)
	{
		return;
	}
	// ���ӹ���·�ɼ�����
	MonitorRoutAndInstrument(pMonitorRoutThread);
	// ϵͳ�ȶ��Ҳ�����ADC���ݲɼ�ʱ����ʱͳ
	MonitorTimeDelay(pMonitorRoutThread->m_pTimeDelayThread);
	// ϵͳ�ȶ������������ADC��������
	MonitorADCSet(pMonitorRoutThread->m_pADCSetThread);
}
// �̺߳���
DWORD WINAPI RunMonitorRoutThread(m_oMonitorRoutThreadStruct* pMonitorRoutThread)
{
	if (pMonitorRoutThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pMonitorRoutThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pMonitorRoutThread->m_pThread->m_bWork == true)
		{
			EnterCriticalSection(&pMonitorRoutThread->m_pInstrumentList->m_oSecInstrumentList);
			EnterCriticalSection(&pMonitorRoutThread->m_pRoutList->m_oSecRoutList);
			// ����·�ɼ���
			ProcMonitorRout(pMonitorRoutThread);
			LeaveCriticalSection(&pMonitorRoutThread->m_pRoutList->m_oSecRoutList);
			LeaveCriticalSection(&pMonitorRoutThread->m_pInstrumentList->m_oSecInstrumentList);
		}
		if (pMonitorRoutThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitMonitorRoutThread(pMonitorRoutThread);
	}
	::SetEvent(pMonitorRoutThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ��·�ɼ����߳�
MatrixServerDll_API bool OnInitMonitorRoutThread(m_oMonitorRoutThreadStruct* pMonitorRoutThread)
{
	if (pMonitorRoutThread == NULL)
	{
		return false;
	}
	pMonitorRoutThread->m_pThread->m_bClose = false;
	pMonitorRoutThread->m_pThread->m_bWork = false;
	pMonitorRoutThread->m_pThread->m_hThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if (pMonitorRoutThread->m_pThread->m_hThreadClose == NULL)
	{
		AddMsgToLogOutPutList(pMonitorRoutThread->m_pThread->m_pLogOutPut, "OnInitMonitorRoutThread",
			"pMonitorRoutThread->m_pThread->m_hThreadClose", ErrorType, IDS_ERR_CREATE_EVENT);
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AddMsgToLogOutPutList(pMonitorRoutThread->m_pThread->m_pLogOutPut, "OnInitMonitorRoutThread", 
			"pMonitorRoutThread->m_pThread->m_hThreadClose", ErrorType, ERROR_ALREADY_EXISTS);
	}
	::ResetEvent(pMonitorRoutThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pMonitorRoutThread->m_pThread->m_hThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunMonitorRoutThread,
		pMonitorRoutThread, 
		0, 
		&pMonitorRoutThread->m_pThread->m_dwThreadID);
	if (pMonitorRoutThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pMonitorRoutThread->m_pThread->m_pLogOutPut, "OnInitMonitorRoutThread", 
			"pMonitorRoutThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pMonitorRoutThread->m_pThread->m_pLogOutPut, "OnInitMonitorRoutThread", "·�ɼ����̴߳����ɹ�");
	return true;
}
// �ر�·�ɼ����߳�
MatrixServerDll_API bool OnCloseMonitorRoutThread(m_oMonitorRoutThreadStruct* pMonitorRoutThread)
{
	if (pMonitorRoutThread == NULL)
	{
		return false;
	}
	int iResult = WaitForSingleObject(pMonitorRoutThread->m_pThread->m_hThreadClose, 
		pMonitorRoutThread->m_pThread->m_pConstVar->m_iCloseThreadSleepTimes
		* pMonitorRoutThread->m_pThread->m_pConstVar->m_iOneSleepTime);
	if (iResult != WAIT_OBJECT_0)
	{
		::TerminateThread(pMonitorRoutThread->m_pThread->m_hThread, 0);
		AddMsgToLogOutPutList(pMonitorRoutThread->m_pThread->m_pLogOutPut, "OnCloseMonitorRoutThread", 
			"·�ɼ����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pMonitorRoutThread->m_pThread->m_pLogOutPut, "OnCloseMonitorRoutThread", "·�ɼ����̳߳ɹ��ر�");
	return true;
}
// �ͷ�·�ɼ����߳�
MatrixServerDll_API void OnFreeMonitorRoutThread(m_oMonitorRoutThreadStruct* pMonitorRoutThread)
{
	if (pMonitorRoutThread == NULL)
	{
		return;
	}
	if (pMonitorRoutThread->m_pThread != NULL)
	{
		delete pMonitorRoutThread->m_pThread;
	}
	delete pMonitorRoutThread;
}
// ����ʱͳ�߳�
MatrixServerDll_API m_oTimeDelayThreadStruct* OnCreateTimeDelayThread(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oTimeDelayThreadStruct* pTimeDelayThread = NULL;
	pTimeDelayThread = new m_oTimeDelayThreadStruct;
	pTimeDelayThread->m_pThread = new m_oThreadStruct;
	pTimeDelayThread->m_pThread->m_pLogOutPut = pLogOutPut;
	pTimeDelayThread->m_pThread->m_hThread = INVALID_HANDLE_VALUE;
	pTimeDelayThread->m_pThread->m_hThreadClose = INVALID_HANDLE_VALUE;
	pTimeDelayThread->m_pThread->m_dwThreadID = 0;
	pTimeDelayThread->m_pLogOutPutTimeDelay = NULL;
	return pTimeDelayThread;
}
// �̵߳ȴ�����
MatrixServerDll_API void WaitTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pTimeDelayThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pTimeDelayThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pTimeDelayThread->m_pThread->m_pConstVar->m_iTimeDelaySleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// β��ʱ�̲�ѯ׼������
MatrixServerDll_API void PrepareTailTimeFrame(m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	if (pRout == NULL)
	{
		return;
	}
	if (pConstVar == NULL)
	{
		return;
	}

	m_oInstrumentStruct* pInstrumentNext = NULL;
	m_oInstrumentStruct* pInstrument = NULL;
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pConstVar);
		pInstrument = pInstrumentNext;
		// 		/** β��ʱ�̲�ѯ����*/
		// 		pInstrumentNext->m_iTailTimeQueryCount++;
		/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
		pInstrumentNext->m_bTailTimeQueryOK = false;
	} while (pInstrumentNext != pRout->m_pTail);
}
// ����β��ʱ�̲�ѯ
MatrixServerDll_API void ProcTailTimeFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ProcTailTimeFrame", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	CString str = _T("");
	// ׼������
	PrepareTailTimeFrame(pRout, pTimeDelayThread->m_pThread->m_pConstVar);
	// ��IP��ѯ·��ͷ������β��ʱ��
	MakeInstrumentTailTimeQueryFramebyIP(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar, pRout->m_pHead->m_uiIP);
	SendInstrumentTailTimeQueryFrame(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar);
	str.Format(_T("������IP��ַ = 0x%x ����������β��ʱ�̲�ѯ֡"), pRout->m_pHead->m_uiIP);
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", ConvertCStrToStr(str));
	pTimeDelayThread->m_uiTailTimeQueryNum++;
	// �㲥��ѯ·��������β��ʱ��
	MakeInstrumentTailTimeQueryFramebyBroadCast(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar, pRout->m_pTail->m_uiBroadCastPort);
	SendInstrumentTailTimeQueryFrame(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar);
	str.Format(_T("��㲥�˿� = 0x%x �������㲥����β��ʱ�̲�ѯ֡"), pRout->m_pTail->m_uiBroadCastPort);
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", ConvertCStrToStr(str));
	pTimeDelayThread->m_uiTailTimeQueryNum += pRout->m_uiInstrumentNum;
}
// ������β��ʱ�̲�ѯӦ��֡
MatrixServerDll_API void ProcTailTimeReturnFrameOne(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	CString strOutPut = _T("");
	// �ж�����IP�Ƿ���SN��������
	if (TRUE == IfIndexExistInMap(pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_uiSrcIP,
		&pTimeDelayThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_uiSrcIP,
			&pTimeDelayThread->m_pInstrumentList->m_oIPInstrumentMap);
		// @@@@@@@�ݲ��ж�β��ʱ�̹��ڵ����
		// ���յ�β��ʱ�̲�ѯӦ���־λ��Ϊtrue
		pInstrument->m_bTailTimeQueryOK = true;
		str.Format(_T("���յ�IP��ַ = 0x%x ������β��ʱ�̲�ѯӦ��֡,	"), pInstrument->m_uiIP);
		strOutPut += str;
		// �����������Ϊ����վ����LCI
		if ((pInstrument->m_iInstrumentType == pTimeDelayThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pTimeDelayThread->m_pThread->m_pConstVar->m_iInstrumentTypeLAUX))
		{
			// ���Ϊ�����߷���·��
			if (pRout->m_bRoutLaux == true)
			{
				pInstrument->m_usCrossTopReceiveTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLAUXLineA;
				pInstrument->m_usCrossDownReceiveTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLAUXLineB;
				str.Format(_T("����վ������Aβ������ʱ�� = 0x%x������վ������Bβ������ʱ�� = 0x%x,	"), 
					pInstrument->m_usCrossTopReceiveTime, pInstrument->m_usCrossDownReceiveTime);
				strOutPut += str;
			}
			// ���߷���
			else
			{
				pInstrument->m_usLineLeftReceiveTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLineA;
				pInstrument->m_usLineRightReceiveTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLineB;
				str.Format(_T("����վ����Aβ������ʱ�� = 0x%x������վ����Bβ������ʱ�� = 0x%x,	"), 
					pInstrument->m_usLineLeftReceiveTime, pInstrument->m_usLineRightReceiveTime);
				strOutPut += str;
			}
		}
		else
		{
			// �ɼ�վ���Դվβ������ʱ��
			pInstrument->m_usReceiveTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usTailRecTime;
			str.Format(_T("�ɼ�վβ������ʱ�� = 0x%x,	"), pInstrument->m_usReceiveTime);
			strOutPut += str;
		}
		// β������ʱ��
		pInstrument->m_usSendTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usTailSndTime;
		str.Format(_T("β������ʱ�� = 0x%x"), pInstrument->m_usSendTime);
		strOutPut += str;
		AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", ConvertCStrToStr(strOutPut));
	}
	else
	{
		str.Format(_T("���յ�IP��ַ = 0x%x ������β��ʱ�̲�ѯӦ��֡"), pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_uiSrcIP);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ProcTailTimeReturnFrameOne", ConvertCStrToStr(str),
			ErrorType, IDS_ERR_IPMAP_NOTEXIT);
	}
}
// ����β��ʱ�̲�ѯӦ��
MatrixServerDll_API void ProcTailTimeReturnFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket,
		pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTimeDelayThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket,
				pTimeDelayThread->m_pTailTimeFrame->m_pcRcvFrameData, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTimeDelayThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentTailTimeReturnFrame(pTimeDelayThread->m_pTailTimeFrame, 
					pTimeDelayThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ParseInstrumentTailTimeReturnFrame", 
						"", ErrorType, IDS_ERR_PARSE_HEADFRAME);
				}
				else
				{
					// ������β��ʱ�̲�ѯӦ��֡
					ProcTailTimeReturnFrameOne(pRout, pTimeDelayThread);
					pTimeDelayThread->m_uiTailTimeReturnNum++;
				}	
			}		
		}		
	}
}
// ���β��ʱ�̲�ѯ����Ƿ������ȫ
MatrixServerDll_API bool CheckTailTimeReturn(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return false;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTailTimeReturn", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	m_oInstrumentStruct* pInstrumentNext = NULL;
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pTimeDelayThread->m_pThread->m_pConstVar);
		pInstrument = pInstrumentNext;
		/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
		if (pInstrumentNext->m_bTailTimeQueryOK == false)
		{
			str.Format(_T("·��IP = 0x%x��������β��ʱ�̲�ѯ���ղ���ȫ"), pRout->m_uiRoutIP);
			AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTailTimeReturn", ConvertCStrToStr(str), WarningType);
			return false;
		}
	} while (pInstrumentNext != pRout->m_pTail);
	str.Format(_T("·��IP = 0x%x��������β��ʱ�̲�ѯ������ȫ"), pRout->m_uiRoutIP);
	AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTailTimeReturn", ConvertCStrToStr(str));
	return true;
}
// ����ʱͳ����
MatrixServerDll_API void ProcTimeDelayFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ProcTimeDelayFrame", "pRout", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	// ��ʱ����
	int itmp1 = 0;
	int itmp2 = 0;
	CString str = _T("");
	CString strOutPut = _T("");
	pInstrument = pRout->m_pHead;

	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pTimeDelayThread->m_pThread->m_pConstVar);
		// ��������ΪLCI�򽻲�վ
		if ((pInstrument->m_iInstrumentType == pTimeDelayThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pTimeDelayThread->m_pThread->m_pConstVar->m_iInstrumentTypeLAUX))
		{
			// ���·�ɷ���Ϊ�Ϸ�
			if (pRout->m_iRoutDirection == pTimeDelayThread->m_pThread->m_pConstVar->m_iDirectionTop)
			{
				itmp1 = pInstrument->m_usCrossTopReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ�·�
			else if (pRout->m_iRoutDirection == pTimeDelayThread->m_pThread->m_pConstVar->m_iDirectionDown)
			{
				itmp1 = pInstrument->m_usCrossDownReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ��
			else if (pRout->m_iRoutDirection == pTimeDelayThread->m_pThread->m_pConstVar->m_iDirectionLeft)
			{
				itmp1 = pInstrument->m_usLineLeftReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ�ҷ�
			else if (pRout->m_iRoutDirection == pTimeDelayThread->m_pThread->m_pConstVar->m_iDirectionRight)
			{
				itmp1 = pInstrument->m_usLineRightReceiveTime - pInstrumentNext->m_usSendTime;
			}
		}
		else
		{
			itmp1 = pInstrument->m_usReceiveTime - pInstrumentNext->m_usSendTime;
		}
		if (itmp1 < 0)
		{
			itmp1 += 0x3fff;
		}
		str.Format(_T("IP��ַ = 0x%x ��������β��ʱ�̲�ֵΪ %d,	"), pInstrumentNext->m_uiIP, itmp1);
		strOutPut = str;
		itmp1 = itmp1 / 2;
		itmp2 += itmp1;
		// ʱ��������λ
		pInstrumentNext->m_uiTimeLow = itmp2 & 0x3fff;
		// ʱ��������λ
		pInstrumentNext->m_uiTimeHigh = (pInstrumentNext->m_uiNetTime - pInstrumentNext->m_uiSystemTime) & 0xffffffff;
		// �����ݲɼ��ڼ�ֻ���δʱͳ����������ʱͳ����
		if (pTimeDelayThread->m_bADCStartSample == true)
		{
			if (pInstrumentNext->m_iTimeSetCount == 0)
			{
				// ���ɲ�����ʱͳ����֡
				MakeInstrumentDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, pTimeDelayThread->m_pThread->m_pConstVar, pInstrumentNext);
				SendInstrumentDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, pTimeDelayThread->m_pThread->m_pConstVar);
				pTimeDelayThread->m_uiTimeDelaySetNum++;
				str.Format(_T("����ʱͳ����֡ʱͳ������λΪ 0x%x��ʱͳ������λΪ 0x%x"), 
					pInstrumentNext->m_uiTimeHigh, pInstrumentNext->m_uiTimeLow);
				strOutPut += str;
				AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", ConvertCStrToStr(strOutPut));
			}
		}
		else
		{
			// ���ɲ�����ʱͳ����֡
			MakeInstrumentDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, pTimeDelayThread->m_pThread->m_pConstVar, pInstrumentNext);
			SendInstrumentDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, pTimeDelayThread->m_pThread->m_pConstVar);
			pTimeDelayThread->m_uiTimeDelaySetNum++;
			str.Format(_T("����ʱͳ����֡ʱͳ������λΪ 0x%x��ʱͳ������λΪ 0x%x"), 
				pInstrumentNext->m_uiTimeHigh, pInstrumentNext->m_uiTimeLow);
			strOutPut += str;
			AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", ConvertCStrToStr(strOutPut));
		}
		pInstrument = pInstrumentNext;
	} while (pInstrumentNext != pRout->m_pTail);
}
// ������ʱͳ����Ӧ��
MatrixServerDll_API void ProcTimeDelayReturnFrameOne(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	// �ж�����IP�Ƿ���SN��������
	if (TRUE == IfIndexExistInMap(pTimeDelayThread->m_pTimeDelayFrame->m_pCommandStructReturn->m_uiSrcIP,
		&pTimeDelayThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(pTimeDelayThread->m_pTimeDelayFrame->m_pCommandStructReturn->m_uiSrcIP,
			&pTimeDelayThread->m_pInstrumentList->m_oIPInstrumentMap);
		// ���յ�ʱͳ����Ӧ���־λ
		pInstrument->m_bTimeSetOK = true;
		pInstrument->m_iTimeSetCount++;
		str.Format(_T("���յ�IP��ַ = 0x%x ������ʱͳ����Ӧ��֡"), pInstrument->m_uiIP);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", ConvertCStrToStr(str));
	}
	else
	{
		str.Format(_T("���յ�IP��ַ = 0x%x ������ʱͳ����Ӧ��֡"), pTimeDelayThread->m_pTimeDelayFrame->m_pCommandStructReturn->m_uiSrcIP);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ProcTimeDelayReturnFrameOne", ConvertCStrToStr(str),
			ErrorType, IDS_ERR_IPMAP_NOTEXIT);
	}
}
// ����ʱͳ����Ӧ��
MatrixServerDll_API void ProcTimeDelayReturnFrame(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket,
		pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTimeDelayThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket,
				pTimeDelayThread->m_pTimeDelayFrame->m_pcRcvFrameData, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTimeDelayThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentTimeDelayReturnFrame(pTimeDelayThread->m_pTimeDelayFrame, 
					pTimeDelayThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ParseInstrumentTimeDelayReturnFrame", 
						"", ErrorType, IDS_ERR_PARSE_HEADFRAME);
				}
				else
				{
					// ������ʱͳ����Ӧ��֡
					ProcTimeDelayReturnFrameOne(pTimeDelayThread);
					pTimeDelayThread->m_uiTimeDelayReturnNum++;
				}	
			}		
		}		
	}
}
// �̺߳���
DWORD WINAPI RunTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return 1;
	}
	m_oRoutStruct* pRout = NULL;
	CString str = _T("");
	unsigned int uiProcRoutIP = 0;
	while(true)
	{
		if (pTimeDelayThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pTimeDelayThread->m_pThread->m_bWork == true)
		{
			EnterCriticalSection(&pTimeDelayThread->m_pInstrumentList->m_oSecInstrumentList);
			EnterCriticalSection(&pTimeDelayThread->m_pRoutList->m_oSecRoutList);
			if (pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.size() > 0)
			{
				pTimeDelayThread->m_uiCounter++;
				if (pTimeDelayThread->m_uiCounter == 1)
				{
					// �õ�ʱͳ����ͷ��·��IP��ַ��Ϊ��ǰ�������·��IP
					uiProcRoutIP = *pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.begin();
					// ��ǰ������·��IP��·����������
					if (TRUE == IfIndexExistInRoutMap(uiProcRoutIP, &pTimeDelayThread->m_pRoutList->m_oRoutMap))
					{
						// �õ���ǰ������·��ָ��
						pRout = GetRout(uiProcRoutIP, &pTimeDelayThread->m_pRoutList->m_oRoutMap);
					}
					else
					{
						str.Format(_T("·��IP = 0x%x"), pRout->m_uiRoutIP);
						AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "RunTimeDelayThread", ConvertCStrToStr(str), 
							ErrorType, IDS_ERR_ROUT_NOTEXIT);
					}
					// ����β��ʱ�̲�ѯ
					ProcTailTimeFrame(pRout, pTimeDelayThread);
				}
				else if (pTimeDelayThread->m_uiCounter == 5)
				{
					// ����β��ʱ�̲�ѯӦ��
					ProcTailTimeReturnFrame(pRout, pTimeDelayThread);
					// ���β��ʱ�̲�ѯ����Ƿ������ȫ
					if (false == CheckTailTimeReturn(pRout, pTimeDelayThread))
					{
						pTimeDelayThread->m_uiCounter = 0;
					}
					else
					{
						// ����ʱͳ����
						ProcTimeDelayFrame(pRout, pTimeDelayThread);
					}
				}
				else if (pTimeDelayThread->m_uiCounter == 10)
				{
					// ����ʱͳ����Ӧ��
					ProcTimeDelayReturnFrame(pTimeDelayThread);
					// �жϸ�·�ɷ����Ƿ����ʱͳ
					// ���ʱͳ����Ӧ���Ƿ������ȫ
					if (true == CheckTimeDelayReturnByRout(pRout, pTimeDelayThread, false))
					{
						// ʱͳ�����Ƶ�����β
						pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.pop_front();
						pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.push_back(uiProcRoutIP);
					}
				}
				else if (pTimeDelayThread->m_uiCounter == 15)
				{
					pTimeDelayThread->m_uiCounter = 0;
				}
			}
			LeaveCriticalSection(&pTimeDelayThread->m_pRoutList->m_oSecRoutList);
			LeaveCriticalSection(&pTimeDelayThread->m_pInstrumentList->m_oSecInstrumentList);
		}
		if (pTimeDelayThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitTimeDelayThread(pTimeDelayThread);
	}
	::SetEvent(pTimeDelayThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ��ʱͳ�����߳�
MatrixServerDll_API bool OnInitTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return false;
	}
	pTimeDelayThread->m_bADCStartSample = false;
	pTimeDelayThread->m_uiCounter = 0;
	// β����ѯ֡��ѯ����������
	pTimeDelayThread->m_uiTailTimeQueryNum = 0;
	// β����ѯ֡Ӧ�����
	pTimeDelayThread->m_uiTailTimeReturnNum = 0;
	// ʱͳ����֡����
	pTimeDelayThread->m_uiTimeDelaySetNum = 0;
	// ʱͳ����Ӧ��֡����
	pTimeDelayThread->m_uiTimeDelayReturnNum = 0;
	pTimeDelayThread->m_pThread->m_bClose = false;
	pTimeDelayThread->m_pThread->m_bWork = false;
	pTimeDelayThread->m_pThread->m_hThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if (pTimeDelayThread->m_pThread->m_hThreadClose == NULL)
	{
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnInitTimeDelayThread",
			"pTimeDelayThread->m_pThread->m_hThreadClose", ErrorType, IDS_ERR_CREATE_EVENT);
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnInitTimeDelayThread", 
			"pTimeDelayThread->m_pThread->m_hThreadClose", ErrorType, ERROR_ALREADY_EXISTS);
	}
	::ResetEvent(pTimeDelayThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pTimeDelayThread->m_pThread->m_hThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunTimeDelayThread,
		pTimeDelayThread, 
		0, 
		&pTimeDelayThread->m_pThread->m_dwThreadID);
	if (pTimeDelayThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnInitTimeDelayThread", 
			"pTimeDelayThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnInitTimeDelayThread", "ʱͳ�����̴߳����ɹ�");
	return true;
}
// �ر�ʱͳ�����߳�
MatrixServerDll_API bool OnCloseTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return false;
	}
	int iResult = WaitForSingleObject(pTimeDelayThread->m_pThread->m_hThreadClose, 
		pTimeDelayThread->m_pThread->m_pConstVar->m_iCloseThreadSleepTimes
		* pTimeDelayThread->m_pThread->m_pConstVar->m_iOneSleepTime);
	if (iResult != WAIT_OBJECT_0)
	{
		::TerminateThread(pTimeDelayThread->m_pThread->m_hThread, 0);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnCloseTimeDelayThread", 
			"ʱͳ�����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnCloseTimeDelayThread", "ʱͳ�����̳߳ɹ��ر�");
	return true;
}
// �ͷ�ʱͳ�����߳�
MatrixServerDll_API void OnFreeTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	if (pTimeDelayThread->m_pThread != NULL)
	{
		delete pTimeDelayThread->m_pThread;
	}
	delete pTimeDelayThread;
}
// ����ADC���������߳�
MatrixServerDll_API m_oADCSetThreadStruct* OnCreateADCSetThread(m_oLogOutPutStruct* pLogOutPut = NULL)
{
	m_oADCSetThreadStruct* pADCSetThread = NULL;
	pADCSetThread = new m_oADCSetThreadStruct;
	pADCSetThread->m_pThread = new m_oThreadStruct;
	pADCSetThread->m_pThread->m_pLogOutPut = pLogOutPut;
	pADCSetThread->m_pThread->m_hThread = INVALID_HANDLE_VALUE;
	pADCSetThread->m_pThread->m_hThreadClose = INVALID_HANDLE_VALUE;
	pADCSetThread->m_pThread->m_dwThreadID = 0;
	return pADCSetThread;
}
// ����ADC��������֡
MatrixServerDll_API void OnSelectADCSetCmd(m_oADCSetThreadStruct* pADCSetThread, bool bRout, unsigned int uiDstIP)
{
	CString str = _T("");
	unsigned int uiTemp = 0;
	EnterCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	// ��ѯ�����ָ���
	pADCSetThread->m_pADCSetFrame->m_usCommandWordNum = 0;
	// ����·�ɵĹ㲥�˿ڹ㲥����ADC������������֡
	if (bRout == true)
	{
		// Ŀ��IP��ַ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiDstIP = pADCSetThread->m_pThread->m_pConstVar->m_iIPBroadcastAddr;
		// �㲥�˿�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiBroadCastPortSeted = uiDstIP;
		// ��ѯ����������
		// �㲥�˿�
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdBroadCastPortSeted;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		str.Format(_T("��㲥�˿� = 0x%x �������㲥����ADC��������֡��������� = %d"), 
			uiDstIP, pADCSetThread->m_uiADCSetOperationNb);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", ConvertCStrToStr(str));
	}
	// ����IP��ַ����ADC������������֡
	else
	{
		// Ŀ��IP��ַ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiDstIP = uiDstIP;
		str.Format(_T("��IP��ַ = 0x%x ����������ADC��������֡��������� = %d"), 
			uiDstIP, pADCSetThread->m_uiADCSetOperationNb);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", ConvertCStrToStr(str));
	}
	// 1~11ΪADC�����������12~18ΪADC��ʼ�������19~22ΪADCֹͣ��������
	switch (pADCSetThread->m_uiADCSetOperationNb)
	{
	case 1:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TB��λ�ر�TB����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow = 0;
		// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBCtrl = 0;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdTbLow;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 2:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC�������Ҳ�����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCSetSine;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCSetSineSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 3:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 4:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB��Դ��λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCOpenTBPowerLow;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCOpenTBPowerLowSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 5:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB��Դ��λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCOpenTBPowerHigh;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCOpenTBPowerHighSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 6:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB���ص�λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCOpenSwitchTBLow;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCOpenSwitchTBLowSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 7:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB���ظ�λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCOpenSwitchTBHigh;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCOpenSwitchTBHighSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 8:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 9:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����д�Ĵ���
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCRegisterWrite;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCRegisterWriteSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 10:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ö��Ĵ���
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCRegisterRead;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCRegisterReadSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 11:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC�������ݷ��ض˿�
		// �Զ�AD���ص�ַ
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCDataReturnAddr;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		// �Զ����ݷ��ض˿ں�����
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCDataReturnPort;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		// �˿ڵ������޺�����
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCDataReturnPortLimit;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 12:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCTBSwitchOpen;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCTBSwitchOpenSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 13:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 14:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TB��λ�ر�TB����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow = 0;
		// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBCtrl = 0;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdTbLow;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 15:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����ADC���ݲ����ʵȲ���
		// @@@��Ҫ�������ò����ʵȲ�������ѡΪ1K������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCSampleSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 16:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����������������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCReadContinuous;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCReadContinuousSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 17:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendQueryCmd;
		// ��ѯ�����ĵ�ǰϵͳʱ��
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdLocalSysTime;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 18:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TBʱ���λ
		if (pADCSetThread->m_uiLocalSysTime < pADCSetThread->m_uiTBTimeOld)
		{
			uiTemp = (0xffffffff - pADCSetThread->m_uiTBTimeOld + pADCSetThread->m_uiLocalSysTime) % (72 * 16);
		}
		else
		{
			uiTemp = (pADCSetThread->m_uiLocalSysTime - pADCSetThread->m_uiTBTimeOld) % (72 * 16);
		}
		if (pADCSetThread->m_uiLocalSysTime < uiTemp)
		{
			pADCSetThread->m_uiLocalSysTime = 0xffffffff - uiTemp + pADCSetThread->m_uiLocalSysTime;
		}
		else
		{
			pADCSetThread->m_uiLocalSysTime -= uiTemp;
		}
		pADCSetThread->m_uiTBTimeOld = pADCSetThread->m_uiLocalSysTime;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiTBHigh = 
			pADCSetThread->m_pThread->m_pConstVar->m_uiTBSleepTimeHigh + pADCSetThread->m_uiLocalSysTime;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdTBHigh;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		// ����TBʱ���λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow = pADCSetThread->m_pThread->m_pConstVar->m_usTBSleepTimeLow;
		// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBCtrl = pADCSetThread->m_pThread->m_pConstVar->m_usCmdTBCtrlStartSample
			+ pADCSetThread->m_pThread->m_pConstVar->m_usCmdCtrlCloseLed;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdTbLow;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		str.Format(_T("ADC��ʼ������TBʱ���λ = 0x%x��TBʱ���λ = 0x%x"), 
			pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiTBHigh, 
			pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", ConvertCStrToStr(str));
		break;
	case 19:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 20:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 21:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_pcADCSet = pADCSetThread->m_pThread->m_pConstVar->m_pSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 22:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TB��λ�ر�TB����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow = 0;
		// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBCtrl = 0;
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_byCmdTbLow;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	default:
		break;
	}
	MakeInstrumentFrame(pADCSetThread->m_pADCSetFrame->m_pCommandStructSet, 
		pADCSetThread->m_pThread->m_pConstVar, 
		pADCSetThread->m_pADCSetFrame->m_pcSndFrameData, 
		pADCSetThread->m_pADCSetFrame->m_pcCommandWord, 
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	// ����ADC��������֡
	SendInstrumentADCSetFrame(pADCSetThread->m_pADCSetFrame, pADCSetThread->m_pThread->m_pConstVar);
}
// ����ADC��������֡
MatrixServerDll_API void OnSendADCSetCmd(m_oADCSetThreadStruct* pADCSetThread)
{
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	hash_map<unsigned int, m_oInstrumentStruct*> ::iterator iter2;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	for (iter = pADCSetThread->m_pRoutList->m_oADCSetRoutMap.begin();iter != pADCSetThread->m_pRoutList->m_oADCSetRoutMap.end(); iter++)
	{
		iter->second->m_bADCSetReturn = false;
		// ����ADC��������Ӧ���־λ
		pInstrument = iter->second->m_pHead;
		do 
		{
			pInstrumentNext = GetNextInstrument(iter->second->m_iRoutDirection, pInstrument, pADCSetThread->m_pThread->m_pConstVar);
			pInstrumentNext->m_bADCSetReturn = false;
			pInstrument = pInstrumentNext;
		} while (pInstrument != iter->second->m_pTail);
		if (iter->second->m_bADCSetRout == true)
		{
			// ѡ��ADC������������
			OnSelectADCSetCmd(pADCSetThread, true, iter->second->m_pTail->m_uiBroadCastPort);
			pADCSetThread->m_uiADCSetNum += iter->second->m_uiInstrumentNum;
		}
	}
	for (iter2 = pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.begin();iter2 != pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.end(); iter2++)
	{
		// ����ADC��������Ӧ���־λ
		iter2->second->m_bADCSetReturn = false;
		// ѡ��ADC������������
		OnSelectADCSetCmd(pADCSetThread, false, iter2->second->m_uiIP);
		pADCSetThread->m_uiADCSetNum++;
	}
}
// ����ADC��������Ӧ��֡
MatrixServerDll_API void ProcADCSetReturnFrameOne(m_oADCSetThreadStruct* pADCSetThread)
{
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	if (pADCSetThread == NULL)
	{
		return;
	}
	// �õ�����IP
	uiIPInstrument = pADCSetThread->m_pADCSetFrame->m_pCommandStructReturn->m_uiSrcIP;
	// ��������������
	if (TRUE == IfIndexExistInMap(uiIPInstrument, &pADCSetThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(uiIPInstrument, &pADCSetThread->m_pInstrumentList->m_oIPInstrumentMap);
		pInstrument->m_bADCSetReturn = true;
		if (pADCSetThread->m_uiADCSetOperationNb == 17)
		{
			pADCSetThread->m_uiLocalSysTime = pADCSetThread->m_pADCSetFrame->m_pCommandStructReturn->m_uiSysTime;
			str.Format(_T("IP��ַ = 0x%x����������ʱ��Ϊ = 0x%x"), uiIPInstrument, pADCSetThread->m_uiLocalSysTime);
			AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ProcADCSetReturnFrameOne", ConvertCStrToStr(str));
		}
	}
	else
	{
		str.Format(_T("���յ�IP��ַ = 0x%x��ADC��������Ӧ��"), uiIPInstrument);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ProcADCSetReturnFrameOne", ConvertCStrToStr(str),
			ErrorType, IDS_ERR_IPMAP_NOTEXIT);
	}
}
// ����Ӧ�������ȫ��Ĳ���
MatrixServerDll_API void OnADCSetNextOpt(m_oADCSetThreadStruct* pADCSetThread)
{
	// ִ����һ��ADC����Ͳ�����Ӧ����Ӷ�ʱ��
	pADCSetThread->m_uiADCSetOperationNb++;
	pADCSetThread->m_uiCounter = 0;
	// ���ADC��������
	if (pADCSetThread->m_uiADCSetOperationNb == 12)
	{
		pADCSetThread->m_uiADCSetOperationNb = 0;
		// ADC���������߳�ֹͣ����
		pADCSetThread->m_pThread->m_bWork = false;
		return;
	}
	// ���ADC��ʼ���ݲɼ�
	else if (pADCSetThread->m_uiADCSetOperationNb == 19)
	{
		pADCSetThread->m_uiADCSetOperationNb = 0;
		// ADC���������߳�ֹͣ����
		pADCSetThread->m_pThread->m_bWork = false;
		return;
	}
	// ���ADCֹͣ���ݲɼ�
	else if (pADCSetThread->m_uiADCSetOperationNb == 23)
	{
		pADCSetThread->m_uiADCSetOperationNb = 0;
		// ADC���������߳�ֹͣ����
		pADCSetThread->m_pThread->m_bWork = false;
		return;
	}
}
// �ж�ADC��������Ӧ���Ƿ������ȫ
MatrixServerDll_API bool CheckADCSetReturnFrame(m_oADCSetThreadStruct* pADCSetThread)
{
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	hash_map<unsigned int, m_oInstrumentStruct*> ::iterator iter2;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	bool bADCSetRoutReturn = true;
	bool bReturn = true; 
	for (iter = pADCSetThread->m_pRoutList->m_oADCSetRoutMap.begin();iter != pADCSetThread->m_pRoutList->m_oADCSetRoutMap.end(); iter++)
	{
		if (false == iter->second->m_bADCSetReturn)
		{
			bADCSetRoutReturn = true;
			pInstrument = iter->second->m_pHead;
			do 
			{
				pInstrumentNext = GetNextInstrument(iter->second->m_iRoutDirection, pInstrument, pADCSetThread->m_pThread->m_pConstVar);
				if (pInstrumentNext->m_iInstrumentType == pADCSetThread->m_pThread->m_pConstVar->m_iInstrumentTypeFDU)
				{
					if (false == pInstrumentNext->m_bADCSetReturn)
					{
						// �Ҳ��������������
						// �������������Ѿ��е�·�ɲ��ٹ㲥����ADC��������
						if (FALSE == IfIndexExistInMap(pInstrumentNext->m_uiIP, &pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap))
						{
							AddInstrumentToMap(pInstrumentNext->m_uiIP, pInstrumentNext, &pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
						}
						bReturn = false;
						bADCSetRoutReturn = false;
					}
					else
					{
						if (pADCSetThread->m_uiADCSetOperationNb == 11)
						{
							pInstrumentNext->m_bADCSet = true;
						}
						else if (pADCSetThread->m_uiADCSetOperationNb == 18)
						{
							pInstrumentNext->m_bADCStartSample = true;
						}
						else if (pADCSetThread->m_uiADCSetOperationNb == 22)
						{
							pInstrumentNext->m_bADCStopSample = true;
						}
						// ��������������ҵ���������ɾ��
						DeleteInstrumentFromMap(pInstrumentNext->m_uiIP, &pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
					}
				}
				pInstrument = pInstrumentNext;
			} while (pInstrument != iter->second->m_pTail);
			iter->second->m_bADCSetReturn = bADCSetRoutReturn;
			iter->second->m_bADCSetRout = bADCSetRoutReturn;
		}
	}
	for (iter2 = pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.begin();iter2 != pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.end(); iter2++)
	{
		if (false == iter2->second->m_bADCSetReturn)
		{
			bReturn = false;
			break;
		}
		else
		{
			if (pADCSetThread->m_uiADCSetOperationNb == 11)
			{
				iter2->second->m_bADCSet = true;
			}
			else if (pADCSetThread->m_uiADCSetOperationNb == 18)
			{
				iter2->second->m_bADCStartSample = true;
			}
			else if (pADCSetThread->m_uiADCSetOperationNb == 22)
			{
				iter2->second->m_bADCStopSample = true;
			}
		}
	}
	return bReturn;
}
// ����ADC��������Ӧ��֡
MatrixServerDll_API void ProcADCSetReturnFrame(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	CString str = _T("");
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pADCSetThread->m_pADCSetFrame->m_oADCSetFrameSocket,
		pADCSetThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pADCSetThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pADCSetThread->m_pADCSetFrame->m_oADCSetFrameSocket,
				pADCSetThread->m_pADCSetFrame->m_pcRcvFrameData, 
				pADCSetThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pADCSetThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentADCSetReturnFrame(pADCSetThread->m_pADCSetFrame, 
					pADCSetThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ParseInstrumentADCSetReturnFrame",
						"", ErrorType, IDS_ERR_PARSE_IPSETRETURNFRAME);
				}
				else
				{
					EnterCriticalSection(&pADCSetThread->m_pInstrumentList->m_oSecInstrumentList);
					// ������ADC��������Ӧ��֡
					ProcADCSetReturnFrameOne(pADCSetThread);
					pADCSetThread->m_uiADCSetReturnNum++;
					LeaveCriticalSection(&pADCSetThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
	// �ж�ADC��������Ӧ���Ƿ������ȫ
	if (true == CheckADCSetReturnFrame(pADCSetThread))
	{
		str.Format(_T("ADC������������ %d Ӧ�������ȫ"), pADCSetThread->m_uiADCSetOperationNb);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "CheckADCSetReturnFrame", ConvertCStrToStr(str));
		// ����Ӧ�������ȫ��Ĳ���
		OnADCSetNextOpt(pADCSetThread);
	}
	else
	{
		str.Format(_T("ADC������������ %d Ӧ����ղ���ȫ"), pADCSetThread->m_uiADCSetOperationNb);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "CheckADCSetReturnFrame", ConvertCStrToStr(str), WarningType);
	}
}
// �̵߳ȴ�����
MatrixServerDll_API void WaitADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pADCSetThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pADCSetThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pADCSetThread->m_pThread->m_pConstVar->m_iADCSetSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pADCSetThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pADCSetThread->m_pThread->m_bWork == true)
		{
			if (pADCSetThread->m_uiADCSetOperationNb != 0)
			{
				// ����ADC��������������з��Ͳ�������֡
				pADCSetThread->m_uiCounter++;
				if (pADCSetThread->m_uiCounter == 1)
				{
					OnSendADCSetCmd(pADCSetThread);
				}
				else if (pADCSetThread->m_uiCounter == 2)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (pADCSetThread->m_uiCounter == 3)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (pADCSetThread->m_uiCounter == 4)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (pADCSetThread->m_uiCounter == 5)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else
				{
					pADCSetThread->m_uiCounter = 0;
				}
			}
		}
		if (pADCSetThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitADCSetThread(pADCSetThread);
	}
	::SetEvent(pADCSetThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ��ADC���������߳�
MatrixServerDll_API bool OnInitADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return false;
	}
	pADCSetThread->m_pThread->m_bClose = false;
	pADCSetThread->m_pThread->m_bWork = false;
	pADCSetThread->m_pThread->m_hThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	pADCSetThread->m_uiADCSetOperationNb = 0;
	pADCSetThread->m_bADCStartSample = false;
	pADCSetThread->m_bADCStopSample = false;
	pADCSetThread->m_uiLocalSysTime = 0;
	pADCSetThread->m_uiTBTimeOld = 0;
	pADCSetThread->m_uiADCSetNum = 0;
	pADCSetThread->m_uiADCSetReturnNum = 0;
	if (pADCSetThread->m_pThread->m_hThreadClose == NULL)
	{
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnInitADCSetThread",
			"pADCSetThread->m_pThread->m_hThreadClose", ErrorType, IDS_ERR_CREATE_EVENT);
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnInitADCSetThread", 
			"pADCSetThread->m_pThread->m_hThreadClose", ErrorType, ERROR_ALREADY_EXISTS);
	}
	::ResetEvent(pADCSetThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pADCSetThread->m_pThread->m_hThread = ::CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunADCSetThread,
		pADCSetThread, 
		0, 
		&pADCSetThread->m_pThread->m_dwThreadID);
	if (pADCSetThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnInitADCSetThread", 
			"pADCSetThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnInitADCSetThread", "ADC���������̴߳����ɹ�");
	return true;
}
// �ر�ADC���������߳�
MatrixServerDll_API bool OnCloseADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return false;
	}
	int iResult = WaitForSingleObject(pADCSetThread->m_pThread->m_hThreadClose, 
		pADCSetThread->m_pThread->m_pConstVar->m_iCloseThreadSleepTimes
		* pADCSetThread->m_pThread->m_pConstVar->m_iOneSleepTime);
	if (iResult != WAIT_OBJECT_0)
	{
		::TerminateThread(pADCSetThread->m_pThread->m_hThread, 0);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnCloseADCSetThread", 
			"ADC���������߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnCloseADCSetThread", "ADC���������̳߳ɹ��ر�");
	return true;
}
// �ͷ�ADC���������߳�
MatrixServerDll_API void OnFreeADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	if (pADCSetThread->m_pThread != NULL)
	{
		delete pADCSetThread->m_pThread;
	}
	delete pADCSetThread;
}
// ��ʼ��ʵ��
MatrixServerDll_API void OnInitInstance(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	CString str = _T("");
	CString strPath = _T("");
	SYSTEMTIME  sysTime;
	// ��������������־�ļ���
	CreateDirectory(LogFolderPath, NULL);
	GetLocalTime(&sysTime);
	str.Format(_T("\\%04d��%02d��%02d��_Log"),sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	strPath = LogFolderPath + str;
	CreateDirectory(strPath, NULL);
	str.Format(_T("\\%02dʱ%02d��%02d��_log"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	strPath += str;
	CreateDirectory(strPath, NULL);
	// ����������־����ṹ��
	pEnv->m_pLogOutPutOpt = OnCreateLogOutPut();
	pEnv->m_pLogOutPutOpt->m_csSaveLogFilePath = strPath + SysOptLogFolderPath;
	// ����ʱͳ��־����ṹ��
	pEnv->m_pLogOutPutTimeDelay = OnCreateLogOutPut();
	pEnv->m_pLogOutPutTimeDelay->m_csSaveLogFilePath = strPath + TimeDelayLogFolderPath;
	// ���������ѯ��־����ṹ��
	pEnv->m_pLogOutPutErrorCode = OnCreateLogOutPut();
	pEnv->m_pLogOutPutErrorCode->m_csSaveLogFilePath = strPath + ErrorCodeLogFolderPath;
	// ����ADC����֡ʱ����־����ṹ��
	pEnv->m_pLogOutPutADCFrameTime = OnCreateLogOutPut();
	pEnv->m_pLogOutPutADCFrameTime->m_csSaveLogFilePath = strPath + ADCFrameTimeLogFolderPath;
	// ����������Ϣ�ṹ��
	pEnv->m_pConstVar = OnCreateConstVar(pEnv->m_pLogOutPutOpt);
	// ��������ͨѶ��Ϣ�ṹ��
	pEnv->m_pInstrumentCommInfo = OnCreateInstrumentCommInfo(pEnv->m_pLogOutPutOpt);
	// ��������֡��Ϣ�ṹ��
	pEnv->m_pHeartBeatFrame = OnCreateInstrumentHeartBeat(pEnv->m_pLogOutPutOpt);
	// �����װ�֡��Ϣ�ṹ��
	pEnv->m_pHeadFrame = OnCreateInstrumentHeadFrame(pEnv->m_pLogOutPutOpt);
	// ����IP��ַ����֡��Ϣ�ṹ��
	pEnv->m_pIPSetFrame = OnCreateInstrumentIPSetFrame(pEnv->m_pLogOutPutOpt);
	// ����β��֡��Ϣ�ṹ��
	pEnv->m_pTailFrame = OnCreateInstrumentTailFrame(pEnv->m_pLogOutPutOpt);
	// ����β��ʱ��֡��Ϣ�ṹ��
	pEnv->m_pTailTimeFrame = OnCreateInstrumentTailTimeFrame(pEnv->m_pLogOutPutOpt);
	// ����ʱͳ����֡��Ϣ�ṹ��
	pEnv->m_pTimeDelayFrame = OnCreateInstrumentTimeDelayFrame(pEnv->m_pLogOutPutOpt);
	// ����ADC��������֡��Ϣ�ṹ��
	pEnv->m_pADCSetFrame = OnCreateInstrumentADCSetFrame(pEnv->m_pLogOutPutOpt);
	// �����������нṹ��
	pEnv->m_pInstrumentList = OnCreateInstrumentList(pEnv->m_pLogOutPutOpt);
	// ����·�ɶ��нṹ��
	pEnv->m_pRoutList = OnCreateRoutList(pEnv->m_pLogOutPutOpt);
	// ������־����߳�
	pEnv->m_pLogOutPutThread = OnCreateLogOutPutThread(pEnv->m_pLogOutPutOpt);
	pEnv->m_pLogOutPutThread->m_pLogOutPutTimeDelay = pEnv->m_pLogOutPutTimeDelay;
	pEnv->m_pLogOutPutThread->m_pLogOutPutErrorCode = pEnv->m_pLogOutPutErrorCode;
	pEnv->m_pLogOutPutThread->m_pLogOutPutADCFrameTime = pEnv->m_pLogOutPutADCFrameTime;
	// ���������߳�
	pEnv->m_pHeartBeatThread = OnCreateHeartBeatThread(pEnv->m_pLogOutPutOpt);
	// �����װ������߳�
	pEnv->m_pHeadFrameThread = OnCreateHeadFrameThread(pEnv->m_pLogOutPutOpt);
	// ����IP��ַ�����߳�
	pEnv->m_pIPSetFrameThread = OnCreateIPSetFrameThread(pEnv->m_pLogOutPutOpt);
	// ����β�������߳�
	pEnv->m_pTailFrameThread = OnCreateTailFrameThread(pEnv->m_pLogOutPutOpt);
	// ����·�ɼ����߳�
	pEnv->m_pMonitorRoutThread = OnCreateMonitorRoutThread(pEnv->m_pLogOutPutOpt);
	// ����ʱͳ�߳�
	pEnv->m_pTimeDelayThread = OnCreateTimeDelayThread(pEnv->m_pLogOutPutOpt);
	pEnv->m_pTimeDelayThread->m_pLogOutPutTimeDelay = pEnv->m_pLogOutPutTimeDelay;
	// ����ADC���������߳�
	pEnv->m_pADCSetThread = OnCreateADCSetThread(pEnv->m_pLogOutPutOpt);

	// ��ʼ��������־����ṹ��
	OnInitLogOutPut(pEnv->m_pLogOutPutOpt);
	// ��ʼ��ʱͳ��־����ṹ��
	OnInitLogOutPut(pEnv->m_pLogOutPutTimeDelay);
	// ��ʼ�������ѯ��־����ṹ��
	OnInitLogOutPut(pEnv->m_pLogOutPutErrorCode);
	// ��ʼ��ADC����֡ʱ����־����ṹ��
	OnInitLogOutPut(pEnv->m_pLogOutPutADCFrameTime);
	// ��ʼ��������Ϣ�ṹ��
	OnInitConstVar(pEnv->m_pConstVar);
	// ��ʼ������ͨѶ��Ϣ�ṹ��
	OnInitInstrumentCommInfo(pEnv->m_pInstrumentCommInfo);
	// ��ʼ���׽��ֿ�
	OnInitSocketLib(pEnv->m_pLogOutPutOpt);
	// ��ʼ����־����߳�
	pEnv->m_pLogOutPutThread->m_pThread->m_pConstVar = pEnv->m_pConstVar;
	OnInitLogOutPutThread(pEnv->m_pLogOutPutThread);
	// ��ʼ�������߳�
	pEnv->m_pHeartBeatThread->m_pThread->m_pConstVar = pEnv->m_pConstVar;
	pEnv->m_pHeartBeatThread->m_pHeartBeatFrame = pEnv->m_pHeartBeatFrame;
	OnInitHeartBeatThread(pEnv->m_pHeartBeatThread);
	// ��ʼ���װ������߳�
	pEnv->m_pHeadFrameThread->m_pThread->m_pConstVar = pEnv->m_pConstVar;
	pEnv->m_pHeadFrameThread->m_pHeadFrame = pEnv->m_pHeadFrame;
	pEnv->m_pHeadFrameThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pHeadFrameThread->m_pRoutList = pEnv->m_pRoutList;
	OnInitHeadFrameThread(pEnv->m_pHeadFrameThread);
	// ��ʼ��IP��ַ�����߳�
	pEnv->m_pIPSetFrameThread->m_pThread->m_pConstVar = pEnv->m_pConstVar;
	pEnv->m_pIPSetFrameThread->m_pIPSetFrame = pEnv->m_pIPSetFrame;
	pEnv->m_pIPSetFrameThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	OnInitIPSetFrameThread(pEnv->m_pIPSetFrameThread);
	// ��ʼ��β�������߳�
	pEnv->m_pTailFrameThread->m_pThread->m_pConstVar = pEnv->m_pConstVar;
	pEnv->m_pTailFrameThread->m_pTailFrame = pEnv->m_pTailFrame;
	pEnv->m_pTailFrameThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pTailFrameThread->m_pRoutList = pEnv->m_pRoutList;
	OnInitTailFrameThread(pEnv->m_pTailFrameThread);
	// ��ʼ��ʱͳ�����߳�
	pEnv->m_pTimeDelayThread->m_pThread->m_pConstVar = pEnv->m_pConstVar;
	pEnv->m_pTimeDelayThread->m_pTailTimeFrame = pEnv->m_pTailTimeFrame;
	pEnv->m_pTimeDelayThread->m_pTimeDelayFrame = pEnv->m_pTimeDelayFrame;
	pEnv->m_pTimeDelayThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pTimeDelayThread->m_pRoutList = pEnv->m_pRoutList;
	OnInitTimeDelayThread(pEnv->m_pTimeDelayThread);
	// ��ʼ��·�ɼ����߳�
	pEnv->m_pMonitorRoutThread->m_pThread->m_pConstVar = pEnv->m_pConstVar;
	pEnv->m_pMonitorRoutThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pMonitorRoutThread->m_pRoutList = pEnv->m_pRoutList;
	pEnv->m_pMonitorRoutThread->m_pTimeDelayThread = pEnv->m_pTimeDelayThread;
	pEnv->m_pMonitorRoutThread->m_pADCSetThread = pEnv->m_pADCSetThread;
	OnInitMonitorRoutThread(pEnv->m_pMonitorRoutThread);
	// ��ʼ��ADC���������߳�
	pEnv->m_pADCSetThread->m_pThread->m_pConstVar = pEnv->m_pConstVar;
	pEnv->m_pADCSetThread->m_pADCSetFrame = pEnv->m_pADCSetFrame;
	pEnv->m_pADCSetThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pADCSetThread->m_pRoutList = pEnv->m_pRoutList;
	OnInitADCSetThread(pEnv->m_pADCSetThread);
}
// ��ʼ��
MatrixServerDll_API void OnInit(m_oEnvironmentStruct* pEnv)
{
	OnInitInstance(pEnv);
}
// �ر�
MatrixServerDll_API void OnClose(m_oEnvironmentStruct* pEnv)
{
	CString str = _T("");
	// �̹߳رձ�־λΪtrue
	pEnv->m_pLogOutPutThread->m_pThread->m_bClose = true;
	// �̹߳رձ�־λΪtrue
	pEnv->m_pHeartBeatThread->m_pThread->m_bClose = true;
	// �̹߳رձ�־λΪtrue
	pEnv->m_pHeadFrameThread->m_pThread->m_bClose = true;
	// �̹߳رձ�־λΪtrue
	pEnv->m_pIPSetFrameThread->m_pThread->m_bClose = true;
	// �̹߳رձ�־λΪtrue
	pEnv->m_pTailFrameThread->m_pThread->m_bClose = true;
	// �̹߳رձ�־λΪtrue
	pEnv->m_pMonitorRoutThread->m_pThread->m_bClose = true;
	// �̹߳رձ�־λΪtrue
	pEnv->m_pTimeDelayThread->m_pThread->m_bClose = true;
	// �̹߳رձ�־λΪtrue
	pEnv->m_pADCSetThread->m_pThread->m_bClose = true;
	// �ر������߳�
	OnCloseHeartBeatThread(pEnv->m_pHeartBeatThread);
	// �ر��װ������߳�
	OnCloseHeadFrameThread(pEnv->m_pHeadFrameThread);
	// �ر�IP��ַ�����߳�
	OnCloseIPSetFrameThread(pEnv->m_pIPSetFrameThread);
	// �ر�β�������߳�
	OnCloseTailFrameThread(pEnv->m_pTailFrameThread);
	// �ر�·�ɼ����߳�
	OnCloseMonitorRoutThread(pEnv->m_pMonitorRoutThread);
	// �ر�ʱͳ�����߳�
	OnCloseTimeDelayThread(pEnv->m_pTimeDelayThread);
	// �ر�ADC���������߳�
	OnCloseADCSetThread(pEnv->m_pADCSetThread);
	// �ر���־����߳�
	OnCloseLogOutPutThread(pEnv->m_pLogOutPutThread);

	// �ر�����Socket
	OnCloseSocket(pEnv->m_pHeartBeatFrame->m_oHeartBeatSocket);
	// �ر��װ�Socket
	OnCloseSocket(pEnv->m_pHeadFrame->m_oHeadFrameSocket);
	// �ر�IP��ַ����Socket
	OnCloseSocket(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket);
	// �ر�β��Socket
	OnCloseSocket(pEnv->m_pTailFrame->m_oTailFrameSocket);
	// �ر�β��ʱ��Socket
	OnCloseSocket(pEnv->m_pTailTimeFrame->m_oTailTimeFrameSocket);
	// �ر�ʱͳ����Socket
	OnCloseSocket(pEnv->m_pTimeDelayFrame->m_oTimeDelayFrameSocket);
	// �ر�ADC��������Socket
	OnCloseSocket(pEnv->m_pADCSetFrame->m_oADCSetFrameSocket);
	// �ͷ��׽��ֿ�
	OnCloseSocketLib(pEnv->m_pLogOutPutOpt);
	// �ͷų�����Դ
	OnCloseConstVar(pEnv->m_pConstVar);
	// �ͷ�������Դ
	OnCloseInstrumentHeartBeat(pEnv->m_pHeartBeatFrame);
	// �ͷ��װ���Դ
	OnCloseInstrumentHeadFrame(pEnv->m_pHeadFrame);
	// �ͷ�IP��ַ������Դ
	OnCloseInstrumentIPSetFrame(pEnv->m_pIPSetFrame);
	// �ͷ�β����Դ
	OnCloseInstrumentTailFrame(pEnv->m_pTailFrame);
	// �ͷ�β��ʱ����Դ
	OnCloseInstrumentTailTimeFrame(pEnv->m_pTailTimeFrame);
	// �ͷ�ʱͳ������Դ
	OnCloseInstrumentTimeDelayFrame(pEnv->m_pTimeDelayFrame);
	// �ͷ�ADC����������Դ
	OnCloseInstrumentADCSetFrame(pEnv->m_pADCSetFrame);
	// �ͷ�����������Դ
	OnCloseInstrumentList(pEnv->m_pInstrumentList);
	// �ͷ�·�ɶ�����Դ
	OnCloseRoutList(pEnv->m_pRoutList);
	// β��ʱ��
	str.Format(_T("β��ʱ�̲�ѯ�����ĸ���%d�� Ӧ��֡����%d"), pEnv->m_pTimeDelayThread->m_uiTailTimeQueryNum,
		pEnv->m_pTimeDelayThread->m_uiTailTimeReturnNum);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", ConvertCStrToStr(str));
	// ʱͳ
	str.Format(_T("ʱͳ���������ĸ���%d�� Ӧ��֡����%d"), pEnv->m_pTimeDelayThread->m_uiTimeDelaySetNum,
		pEnv->m_pTimeDelayThread->m_uiTimeDelayReturnNum);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", ConvertCStrToStr(str));

	// �رղ�����־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutOpt);
	// �ر�ʱͳ��־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutTimeDelay);
	// �ر������ѯ��־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutErrorCode);
	// �ر�ADC����֡ʱ����־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutADCFrameTime);
}
// ����
MatrixServerDll_API void OnWork(m_oEnvironmentStruct* pEnv)
{
	// ��ʼ������
	OnWorkInstrumentHeartBeat(pEnv->m_pHeartBeatFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ���װ�
	OnWorkInstrumentHeadFrame(pEnv->m_pHeadFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��IP��ַ����
	OnWorkInstrumentIPSetFrame(pEnv->m_pIPSetFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��β��
	OnWorkInstrumentTailFrame(pEnv->m_pTailFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��β��ʱ��
	OnWorkInstrumentTailTimeFrame(pEnv->m_pTailTimeFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��ʱͳ����
	OnWorkInstrumentTimeDelayFrame(pEnv->m_pTimeDelayFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��ADC��������
	OnWorkInstrumentADCSetFrame(pEnv->m_pADCSetFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ���������нṹ��
	OnWorkInstrumentList(pEnv->m_pInstrumentList, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��·�ɶ��нṹ��
	OnWorkRoutList(pEnv->m_pRoutList, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// �ر�����Socket
	OnCloseSocket(pEnv->m_pHeartBeatFrame->m_oHeartBeatSocket);
	// ���������������˿�
	OnCreateAndSetHeartBeatSocket(pEnv->m_pHeartBeatFrame);
	// �ر��װ�Socket
	OnCloseSocket(pEnv->m_pHeadFrame->m_oHeadFrameSocket);
	// �����������װ��˿�
	OnCreateAndSetHeadFrameSocket(pEnv->m_pHeadFrame);
	// �ر�IP��ַ����Socket
	OnCloseSocket(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket);
	// ����������IP��ַ���ö˿�
	OnCreateAndSetIPSetFrameSocket(pEnv->m_pIPSetFrame);
	// �ر�β��Socket
	OnCloseSocket(pEnv->m_pTailFrame->m_oTailFrameSocket);
	// ����������β���˿�
	OnCreateAndSetTailFrameSocket(pEnv->m_pTailFrame);
	// �ر�β��ʱ��Socket
	OnCloseSocket(pEnv->m_pTailTimeFrame->m_oTailTimeFrameSocket);
	// ����������β��ʱ�̲�ѯ֡�˿�
	OnCreateAndSetTailTimeFrameSocket(pEnv->m_pTailTimeFrame);
	// �ر�ʱͳ����Socket
	OnCloseSocket(pEnv->m_pTimeDelayFrame->m_oTimeDelayFrameSocket);
	// ����������ʱͳ����֡�˿�
	OnCreateAndSetTimeDelayFrameSocket(pEnv->m_pTimeDelayFrame);
	// �ر�ADC��������Socket
	OnCloseSocket(pEnv->m_pADCSetFrame->m_oADCSetFrameSocket);
	// ����������ADC��������֡�˿�
	OnCreateAndSetADCSetFrameSocket(pEnv->m_pADCSetFrame);
	// ��־����߳̿�ʼ����
	pEnv->m_pLogOutPutThread->m_pThread->m_bWork = true;
	// �����߳̿�ʼ����
	pEnv->m_pHeartBeatThread->m_pThread->m_bWork = true;
	// ����װ�֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pHeadFrameThread->m_pHeadFrame->m_oHeadFrameSocket, pEnv->m_pConstVar);
	// �װ������߳̿�ʼ����
	pEnv->m_pHeadFrameThread->m_pThread->m_bWork = true;
	// ���IP��ַ����Ӧ��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pIPSetFrameThread->m_pIPSetFrame->m_oIPSetFrameSocket, pEnv->m_pConstVar);
	// IP��ַ�����߳̿�ʼ����
	pEnv->m_pIPSetFrameThread->m_pThread->m_bWork = true;
	// ���β��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTailFrameThread->m_pTailFrame->m_oTailFrameSocket, pEnv->m_pConstVar);
	// β�������߳̿�ʼ����
	pEnv->m_pTailFrameThread->m_pThread->m_bWork = true;
	// ·�ɼ����߳̿�ʼ����
	pEnv->m_pMonitorRoutThread->m_pThread->m_bWork = true;
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnWork", "��ʼ����");
}
// ֹͣ
MatrixServerDll_API void OnStop(m_oEnvironmentStruct* pEnv)
{
	// ��־����߳�ֹͣ����
	pEnv->m_pLogOutPutThread->m_pThread->m_bWork = false;
	// �����߳�ֹͣ����
	pEnv->m_pHeartBeatThread->m_pThread->m_bWork = false;
	// �װ������߳�ֹͣ����
	pEnv->m_pHeadFrameThread->m_pThread->m_bWork = false;
	// IP��ַ�����߳�ֹͣ����
	pEnv->m_pIPSetFrameThread->m_pThread->m_bWork = false;
	// β�������߳�ֹͣ����
	pEnv->m_pTailFrameThread->m_pThread->m_bWork = false;
	// ·�ɼ����߳�ֹͣ����
	pEnv->m_pMonitorRoutThread->m_pThread->m_bWork = false;
	// ʱͳ�����߳�ֹͣ����
	pEnv->m_pTimeDelayThread->m_pThread->m_bWork = false;
	// ADC���������߳�ֹͣ����
	pEnv->m_pADCSetThread->m_pThread->m_bWork = false;
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnStop", "ֹͣ����");
}
// �ͷ�ʵ����Դ
MatrixServerDll_API void OnFreeInstance(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	// �ͷŲ�����־����ṹ����Դ
	OnFreeLogOutPut(pEnv->m_pLogOutPutOpt);
	// �ͷ�ʱͳ��־����ṹ����Դ
	OnFreeLogOutPut(pEnv->m_pLogOutPutTimeDelay);
	// �ͷ������ѯ��־����ṹ����Դ
	OnFreeLogOutPut(pEnv->m_pLogOutPutErrorCode);
	// �ͷ�ADC����֡ʱ����־����ṹ����Դ
	OnFreeLogOutPut(pEnv->m_pLogOutPutADCFrameTime);
	// �ͷ�INI�ļ����볣���ṹ����Դ
	OnFreeConstVar(pEnv->m_pConstVar);
	// �ͷ�XML�ļ������ͨѶ��Ϣ���ýṹ����Դ
	OnFreeInstrumentCommInfo(pEnv->m_pInstrumentCommInfo);
	// �ͷ�����֡�ṹ����Դ
	OnFreeInstrumentHeartBeat(pEnv->m_pHeartBeatFrame);
	// �ͷ��װ�֡�ṹ����Դ
	OnFreeInstrumentHeadFrame(pEnv->m_pHeadFrame);
	// �ͷ�IP��ַ����֡�ṹ����Դ
	OnFreeInstrumentIPSetFrame(pEnv->m_pIPSetFrame);
	// �ͷ�β��֡�ṹ����Դ
	OnFreeInstrumentTailFrame(pEnv->m_pTailFrame);
	// �ͷ�β��ʱ��֡�ṹ����Դ
	OnFreeInstrumentTailTimeFrame(pEnv->m_pTailTimeFrame);
	// �ͷ�ʱͳ����֡�ṹ����Դ
	OnFreeInstrumentTimeDelayFrame(pEnv->m_pTimeDelayFrame);
	// �ͷ�ADC��������֡�ṹ����Դ
	OnFreeInstrumentADCSetFrame(pEnv->m_pADCSetFrame);
	// �ͷ��������нṹ����Դ
	OnFreeInstrumentList(pEnv->m_pInstrumentList);
	// �ͷ�·�ɶ��нṹ����Դ
	OnFreeRoutList(pEnv->m_pRoutList);
	// �ͷ���־����߳�
	OnFreeLogOutPutThread(pEnv->m_pLogOutPutThread);
	// �ͷ������߳�
	OnFreeHeartBeatThread(pEnv->m_pHeartBeatThread);
	// �ͷ��װ������߳�
	OnFreeHeadFrameThread(pEnv->m_pHeadFrameThread);
	// �ͷ�IP��ַ�����߳�
	OnFreeIPSetFrameThread(pEnv->m_pIPSetFrameThread);
	// �ͷ�β�������߳�
	OnFreeTailFrameThread(pEnv->m_pTailFrameThread);
	// �ͷ�·�ɼ����߳�
	OnFreeMonitorRoutThread(pEnv->m_pMonitorRoutThread);
	// �ͷ�ʱͳ�����߳�
	OnFreeTimeDelayThread(pEnv->m_pTimeDelayThread);
	// �ͷ�ADC���������߳�
	OnFreeADCSetThread(pEnv->m_pADCSetThread);
	delete pEnv;
	pEnv = NULL;
}