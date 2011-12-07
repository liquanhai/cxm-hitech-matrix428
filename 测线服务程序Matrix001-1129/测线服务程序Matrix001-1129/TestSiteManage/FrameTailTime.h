#pragma once

/**
*@brief ����β��ʱ��֡��
*/
class CFrameTailTime
{
public:
	CFrameTailTime();
	~CFrameTailTime();
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

	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiInstrumentType;

	/** 16bitsʱ�䣬����ʱ�̵�λ*/
	unsigned short m_usReceiveTime;	
	/** 16bitsʱ�䣬����ʱ�̵�λ*/
	unsigned short m_usSendTime;	

	/** ����ʱ��*/
	unsigned int m_uiTimeSystem;
	/** ����ʱ��*/
	unsigned int m_uiNetTime;
	/** ����ʱ��*/
	unsigned int m_uiNetState;
	/** ����ʱ��*/
	unsigned int m_uiNetOrder;

	/** 16bits ���߷�������β������ʱ��*/
	unsigned short m_usLineLeftReceiveTime;	
	/** 16bits ���߷�������β������ʱ��*/
	unsigned short m_usLineRightReceiveTime;	

	/** 16bits �����߷�������β������ʱ��*/
	unsigned short m_usCrossTopReceiveTime;	
	/** 16bits �����߷�����β������ʱ��*/
	unsigned short m_usCrossDownReceiveTime;	

public: // ����
	// ���ö���
	void Reset();
	// ����β��ʱ�̲�ѯӦ��֡
	bool ParseFrame();
	// ����������
	bool ParseCommandWord();
	// ����β��ʱ�̲�ѯ֡
	void MakeFrameData();
};
