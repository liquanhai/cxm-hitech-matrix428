#include "StdAfx.h"
#include "SurveySetupData.h"

CSurveySetupData::CSurveySetupData()
{
}

CSurveySetupData::~CSurveySetupData()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CSurveySetupData::OnInit()
{
	// ��������
	m_uiLineCount = 0;
	// ����ͷָ��
	m_pLineHead = NULL;
	// ����βָ��
	m_pLineTail = NULL;

	// �������
	m_uiPointCount = 0;
	// ���ͷָ��
	m_pPointHead = NULL;
	// ���βָ��
	m_pPointTail = NULL;

	// �������
	m_uiChannelCount = 0;
	// ���ͷָ��
	m_pChannelHead = NULL;
	// ���βָ��
	m_pChannelTail = NULL;

	// ������������
	m_oLineList.m_uiCountAll = m_uiLineCountAll;
	// ���߶���
	m_oLineList.OnInit();

	// �����������
	m_oPointList.m_uiCountAll = m_uiPointCountAll;
	// ������
	m_oPointList.OnInit();

	// �����������
	m_oChannelList.m_uiCountAll = m_uiChannelCountAll;
	// �������
	m_oChannelList.OnInit();

	// �첨���б����
	m_oSensorList.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oSensorList.OnInit();

	// ������б����
	m_oPointCodeList.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oPointCodeList.m_pSensorList = &m_oSensorList;	// �첨���б����
	m_oPointCodeList.OnInit();

	// ���������ļ�
	ParseXML();
	// ����
	Link();
}

/**
* ����
* @param void
* @return void
*/
void CSurveySetupData::OnReset()
{
	// �������
	m_oChannelList.OnReset();
}

/**
* ���¼���
* @param void
* @return void
*/
void CSurveySetupData::OnReload()
{
	// ��������
	m_uiLineCount = 0;
	// ����ͷָ��
	m_pLineHead = NULL;
	// ����βָ��
	m_pLineTail = NULL;

	// �������
	m_uiPointCount = 0;
	// ���ͷָ��
	m_pPointHead = NULL;
	// ���βָ��
	m_pPointTail = NULL;

	// �������
	m_uiChannelCount = 0;
	// ���ͷָ��
	m_pChannelHead = NULL;
	// ���βָ��
	m_pChannelTail = NULL;

	// ���߶���
	m_oLineList.OnReload();

	// ������
	m_oPointList.OnReload();

	// �������
	m_oChannelList.OnReload();

	// �첨���б����
	m_oSensorList.OnReload();

	// ������б����
	m_oPointCodeList.OnReload();

	// ���������ļ�
	ParseXML();
	// ����
	Link();
}

/**
* �ر�
* @param void
* @return void
*/
void CSurveySetupData::OnClose()
{
	// ���߶���
	m_oLineList.OnClose();

	// ������
	m_oPointList.OnClose();

	// �������
	m_oChannelList.OnClose();

	// �첨���б����
	m_oSensorList.OnClose();

	// ������б����
	m_oPointCodeList.OnClose();
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CSurveySetupData::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ��첨��������
	strKey = "SurverySetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ���������
	strKey = "Count";
	m_uiLineCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CLineSetupData* pLineSetupData = NULL;
	for(unsigned int i = 0; i < m_uiLineCount; i++)
	{
		// �õ�XMLԪ��
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);

		// �õ�һ�����в���
		pLineSetupData = m_oLineList.GetFreeLine();
		pLineSetupData->ParseXML(&oElement);
		// �������������
		m_oLineList.AddLineToMap(pLineSetupData->m_uiNbLine, pLineSetupData);
		// ��������
		ParseLine(pLineSetupData);
	}
}

/**
* ��������
* @param CLineSetupData* pLineSetupData ������������ָ��
* @return void
*/
void CSurveySetupData::ParseLine(CLineSetupData* pLineSetupData)
{
	// �������ߵĲ�㶨��
	ParseLineReceiverSection(pLineSetupData);
}

