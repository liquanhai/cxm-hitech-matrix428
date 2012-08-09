#include "stdafx.h"
#include "MatrixServerDll.h"

// ��ʼ��ʩ���ͻ�����������Ϣ
void OnInitOptClientXMLSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
// 	pCommInfo->m_oLineSetupData.m_oSeisMonitor.m_pcAbsoluteSpread = NULL;
	// ����ʩ���ͻ�����Ϣ
	OnResetOptClientXMLSetupData(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// �����ڵ����
void OnResetOptSourceShotList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oSourceShotStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsSourceShot.begin(); 
		iter != pCommInfo->m_oOptSetupData.m_olsSourceShot.end(); iter++)
	{
		if (iter->m_pcComments != NULL)
		{
			delete[] iter->m_pcComments;
			iter->m_pcComments = NULL;
		}
	}
	pCommInfo->m_oOptSetupData.m_olsSourceShot.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Explo��Դ���Ͷ���
void OnResetOptExploList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oSourceExploStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsExploStruct.begin(); 
		iter != pCommInfo->m_oOptSetupData.m_olsExploStruct.end(); iter++)
	{
		if (iter->m_pcComments != NULL)
		{
			delete[] iter->m_pcComments;
			iter->m_pcComments = NULL;
		}
		if (iter->m_pcLabel != NULL)
		{
			delete[] iter->m_pcLabel;
			iter->m_pcLabel = NULL;
		}
	}
	pCommInfo->m_oOptSetupData.m_olsExploStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Vibro��Դ���Ͷ���
void OnResetOptVibroList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oSourceVibroStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsVibroStruct.begin(); 
		iter != pCommInfo->m_oOptSetupData.m_olsVibroStruct.end(); iter++)
	{
		if (iter->m_pcComments != NULL)
		{
			delete[] iter->m_pcComments;
			iter->m_pcComments = NULL;
		}
		if (iter->m_pcLabel != NULL)
		{
			delete[] iter->m_pcLabel;
			iter->m_pcLabel = NULL;
		}
	}
	pCommInfo->m_oOptSetupData.m_olsVibroStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ���ô�������Aux����
void OnResetOptProcessAuxList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oProcessAuxStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.begin(); 
		iter != pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.end(); iter++)
	{
		if (iter->m_pcAuxProcessing != NULL)
		{
			delete[] iter->m_pcAuxProcessing;
			iter->m_pcAuxProcessing = NULL;
		}
	}
	pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ���ô�������Acq����
void OnResetOptProcessAcqList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	pCommInfo->m_oOptSetupData.m_olsProcessAcqStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ���ô������Ͷ���
void OnResetOptProcessTypeList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oProcessTypeStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.begin(); 
		iter != pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.end(); iter++)
	{
		if (iter->m_pcLabel != NULL)
		{
			delete[] iter->m_pcLabel;
			iter->m_pcLabel = NULL;
		}
	}
	pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ע�Ͷ���
