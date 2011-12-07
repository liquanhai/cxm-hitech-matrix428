#pragma once
//#include "Parameter.h"
//#include "FDUADSet.h"
//#include "..\common\OperaStruct.h"
//#include "..\common\SocketParam.h"
// ���� FDU �������
#define  FDU_MAXINUM	   256
// �������ݰ��Ĵ�С
#define ADDataSize			3
//��������
#define  SamplingRate	   1000
// ����ÿ�����ݲ���֡�Ĳ��������ֽ���
#define  SAMPFRM_DATALEN   216
//���֡��
#define  MaxrevFramePoint	   32*SamplingRate/1000
//ÿ֡�ɼ�����
#define ReceiveDataPoint	72	
#define  MaxrevFrameSize	   MaxrevFramePoint*ReceiveDataPoint*ADDataSize		//64*72*3=13824
//�ɼ����ջ�����
#define  RecvBuf	MaxrevFrameSize

class CADCDataSaveToFile
{
public:
	CADCDataSaveToFile(void);
	~CADCDataSaveToFile(void);
protected:
	// �ļ��򿪱�־λ
	BOOL m_bOpenADCSaveFile;
public:
	// �����ļ����ļ�ָ��
	//FILE * m_pFileSave;
	CFile m_pFileSave;
	// ����ADC�����ļ�����
	unsigned int m_uiADCSaveFileNum;
	// ADC���ݱ����ļ��ߴ�
	unsigned int m_uiADCFileLength;
	// �������ݵ��ļ��Ĵ洢·��
	//CString m_csSaveFilePath;
	// �������ADC���ݸ���
	unsigned int m_uiADCDataToSaveNum;
	// �ļ����
	unsigned int m_uiSaveNum;
	// �����ٽ���ȫ�ֱ���
	CCriticalSection m_Sec;
	CArchive *arP;
	int iline;
	unsigned char m_RevBuf[FDU_MAXINUM*RecvBuf];

public:
	// ��ADC���ݱ��浽�ļ���
	//void OnSaveADCToFile(double(* dpADCDataBuf)[ADCDataTempDataSize], unsigned int* uiADCDataNum,
	//	unsigned int uiADCDataToSaveNum, bool bFinish);
	//void OnSaveADCToFile(unsigned char  *m_RevBuf, int (*upADCDataNum)[MaxrevFfameSize+ReceiveDataPoint],int *Revidx,int SpreadCount, bool bFinish,int type);
	void OnSaveADCToFile(unsigned char  *m_RevBuf, int *upADCDataNum,int *Revidx,int SpreadCount, bool bFinish,int type,int lineCount);
	// �ر�ADC���������ļ�
	void OnCloseADCSaveFile(void);
	// ��������ADC���������ļ�
	void OnOpenADCSaveFile(int);
protected:
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};
