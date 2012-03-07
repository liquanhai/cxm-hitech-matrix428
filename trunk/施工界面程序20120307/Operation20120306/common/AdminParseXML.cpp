#include "StdAfx.h"
#include "AdminParseXML.h"

CAdminParseXML::CAdminParseXML(void)
{
}

CAdminParseXML::~CAdminParseXML(void)
{

}
/**
 * @brief �������ó������û���Ϣ
 * @note  �������ó������û���Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CUserInfo*  pUserInfo, �û�����
 * @return �����Ƿ�ɹ�
 */
bool  CAdminParseXML::ParseUserInfo(CXMLDOMElement* pElement,CUserInfo*  pUserInfo)
{	
	try
	{	
		CString strKey,strTemp;	// ����	
		if(NULL==pUserInfo)
			return false;
		// �û���
		strKey =_T("UserName");
		pUserInfo->m_strUserName = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		// ���� 
		strKey =_T("Password");
		pUserInfo->m_strPassword= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		// ��ɫ
		strKey =_T("UserRole");
		strTemp = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		if(strTemp.CompareNoCase(_T("Guest"))==0)
		{
			pUserInfo->m_nRole = USERINFO_ROLE_GUEST;
		}
		else if(strTemp.CompareNoCase(_T("Observer"))==0)
		{
			pUserInfo->m_nRole = USERINFO_ROLE_OBSERVER;
		}
		else if(strTemp.CompareNoCase(_T("Senior Observer"))==0)
		{
			pUserInfo->m_nRole = USERINFO_ROLE_SENIOROBSERVER;
		}
		else
		{
			pUserInfo->m_nRole = USERINFO_ROLE_GUEST;
		}
		// ע������
		strKey =_T("RegistrationDate");
		strTemp= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strTemp.Replace(':',' ');
		strTemp.Replace('-',' ');
		_stscanf_s((LPCTSTR)strTemp,_T("%d %d %d %d %d %d"),&pUserInfo->m_tmRegister.wYear,
			&pUserInfo->m_tmRegister.wMonth,&pUserInfo->m_tmRegister.wDay,&pUserInfo->m_tmRegister.wHour,
			&pUserInfo->m_tmRegister.wMinute,&pUserInfo->m_tmRegister.wSecond);
		// ���ں���ʽ
		strKey =_T("ExpiredMode");
		pUserInfo->m_nExpiredMode = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
		// ʧЧ����
		strKey =_T("ExpiryDate");
		strTemp= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strTemp.Replace(':',' ');
		strTemp.Replace('-',' ');
		_stscanf_s((LPCTSTR)strTemp,_T("%d %d %d %d %d %d"),&pUserInfo->m_tmExpiryDate.wYear,
			&pUserInfo->m_tmExpiryDate.wMonth,&pUserInfo->m_tmExpiryDate.wDay,&pUserInfo->m_tmExpiryDate.wHour,
			&pUserInfo->m_tmExpiryDate.wMinute,&pUserInfo->m_tmExpiryDate.wSecond);
		// �Ƿ��Զ�ɾ��
		strKey =_T("AutoDelete");
		pUserInfo->m_bAutoDelete = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
		// ��¼����
		strKey =_T("LastUsed");
		strTemp= CXMLDOMTool::GetElementAttributeString(pElement, strKey);
		strTemp.Replace(':',' ');
		strTemp.Replace('-',' ');
		_stscanf_s((LPCTSTR)strTemp,_T("%d %d %d %d %d %d"),&pUserInfo->m_tmLastUsed.wYear,
			&pUserInfo->m_tmLastUsed.wMonth,&pUserInfo->m_tmLastUsed.wDay,&pUserInfo->m_tmLastUsed.wHour,
			&pUserInfo->m_tmLastUsed.wMinute,&pUserInfo->m_tmLastUsed.wSecond);
		return true;
	}
	catch (CException* )
	{
		return false;
	}
}
bool  CAdminParseXML::ParseHostConfig(LPCTSTR pstrXMLFilePath,CString& strIP)
{
	try
	{
		CString strOLEObject;
		COleException oError;
		COleVariant oVariant;

		CXMLDOMDocument oXMLDOMDocument;
		CString strKey;
		CXMLDOMNodeList oNodeList;
		CXMLDOMElement oElement;
		LPDISPATCH lpDispatch;

		//CoInitialize(NULL);
		// ����XML����
		strOLEObject =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// --------------------------------
		// �ҵ�AdminServer
		strKey =_T("AdminServer");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);
		// �õ�IP
		strKey =_T("IP");
		strIP = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		
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
 * @brief �����û��˺�����
 * @note  ��XML�������ļ��ж�ȡ�������û����˺���Ϣ�������û����󼯺�CUserInfos��
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·��
 * @param CUserInfos*  pUserInfos���û����󼯺�
 * @return bool���ɹ��򷵻�true��ʧ�ܷ���false
 */
bool  CAdminParseXML::ParseAllUserInfo(LPCTSTR pstrXMLFilePath,CUserInfos*  pUserInfos)
{
	try
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
	
		// -------------------------------------
		// �ҵ�Users
		strKey =_T("Users");
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

		CUserInfo* pUserInfo = NULL;
		for(unsigned int i = 0; i < dwCount; i++)
		{
			pUserInfo = new CUserInfo;
			// �õ�XMLԪ��
			lpDispatch = oNodeList.get_item(i);
			oElement.AttachDispatch(lpDispatch);
			// �õ�User
			ParseUserInfo(&oElement, pUserInfo);		
			// ������ڱ�
			pUserInfos->Add(pUserInfo);		
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
 * @brief ����һ���û���Ϣ
 * @note  ��XML�����ļ���д��һ���û���Ϣ
 * @param CXMLDOMElement* pElement��XMLָ��
 * @param CUserInfo*  pUserInfo, ���е��û���Ϣ����
 * @return д���Ƿ�ɹ�
 */
bool  CAdminParseXML::WriteUserInfo(CXMLDOMElement* pElement,CUserInfo*  pUserInfo)
{
	CString strKey,strTemp;	
	COleVariant   oVariant;
	VARIANT   vt;
	if(NULL==pUserInfo)
		return 0;
	try
	{// �û���	
		strKey = _T("UserName");
		oVariant = pUserInfo->m_strUserName;
		pElement->setAttribute(strKey, oVariant);
		// ����
		strKey = _T("Password");	
		oVariant = pUserInfo->m_strPassword;	
		pElement->setAttribute(strKey, oVariant);
		// �û���ɫ
		switch(pUserInfo->m_nRole)	
		{
		case USERINFO_ROLE_GUEST:		// guest
			oVariant = _T("Guest");
			break;
		case USERINFO_ROLE_OBSERVER:	// Observer
			oVariant = _T("Observer");
			break;
		case USERINFO_ROLE_SENIOROBSERVER:// Senior Observer
			oVariant = _T("Senior Observer");
			break;
		default:
			oVariant = _T("Guest");
			break;
		}
		// ��ɫ
		strKey = _T("UserRole");
// 		vt.vt = VT_UI4;
// 		vt.ulVal = pUserInfo->m_nRole;
// 		oVariant = vt;
		pElement->setAttribute(strKey, oVariant);
		// ע������
		strTemp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),pUserInfo->m_tmRegister.wYear,pUserInfo->m_tmRegister.wMonth
			,pUserInfo->m_tmRegister.wDay,pUserInfo->m_tmRegister.wHour,
			pUserInfo->m_tmRegister.wMinute	,pUserInfo->m_tmRegister.wSecond);
		strKey = _T("RegistrationDate");
		oVariant =strTemp;
		pElement->setAttribute(strKey, oVariant);
		// ʧЧģʽ
		strKey = _T("ExpiredMode");
		vt.vt = VT_UI4;
		vt.ulVal = pUserInfo->m_nExpiredMode;
		oVariant = vt;
		pElement->setAttribute(strKey, oVariant);
		// ʧЧ����
		strTemp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),pUserInfo->m_tmExpiryDate.wYear,pUserInfo->m_tmExpiryDate.wMonth
			,pUserInfo->m_tmExpiryDate.wDay,pUserInfo->m_tmExpiryDate.wHour,
			pUserInfo->m_tmExpiryDate.wMinute	,pUserInfo->m_tmExpiryDate.wSecond);
		strKey = _T("ExpiryDate");
		oVariant =strTemp;
		pElement->setAttribute(strKey, oVariant);
		// AutoDelete
		strKey = _T("AutoDelete");
		vt.vt = VT_UI4;
		vt.ulVal = pUserInfo->m_bAutoDelete;
		oVariant = vt;
		pElement->setAttribute(strKey, oVariant);
		// ����¼����
		strTemp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),pUserInfo->m_tmLastUsed.wYear,pUserInfo->m_tmLastUsed.wMonth
			,pUserInfo->m_tmLastUsed.wDay,pUserInfo->m_tmLastUsed.wHour,
			pUserInfo->m_tmLastUsed.wMinute	,pUserInfo->m_tmLastUsed.wSecond);
		strKey = _T("LastUsed");
		oVariant =strTemp;
		pElement->setAttribute(strKey, oVariant);
		return true;
	}
	catch (CException* )
	{
		return false;
	}
	
}
/**
 * @brief �������е��û���Ϣ
 * @note  ��XML�����ļ���д���û���Ϣ
 * @param LPCTSTR pstrXMLFilePath��XML�����ļ�·�� 
 * @param CUserInfos*  pUserInfos, ���е��û���Ϣ����
 * @return д���Ƿ�ɹ�
 */
