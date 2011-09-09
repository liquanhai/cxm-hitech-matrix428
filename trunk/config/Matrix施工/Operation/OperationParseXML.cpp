#include "StdAfx.h"
#include "Operation.h"
#include "OperationParseXML.h"
#include "../common/LineStruct.h"

/**
 * @brief COperationParseXML���캯��
 */
COperationParseXML::COperationParseXML(void)
{
}
/**
 * @brief COperationParseXML��������
 */
COperationParseXML::~COperationParseXML(void)
{

}

/**
 * @brief ���ͻ��˵�ϵͳ����
 * @note  �������ļ��ж�ȡ�ͻ��˵�����IP����Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @return �����Ƿ�ɹ�
 
bool COperationParseXML::ParseClientSetup(LPCTSTR pstrXMLFilePath)
{
	CString strTemp;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	

	try
	{	// ����XML����
		strTemp =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strTemp, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ����ڱ�����
		strKey =_T("OperationClient");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// �õ��ͻ���IP��ַ��������IP��ַ
		strKey =_T("HostIP");
		strTemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);		
		// theApp.m_dwHostIP = StringIPToDWORDIP(strTemp);
		theApp.m_strHostIP = strTemp;
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
		return true;
	}
	catch (CException* )
	{
		return false;
	}
}*/
/**
 * @brief �����ɼ�վ������Ϣ
 * @note  ��XML�����ļ��н������ɼ�վ�Ļ���������Ϣ����Ҫ
 ������ǰ�÷Ŵ�ģ����ѡ��5373ģʽ��DA˥���������ʡ�IIRѡ��FIRѡ��
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CFDUConfig* pFDUConfig�����ö���
 * @return ��ȡ�Ķ������

bool COperationParseXML::ParseFDUConfig(LPCTSTR pstrXMLFilePath,CFDUConfig* pFDUConfig)
{
	CString strTemp;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	

	if(!pFDUConfig)
		return false;
	try
	{	// ����XML����
		strTemp =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strTemp, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ����
		strKey =_T("samplerate");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwSampleRateIndex = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("FilterFIR");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwFilterFIRIndex = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("FilterIIR");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwFilterIIRIndex = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("Gain3301");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwGain3301Index = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("Mux3301");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwMux3301Index = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("Mode5373");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwMode5373Index = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("Attr5373");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwAttr5373Index = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
		return true;
	}
	catch (CException* )
	{
		return false;
	}

} */
/**
 * @brief��������ʩ��ע�ͼ�¼
 * @note  ��������ʩ��ע�ͼ�¼��
 * @param CXMLDOMElement* pElement��XML�ڵ����ָ��
 * @param CShotComment* pComment��ע�Ͷ���
 * @return �ɹ�����1��ʧ�ܷ���0
 */
int COperationParseXML::ParseCommentRecord(CXMLDOMElement* pElement,CShotComment* pComment)
{
	CString strKey;
	try
	{
		strKey =_T("Nb");
		pComment->m_dwCommentNb= CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);

		strKey =_T("Label");
		pComment->m_strLabel= CXMLDOMTool::GetElementAttributeString(pElement, strKey);

		strKey =_T("Comment");
		pComment->m_strComment= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	}	
	catch (CException* )
	{
		return 0;
	}

	return 1;	
}
/**
 * @brief ���浥��ʩ��ע�ͼ�¼
 * @note  ���浥��ʩ��ע�ͼ�¼���浽XML�������ļ��С�
 * @param CXMLDOMElement* pElement��XML�ڵ����ָ��
 * @param CShotComment* pComment��ע�Ͷ���
 * @return �ɹ�����1
 */
int COperationParseXML::SaveCommentRecord(CXMLDOMElement* pElement,CShotComment* pComment)
{
	CString strKey;	// ����	
	COleVariant   oVariant;
	VARIANT   vt;
	if(NULL==pComment)
		return 0;
	try
	{
		// Nb
		strKey = _T("Nb");
		vt.vt = VT_UI4;
		vt.ulVal = pComment->m_dwCommentNb;
		oVariant = vt;
		pElement->setAttribute(strKey, oVariant);

		// Label
		strKey =_T("Label");
		oVariant = pComment->m_strLabel;
		pElement->setAttribute(strKey, oVariant);

		// Comments
		strKey =_T("Comment");
		oVariant = pComment->m_strComment;
		pElement->setAttribute(strKey, oVariant);
	}	
	catch (CException* )
	{
		return 0;
	}
	return 1;
}
/**
 * @brief ����ʩ��ע�ͼ�¼��
 * @note  ��XML�������ļ��н���ʩ��ע�ͼ�¼��
 * @param LPCTSTR pstrXMLFilePath��XML�ļ�
 * @param CShotComments* pComments��ע�Ͷ���
 * @return �ɹ����ؼ�¼����
 */
int  COperationParseXML::ParseComments(LPCTSTR pstrXMLFilePath,CShotComments* pComments)
{
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	ULONG		dwCount;
	try
	{
		//CoInitialize(NULL);
		// ����XML����
		strOLEObject =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�ʩ��ע������
		strKey =_T("OperationComment");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����
		strKey =_T("Count");
		dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		CShotComment* pComment = NULL;
		for(unsigned int i = 0; i < dwCount; i++)
		{
			pComment = new CShotComment;
			// �õ�XMLԪ��
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			// �õ��ں�
			ParseCommentRecord(&oElement, pComment);		
			// ������ڱ�
			pComments->Add(pComment);
		}
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();	
	}	
	catch (CException* )
	{
		return 0;
	}
	return dwCount;
}
/**
 * @brief ����ʩ��ע�ͱ�
 * @note  ��ע�ͱ����pComments�����ݱ��浽XML�������ļ��С�
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotComments* pComments��ע�ͱ����Ҳ��ʩ��ע�͵ļ��϶���
 * @return �洢�Ķ������
 */
