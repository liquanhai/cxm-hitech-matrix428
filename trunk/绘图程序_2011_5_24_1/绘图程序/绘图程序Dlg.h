// ��ͼ����Dlg.h : ͷ�ļ�
//

#pragma once
#include "ChartViewer.h"
#include "afxwin.h"
#include "Parameter.h"
#include <vector>
using namespace std;
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
	//�ڴ��ڴ�С�����仯ʱ���ؼ�λ�ÿ�����Ӧ�Ľ��е���
	typedef struct _dlgControlTag 
	{
		int iId;
		int iFlag;
		int iPercent;
	} DLGCTLINFO, *PDLGCTLINFO;
	enum
	{
		MOVEX = 0,
		MOVEY,
		MOVEXY,
		ELASTICX,
		ELASTICY,
		ELASTICXY
	};

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
	int m_extBgColor;						// Ĭ�ϵı�����ɫ
	double m_minData;						// ���������Сֵ
	double m_maxData;					// ����������ֵ
	double m_dateRange;					// ���������ֵ�仯��Χ
	double m_maxValue;					// ����������ֵ
	double m_minValue;					// ���������Сֵ
	unsigned int m_uiIntervalNum;	// ��ͼ�������������
	// ��¼X���������Ϣ
	vector <double>	m_DrawPoint_X;
	// ��¼����ͼ�ߵ����Ϣ
	vector <vector <double>> m_DrawLine_Y;
private:
	int m_iClientWidth;				// �Ի���client����Ŀ��
	int m_iClientHeight;			// �Ի���client����ĸ߶�
	int m_iMinWidth;				// �Ի������С���
	int m_iMinHeight;				// �Ի������С�߶�
	PDLGCTLINFO m_pControlArray;	// �ؼ���Ϣ����ָ��
	int m_iControlNumber;			// ���ÿؼ���Ϣ�Ŀؼ�����
	BOOL m_bShowSizeIcon;			// �Ƿ���ʾ��ʾ�ɸı��С��ͼ��
	CStatic m_wndSizeIcon;			// ��ͼ��ľ�̬�ؼ�
	// ����ͼ���bitmap
	CBitmap m_bmpSizeIcon; 
	BITMAP m_bitmap; 
	// ���ļ���·��
	CString m_csOpenFilePath;
	// �ɼ�վ�豸����
	unsigned int m_uiInstrumentMaxNum;
	// ����ADC���ݲɼ��Ĳɼ�վ�豸��
	unsigned int m_uiInstrumentADCNum;
	// ADC���ݿ�ʼ�����ݵ���
	unsigned int m_uiADCStartNum;
	// ADC����ת����ʽ
	unsigned int m_uiADCDataCovNb;
	// �ɼ�վ�ɼ�����ADC��������
	unsigned int m_uiADCDataNum;
	// ÿ���ɼ�վ�ɼ�����ADC���ݸ���
	unsigned int m_uiADCDataFduNum;
	// �ɼ�վADC���ݴ洢
	vector<double>* m_dbFduData;
	// ADC���ݻ�����ָ������
	double** m_viewPortDataSeries;
	// ��¼��һ�����ݿ��ٵĻ�����
	double *m_dbDataTemp;
public:	
	CChartViewer	m_ChartViewer;	// ��ӻ�ͼ�ؼ��Ŀ��Ʊ���
	double m_currentDuration;			// ��ǰ��ʾ���ݵ�ĸ���
	CButton m_PointerPB;				// ����Pointer�Ŀ��Ʊ���
	CButton m_XZoomPB;				// ����X Zoom/Y Auto�Ŀ��Ʊ���
	CScrollBar m_HScrollBar;			// ����������Ŀ��Ʊ���
	CScrollBar m_VScrollBar;			// ����������Ŀ��Ʊ���
	CComboBox m_Duration;			// ��ͼ��ʾ����ѡ����Ʊ���
	double m_minDuration;				// ������ʾ��ĸ���
private:
	// �õ�Ĭ�ϵı�����ɫ
	int getDefaultBgColor(void);
	// ��������
	BOOL OnOpenFile(void);
	// ����һ��ͼ����Դ����ť
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
	// ���û�ѡ��ʱ�ƶ�������
	double moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// ����ͼ��
	void drawChart(CChartViewer *viewer);
	// �ػ�ͼƬ
	void updateImageMap(CChartViewer *viewer);
	// ��֤�û��������ʾ����
	void validateDuration(const CString &text);
	// ���ÿؼ���Ϣ
	BOOL SetControlProperty(PDLGCTLINFO lp, int nElements);
	// �Ƿ��ڶԻ������½���ʾ��ʾ�ɸı��С��ͼ��
	void ShowSizeIcon(BOOL bShow = TRUE);
	// ���Ի�����ؼ���Ϊ�ߴ�ɱ��
	void OnSiteSizeBox(void);
	// ���ļ�����������
	BOOL LoadData(CString csOpenFilePath);
	// �����һ��ADC����
	void OnPhraseFirstLine(CString str);
public:
	afx_msg void OnBnClickedPointerpb();
	afx_msg void OnBnClickedZoominpb();
	afx_msg void OnBnClickedZoomoutpb();
	afx_msg void OnBnClickedXzoompb();
	afx_msg void OnBnClickedXyzoompb();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnViewPortChanged();
	afx_msg void OnBnClickedChartViewer();
	afx_msg void OnCbnSelchangeDuration();
	afx_msg void OnCbnKillfocusDuration();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedButtonSavechart();
	afx_msg void OnBnClickedButtonOpenadcfile();
};
