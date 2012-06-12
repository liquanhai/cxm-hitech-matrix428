#pragma once

#include "Instrument.h"
#include "indexinstrumentmap.h"

class CInstrumentList
{
public:
	CInstrumentList(void);
	~CInstrumentList(void);

public: //����
	// ��������ָ��
	CInstrument* m_pArrayInstrument;
	// ��������
	unsigned int m_uiCountAll;
	// ������������
	unsigned int m_uiCountFree;
	// ʹ������������
	unsigned int m_uiCountUsed;

	CInstrument* m_pFirstMainCross;	// �׸�������վָ��	
	CIndexInstrumentMap m_oSNInstrumentMap;	// SN����������	
	CIndexInstrumentMap m_oIPInstrumentMap;	// IP��ַ����������

	CIndexInstrumentMap m_oSNInstrumentCrossMap;	// SN��������������վ
	CIndexInstrumentMap m_oSNInstrumentPowerMap;	// SN������������Դվ

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// �����ֳ��������ݶ���
	void LoadSiteData();

	// ���ý���վ�ڲ����е�λ��
	void SetInstrumentCrossSurveryPosition();
	// ���õ�Դվ�ڲ����е�λ��
	void SetInstrumentPowerSurveryPosition();
	// ���������ڲ����е�λ��
	void SetInstrumentSurveryPosition(CInstrument* &pInstrument);

	// �õ��׸�����λ��
	POSITION GetFirstInstrumentPosition();
	// �õ���һ������
	void GetNextInstrumentByPosition(POSITION &pos, CInstrument* &pInstrument);

	// �õ��ػص�����������
	int GetDetourInstrumentCount(unsigned int uiIndex);

	// �ж�����A�Ƿ�������B���
	bool JudgeInstrumentAAtInstrumentBLeft(CInstrument* pInstrumentA, CInstrument* pInstrumentB);
	// �ж�����A�Ƿ�������B�ұ�
	bool JudgeInstrumentAAtInstrumentBRight(CInstrument* pInstrumentA, CInstrument* pInstrumentB);
};
