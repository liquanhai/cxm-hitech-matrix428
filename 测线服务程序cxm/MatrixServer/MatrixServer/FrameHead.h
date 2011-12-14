#pragma once
#include "Parameter.h"
/**
*@brief �����װ�֡��
*/
class CFrameHead
{
public:
	CFrameHead();
	~CFrameHead();

public: // ����
	/** ֡����*/
	byte m_pFrameData[RcvFrameSize];
	/** ����SN��*/
	unsigned int m_uiSN;
	/** �����װ�ʱ��*/
	unsigned int m_uiTimeHeadFrame;
	// ��������ʱ��
	unsigned int m_uiSysTime;
	/** ·��IP��ַ��·�ɷ��� 1-�ϣ�2-�£�3-��4-��*/
	unsigned int m_uiRoutIP;

public: // ����
	// ���ö���
	void Reset();
	// �����װ�֡
	bool ParseFrame();
};
