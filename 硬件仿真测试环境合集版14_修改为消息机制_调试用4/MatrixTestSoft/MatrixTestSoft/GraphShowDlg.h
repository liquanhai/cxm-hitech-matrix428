#pragma once
#include "OScopeCtrl.h"
#include "ADCDataRecThread.h"
#include "afxwin.h"
#include <afxmt.h>
// CGraphShowDlg �Ի���

class CGraphShowDlg : public CDialog
{
	DECLARE_DYNAMIC(CGraphShowDlg)

public:
	CGraphShowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGraphShowDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_GRAPHSHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	// ͼ��ģ��
	COScopeCtrl m_OScopeCtrl;
protected:
	// ����ͼ����ʾģ��
	void CreateGraph(int iGraphViewId, COScopeCtrl* oScopeCtrl);
	// ���ò���ȡֵ��Χ
	void SetRange(double dLower, double dUpper, int nDecimalPlaces, COScopeCtrl* oScopeCtrl);
	// ����Y���ǩ
	void SetYUnits(CString str, COScopeCtrl* oScopeCtrl);
	// ����X���ǩ
	void SetXUnits(CString str, COScopeCtrl* oScopeCtrl);
	// ���ñ�����ɫ
	void SetBackgroundColor(COLORREF color, COScopeCtrl* oScopeCtrl);
	// ����������ɫ
	void SetGridColor(COLORREF color, COScopeCtrl* oScopeCtrl);
	// ���û�����ɫ
	void SetPlotColor(COLORREF color, COScopeCtrl* oScopeCtrl);
	// �������϶���������ȡ�ļ���ͼ
	void OnMoveScrollBarToPos(unsigned int uiPos);
public:
	// ��ʾADC�����豸�����
	unsigned int m_uiADCGraphNb;
	afx_msg void OnClose();
	// ADC���ݽ���Socket
	CADCDataRecThread* m_ADCDataRecThread;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// ��������������ֵ
	unsigned int m_uiScrollBarMax;
	// ���ú����������Χ
	void OnSetHScrollBarRange(void);
	// ��ADC�����ļ�
	void OnReadADCDataFile(CString csPathName, unsigned int uiPos, unsigned int uiPosNum);
	// ADC�����Զ��洢�ļ����ݵ����
	unsigned int m_uiADCFileLength;
	// ����ֹͣ��־λ
	BOOL m_bStopSample;
	// ����������Ŀ��Ʊ���
	CScrollBar m_ctrlScrollBar;
	// �����ٽ�������
	CCriticalSection m_Sec;
	// ��������ָ��
	double* m_pSampleData;
	// ��������
	unsigned int m_uiSampleDataNum;
};
