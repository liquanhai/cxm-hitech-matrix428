#pragma once

#include "LineList.h"
#include "PointList.h"
#include "ChannelList.h"
#include "SensorList.h"
#include "PointCodeList.h"

class CSurveySetupData
{
public:
	CSurveySetupData(void);
	~CSurveySetupData(void);

public: // ����
	// ��������
	unsigned int m_uiLineCount;
	// ����ͷָ��
	CLineSetupData* m_pLineHead;
	// ����βָ��
	CLineSetupData* m_pLineTail;

	// �������
	unsigned int m_uiPointCount;
	// ���ͷָ��
	CPointSetupData* m_pPointHead;
	// ���βָ��
	CPointSetupData* m_pPointTail;

	// �������
	unsigned int m_uiChannelCount;
	// ���ͷָ��
	CChannelSetupData* m_pChannelHead;
	// ���βָ��
	CChannelSetupData* m_pChannelTail;

	// ������������
	unsigned int m_uiLineCountAll;
	// ���߶���
	CLineList m_oLineList;

	// �����������
	unsigned int m_uiPointCountAll;
	// ������
	CPointList m_oPointList;

	// �����������
	unsigned int m_uiChannelCountAll;
	// �������
	CChannelList m_oChannelList;

	// XMLDOM�ļ�����ָ��
	CXMLDOMDocument* m_pXMLDOMDocument;

	// �첨���б����
	CSensorList m_oSensorList;
	// ������б����
	CPointCodeList m_oPointCodeList;

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// ���������ļ�
	void ParseXML();
	// ��������
	void ParseLine(CLineSetupData* pLineSetupData);
	// �������
	void ParsePoint(CPointSetupData* pPointSetupData);
	// �������
	void ParseChannel(CChannelSetupData* pChannelSetupData);
	// �������ߵĲ�㶨��
	void ParseLineReceiverSection(CLineSetupData* pLineSetupData);
	// �������߶�
	void ParseLineReceiverSectionPart(CLineSetupData* pLineSetupData, CString strPart);
	// ����
	void Link();
	// ���Ӳ���
	void LinkLine();
	// ���Ӳ��
	void LinkPoint();
	// ���Ӳ��
	void LinkChannel();
	// �õ����������IP��ַ
	CChannelSetupData* GetChannel(unsigned int uiIP);
	// �õ���������ݲ��ߺš����š������
	CChannelSetupData* GetChannel(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel);
	// �õ���㣬���ݲ��������
	CPointSetupData* GetPoint(unsigned int uiIndexPoint);
	// �õ���㣬���ݲ��ߺš�����
	CPointSetupData* GetPoint(unsigned int uiNbLine, unsigned int uiNbPoint);
	// �õ�����
	CLineSetupData* GetLine(unsigned int uiNbLine);

	// ���������ͷ��򣬵õ��������ڵ�
	CPointSetupData* GetPointByIncrementAndDirection(CPointSetupData* pPointSetupData, unsigned int uiIncrement, unsigned int uiDirection);
	// �������У��õ�IP��ַ���У��ɼ���
	bool ParseSpreadToIPListByAbsoluteSpread(CList<unsigned int, unsigned int>* plsIP, CString strAbsoluteSpread);
	// �������У��õ�IP��ַ���У��ɼ���
	bool ParseSpreadToIPListByAbsoluteSpreadPart(CList<unsigned int, unsigned int>* plsIP, CString strPart);
};
