#include <vector>
using std::vector;
// ____________��������___________
// ����������������
#define SetVScrollWidth							25
// ���ú�����������
#define SetHScrollWidth						25
// ���û�ͼ�ؼ�X������
#define SetPlotCtrlXInterval					15
// ���û�ͼ�ؼ�Y������
#define SetPlotCtrlYInterval					15
// ���û�ͼ��X������
#define SetPlotAreaXInterval					10
// ���û�ͼ��Y������
#define SetPlotAreaYInterval					45
// ���û�ͼ���ײ����
#define SetPlotAreaBottomInterval		30
// ���ñ�ǩ���
#define SetLegendWidth						15	
// ���ñ�ǩX������
#define SetLegendXInterval					10
// ���ñ�ǩY������
#define SetLegendYInterval					45
// ���û�ͼ�ؼ�������ɫ
#define SetPlotCtrlBackgroundColor		0xf0f0ff
// ���û�ͼ��������ɫ
#define SetPlotAreaBackgroundColor	0xffffff
// ���ú���դ������ɫ
#define SetHGridColor							0xcccccc
// ��������դ������ɫ					
#define SetVGridColor							0xcccccc
// ���ñ�����������ɫ
#define SetTitleBackgroundColor			0xccccff
// ���ñ������߿���ɫ
#define SetTitleEdgeColor						0x000000
// ���ñ�ǩ�������С
#define SetLegnedBoxFontSize				9
// ���ñ����������С
#define SetTitleBoxFontSize					12
// ���û��ߵĿ��
#define SetLineWidth								1
// ����X��Ŀ��
#define SetXAxisWidth							2
// ����Y��Ŀ��
#define SetYAxisWidth							2
// _________����������ɫ___________
// ��ɫRGB
#define RedColor								0xFF0000
// ��ɫRGB
#define GreenColor							0x00FF00
// ��ɫRGB
#define BlueColor								0x0000FF
// �ۺ�RGB
#define PinkColor								0xFF8888
// _________ADC���ݽ���___________
// ADC����ͼ�λ���ʾ���ն˿�
#define ADCGraphShowPort				0x7800
// ADC����ͼ�λ���ʾ���÷���Ŀ��˿�
#define ADCGraphSetRecPort			0x9401
// ����IP��ַ
#define IPHostAddr							_T("127.0.0.1")
// ����ADC����һ֡�Ļ�������С
#define ADCRecFrameBufSize			256
// ����ADC����ͼ����ʾ����֡�Ļ�������С
#define ADCSendFrameBufSize			256
// �������ݰ���ADC���ݸ���
#define ReceiveDataNum					72
// ÿ���ļ��洢ÿ��������ADC���ݰ�����
#define SaveADCDataPackageNum	406
// ÿ���������ļ�����ռ�ռ��С
#define ADCDataSaveSize					10
// ADC���ݶ˿ڽ��ջ�������С
#define ADCRecPortBufSize				10000 * ADCRecFrameBufSize
// ADC���ݿ�ʼͼ�λ���ʾ��־λ
#define StartGraphShow						3
// ADC����ֹͣͼ�λ���ʾ��־λ
#define StopGraphShow						4
// ȡ��Сֵ����
#define OptMinValue							1
// ȡ���ֵ����
#define OptMaxValue							2
// _________��������____________
// ���ö�ȡ�ļ�ͷ�Ļ�������С
#define SetReadFileHeadBufSize			1000
// һ��ADC����ռ�û�������С
#define ADCDataBufSize						12
// ADC���ݼ�ļ����С���ո�+\t��
#define ADCDataInterval						2
// ���紫����ʾ֡��
#define ADCRecFrameShowNum			7
// ��ʼ״̬ÿ������ʾ�ĵ���
#define ShowLinePointsNumNow			ADCRecFrameShowNum * ReceiveDataNum
// ÿ����������ʾ�ĵ���
#define ShowLinePointsNumMin			10
// X�������ǩ��С��ʾ�����
#define SetLegendXIntervalNumMin		3
// ����֡��������ֵ�趨
#define SndFrameBufInit						0x00
// �����ļ�
#define OptTypeLoadFile						1
// �����ļ���
#define OptTypeLoadFolder					2
// ���紫���ͼ
#define OptTypeNetwork						3
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
// ADC����ͼ�λ���ʾ������
#define CmdADCDataSamplingRate		0x20
// �����ֳ���1�ֽ�
#define FrameCmdSize1B			1
// ���������2�ֽ�
#define FramePacketSize2B		2
// ���������4�ֽ�
#define FramePacketSize4B		4
// ADC������ռ�ֽ���
#define ADCDataSize3B			3
//____________________����������__________________
// ������������
#define SendSetCmd								0x0001
// ���Ͳ�ѯ����
#define SendQueryCmd							0x0002
// ����ADC������������
#define SendADCCmd							0x0003
//___________________��ʱ������____________________
// ����ˢ�¶�ʱ�����
#define GraphRefreshTimerNb								1
// ����ˢ�¶�ʱ����ʱ����
#define GraphRefreshTimerSet								500

// ����Y������
#define DrawGraphYAxisLower							-2.5
// ����Y������
#define DrawGraphYAxisUpper								2.5
// �ɼ�վADC���ݴ洢
extern vector<double>* m_dbFduData;
// �ɼ�վADC���ݻ�ͼ
extern vector<double>* m_dbFduShow;