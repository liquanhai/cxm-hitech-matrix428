#pragma once

#include "Instrument.h"

/**
*@brief ·��������
*/
class CRout
{
public:
	CRout();
	~CRout();

public: //����
	/** ��·�������е�λ��*/
	unsigned int m_uiIndex;
// 
	/** ·���Ƿ�ʹ����*/
	bool m_bInUsed;

	/** ·��IP��ַ*/
	unsigned int m_uiRoutIP;
	/** ·�ɷ��� 1-�ϣ�2-�£�3-��4��*/
	unsigned int m_uiRoutDirection;
	/** ·��ͷ����*/
	CInstrument* m_pHead;
	/** ·��β����*/
	CInstrument* m_pTail;

// 	/** ·��ͷ����*/
// 	unsigned int m_uiSNHead;
// 	/** ·��β����*/
// 	unsigned int m_uiSNTail;
// 	/** ·��ͷ����*/
// 	int m_iIndexHead;
// 	/** ·��β����*/
// 	int m_iIndexTail;
	/** ·��ʱ��*/
	unsigned int m_uiRoutTime;
	/** �ϴ�ʱͳ����ʱ��*/
	unsigned int m_uiDelayProcTime;

public: //����
	// ����
	void OnReset();
	// ����·��ʱ��
	void UpdateRoutTime();
	// �����ϴ�ʱͳ����ʱ��
	void UpdateDelayProcTime();
};
