#include <string>
using namespace std;
//__________________ͨѶ�˿�����__________________
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
// ��ѯӲ���豸�����������ض˿�
#define QueryErrorCodePort		0x8207 
// ADC���ù㲥�˿�
#define ADCSetBroadcastPort	0x66666666
// �㲥�˿�
#define BroadCastPort				0xffffffff

//___________________����������____________________
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
#define HeartBeatSndBufSize		1280
// ���յ��������ݰ���С
#define RcvFrameSize					256
// ���͵��������ݰ���С
#define SndFrameSize						128
// ����֡��������ֵ�趨
#define SndFrameBufInit				0x00
// ADC����������Ԥ��Ļ�����֡��
#define ADCDataTempFrameNum	40
// ADC����������Ԥ��Ļ�������С
#define ADCDataTempDataSize	(ADCDataTempFrameNum * ReceiveDataSize)
//__________________���ڶ˿ڶ���__________________
#define COMNum	10

//_________________���ڲ����ʶ���_________________
#define BAUD0		300
#define BAUD1		600
#define BAUD2		1200
#define BAUD3		2400
#define BAUD4		4800
#define BAUD5		9600
#define BAUD6		19200
#define BAUD7		38400
#define BAUD8		43000
#define BAUD9		56000
#define BAUD10	57600
#define BAUD11	115200

//_____________________��������____________________
// �װ�����
#define HeadFrameCount						4
// IP��ַ�������
#define IPAddrResetTimes						3
// β������
#define TailFrameCount							15
// ��������-�ɼ�վ
#define InstrumentTypeFDU					3
// ��������-����վ
#define InstrumentTypeLAUX				1
// ADC�����ļ��ļ�ͷ����
#define ADCFileHeadRow						3
// ADC����С�����λ��
#define DecimalPlaces							9
// ADC����֡�ط�����
#define ADCFrameRetransmissionNum	1
// �̹߳رյȴ�ʱ��
#define WaitForThreadCloseTime			550
// IP��ַ���õ���ʼ��ַ
#define IPSetAddrStart							71
// IP��ַ���õļ��
#define IPSetAddrInterval						10
// ADC����ָ֡�뷭ת����
#define ADCFramePointLength				2048
// ����վ�Ϸ�·������
#define RoutIPTop									0x55555555
// ����վ�·�·������
#define RoutIPDown								0x66666666
// ����վ��·������
#define RoutIPLeft									0x77777777
// ����վ�ҷ�·������
#define RoutIPRight								0x88888888
// ��������������ఴť���ƶ���
#define ScrollBarLineLeftMove				5
// �������������Ҳఴť���ƶ���
#define ScrollBarLineRightMove			5
// �������������ҳ���ƶ���
#define ScrollBarPageLeftMove			30
// ������������ҷ�ҳ���ƶ���
#define ScrollBarPageRightMove			30
// ADC��ƯУ����Ҫд�Ĵ�����λ��
#define ADCZeroDriftWritebytesNum	6
// ��ѯ�豸�����������
#define QueryErrorCodeNum					4
// ADC����������ʱ
#define ADCOperationSleepTime			100
// �˿ڼ��ӷ����߳�Sleepʱ��
#define PortMonitoringSendThreadSleepTime	1
// �˿ڼ��ӽ����߳�Sleepʱ��
#define PortMonitoringRecThreadSleepTime	1
// �����߳�Sleepʱ��
#define HeartBeatThreadSleepTime					500
// ADC���ݽ����߳�Sleepʱ��
#define ADCDataRecThreadSleepTime				1
// TB������ʱ��λ
#define TBSleepTimeHigh									0x5000
// TB������ʱ��λ
#define TBSleepTimeLow									0xfa
// ADC������ʾ����ÿ����ʾ�ĸ���
#define ADCDataShowPerLineNum					6
// IP�㲥��ַ
#define IPBroadcastAddr		_T("255.255.255.255")
// Ĭ�ϵı���IP��ַ
#define IPHostAddr				_T("127.0.0.1")
// XML�����ļ���
#define XMLFileName			_T("MatrixTestSoft.xml")

