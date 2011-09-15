#pragma once


#include "FDUConfig.h"
#include "DiskRecordConfig.h"
class CConfigParseXML
{
public:
	CConfigParseXML(void);
	~CConfigParseXML(void);

private:
 	
	bool  ParseFDUConfig(CXMLDOMDocument* pXMLDOMDocument,CFDUConfig* pFDUConfig);
public:


	bool  ParseCrewConfig(LPCTSTR pstrXMLFilePath,CFDUConfig* pFDUConfig);
	bool  WriteCrewConfig(LPCTSTR pstrXMLFilePath,CFDUConfig* pFDUConfig);


	bool  ParseUserInfo(LPCTSTR pstrXMLFilePath,CString&  strUserInfo);
	bool  WriteUserInfo(LPCTSTR pstrXMLFilePath,CString&  strUserInfo);

	bool  ParseDiskRecord(LPCTSTR pstrXMLFilePath,CDiskRecordConfig* pDiskRecord);
	bool  WriteDiskRecord(LPCTSTR pstrXMLFilePath,CDiskRecordConfig* pDiskRecord);
	// �������ó�����SPS�ļ����ò���
	bool ParseSPSFile(LPCTSTR pstrXMLFilePath, CString& strSPSRFilePath, CString& strSPSXFilePath);
	// �������ļ���д��SPS�ļ����ò���
	bool WriteSPSFile(LPCTSTR pstrXMLFilePath, CString& strSPSRFilePath, CString& strSPSXFilePath);
};
