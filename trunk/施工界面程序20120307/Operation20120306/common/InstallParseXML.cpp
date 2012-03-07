#include "StdAfx.h"
#include "InstallParseXML.h"

CInstallParseXML::CInstallParseXML(void)
{
}

CInstallParseXML::~CInstallParseXML(void)
{
}
/**
 * @brief ����װ���������
 * @note  �������ļ��ж�ȡ��װ��������ò���
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CInstallParam* pInstallParam, ��װ������
 * @return �����Ƿ�ɹ�
 */
bool  CInstallParseXML::ParseInstallParam(LPCTSTR pstrFilePath,CInstallParam* pInstallParam)
{
	if(!pInstallParam)
		return false;
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

		oVariant = pstrFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�����
		strKey =_T("Peripherals");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		
		// �õ��ɿ���Դ����
		strKey =_T("VibratorType");
		strTemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		pInstallParam->SetVibratorType(strTemp);		
		// �õ���ը������
		strKey =_T("BlasterType");
		strTemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		pInstallParam->SetBlasterType(strTemp);
		// �õ�������
		strKey =_T("BlasterBaudRate");
		pInstallParam->m_nBlasterBaudRate = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// �õ���ͼ�Ǹ���
		strKey =_T("NbOfPlotters");
		pInstallParam->m_nNbOfPlotters= CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		// ��ͼ��1����
		strKey =_T("PlotterType1");
		strTemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		pInstallParam->m_nPlotterType1 = pInstallParam->GetBlasterNbByType(strTemp);
		// ��ͼ��1 Name
		strKey =_T("PlotterName1");
		pInstallParam->m_strPlotterName1 = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		// ��ͼ��1 Mac��ַ
		strKey =_T("PlotterMacAddress1");
		pInstallParam->m_strPlotterMacAddress1 = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		// ��ͼ��2����
		strKey =_T("PlotterType2");
		strTemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		pInstallParam->m_nPlotterType2 = pInstallParam->GetBlasterNbByType(strTemp);
		// ��ͼ��2 Name
		strKey =_T("PlotterName2");
		pInstallParam->m_strPlotterName2 = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		// ��ͼ��2 Mac��ַ
		strKey =_T("PlotterMacAddress2");
		pInstallParam->m_strPlotterMacAddress2 = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);


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
 */
bool  CInstallParseXML::WriteInstallParam(LPCTSTR pstrFilePath,CInstallParam* pInstallParam)
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
}