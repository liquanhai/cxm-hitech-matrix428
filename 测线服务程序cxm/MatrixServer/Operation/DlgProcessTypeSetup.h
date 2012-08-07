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
	// �����ӳٵ���ֵ����
	int m_editIndexRefractionDelay;
	// ��¼����
	int m_editIndexListeningTime;
	// PreStack�Ĳ����ͱ���
	BOOL m_bPreStack;
public:
	CGridCtrlList		m_wndAuxListGrid;
	CGridCtrlEdit		m_wndAuxEditGrid;
	CGridCtrlList		m_wndAcqListGrid;
	CGridCtrlEdit		m_wndAcqEditGrid;
	CGridCtrlList		m_wndProTypeListGrid;
	CGridCtrlEdit		m_wndProTypeEditGrid;
	// ProType�ؼ���ʾ
	typedef struct ProTypeControls
	{
		// IDC_STATIC_TBWINDOW
		bool m_bTbWindow;
		// IDC_STATIC_PEAKTIME
		bool m_bPeakTime;
		// IDC_STATIC_REFRACTIONDELAY
		bool m_bRefractionDelay;
		// IDC_STATIC_LISTENINGTIME
		bool m_bListeningTime;
		// IDC_STATIC_RAW
		bool m_bRaw;
		// IDC_STATIC_PRESTACK
		bool m_bPreStack;
	}m_oProTypeControls;
	m_oProTypeControls m_oProTypeControlsShow;
	// Aux�ؼ���ʾ
	typedef struct AuxControls
	{
		// IDC_STATIC_AUX_COR
		bool m_bAuxCor;
		// IDC_CHECK_AUX
		bool m_bAuxCheck;
	}m_oAuxControls;
	m_oAuxControls m_oAuxControlsShow;
	// Acq�ؼ���ʾ
	typedef struct AcqControls
	{
		// IDC_STATIC_ACQGROUP
		bool m_bAcqGroup;
		// IDC_STATIC_ACQ
		bool m_bAcq;
		// IDC_STATIC_ACQNB
		bool m_bAcqNb;
		// IDC_STATIC_ACQTYPE
		bool m_bAcqType;
		// IDC_STATIC_ACQSIGNSTACK
		bool m_bAcqSignStack;
		// IDC_STATIC_ACQOUTPUT
		bool m_bAcqOutput;
		// IDC_STATIC_ACQ_GRID_EDIT
		bool m_bAcqGridEdit;
		// IDC_STATIC_ACQ_GRID
		bool m_bAcqGridList;
		// IDC_BUTTON_ACQ_ADD,IDC_BUTTON_ACQ_CHANGE,IDC_BUTTON_ACQ_DELETE
		bool m_bAcqEdit;
	}m_oAcqControls;
	m_oAcqControls m_oAcqControlsShow;
	// ��ʾ�ؼ�
	void OnShowControls(void);
	// ������߽����ÿؼ�λ�úͳߴ�
	void OnSetControlsLocationByLeftPos(int ID, int iLeftPos);
	// �����ұ߽����ÿؼ�λ�úͳߴ�
	void OnSetControlsLocationByRightPos(int ID, int iRightPos);
	// ��ʾ�������Ϳؼ�
	void OnShowProTypeControls(void);
	// ��ʾAux�ؼ�
	void OnShowAuxControls(void);
	// ��ʾAcq�ؼ�
	void OnShowAcqControls(void);
	// ��ʾ�������ʹ���
	void OnShowProcessTypeWindow(int iProcessType);
	// ��ʾAux����
	void OnShowAuxWindow(void);
	// ��ʾAux����
	void OnShowAcqWindow(void);
	// ��ʾProcess Type����
	void OnShowProTypeWindow(void);
};
