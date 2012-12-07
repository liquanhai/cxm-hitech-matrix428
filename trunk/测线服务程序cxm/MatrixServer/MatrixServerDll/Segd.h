#ifndef _SEGD_H
#define _SEGD_H
#define COUNT_SCAN_TYPE_HEADER		16
#define SIZE_BUFFER					256
/**
* @struct Segd_Standard_Header_Struct
* @brief Segd�ļ���׼ͷ�ṹ��
*/
typedef struct Segd_Standard_Header_Struct
{
	/** ������*/
	unsigned int m_uiSampleRate;
	/** ��������*/
	int m_iSampleLength;
	/** ����ʱ��*/
	unsigned int m_uiSampleTime;
	/** ��������Ŀ*/
	int m_iAuxTraceNum;
	/* �ɼ�����Ŀ*/
	int m_iAcqTraceNum;
	/** �ܵ���*/
	int m_iTotalTraceNum;
	/** �ں�*/
	unsigned int m_uiShotNo;

	//˵�����ֽ���������
	string m_pFileNumberGeneral1;//��λ���ļ���� (0-9999),2,0327
	string m_pFormatCodeGeneral1;//��ʽ����,2,8058
	string m_pGeneralConstantsGeneral1;//��ͨ����,6,000000000005
	string m_pLastTwoDigitsOfYearGeneral1;//��ݵ������λ��(0-99),1,12
	string m_pNumberAdditionalBlocksGeneral1;//��ͨͷ���ж������ݿ���Ŀ,H,2
	string m_pJulianDayGeneral1;//�����գ�3 λ��(1-366),L+1,187
	string m_pHourOfDayGeneral1;//һ���е�Сʱ��0-23��,1,08
	string m_pMinuteOfHourGeneral1;//Сʱ�еķ��ӣ�0-59��,1,36
	string m_pSecondOfMinuteGeneral1;//�����е����ӣ�0-59��,1,06
	string m_pManufacturerCodeGeneral1;//�����̴���,1,13
	string m_pManufacturerSerialNumberGeneral1;//���������к�,2,0000
	string m_pBytesPerScanGeneral1;//ÿ��ɨ���ֽ���,3,000000
	string m_pBaseScanIntervalGeneral1;//����ɨ����,1,10
	string m_pPolarityGeneral1;//����,H,0
	string m_pNotUsedGeneral1;//δʹ��,L+1,000
	string m_pRecordTypeGeneral1;//��¼����,H,8
	string m_pRecordLengthGeneral1;//��¼����,L+1,fff
	string m_pScanTypePerRecordGeneral1;//ÿ����¼��ɨ������,1,01
	string m_pNumberChannelSetsPerRecordGeneral1;//ÿ����¼�ĵ��������Ŀ,1,16
	string m_pNumberSampleSkew32ByteExtensionsGeneral1;//����ʱ�� 32 �ֽ���չ����Ŀ,1,00
	string m_pExtendedHeaderLengthGeneral1;//��չͷ�γ���,1,32
	string m_pExternalHeaderLengthGeneral1;//�ⲿͷ�γ���,1,32

	string m_pExpandedFileNumberGeneral2;//��չ�ļ����,3,327
	string m_pExpandedChannelSetsGeneral2;//��չ�������/ ɨ�����ͣ�δʹ�ã�,2,0000
	string m_pExtendedHeaderBlocksGeneral2;//��չͷ�����ݿ飨δʹ�ã�,2,0000
	string m_pExternalHeaderBlocksGeneral2;//�ⲿͷ�����ݿ�,2,00
	string m_pNotUsed1General2;//δʹ��,1,00
	string m_pSegdRevisionNumberGeneral2;//SEG-D �汾��,2,0201
	string m_pNumberBlocksGeneralTrailerGeneral2;//��ͨβ�����ݿ���Ŀ,2,0000
	string m_pExpandedRecordLengthGeneral2;//��չ��¼���ȣ�0-128000 ���룩,3,4000
	string m_pNotUsed2General2;//δʹ��,1,00
	string m_pGeneralHeaderBlockNumberGeneral2;//��ͨͷ�����ݿ���,1,02
	string m_pNotUsed3General2;//δʹ��,13,00000000000000000000000000

	string m_pExpandedFileNumberGeneral3;//��չ�ļ����,3,000147
	string m_pSourceLineNumberGeneral3;//��Դ���ߺ�(0-99999.99),5,0000030000
	string m_pSourcePointNumberGeneral3;//��Դ���(0-99999.99),5,00001e0000
	string m_pSourcePointIndexGeneral3;//��Դ������ (1-9),1,01
	string m_pPhaseControlGeneral3;//��λ���ƣ�δ��¼�ģ�,1,00
	string m_pVibratorTypeGeneral3;//�ɿ���Դ���ͣ�δ��¼�ģ�,1,00
	string m_pPhaseAngleGeneral3;//��λ�ǣ�δ��¼�ģ�,2,0000
	string m_pGeneralHeaderBlockNumberGeneral3;//��ͨͷ�����ݿ���,1,03
	string m_pSourceSetNumberGeneral3;//��Դ���,1,01
	string m_pNotUsedGeneral3;//δʹ��,12,000000000000000000000000

	//˵�����ֽ���������1������2������3���˺��ͬ����3������16
	string m_pScanTypeHeaderScan[16];//ɨ������ͷ��,1,01,01,00...
	string m_pChannelSetNumberScan[16];//��������,1,01,02,00...
	string m_pChannelSetStartingTimeScan[16];//���������ʼʱ��,2,00,00,00...
	string m_pChannelSetEndTimeScan[16];//����������ʱ��,2,2000,2000,00...
	string m_pDescaleMultiplierScan[16];//��С��������,2,6db7,6db7,0000...
	string m_pNumberChannelsOfChannelSetScan[16];//�˵�������е������Ŀ,2,0002,0012,0000...
	string m_pChannelTypeIdentificationScan[16];//��������ͱ�ʶ,H,9,1,0...
	string m_pNotUsedScan[16];//δʹ��,L,0,0,0...
	string m_pNumberSubscansExponentScan[16];//��ɨ��ָ����Ŀ,H,0,0,00...
	string m_pChannelGainControlMethodScan[16];//�����������Ʒ������̶����棩,L,3,3,00...
	string m_pAliasFilterFrequency3dBPointScan[16];//3dB �㴦�Ļ���˲���Ƶ��,2,0400,0400,0000...
	string m_pAliasFilterSlopeScan[16];//����˲���б��,2,0370,0370,0000...
	string m_pLowCutFilterFrequencyScan[16];//�ͽ��˲���Ƶ��,2,0000,0000,0000...
	string m_pLowCutFilterSlopeScan[16];//�ͽ��˲���б��,2,0000,0000,0000...
	string m_pFirstNotchFrequencyScan[16];//��һ�ݲ�Ƶ��,2,0000,0000,0000...
	string m_pSecondNotchFrequencyScan[16];//�ڶ��ݲ�Ƶ��,2,0000,0000,0000...
	string m_pThirdNotchFrequencyScan[16];//�����ݲ�Ƶ��,2,0000,0000,0000...
	string m_pExtendedChannelSetNumberScan[16];//��չ��������,2,0000,0000,0000...
	string m_pExtendedHeaderFlagScan[16];//��չͷ�α��,H,0,0,0...
	string m_pTraceHeaderExtensionsScan[16];//��ͷ��չ,L,7,7,0...
	string m_pVerticalStackScan[16];//��ֱ����,1,01,01,00...
	string m_pStreamerCableNumberScan[16];//���µ��º�,1,00,00,00...
	string m_pArrayFormingScan[16];//������ɣ���������ɣ�,1,01,01,00...

	string m_pAcquisitionLengthExtended;//�ɼ�����,4,4000
	string m_pSampleRateExtended;//������,4,1000
	string m_pTotalNumberTracesExtended;//��¼������,4,14
	string m_pNumberAuxesExtended;//��������Ŀ,4,02
	string m_pNumberSeisTracesExtended;//�����¼����Ŀ,4,12
	string m_pNumberDeadSeisTracesExtended;//ͣ�͵����¼����Ŀ,4,00
	string m_pNumberLiveSeisTracesExtended;//������¼����Ŀ,4,12
	string m_pTypeSourceExtended;//��Դ����,4,01
	string m_pNumberSamplesInTraceExtended;//��¼����������Ŀ,4,4001
	string m_pShotNumberExtended;//�ں�,4,01
	string m_pTBWindowExtended;//TB ����,4,3000.000000
	string m_pTestRecordTypeExtended;//���Լ�¼����,4,00
	string m_pSpreadFirstLineExtended;//������һ������,4,01
	string m_pSpreadFirstNumberExtended;//������һ������,4,34
	string m_pSpreadNumberExtended;//���б��,4,01
	string m_pSpreadTypeExtended;//��������,4,01
	string m_pTimebreakExtended;//ʱ���ź�,4,00
	string m_pUpholeTimeExtended;//����ʱ��,4,00
	string m_pBlasterIdExtended;//��ը����ʶ��,4,01
	string m_pBlasterStatusExtended;//��ը��״̬,4,02
	string m_pRefractionDelayExtended;//�����ӳ�,4,00
	string m_pTBtoT0TimeExtended;//Tb �� T0 ʱ��,4,00
	string m_pInternalTimeBreakExtended;//�ڲ�ʱ���ź�,4,00
	string m_pPrestackWithinFieldUnitsExtended;//Ұ���豸��Ԥ����,4,00
	string m_pNoiseEliminationTypeExtended;//������������,4,01
	string m_pLowTracePercentageExtended;//�ͼ�¼���ٷֱ�,4,00
	string m_pLowTraceValueExtended;//�ͼ�¼��ֵ,4,00
	string m_pNumberWindowsOrWindowLengthExtended;//������Ŀ,4,00
	string m_pHistoricEditingTypeOrOverlapExtended;//��ʷ�༭����,4,00
	string m_pNoisyTracePercentageExtended;//������¼���ٷֱ�,4,00
	string m_pHistoricRangeExtended;//��ʷ��Χ,4,00
	string m_pHistoricTaperLengthExtended;//��ʷ׶�γ��� 2 ��ָ��,4,00
	string m_pThresholdHoldOrNotExtended;//�ż�ֵ����/ �仯,4,00
	string m_pHistoricThresholdInitValueExtended;//��ʷ�ż�ֵ��ʼֵ,4,00
	string m_pHistoricZeroingLengthExtended;//��ʷ���㳤��,4,00
	string m_pTypeProcessExtended;//��������,4,01
	string m_pAcquisitionTypeTablesExtended;//�ɼ����ͱ�,128,00
	string m_pThresholdTypeTablesExtended;//�ż�ֵ���ͱ�,128,00
	string m_pStackingFoldExtended;//���Ӵ���,4,01
	string m_pNotUsed1Extended;//δʹ��,80,00
	string m_pRecordLengthExtended;//��¼����,4,4000
	string m_pAutocorrelationPeakTimeExtended;//����ط�ֵʱ��,4,00
	string m_pNotUsed2Extended;//δʹ��,4,00
	string m_pCorrelationPilotNoExtended;//��زο��źű��,4,00
	string m_pPilotLengthExtended;//�ο��źų���,4,00
	string m_pSweepLengthExtended;//ɨ�賤��,4,00
	string m_pAcquisitionNumberExtended;//�ɼ���,4,01
	string m_pMaxOfMaxAuxExtended;//��ศ���������ֵ,4,3041785.250000
	string m_pMaxOfMaxSeisExtended;//����������ֵ,4,-614945.500000
	string m_pDumpStackingFoldExtended;//ת�����Ӵ���,4,01
	string m_pTapeLabelExtended;//�Ŵ���ǩ,16,label
	string m_pTapeNumberExtended;//�Ŵ���,4,50
	string m_pSoftwareVersionExtended;//����汾,16,4.0
	string m_pDateExtended;//����,12,05 Jul 2012
	string m_pSourceEastingExtended;//��Դƫ����,8,0
	string m_pSourceNorthingExtended;//��Դ����γ�Ȳ�,8,0
	string m_pSourceElevationExtended;//��Դ�߳�,4,0.000000
	string m_pSlipSweepModeUsedExtended;//���õĻ���ɨ��ģʽ,4,00
	string m_pFilesPerTapeExtended;//ÿ���Ŵ����ļ���,4,2000
	string m_pFileCountExtended;//�ļ�����,4,01
	string m_pAcquisitionErrorDescriptionExtended;//�ɼ�����˵��,160,
	string m_pFilterTypeExtended;//�˲�������,4,02
	string m_pStackDumpedExtended;//������ת��,4,00
	string m_pStackSignExtended;//���ӷ��ţ���ǰ��,4,01
	string m_pPRMTiltCorrectionUsedExtended;//���õ� PRM ��б��У��,4,00
	string m_pSwathNameExtended;//������,64,D5
	string m_pOperatingModeExtended;//����ģʽ,4,01
	string m_pReserved1Extended;//����,4,79
	string m_pNoLogExtended;//�޼�¼,4,00
	string m_pListeningTimeExtended;//����ʱ��,4,4000
	string m_pTypeDumpExtended;//ת������,4,00
	string m_pReserved2Extended;//����,4,00
	string m_pSwathIdExtended;//���� Id,4,01
	string m_pSeismicTraceOffsetRemovalDisabledExtended;//,4,00
	string m_pGPSTimeAcquisitionTimeBreakExtended;//,8,0003a4ac0c90344f
	string m_pAlignedGPSTimeAcquisitionExtended;//,8,0000000000000000
	string m_pNotUsed3Extended;//δʹ��,132,000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

	char* m_pConcatenationOfExternal;//�ⲿͷ��,m_pExternalHeaderLengthGeneral1*32,*SHOTPRO SP#    1/SL#    3.0/SN#   30.0/SI#1/SEQ# 1/STA:2/CTB:00.000/UH:000.0
}m_oSegdStandardHeaderStruct;

