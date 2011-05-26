#pragma once

#include "MainFrm.h"
#include "SiteData.h"
#include "StaticFloat.h"

// CSeismonitorGraphView ��ͼ

class CSeismonitorGraphView : public CScrollView
{
	DECLARE_DYNCREATE(CSeismonitorGraphView)

protected:
	CSeismonitorGraphView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSeismonitorGraphView();

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
	afx_msg void OnGraphViewSensorProperties();
	afx_msg void OnGraphViewSensorSetAuxiliary();
	afx_msg void OnGraphViewSensorSetMute();

	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

public: // ����
	CSiteData*	m_pSiteData;	// �ֳ����ݶ���

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

	/**ѡ�������Ӧ�ľ�������*/
	CString m_strAbsoluteSpread;

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
	void OnShowTestValueInFloatWindow(CChannelSetupData* pChannelSetupData, CPoint pointClient);
	// ��Ӧ��ʾ����ֵ
	void OnShowProperty(unsigned int uiIndex);

	// ������м��ѡ������
	void DrawSelectArea(CDC* pDC);

	// Ϊ�µĲ�������ˢ����ʾ
	void OnRefreshForNewTestValue();
};


