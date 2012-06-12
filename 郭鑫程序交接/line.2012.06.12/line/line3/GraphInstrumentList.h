#pragma once

#include "GraphInstrumentData.h"
#include "InstrumentList.h"

class CGraphInstrumentList
{
public:
	CGraphInstrumentList(void);
	~CGraphInstrumentList(void);
public: // ����
	CInstrumentList* m_pInstrumentList;	// ��������ָ��	

	CGraphInstrumentData* m_pArrayGraphInstrument;	// ����ͼ�ε�Ԫ����ָ��	
	unsigned int m_uiCountAll;	// ����	
	unsigned int m_uiCountUsed;	// ʹ��������	
	unsigned int m_uiCountFree;	// ��������

	CMap<unsigned int, unsigned int, CGraphInstrumentData*, CGraphInstrumentData*> m_oGraphInstrumentMap;	// ͼ�ε�Ԫ������
	CList<int, int> m_olsRowLineNb;	// ��Ԫ����-���ߺŶ�Ӧ�б�
	CList<int, int> m_olsColumnPointNb;	// ��Ԫ����-���Ŷ�Ӧ�б�

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

	CRect m_oRectArea;	// ͼ����λ��

public: // ����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// �ر�
	void OnClose();

	// �õ�ͼ�ε�Ԫ������ͼ�ε�Ԫ��������
	CGraphInstrumentData* GetGraphInstrumentDataByIndex(unsigned int uiIndex);
	// �õ���������ָ�룬����ͼ�ε�Ԫ��������
	CInstrument* GetInstrumentByIndex(unsigned int uiIndex);
	// �õ�ͼ�ε�Ԫ������ͼ��������
	CGraphInstrumentData* GetGraphInstrumentDataByPosIndex(unsigned int uiPosX, unsigned int uiPosY);
	// �õ���������ָ�룬����ͼ��������
	CInstrument* GetInstrumentByPosIndex(unsigned int uiPosX, unsigned int uiPosY);
	// �õ���������Ӧ�Ĳ��ߺ�
	int GetLineNbByRowIndex(unsigned int uiRowIndex);
	// �õ���������Ӧ�Ĳ���
	int GetPointNbByColumnIndex(unsigned int uiColumnIndex);
	// ���õ�Ԫ��������Ͳ��߶�Ӧ��ϵ
	void SetLineNbList();
	// ���õ�Ԫ��������Ͳ���Ӧ��ϵ
	void SetPointNbList();

	// ��������ͼ����ͼ����ͼ�ε�Ԫ����
	void LoadSiteData();
	// ����������λ�ã��ݹ�
	void SetInstrumentPos(CInstrument* pInstrument, unsigned int uiDirection);
	// ��ѡ������ת��Ϊ���������ַ���
	CString ConvertSelectAreaToAbsoluteSpreadString(CRect* pSelectAreaIndex);

	// ������ͼ
	void DrawGrid(CDC* pDC, int iPaperX, int iPaperY, int iGridX, int iGridY);
	// �����߱�ߺͲ����
	void DrawMarkLineNbAndPointNb(CDC* pDC, int iGridX, int iGridY);
	// �����߱�ߣ�����
	void DrawMarkLineNb(CDC* pDC, int iGridY);
	// ������ߣ����
	void DrawMarkPointNb(CDC* pDC, int iGridX);
	// ��ͼ�ε�Ԫ������
	void DrawUnitLinkLineAll(CDC* pDC, int iGridX, int iGridY);
	// ��ͼ�ε�Ԫ
	void DrawUnitAll(CDC* pDC, int iGridX, int iGridY, unsigned int uiTestType, bool bShowCross, bool bShowPower, bool bShowCollect);
	// �õ�ͼ�ε�Ԫ�ߴ�
	void GetUnitSize(int iGridX, int &iUnitWidth, int &iUnitHight, int &iUnitSizeMode);
};
