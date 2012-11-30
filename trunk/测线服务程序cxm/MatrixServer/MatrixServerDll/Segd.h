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
	char m_pFileNumberGeneral1[SIZE_BUFFER];//��λ���ļ���� (0-9999),2,0327
	char m_pFormatCodeGeneral1[SIZE_BUFFER];//��ʽ����,2,8058
	char m_pGeneralConstantsGeneral1[SIZE_BUFFER];//��ͨ����,6,000000000005
	char m_pLastTwoDigitsOfYearGeneral1[SIZE_BUFFER];//��ݵ������λ��(0-99),1,12
	char m_pNumberAdditionalBlocksGeneral1[SIZE_BUFFER];//��ͨͷ���ж������ݿ���Ŀ,H,2
	char m_pJulianDayGeneral1[SIZE_BUFFER];//�����գ�3 λ��(1-366),L+1,187
	char m_pHourOfDayGeneral1[SIZE_BUFFER];//һ���е�Сʱ��0-23��,1,08
	char m_pMinuteOfHourGeneral1[SIZE_BUFFER];//Сʱ�еķ��ӣ�0-59��,1,36
	char m_pSecondOfMinuteGeneral1[SIZE_BUFFER];//�����е����ӣ�0-59��,1,06
	char m_pManufacturerCodeGeneral1[SIZE_BUFFER];//�����̴���,1,13
	char m_pManufacturerSerialNumberGeneral1[SIZE_BUFFER];//���������к�,2,0000
	char m_pBytesPerScanGeneral1[SIZE_BUFFER];//ÿ��ɨ���ֽ���,3,000000
	char m_pBaseScanIntervalGeneral1[SIZE_BUFFER];//����ɨ����,1,10
	char m_pPolarityGeneral1[SIZE_BUFFER];//����,H,0
	char m_pNotUsedGeneral1[SIZE_BUFFER];//δʹ��,L+1,000
	char m_pRecordTypeGeneral1[SIZE_BUFFER];//��¼����,H,8
	char m_pRecordLengthGeneral1[SIZE_BUFFER];//��¼����,L+1,fff
	char m_pScanTypePerRecordGeneral1[SIZE_BUFFER];//ÿ����¼��ɨ������,1,01
	char m_pNumberChannelSetsPerRecordGeneral1[SIZE_BUFFER];//ÿ����¼�ĵ��������Ŀ,1,16
	char m_pNumberSampleSkew32ByteExtensionsGeneral1[SIZE_BUFFER];//����ʱ�� 32 �ֽ���չ����Ŀ,1,00
	char m_pExtendedHeaderLengthGeneral1[SIZE_BUFFER];//��չͷ�γ���,1,32
	char m_pExternalHeaderLengthGeneral1[SIZE_BUFFER];//�ⲿͷ�γ���,1,32

	char m_pExpandedFileNumberGeneral2[SIZE_BUFFER];//��չ�ļ����,3,327
	char m_pExpandedChannelSetsGeneral2[SIZE_BUFFER];//��չ�������/ ɨ�����ͣ�δʹ�ã�,2,0000
	char m_pExtendedHeaderBlocksGeneral2[SIZE_BUFFER];//��չͷ�����ݿ飨δʹ�ã�,2,0000
	char m_pExternalHeaderBlocksGeneral2[SIZE_BUFFER];//�ⲿͷ�����ݿ�,2,00
	char m_pNotUsed1General2[SIZE_BUFFER];//δʹ��,1,00
	char m_pSegdRevisionNumberGeneral2[SIZE_BUFFER];//SEG-D �汾��,2,0201
	char m_pNumberBlocksGeneralTrailerGeneral2[SIZE_BUFFER];//��ͨβ�����ݿ���Ŀ,2,0000
	char m_pExpandedRecordLengthGeneral2[SIZE_BUFFER];//��չ��¼���ȣ�0-128000 ���룩,3,4000
	char m_pNotUsed2General2[SIZE_BUFFER];//δʹ��,1,00
	char m_pGeneralHeaderBlockNumberGeneral2[SIZE_BUFFER];//��ͨͷ�����ݿ���,1,02
	char m_pNotUsed3General2[SIZE_BUFFER];//δʹ��,13,00000000000000000000000000

	char m_pExpandedFileNumberGeneral3[SIZE_BUFFER];//��չ�ļ����,3,000147
	char m_pSourceLineNumberGeneral3[SIZE_BUFFER];//��Դ���ߺ�(0-99999.99),5,0000030000
	char m_pSourcePointNumberGeneral3[SIZE_BUFFER];//��Դ���(0-99999.99),5,00001e0000
	char m_pSourcePointIndexGeneral3[SIZE_BUFFER];//��Դ������ (1-9),1,01
	char m_pPhaseControlGeneral3[SIZE_BUFFER];//��λ���ƣ�δ��¼�ģ�,1,00
	char m_pVibratorTypeGeneral3[SIZE_BUFFER];//�ɿ���Դ���ͣ�δ��¼�ģ�,1,00
	char m_pPhaseAngleGeneral3[SIZE_BUFFER];//��λ�ǣ�δ��¼�ģ�,2,0000
	char m_pGeneralHeaderBlockNumberGeneral3[SIZE_BUFFER];//��ͨͷ�����ݿ���,1,03
	char m_pSourceSetNumberGeneral3[SIZE_BUFFER];//��Դ���,1,01
	char m_pNotUsedGeneral3[SIZE_BUFFER];//δʹ��,12,000000000000000000000000

	//˵�����ֽ���������1������2������3���˺��ͬ����3������16
	char m_pScanTypeHeaderScan[16][SIZE_BUFFER];//ɨ������ͷ��,1,01,01,00...
	char m_pChannelSetNumberScan[16][SIZE_BUFFER];//��������,1,01,02,00...
	char m_pChannelSetStartingTimeScan[16][SIZE_BUFFER];//���������ʼʱ��,2,00,00,00...
	char m_pChannelSetEndTimeScan[16][SIZE_BUFFER];//����������ʱ��,2,2000,2000,00...
	char m_pDescaleMultiplierScan[16][SIZE_BUFFER];//��С��������,2,6db7,6db7,0000...
	char m_pNumberChannelsOfChannelSetScan[16][SIZE_BUFFER];//�˵�������е������Ŀ,2,0002,0012,0000...
	char m_pChannelTypeIdentificationScan[16][SIZE_BUFFER];//��������ͱ�ʶ,H,9,1,0...
	char m_pNotUsedScan[16][SIZE_BUFFER];//δʹ��,L,0,0,0...
	char m_pNumberSubscansExponentScan[16][SIZE_BUFFER];//��ɨ��ָ����Ŀ,H,0,0,00...
	char m_pChannelGainControlMethodScan[16][SIZE_BUFFER];//�����������Ʒ������̶����棩,L,3,3,00...
	char m_pAliasFilterFrequency3dBPointScan[16][SIZE_BUFFER];//3dB �㴦�Ļ���˲���Ƶ��,2,0400,0400,0000...
	char m_pAliasFilterSlopeScan[16][SIZE_BUFFER];//����˲���б��,2,0370,0370,0000...
	char m_pLowCutFilterFrequencyScan[16][SIZE_BUFFER];//�ͽ��˲���Ƶ��,2,0000,0000,0000...
	char m_pLowCutFilterSlopeScan[16][SIZE_BUFFER];//�ͽ��˲���б��,2,0000,0000,0000...
	char m_pFirstNotchFrequencyScan[16][SIZE_BUFFER];//��һ�ݲ�Ƶ��,2,0000,0000,0000...
	char m_pSecondNotchFrequencyScan[16][SIZE_BUFFER];//�ڶ��ݲ�Ƶ��,2,0000,0000,0000...
	char m_pThirdNotchFrequencyScan[16][SIZE_BUFFER];//�����ݲ�Ƶ��,2,0000,0000,0000...
	char m_pExtendedChannelSetNumberScan[16][SIZE_BUFFER];//��չ��������,2,0000,0000,0000...
	char m_pExtendedHeaderFlagScan[16][SIZE_BUFFER];//��չͷ�α��,H,0,0,0...
	char m_pTraceHeaderExtensionsScan[16][SIZE_BUFFER];//��ͷ��չ,L,7,7,0...
	char m_pVerticalStackScan[16][SIZE_BUFFER];//��ֱ����,1,01,01,00...
	char m_pStreamerCableNumberScan[16][SIZE_BUFFER];//���µ��º�,1,00,00,00...
	char m_pArrayFormingScan[16][SIZE_BUFFER];//������ɣ���������ɣ�,1,01,01,00...

	char m_pAcquisitionLengthExtended[SIZE_BUFFER];//�ɼ�����,4,4000
	char m_pSampleRateExtended[SIZE_BUFFER];//������,4,1000
	char m_pTotalNumberTracesExtended[SIZE_BUFFER];//��¼������,4,14
	char m_pNumberAuxesExtended[SIZE_BUFFER];//��������Ŀ,4,02
	char m_pNumberSeisTracesExtended[SIZE_BUFFER];//�����¼����Ŀ,4,12
	char m_pNumberDeadSeisTracesExtended[SIZE_BUFFER];//ͣ�͵����¼����Ŀ,4,00
	char m_pNumberLiveSeisTracesExtended[SIZE_BUFFER];//������¼����Ŀ,4,12
	char m_pTypeSourceExtended[SIZE_BUFFER];//��Դ����,4,01
	char m_pNumberSamplesInTraceExtended[SIZE_BUFFER];//��¼����������Ŀ,4,4001
	char m_pShotNumberExtended[SIZE_BUFFER];//�ں�,4,01
	char m_pTBWindowExtended[SIZE_BUFFER];//TB ����,4,3000.000000
	char m_pTestRecordTypeExtended[SIZE_BUFFER];//���Լ�¼����,4,00
	char m_pSpreadFirstLineExtended[SIZE_BUFFER];//������һ������,4,01
	char m_pSpreadFirstNumberExtended[SIZE_BUFFER];//������һ������,4,34
	char m_pSpreadNumberExtended[SIZE_BUFFER];//���б��,4,01
	char m_pSpreadTypeExtended[SIZE_BUFFER];//��������,4,01
	char m_pTimebreakExtended[SIZE_BUFFER];//ʱ���ź�,4,00
	char m_pUpholeTimeExtended[SIZE_BUFFER];//����ʱ��,4,00
	char m_pBlasterIdExtended[SIZE_BUFFER];//��ը����ʶ��,4,01
	char m_pBlasterStatusExtended[SIZE_BUFFER];//��ը��״̬,4,02
	char m_pRefractionDelayExtended[SIZE_BUFFER];//�����ӳ�,4,00
	char m_pTBtoT0TimeExtended[SIZE_BUFFER];//Tb �� T0 ʱ��,4,00
	char m_pInternalTimeBreakExtended[SIZE_BUFFER];//�ڲ�ʱ���ź�,4,00
	char m_pPrestackWithinFieldUnitsExtended[SIZE_BUFFER];//Ұ���豸��Ԥ����,4,00
	char m_pNoiseEliminationTypeExtended[SIZE_BUFFER];//������������,4,01
	char m_pLowTracePercentageExtended[SIZE_BUFFER];//�ͼ�¼���ٷֱ�,4,00
	char m_pLowTraceValueExtended[SIZE_BUFFER];//�ͼ�¼��ֵ,4,00
	char m_pNumberWindowsOrWindowLengthExtended[SIZE_BUFFER];//������Ŀ,4,00
	char m_pHistoricEditingTypeOrOverlapExtended[SIZE_BUFFER];//��ʷ�༭����,4,00
	char m_pNoisyTracePercentageExtended[SIZE_BUFFER];//������¼���ٷֱ�,4,00
	char m_pHistoricRangeExtended[SIZE_BUFFER];//��ʷ��Χ,4,00
	char m_pHistoricTaperLengthExtended[SIZE_BUFFER];//��ʷ׶�γ��� 2 ��ָ��,4,00
	char m_pThresholdHoldOrNotExtended[SIZE_BUFFER];//�ż�ֵ����/ �仯,4,00
	char m_pHistoricThresholdInitValueExtended[SIZE_BUFFER];//��ʷ�ż�ֵ��ʼֵ,4,00
	char m_pHistoricZeroingLengthExtended[SIZE_BUFFER];//��ʷ���㳤��,4,00
	char m_pTypeProcessExtended[SIZE_BUFFER];//��������,4,01
	char m_pAcquisitionTypeTablesExtended[SIZE_BUFFER];//�ɼ����ͱ�,128,00
	char m_pThresholdTypeTablesExtended[SIZE_BUFFER];//�ż�ֵ���ͱ�,128,00
	char m_pStackingFoldExtended[SIZE_BUFFER];//���Ӵ���,4,01
	char m_pNotUsed1Extended[SIZE_BUFFER];//δʹ��,80,00
	char m_pRecordLengthExtended[SIZE_BUFFER];//��¼����,4,4000
	char m_pAutocorrelationPeakTimeExtended[SIZE_BUFFER];//����ط�ֵʱ��,4,00
	char m_pNotUsed2Extended[SIZE_BUFFER];//δʹ��,4,00
	char m_pCorrelationPilotNoExtended[SIZE_BUFFER];//��زο��źű��,4,00
	char m_pPilotLengthExtended[SIZE_BUFFER];//�ο��źų���,4,00
	char m_pSweepLengthExtended[SIZE_BUFFER];//ɨ�賤��,4,00
	char m_pAcquisitionNumberExtended[SIZE_BUFFER];//�ɼ���,4,01
	char m_pMaxOfMaxAuxExtended[SIZE_BUFFER];//��ศ���������ֵ,4,3041785.250000
	char m_pMaxOfMaxSeisExtended[SIZE_BUFFER];//����������ֵ,4,-614945.500000
	char m_pDumpStackingFoldExtended[SIZE_BUFFER];//ת�����Ӵ���,4,01
	char m_pTapeLabelExtended[SIZE_BUFFER];//�Ŵ���ǩ,16,label
	char m_pTapeNumberExtended[SIZE_BUFFER];//�Ŵ���,4,50
	char m_pSoftwareVersionExtended[SIZE_BUFFER];//����汾,16,4.0
	char m_pDateExtended[SIZE_BUFFER];//����,12,05 Jul 2012
	char m_pSourceEastingExtended[SIZE_BUFFER];//��Դƫ����,8,0
	char m_pSourceNorthingExtended[SIZE_BUFFER];//��Դ����γ�Ȳ�,8,0
	char m_pSourceElevationExtended[SIZE_BUFFER];//��Դ�߳�,4,0.000000
	char m_pSlipSweepModeUsedExtended[SIZE_BUFFER];//���õĻ���ɨ��ģʽ,4,00
	char m_pFilesPerTapeExtended[SIZE_BUFFER];//ÿ���Ŵ����ļ���,4,2000
	char m_pFileCountExtended[SIZE_BUFFER];//�ļ�����,4,01
	char m_pAcquisitionErrorDescriptionExtended[SIZE_BUFFER];//�ɼ�����˵��,160,
	char m_pFilterTypeExtended[SIZE_BUFFER];//�˲�������,4,02
	char m_pStackDumpedExtended[SIZE_BUFFER];//������ת��,4,00
	char m_pStackSignExtended[SIZE_BUFFER];//���ӷ��ţ���ǰ��,4,01
	char m_pPRMTiltCorrectionUsedExtended[SIZE_BUFFER];//���õ� PRM ��б��У��,4,00
	char m_pSwathNameExtended[SIZE_BUFFER];//������,64,D5
	char m_pOperatingModeExtended[SIZE_BUFFER];//����ģʽ,4,01
	char m_pReserved1Extended[SIZE_BUFFER];//����,4,79
	char m_pNoLogExtended[SIZE_BUFFER];//�޼�¼,4,00
	char m_pListeningTimeExtended[SIZE_BUFFER];//����ʱ��,4,4000
	char m_pTypeDumpExtended[SIZE_BUFFER];//ת������,4,00
	char m_pReserved2Extended[SIZE_BUFFER];//����,4,00
	char m_pSwathIdExtended[SIZE_BUFFER];//���� Id,4,01
	char m_pSeismicTraceOffsetRemovalDisabledExtended[SIZE_BUFFER];//,4,00
	char m_pGPSTimeAcquisitionTimeBreakExtended[SIZE_BUFFER];//,8,0003a4ac0c90344f
	char m_pAlignedGPSTimeAcquisitionExtended[SIZE_BUFFER];//,8,0000000000000000
	char m_pNotUsed3Extended[SIZE_BUFFER];//δʹ��,132,000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

	char* m_pConcatenationOfExternal;//�ⲿͷ��,m_pExternalHeaderLengthGeneral1*32,*SHOTPRO SP#    1/SL#    3.0/SN#   30.0/SI#1/SEQ# 1/STA:2/CTB:00.000/UH:000.0
}m_oSegdStandardHeaderStruct;

