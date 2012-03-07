#include "StdAfx.h"
#include "FileSEGD.h"



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////CSEGDScanTypeHeader//////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
CSEGDScanTypeHeader::CSEGDScanTypeHeader(void)
{	
	/** ����ͨ�������*/
	m_byChnSetNb=0;
	/** ����ͨ���ĵ���*/ 
	m_wChnCount=0;
	/** ͨ������: CHN_NORMAL=0Ϊ�������CHN_MUTE=1Ϊ�Ƶ���CHN_AUXI = 2Ϊ������;*/
	m_byChnType=0;
	/** ͨ���鿪ʼʱ�䣬���ڸ���������Ϊ0,���ɼ������������ӳ�ʱ�䡣
	    2msΪ���������ȡֵӦ����ʵ�ʿ�ʼʱ���һ��*/
	m_wChnStartingTime=0;
	/* ͨ�������ʱ�䣬2msΪ���������ȡֵӦ����ͨ����ʼʱ����ϲ������ȵ�һ�롣*/
	m_wChnEndTime=0;
	/** �������ͣ�0x00δȷ����0x01ΪFDU��0x1C��ʾDSU428��0x20��VE464*/
	m_byUnitType=1;
	/** �Ŵ�����,ȡֵ��1,2,4,8,16,32,64,����1��ӦSercel��g1����,4��ӦΪg2*/
	m_dwGain=1;
	/** ��ֱ����(1�ֽڣ��޷��Ŷ�������)��Ĭ��Ϊ0����Ч�ĵ��Ӵ�����
	    ������⽫��������Ϊ0����ֱ������Ϊ0�����δ���ӣ���Ϊ1����
		�������ǵ��ӵĽ��(�������δ����)����Ϊ��Ч���Ӵ���*/
	m_byVerticalStack=0;
}
CSEGDScanTypeHeader::~CSEGDScanTypeHeader(void)
{

}
/// �õ���С����ϵ��,Descale Multiplier��λ��ɨ������ͷ�ε�7��8�ֽ�
WORD	CSEGDScanTypeHeader::GetDescaleMultiplier()
{
	if(m_byUnitType==2)
	{
		return 0xAF6D;
	}
	else if(m_byUnitType==1)
	{
		if(m_dwGain==1)
			return 0xAF6D;
		if(m_dwGain==4)
			return 0xB76D;
	}
	return 0x8000;
}
/// 3dB �㴦�Ļ���˲���Ƶ��; Alias filter frequency at - 3dB point
WORD    CSEGDScanTypeHeader::GetAliasFilterfrequency(DWORD dwSampleRateUS)
{
	switch(dwSampleRateUS)
	{
	case 250:		// 
		return 1600;
		break;
	case 500:
		return 800;
		break;
	case 1000:
		return 400;
		break;
	case 2000:
		return 200;
		break;
	case 4000:
		return 100;
		break;
	default:
		return 400;
		break;
	}	
	return 400;	
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////CSEGDExtendedHeader///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
CSEGDExtendedHeader::CSEGDExtendedHeader()
{
	/** ��¼������*/
	m_dwTraceCount=0;
	/** ����������*/
	m_dwAuxesTraceCount=0;
	/** ��Ӧ���ַ������*/
	//m_dwDeadSeisTraceCount=0;
	/** ��Ӧ���ַ������*/
	m_dwLiveSeisTraceCount=0;

	/**��Դ����:0Ϊ����Դ��1Ϊ���壬2Ϊ�ɿ�*/
	m_dwSourceType=1;
	/** �ں�*/
	m_dwShotNb=0;
	/** TB����ʱ��*/
	m_fTBWindowS=1.0f;
	/** �ɼ����еĵ�һ������ */
	m_dwSpreadSFL =1;
	/** ���е�һ�����ռ첨��λ�ú��� */
	m_dwSpreadSFN=0;
	/** �ɼ����б�� */
	m_dwSpreadNb=0;
	/** �ɼ���������: 1Ϊ��ͨ���У�2Ϊ�������� */
	m_dwSpreadType=2; 
	/** ���Լ�¼����Test record type:
	0 ������¼��1 Ұ��������2 Ұ�����塣3 Ұ�⴮����4 ����������
	5 �������䡣6 ��������/ ��λ��	7 ����������	8 ������ģ��
	9 �ϳɡ�	10 һ���ԣ����� CM408����11 �������塣12 Ұ����䡣
	13 ����������14 Ұ��©�硣15 Ұ����衣*/
	m_dwTestType=0;
	
	/** ʱ���ź�Timebreak��΢�뵥λ */
	m_dwConfirmationTBUS=0;
	/** ����ʱ��,΢��Ϊ��λ*/
	m_dwUpholetimeUS=0;
	/** ��ը����ʶBlaster id */
	m_dwBlasterID=1;
	/** ��ը��״̬ */
	m_dwBlasterStatus=1;
	

	/**������ʱ������ms*/
	m_dwRefractionDelayMS=0;
	/**TB��T0ʱ�䣬ȷ�ϵ�TBʱ���ȥ����ʱ��,��λ΢��*/
	m_lTBToTStartUS = 0;
	/**�ڲ�ʱ���źţ�ITB ָʾ; 0Ϊ�ǣ�1Ϊ��*/
	m_dwInternalTimeBreak=1;
	
	
	/** Ұ���豸��Ԥ���ӣ�0Ϊ�ǣ�1Ϊ��Prestack within field units*/
	m_dwPrestack=1;
	/**������������: 1 ��;2��������;3 ��ʷ;4 �ر�*/
	m_dwNoiseEliminationType=1;
	/** �ͼ�¼���ٷֱȣ�0~100%; Low trace percentage*/
	m_dwLowTracePercentage=0;
	/** �ͼ�¼��ֵ;0-132db; Low trace value */
	m_dwLowTraceValue=0;
	/** ������Ŀ1-64; Number of windows (Div.)or Window length (Enhanced Div.) */
	m_dwWindowLength=1;
	/** ��ʷ�༭���ͣ�1Ϊ���㣻2Ϊ���ã�*/
	m_dwHistoricEditingType=1;
	/** ������¼���ٷֱȣ�0 ��100% �� Noisy trace percentage*/
	m_dwNoisyTracePercentage=0;
	/** ��ʷ��Χ0 �� 36 dB;  Historic range */
	m_dwHistoricRange=0;
	/** ��ʷ׶�γ��� 2 ��ָ��:0 �� 8;Historic taper length 2��s	exponent*/
	m_dwExpHistoricTaperLen=0;
	/** �ż�ֵ����/ �仯1 = ����;2 = �仯; Threshold Hold/Var*/
	m_dwThresholdHold=1;
	/**��ʷ�ż�ֵ��ʼֵ0 �� 132 dB; Historic threshold Init value*/
	m_dwHistoricThresholdValue=0;
	/**��ʷ���㳤��1 �� 500 ����; Historic zeroing length*/
	m_dwHistoricZeroingLen=1;
	
	
	/**��������1 �޲�����ԭʼ���ݣ�;2 ����;	3 ���Ӻ����;4 ����ǰ���;5 ԭʼ���ݣ�����;	6 ԭʼ���ݣ����Ӻ����;7 ԭʼ���ݣ�����ǰ���*/
	m_dwProcessType=1;
	/** �ɼ����ͱ�,32����ֵ��128�ֽ�*/
	// m_dwAcquisitionTypeTable[32];
	memset(m_dwAcquisitionTypeTable,0,128);
	/**�ż�ֵ���ͱ�32 ����ֵ��128 �ֽڣ�,Threshold type tables 32 values (128 bytes).*/
	// m_dwThresholdTypeTable[32];
	memset(m_dwThresholdTypeTable,0,128);
	/**���Ӵ���,1~32; Stacking fold*/
	m_dwStackingFold=1;
	/** ��¼����100 �� 128000 ����;Record length*/
	m_dwRecordLength=1000;
	/** ����ط�ֵʱ��1 �� 128000 ����; Autocorrelation peak time */
	m_dwAutoCorrPeakTime=1;
	/** ��زο��źű��1 �� 100000;Correlation Pilot No. 1 to 100000.*/
	m_dwCorrelationPilot=1;
	/** �ο��źų���1000 �� 128000 ���� ; Pilot length*/
	m_dwPilotLength=1000;
	/** ɨ�賤��1000 �� 128000 ����; Sweep length*/
	m_dwSweepLength=1000;
	/** �ɼ���1 �� 32; Acquisition number */
	m_dwAcquisitionNb=1;
	/** ��ศ���������ֵ;Max of max, Aux*/
	m_fMaxAux=0;
	/** ����������ֵIEEE ��ʽ��������;Max of max, Seis*/
	m_fMaxSeis=0;
	/** ת�����Ӵ���1..32;Dump stacking fold*/
	m_dwDumpStackingFold=1;
	/** �Ŵ���ǩASCII �ı���16 ���ַ�*/
	// m_byTapeLabel[16];
	memset(m_byTapeLabel,0,16);
	/** �Ŵ���1 �� 9999 */
	m_dwTapeNb=1;
	/** ����汾ASCII �ı���16 ���ַ�; Software version ASCII text, 16 characters.*/
	//m_bySoftwareVersion[16];
	strcpy_s((char*)m_bySoftwareVersion,16,"1.0");
	/** ����ASCII �ı���12 ���ַ�(dd mmm yyyy)*/
	//m_byDate[12];
	strcpy_s((char*)m_bySoftwareVersion,12,"01  01 2011");
	/** ��Դƫ����; Source easting*/
	m_dbSourceEasting=0;
	/** ��Դ����γ�Ȳ�; Source northing*/
	m_dbSourceNorthing=0;
	/** ��Դ�߳�; Source elevation*/
	m_fSourceElevation=0;
	/** ���õĻ���ɨ��ģʽ�� 0Ϊ��;1Ϊ�� */
	m_dwSlipSweepMode=0;
	/** ÿ���Ŵ����ļ���1 �� 9999*/
	m_dwFilesPerTape=1;
	/** �ļ�����1 �� 9999*/
	m_dwFileCount=1;
	/** �ɼ�����˵��ASCII �ı���160 ���ַ�*/
	//m_byAcquisitErrorDesc[160];
	memset(m_byAcquisitErrorDesc,0,160);
	/** �˲�������: 1 =0.8��С; 2= 0.8 ����; */
	m_dwFilterType=1;
	/** ������ת��: 	0 = No; 1 = Yes.;*/
	m_dwStackIsDumped=0;
	/** ���ӷ��ţ���ǰ�� 0 = ��;1 = ��;2 = ��*/
	m_dwStackSign=0;
	/** ���õ� PRM ��б��У��0 = ��;1Ϊ��; PRM Tilt Correction used*/
	m_dwPRMTiltCorrect=0;
	/** ������;ASCII �ı���64���ַ�; */
	//m_bySwathName[64];
	strcpy_s((char*)m_bySwathName,64,"SW1");
	/**ʩ��ģʽbit0 = 1 Standard.bit1 = 1 Microseismic.bit2 = 1 Slip-sweep.	bit3 = 1 SQC Dump (VSR).bit4 = 1 Guidance(Navigation).*/
	m_dwOperatingMode=1;
	/** �޼�¼0 = ��;1 = ��*/
	m_dwNoLog=0;
	/** ����ʱ��100 �� 128000����; Listening time 100 to 128000 ms.*/
	m_dwListeningTime=1000;
	/** ת������0 = ����ת��;1 = ԭʼת��;2 = ����ת��;*/
	m_dwDumpType=0;
	/** ���� Id; Swath ID*/
	m_dwSwathId=1;
	
	/** Seismic trace offset removal is disabled; 0 = No (i.e.offset is removed);1 = Yes (Microseismic mode); Sercel 4.0�汾����*/
	m_dwSeismicTaceOffsetRemoval=0;
}
CSEGDExtendedHeader::~CSEGDExtendedHeader()
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////CSEGDTraceHeads///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
CSEGDTraceHeads::CSEGDTraceHeads()
{
	/** ��������*/
	m_byChnSetNb=1;
	/** ��¼�����*/
	m_dwTraceNb=1;
	/** ��¼���༭;00:δ���б༭��02:�ɼ�ǰ�����ͣ�͡�03: �ɲɼ�ϵͳ�༭*/
	m_byTraceEdit=0;

	/** ���յ���ߺ�*/
	m_dwLineNb=1;
	/** ���յ��*/
	m_dwPointNb=0;
	/** ���յ�����*/
	m_byPointIndex=1;
	/** ��������������*/
	//DWORD dwSampleCount;
	/** �첨��SEGD����,��Line����������*/
	m_bySensorSEGDCode=0;

	/** ���յ�ƫ����*/
	m_dbPointEasting=0;
	/** ���յ㱱��γ��*/
	m_dbPointNorthing=0;
	/** ���յ�߳�*/
	m_fPointElevation=0;
	/** ���������ͱ��*/
	m_bySensorType=1;

	/** ����ֵ����*/
	m_fResistanceMax=10000;
	/** ����ֵ����*/
	m_fResistanceMin=0;
	/** ����ֵ*/
	m_fResistanceVal=0;
	/** ���½�ϼ첨����б�Ȱٷֱ�*/
	m_fTiltMax=0;
	/** ��б��ֵ*/
	m_fTiltVal=0;

	/** ��������*/
	m_fCapacitanceMax=10;
	/** ��������*/
	m_fCapacitanceMin=0;
	/** ����ֵ���ɷ���*/
	m_fCapacitanceVal=0;
	/** ��ֹ����*/
	m_fCutoffFreqMax=0;
	/** ��ֹ����*/
	m_fCutoffFreqMin=0;
	/** ��ֵֹ*/
	m_fCutoffFreqVal=0;
	/** ©�����*/
	m_fLeakageLimit=100;
	/** ©��ֵ*/
	m_fLeakageVal=10000;

	/**�豸����, �������ͣ�1ΪFDU��0x1C��ʾDSU428 */
	// BYTE	m_byUnitType;��ɨ������ͷ�εı���˵��
	/** �豸���к�*/
	m_dwUnitSN=0;
	/** ��������*/
	m_byChannelNb=0;
	/**�������*/
	m_byAssemblyType=1;
	/** FDU �� DSU ������к�*/
	m_dwFDUAssemblySN=0;
	m_byLocationInFDUAssembly = 0;
	/** �ӵ�Ԫ����*/
	m_bySubunitType=0x01;
	/** ���������:0 �첨��;1 ѹ���첨��*/
	m_byChannelType=0;
	/** �첨��������*/

	/** ���Ƶ�Ԫ����:0x01 LCI408;0x02 LAUL408;0x03 LAUX408;0x04 LAULS408;0x05 LAUXS408;0x06 LAUL428;0x16 LRU;0x17 LAUR428;0x30 LAUX428;0x31 LCI428*/
	m_byControlUnitType=0x01;
	/** ���Ƶ�Ԫ���к�*/
	m_dwControlUnitSN=0;
	/** ���������̶�*/
	m_byGainScale=1;
	/** ������˲���*/
	m_byChannelFilter=1;
	/** ������������*/
	m_byChannelDataError=0;
	/** ������༭״̬,1 ͣ��;2 �ɼ�/ �ش�����;3 �����༭*/
	m_byChannelEditedStatus=1;
	/** �������������ת��ϵ��,������Ϊ0*/
	m_fChannelConversionFactor=0;
	/** ���������Ӵ���*/
	m_byNumberOfStacksNoisy=0;
	/** �͵��Ӵ���*/
	m_byNumberOfStacksLow=0;
	/** ��������ͱ�ʶ�ţ�1 = �����;9 = ������;��ɨ������ͷ�ζ�����*/

	/** ���������:01=ԭʼ����;	02=����������;03=��أ�������;04=��أ�������;05=��̬���;06=���������*/
	m_byChannelProcessType=01;
	/** ��¼�����ֵ*/
	m_fTraceMaxValue=0;
	/** ��¼�����ʱ��,΢��*/
	m_dwTraceMaxtime=0;
	/** �ڲ����*/
	m_dwInterpolations=0;
	/**Seismic trace offset value(if offset removal is disabled).*/
	m_dwSeismicTraceOffsetValue=0;
}
CSEGDTraceHeads::~CSEGDTraceHeads()
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////   CSEGDFile   ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief CSEGDFile���캯��
 * @note  CSEGDFile���캯��
 * @param  void
 * @return void
 */
CSEGDFile::CSEGDFile(void)
: m_pFile(NULL)
{
	InitASCIIToBCD();
	m_dwFileNumber = 800;
	m_dwSampleRateUS = 1000;
	m_dwRecordLenMS = 10000;
	m_byRecordType = 8;
	m_dwSourcePointIndex = 1;
	m_dwFleetNb = 1;

	m_byManufacturerCode=13;
	m_wManufacturerSN=0;
	m_byChnSetsCount=16;
	m_wExternalHeaderSize = 1024;

	
	m_strShooterInfo = _T("");
	/** ����Config�������õ��û���Ϣ*/
	m_strConfigUserInfo = _T("");
	/** ʩ�����ڵ���Դע��*/
	m_strSourceComment = _T("");
}
/**
 * @brief CSEGDFile��������
 * @note  CSEGDFile��������
 * @param  void
 * @return void
 */
CSEGDFile::~CSEGDFile(void)
{
	if(m_pFile)
	{
		m_pFile->Flush();
		m_pFile->Close();
		delete m_pFile;
		m_pFile=NULL;
	}
}
/**
 * @brief �ر�SEGD�ļ���ɾ������
 * @note  �ر�SEGD�ļ���ɾ������
 * @param  void
 * @return void
 */
bool CSEGDFile::CloseSEGDFile(void)
{
	try
	{
		if(m_pFile)
		{
			m_pFile->Flush();
			m_pFile->Close();
			delete m_pFile;
			m_pFile=NULL;
		}
	}
	catch (CFileException* )
	{
		return false;
	}
	return true;	
}
/**
 * @brief ʮ��������ת��ΪBCD��
 * @note  ʮ��������ת��ΪBCD��
 * @param  void
 * @return void
 */
void    CSEGDFile::InitASCIIToBCD(void)
{	
	BYTE byData[10];
	m_unionType.lData = -0x12345678;
	byData[0]= m_unionType.byData[2];	// ��չ�ļ�������λ
	byData[1]= m_unionType.byData[1];	
	byData[2]= m_unionType.byData[0];	// ��չ�ļ�������λ
	byData[3]= 0;

	m_byDecToBCD[0] = 0;
	m_byDecToBCD[1] = 0x01;
	m_byDecToBCD[2] = 0x02;
	m_byDecToBCD[3] = 0x03;
	m_byDecToBCD[4] = 0x04;
	m_byDecToBCD[5] = 0x05;
	m_byDecToBCD[6] = 0x06;
	m_byDecToBCD[7] = 0x07;
	m_byDecToBCD[8] = 0x08;
	m_byDecToBCD[9] = 0x09;
}
/**
 * @brief �ֽڰ�λ����
 * @note  ���ֽڷ������λ������λ������ת����������01001001�������Ϊ10010010
 * @param  unsigned char   ucRegchar
 * @return unsigned char,������
 */
unsigned char   CSEGDFile::ReverseChar(unsigned char   ucRegchar) 
{ 
	unsigned char   ucTemp   = 0; 
	unsigned char   ucResult = 0; 
	int   i; 

	for(i=0;i<8;i++) 
	{
		ucTemp = ucRegchar >> (7-i); 
		ucResult |= (ucTemp & (unsigned char)0x1) << i; 
	} 
	return   ucResult; 
} 
/**
 * @brief ���ֽ�����ת��ΪBCD��
 * @note  �����ֽ�����ת��ΪBCD�룻��Ҫ���иߵ�λ��������λ�ڵ�һ���ֽڣ������λλ�ڵ�һ���ֽڵ�0λ��
 * @param  WORD wData,С�ڻ��ߵ���9999
 * @param  unsigned char* byData�������ĸ��ֽڵ�BCD�룬��λ��ǰ�������λλ�ڵ�һ���ֽڵ�0λ��
 * @return void
 */
BYTE CSEGDFile::ConvertBYTEToBCD(BYTE byData)
{
	BYTE  byTemp,byRet;
	byTemp = byData/10;
	byRet = m_byDecToBCD[byTemp];
	byTemp = byData%10;
	byRet = byRet << 4;
	byRet |= m_byDecToBCD[byTemp];
	// byRet = ReverseChar(byRet);
	return byRet;
}
/**
 * @brief ��������9999������ת��ΪBCD��
 * @note  ��������9999������ת��ΪBCD�룻��Ҫ���иߵ�λ��������λ�ڵ�һ���ֽڣ������λλ�ڵ�һ���ֽڵ�0λ��
 * @param  WORD wData,С�ڻ��ߵ���9999
 * @param  unsigned char* byOut���������������2���ֽڵĿռ䣬����BCD�룬��λ��ǰ�������λλ�ڵ�һ���ֽڵ�0λ��
 * @return void
 */
void  CSEGDFile::ConvertWORDToBCD(WORD wData,unsigned char* byOut)
{
	WORD    wTemp;
	BYTE	byData[4];
	if(!byOut || wData>9999)
		return ;
	// �������λ
	wTemp = wData/1000;
	byData[0] = m_byDecToBCD[wTemp]; 
	wData -=wTemp*1000;
	wTemp = wData/100;
	byData[1] =  m_byDecToBCD[wTemp];
	wData -=wTemp*100;
	wTemp = wData/10;
	byData[2] =  m_byDecToBCD[wTemp]; 	
	wTemp = wData%10;
	byData[3] =  m_byDecToBCD[wTemp];

	byData[0]=byData[0]<<4;
	byData[0]|=byData[1];
	//byOut[0] = ReverseChar(byData[0]);
	byOut[0] = byData[0];
	
	byData[2]=byData[2]<<4;
	byData[2]|=byData[3];
	// byOut[1] = ReverseChar(byData[2]);
	byOut[1] = byData[2];
	
	//wTemp = MAKEWORD(byData[1],byData[3]);	
	return ;
}

/**
 * @brief ����������
 * @note  ���������ռ������ڵ������գ����������ͨͷ��1 ��12��13�ֽ�
          ���������յļ��㹫ʽ��

	      ���ڵ������� N �������¹�ʽ�ó���N = INT(275*M/9) - K*INT((M+9)/12) + D - 30 

		  �˴� M Ϊ�·ݣ�DΪ�������ڣ����� K = 1��ƽ�� K = 2 Nȡ��������1��1�տ�ʼȡֵ1��ֱ��12��31��ȡֵ365��������ȡֵ366����

		  �� 7.f 1978��11��14�ա� 

		  ƽ�� K=2��M = 11, D = 14, K = 2���� N = 318

		  �� 7.g 1988��4��22�ա� 

		  ���� K=1�� M = 4�� D = 22��K = 1���� N = 113. 

		  ���������ǿ��������⣺ ����������N��֪��Ҫ����Ӧ�����ڣ�MΪ�·ݣ�DΪ�������ڡ�

		  ������㷨���ɱ���ʱ�������Э���A. Pouplier���ֵġ� 

		  ������������K = 1 ��Ϊ����K = 2 ��Ϊƽ��M = INT(9(K+N)/275+0.98)��

		  �� N < 32������ M = 1D = N �C INT(275M/9) + K*INT((M+9)/12) + 30 

 * @param  SYSTEMTIME* pSysTime����ǰʱ��
 * @return �����ֽ����ڵ�������
 */
WORD CSEGDFile::CalcJulianDay(SYSTEMTIME* pSysTime)
{
	WORD   wResult;
	if(!pSysTime)
		return 0;
	int nLeapYear = 2;
	wResult = pSysTime->wYear;
	// �ж��Ƿ�Ϊ���꣬���Ϊ���꣬nLeapYear = 1
	if((wResult%4==0) && (wResult%100!=0))
	{
		nLeapYear = 1;
	}
	if (wResult%400 == 0)
	{
		nLeapYear =1;
	}

	wResult = 275*pSysTime->wMonth/9 - nLeapYear*((pSysTime->wMonth+9)/12)+pSysTime->wDay-30;
	return wResult;

}
/**
 * @brief ת������ɨ����ΪSEGDҪ���ʽ
 * @note  ת������ɨ����ΪSEGDҪ���ʽ
 * @param  float fSample
 * @return void
 */
BYTE  CSEGDFile::GetBaseScanInterval()
{
	switch(m_dwSampleRateUS)
	{
	case 250:
		return 4;
		break;
	case 500:
		return 8;
		break;
	case 1000:
		return 10;
		break;
	case 2000:
		return 20;
		break;
	case 4000:
		return 40;
		break;
	default:
		return 10;
		break;
	}
}

/**
 * @brief ��С��1�ĸ�����ת��Ϊ16λ�ı�ʾ����
 * @note ��С��1�ĸ�����ת��Ϊ16λ�ı�ʾ���������Ϊ�����ֽڣ�byOut[0]Ϊ��λ��byOut[1]Ϊ��λ
 * @param  
 * @return void
 */
void CSEGDFile::ConvertLessOneFloatToWORD(double fValue,unsigned char* byOut)
{
	int i;
	unsigned long dwTemp=0;
	unsigned long dwRet=0;
	for(i=0;i<16;i++)
	{
		fValue*=2;
		dwRet = dwRet<<1;
		dwTemp = (unsigned long)fValue;
		dwRet |=dwTemp;
		fValue -=dwTemp;		
	}
	byOut[0] = HIBYTE(dwRet);
	byOut[1] = LOBYTE(dwRet);
}

/**
 * @brief ��С��1��С��ת��Ϊ1���ֽڵ�������ʽ
 * @note ��С��1�ĸ�����ת��Ϊ1���ֽڵı�ʾ����:T-1,T-2,T-3,T-4,T-5,T-6,T-7,T-8
 * @param  
 * @return BYTE
 */
BYTE  CSEGDFile::ConvertLessOneFloatToBYTE(double fValue)
{
	int i;
	BYTE byTemp=0;
	BYTE byRet=0;
	for(i=0;i<16;i++)
	{
		fValue*=2;
		byRet = byRet<<1;
		byTemp = (BYTE)fValue;
		byRet |=byTemp;
		fValue -=byTemp;		
	}
	return byRet;
}
/**
 * @brief  ���ļ���д����ͷ�����ݿ�1
 * @note   ����SEGD2.1�ĸ�ʽд����ͷ��1������Ϊ32�ֽ�
 * @param  void
 * @return void
 */
void CSEGDFile::WriteGeneralHeader1( )
{
	unsigned char byData[32];
	WORD  wTemp;
	// 1-2�ֽڣ��ļ����
	if(m_dwFileNumber>9999)
	{
		byData[0] = 0xFF;
		byData[1] = 0xFF;
	}
	else
	{
		ConvertWORDToBCD(WORD(m_dwFileNumber),byData);
	}
	// 3-4�ֽڣ������ʽ���룬32λIEEE
	ConvertWORDToBCD(8058,byData+2);
	// 5-10�ֽڣ���ͨ����
	memset(byData+4,0,6);
	byData[9] = 0x05;		// ??????? 428XL��ӦΪ5��û������
	// 11�ֽڣ���ݵ������λ����0-99��
	SYSTEMTIME	sysTime;
	GetLocalTime(&sysTime);
	byData[11] = sysTime.wYear%100;
	byData[10] = ConvertBYTEToBCD(byData[11]);

	// 12H��ȡֵ2����ʾ���ӵĿ���
	// 12L-13�ֽڣ�Julia�գ������գ���3λ��(0-366)
	wTemp = CalcJulianDay(&sysTime);
	wTemp = wTemp + 2000;
	ConvertWORDToBCD(wTemp,byData+11);
	// 14�ֽڣ�һ���е�Сʱ(0-23)
	byData[14] = (BYTE)sysTime.wHour;
    byData[13]=ConvertBYTEToBCD(byData[14]);

	// 15�ֽڣ�һ���еķ���(0-59)
	byData[15] = (BYTE)sysTime.wMinute;
	byData[14]=ConvertBYTEToBCD(byData[15]);

	// 16�ֽڣ�һ���еķ���(0-59)
	byData[16] = (BYTE)sysTime.wSecond;
	byData[15]=ConvertBYTEToBCD(byData[16]);

	// 17�ֽڣ������̴���,Sercel��˾Ϊ13,
	byData[16] = ConvertBYTEToBCD(m_byManufacturerCode);
	// 18-19�ֽڣ����������к�
	ConvertWORDToBCD(m_wManufacturerSN,byData+17);	
	// 20-22�ֽڣ�SEGD��׼δ��
	byData[19] = 0;
	byData[20] = 0;
	byData[21] = 0;
	// 23�ֽڣ�����ɨ����
	byData[22] = GetBaseScanInterval();
	byData[22]=ConvertBYTEToBCD(byData[22]);
	// 24H���Բ��ԣ�24L-25δ�ã������ֽھ�Ϊ0
	byData[23] = 0;
	byData[24] = 0;
	// 26H����¼���ͣ�8Ϊ����
	byData[25] = ConvertBYTEToBCD(m_byRecordType)<<4;
	// 26L-27����¼���ȣ�ʹ����չ��¼����Ϊ0xFFF;
	byData[25]|= 0x0F;
	byData[26] = 0xFF;
	// 28�ֽڣ�ÿ����¼��ɨ��������
	byData[27] = 1;
	// 29�ֽڣ�ÿ��ɨ������ͨ��������16
	byData[28] = ConvertBYTEToBCD(m_byChnSetsCount);
	// 30�ֽڣ�����ʱƫͷ�ˣ�0
	byData[29] = 0;
	// 31�ֽڣ���չͷ�˳��ȣ�32*32=1024
	byData[30] = ConvertBYTEToBCD(32);
	// 32�ֽڣ��ⲿͷ�˳��ȣ�32*32=1024
	if(m_wExternalHeaderSize>99*32)
		byData[31] = 0xFF;
	else
		byData[31] = ConvertBYTEToBCD(BYTE(m_wExternalHeaderSize/32));
	// byData[31] = 0;

	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д����ͷ�����ݿ�2
 * @note  ����SEGD2.1�ĸ�ʽд����ͷ��2������Ϊ32�ֽ�
 * @param  
 * @return void
 */
void CSEGDFile::WriteGeneralHeader2()
{
	unsigned char  byData[32];
	WORD           wTemp;
	// 1-3�ֽڣ��ļ����,4-5�ֽ�Ϊɨ�����ͣ�δʹ��Ϊ0
	if(m_dwFileNumber<=9999)
	{
		byData[0] = 0x00;
		byData[1] = 0x00;
		byData[2] = 0x00;
		byData[3] = 0x00;
	}
	else
	{	
		m_unionType.dwData = m_dwFileNumber;
		byData[0]= m_unionType.byData[2];	// ��չ�ļ�������λ
		byData[1]= m_unionType.byData[1];	
		byData[2]= m_unionType.byData[0];	// ��չ�ļ�������λ
		byData[3]= 0;
		
	}
	byData[4] = 0x00;

	// 6-7�ֽ�Ϊ��չͷ�����ݿ飨δʹ�ã�
	byData[5] = 0x00;
	byData[6] = 0x00;
	// 8-9�ֽ�Ϊ�ⲿͷ�����ݿ�
	if(m_wExternalHeaderSize<=99*32)
	{
		byData[7] = 0x00;
		byData[8] = 0x00;
	}
	else
	{
		wTemp = m_wExternalHeaderSize/32;
		byData[7] = HIBYTE(wTemp);
		byData[8] = LOBYTE(wTemp);
	}	
	// 10�ֽ�δʹ��
	byData[9] = 0x00;
	// 11-12�ֽڣ�bin,SEGD�汾, ����rev2.1��׼дΪ2.0
	byData[10] = 0x02;
	byData[11] = 0x00;
	// 13-14�ֽڣ���ͨβ��
	byData[12] = 0x00;
	byData[13] = 0x00;
	// 15-17�ֽڣ�bin��չ��¼���ȣ�0-128000ms
	m_unionType.dwData = m_dwRecordLenMS;
	byData[14] = m_unionType.byData[2];	// ���λ
	byData[15] = m_unionType.byData[1];
	byData[16] = m_unionType.byData[0];	// ���λ
	// 18�ֽڣ�δʹ��
	byData[17] = 0;
	// 19�ֽڣ���ͷ���ţ�Ϊ2������ͷ��
	byData[18] = 2;
	// 20-32δʹ��
	memset(byData+19,0,13);

	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д����ͷ�����ݿ�3
 * @note  ����SEGD2.1�ĸ�ʽд����ͷ��3������Ϊ32�ֽ�
 * @param  DWORD dwFileNumber,double fSourceLine,double fSourceNb,DWORD dwSourcePointIndex,DWORD dwSwathNb
 * @return void
 */
void CSEGDFile::WriteGeneralHeader3()
{
	unsigned char  byData[32];
	// 1-3�ֽڣ���չ�ļ����
	if(m_dwFileNumber<=9999)
	{
		byData[0] = 0x00;
		byData[1] = 0x00;
		byData[2] = 0x00;
	}
	else
	{	
		m_unionType.dwData = m_dwFileNumber;
		byData[0]= m_unionType.byData[2];	// ��չ�ļ�������λ
		byData[1]= m_unionType.byData[1];	
		byData[2]= m_unionType.byData[0];	// ��չ�ļ�������λ
	}
	// 4-8�ֽڣ���Դ���ߺţ�0-99999.99��������4-6Ϊ�������֣�3�ֽڣ�2�Ĳ��룩,7-8С������
	m_unionType.lData = (long)m_fSourceLine;
	byData[3]= m_unionType.byData[2];	// ��չ�ļ�������λ
	byData[4]= m_unionType.byData[1];	
	byData[5]= m_unionType.byData[0];	// ��չ�ļ�������λ
	ConvertLessOneFloatToWORD(m_fSourceLine-m_unionType.lData,byData+6);
	// 9-13�ֽڣ���Դ��ţ�0-99999.99��������9-11Ϊ�������֣�3�ֽڣ�2�Ĳ��룩,12-13С������
	m_unionType.lData = (long)m_fSourceNb;
	byData[8]= m_unionType.byData[2];	// ��չ�ļ�������λ
	byData[9]= m_unionType.byData[1];	
	byData[10]= m_unionType.byData[0];	// ��չ�ļ�������λ
	ConvertLessOneFloatToWORD(m_fSourceNb-m_unionType.lData,byData+11);
	// 14�ֽڣ���Դ����������Դ���ƶ�����(1-9)
	byData[13] = (unsigned char)m_dwSourcePointIndex;		
	// 15�ֽڣ���λ����(δ��¼)
	byData[14]=0;
	// 16�ֽڣ��ɿ���Դ����(δ��¼)
	byData[15]=0;
	// 17-18�ֽڣ���λ��(δ��¼)
	byData[16]=0;
	byData[17]=0;
	// 19�ֽڣ���ͷ�α��
	byData[18] = 3;
	// 20�ֽڣ���Դ���
	byData[19] = (unsigned char)m_dwFleetNb;		// ??????????????�����ڵ��SwathNb
	// 21-32δʹ��
	memset(byData+20,0,12);

	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д��һ��ɨ������ͷ�εĵ������
 * @note  ����SEGD2.1�ĸ�ʽд��һ��ɨ������ͷ�εĵ�����飬����Ϊ32�ֽ�;
          ��������һ��ɨ������ͷ�����ж��������顣
 * @param  
 * @param  
 * @return void
 */
void CSEGDFile::WriteScanTypeHeader(CSEGDScanTypeHeader* pScanTypeHeader)
{
	unsigned char  byData[32];
	memset(byData,0,32);
	if(!pScanTypeHeader)
	{
		if(m_pFile)
		{
			m_pFile->Write(byData,32);
		}
		return;
	}
	WORD  wTemp;
	// 1�ֽڣ�ɨ������ͷ�α�ţ�ֻ��һ����ȡֵ01
	byData[0] = 0x01;
	// 2�ֽڣ������ͨ�����
	byData[1] = ConvertBYTEToBCD(pScanTypeHeader->m_byChnSetNb);
	// 3-4�ֽڣ�ͨ���鿪ʼʱ�䣬2msΪ������0-131070ms
	byData[2] = HIBYTE(pScanTypeHeader->m_wChnStartingTime);
	byData[3] = LOBYTE(pScanTypeHeader->m_wChnStartingTime);
	// 5-6�ֽڣ�ͨ������ֹʱ�䣬2msΪ������0-131070ms
	byData[4] = HIBYTE(pScanTypeHeader->m_wChnEndTime);
	byData[5] = LOBYTE(pScanTypeHeader->m_wChnEndTime);
	// 7-8�ֽڣ���С��������	
	wTemp = pScanTypeHeader->GetDescaleMultiplier();
	byData[6] = LOBYTE(wTemp);
	byData[7] = HIBYTE(wTemp);
	// 9-10�ֽڣ�BCD�룬��ͨ������ͨ����,0-9999
	ConvertWORDToBCD(pScanTypeHeader->m_wChnCount,byData+8);
	// 11HΪ��������ͱ�ʶ��1Ϊ�������9Ϊ������;
	// 11Lδʹ��
	if (pScanTypeHeader->m_byChnType==9)
	{
		byData[10]=0x90;
	}
	else
	{
		byData[10] = 0x10;
	}
	// 12HΪ��ɨ��ָ����Ŀ,Ϊ0
	// 12LΪ�����������Ʒ�ʽ���̶�����Ϊ3
	byData[11] = 0x03;	
	// 13-14�ֽڣ�BCD�룬3db�㴦�Ļ���˲���Ƶ��	
	wTemp = pScanTypeHeader->GetAliasFilterfrequency(m_dwSampleRateUS);
	ConvertWORDToBCD(wTemp,byData+12);
	// 15-16�ֽڣ�BCD�룬����˲���б��			
	wTemp = pScanTypeHeader->GetAliasFilterSlope();
	ConvertWORDToBCD(wTemp,byData+14);	
	// 17-18�ֽڣ�BCD�룬�ͽ��˲���Ƶ��
	wTemp = pScanTypeHeader->GetLowcutFilterFrequency();
	ConvertWORDToBCD(wTemp,byData+16);	
	// 19-20�ֽڣ�BCD�룬�ͽ��˲���б��
	wTemp = pScanTypeHeader->GetLowcutFilterSlope();
	ConvertWORDToBCD(wTemp,byData+18);
	// 21-22�ֽڣ���һ�ݲ���б��
	byData[20] = 0;
	byData[21] = 0;
	// 23-24�ֽڣ��ڶ��ݲ���б��
	byData[22] = 0;
	byData[23] = 0;
	// 25-26�ֽڣ������ݲ���б��
	byData[24] = 0;
	byData[25] = 0;
	// 27-28�ֽڣ���չ���������
	byData[26] = 0;
	byData[27] = 0;
	// 29H,��չͷ��ǣ�29L����ͷ��չ
	byData[28] = 0x07;
	// 30�ֽڣ���ֱ����
	byData[29] = pScanTypeHeader->m_byVerticalStack;
	// 31�ֽڣ��������µ��ºţ�½��Ϊ0
	byData[30] = 0x00;
	// 32�ֽڣ��������,�������
	byData[31] = 0x01;
	
	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д����չͷ��
 * @note  ����SEGD2.1�ĸ�ʽд����չͷ�Σ�����Ϊ32*32=1024�ֽ�;
          ��չͷ���ɳ��Ҿ����������ݴ��������й�ϵ
 * @param  
		
 * @return void
 */
#define   MACRO_Write_BigEndianDWORD(dwValue)  { ReverseDWORDToBigEndian((dwValue),byData+nPos); nPos+=4; }
#define   MACRO_Write_BigEndianFloat(dwValue)  { ReverseFloatToBigEndian((dwValue),byData+nPos); nPos+=4; }

void CSEGDFile::WriteExtendedHeader()
{	
	unsigned char byData[1024];
	memset(byData,0,1024);
	DWORD		  dwTemp;
	int           nPos=0;
	union unDOUBLE
	{
		BYTE  byData[8];
		double dbData;
	}undbTemp;

	// 1-4���������ȣ�����ͨͷ��2�ŵ�15-17�ֽ���ͬ
	MACRO_Write_BigEndianDWORD( m_dwRecordLenMS );	
	// 5-8�������ʣ���΢��Ϊ��λ
	MACRO_Write_BigEndianDWORD( m_dwSampleRateUS);		
	// 9-12����¼������
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwTraceCount);	
	// 13-16������������
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwAuxesTraceCount);	
	// 17-20�������¼������
	dwTemp = m_ExtendedHeader.m_dwTraceCount-m_ExtendedHeader.m_dwAuxesTraceCount;	
	MACRO_Write_BigEndianDWORD( dwTemp);
	// 21-24��ͣ�͵����¼����Ŀ: �����¼������ - ������¼����Ŀ
	dwTemp -= m_ExtendedHeader.m_dwLiveSeisTraceCount;
	MACRO_Write_BigEndianDWORD( dwTemp);	
	// 25-28��������¼����Ŀ			
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwLiveSeisTraceCount);	
	// 29-32����Դ����
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSourceType );	
	// 33-36����¼���в�����Ŀ
	dwTemp =  GetNumberOfSamples();
	MACRO_Write_BigEndianDWORD( dwTemp );
	// 37-40���ں�
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwShotNb);
	// 41-44,TB����
	MACRO_Write_BigEndianFloat( m_ExtendedHeader.m_fTBWindowS);	// ????????????�Ƿ�Ҫ���BigEndian
	// 45-48,���Լ�¼����
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwTestType);
	// 49-52,��һ����
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSpreadSFL);


	// 53-56,Spread first number
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSpreadSFN);		
	// 57-60,���б��
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSpreadNb);	
	// 61-64����������
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSpreadType);	
	// 65-68,ʱ���ź�
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwConfirmationTBUS);
	// 69-72,�����ź�
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwUpholetimeUS);
	// 73-76,��ը����ʶ
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwBlasterID);
	// 77-80,��ը��״̬
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwBlasterStatus);
	// 81-84,������ʱ
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwRefractionDelayMS);
	// 85-88,TB��T0ʱ��	
	ReverseDWORDToBigEndian((DWORD)m_ExtendedHeader.m_lTBToTStartUS,byData+nPos);
	nPos+=4;
	// 89-92,�ڲ�ʱ���źţ�ITB�ж�
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwInternalTimeBreak);

	// 93-96,Ұ���豸��Ԥ����
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwPrestack);
	// 97-100,������������: 1 ��;2��������;3 ��ʷ;4 �ر�
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwNoiseEliminationType);	
	// 101-104,�ͼ�¼���ٷֱȣ�0~100%; Low trace percentage	
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwLowTracePercentage);	
	// 105-108,�ͼ�¼��ֵ;0-132db; Low trace value 
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwLowTraceValue);
	// 109-112,������Ŀ1-64; Number of windows (Div.)or Window length (Enhanced Div.) 
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwWindowLength);
	// 113-116,��ʷ�༭���ͣ�1Ϊ���㣻2Ϊ���ã�
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwHistoricEditingType);
	// 117-120,������¼���ٷֱȣ�0 ��100% �� Noisy trace percentage
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwNoisyTracePercentage);	
	// 121-124,��ʷ��Χ0 �� 36 dB;  Historic range 
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwHistoricRange);	
	// 125-128,��ʷ׶�γ��� 2 ��ָ��:0 �� 8;Historic taper length 2��s	exponent
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwExpHistoricTaperLen );
	// 129-132 �ż�ֵ����/ �仯1 = ����;2 = �仯; Threshold Hold/Var
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwThresholdHold );
	// 133-136,��ʷ�ż�ֵ��ʼֵ0 �� 132 dB; Historic threshold Init value
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwHistoricThresholdValue);
	// 137-140,��ʷ���㳤��1 �� 500 ����; Historic zeroing length
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwHistoricZeroingLen);

	// 141-144, ��������1 �޲�����ԭʼ���ݣ�;2 ����;	3 ���Ӻ����;4 ����ǰ���;5 ԭʼ���ݣ�����;	6 ԭʼ���ݣ����Ӻ����;7 ԭʼ���ݣ�����ǰ���
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwProcessType);
	// 145-272 �ɼ����ͱ�,32����ֵ��128�ֽ�*/
	for (dwTemp=0;dwTemp<32;dwTemp++)
	{
		MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwAcquisitionTypeTable[dwTemp]);
	}	
	// 273-400,�ż�ֵ���ͱ�32 ����ֵ��128 �ֽڣ�,Threshold type tables 32 values (128 bytes).*/
	for (dwTemp=0;dwTemp<32;dwTemp++)
	{
		MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwThresholdTypeTable[dwTemp]);
	}	
	// 401-404,���Ӵ���,1~32; Stacking fold
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwStackingFold);
	// 405-484,δʹ��
	nPos=485;
	// 485-488,��¼����100 �� 128000 ����;Record length
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwRecordLength);
	// 489-492,����ط�ֵʱ��1 �� 128000 ����; Autocorrelation peak time 
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwAutoCorrPeakTime);
	// 493-496,δʹ��
	nPos = 497;
	// 497-500,��زο��źű��1 �� 100000;Correlation Pilot No. 1 to 100000.
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwCorrelationPilot);
	// 501-504,�ο��źų���1000 �� 128000 ���� ; Pilot length
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwPilotLength);
	// 505-508,ɨ�賤��1000 �� 128000 ����; Sweep length
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSweepLength);
	// 509-512,�ɼ���1 �� 32; Acquisition number 
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwAcquisitionNb);

	// 513-516,��ศ���������ֵ;Max of max, Aux
	MACRO_Write_BigEndianFloat( m_ExtendedHeader.m_fMaxAux);
	// 517-520,����������ֵIEEE ��ʽ��������;Max of max, Seis
	MACRO_Write_BigEndianFloat( m_ExtendedHeader.m_fMaxSeis);
	// 521-524,ת�����Ӵ���1..32;Dump stacking fold
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwDumpStackingFold);
	// 525-540,�Ŵ���ǩASCII �ı���16 ���ַ�
	memcpy_s(byData+nPos,16,m_ExtendedHeader.m_byTapeLabel,16);
	nPos+=16;
	// 541-544,�Ŵ���1 �� 9999 
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwTapeNb);
	// 545-560,����汾ASCII �ı���16 ���ַ�; Software version ASCII text, 16 characters.
	memcpy_s(byData+nPos,16,m_ExtendedHeader.m_bySoftwareVersion,16);	
	nPos+=16;
	// 561-572,����ASCII �ı���12 ���ַ�(dd mmm yyyy)
	memcpy_s(byData+nPos,12,m_ExtendedHeader.m_byDate,12);
	nPos+=12;
	// 573-580,��Դƫ����; Source easting	
	undbTemp.dbData = m_ExtendedHeader.m_dbSourceEasting;
	byData[nPos++] = undbTemp.byData[7];
	byData[nPos++] = undbTemp.byData[6];
	byData[nPos++] = undbTemp.byData[5];
	byData[nPos++] = undbTemp.byData[4];
	byData[nPos++] = undbTemp.byData[3];
	byData[nPos++] = undbTemp.byData[2];
	byData[nPos++] = undbTemp.byData[1];
	byData[nPos++] = undbTemp.byData[0];
	// 581-588, ��Դ����γ�Ȳ�; Source northing
	undbTemp.dbData = m_ExtendedHeader.m_dbSourceNorthing;
	byData[nPos++] = undbTemp.byData[7];
	byData[nPos++] = undbTemp.byData[6];
	byData[nPos++] = undbTemp.byData[5];
	byData[nPos++] = undbTemp.byData[4];
	byData[nPos++] = undbTemp.byData[3];
	byData[nPos++] = undbTemp.byData[2];
	byData[nPos++] = undbTemp.byData[1];
	byData[nPos++] = undbTemp.byData[0];
	// 589-592,��Դ�߳�; Source elevation
	MACRO_Write_BigEndianFloat( m_ExtendedHeader.m_fSourceElevation);	
	// 593-596,���õĻ���ɨ��ģʽ�� 0Ϊ��;1Ϊ�� 
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSlipSweepMode);
	// 597-600,ÿ���Ŵ����ļ���1 �� 9999
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwFilesPerTape);
	// 601-604,�ļ�����1 �� 9999
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwFileCount);
	// 605-764,�ɼ�����˵��ASCII �ı���160 ���ַ�
	memcpy_s(byData+nPos,160,m_ExtendedHeader.m_byAcquisitErrorDesc,160);	
	nPos+=160;
	// 765-768,�˲�������: 1 =0.8��С; 2= 0.8 ����; 
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwFilterType);
	// 769-772, ������ת��: 	0 = No; 1 = Yes.;
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwStackIsDumped);
	// 773-776, ���ӷ��ţ���ǰ�� 0 = ��;1 = ��;2 = ��
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwStackSign);
	// 777-780, ���õ� PRM ��б��У��0 = ��;1Ϊ��; PRM Tilt Correction used
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwPRMTiltCorrect);
	// 781-844, ������;ASCII �ı���64���ַ�; 
	memcpy_s(byData+nPos,64,m_ExtendedHeader.m_bySwathName,64);	
	nPos+=64;
	// 845-848, ʩ��ģʽ
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwOperatingMode);
	// 849-852, δ��
	nPos = 853;
	// 853-856, �޼�¼0 = ��;1 = ��
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwNoLog);
	// 857-860,����ʱ��100 �� 128000����; Listening time 100 to 128000 ms.
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwListeningTime);
	// 861-864, ת������0 = ����ת��;1 = ԭʼת��;2 = ����ת��;
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwDumpType);
	// 865-868, δ��
	nPos = 869;
	// 869-872, ���� Id; Swath ID*/
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSwathId);

	// 873-876,Seismic trace offset removal is disabled; Sercel 4.0�汾����
	MACRO_Write_BigEndianDWORD( m_ExtendedHeader.m_dwSeismicTaceOffsetRemoval);
	// 877-1024,δʹ��
	if(m_pFile)
	{
		m_pFile->Write(byData,1024);
	}
}
/**
 * @brief ���ļ���д���ⲿͷ��
 * @note  д���ⲿͷ�Σ�����Ϊ m_wExternalHeaderSize �ֽ�;
          ��չͷ���ɳ��Ҿ�������Ҫ�����������ô��ڡ�ʩ�����ڵ�ע��
 * @param  
		
 * @return void
 */
