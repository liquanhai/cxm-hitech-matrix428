#pragma once

#include "GraphSensorData.h"
#include "ChannelList.h"

class CGraphSensorList
{
public:
	CGraphSensorList();
	~CGraphSensorList();

public: // ����
	CChannelList* m_pChannelList;	// �������ָ��	
	
	CGraphSensorData* m_pArrayGraphSensor;	// �첨��ͼ�ε�Ԫ����ָ��	
	unsigned int m_uiCountAll;	// ����	
	unsigned int m_uiCountUsed;	// ʹ��������	
	unsigned int m_uiCountFree;	// ��������

	COLORREF m_oPaperColor;	// ������ɫ
	COLORREF m_oGridColor;	// ��������ɫ

	unsigned int m_uiRowCount;	// ����
	unsigned int m_uiColumnCount;	// ����

	int m_iGridX;	// ��Ԫ��X����ߴ�
	int m_iGridY;	// ��Ԫ��Y����ߴ�

	int m_iPaperX;	// ͼ����X����ߴ�
	int m_iPaperY;	// ͼ����Y����ߴ�

	int m_iPaperHeadLeft;	// ͼ�������Ԥ���ߴ�
	int m_iPaperHeadTop;	// ͼ�������Ԥ���ߴ�

	int m_iGridXMin;	// ��Ԫ��X������С�ߴ�
	int m_iGridYMin;	// ��Ԫ��Y������С�ߴ�
	int m_iGridXMax;	// ��Ԫ��X�������ߴ�
	int m_iGridYMax;	// ��Ԫ��Y�������ߴ�

	int m_iSizeModeMin;	// ͼ�ε�Ԫ��С�ߴ�ģʽʱ�����޳ߴ�
	int m_iSizeModeMax;	// ͼ�ε�Ԫ���ߴ�ģʽʱ�����޳ߴ�

	int m_iUnitWidthMin;	// ͼ�ε�Ԫ��ȣ���С�ߴ�ģʽ
	int m_iUnitHightMin;	// ͼ�ε�Ԫ�߶ȣ���С�ߴ�ģʽ

	int m_iUnitWidthNormal;	// ͼ�ε�Ԫ��ȣ������ߴ�ģʽ
	int m_iUnitHightNormal;	// ͼ�ε�Ԫ�߶ȣ������ߴ�ģʽ

	int m_iUnitWidthMax;	// ͼ�ε�Ԫ��ȣ����ߴ�ģʽ	
	int m_iUnitHightMax;	// ͼ�ε�Ԫ�߶ȣ����ߴ�ģʽ

public: // ����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// �ر�
	void OnClose();
	// ���ؼ첨��ͼ����ͼ�첨��ͼ�ε�Ԫ����
	void LoadSiteData();
	// �õ����ߺ���ͼ�������ڵ�������
	unsigned int GetUintRowIndex(unsigned int uiNbLine);
	// �õ��������ͼ�������ڵ�������
	unsigned int GetUintColumnIndex(unsigned int uiNbPoint, unsigned int uiNbChannel);
	// �õ�ͼ������������Ӧ�Ĳ��ߺ�
	unsigned int GetUintLineNb(unsigned int uiRowIndex);
	// �õ�ͼ������������Ӧ�Ĳ���
	unsigned int GetUintPointNb(unsigned int uiColumnIndex);
	// �õ�ͼ������������Ӧ�Ĳ����
	unsigned int GetUintChannelNb(unsigned int uiColumIndex);
	// �õ�ͼ��������������Ӧ�Ĳ��
	CChannelSetupData* GetChannelSetupData(unsigned int uiRowIndex, unsigned int uiColumIndex);
	// ��ѡ������ת��Ϊ���������ַ���
	CString ConvertSelectAreaToAbsoluteSpreadString(CRect* pSelectAreaIndex);

	// ������ͼ
	void DrawGrid(CDC* pDC, int iPaperX, int iPaperY, int iGridX, int iGridY);
	// �����߱�ߺͲ����
	void DrawMarkLineNbAndPointNb(CDC* pDC, int iGridX, int iGridY);
	// �����߱��
	void DrawMarkLineNb(CDC* pDC, int iGridY);
	// �������
	void DrawMarkPointNb(CDC* pDC, int iGridX);
	// ��ͼ�ε�Ԫ
	void DrawUnitAll(CDC* pDC, int iGridX, int iGridY, unsigned int uiTestType, unsigned int uiSensorNbSelest, CMap<unsigned int, unsigned int, unsigned int, unsigned int>& oSensorNbMap, float fSeismonitorLimit);
	// �õ�ͼ�ε�Ԫ�ߴ�
	void GetUnitSize(int iGridX, int &iUnitWidth, int &iUnitHight, int &iUnitSizeMode);
};
