#pragma once

#ifdef PROGRAM_OPERATIONSERVER
#include "OperaStruct.h"
#include "FDUConfig.h"
#include "..\operationserver\OperaThread.h"
#include "ChannelList.h"
// class COperaThread;
#endif

/**
 * @class CSEGDScanTypeHeader
 * @brief ɨ������ͷ������
 *
 * SEGD��ʽ��ɨ������ͷ�����ݽṹ��
 */
class CSEGDScanTypeHeader
{
public:
	CSEGDScanTypeHeader(void);
	~CSEGDScanTypeHeader(void);
	/** ����ͨ�������*/
	BYTE	m_byChnSetNb;
	/** ����ͨ���ĵ���*/ 
	WORD	m_wChnCount;
	/** ͨ������: 1Ϊ�����(���Ƶ�����9Ϊ������;*/
	BYTE	m_byChnType;
	/** ͨ���鿪ʼʱ�䣬���ڸ���������Ϊ0,���ɼ������������ӳ�ʱ�䡣
	    2msΪ���������ȡֵӦ����ʵ�ʿ�ʼʱ���һ��*/
	WORD	m_wChnStartingTime;
	/* ͨ�������ʱ�䣬2msΪ���������ȡֵӦ����ͨ����ʼʱ����ϲ������ȵ�һ�롣*/
	WORD	m_wChnEndTime;
	/** �������ͣ�0x00δȷ����0x01ΪFDU��0x1C��ʾDSU428��0x20��VE464*/
	BYTE	m_byUnitType;
	/** �Ŵ�����,ȡֵ��1,2,4,8,16,32,64,����1��ӦSercel��g1����,4��ӦΪg2*/
	DWORD	m_dwGain;
	/** ��ֱ����(1�ֽڣ��޷��Ŷ�������)��Ĭ��Ϊ0����Ч�ĵ��Ӵ�����
	    ������⽫��������Ϊ0����ֱ������Ϊ0�����δ���ӣ���Ϊ1����
		�������ǵ��ӵĽ��(�������δ����)����Ϊ��Ч���Ӵ���*/
	BYTE	m_byVerticalStack;
public:
	/// �õ���С����ϵ��,Descale Multiplier��λ��ɨ������ͷ�ε�7��8�ֽ�
	WORD	GetDescaleMultiplier();
	/// 3dB �㴦�Ļ���˲���Ƶ��; Alias filter frequency at - 3dB point
	WORD    GetAliasFilterfrequency(DWORD dwSampleRateUS);
	/// ����˲���б��;Alias filter slope
	WORD    GetAliasFilterSlope()			{ return 370;};
	/// �ͽ��˲���Ƶ��; Low-cut filter frequency
	WORD    GetLowcutFilterFrequency()		{ return 0;};
	/// �ͽ��˲���б��,Low-cut filter slope
	WORD    GetLowcutFilterSlope()			{ return 0;};
};
/**
 * @class CSEGDExtendedHeader
 * @brief ��չͷ�����ݽṹ
 *
 * SEGD��ʽ����չͷ�����ݽṹ��
 */
class CSEGDExtendedHeader
{
public:
	CSEGDExtendedHeader();
	~CSEGDExtendedHeader();
	// ����
public:
	
	/** ��¼������*/
	DWORD	m_dwTraceCount;
	/** ����������*/
	DWORD	m_dwAuxesTraceCount;
	/** ��Ӧ���ַ������*/
	// DWORD	m_dwDeadSeisTraceCount;
	/** ��Ӧ���ַ������*/
	DWORD	m_dwLiveSeisTraceCount;

	/**��Դ����:0Ϊ����Դ��1Ϊ���壬2Ϊ�ɿ�*/
	DWORD   m_dwSourceType;
	/** �ں�*/
	DWORD	m_dwShotNb;
	/** TB����ʱ��,��Ϊ��λ*/
	float   m_fTBWindowS;
	/** �ɼ����еĵ�һ������ */
	DWORD	m_dwSpreadSFL;
	/** ���е�һ�����ռ첨��λ�ú��� */
	DWORD	m_dwSpreadSFN;
	/** �ɼ����б�� */
	DWORD	m_dwSpreadNb;
	/** �ɼ���������: 1Ϊ��ͨ���У�2Ϊ�������� */
	DWORD   m_dwSpreadType; 
	/** ���Լ�¼����Test record type:
	0 ������¼��1 Ұ��������2 Ұ�����塣3 Ұ�⴮����4 ����������
	5 �������䡣6 ��������/ ��λ��	7 ����������	8 ������ģ��
	9 �ϳɡ�	10 һ���ԣ����� CM408����11 �������塣12 Ұ����䡣
	13 ����������14 Ұ��©�硣15 Ұ����衣*/
	DWORD	m_dwTestType;
	
