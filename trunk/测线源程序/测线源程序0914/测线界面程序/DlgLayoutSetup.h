#pragma once

#include "TabMarker.h"
#include "TabAux.h"
#include "TabDetour.h"
#include "TabMute.h"
#include "TabBlastMachine.h"

#include "SiteData.h"

/**
CDlgLayoutSetup �������öԻ�����
*/
class CDlgLayoutSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgLayoutSetup)

public:
	CDlgLayoutSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLayoutSetup();

// �Ի�������
	enum { IDD = 0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

public:	// ����
	/** �ֳ�����*/
	CSiteData* m_pSiteData;
	/** ����ҳ����*/
	CBCGPTabWnd m_oTabWnd;
	/** ����ҳ��ǵ�*/
	CTabMarker m_oTabMarker;
	/** ����ҳ������*/
	CTabAux m_oTabAux;
	/** ����ҳ�ػص�*/
	CTabDetour m_oTabDetour;
	/** ����ҳ�Ƶ�*/
	CTabMute m_oTabMute;
	/** ����ҳ��ը��������*/
	CTabBlastMachine m_oTabBlastMachine;

public:	// ����
	// ��Ӧ��굥����ť��Apply
	afx_msg void OnBnClickedButtonApply();
	// ��Ӧ��굥����ť��Reset
	afx_msg void OnBnClickedButtonReset();
	// ��Ӧ��굥����ť��Add
	afx_msg void OnBnClickedButtonAdd();
	// ��Ӧ��굥����ť��Change
	afx_msg void OnBnClickedButtonChange();
	// ��Ӧ��굥����ť��Delete
	afx_msg void OnBnClickedButtonDelete();
	// ��Ӧ��굥����ť��Clear
	afx_msg void OnBnClickedButtonClear();

	// ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
	void OnGraphViewInstrumentSetMarker(unsigned int uiInstrumentType, unsigned int uiSN);
	// ��Ӧ����ͼ����ͼ�����˵����ø�����
	void OnGraphViewInstrumentSetAuxiliary(unsigned int uiInstrumentType, unsigned int uiSN);
	// ��Ӧ����ͼ����ͼ�����˵������ػص�
	void OnGraphViewInstrumentSetDetour(unsigned int uiInstrumentTypeLow, unsigned int uiSNLow, unsigned int uiInstrumentTypeHigh, unsigned int uiSNHight);
	// ��Ӧ�첨��ͼ����ͼ�����˵�Mute����
	void OnGraphViewSensorSetMute(unsigned int uiNbLine, unsigned int uiNbPoint);
};
