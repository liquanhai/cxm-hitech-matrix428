// Draw3DGraph_Test2Dlg.h : ͷ�ļ�
//

#pragma once
#include "nigraph3d.h"
#include "afxwin.h"
// �������ݷ�ֵ
#define SampleAmpMax		2.5
// ����ʱ��
#define SampleTime			100
// ͨ����
#define TraceNum			10
// ����
#define LineNum				3
// ��ʱ�����
#define TimerID				1
// ��ʱ����ʱ
#define TimerDelay			500

// CDraw3DGraph_Test2Dlg �Ի���
class CDraw3DGraph_Test2Dlg : public CDialog
{
// ����
public:
	CDraw3DGraph_Test2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAW3DGRAPH_TEST2_DIALOG };

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
	// 3D��ͼ�ؼ����Ʊ���
	NI::CNiGraph3D m_ctrlGraph3D;
	// ��ʼ��ʾ��ť���Ʊ���
	CButton m_ctrlBtnStart;
	// ֹͣ��ʾ��ť���Ʊ���
	CButton m_ctrlBtnStop;
	CNiReal64Vector m_xTimeData;
	CNiReal64Vector m_yTraceData;
	CNiReal64Matrix m_zAmpData;
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedRadioSurface();
	afx_msg void OnBnClickedRadioSurfaceline();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// ����
	int m_iCounter;
	CNiAxis3D m_Axis3D;
};
