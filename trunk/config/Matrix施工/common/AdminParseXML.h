#pragma once


#include "UserInfo.h"

class CAdminParseXML
{
public:
	CAdminParseXML(void);
	~CAdminParseXML(void);

private:
	bool  ParseUserInfo(CXMLDOMElement* pElement,CUserInfo*  pUserInfo);
	bool  WriteUserInfo(CXMLDOMElement* pElement,CUserInfo*  pUserInfo);
public:
	// ��������IP��ַ
	bool  ParseHostConfig(LPCTSTR pstrXMLFilePath,CString& strIP);
	bool  ParseAllUserInfo(LPCTSTR pstrXMLFilePath,CUserInfos*  pUserInfos);
	bool  WriteAllUserInfo(LPCTSTR pstrXMLFilePath,CUserInfos*  pUserInfos);
	
};
