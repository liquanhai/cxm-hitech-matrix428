#include "PortMonitoringDlg.h"

#define RcvPort1	0x8202	// Ŀ��1���ն˿�
#define SendPort1	0x9002	// Ŀ��1���Ͷ˿�
#define RcvPort2	0x9001	// Ŀ��2���ն˿�
#define SendPort2	0x8201	// Ŀ��2���Ͷ˿�
#define RcvBufSize	655360	// ������ջ�������С
#define SndBufSize	655360	// ���巢�ͻ�������С
#define InstrumentForTest	8	// ��������������
#define ClearListFrameCount	100	// �ﵽָ��֡�������б��й����ط�֡
#define ADCRetransmissionCmd	0x0003	// ADC�����ط�����
class CPortMonitoringDlg;
extern CPortMonitoringDlg* pDlg;
