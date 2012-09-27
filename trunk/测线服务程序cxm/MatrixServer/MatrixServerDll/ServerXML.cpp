#include "stdafx.h"
#include "MatrixServerDll.h"

// ��ʼ���������������Ϣ
void OnInitServerXMLSetupData(m_oServerSetupDataStruct* pServerSetupData)
{
	InitializeCriticalSection(&pServerSetupData->m_oSecCommInfo);
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	pServerSetupData->m_strServerXMLFilePath = "..\\parameter\\MatrixServer.XML";
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSetSine = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterRead = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterWrite = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_cpSetADCReadContinuous = NULL;
	pServerSetupData->m_oXMLADCSetupData.m_iSampleRate = 1000;	// Ĭ��1K������
	pServerSetupData->m_oXMLADCSetupData.m_bHPFOpen = true;	// ��ͨ�˲���Ĭ�Ͽ���
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ���������ͨѶ��Ϣ�ṹ��
m_oServerSetupDataStruct* OnCreateServerAppSetupData(void)
{
	m_oServerSetupDataStruct* pServerSetupData = NULL;
	pServerSetupData = new m_oServerSetupDataStruct;
	// ��ʼ���������������Ϣ
	OnInitServerXMLSetupData(pServerSetupData);
	return pServerSetupData;
}
// �򿪷�����������ļ�
BOOL OpenServerXMLFile(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return FALSE;
	}
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;
	CString str = _T("");
	strOLEObject = _T("msxml2.domdocument");
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	// ��ʼ��COM��
	CoInitialize(NULL);
	if (FALSE == pServerSetupData->m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError))
	{
		AfxMessageBox(_T("XML�ṹ����ʧ�ܣ�"));
		LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
		return FALSE;
	}
	str = pServerSetupData->m_strServerXMLFilePath.c_str();
	oVariant = str;
	if (false == IfFileExist(str))
	{
		AfxMessageBox(_T("�ļ�������"));
		LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
		return FALSE;
	}
	if (FALSE == pServerSetupData->m_oXMLDOMDocument.load(oVariant))
	{
		LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
		return FALSE;
	}
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
	return TRUE;
}
// �رշ�����������ļ�
void CloseServerXMLFile(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	pServerSetupData->m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ����IP��ַ��������
void LoadServerIP(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	CString csSrcIP = _T("");
	CString csDstIP = _T("");
	string strConv = "";
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	try
	{
		// �ҵ�IP��ַ������
		strKey = _T("ServerAppIPSetup");
		lpDispatch = pServerSetupData->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// ���ֳ�����ͨѶ�ı���IP��ַ
		strKey = _T("ServerIP");
		csSrcIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		strConv = (CStringA)csSrcIP;
		pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP = inet_addr(strConv.c_str());
		// LCI��IP��ַ
		strKey = _T("IPLCI");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		strConv = (CStringA)csDstIP;
		pServerSetupData->m_oXMLIPSetupData.m_uiAimIP = inet_addr(strConv.c_str());
		// ADC���ݷ��ص�ַ
		strKey = _T("IPForADCDataReturn");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		strConv = (CStringA)csDstIP;
		pServerSetupData->m_oXMLIPSetupData.m_uiADCDataReturnAddr = inet_addr(strConv.c_str());
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
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ���ض˿���������
void LoadServerPort(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	try
	{
		// �ҵ�IP��ַ������
		strKey = _T("ServerAppPortSetSetup");
		lpDispatch = pServerSetupData->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = _T("PortLCI");
		pServerSetupData->m_oXMLPortSetupData.m_usAimPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForHeartBeatSet");
		pServerSetupData->m_oXMLPortSetupData.m_usHeartBeatReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForHeadFrameSet");
		pServerSetupData->m_oXMLPortSetupData.m_usHeadFramePort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForIPSetSet");
		pServerSetupData->m_oXMLPortSetupData.m_usIPSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTailFrameSet");
		pServerSetupData->m_oXMLPortSetupData.m_usTailFramePort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTailTimeFrameSet");
		pServerSetupData->m_oXMLPortSetupData.m_usTailTimeReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTimeSetSet");
		pServerSetupData->m_oXMLPortSetupData.m_usTimeDelayReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCSetSet");
		pServerSetupData->m_oXMLPortSetupData.m_usADCSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForErrorCodeSet");
		pServerSetupData->m_oXMLPortSetupData.m_usErrorCodeReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCDataSet");
		pServerSetupData->m_oXMLPortSetupData.m_usADCDataReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
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
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ����ADC������������
void LoadServerADCSet(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	CString strKey = _T("");
	CString strValue = _T("");
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	try
	{
		// �ҵ�ADC����������
		strKey = _T("ServerAppADCSetSetup");
		lpDispatch = pServerSetupData->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// ADC�������Ҳ������С
		strKey = _T("SetADCSetSineSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCSetSineSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC�������Ҳ�����
		strKey = _T("SetADCSetSine");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSetSine, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCSetSineSize, strValue);

		// ADC����ֹͣ���������С
		strKey = _T("SetADCStopSampleSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCStopSampleSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC����ֹͣ��������
		strKey = _T("SetADCStopSample");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCStopSampleSize, strValue);

		// ADC���ô�TB��Դ��λ��С
		strKey = _T("SetADCOpenTBPowerLowSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenTBPowerLowSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB��Դ��λ
		strKey = _T("SetADCOpenTBPowerLow");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenTBPowerLowSize, strValue);

		// ADC���ô�TB��Դ��λ��С
		strKey = _T("SetADCOpenTBPowerHighSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenTBPowerHighSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB��Դ��λ
		strKey = _T("SetADCOpenTBPowerHigh");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenTBPowerHighSize, strValue);

		// ADC���ô�TB���ص�λ��С
		strKey = _T("SetADCOpenSwitchTBLowSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBLowSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB���ص�λ
		strKey = _T("SetADCOpenSwitchTBLow");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBLowSize, strValue);

		// ADC���ô�TB���ظ�λ��С
		strKey = _T("SetADCOpenSwitchTBHighSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBHighSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB���ظ�λ
		strKey = _T("SetADCOpenSwitchTBHigh");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBHighSize, strValue);

		// ADC���ö��Ĵ�����С
		strKey = _T("SetADCRegisterReadSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCRegisterReadSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ö��Ĵ���
		strKey = _T("SetADCRegisterRead");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterRead, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCRegisterReadSize, strValue);

		// ADC����д�Ĵ�����С
		strKey = _T("SetADCRegisterWriteSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCRegisterWriteSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC����д�Ĵ���
		strKey = _T("SetADCRegisterWrite");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterWrite, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCRegisterWriteSize, strValue);

		// ADC���ô�TB���ش�С
		strKey = _T("SetADCTBSwitchOpenSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCTBSwitchOpenSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB����
		strKey = _T("SetADCTBSwitchOpen");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCTBSwitchOpenSize, strValue);

		// ADC�������ô�С
		strKey = _T("SetADCSampleSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCSampleSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC��������
		strKey = _T("SetADCSample");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCSampleSize, strValue);

		// ADC��������������С
		strKey = _T("SetADCReadContinuousSize");
		pServerSetupData->m_oXMLADCSetupData.m_iSetADCReadContinuousSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC������������
		strKey = _T("SetADCReadContinuous");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pServerSetupData->m_oXMLADCSetupData.m_cpSetADCReadContinuous, 
			pServerSetupData->m_oXMLADCSetupData.m_iSetADCReadContinuousSize, strValue);
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
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ���ط���˲�����������
void LoadServerParameter(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	CString strKey;
	CString str = _T("");
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	int nYear,nMonth,nDay,nHour,nMin,nSec;
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	try
	{
		// �ҵ�����������
		strKey = _T("ServerAppParameterSetup");
		lpDispatch = pServerSetupData->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = _T("FieldOffTime");
		str = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		_stscanf_s(str, _T("%d.%d.%d %d:%d:%d"), &nYear, &nMonth, &nDay, &nHour, &nMin, &nSec);
		CTime time(nYear, nMonth, nDay, nHour, nMin, nSec);
		pServerSetupData->m_oXMLParameterSetupData.m_oTimeFieldOff = time;
		strKey = _T("NetRcvPortMove");
		pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
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
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// �������˲�����������
void SaveServerParameter(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	CString strKey;
	CString str = _T("");
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	COleVariant oVariant;
	CTime time;
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	try
	{
		// �ҵ�����������
		strKey = _T("ServerAppParameterSetup");
		lpDispatch = pServerSetupData->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = _T("FieldOffTime");
		time = pServerSetupData->m_oXMLParameterSetupData.m_oTimeFieldOff;
		str.Format(_T("%d.%d.%d %d:%d:%d"), time.GetYear(), time.GetMonth(), time.GetDay(),
			time.GetHour(), time.GetMinute(), time.GetSecond());
		oVariant = str;
		oElement.setAttribute(strKey, oVariant);
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
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ����IP��ַ��������
void LoadServerIPSetupData(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenServerXMLFile(pServerSetupData))
	{
		// ����IP��ַ��������
		LoadServerIP(pServerSetupData);
	}
	// �رճ��������ļ�
	CloseServerXMLFile(pServerSetupData);
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ���ض˿���������
void LoadServerPortSetupData(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenServerXMLFile(pServerSetupData))
	{
		// ���ض˿���������
		LoadServerPort(pServerSetupData);
	}
	// �رճ��������ļ�
	CloseServerXMLFile(pServerSetupData);
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ����ADC������������
void LoadServerADCSetSetupData(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenServerXMLFile(pServerSetupData))
	{
		// ����ADC������������
		LoadServerADCSet(pServerSetupData);
	}
	// �رճ��������ļ�
	CloseServerXMLFile(pServerSetupData);
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ���ط������˲�����������
void LoadServerParameterSetupData(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenServerXMLFile(pServerSetupData))
	{
		// ���ط���˲�����������
		LoadServerParameter(pServerSetupData);
	}
	// �رճ��������ļ�
	CloseServerXMLFile(pServerSetupData);
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ����������˲�����������
void SaveServerParameterSetupData(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenServerXMLFile(pServerSetupData))
	{
		// ����������˲�����������
		SaveServerParameter(pServerSetupData);
	}
	oVariant = (CString)(pServerSetupData->m_strServerXMLFilePath.c_str());
	pServerSetupData->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseServerXMLFile(pServerSetupData);
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
}
// ���ط�����������������
void LoadServerAppSetupData(m_oServerSetupDataStruct* pServerSetupData)
{
	// ����IP��ַ��������
	LoadServerIPSetupData(pServerSetupData);
	// ���ض˿���������
	LoadServerPortSetupData(pServerSetupData);
	// ����ADC������������
	LoadServerADCSetSetupData(pServerSetupData);
	// ���ط������˲�����������
	LoadServerParameterSetupData(pServerSetupData);
}
// �ͷŷ���˲���������Ϣ�ṹ�建����
void OnFreeServerXMLSetupData(m_oServerSetupDataStruct* pServerSetupData)
{
	if (pServerSetupData == NULL)
	{
		return;
	}
	EnterCriticalSection(&pServerSetupData->m_oSecCommInfo);
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSetSine != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSetSine;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSetSine = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterRead != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterRead;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterRead = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterWrite != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterWrite;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterWrite = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample = NULL;
	}
	if (pServerSetupData->m_oXMLADCSetupData.m_cpSetADCReadContinuous != NULL)
	{
		delete[] pServerSetupData->m_oXMLADCSetupData.m_cpSetADCReadContinuous;
		pServerSetupData->m_oXMLADCSetupData.m_cpSetADCReadContinuous = NULL;
	}
	LeaveCriticalSection(&pServerSetupData->m_oSecCommInfo);
	DeleteCriticalSection(&pServerSetupData->m_oSecCommInfo);
	delete pServerSetupData;
	pServerSetupData = NULL;
}