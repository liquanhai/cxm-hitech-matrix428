#pragma once
#include "ShotPoints.h"
#include "shotsources.h"
#include "ShotSpreads.h"
#include "ProcessTypes.h"
#include "ChannelList.h"
#include "..\common\FDUConfig.h"
/******************************************************************************
    ��    �ͣ�
    
    ��    �ܣ� ��ȡ�����ļ�

    �޸���ʷ��

*******************************************************************************/
/**
 * @class COperationParseXML
 * @brief ���������ļ�
 *
 * @note ��ʩ�������ļ���XML��ʽ���ж�ȡ������Ϣ����Ҫ�������ڱ���Դ���ɼ����С��������͵�
 */
class COperationParseXML
{
private:
	int ParseOperationTableRecord(CXMLDOMElement* pElement,CShotPoint* pVP);	
	int ParseSourceExplo(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	int ParseSourceExploRecord(CXMLDOMElement* pElement,CShotSourceExplo* pExploSrc);
	int ParseSourceVibro(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	int ParseSourceVibroRecord(CXMLDOMElement* pElement,CShotSourceVibro* pVibroSrc);
	int ParseProcessImpulsive(CXMLDOMElement* pElement,CProcessImpulsive* pProcess);
	// ����������
	int ParseProcessAuxi(CXMLDOMElement* pElement,CProcessType* pProcess);
	// �����ɼ����е�һ����¼
	int ParseShotSpreadRecord(CXMLDOMElement* pElement, CShotSpread *pSpread,CChannelList* pChannelList);
	bool AppendChannelsToShotSpread(DWORD dwLine,DWORD dwPointMin,DWORD dwPointMax,DWORD dwGain,CShotSpread *pSpread,CChannelList* pChannelList);
public:
	COperationParseXML(void);
	~COperationParseXML(void);
	// �����ɼ�վ������Ϣ
	int ParseFDUConfig(LPCTSTR pstrXMLFilePath,CFDUConfig* pFDUConfig);
	// �������ڱ�
	int ParseOperationTable(LPCTSTR pstrXMLFilePath,CShotPoints* pShotPoints);
	// ������Դ
	int ParseSourceType(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	// �����ɼ�����
	// int ParseShotSpread(LPCTSTR pstrXMLFilePath,CShotSpreads* pShotSrcs);
	int ParseShotSpread(LPCTSTR pstrXMLFilePath,CShotSpreads* pShotSrcs,CChannelList* pChannelList);
	// �������ݴ������
	int ParseProcessType(LPCTSTR pstrXMLFilePath,CProcessTypes* pProcesses);
	// ���ϵͳ������Ϣ
	bool ParseClientSetup(LPCTSTR pstrXMLFilePath);
	// ���ַ���IPת��ΪDWORD��
	DWORD StringIPToDWORDIP(CString& strIP);

};
