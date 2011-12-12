#pragma once
// һ�����ߵ�ʱ��
#define OneSleepTime						50
// �����̷߳�������֡��ʱ����
#define HertBeatSleepTimes					5
// �װ��߳̽����װ���ʱ����
#define HeadFrameSleepTimes					1

// �ȴ������̹߳رյ���ʱ����
#define CloseAllThreadSleepTimes			4
// Field OnҰ����߷�������
#define	FieldOn								1
// Field OnҰ����߷���ر�
#define FieldOff							0

// ���յ���������֡֡����
#define RcvFrameSize						256
// ���͵���������֡֡����
#define SndFrameSize						128

// �������Ϳͻ���֮����Ϣ��������֡��������С
#define NetInterfaceBufSize					65536

// ��������-����վ
#define InstrumentTypeLAUX					1
// ��������-��Դվ
#define InstrumentTypeLAUL					2
// ��������-�ɼ�վ
#define InstrumentTypeFDU					3
// ��������-LCI
#define InstrumentTypeLCI					4
// �����Ϸ�
#define DirectionTop						1
// �����Ϸ�
#define DirectionDown						2
// �����Ϸ�
#define DirectionLeft						3
// �����Ϸ�
#define DirectionRight						4
// ��������
#define DirectionCenter						0

//________________��������ͻ�������������_________________
// ����1-Field ON/OFF
#define FieldCmd							0x0001
// ����2-FormLine
#define FormLineCmd							0x0002
// ����3-Look
#define LookCmd								0x0003
// ����4-Test From InstrumentTestSetup
#define InstrumentTestCmd					0x0004
// ����5-Test From SensorTestSetup
#define SensorTestCmd						0x0005
// ����6-Test From MultipleTestSetup
#define MultipleTestCmd						0x0006
// ����7-Test From SeismonitorTestSetup
#define SeismonitorTestCmd					0x0007
// ����8-Test From InstrumentView ����������ͼ�ġ�GO����ť
#define InstrumentViewTestCmd				0x0008
// ����9-Test From SensorTestView	���Լ첨����ͼ�ġ�GO����ť
#define SensorTestViewTestCmd				0x0009
// ����	10-Test From SeismonitoView
#define SeismonitoViewTestCmd				0x000a
// ֡ͷ�����ָ�λ
#define FrameHeadHigh						0xEB
// ֡ͷ�����ֵ�λ
#define FrameHeadLow						0x90
// ֡β�����ָ�λ
#define FrameTailHigh						0x14
// ֡β�����ֵ�λ
#define FrameTailLow						0x6F
// ֡���� 0xFF-����֡
#define FrameTypeReturnCmd					0xFF
// ֡���� 0x01-����֡����Ҫ�����֡
#define FrameTypeNoReturnCmd				0x01
// �����ֳ��������֪ͨ����
#define CmdGenerateOutputData				0x64
// ���� 101-Server Field ON/OFF
#define CmdServerFieldStatus				0x65

//_________________���������豸����������__________________
// ������������
#define SendSetCmd									0x0001
// ���Ͳ�ѯ����
#define SendQueryCmd							0x0002
// ����ADC���������ط�����
#define SendADCCmd								0x0003
// TB��ʼ�ɼ����ؿ�������(TB_L��8λ)
#define CmdTBCtrl									0x050000
// ����
#define CmdSn											0x01
// �װ�ʱ��
#define CmdHeadFrameTime					0x02
// ����IP��ַ
#define CmdLocalIPAddr							0x03
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
#define CmdSetBroadCastPort					0x0a
// ϵͳӲ��״̬����
#define CmdFDUErrorCode						0x0b
// TBʱ�̸�λ
#define CmdTBHigh									0x0c
// TBʱ�̵�λ
#define CmdTbLow									0x0d
// work_ctrl ����վ����
#define CmdLAUXRoutOpenQuery		0x0e
// ·�ɿ���
#define CmdLAUXRoutOpenSet			0x0f
// β������\����ʱ�̵�λ
#define CmdTailRecSndTimeLow			0x16
// �㲥����ȴ��˿�ƥ��
#define CmdBroadCastPortSet					0x17
// ����ADC��������������
#define CmdADCSet								0x18
// ����ʱ��
#define CmdNetTime								0x19
// ����վ����β������ʱ��
#define CmdLineTailRecTimeLAUX		0x1b
// ����վ������β������ʱ��
#define CmdLAUTailRecTimeLAUX		0x1c
// ����վ����1
#define CmdLAUXErrorCode1				0x1d
// ����վ����2
#define CmdLAUXErrorCode2				0x1e
// ����վ·�ɷ���
#define CmdLAUXSetRout						0x1f
// ADC����ͼ�λ���ʾ������
#define CmdADCDataSamplingRate		0x20
// ����·��
#define CmdReturnRout							0x3f

//___________________֡��ʽ����___________________
// ֡ͷ����
#define FrameHeadSize				16
// ֡ͷУ���ֳ���
#define FrameHeadCheckSize		4
// ֡ͷ��һ���ֽ�
#define FrameHeadCheck0			0x11
// ֡ͷ�ڶ����ֽ�
#define FrameHeadCheck1			0x22
// ֡ͷ�������ֽ�
#define FrameHeadCheck2			0x33
// ֡ͷ���ĸ��ֽ�
#define FrameHeadCheck3			0x44
// �����ֳ���1�ֽ�
#define FrameCmdSize1B			1
// ���������2�ֽ�
#define FramePacketSize2B			2
// ���������4�ֽ�
#define FramePacketSize4B			4
// ADC������ռ�ֽ���
#define ADCDataSize3B				3
// ����֡��������ֵ�趨
#define SndFrameBufInit					0x00
// CRCУ��ֵ�ֽ���
#define CRCSize							2
// CRCУ��Ԥ���ֽ���
#define CRCCheckSize					4
