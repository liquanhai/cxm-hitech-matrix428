#pragma once

/**
*@brief ����ʱͳ����֡��
*/
class CFrameTimeSet
{
public:
	CFrameTimeSet();
	~CFrameTimeSet();

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

	/** ����ʱ��������λ*/
	unsigned int m_uiTimeHigh;
	/** ����ʱ��������λ*/
	unsigned int m_uiTimeLow;

public: // ����
	// ���ö���
	void Reset();
	// ����ʱ������Ӧ��֡
	bool ParseFrame();
	// ����������
	bool ParseCommandWord();
	// ��������ʱ���ַ����֡
	void MakeFrameData();
};
