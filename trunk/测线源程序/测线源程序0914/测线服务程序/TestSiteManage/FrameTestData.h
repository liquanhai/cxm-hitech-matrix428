#pragma once

/**
*@brief ������������֡��
*/
class CFrameTestData
{
public:
	CFrameTestData();
	~CFrameTestData();

public: // ����
	// ֡��С*/
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

	/** ��������*/
	unsigned short m_usDataIndex;
	/** ��������*/
	byte* m_pData;

public: // ����
	// ���ö���
	void Reset();
	// ��������֡
	bool ParseFrame();
};