	/** ʱ���ź�Timebreak��΢�뵥λ */
	DWORD	m_dwConfirmationTBUS;
	/** ����ʱ��,΢��Ϊ��λ*/
	DWORD	m_dwUpholetimeUS;
	/** ��ը����ʶBlaster id */
	DWORD	m_dwBlasterID;
	/** ��ը��״̬ */
	DWORD	m_dwBlasterStatus;
	

	/** ������ʱ������ms*/
	DWORD	m_dwRefractionDelayMS;
	/** TB��T0ʱ�䣬ȷ�ϵ�TBʱ���ȥ����ʱ��,��λ΢��*/
	long	m_lTBToTStartUS;
	/** �ڲ�ʱ���źţ�ITB ָʾ; 0Ϊ�ǣ�1Ϊ��*/
	DWORD	m_dwInternalTimeBreak;
	
	
	/** Ұ���豸��Ԥ���ӣ�0Ϊ�ǣ�1Ϊ��Prestack within field units*/
	DWORD	m_dwPrestack;
	/**������������: 1 ��;2��������;3 ��ʷ;4 �ر�*/
	DWORD	m_dwNoiseEliminationType;
	/** �ͼ�¼���ٷֱȣ�0~100%; Low trace percentage*/
	DWORD	m_dwLowTracePercentage;
	/** �ͼ�¼��ֵ;0-132db; Low trace value */
	DWORD	m_dwLowTraceValue;
	/** ������Ŀ1-64; Number of windows (Div.)or Window length (Enhanced Div.) */
	DWORD	m_dwWindowLength;
	/** ��ʷ�༭���ͣ�1Ϊ���㣻2Ϊ���ã�*/
	DWORD	m_dwHistoricEditingType;
	/** ������¼���ٷֱȣ�0 ��100% �� Noisy trace percentage*/
	DWORD	m_dwNoisyTracePercentage;
	/** ��ʷ��Χ0 �� 36 dB;  Historic range */
	DWORD   m_dwHistoricRange;
	/** ��ʷ׶�γ��� 2 ��ָ��:0 �� 8;Historic taper length 2��s	exponent*/
	DWORD   m_dwExpHistoricTaperLen;
	/** �ż�ֵ����/ �仯1 = ����;2 = �仯; Threshold Hold/Var*/
	DWORD   m_dwThresholdHold;
	/**��ʷ�ż�ֵ��ʼֵ0 �� 132 dB; Historic threshold Init value*/
	DWORD	m_dwHistoricThresholdValue;
	/**��ʷ���㳤��1 �� 500 ����; Historic zeroing length*/
	DWORD	m_dwHistoricZeroingLen;
	
	
	/**��������1 �޲�����ԭʼ���ݣ�;2 ����;	3 ���Ӻ����;4 ����ǰ���;5 ԭʼ���ݣ�����;	6 ԭʼ���ݣ����Ӻ����;7 ԭʼ���ݣ�����ǰ���*/
	DWORD   m_dwProcessType;
	/** �ɼ����ͱ�,32����ֵ��128�ֽ�*/
	DWORD	m_dwAcquisitionTypeTable[32];
	/**�ż�ֵ���ͱ�32 ����ֵ��128 �ֽڣ�,Threshold type tables 32 values (128 bytes).*/
	DWORD   m_dwThresholdTypeTable[32];
	/**���Ӵ���,1~32; Stacking fold*/
	DWORD   m_dwStackingFold;
	/** ��¼����100 �� 128000 ����;Record length*/
	DWORD	m_dwRecordLength;
	/** ����ط�ֵʱ��1 �� 128000 ����; Autocorrelation peak time */
	DWORD	m_dwAutoCorrPeakTime;
	/** ��زο��źű��1 �� 100000;Correlation Pilot No. 1 to 100000.*/
	DWORD	m_dwCorrelationPilot;
	/** �ο��źų���1000 �� 128000 ���� ; Pilot length*/
	DWORD	m_dwPilotLength;
	/** ɨ�賤��1000 �� 128000 ����; Sweep length*/
	DWORD   m_dwSweepLength;
	/** �ɼ���1 �� 32; Acquisition number */
	DWORD	m_dwAcquisitionNb;

