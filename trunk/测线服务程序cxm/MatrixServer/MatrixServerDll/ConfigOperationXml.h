#ifndef _ConfigOptXml_H
#define _ConfigOptXml_H
#include <list>
#include <map>
using std::list;
using std::map;
using std::string;
/**
* @struct Delay_Struct
* @brief Delay SETUP�ṹ��
*/
typedef struct Delay_Struct
{
	/** VPʱ�们��ֵ*/
	int m_iVPSlipTime;
	/** VPʱ����ʱ���ֵ*/
	int m_iVPTimeMax;
	/** VPʱ����ʱ��Сֵ*/
	int m_iVPTimeMin;
	/** Acqʱ�们��ֵ*/
	int m_iAcqSlipTime;
	/** Acqʱ����ʱ���ֵ*/
	int m_iAcqTimeMax;
	/** Acqʱ����ʱ��Сֵ*/
	int m_iAcqTimeMin;
}m_oDelayStruct;

/**
* @struct SourceShot_Struct
* @brief �ڱ�ṹ��
*/
typedef struct SourceShot_Struct
{
	/** �ڵ�״̬*/
	unsigned int m_uiVPStatus;
	/** �ں�*/
	unsigned int m_uiShotID;
	/** �жϱ�־λ*/
	unsigned int m_uiBreakPoint;
	/** ��Դ����ߺ�*/
	float m_fSourceLine;
	/** ��Դ����յ�λ�ú�*/
	float m_fSourceReceiver;
	/** �����е���Ͳ��ߺ�*/
	unsigned int m_uiSFL;
	/** ���е�һ�����ռ첨��λ�ú���*/
	unsigned int m_uiSFN;
	/** �������ͣ��������к�������У�*/
	unsigned int m_uiSpreadType;
	/** �������У���ʹ������ʾΪ��,ֵΪ-1��*/
	int m_iSuperSpread;
	/** ���ݴ�������*/
	unsigned int m_uiProcessType;
	/** ע����Ϣ����*/
	unsigned short m_usCommentsSize;
	/** ע��*/
	char* m_pcComments;
}m_oSourceShotStruct;

/**
* @struct SourceExplo_Struct
* @brief Explo��Դ�ṹ��
*/
typedef struct SourceExplo_Struct
{
	/** ��Դ״̬*/
	unsigned int m_uiSourceStatus;
	/** ��Դ���*/
	unsigned int m_uiSourceNb;
	/** ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ*/
	char* m_pcLabel;
	/** ��Դ����������ݺ�*/
	unsigned int m_uiShooterSN;
	/** ���һ�η��ں�Ҫʹ�õĵ�������*/
	int m_iIncrNb;
	/** ע����Ϣ����*/
	unsigned short m_usCommentsSize;
	/** ע��*/
	char* m_pcComments;
}m_oSourceExploStruct;

/**
* @struct SourceVibro_Struct
* @brief Vibro��Դ�ṹ��
*/
typedef struct SourceVibro_Struct
{
	/** ��Դ״̬*/
	unsigned int m_uiSourceStatus;
	/** ��Դ���*/
	unsigned int m_uiSourceNb;
	/** ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ*/
	char* m_pcLabel;
	/** �ɿ���Դ�����ݺ�*/
	unsigned int m_uiFleetNb;
	/** moving������ѡ��*/
	unsigned int m_uiMoving;
	/** ��������*/
	int m_iStep;
	/** Work by Acq*/
	unsigned int m_uiWorkByAcq;
	/** Cluster ���ȷ��Ҫͬʱʹ�õ�������Դ��*/
	unsigned int m_uiCluster;
	/** ע����Ϣ����*/
	unsigned short m_usCommentsSize;
	/** ע��*/
	char* m_pcComments;
}m_oSourceVibroStruct;

