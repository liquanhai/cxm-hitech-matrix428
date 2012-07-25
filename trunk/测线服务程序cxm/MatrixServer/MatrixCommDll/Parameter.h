
/**
* @brief ��������
*/
/** ����SNλ��*/
#define InstrumentBytes						4
/** �����������С������SNΪ0���ʾ������*/
#define InstrumentTableWindowSize			169
/** ���Խ��λ��*/
#define TestResultBytes						1
/** ���紫�������λ��*/
#define TestDataBytes						4
/** ���ݱ������С*/
#define DataTableWindowSize					270
/** C/S���ջ�������С*/
#define CommRecBufferSize					8192000
/** C/S���ͻ�������С*/
#define CommSndBufferSize					8192000
/** C/SͨѶ�˿�*/
#define ServerClientPort					0x8330
/** ������ӵĿͻ��˸���*/
#define ListenClientMaxNum					15
/** ������ջ�������С*/
#define ServerRecBufSize					8192000
/** ������֡�ṹ����*/
#define FrameStructNumMax					5800
/** �̹߳رյĵȴ�ʱ��*/
#define CloseClientCommThreadTimes			800
/** �߳�ִ�еļ��ʱ��*/
#define ClientCommThreadWaitTime			50
/** �߳�ִ�еļ������*/
#define ClientCommThreadWaitTimes			10
/** ����֡��ʱ�ȴ�����*/
#define SndFrameWaitTimes					5
/** ����֡��෢�ʹ���*/
#define SndFrameMaxNum						5
/** �ͻ�����֤ʱ�����*/
#define ClientCheckCountNum					50
/** �ͻ��˻�Ծʱ��������*/
#define ClientActiveCountNum				50
/** ���ݴ���������С��20000վ*���ߺ�+���+����ָ���ַ����*/
#define ProcBufferSize						240000
/** ����FieldOnʱ����*/
#define FieldOnWaitForTime					120000
/**
* @brief �����ֺ�ͨѶЭ��/n
* ��ѯĳ������ͻ���ֻ�跢���кź������/n
* �������������ź��кź��ټ����������ԣ�SN��4���ֽ�)���IP��4���ֽڣ�)����ֵ����ֵ(4���ֽ�)������Խ����1���ֽڣ���/n
* ��ѯ�����б�ĳ������4���ֽڵ��кź�4���ֽڵ�������ţ�
*/

/** Ӧ������λ������Ӧ�𣬽���������б�*/
#define CmdReturnBit						(1 << 15)
/** ��������Ϊ��������*/
#define CmdTypeSet							0x01
/** ��������ΪӦ��*/
#define CmdTypeReturn						0x02
/** TCP/IP֡������*/
#define FrameSizeLimit						1400
/** ֡ͷ����*/
#define FrameHeadSize						4
/** ֡������*/
#define FrameLengthSize						2
/** ֡ͷ��Ϣ����*/
#define FrameHeadInfoSize					27
/** ֡β����*/
#define FrameTailSize						1
/** ֡��������*/
#define FrameInfoSizeLimit					(FrameSizeLimit-FrameHeadSize-FrameLengthSize-FrameHeadInfoSize-FrameTailSize)
/** ֡ͷ*/
#define FrameHead1							(char)(0xaa)
/** ֡ͷ*/
#define FrameHead2							(char)(0xa5)
/** ֡ͷ*/
#define FrameHead3							0x5a
/** ֡ͷ*/
#define FrameHead4							0x55
/** ֡β*/
#define FrameTail							(char)(0xff)
/** ֡����ִ�н��-�ȴ�ִ��*/
#define CmdResultWait						0x00
/** ֡����ִ�н��-ִ�гɹ�*/
#define CmdResultSuccess					0x01
/** ֡����ִ�н��-ִ��ʧ��*/
#define CmdResultFail						0x02
/** ֡����ִ�н��-��Ҫ��ʱִ��*/
#define CmdResultDelay						0x03
/** ֡����ִ�н��-�������Ѿ�ִ��*/
#define CmdResultDone						0x04
/** ���Խ��-�ϸ�*/
#define TestResultQualified					0x01
/** ���Խ��-���ϸ�*/
#define TestResultFailure					0x02
/** ���Խ��-������*/
#define TestResultNull						0x03
/** �ͻ��������˷�����֤��*/
#define CommCheck							"���̩���Ƽ����޹�˾"

/**
* @brief �������ͻ���ͨѶ֡�ṹ\n
* ҵ���߼������ҵ�֡ͷ��֡ͷУ�飬�ɹ��������ʧ����������֡ͷ����ȡ֡��\n
* ���ܳ��ȣ���֤������ԣ���������������֡ͷ�����ҵ�֡β������������Ȳ�\n
* ������֤֡β����ȷ���֡���ݽ���ҵ����������������֡ͷ��
*/
typedef struct CommFrame_Struct
{
	// 	/** ֡ͷ*/
	// 	char m_cFrameHead[4];
	// 	/** ��֡��֮��֡β������֡β��Ϊ֡�����ܳ��ȣ���ҪС��֡������*/
	// 	unsigned short m_usFrameLength;
	/** ֡�����֡�ʱ���������ˮ�ž���ͬ������Ϊ��ͬһ֡*/
	/** ֡�������ͣ�Ϊ1��Ϊ���Ϊ3��ΪӦ��*/
	char m_cCmdType;
	/** ֡�����֣�����֡�Ĺ���*/
	unsigned short m_usCmd;
	/** �����ʱ���*/
	unsigned int m_uiServerTimeStep;
	/** �ͻ���ʱ���*/
	unsigned int m_uiClientTimeStep;
	/** ����ˮ��*/
	unsigned int m_uiPacketIndex;
	/** ������ˮ��*/
	unsigned int m_uiCmdIndex;
	/** ��֡��*/
	unsigned int m_uiFrameNum;
	/** ֡��ţ���1��ʼ��*/
	unsigned int m_uiFrameIndex;
	/** ֡����ִ�н��*/
	char m_cResult;
	/** ֡���ݳ��� = ֡�����ܳ��� �C 2 �C 4 �C 4 �C 4 - 1��*/
	/** FieldOn�����Ӧ��4���ֽڱ����ͻ���FieldOn��Ҫ�ȴ���ʱ�䣬
	����Ϊ��λΪ0��ִ�У�����ȴ�)��*/
	unsigned short m_usFrameInfoSize;
	/** ֡����ָ�룬���Ϊ��ѯ������֡���ݵ�ǰ�����ֽڷֱ����кź������*/
	char m_pcFrameInfo[FrameInfoSizeLimit];
	// 	/** ֡β*/
	// 	char m_cFrameTail;
	/** ��ʱ����*/
	unsigned int m_uiTimeOutCount;
	/** ���ʹ�������*/
	unsigned int m_uiSndCount;
}m_oCommFrameStruct, *m_oCommFrameStructPtr;
