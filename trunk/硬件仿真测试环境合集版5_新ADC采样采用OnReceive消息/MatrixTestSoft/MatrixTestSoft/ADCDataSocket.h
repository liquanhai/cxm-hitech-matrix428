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
	vector <double>* m_pSampleData[GraphViewNum];
	// ͼ��ģ��ָ��
	COScopeCtrl* m_pOScopeCtrl[GraphViewNum];
	// �����ٽ�������
	CCriticalSection m_Sec;
	virtual void OnReceive(int nErrorCode);
	// ��¼ָ��ƫ����
	unsigned int m_uiDataPointMove[GraphViewNum][10000];
	// ��¼�׸�ָ��ƫ����
	unsigned int m_uiDataPointLast[GraphViewNum];
	// �������ݰ�����
	unsigned int m_uiDataFrameNum[GraphViewNum];
	// ���ڴ洢ADC����
	vector <double> m_dADCSaveData[GraphViewNum];
	// ����ָ��
//	CWnd* m_pwnd;
};
