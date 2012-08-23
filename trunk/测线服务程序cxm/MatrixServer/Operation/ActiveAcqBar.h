#pragma once
#include "bcgpdockingcontrolbar.h"
#include "..\\MatrixServerDll\\ConfigOperationXml.h"
class CActiveAcqBar : public CBCGPDockingControlBar
{
public:
	CActiveAcqBar(void);
	~CActiveAcqBar(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
private:
	CBCGPGridCtrl   m_GridView;
	CImageList	m_ImageList;
public:
	// ���ñ�ͷ
	bool SetGridHead(void);
	// ����ȫ��Acq��Ϣ
	void LoadAcqInfos(void);
	// ���뵥��Acq��Ϣ
	void LoadAcqInfo(m_oProcessAcqStruct* pStruct);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// �Ƿ���Ҫ������������
	bool m_bReload;
	/** ʩ���ͻ�����Ϣ*/
	m_oOptSetupDataStruct* m_pOptSetupData;
};

