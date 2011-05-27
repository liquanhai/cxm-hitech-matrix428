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
#define InstrumentMaxCount	10	
// �װ�����
#define HeadFrameCount		5
// β������
#define TailFrameCount		15
// ��ͼ�ؼ�����
#define GraphViewNum	9
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
// ADC���ջ���������
#define ADCRecBufNum	8
// ��¼ADC��Ϣ���ݵĸ���
#define ADCFrameInfoSize	1
// ADC���ݱ���֡����
#define ADCFrameNumNeedToSave	10
// ADC���ݴ���������С
#define ADCDataProcBufSize	((ReceiveDataSize + ADCFrameInfoSize) * ADCFrameNumNeedToSave)
// ADC����������ʱ�ļ��Ļ���������
#define ADCDataNeedToSaveBufNum	12
// ADC����������ʱ�ļ��Ļ�������С
#define ADCDataNeedToSaveBufSize	(ReceiveDataSize * ADCFrameNumNeedToSave * ADCDataNeedToSaveBufNum)
// ADC�����ļ��洢����������
#define ADCDataSaveToFileBufNum	60	
// ADC�����ļ��洢��������С
#define ADCDataSaveToFileBufSize	(ReceiveDataSize * ADCFrameNumNeedToSave * ADCDataSaveToFileBufNum)	
// �˿ڼ��Ӷ˿ڻ�������С��48��վ4K������ÿ��Լ��650K���壬��Ϊ1000K
#define PortMonitoringBufSize	1024000
// ����תUDP�˿ڻ�������С�����ڲ�����Ϊ115200����ÿ��14400Byte
#define UartToUDPBufSize	14400
// ADC�����ط��˿ڻ�������С��48��վ��ÿ��վÿ�����ط�20֡
#define ADCRetransmissionBufSize	245760
// ADC���ݶ˿ڽ��ջ�������С��48��վ4K������ÿ��Լ��650K���壬��Ϊ1000K
#define ADCBufSize	1024000
// UDPͨѶADC�������ջ�������С,���ǵ�������������軺����Ϊ16֡��С
#define ADCDataBufSize			4096
// ʱͳ����
#define TimeDelayTimes	30 
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