int  COperationParseXML::SaveComments(LPCTSTR pstrXMLFilePath,CShotComments* pComments)
{
	COleException	oError;
	COleVariant		oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString			strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement	oElementParent,oElementChild;
	LPDISPATCH		lpDispatch;
	long			i,lCount;
	try
	{	//CoInitialize(NULL);
		// ����XML����
		strKey =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strKey, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ����ڱ�����
		strKey =_T("OperationComment");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// ���õ��������
		strKey = _T("Count");
		lCount = (long)(pComments->GetCount());
		oVariant = lCount;
		oElementParent.setAttribute(strKey, oVariant);

		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		// �����½ڵ�
		CShotComment *pComment =NULL;
		for( i = 0; i < lCount; i++)
		{
			pComment = pComments->GetShotComment(i);

			lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t"));
			oElementParent.appendChild(lpDispatch);

			lpDispatch = oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);		
			//���浥�����ڼ�¼
			SaveCommentRecord(&oElementChild,pComment);	
			oElementParent.appendChild(lpDispatch);

		}
		lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t"));
		oElementParent.appendChild(lpDispatch);

		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.save(oVariant);
		theApp.SaveXMLToFTPServer();
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
		theApp.SaveXMLToFTPServer();
	}	
	catch (CException* )
	{
		return 0;
	}
	return lCount;
}
/**
 * @brief �������ڱ�
 * @note  ��XML�������ļ��ж�ȡ���������ڱ�������ڱ����pShotPoints�С�
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotPoints* pShotPoints�����ڱ����Ҳ�Ǵ洢�ںŵļ��϶���
 * @return ��ȡ�Ķ������
 */
int COperationParseXML::ParseOperationTable(LPCTSTR pstrXMLFilePath,CShotPoints* pShotPoints)
{
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	ULONG		dwCount;

	//CoInitialize(NULL);
	// ����XML����
	strOLEObject =_T("msxml2.domdocument");
	BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

	oVariant = pstrXMLFilePath;
	bData = oXMLDOMDocument.load(oVariant);

	// �ҵ����ڱ�����
	strKey =_T("OperationTable");
	lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ�����
	strKey =_T("Count");
	dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CShotPoint* pVP = NULL;
	for(unsigned int i = 0; i < dwCount; i++)
	{
		pVP = new CShotPoint;
		// �õ�XMLԪ��
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		// �õ��ں�
		ParseOperationTableRecord(&oElement, pVP);		
		// ������ڱ�
		pShotPoints->Add(pVP);		
	}
	// �ͷŶ���
	oXMLDOMDocument.DetachDispatch();
	//CoUninitialize();
	return dwCount;
}
/**
 * @brief ������ڱ�
 * @note  �����ڱ����pShotPoints�����ݱ��浽XML�������ļ��С�
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotPoints* pShotPoints�����ڱ����Ҳ�Ǵ洢�ںŵļ��϶���
 * @return �洢�Ķ������
 */
int COperationParseXML::SaveOperationTable(LPCTSTR pstrXMLFilePath,CShotPoints* pShotPoints)
{	
	COleException	oError;
	COleVariant		oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString			strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement	oElementParent,oElementChild;
	LPDISPATCH		lpDispatch;
	long			i,lCount;

	//CoInitialize(NULL);
	// ����XML����
	strKey =_T("msxml2.domdocument");
	BOOL bData = oXMLDOMDocument.CreateDispatch(strKey, &oError);

	oVariant = pstrXMLFilePath;
	bData = oXMLDOMDocument.load(oVariant);

	// �ҵ����ڱ�����
	strKey =_T("OperationTable");
	lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	
	// ���õ��������
	strKey = _T("Count");
	lCount = (long)(pShotPoints->GetCount());
	oVariant = lCount;
	oElementParent.setAttribute(strKey, oVariant);

	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}
	// �����½ڵ�
	CShotPoint *pShotPoint =NULL;
	for( i = 0; i < lCount; i++)
	{
		pShotPoint = pShotPoints->GetShotPoint(i);

		lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t"));
		oElementParent.appendChild(lpDispatch);

		lpDispatch = oXMLDOMDocument.createElement(_T("Record"));
		oElementChild.AttachDispatch(lpDispatch);		
		//���浥�����ڼ�¼
		SaveOperationTableRecord(&oElementChild,pShotPoint);	
		oElementParent.appendChild(lpDispatch);
				
	}
	lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t"));
	oElementParent.appendChild(lpDispatch);

	oVariant = pstrXMLFilePath;
	oXMLDOMDocument.save(oVariant);
	// �ͷŶ���
	oXMLDOMDocument.DetachDispatch();
	theApp.SaveXMLToFTPServer();
	return lCount;
}

/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�

			ÿ����¼��XML��ʽ���£�
			<Record VPStatus="0" ShotID="1" BreakPoint="N" SwathNb ="1" SourcePointIndex ="1"
			SourceLine = "1" SourceReceiver = "1" SpreadType ="Absolute" SpreadSFL ="" SpreadSFN ="" 
			SuperSpread="" ProcessTypeID ="1" Comments ="ע��"/>

    �޸���ʷ��



*******************************************************************************/
int COperationParseXML::ParseOperationTableRecord(CXMLDOMElement* pElement,CShotPoint* pVP)
{
	CString strKey;	// ����	
	if(NULL==pVP)
		return 0;
	// ����״̬
	strKey = _T("VPStatus");
	pVP->m_VPState =(unsigned char)CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// �ں�
	strKey =_T("ShotID");
	pVP->m_dwShotNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	//  
	strKey =_T("BreakPoint");
	strKey= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	if(strKey.CompareNoCase(_T("Y")))
		pVP->m_byBreakPoint = 0;
	else
		pVP->m_byBreakPoint = 1;
	// 
	strKey =_T("SwathNb");
	pVP->m_dwSwathNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// 
	strKey =_T("SourcePointIndex");
	pVP->m_dwSourcePointIndex= CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// 
	strKey =_T("SourceLine");
	pVP->m_fSourceLine = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
	// 
	strKey =_T("SourceReceiver");
	pVP->m_fSourceNb= CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);
	// 
	strKey =_T("SpreadSFL");
	pVP->m_dwSpreadSFL = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// 
	strKey =_T("SpreadSFN");
	pVP->m_dwSpreadSFN= CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// 
	// 
	strKey =_T("SpreadType");
	pVP->m_dwSpreadNb= CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	/*
	strKey =_T("SpreadType");
	strKey= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	if(strKey.CompareNoCase(_T("Absolute")))
		pVP->m_bySpreadType= SPREADTYPE_GENERIC;
	else
		pVP->m_byBreakPoint = SPREADTYPE_ABSOLUTE;
	*/
	// 
	strKey =_T("ProcessTypeID");
	pVP->m_dwProcessNb= CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// 
	strKey =_T("Comment");
	pVP->m_szComments= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	return 1;
}
/**
 * @brief ���浥�����ڼ�¼
 * @note  �����ڶ���pShotPoint�����ݱ��浽XML�������ļ��С�
 * @param CXMLDOMElement* pElement��XML�ڵ����ָ��
 * @param CShotPoint* pShotPoint�����ڶ���
 * @return �ɹ�����1
 */
