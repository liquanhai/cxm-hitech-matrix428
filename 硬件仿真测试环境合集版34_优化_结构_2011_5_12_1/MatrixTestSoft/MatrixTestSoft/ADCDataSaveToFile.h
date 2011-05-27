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
public:
	// ����ADC�����ļ�����
	unsigned int m_uiADCSaveFileNum;
	// ADC���ݱ����ļ��ߴ�
	unsigned int m_uiADCFileLength;
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// �������ADC���ݸ���
	unsigned int m_uiADCDataToSaveNum;
public:
	// ��ADC���ݱ��浽�ļ���
	void OnSaveADCToFile(double(* dpADCDataBuf)[ADCDataTempDataSize], unsigned int* uiADCDataNum,
		unsigned int uiADCDataToSaveNum, bool bFinish);
	// �ر�ADC���������ļ�
	void OnCloseADCSaveFile(void);
protected:
	// ��������ADC���������ļ�
	void OnOpenADCSaveFile(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};
