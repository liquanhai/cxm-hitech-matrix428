#pragma once

#include "ChannelSetupData.h"

/**
*@brief ������ݶ�����
*/
class CChannelList
{
public:
	CChannelList();
	~CChannelList();

public: //����
	/** �������ָ��*/
	CChannelSetupData* m_pArrayChannel;
	/** �������ָ�룬Ϊ�ֳ��������׼��*/
	CChannelSetupData* m_pArrayChannelOutput;
	/** �������*/
	unsigned int m_uiCountAll;
	/** ʹ���в������*/
	unsigned int m_uiCountUsed;
	/** ���в������*/
	unsigned int m_uiCountFree;
	/** ���������*/
	CMap<unsigned int, unsigned int, CChannelSetupData*, CChannelSetupData*> m_oChannelMap;

public: //����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// �õ�һ�����в��
	CChannelSetupData* GetFreeChannel();
	// ����һ�������������
	void AddChannelToMap(unsigned int uiIndex, CChannelSetupData* pChannel);
	// ��������õ�һ�����
	BOOL GetChannelFromMap(unsigned int uiIndex, CChannelSetupData* &pChannel);
	// ����������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);
	// �õ�һ�����
	CChannelSetupData* GetChannelByIndex(unsigned int uiIndex);
	// �õ����
	CChannelSetupData* GetChannel(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel);
	// ���Ʋ�����鵽�������
	void CopyChannelArrayForOutput();
};
