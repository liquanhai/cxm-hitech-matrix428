#pragma once


// CWndInstrument

class CWndInstrument : public CBCGPStatic
{
	DECLARE_DYNAMIC(CWndInstrument)

public:
	CWndInstrument();
	virtual ~CWndInstrument();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

public:	// ����
	/** ��������*/
	unsigned int m_uiInstrumentCountAll;

	/** ͼ�ε�Ԫ���X*/
	int m_iGridX;
	/** ͼ�ε�Ԫ���Y*/
	int m_iGridY;
	/** ͼ�ε�Ԫ���*/
	int m_iUnitWidth;
	/** ͼ�ε�Ԫ�߶�*/
	int m_iUnitHight;
	/** ͼ�θ߶�X*/
	int m_iPaperHight;
	/** ��ͼ����X*/
	CRect m_oRect;

public:	// ����
	// ��Ӧ��ʾ�ػص�ͼ����ͼ
	void OnShowDetourGraphView(unsigned int uiCount);

	// ������
	void DrawBackground(CDC* pDC);
	// ��������
	void DrawLinkLine(CDC* pDC);
	// ����Ԫͼ
	void DrawUnit(CDC* pDC, int iIndex);
};