typedef struct Segd_Trace_Header_Struct
{
	//˵�����ֽ������ɼ������ݣ�����������
	string m_pFileNumberTrace;//��λ���ļ���(0-9999),2,0327,0327
	string m_pScanTypeNumberTrace;//ɨ�����ͱ��,1,01,01
	string m_pChannelSetNumberTrace;//��������,1,02,01
	string m_pTraceNumberTrace;//��¼�����,2,0001,0001
	string m_pFirstTimingWordTrace;//��һ����ʱ��,3,00,00
	string m_pTraceHeaderExtensionTrace;//��ͷ��չ,1,07,07
	string m_pSampleSkewTrace;//����ʱ��,1,00,00
	string m_pTraceEditTrace;//��¼���༭,1,00,00
	string m_pTimeBreakWindowTrace;//ʱ���źŴ���,3,00,00
	string m_pExtendedChannelSetNumberTrace;//��չ��������,2,0000,0000
	string m_pExtendedFileNumberTrace;//��չ�ļ����,3,000147,000147

	string m_pReceiverLineNumberTrace1;//���յ���ߺ�,3,01,00
	string m_pReceiverPointNumberTrace1;//���յ��,3,34,01
	string m_pReceiverPointIndexTrace1;//���յ�����,1,01,01
	string m_pNumberSamplesPerTraceTrace1;//ÿ����¼��������Ŀ,3,4001,4001
	string m_pExtendedReceiverLineNumberTrace1;//��չ���յ���ߺ�,5,0000000000,0000000000
	string m_pExtendedReceiverPointNumberTrace1;//��չ���յ��,5,0000000000,0000000000
	string m_pSensorSEGDCodeTrace1;//�첨�� SEGD ����,1,02,00
	string m_pNotUsedTrace1;//δʹ��,11,0000000000000000000000,0000000000000000000000

	string m_pReceiverPointEastingTrace2;//���յ�ƫ����,8,0,0
	string m_pReceiverPointNorthingTrace2;//���յ㱱��γ�Ȳ�,8,0,0
	string m_pReceiverPointElevationTrace2;//���յ�߳�,4,0.000000,0.000000
	string m_pSensorTypeNumberTrace2;//�첨�����ͱ�ţ�1 �� 9��,1,01,00
	string m_pNotUsedTrace2;//δʹ��,3,000000,000000
	string m_pDSDIdentificationNoTrace2;//δʹ��,4,00,00
	string m_pExtendedTraceNoTrace2;//��չ��¼�����,4,01,01

	string m_pResistanceLowLimitTrace3;//��������,4,300.000000,0.000000
	string m_pResistanceHighLimitTrace3;//��������,4,500.000000,0.000000
	string m_pResistanceResistanceValueTrace3;//����ֵ,4,1904.939941,0.000000
	string m_pTiltLimitTrace3;//��б�Ƚ���,4,15.000000,0.000000
	string m_pTiltValueTrace3;//��б��ֵ,4,N-,0.000000
	string m_pResistanceErrorTrace3;//�������,1,01,00
	string m_pTiltErrorTrace3;//��б�����,1,00,00
	string m_pNotUsedTrace3;//δʹ��,10,00000000000000000000,00000000000000000000

	string m_pCapacitanceLowLimitTrace4;//��������,4,N-,0.000000
	string m_pCapacitanceHighLimitTrace4;//��������,4,N-,0.000000
	string m_pCapacitanceValueTrace4;//����ֵ,4,N-,0.000000
	string m_pCutOffLowLimitTrace4;//��ֹ����,4,N-,0.000000
	string m_pCutOffHighLimitsTrace4;//��ֹ����,4,N-,0.000000
	string m_pCutOffValueTrace4;//��ֵֹ,4,N-,0.000000
	string m_pCapacitanceErrorTrace4;//�������,1,00,00
	string m_pCutOffErrorTrace4;//��ֹ���,1,00,00
	string m_pNotUsedTrace4;//δʹ��,6,000000000000,000000000000

	string m_pLeakageLimitTrace5;//©�����,4,5.000000,0.000000
	string m_pLeakageValueTrace5;//©��ֵ,4,5.000000,0.000000
	string m_pNotUsed1Trace5;//δʹ��,16,00000000000000000000000000000000,00000000000000000000000000000000
	string m_pLeakageErrorTrace5;//©�����,1,00,00
	string m_pNotUsed2Trace5;//δʹ��,7,00000000000000,00000000000000

	string m_pUnitTypeTrace6;//�豸����,1,01,01
	string m_pUnitSerialNumberTrace6;//�豸���к�,3,6104422,4819236
	string m_pChannelNumberTrace6;//��������,1,01,01
	string m_pSpare1Trace6;//����,3,000000,000000
	string m_pAssemblyTypeTrace6;//�������,1,03,04
	string m_pFDUorDSUAssemblySerialNumberTrace6;//FDU �� DSU ������к�,3,1791352,4819236
	string m_pLocationInFDUorDSUAssemblyTrace6;//�� FDU �� DSU����е�λ��,1,02,01
	string m_pSpare2Trace6;//����,3,000000,000000
	string m_pSubunitTypeTrace6;//FDU �� DSU �豸����,1,01,21
	string m_pChannelTypeTrace6;//���������,1,00,00
	string m_pSpare3Trace6;//����,2,0000,0000
	string m_pSensorSensitivityTrace6;//�첨��������,4,4294967296.000000,4294967296.000000
	string m_pNotUsedTrace6;//δʹ��,8,0000000000000000,0000000000000000

	string m_pControlUnitTypeTrace7;//���Ƶ�Ԫ����,1,02,49
	string m_pControlUnitSerialNumberTrace7;//���Ƶ�Ԫ���к�,3,17693,2442269
	string m_pChannelGainScaleTrace7;//���������̶�,1,02,02
	string m_pChannelFilterTrace7;//������˲���,1,02,02
	string m_pChannelDataErrorTrace7;//�����������������Χ,1,00,00
	string m_pChannelEditedStatusTrace7;//������༭״̬,1,00,00
	string m_pChannelSampleTomVConversionFactorTrace7;//�������������ת��ϵ��,4,0.000067,0.000000
	string m_pNumberOfStacksNoisyTrace7;//���������Ӵ���,1,00,00
	string m_pNumberOfStacksLowTrace7;//�͵��Ӵ���,1,00,00
	string m_pChannelTypeIdTrace7;//��������ͱ�ʶ��,1,01,09
	string m_pChannelProcessTrace7;//���������,1,01,01
	string m_pTraceMaxValueTrace7;//��¼�����ֵ,4,0.000000,0.000000
	string m_pTraceMaxTimeTrace7;//��¼�����ʱ��,4,00,00
	string m_pNumberInterpolationsTrace7;//�ڲ����,4,00,00
	string m_pSeismicTraceOffsetValueTrace7;//δʹ��,4,00,00	
}m_oSegdTraceHeaderStruct;
/**
* @struct Segd_Data_Header_Struct
* @brief Segd�ļ�����ͷ�ṹ��
*/
typedef struct Segd_Data_Header_Struct
{
	/** ����վ���*/
	int m_iPointIndex;
	/** ����վ�ߺ�*/
	int m_iLineIndex;
	/** λ�����*/
	unsigned int m_uiLocation;
	/** ���ݵ�ͷ*/
	m_oSegdTraceHeaderStruct m_oSegdTH;
}m_oSegdDataHeaderStruct;
/**
* @struct Segd_File_Struct
* @brief Segd�ļ��洢�ṹ��
*/
typedef struct Segd_File_Struct
{
	/** Segd�ļ�����·��*/
	string m_strPath;
	/** Segd��׼ͷ�ļ�*/
	m_oSegdStandardHeaderStruct m_oSegdSH;
	/** Segd����ͷ����*/
	list<m_oSegdDataHeaderStruct*>* m_pSegdDHList;
	/** Segd���ݻ�����ָ�룬���������ݷź���*/
	char* m_pSegdDataBuf;
	/** Segd���ݻ���������*/
	unsigned int m_uiSegdDataBufLength;
}m_oSegdFileStruct;
#endif