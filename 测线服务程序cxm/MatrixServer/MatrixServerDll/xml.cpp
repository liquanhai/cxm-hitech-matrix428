#include "stdafx.h"
#include "MatrixServerDll.h"

// ��������ͨѶ��Ϣ�ṹ��
m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(void)
{
	m_oInstrumentCommInfoStruct* pCommInfo = NULL;
	pCommInfo = new m_oInstrumentCommInfoStruct;
	pCommInfo->m_pLogOutPut = NULL;
	pCommInfo->m_cpSetADCSetSine = NULL;
	pCommInfo->m_cpSetADCStopSample = NULL;
	pCommInfo->m_cpSetADCOpenTBPowerLow = NULL;
	pCommInfo->m_cpSetADCOpenTBPowerHigh = NULL;
	pCommInfo->m_cpSetADCOpenSwitchTBLow = NULL;
	pCommInfo->m_cpSetADCOpenSwitchTBHigh = NULL;
	pCommInfo->m_cpSetADCRegisterRead = NULL;
	pCommInfo->m_cpSetADCRegisterWrite = NULL;
	pCommInfo->m_cpSetADCTBSwitchOpen = NULL;
	pCommInfo->m_cpSetADCSample = NULL;
	pCommInfo->m_cpSetADCReadContinuous = NULL;
	InitializeCriticalSection(&pCommInfo->m_oSecCommInfo);
	return pCommInfo;
}
// �򿪳��������ļ�
BOOL OpenAppIniXMLFile(m_oInstrumentCommInfoStruct* pCommInfo,
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
		pCommInfo->m_uiSrcIP = inet_addr(strConv.c_str());
		// LCI��IP��ַ
		strKey = _T("IPLCI");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ConvertCStrToStr(csDstIP, &strConv);
		pCommInfo->m_uiAimIP = inet_addr(strConv.c_str());
		// ADC���ݷ��ص�ַ
		strKey = _T("IPForADCData");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ConvertCStrToStr(csDstIP, &strConv);
		pCommInfo->m_uiADCDataReturnAddr = inet_addr(strConv.c_str());
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
		strKey = _T("PortForErrorCode");
		pCommInfo->m_usErrorCodeReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
		strKey = _T("PortForADCData");
		pCommInfo->m_usADCDataReturnPort = CXMLDOMTool::GetElementAttributeUnsignedShort(&oElement, strKey);
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
		pCommInfo->m_iSetADCSetSineSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC�������Ҳ�����
		strKey = _T("SetADCSetSine");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCSetSine, pCommInfo->m_iSetADCSetSineSize, strValue);

		// ADC����ֹͣ���������С
		strKey = _T("SetADCStopSampleSize");
		pCommInfo->m_iSetADCStopSampleSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC����ֹͣ��������
		strKey = _T("SetADCStopSample");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCStopSample, pCommInfo->m_iSetADCStopSampleSize, strValue);

		// ADC���ô�TB��Դ��λ��С
		strKey = _T("SetADCOpenTBPowerLowSize");
		pCommInfo->m_iSetADCOpenTBPowerLowSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB��Դ��λ
		strKey = _T("SetADCOpenTBPowerLow");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCOpenTBPowerLow, pCommInfo->m_iSetADCOpenTBPowerLowSize, strValue);
	
		// ADC���ô�TB��Դ��λ��С
		strKey = _T("SetADCOpenTBPowerHighSize");
		pCommInfo->m_iSetADCOpenTBPowerHighSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB��Դ��λ
		strKey = _T("SetADCOpenTBPowerHigh");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCOpenTBPowerHigh, pCommInfo->m_iSetADCOpenTBPowerHighSize, strValue);
	
		// ADC���ô�TB���ص�λ��С
		strKey = _T("SetADCOpenSwitchTBLowSize");
		pCommInfo->m_iSetADCOpenSwitchTBLowSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB���ص�λ
		strKey = _T("SetADCOpenSwitchTBLow");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCOpenSwitchTBLow, pCommInfo->m_iSetADCOpenSwitchTBLowSize, strValue);
	
		// ADC���ô�TB���ظ�λ��С
		strKey = _T("SetADCOpenSwitchTBHighSize");
		pCommInfo->m_iSetADCOpenSwitchTBHighSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB���ظ�λ
		strKey = _T("SetADCOpenSwitchTBHigh");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCOpenSwitchTBHigh, pCommInfo->m_iSetADCOpenSwitchTBHighSize, strValue);
	
		// ADC���ö��Ĵ�����С
		strKey = _T("SetADCRegisterReadSize");
		pCommInfo->m_iSetADCRegisterReadSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ö��Ĵ���
		strKey = _T("SetADCRegisterRead");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCRegisterRead, pCommInfo->m_iSetADCRegisterReadSize, strValue);

		// ADC����д�Ĵ�����С
		strKey = _T("SetADCRegisterWriteSize");
		pCommInfo->m_iSetADCRegisterWriteSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC����д�Ĵ���
		strKey = _T("SetADCRegisterWrite");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCRegisterWrite, pCommInfo->m_iSetADCRegisterWriteSize, strValue);

		// ADC���ô�TB���ش�С
		strKey = _T("SetADCTBSwitchOpenSize");
		pCommInfo->m_iSetADCTBSwitchOpenSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC���ô�TB����
		strKey = _T("SetADCTBSwitchOpen");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCTBSwitchOpen, pCommInfo->m_iSetADCTBSwitchOpenSize, strValue);
		
		// ADC�������ô�С
		strKey = _T("SetADCSampleSize");
		pCommInfo->m_iSetADCSampleSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC��������
		strKey = _T("SetADCSample");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCSample, pCommInfo->m_iSetADCSampleSize, strValue);
		
		// ADC��������������С
		strKey = _T("SetADCReadContinuousSize");
		pCommInfo->m_iSetADCReadContinuousSize = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// ADC������������
		strKey = _T("SetADCReadContinuous");
		strValue = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		ParseCStringToArray(&pCommInfo->m_cpSetADCReadContinuous, pCommInfo->m_iSetADCReadContinuousSize, strValue);
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
void LoadLineServerAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo,
	string strXMLFilePath)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppIniXMLFile(pCommInfo, strXMLFilePath))
	{
		//����IP��ַ��������
		LoadIPSetupData(pCommInfo);
		//���ض˿���������
		LoadPortSetupData(pCommInfo);
		//����ADC������������
		LoadADCSetData(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppIniXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ��ʼ������ͨѶ��Ϣ�ṹ��
void OnInitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo, 
	string strXMLFilePath, m_oLogOutPutStruct* pLogOutPut)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	pCommInfo->m_pLogOutPut = pLogOutPut;
	LoadLineServerAppSetupData(pCommInfo, strXMLFilePath);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// �رճ��������ļ�
void CloseAppIniXMLFile(m_oInstrumentCommInfoStruct* pCommInfo)
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
	if (pCommInfo->m_cpSetADCSetSine != NULL)
	{
		delete[] pCommInfo->m_cpSetADCSetSine;
		pCommInfo->m_cpSetADCSetSine = NULL;
	}
	if (pCommInfo->m_cpSetADCStopSample != NULL)
	{
		delete[] pCommInfo->m_cpSetADCStopSample;
		pCommInfo->m_cpSetADCStopSample = NULL;
	}
	if (pCommInfo->m_cpSetADCOpenTBPowerLow != NULL)
	{
		delete[] pCommInfo->m_cpSetADCOpenTBPowerLow;
		pCommInfo->m_cpSetADCOpenTBPowerLow = NULL;
	}
	if (pCommInfo->m_cpSetADCOpenTBPowerHigh != NULL)
	{
		delete[] pCommInfo->m_cpSetADCOpenTBPowerHigh;
		pCommInfo->m_cpSetADCOpenTBPowerHigh = NULL;
	}
	if (pCommInfo->m_cpSetADCOpenSwitchTBLow != NULL)
	{
		delete[] pCommInfo->m_cpSetADCOpenSwitchTBLow;
		pCommInfo->m_cpSetADCOpenSwitchTBLow = NULL;
	}
	if (pCommInfo->m_cpSetADCOpenSwitchTBHigh != NULL)
	{
		delete[] pCommInfo->m_cpSetADCOpenSwitchTBHigh;
		pCommInfo->m_cpSetADCOpenSwitchTBHigh = NULL;
	}
	if (pCommInfo->m_cpSetADCRegisterRead != NULL)
	{
		delete[] pCommInfo->m_cpSetADCRegisterRead;
		pCommInfo->m_cpSetADCRegisterRead = NULL;
	}
	if (pCommInfo->m_cpSetADCRegisterWrite != NULL)
	{
		delete[] pCommInfo->m_cpSetADCRegisterWrite;
		pCommInfo->m_cpSetADCRegisterWrite = NULL;
	}
	if (pCommInfo->m_cpSetADCTBSwitchOpen != NULL)
	{
		delete[] pCommInfo->m_cpSetADCTBSwitchOpen;
		pCommInfo->m_cpSetADCTBSwitchOpen = NULL;
	}
	if (pCommInfo->m_cpSetADCSample != NULL)
	{
		delete[] pCommInfo->m_cpSetADCSample;
		pCommInfo->m_cpSetADCSample = NULL;
	}
	if (pCommInfo->m_cpSetADCReadContinuous != NULL)
	{
		delete[] pCommInfo->m_cpSetADCReadContinuous;
		pCommInfo->m_cpSetADCReadContinuous = NULL;
	}
	DeleteCriticalSection(&pCommInfo->m_oSecCommInfo);
	delete pCommInfo;
}