int COperationParseXML::SaveOperationTableRecord(CXMLDOMElement* pElement,CShotPoint* pShotPoint)
{
	CString strKey;	// ����	
	COleVariant   oVariant;
	VARIANT   vt;
	if(NULL==pShotPoint)
		return 0;
	// ����״̬	
	strKey = _T("VPStatus");
	oVariant = pShotPoint->m_VPState;
	pElement->setAttribute(strKey, oVariant);
	// �ں�
	strKey = _T("ShotID");
	vt.vt = VT_UI4;
	vt.ulVal = pShotPoint->m_dwShotNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);	
	 
	// BreakPoint
	strKey = _T("BreakPoint");
	if(pShotPoint->m_byBreakPoint)
		oVariant = _T("Y"); 
	else
		oVariant = _T("N");
	pElement->setAttribute(strKey, oVariant);
	// SwathNb
	strKey =_T("SwathNb");
	vt.vt = VT_UI4;
	vt.ulVal = pShotPoint->m_dwSwathNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);	
	// SourcePointIndex
	strKey =_T("SourcePointIndex");
	vt.vt = VT_UI4;
	vt.ulVal = pShotPoint->m_dwSourcePointIndex;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);
	// SourceLine
	strKey =_T("SourceLine");
	oVariant = pShotPoint->m_fSourceLine;
	pElement->setAttribute(strKey, oVariant);	
	// SourceReceiver
	strKey =_T("SourceReceiver");
	oVariant = pShotPoint->m_fSourceNb;
	pElement->setAttribute(strKey, oVariant);	
	// SpreadSFL
	strKey =_T("SpreadSFL");
	vt.vt = VT_UI4;
	vt.ulVal = pShotPoint->m_dwSpreadSFL;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);	
	// SpreadSFN
	strKey =_T("SpreadSFN");
	vt.vt = VT_UI4;
	vt.ulVal = pShotPoint->m_dwSpreadSFN;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);	
	// SpreadType
	strKey =_T("SpreadType");
	vt.vt = VT_UI4;
	vt.ulVal = pShotPoint->m_dwSpreadNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);
	// ProcessTypeID
	strKey =_T("ProcessTypeID");
	vt.vt = VT_UI4;
	vt.ulVal = pShotPoint->m_dwProcessNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);
	// Comments
	strKey =_T("Comment");
	oVariant = pShotPoint->m_szComments;
	pElement->setAttribute(strKey, oVariant);
	return 1;
}
/**
 * @brief ������Դ��
 * @note  ��XML�������ļ��ж�ȡ����Դ���������pShotSrcs�С�
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotSources* pShotSrcs����Դ�����Ҳ�Ǵ洢��Դ�ļ��϶���
 * @return ��ȡ�Ķ������
 */
int COperationParseXML::ParseSourceType(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs)
{

	return ParseSourceExplo(pstrXMLFilePath,pShotSrcs)+ParseSourceVibro(pstrXMLFilePath,pShotSrcs);
}
int COperationParseXML::SaveSourceType(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs)
{
	
	int nRet = SaveSourceExplo(pstrXMLFilePath,pShotSrcs)+SaveSourceVibro(pstrXMLFilePath,pShotSrcs);
	theApp.SaveXMLToFTPServer();
	return nRet;
}
/******************************************************************************
    ��    ����ParseSourceExplo
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� �������屬ը��Դ

    �޸���ʷ��

*******************************************************************************/
int COperationParseXML::ParseSourceExplo(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs)
{
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	ULONG		dwCount;
	try
	{
		//CoInitialize(NULL);
		// ����XML����
		strOLEObject =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�������Դ
		strKey =_T("SourceExplo");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����
		strKey =_T("Count");
		dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		CShotSourceExplo* pSrc = NULL;
		for(unsigned int i = 0; i < dwCount; i++)
		{
			pSrc = new CShotSourceExplo;
			// �õ�XMLԪ��
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			// ������Դ
			ParseSourceExploRecord(&oElement, pSrc);		
			// ������Դ��
			pShotSrcs->Add(pSrc);

		}
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
	}	
	catch (CException* )
	{
		return 0;
	}
	return dwCount;

}
int COperationParseXML::SaveSourceExplo(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs)
{
	COleException	oError;
	COleVariant		oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString			strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement	oElementParent,oElementChild;
	LPDISPATCH		lpDispatch;
	long			i,lCount;

	//CoInitialize(NULL);
	// ����XML����
	strKey =_T("msxml2.domdocument");
	BOOL bData = oXMLDOMDocument.CreateDispatch(strKey, &oError);

	oVariant = pstrXMLFilePath;
	bData = oXMLDOMDocument.load(oVariant);

	// �ҵ�������Դ������
	strKey =_T("SourceExplo");
	lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);

	// ���õ��������
	strKey = _T("Count");
	lCount = (long)(pShotSrcs->GetExploCount());
	oVariant = lCount;
	oElementParent.setAttribute(strKey, oVariant);

	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}
	// �����½ڵ�
	lCount = pShotSrcs->GetCount();
	CShotSource *pShotSource =NULL;	
	for( i = 0; i < lCount; i++)
	{
		pShotSource = pShotSrcs->GetShotSource(i);
		if(pShotSource==NULL || pShotSource->m_dwSourceType!=SHOTTYPE_EXPLO)
			continue;
		lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t\t"));
		oElementParent.appendChild(lpDispatch);

		lpDispatch = oXMLDOMDocument.createElement(_T("Record"));
		oElementChild.AttachDispatch(lpDispatch);		
		//���浥�����ڼ�¼
		SaveSourceExploRecord(&oElementChild,(CShotSourceExplo*)pShotSource);
		oElementParent.appendChild(lpDispatch);

	}
	lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t"));
	oElementParent.appendChild(lpDispatch);

	oVariant = pstrXMLFilePath;
	oXMLDOMDocument.save(oVariant);
	// �ͷŶ���
	oXMLDOMDocument.DetachDispatch();
	return lCount;
}