	/** ��ศ���������ֵ;Max of max, Aux*/
	float	m_fMaxAux;
	/** ����������ֵIEEE ��ʽ��������;Max of max, Seis*/
	float	m_fMaxSeis;
	/** ת�����Ӵ���1..32;Dump stacking fold*/
	DWORD	m_dwDumpStackingFold;
	/** �Ŵ���ǩASCII �ı���16 ���ַ�*/
	BYTE	m_byTapeLabel[16];
	/** �Ŵ���1 �� 9999 */
	DWORD	m_dwTapeNb;
	/** ����汾ASCII �ı���16 ���ַ�; Software version ASCII text, 16 characters.*/
	BYTE	m_bySoftwareVersion[16];
	/** ����ASCII �ı���12 ���ַ�(dd mmm yyyy)*/
	BYTE    m_byDate[12];
	/** ��Դƫ����; Source easting*/
	double	m_dbSourceEasting;
	/** ��Դ����γ�Ȳ�; Source northing*/
	double  m_dbSourceNorthing;
	/** ��Դ�߳�; Source elevation*/
	float   m_fSourceElevation;

	/** ���õĻ���ɨ��ģʽ�� 0Ϊ��;1Ϊ�� */
	DWORD   m_dwSlipSweepMode;
	/** ÿ���Ŵ����ļ���1 �� 9999*/
	DWORD   m_dwFilesPerTape;
	/** �ļ�����1 �� 9999*/
	DWORD   m_dwFileCount;
	/** �ɼ�����˵��ASCII �ı���160 ���ַ�*/
	BYTE	m_byAcquisitErrorDesc[160];
	/** �˲�������: 1 =0.8��С; 2= 0.8 ����; */
	DWORD   m_dwFilterType;
	/** ������ת��: 	0 = No; 1 = Yes.;*/
	DWORD   m_dwStackIsDumped;
	/** ���ӷ��ţ���ǰ�� 0 = ��;1 = ��;2 = ��*/
	DWORD   m_dwStackSign;
	/** ���õ� PRM ��б��У��0 = ��;1Ϊ��; PRM Tilt Correction used*/
	DWORD	m_dwPRMTiltCorrect;
	/** ������;ASCII �ı���64���ַ�; */
	BYTE	m_bySwathName[64];

	/**ʩ��ģʽbit0 = 1 Standard.bit1 = 1 Microseismic.bit2 = 1 Slip-sweep.	bit3 = 1 SQC Dump (VSR).bit4 = 1 Guidance(Navigation).*/
	DWORD	m_dwOperatingMode;
	/** �޼�¼0 = ��;1 = ��*/
	DWORD	m_dwNoLog;
	/** ����ʱ��100 �� 128000����; Listening time 100 to 128000 ms.*/
	DWORD	m_dwListeningTime;
	/** ת������0 = ����ת��;1 = ԭʼת��;2 = ����ת��;*/
	DWORD   m_dwDumpType;
	/** ���� Id; Swath ID*/
	DWORD	m_dwSwathId;
	
	/** Seismic trace offset removal is disabled; 0 = No (i.e.offset is removed);1 = Yes (Microseismic mode); Sercel 4.0�汾����*/
	DWORD   m_dwSeismicTaceOffsetRemoval;

	/**GPS time of acquisition Time Break, expressed as the	number of microseconds
	since January 6, 1980 at 0:00 a.m. UTC (signed integer).*/

};
/**
 * @class CSEGDTraceData
 * @brief ��дSEGD�ļ�
 *
 * ��дSEGD��ʽ���ļ���
 */