/**
* �������
* @param CPointSetupData* pPointSetupData �����������ָ��
* @return void
*/
void CSurveySetupData::ParsePoint(CPointSetupData* pPointSetupData)
{
	// �õ�����Ӧ�ĵ����
	CPointCodeData* pPointCodeData = m_oPointCodeList.GetPointCode(pPointSetupData->m_iPointCode);
	if(NULL != pPointCodeData)
	{
		// ���
		CChannelSetupData* pChannelSetupData = NULL;
		// �첨��
		CSensorData* pSensorData = NULL;
		for(int i = 0; i < pPointCodeData->m_iSensorCount; i++)
		{
			// �õ�һ�����в��
			pChannelSetupData = m_oChannelList.GetFreeChannel();
			// ���ߺ�
			pChannelSetupData->m_uiNbLine = pPointSetupData->m_uiNbLine;
			// ����
			pChannelSetupData->m_uiNbPoint = pPointSetupData->m_uiNbPoint;	
			// ���������
			pChannelSetupData->m_uiIndexPoint = pPointSetupData->m_uiIndexPoint;
			// �����
			pChannelSetupData->m_uiNbChannel = i + 1;
			// ���������ţ��õ��첨��
			pSensorData = pPointCodeData->GetSensorData(i);
			// �첨����
			pChannelSetupData->m_uiSensorNb = pSensorData->m_uiNb;
			// SegdCode
			pChannelSetupData->m_uiSegdCode = pSensorData->m_uiSegdCode;
			// ���ݲ��ߺš����š�����ţ�����IP��ַ
			pChannelSetupData->CreateIP();
			// ������������
			m_oChannelList.AddChannelToMap(pChannelSetupData->m_uiIP, pChannelSetupData);
			// �������
			ParseChannel(pChannelSetupData);				
		}
	}
}

/**
* �������
* @param CChannelSetupData* pChannelSetupData �����������ָ��
* @return void
*/
void CSurveySetupData::ParseChannel(CChannelSetupData* pChannelSetupData)
{
	// �첨����Ϊ0
	if(0 == pChannelSetupData->m_uiSensorNb)
	{
		// �Ƿ�������
		pChannelSetupData->m_bJumped = true;
	}
}

/**
* �������ߵĲ�㶨��
* @param CLineSetupData* pLineSetupData ������������ָ��
* @return void
*/
void CSurveySetupData::ParseLineReceiverSection(CLineSetupData* pLineSetupData)
{
	CString strReceiverSection;
	strReceiverSection = pLineSetupData->m_strReceiverSection;
	// ת��ΪСд
	strReceiverSection.MakeLower();

	CString strPart;	// �߶��ַ���
	POSITION pos;	// λ��
	int iPos, iPosStart, iPosStartEnd;	// λ��
	int iCount, i;
	CList<int, int> lsPos;	// λ�ö���

	lsPos.AddTail(-1);
	iPosStart = 0;
	while(true)
	{
		// ���ҷָ���","
		iPos = strReceiverSection.Find(',', iPosStart);
		if(-1 == iPos)
		{
			break;
		}
		lsPos.AddTail(iPos);
		iPosStart = iPos + 1;
	}
	lsPos.AddTail(strReceiverSection.GetAllocLength());

	// �õ���ǵ� "," ����
	iCount = lsPos.GetCount();
	for(i = 0; i < iCount - 1; i++)
	{
		pos = lsPos.FindIndex(i);
		iPosStart = lsPos.GetAt(pos) + 1;
		pos = lsPos.FindIndex(i + 1);
		iPosStartEnd = lsPos.GetAt(pos);
		// �õ��߶��ַ���
		strPart = strReceiverSection.Mid(iPosStart, iPosStartEnd - iPosStart);
		// �������߶�
		ParseLineReceiverSectionPart(pLineSetupData, strPart);
	}
}

