
#include <list>

using std::list;
using std::string;

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _LogOutPut_H
#define   _LogOutPut_H
// ��־�ļ���
#define LogFolderPath				_T("..\\Log")
// ϵͳ��־�ļ��У��������������桢����
#define SysOptLogFolderPath			_T("\\ϵͳ������־")
// ʱͳ��־�ļ��У�����β��ʱ�̲�ѯ��ʱͳ����Ӧ�𼰽��ͳ�ƣ�
#define TimeDelayLogFolderPath		_T("\\ʱͳ��־")
// �����ѯ��־�ļ��У����������ѯӦ�𼰽��ͳ�ƣ�
#define ErrorCodeLogFolderPath		_T("\\�����ѯ��־")
// ֡ʱ���ƫ������־��������֡���ط�֡��ʧЧ֡���ͳ�ƣ�
#define ADCFrameTimeLogFolderPath	_T("\\��������֡ʱ�估ƫ����")
// ADC����֡
#define ADCDataLogFolderPath		_T("\\��������")

// ���ѡ��:Debug�����Ϊ0��Release�����Ϊ1
#define OutPutSelect				0
// ���������־����
#define OutPutLogErrorLimit			100
// ��־�ļ������ļ������Ϣ����
#define OutPutLogFileInfoNumLimit	5000
// ��־�������
enum{LogType, WarningType, ErrorType, ExpandType};
// ��־�ļ�����
enum{OptLogType, TimeDelayLogType, ErrorCodeLogType, ADCFrameTimeLogType};


// ��־����ṹ
typedef struct LogOutPut_Struct
{
	// ��־�����Դͬ������
	CRITICAL_SECTION m_oSecLogFile;
	// ��־����ļ�ָ��
	FILE* m_pFile;
	// ��־����ṹ
	list<string> m_oLogOutputList;
	// �������
	unsigned int m_uiErrorCount;
	// ��־���·��
	string m_SaveLogFilePath;
	// ��־�ļ����
	unsigned int m_uiLogFileNb;
	// ��־�ļ��洢��Ϣ��������
	unsigned int m_uiLogInfoCount;
	// ��־�ļ�����
	byte m_byLogFileType;
}m_oLogOutPutStruct;
#endif