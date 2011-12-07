#pragma once

#include "ChannelSetupData.h"

/**
*@brief ���������
*/
class CPointSetupData
{
public:
	CPointSetupData();
	~CPointSetupData();

public: // ����
	/** �ڲ�������е�λ��*/
	unsigned int m_uiIndex;

	/** ����Ƿ�ʹ����*/
	bool m_bInUsed;
	/** �����*/
	int m_iPointCode;

	/** ���ߺ�*/
	unsigned int m_uiNbLine;
	/** ����*/
	unsigned int m_uiNbPoint;
	/** ���������*/
	unsigned int m_uiIndexPoint;
	/** �Ƿ��Ƶ�*/
	bool m_bMute;

	/** ������ӵĲ��*/
	CPointSetupData* m_pPointLeft;
	/** ������ӵĲ��*/
	CPointSetupData* m_pPointRight;
	/** �������ӵĲ��*/
	CPointSetupData* m_pPointlTop;
	/** �������ӵĲ��*/
	CPointSetupData* m_pPointlDown;

	/** �������*/
	unsigned int m_uiChannelCount;
	/** ���ͷָ��*/
	CChannelSetupData* m_pChannelHead;
	/** ���βָ��*/
	CChannelSetupData* m_pChannelTail;

public: // ����
	// ����
	void OnReset();

	// ���ݲ��ߺźͲ��ţ����ɲ��������
	void CreateIndexPoint();
	// ���ݲ��ߺźͲ��ţ����ɲ��������
	static unsigned int CreateIndexPoint(unsigned int uiNbLine, unsigned int uiNbPoint);
	// �õ�������ӵĲ��
	CChannelSetupData* GetChannelRight(CChannelSetupData* pChannelSetupData, unsigned int uiDirection);
	// �õ����������ӵĲ��
	CChannelSetupData* GetChannelLeft(CChannelSetupData* pChannelSetupData);
	// �õ�����ұ����ӵĲ��
	CChannelSetupData* GetChannelRight(CChannelSetupData* pChannelSetupData);
};