void OnResetOptCommentList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oOperationCommentStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsComment.begin(); 
		iter != pCommInfo->m_oOptSetupData.m_olsComment.end(); iter++)
	{
		if (iter->m_pcLabel != NULL)
		{
			delete[] iter->m_pcLabel;
			iter->m_pcLabel = NULL;
		}
		if (iter->m_pcComments != NULL)
		{
			delete[] iter->m_pcComments;
			iter->m_pcComments = NULL;
		}
	}
	pCommInfo->m_oOptSetupData.m_olsComment.clear();
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ʩ���ͻ�����Ϣ
void OnResetOptClientXMLSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	// �����ڵ����
	OnResetOptSourceShotList(pCommInfo);
	// ����Explo��Դ���Ͷ���
	OnResetOptExploList(pCommInfo);
	// ����Vibro��Դ���Ͷ���
	OnResetOptVibroList(pCommInfo);
	// ���ô�������Aux����
	OnResetOptProcessAuxList(pCommInfo);
	// ���ô�������Acq����
	OnResetOptProcessAcqList(pCommInfo);
	// ���ô������Ͷ���
	OnResetOptProcessTypeList(pCommInfo);
	// ����ע�Ͷ���
	OnResetOptCommentList(pCommInfo);
}
// ����Delay��������
void LoadDelay(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	string strConv = "";
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�Operation Delay������
		strKey = "OperationDelay";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = "VPSlipTime";
		pCommInfo->m_oOptSetupData.m_oDelay.m_iVPSlipTime = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		strKey = "VPTimeMax";
		pCommInfo->m_oOptSetupData.m_oDelay.m_iVPTimeMax = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		strKey = "VPTimeMin";
		pCommInfo->m_oOptSetupData.m_oDelay.m_iVPTimeMin = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		strKey = "AcqSlipTime";
		pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqSlipTime = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		strKey = "AcqTimeMax";
		pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqTimeMax = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		strKey = "AcqTimeMin";
		pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqTimeMin = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
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
// ����Delay��������
void LoadOptDelaySetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����Delay��������
		LoadDelay(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Delay��������
void SaveDelay(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	string strConv = "";
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�Delay������
		strKey = "OperationDelay";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = "VPSlipTime";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oDelay.m_iVPSlipTime;
		oElement.setAttribute(strKey, oVariant);
		strKey = "VPTimeMax";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oDelay.m_iVPTimeMax;
		oElement.setAttribute(strKey, oVariant);
		strKey = "VPTimeMin";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oDelay.m_iVPTimeMin;
		oElement.setAttribute(strKey, oVariant);
		strKey = "AcqSlipTime";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqSlipTime;
		oElement.setAttribute(strKey, oVariant);
		strKey = "AcqTimeMax";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqTimeMax;
		oElement.setAttribute(strKey, oVariant);
		strKey = "AcqTimeMin";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqTimeMin;
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
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Delay��������
void SaveDelaySetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����Delay��������
		SaveDelay(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Delay��������
void SetDelaySetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	unsigned int uiPos = 0;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	while(uiPos < uiSize)
	{
		memcpy(&pCommInfo->m_oOptSetupData.m_oDelay.m_iVPSlipTime, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oDelay.m_iVPTimeMax, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oDelay.m_iVPTimeMin, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqSlipTime, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqTimeMax, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqTimeMin, &pChar[uiPos], 4);
		uiPos += 4;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	SaveDelaySetupData(pCommInfo);
}
// ��ѯ Delay XML�ļ���Ϣ
void QueryDelaySetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oDelay.m_iVPSlipTime, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oDelay.m_iVPTimeMax, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oDelay.m_iVPTimeMin, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqSlipTime, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqTimeMax, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oDelay.m_iAcqTimeMin, 4);
	iPos += 4;
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}

// ����SourceShot��������
void LoadSourceShot(m_oSourceShotStruct* pSourceShotStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "VPStatus";
		pSourceShotStruct->m_uiVPStatus = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ShotID";
		pSourceShotStruct->m_uiShotID = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "BreakPoint";
		pSourceShotStruct->m_uiBreakPoint = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SourceLine";
		pSourceShotStruct->m_fSourceLine = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
		strKey = "SourceReceiver";
		pSourceShotStruct->m_fSourceReceiver = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
		strKey = "SpreadSFL";
		pSourceShotStruct->m_uiSFL = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SpreadSFN";
		pSourceShotStruct->m_uiSFN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SpreadType";
		pSourceShotStruct->m_uiSpreadType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SuperSpread";
		pSourceShotStruct->m_iSuperSpread = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
		strKey = "ProcessTypeID";
		pSourceShotStruct->m_uiProcessType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Comments";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pSourceShotStruct->m_usCommentsSize = (unsigned short)(strConv.size() + 1);
		pSourceShotStruct->m_pcComments = new char[pSourceShotStruct->m_usCommentsSize];
		memcpy(pSourceShotStruct->m_pcComments, strConv.c_str(), pSourceShotStruct->m_usCommentsSize);
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
// ����SourceShot���ö�������
void LoadSourceShotList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�VPTable������
		strKey = "VPTable";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�SourceShot����
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oSourceShotStruct oSourceShotStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadSourceShot(&oSourceShotStruct, &oElement);
			// ����SourceShot
			pCommInfo->m_oOptSetupData.m_olsSourceShot.push_back(oSourceShotStruct);
		}
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
// ����SourceShot��������
void LoadSourceShotSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ����SourceShot
	OnResetOptSourceShotList(pCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����SourceShot���ö�������
		LoadSourceShotList(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����SourceShot��������
void SaveSourceShot(m_oSourceShotStruct* pSourceShotStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	COleVariant oVariant;
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "VPStatus";
		oVariant = (long)pSourceShotStruct->m_uiVPStatus;
		pElement->setAttribute(strKey, oVariant);
		strKey = "ShotID";
		oVariant = (long)pSourceShotStruct->m_uiShotID;
		pElement->setAttribute(strKey, oVariant);
		strKey = "BreakPoint";
		oVariant = (long)pSourceShotStruct->m_uiBreakPoint;
		pElement->setAttribute(strKey, oVariant);
		strKey = "SourceLine";
		oVariant = (long)pSourceShotStruct->m_fSourceLine;
		pElement->setAttribute(strKey, oVariant);
		strKey = "SourceReceiver";
		oVariant = (long)pSourceShotStruct->m_fSourceReceiver;
		pElement->setAttribute(strKey, oVariant);
		strKey = "SpreadSFL";
		oVariant = (long)pSourceShotStruct->m_uiSFL;
		pElement->setAttribute(strKey, oVariant);
		strKey = "SpreadSFN";
		oVariant = (long)pSourceShotStruct->m_uiSFN;
		pElement->setAttribute(strKey, oVariant);
		strKey = "SpreadType";
		oVariant = (long)pSourceShotStruct->m_uiSpreadType;
		pElement->setAttribute(strKey, oVariant);
		strKey = "SuperSpread";
		oVariant = (long)pSourceShotStruct->m_iSuperSpread;
		pElement->setAttribute(strKey, oVariant);
		strKey = "ProcessTypeID";
		oVariant = (long)pSourceShotStruct->m_uiProcessType;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Comments";
		strConv = pSourceShotStruct->m_pcComments;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
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
// ����SourceShot���ö�������
void SaveSourceShotList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;
	unsigned int uiTabCount = 0;
	CString strTabChild = _T("");
	CString strTabParent = _T("");
	list<m_oSourceShotStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�SourceShot������
		strKey = "VPTable";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// �õ�Tab������
		strKey = "TabCount";
		uiTabCount = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElementParent, strKey);
		strTabChild = _T("\r\n");
		strTabParent = _T("\r\n");
		for(unsigned int i = 0; i < uiTabCount; i++)
		{
			strTabChild += _T("\t");
			if (i < (uiTabCount - 1))
			{
				strTabParent += _T("\t");
			}
		}
		// ����SourceShot����
		strKey = "Count";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_olsSourceShot.size();
		oElementParent.setAttribute(strKey, oVariant);
		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		for (iter = pCommInfo->m_oOptSetupData.m_olsSourceShot.begin();
			iter != pCommInfo->m_oOptSetupData.m_olsSourceShot.end(); iter++)
		{
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabChild);
			oElementParent.appendChild(lpDispatch);
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);
			SaveSourceShot(&(*iter), &oElementChild);
			oElementParent.appendChild(lpDispatch);		
		}
		lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabParent);
		oElementParent.appendChild(lpDispatch);
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
// ����SourceShot��������
void SaveSourceShotSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����SourceShot���ö�������
		SaveSourceShotList(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����SourceShot��������
void SetSourceShotSetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	m_oSourceShotStruct oSourceShotStruct;
	unsigned int uiPos = 0;
	OnResetOptSourceShotList(pCommInfo);
	while(uiPos < uiSize)
	{
		memcpy(&oSourceShotStruct.m_uiVPStatus, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_uiShotID, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_uiBreakPoint, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_fSourceLine, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_fSourceReceiver, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_uiSFL, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_uiSFN, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_uiSpreadType, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_iSuperSpread, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_uiProcessType, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceShotStruct.m_usCommentsSize, &pChar[uiPos], 2);
		uiPos += 2;
		oSourceShotStruct.m_pcComments = new char[oSourceShotStruct.m_usCommentsSize];
		memcpy(&oSourceShotStruct.m_pcComments, &pChar[uiPos], oSourceShotStruct.m_usCommentsSize);
		uiPos += oSourceShotStruct.m_usCommentsSize;
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		pCommInfo->m_oOptSetupData.m_olsSourceShot.push_back(oSourceShotStruct);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	}
	SaveSourceShotSetupData(pCommInfo);
}
// ��ѯ SourceShot XML�ļ���Ϣ
void QuerySourceShotSetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oSourceShotStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsSourceShot.begin();
		iter != pCommInfo->m_oOptSetupData.m_olsSourceShot.end(); iter++)
	{
		memcpy(&cProcBuf[iPos], &iter->m_uiVPStatus, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiShotID, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiBreakPoint, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_fSourceLine, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_fSourceReceiver, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiSFL, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiSFN, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiSpreadType, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_iSuperSpread, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiProcessType, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_usCommentsSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcComments, iter->m_usCommentsSize);
		iPos += iter->m_usCommentsSize;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}

