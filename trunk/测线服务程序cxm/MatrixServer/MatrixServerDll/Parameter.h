#ifndef _Parameter_H
#define _Parameter_H
/** ��־�ļ���*/
#define LogFolderPath				_T("..\\Log")
/** ϵͳ��־�ļ��У��������������桢����*/
#define SysOptLogFolderPath			_T("\\ϵͳ������־")
/** ʱͳ��־�ļ��У�����β��ʱ�̲�ѯ��ʱͳ����Ӧ�𼰽��ͳ�ƣ�*/
#define TimeDelayLogFolderPath		_T("\\ʱͳ��־")
/** �����ѯ��־�ļ��У����������ѯӦ�𼰽��ͳ�ƣ�*/
#define ErrorCodeLogFolderPath		_T("\\�����ѯ��־")
/** ֡ʱ���ƫ������־��������֡���ط�֡��ʧЧ֡���ͳ�ƣ�*/
#define ADCFrameTimeLogFolderPath	_T("\\��������֡ʱ�估ƫ����")
/** ADC����֡*/
#define ADCDataLogFolderPath		_T("\\��������")
/** ����������·��*/
#define ParamServerFolderPath		"..\\parameter\\Server"
/** ������������ļ��ļ���*/
#define ServerXmlFileName			"\\MatrixServer.XML"
/** ����������ļ��ļ���*/
#define ServerIniFileName			"\\MatrixServerDLL.ini"

/** ���ѡ��:Debug�����Ϊ0��Release�����Ϊ1*/
#define OutPutSelect				0
/** ���������־����*/
#define OutPutLogErrorLimit			1000
/** ��־�ļ������ļ������Ϣ����*/
#define OutPutLogFileInfoNumLimit	5000
/** ��־�������*/
enum{LogType, WarningType, ErrorType, ExpandType};
/** ��־�ļ�����*/
enum{OptLogType, TimeDelayLogType, ErrorCodeLogType, ADCFrameTimeLogType};
/** INI�ļ���ȡ�ؼ��ֻ�������С*/
#define INIFileStrBufSize			256
/** �ص�����-�ɼ�����*/
// typedef void (CALLBACK* ProSampleDateCallBack)(int _iLineIndex, int _iPointIndex, int *_piData,
// 	int _iSize, unsigned int _uiSN);
/** ʱͳ��λ����ֵ����*/
#define TimeDelayLowLimit	50
/** ʱͳ��λ����Ĭ��ֵ*/
#define TimeDelayDefault	32

/** ADC�������ò������*/
#define ADCSetOptNb			1
/** ADC��ʼ�ɼ��������*/
#define	ADCStartSampleOptNb	2
/** ADCֹͣ�ɼ��������*/
#define ADCStopSampleOptNb	3
/** ��������-����վ*/
#define InstrumentTypeLAUX	1
/** ��������-��Դվ*/
#define InstrumentTypeLAUL	2
/** ��������-�ɼ�վ*/
#define InstrumentTypeFDU	3
/** ��������-LCI*/
#define InstrumentTypeLCI	4
/** �����Ϸ�*/
#define DirectionTop		1
/** �����·�*/
#define DirectionDown		2
/** ������*/
#define	DirectionLeft		3
/** �����ҷ�*/
#define DirectionRight		4
/** ��������*/
#define DirectionCenter		0
#endif