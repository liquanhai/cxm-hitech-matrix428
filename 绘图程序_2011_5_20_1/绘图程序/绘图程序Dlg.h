// ��ͼ����Dlg.h : ͷ�ļ�
//

#pragma once
#include "ChartViewer.h"
#include "afxwin.h"
#include "Parameter.h"
// C��ͼ����Dlg �Ի���
class C��ͼ����Dlg : public CDialog
{

// ����
public:
	C��ͼ����Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~C��ͼ����Dlg();

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

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
private:
	// Ĭ�ϵı�����ɫ
	int m_extBgColor;

	double m_minDate;			// The earliest date (in chartTime unit)
	double m_dateRange;			// The overall duration (in seconds)
	double m_maxValue;			// The maximum overall y scale
	double m_minValue;			// The minimum overall y scale

	DoubleArray m_timeStamps;
	DoubleArray m_dataSeriesA;
	DoubleArray m_dataSeriesB;
	DoubleArray m_dataSeriesC;
public:
	// ��ӻ�ͼ�ؼ��Ŀ��Ʊ���
	CChartViewer	m_ChartViewer;
private:
	// ����һ��ͼ����Դ����ť
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
	// Moves the scroll bar when the user clicks on it
	double moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// Draw chart
	void drawChart(CChartViewer *viewer);
	// Update image map 
	void updateImageMap(CChartViewer *viewer);
public:
	// �õ�Ĭ�ϵı�����ɫ
	int getDefaultBgColor(void);
	// ��������
	void LoadData(void);
	// ��ǰ��ʾ���ݵ�ĸ���
	double m_currentDuration;
	// ����Pointer�Ŀ��Ʊ���
	CButton m_PointerPB;
	// ����X Zoom/Y Auto�Ŀ��Ʊ���
	CButton m_XZoomPB;
	afx_msg void OnBnClickedPointerpb();
	afx_msg void OnBnClickedZoominpb();
	afx_msg void OnBnClickedZoomoutpb();
	afx_msg void OnBnClickedXzoompb();
	afx_msg void OnBnClickedXyzoompb();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnViewPortChanged();
	afx_msg void OnBnClickedChartViewer();
	// ����������Ŀ��Ʊ���
	CScrollBar m_HScrollBar;
	// ����������Ŀ��Ʊ���
	CScrollBar m_VScrollBar;

	double timeTemp[2000];
	double data0[2000];
	double data1[2000];
	double data2[2000];
	// ������ʾ��ĸ���
	double m_minDuration;
};
