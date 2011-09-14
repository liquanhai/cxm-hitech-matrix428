#pragma once

/**
*@brief ����β��֡��
*/
class CFrameTail
{
public:
	CFrameTail();
	~CFrameTail();

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
	// ����������
	bool ParseCommandWord();
};
