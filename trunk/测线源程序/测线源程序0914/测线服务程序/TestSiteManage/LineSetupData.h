#pragma once

#include "PointSetupData.h"

/**
*@brief ����������
*/
class CLineSetupData
{
public:
	CLineSetupData();
	~CLineSetupData();

public: // ����
	/** �ڲ��������е�λ��*/
	unsigned int m_uiIndex;

	/** �����Ƿ�ʹ����*/
	bool m_bInUsed;

	/** ���ߺ�*/
	unsigned int m_uiNbLine;

	/** �������ӵĲ���*/
	CLineSetupData* m_pLinelTop;
	/** �������ӵĲ���*/
	CLineSetupData* m_pLinelDown;

	/** �������*/
	unsigned int m_uiPointCount;
	/** ���ͷָ��*/
	CPointSetupData* m_pPointHead;
	/** ���βָ��*/
	CPointSetupData* m_pPointTail;

	/** �������*/
	unsigned int m_uiChannelCount;
	/** ���ͷָ��*/
	CChannelSetupData* m_pChannelHead;
	/** ���βָ��*/
	CChannelSetupData* m_pChannelTail;

	/** �����ϵĲ�㶨��*/
	CString m_strReceiverSection;

public: // ����
	// ����
	void OnReset();
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// �õ�������ӵĲ��
	CPointSetupData* GetPointByDirection(CPointSetupData* pPointSetupData, unsigned int uiDirection);
	// �õ����������ӵĲ��
	CPointSetupData* GetPointLeft(CPointSetupData* pPointSetupData);
	// �õ�����ұ����ӵĲ��
	CPointSetupData* GetPointRight(CPointSetupData* pPointSetupData);
};