/******************************************************************************
    ��    ����ParseSourceExploRecord
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ����������Դ��¼

				<Record SourceStatus="0" SourceNb ="1" Label="label1" 
				ShooterNb="123456" IncrNb="1" Comment="SourceExplo��Դ����" />
    �޸���ʷ��

*******************************************************************************/
int COperationParseXML::ParseSourceExploRecord(CXMLDOMElement* pElement,CShotSourceExplo* pExploSrc)
{
	CString strKey;	// ����	
	if(NULL==pExploSrc)
		return 0;
	// ״̬
	strKey = _T("SourceStatus");
	pExploSrc->m_bySourceState =CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// ���
	strKey = _T("SourceNb");
	pExploSrc->m_dwSourceNb =CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// ��ǩ
	strKey = _T("Label");
	pExploSrc->m_strLabel =CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	// �����ɼ�վSN
	strKey = _T("ShooterNb");
	pExploSrc->m_dwShooterNb =CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// ��������������Ϊ��
	strKey = _T("IncrNb");
	pExploSrc->m_lStep =CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// Comment
	strKey = _T("Comment");
	pExploSrc->m_strComment =CXMLDOMTool::GetElementAttributeString(pElement, strKey);	
	return 1;
}
int COperationParseXML::SaveSourceExploRecord(CXMLDOMElement* pElement,CShotSourceExplo* pExploSrc)
{
	CString		strKey;	// ����	
	COleVariant oVariant;
	VARIANT		vt;
	if(NULL==pExploSrc)
		return 0;
	// ״̬	
	strKey = _T("SourceStatus");
	oVariant = pExploSrc->m_bySourceState;
	pElement->setAttribute(strKey, oVariant);
	// SourceNb
	strKey = _T("SourceNb");
	vt.vt = VT_UI4;
	vt.ulVal = pExploSrc->m_dwSourceNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);		
	// Label
	strKey =_T("Label");	
	oVariant = pExploSrc->m_strLabel;
	pElement->setAttribute(strKey, oVariant);	
	// ShooterNb
	strKey =_T("ShooterNb");
	vt.vt = VT_UI4;
	vt.ulVal = pExploSrc->m_dwShooterNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);
	// IncrNb
	strKey =_T("IncrNb");
	oVariant = pExploSrc->m_lStep;
	pElement->setAttribute(strKey, oVariant);	
	// Comment
	strKey =_T("Comment");
	oVariant = pExploSrc->m_strComment;
	pElement->setAttribute(strKey, oVariant);	
	return 1;
}
/******************************************************************************
    ��    ����ParseSourceVibro
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� �����ɿ���Դ

    �޸���ʷ��

*******************************************************************************/
int COperationParseXML::ParseSourceVibro(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs)
{
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	ULONG		dwCount;
	try
	{	//CoInitialize(NULL);
		// ����XML����
		strOLEObject =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�������Դ
		strKey =_T("SourceVibro");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����
		strKey =_T("Count");
		dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		CShotSourceVibro* pSrc = NULL;
		for(unsigned int i = 0; i < dwCount; i++)
		{
			pSrc = new CShotSourceVibro;
			// �õ�XMLԪ��
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			// ������Դ
			ParseSourceVibroRecord(&oElement, pSrc);		
			// ������Դ��
			pShotSrcs->Add(pSrc);

		}
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
	}	
	catch (CException* )
	{
		return 0;
	}
	return dwCount;
}
int COperationParseXML::SaveSourceVibro(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs)
{
	COleException	oError;
	COleVariant		oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString			strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement	oElementParent,oElementChild;
	LPDISPATCH		lpDispatch;
	long			i,lCount;
	try
	{
		//CoInitialize(NULL);
		// ����XML����
		strKey =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strKey, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�������Դ������
		strKey =_T("SourceVibro");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// ���õ��������
		strKey = _T("Count");
		lCount = (long)(pShotSrcs->GetVibroCount());
		oVariant = lCount;
		oElementParent.setAttribute(strKey, oVariant);

		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		// �����½ڵ�
		lCount = pShotSrcs->GetCount();
		CShotSource *pShotSource =NULL;	
		for( i = 0; i < lCount; i++)
		{
			pShotSource = pShotSrcs->GetShotSource(i);
			if(pShotSource==NULL || pShotSource->m_dwSourceType!=SHOTTYPE_VIBRO)
				continue;
			lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t\t"));
			oElementParent.appendChild(lpDispatch);

			lpDispatch = oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);		
			//���浥�����ڼ�¼
			SaveSourceVibroRecord(&oElementChild,(CShotSourceVibro*)pShotSource);
			oElementParent.appendChild(lpDispatch);

		}
		lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t"));
		oElementParent.appendChild(lpDispatch);

		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.save(oVariant);
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
	}	
	catch (CException* )
	{
		return 0;
	}
	return lCount;
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ���������ɿ���Դ�ļ�¼

	<Record SourceStatus="0" SourceNb ="1" Label="label1" ShooterNb="12345" 
	Moving="1" Step="1" WorkByAcq="0" ClusterNb="1" Comment="SourceVibro��Դ����" />

	�޸���ʷ��

*******************************************************************************/
int COperationParseXML::ParseSourceVibroRecord(CXMLDOMElement* pElement,CShotSourceVibro* pVibroSrc)
{
	CString strKey;	// ����	
	if(NULL==pVibroSrc)
		return 0;
	// ״̬
	strKey = _T("SourceStatus");
	pVibroSrc->m_bySourceState =CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// ���
	strKey = _T("SourceNb");
	pVibroSrc->m_dwSourceNb =CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// ��ǩ
	strKey = _T("Label");
	pVibroSrc->m_strLabel =CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	// �����ɼ�վSN
	strKey = _T("ShooterNb");
	pVibroSrc->m_dwShooterNb =CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// ��������������Ϊ��
	strKey = _T("Step");
	pVibroSrc->m_lStep =CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// Comment
	strKey = _T("Comment");
	pVibroSrc->m_strComment =CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	// ��������������Ϊ��
	strKey = _T("Moving");
	pVibroSrc->m_byMoving =(unsigned char)CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// ���ӵĶ�βɼ�
	strKey = _T("WorkByAcq");
	if(CXMLDOMTool::GetElementAttributeInt(pElement, strKey))
	    pVibroSrc->m_bWorkByAcq = TRUE;
	else
		pVibroSrc->m_bWorkByAcq = FALSE;
	// ͬʱ˫��Դ��ҵ
	strKey = _T("ClusterNb");
	pVibroSrc->m_dwClusterNb =CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	
	return 1;
}
/**
 * @brief ����ɿ���Դ������¼
 * @note  ��һ���ɿ���Դ��¼д��XML
 * @param CXMLDOMElement* pElement��XMLԪ�ض���ָ��
 * @param CShotSourceVibro* pVibroSrc���ɿ���Դ
 * @return �ɹ�����1��ʧ�ܷ���0
 */
