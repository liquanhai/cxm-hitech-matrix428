#pragma once
#include "afxwin.h"


// CTabADCSettings �Ի���

class CTabADCSettings : public CDialog
{
	DECLARE_DYNAMIC(CTabADCSettings)

public:
	CTabADCSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabADCSettings();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADCSETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	// ADCͬ������ѡ����Ʊ���
	CComboBox m_comboSync;
	// ADCģʽ����ѡ����Ʊ���
	CComboBox m_comboMode;
	// ADC����������ѡ����Ʊ���
	CComboBox m_comboSps;
	// ADCFIR��λ����ѡ����Ʊ���
	CComboBox m_comboPhs;
	// ADC�����˲�������ѡ����Ʊ���
	CComboBox m_comboFilter;
	// ADC��·������ѡ����Ʊ���
	CComboBox m_comboMux;
	// ADC CHOP����ѡ����Ʊ���
	CComboBox m_comboChop;
	// ADC PGA��������ѡ����Ʊ���
	CComboBox m_comboPga;
	// HPF��λ���Ʊ���
	CEdit m_editHpfLow;
	// HPF��λ���Ʊ���
	CEdit m_editHpfHigh;
};
