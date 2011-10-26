#include <string>
using std::string;
using std::wstring;
//______________ѡ��ؼ�λ������______________
// ����ѡ�λ��
#define TabSampleCtl									0
// ADC��������ѡ�λ��
#define TabADCSettingsCtl						1
// ADC����������ʾѡ�λ��
#define TabADCDataShowCtl					2
// ����תUDPѡ�λ��
#define TabUartToUdpCtl							3
// �˿ڼ���ѡ�λ��
#define TabPortMonitoringCtl					4
// �����豸EEPROMѡ�λ��
#define TabEepromCtl								5
// �˿ڼ��ӽ���֡ѡ�λ��
#define TabPortMonitoringRecCtl				0
// �˿ڼ��ӽ���֡ѡ�λ��
#define TabPortMonitoringSndCtl				1
//____________UDP�׽����¼���Ϣ����____________
// ����תUDP�׽����¼�
#define WM_UARTTOUDPSOCKET		WM_USER + 1001
// �װ�UDP�׽����¼�
#define WM_HEADFRAMESOCKET		WM_USER + 1002
// IP��ַ����UDP�׽����¼�
#define WM_IPSETSOCKET					WM_USER + 1003
// β��UDP�׽����¼�
#define WM_TAILFRAMESOCKET		WM_USER + 1004
// β��ʱ�̲�ѯUDP�׽����¼�
#define WM_TAILTIMESOCKET			WM_USER + 1005
// ����ʱ���ѯUDP�׽����¼�
#define WM_SYSTIMESOCKET				WM_USER + 1006
// ADC����UDP�׽����¼�
#define WM_ADCSETSOCKET				WM_USER + 1007
// ADC����ͼ�λ���ʾUDP�׽����¼�
#define WM_ADCGRAPHSOCKET			WM_USER + 1008
//__________________ͨѶ�˿�����__________________
// ����֡���ʹ����˿�
#define HeartBeatPort					0x7000
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
#define ADSetReturnPort			0x8300
// AD���ݲɼ����ն˿�
#define ADRecPort						0x8400
// �ɼ�վ����ʱ�̲�ѯ�˿�
#define CollectSysTimePort		0x8500
// ��ѯӲ���豸����������ض˿�
#define QueryErrorCodePort		0x8600 
// ADC����ͼ�λ���ʾ���Ͷ˿�
#define ADCGraphShowPort		0x7800
// ADC����ͼ�λ���ʾ���ý��ն˿�
#define ADCGraphSetRecPort	0x9401
// EEPROM��дӦ��˿�
#define EepromRecPort			0x8700
// ADC���ù㲥�˿�
#define ADCSetBroadcastPort	0x66666666
// �㲥�˿�
#define BroadCastPort				0xffffffff