/**
* @struct ProcessRecord_Struct
* @brief ProcessRecord�ṹ��
*/
typedef struct ProcessRecord_Struct
{
	/** Plugѡ��*/
	unsigned int m_uiPlug;
	/** BoxTypeѡ��*/
	unsigned int m_uiBoxType;
	/** SN����*/
	unsigned int m_uiSN;
	/** ������ģʽ�м�¼����*/
	unsigned int m_uiRecordLength;
	/** �����ӳ�*/
	unsigned int m_uiRefractionDelay;
	/** TB����ʱ��*/
	unsigned int m_uiTBWindow;
	/** �ڿɿ���Դģʽ�м�¼����*/
	unsigned int m_uiListeningTime;
	/** PeakTime*/
	unsigned int m_uiPeakTime;
	/** Raw*/
	unsigned int m_uiRaw;
	/** PreStack*/
	unsigned int m_uiPreStack;
}m_oProcessRecordStruct;

/**
* @struct ProcessAux_Struct
* @brief ProcessAux�ṹ��
*/
typedef struct ProcessAux_Struct
{
	/** ���������*/
	unsigned int m_uiAuxNb;
	/** ��������Ϣ����*/
	unsigned short m_usAuxProcessingSize;
	/** ������*/
	char* m_pcAuxProcessing;
}m_oProcessAuxStruct;

/**
* @struct ProcessAcq_Struct
* @brief ProcessAcq�ṹ��
*/
typedef struct ProcessAcq_Struct
{
	/** ACQ״̬*/
	unsigned int m_uiAcqStatus;
	/** ÿ�ζ����ɼ���������*/
	unsigned int m_uiAcqNb;
	/** �ɼ�������*/
	unsigned int m_uiAcqType;
	/** ���ӷ�ʽ*/
	unsigned int m_uiSignStack;
	/** ���ģʽѡ��*/
	unsigned int m_uiOutPut;
}m_oProcessAcqStruct;

/**
* @struct ProcessType_Struct
* @brief ProcessType�ṹ��
*/
typedef struct ProcessType_Struct
{
	/** ���*/
	unsigned int m_uiProNb;
	/** ��ǩ��Ϣ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ*/
	char* m_pcLabel;
}m_oProcessTypeStruct;

/**
* @struct OperationComment_Struct
* @brief OperationComment�ṹ��
*/
typedef struct OperationComment_Struct
{
	/** ���*/
	unsigned int m_uiNb;
	/** ��ǩ��Ϣ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ*/
	char* m_pcLabel;
	/** ע����Ϣ����*/
	unsigned short m_usCommentsSize;
	/** ע��*/
	char* m_pcComments;
}m_oOperationCommentStruct;

/**
* @struct OptSetupData_Struct
* @brief ʩ���ͻ�����Ϣ�ṹ��
*/
typedef struct OptSetupData_Struct
{
	/**	Delay*/
	m_oDelayStruct m_oDelay;
	/** �ڵ����*/
	list<m_oSourceShotStruct> m_olsSourceShot;
	/** Explo��Դ�ṹ��*/
	list<m_oSourceExploStruct> m_olsExploStruct;
	/** Vibro��Դ�ṹ��*/
	list<m_oSourceVibroStruct> m_olsVibroStruct;
	/** ��������*/
	m_oProcessRecordStruct m_oProcessRecord;
	/** AppendAuxesFromDsd*/
	unsigned int m_uiAppendAux;
	/** Correl with*/
	int m_iCorrelWith;
	/** �ػص�����*/
	list<m_oProcessAuxStruct> m_olsProcessAuxStruct;
	/** Acq����*/
	list<m_oProcessAcqStruct> m_olsProcessAcqStruct;
	/** �������Ͷ���*/
	list<m_oProcessTypeStruct> m_olsProcessTypeStruct;
	/** ע�Ͷ���*/
	list<m_oOperationCommentStruct> m_olsComment;
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecCommInfo;
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;
	/** ʩ��XML�����ļ�·��*/
	string m_strOptXMLFilePath;
}m_oOptSetupDataStruct;
#endif