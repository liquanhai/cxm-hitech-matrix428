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
DWORD COperationParseXML::StringIPToDWORDIP(CString& strIP)
{
	DWORD  by1,by2,by3,by4;
	DWORD dwIP;
	strIP.Replace(_T("."),_T(" "));
	_stscanf_s(LPCTSTR(strIP),_T("%d%d%d%d"),&by1,&by2,&by3,&by4);
	dwIP= by4;
	dwIP= dwIP<<8 | by3;
	dwIP= dwIP<<8 | by2;
	dwIP= dwIP<<8 | by1;
	return dwIP;
}
/**
 * @brief ���ͻ��˵�ϵͳ����
 * @note  �������ļ��ж�ȡ�ͻ��˵�����IP����Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @return �����Ƿ�ɹ�
 */
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

		// �õ��ͻ���IP��ַ
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
}
/**
 * @brief �����ɼ�վ������Ϣ
 * @note  ��XML�����ļ��н������ɼ�վ�Ļ���������Ϣ����Ҫ
 ������ǰ�÷Ŵ�ģ����ѡ��5373ģʽ��DA˥���������ʡ�IIRѡ��FIRѡ��
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CFDUConfig* pFDUConfig�����ö���
 * @return ��ȡ�Ķ������
 */
int COperationParseXML::ParseFDUConfig(LPCTSTR pstrXMLFilePath,CFDUConfig* pFDUConfig)
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
		return -1;
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
	strKey =_T("Comments");
	pVP->m_szComments= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
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
	//CoUninitialize();
	return dwCount;

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

	//CoInitialize(NULL);
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
	//CoUninitialize();
	return dwCount;
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
	    pVibroSrc->m_bWorkByAcq = true;
	else
		pVibroSrc->m_bWorkByAcq = false;
	// ͬʱ˫��Դ��ҵ
	strKey = _T("ClusterNb");
	pVibroSrc->m_dwClusterNb =CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	
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
 * @brief �����ɼ����б�
 * @note  ��XML�������ļ��ж�ȡ���ɼ����б��������CShotSpreads�С����ڲɼ����еĶ�����
 ����˵�����ߺš���ţ�û�ж�����ţ������Ҫ��2����ļ�¼�������ߺš�������ҳ����ܵ����вɼ�����
 ���ɼ�����ӵ��ɼ������С�
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CShotSpreads* pSpreads���ɼ����б����Ҳ�Ǵ洢�ɼ����еļ��϶���
 * @param CChannelList* pChannelList�����еĲɼ����б�
 * @return ��ȡ�Ķ������
 */
int COperationParseXML::ParseShotSpread(LPCTSTR pstrXMLFilePath,CShotSpreads* pSpreads,CChannelList* pChannelList)
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
				dwGain = 1600;
			}
			else
			{
				dwGain = 400;
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
		// ���ҵ�һ����λ��
		dwIP = CChannelSetupData::CreateIP(dwLine,dwIndex,1);
		if(!pChannelList->GetChannelFromMap(dwIP,pChnData))
		{
			continue;
		}
		// �ҵ���һ���Ķ��󣬼�¼���
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
		
		// Ѱ���Ƿ����
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
	//CoUninitialize();
	return dwCount;

}
/****************************************************************************************
    ��    ����ParseProcessAuxi
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�����������

			<Auxiliaries Count="1"  CorreWith = "Pilot" >	
				<Record AuxiNb ="1" AuxiProcessing="Aux1*Aux2"  />
			</Auxiliaries>    
    �޸���ʷ��	   

*****************************************************************************************/
int COperationParseXML::ParseProcessAuxi(CXMLDOMElement* pElement,CProcessType* pProcess)
{
	CXMLDOMNodeList oNodeList;	
	CXMLDOMElement	oElement;
	LPDISPATCH		lpDispatch;
	ULONG			dwCount;
	CString			strKey;
	if(NULL==pProcess || NULL==pElement)
		return 0;

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
		_tcscpy_s(AuxiCHN.m_szProcessing,256,strKey);
		pProcess->m_arrAuxiChannel.Add(AuxiCHN);
	}
	return dwCount;
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