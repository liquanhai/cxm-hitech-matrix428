// ����֡���ʹ����˿�
#define HeartBeatRec		0x7000
// �װ����ն˿�
#define HeadFramePort		0x8000
// ���ڽ���IP��ַ����Ӧ��˿�
#define IPSetPort			0x9100
// β�����ն˿�
#define TailFramePort		0x9000
// ���ڽ�������β��ʱ�̲�ѯ�Ķ˿ں�
#define TailTimeFramePort	0x9200
// ���ڷ�������ʱ�����õĶ˿ں�
#define TimeSetPort			0x9300
// ���ݲ�������Ӧ��֡�˿�
#define ADSetReturnPort		0x8204
// AD���ݲɼ����ն˿�
#define ADRecPort			0x8300
// �ɼ�վ����ʱ�̲�ѯ�˿�
#define CollectSysTimePort	0x8205
// ״̬��ѯ֡Ӧ��˿�
#define	GetStatusPort		0x8206
// ADC���ù㲥�˿�
#define ADCSetBroadcastPort	0x6666
// ADC���ݲ�ѯ����Socket���ն˿�
#define ADCFrameRetransmissionPort	0x8207
// IP�㲥��ַ
#define IPBroadcastAddr	"255.255.255.255"
// ������ӵ��豸��
#define InstrumentMaxCount	4	
// �װ�����
#define HeadFrameCount		5
// β������
#define TailFrameCount		5
// ��ͼ�ؼ�����
#define GraphViewNum	3
// �������ݰ��Ĵ�С
#define ReceiveDataSize		74
// ADC�����ļ��ļ�ͷ����
#define ADCFileHeadRow	3
// ADC����С�����λ��
#define DecimalPlaces	9
// XML�����ļ���
#define XMLFileName		"MatrixTestSoft.xml"
// ADC����֡�ط�����
#define ADCFrameRetransmissionNum	1
// ADC���ݶ˿ڽ��ջ�������С
#define ADCBufSize	655360
// ADC���ջ���������
#define ADCRecBufNum	8
// ��¼ADC��Ϣ���ݵĸ���
#define ADCFrameInfoSize	1
// ADC���ݱ���֡����
#define ADCFrameNumNeedToSave	10
// ADC���ݴ���������С
#define ADCDataProcBufSize	((ReceiveDataSize + ADCFrameInfoSize) * ADCFrameNumNeedToSave)
// ADC����������ʱ�ļ��Ļ���������
#define ADCDataNeedToSaveBufNum	2
// ADC����������ʱ�ļ��Ļ�������С
#define ADCDataNeedToSaveBufSize	(ReceiveDataSize * ADCFrameNumNeedToSave * ADCDataNeedToSaveBufNum)
// ADC�����ļ��洢����������
#define ADCDataSaveToFileBufNum	10	
// ADC�����ļ��洢��������С
#define ADCDataSaveToFileBufSize	(ReceiveDataSize * ADCFrameNumNeedToSave * ADCDataSaveToFileBufNum)	
// �˿ڼ��Ӷ˿ڻ�������С
#define PortMonitoringBufSize	655360
// ����תUDP�˿ڻ�������С
#define UartToUDPBufSize	655360
// ADC�����ط��˿ڻ�������С
#define ADCRetransmissionBufSize	655360
// UDPͨѶADC�������ջ�������С
#define ADCDataBufSize			4096
// �������ͻ�������С
#define HeartBeatSndBufSize	3
// ���յ��������ݰ���С
#define RcvFrameSize	256
// ���͵��������ݰ���С
#define SndFrameSize	128
// ������������
#define SendSetCmd	0x0001
// ���Ͳ�ѯ����
#define SendQueryCmd	0x0002
// ����ADC���������ط�����
#define SendADCRetransmissionCmd	0x03
// CRCУ��ֵ�ֽ���
#define CRCSize			2
// CRCУ��Ԥ���ֽ���
#define CRCCheckSize	4
// ֡ͷ����
#define FrameHeadSize	16

// ����β��ʱ�̲�ѯ֡����
extern unsigned int m_uiSendTailTimeFrameCount;
// ���յ���β��ʱ�̲�ѯ֡����
extern unsigned int m_uiRecTailTimeFrameCount;
// CRC16У��
extern unsigned short get_crc_16(unsigned char* buf, int buf_size);
// extern HANDLE	hCom;				// ׼���򿪵Ĵ��ڵľ��