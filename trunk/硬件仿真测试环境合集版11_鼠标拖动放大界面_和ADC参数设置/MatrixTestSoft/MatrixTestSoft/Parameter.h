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
// IP�㲥��ַ
#define IPBroadcastAddr	"255.255.255.255"
// ������ӵ��豸��
#define InstrumentMaxCount	5	
// �װ�����
#define HeadFrameCount		5
// β������
#define TailFrameCount		5
// ��ͼ�ؼ�����
#define GraphViewNum	48
// �����������ݴ��������ʾ�ؼ�ID����
#define MathValueIdNum	4 
// �������ݰ��Ĵ�С
#define ReceiveDataSize		74
// ADC�����ļ��ļ�ͷ����
#define ADCFileHeadRow	3
// ADC����С�����λ��
#define DecimalPlaces	9

// ����β��ʱ�̲�ѯ֡����
extern unsigned int m_uiSendTailTimeFrameCount;
// ���յ���β��ʱ�̲�ѯ֡����
extern unsigned int m_uiRecTailTimeFrameCount;
// extern HANDLE	hCom;				// ׼���򿪵Ĵ��ڵľ��