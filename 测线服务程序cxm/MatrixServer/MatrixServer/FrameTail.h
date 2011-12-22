#pragma once
#include "Parameter.h"
/**
*@brief ����β��֡��
*/
class CFrameTail
{
public:
	CFrameTail();
	~CFrameTail();

public: // ����
	/** ֡����*/
	byte m_pFrameData[RcvFrameSize];
	/** ��������IP��ַ*/
	unsigned int m_uiIPInstrument;
	/** ����SN��*/
	unsigned int m_uiSN;
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiInstrumentType;
	/** ����ϵͳʱ��*/
	unsigned int m_uiTimeSystem;
	/** ·��IP��ַ��·�ɷ��� 1-�ϣ�2-�£�3-��4-��*/
	unsigned int m_uiRoutIP;

public: // ����
	// ���ö���
	void Reset();
	// �����װ�֡
	bool ParseFrame();
};
