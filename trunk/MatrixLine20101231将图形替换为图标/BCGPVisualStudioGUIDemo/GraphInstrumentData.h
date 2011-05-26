#pragma once

#include "Instrument.h"

class CGraphInstrumentData
{
public:
	CGraphInstrumentData(void);
	~CGraphInstrumentData(void);

public: //����	
	bool m_bInUsed;	// ͼ�ε�Ԫ�Ƿ�ʹ����

	int m_iPosX;	// X����λ��
	int m_iPosY;	// Y����λ��
	int m_iPosIndex;	// ����λ������

	CInstrument* m_pInstrument;	// ����ָ��

public: // ����
	// ����
	void OnReset();
	// ��������λ������
	static int CreatePosIndex(int iPosX, int iPosY);
	// ����ͼ�β���
	void SetDrawParam();

	// ��ͼ����Ԫ������
	void DrawUnitLinkLine(CDC* pDC, int iGridX, int iGridY);
	// ��ͼ
	void DrawUnit(CDC* pDC, int iGridX, int iGridY, int iUnitWidth, int iUnitHight, int iUnitSizeMode, unsigned int uiTestType);
};

/*
��Ԫ���ƹ���
δ����IP��ַ�ģ���ʾΪ��ʮ��


����QC��Χ�Ĳɼ�վ
���Ժϸ� ��ɫ
���Բ��ϸ� ��ɫ
δ���� ��ɫ
���źŻ�δ�ж� ��ɫ

*/