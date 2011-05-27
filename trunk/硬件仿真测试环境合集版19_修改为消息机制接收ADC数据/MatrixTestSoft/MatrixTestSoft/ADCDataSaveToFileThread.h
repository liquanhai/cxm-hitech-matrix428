#pragma once
#include "Parameter.h"


// CADCDataSaveToFileThread

class CADCDataSaveToFileThread : public CWinThread
{
	DECLARE_DYNCREATE(CADCDataSaveToFileThread)

public:
	CADCDataSaveToFileThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CADCDataSaveToFileThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();
	// ��ʼ��
	void OnInit(void);
	// ��ʼ
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// �ر�
	void OnClose(void);
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hADCDataSaveToFileThreadClose;
	// �߳̿�ʼ�����¼�
	HANDLE m_hADCDataSaveToFileThreadWork;
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ��ADC���ݱ��浽�ļ�
	void OnProcess(void);
	// ADC���ݱ�����ջ�����
	double m_dADCSaveToFileRecBuf[GraphViewNum][ADCDataSaveToFileBufSize];
	// ADC���ݱ��洦������
	double m_dADCSaveToFileProcBuf[GraphViewNum][ADCDataSaveToFileBufSize];
	// ADC���ݱ���֡���յĸ���
	unsigned int m_uiADCFrameSaveToFileRecNum[GraphViewNum];
	// ADC���ݱ���֡����ĸ���
	unsigned int m_uiADCFrameSaveToFileProcNum[GraphViewNum];
	// ADC���ݱ���ʣ��֡����
	unsigned int m_uiADCFrameRemain[GraphViewNum];
	// ADC��ɴ洢��֡��
	unsigned int m_uiADCFrameSaved[GraphViewNum];
	// ѡ����������
	int* m_pSelectObject;
	// ѡ�������������������
	int* m_pSelectObjectNoise;
	// �����ļ����ļ�ָ��
	FILE * m_pFileSave;
	// �ļ��򿪱�־λ
	BOOL m_bOpenADCSaveFile;
	// �������ADC���ݸ���
	unsigned int m_uiADCDataToSaveNum;
	// ADC���ݱ����ļ��ߴ�
	unsigned int m_uiADCFileLength;
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// ����ADC�����ļ�����
	unsigned int m_uiADCSaveFileNum;
	// ѡ�е�������������
	char* m_cSelectObjectName[GraphViewNum];
	// �ж�ADC����ֹͣ��־λ�����ڱ���ʣ���ADC��������
	BOOL m_bStopSample;
	// ����һ�δ���ʱ�ļ��������еõ�������
	void OnSaveADCDataFramesToFile(void);
	// ��������ADC���������ļ�
	void OnOpenADCSaveFile(void);
	// �ر�ADC���������ļ�
	void OnCloseADCSaveFile(void);

	// �������С�Ĵ��������
	unsigned int OnCalMinProcNum(void);
	// ��������Ĵ��������
	unsigned int OnCalMaxNeedToSaveDataNum(void);
	// ��ADC���ݱ��浽�ļ���
	void OnSaveADCToFile(unsigned int uiADCSaveDataNum);
	// ��ADC���ݱ��浽�ļ���
	void OnSaveADCToFile(unsigned int uiADCSaveDataNum, unsigned int uiADCSaveDataPointNb);
	// �������������
	void OnClearProcData(unsigned int uiOutDataedProcNum);
};


