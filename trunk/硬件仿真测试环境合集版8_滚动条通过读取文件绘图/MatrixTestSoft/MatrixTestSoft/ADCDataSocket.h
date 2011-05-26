#pragma once
#include <vector>
#include "OScopeCtrl.h"
#include "Parameter.h"
#include <afxmt.h>
using namespace std;
// CADCDataSocket ����Ŀ��

class CADCDataSocket : public CSocket
{
public:
	CADCDataSocket();
	virtual ~CADCDataSocket();
public:
	// ADC�������ݻ�����
	byte ADCData[256];
	// ���ղ�������
	void ReceiveSampleData(byte* pSampleData);
	// ѡ����������
	int* m_pSelectObject;
	// ѡ�������������������
	int* m_pSelectObjectNoise;
	// �ɼ���������
//	vector <double>* m_pSampleData[GraphViewNum];
	// ͼ��ģ��ָ��
	COScopeCtrl* m_pOScopeCtrl[GraphViewNum];
	// �����ٽ�������
	CCriticalSection m_Sec;
	virtual void OnReceive(int nErrorCode);
	// ��¼ָ��ƫ����
	unsigned short m_usDataPointMove[GraphViewNum][10000];
	// ��¼ǰһ�����յ���ADC���ݵ�ָ��ƫ����                  
	unsigned short m_usDataPointPrevious[GraphViewNum];
	// ��¼Ӧ����ADC���ݰ�����
	unsigned int m_uiADCDataFrameCount[GraphViewNum];
// 	// ����ָ��
// 	CWnd* m_pwnd;
	// �ж�ADC������ʼ��־λ�����ڶ���TB֮ǰ����Ч����
	BOOL m_bStartSample;
	// ����ADC�����ط�֡
	void MakeADCDataRetransmissionFrame(unsigned short usDataPointNb, unsigned int uiIPAim);
	// ADC�����ط�֡
	unsigned char m_ucADCRetransmission[128];
	// ԴIP��ַ
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// ��Ҫ�ط���ADC������Ϣ�ṹ
	typedef struct m_structADC
	{
		unsigned int uiIPAim;			// �ط�֡IP��ַ
		unsigned short usDataPointNb;	// �ط�֡��ָ��ƫ����
		unsigned int uiDataCount;		// �ط�֡����Ӧ��֡λ�ã�������
		BOOL operator == (const m_structADC&   tdl)const
		{ 

			if(uiIPAim != tdl.uiIPAim) 
				return   FALSE; 
			if(usDataPointNb != tdl.usDataPointNb) 
				return   FALSE; 
			return   TRUE; 
		} 
	};
	// ��Ҫ�ط���ADC��������
	CList <m_structADC, m_structADC&> m_listADC;
	// ��¼��ɻ�ͼ��ADC���ݸ���
	unsigned int m_uiADCRecCompleteCount[GraphViewNum];
	// ADC������Ҫ���·���֡��Ӧ����С����
	unsigned int OnADCRetransimissionMinNb(void);
	// ��ADC�����ط����ȱ���������������
	vector <double> m_dSampleTemp[GraphViewNum];
	// ���Զ�֡���
	unsigned int m_uiTestADCLost;


	// ADC���ݱ�����ļ������ݻ�����
	vector <double> m_dADCSave[GraphViewNum];
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
 	// ��������ADC���������ļ�
 	void OnOpenADCSaveFile(void);
 	// �ر�ADC���������ļ�
 	void OnCloseADCSaveFile(void);
	// ����ADC�����ļ�����
	unsigned int m_uiADCSaveFileNum;
	// �����ļ����ļ�ָ��
	FILE * m_pFileSave;
	// ��ADC���ݱ��浽�ļ���
	void OnSaveADCToFile(void);
	// �ļ��򿪱�־λ
	BOOL m_bOpenADCSaveFile;
	// ѡ�е�������������
	char* m_cSelectObjectName[GraphViewId];
	// ��ѡ��������ADC���ݸ�������Сֵ
	unsigned int OnADCRecDataMinNum(void);
	// �������ADC���ݸ���
	unsigned int m_uiADCDataToSaveNum;
	// �رղ����󱣴�ʣ������
	void OnSaveRemainADCData(unsigned int uiADCDataNeedToSave);
	// ADC���ݱ����ļ��ߴ�
	unsigned int m_uiADCFileLength;
};
