#pragma once

#include "SensorListCtrl.h"

// CSensorListView ��ͼ

class CSensorListView : public CBCGPGridView
{
	DECLARE_DYNCREATE(CSensorListView)

protected:
	CSensorListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSensorListView();
	virtual void OnInitialUpdate();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

public:	// ����	
	CSensorListCtrl* m_pSensorListCtrl;	// �첨���б�����ؼ�

public:	// ����
	void AdjustLayout();	// ����

	// ���¼����ֳ���������
	void OnReloadSiteDataCMD();

	// Ϊ�µĲ�������ˢ����ʾ
	void OnRefreshForNewTestValue(int iTestType);
};


