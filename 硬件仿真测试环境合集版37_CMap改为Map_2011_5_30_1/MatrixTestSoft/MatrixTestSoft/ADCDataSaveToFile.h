#pragma once
#include "Parameter.h"
#include "InstrumentList.h"
class CADCDataSaveToFile
{
public:
	CADCDataSaveToFile(void);
	~CADCDataSaveToFile(void);
protected:
	// �ļ��򿪱�־λ
	BOOL m_bOpenADCSaveFile;
	// �����ļ����ļ�ָ��
//	FILE * m_pFileSave;
	CFile m_FileSave;
	// �����ļ�
	CArchive* m_arFileSave;
public:
	// ����ADC�����ļ�����
	unsigned int m_uiADCSaveFileNum;
	// ADC���ݱ����ļ��ߴ�
	unsigned int m_uiADCFileLength;
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// �������ADC���ݸ���
	unsigned int m_uiADCDataToSaveNum;
	// ����������豸����
	unsigned int m_uiSampleInstrumentNum;
	// �豸��ָ��
	CInstrumentList* m_pInstrumentList;
public:
	// ��ADC���ݱ��浽�ļ���
	void OnSaveADCToFile(int(* iADCDataBuf)[ADCDataTempDataSize], unsigned int* uiADCDataNum,
		unsigned int uiADCDataToSaveNum, bool bFinish);
	// �ر�ADC���������ļ�
	void OnCloseADCSaveFile(void);
	// ��������ADC���������ļ�
	void OnOpenADCSaveFile(void);
protected:
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};
