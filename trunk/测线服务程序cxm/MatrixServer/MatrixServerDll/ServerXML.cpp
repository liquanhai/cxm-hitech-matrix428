#include "stdafx.h"
#include "MatrixServerDll.h"

// ��ʼ���������������Ϣ
void OnInitServerXMLSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample = NULL;
	pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous = NULL;
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}

// ����IP��ַ��������
void LoadServerIP(m_oInstrumentCommInfoStruct* pCommInfo)
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
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
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
		strConv = (CStringA)csSrcIP;
		pCommInfo->m_oXMLIPSetupData.m_uiSrcIP = inet_addr(strConv.c_str());
		// LCI��IP��ַ
		strKey = _T("IPLCI");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		strConv = (CStringA)csDstIP;
		pCommInfo->m_oXMLIPSetupData.m_uiAimIP = inet_addr(strConv.c_str());
		// ADC���ݷ��ص�ַ
		strKey = _T("IPForADCData");
		csDstIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		strConv = (CStringA)csDstIP;
		pCommInfo->m_oXMLIPSetupData.m_uiADCDataReturnAddr = inet_addr(strConv.c_str());
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
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ���ض˿���������
void LoadServerPort(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
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
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ADC������������
void LoadServerADCSet(m_oInstrumentCommInfoStruct* pCommInfo)
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
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
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
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}

// ����IP��ַ��������
void LoadServerIPSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strDllXMLFilePath))
	{
		// ����IP��ַ��������
		LoadServerIP(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ���ض˿���������
void LoadServerPortSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strDllXMLFilePath))
	{
		// ���ض˿���������
		LoadServerPort(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ADC������������
void LoadServerADCSetSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strDllXMLFilePath))
	{
		// ����ADC������������
		LoadServerADCSet(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ���ط�����������������
void LoadServerAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	// ����IP��ַ��������
	LoadServerIPSetupData(pCommInfo);
	// ���ض˿���������
	LoadServerPortSetupData(pCommInfo);
	// ����ADC������������
	LoadServerADCSetSetupData(pCommInfo);
}
// �ͷŷ���˲���������Ϣ�ṹ�建����
void OnFreeServerXMLSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCSetSine = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCStopSample = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterRead = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCRegisterWrite = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCSample = NULL;
	}
	if (pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous != NULL)
	{
		delete[] pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous;
		pCommInfo->m_oXMLADCSetupData.m_cpSetADCReadContinuous = NULL;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}