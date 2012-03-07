#include "StdAfx.h"
#include "StartParseXML.h"

CStartParseXML::CStartParseXML(void)
{
}

CStartParseXML::~CStartParseXML(void)
{
}
/**
 * @brief ��ȡ�ͻ�����IP��ַ
 * @note  �������ļ��ж�ȡ�ͻ�����IP��ַ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CString& strIP, ��������������ͻ���IP
 * @return �ɹ�����true��ʧ�ܷ���false
 */
bool  CStartParseXML::ParseClientComputer(LPCTSTR pstrFilePath,CString& strIP,CString& strFTPIP)
{
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	
	
	try
	{	// ����XML����
		strKey =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strKey, &oError);

		oVariant = pstrFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�����ClientComputer
		strKey =_T("ClientComputer");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);		
		// �ͻ�����IP
		strKey =_T("HostIP");
		strIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);

		// �ҵ�����FTPServer
		strKey =_T("FTPServer");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// FTP��IP
		strKey =_T("HostIP");
		strFTPIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);	

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
 * @brief �洢��װ���������
 * @note  �������ļ���д�밲װ��������ò���
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CInstallParam* pInstallParam, ��װ������
 * @return �����Ƿ�ɹ�

bool  CStartParseXML::WriteInstallParam(LPCTSTR pstrFilePath,CInstallParam* pInstallParam)
{
	if(!pInstallParam)
		return false;
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

		oVariant = pstrFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�ʩ��������
		strKey =_T("Peripherals");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �ɿ���Դ����
		pInstallParam->GetVibratorType(strTemp);
		oVariant = strTemp;
		oElement.setAttribute(_T("VibratorType"), oVariant);
		// ��ը��Դ����
		pInstallParam->GetBlasterType(strTemp);
		oVariant = strTemp;
		oElement.setAttribute(_T("BlasterType"), oVariant);
		// ��ը��Դ������		
		oVariant = (long)pInstallParam->m_nBlasterBaudRate;
		oElement.setAttribute(_T("BlasterBaudRate"), oVariant);
		// ��ͼ�Ǹ���		
		oVariant = (long)pInstallParam->m_nNbOfPlotters;
		oElement.setAttribute(_T("NbOfPlotters"), oVariant);
		
		// ��ͼ��1����
		pInstallParam->GetBlasterTypeByNb(pInstallParam->m_nPlotterType1,strTemp);
		oVariant = strTemp;
		oElement.setAttribute(_T("PlotterType1"), oVariant);		
		// ��ͼ��1 Name
		oVariant = pInstallParam->m_strPlotterName1;
		oElement.setAttribute(_T("PlotterName1"), oVariant);		
		// ��ͼ��1 Mac��ַ
		oVariant = pInstallParam->m_strPlotterMacAddress1;
		oElement.setAttribute(_T("PlotterMacAddress1"), oVariant);
		// ��ͼ��2����
		pInstallParam->GetBlasterTypeByNb(pInstallParam->m_nPlotterType2,strTemp);
		oVariant = strTemp;
		oElement.setAttribute(_T("PlotterType2"), oVariant);		
		// ��ͼ��2 Name
		oVariant = pInstallParam->m_strPlotterName2;
		oElement.setAttribute(_T("PlotterName2"), oVariant);		
		// ��ͼ��2 Mac��ַ
		oVariant = pInstallParam->m_strPlotterMacAddress2;
		oElement.setAttribute(_T("PlotterMacAddress2"), oVariant);

		oVariant = pstrFilePath;
		oXMLDOMDocument.save(oVariant);
		// �ͷŶ���
		oXMLDOMDocument.DetachDispatch();
		return true;
	}	
	catch (CException* )
	{
		return false;
	}
} */