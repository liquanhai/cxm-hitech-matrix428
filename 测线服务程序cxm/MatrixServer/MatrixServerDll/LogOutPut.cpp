#include "stdafx.h"
#include "MatrixServerDll.h"

// ������־����ṹ��
m_oLogOutPutStruct* OnCreateLogOutPut()
{
	m_oLogOutPutStruct* pLogOutPut = NULL;
	pLogOutPut = new m_oLogOutPutStruct;
	InitializeCriticalSection(&pLogOutPut->m_oSecLogFile);
	return pLogOutPut;
}
// ����־����ļ�
int OpenLogOutPutFile(m_oLogOutPutStruct* pLogOutPut)
{
	if ((pLogOutPut == NULL)
		|| ((OutPutSelect == 1) && (pLogOutPut->m_cLogFileType != OptLogType)))
	{
		return -1;
	}
	CString strPath = _T("");
	CString str = _T("");
	string strConv = "";
	errno_t err;
	// ��������������־�ļ���
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	pLogOutPut->m_uiLogFileNb++;
	strPath.Format(_T("\\%d.log"), pLogOutPut->m_uiLogFileNb);
	str = pLogOutPut->m_SaveLogFilePath.c_str();
	strPath = str + strPath;
	pLogOutPut->m_uiLogInfoCount = 0;
	strConv = (CStringA)strPath;
	err = fopen_s(&pLogOutPut->m_pFile, strConv.c_str(), 
		"wt+, ccs=UNICODE");
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
	return err;
}
// ���뵽��־�������
void AddMsgToLogOutPutList(m_oLogOutPutStruct* pLogOutPut, string pFuncName, 
	string pVarName, byte byErrorType, unsigned int uiErrorCode)
{
	if ((pLogOutPut == NULL)
		|| ((OutPutSelect == 1) 
		&& ((byErrorType != ErrorType) || (pLogOutPut->m_cLogFileType != OptLogType))))
	{
		return;
	}

	CString strTime = _T("");
	CString strErrorCode = _T("");
	CString strOutPut = _T("");
	string str = "";
	string strTemp = "";
	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);
	strTime.Format(_T("%04d��%02d��%02d�� %02d:%02d:%02d:%03d\t"), sysTime.wYear,
		sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, 
		sysTime.wSecond, sysTime.wMilliseconds);
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
		strErrorCode.Format(_T("ErrorCode = %d\t"), uiErrorCode);
		strOutPut += strErrorCode;
	}
	else if (byErrorType == ExpandType)
	{
		strOutPut += _T("ExpandType\t");
	}
	strOutPut += strTime;
	str = (CStringA)strOutPut;
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
	if ((byErrorType == ErrorType) || (byErrorType == WarningType))
	{
		OutputDebugString((CString)str.c_str());
	}
	str += '\n';
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	if (pLogOutPut->m_uiErrorCount > OutPutLogErrorLimit)
	{
		LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
		return;
	}
	pLogOutPut->m_oLogOutputList.push_back(str);
	if (byErrorType == ErrorType)
	{
		pLogOutPut->m_uiErrorCount++;
	}
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// ��־���д���ļ�
void LogOutPutWriteInFile(FILE* pFile, string str, bool bFlush)
{
	if (pFile == NULL)
	{
		return;
	}
	size_t strSize = str.length();
	fwrite(str.c_str(), sizeof(char), strSize, pFile);
	if (bFlush == true)
	{
		fflush(pFile);
	}
}
// д����־����ļ�
void WriteLogOutPutListToFile(m_oLogOutPutStruct* pLogOutPut)
{
	if ((pLogOutPut == NULL)
		|| ((OutPutSelect == 1) && (pLogOutPut->m_cLogFileType != OptLogType))
		|| (pLogOutPut->m_pFile == NULL))
	{
		return;
	}
	list<string>::iterator iter;
	string str = "";
	bool bOpenNewFile = false;
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	while(pLogOutPut->m_oLogOutputList.empty() == false)
	{
		iter = pLogOutPut->m_oLogOutputList.begin();
		str += *iter;
		pLogOutPut->m_oLogOutputList.pop_front();
		pLogOutPut->m_uiLogInfoCount++;
	}
	if (pLogOutPut->m_cLogFileType == OptLogType)
	{
		LogOutPutWriteInFile(pLogOutPut->m_pFile, str, true);
	}
	else
	{
		LogOutPutWriteInFile(pLogOutPut->m_pFile, str, false);
	}
	if (pLogOutPut->m_uiLogInfoCount > OutPutLogFileInfoNumLimit)
	{
		fclose(pLogOutPut->m_pFile);
		bOpenNewFile = true;
	}
	if (bOpenNewFile == true)
	{
		OpenLogOutPutFile(pLogOutPut);
	}
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}
// �ر���־����ļ�
void CloseLogOutPutFile(m_oLogOutPutStruct* pLogOutPut)
{
	if ((pLogOutPut == NULL)
		|| ((OutPutSelect == 1) && (pLogOutPut->m_cLogFileType != OptLogType))
		|| (pLogOutPut->m_pFile == NULL))
	{
		return;
	}
	EnterCriticalSection(&pLogOutPut->m_oSecLogFile);
	WriteLogOutPutListToFile(pLogOutPut);
	fclose( pLogOutPut->m_pFile );
	LeaveCriticalSection(&pLogOutPut->m_oSecLogFile);
}

// ��ʼ����־����ṹ��
void OnInitLogOutPut(m_oLogOutPutStruct* pLogOutPut)
{
	if ((pLogOutPut == NULL)
		|| ((OutPutSelect == 1) && (pLogOutPut->m_cLogFileType != OptLogType)))
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
void OnCloseLogOutPut(m_oLogOutPutStruct* pLogOutPut)
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
}
// �ͷ���־����ṹ��
void OnFreeLogOutPut(m_oLogOutPutStruct* pLogOutPut)
{
	if (pLogOutPut == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pLogOutPut->m_oSecLogFile);
	delete pLogOutPut;
	pLogOutPut = NULL;
}