class CSEGDTraceHeads
{
public:
	CSEGDTraceHeads();
	~CSEGDTraceHeads();
public:
	/** ��������*/
	BYTE		m_byChnSetNb;
	/** ��¼�����*/
	DWORD		m_dwTraceNb;
	/** ��¼���༭;00:δ���б༭��02:�ɼ�ǰ�����ͣ�͡�03: �ɲɼ�ϵͳ�༭*/
	BYTE		m_byTraceEdit;

	/** ���յ���ߺ�*/
	DWORD		m_dwLineNb;
	/** ���յ��*/
	DWORD		m_dwPointNb;
	/** ���յ�����*/
	BYTE		m_byPointIndex;
	/** ����������������չ�ֶ���ͬ*/
	//DWORD dwSampleCount;
	/** �첨��SEGD����,��Line����������*/
	BYTE m_bySensorSEGDCode;

	/** ���յ�ƫ����*/
	double		m_dbPointEasting;
	/** ���յ㱱��γ��*/
	double		m_dbPointNorthing;
	/** ���յ�߳�*/
	float		m_fPointElevation;
	/** ���������ͱ��,ȡֵ1-9*/
	BYTE		m_bySensorType;

	/** ����ֵ����*/
	float		m_fResistanceMax;
	/** ����ֵ����*/
	float		m_fResistanceMin;
	/** ����ֵ*/
	float		m_fResistanceVal;
	/** ���½�ϼ첨����б�Ȱٷֱ�*/
	float		m_fTiltMax;
	/** ��б��ֵ*/
	float		m_fTiltVal;
	
	/** ��������*/
	float		m_fCapacitanceMax;
	/** ��������*/
	float		m_fCapacitanceMin;
	/** ����ֵ���ɷ���*/
	float		m_fCapacitanceVal;
	/** ��ֹ����*/
	float		m_fCutoffFreqMax;
	/** ��ֹ����*/
	float		m_fCutoffFreqMin;
	/** ��ֵֹ*/
	float		m_fCutoffFreqVal;
	/** ©�����*/
	float		m_fLeakageLimit;
	/** ©��ֵ*/
	float		m_fLeakageVal;
	
	/**�豸����, �������ͣ�1ΪFDU��0x1C��ʾDSU428 */
	// BYTE	m_byUnitType;��ɨ������ͷ�εı���˵��
	/** �豸���к�*/
	DWORD		m_dwUnitSN;
	/** ��������*/
	BYTE		m_byChannelNb;
	/** �������*/
	BYTE		m_byAssemblyType;
	/** FDU �� DSU ������к�*/
	DWORD		m_dwFDUAssemblySN;
	/**�� FDU �� DSU����е�λ�� */
	BYTE		m_byLocationInFDUAssembly;
	/** �ӵ�Ԫ����*/
	BYTE		m_bySubunitType;
	/** ���������:0 �첨��;1 ѹ���첨��*/
	BYTE		m_byChannelType;
	/** �첨��������*/

	/** ���Ƶ�Ԫ����:0x01 LCI408;0x02 LAUL408;0x03 LAUX408;0x04 LAULS408;0x05 LAUXS408;0x06 LAUL428;0x16 LRU;0x17 LAUR428;0x30 LAUX428;0x31 LCI428*/
	BYTE		m_byControlUnitType;
	/** ���Ƶ�Ԫ���к�*/
	DWORD		m_dwControlUnitSN;
	/** ���������̶�*/
	BYTE		m_byGainScale;
	/** ������˲���*/
	BYTE		m_byChannelFilter;
	/** ������������*/
	BYTE		m_byChannelDataError;
	/** ������༭״̬,1 ͣ��;2 �ɼ�/ �ش�����;3 �����༭*/
	BYTE		m_byChannelEditedStatus;
	/** �������������ת��ϵ��,������Ϊ0*/
	float		m_fChannelConversionFactor;
	/** ���������Ӵ���*/
	BYTE		m_byNumberOfStacksNoisy;
	/** �͵��Ӵ���*/
	BYTE		m_byNumberOfStacksLow;
	/** ��������ͱ�ʶ�ţ�1 = �����;9 = ������;��ɨ������ͷ�ζ�����*/
	