int COperationParseXML::SaveSourceVibroRecord(CXMLDOMElement* pElement,CShotSourceVibro* pVibroSrc)
{
	CString		strKey;	// ����	
	COleVariant oVariant;
	VARIANT		vt;
	if(!pVibroSrc || !pElement)
		return 0;
	// ״̬	
	strKey = _T("SourceStatus");
	oVariant = pVibroSrc->m_bySourceState;
	pElement->setAttribute(strKey, oVariant);
	// SourceNb
	strKey = _T("SourceNb");
	vt.vt = VT_UI4;
	vt.ulVal = pVibroSrc->m_dwSourceNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);		
	// Label
	strKey =_T("Label");	
	oVariant = pVibroSrc->m_strLabel;
	pElement->setAttribute(strKey, oVariant);	
	// ShooterNb
	strKey =_T("ShooterNb");
	vt.vt = VT_UI4;
	vt.ulVal = pVibroSrc->m_dwShooterNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);
	// Moving	
	strKey = _T("Moving");
	oVariant = pVibroSrc->m_byMoving;
	pElement->setAttribute(strKey, oVariant);
	// Step
	strKey =_T("Step");
	oVariant = pVibroSrc->m_lStep;
	pElement->setAttribute(strKey, oVariant);	
	// WorkByAcq
	strKey =_T("WorkByAcq");
	if(pVibroSrc->m_bWorkByAcq)
		oVariant = 1L;
	else
		oVariant = 0L;
	pElement->setAttribute(strKey, oVariant);
	// ClusterNb
	strKey =_T("ClusterNb");
	vt.vt = VT_UI4;
	vt.ulVal = pVibroSrc->m_dwClusterNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);
	// Comment
	strKey =_T("Comment");
	oVariant = pVibroSrc->m_strComment;
	pElement->setAttribute(strKey, oVariant);	
	return 1;
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ��ȡ�ɼ����� ????????????????????

    �޸���ʷ�� 20100729: ��ǰ�ǲ��Դ��룬��ȡ10*150�Ĳɼ����У�����Ҫ�޸�

*******************************************************************************/
/**
 * @brief �����ɼ����б�
 * @note  ��XML�������ļ��ж�ȡ���ɼ����б��������CShotSpreads�С�
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotSpreads* pSpreads���ɼ����б����Ҳ�Ǵ洢�ɼ����еļ��϶���
 * @return ��ȡ�Ķ������

int COperationParseXML::ParseShotSpread(LPCTSTR pstrXMLFilePath,CShotSpreads* pSpreads)
{
	CShotSpread *pSpread = new CShotSpread;

	pSpread->m_dwNb = 1;
	int i,j;
	SHOTSPREAD    ShotSpread;
	for (i=1;i<=10;i++) // ��������
	{
		for (j=11;j<=20;j++) // ���
		{
			ShotSpread.m_dwIP = CIPList::GetCollectIP(i,j,1);
			ShotSpread.m_dwGain = 1;
			pSpread->m_arrSpread.Add(ShotSpread);
		}
	}
	pSpreads->m_AllSpread.Add(pSpread);
	return 1;
} */
/**
 * @brief ������������¼
 * @note  �������ļ��ж�ȡ������������¼��Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @return �ɹ�����1��ʧ�ܷ���0
 */
int COperationParseXML::ParseAuxChannelRecord(CXMLDOMElement* pElement,CAuxChannel* pAuxChannel)
{
	CString strKey;
	if(!pAuxChannel)
		return 0;
	strKey = _T("Nb");
	pAuxChannel->m_dwNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = _T("Label");
	pAuxChannel->m_strLabel = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	strKey = _T("BoxType");
	pAuxChannel->m_dwBoxType = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = _T("SN");
	pAuxChannel->m_dwSN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = _T("ChannelNb");
	pAuxChannel->m_dwChannelNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = _T("Gain");
	pAuxChannel->m_dwGain = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = _T("DPGNb");
	pAuxChannel->m_dwDPGNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = _T("Comments");
	pAuxChannel->m_strComments = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	// IP��ַ
	pAuxChannel->m_dwIP = CIPList::GetAuxIP(pAuxChannel->m_dwNb);		
	return 1;

}
/**
 * @brief ���ͻ��˵�ϵͳ����
 * @note  �������ļ��ж�ȡ������������Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
  * @param CAuxChannels* pAllAuxes���������������
 * @return ����������
 */
int COperationParseXML::ParseAuxChannel(LPCTSTR pstrXMLFilePath,CAuxChannels* pAllAuxes)
{
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	ULONG		dwCount;
	try
	{
		// ����XML����
		strOLEObject =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�����������
		strKey =_T("AuxSetup");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����
		strKey =_T("Count");
		dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		CAuxChannel* pAuxChannel = NULL;
		for(unsigned int i = 0; i < dwCount; i++)
		{
			pAuxChannel = new CAuxChannel;
			// �õ�XMLԪ��
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			// �õ��ں�
			ParseAuxChannelRecord(&oElement, pAuxChannel);		
			// ������ڱ�
			pAllAuxes->Add(pAuxChannel);
		}
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
		return true;
	}	
	catch (CException* )
	{
		return false;
	}
}
/**
 * @brief �����ɼ����б�
 * @note  ��XML�������ļ��ж�ȡ���ɼ����б��������CShotSpreads�С����ڲɼ����еĶ�����
 ����˵�����ߺš���ţ�û�ж�����ţ������Ҫ��2����ļ�¼�������ߺš�������ҳ����ܵ����вɼ�����
 ���ɼ�����ӵ��ɼ������С�
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotSpreads* pSpreads���ɼ����б����Ҳ�Ǵ洢�ɼ����еļ��϶���
 * @param CChannelList* pChannelList�����еĲɼ����б�
 * @return ��ȡ�Ķ��������ʧ�ܷ���-1��
 */
int COperationParseXML::ParseAllAbsoluteSpread(LPCTSTR pstrXMLFilePath,CShotSpreads* pSpreads,CChannelList* pChannelList)
{
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	ULONG		dwCount;
	try
	{
		//CoInitialize(NULL);
		// ����XML����
		strOLEObject =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�������Դ
		strKey =_T("AbsoluteSetup");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����
		strKey =_T("Count");
		dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		CShotSpread *pSpread = NULL;
		for(unsigned int i = 0; i < dwCount; i++)
		{
			pSpread= new CShotSpread;
			// �õ�XMLԪ��
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			// �����ɼ�����
			ParseShotSpreadRecord(&oElement, pSpread,pChannelList);		
			// ������Դ��
			pSpreads->Add(pSpread);

		}
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
	}	
	catch (CException* )
	{
		return -1;
	}
	return dwCount;
}