/**
* �������߶�
* @param CLineSetupData* pLineSetupData ������������ָ��
* @param CString strPart ���߶ζ����ַ���
* @return void
*/
void CSurveySetupData::ParseLineReceiverSectionPart(CLineSetupData* pLineSetupData, CString strPart)
{
	int iPointCode;	// �����
	int iPos;	// λ��
	int iStep = 1;	// ����
	int iStart = 1;	// ��ʼ���
	int iEnd = 1;	// ��ֹ���
	CString strData;

	// �õ�����
	iPos = strPart.Find('/', 0);
	// �޲�������
	if(-1 == iPos)
	{
		iStep = 1;	// ����
	}
	else	// �в�������
	{
		iPos++;
		strData = strPart.Mid(iPos, strPart.GetLength() - iPos);
		// ����
		iStep = CXMLDOMTool::ConvertStringToInt(strData);
		strPart = strPart.Mid(0, iPos - 1);
	}

	// �õ������
	iPos = strPart.Find('p', 0);
	iPos++;
	strData = strPart.Mid(iPos, strPart.GetLength() - iPos);
	// �����
	iPointCode = CXMLDOMTool::ConvertStringToInt(strData);
	strPart = strPart.Mid(0, iPos - 1);

	// �õ���ʼ��
	iPos = strPart.Find('-', 0);
	// �޷ָ���
	if(-1 == iPos)
	{
		// ��ʼ���
		iStart = CXMLDOMTool::ConvertStringToInt(strPart);
		// ��ֹ���
		iEnd = iStart;
	}
	else	// �зָ���
	{
		strData = strPart.Mid(0, iPos);
		// ��ʼ���
		iStart = CXMLDOMTool::ConvertStringToInt(strData);

		iPos++;
		strData = strPart.Mid(iPos, strPart.GetLength() - iPos);
		// ��ֹ���
		iEnd = CXMLDOMTool::ConvertStringToInt(strData);
	}

	CPointSetupData* pPointSetupData = NULL;
	for(int i = iStart; i <= iEnd; i = i + iStep)
	{
		// �õ�һ�����в��
		pPointSetupData = m_oPointList.GetFreePoint();
		// ���ߺ�
		pPointSetupData->m_uiNbLine = pLineSetupData->m_uiNbLine;
		// ����
		pPointSetupData->m_uiNbPoint = i;
		// �����
		pPointSetupData->m_iPointCode = iPointCode;
		// ���������
		pPointSetupData->CreateIndexPoint();
		// ������������
		m_oPointList.AddPointToMap(pPointSetupData->m_uiIndexPoint, pPointSetupData);
		// �������
		ParsePoint(pPointSetupData);
	}
}

/**
* ���ӵ�����������
* @param void
* @return void
*/
void CSurveySetupData::Link()
{
	// ���Ӳ���
	LinkLine();
	// ���Ӳ��
	LinkPoint();
	// ���Ӳ��
	LinkChannel();
}

/**
* ���Ӳ���
* @param void
* @return void
*/
void CSurveySetupData::LinkLine()
{
	// ��������
	m_uiLineCount = m_oLineList.m_uiCountUsed;
	// ����ͷָ��
	m_pLineHead = m_oLineList.GetLineByIndex(0);
	// ����βָ��
	m_pLineTail = m_oLineList.GetLineByIndex(m_uiLineCount - 1);

	// ����ָ��
	CLineSetupData* pLineSetupData;
	// ��һ������ָ��
	CLineSetupData* pLineSetupDataNext;
	for(unsigned int i = 0; i < m_uiLineCount - 1; i++)
	{
		pLineSetupData = m_oLineList.GetLineByIndex(i);
		pLineSetupDataNext = m_oLineList.GetLineByIndex(i + 1);
		// ��������
		pLineSetupData->m_pLinelDown = pLineSetupDataNext;
		pLineSetupDataNext->m_pLinelTop = pLineSetupData;
	}
}

/**
* ���Ӳ��
* @param void
* @return void
*/
void CSurveySetupData::LinkPoint()
{
	// �������
	m_uiPointCount = m_oPointList.m_uiCountUsed;
	// ���ͷָ��
	m_pPointHead = m_oPointList.GetPointByIndex(0);
	// ���βָ��
	m_pPointTail = m_oPointList.GetPointByIndex(m_uiPointCount - 1);

	// ���ָ��
	CPointSetupData* pPointSetupData;
	// ��һ�����ָ��
	CPointSetupData* pPointSetupDataNext;

	// ����ָ��
	CLineSetupData* pLineSetupData = m_pLineHead;
	// ����ͷָ��
	pLineSetupData->m_pPointHead = m_pPointHead;

	for(unsigned int i = 0; i < m_uiPointCount - 1; i++)
	{
		pPointSetupData = m_oPointList.GetPointByIndex(i);
		pPointSetupDataNext = m_oPointList.GetPointByIndex(i + 1);
		// ���Ͳ�����ͬһ������
		if(pPointSetupData->m_uiNbLine == pLineSetupData->m_uiNbLine)
		{
			// �������
			pLineSetupData->m_uiPointCount++;
		}
		// ǰ������ͬһ������
		if(pPointSetupData->m_uiNbLine == pPointSetupDataNext->m_uiNbLine)
		{
			// ��������
			pPointSetupData->m_pPointRight = pPointSetupDataNext;
			pPointSetupDataNext->m_pPointLeft = pPointSetupData;
		}
		else	// ����ͬһ��������
		{
			// ���ߵĲ��βָ��
			pLineSetupData->m_pPointTail = pPointSetupData;
			// ���Ӳ������
			pLineSetupData->m_pPointHead->m_pPointlDown = pPointSetupDataNext;
			pPointSetupDataNext->m_pPointlTop = pLineSetupData->m_pPointHead;
			// ��һ������
			pLineSetupData = pLineSetupData->m_pLinelDown;
			pLineSetupData->m_pPointHead = pPointSetupDataNext;
		}
	}
	// �������
	pLineSetupData->m_uiPointCount++;
	// ���ߵĲ��βָ��
	pLineSetupData->m_pPointTail = pPointSetupDataNext;
}

