// ��ͼ����Dlg.h : ͷ�ļ�
//

#pragma once
#include "ChartViewer.h"
#include "afxwin.h"
#include "Parameter.h"
#include "SocketADCDataRec.h"
#include "ParameterSet.h"
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
	// ��¼����ͼ�ߵ����Ϣ
	vector <vector <double>> m_DrawLine_Y;
	// ��¼X���������Ϣָ��
	vector <double>	m_DrawPoint_X;
	// Y������̶���־
	BOOL m_bCheckYAxisFixed;
	// ��ʼ����ˢ�±�־λ
	BOOL m_bStartShow;
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
	// ADC���ݿ�ʼ�����ݵ���
	unsigned int m_uiADCStartNum;
	// ADC����ת����ʽ
	unsigned int m_uiADCDataCovNb;
	// �ɼ�վ�ɼ�����ADC��������
	unsigned int m_uiADCDataNum;
	// ÿ���ɼ�վ�ɼ�����ADC���ݸ���
	unsigned int m_uiADCDataFduNum;
	// ADC���ݻ�����ָ������
	double** m_viewPortDataSeries;
	// ��ȡ�ļ������ݵ�����
	unsigned int m_uiADCFileLineNum;
	// ����ADC���ݲɼ��Ĳɼ�վ�豸��
	unsigned int m_uiInstrumentADCNum;
	// �ļ��б���Ϣ
	vector<CString> m_FileInfo;
	// �洢ADC������Ϣ
	vector<CString> m_ADCDataInfo;
	// �豸��ǵ��������ָ��
	unsigned int* m_uiInstrumentNb;
	// ��ȡ�ļ�
	CFile m_file;
	// ��ʼ����ADC���ݵ����ʼλ��
	unsigned int m_uiStartDrawPointsNum;
	// ���ļ����ļ���ţ���0��ʼ��
	unsigned int m_uiOpenFileNb;
	// ��ȡ�ļ���ͼ��־λ
	unsigned int m_uiOptType;
	// �ļ�����ÿ�������豸�����в��������ļ���������ADC��������
	unsigned int m_uiEndDrawPointsNumMax;
	// ���ļ����ҵ�������������
	unsigned int m_uiFindLineCount;
	// ADC�����ļ�һ����ռ�ֽ���
	unsigned int m_uiADCLineBufNum;
	// ADC�����ļ�һ�ж�ȡ������
	wchar_t* m_pLinebufRead;
	// ��ͼ�����¼�
	HANDLE m_hDrawGraph;
	// �������ý���
	CParameterSet m_oParameterSet;

public:	
	CChartViewer	m_ChartViewer;	// ��ӻ�ͼ�ؼ��Ŀ��Ʊ���
	double m_currentDuration;			// ��ǰ��ʾ���ݵ�ĸ���
	CButton m_PointerPB;				// ����Pointer�Ŀ��Ʊ���
	CButton m_XZoomPB;				// ����X Zoom/Y Auto�Ŀ��Ʊ���
	CScrollBar m_HScrollBar;			// ����������Ŀ��Ʊ���
	CScrollBar m_VScrollBar;			// ����������Ŀ��Ʊ���
	CComboBox m_Duration;			// ��ͼ��ʾ����ѡ����Ʊ���
	double m_minDuration;				// ������ʾ��ĸ���
	CSocketADCDataRec m_oSocketADCDataRec;	// ADC���ݽ���CSocket�����
private:
	// �õ�Ĭ�ϵı�����ɫ
	int getDefaultBgColor(void);
	// ����һ��ͼ����Դ����ť
	void LoadButtonIcon(int buttonId, int iconId, int width, int height);
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
	// ���ļ����������ݣ�������������һ���ļ���vector��Ҫ��������
	BOOL LoadData(CString csOpenFilePath, BOOL bLoadLastFile);
	// �����һ��ADC����
	void OnPhraseEachLine(CString str);
	// ����ADC���ݽ���Socket
	void OnCreateADCRecSocket(void);
	// ��ADC������Ϣ�������н����������ڻ�ͼ
	BOOL FraseDataToDraw(unsigned int uiStartDrawPointsNum, unsigned int uiEndDrawPointsNum);
	// �������ݲ���ͼ
	BOOL FraseDataAndDrawGraph(void);
	// ���ļ�����������
	void LoadADCDataFromFile(unsigned int uiStartDrawPointsNum, unsigned int uiEndDrawPointsNum);
	// �������һ��ADC���ݲ����ļ�
	BOOL LoadLastADCDataFromFile(void);
	// �����豸��ǩ
	void OnPhraseLabels(CString str);
	// ��������ADC����
	void OnNetADCGraph(void);
	// ����X��ȡֵ��Χ�ͱ�ǩ���
	void OnSetXAxisRange(double dbmaxData, double dbminData);
	// ���������ļ�������ͼ��׼������
	void OnPrepareToDrawGraph(void);
	// �����ļ����µ��ļ����г�
	void FindFileAndList(CString csSaveFolderPath);
	// 	// ����λͼ
	// 	BOOL LoadBitmapAndPrint(CString   csPathName);
	// 	void OnPrint(CDC* pdc,CPrintInfo * lParam,CString strFileName);
	// �õ������ô�ӡ����Ϣ
	void GetAndSetPrinterInfo(void);
	// ���ļ��ж�ȡbmp����ӡ
	void LoadBmpFromFileAndPrint(CString csPathName);
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
	afx_msg void OnBnClickedYzoompb();
	afx_msg void OnBnClickedButtonRedraw();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedCheckYaxisfixed();
	afx_msg void OnBnClickedButtonOpenadcfolder();
	afx_msg void OnLbnDblclkListFile();
	afx_msg void OnBnClickedButtonParameterset();
	// �����ͼ���License
	bool LoadChartDirLicense(void);
};
