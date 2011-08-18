#pragma once
#include "Parameter.h"
#include <vector>
using namespace std;
// CSocketADCDataRec ����Ŀ��

class CSocketADCDataRec : public CSocket
{
public:
	CSocketADCDataRec();
	virtual ~CSocketADCDataRec();
	virtual void OnReceive(int nErrorCode);
private:
	// ����ADC����֡���ջ�����
	unsigned char m_oADCRecFrameBuf[ADCRecFrameBufSize];
public:
	// ����ָ��
	CWnd* m_pwnd;
	// ���յ���֡��
	unsigned int* m_uipRecFrameNum;
	// ��X������ο�����������
	unsigned int m_uiDrawPointXNb;
	// ��¼X���������Ϣָ��
	vector <double>	m_DrawPoint_X;
	// ����ADC���ݲɼ��Ĳɼ�վ�豸��
	unsigned int m_uiInstrumentADCNum;
private:
	// ����֡����
	void ProcFrameOne(void);
	// ADC���ݻ�ͼ׼��
	void OnPrepareToShow(unsigned short usInstrumentNum);
public:
	// �õ���ǰADC���ݽ���֡��С֡�����������������
	unsigned int GetRecFrameNumMin(void);
	// �õ���ǰADC���ݽ���֡���֡�����������������
	unsigned int GetRecFrameNumMax(void);
};


