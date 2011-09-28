#pragma once

#include "MainFrm.h"
#include "SiteData.h"
#include "StaticFloat.h"

// CInstrumentGraphView ��ͼ

class CInstrumentGraphView : public CScrollView
{
	DECLARE_DYNCREATE(CInstrumentGraphView)

protected:
	CInstrumentGraphView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CInstrumentGraphView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGraphViewInstrumentSetMarker();
	afx_msg void OnGraphViewInstrumentProperties();
	afx_msg void OnGraphViewInstrumentSetAuxiliary();
	afx_msg void OnGraphViewInstrumentSetLowBoxDetour();
	afx_msg void OnGraphViewInstrumentSetHighBoxDetour();
	afx_msg void OnGraphViewInstrumentFormLine();
	afx_msg void OnPopupGraphviewInstrumentSetinstrument();

	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

public: // ����
	/**�ֳ����ݶ���*/
	CSiteData*	m_pSiteData;

	/**��Ԫ��X����ߴ�*/
	int m_iGridX;
	/**��Ԫ��Y����ߴ�*/
	int m_iGridY;

	/**��Ԫ��X����ߴ磬��һ��*/
	int m_iGridXPre;
	/**��Ԫ��Y����ߴ磬��һ��*/
	int m_iGridYPre;

	/**ͼ����X����ߴ�*/
	int m_iPaperX;
	/**ͼ����Y����ߴ�*/
	int m_iPaperY;

	/**�Ŵ���*/
	float m_fZoomRate;

	/**������λ��*/
	CPoint m_oPointScrollPos;
	/**��������ʱ����*/
	CPoint m_oPointBase;
	/**�����ͷ�ʱ����*/
	CPoint m_oPointLast;
	/**�������Ƿ���*/
	bool m_bMouseDownLeft;
	/**����м���Ƿ���*/
	bool m_bMouseDownMiddle;

	/**�Ƿ�����м��ѡ������λ��*/
	bool m_bDrawSelectArea;
	/**����м��ѡ������λ�ã���λ����*/
	CRect m_oSelectAreaPoint;
	/**����м��ѡ������λ�ã���λ��Ԫ��*/
	CRect m_oSelectAreaIndex;

	/**ѡ�е�Ԫ������*/
	int m_iSelectUnitColumnIndex;
	/**ѡ�е�Ԫ������*/
	int m_iSelectUnitRowIndex;

	/**ѡ��������������*/
	int m_iSelectLinkColumnIndex;
	/**ѡ��������������*/
	int m_iSelectLinkRowIndex;
	/**ѡ�������߷��� 2���£�4����*/
	int m_iSelectLinkDirection;

	/**ѡ�������Ӧ�ľ�������*/
	CString m_strAbsoluteSpread;

	/**�ػص��Ͷ�����*/
	CGraphInstrumentData* m_pGraphInstrumentDataDetourLow;
	/**�ػص��߶�����*/
	CGraphInstrumentData* m_pGraphInstrumentDataDetourHigh;

	/**����ֵƯ������*/
	CStaticFloat m_wndStaticFloat;

public: // ����
	// �Ŵ�
	void OnZoomIn();
	// �ֲ��Ŵ�
	void OnZoomInDrag();
	// �����ֲ��Ŵ�
	void OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY);
	// ��С
	void OnZoomOut();
	// �ֳ����ݶ����ʼ��
	void OnSiteDataInit();

	// ��Ӧ���ò�������
	void OnSetLineCount();

	// �����ֳ�����
	void OnLoadSiteData();
	// ���¼����ֳ�����
	void OnReloadSiteDataCMD();

	// ��ͼǰ���û�ͼ����
	void SetupPageSize();
	// ����ͼ��
	void OnZoomGraph();
	// �õ��������Ӧ�ĵ�Ԫ
	void GetUnitUnderPoint(CPoint* pPoint);
	// �õ�ѡ�е�����
	bool GetSelectAreaPoint();
	// �õ�ѡ������������������������
	void GetSelectAreaIndex();
	// ��ѡ������ת��Ϊ���������ַ���
	void ConvertSelectAreaToAbsoluteSpreadString();
	// �жϵ��Ƿ��ڻ�ͼ������
	bool JudgeIfPointInPaper(CPoint* pPoint);
	// ��ʾ��Ԫ�Ĳ��ߺźͲ���
	void OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint);
	// �ڸ�����������ʾ����ֵ
	void OnShowTestValueInFloatWindow(CInstrument* pInstrument, CPoint pointClient);
	// ��Ӧ��ʾ����ֵ
	void OnShowProperty(unsigned int uiIndex);
	// ��Ӧ��ʾ�ػص�ͼ����ͼ
	void OnShowDetourGraphView(unsigned int uiIndex);

	// ������м��ѡ������
	void DrawSelectArea(CDC* pDC);
	// ���ػص����
	void DrawDetourMarker(CDC* pDC);
	// ���ػص����
	void DrawDetourMarker(CDC* pDC, CGraphInstrumentData* m_pGraphInstrumentData);
	// ����ػص����
	void ClearDetourMarker();
	// ����ػص����
	void ClearDetourMarker(CGraphInstrumentData* m_pGraphInstrumentData);

	// Ϊ�µĲ�������ˢ����ʾ
	void OnRefreshForNewTestValue(int iTestType);
	// ���GO��ť�����ѡ���豸�Ĳ��Խ��
	void OnClearCheckInstrumentTestResult(unsigned int uiTestType);
};


