#pragma once
#include "..\common\LineStruct.h"
#include "..\common\OperaStruct.h"

class COperationServerParseXML
{
public:
	COperationServerParseXML(void);
	~COperationServerParseXML(void);

private:
	// ������������¼
	//int ParseAuxChannelRecord(CXMLDOMElement* pElement,CAuxChannel* pAuxChannel);	
public:
	// ���ϵͳ������Ϣ
	bool ParseServerSetup(LPCTSTR pstrXMLFilePath);
	// ���ַ���IPת��ΪDWORD��
	static DWORD StringIPToDWORDIP(CString& strIP);
	// �����������ñ��浽XML�ļ���
	bool WriteServerSetup(LPCTSTR pstrXMLFilePath);

	// ����������
	//int ParseAuxChannel(LPCTSTR pstrXMLFilePath,CAuxChannels* pAllAuxes);
	// �õ�������һ������ʱ����¼��SEGD�ļ����
	DWORD ParseLastUsedSEGDFileNumber(LPCTSTR pstrXMLFilePath);
	// ����ǰ��SEGD�ļ���ű��浽XML�ļ��У�һ���ڳ����˳�ʱ����
	bool WriteLastUsedSEGDFileNumber(LPCTSTR pstrXMLFilePath,DWORD dwSEGDFileNumber);
};
