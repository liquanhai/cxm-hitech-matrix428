#pragma once

#include "FrameTestSet.h"
#include "RunTimeDataList.h"
#include "Matrixline.h"
#include "TestElementList.h"
#include "Parameter.h"
/**
*@brief ������������֡��������ӿ���
*/
class CSocketTestSetFrame : public CSocket
{
public:
	CSocketTestSetFrame();
	virtual ~CSocketTestSetFrame();

public: // ����
	/** LCI�豸IP��ַ*/
	CString m_strIPLCI;
	/**  LCI�豸IP��ַ�˿ں�*/
	UINT m_uiPortLCI;

	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	UINT m_uiIPForInstrument;
	/** �������ö˿ں�*/
	UINT m_uiPortForTestSet;

	/** ֡�ֽ���*/
	int m_iFrameSize;
	/** ֡���ݶ���*/
	CFrameTestSet m_oFrameTestSet;
	/** ������־*/
	CRunTimeDataList *m_oRunTimeDataList;
	/** ������ ��λ΢��*/
	unsigned int m_uiSamplingRate;
	/** ��ͼ������ */
	unsigned int m_uiSamplingView;
	/** ��ͼ״̬ 1��ʼ 0ֹͣ */
	int Viewtype;
	unsigned char * ofccheck;
	char ReceiveBuf[FrameLength*16];
	CString strrecv;
	int adsetcount;
	int adgetcount;
	int gettestcount;
	int getTBcount;
	int checkrecv[ADcheckrecv];

	/** ���Ե�Ԫ����*/
	CTestElementList* m_pTestElementList;
	// ADC�����������
	unsigned int m_uiADCSetOperationNb;
	// �ɼ�վ����ʱ��
	unsigned int m_uiTnow;
	/** �μӲ���IP��ַ����*/
	unsigned int m_uiIPCount;
	// UDP���ջ�����
	unsigned char m_ucUdpBuf[ADCSetReturnBufSize];
	// UDP����ָ֡��ƫ����
	unsigned int m_uiUdpCount;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInstrument, UINT uiIPForInstrument, UINT uiPortForTestSet, CString strIPLCI, UINT uiPortLCI);
	// ���÷��ͻ��������Է��͵�֡����
	BOOL SetBufferSize(int iFrameCount);
	// ���ɲ�������֡
	void MakeFrameDataForTestSet();
	// ���Ͳ�������֡
	void SendTestSetFrame();
	// ����AD���ն˿�
	int MakeFrameADListen();
	// ���ɲ��Կ�ʼ֡
	void MakeFrameDataForTestStart();
	// ���ɲ���ֹͣ֡
	void MakeFrameDataForTestEnd(unsigned int uiInstrumentIP);
	// ���Ͳ���ֹͣ֡
	void SendTestEndFrame();
	//����AD����
	void MakeFrameADSet();
	//����֡ͷ
	int MakeFrameHead();
	//����֡ͷ,�ǹ㲥
	int MakeFrameHead1();
	void ParseFrameHead(int iCount,char *ReceiveBuf);
	//����AD�ɼ���ʼ
	void MakeFrameADTestStart();
	//����AD��Ư�ɼ���ʼ
	void MakeFrameADClickTestStart1();
	void MakeFrameADIPTestStart();
	void MakeFrameADClickTestStart2();
	//���û�ͼ��ʼ֡
	void ViewSet(int itype);
	// ����AD����ֹͣ
	void MakeFrameADTestSTOP(unsigned int uiInstrumentIP);
	// ���ɼ�����
	void ReloadTestDataFrame(unsigned int UiIP,int i_idx);
	//����AD��Ư
	void MakeFrameADClick0();
	bool ParseCommandWord(byte  * pBuf);
	bool AppCommandWord(unsigned char * pBuf);
	void resetcheckrecv();
	// ADC��������
	void OnADCSet(void);
	// ADC���ݲɼ�ֹͣ
	void OnADCSampleStop(void);
	// ADC��ƯУ��
	void OnADCZeroDrift(void);
	// ADC����TBʱ�̿�ʼ�ɼ�
	void OnADCPrepareToSample(void);
	// ����ADC��������֡
	void OnSendADCSetCmd(void);
	// ����ADC����Ӧ��֡
	void OnProcADCSetReturn(unsigned int uiIP);
	// ����Ƿ��յ����вɼ�վ��ADC����Ӧ��
	BOOL OnCheckADCSetReturn(void);
	// ������ƯУ����ѯӦ��
	void OnProcADCZeroDriftReturn(unsigned int uiIPAim);
	// ����ADC��������Ӧ��֡
	void OnReceiveADCSetReturn(int itype);
	// ���ݴ���
	void OnProcess(int iCount);
	// ����һ֡ADC��������Ӧ��֡
	void	OnProcessOneADCSetReturn(void);
	// ����ADC�������ò������
	void OnResetADCOperationNb(void);
	// ���ADC�������ý��ջ�����
	void OnClearADCSetReturnBuf(void);
	// ���ADC��������Ӧ��֡�Ƿ������ȫ
	void OnCheckADCSetReturnComplete(void);
	// ADC�������ò�������
	void OnADCSetOperation(void);
	// ADC����TBʱ��
	void OnADCSetTBTime(unsigned int tnow);
};


