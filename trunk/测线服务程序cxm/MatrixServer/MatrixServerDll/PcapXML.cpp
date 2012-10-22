#include "stdafx.h"
#include "MatrixServerDll.h"
// ��ʼ��Pcap����������Ϣ�ṹ��
void OnInitPcapXMLSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	InitializeCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	pPcapSetupData->m_strPcapXMLFilePath = "..\\parameter\\MatrixServer.XML";
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
}
// ����Pcap������Ϣ�ṹ��
m_oNetPcapSetupDataStruct* OnCreatePcapAppSetupData(void)
{
	m_oNetPcapSetupDataStruct* pPcapSetupData = NULL;
	pPcapSetupData = new m_oNetPcapSetupDataStruct;
	// ��ʼ��Pcap������Ϣ�ṹ��
	OnInitPcapXMLSetupData(pPcapSetupData);
	return pPcapSetupData;
}
// ��Pcap���������ļ�
BOOL OpenPcapXMLFile(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;
	CString str = _T("");
	strOLEObject = _T("msxml2.domdocument");
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	// ��ʼ��COM��
	CoInitialize(NULL);
	if (FALSE == pPcapSetupData->m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError))
	{
		AfxMessageBox(_T("XML�ṹ����ʧ�ܣ�"));
		LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
		return FALSE;
	}
	str = pPcapSetupData->m_strPcapXMLFilePath.c_str();
	oVariant = str;
	if (false == IfFileExist(str))
	{
		AfxMessageBox(_T("�ļ�������"));
		LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
		return FALSE;
	}
	if (FALSE == pPcapSetupData->m_oXMLDOMDocument.load(oVariant))
	{
		LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
		return FALSE;
	}
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	return TRUE;
}
// �ر�Pcap���������ļ�
void ClosePcapXMLFile(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	pPcapSetupData->m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
}
// ����IP��������
void LoadPcapIP(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
	CString strKey;
	string strConv = "";
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	try
	{
		// �ҵ�NetIPSetup������
		strKey = "NetIPSetup";
		lpDispatch = pPcapSetupData->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = "LowIP";
		pPcapSetupData->m_oXMLIPSetupData.m_strLowIP = (CStringA)CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		strKey = "HighIP";
		pPcapSetupData->m_oXMLIPSetupData.m_strHighIP = (CStringA)CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
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
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
}
// ����PcapIP��������
void LoadPcapIPSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenPcapXMLFile(pPcapSetupData))
	{
		// ����IP��������
		LoadPcapIP(pPcapSetupData);
	}
	// �رճ��������ļ�
	ClosePcapXMLFile(pPcapSetupData);
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
}
// ���ض˿���������
void LoadPcapPort(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
	CString strKey;
	string strConv = "";
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	try
	{
		// �ҵ�NetPortSetup������
		strKey = "NetPortSetup";
		lpDispatch = pPcapSetupData->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = "NetDownStreamSrcPort";
		pPcapSetupData->m_oXMLPortSetupData.m_usDownStreamPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = "NetUpStreamSrcPort";
		pPcapSetupData->m_oXMLPortSetupData.m_usUpStreamPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
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
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
}
// ����Pcap�˿���������
void LoadPcapPortSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenPcapXMLFile(pPcapSetupData))
	{
		// ���ض˿���������
		LoadPcapPort(pPcapSetupData);
	}
	// �رճ��������ļ�
	ClosePcapXMLFile(pPcapSetupData);
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
}
// ���ز�����������
void LoadPcapParam(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
	CString strKey;
	string strConv = "";
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	try
	{
		// �ҵ�NetParameterSetup������
		strKey = "NetParameterSetup";
		lpDispatch = pPcapSetupData->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = "NetAppPath";
		pPcapSetupData->m_oPcapParamSetupData.m_strPath = (CStringA)CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		strKey = "NetCardId";
		pPcapSetupData->m_oPcapParamSetupData.m_usNetCardID = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = "WinpcapBufSize";
		pPcapSetupData->m_oPcapParamSetupData.m_uiPcapBufSize = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "DownStreamSndBufSize";
		pPcapSetupData->m_oPcapParamSetupData.m_uiDownStreamSndBufSize = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "UpStreamSndBufSize";
		pPcapSetupData->m_oPcapParamSetupData.m_uiUpStreamSndBufSize = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "MaxPackageSize";
		pPcapSetupData->m_oPcapParamSetupData.m_uiPcapMaxPackageSize = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "PcapTimeOut";
		pPcapSetupData->m_oPcapParamSetupData.m_uiPcapTimeOut = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "PcapSndWaitTime";
		pPcapSetupData->m_oPcapParamSetupData.m_uiPcapSndWaitTime = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "PcapRcvWaitTime";
		pPcapSetupData->m_oPcapParamSetupData.m_uiPcapRcvWaitTime = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "PcapQueueSize";
		pPcapSetupData->m_oPcapParamSetupData.m_uiPcapQueueSize = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
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
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
}
// ����Pcap������������
void LoadPcapParamSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
	EnterCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenPcapXMLFile(pPcapSetupData))
	{
		// ���ز�����������
		LoadPcapParam(pPcapSetupData);
	}
	// �رճ��������ļ�
	ClosePcapXMLFile(pPcapSetupData);
	LeaveCriticalSection(&pPcapSetupData->m_oSecCommInfo);
}
// ����Pcap����������Ϣ
void LoadPcapAppSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	ASSERT(pPcapSetupData != NULL);
 	// ����IP����
 	LoadPcapIPSetupData(pPcapSetupData);
  	// ���ض˿�����
  	LoadPcapPortSetupData(pPcapSetupData);
  	// ���ز�������
  	LoadPcapParamSetupData(pPcapSetupData);
}

// �ͷ�Pcap����������Ϣ�ṹ�建����
void OnFreePcapXMLSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData)
{
	DeleteCriticalSection(&pPcapSetupData->m_oSecCommInfo);
	delete pPcapSetupData;
	pPcapSetupData = NULL;
}