//___________________����������____________________
// ������ӵ��豸��
#define InstrumentMaxCount			300
// ��ͼ�ؼ�����
#define InstrumentNum					300
// �������ݰ��Ĵ�С
#define ReceiveDataSize				72
// ����������
#define RcvBufNum						4
// �������ͻ�������С
#define HeartBeatSndBufSize		1280
// ���յ��������ݰ���С
#define RcvFrameSize					256
// ���͵��������ݰ���С
#define SndFrameSize						128
// ����ת�˿��ж˿ڻ�������С
#define UartToUdpRcvSize			1024
// ADC���ݻ�������С��4K�����ʵ����豸һ��������ϴ�56֡����
#define ADCDataBufSize				10000000
// �˿ڼ��ӻ�������С��ADC���ݻ�������С��2��
#define PortMonitoringBufSize		10000000
// ����תUDP�˿ڻ�������С
#define UartToUDPBufSize			65536
// ����֡��������ֵ�趨
#define SndFrameBufInit				0x00
// ADC���������Ԥ��Ļ�����֡��
#define ADCDataTempFrameNum	60
// ADC���������Ԥ��Ļ�������С
#define ADCDataTempDataSize	(ADCDataTempFrameNum * ReceiveDataSize)
// EEPROM��������С
#define EEPROMCapacity				8192
// ÿ֡��ȡEEPROM���ݵ����ֵ
#define EEPROMPerFrameReadMax	64
// ÿ֡д��EEPROM���ݵ����ֵ
#define EEPROMPerFrameWriteMax	64
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
// ����վβ������
#define TailFrameLAUXCount				5
// ����վβ���ȶ�����
#define TailFrameStableLAUXCount		8
// �ɼ�վβ������
#define TailFrameFDUCount					8
// �ɼ�վβ���ȶ�����
#define TailFrameStableFDUCount		10
// β����ѯ����
#define TailTimeFrameCount					8
// ��������-�ɼ�վ
#define InstrumentTypeFDU					3
// ��������-��Դվ
#define InstrumentTypeLAUL				2 
// ��������-����վ
#define InstrumentTypeLAUX				1
// ADC�����ļ��ļ�ͷ����
#define ADCFileHeadRow						3
// ADC����С�����λ��
#define DecimalPlaces							8
// ADC���ݼ��
#define ADCDataPlaces							2
// ADC����֡�ط�����
#define ADCFrameRetransmissionNum	5
// Ӳ���洢ADC���ݸ�����������С
#define HardwareSaveADCNum			2000
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
#define ADCOperationSleepTime						100
// ADC��ƯУ�����������ɼ���ʱ
#define ADCReadContinuousSleepTime			500
// �˿ڼ��ӷ����߳�Sleepʱ��
#define PortMonitoringSendThreadSleepTime	50
// �˿ڼ��ӽ����߳�Sleepʱ��
#define PortMonitoringRecThreadSleepTime	50
// �����߳�Sleepʱ��
#define HeartBeatThreadSleepTime					500
// �豸���������߳�Sleepʱ��
#define InstrumentMonitorThreadSleepTime		1000
// ADC���ݽ����߳�Sleepʱ��
#define ADCDataRecThreadSleepTime				50
// TB������ʱ��λ
#define TBSleepTimeHigh									0xa000
// TB������ʱ��λ
#define TBSleepTimeLow									0x00fa
// ADC������ʾ����ÿ����ʾ�ĸ���
#define ADCDataShowPerLineNum					6
// IP�㲥��ַ
#define IPBroadcastAddr		0xFFFFFFFF
// XML�����ļ���
#define XMLFileName			_T("MatrixTestSoft.xml")
// ADC����ת��
#define ADCDataConvert									1
// ADC���ݲ�ת��
#define ADCDataNoConvert								0
// ȡ��Сֵ����
#define OptMinValue											1
// ȡ���ֵ����
#define OptMaxValue											2
// �ж��Ƿ���Ȳ���
#define OptCheckEqule										3
// �Ƚ�ֵ����ȵķ���ֵ
#define CheckEquleReturn									-1
// �Ƚ�ֵ����ȵķ���ֵ
#define CheckNotEquleReturn							-2
// EEPROM�б�������
#define EEPROMListAdd									1
// EEPROM�б�ɾ������
#define EEPROMListDelete								2
//____________________����������__________________
// ������������
#define SendSetCmd								0x0001
// ���Ͳ�ѯ����
#define SendQueryCmd							0x0002
// ����ADC���������ط�����
#define SendADCCmd							0x0003
// TB��ʼ�ɼ����ؿ�������(TB_L��8λ)
#define CmdTBCtrl									0x010000
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
// ADC����ͼ�λ���ʾ������
#define CmdADCDataSamplingRate		0x20
// ����·��
#define CmdReturnRout							0x3f
// ADC���ݿ�ʼͼ�λ���ʾ��־λ
#define StartGraphShow							3
// ADC����ֹͣͼ�λ���ʾ��־λ
#define StopGraphShow							4
// ��EEPROM����
#define ReadEEPROMCmd						1
// дEEPROM����
#define WriteEEPROMCmd						2
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
#define TabSampleStartSampleTimerSet				1000
// TabSample����ֹͣ������ʱ�����
#define TabSampleStopSampleTimerNb				2
// TabSample����ֹͣ������ʱ����ʱ����
#define TabSampleStopSampleTimerSet				3000
// TabSample�����ѯӲ���豸���������ʱ�����
#define TabSampleQueryErrorCountTimerNb		3
// TabSample�����ѯӲ���豸���������ʱ����ʱ����
#define TabSampleQueryErrorCountTimerSet		1000
// TabSample����β����ⶨʱ�����
#define TabSampleTailMonitorTimerNb				4
// TabSample����β����ⶨʱ����ʱ����
#define TabSampleTailMonitorTimerSet				1000
// TabSample����IP��ַ���ü�ⶨʱ�����
#define TabSampleIPSetMonitorTimerNb				5
// TabSample����IP��ַ���ü�ⶨʱ����ʱ����
#define TabSampleIPSetMonitorTimerSet				8000
// TabSample�����ʼ����������ʱ��Ķ�ʱ�����
#define TabSampleInitSysTimeTimerNb				6
// TabSample�����ʼ����������ʱ��Ķ�ʱ����ʱ����
#define TabSampleInitSysTimeTimerSet				1000
// TabSample������ʱͳ���õĶ�ʱ�����
#define TabSampleTimeCalTimerNb						7
// TabSample������ʱͳ���õĶ�ʱ����ʱ����
#define TabSampleTimeCalTimerSet						2300
// TabSample������ADC�������õĶ�ʱ�����
#define TabSampleADCSetTimerNb						8
// TabSample������ADC�������õĶ�ʱ����ʱ����
#define TabSampleADCSetTimerSet						2500
// TabSample������ADC��ƯУ���Ķ�ʱ�����
#define TabSampleADCZeroDriftTimerNb			9
// TabSample������ADC��ƯУ���Ķ�ʱ����ʱ����
#define TabSampleADCZeroDriftTimerSet			2000
// TabSample������ADC��������Ӧ����ӵĶ�ʱ�����
#define TabSampleADCSetReturnTimerNb			10
// TabSample������ADC��������Ӧ����ӵĶ�ʱ����ʱ����
#define TabSampleADCSetReturnTimerSet			1000

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
//__________________��־��¼״̬__________________
// ��������״̬
#define SuccessStatus												1
// ����״̬
#define WarningStatus											2
// ����״̬
#define ErrorStatus													3
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
// extern void WriteCHToCFile(CFile *file, CString str);
extern void WriteCHToCFile(CArchive *ar, CString str);
// CStringת��Ϊconst char*
extern const char* ConvertCStringToConstCharPointer(CString str);
// 
extern char* Convert(char* ch,int dec,int sign);
