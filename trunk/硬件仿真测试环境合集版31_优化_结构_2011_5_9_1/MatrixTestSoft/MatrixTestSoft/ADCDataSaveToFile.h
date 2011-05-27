#pragma once
#include "Parameter.h"
class CADCDataSaveToFile
{
public:
	CADCDataSaveToFile(void);
	~CADCDataSaveToFile(void);
protected:
	// �ļ��򿪱�־λ
	BOOL m_bOpenADCSaveFile;
	// �����ļ����ļ�ָ��
	FILE * m_pFileSave;
	// �������ADC���ݸ���
	unsigned int m_uiADCDataToSaveNum;
public:
	// ����ADC�����ļ�����
	unsigned int m_uiADCSaveFileNum;
	// ADC���ݱ����ļ��ߴ�
	unsigned int m_uiADCFileLength;
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
public:
	// ��ADC���ݱ��浽�ļ���
	int OnSaveADCToFile(double(* dpADCDataBuf)[ADCDataTempDataSize], unsigned int* uiADCDataNum,
		int* pSelectObject, int* pSelectObjectNoise, bool bFinish);
protected:
	// ��������ADC���������ļ�
	void OnOpenADCSaveFile(void);
	// ��ѡ��������ADC���ݸ�������Сֵ
	unsigned int OnADCRecDataMinNum(unsigned int* uiADCDataNum, int* pSelectObject, int* pSelectObjectNoise);
	// �ر�ADC���������ļ�
	void OnCloseADCSaveFile(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ��ѡ��������ADC���ݸ��������ֵ
	unsigned int OnADCRecDataMaxNum(unsigned int* upADCDataNum, int* pSelectObject, int* pSelectObjectNoise);
};