int COperationParseXML::ParseShotSpreadRecord(CXMLDOMElement* pElement, CShotSpread *pSpread,CChannelList* pChannelList)
{
	CString			strKey;	// ����	
	CString         strTemp;
	CString			strSpread;
	LPTSTR			lpStr;
	int				nPos;
	DWORD           dwLineNb,dwPointMin,dwPointMax;
	DWORD			dwGain;
	
	if(NULL==pSpread|| NULL==pChannelList)
		return 0;
	// ���
	strKey = _T("Nb");
	pSpread->m_dwNb =CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// ��ǩ
	strKey = _T("Label");
	pSpread->m_strLabel =CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	// �ɼ�����
	strKey = _T("Spread");
	strSpread =CXMLDOMTool::GetElementAttributeString(pElement, strKey);

	// �����ɼ����У�ʾ��Ϊ�� strSpread="10:101-103g1,106-115g2;20:101-103g1,106-115g2;30:101-103g1,106-115g2"
	while(strSpread!=_T(""))
	{
		nPos = strSpread.Find(_T(";"));
		if(nPos>0)
		{
			strKey = strSpread.Left(nPos);
			strSpread = strSpread.Right(strSpread.GetLength()-nPos-1);
		}
		else
		{
			strKey = strSpread;
			strSpread = _T("");
		}
		
		// �������10:101-103g1,106-115g2
		// �������к�		
		dwLineNb = _tcstoul(LPCTSTR(strKey),&lpStr,10);
		// ��ʱlpStr = :101-103g1,106-115g2
		strKey = lpStr+1;	
		do // ������ĳһ�����ߵ����е�Ŷ���
		{		
			// ��������ŵ���Сֵ
			dwPointMin= _tcstoul(LPCTSTR(strKey),&lpStr,10);
			// lpStr = -103g1,106-115g2
			strKey = lpStr+1;
			// ��������ŵ����ֵ
			dwPointMax= _tcstoul(LPCTSTR(strKey),&lpStr,10);
			// lpStr = g1,106-115g2
			strTemp = lpStr;	
			// ����������
			strKey = strTemp.Left(2);
			if(!strKey.CompareNoCase(_T("g1")))
			{
				dwGain = 1;
			}
			else
			{
				dwGain = 4;
			}
			// �Ը������߷�ΧdwPointMin - dwPointMax֮��������ڴ�
			AppendChannelsToShotSpread(dwLineNb, dwPointMin, dwPointMax,dwGain, pSpread, pChannelList);
			// �ж��Ƿ����
			nPos= strTemp.Find(_T(","));
			// �Ҳ��������������ʾ�ô����Ѿ�������ɣ��˳�������һ������
			if (nPos<=0)
			{	
				break;
			}
			// ��ú���ĵ�Ŷ��壬���� 106-115g2
			strKey = strTemp.Right(strTemp.GetLength()-nPos-1);

		} while (true);	
		
	}	
	return 1;	
}
/**
 * @brief ����ɼ������Բ�����ɼ����ж�����
 * @note  ����ĳһ��Χ�Ĳɼ������ԣ������ɼ���SHOTSPREAD����ɼ�����CShotSpread��
 * @param DWORD dwLine, �ߺ�
 * @param DWORD dwPointMin,��С���
 * @param DWORD dwPointMax,�����
 * @param DWORD dwGain,����
 * @param CShotSpread *pSpread,�ɼ����ж���
 * @param CChannelList* pChannelList 
 * @return �����ɹ�����true��ʧ�ܷ���false
 */
bool COperationParseXML::AppendChannelsToShotSpread(DWORD dwLine,DWORD dwPointMin,DWORD dwPointMax,DWORD dwGain,
													CShotSpread *pSpread,CChannelList* pChannelList)
{
	DWORD			dwIndex;
	DWORD			dwIP;
	// DWORD           dwTemp;
	SHOTSPREAD		ShotSpread;
	CChannelSetupData* pChnData=NULL;
	if(!pSpread || !pChannelList)
		return false;
	// ��ֹ����ĵ�����ֵС����Сֵ
	if(dwPointMin>dwPointMax)
	{	// �����ֵ����Сֵ����
		dwIndex=dwPointMin;
		dwPointMin = dwPointMax;
		dwPointMax = dwIndex;
	}
	for (dwIndex=dwPointMin;dwIndex<=dwPointMax;dwIndex++)
	{
		// �ߺ�
		ShotSpread.m_dwLineNb = dwLine;
		// ���
		ShotSpread.m_dwPointNb = dwIndex;
		// ����
		ShotSpread.m_dwGain = dwGain;
		// һ���ɼ�վ�¿����ж���������ҵ�һ����λ��
		dwIP = CChannelSetupData::CreateIP(dwLine,dwIndex,1);
		// �Ӳ�����ƵĶ����в�����Ӧ�Ĳɼ���
		if(!pChannelList->GetChannelFromMap(dwIP,pChnData))
		{
			continue;
		}
		// �����һ���Ķ��󣬼�¼���
		ShotSpread.m_dwChannelNb = 1;
		// IP��ַ
		ShotSpread.m_dwIP = dwIP;
		// �жϲɼ�������
		if(pChnData->m_bMute)
			ShotSpread.m_byType = CHN_MUTE;
		else
			ShotSpread.m_byType = CHN_NORMAL;
		// �������������
		if(!pChnData->m_bJumped)
			pSpread->Append(ShotSpread);
		
		// Ѱ���Ƿ���������ɼ�ͨ��
		while(pChnData!=NULL)
		{
			// ������ɼ��������������Ƿ���ͬ�Ĳ��ߡ���㣬�����ڲ�ͬ�ĵ��Ŷ���
			pChnData = pChannelList->GetChannelByIndex(pChnData->m_uiIndex+1);
			if (pChnData==NULL)
			{
				break;
			}
			// �ҵ��µĲɼ��������жϲ��ߺ͵���Ƿ�һ��
			if(pChnData->m_uiNbLine!=dwLine || pChnData->m_uiNbPoint != dwIndex)
				break;
			// ������
			if(pChnData->m_bJumped)
				continue;
			// �ɼ�����
			ShotSpread.m_dwChannelNb =pChnData->m_uiNbChannel;
			// IP��ַ
			ShotSpread.m_dwIP = pChnData->m_uiIP;
			// �жϲɼ�������
			if(pChnData->m_bMute)
				ShotSpread.m_byType = CHN_MUTE;
			else
				ShotSpread.m_byType = CHN_NORMAL;
			pSpread->Append(ShotSpread);
		}
	}
	return true;
}
/**
 * @brief �����������ͱ�
 * @note  ��XML�������ļ��ж�ȡ���ɼ����б��������CShotSpreads�С�
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotSpreads* pSpreads���ɼ����б����Ҳ�Ǵ洢�ɼ����еļ��϶���
 * @return ��ȡ�Ķ������
 */