/**
* ���Ӳ��
* @param void
* @return void
*/
void CSurveySetupData::LinkChannel()
{
	// �������
	m_uiChannelCount = m_oChannelList.m_uiCountUsed;
	// ���ͷָ��
	m_pChannelHead = m_oChannelList.GetChannelByIndex(0);
	// ���βָ��
	m_pChannelTail = m_oChannelList.GetChannelByIndex(m_uiChannelCount - 1);

	// ���ָ��
	CChannelSetupData* pChannelSetupData;
	// ��һ�����ָ��
	CChannelSetupData* pChannelSetupDataNext;

	// ����ָ��
	CLineSetupData* pLineSetupData = m_pLineHead;
	// ����ͷָ��
	pLineSetupData->m_pChannelHead = m_pChannelHead;

	// ���ָ��
	CPointSetupData* pPointSetupData = m_pPointHead;
	// ���ͷָ��
	pPointSetupData->m_pChannelHead = m_pChannelHead;

	for(unsigned int i = 0; i < m_uiChannelCount - 1; i++)
	{
		pChannelSetupData = m_oChannelList.GetChannelByIndex(i);
		pChannelSetupDataNext = m_oChannelList.GetChannelByIndex(i + 1);
		// ͬһ������
		if(pChannelSetupData->m_uiNbLine == pLineSetupData->m_uiNbLine)
		{
			// �������
			pLineSetupData->m_uiChannelCount++;
		}
		// ͬһ�����
		if(pChannelSetupData->m_uiNbPoint == pPointSetupData->m_uiNbPoint)
		{
			// �������
			pPointSetupData->m_uiChannelCount++;
		}
		// ǰ������ͬһ������
		if(pChannelSetupData->m_uiNbLine == pChannelSetupDataNext->m_uiNbLine)
		{
			// ��������
			pChannelSetupData->m_pChannelRight = pChannelSetupDataNext;
			pChannelSetupDataNext->m_pChannelLeft = pChannelSetupData;
		}
		else	// ����ͬһ��������
		{
			// ���ߵĲ��βָ��
			pLineSetupData->m_pChannelTail = pChannelSetupData;
			// ���Ӳ������
			pLineSetupData->m_pChannelHead->m_pChannelDown = pChannelSetupDataNext;
			pChannelSetupDataNext->m_pChannelTop = pLineSetupData->m_pChannelHead;
			// ��һ������
			pLineSetupData = pLineSetupData->m_pLinelDown;
			pLineSetupData->m_pChannelHead = pChannelSetupDataNext;
		}
		// ǰ��������ͬһ�����
		if(pChannelSetupData->m_uiNbPoint != pChannelSetupDataNext->m_uiNbPoint)
		{
			// ���Ĳ��βָ��
			pPointSetupData->m_pChannelTail = pChannelSetupData;
			// ��һ�����
			pPointSetupData = m_oPointList.GetPointByIndex(pPointSetupData->m_uiIndex + 1);
			pPointSetupData->m_pChannelHead = pChannelSetupDataNext;
		}
	}
	// �������
	pLineSetupData->m_uiChannelCount++;
	// ���ߵĲ��βָ��
	pLineSetupData->m_pChannelTail = pChannelSetupDataNext;

	// �������
	pPointSetupData->m_uiChannelCount++;
	// ���Ĳ��βָ��
	pPointSetupData->m_pChannelTail = pChannelSetupDataNext;
}