bool  CAdminParseXML::WriteAllUserInfo(LPCTSTR pstrXMLFilePath,CUserInfos*  pUserInfos)
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
		// ����XML����
		strKey =_T("msxml2.domdocument");
		BOOL bData = oXMLDOMDocument.CreateDispatch(strKey, &oError);
		oXMLDOMDocument.put_preserveWhiteSpace(TRUE);
		oVariant = pstrXMLFilePath;
		bData = oXMLDOMDocument.load(oVariant);

		// �ҵ�Users����
		strKey =_T("Users");
		lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElementParent.AttachDispatch(lpDispatch);

		// ���õ��������
		strKey = _T("Count");
		lCount = (long)(pUserInfos->GetCount());
		oVariant = lCount;
		oElementParent.setAttribute(strKey, oVariant);

		// ɾ�������ӽڵ�
		while(TRUE == oElementParent.hasChildNodes())
		{
			lpDispatch = oElementParent.get_firstChild();
			oElementParent.removeChild(lpDispatch);
		}
		// �����½ڵ�
		CUserInfo *pUserInfo =NULL;
		for( i = 0; i < lCount; i++)
		{
			pUserInfo = pUserInfos->GetUserInfo(i);

			lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t\t"));
			oElementParent.appendChild(lpDispatch);

			lpDispatch = oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);		
			//���浥����¼
			WriteUserInfo(&oElementChild,pUserInfo);
			oElementParent.appendChild(lpDispatch);

		}
		lpDispatch = oXMLDOMDocument.createTextNode(_T("\r\n\t\t"));
		oElementParent.appendChild(lpDispatch);

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
