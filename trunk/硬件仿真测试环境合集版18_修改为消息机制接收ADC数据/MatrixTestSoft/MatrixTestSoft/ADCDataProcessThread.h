#pragma once
#include "Parameter.h"
#include <afxmt.h>
#include "OScopeCtrl.h"
#include "ADCDataSaveToFileThread.h"

// CADCDataProcessThread

class CADCDataProcessThread : public CWinThread
{
	DECLARE_DYNCREATE(CADCDataProcessThread)

public:
	CADCDataProcessThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CADCDataProcessThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// ��ʼ��
	void OnInit(void);
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// �ر�
	void OnClose(void);
	virtual int Run();
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hADCDataProcessThreadClose;
	// �̹߳����¼�
	HANDLE m_hADCDataProcessThreadWork;
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ��¼ǰһ�����յ���ADC���ݵ�ָ��ƫ����                  
	unsigned short m_usDataPointPrevious[GraphViewNum];
	// ��¼ÿ�δ���ʵ�ʽ���ADC���ݰ�����
	unsigned int m_uiADCDataFrameRecCount[GraphViewNum];
	// ��¼ÿ����Ҫ�����ADC���ݰ�����
	unsigned int m_uiADCDataFrameProcCount[GraphViewNum];
	// ��¼Ӧ�ղɼ�����ADC����֡�ĸ���
	unsigned int m_uiADCDataFrameProcNum[GraphViewNum];
	// ADC���ݽ��ջ��壬1��ָ��ƫ����+74������
	double m_dADCDataRecBuf[GraphViewNum][ADCDataProcBufSize];
	// ADC���ݴ�������
	double m_dADCDataProcBuf[GraphViewNum][ADCDataProcBufSize];
	// ADC���������ļ��洢����ʱ������
	double m_dADCDataNeedToSaveBuf[GraphViewNum][ADCDataNeedToSaveBufSize];
	// ����ʱ���ݿ������ļ��洢�������Ĵ���
	unsigned int m_uiCopySaveBufNum[GraphViewNum];
	// ��Ҫ�ط���ADC������Ϣ�ṹ
	typedef struct m_structADC
	{
		unsigned int uiDataCount;		// �ط�֡����Ӧ��֡λ�ã�������
		unsigned short uiRetransmissionNum;	// �ط�����
	};
	// ��Ҫ�ط���ADC������
	CMap<unsigned int, unsigned int, m_structADC, m_structADC&> m_oADCLostMap[GraphViewNum];
	// �����ٽ�������
	CCriticalSection m_Sec;
	// ADC�����ط�֡
	unsigned char m_ucADCRetransmission[SndFrameSize];
	// ԴIP��ַ
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// ADC���ݽ���Socket
	CSocket m_ADCRetransmissionSocket;
	// ADC���ݴ洢�߳�ָ��
	CADCDataSaveToFileThread* m_pADCDataSaveToFileThread;
	// ADC���ݴ���
	void OnProcess(void);
	// ������֡�Ƿ�Ϊ�ط�֡
	BOOL OnCheckFrameIsRetransmission(unsigned int uiInstrumentNb, unsigned int uiADCDataFrameProcNb);
	// ����ADC����֡��д�ļ���ʱ������
	void OnSaveADCFrameToFileBuf(unsigned int uiInstrumentNb, BOOL bADCRetransimission, unsigned int uiADCDataFrameProcNb);
	// ����һ֡ADC����
	void OnProcessOneFrame(unsigned int uiInstrumentNb, unsigned int uiADCDataFrameProcNb);
	// ��¼�ط�֡��λ��
	unsigned int m_uiADCRetransmissionNb;
	// ͼ��ģ��ָ��
	COScopeCtrl* m_pOScopeCtrl;
	// ADCͼ����ʾ�豸IP
	unsigned int m_uiADCGraphIP;
	// ѡ�������������������
	int* m_pSelectObjectNoise;
	// ���������������������
	void OnClearOutdatedFromMap(unsigned int uiInstrumentNb);
	// ���������з���ADC���ݲ�ѯ֡
	void OnSendADCFrameFromMap(void);
	// ����ADC�����ط�֡
	void MakeADCDataRetransmissionFrame(unsigned short usDataPointNb, unsigned int uiIPAim);
	// ����ʱ�������ļ��������ļ��洢������
	void OnCopyToFileBuf(unsigned int uiInstrumentNb);
};