//____________________����������__________________
// ������������
#define SendSetCmd								0x0001
// ���Ͳ�ѯ����
#define SendQueryCmd							0x0002
// ����ADC���������ط�����
#define SendADCRetransmissionCmd	0x0003
// ����
#define CmdSn										0x01
// �װ�ʱ��
#define CmdHeadFrameTime					0x02
// ����IP��ַ
#define CmdLocalIPAddr						0x03
// ����ϵͳʱ��
#define CmdLocalSysTime						0x04
// ����ʱ��������λ
#define CmdLocalFixedTimeHigh			0x05
// ����ʱ��������λ
#define CmdLocalFixedTimeLow			0x06
// �Զ����ݷ��ص�ַ
#define CmdADCDataReturnAddr			0x07
// �Զ����ݷ��ض˿ں�����
#define CmdADCDataReturnPort			0x08
// �˿ڵ������޺�����
#define CmdADCDataReturnPortLimit	0x09
// ��������ȴ��˿ں�����
#define CmdSetBroadCastPort				0x0a
// ϵͳӲ��״̬����
#define CmdFDUErrorCode					0x0b
// TBʱ�̸�λ
#define CmdTBHigh								0x0c
// TBʱ�̵�λ
#define CmdTbLow								0x0d
// β������\����ʱ�̵�λ
#define CmdTailRecSndTimeLow			0x16
// �㲥����ȴ��˿�ƥ��
#define CmdBroadCastPortSet				0x17
// ����ADC��������������
#define CmdADCSet								0x18
// ����ʱ��
#define CmdNetTime								0x19
// ����վ����β������ʱ��
#define CmdTailRecTimeLAUX			0x1b
// ����վ����1
#define CmdLAUXErrorCode1				0x1d
// ����վ����2
#define CmdLAUXErrorCode2				0x1e
// ����վ·�ɷ���
#define CmdLAUXSetRout					0x1f
// ����·��
#define CmdReturnRout							0x3f
//__________________ADC��������__________________
// ADC�������Ҳ�����
#define SetADCSetSine							{0xb2, 0x00, 0x80, 0x00}
// ADC����ֹͣ��������
#define SetADCStopSample					{0x81, 0x11, 0x00, 0x00}
// ADC���ô�TB��Դ��λ
#define SetADCOpenTBPowerLow		{0xa3, 0x00, 0x30, 0x00}
// ADC���ô�TB��Դ��λ
#define SetADCOpenTBPowerHigh		{0xa3, 0x00, 0x30, 0x40}
// ADC���ô�TB���ص�λ
#define SetADCOpenSwitchTBLow		{0xa3, 0x00, 0xf0, 0x00}
// ADC���ô�TB���ظ�λ
#define SetADCOpenSwitchTBHigh		{0xa3, 0x00, 0xf0, 0x40}
// ADC���ö��Ĵ���
#define SetADCRegisterRead					{0x82, 0x20, 0x0a, 0x00}
// ADC����д�Ĵ���
#define SetADCRegisterWrite				{0x8d, 0x40, 0x0a, 0x00, 0x52, 0x08, 0x32, 0x03, 0x6f, 0x0c, 0xff, 0x7d, 0x52, 0x40, 0x00, 0x00}
// ADC������������
#define SetADCReadContinuous			{0x81, 0x10, 0x00, 0x00}
// ADC���ô���ƯУ����Դ
#define SetADCOpenPowerZeroDrift	{0xa3, 0x05, 0xf8, 0x00}
// ADC���ò�ѯADC�Ĵ���
#define SetADCRegisterQuery				{0x00, 0x00, 0x00, 0x00}
// ADC�������ݲɼ�ͬ��
#define SetADCSampleSynchronization	{0x81, 0x04, 0x00, 0x00}
// ADC������Ưƫ�ƽ���
#define SetADCZeroDriftCorrection		{0x81, 0x60, 0x00, 0x00}
// ADC���ô�TB����
#define SetADCTBSwitchOpen				{0xa3, 0x05, 0xf8, 0x40}
// ADC������Ư
#define SetADCZeroDriftSetFromIP		{0x87, 0x40, 0x04, 0x00, 0x52, 0x08, 0x32, 0x03}

//___________________֡��ʽ����___________________
// ֡ͷ����
#define FrameHeadSize				16
// ֡ͷУ���ֳ���
#define FrameHeadCheckSize	4
// ֡ͷ��һ���ֽ�
#define FrameHeadCheck0		0x11
// ֡ͷ�ڶ����ֽ�
#define FrameHeadCheck1		0x22
// ֡ͷ�������ֽ�
#define FrameHeadCheck2		0x33
// ֡ͷ���ĸ��ֽ�
#define FrameHeadCheck3		0x44
// �����ֳ���1�ֽ�
#define FrameCmdSize1B			1
// ���������2�ֽ�
#define FramePacketSize2B		2
// ���������4�ֽ�
#define FramePacketSize4B		4
// ADC������ռ�ֽ���
#define ADCDataSize3B			3

