#pragma once

#include "Instrument.h"

/**
*@brief ����������
*/
class CInstrumentList
{
public:
	CInstrumentList();
	~CInstrumentList();

public: //����
	/** ��������ָ��*/
	CInstrument* m_pArrayInstrument;
	/** ��������ָ�룬Ϊ�ֳ��������׼��*/
	CInstrument* m_pArrayInstrumentOutput;
	/** ������������*/
	CList<CInstrument*, CInstrument*> m_olsInstrumentFree;
	/** ��������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// �õ�һ����������
	CInstrument* GetFreeInstrument();
	// ����һ����������
	void AddFreeInstrument(CInstrument* pInstrument);
	// �����������鵽�������
	void CopyInstrumentArrayForOutput();
};