int COperationParseXML::ParseProcessType(LPCTSTR pstrXMLFilePath,CProcessTypes* pProcesses)
{
	CString			strOLEObject;
	COleException	oError;
	COleVariant		oVariant;

	CXMLDOMDocument oXMLDOMDocument;	
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement	oElement;
	LPDISPATCH		lpDispatch;
	ULONG			dwCount;
	CString			strKey;
	BYTE            byType;	
	try
	{
		// ����XML����
		strOLEObject =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�������Դ
		strKey =_T("ProcessType");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����
		strKey =_T("Count");
		dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		CProcessType* pProcess = NULL;
		for(unsigned int i = 0; i < dwCount; i++)
		{		
			// �õ�XMLԪ��
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			strKey =_T("Type");	// �õ������������ͣ��������ʹ�����ͬ����
			byType = (BYTE)CXMLDOMTool::GetElementAttributeInt(&oElement,strKey);
			switch(byType )
			{
			case PROCESS_IMPULSIVE:
				pProcess = new CProcessImpulsive;
				ParseProcessImpulsive(&oElement,(CProcessImpulsive*)pProcess);
				pProcesses->Add(pProcess);// ������Դ��
				break;
			default:
				break;
			}		
		}
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();		
	}	
	catch (CException* )
	{
		return 0;
	}
	return dwCount;

}

/**
 * @brief ����������
 * @note  ��XML�������ļ��ж�ȡ��ĳһ���������͵ĸ��������������CProcessType�С�
		����������
		<Auxiliaries Count="1"  CorreWith = "Pilot" >	
			<Record AuxiNb ="1" AuxiProcessing="Aux1*Aux2"  />
		</Auxiliaries>    

 * @param CXMLDOMElement* pElement��ָ�򸸽ڵ�ProcessRecordԪ�ص�ָ��
 * @param CProcessType* pProcess���������Ͷ���
 * @return ��ȡ�Ķ������
 */
int COperationParseXML::ParseProcessAuxi(CXMLDOMElement* pElement,CProcessType* pProcess)
{
	CXMLDOMNodeList oNodeList;	
	CXMLDOMElement	oElement;
	LPDISPATCH		lpDispatch;
	ULONG			dwCount;
	CString			strKey;
	if(NULL==pProcess || NULL==pElement)
		return 0;
	try
	{
		lpDispatch = pElement->get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);

		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����
		strKey =_T("Count");
		dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// �õ�����
		lpDispatch = oElement.get_childNodes();
		oNodeList.AttachDispatch(lpDispatch);
		// CProcessType* pProcess = NULL;
		AUXICHANNEL  AuxiCHN;
		for(unsigned int i = 0; i < dwCount; i++)
		{		
			// �õ�XMLԪ��
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			AuxiCHN.m_dwNb = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, _T("AuxiNb"));
			strKey = CXMLDOMTool::GetElementAttributeString(&oElement, _T("AuxiProcessing"));
			_tcscpy_s(AuxiCHN.m_szProcessing,_countof(AuxiCHN.m_szProcessing),strKey);
			pProcess->m_arrAuxiChannel.Add(AuxiCHN);
		}
		return dwCount;
	}
	catch (CException* )
	{
		return 0;
	}
}

/**
 * @brief ���渨����
 * @note ĳһ���������͵ĸ��������浽XML�������ļ���
		����������
		<Auxiliaries Count="1"  CorreWith = "Pilot" >	
			<Record AuxiNb ="1" AuxiProcessing="Aux1*Aux2"  />
		</Auxiliaries>    

 * @param CXMLDOMElement* pElement��ָ�򸸽ڵ�ProcessRecordԪ�ص�ָ��
 * @param CProcessType* pProcess���������Ͷ���
 * @return ��ȡ�Ķ������
 */
int COperationParseXML::SaveProcessAuxi(CXMLDOMDocument* pXMLDOMDocument,CXMLDOMElement* pElement,CProcessType* pProcess)
{
	CXMLDOMNodeList oNodeList;	
	CXMLDOMElement	oElement;		// Auxiliaries �ڵ�
	CXMLDOMElement	oElementChild;	// ָ��Auxi ��Record�ڵ�
	LPDISPATCH		lpDispatch;
	long			lCount;
	CString			strKey;
	COleVariant     oVariant;
	VARIANT			vt;
	if(!pXMLDOMDocument || !pElement || !pProcess)
		return 0;

	lpDispatch = pXMLDOMDocument->createTextNode(_T("\r\n\t\t\t\t\t"));
	pElement->appendChild(lpDispatch);

	// ��� Auxiliaries �ڵ�
	lpDispatch = pXMLDOMDocument->createElement(_T("Auxiliaries"));
	oElement.AttachDispatch(lpDispatch);
	pElement->appendChild(lpDispatch);

	// ���õ��������
	strKey = _T("Count");
	lCount = (long)(pProcess->m_arrAuxiChannel.GetCount());
	oVariant = lCount;
	oElement.setAttribute(strKey, oVariant);
	
	// �����½ڵ�
	// lCount = pShotSrcs->GetCount();
	// CShotSource *pShotSource =NULL;	
	for(int i = 0; i < lCount; i++)
	{		
		lpDispatch = pXMLDOMDocument->createTextNode(_T("\r\n\t\t\t\t\t\t"));
		oElement.appendChild(lpDispatch);

		lpDispatch = pXMLDOMDocument->createElement(_T("Record"));
		oElementChild.AttachDispatch(lpDispatch);		
		//���浥�����ڼ�¼
		//SaveSourceVibroRecord(&oElementChild,(CShotSourceVibro*)pShotSource);
		// SourceNb
		strKey = _T("AuxiNb");
		vt.vt = VT_UI4;
		vt.ulVal = pProcess->m_arrAuxiChannel[i].m_dwNb;
		oVariant = vt;
		oElementChild.setAttribute(strKey, oVariant);		
		// Label
		strKey =_T("AuxiProcessing");		
		oVariant = pProcess->m_arrAuxiChannel[i].m_szProcessing;
		oElementChild.setAttribute(strKey, oVariant);	
		oElement.appendChild(lpDispatch);

	}
	lpDispatch = pXMLDOMDocument->createTextNode(_T("\r\n\t\t\t\t\t"));
	oElement.appendChild(lpDispatch);
	lpDispatch = pXMLDOMDocument->createTextNode(_T("\r\n\t\t\t\t"));
	pElement->appendChild(lpDispatch);
	return lCount;
}
/******************************************************************************
    ��    ����ParseProcessImpulsive
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ������������, ���� ���� Type ="0" 

	<ProcessRecord Nb="1"  Label ="record" Type ="0" ProcessSetup = "0" SerialNb = "12345"  RecordLength="7" RefractingDelay="1000" TBWindow="200">      		
		<Auxiliaries Count="1"  CorreWith = "Pilot" >	
			<Record AuxiNb ="1" AuxiProcessing="Aux1*Aux2"  />
		</Auxiliaries>      	        	   	
	</ProcessRecord>

    �޸���ʷ��

*******************************************************************************/
int COperationParseXML::ParseProcessImpulsive(CXMLDOMElement* pElement,CProcessImpulsive* pProcess)
{
	CString strKey;	// ����	
	if(NULL==pProcess)
		return 0;
	// ���
	strKey = _T("Nb");
	pProcess->m_dwProcessNb=CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// ����
	strKey = _T("Type");
	pProcess->m_byProcessType =(BYTE)CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// ��ǩ
	strKey = _T("Label");
	pProcess->m_strLabel =CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	// ���ã���׼���߼�
	strKey = _T("ProcessSetup");
	pProcess->m_ProcessSetup =(BYTE)CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// ��ը�������������ɼ�վSN
	strKey = _T("SerialNb");
	pProcess->m_dwFDUSN =CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// ��¼����
	strKey = _T("RecordLength");
	pProcess->m_dwRecordLen =CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// Refraction Delay  �����ӳ�
	strKey = _T("RefractingDelay");
	pProcess->m_dwRefractionDelay=CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
    // TB Window
	strKey = _T("TBWindow");
	pProcess->m_dwTBWindow=CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	// ������
	ParseProcessAuxi( pElement,pProcess);
	return 1;
}
/**
 * @brief �����������
 * @note ĳһ���������͵ĸ��������浽XML�������ļ���
 
 <ProcessRecord Nb="1" Label="record" Type="0" ProcessSetup="0" SerialNb="12345" RecordLength="20000" RefractingDelay="1000" TBWindow="2000">
	<Auxiliaries Count="1" CorreWith="Pilot">
		<Record AuxiNb="1" AuxiProcessing="Aux1*Aux2"/>
	</Auxiliaries>
 </ProcessRecord>   

 * @param CXMLDOMDocument* pXMLDOMDocument, XML�ĵ�����
 * @param CXMLDOMElement* pElement��ָ�򸸽ڵ�ProcessRecordԪ�ص�ָ��
 * @param CProcessType* pProcess���������Ͷ���
 * @return ��ȡ�Ķ������
 */