/**
* ��������IP��ַ���ڲ�������еõ����
* @param unsigned int uiIP ����IP��ַ
* @return CChannelSetupData* ���ָ�� NULL���޶�Ӧ���
*/
CChannelSetupData* CSurveySetupData::GetChannel(unsigned int uiIP)
{
	CChannelSetupData* pChannel = NULL;
	if(TRUE == m_oChannelList.GetChannelFromMap(uiIP, pChannel))
	{
		return pChannel;
	}
	return NULL;
}

/**
* ���ݲ��ߡ���㡢������ڲ�������еõ����
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @param unsigned int uiNbChannel �����
* @return CChannelSetupData* ���ָ�� NULL���޶�Ӧ���
*/
CChannelSetupData* CSurveySetupData::GetChannel(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel)
{
	return m_oChannelList.GetChannel(uiNbLine, uiNbPoint, uiNbChannel);
}

/**
* ���ݲ�������ţ��õ����
* @param unsigned int uiIndexPoint ���������
* @return CPointSetupData* ���ָ�� NULL���޶�Ӧ���
*/
// �õ����
CPointSetupData* CSurveySetupData::GetPoint(unsigned int uiIndexPoint)
{
	CPointSetupData* pPoint = NULL;
	if(TRUE == m_oPointList.GetPointFromMap(uiIndexPoint, pPoint))
	{
		return pPoint;
	}
	return NULL;
}

/**
* ���ݲ��ߡ���㣬�ڲ������еõ����
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @return CPointSetupData* ���ָ�� NULL���޶�Ӧ���
*/
CPointSetupData* CSurveySetupData::GetPoint(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	return m_oPointList.GetPoint(uiNbLine, uiNbPoint);
}

/**
* ���ݲ��ߺţ��õ�����
* @param unsigned int uiNbLine ���ߺ�
* @return CLineSetupData* ����ָ�� NULL���޶�Ӧ����
*/
CLineSetupData* CSurveySetupData::GetLine(unsigned int uiNbLine)
{
	return m_oLineList.GetLine(uiNbLine);
}

/**
* ���������ͷ��򣬵õ��������ڵ�
* @param CPointSetupData* pPointSetupData ���ָ��
* @param unsigned int uiIncrement ����
* @param unsigned int uiDirection ���� 3����4����
* @return CPointSetupData* ���ָ�� NULL���޶�Ӧ���
*/
CPointSetupData* CSurveySetupData::GetPointByIncrementAndDirection(CPointSetupData* pPointSetupData, unsigned int uiIncrement, unsigned int uiDirection)
{
	if(NULL == pPointSetupData)
	{
		return NULL;
	}

	CPointSetupData* pPoint = pPointSetupData;
	unsigned int iCount = 0;
	// �жϷ���
	switch(uiDirection)
	{
	case 3:	// ��
		{
			while(true)
			{
				pPoint = pPoint->m_pPointLeft;
				if(NULL == pPoint)
				{
					return NULL;
				}
				iCount++;
				if(iCount == uiIncrement)
				{
					return pPoint;
				}
			}
			break;
		}
	case 4:	// ��
		{
			while(true)
			{
				pPoint = pPoint->m_pPointRight;
				if(NULL == pPoint)
				{
					return NULL;
				}
				iCount++;
				if(iCount == uiIncrement)
				{
					return pPoint;
				}
			}
			break;
		}
	}
	return NULL;
}

