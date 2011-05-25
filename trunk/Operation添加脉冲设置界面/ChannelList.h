#pragma once


#include "ChannelSetupData.h"

class CChannelList
{
public:
	CChannelList(void);
	~CChannelList(void);

public: //����
	// �������ָ��
	CChannelSetupData* m_pArrayChannel;
	// �������
	unsigned int m_uiCountAll;
	// ʹ���в������
	unsigned int m_uiCountUsed;
	// ���в������
	unsigned int m_uiCountFree;
	// ���������
	CMap<unsigned int, unsigned int, CChannelSetupData*, CChannelSetupData*> m_oChannelMap;

	/*
	unsigned int m_uiNbPointMin;	// ��С����
	unsigned int m_uiNbPointMax;	// ������
	unsigned int m_uiPointChannelCountMax;	// ��������������
	unsigned int m_uiNbLineCount;	// ��������
	
	CList<unsigned int, unsigned int> m_olsNbLine;	// ���ߺŶ���
	CMap<unsigned int, unsigned int, unsigned int, unsigned int> m_oNbLineMap;	// ���ߺ�������
	*/
public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// ����һ�������������
	void AddChannelToMap(unsigned int uiIndex, CChannelSetupData* pChannel);
	// ��IP������õ�һ�����
	BOOL GetChannelFromMap(unsigned int uiIndex, CChannelSetupData* &pChannel);
	// ����������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);
	// �õ�һ�����
	CChannelSetupData* GetChannelByIndex(unsigned int uiIndex);
	// �õ����
	CChannelSetupData* GetChannel(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel);
	// �����ֳ�������ݶ���
	void LoadSiteData();

};
