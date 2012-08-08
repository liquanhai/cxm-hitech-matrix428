#include "stdafx.h"
#include "MatrixServerDll.h"

// ��������ͨѶ��Ϣ�ṹ��
m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(void)
{
	m_oInstrumentCommInfoStruct* pCommInfo = NULL;
	pCommInfo = new m_oInstrumentCommInfoStruct;
	pCommInfo->m_pLogOutPut = NULL;
	pCommInfo->m_strServerXMLFilePath = "..\\parameter\\MatrixServer.XML";
	pCommInfo->m_strLineXMLFilePath = "..\\parameter\\MatrixLine.XML";
	pCommInfo->m_strOptXMLFilePath = "..\\parameter\\MatrixOperation.XML";

	InitializeCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ��ʼ���������������Ϣ
	OnInitServerXMLSetupData(pCommInfo);
	// ��ʼ�����߿ͻ�����������Ϣ
	OnInitLineClientXMLSetupData(pCommInfo);
	// ��ʼ��ʩ���ͻ�����������Ϣ
	OnInitOptClientXMLSetupData(pCommInfo);
	return pCommInfo;
}

// �򿪳��������ļ�
BOOL OpenAppXMLFile(m_oInstrumentCommInfoStruct* pCommInfo,
	string strXMLFilePath)
{
	if (pCommInfo == NULL)
	{
		return FALSE;
	}
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;
	CString str = _T("");
	strOLEObject = _T("msxml2.domdocument");
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ��ʼ��COM��
	CoInitialize(NULL);
	if (FALSE == pCommInfo->m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError))
	{
		AddMsgToLogOutPutList(pCommInfo->m_pLogOutPut, "OpenAppIniXMLFile", "CreateDispatch",
			ErrorType, IDS_ERR_XMLINTERFACE);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
		return FALSE;
	}
	str = strXMLFilePath.c_str();
	oVariant = str;
	if (false == IfFileExist(str))
	{
		AddMsgToLogOutPutList(pCommInfo->m_pLogOutPut, "OpenAppIniXMLFile", "",
			ErrorType, IDS_ERR_FILE_NOEXIST);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
		return FALSE;
	}
	if (FALSE == pCommInfo->m_oXMLDOMDocument.load(oVariant))
	{
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
		return FALSE;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	return TRUE;
}

// ��ʼ������ͨѶ��Ϣ�ṹ��
void OnInitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo, 
	m_oLogOutPutStruct* pLogOutPut)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	pCommInfo->m_pLogOutPut = pLogOutPut;
	// ���ط�����������������
	LoadServerAppSetupData(pCommInfo);
	// ���ز��߿ͻ��˳�����������
	LoadLineAppSetupData(pCommInfo);
	// ����ʩ���ͻ��˳�����������
	LoadOptAppSetupData(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// �رճ��������ļ�
void CloseAppXMLFile(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	pCommInfo->m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// �ͷ�����ͨѶ��Ϣ�ṹ��
void OnFreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// �ͷŷ���˲���������Ϣ�ṹ�建����
	OnFreeServerXMLSetupData(pCommInfo);
	// ������߿ͻ��˳�����������
	SaveLineAppSetupData(pCommInfo);
	// ���ò��߿ͻ�����Ϣ
	OnResetLineClientXMLSetupData(pCommInfo);
	// ����ʩ���ͻ��˳�����������
	SaveOptAppSetupData(pCommInfo);
	// ����ʩ���ͻ�����Ϣ
	OnResetOptClientXMLSetupData(pCommInfo);
	DeleteCriticalSection(&pCommInfo->m_oSecCommInfo);
	delete pCommInfo;
	pCommInfo = NULL;
}