void CSEGDFile::WriteExternalHeader()
{
	char* byData=new char[m_wExternalHeaderSize];
	memset(byData,0,m_wExternalHeaderSize);
	// ���ڻ��ߵ���ϵͳ��Ϣ
	CT2A	pstr1(m_strShooterInfo);
	size_t  nLen1=strlen(pstr1)+2;
	strcpy_s(byData,m_wExternalHeaderSize,pstr1);
	// ����Config�������õ��û���Ϣ
	CT2A	pstr2(m_strConfigUserInfo);
	size_t  nLen2=strlen(pstr2)+2;
	strcpy_s(byData+nLen1,m_wExternalHeaderSize-nLen1,pstr2);
	// ʩ��ע����Ϣ
	CT2A	pstr3(m_strSourceComment);
	strcpy_s(byData+nLen1+nLen2,m_wExternalHeaderSize-nLen1-nLen2,pstr3);

	if(m_pFile)
	{
		m_pFile->Write(byData,m_wExternalHeaderSize);
	}
}

/**
 * @brief ���ļ���д��ͷ����
 * @note  ÿ������ǰ�����20�ֽڵĶ�·����ͷ
 * @param void
 * @return void
 */
void CSEGDFile::WriteDemuxTraceHeader(CSEGDTraceHeads*	pTrace)
{
	unsigned char byData[20];
	WORD    wTemp;
	// 1-2�ֽڣ��ļ����
	if(m_dwFileNumber>9999)
	{
		byData[0] = 0xFF;
		byData[1] = 0xFF;
	}
	else
	{
		ConvertWORDToBCD(WORD(m_dwFileNumber),byData);
	}
	// 3Byteɨ�����ͱ��
	byData[2] = 0x01;
	// 4�ֽڣ���������
	byData[3] = ConvertBYTEToBCD(pTrace->m_byChnSetNb);
	// 5-6�ֽڣ���¼�����
	if(pTrace->m_dwTraceNb>9999)
	{
		byData[4] = 0xFF;
		byData[5] = 0xFF;
	}
	else
	{
		wTemp = (WORD)pTrace->m_dwTraceNb;
		ConvertWORDToBCD(wTemp,byData+4);
	}	
	// 7-9�ֽڣ���һ����ʱ�֣��������ӳ�
	m_unionType.lData = m_ExtendedHeader.m_dwRefractionDelayMS;		// ???????????
	byData[6] = m_unionType.byData[2];
	byData[7] = m_unionType.byData[1];
	byData[8] = m_unionType.byData[0];
	// 10�ֽڣ���ͷ��չ��������Ϊ7
	byData[9] = 7;
	// 11�ֽڣ�����ʱ��/����Ť��
	byData[10] = 0;
	// 12�ֽڣ���¼���༭
	byData[11] = pTrace->m_byTraceEdit;
	// 13-15�ֽڣ�ʱ���źŴ���
	wTemp = (WORD)m_ExtendedHeader.m_fTBWindowS;
	byData[12] = HIBYTE(wTemp);
	byData[13] = LOBYTE(wTemp);
	byData[14] = ConvertLessOneFloatToBYTE(m_ExtendedHeader.m_fTBWindowS - wTemp);
	// 16-17�ֽڣ���չ��������
	byData[15] = 0;
	byData[16] = 0;
	// 18-20�ֽڣ���չ�ļ����
	m_unionType.dwData = m_dwFileNumber;
	byData[17] = m_unionType.byData[2];	// ��չ�ļ�������λ
	byData[18] = m_unionType.byData[1];	
	byData[19] = m_unionType.byData[0];	// ��չ�ļ�������λ
	
	if(m_pFile)
	{
		m_pFile->Write(byData,20);
	}
}