	/** ���������:01=ԭʼ����;	02=����������;03=��أ�������;04=��أ�������;05=��̬���;06=���������*/
	BYTE		m_byChannelProcessType;
	/** ��¼�����ֵ*/
	float		m_fTraceMaxValue;
	/** ��¼�����ʱ��,΢��*/
	DWORD		m_dwTraceMaxtime;
	/** �ڲ����*/
	DWORD		m_dwInterpolations;
	/**Seismic trace offset value(if offset removal is disabled).*/
	DWORD		m_dwSeismicTraceOffsetValue;
};
 /**
 * @class CSEGDFile
 * @brief ��дSEGD�ļ�
 *
 * ��дSEGD��ʽ���ļ���
 */
class CSEGDFile
{
public:
	CSEGDFile(void);
	~CSEGDFile(void);
// ��������
public:
	/** �ļ���� */
	DWORD			m_dwFileNumber;	
	/** �����̴��룬Ĭ��13*/
	BYTE			m_byManufacturerCode;
	/** ���������кţ�Ĭ��0*/
	WORD			m_wManufacturerSN;
	/** ÿ����¼�ĵ������������Ĭ��16,�޸ĺ��Ӧ����CSEGDScanTypeHeader�������*/
	BYTE			m_byChnSetsCount;
	/** �ⲿͷ�δ�С����Config���������ж�ȡ*/
	WORD			m_wExternalHeaderSize;

	/** ����ɨ�����������ʣ���΢��Ϊ��λ��һ��ȡֵ��250,500,1000,2000,4000 */
	DWORD			m_dwSampleRateUS;
	/** �������ȣ���msΪ��λ��ȡֵ0-128000ms */
	DWORD			m_dwRecordLenMS;
	/** ��������,ȡֵ��8Ϊ����������2Ϊ���Բ��� */
	BYTE			m_byRecordType;
	/** ��Դ���ߺţ�С�������λ */
	double			m_fSourceLine;
	/** ��Դ��ţ�С�������λ */
	double			m_fSourceNb;
	/** ��Դ������ */
	DWORD			m_dwSourcePointIndex;
	/** ��Դ��� */
	DWORD			m_dwFleetNb;
	
	/** 16��ɨ������ͷ�� */
	// CSEGDScanTypeHeader	m_ScanTypeHeader[16];
	
	/** ��չͷ������ */
	CSEGDExtendedHeader	m_ExtendedHeader;

	/** ���ڻ��ߵ���ϵͳ��Ϣ */
	CString			m_strShooterInfo;
	/** ����Config�������õ��û���Ϣ*/
	CString			m_strConfigUserInfo;
	/** ʩ�����ڵ���Դע��*/
	CString         m_strSourceComment;
	/***/
	/***/
	/***/
	/***/
	/***/
// ˽������
private:

	union DATATYPE
	{
		unsigned char   byData[4];
		unsigned long   dwData;
		         long   lData;
				 float  fData;

	}m_unionType;
	/** ������ת��ΪBCD���������,����0,1,2,3,4,5,6,7,8,9 */
	unsigned char m_byDecToBCD[10];
	
	/** SEGD�ļ�ָ�� */
	CFile*	m_pFile;
// ˽�к���
private:

	// ����������
	WORD CalcJulianDay(SYSTEMTIME* pSysTime);
	/// ɾ���ļ�ָ��
	bool CloseSEGDFile(void);
	/// ��ʼ��ASCII��BCD��ӳ���
	void    InitASCIIToBCD(void);
	/// ���ֽڷ������λ������λ������ת��
	unsigned char   ReverseChar(unsigned char   ucRegchar);
	/// �������ֽڵ�ʮ��������ת��ΪBCD���ʽ
	void  ConvertWORDToBCD(WORD wData,unsigned char* byOut);
	/// ��1���ֽڵ�ʮ��������ת��ΪBCD���ʽ
	BYTE  ConvertBYTEToBCD(BYTE byData);
	// ��С��0��С��ת��Ϊ�����ֽڵ�������ʽ
	void  ConvertLessOneFloatToWORD(double fValue,unsigned char* byOut);
	// ��С��0��С��ת��Ϊ1���ֽڵ�������ʽ
	BYTE  ConvertLessOneFloatToBYTE(double fValue);
	/// ����ɨ����
	BYTE  GetBaseScanInterval();

