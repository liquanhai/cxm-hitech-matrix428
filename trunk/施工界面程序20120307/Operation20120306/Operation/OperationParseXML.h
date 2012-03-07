#pragma once
#include "ShotPoints.h"
#include "shotsources.h"
#include "ShotSpreads.h"
#include "ProcessTypes.h"
#include "ShotComment.h"

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
	int ParseCommentRecord(CXMLDOMElement* pElement,CShotComment* pComment);
	int SaveCommentRecord(CXMLDOMElement* pElement,CShotComment* pComment);

	int ParseOperationTableRecord(CXMLDOMElement* pElement,CShotPoint* pVP);
	int SaveOperationTableRecord(CXMLDOMElement* pElement,CShotPoint* pVP);

	int ParseSourceExplo(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	int ParseSourceExploRecord(CXMLDOMElement* pElement,CShotSourceExplo* pExploSrc);
	int SaveSourceExplo(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	int SaveSourceExploRecord(CXMLDOMElement* pElement,CShotSourceExplo* pExploSrc);

	int ParseSourceVibro(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	int ParseSourceVibroRecord(CXMLDOMElement* pElement,CShotSourceVibro* pVibroSrc);
	int SaveSourceVibro(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	int SaveSourceVibroRecord(CXMLDOMElement* pElement,CShotSourceVibro* pVibroSrc);
	// �������߶���ĸ�������¼
	int ParseAuxChannelRecord(CXMLDOMElement* pElement,CAuxChannel* pAuxChannel);	
	// ���崦������
	int ParseProcessImpulsive(CXMLDOMElement* pElement,CProcessImpulsive* pProcess);
	int SaveProcessImpulsive(CXMLDOMDocument* pXMLDOMDocument,CXMLDOMElement* pElement,CProcessImpulsive* pProcess);
	// �����������͸�����
	int ParseProcessAuxi(CXMLDOMElement* pElement,CProcessType* pProcess);
	int SaveProcessAuxi(CXMLDOMDocument* pXMLDOMDocument,CXMLDOMElement* pElement,CProcessType* pProcess);
	// �����ɼ����е�һ����¼
	int ParseShotSpreadRecord(CXMLDOMElement* pElement, CShotSpread *pSpread,CChannelList* pChannelList);
	bool AppendChannelsToShotSpread(DWORD dwLine,DWORD dwPointMin,DWORD dwPointMax,DWORD dwGain,CShotSpread *pSpread,CChannelList* pChannelList);
public:
	COperationParseXML(void);
	~COperationParseXML(void);
	// �����ɼ�վ������Ϣ
	// bool ParseFDUConfig(LPCTSTR pstrXMLFilePath,CFDUConfig* pFDUConfig);
	// 
	int ParseComments(LPCTSTR pstrXMLFilePath,CShotComments* pComments);
	int SaveComments(LPCTSTR pstrXMLFilePath,CShotComments* pComments);
	// �������ڱ�
	int ParseOperationTable(LPCTSTR pstrXMLFilePath,CShotPoints* pShotPoints);
	// ������ڱ�
	int SaveOperationTable(LPCTSTR pstrXMLFilePath,CShotPoints* pShotPoints);
	// ������Դ
	int ParseSourceType(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	// ������Դ
	int SaveSourceType(LPCTSTR pstrXMLFilePath,CShotSources* pShotSrcs);
	// ����������
	int ParseAuxChannel(LPCTSTR pstrXMLFilePath,CAuxChannels* pAllAuxes);

	// �����ɼ�����
	// int ParseShotSpread(LPCTSTR pstrXMLFilePath,CShotSpreads* pShotSrcs);
	int ParseAllAbsoluteSpread(LPCTSTR pstrXMLFilePath,CShotSpreads* pShotSrcs,CChannelList* pChannelList);
	// �������ݴ������
	int ParseProcessType(LPCTSTR pstrXMLFilePath,CProcessTypes* pProcesses);
	int SaveProcessType(LPCTSTR pstrXMLFilePath,CProcessTypes* pProcesses);
	// ���ϵͳ������Ϣ
	//bool ParseClientSetup(LPCTSTR pstrXMLFilePath);
	
};
