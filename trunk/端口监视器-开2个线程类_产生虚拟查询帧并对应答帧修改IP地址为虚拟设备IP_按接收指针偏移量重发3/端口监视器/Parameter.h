#include "PortMonitoringDlg.h"

#define RcvPort1	0x8202	// Ŀ��1���ն˿�
#define SendPort1	0x9002	// Ŀ��1���Ͷ˿�
#define RcvPort2	0x9001	// Ŀ��2���ն˿�
#define SendPort2	0x8201	// Ŀ��2���Ͷ˿�
#define RcvBufSize	655360	// ������ջ�������С
#define SndBufSize	655360	// ���巢�ͻ�������С
#define InstrumentForTest	10	// ��������������
#define ClearListFrameCount	10	// �ﵽָ��֡�������б��й����ط�֡
#define ADCRetransmissionCmd	0x0003	// ADC�����ط�����
#define SendADCFrameCountMax		10	// ���һ�η���ADC���ݲ�ѯ֡��
#define ADRecPort				0x8300	// AD���ݲɼ����ն˿�
class CPortMonitoringDlg;
extern CPortMonitoringDlg* pDlg;