// CRCУ��ֵ�ֽ���
#define CRCSize			2
// CRCУ��Ԥ���ֽ���
#define CRCCheckSize	4
//__________________��ͼ��������___________________
// ����Y������
#define DrawGraphYAxisLower							-2.5
// ����Y������
#define DrawGraphYAxisUpper								2.5
// ����Y���������ǩ
#define DrawGraphYAxisLabel								_T("Y")
// ����X���������ǩ
#define DrawGraphXAxisLabel								_T("X")
// ���ñ�����ɫ
#define DrawGraphSetBackgroundColor				RGB(0, 0, 64)
// ����դ����ɫ
#define DrawGraphSetGridColor							RGB(192, 192, 255)
// ���û����ɫ
#define DrawGraphSetPlotColor							RGB(255, 255, 255)
//___________________��ʱ������____________________
// TabUartToUdp���洮�ڽ��ն�ʱ�����
#define TabUartToUdpRecTimerNb						1
// TabUartToUdp���洮�ڽ��ն�ʱ����ʱ����
#define TabUartToUdpRecTimerSet						100
// TabSample���濪ʼ������ʱ�����
#define TabSampleStartSampleTimerNb				1
// TabSample���濪ʼ������ʱ����ʱ����
#define TabSampleStartSampleTimerSet				4000
// TabSample����ֹͣ������ʱ�����
#define TabSampleStopSampleTimerNb				2
// TabSample����ֹͣ������ʱ����ʱ����
#define TabSampleStopSampleTimerSet				1000
// TabSample�����ѯӲ���豸����������ʱ�����
#define TabSampleQueryErrorCountTimerNb		3
// TabSample�����ѯӲ���豸����������ʱ����ʱ����
#define TabSampleQueryErrorCountTimerSet		1000
// TabSample����β����ⶨʱ�����
#define TabSampleTailMonitorTimerNb				4
// TabSample����β����ⶨʱ����ʱ����
#define TabSampleTailMonitorTimerSet				1000
// TabSample����IP��ַ���ü�ⶨʱ�����
#define TabSampleIPSetMonitorTimerNb				5
// TabSample����IP��ַ���ü�ⶨʱ����ʱ����
#define TabSampleIPSetMonitorTimerSet				5000
// TabSample�����ʼ����������ʱ��Ķ�ʱ�����
#define TabSampleInitSysTimeTimerNb				6
// TabSample�����ʼ����������ʱ��Ķ�ʱ����ʱ����
#define TabSampleInitSysTimeTimerSet				1000
// TabSample������ʱͳ���õĶ�ʱ�����
#define TabSampleTimeCalTimerNb						7
// TabSample������ʱͳ���õĶ�ʱ����ʱ����
#define TabSampleTimeCalTimerSet						2000
// TabSample������ADC�������õĶ�ʱ�����
#define TabSampleADCSetTimerNb						8
// TabSample������ADC�������õĶ�ʱ����ʱ����
#define TabSampleADCSetTimerSet						2500
// TabSample������ADC��ƯУ���Ķ�ʱ�����
#define TabSampleADCZeroDriftTimerNb			9
// TabSample������ADC��ƯУ���Ķ�ʱ����ʱ����
#define TabSampleADCZeroDriftTimerSet			2000
// TabPortMonitoring����ˢ�½��շ���֡���Ķ�ʱ�����
#define TabPortMonitoringFrameNumTimerNb	1
// TabPortMonitoring����ˢ�½��շ���֡���Ķ�ʱ����ʱ����
#define TabPortMonitoringFrameNumTimerSet	1000
// TabADCDataShow����ˢ�½��յ�ADC��ֵ�Ķ�ʱ�����
#define TabADCDataShowADCTimerNb				1
// TabADCDataShow����ˢ�½��յ�ADC��ֵ�Ķ�ʱ����ʱ����
#define TabADCDataShowADCTimerSet				3000
// PortMonitoringRec����ˢ�½���֡�Ķ�ʱ�����
#define PortMonitoringRecTimerNb						1
// PortMonitoringRec����ˢ�½���֡�Ķ�ʱ����ʱ����
#define PortMonitoringRecTimerSet						1000
// PortMonitoringSend����ˢ�½���֡�Ķ�ʱ�����
#define PortMonitoringSendTimerNb						1
// PortMonitoringSend����ˢ�½���֡�Ķ�ʱ����ʱ����
#define PortMonitoringSendTimerSet					1000

//__________________ȫ�ֱ�������___________________
// ����β��ʱ�̲�ѯ֡����
extern unsigned int m_uiSendTailTimeFrameCount;
// ���յ���β��ʱ�̲�ѯ֡����
extern unsigned int m_uiRecTailTimeFrameCount;
// CRC16У��
extern unsigned short get_crc_16(unsigned char* buf, int buf_size);
// ���ֽ��ַ���ת��Ϊ���ֽ��ַ���
extern string WideCharToMultiChar(wstring str);
// ���������ĵ��ַ���д���ļ�
extern void WriteCHToCFile(CFile *file, CString str);