/**
* �����ɼ����������У��õ�IP��ַ����
* @param CList<unsigned int, unsigned int>* plsIP IP��ַ����ָ��
* @param CString strAbsoluteSpread ��������
* @return bool true���ɹ���false��ʧ��
*/
bool CSurveySetupData::ParseSpreadToIPListByAbsoluteSpread(CList<unsigned int, unsigned int>* plsIP, CString strAbsoluteSpread)
{
	// �����������ж���
	// �жϣ�û�ж�����
	if(strAbsoluteSpread == "")
	{
		return true;
	}
	// �жϣ����в���������
	if(strAbsoluteSpread == "all")
	{
		for(unsigned int  i = 0; i < m_oChannelList.m_uiCountUsed; i++)
		{
			// �жϣ�����������������Ƶ�
			if((false == m_oChannelList.m_pArrayChannel[i].m_bJumped) && ((false == m_oChannelList.m_pArrayChannel[i].m_bMute)))
			{
				// �жϣ�ֻ����Ѿ����ӵ��ֳ��Ĳ��IP��ַ
				if(0 < m_oChannelList.m_pArrayChannel[i].m_uiSN)
				{
					if(NULL == plsIP->Find(m_oChannelList.m_pArrayChannel[i].m_uiIP, 0))
					{
						plsIP->AddTail(m_oChannelList.m_pArrayChannel[i].m_uiIP);
					}
				}
			}
		}
	}
	else
	{
		CString strPart;	// �߶��ַ���                                        
		POSITION pos;	// λ��                                                  
		int iPos, iPosStart, iPosStartEnd;	// λ��                              
		int iCount, i;                                                           
		CList<int, int> lsPos;	// λ�ö���                                      

		lsPos.AddTail(-1);                                                       
		iPosStart = 0;                                                           
		while(true)                                                              
		{                                                                        
			// ���ҷָ���";"                                                   
			iPos = strAbsoluteSpread.Find(';', iPosStart);                       
			if(-1 == iPos)                                                       
			{                                                                    
				break;                                                           
			}                                                                    
			lsPos.AddTail(iPos);                                                 
			iPosStart = iPos + 1;                                                
		}                                                                        
		lsPos.AddTail(strAbsoluteSpread.GetAllocLength());                       

		// �õ���ǵ� ";" ����                                                   
		iCount = lsPos.GetCount();                                               
		for(i = 0; i < iCount - 1; i++)                                          
		{                                                                        
			pos = lsPos.FindIndex(i);                                            
			iPosStart = lsPos.GetAt(pos) + 1;                                    
			pos = lsPos.FindIndex(i + 1);                                        
			iPosStartEnd = lsPos.GetAt(pos);                                     
			// �õ��߶��ַ���                                                    
			strPart = strAbsoluteSpread.Mid(iPosStart, iPosStartEnd - iPosStart);
			ParseSpreadToIPListByAbsoluteSpreadPart(plsIP, strPart);             
		}                                                                        
	}
	return true;
}

/**
* �����ɼ������ж��壬�õ�IP��ַ����
* @param CList<unsigned int, unsigned int>* plsIP IP��ַ����ָ��
* @param CString strPart ���ж���
* @return bool true���ɹ���false��ʧ��
*/
bool CSurveySetupData::ParseSpreadToIPListByAbsoluteSpreadPart(CList<unsigned int, unsigned int>* plsIP, CString strPart)
{
	unsigned int uiNbLine;	// ���ߺ�
	unsigned int uiNbPointStart;	// ��ʼ����
	unsigned int uiNbPointEnd;	// ��ֹ����
	CLineSetupData* pLineSetupData = NULL;	// ����
	CPointSetupData* pPointSetupDataStart = NULL;	// ��ʼ���
	CPointSetupData* pPointSetupDataEnd = NULL;	// ��ֹ���

	int iPos = 0;	// λ��
	CString strData;

	// �õ����ߺ�
	iPos = strPart.Find(':', 0);
	strData = strPart.Mid(0, iPos);	// ���ߺ�
	uiNbLine = CXMLDOMTool::ConvertStringToInt(strData);
	pLineSetupData = GetLine(uiNbLine);
	if(NULL == pLineSetupData)
	{
		return true;
	}

	iPos = iPos++;
	strPart = strPart.Mid(iPos, strPart.GetLength() - iPos);
	// �õ���ʼ��
	iPos = strPart.Find('-', 0);
	// �޷ָ���
	if(-1 == iPos)
	{
		// ��ʼ���
		uiNbPointStart = CXMLDOMTool::ConvertStringToInt(strPart);
		// ��ֹ���
		uiNbPointEnd = uiNbPointStart;
	}
	else	// �зָ���
	{
		strData = strPart.Mid(0, iPos);
		// ��ʼ���
		uiNbPointStart = CXMLDOMTool::ConvertStringToInt(strData);

		iPos++;
		strData = strPart.Mid(iPos, strPart.GetLength() - iPos);
		// ��ֹ���
		uiNbPointEnd = CXMLDOMTool::ConvertStringToInt(strData);
	}
	// �õ�����
	CLineSetupData* GetLine(unsigned int uiNbLine);

	// �õ���ʼ��㣬���ݲ��ߺš�����
	pPointSetupDataStart = GetPoint(uiNbLine, uiNbPointStart);
	if(NULL == pPointSetupDataStart)
	{
		pPointSetupDataStart = pLineSetupData->m_pPointHead;
	}
	// �õ���ֹ��㣬���ݲ��ߺš�����
	pPointSetupDataEnd = GetPoint(uiNbLine, uiNbPointEnd);
	if(NULL == pPointSetupDataEnd)
	{
		pPointSetupDataEnd = pLineSetupData->m_pPointTail;
	}
	
	int iChannelIndexStart = pPointSetupDataStart->m_pChannelHead->m_uiIndex;
	int iChannelIndexEnd = pPointSetupDataEnd->m_pChannelTail->m_uiIndex;

	for(int i = iChannelIndexStart; i <= iChannelIndexEnd; i++)
	{
		// �жϣ�����������������Ƶ�
		if((false == m_oChannelList.m_pArrayChannel[i].m_bJumped) && ((false == m_oChannelList.m_pArrayChannel[i].m_bMute)))
		{
			// �жϣ�ֻ����Ѿ����ӵ��ֳ��Ĳ��IP��ַ
			if(0 < m_oChannelList.m_pArrayChannel[i].m_uiSN)
			{
				if(NULL == plsIP->Find(m_oChannelList.m_pArrayChannel[i].m_uiIP, 0))
				{
					plsIP->AddTail(m_oChannelList.m_pArrayChannel[i].m_uiIP);
				}
			}
		}		
	}
	return true;
}

