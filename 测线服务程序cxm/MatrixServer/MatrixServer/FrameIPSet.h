#pragma once
#include "Parameter.h"
/**
*@brief ����IP��ַ����֡��
*/
class CFrameIPSet
{
public:
	CFrameIPSet();
	~CFrameIPSet();

public: // ����
	/** ����֡����*/
	byte m_pRcvFrameData[RcvFrameSize];
	/** ����֡����*/
	byte m_pSndFrameData[SndFrameSize];
	/** ԴIP��ַ*/
	unsigned int m_uiIPSource;
	/** Ŀ��IP��ַ*/
	unsigned int m_uiIPAim;
	/** Ŀ��˿ں�*/
	unsigned short m_usPortAim;
	/** ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�*/
	unsigned short m_usCommand;
	/** ����SN��*/
	unsigned int m_uiSN;
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiInstrumentType;
	/** ��������IP*/
	unsigned int m_uiIPInstrument;
	/** ·��IP��ַ��·�ɷ��� 1-��*/
	unsigned int m_uiRoutIPTop;
	/** ·��IP��ַ��·�ɷ��� 2-��*/
	unsigned int m_uiRoutIPDown;
	/** ·��IP��ַ��·�ɷ��� 3-��*/
	unsigned int m_uiRoutIPLeft;
	/** ·��IP��ַ��·�ɷ��� 4-��*/
	unsigned int m_uiRoutIPRight;
	/** ·��IP��ַ��·�ɷ��� 1-�ϣ�2-�£�3-��4��*/
	unsigned int m_uiRoutIP;
	// �㲥�˿�
	unsigned int m_uiBroadCastPort;
	// ·�ɿ���
	unsigned int m_uiRoutOpen;
public: // ����
	// ���ö���
	void Reset();
	// ����IP��ַ����Ӧ��֡
	bool ParseFrame();
	// ��������IP��ַ����֡
	void MakeFrameData();
};
