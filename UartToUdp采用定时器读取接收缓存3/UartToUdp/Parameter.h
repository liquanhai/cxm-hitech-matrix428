
//__________________���ڶ˿ڶ���__________________
#define COM0 "�˿�1"
#define COM1 "�˿�2"
#define COM2 "�˿�3"
#define COM3 "�˿�4"
#define COM4 "�˿�5"
#define COM5 "�˿�6"
#define COM6 "�˿�7"
#define COM7 "�˿�8"
#define COM8 "�˿�9"

//__________________���ڲ����ʶ���________________
#define BAUD0 "300"
#define BAUD1 "600"
#define BAUD2 "1200"
#define BAUD3 "2400"
#define BAUD4 "4800"
#define BAUD5 "9600"
#define BAUD6 "19200"
#define BAUD7 "38400"
#define BAUD8 "43000"
#define BAUD9 "56000"
#define BAUD10 "57600"
#define BAUD11 "115200"

//____________________�˿ڶ���_____________________
// UDP���ն˿�
#define ReceivePort		0x8202
// AD���ݲɼ����ն˿�
#define ADRecPort		0x8300
// AD���ݲɼ�����Ͷ˿�
#define ADCmdSend		0x6000
// AD���ݲɼ�����Ӧ��˿�
#define ADCmdRec		0x6500
// ����֡���ʹ����˿�
#define HeartBeatRec	0x7000
// ���Ͷ˿�
#define SendPort		0x8202
// �װ����ն˿�
#define HeadFramePort	0x8000
// ���ڽ���IP��ַ����Ӧ��˿�
#define IPSetPort		0x9100
// β�����ն˿�
#define TailFramePort	0x9000
// ���ڽ�������β��ʱ�̲�ѯ�Ķ˿ں�
#define TailTimeFramePort	0x9200
// ���ڷ�������ʱ�����õĶ˿ں�
#define TimeSetPort		0x9300
// ����IP��ַ
#define IPSource		_T("127.0.0.1")
//���ڽ��մ�UDP���͵Ķ˿���
#define UDPPortNb	6