#pragma once
#include "afxwin.h"
#include "SetupGridCtrl.h"
// vivi 2010.11.9
// CDlgImpulsive �Ի���

class CDlgImpulsive : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgImpulsive)

public:
	CDlgImpulsive(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImpulsive();

// �Ի�������
	enum { IDD = IDD_IMPULSIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	// ���öԻ���ߴ�ΪIDC_STATICPICTURE�ĳߴ�
	CRect dlgRect;
	// �ؼ�IDC_COMBO_PULG�Ŀ��Ʊ���
	int m_comboPulg;
	// �ؼ�IDC_COMBO_BOXTYPE�Ŀ��Ʊ���
	int m_comboBoxType;

	// ������¼���༭
	CStatic m_ctrlEditGridLocation;
	// ������¼���б�
	CStatic m_ctrlGridLocation;
	// ������¼���ؼ�
	CGridCtrlEdit* m_wndEditGrid;
	CGridCtrlList* m_wndListGrid;
public:
	BOOL OnInitDialog(void);
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg LRESULT OnGridItemClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGridItemDblClk(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnDestroy();
	// ����������������
	void Load(void);
	// ����һ��������¼����¼
	void AppendRecord(AUXICHANNEL m_arrAuxiChannel);
};
