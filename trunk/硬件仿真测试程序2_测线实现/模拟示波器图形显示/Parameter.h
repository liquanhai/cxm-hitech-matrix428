#include "HardwareTestDlg.h"

// ��ͼ�ؼ�����
#define GraphViewNum	8
// ��ͼ�ؼ�ID��
#define GraphViewId		8
// �����������ݴ��������ʾ�ؼ�ID����
#define MathValueIdNum	4 
// ��ʼ�ɼ�����
#define StartSampleCmd	81
// �������ݰ��Ĵ�С
#define ReceiveDataSize	74
// AD���ݲɼ����ն˿�
#define ADRecPort		0x8300
// AD���ݲɼ�����Ͷ˿�
#define ADCmdSend		0x6000
// AD���ݲɼ�����Ӧ��˿�
#define ADCmdRec		0x6500
// IP�㲥��ַ
#define IPBroadcastAddr	"127.0.0.1"
// ԴIP��ַ
#define IPSource		"127.0.0.1"
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
// ������ӵ��豸��
#define InstrumentMaxCount	5	
// �װ�����
#define HeadFrameCount		5
// β������
#define TailFrameCount		5
class CHardwareTestDlg;
extern CHardwareTestDlg* pHardwareTestDlg;