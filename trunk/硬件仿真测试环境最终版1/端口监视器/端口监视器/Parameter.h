#include "PortMonitoringDlg.h"

#define RcvPort1	0x8202	// Ŀ��1���ն˿�
#define SendPort1	0x9002	// Ŀ��1���Ͷ˿�
#define RcvPort2	0x9001	// Ŀ��2���ն˿�
#define SendPort2	0x8201	// Ŀ��2���Ͷ˿�

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
// ״̬��ѯ֡Ӧ��˿�
#define	GetStatusPort		0x8206


class CPortMonitoringDlg;

extern CPortMonitoringDlg* pDlg;
