#include "StdAfx.h"
#include "ConfigParseXML.h"

CConfigParseXML::CConfigParseXML(void)
{
}

CConfigParseXML::~CConfigParseXML(void)
{

}
/**
 * @brief ���ɼ�վ���ò���
 * @note  �������ļ��ж�ȡ�ɼ�վ���ò���
 * @param CXMLDOMDocument* pXMLDOMDocument��XML�ĵ�ָ�� 
 * @param CInstallParam* pFDUConfig, ��װ������
 * @return �����Ƿ�ɹ�
 */
bool  CConfigParseXML::ParseFDUConfig(CXMLDOMDocument* pXMLDOMDocument,CFDUConfig* pFDUConfig)
{		
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	

	if(!pFDUConfig || !pXMLDOMDocument)
		return false;
	try
	{	
		// �ҵ����
		strKey =_T("CrewSetup");
		lpDispatch = pXMLDOMDocument->getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("CrewName");
		pFDUConfig->m_strCrewName= CXMLDOMTool::GetElementAttributeString(&oElement, strKey);

		// �ҵ����
		strKey =_T("samplerate");
		lpDispatch = pXMLDOMDocument->getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwSampleRateIndex = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("FilterFIR");
		lpDispatch = pXMLDOMDocument->getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwFilterFIRIndex = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("FilterIIR");
		lpDispatch = pXMLDOMDocument->getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwFilterIIRIndex = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("Gain3301");
		lpDispatch = pXMLDOMDocument->getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwGain3301Index = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("Mux3301");
		lpDispatch = pXMLDOMDocument->getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwMux3301Index = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("Mode5373");
		lpDispatch = pXMLDOMDocument->getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwMode5373Index = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		// �ҵ����
		strKey =_T("Attr5373");
		lpDispatch = pXMLDOMDocument->getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Index");
		pFDUConfig->m_dwAttr5373Index = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

		return true;
	}
	catch (CException* )
	{
		return false;
	}
}
/**
 * @brief �����ó�������ò���
 * @note  �������ļ��ж�ȡ���ó�������ò���
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CInstallParam* pFDUConfig, ��װ������
 * @return �����Ƿ�ɹ�
 */
bool  CConfigParseXML::ParseCrewConfig(LPCTSTR pstrXMLFilePath,CFDUConfig* pFDUConfig)
{
	if(!pFDUConfig)
		return false;
	try
	{	
		COleException oError;
		COleVariant oVariant;
		CString strTemp;
		CXMLDOMDocument oXMLDOMDocument;
		// ����XML����
		strTemp =_T("msxml2.domdocument");
		oXMLDOMDocument.CreateDispatch(strTemp, &oError);

		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.load(oVariant);

		ParseFDUConfig(&oXMLDOMDocument,pFDUConfig);
		oXMLDOMDocument.DetachDispatch();
		return true;
	}
	catch (CException* )
	{
		return false;
	}
}
/**
 * @brief �洢���ó����вɼ�վ�Ĳ���������Ϣ
 * @note  �����ó���������ļ���д��ɼ�վ������Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CFDUConfig* pFDUConfig, ����������ɼ�վ���ò���
 * @return �����Ƿ�ɹ�
 */
