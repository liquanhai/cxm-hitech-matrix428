#pragma once

#include "ChannelSetupData.h"

class CGraphSensorData
{
public:
	CGraphSensorData(void);
	~CGraphSensorData(void);

public: //����
	int m_iPosX;	// X����λ��
	int m_iPosY;	// Y����λ��
	CChannelSetupData* m_pChannelSetupData;	// ���ָ��

public: // ����
	// ����
	void OnReset();
	// ����ͼ�β���
	void SetDrawParam();
	// ��ͼ
	void DrawUnit(CDC* pDC, int iGridX, int iGridY, int iUnitWidth, int iUnitHight, int iUnitSizeMode, unsigned int uiTestType, bool bDrawSensorNb, float fSeismonitorLimit);
	// �õ��������ͼ�ε�Ԫ��Ը߶�
	int GetSeismonitorGraphHight(float fSeismonitorLimit);
	// �õ��������ͼ�ε�Ԫ�߶�
	int GetSeismonitorGraphHight(int iUnitHight, float fSeismonitorLimit);
	// �õ��������ͼ�ε�Ԫ��ɫ
	void GetSeismonitorGraphColour(CBrush *oBrushUnit, float fSeismonitorLimit);
};

/*
��Ԫ���ƹ���
δ����IP��ַ�ģ���ʾΪ��ʮ��
����������ʾΪ��ʮ��
�Ƶ�����ʾΪ��ʮ��

����QC��Χ�Ĳɼ���
���Ժϸ� ��ɫ
���Բ��ϸ� ��ɫ
δ���� ��ɫ
���ź� ��ʮ��

������QC��Χ�Ĳɼ���
�ɼ��� ��ɫ
*/