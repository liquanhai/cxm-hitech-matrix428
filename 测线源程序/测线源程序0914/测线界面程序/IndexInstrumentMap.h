#pragma once

#include "Instrument.h"

class CIndexInstrumentMap
{
public:
	CIndexInstrumentMap(void);
	~CIndexInstrumentMap(void);

public: //����
	// ��ϣ��
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentMap;

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
	void DeleteInstrumentAll(void);
	// �����������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);

	// �õ��׸�����λ��
	POSITION GetFirstInstrumentPosition();
	// �õ���һ������
	void GetNextInstrumentByPosition(POSITION &pos, CInstrument* &pInstrument);
};