bool  CConfigParseXML::WriteCrewConfig(LPCTSTR pstrXMLFilePath,CFDUConfig* pFDUConfig)
{
	if(!pFDUConfig)
		return false;
	CString strKey;
	CString strTemp;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	
	VARIANT		vtVal;
	try
	{		
		CXMLDOMDocument oXMLDOMDocument;
		// ����XML����
		strTemp =_T("msxml2.domdocument");
		oXMLDOMDocument.CreateDispatch(strTemp, &oError);
		
		oXMLDOMDocument.put_preserveWhiteSpace(TRUE);
		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.load(oVariant);
		
		// �ҵ�Crew����
		strKey =_T("CrewSetup");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);		
		oVariant = pFDUConfig->m_strCrewName;
		oElement.setAttribute(_T("CrewName"), oVariant);

		// �ҵ�samplerate����
		strKey =_T("samplerate");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		vtVal.vt = VT_UI4;
		vtVal.ulVal = pFDUConfig->m_dwSampleRateIndex;
		oVariant = vtVal;
		oElement.setAttribute(_T("Index"), oVariant);
		
		// �ҵ�Gain3301����
		strKey =_T("Gain3301");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);	
		vtVal.vt = VT_UI4;
		vtVal.ulVal = pFDUConfig->m_dwGain3301Index;
		oVariant = vtVal;
		oElement.setAttribute(_T("Index"), oVariant);
		// �ҵ�FilterFIR����
		strKey =_T("FilterFIR");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		vtVal.vt = VT_UI4;
		vtVal.ulVal = pFDUConfig->m_dwFilterFIRIndex;
		oVariant = vtVal;
		oElement.setAttribute(_T("Index"), oVariant);

		// �ҵ�FilterIIR����
		strKey =_T("FilterIIR");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);	
		vtVal.vt = VT_UI4;
		vtVal.ulVal = pFDUConfig->m_dwFilterIIRIndex;
		oVariant = vtVal;
		oElement.setAttribute(_T("Index"), oVariant);
		// �ҵ�Mux3301����
		strKey =_T("Mux3301");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);		
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		vtVal.vt = VT_UI4;
		vtVal.ulVal = pFDUConfig->m_dwMux3301Index;
		oVariant = vtVal;
		oElement.setAttribute(_T("Index"), oVariant);
		// �ҵ�Mode5373����
		strKey =_T("Mode5373");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);		
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		vtVal.vt = VT_UI4;
		vtVal.ulVal = pFDUConfig->m_dwMode5373Index;
		oVariant = vtVal;
		oElement.setAttribute(_T("Index"), oVariant);
		// �ҵ�Attr5373����
		strKey =_T("Attr5373");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);		
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		vtVal.vt = VT_UI4;
		vtVal.ulVal = pFDUConfig->m_dwAttr5373Index;
		oVariant = vtVal;
		oElement.setAttribute(_T("Index"), oVariant);

		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.save(oVariant);
		oXMLDOMDocument.DetachDispatch();
		return true;
	}	
	catch (CException* )
	{
		return false;
	}
}
/**
 * @brief �������ó������û���Ϣ���ò���
 * @note  �������ó������û���Ϣ���ò���
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CString&  strUserInfo, ��������������û�������Ϣ
 * @return �����Ƿ�ɹ�
 */
bool  CConfigParseXML::ParseUserInfo(LPCTSTR pstrXMLFilePath,CString&  strUserInfo)
{	
	try
	{	
		CXMLDOMNodeList oNodeList;
		CXMLDOMElement oElement;
		LPDISPATCH lpDispatch;	

		COleException oError;
		COleVariant oVariant;
		CString strKey;
		CXMLDOMDocument oXMLDOMDocument;
		// ����XML����
		strKey =_T("msxml2.domdocument");
		oXMLDOMDocument.CreateDispatch(strKey, &oError);

		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.put_preserveWhiteSpace(TRUE);
		oXMLDOMDocument.load(oVariant);
		
		// �ҵ����
		strKey =_T("UserInfo");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�����ֵ
		strKey =_T("Text");
		strUserInfo= CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		
		oXMLDOMDocument.DetachDispatch();
		return true;
	}
	catch (CException* )
	{
		return false;
	}
}

/**
 * @brief д�û���Ϣ����
 * @note  ��XML�����ļ���д���û���Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CString&  strUserInfo, �û���Ϣ����
 * @return �����Ƿ�ɹ�
 */
