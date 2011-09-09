#include "StdAfx.h"
#include "SurveySetupData.h"

CSurveySetupData::CSurveySetupData(void)
{
}

CSurveySetupData::~CSurveySetupData(void)
{
}

// ��ʼ��
void CSurveySetupData::OnInit(void)
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

// ����
void CSurveySetupData::OnReset(void)
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
	m_oLineList.OnReset();

	// ������
	m_oPointList.OnReset();

	// �������
	m_oChannelList.OnReset();

	// �첨���б����
	m_oSensorList.OnReset();

	// ������б����
	m_oPointCodeList.OnReset();

	// ���������ļ�
	ParseXML();
	// ����
	Link();
}

// �ر�
void CSurveySetupData::OnClose(void)
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

// ���������ļ�
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

// ��������
void CSurveySetupData::ParseLine(CLineSetupData* pLineSetupData)
{
	// �������ߵĲ�㶨��
	ParseLineReceiverSection(pLineSetupData);
}

// �������
void CSurveySetupData::ParsePoint(CPointSetupData* pPointSetupData)
{
	// �õ�����Ӧ�ĵ����
	CPointCodeData* pPointCodeData = m_oPointCodeList.GetPointCode(pPointSetupData->iPointCode);
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
			// ���ݲ��ߺš����š�����ţ�����IP��ַ
			pChannelSetupData->CreateIP();
			// ������������
			m_oChannelList.AddChannelToMap(pChannelSetupData->m_uiIP, pChannelSetupData);
			// �������
			ParseChannel(pChannelSetupData);				
		}
	}
}

// �������
void CSurveySetupData::ParseChannel(CChannelSetupData* pChannelSetupData)
{
	// �첨����Ϊ0
	if(0 == pChannelSetupData->m_uiSensorNb)
	{
		// �Ƿ�������
		pChannelSetupData->m_bJumped = true;
	}
}

// �������ߵĲ�㶨��
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

// �������߶�
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
		pPointSetupData->iPointCode = iPointCode;
		// ���������
		pPointSetupData->CreateIndexPoint();
		// ������������
		m_oPointList.AddPointToMap(pPointSetupData->m_uiIndexPoint, pPointSetupData);
		// �������
		ParsePoint(pPointSetupData);
	}
}

// ����
void CSurveySetupData::Link()
{
	// ���Ӳ���
	LinkLine();
	// ���Ӳ��
	LinkPoint();
	// ���Ӳ��
	LinkChannel();

	// ���Դ���***
	unsigned int i;
	CLineSetupData* pLineSetupData;
	for(i = 0; i < m_uiLineCount; i++)
	{
		pLineSetupData = m_oLineList.GetLineByIndex(i);
	}
	CPointSetupData* pPointSetupData;
	for(i = 0; i < m_uiPointCount; i++)
	{
		pPointSetupData = m_oPointList.GetPointByIndex(i);
	}
	CChannelSetupData* pChannelSetupData;
	for(i = 0; i < m_uiChannelCount; i++)
	{
		pChannelSetupData = m_oChannelList.GetChannelByIndex(i);
	}
	// ���Դ���***
}

// ���Ӳ���
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

// ���Ӳ��
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

// ���Ӳ��
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

// �õ����
CChannelSetupData* CSurveySetupData::GetChannel(unsigned int uiIP)
{
	CChannelSetupData* pChannel = NULL;
	if(TRUE == m_oChannelList.GetChannelFromMap(uiIP, pChannel))
	{
		return pChannel;
	}
	return NULL;
}

// �õ����
CChannelSetupData* CSurveySetupData::GetChannel(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel)
{
	return m_oChannelList.GetChannel(uiNbLine, uiNbPoint, uiNbChannel);
}

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

// �õ����
CPointSetupData* CSurveySetupData::GetPoint(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	return m_oPointList.GetPoint(uiNbLine, uiNbPoint);
}

// �õ�����
CLineSetupData* CSurveySetupData::GetLine(unsigned int uiNbLine)
{
	return m_oLineList.GetLine(uiNbLine);
}

// ���������ͷ��򣬵õ��������ڵ�
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

// �������У��õ�IP��ַ���У��ɼ���
bool CSurveySetupData::ParseSpreadToIPListByAbsoluteSpread(CList<unsigned int, unsigned int>* plsIP, CString strAbsoluteSpread)
{
	// �����������ж���
	if(strAbsoluteSpread == "")	// ���в���������
	{
		for(unsigned int  i = 0; i < m_oChannelList.m_uiCountUsed; i++)
		{
			plsIP->AddTail(m_oChannelList.m_pArrayChannel[i].m_uiIP);
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

// �������У��õ�IP��ַ���У��ɼ���
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
		plsIP->AddTail(m_oChannelList.m_pArrayChannel[i].m_uiIP);
	}

	return true;
}