int COperationParseXML::SaveProcessImpulsive(CXMLDOMDocument* pXMLDOMDocument,CXMLDOMElement* pElement,CProcessImpulsive* pProcess)
{
	CString		strKey;	// ����	
	COleVariant oVariant;
	VARIANT		vt;
	if(!pProcess || !pElement || !pXMLDOMDocument)
		return 0;
	
	// Nb
	strKey = _T("Nb");
	vt.vt = VT_UI4;
	vt.ulVal = pProcess->m_dwProcessNb;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);		
	// Type
	strKey =_T("Type");	
	oVariant = pProcess->m_byProcessType;
	pElement->setAttribute(strKey, oVariant);	
	// Label
	strKey =_T("Label");
	oVariant = pProcess->m_strLabel;
	pElement->setAttribute(strKey, oVariant);
	// ProcessSetup	
	strKey = _T("ProcessSetup");
	oVariant = pProcess->m_ProcessSetup;
	pElement->setAttribute(strKey, oVariant);
	// SerialNb
	strKey =_T("SerialNb");
	vt.vt = VT_UI4;
	vt.ulVal = pProcess->m_dwFDUSN;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);
	
	// RecordLength
	strKey =_T("RecordLength");
	vt.vt = VT_UI4;
	vt.ulVal = pProcess->m_dwRecordLen;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);
	// RefractingDelay
	strKey =_T("RefractingDelay");
	vt.vt = VT_UI4;
	vt.ulVal = pProcess->m_dwRefractionDelay;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);	
	// TBWindow
	strKey =_T("TBWindow");
	vt.vt = VT_UI4;
	vt.ulVal = pProcess->m_dwTBWindow;
	oVariant = vt;
	pElement->setAttribute(strKey, oVariant);

	SaveProcessAuxi(pXMLDOMDocument, pElement,(CProcessType*)pProcess);
	return 1;
}

/**
 * @brief �����������ͱ�
 * @note  ��XML�������ļ���д��ɼ����б����CShotSpreads��
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotSpreads* pSpreads���ɼ����б����Ҳ�Ǵ洢�ɼ����еļ��϶���
 * @return �������
 */
int COperationParseXML::SaveProcessType(LPCTSTR pstrXMLFilePath,CProcessTypes* pProcesses)
{
	CString			strOLEObject;
	COleException	oError;
	COleVariant		oVariant;

	CXMLDOMDocument oXMLDOMDocument;	
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement	oElementParent,oElementChild;
	LPDISPATCH		lpDispatch;
	long			lCount;
	CString			strKey;
		
	try
	{
		//CoInitialize(NULL);
		// ����XML����
		strOLEObject =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�������Դ
		strKey =_T("ProcessType");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// ���õ��������
		strKey = _T("Count");
		lCount = (long)(pProcesses->GetCount());
		oVariant = lCount;
		oElementParent.setAttribute(strKey, oVariant);
		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		CProcessType* pProcess = NULL;
		for( int i = 0; i < lCount; i++)
		{		
			lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t\t"));
			oElementParent.appendChild(lpDispatch);

			lpDispatch = oXMLDOMDocument.createElement(_T("ProcessRecord"));
			oElementChild.AttachDispatch(lpDispatch);		
			//���浥�����ڼ�¼
			pProcess = pProcesses->GetProcessType(i);
			switch(pProcess->m_byProcessType )
			{
			case PROCESS_IMPULSIVE:
				SaveProcessImpulsive(&oXMLDOMDocument,&oElementChild,(CProcessImpulsive*)pProcess);
				break;
			default:
				break;
			}	

			oElementParent.appendChild(lpDispatch);	
		}
		lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t"));
		oElementParent.appendChild(lpDispatch);

		oVariant = pstrXMLFilePath;	
		oXMLDOMDocument.save(oVariant);
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
		theApp.SaveXMLToFTPServer();
	}	
	catch (CException* )
	{
		return 0;
	}
	return lCount;

}
