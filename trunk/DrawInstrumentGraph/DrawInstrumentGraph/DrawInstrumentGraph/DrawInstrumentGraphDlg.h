// DrawInstrumentGraphDlg.h : ͷ�ļ�
//

#pragma once
#include "InstrumentGraph.h"
// CDrawInstrumentGraphDlg �Ի���
class CDrawInstrumentGraphDlg : public CDialog
{
// ����
public:
	CDrawInstrumentGraphDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAWINSTRUMENTGRAPH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CInstrumentGraph m_oInstrumentGraph;
public:
	// �����豸����ͼ
	void OnDrawInstrumentGraph(void);
};
