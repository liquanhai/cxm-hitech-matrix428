// Draw3DGraph_Test5Dlg.h : ͷ�ļ�
//

#pragma once
#include "nigraph3d.h"


// CDraw3DGraph_Test5Dlg �Ի���
class CDraw3DGraph_Test5Dlg : public CDialog
{
// ����
public:
	CDraw3DGraph_Test5Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAW3DGRAPH_TEST5_DIALOG };

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
	// ��ͼ�ؼ����Ʊ���
	NI::CNiGraph3D m_ctrlGraph3D;
	NI::CNiAxis3D m_Axis3D;
};