	// �ߵ��������ߵ�λ����λ��ǰ����λ�ں�
	void ReverseFloatToBigEndian(float fValue,BYTE* byData);
	// �ߵ������ߵ�λ����λ��ǰ����λ�ں�
	void ReverseDWORDToBigEndian(DWORD dwValue,BYTE* byData);
	// �������ֽڵ�����ת��Ϊ�ĸ��ֽڵĸ�������ʽ�����ߵ��ֽڻ���
	void Convert3ByteIntTo4ByteAntiFlt(BYTE* lpInData,BYTE* lpOutData);
	
	//////////////////////////////////////////////////////////////////////////
	/// �����������
	DWORD	GetNumberOfSamples() { return m_dwRecordLenMS*1000/m_dwSampleRateUS+1;};
// ���к���
public:
	/// д��ͷ��1
	void WriteGeneralHeader1();
	/// д��ͷ��2
	void WriteGeneralHeader2();
	/// д��ͷ��3
	void WriteGeneralHeader3();
	// дɨ������ͷ�Σ�
	void WriteScanTypeHeader(CSEGDScanTypeHeader* pScanTypeHeader);
	// д��չͷ������
	void WriteExtendedHeader();
	// д�ⲿͷ��
	void WriteExternalHeader();

	// д��ͷ����
	void WriteDemuxTraceHeader(CSEGDTraceHeads*	pTrace);
	// д��ͷ��չ1
	void WriteTraceHeaderExtension1(CSEGDTraceHeads*	pTrace);
	// д��ͷ��չ2
	void WriteTraceHeaderExtension2(CSEGDTraceHeads*	pTrace);
	// д��ͷ��չ3
	void WriteTraceHeaderExtension3(CSEGDTraceHeads*	pTrace);
	// д��ͷ��չ4
	void WriteTraceHeaderExtension4(CSEGDTraceHeads*	pTrace);
	// д��ͷ��չ5
	void WriteTraceHeaderExtension5(CSEGDTraceHeads*	pTrace);
	// д��ͷ��չ6
	void WriteTraceHeaderExtension6(CSEGDTraceHeads*	pTrace,CSEGDScanTypeHeader* pScanTypeHeader);
	// д��ͷ��չ7
	void WriteTraceHeaderExtension7(CSEGDTraceHeads*	pTrace,CSEGDScanTypeHeader* pScanTypeHeader);
	
	//
// ���к���
public:
	// �洢SEGD ���ļ�ͷ����
	void SaveSEGDHead(CSEGDScanTypeHeader* pScanTypeHeader);
	// �洢Sĳһ����ͷ��������
	void SaveSEGDTraceHead(CSEGDTraceHeads*	pTrace,CSEGDScanTypeHeader* pScanTypeHeader);

#ifdef PROGRAM_OPERATIONSERVER
	// д��չͷ������
	void	SetExtendedHeader(COperaThread* pThread,CChannelList* pChannelList);
	// �����ɨ�������вɼ����ڲɼ�����������
	void	GetScanTypeOfSpread(CShotSpread* pSpread,CDWordArray& arrAuxiG1Scantype,
		CDWordArray& arrAuxiG2Scantype,CDWordArray& arrSeisG1Scantype,CDWordArray& arrSeisG2Scantype);
	// дĳһ��������
	void    WriteAuxiTraceHeader(int nChnSetNb,int nTraceIndexInSpread,CSEGDScanTypeHeader* pScanTypeHeader,COperaThread* pThread,CChannelList* pChannelList);
	// дĳһ��������
	void    WriteSeisTraceHeader(int nChnSetNb,int nTraceIndexInSpread,CSEGDScanTypeHeader* pScanTypeHeader,COperaThread* pThread,CChannelList* pChannelList);
	// ��ĳһ��һ֡�ڲ�������д��SEGD�ļ���
	void WriteTraceDataOfAFrame(BYTE* lpInData,int nSize);
	// дĳһ������
	void	WriteTraceData(int nTraceIndexInSpread,int nTraceCountOfSpread,CFile*	pFileData);
	// �洢SEGD Rev1.0�汾���ļ�
	bool SaveSEGDRev21(CFile* pFileData,COperaThread* pThread,CChannelList* pChannelList);
#endif
};
