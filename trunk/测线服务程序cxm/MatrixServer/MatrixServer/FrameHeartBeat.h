#pragma once

/**
*@brief ��������֡��
*/
class CFrameHeartBeat
{
public:
	CFrameHeartBeat();
	~CFrameHeartBeat();

public: // ����
	/** ֡��С*/
	int m_iFrameSize;
	/** ֡����*/
	byte m_pFrameData[256];
	/** ԴIP��ַ*/
	unsigned int m_uiIPSource;
	/** Ŀ��IP��ַ*/
	unsigned int m_uiIPAim;
	/** Ŀ��˿ں�*/
	unsigned short m_usPortAim;
	/** ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�*/
	unsigned short m_usCommand;

public: // ����
	// ���ö���
	void Reset();
};
