#pragma once

#include "XMLFileNameParam.h"
/**
 * @class CStartParseXML
 * @brief ����Start�����XML�����ļ�
 *
 * 
 */
class CStartParseXML
{
public:
	CStartParseXML(void);
	~CStartParseXML(void);
 
public:
	bool  ParseClientComputer(LPCTSTR pstrFilePath,CString& strIP,CString& strFTPIP);
	// bool  WriteInstallParam(LPCTSTR pstrFilePath,CInstallParam* pInstallParam);
};
