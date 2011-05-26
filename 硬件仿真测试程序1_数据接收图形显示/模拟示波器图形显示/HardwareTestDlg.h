// HardwareTestDlg.h : ͷ�ļ�
//

#include "OScopeCtrl.h"
#include <vector>
#include "resource.h"
using namespace std;

// ��ͼ�ؼ�����
#define GraphViewNum	8
// ��ͼ�ؼ�ID��
#define GraphViewId		8
// �����������ݴ��������ʾ�ؼ�ID����
#define MathValueIdNum	4 
// ��ʼ�ɼ�����
#define StartSampleCmd	81
// �������ݰ��Ĵ�С
#define ReceiveDataSize	74
// AD���ݲɼ����ն˿�
#define ADRecPort		0x8300
// AD���ݲɼ�����Ͷ˿�
#define ADCmdSend		0x6000
// AD���ݲɼ�����Ӧ��˿�
#define ADCmdRec		0x6500
// IP�㲥��ַ
#define IPBroadcastAddr	"255.255.255.255"
#pragma once


// CHardwareTestDlg �Ի���
class CHardwareTestSocket;
class CHardwareTestDlg : public CDialog
{
// ����
public:
	CHardwareTestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CHardwareTestDlg();

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

public:
	// ͼ��ģ��ָ��
	COScopeCtrl m_OScopeCtrl[GraphViewNum];
	// ͼ�ζ�Ӧ��picture�ؼ�IDָ��
	int m_iGraphViewId[GraphViewId];
	// ������ʼ��־λ
	BOOL m_bStartSample;
	// ���õĲ���ʱ��
	double m_dSampleTime;
	// �ɼ���������
	vector <double> m_dSampleData[GraphViewNum];
	// ѡ����������
	int m_bSelectObject[GraphViewId];
	// ѡ����������1
	int m_bSelectObject1;
	// ѡ����������2
	int m_bSelectObject2;
	// ѡ����������3
	int m_bSelectObject3;
	// ѡ����������4
	int m_bSelectObject4;
	// ѡ����������5
	int m_bSelectObject5;
	// ѡ����������6
	int m_bSelectObject6;
	// ѡ����������7
	int m_bSelectObject7;
	// ѡ����������8
	int m_bSelectObject8;
	// ѡ�е�������������
	char** m_cSelectObjectName;
	// ������������ļ���·��
	char cSaveToFilePath[MAX_PATH];
	CString strFilePath;
	// �����������������Сֵ
	UINT MAX_RANGE; 
	UINT MIN_RANGE; 

	// ����ֹͣ��־λ
	BOOL m_bStopSample;
	// ����ѡ��
	UINT32 m_uiSampleNb;
	// �����������Ĳ�������
	unsigned int m_iMaxLength;
	// �������ݴ�������ʾ����ؼ�ID
	int m_iMathId[GraphViewId][MathValueIdNum];
	// ѡ�������������������
	int m_bSelectObjectNoise[GraphViewId];
	// ѡ����������1���������
	int m_bSelectObjectNoise1;
	// ѡ����������2���������
	int m_bSelectObjectNoise2;
	// ѡ����������3���������
	int m_bSelectObjectNoise3;
	// ѡ����������4���������
	int m_bSelectObjectNoise4;
	// ѡ����������5���������
	int m_bSelectObjectNoise5;
	// ѡ����������6���������
	int m_bSelectObjectNoise6;
	// ѡ����������7���������
	int m_bSelectObjectNoise7;
	// ѡ����������8���������
	int m_bSelectObjectNoise8;
	// �����ɼ���ʼ��־λ
	BOOL m_bStartNoise;
	// ��������ѡ��
	UINT32 m_uiNoiseNb;
	// AD�������ݽ���SOCKET
	CHardwareTestSocket* m_socketAD;
	// AD���������SOCKET
	CSocket m_socketADCmd;
public:
	// ����ͼ����ʾģ��
	void CreateGraph(int iGraphViewNum, int* iGraphViewId, COScopeCtrl* oScopeCtrl);
	// ���ò���ȡֵ��Χ
	void SetRange(double dLower, double dUpper, int nDecimalPlaces, int iGraphViewNum, COScopeCtrl* oScopeCtrl);
	// ����Y���ǩ
	void SetYUnits(CString string, int iGraphViewNum, COScopeCtrl* oScopeCtrl);
	// ����X���ǩ
	void SetXUnits(CString string, int iGraphViewNum, COScopeCtrl* oScopeCtrl);
	// ���ñ�����ɫ
	void SetBackgroundColor(COLORREF color, int iGraphViewNum, COScopeCtrl* oScopeCtrl);
	// ����������ɫ
	void SetGridColor(COLORREF color, int iGraphViewNum, COScopeCtrl* oScopeCtrl);
	// ���û�����ɫ
	void SetPlotColor(COLORREF color, int iGraphViewNum, COScopeCtrl* oScopeCtrl);
	// ���ɼ��������ݱ��浽�ļ���
	void OnSaveToFile(int iMathValueIdNum, int iGraphViewNum, char** cppSelectObjectName, vector <double>* dSampleData);
	// �����������Ĳ�������
	unsigned int OnSampleDataMaxLength(int iGraphViewNum, vector<double>* dSampleData);
	// ��������ݵ�ƽ��ֵ
	double SampleDataAverage(vector<double> dSampleData);
	// ��������ݵ����ֵ
	double SampleDataMax(vector<double> dSampleData);
	// ��������ݵ���Сֵ
	double SampleDataMin(vector<double> dSampleData);
	// ��������ݵľ�����
	double SampleDataRms(vector<double> dSampleData);

	// ���ղ�������
	void ReceiveSampleData(byte* pSampleData);


public:
	afx_msg void OnBnClickedButtotStartSample();
	afx_msg void OnBnClickedButtonStopSample();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonStartNoise();
	afx_msg void OnBnClickedButtonStopNoise();
	// �������ݲɼ�����֡
	void OnSendCmdFrame(unsigned short usCommand, byte byOperation, UINT uiTestNb);
};