bool  CConfigParseXML::WriteUserInfo(LPCTSTR pstrXMLFilePath,CString&  strUserInfo)
{
	CString strKey;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	

	try
	{		
		CXMLDOMDocument oXMLDOMDocument;
		// ����XML����
		strKey =_T("msxml2.domdocument");
		oXMLDOMDocument.CreateDispatch(strKey, &oError);

		oXMLDOMDocument.put_preserveWhiteSpace(TRUE);
		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.load(oVariant);

		// �ҵ�Crew����
		strKey =_T("UserInfo");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);		
		oVariant = strUserInfo;
		oElement.setAttribute(_T("Text"), oVariant);
		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.save(oVariant);
		oXMLDOMDocument.DetachDispatch();
		return true;
	}	
	catch (CException* )
	{
		return false;
	}
}
/**
 * @brief �������ó����д������ò���
 * @note  �������ó����д������ò���
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CDiskRecordConfig* pDiskRecord, ������������ش��̵�Ŀ¼��
 * @return �����Ƿ�ɹ�
 */
bool  CConfigParseXML::ParseDiskRecord(LPCTSTR pstrXMLFilePath,CDiskRecordConfig* pDiskRecord)
{
	try
	{	
		CXMLDOMNodeList oNodeList;
		CXMLDOMElement oElement;
		LPDISPATCH lpDispatch;	

		COleException	oError;
		COleVariant		oVariant;
		CString			strKey;
		CString         strTemp;
		int             nTemp;
		CXMLDOMDocument oXMLDOMDocument;
		// ����XML����
		strKey =_T("msxml2.domdocument");
		oXMLDOMDocument.CreateDispatch(strKey, &oError);

		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.put_preserveWhiteSpace(TRUE);
		oXMLDOMDocument.load(oVariant);

		// �ҵ����
		strKey =_T("DiskRecord");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// Mode
		strKey =_T("Mode");
	    strTemp= CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		if(strTemp.CompareNoCase(_T("Advanced"))==0)
		{
			pDiskRecord->SetDiskRecordMode(1);
		}
		else
		{
			pDiskRecord->SetDiskRecordMode(0);
		}
		// BackupSettings
		strKey =_T("BackupSettings");
		nTemp= CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		pDiskRecord->SetBackupSetting(nTemp);
		// FileDirectory
		strKey =_T("FileDirectory");
		strTemp= CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		pDiskRecord->SetFilePath(strTemp);

		oXMLDOMDocument.DetachDispatch();
		return true;
	}
	catch (CException* )
	{
		return false;
	}
}
/**
 * @brief д����������Ϣ
 * @note  ��XML�����ļ���д�����������Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CDiskRecordConfig* pDiskRecord, ����������Ϣ����
 * @return �����Ƿ�ɹ�
 */
bool  CConfigParseXML::WriteDiskRecord(LPCTSTR pstrXMLFilePath,CDiskRecordConfig* pDiskRecord)
{

	CString strKey;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	

	try
	{		
		CXMLDOMDocument oXMLDOMDocument;
		// ����XML����
		strKey =_T("msxml2.domdocument");
		oXMLDOMDocument.CreateDispatch(strKey, &oError);
		oXMLDOMDocument.put_preserveWhiteSpace(TRUE);
		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.load(oVariant);

		// �ҵ�DiskRecord����
		strKey =_T("DiskRecord");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// Mode
		if(pDiskRecord->GetDiskRecordMode())
		{
			strKey = _T("Advanced");
		}
		else
		{
			strKey = _T("Standard");
		}
		oVariant = strKey;
		oElement.setAttribute(_T("Mode"), oVariant);
		// BackupSettings
		oVariant = (long)(pDiskRecord->GetBackupSetting());
		oElement.setAttribute(_T("BackupSettings"), oVariant);
		// FileDirectory
		oVariant = pDiskRecord->GetFilePath();
		oElement.setAttribute(_T("FileDirectory"), oVariant);

		oVariant = pstrXMLFilePath;
		oXMLDOMDocument.save(oVariant);
		oXMLDOMDocument.DetachDispatch();
		return true;
	}	
	catch (CException* )
	{
		return false;
	}
}