#pragma once
#include "Parameter.h"
#include "SetupGridCtrl.h"
// CDlgProcessTypeSetup �Ի���

class CDlgProcessTypeSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgProcessTypeSetup)

public:
	CDlgProcessTypeSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProcessTypeSetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROCESSSETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioStandard();
	afx_msg void OnBnClickedRadioAdvanced();
	afx_msg void OnCbnSelchangeComboProcesstypeselect();
	afx_msg void OnBnClickedButtonAuxAdd();
	afx_msg void OnBnClickedButtonAuxChange();
	afx_msg void OnBnClickedButtonAuxDelete();
	afx_msg void OnBnClickedButtonAcqAdd();
	afx_msg void OnBnClickedButtonAcqChange();
	afx_msg void OnBnClickedButtonAcqDelete();
	afx_msg void OnBnClickedButtonProAdd();
	afx_msg void OnBnClickedButtonProChange();
	afx_msg void OnBnClickedButtonProDelete();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnDestroy();
public:
	// ��������ѡ��
	int m_radioProcessSetup;
	// ��������ѡ��
	int m_cbindexProcessType;
	// Plugѡ�����ֵ����
	int m_cbindexPlug;
	// �豸����ѡ�����ֵ����
	int m_cbindexBoxType;
	// ���ŵ���ֵ����
	int m_editindexSerialNb;
	// ��¼ʱ����ֵ����
	int m_editindexRecordLength;
	// TBʱ�䴰�ڵ���ֵ����
	int m_editindexTBWindow;
	// PeakTime����ֵ����
	int m_editindexPeakTime;
	// Raw�Ĳ����ͱ���
	BOOL m_bCheckRaw;
	// CorrelWith���ַ�������
	CString m_strCorrelWith;
	// AuxesFromDSD�Ĳ����ͱ���
	BOOL m_bAuxesFromDSD;
public:
	CGridCtrlList		m_wndAuxListGrid;
	CGridCtrlEdit		m_wndAuxEditGrid;
	CGridCtrlList		m_wndAcqListGrid;
	CGridCtrlEdit		m_wndAcqEditGrid;
	CGridCtrlList		m_wndProTypeListGrid;
	CGridCtrlEdit		m_wndProTypeEditGrid;
	// ��ʾ�������ʹ���
	void OnShowProcessTypeWindow(int iProcessType);
	// ��ʾAux����
	void OnShowAuxWindow(void);
	// ��ʾProcess Type����
	void OnShowProTypeWindow(void);
	// ����Impulsive�������Ϳؼ���λ��
	void SetProcessImpulsiveCtrlsRect(void);
};
