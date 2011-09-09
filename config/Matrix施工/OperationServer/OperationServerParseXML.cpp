#include "StdAfx.h"
#include "OperationServer.h"
#include "OperationServerParseXML.h"

COperationServerParseXML::COperationServerParseXML(void)
{
}

COperationServerParseXML::~COperationServerParseXML(void)
{
}
/**
 * @brief �ַ�������IP��ַ����ת��
 * @note  ���ַ������͵�IP��ַת��Ϊ������
 * @param CString& strIP��IP��ַ�ַ��� 
 * @return ������IP��ַ
 */
DWORD COperationServerParseXML::StringIPToDWORDIP(CString& strIP)
{	
	DWORD dwIP;
	DWORD  by1,by2,by3,by4;
	strIP.Replace(_T("."),_T(" "));
	_stscanf_s(LPCTSTR(strIP),_T("%d %d %d %d"),&by1,&by2,&by3,&by4);
	dwIP= by4;
	dwIP= dwIP<<8 | by3;
	dwIP= dwIP<<8 | by2;
	dwIP= dwIP<<8 | by1;
	return dwIP;
}
/**
 * @brief ���ͻ��˵�ϵͳ����
 * @note  �������ļ��ж�ȡ����IP��������վ����Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @return �����Ƿ�ɹ�
 */
bool COperationServerParseXML::ParseServerSetup(LPCTSTR pstrXMLFilePath)
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

		// �ҵ�ʩ��������
		strKey =_T("OperationServer");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// �õ�ʩ��������IP��ַ
		strKey =_T("HostIP");
		strTemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		theApp.m_strHostIP = strTemp;
		theApp.m_dwHostIP = StringIPToDWORDIP(strTemp);
		// �õ����ݴ洢·��
		//strKey =_T("RevFilePath");
		//theApp.m_strFilePath = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		//theApp.m_strFilePath +=_T("\\");

		// �ҵ�������վ
		strKey =_T("MainCross");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// �õ�������վIP��ַ
		strKey =_T("MainCrossIP");
		strTemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);		
		theApp.m_dwMainCrossIP = StringIPToDWORDIP(strTemp);
		// �õ�������վ�˿�
		strKey =_T("MainCrossPort");
		theApp.m_wMainCrossPort = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
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
 * @brief д��������ϵͳ����
 * @note  ��ʩ���������������ļ���д������IP����Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @return �����Ƿ�ɹ�
 */
bool COperationServerParseXML::WriteServerSetup(LPCTSTR pstrXMLFilePath)
{
	CString strKey;
	CString strTemp;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;	
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	
	
	try
	{
		// ����XML����
		strTemp =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strTemp, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�ʩ��������
		strKey =_T("OperationServer");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// ���汾��IP��ַ
		oVariant = theApp.m_strHostIP;
		oElement.setAttribute(_T("HostIP"), oVariant);
		// �������ݴ洢��·��
		// oVariant = theApp.m_strFilePath;
		// oElement.setAttribute(_T("RevFilePath"), oVariant);

		/*
		// �ҵ�����վ����
		strKey =_T("MainCross");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// ����������վ��ַ
		oVariant = inet_ntoa(theApp.m_dwMainCrossIP);
		oElement.setAttribute(_T("MainCrossIP"), oVariant);
		// �������ݴ洢��·��
		//oVariant = theApp.m_strFilePath;
		//oElement.setAttribute(_T("RevFilePath"), oVariant);
		*/
		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.save(oVariant);
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
 * @brief ���Ľ���SEGD�ļ����
 * @note  �������ļ����ϴγ�����������¼��SEGD�ļ����
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @return �ɹ������ϴγ�������ʱSEGD�ļ���ţ�ʧ�ܷ���0
 */
DWORD COperationServerParseXML::ParseLastUsedSEGDFileNumber(LPCTSTR pstrXMLFilePath)
{
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	
	DWORD		dwSEGDFIleNumber=0;
	try
	{	// ����XML����
		strKey =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strKey, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ����̼�¼
		strKey =_T("DiskRecord");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// �õ�LastusedSEGDFileNumber
		strKey =_T("LastusedSEGDFileNumber");
		dwSEGDFIleNumber = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
		
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
		return dwSEGDFIleNumber;
	}
	catch (CException* )
	{
		return 0;
	}
}
/**
 * @brief ���Ľ���SEGD�ļ����
 * @note  �������ļ����ϴγ�����������¼��SEGD�ļ����
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @return �ɹ������ϴγ�������ʱSEGD�ļ���ţ�ʧ�ܷ���0
 */
bool COperationServerParseXML::WriteLastUsedSEGDFileNumber(LPCTSTR pstrXMLFilePath,DWORD dwSEGDFileNumber)
{
	CString strKey;
	CString strTemp;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;	
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	
	
	try
	{
		// ����XML����
		strTemp =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strTemp, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�ʩ��������
		strKey =_T("DiskRecord");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �����ļ����
		oVariant = (long)dwSEGDFileNumber;
		oElement.setAttribute(_T("LastusedSEGDFileNumber"), oVariant);
	
		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.save(oVariant);
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
 * @brief ������������¼
 * @note  �������ļ��ж�ȡ������������¼��Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @return �ɹ�����1��ʧ�ܷ���0
 
int COperationServerParseXML::ParseAuxChannelRecord(CXMLDOMElement* pElement,CAuxChannel* pAuxChannel)
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

}*/
/**
 * @brief ���ͻ��˵�ϵͳ����
 * @note  �������ļ��ж�ȡ������������Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
  * @param CAuxChannels* pAllAuxes���������������
 * @return ����������
 
int COperationServerParseXML::ParseAuxChannel(LPCTSTR pstrXMLFilePath,CAuxChannels* pAllAuxes)
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
		return dwCount;
	}	
	catch (CException* )
	{
		return false;
	}
}*/