/**
* �õ�IP��ַ���У��μ��¼Ӽ첨���ĳ�ʼ����
* @param CList<unsigned int, unsigned int>* plsIP IP��ַ����ָ��
* @return bool true���ɹ���false��ʧ��
*/
bool CSurveySetupData::GetIPListForSensorTestOnField(CList<unsigned int, unsigned int>* plsIP)
{
	for(unsigned int  i = 0; i < m_oChannelList.m_uiCountUsed; i++)
	{
		// �жϣ�����������������Ƶ�
		if((false == m_oChannelList.m_pArrayChannel[i].m_bJumped) && ((false == m_oChannelList.m_pArrayChannel[i].m_bMute)))
		{
			// �жϣ�ֻ����Ѿ����ӵ��ֳ��Ĳ��IP��ַ����δ���м첨���ĳ�ʼ����
			if((0 < m_oChannelList.m_pArrayChannel[i].m_uiSN) && ((0 == m_oChannelList.m_pArrayChannel[i].m_byTestOnField)))
			{
				if(NULL == plsIP->Find(m_oChannelList.m_pArrayChannel[i].m_uiIP, 0))
				{
					plsIP->AddTail(m_oChannelList.m_pArrayChannel[i].m_uiIP);
				}
			}
		}
	}
	return true;
}

/**
* �����оݺź�IP��ַ���õ������о�
* @param unsigned int uiTestLimitIndex �оݺ�
* @param unsigned int uiIP IP��ַ
* @return float �����оݣ����÷�ʽ����
* @return bool true���ɹ���false��ʧ��
*/
bool CSurveySetupData::GetTestLimitValue(unsigned int uiTestLimitIndex, unsigned int uiIP, float& fLimit)
{
	bool bReturn = false;
	fLimit = 0.0;
	CChannelSetupData* pSurveySetupData = NULL;
	pSurveySetupData = GetChannel(uiIP);
	if(NULL != pSurveySetupData)
	{
		CSensorData* pSensorData = NULL;
		pSensorData = m_oSensorList.GetSensor(pSurveySetupData->m_uiSensorNb);
		if(NULL != pSensorData)
		{
			switch(uiTestLimitIndex)
			{
				// ������Сֵ
			case 1500:
				fLimit = pSensorData->m_fContinuityMin;
				bReturn = true;
				break;
				// �������ֵ
			case 1501:
				fLimit = pSensorData->m_fContinuityMax;
				bReturn = true;
				break;
				// ©��
			case 1400:
				fLimit = pSensorData->m_fLeaKage;
				bReturn = true;
				break;
				// ����
			case 100:
				fLimit = pSensorData->m_fNoise;
				bReturn = true;
				break;
				// ��б��
			case 2000:
				fLimit = pSensorData->m_fTilt;
				bReturn = true;
				break;
			}
		}
	}
	return bReturn;	
}