// ����Explo��������
void LoadExplo(m_oSourceExploStruct* pSourceExploStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "SourceStatus";
		pSourceExploStruct->m_uiSourceStatus = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SourceNb";
		pSourceExploStruct->m_uiSourceNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Label";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pSourceExploStruct->m_usLabelSize = (unsigned short)(strConv.size() + 1);
		pSourceExploStruct->m_pcLabel = new char[pSourceExploStruct->m_usLabelSize];
		memcpy(pSourceExploStruct->m_pcLabel, strConv.c_str(), pSourceExploStruct->m_usLabelSize);
		strKey = "ShooterSN";
		pSourceExploStruct->m_uiShooterSN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "IncrNb";
		pSourceExploStruct->m_iIncrNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
		strKey = "Comments";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pSourceExploStruct->m_usCommentsSize = (unsigned short)(strConv.size() + 1);
		pSourceExploStruct->m_pcComments = new char[pSourceExploStruct->m_usCommentsSize];
		memcpy(pSourceExploStruct->m_pcComments, strConv.c_str(), pSourceExploStruct->m_usCommentsSize);
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
// ����Explo���ö�������
void LoadExploList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�Explo������
		strKey = "SourceExplo";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�Explo����
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oSourceExploStruct oSourceExploStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadExplo(&oSourceExploStruct, &oElement);
			// ����Explo
			pCommInfo->m_oOptSetupData.m_olsExploStruct.push_back(oSourceExploStruct);
		}
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
// ����Explo��������
void LoadExploSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ����Explo
	OnResetOptExploList(pCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����Explo���ö�������
		LoadExploList(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Explo��������
void SaveExplo(m_oSourceExploStruct* pSourceExploStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	COleVariant oVariant;
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "SourceStatus";
		oVariant = (long)pSourceExploStruct->m_uiSourceStatus;
		pElement->setAttribute(strKey, oVariant);
		strKey = "SourceNb";
		oVariant = (long)pSourceExploStruct->m_uiSourceNb;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Label";
		strConv = pSourceExploStruct->m_pcLabel;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
		strKey = "ShooterSN";
		oVariant = (long)pSourceExploStruct->m_uiShooterSN;
		pElement->setAttribute(strKey, oVariant);
		strKey = "IncrNb";
		oVariant = (long)pSourceExploStruct->m_iIncrNb;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Comments";
		strConv = pSourceExploStruct->m_pcComments;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
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
// ����Explo���ö�������
void SaveExploList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;
	unsigned int uiTabCount = 0;
	CString strTabChild = _T("");
	CString strTabParent = _T("");
	list<m_oSourceExploStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�Explo������
		strKey = "SourceExplo";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// �õ�Tab������
		strKey = "TabCount";
		uiTabCount = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElementParent, strKey);
		strTabChild = _T("\r\n");
		strTabParent = _T("\r\n");
		for(unsigned int i = 0; i < uiTabCount; i++)
		{
			strTabChild += _T("\t");
			if (i < (uiTabCount - 1))
			{
				strTabParent += _T("\t");
			}
		}
		// ����Explo����
		strKey = "Count";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_olsExploStruct.size();
		oElementParent.setAttribute(strKey, oVariant);
		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		for (iter = pCommInfo->m_oOptSetupData.m_olsExploStruct.begin();
			iter != pCommInfo->m_oOptSetupData.m_olsExploStruct.end(); iter++)
		{
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabChild);
			oElementParent.appendChild(lpDispatch);
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);
			SaveExplo(&(*iter), &oElementChild);
			oElementParent.appendChild(lpDispatch);		
		}
		lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabParent);
		oElementParent.appendChild(lpDispatch);
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
// ����Explo��������
void SaveExploSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����Explo���ö�������
		SaveExploList(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Explo��������
void SetExploSetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	m_oSourceExploStruct oSourceExploStruct;
	unsigned int uiPos = 0;
	OnResetOptExploList(pCommInfo);
	while(uiPos < uiSize)
	{
		memcpy(&oSourceExploStruct.m_uiSourceStatus, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceExploStruct.m_uiSourceNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceExploStruct.m_usLabelSize, &pChar[uiPos], 2);
		uiPos += 2;
		oSourceExploStruct.m_pcLabel = new char[oSourceExploStruct.m_usLabelSize];
		memcpy(&oSourceExploStruct.m_pcLabel, &pChar[uiPos], oSourceExploStruct.m_usLabelSize);
		uiPos += oSourceExploStruct.m_usLabelSize;
		memcpy(&oSourceExploStruct.m_uiShooterSN, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceExploStruct.m_iIncrNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceExploStruct.m_usCommentsSize, &pChar[uiPos], 2);
		uiPos += 2;
		oSourceExploStruct.m_pcComments = new char[oSourceExploStruct.m_usCommentsSize];
		memcpy(&oSourceExploStruct.m_pcComments, &pChar[uiPos], oSourceExploStruct.m_usCommentsSize);
		uiPos += oSourceExploStruct.m_usCommentsSize;
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		pCommInfo->m_oOptSetupData.m_olsExploStruct.push_back(oSourceExploStruct);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	}
	SaveExploSetupData(pCommInfo);
}
// ��ѯ Explo XML�ļ���Ϣ
void QueryExploSetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oSourceExploStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsExploStruct.begin();
		iter != pCommInfo->m_oOptSetupData.m_olsExploStruct.end(); iter++)
	{
		memcpy(&cProcBuf[iPos], &iter->m_uiSourceStatus, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiSourceNb, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
		memcpy(&cProcBuf[iPos], &iter->m_uiShooterSN, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_iIncrNb, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_usCommentsSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcComments, iter->m_usCommentsSize);
		iPos += iter->m_usCommentsSize;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Vibro��������
void LoadVibro(m_oSourceVibroStruct* pSourceVibroStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "SourceStatus";
		pSourceVibroStruct->m_uiSourceStatus = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "SourceNb";
		pSourceVibroStruct->m_uiSourceNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Label";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pSourceVibroStruct->m_usLabelSize = (unsigned short)(strConv.size() + 1);
		pSourceVibroStruct->m_pcLabel = new char[pSourceVibroStruct->m_usLabelSize];
		memcpy(pSourceVibroStruct->m_pcLabel, strConv.c_str(), pSourceVibroStruct->m_usLabelSize);
		strKey = "FleetNb";
		pSourceVibroStruct->m_uiFleetNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Moving";
		pSourceVibroStruct->m_uiMoving = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Step";
		pSourceVibroStruct->m_iStep = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
		strKey = "WorkByAcq";
		pSourceVibroStruct->m_uiWorkByAcq = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ClusterNb";
		pSourceVibroStruct->m_uiCluster = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Comments";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pSourceVibroStruct->m_usCommentsSize = (unsigned short)(strConv.size() + 1);
		pSourceVibroStruct->m_pcComments = new char[pSourceVibroStruct->m_usCommentsSize];
		memcpy(pSourceVibroStruct->m_pcComments, strConv.c_str(), pSourceVibroStruct->m_usCommentsSize);
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
// ����Vibro���ö�������
void LoadVibroList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�Vibro������
		strKey = "SourceVibro";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�Vibro����
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oSourceVibroStruct oSourceVibroStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadVibro(&oSourceVibroStruct, &oElement);
			// ����Vibro
			pCommInfo->m_oOptSetupData.m_olsVibroStruct.push_back(oSourceVibroStruct);
		}
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
// ����Vibro��������
void LoadVibroSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ����Vibro
	OnResetOptVibroList(pCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����Vibro���ö�������
		LoadVibroList(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Vibro��������
void SaveVibro(m_oSourceVibroStruct* pSourceVibroStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	COleVariant oVariant;
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "SourceStatus";
		oVariant = (long)pSourceVibroStruct->m_uiSourceStatus;
		pElement->setAttribute(strKey, oVariant);
		strKey = "SourceNb";
		oVariant = (long)pSourceVibroStruct->m_uiSourceNb;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Label";
		strConv = pSourceVibroStruct->m_pcLabel;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
		strKey = "FleetNb";
		oVariant = (long)pSourceVibroStruct->m_uiFleetNb;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Moving";
		oVariant = (long)pSourceVibroStruct->m_uiMoving;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Step";
		oVariant = (long)pSourceVibroStruct->m_iStep;
		pElement->setAttribute(strKey, oVariant);
		strKey = "WorkByAcq";
		oVariant = (long)pSourceVibroStruct->m_uiWorkByAcq;
		pElement->setAttribute(strKey, oVariant);
		strKey = "ClusterNb";
		oVariant = (long)pSourceVibroStruct->m_uiCluster;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Comments";
		strConv = pSourceVibroStruct->m_pcComments;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
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
// ����Vibro���ö�������
void SaveVibroList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;
	unsigned int uiTabCount = 0;
	CString strTabChild = _T("");
	CString strTabParent = _T("");
	list<m_oSourceVibroStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�Vibro������
		strKey = "SourceVibro";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// �õ�Tab������
		strKey = "TabCount";
		uiTabCount = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElementParent, strKey);
		strTabChild = _T("\r\n");
		strTabParent = _T("\r\n");
		for(unsigned int i = 0; i < uiTabCount; i++)
		{
			strTabChild += _T("\t");
			if (i < (uiTabCount - 1))
			{
				strTabParent += _T("\t");
			}
		}
		// ����Explo����
		strKey = "Count";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_olsVibroStruct.size();
		oElementParent.setAttribute(strKey, oVariant);
		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		for (iter = pCommInfo->m_oOptSetupData.m_olsVibroStruct.begin();
			iter != pCommInfo->m_oOptSetupData.m_olsVibroStruct.end(); iter++)
		{
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabChild);
			oElementParent.appendChild(lpDispatch);
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);
			SaveVibro(&(*iter), &oElementChild);
			oElementParent.appendChild(lpDispatch);		
		}
		lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabParent);
		oElementParent.appendChild(lpDispatch);
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
// ����Vibro��������
void SaveVibroSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����Vibro���ö�������
		SaveVibroList(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����Vibro��������
void SetVibroSetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	m_oSourceVibroStruct oSourceVibroStruct;
	unsigned int uiPos = 0;
	OnResetOptVibroList(pCommInfo);
	while(uiPos < uiSize)
	{
		memcpy(&oSourceVibroStruct.m_uiSourceStatus, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceVibroStruct.m_uiSourceNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceVibroStruct.m_usLabelSize, &pChar[uiPos], 2);
		uiPos += 2;
		oSourceVibroStruct.m_pcLabel = new char[oSourceVibroStruct.m_usLabelSize];
		memcpy(&oSourceVibroStruct.m_pcLabel, &pChar[uiPos], oSourceVibroStruct.m_usLabelSize);
		uiPos += oSourceVibroStruct.m_usLabelSize;
		memcpy(&oSourceVibroStruct.m_uiFleetNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceVibroStruct.m_uiMoving, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceVibroStruct.m_iStep, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceVibroStruct.m_uiWorkByAcq, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceVibroStruct.m_uiCluster, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oSourceVibroStruct.m_usCommentsSize, &pChar[uiPos], 2);
		uiPos += 2;
		oSourceVibroStruct.m_pcComments = new char[oSourceVibroStruct.m_usCommentsSize];
		memcpy(&oSourceVibroStruct.m_pcComments, &pChar[uiPos], oSourceVibroStruct.m_usCommentsSize);
		uiPos += oSourceVibroStruct.m_usCommentsSize;
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		pCommInfo->m_oOptSetupData.m_olsVibroStruct.push_back(oSourceVibroStruct);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	}
	SaveVibroSetupData(pCommInfo);
}
// ��ѯ Vibro XML�ļ���Ϣ
void QueryVibroSetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oSourceVibroStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsVibroStruct.begin();
		iter != pCommInfo->m_oOptSetupData.m_olsVibroStruct.end(); iter++)
	{
		memcpy(&cProcBuf[iPos], &iter->m_uiSourceStatus, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiSourceNb, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
		memcpy(&cProcBuf[iPos], &iter->m_uiFleetNb, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiMoving, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_iStep, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiWorkByAcq, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiCluster, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_usCommentsSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcComments, iter->m_usCommentsSize);
		iPos += iter->m_usCommentsSize;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}

// ����ProcessRecord��������
void LoadProcessRecord(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	string strConv = "";
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�Operation ProcessRecord������
		strKey = "ProcessRecord";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = "Plug";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPlug = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "BoxType";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiBoxType = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "SerialNb";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiSN = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "RecordLength";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRecordLength = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "RefractionDelay";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRefractionDelay = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "TBWindow";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiTBWindow = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "ListeningTime";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiListeningTime = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "PeakTime";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPeakTime = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "Raw";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRaw = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "PreStack";
		pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPreStack = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
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
// ����ProcessRecord��������
void LoadOptProcessRecordSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessRecord��������
		LoadProcessRecord(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessRecord��������
void SaveProcessRecord(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	string strConv = "";
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessRecord������
		strKey = "ProcessRecord";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		strKey = "Plug";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPlug;
		oElement.setAttribute(strKey, oVariant);
		strKey = "BoxType";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiBoxType;
		oElement.setAttribute(strKey, oVariant);
		strKey = "SerialNb";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiSN;
		oElement.setAttribute(strKey, oVariant);
		strKey = "RecordLength";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRecordLength;
		oElement.setAttribute(strKey, oVariant);
		strKey = "RefractionDelay";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRefractionDelay;
		oElement.setAttribute(strKey, oVariant);
		strKey = "TBWindow";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiTBWindow;
		oElement.setAttribute(strKey, oVariant);
		strKey = "ListeningTime";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiListeningTime;
		oElement.setAttribute(strKey, oVariant);
		strKey = "PeakTime";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPeakTime;
		oElement.setAttribute(strKey, oVariant);
		strKey = "Raw";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRaw;
		oElement.setAttribute(strKey, oVariant);
		strKey = "PreStack";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPreStack;
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
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessRecord��������
void SaveProcessRecordSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessRecord��������
		SaveProcessRecord(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessRecord��������
void SetProcessRecordSetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	unsigned int uiPos = 0;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	while(uiPos < uiSize)
	{
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPlug, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiBoxType, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiSN, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRecordLength, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRefractionDelay, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiTBWindow, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiListeningTime, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPeakTime, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRaw, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPreStack, &pChar[uiPos], 4);
		uiPos += 4;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	SaveProcessRecordSetupData(pCommInfo);
}
// ��ѯ ProcessRecord XML�ļ���Ϣ
void QueryProcessRecordSetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPlug, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiBoxType, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiSN, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRecordLength, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRefractionDelay, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiTBWindow, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiListeningTime, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPeakTime, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiRaw, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_oProcessRecord.m_uiPreStack, 4);
	iPos += 4;
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}

// ����ProcessAux��������
void LoadProcessAux(m_oProcessAuxStruct* pProcessAuxStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "AuxNb";
		pProcessAuxStruct->m_uiAuxNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "AuxProcessing";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pProcessAuxStruct->m_usAuxProcessingSize = (unsigned short)(strConv.size() + 1);
		pProcessAuxStruct->m_pcAuxProcessing = new char[pProcessAuxStruct->m_usAuxProcessingSize];
		memcpy(pProcessAuxStruct->m_pcAuxProcessing, strConv.c_str(), pProcessAuxStruct->m_usAuxProcessingSize);
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
// ����ProcessAux���ö�������
void LoadProcessAuxList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessAux������
		strKey = "Auxiliaries";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�ProcessAux����
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "AppendAuxesFromDsd";
		pCommInfo->m_oOptSetupData.m_uiAppendAux = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		strKey = "CorrelWith";
		pCommInfo->m_oOptSetupData.m_iCorrelWith = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oProcessAuxStruct oProcessAuxStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadProcessAux(&oProcessAuxStruct, &oElement);
			// ����ProcessAux
			pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.push_back(oProcessAuxStruct);
		}
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
// ����ProcessAux��������
void LoadProcessAuxSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ����ProcessAux
	OnResetOptProcessAuxList(pCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessAux���ö�������
		LoadProcessAuxList(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessAux��������
void SaveProcessAux(m_oProcessAuxStruct* pProcessAuxStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	COleVariant oVariant;
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "AuxNb";
		oVariant = (long)pProcessAuxStruct->m_uiAuxNb;
		pElement->setAttribute(strKey, oVariant);
		strKey = "AuxProcessing";
		strConv = pProcessAuxStruct->m_pcAuxProcessing;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
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
// ����ProcessAux���ö�������
void SaveProcessAuxList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;
	unsigned int uiTabCount = 0;
	CString strTabChild = _T("");
	CString strTabParent = _T("");
	list<m_oProcessAuxStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessAux������
		strKey = "Auxiliaries";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// �õ�Tab������
		strKey = "TabCount";
		uiTabCount = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElementParent, strKey);
		strTabChild = _T("\r\n");
		strTabParent = _T("\r\n");
		for(unsigned int i = 0; i < uiTabCount; i++)
		{
			strTabChild += _T("\t");
			if (i < (uiTabCount - 1))
			{
				strTabParent += _T("\t");
			}
		}
		// ����ProcessAux����
		strKey = "Count";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.size();
		oElementParent.setAttribute(strKey, oVariant);
		strKey = "AppendAuxesFromDsd";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_uiAppendAux;
		oElementParent.setAttribute(strKey, oVariant);
		strKey = "CorrelWith";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_iCorrelWith;
		oElementParent.setAttribute(strKey, oVariant);
		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		for (iter = pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.begin();
			iter != pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.end(); iter++)
		{
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabChild);
			oElementParent.appendChild(lpDispatch);
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);
			SaveProcessAux(&(*iter), &oElementChild);
			oElementParent.appendChild(lpDispatch);		
		}
		lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabParent);
		oElementParent.appendChild(lpDispatch);
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
// ����ProcessAux��������
void SaveProcessAuxSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessAux���ö�������
		SaveProcessAuxList(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessAux��������
void SetProcessAuxSetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	m_oProcessAuxStruct oProcessAuxStruct;
	unsigned int uiPos = 0;
	OnResetOptProcessAuxList(pCommInfo);
	memcpy(&pCommInfo->m_oOptSetupData.m_uiAppendAux, &pChar[uiPos], 4);
	uiPos += 4;
	memcpy(&pCommInfo->m_oOptSetupData.m_iCorrelWith, &pChar[uiPos], 4);
	uiPos += 4;
	while(uiPos < uiSize)
	{
		memcpy(&oProcessAuxStruct.m_uiAuxNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oProcessAuxStruct.m_usAuxProcessingSize, &pChar[uiPos], 2);
		uiPos += 2;
		oProcessAuxStruct.m_pcAuxProcessing = new char[oProcessAuxStruct.m_usAuxProcessingSize];
		memcpy(&oProcessAuxStruct.m_pcAuxProcessing, &pChar[uiPos], oProcessAuxStruct.m_usAuxProcessingSize);
		uiPos += oProcessAuxStruct.m_usAuxProcessingSize;
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.push_back(oProcessAuxStruct);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	}
	SaveProcessAuxSetupData(pCommInfo);
}
// ��ѯ ProcessAux XML�ļ���Ϣ
void QueryProcessAuxSetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oProcessAuxStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_uiAppendAux, 4);
	iPos += 4;
	memcpy(&cProcBuf[iPos], &pCommInfo->m_oOptSetupData.m_iCorrelWith, 4);
	iPos += 4;
	for (iter = pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.begin();
		iter != pCommInfo->m_oOptSetupData.m_olsProcessAuxStruct.end(); iter++)
	{
		memcpy(&cProcBuf[iPos], &iter->m_uiAuxNb, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_usAuxProcessingSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcAuxProcessing, iter->m_usAuxProcessingSize);
		iPos += iter->m_usAuxProcessingSize;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessAcq��������
void LoadProcessAcq(m_oProcessAcqStruct* pProcessAcqStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "AcqStatus";
		pProcessAcqStruct->m_uiAcqStatus = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "AcqNb";
		pProcessAcqStruct->m_uiAcqNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "AcqType";
		pProcessAcqStruct->m_uiAcqType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "AcqSignStack";
		pProcessAcqStruct->m_uiSignStack = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "AcqOutPut";
		pProcessAcqStruct->m_uiOutPut = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
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
// ����ProcessAcq���ö�������
void LoadProcessAcqList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessAcq������
		strKey = "Acquisition";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�ProcessAcq����
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oProcessAcqStruct oProcessAcqStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadProcessAcq(&oProcessAcqStruct, &oElement);
			// ����ProcessAux
			pCommInfo->m_oOptSetupData.m_olsProcessAcqStruct.push_back(oProcessAcqStruct);
		}
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
// ����ProcessAcq��������
void LoadProcessAcqSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ����ProcessAcq
	OnResetOptProcessAcqList(pCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessAcq���ö�������
		LoadProcessAcqList(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessAcq��������
void SaveProcessAcq(m_oProcessAcqStruct* pProcessAcqStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	COleVariant oVariant;
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "AcqStatus";
		oVariant = (long)pProcessAcqStruct->m_uiAcqStatus;
		pElement->setAttribute(strKey, oVariant);
		strKey = "AcqNb";
		oVariant = (long)pProcessAcqStruct->m_uiAcqNb;
		pElement->setAttribute(strKey, oVariant);
		strKey = "AcqType";
		oVariant = (long)pProcessAcqStruct->m_uiAcqType;
		pElement->setAttribute(strKey, oVariant);
		strKey = "AcqSignStack";
		oVariant = (long)pProcessAcqStruct->m_uiSignStack;
		pElement->setAttribute(strKey, oVariant);
		strKey = "AcqOutPut";
		oVariant = (long)pProcessAcqStruct->m_uiOutPut;
		pElement->setAttribute(strKey, oVariant);
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
// ����ProcessAcq���ö�������
void SaveProcessAcqList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;
	unsigned int uiTabCount = 0;
	CString strTabChild = _T("");
	CString strTabParent = _T("");
	list<m_oProcessAcqStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessAcq������
		strKey = "Acquisition";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// �õ�Tab������
		strKey = "TabCount";
		uiTabCount = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElementParent, strKey);
		strTabChild = _T("\r\n");
		strTabParent = _T("\r\n");
		for(unsigned int i = 0; i < uiTabCount; i++)
		{
			strTabChild += _T("\t");
			if (i < (uiTabCount - 1))
			{
				strTabParent += _T("\t");
			}
		}
		// ����ProcessAcq����
		strKey = "Count";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_olsProcessAcqStruct.size();
		oElementParent.setAttribute(strKey, oVariant);
		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		for (iter = pCommInfo->m_oOptSetupData.m_olsProcessAcqStruct.begin();
			iter != pCommInfo->m_oOptSetupData.m_olsProcessAcqStruct.end(); iter++)
		{
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabChild);
			oElementParent.appendChild(lpDispatch);
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);
			SaveProcessAcq(&(*iter), &oElementChild);
			oElementParent.appendChild(lpDispatch);		
		}
		lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabParent);
		oElementParent.appendChild(lpDispatch);
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
// ����ProcessAcq��������
void SaveProcessAcqSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessAcq���ö�������
		SaveProcessAcqList(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessAcq��������
void SetProcessAcqSetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	m_oProcessAcqStruct oProcessAcqStruct;
	unsigned int uiPos = 0;
	OnResetOptProcessAcqList(pCommInfo);
	while(uiPos < uiSize)
	{
		memcpy(&oProcessAcqStruct.m_uiAcqStatus, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oProcessAcqStruct.m_uiAcqNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oProcessAcqStruct.m_uiAcqType, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oProcessAcqStruct.m_uiSignStack, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oProcessAcqStruct.m_uiOutPut, &pChar[uiPos], 4);
		uiPos += 4;
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		pCommInfo->m_oOptSetupData.m_olsProcessAcqStruct.push_back(oProcessAcqStruct);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	}
	SaveProcessAcqSetupData(pCommInfo);
}
// ��ѯ ProcessAcq XML�ļ���Ϣ
void QueryProcessAcqSetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oProcessAcqStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsProcessAcqStruct.begin();
		iter != pCommInfo->m_oOptSetupData.m_olsProcessAcqStruct.end(); iter++)
	{
		memcpy(&cProcBuf[iPos], &iter->m_uiAcqStatus, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiAcqNb, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiAcqType, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiSignStack, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_uiOutPut, 4);
		iPos += 4;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessType��������
void LoadProcessType(m_oProcessTypeStruct* pProcessTypeStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "ProNb";
		pProcessTypeStruct->m_uiProNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "ProLabel";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pProcessTypeStruct->m_usLabelSize = (unsigned short)(strConv.size() + 1);
		pProcessTypeStruct->m_pcLabel = new char[pProcessTypeStruct->m_usLabelSize];
		memcpy(pProcessTypeStruct->m_pcLabel, strConv.c_str(), pProcessTypeStruct->m_usLabelSize);
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
// ����ProcessType���ö�������
void LoadProcessTypeList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessType������
		strKey = "ProcessType";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�ProcessType����
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oProcessTypeStruct oProcessTypeStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadProcessType(&oProcessTypeStruct, &oElement);
			// ����ProcessAux
			pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.push_back(oProcessTypeStruct);
		}
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
// ����ProcessType��������
void LoadProcessTypeSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ����ProcessType
	OnResetOptProcessTypeList(pCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessType���ö�������
		LoadProcessTypeList(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessType��������
void SaveProcessType(m_oProcessTypeStruct* pProcessTypeStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	COleVariant oVariant;
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "ProNb";
		oVariant = (long)pProcessTypeStruct->m_uiProNb;
		pElement->setAttribute(strKey, oVariant);
		strKey = "ProLabel";
		strConv = pProcessTypeStruct->m_pcLabel;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
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
// ����ProcessType���ö�������
void SaveProcessTypeList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;
	unsigned int uiTabCount = 0;
	CString strTabChild = _T("");
	CString strTabParent = _T("");
	list<m_oProcessTypeStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessType������
		strKey = "ProcessType";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// �õ�Tab������
		strKey = "TabCount";
		uiTabCount = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElementParent, strKey);
		strTabChild = _T("\r\n");
		strTabParent = _T("\r\n");
		for(unsigned int i = 0; i < uiTabCount; i++)
		{
			strTabChild += _T("\t");
			if (i < (uiTabCount - 1))
			{
				strTabParent += _T("\t");
			}
		}
		// ����ProcessType����
		strKey = "Count";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.size();
		oElementParent.setAttribute(strKey, oVariant);
		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		for (iter = pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.begin();
			iter != pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.end(); iter++)
		{
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabChild);
			oElementParent.appendChild(lpDispatch);
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);
			SaveProcessType(&(*iter), &oElementChild);
			oElementParent.appendChild(lpDispatch);		
		}
		lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabParent);
		oElementParent.appendChild(lpDispatch);
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
// ����ProcessType��������
void SaveProcessTypeSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessType���ö�������
		SaveProcessTypeList(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessType��������
void SetProcessTypeSetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	m_oProcessTypeStruct oProcessTypeStruct;
	unsigned int uiPos = 0;
	OnResetOptProcessTypeList(pCommInfo);
	while(uiPos < uiSize)
	{
		memcpy(&oProcessTypeStruct.m_uiProNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oProcessTypeStruct.m_usLabelSize, &pChar[uiPos], 2);
		uiPos += 2;
		memcpy(&oProcessTypeStruct.m_pcLabel, &pChar[uiPos], oProcessTypeStruct.m_usLabelSize);
		uiPos += oProcessTypeStruct.m_usLabelSize;
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.push_back(oProcessTypeStruct);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	}
	SaveProcessTypeSetupData(pCommInfo);
}
// ��ѯ ProcessType XML�ļ���Ϣ
void QueryProcessTypeSetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oProcessTypeStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.begin();
		iter != pCommInfo->m_oOptSetupData.m_olsProcessTypeStruct.end(); iter++)
	{
		memcpy(&cProcBuf[iPos], &iter->m_uiProNb, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessComments��������
void LoadProcessComments(m_oOperationCommentStruct* pCommentsStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "Nb";
		pCommentsStruct->m_uiNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
		strKey = "Label";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pCommentsStruct->m_usLabelSize = (unsigned short)(strConv.size() + 1);
		pCommentsStruct->m_pcLabel = new char[pCommentsStruct->m_usLabelSize];
		memcpy(pCommentsStruct->m_pcLabel, strConv.c_str(), pCommentsStruct->m_usLabelSize);
		strKey = "Comments";
		str = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strConv = (CStringA)str;
		pCommentsStruct->m_usCommentsSize = (unsigned short)(strConv.size() + 1);
		pCommentsStruct->m_pcComments = new char[pCommentsStruct->m_usCommentsSize];
		memcpy(pCommentsStruct->m_pcComments, strConv.c_str(), pCommentsStruct->m_usCommentsSize);
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
// ����ProcessComments���ö�������
void LoadProcessCommentsList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int uiCountAll;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessComments������
		strKey = "OperationComment";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�ProcessComments����
		strKey = "Count";
		uiCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		m_oOperationCommentStruct oOperationCommentStruct;
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			LoadProcessComments(&oOperationCommentStruct, &oElement);
			// ����ProcessComments
			pCommInfo->m_oOptSetupData.m_olsComment.push_back(oOperationCommentStruct);
		}
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
// ����ProcessComments��������
void LoadProcessCommentsSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// ����ProcessComments
	OnResetOptCommentList(pCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessComments���ö�������
		LoadProcessCommentsList(pCommInfo);
	}
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessComments��������
void SaveProcessComments(m_oOperationCommentStruct* pCommentsStruct,CXMLDOMElement* pElement)
{
	CString strKey = _T("");
	COleVariant oVariant;
	CString str = _T("");
	string strConv = "";
	try
	{
		strKey = "Nb";
		oVariant = (long)pCommentsStruct->m_uiNb;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Label";
		strConv = pCommentsStruct->m_pcLabel;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
		strKey = "Comments";
		strConv = pCommentsStruct->m_pcComments;
		str = strConv.c_str();
		oVariant = str;
		pElement->setAttribute(strKey, oVariant);
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
// ����ProcessComments���ö�������
void SaveProcessCommentsList(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;
	unsigned int uiTabCount = 0;
	CString strTabChild = _T("");
	CString strTabParent = _T("");
	list<m_oOperationCommentStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	try
	{
		// �ҵ�ProcessComments������
		strKey = "OperationComment";
		lpDispatch = pCommInfo->m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// �õ�Tab������
		strKey = "TabCount";
		uiTabCount = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElementParent, strKey);
		strTabChild = _T("\r\n");
		strTabParent = _T("\r\n");
		for(unsigned int i = 0; i < uiTabCount; i++)
		{
			strTabChild += _T("\t");
			if (i < (uiTabCount - 1))
			{
				strTabParent += _T("\t");
			}
		}
		// ����ProcessComments����
		strKey = "Count";
		oVariant = (long)pCommInfo->m_oOptSetupData.m_olsComment.size();
		oElementParent.setAttribute(strKey, oVariant);
		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		for (iter = pCommInfo->m_oOptSetupData.m_olsComment.begin();
			iter != pCommInfo->m_oOptSetupData.m_olsComment.end(); iter++)
		{
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabChild);
			oElementParent.appendChild(lpDispatch);
			lpDispatch = pCommInfo->m_oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);
			SaveProcessComments(&(*iter), &oElementChild);
			oElementParent.appendChild(lpDispatch);		
		}
		lpDispatch = pCommInfo->m_oXMLDOMDocument.createTextNode(strTabParent);
		oElementParent.appendChild(lpDispatch);
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
// ����ProcessComments��������
void SaveProcessCommentsSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	COleVariant oVariant;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	// �򿪳��������ļ�
	if (TRUE == OpenAppXMLFile(pCommInfo, pCommInfo->m_strOptXMLFilePath))
	{
		// ����ProcessComments���ö�������
		SaveProcessCommentsList(pCommInfo);
	}
	oVariant = (CString)(pCommInfo->m_strOptXMLFilePath.c_str());
	pCommInfo->m_oXMLDOMDocument.save(oVariant);
	// �رճ��������ļ�
	CloseAppXMLFile(pCommInfo);
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}
// ����ProcessComments��������
void SetProcessCommentsSetupData(char* pChar, unsigned int uiSize, m_oInstrumentCommInfoStruct* pCommInfo)
{
	m_oOperationCommentStruct oCommentStruct;
	unsigned int uiPos = 0;
	OnResetOptCommentList(pCommInfo);
	while(uiPos < uiSize)
	{
		memcpy(&oCommentStruct.m_uiNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oCommentStruct.m_usLabelSize, &pChar[uiPos], 2);
		uiPos += 2;
		memcpy(&oCommentStruct.m_pcLabel, &pChar[uiPos], oCommentStruct.m_usLabelSize);
		uiPos += oCommentStruct.m_usLabelSize;
		memcpy(&oCommentStruct.m_usCommentsSize, &pChar[uiPos], 2);
		uiPos += 2;
		memcpy(&oCommentStruct.m_pcComments, &pChar[uiPos], oCommentStruct.m_usCommentsSize);
		uiPos += oCommentStruct.m_usCommentsSize;
		EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
		pCommInfo->m_oOptSetupData.m_olsComment.push_back(oCommentStruct);
		LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
	}
	SaveProcessCommentsSetupData(pCommInfo);
}
// ��ѯ ProcessComments XML�ļ���Ϣ
void QueryProcessCommentsSetupData(char* cProcBuf, int& iPos, m_oInstrumentCommInfoStruct* pCommInfo)
{
	list<m_oOperationCommentStruct>::iterator iter;
	EnterCriticalSection(&pCommInfo->m_oSecCommInfo);
	for (iter = pCommInfo->m_oOptSetupData.m_olsComment.begin();
		iter != pCommInfo->m_oOptSetupData.m_olsComment.end(); iter++)
	{
		memcpy(&cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
		memcpy(&cProcBuf[iPos], &iter->m_usCommentsSize, 2);
		iPos += 2;
		memcpy(&cProcBuf[iPos], &iter->m_pcComments, iter->m_usCommentsSize);
		iPos += iter->m_usCommentsSize;
	}
	LeaveCriticalSection(&pCommInfo->m_oSecCommInfo);
}

// ����ʩ���ͻ��˳�����������
void LoadOptAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// ����Delay��������
	LoadOptDelaySetupData(pCommInfo);
	// ����SourceShot��������
	LoadSourceShotSetupData(pCommInfo);
	// ����Explo��������
	LoadExploSetupData(pCommInfo);
	// ����Vibro��������
	LoadVibroSetupData(pCommInfo);
	// ����ProcessRecord��������
	LoadOptProcessRecordSetupData(pCommInfo);
	// ����ProcessAux��������
	LoadProcessAuxSetupData(pCommInfo);
	// ����ProcessAcq��������
	LoadProcessAcqSetupData(pCommInfo);
	// ����ProcessType��������
	LoadProcessTypeSetupData(pCommInfo);
	// ����ProcessComments��������
	LoadProcessCommentsSetupData(pCommInfo);
}

// ����ʩ���ͻ��˳�����������
void SaveOptAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// ����Delay��������
	SaveDelaySetupData(pCommInfo);
	// ����SourceShot��������
	SaveSourceShotSetupData(pCommInfo);
	// ����Explo��������
	SaveExploSetupData(pCommInfo);
	// ����Vibro��������
	SaveVibroSetupData(pCommInfo);
	// ����ProcessRecord��������
	SaveProcessRecordSetupData(pCommInfo);
	// ����ProcessAux��������
	SaveProcessAuxSetupData(pCommInfo);
	// ����ProcessAcq��������
	SaveProcessAcqSetupData(pCommInfo);
	// ����ProcessType��������
	SaveProcessTypeSetupData(pCommInfo);
	// ����ProcessComments��������
	SaveProcessCommentsSetupData(pCommInfo);
}