/**
 * @brief ���ļ���д��ͷ��չ���ݿ�1
 * @note  
 * @param 	
 long lLineNb,���յ���ߺ�
 long lPointNb,���յ���
 BYTE byPointIndex,���յ�����
 DWORD dwSampleCount,ÿ����¼������������Ŀ
 BYTE bySensorSEGDCode
 * @return void
 */
void CSEGDFile::WriteTraceHeaderExtension1(CSEGDTraceHeads*	pTrace)
{
	unsigned char byData[32];
	// 1-3�ֽڣ����յ���ߺ�
	m_unionType.lData = pTrace->m_dwLineNb;
	byData[0] = m_unionType.byData[2];
	byData[1] = m_unionType.byData[1];
	byData[2] = m_unionType.byData[0];
	// 4-6�ֽڣ����յ���
	m_unionType.lData = pTrace->m_dwPointNb;
	byData[3] = m_unionType.byData[2];
	byData[4] = m_unionType.byData[1];
	byData[5] = m_unionType.byData[0];
	// 7�ֽڣ����յ�����
	byData[6] = pTrace->m_byPointIndex;
	// 8-10�ֽڣ�ÿ����¼������������Ŀ
	m_unionType.dwData = GetNumberOfSamples();
	byData[7] = m_unionType.byData[2];
	byData[8] = m_unionType.byData[1];
	byData[9] = m_unionType.byData[0];
	// 11-15�ֽڣ���չ���յ���ߺ�;�����յ���ߺŴ���0xFFFFFFʱ��ʹ����չ���յ�
	// 16-20�ֽڣ���չ���յ���
	memset(byData+10,0,10);
	// 21�ֽڣ��첨����SEGD����
	byData[20] = pTrace->m_bySensorSEGDCode;
	// 22-32δʹ��
	memset(byData+21,0,10);
	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д��ͷ��չ���ݿ�2
 * @note  
 * @param 	
 double dbFromeEast,���յ�ƫ����
 double dbNorthLatitudeDifference,���յ㱱��γ�Ȳ�
 float fElevation,���յ�߳�
 BYTE bySensorType,�첨�����ͱ��
 DWORD dwTraceNb,��չ��¼�����
 * @return void
 */
void CSEGDFile::WriteTraceHeaderExtension2(CSEGDTraceHeads*	pTrace)
{
	unsigned char byData[32];
	union unDOUBLE
	{
		BYTE  byData[8];
		double dbData;
	}undbTemp;
	
	// 1-8�ֽڣ�double���ͣ����յ�ƫ����
	undbTemp.dbData = pTrace->m_dbPointEasting;
	byData[0] = undbTemp.byData[7];
	byData[1] = undbTemp.byData[6];
	byData[2] = undbTemp.byData[5];
	byData[3] = undbTemp.byData[4];
	byData[4] = undbTemp.byData[3];
	byData[5] = undbTemp.byData[2];
	byData[6] = undbTemp.byData[1];
	byData[7] = undbTemp.byData[0];
	// 9-16�ֽڣ�double���ͣ����յ㱱��γ�Ȳ�
	undbTemp.dbData = pTrace->m_dbPointNorthing;
	byData[8] = undbTemp.byData[7];
	byData[9] = undbTemp.byData[6];
	byData[10] = undbTemp.byData[5];
	byData[11] = undbTemp.byData[4];
	byData[12] = undbTemp.byData[3];
	byData[13] = undbTemp.byData[2];
	byData[14] = undbTemp.byData[1];
	byData[15] = undbTemp.byData[0];
	// 17-20�ֽڣ�float���ͣ����յ�߳�
	m_unionType.fData = pTrace->m_fPointElevation;
	byData[16] = m_unionType.byData[3];
	byData[17] = m_unionType.byData[2];
	byData[18] = m_unionType.byData[1];
	byData[19] = m_unionType.byData[0];
	// 21�ֽڣ��첨�����ͱ��
	byData[20] = pTrace->m_bySensorType;
	// 22-28�ֽڣ�δʹ��
	memset(byData+21,0,6);
	// 29-32�ֽڣ���չ��¼�����
	if(pTrace->m_dwTraceNb>9999)
	{
		m_unionType.dwData = pTrace->m_dwTraceNb;
		byData[28] = m_unionType.byData[3];
		byData[29] = m_unionType.byData[2];
		byData[30] = m_unionType.byData[1];
		byData[31] = m_unionType.byData[0];
	}
	else
	{
		memset(byData+28,0,4);
	}
	
	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д��ͷ��չ���ݿ�3
 * @note  
 * @param 	float fResistanceMax,
 float fResistanceMin,
 float fResistanceVal,
 float fTiltMax,
 float fTiltVal,
 BYTE byResistanceError,
 BYTE byTiltError	
 * @return void
 */
void CSEGDFile::WriteTraceHeaderExtension3(CSEGDTraceHeads*	pTrace)
{
	unsigned char byData[32];
	// 1-4 �ֽڣ���������
	m_unionType.fData = pTrace->m_fResistanceMin;
	byData[0] = m_unionType.byData[3];
	byData[1] = m_unionType.byData[2];
	byData[2] = m_unionType.byData[1];
	byData[3] = m_unionType.byData[0];
	// 5-8 �ֽڣ���������
	m_unionType.fData = pTrace->m_fResistanceMax;
	byData[4] = m_unionType.byData[3];
	byData[5] = m_unionType.byData[2];
	byData[6] = m_unionType.byData[1];
	byData[7] = m_unionType.byData[0];
	// 9-12 �ֽڣ�����ֵ(ŷķ)
	m_unionType.fData = pTrace->m_fResistanceVal;
	byData[8] = m_unionType.byData[3];
	byData[9] = m_unionType.byData[2];
	byData[10] = m_unionType.byData[1];
	byData[11] = m_unionType.byData[0];
	// 13-16�ֽڣ���б�Ƚ���
	m_unionType.fData = pTrace->m_fTiltMax;
	byData[12] = m_unionType.byData[3];
	byData[13] = m_unionType.byData[2];
	byData[14] = m_unionType.byData[1];
	byData[15] = m_unionType.byData[0];
	// 17-20�ֽڣ���б��ֵ(����FDU�����Ϊ%������DSU�����Ϊ��)
	m_unionType.fData = pTrace->m_fTiltVal;
	byData[16] = m_unionType.byData[3];
	byData[17] = m_unionType.byData[2];
	byData[18] = m_unionType.byData[1];
	byData[19] = m_unionType.byData[0];
	// 21�ֽڣ��������:0Ϊ��1Ϊ��
	if(pTrace->m_fResistanceVal<pTrace->m_fResistanceMin ||pTrace->m_fResistanceVal>pTrace->m_fResistanceMax)
		byData[20] = 1;
	else
		byData[20] = 0;
	// 22�ֽڣ���б�����:0Ϊ��1Ϊ��
	if(pTrace->m_fTiltVal>pTrace->m_fTiltMax)
		byData[21] = 1;
	else
		byData[21] = 0;
	// 23-32δ��
	memset(byData+22,0,10);
	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д��ͷ��չ���ݿ�4
 * @note  
 * @param 		
 * @return void
 */
void CSEGDFile::WriteTraceHeaderExtension4(CSEGDTraceHeads*	pTrace)
{
	unsigned char byData[32];
	memset(byData,0xFF,32);
	// 1-4 �ֽڣ���������
	m_unionType.fData = pTrace->m_fCapacitanceMin;
	byData[0] = m_unionType.byData[3];
	byData[1] = m_unionType.byData[2];
	byData[2] = m_unionType.byData[1];
	byData[3] = m_unionType.byData[0];
	// 5-8 �ֽڣ���������
	m_unionType.fData = pTrace->m_fCapacitanceMax;
	byData[4] = m_unionType.byData[3];
	byData[5] = m_unionType.byData[2];
	byData[6] = m_unionType.byData[1];
	byData[7] = m_unionType.byData[0];
	// 9-12 �ֽڣ�����ֵ(�ɷ���)
	m_unionType.fData = pTrace->m_fCapacitanceVal;
	byData[8] = m_unionType.byData[3];
	byData[9] = m_unionType.byData[2];
	byData[10] = m_unionType.byData[1];
	byData[11] = m_unionType.byData[0];
	// 13-16 �ֽڣ���ֹ����
	m_unionType.fData = pTrace->m_fCutoffFreqMin;
	byData[12] = m_unionType.byData[3];
	byData[13] = m_unionType.byData[2];
	byData[14] = m_unionType.byData[1];
	byData[15] = m_unionType.byData[0];
	// 17-20 �ֽڣ���ֹ����
	m_unionType.fData = pTrace->m_fCutoffFreqMax;
	byData[16] = m_unionType.byData[3];
	byData[17] = m_unionType.byData[2];
	byData[18] = m_unionType.byData[1];
	byData[19] = m_unionType.byData[0];
	// 21-24 �ֽڣ���ֵֹ(����)
	m_unionType.fData = pTrace->m_fCutoffFreqVal;
	byData[20] = m_unionType.byData[3];
	byData[21] = m_unionType.byData[2];
	byData[22] = m_unionType.byData[1];
	byData[23] = m_unionType.byData[0];
	// 25�ֽڣ��������:0Ϊ��1Ϊ��
	if(pTrace->m_fCapacitanceVal<pTrace->m_fCapacitanceMin || pTrace->m_fCapacitanceVal>pTrace->m_fCapacitanceMax)
		byData[24] = 1;
	else
		byData[24] = 0;
	// 26�ֽڣ���ֹ���:0Ϊ��1Ϊ��
	if(pTrace->m_fCutoffFreqVal<pTrace->m_fCutoffFreqMin || pTrace->m_fCutoffFreqVal>pTrace->m_fCutoffFreqMax)
		byData[25] = 1;
	else
		byData[25] = 0;
	// 27-32δ��
	// memset(byData+26,0,6);
	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д��ͷ��չ���ݿ�5
 * @note  
 * @param 		
 * @return void
 */
void CSEGDFile::WriteTraceHeaderExtension5(CSEGDTraceHeads*	pTrace)
{
	unsigned char byData[32];
	memset(byData,0xFF,32);
	// 1-4 �ֽڣ�©�����
	m_unionType.fData = pTrace->m_fLeakageLimit;
	byData[0] = m_unionType.byData[3];
	byData[1] = m_unionType.byData[2];
	byData[2] = m_unionType.byData[1];
	byData[3] = m_unionType.byData[0];
	// 5-8 �ֽڣ�©��ֵ��ǧŷ��
	m_unionType.fData = pTrace->m_fLeakageVal;
	byData[4] = m_unionType.byData[3];
	byData[5] = m_unionType.byData[2];
	byData[6] = m_unionType.byData[1];
	byData[7] = m_unionType.byData[0];
	// 9-24�ֽ�δʹ��
	// 25�ֽڣ�©�����
	if(pTrace->m_fLeakageVal<pTrace->m_fLeakageLimit)
		byData[24] = 1;
	else
		byData[24] = 0;
	// 26-32δ��
	// memset(byData+25,0,7);
	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д��ͷ��չ���ݿ�6
 * @note  
 * @param 		
 * @return void
 */
void CSEGDFile::WriteTraceHeaderExtension6(CSEGDTraceHeads*	pTrace,CSEGDScanTypeHeader* pScanTypeHeader)
{
	unsigned char byData[32];
	//memset(byData,0xFF,32);
	if(!pTrace || !pScanTypeHeader)
		return;
	// 1,�豸����
	byData[0] = pScanTypeHeader->m_byUnitType;	
	// 2-4,�豸���к�
	m_unionType.dwData = pTrace->m_dwUnitSN;
	byData[1] = m_unionType.byData[2];
	byData[2] = m_unionType.byData[1];
	byData[3] = m_unionType.byData[0];
	// 5,�������
	byData[4] = pTrace->m_byChannelNb;
	// 6-8,����
	byData[5] = 0;
	byData[6] = 0;
	byData[7] = 0;
	// 9���������
	byData[8] = pTrace->m_byAssemblyType;
	// 10-12��FDU����DSU������к�
	m_unionType.dwData = pTrace->m_dwFDUAssemblySN;
	byData[9] = m_unionType.byData[2];
	byData[10] = m_unionType.byData[1];
	byData[11] = m_unionType.byData[0];
	// 13����FDU�����λ��
	byData[12] = pTrace->m_byLocationInFDUAssembly;
	// 14-16,����
	byData[13] = 0;
	byData[14] = 0;
	byData[15] = 0;
	// 17��FDU/DSU�豸����
	byData[16] = pTrace->m_bySubunitType;
	// 18�����������
	byData[17] = pTrace->m_byChannelType;
	// 19-20,����
	byData[18] = 0;
	byData[19] = 0;
	// 21-24,�첨��������
	memset(byData+20,0xFF,4);
	// 25-32,δʹ��
	memset(byData+24,0x0,8);
	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief ���ļ���д��ͷ��չ���ݿ�7
 * @note  
 * @param 		
 * @return void
 */
void CSEGDFile::WriteTraceHeaderExtension7(CSEGDTraceHeads*	pTrace,CSEGDScanTypeHeader* pScanTypeHeader)
{
	unsigned char byData[32];
	//memset(byData,0xFF,32);
	// 1,���Ƶ�Ԫ����
	byData[0] = pTrace->m_byControlUnitType;
	// 2-4,���Ƶ�Ԫ���к�
	m_unionType.dwData = pTrace->m_dwControlUnitSN;
	byData[1] = m_unionType.byData[2];
	byData[2] = m_unionType.byData[1];
	byData[3] = m_unionType.byData[0];
	// 5�����������̶�
	byData[4] = (BYTE)pScanTypeHeader->m_dwGain;
	// 6��������˲���
	byData[5] = pTrace->m_byChannelFilter;
	// 7����������ݴ���,
	byData[6] = pTrace->m_byChannelDataError;
	// 8,������༭״̬
	byData[7] = pTrace->m_byChannelEditedStatus;
	// 9-12�����������������������ת��ϵ��
	ReverseFloatToBigEndian(pTrace->m_fChannelConversionFactor,byData+8);
	// 13,���������Ӵ���
	byData[12] = pTrace->m_byNumberOfStacksNoisy;
	// 14, �͵��Ӵ���
	byData[13] = pTrace->m_byNumberOfStacksLow;
	// 15,��������ͱ�ʶ�ţ�1 = �����;9 = ������;��ɨ������ͷ�ζ�����
	/*if(pScanTypeHeader->m_byChnType==CHN_AUXI)
		byData[14] = 0x09;
	else
		byData[14] = 0x01;*/
	byData[14] = pScanTypeHeader->m_byChnType;
	// 16,���������:01=ԭʼ����;	02=����������;03=��أ�������;04=��أ�������;05=��̬���;06=���������
	byData[15] = pTrace->m_byChannelProcessType;
	// 17-20, ��¼�����ֵ
	ReverseFloatToBigEndian(pTrace->m_fTraceMaxValue,byData+16);
	// 21-24,��¼�����ʱ��,΢��
	ReverseDWORDToBigEndian(pTrace->m_dwTraceMaxtime,byData+20);
	// 25-28,�ڲ����	
	ReverseDWORDToBigEndian(pTrace->m_dwInterpolations,byData+24);
	// 29-32,Seismic trace offset value(if offset removal is disabled).
	ReverseDWORDToBigEndian(pTrace->m_dwSeismicTraceOffsetValue,byData+24);
	if(m_pFile)
	{
		m_pFile->Write(byData,32);
	}
}
/**
 * @brief �ߵ��������ߵ�λ
 * @note  �ߵ��������ߵ�λ����λ��ǰ����λ�ں�
 * @param 		
 * @return void
 */
void CSEGDFile::ReverseFloatToBigEndian(float fValue,BYTE* byData)
{
	if(!byData)
		return;
	m_unionType.fData = fValue;
	byData[0] = m_unionType.byData[3];
	byData[1] = m_unionType.byData[2];
	byData[2] = m_unionType.byData[1];
	byData[3] = m_unionType.byData[0];

}
/**
 * @brief �ߵ������ߵ�λ
 * @note  �ߵ������ߵ�λ����λ��ǰ����λ�ں�
 * @param 		
 * @return void
 */
void CSEGDFile::ReverseDWORDToBigEndian(DWORD dwValue,BYTE* byData)
{
	if(!byData)
		return;
	m_unionType.dwData = dwValue;
	byData[0] = m_unionType.byData[3];
	byData[1] = m_unionType.byData[2];
	byData[2] = m_unionType.byData[1];
	byData[3] = m_unionType.byData[0];

}
/**
 * @brief �������ֽڵ�����ת��Ϊ�ĸ��ֽڵĸ�������ʽ�����ߵ��ֽڻ���
 * @note  �������ֽڵ�����ת��Ϊ�ĸ��ֽڵĸ�������ʽ���ߵ��������ߵ�λ����λ��ǰ����λ�ں�
 * @param 		
 * @return void
 */
void CSEGDFile::Convert3ByteIntTo4ByteAntiFlt(BYTE* lpInData,BYTE* lpOutData)
{
	if(!lpInData || !lpOutData)
		return;
	
	DWORD	dwTemp=0;
	// ��λ
	dwTemp = lpInData[2];
	dwTemp = dwTemp<<8;
	dwTemp = dwTemp+ lpInData[1];
	dwTemp = dwTemp<<8;
	// ���λ
	dwTemp = dwTemp+ lpInData[0];
	m_unionType.fData = (float)dwTemp;
	lpOutData[0] = m_unionType.byData[3];
	lpOutData[1] = m_unionType.byData[2];
	lpOutData[2] = m_unionType.byData[1];
	lpOutData[3] = m_unionType.byData[0];

}

/**
 * @brief дSEGD�ļ�
 * @note  �ú���д������SEGD�ļ�
 * @param 		
 * @return void
 */
void CSEGDFile::SaveSEGDHead(CSEGDScanTypeHeader* pScanTypeHeader)
{
	DWORD	dwTemp;
	// ��ͨͷ��1
	WriteGeneralHeader1();
	// ��ͨͷ��2
	WriteGeneralHeader2();
	// ��ͨͷ��3
	WriteGeneralHeader3();	
	// ɨ������ͷ��
	for (dwTemp=0;dwTemp<m_byChnSetsCount;dwTemp++)
	{
		WriteScanTypeHeader(pScanTypeHeader+dwTemp);
	}
	// ��չͷ��
	WriteExtendedHeader();
	// �ⲿͷ��
	WriteExternalHeader();

}

/**
 * @brief �洢ĳһ���ĵ�ͷ��������
 * @note  �洢ĳһ���ĵ�ͷ��������
 * @param 		
 * @return void
 */
void CSEGDFile::SaveSEGDTraceHead(CSEGDTraceHeads*	pTrace,CSEGDScanTypeHeader* pScanTypeHeader)
{
	// ��·����ͷ
	WriteDemuxTraceHeader(pTrace);
	// ��ͷ��չ
	WriteTraceHeaderExtension1(pTrace);
	WriteTraceHeaderExtension2(pTrace);
	WriteTraceHeaderExtension3(pTrace);
	WriteTraceHeaderExtension4(pTrace);
	WriteTraceHeaderExtension5(pTrace);
	WriteTraceHeaderExtension6(pTrace,pScanTypeHeader);
	WriteTraceHeaderExtension7(pTrace,pScanTypeHeader);
}
// =============================ֻ��ʩ���������ʹ�õ����к���======================================
#ifdef PROGRAM_OPERATIONSERVER
void	CSEGDFile::SetExtendedHeader(COperaThread* pThread,CChannelList* pChannelList)
{
	if(!pThread || !pChannelList)
		return;
	CShotClient* pShotClient = pThread->GetShotClient();
	/** ��¼������*/
	m_ExtendedHeader.m_dwTraceCount=pShotClient->m_pSpread->GetCount();
	/** ����������*/
	m_ExtendedHeader.m_dwAuxesTraceCount=pShotClient->m_pSpread->GetAuxiCount();
	/** ��Ӧ���ַ������*/
	m_ExtendedHeader.m_dwLiveSeisTraceCount=pShotClient->m_pSpread->TotalOfAcked();
	/** ��Ӧ���ַ������*/
	// m_dwDeadSeisTraceCount=0;	

	/**��Դ����:0Ϊ����Դ��1Ϊ���壬2Ϊ�ɿ�*/
	m_ExtendedHeader.m_dwSourceType=pShotClient->m_pShotSource->m_dwSourceType;
	/** �ں�*/
	m_ExtendedHeader.m_dwShotNb=pShotClient->m_pShotPoint->m_dwShotNb;
	/** TB����ʱ��*/
	m_ExtendedHeader.m_fTBWindowS=pShotClient->m_pProcessType->m_dwTBWindow/1000.0f;
	/** �ɼ����еĵ�һ������ */
	m_ExtendedHeader.m_dwSpreadSFL =pShotClient->m_pShotPoint->m_dwSpreadSFL;
	/** ���е�һ�����ռ첨��λ�ú��� */
	m_ExtendedHeader.m_dwSpreadSFN=pShotClient->m_pShotPoint->m_dwSpreadSFN;
	/** �ɼ����б�� */
	m_ExtendedHeader.m_dwSpreadNb=pShotClient->m_pSpread->m_dwNb;
	/** �ɼ���������: 1Ϊ��ͨ���У�2Ϊ�������� */
	m_ExtendedHeader.m_dwSpreadType=pShotClient->m_pSpread->m_bySpreadType; 
	/** ���Լ�¼����Test record type:
	0 ������¼��1 Ұ��������2 Ұ�����塣3 Ұ�⴮����4 ����������
	5 �������䡣6 ��������/ ��λ��	7 ����������	8 ������ģ��
	9 �ϳɡ�	10 һ���ԣ����� CM408����11 �������塣12 Ұ����䡣
	13 ����������14 Ұ��©�硣15 Ұ����衣*/
	m_ExtendedHeader.m_dwTestType=0;
	
	/** ʱ���ź�Timebreak��΢�뵥λ */
	m_ExtendedHeader.m_dwConfirmationTBUS=DWORD(pThread->m_pShotCtrl->m_fConfirmedTB*1000);
	/** ����ʱ��,΢��Ϊ��λ*/
	m_ExtendedHeader.m_dwUpholetimeUS = DWORD(pThread->m_pShotCtrl->m_fUpholeTime*1000);
	/** ��ը����ʶBlaster id */
	m_ExtendedHeader.m_dwBlasterID=1;		// ????????��ը������λ����Э���н�����ֻ�в��ֱ�ը��Э�����и��ֶ�			
	/** ��ը��״̬ */
	m_ExtendedHeader.m_dwBlasterStatus=pThread->m_pShotCtrl->m_byBlasterState;
	

	/** ������ʱ������ms*/
	if(pShotClient->m_pProcessType->m_byProcessType == PROCESS_IMPULSIVE)
		m_ExtendedHeader.m_dwRefractionDelayMS=((CProcessImpulsive*)(pShotClient->m_pProcessType))->m_dwRefractionDelay;
	else
		m_ExtendedHeader.m_dwRefractionDelayMS = 0;
	/** TB��T0ʱ�䣬ȷ�ϵ�TBʱ���ȥ����ʱ��,��λ΢��*/
	m_ExtendedHeader.m_lTBToTStartUS = DWORD(pThread->m_pShotCtrl->m_fConfirmedTB*1000-m_ExtendedHeader.m_dwRefractionDelayMS*1000);// ???????????????????
	/** �ڲ�ʱ���źţ�ITB ָʾ; 0Ϊ�ǣ�1Ϊ��*/
	if(pThread->m_pShotCtrl->m_fConfirmedTB<pShotClient->m_pProcessType->m_dwTBWindow)
		m_ExtendedHeader.m_dwInternalTimeBreak = 1;								// ???????????????????
	else
		m_ExtendedHeader.m_dwInternalTimeBreak = 0;
	
	/** Ұ���豸��Ԥ���ӣ�0Ϊ�ǣ�1Ϊ��Prestack within field units*/
	m_ExtendedHeader.m_dwPrestack=1;											// ???????????????���±��������޸�
	/**������������: 1 ��;2��������;3 ��ʷ;4 �ر�*/
	m_ExtendedHeader.m_dwNoiseEliminationType=1;
	/** �ͼ�¼���ٷֱȣ�0~100%; Low trace percentage*/
	m_ExtendedHeader.m_dwLowTracePercentage=0;
	/** �ͼ�¼��ֵ;0-132db; Low trace value */
	m_ExtendedHeader.m_dwLowTraceValue=0;
	/** ������Ŀ1-64; Number of windows (Div.)or Window length (Enhanced Div.) */
	m_ExtendedHeader.m_dwWindowLength=1;
	/** ��ʷ�༭���ͣ�1Ϊ���㣻2Ϊ���ã�*/
	m_ExtendedHeader.m_dwHistoricEditingType=1;
	/** ������¼���ٷֱȣ�0 ��100% �� Noisy trace percentage*/
	m_ExtendedHeader.m_dwNoisyTracePercentage=0;
	/** ��ʷ��Χ0 �� 36 dB;  Historic range */
	m_ExtendedHeader.m_dwHistoricRange=0;
	/** ��ʷ׶�γ��� 2 ��ָ��:0 �� 8;Historic taper length 2��s	exponent*/
	m_ExtendedHeader.m_dwExpHistoricTaperLen=0;
	/** �ż�ֵ����/ �仯1 = ����;2 = �仯; Threshold Hold/Var*/
	m_ExtendedHeader.m_dwThresholdHold=1;
	/**��ʷ�ż�ֵ��ʼֵ0 �� 132 dB; Historic threshold Init value*/
	m_ExtendedHeader.m_dwHistoricThresholdValue=0;
	/**��ʷ���㳤��1 �� 500 ����; Historic zeroing length*/
	m_ExtendedHeader.m_dwHistoricZeroingLen=1;								// ??????????????????????????����Ϊֹ
	
	
	/**��������1 �޲�����ԭʼ���ݣ�;2 ����;	3 ���Ӻ����;4 ����ǰ���;5 ԭʼ���ݣ�����;	6 ԭʼ���ݣ����Ӻ����;7 ԭʼ���ݣ�����ǰ���*/
	m_ExtendedHeader.m_dwProcessType=1;
	/** �ɼ����ͱ�,32����ֵ��128�ֽ�*/
	// m_dwAcquisitionTypeTable[32];
	memset(m_ExtendedHeader.m_dwAcquisitionTypeTable,0,128);
	/**�ż�ֵ���ͱ�32 ����ֵ��128 �ֽڣ�,Threshold type tables 32 values (128 bytes).*/
	// m_dwThresholdTypeTable[32];
	memset(m_ExtendedHeader.m_dwThresholdTypeTable,0,128);
	/**���Ӵ���,1~32; Stacking fold*/
	m_ExtendedHeader.m_dwStackingFold=1;
	/** ��¼����100 �� 128000 ����;Record length*/
	m_ExtendedHeader.m_dwRecordLength=pShotClient->m_pProcessType->m_dwRecordLen;
	/** ����ط�ֵʱ��1 �� 128000 ����; Autocorrelation peak time */
	m_ExtendedHeader.m_dwAutoCorrPeakTime=1;
	/** ��زο��źű��1 �� 100000;Correlation Pilot No. 1 to 100000.*/
	m_ExtendedHeader.m_dwCorrelationPilot=1;
	/** �ο��źų���1000 �� 128000 ���� ; Pilot length*/
	m_ExtendedHeader.m_dwPilotLength=1000;
	/** ɨ�賤��1000 �� 128000 ����; Sweep length*/
	m_ExtendedHeader.m_dwSweepLength=1000;
	/** �ɼ���1 �� 32; Acquisition number */
	m_ExtendedHeader.m_dwAcquisitionNb=1;
	/** ��ศ���������ֵ;Max of max, Aux*/
	m_ExtendedHeader.m_fMaxAux=0;
	/** ����������ֵIEEE ��ʽ��������;Max of max, Seis*/
	m_ExtendedHeader.m_fMaxSeis=0;
	/** ת�����Ӵ���1..32;Dump stacking fold*/
	m_ExtendedHeader.m_dwDumpStackingFold=1;
	/** �Ŵ���ǩASCII �ı���16 ���ַ�*/
	// m_byTapeLabel[16];
	memset(m_ExtendedHeader.m_byTapeLabel,0,16);
	/** �Ŵ���1 �� 9999 */
	m_ExtendedHeader.m_dwTapeNb=1;
	/** ����汾ASCII �ı���16 ���ַ�; Software version ASCII text, 16 characters.*/
	//m_bySoftwareVersion[16];
	strcpy_s((char*)m_ExtendedHeader.m_bySoftwareVersion,16,"1.0");					// ??????????????����汾
	/** ����ASCII �ı���12 ���ַ�(dd mmm yyyy)*/
	//m_byDate[12];
	strcpy_s((char*)m_ExtendedHeader.m_bySoftwareVersion,12,"01  01 2011");
	/** ��Դƫ����; Source easting*/
	m_ExtendedHeader.m_dbSourceEasting=0;
	/** ��Դ����γ�Ȳ�; Source northing*/
	m_ExtendedHeader.m_dbSourceNorthing=0;
	/** ��Դ�߳�; Source elevation*/
	m_ExtendedHeader.m_fSourceElevation=0;
	/** ���õĻ���ɨ��ģʽ�� 0Ϊ��;1Ϊ�� */
	m_ExtendedHeader.m_dwSlipSweepMode=0;
	/** ÿ���Ŵ����ļ���1 �� 9999*/
	m_ExtendedHeader.m_dwFilesPerTape=1;
	/** �ļ�����1 �� 9999*/
	m_ExtendedHeader.m_dwFileCount=1;
	/** �ɼ�����˵��ASCII �ı���160 ���ַ�*/
	//m_byAcquisitErrorDesc[160];
	memset(m_ExtendedHeader.m_byAcquisitErrorDesc,0,160);
	/** �˲�������: 1 =0.8��С; 2= 0.8 ����; */
	m_ExtendedHeader.m_dwFilterType=1;
	/** ������ת��: 	0 = No; 1 = Yes.;*/
	m_ExtendedHeader.m_dwStackIsDumped=0;
	/** ���ӷ��ţ���ǰ�� 0 = ��;1 = ��;2 = ��*/
	m_ExtendedHeader.m_dwStackSign=0;
	/** ���õ� PRM ��б��У��0 = ��;1Ϊ��; PRM Tilt Correction used*/
	m_ExtendedHeader.m_dwPRMTiltCorrect=0;
	/** ������;ASCII �ı���64���ַ�; */
	//m_bySwathName[64];
	strcpy_s((char*)m_ExtendedHeader.m_bySwathName,64,"SW1");
	/**ʩ��ģʽbit0 = 1 Standard.bit1 = 1 Microseismic.bit2 = 1 Slip-sweep.	bit3 = 1 SQC Dump (VSR).bit4 = 1 Guidance(Navigation).*/
	m_ExtendedHeader.m_dwOperatingMode=1;
	/** �޼�¼0 = ��;1 = ��*/
	m_ExtendedHeader.m_dwNoLog=0;
	/** ����ʱ��100 �� 128000����; Listening time 100 to 128000 ms.*/
	m_ExtendedHeader.m_dwListeningTime=1000;
	/** ת������0 = ����ת��;1 = ԭʼת��;2 = ����ת��;*/
	m_ExtendedHeader.m_dwDumpType=0;
	/** ���� Id; Swath ID*/
	m_ExtendedHeader.m_dwSwathId=1;
	
	/** Seismic trace offset removal is disabled; 0 = No (i.e.offset is removed);1 = Yes (Microseismic mode); Sercel 4.0�汾����*/
	m_ExtendedHeader.m_dwSeismicTaceOffsetRemoval=0;
	
}
/**
 * @brief �õ�������ɨ�������������λ������
 * @note  �Ӳɼ��������ҳ����еĸ�����������¼�ڲɼ�����������λ�ã�д��arr*Scantype������
 ��ǰ����������ɨ������ͷ�Σ�������+����g1��������+����g2���ɼ���+����g1���ɼ���+����g2
 * @param 		
 * @return void
 */
void	CSEGDFile::GetScanTypeOfSpread(CShotSpread* pSpread,CDWordArray& arrAuxiG1Scantype,
			CDWordArray& arrAuxiG2Scantype,CDWordArray& arrSeisG1Scantype,CDWordArray& arrSeisG2Scantype)
{
	if(!pSpread)
		return;
	int	i;
	int nCount = pSpread->GetCount();
	for (i=0;i<nCount;i++)
	{
		if(pSpread->m_arrSpread[i].m_byType==CHN_AUXI)
		{
			 if(pSpread->m_arrSpread[i].m_dwGain==1)
				 arrAuxiG1Scantype.Add(i);
			 else if( pSpread->m_arrSpread[i].m_dwGain==4)
				 arrAuxiG2Scantype.Add(i);
		}
		else
		{
			if(pSpread->m_arrSpread[i].m_dwGain==1)
				arrSeisG1Scantype.Add(i);
			else if( pSpread->m_arrSpread[i].m_dwGain==4)
				arrSeisG2Scantype.Add(i);
		}
	}
}
void    CSEGDFile::WriteAuxiTraceHeader(int nChnSetNb,int nTraceIndexInSpread,CSEGDScanTypeHeader* pScanTypeHeader,COperaThread* pThread,CChannelList* pChannelList)
{
	CSEGDTraceHeads		TraceHeads;
	CShotSpread*	pSpread = pThread->GetShotClient()->m_pSpread;
	/** ��������*/
	TraceHeads.m_byChnSetNb=nChnSetNb;
	/** ��¼�����*/
	TraceHeads.m_dwTraceNb=nTraceIndexInSpread;
	/** ��¼���༭;00:δ���б༭��02:�ɼ�ǰ�����ͣ�͡�03: �ɲɼ�ϵͳ�༭*/
	TraceHeads.m_byTraceEdit=0;

	/** ���յ���ߺ�*/
	TraceHeads.m_dwLineNb=0;
	/** ���յ��*/
	TraceHeads.m_dwPointNb=0;
	/** ���յ�����*/
	TraceHeads.m_byPointIndex=BYTE(pSpread->m_arrSpread[nTraceIndexInSpread].m_dwChannelNb);
	
	/** �첨��SEGD����,��Line����������*/
	TraceHeads.m_bySensorSEGDCode=0;

	/** ���յ�ƫ����*/
	TraceHeads.m_dbPointEasting=0;
	/** ���յ㱱��γ��*/
	TraceHeads.m_dbPointNorthing=0;
	/** ���յ�߳�*/
	TraceHeads.m_fPointElevation=0;
	/** ���������ͱ��*/
	TraceHeads.m_bySensorType=1;

	/** ����ֵ����*/
	TraceHeads.m_fResistanceMax=0;
	/** ����ֵ����*/
	TraceHeads.m_fResistanceMin=0;
	/** ����ֵ*/
	TraceHeads.m_fResistanceVal=0;
	/** ���½�ϼ첨����б�Ȱٷֱ�*/
	TraceHeads.m_fTiltMax=0;
	/** ��б��ֵ*/
	TraceHeads.m_fTiltVal=0;

	/** ��������*/
	TraceHeads.m_fCapacitanceMax=0;
	/** ��������*/
	TraceHeads.m_fCapacitanceMin=0;
	/** ����ֵ���ɷ���*/
	TraceHeads.m_fCapacitanceVal=0;
	/** ��ֹ����*/
	TraceHeads.m_fCutoffFreqMax=0;
	/** ��ֹ����*/
	TraceHeads.m_fCutoffFreqMin=0;
	/** ��ֵֹ*/
	TraceHeads.m_fCutoffFreqVal=0;
	/** ©�����*/
	TraceHeads.m_fLeakageLimit=0;
	/** ©��ֵ*/
	TraceHeads.m_fLeakageVal=0;

	/**�豸����, �������ͣ�1ΪFDU��0x1C��ʾDSU428 */
	// BYTE	m_byUnitType;��ɨ������ͷ�εı���˵��
	/** �豸���к�*/
	TraceHeads.m_dwUnitSN=pSpread->m_arrSpread[nTraceIndexInSpread].m_dwPointNb;
	/** ��������*/
	TraceHeads.m_byChannelNb=BYTE(pSpread->m_arrSpread[nTraceIndexInSpread].m_dwChannelNb);
	/**�������*/
	TraceHeads.m_byAssemblyType=1;
	/** FDU �� DSU ������к�*/
	TraceHeads.m_dwFDUAssemblySN=0;
	TraceHeads.m_byLocationInFDUAssembly = 0;
	/** �ӵ�Ԫ����*/
	TraceHeads.m_bySubunitType=0x01;
	/** ���������:0 �첨��;1 ѹ���첨��*/
	TraceHeads.m_byChannelType=0;
	/** �첨��������*/

	/** ���Ƶ�Ԫ����:0x01 LCI408;0x02 LAUL408;0x03 LAUX408;0x04 LAULS408;0x05 LAUXS408;0x06 LAUL428;0x16 LRU;0x17 LAUR428;0x30 LAUX428;0x31 LCI428*/
	TraceHeads.m_byControlUnitType=0x31;
	/** ���Ƶ�Ԫ���к�*/
	TraceHeads.m_dwControlUnitSN=0;
	/** ���������̶�*/
	TraceHeads.m_byGainScale=1;
	/** ������˲���*/
	TraceHeads.m_byChannelFilter=1;
	/** ������������*/
	TraceHeads.m_byChannelDataError=0;
	/** ������༭״̬,1 ͣ��;2 �ɼ�/ �ش�����;3 �����༭*/
	TraceHeads.m_byChannelEditedStatus=1;
	/** �������������ת��ϵ��,������Ϊ0*/
	TraceHeads.m_fChannelConversionFactor=0;
	/** ���������Ӵ���*/
	TraceHeads.m_byNumberOfStacksNoisy=0;
	/** �͵��Ӵ���*/
	TraceHeads.m_byNumberOfStacksLow=0;
	/** ��������ͱ�ʶ�ţ�1 = �����;9 = ������;��ɨ������ͷ�ζ�����*/

	/** ���������:01=ԭʼ����;	02=����������;03=��أ�������;04=��أ�������;05=��̬���;06=���������*/
	TraceHeads.m_byChannelProcessType=01;
	/** ��¼�����ֵ*/
	TraceHeads.m_fTraceMaxValue=0;
	/** ��¼�����ʱ��,΢��*/
	TraceHeads.m_dwTraceMaxtime=0;
	/** �ڲ����*/
	TraceHeads.m_dwInterpolations=0;
	/**Seismic trace offset value(if offset removal is disabled).*/
	TraceHeads.m_dwSeismicTraceOffsetValue=0;

	if(m_pFile)
	{
		SaveSEGDTraceHead(&TraceHeads,pScanTypeHeader);
	}
}
void    CSEGDFile::WriteSeisTraceHeader(int nChnSetNb,int nTraceIndexInSpread,CSEGDScanTypeHeader* pScanTypeHeader,COperaThread* pThread,CChannelList* pChannelList)
{
	CSEGDTraceHeads		TraceHeads;
	CShotSpread*	pSpread = pThread->GetShotClient()->m_pSpread;
	/** ��������*/
	TraceHeads.m_byChnSetNb=nChnSetNb;
	/** ��¼�����*/
	TraceHeads.m_dwTraceNb=nTraceIndexInSpread;
	/** ��¼���༭;00:δ���б༭��02:�ɼ�ǰ�����ͣ�͡�03: �ɲɼ�ϵͳ�༭*/
	TraceHeads.m_byTraceEdit=0;

	/** ���յ���ߺ�*/
	TraceHeads.m_dwLineNb=pSpread->m_arrSpread[nTraceIndexInSpread].m_dwLineNb;
	/** ���յ��*/
	TraceHeads.m_dwPointNb=pSpread->m_arrSpread[nTraceIndexInSpread].m_dwPointNb;
	/** ���յ�����*/
	TraceHeads.m_byPointIndex=BYTE(pSpread->m_arrSpread[nTraceIndexInSpread].m_dwChannelNb);

	CChannelSetupData*	pChnData=pChannelList->GetChannel(TraceHeads.m_dwLineNb,TraceHeads.m_dwPointNb,TraceHeads.m_byPointIndex);
	if(pChnData)
	{
		/** �첨��SEGD����,��Line����������*/
		TraceHeads.m_bySensorSEGDCode=pChnData->m_uiSegdCode;

		/** ���յ�ƫ����*/
		TraceHeads.m_dbPointEasting=0;
		/** ���յ㱱��γ��*/
		TraceHeads.m_dbPointNorthing=0;
		/** ���յ�߳�*/
		TraceHeads.m_fPointElevation=0;
		/** ���������ͱ��*/
		TraceHeads.m_bySensorType=pChnData->m_uiSensorNb;

		/** ����ֵ����*/
		TraceHeads.m_fResistanceMax=pChnData->m_fResistanceLimitMax;
		/** ����ֵ����*/
		TraceHeads.m_fResistanceMin=pChnData->m_fResistanceLimitMin;
		/** ����ֵ*/
		TraceHeads.m_fResistanceVal=pChnData->m_fResistanceValue;
		/** ���½�ϼ첨����б�Ȱٷֱ�*/
		TraceHeads.m_fTiltMax=pChnData->m_fTiltLimit;
		/** ��б��ֵ*/
		TraceHeads.m_fTiltVal=pChnData->m_fTiltValue;

		/** ��������*/
		TraceHeads.m_fCapacitanceMax=0;
		/** ��������*/
		TraceHeads.m_fCapacitanceMin=0;
		/** ����ֵ���ɷ���*/
		TraceHeads.m_fCapacitanceVal=0;
		/** ��ֹ����*/
		TraceHeads.m_fCutoffFreqMax=0;
		/** ��ֹ����*/
		TraceHeads.m_fCutoffFreqMin=0;
		/** ��ֵֹ*/
		TraceHeads.m_fCutoffFreqVal=0;
		/** ©�����*/
		TraceHeads.m_fLeakageLimit=pChnData->m_fLeakageLimit;
		/** ©��ֵ*/
		TraceHeads.m_fLeakageVal=pChnData->m_fLeakageValue;

		/**�豸����, �������ͣ�1ΪFDU��0x1C��ʾDSU428 */
		// BYTE	m_byUnitType;��ɨ������ͷ�εı���˵��
		/** �豸���к�*/
		TraceHeads.m_dwUnitSN=pChnData->m_uiSN;
		/** ��������*/
		TraceHeads.m_byChannelNb= BYTE(pChnData->m_uiNbChannel);
		/**�������*/
		TraceHeads.m_byAssemblyType=1;
		/** FDU �� DSU ������к�*/
		TraceHeads.m_dwFDUAssemblySN=0;
		TraceHeads.m_byLocationInFDUAssembly = 0;
		/** �ӵ�Ԫ����*/
		TraceHeads.m_bySubunitType=0x01;
		/** ���������:0 �첨��;1 ѹ���첨��*/
		TraceHeads.m_byChannelType=0;
		/** �첨��������*/

		/** ���Ƶ�Ԫ����:0x01 LCI408;0x02 LAUL408;0x03 LAUX408;0x04 LAULS408;0x05 LAUXS408;0x06 LAUL428;0x16 LRU;0x17 LAUR428;0x30 LAUX428;0x31 LCI428*/
		TraceHeads.m_byControlUnitType=0x31;
		/** ���Ƶ�Ԫ���к�*/
		TraceHeads.m_dwControlUnitSN=0;
		/** ���������̶�*/
		if(pSpread->m_arrSpread[nTraceIndexInSpread].m_dwGain ==1)
			TraceHeads.m_byGainScale=1;
		else
			TraceHeads.m_byGainScale=2;
		/** ������˲���*/
		TraceHeads.m_byChannelFilter=1;
		/** ������������*/
		TraceHeads.m_byChannelDataError=0;
		/** ������༭״̬,1 ͣ��;2 �ɼ�/ �ش�����;3 �����༭*/
		TraceHeads.m_byChannelEditedStatus=1;
		/** �������������ת��ϵ��,������Ϊ0*/
		TraceHeads.m_fChannelConversionFactor=0;
		/** ���������Ӵ���*/
		TraceHeads.m_byNumberOfStacksNoisy=0;
		/** �͵��Ӵ���*/
		TraceHeads.m_byNumberOfStacksLow=0;
		/** ��������ͱ�ʶ�ţ�1 = �����;9 = ������;��ɨ������ͷ�ζ�����*/

		/** ���������:01=ԭʼ����;	02=����������;03=��أ�������;04=��أ�������;05=��̬���;06=���������*/
		TraceHeads.m_byChannelProcessType=01;
		/** ��¼�����ֵ*/
		TraceHeads.m_fTraceMaxValue=0;
		/** ��¼�����ʱ��,΢��*/
		TraceHeads.m_dwTraceMaxtime=0;
		/** �ڲ����*/
		TraceHeads.m_dwInterpolations=0;
		/**Seismic trace offset value(if offset removal is disabled).*/
		TraceHeads.m_dwSeismicTraceOffsetValue=0;
	}
	else
	{
		/** �첨��SEGD����,��Line����������*/
		TraceHeads.m_bySensorSEGDCode=0;

		/** ���յ�ƫ����*/
		TraceHeads.m_dbPointEasting=0;
		/** ���յ㱱��γ��*/
		TraceHeads.m_dbPointNorthing=0;
		/** ���յ�߳�*/
		TraceHeads.m_fPointElevation=0;
		/** ���������ͱ��*/
		TraceHeads.m_bySensorType=1;

		/** ����ֵ����*/
		TraceHeads.m_fResistanceMax=0;
		/** ����ֵ����*/
		TraceHeads.m_fResistanceMin=0;
		/** ����ֵ*/
		TraceHeads.m_fResistanceVal=0;
		/** ���½�ϼ첨����б�Ȱٷֱ�*/
		TraceHeads.m_fTiltMax=0;
		/** ��б��ֵ*/
		TraceHeads.m_fTiltVal=0;

		/** ��������*/
		TraceHeads.m_fCapacitanceMax=0;
		/** ��������*/
		TraceHeads.m_fCapacitanceMin=0;
		/** ����ֵ���ɷ���*/
		TraceHeads.m_fCapacitanceVal=0;
		/** ��ֹ����*/
		TraceHeads.m_fCutoffFreqMax=0;
		/** ��ֹ����*/
		TraceHeads.m_fCutoffFreqMin=0;
		/** ��ֵֹ*/
		TraceHeads.m_fCutoffFreqVal=0;
		/** ©�����*/
		TraceHeads.m_fLeakageLimit=0;
		/** ©��ֵ*/
		TraceHeads.m_fLeakageVal=0;

		/**�豸����, �������ͣ�1ΪFDU��0x1C��ʾDSU428 */
		// BYTE	m_byUnitType;��ɨ������ͷ�εı���˵��
		/** �豸���к�*/
		TraceHeads.m_dwUnitSN=0;
		/** ��������*/
		TraceHeads.m_byChannelNb=BYTE(pSpread->m_arrSpread[nTraceIndexInSpread].m_dwChannelNb);
		/**�������*/
		TraceHeads.m_byAssemblyType=1;
		/** FDU �� DSU ������к�*/
		TraceHeads.m_dwFDUAssemblySN=0;
		TraceHeads.m_byLocationInFDUAssembly = 0;
		/** �ӵ�Ԫ����*/
		TraceHeads.m_bySubunitType=0x01;
		/** ���������:0 �첨��;1 ѹ���첨��*/
		TraceHeads.m_byChannelType=0;
		/** �첨��������*/

		/** ���Ƶ�Ԫ����:0x01 LCI408;0x02 LAUL408;0x03 LAUX408;0x04 LAULS408;0x05 LAUXS408;0x06 LAUL428;0x16 LRU;0x17 LAUR428;0x30 LAUX428;0x31 LCI428*/
		TraceHeads.m_byControlUnitType=0x31;
		/** ���Ƶ�Ԫ���к�*/
		TraceHeads.m_dwControlUnitSN=0;
		/** ���������̶�*/
		TraceHeads.m_byGainScale=1;
		/** ������˲���*/
		TraceHeads.m_byChannelFilter=1;
		/** ������������*/
		TraceHeads.m_byChannelDataError=0;
		/** ������༭״̬,1 ͣ��;2 �ɼ�/ �ش�����;3 �����༭*/
		TraceHeads.m_byChannelEditedStatus=1;
		/** �������������ת��ϵ��,������Ϊ0*/
		TraceHeads.m_fChannelConversionFactor=0;
		/** ���������Ӵ���*/
		TraceHeads.m_byNumberOfStacksNoisy=0;
		/** �͵��Ӵ���*/
		TraceHeads.m_byNumberOfStacksLow=0;
		/** ��������ͱ�ʶ�ţ�1 = �����;9 = ������;��ɨ������ͷ�ζ�����*/

		/** ���������:01=ԭʼ����;	02=����������;03=��أ�������;04=��أ�������;05=��̬���;06=���������*/
		TraceHeads.m_byChannelProcessType=01;
		/** ��¼�����ֵ*/
		TraceHeads.m_fTraceMaxValue=0;
		/** ��¼�����ʱ��,΢��*/
		TraceHeads.m_dwTraceMaxtime=0;
		/** �ڲ����*/
		TraceHeads.m_dwInterpolations=0;
		/**Seismic trace offset value(if offset removal is disabled).*/
		TraceHeads.m_dwSeismicTraceOffsetValue=0;
	}
	if(m_pFile)
	{
		SaveSEGDTraceHead(&TraceHeads,pScanTypeHeader);
	}
}
/**
 * @brief д��ĳһ����һ�η��͵Ĳ�������
 * @note  ĳһ�ɼ���ÿ�β���Ϊ24bits�����������74�β����󣬻��74*3=222Bytes�����ݣ�����һ���������ݰ��д��͸�������
 �ú�����222Bytes�����ݸ�ʽ��ÿ�����ֽڵ�����ת��Ϊ����������д��SEGD�ļ��С�
 * @param BYTE* lpInData,��������
  * @param int nSize���������ֽڴ�С��һ����3�ı�����ȱʡΪ222		
 * @return void
 */
void CSEGDFile::WriteTraceDataOfAFrame(BYTE* lpInData,int nSize)
{
	BYTE   byData[4];
	int i,nCount = nSize/3;
	if(!m_pFile)
		return;
	for (i=0;i<nCount;i++)
	{
		Convert3ByteIntTo4ByteAntiFlt(lpInData+3*i,byData);
		m_pFile->Write(byData,4);		
	}	
}
/**
 * @brief ��ĳһ�����ݵĶ�·���ŷ�ʽת��ΪSEGD2.1�ķ���·���ŷ�ʽ
 * @note  
 * @param int nTraceIndexInSpread,
 * @param int nTraceCountOfSpread,
 * @param CFile*	pFileData,	
 * @return void
 */
void	CSEGDFile::WriteTraceData(int nTraceIndexInSpread,int nTraceCountOfSpread,CFile*	pFileData)
{
	if(!pFileData)
		return;
	int   i;
	int   nNumberOfSamples = GetNumberOfSamples();
	ULONGLONG	  nFileLen = pFileData->GetLength();
	int   nFilePos;
	BYTE	pBuf[SAMPFRM_DATALEN];
	for(i=0;i<nNumberOfSamples;i++)
	{
		nFilePos = nTraceIndexInSpread +i*nTraceCountOfSpread;
		nFilePos *=SAMPFRM_DATALEN;
		if(nFilePos+222>=nFileLen)
			break;
		pFileData->Seek(nFilePos,CFile::begin);
		pFileData->Read(pBuf,SAMPFRM_DATALEN);
		WriteTraceDataOfAFrame(pBuf,SAMPFRM_DATALEN);
	}
}
/**
 * @brief ����1.0�汾�ĸ�ʽдSEGD �ļ�
 * @note  �ú���д������SEGD�ļ�������1.0�汾�ĸ�ʽд�����ļ�
 * @param 		
 * @return void
 */
bool CSEGDFile::SaveSEGDRev21(CFile* pFileData,COperaThread* pThread,CChannelList* pChannelList)
{
	if(!pFileData || !pThread || !pChannelList)
		return false;  
	CShotClient*	pShotClient = pThread->GetShotClient();
	if(!pShotClient)
		return false;
	
	// --------------------------�ȴ����ļ�-------------------------------------------------------------
	CString		strFileName;
	pShotClient->m_strSEGDFileName.Format(_T("%d.SEGD"),pShotClient->m_dwFileNumber);		// ԭ���ļ���
	strFileName = pShotClient->m_strNormalFilePath +_T("\\")+pShotClient->m_strSEGDFileName;	// �ļ�·��
	CFile		SegdFile;
	// �����������ļ����ȴ洢����ԭ��
	if(!SegdFile.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		// �����ļ�����,֪ͨ����
		TRACE1("Failed to Create file %s !",strFileName);
		return false;
	}
	m_pFile = &SegdFile;

	// -----------------------------------------------------------------------------------------------
	/** �ļ���� */
	m_dwFileNumber = pShotClient->m_dwFileNumber;	
	/** �����̴��룬Ĭ��13*/
	m_byManufacturerCode=13;
	/** ���������кţ�Ĭ��0*/
	m_wManufacturerSN =0;
	/** ÿ����¼�ĵ������������Ĭ��16,�޸ĺ��Ӧ����CSEGDScanTypeHeader�������*/
	m_byChnSetsCount = 16;
	/** �ⲿͷ�δ�С����Config���������ж�ȡ*/
	m_wExternalHeaderSize = 1024;						// ????????????????? ��Config�����ж�ȡ

	/** ����ɨ�����������ʣ���΢��Ϊ��λ��һ��ȡֵ��250,500,1000,2000,4000 */
	m_dwSampleRateUS = pShotClient->m_pFDUConfig->GetSampleRateByUS();
	/** �������ȣ���msΪ��λ��ȡֵ0-128000ms */
	m_dwRecordLenMS = pShotClient->m_pProcessType->m_dwRecordLen;
	/** ��������,ȡֵ��8Ϊ����������2Ϊ���Բ��� */
	m_byRecordType = 8;
	/** ��Դ���ߺţ�С�������λ */
	m_fSourceLine = pShotClient->m_pShotPoint->m_fSourceLine;
	/** ��Դ��ţ�С�������λ */
	m_fSourceNb = pShotClient->m_pShotPoint->m_fSourceNb;
	/** ��Դ������ */
	m_dwSourcePointIndex = pShotClient->m_pShotPoint->m_dwSourcePointIndex;	// ?????????????????
	/** ��Դ��� */
	m_dwFleetNb = pShotClient->m_pShotSource->m_dwShooterNb;	// ?????????????????
	
	// -----------------------------------------------------------------------------------------------
	// �Բɼ����еĲɼ������з��飬���岻ͬ��ɨ������ͷ�Ρ�
	// ��ǰ����������ɨ������ͷ�Σ�������+����g1��������+����g2���ɼ���+����g1���ɼ���+����g2
	CDWordArray		arrAuxiG1ScanType;
	CDWordArray		arrAuxiG2ScanType;
	CDWordArray		arrSeisG1ScanType;
	CDWordArray		arrSeisG2ScanType;
	//GetAuxiGain1ScanType(pShotClient->m_pSpread,arrAuxiG1ScanType);
	//GetAuxiGain2ScanType(pShotClient->m_pSpread,arrAuxiG2ScanType);
	//GetSeisGain1ScanType(pShotClient->m_pSpread,arrSeisG1ScanType);
	//GetSeisGain2ScanType(pShotClient->m_pSpread,arrSeisG2ScanType);
	GetScanTypeOfSpread(pShotClient->m_pSpread,arrAuxiG1ScanType,arrAuxiG2ScanType,arrSeisG1ScanType,arrSeisG2ScanType);
	// -----------------------------------------------------------------------------------------------
	CSEGDScanTypeHeader* pScanTypeHeader =new CSEGDScanTypeHeader[m_byChnSetsCount];
	// ����ɨ������ͷ��1: ������+����G1	
	// ��������
	pScanTypeHeader[0].m_byChnSetNb =1;
	/** ����ͨ���ĵ���*/ 
	pScanTypeHeader[0].m_wChnCount=arrAuxiG1ScanType.GetCount();
	/** ͨ������: 1Ϊ�����(���Ƶ�����9Ϊ������;*/
	pScanTypeHeader[0].m_byChnType=9;
	/** ͨ���鿪ʼʱ�䣬���ڸ���������Ϊ0,���ɼ������������ӳ�ʱ�䡣 2msΪ���������ȡֵӦ����ʵ�ʿ�ʼʱ���һ��*/
	pScanTypeHeader[0].m_wChnStartingTime = 0;											// ?????????????????????????
	/* ͨ�������ʱ�䣬2msΪ���������ȡֵӦ����ͨ����ʼʱ����ϲ������ȵ�һ�롣*/
	pScanTypeHeader[0].m_wChnEndTime = WORD(pShotClient->m_pProcessType->m_dwRecordLen/2);	// ?????????????????????????
	/** �������ͣ�0x00δȷ����0x01ΪFDU��0x1C��ʾDSU428��0x20��VE464*/
	pScanTypeHeader[0].m_byUnitType = 0x01;												// ?????????????????????????
	/** �Ŵ�����,ȡֵ��1,2,4,8,16,32,64,����1��ӦSercel��g1����,4��ӦΪg2*/
	pScanTypeHeader[0].m_dwGain = 1;													// ?????????????????????????
	/** ��ֱ����(1�ֽڣ��޷��Ŷ�������)��Ĭ��Ϊ0����Ч�ĵ��Ӵ�����
	   ������⽫��������Ϊ0����ֱ������Ϊ0�����δ���ӣ���Ϊ1����
		�������ǵ��ӵĽ��(�������δ����)����Ϊ��Ч���Ӵ���*/
	pScanTypeHeader[0].m_byVerticalStack = 1;
	// -----------------------------------------------------------------------------------------------
	// ����ɨ������ͷ��2: ������+����G2	
	// ��������
	pScanTypeHeader[1].m_byChnSetNb =2;
	/** ����ͨ���ĵ���*/ 
	pScanTypeHeader[1].m_wChnCount=arrAuxiG2ScanType.GetCount();
	/** ͨ������: 1Ϊ�����(���Ƶ�����9Ϊ������;*/
	pScanTypeHeader[1].m_byChnType=9;
	/** ͨ���鿪ʼʱ�䣬���ڸ���������Ϊ0,���ɼ������������ӳ�ʱ�䡣 2msΪ���������ȡֵӦ����ʵ�ʿ�ʼʱ���һ��*/
	pScanTypeHeader[1].m_wChnStartingTime = 0;										// ?????????????????????????
	/* ͨ�������ʱ�䣬2msΪ���������ȡֵӦ����ͨ����ʼʱ����ϲ������ȵ�һ�롣*/
	pScanTypeHeader[1].m_wChnEndTime = WORD(pShotClient->m_pProcessType->m_dwRecordLen/2);	// ?????????????????????????
	/** �������ͣ�0x00δȷ����0x01ΪFDU��0x1C��ʾDSU428��0x20��VE464*/
	pScanTypeHeader[1].m_byUnitType = 0x01;											// ?????????????????????????
	/** �Ŵ�����,ȡֵ��1,2,4,8,16,32,64,����1��ӦSercel��g1����,4��ӦΪg2*/
	pScanTypeHeader[1].m_dwGain = 4;												// ?????????????????????????
	/** ��ֱ����(1�ֽڣ��޷��Ŷ�������)��Ĭ��Ϊ0����Ч�ĵ��Ӵ�����
	   ������⽫��������Ϊ0����ֱ������Ϊ0�����δ���ӣ���Ϊ1����
		�������ǵ��ӵĽ��(�������δ����)����Ϊ��Ч���Ӵ���*/
	pScanTypeHeader[1].m_byVerticalStack = 1;
	// -----------------------------------------------------------------------------------------------
	// ����ɨ������ͷ��3: �����+����G1	
	// ��������
	pScanTypeHeader[2].m_byChnSetNb =3;
	/** ����ͨ���ĵ���*/ 
	pScanTypeHeader[2].m_wChnCount=arrSeisG1ScanType.GetCount();
	/** ͨ������: 1Ϊ�����(���Ƶ�����9Ϊ������;*/
	pScanTypeHeader[2].m_byChnType=1;
	/** ͨ���鿪ʼʱ�䣬���ڸ���������Ϊ0,���ɼ������������ӳ�ʱ�䡣 2msΪ���������ȡֵӦ����ʵ�ʿ�ʼʱ���һ��*/
	pScanTypeHeader[2].m_wChnStartingTime = 0;										// ?????????????????????????
	/* ͨ�������ʱ�䣬2msΪ���������ȡֵӦ����ͨ����ʼʱ����ϲ������ȵ�һ�롣*/
	pScanTypeHeader[2].m_wChnEndTime = WORD(pShotClient->m_pProcessType->m_dwRecordLen/2);	// ?????????????????????????
	/** �������ͣ�0x00δȷ����0x01ΪFDU��0x1C��ʾDSU428��0x20��VE464*/
	pScanTypeHeader[2].m_byUnitType = 0x01;											// ?????????????????????????
	/** �Ŵ�����,ȡֵ��1,2,4,8,16,32,64,����1��ӦSercel��g1����,4��ӦΪg2*/
	pScanTypeHeader[2].m_dwGain = 1;												// ?????????????????????????
	/** ��ֱ����(1�ֽڣ��޷��Ŷ�������)��Ĭ��Ϊ0����Ч�ĵ��Ӵ�����
	   ������⽫��������Ϊ0����ֱ������Ϊ0�����δ���ӣ���Ϊ1����
		�������ǵ��ӵĽ��(�������δ����)����Ϊ��Ч���Ӵ���*/
	pScanTypeHeader[2].m_byVerticalStack = 1;
	// -----------------------------------------------------------------------------------------------
	// ����ɨ������ͷ��4: �����+����G2	
	// ��������
	pScanTypeHeader[3].m_byChnSetNb = 4;
	/** ����ͨ���ĵ���*/ 
	pScanTypeHeader[3].m_wChnCount=arrSeisG2ScanType.GetCount();
	/** ͨ������: 1Ϊ�����(���Ƶ�����9Ϊ������;*/
	pScanTypeHeader[3].m_byChnType=1;
	/** ͨ���鿪ʼʱ�䣬���ڸ���������Ϊ0,���ɼ������������ӳ�ʱ�䡣 2msΪ���������ȡֵӦ����ʵ�ʿ�ʼʱ���һ��*/
	pScanTypeHeader[3].m_wChnStartingTime = 0;										// ?????????????????????????
	/* ͨ�������ʱ�䣬2msΪ���������ȡֵӦ����ͨ����ʼʱ����ϲ������ȵ�һ�롣*/
	pScanTypeHeader[3].m_wChnEndTime = WORD(pShotClient->m_pProcessType->m_dwRecordLen/2);	// ?????????????????????????
	/** �������ͣ�0x00δȷ����0x01ΪFDU��0x1C��ʾDSU428��0x20��VE464*/
	pScanTypeHeader[3].m_byUnitType = 0x01;											// ?????????????????????????
	/** �Ŵ�����,ȡֵ��1,2,4,8,16,32,64,����1��ӦSercel��g1����,4��ӦΪg2*/
	pScanTypeHeader[3].m_dwGain = 4;												// ?????????????????????????
	/** ��ֱ����(1�ֽڣ��޷��Ŷ�������)��Ĭ��Ϊ0����Ч�ĵ��Ӵ�����
	   ������⽫��������Ϊ0����ֱ������Ϊ0�����δ���ӣ���Ϊ1����
		�������ǵ��ӵĽ��(�������δ����)����Ϊ��Ч���Ӵ���*/
	pScanTypeHeader[3].m_byVerticalStack = 1;
	// ----------------------------------------------------------------------------------------------------
	// ��չͷ��
	SetExtendedHeader(pThread,pChannelList);
	// ----------------------------------------------------------------------------------------------------
	// �ⲿͷ��
	/** ���ڻ��ߵ���ϵͳ��Ϣ */
	// m_strShooterInfo;								// ?????????????????????????
	/** ����Config�������õ��û���Ϣ*/
	m_strConfigUserInfo;								// ?????????????????????????
	/** ʩ�����ڵ���Դע��*/
	m_strSourceComment = pShotClient->m_pShotSource->m_strComment;
	//-----------------------------------------------------------------------------------------------------
	// ��������ͷ������
	SaveSEGDHead(pScanTypeHeader);

	//------------------------------------------------------------------------------------------------------
	// �������������
	INT_PTR		i;
	INT_PTR		nCount;
	// ��һ��ɨ�����ͣ�������������ΪG1
	nCount = arrAuxiG1ScanType.GetCount();
	for(i=0;i<nCount;i++)
	{
		WriteAuxiTraceHeader(1,arrAuxiG1ScanType[i],pScanTypeHeader,pThread,pChannelList);
		WriteTraceData(arrAuxiG1ScanType[i],m_ExtendedHeader.m_dwTraceCount,pFileData);
	}
	// �ڶ���ɨ�����ͣ�������������ΪG2
	nCount = arrAuxiG2ScanType.GetCount();
	for(i=0;i<nCount;i++)
	{
		WriteAuxiTraceHeader(2,arrAuxiG2ScanType[i],pScanTypeHeader+1,pThread,pChannelList);
		WriteTraceData(arrAuxiG2ScanType[i],m_ExtendedHeader.m_dwTraceCount,pFileData);
	}
	// ������ɨ�����ͣ������������ΪG1
	nCount = arrSeisG1ScanType.GetCount();
	for(i=0;i<nCount;i++)
	{
		WriteAuxiTraceHeader(3,arrSeisG1ScanType[i],pScanTypeHeader+2,pThread,pChannelList);
		WriteTraceData(arrSeisG1ScanType[i],m_ExtendedHeader.m_dwTraceCount,pFileData);
	}
	// ���ĸ�ɨ�����ͣ������������ΪG2
	nCount = arrSeisG2ScanType.GetCount();
	for(i=0;i<nCount;i++)
	{
		WriteAuxiTraceHeader(4,arrSeisG2ScanType[i],pScanTypeHeader+3,pThread,pChannelList);
		WriteTraceData(arrSeisG2ScanType[i],m_ExtendedHeader.m_dwTraceCount,pFileData);
	}
	// �ر��ļ�
	SegdFile.Flush();
	SegdFile.Close();
	m_pFile = NULL;
	return true;	
}
#endif