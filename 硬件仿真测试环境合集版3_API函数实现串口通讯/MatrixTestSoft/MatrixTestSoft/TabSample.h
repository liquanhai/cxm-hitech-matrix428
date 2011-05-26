#pragma once
#include "OScopeCtrl.h"
#include <vector>
#include "ThreadManage.h"
#include "Parameter.h"

using namespace std;
// CGraphView �Ի���

class CTabSample : public CDialog
{
	DECLARE_DYNAMIC(CTabSample)

public:
	CTabSample(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabSample();

// �Ի�������
	enum { IDD = IDD_DIALOG_SAMPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ʼ��
	void OnInit(void);

public:
	// ͼ��ģ��
	COScopeCtrl m_OScopeCtrl[GraphViewNum];
	// ͼ�ζ�Ӧ��picture�ؼ�IDָ��
	int m_iGraphViewId[GraphViewId];
	// �������ݴ�������ʾ����ؼ�ID
	int m_iMathId[GraphViewId][MathValueIdNum];
	// ѡ����������
	int m_iSelectObject[GraphViewId];
	// ѡ�������������������
	int m_iSelectObjectNoise[GraphViewId];
	// �ɼ���������
	vector <double> m_dSampleData[GraphViewNum];
	// ѡ�е�������������
	char* m_cSelectObjectName[GraphViewId];
	// �߳̿�����Ķ���
	CThreadManage m_oThreadManage;
protected:
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// ��������������ֵ
	unsigned int m_uiScrollBarMax;
	// �������������Сֵ
	unsigned int m_uiScrollBarMin;
protected:
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
public:
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// ����������־λ
	BOOL m_bMatrixNetwork;

public:
	afx_msg void OnBnClickedCheckMatrixnetwork();
	afx_msg void OnBnClickedButtotStartsample();
	afx_msg void OnBnClickedButtonStopsample();
	afx_msg void OnBnClickedButtonStartnoise();
	afx_msg void OnBnClickedButtonStopnoise();
	afx_msg void OnBnClickedButtonSavefilepath();
	afx_msg void OnBnClickedButtonReset();

	// �ر�
	void OnClose();
	// ������ʼ��־λ
	BOOL m_bStartSample;
	// ���õĲ���ʱ��
	double m_dSampleTime;
	// ѡ����������1
	int m_iSelectObject1;
	// ѡ����������2
	int m_iSelectObject2;
	// ѡ����������3
	int m_iSelectObject3;
	// ѡ����������4
	int m_iSelectObject4;
	// ѡ����������1���������
	int m_iSelectObjectNoise1;
	// ѡ����������2���������
	int m_iSelectObjectNoise2;
	// ѡ����������3���������
	int m_iSelectObjectNoise3;
	// ѡ����������4���������
	int m_iSelectObjectNoise4;
	// �����ɼ���ʼ��־λ
	BOOL m_bStartNoise;
	// ����ѡ��
	unsigned int m_uiSampleNb;
	// ��������ѡ��
	unsigned int m_uiNoiseNb;
	// �����������Ĳ�������
	unsigned int m_iMaxLength;
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
	// �������ݲɼ�����֡
	void OnSendCmdFrame(unsigned int uiTestNb);
	// ����ֹͣ��־λ
	BOOL m_bStopSample;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	// �豸�Ͽ�����ͼ��
	HICON m_iconDisconnected;
	// �豸����ͼ��
	HICON m_iconConnected;
	afx_msg void OnBnClickedCheckHeartbeat();
	// �Ƿ���������BOOL�ͱ���
	BOOL m_bHeartBeat;
};
