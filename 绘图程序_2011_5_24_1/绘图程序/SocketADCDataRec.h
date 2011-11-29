#pragma once
#include "Parameter.h"
#include "ParameterSet.h"
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
	// ����ADC����ͼ����ʾ����֡������
	unsigned char m_oADCGraphSetFrameBuf[ADCSendFrameBufSize];
	// ���յ�ADC������Ϣ֡��־λ
	BOOL m_bRecADCSetInfoFrame;
// 	// ��X������ο�����������
// 	unsigned int m_uiDrawPointXNb;
public:
	// �豸��ǵ��������ָ��
	unsigned int* m_uiInstrumentNb;
	// ���յ���֡��ż�¼
	vector<unsigned int>* m_uipRecFrameNb;
	// ����ADC���ݲɼ��Ĳɼ�վ�豸��
	unsigned int m_uiInstrumentADCNum;
	// ������
	unsigned int m_uiSamplingRate;
	// �������ý���
	CParameterSet* m_pParameterSet;
private:
	// ����֡����
	void ProcFrameOne(void);
	// ADC���ݻ�ͼ׼��
	void OnPrepareToShow(unsigned short usInstrumentNum);
public:
	// �õ���ǰADC���ݽ���֡��ʼ����е����ֵ��������
	unsigned int GetRecFrameBeginMaxNb(void);
	// �õ���ǰADC���ݽ���֡���һ������е���Сֵ��������
	unsigned int GetRecFrameEndMinNb(void);
	// �õ�Ҫ�������������������
	unsigned int GetRecFrameBeginToEndNum(unsigned int uiInstrumentNb, unsigned int uiRecFrameEndMinNb);
	// ���Ͳ���������������
	void OnMakeAndSendSetFrame(unsigned short usSetOperation);
};


