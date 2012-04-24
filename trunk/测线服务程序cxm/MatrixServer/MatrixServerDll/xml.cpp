#include "stdafx.h"
#include "MatrixServerDll.h"

// ��������ͨѶ��Ϣ�ṹ��
m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(void)
{
	m_oInstrumentCommInfoStruct* pCommInfo = NULL;
	pCommInfo = new m_oInstrumentCommInfoStruct;
	pCommInfo->m_pLogOutPut = NULL;
	pCommInfo->m_strDllXMLFilePath = "";
	pCommInfo->m_strLineXMLFilePath = "";
	pCommInfo->m_strOptXMLFilePath = "";
	// ��ʼ��ADC����������Ϣ
	OnInitXMLADCSetupData(&pCommInfo->m_oXMLADCSetupData);
	InitializeCriticalSection(&pCommInfo->m_oSecCommInfo);
	return pCommInfo;
}
// ��ʼ��ADC����������Ϣ
void OnInitXMLADCSetupData(m_oXMLADCSetupDataStruct* pXMLADCSetupData)
{
	pXMLADCSetupData->m_cpSetADCSetSine = NULL;
	pXMLADCSetupData->m_cpSetADCStopSample = NULL;
	pXMLADCSetupData->m_cpSetADCOpenTBPowerLow = NULL;
	pXMLADCSetupData->m_cpSetADCOpenTBPowerHigh = NULL;
	pXMLADCSetupData->m_cpSetADCOpenSwitchTBLow = NULL;
	pXMLADCSetupData->m_cpSetADCOpenSwitchTBHigh = NULL;
	pXMLADCSetupData->m_cpSetADCRegisterRead = NULL;
	pXMLADCSetupData->m_cpSetADCRegisterWrite = NULL;
	pXMLADCSetupData->m_cpSetADCTBSwitchOpen = NULL;
	pXMLADCSetupData->m_cpSetADCSample = NULL;
	pXMLADCSetupData->m_cpSetADCReadContinuous = NULL;
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
//����IP��ַ��������
void LoadIPSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
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
	try
	{
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
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
		ConvertCStrToStr(csSrcIP, &strConv);
		pCommInfo->m_oXMLIPSetupData.m_uiSrcIP = inet_addr(strConv.c_str());
		// LCI��IP��ַ
		strKey = _T("IPLCI");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ConvertCStrToStr(csDstIP, &strConv);
		pCommInfo->m_oXMLIPSetupData.m_uiAimIP = inet_addr(strConv.c_str());
		// ADC���ݷ��ص�ַ
		strKey = _T("IPForADCData");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ConvertCStrToStr(csDstIP, &strConv);
		pCommInfo->m_oXMLIPSetupData.m_uiADCDataReturnAddr = inet_addr(strConv.c_str());
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
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
void LoadPortSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	try
	{
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		// �ҵ�IP��ַ������
		strKey = _T("LineServerAppPortSetup");
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = _T("PortLCI");
		pCommInfo->m_oXMLPortSetupData.m_usAimPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForHeartBeat");
		pCommInfo->m_oXMLPortSetupData.m_usHeartBeatReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForHeadFrame");
		pCommInfo->m_oXMLPortSetupData.m_usHeadFramePort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForIPSet");
		pCommInfo->m_oXMLPortSetupData.m_usIPSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTailFrame");
		pCommInfo->m_oXMLPortSetupData.m_usTailFramePort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTailTimeFrame");
		pCommInfo->m_oXMLPortSetupData.m_usTailTimeReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForTimeSet");
		pCommInfo->m_oXMLPortSetupData.m_usTimeDelayReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCSet");
		pCommInfo->m_oXMLPortSetupData.m_usADCSetReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForErrorCode");
		pCommInfo->m_oXMLPortSetupData.m_usErrorCodeReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCData");
		pCommInfo->m_oXMLPortSetupData.m_usADCDataReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
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
//����ADC������������
void LoadADCSetData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey = _T("");
	CString strValue = _T("");
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	try
	{
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		// �ҵ�ADC����������
		strKey = _T("ADCSetSetup");
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// ADC�������Ҳ������С
		strKey = _T("SetADCSetSineSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCSetSineSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC�������Ҳ�����
		strKey = _T("SetADCSetSine");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCSetSineSize, strValue);

		// ADC����ֹͣ���������С
		strKey = _T("SetADCStopSampleSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCStopSampleSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC����ֹͣ��������
		strKey = _T("SetADCStopSample");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCStopSampleSize, strValue);

		// ADC���ô�TB��Դ��λ��С
		strKey = _T("SetADCOpenTBPowerLowSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenTBPowerLowSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB��Դ��λ
		strKey = _T("SetADCOpenTBPowerLow");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenTBPowerLowSize, strValue);
	
		// ADC���ô�TB��Դ��λ��С
		strKey = _T("SetADCOpenTBPowerHighSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenTBPowerHighSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB��Դ��λ
		strKey = _T("SetADCOpenTBPowerHigh");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenTBPowerHighSize, strValue);
	
		// ADC���ô�TB���ص�λ��С
		strKey = _T("SetADCOpenSwitchTBLowSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBLowSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB���ص�λ
		strKey = _T("SetADCOpenSwitchTBLow");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBLowSize, strValue);
	
		// ADC���ô�TB���ظ�λ��С
		strKey = _T("SetADCOpenSwitchTBHighSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBHighSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB���ظ�λ
		strKey = _T("SetADCOpenSwitchTBHigh");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBHighSize, strValue);
	
		// ADC���ö��Ĵ�����С
		strKey = _T("SetADCRegisterReadSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCRegisterReadSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ö��Ĵ���
		strKey = _T("SetADCRegisterRead");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCRegisterReadSize, strValue);

		// ADC����д�Ĵ�����С
		strKey = _T("SetADCRegisterWriteSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCRegisterWriteSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC����д�Ĵ���
		strKey = _T("SetADCRegisterWrite");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCRegisterWriteSize, strValue);

		// ADC���ô�TB���ش�С
		strKey = _T("SetADCTBSwitchOpenSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCTBSwitchOpenSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB����
		strKey = _T("SetADCTBSwitchOpen");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCTBSwitchOpenSize, strValue);
		
		// ADC�������ô�С
		strKey = _T("SetADCSampleSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCSampleSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC��������
		strKey = _T("SetADCSample");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCSampleSize, strValue);
		
		// ADC��������������С
		strKey = _T("SetADCReadContinuousSize");
		pCommInfo->m_oXMLADCSetupData.m_iSetADCReadContinuousSize = 
			CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC������������
		strKey = _T("SetADCReadContinuous");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous, 
			pCommInfo->m_oXMLADCSetupData.m_iSetADCReadContinuousSize, strValue);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
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
//���ز��߷�����������������
void LoadServerAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strDllXMLFilePath))
	{
		//����IP��ַ��������
		LoadIPSetupData(pCommInfo);
		//���ض˿���������
		LoadPortSetupData(pCommInfo);
		//����ADC������������
		LoadADCSetData(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
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
	LoadServerAppSetupData(pCommInfo);
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
// �ͷ�ADC����������Ϣ�ṹ�建����
void OnFreeXMLADCSetupData(m_oXMLADCSetupDataStruct* pXMLADCSetupData)
{
	if (pXMLADCSetupData == NULL)
	{
		return;
	}
	if (pXMLADCSetupData->m_cpSetADCSetSine != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCSetSine;
		pXMLADCSetupData->m_cpSetADCSetSine = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCStopSample != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCStopSample;
		pXMLADCSetupData->m_cpSetADCStopSample = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCOpenTBPowerLow != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCOpenTBPowerLow;
		pXMLADCSetupData->m_cpSetADCOpenTBPowerLow = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCOpenTBPowerHigh != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCOpenTBPowerHigh;
		pXMLADCSetupData->m_cpSetADCOpenTBPowerHigh = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCOpenSwitchTBLow != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCOpenSwitchTBLow;
		pXMLADCSetupData->m_cpSetADCOpenSwitchTBLow = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCOpenSwitchTBHigh != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCOpenSwitchTBHigh;
		pXMLADCSetupData->m_cpSetADCOpenSwitchTBHigh = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCRegisterRead != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCRegisterRead;
		pXMLADCSetupData->m_cpSetADCRegisterRead = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCRegisterWrite != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCRegisterWrite;
		pXMLADCSetupData->m_cpSetADCRegisterWrite = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCTBSwitchOpen != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCTBSwitchOpen;
		pXMLADCSetupData->m_cpSetADCTBSwitchOpen = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCSample != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCSample;
		pXMLADCSetupData->m_cpSetADCSample = NULL;
	}
	if (pXMLADCSetupData->m_cpSetADCReadContinuous != NULL)
	{
		delete[] pXMLADCSetupData->m_cpSetADCReadContinuous;
		pXMLADCSetupData->m_cpSetADCReadContinuous = NULL;
	}
}
// �ͷ�����ͨѶ��Ϣ�ṹ��
void OnFreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	OnFreeXMLADCSetupData(&pCommInfo->m_oXMLADCSetupData);
	DeleteCriticalSection(&pCommInfo->m_oSecCommInfo);
	delete pCommInfo;
}

