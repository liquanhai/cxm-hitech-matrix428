//**************************************************
//		ͨѶ�˿�����
//**************************************************
// ����֡���ʹ����˿�
#define HeartBeatRec					0x7000
// �װ����ն˿�
#define HeadFramePort				0x8000
// ���ڽ���IP��ַ����Ӧ��˿�
#define IPSetPort						0x9100
// β�����ն˿�
#define TailFramePort				0x9000
// ���ڽ�������β��ʱ�̲�ѯ�Ķ˿ں�
#define TailTimeFramePort		0x9200
// ���ڷ�������ʱ�����õĶ˿ں�
#define TimeSetPort					0x9300
// ���ݲ�������Ӧ��֡�˿�
#define ADSetReturnPort			0x8204
// AD���ݲɼ����ն˿�
#define ADRecPort						0x8300
// �ɼ�վ����ʱ�̲�ѯ�˿�
#define CollectSysTimePort		0x8205
// ״̬��ѯ֡Ӧ��˿�
#define GetStatusPort					0x8206
// ��ѯӲ���豸����������ض˿�
#define QueryErrorCodePort		0x8207 
// ADC���ù㲥�˿�
#define ADCSetBroadcastPort	0x66666666

//**************************************************
//		����������
//**************************************************
// ������ӵ��豸��
#define InstrumentMaxCount			49	
// ��ͼ�ؼ�����
#define InstrumentNum					48
// �������ݰ��Ĵ�С
#define ReceiveDataSize				74
// ����������
#define RcvBufNum						8
// ����ת�˿��ж˿ڻ�������С
#define UartToUdpRcvSize			1024
// ADC���ݻ�������С
#define ADCBufSize						655360
// �˿ڼ��ӻ�������С
#define PortMonitoringBufSize		655360
// ����תUDP�˿ڻ�������С
#define UartToUDPBufSize			655360
// UDPͨѶADC�������ջ�������С
#define ADCDataBufSize				655360
// �������ͻ�������С
#define HeartBeatSndBufSize		3
// ���յ��������ݰ���С
#define RcvFrameSize					256
// ���͵��������ݰ���С
#define SndFrameSize						128
// ����֡��������ֵ�趨
#define SndFrameBufSet				0x00

//**************************************************
//		��������
//**************************************************
// �װ�����
#define HeadFrameCount						4
// IP��ַ�������
#define IPAddrResetTimes						3
// β������
#define TailFrameCount							15
// ADC�����ļ��ļ�ͷ����
#define ADCFileHeadRow						3
// ADC����С�����λ��
#define DecimalPlaces							9
// ADC����֡�ط�����
#define ADCFrameRetransmissionNum	1
// �̹߳رյȴ�ʱ��
#define WaitForThreadCloseTime			550
// IP�㲥��ַ
#define IPBroadcastAddr		"255.255.255.255"
// XML�����ļ���
#define XMLFileName			"MatrixTestSoft.xml"

//**************************************************
//		����������
//**************************************************
// ������������
#define SendSetCmd								0x0001
// ���Ͳ�ѯ����
#define SendQueryCmd							0x0002
// ����ADC���������ط�����
#define SendADCRetransmissionCmd	0x0003
//**************************************************
//		֡��ʽ����
//**************************************************
// ֡ͷ����
#define FrameHeadSize	16
// ֡ͷ��һ���ֽ�
#define FrameHead0		0x11
// ֡ͷ�ڶ����ֽ�
#define FrameHead1		0x22
// ֡ͷ�������ֽ�
#define FrameHead2		0x33
// ֡ͷ���ĸ��ֽ�
#define FrameHead3		0x44
// CRCУ��ֵ�ֽ���
#define CRCSize			2
// CRCУ��Ԥ���ֽ���
#define CRCCheckSize	4
//**************************************************
//		ȫ�ֱ�������
//**************************************************
// ����β��ʱ�̲�ѯ֡����
extern unsigned int m_uiSendTailTimeFrameCount;
// ���յ���β��ʱ�̲�ѯ֡����
extern unsigned int m_uiRecTailTimeFrameCount;
// CRC16У��
extern unsigned short get_crc_16(unsigned char* buf, int buf_size);