typedef struct Segd_Trace_Header_Struct
{
	//˵�����ֽ������ɼ������ݣ�����������
	char m_pFileNumberTrace[SIZE_BUFFER];//��λ���ļ���(0-9999),2,0327,0327
	char m_pScanTypeNumberTrace[SIZE_BUFFER];//ɨ�����ͱ��,1,01,01
	char m_pChannelSetNumberTrace[SIZE_BUFFER];//��������,1,02,01
	char m_pTraceNumberTrace[SIZE_BUFFER];//��¼�����,2,0001,0001
	char m_pFirstTimingWordTrace[SIZE_BUFFER];//��һ����ʱ��,3,00,00
	char m_pTraceHeaderExtensionTrace[SIZE_BUFFER];//��ͷ��չ,1,07,07
	char m_pSampleSkewTrace[SIZE_BUFFER];//����ʱ��,1,00,00
	char m_pTraceEditTrace[SIZE_BUFFER];//��¼���༭,1,00,00
	char m_pTimeBreakWindowTrace[SIZE_BUFFER];//ʱ���źŴ���,3,00,00
	char m_pExtendedChannelSetNumberTrace[SIZE_BUFFER];//��չ��������,2,0000,0000
	char m_pExtendedFileNumberTrace[SIZE_BUFFER];//��չ�ļ����,3,000147,000147

	char m_pReceiverLineNumberTrace1[SIZE_BUFFER];//���յ���ߺ�,3,01,00
	char m_pReceiverPointNumberTrace1[SIZE_BUFFER];//���յ��,3,34,01
	char m_pReceiverPointIndexTrace1[SIZE_BUFFER];//���յ�����,1,01,01
	char m_pNumberSamplesPerTraceTrace1[SIZE_BUFFER];//ÿ����¼��������Ŀ,3,4001,4001
	char m_pExtendedReceiverLineNumberTrace1[SIZE_BUFFER];//��չ���յ���ߺ�,5,0000000000,0000000000
	char m_pExtendedReceiverPointNumberTrace1[SIZE_BUFFER];//��չ���յ��,5,0000000000,0000000000
	char m_pSensorSEGDCodeTrace1[SIZE_BUFFER];//�첨�� SEGD ����,1,02,00
	char m_pNotUsedTrace1[SIZE_BUFFER];//δʹ��,11,0000000000000000000000,0000000000000000000000

	char m_pReceiverPointEastingTrace2[SIZE_BUFFER];//���յ�ƫ����,8,0,0
	char m_pReceiverPointNorthingTrace2[SIZE_BUFFER];//���յ㱱��γ�Ȳ�,8,0,0
	char m_pReceiverPointElevationTrace2[SIZE_BUFFER];//���յ�߳�,4,0.000000,0.000000
	char m_pSensorTypeNumberTrace2[SIZE_BUFFER];//�첨�����ͱ�ţ�1 �� 9��,1,01,00
	char m_pNotUsedTrace2[SIZE_BUFFER];//δʹ��,3,000000,000000
	char m_pDSDIdentificationNoTrace2[SIZE_BUFFER];//δʹ��,4,00,00
	char m_pExtendedTraceNoTrace2[SIZE_BUFFER];//��չ��¼�����,4,01,01

	char m_pResistanceLowLimitTrace3[SIZE_BUFFER];//��������,4,300.000000,0.000000
	char m_pResistanceHighLimitTrace3[SIZE_BUFFER];//��������,4,500.000000,0.000000
	char m_pResistanceResistanceValueTrace3[SIZE_BUFFER];//����ֵ,4,1904.939941,0.000000
	char m_pTiltLimitTrace3[SIZE_BUFFER];//��б�Ƚ���,4,15.000000,0.000000
	char m_pTiltValueTrace3[SIZE_BUFFER];//��б��ֵ,4,N-,0.000000
	char m_pResistanceErrorTrace3[SIZE_BUFFER];//�������,1,01,00
	char m_pTiltErrorTrace3[SIZE_BUFFER];//��б�����,1,00,00
	char m_pNotUsedTrace3[SIZE_BUFFER];//δʹ��,10,00000000000000000000,00000000000000000000

	char m_pCapacitanceLowLimitTrace4[SIZE_BUFFER];//��������,4,N-,0.000000
	char m_pCapacitanceHighLimitTrace4[SIZE_BUFFER];//��������,4,N-,0.000000
	char m_pCapacitanceValueTrace4[SIZE_BUFFER];//����ֵ,4,N-,0.000000
	char m_pCutOffLowLimitTrace4[SIZE_BUFFER];//��ֹ����,4,N-,0.000000
	char m_pCutOffHighLimitsTrace4[SIZE_BUFFER];//��ֹ����,4,N-,0.000000
	char m_pCutOffValueTrace4[SIZE_BUFFER];//��ֵֹ,4,N-,0.000000
	char m_pCapacitanceErrorTrace4[SIZE_BUFFER];//�������,1,00,00
	char m_pCutOffErrorTrace4[SIZE_BUFFER];//��ֹ���,1,00,00
	char m_pNotUsedTrace4[SIZE_BUFFER];//δʹ��,6,000000000000,000000000000

	char m_pLeakageLimitTrace5[SIZE_BUFFER];//©�����,4,5.000000,0.000000
	char m_pLeakageValueTrace5[SIZE_BUFFER];//©��ֵ,4,5.000000,0.000000
	char m_pNotUsed1Trace5[SIZE_BUFFER];//δʹ��,16,00000000000000000000000000000000,00000000000000000000000000000000
	char m_pLeakageErrorTrace5[SIZE_BUFFER];//©�����,1,00,00
	char m_pNotUsed2Trace5[SIZE_BUFFER];//δʹ��,7,00000000000000,00000000000000

	char m_pUnitTypeTrace6[SIZE_BUFFER];//�豸����,1,01,01
	char m_pUnitSerialNumberTrace6[SIZE_BUFFER];//�豸���к�,3,6104422,4819236
	char m_pChannelNumberTrace6[SIZE_BUFFER];//��������,1,01,01
	char m_pSpare1Trace6[SIZE_BUFFER];//����,3,000000,000000
	char m_pAssemblyTypeTrace6[SIZE_BUFFER];//�������,1,03,04
	char m_pFDUorDSUAssemblySerialNumberTrace6[SIZE_BUFFER];//FDU �� DSU ������к�,3,1791352,4819236
	char m_pLocationInFDUorDSUAssemblyTrace6[SIZE_BUFFER];//�� FDU �� DSU����е�λ��,1,02,01
	char m_pSpare2Trace6[SIZE_BUFFER];//����,3,000000,000000
	char m_pSubunitTypeTrace6[SIZE_BUFFER];//FDU �� DSU �豸����,1,01,21
	char m_pChannelTypeTrace6[SIZE_BUFFER];//���������,1,00,00
	char m_pSpare3Trace6[SIZE_BUFFER];//����,2,0000,0000
	char m_pSensorSensitivityTrace6[SIZE_BUFFER];//�첨��������,4,4294967296.000000,4294967296.000000
	char m_pNotUsedTrace6[SIZE_BUFFER];//δʹ��,8,0000000000000000,0000000000000000

	char m_pControlUnitTypeTrace7[SIZE_BUFFER];//���Ƶ�Ԫ����,1,02,49
	char m_pControlUnitSerialNumberTrace7[SIZE_BUFFER];//���Ƶ�Ԫ���к�,3,17693,2442269
	char m_pChannelGainScaleTrace7[SIZE_BUFFER];//���������̶�,1,02,02
	char m_pChannelFilterTrace7[SIZE_BUFFER];//������˲���,1,02,02
	char m_pChannelDataErrorTrace7[SIZE_BUFFER];//�����������������Χ,1,00,00
	char m_pChannelEditedStatusTrace7[SIZE_BUFFER];//������༭״̬,1,00,00
	char m_pChannelSampleTomVConversionFactorTrace7[SIZE_BUFFER];//�������������ת��ϵ��,4,0.000067,0.000000
	char m_pNumberOfStacksNoisyTrace7[SIZE_BUFFER];//���������Ӵ���,1,00,00
	char m_pNumberOfStacksLowTrace7[SIZE_BUFFER];//�͵��Ӵ���,1,00,00
	char m_pChannelTypeIdTrace7[SIZE_BUFFER];//��������ͱ�ʶ��,1,01,09
	char m_pChannelProcessTrace7[SIZE_BUFFER];//���������,1,01,01
	char m_pTraceMaxValueTrace7[SIZE_BUFFER];//��¼�����ֵ,4,0.000000,0.000000
	char m_pTraceMaxTimeTrace7[SIZE_BUFFER];//��¼�����ʱ��,4,00,00
	char m_pNumberInterpolationsTrace7[SIZE_BUFFER];//�ڲ����,4,00,00
	char m_pSeismicTraceOffsetValueTrace7[SIZE_BUFFER];//δʹ��,4,00,00	
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