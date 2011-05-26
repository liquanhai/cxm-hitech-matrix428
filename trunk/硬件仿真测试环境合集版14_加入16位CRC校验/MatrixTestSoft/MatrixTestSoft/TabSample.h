#pragma once
#include "OScopeCtrl.h"
#include <vector>
#include "ThreadManage.h"
#include "Parameter.h"
#include "ADCSet.h"
#include "GraphShowDlg.h"
#include <afxmt.h>
//#include "HeartBeatSocket.h"
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
//	COScopeCtrl m_OScopeCtrl[GraphViewNum];
	// ͼ�ζ�Ӧ��picture�ؼ�IDָ��
//	int m_iGraphViewId[GraphViewId];
	// ѡ����������
	int m_iSelectObject[GraphViewNum];
	// ѡ�������������������
	int m_iSelectObjectNoise[GraphViewNum];
	// ѡ�е�������������
	char m_cSelectObjectName[GraphViewNum][RcvFrameSize];
	// �������ݴ�������ʾ����ؼ�ID
//	int m_iMathId[GraphViewId][MathValueIdNum];
	// �߳̿�����Ķ���
	CThreadManage m_oThreadManage;
	// ����Socket
//	CHeartBeatSocket m_HeartBeatSocket;
protected:
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
protected:
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
	afx_msg void OnBnClickedButtonSavefilepath();
	afx_msg void OnBnClickedButtonReset();

	// ADC���������
	CADCSet m_oADCSet;
	// �ر�
	void OnClose();
	// ������ʼ��־λ
	BOOL m_bStartSample;
	// ��������ݵ�ƽ��ֵ
	double SampleDataAverage(vector<double> dSampleData);
	// ��������ݵ����ֵ
	double SampleDataMax(vector<double> dSampleData);
	// ��������ݵ���Сֵ
	double SampleDataMin(vector<double> dSampleData);
	// ��������ݵľ�����
	double SampleDataRms(vector<double> dSampleData);
	// �����������Ĳ�������
	unsigned int OnSampleDataMaxLength(int iGraphViewNum, vector<double>* dSampleData);
	// �������ݲɼ�����֡
	void OnSendCmdFrame(int* pSelectObject);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	// �ɼ�վ�豸�Ͽ�����ͼ��
	HICON m_iconFDUDisconnected;
	// �ɼ�վ�豸����ͼ��
	HICON m_iconFDUConnected;
	// ����վ�豸�Ͽ�����ͼ��
	HICON m_iconLAUXDisconnected;
	// ����վ�豸����ͼ��
	HICON m_iconLAUXConnected;
	afx_msg void OnBnClickedCheckHeartbeat();
	// �Ƿ���������BOOL�ͱ���
	BOOL m_bHeartBeat;
	afx_msg void OnBnClickedButtonSetadc();
	// ADC��������
	void OnADCSet(unsigned int uiIPAim);
	// ADC���ݲɼ�ֹͣ
	void OnADCSampleStop(unsigned int uiIPAim);
	afx_msg void OnBnClickedButtonTimecal();
	// δ�յ�β������
	unsigned int m_uiTailRecCount;
	// �ɼ�վ�豸Button�ؼ�ID
	int m_iButtonIDFDU[GraphViewNum];
	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
	int m_iCheckIDInstrumentFDU[GraphViewNum];
	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
	int m_iCheckIDNoiseFDU[GraphViewNum];
	// ADC�����Զ��洢�ļ����ݵ����
	unsigned int m_uiADCFileLength;
	// ʹ��button�ؼ�
	void OnEnableButtons(void);
	// ����Button�ؼ�
	void OnDisableButtons(void);
	// ͼ�λ���ʾADC����Dlg
	CGraphShowDlg m_dlgADCData;
	afx_msg void OnBnClickedButtonFdu1();
	afx_msg void OnBnClickedButtonFdu2();
	afx_msg void OnBnClickedButtonFdu3();
	afx_msg void OnBnClickedButtonFdu4();
	afx_msg void OnBnClickedButtonFdu5();
	afx_msg void OnBnClickedButtonFdu6();
	afx_msg void OnBnClickedButtonFdu7();
	afx_msg void OnBnClickedButtonFdu8();
	afx_msg void OnBnClickedButtonFdu9();
	afx_msg void OnBnClickedButtonFdu10();
	afx_msg void OnBnClickedButtonFdu11();
	afx_msg void OnBnClickedButtonFdu12();
	afx_msg void OnBnClickedButtonFdu13();
	afx_msg void OnBnClickedButtonFdu14();
	afx_msg void OnBnClickedButtonFdu15();
	afx_msg void OnBnClickedButtonFdu16();
	afx_msg void OnBnClickedButtonFdu17();
	afx_msg void OnBnClickedButtonFdu18();
	afx_msg void OnBnClickedButtonFdu19();
	afx_msg void OnBnClickedButtonFdu20();
	afx_msg void OnBnClickedButtonFdu21();
	afx_msg void OnBnClickedButtonFdu22();
	afx_msg void OnBnClickedButtonFdu23();
	afx_msg void OnBnClickedButtonFdu24();
	afx_msg void OnBnClickedButtonFdu25();
	afx_msg void OnBnClickedButtonFdu26();
	afx_msg void OnBnClickedButtonFdu27();
	afx_msg void OnBnClickedButtonFdu28();
	afx_msg void OnBnClickedButtonFdu29();
	afx_msg void OnBnClickedButtonFdu30();
	afx_msg void OnBnClickedButtonFdu31();
	afx_msg void OnBnClickedButtonFdu32();
	afx_msg void OnBnClickedButtonFdu33();
	afx_msg void OnBnClickedButtonFdu34();
	afx_msg void OnBnClickedButtonFdu35();
	afx_msg void OnBnClickedButtonFdu36();
	afx_msg void OnBnClickedButtonFdu37();
	afx_msg void OnBnClickedButtonFdu38();
	afx_msg void OnBnClickedButtonFdu39();
	afx_msg void OnBnClickedButtonFdu40();
	afx_msg void OnBnClickedButtonFdu41();
	afx_msg void OnBnClickedButtonFdu42();
	afx_msg void OnBnClickedButtonFdu43();
	afx_msg void OnBnClickedButtonFdu44();
	afx_msg void OnBnClickedButtonFdu45();
	afx_msg void OnBnClickedButtonFdu46();
	afx_msg void OnBnClickedButtonFdu47();
	afx_msg void OnBnClickedButtonFdu48();
	// ����ͼ�λ���ʾADC����Dlg
	void OnShowADCGraph(unsigned int uiADCGraphNb);
	// ADC��Ư����
	void OnADCZeroDrift(unsigned int uiIPAim);
	// �����ٽ�������
	CCriticalSection m_Sec;
	// �������ݷ��Ͷ˿�
	unsigned int m_uiSendPort;
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};
