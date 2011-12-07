#pragma once

#include "Instrument.h"

/**
*@brief ������������
*/
class CIndexInstrumentMap
{
public:
	CIndexInstrumentMap();
	~CIndexInstrumentMap();

public: //����
	/** ����������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentMap;

	CInstrument* m_pInstrument;

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// ����һ������
	void AddInstrument(unsigned int uiIndex, CInstrument* pInstrument);
	// �õ�һ������
	BOOL GetInstrument(unsigned int uiIndex, CInstrument* &pInstrument);
	// ɾ��һ������
	void DeleteInstrument(unsigned int uiIndex);
	// ɾ����������
	void DeleteInstrumentAll();
	// �����������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);
};
