#include "stdafx.h"
#include "MatrixServerDll.h"
// ��ʼ��SEGD�ļ���׼ͷ
void OnInitSegdSH(m_oSegdStandardHeaderStruct* pSegdSH)
{
	//˵�����ֽ���������
	//��λ���ļ���� (0-9999),2,0327
	memcpy(pSegdSH->m_pFileNumberGeneral1, "0327", 4);
	//��ʽ����,2,8058
	memcpy(pSegdSH->m_pFormatCodeGeneral1, "8058", 4);
	//��ͨ����,6,000000000005
	memcpy(pSegdSH->m_pGeneralConstantsGeneral1, "000000000005", 12);
	//��ݵ������λ��(0-99),1,12
	memcpy(pSegdSH->m_pLastTwoDigitsOfYearGeneral1, "12", 2);
	//��ͨͷ���ж������ݿ���Ŀ,H,2
	memcpy(pSegdSH->m_pNumberAdditionalBlocksGeneral1, "2", 1);
	//�����գ�3 λ��(1-366),L+1,187
	memcpy(pSegdSH->m_pJulianDayGeneral1, "187", 3);
	//һ���е�Сʱ��0-23��,1,08
	memcpy(pSegdSH->m_pHourOfDayGeneral1, "08", 2);
	//Сʱ�еķ��ӣ�0-59��,1,36
	memcpy(pSegdSH->m_pMinuteOfHourGeneral1, "36", 2);
	//�����е����ӣ�0-59��,1,06
	memcpy(pSegdSH->m_pSecondOfMinuteGeneral1, "06", 2);
	//�����̴���,1,13
	memcpy(pSegdSH->m_pManufacturerCodeGeneral1, "13", 2);
	//���������к�,2,0000
	memcpy(pSegdSH->m_pManufacturerSerialNumberGeneral1, "0000", 4);
	//ÿ��ɨ���ֽ���,3,000000
	memcpy(pSegdSH->m_pBytesPerScanGeneral1, "000000", 6);
	//����ɨ����,1,10
	memcpy(pSegdSH->m_pBaseScanIntervalGeneral1, "10", 2);
	//����,H,0
	memcpy(pSegdSH->m_pPolarityGeneral1, "0", 1);
	//δʹ��,L+1,000
	memcpy(pSegdSH->m_pNotUsedGeneral1, "000", 3);
	//��¼����,H,8
	memcpy(pSegdSH->m_pRecordTypeGeneral1, "8", 1);
	//��¼����,L+1,fff
	memcpy(pSegdSH->m_pRecordLengthGeneral1, "fff", 3);
	//ÿ����¼��ɨ������,1,01
	memcpy(pSegdSH->m_pScanTypePerRecordGeneral1, "01", 2);
	//ÿ����¼�ĵ��������Ŀ,1,16
	memcpy(pSegdSH->m_pNumberChannelSetsPerRecordGeneral1, "16", 2);
	//����ʱ�� 32 �ֽ���չ����Ŀ,1,00
	memcpy(pSegdSH->m_pNumberSampleSkew32ByteExtensionsGeneral1, "00", 2);
	//��չͷ�γ���,1,32
	memcpy(pSegdSH->m_pExtendedHeaderLengthGeneral1, "32", 2);
	//�ⲿͷ�γ���,1,32
	memcpy(pSegdSH->m_pExternalHeaderLengthGeneral1, "32", 2);
	
	//��չ�ļ����,3,327
	memcpy(pSegdSH->m_pExpandedFileNumberGeneral2, "327", 3);
	//��չ�������/ ɨ�����ͣ�δʹ�ã�,2,0000
	memcpy(pSegdSH->m_pExpandedChannelSetsGeneral2, "0000", 4);
	//��չͷ�����ݿ飨δʹ�ã�,2,0000
	memcpy(pSegdSH->m_pExtendedHeaderBlocksGeneral2, "0000", 4);
	//�ⲿͷ�����ݿ�,2,00
	memcpy(pSegdSH->m_pExternalHeaderBlocksGeneral2, "00", 2);
	//δʹ��,1,00
	memcpy(pSegdSH->m_pNotUsed1General2, "00", 2);
	//SEG-D �汾��,2,0201
	memcpy(pSegdSH->m_pSegdRevisionNumberGeneral2, "0201", 4);
	//��ͨβ�����ݿ���Ŀ,2,0000
	memcpy(pSegdSH->m_pNumberBlocksGeneralTrailerGeneral2, "0000", 4);
	//��չ��¼���ȣ�0-128000 ���룩,3,4000
	memcpy(pSegdSH->m_pExpandedRecordLengthGeneral2, "4000", 4);
	//δʹ��,1,00
	memcpy(pSegdSH->m_pNotUsed2General2, "00", 2);
	//��ͨͷ�����ݿ���,1,02
	memcpy(pSegdSH->m_pGeneralHeaderBlockNumberGeneral2, "02", 2);
	//δʹ��,13,00000000000000000000000000
	memcpy(pSegdSH->m_pNotUsed3General2, "00000000000000000000000000", 26);
	//��չ�ļ����,3,000147
	memcpy(pSegdSH->m_pExpandedFileNumberGeneral3, "000147", 6);
	//��Դ���ߺ�(0-99999.99),5,0000030000
	memcpy(pSegdSH->m_pSourceLineNumberGeneral3, "0000030000", 10);
	//��Դ���(0-99999.99),5,00001e0000
	memcpy(pSegdSH->m_pSourcePointNumberGeneral3, "00001e0000", 10);
	//��Դ������ (1-9),1,01
	memcpy(pSegdSH->m_pSourcePointIndexGeneral3, "01", 2);
	//��λ���ƣ�δ��¼�ģ�,1,00
	memcpy(pSegdSH->m_pPhaseControlGeneral3, "00", 2);
	//�ɿ���Դ���ͣ�δ��¼�ģ�,1,00
	memcpy(pSegdSH->m_pVibratorTypeGeneral3, "00", 2);
	//��λ�ǣ�δ��¼�ģ�,2,0000
	memcpy(pSegdSH->m_pPhaseAngleGeneral3, "0000", 4);
	//��ͨͷ�����ݿ���,1,03
	memcpy(pSegdSH->m_pGeneralHeaderBlockNumberGeneral3, "03", 2);
	//��Դ���,1,01
	memcpy(pSegdSH->m_pSourceSetNumberGeneral3, "01", 2);
	//δʹ��,12,000000000000000000000000
	memcpy(pSegdSH->m_pNotUsedGeneral3, "000000000000000000000000", 24);

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

	//�ɼ�����,4,4000
	memcpy(pSegdSH->m_pAcquisitionLengthExtended, "4000", 4);
	//������,4,1000
	memcpy(pSegdSH->m_pSampleRateExtended, "1000", 4);
	//��¼������,4,14
	memcpy(pSegdSH->m_pTotalNumberTracesExtended, "14", 2);
	//��������Ŀ,4,02
	memcpy(pSegdSH->m_pNumberAuxesExtended, "02", 2);
	//�����¼����Ŀ,4,12
	memcpy(pSegdSH->m_pNumberSeisTracesExtended, "12", 2);
	//ͣ�͵����¼����Ŀ,4,00
	memcpy(pSegdSH->m_pNumberDeadSeisTracesExtended, "00", 2);
	//������¼����Ŀ,4,12
	memcpy(pSegdSH->m_pNumberLiveSeisTracesExtended, "12", 2);
	//��Դ����,4,01
	memcpy(pSegdSH->m_pTypeSourceExtended, "01", 2);
	//��¼����������Ŀ,4,4001
	memcpy(pSegdSH->m_pNumberSamplesInTraceExtended, "4001", 4);
	//�ں�,4,01
	memcpy(pSegdSH->m_pShotNumberExtended, "01", 2);
	//TB ����,4,3000.000000
	memcpy(pSegdSH->m_pTBWindowExtended, "3000.000000", 11);
	//���Լ�¼����,4,00
	memcpy(pSegdSH->m_pTestRecordTypeExtended, "00", 2);
	//������һ������,4,01
	memcpy(pSegdSH->m_pSpreadFirstLineExtended, "01", 2);
	//������һ������,4,34
	memcpy(pSegdSH->m_pSpreadFirstNumberExtended, "34", 2);
	//���б��,4,01
	memcpy(pSegdSH->m_pSpreadNumberExtended, "01", 2);
	//��������,4,01
	memcpy(pSegdSH->m_pSpreadTypeExtended, "01", 2);
	//ʱ���ź�,4,00
	memcpy(pSegdSH->m_pTimebreakExtended, "00", 2);
	//����ʱ��,4,00
	memcpy(pSegdSH->m_pUpholeTimeExtended, "00", 2);
	//��ը����ʶ��,4,01
	memcpy(pSegdSH->m_pBlasterIdExtended, "01", 2);
	//��ը��״̬,4,02
	memcpy(pSegdSH->m_pBlasterStatusExtended, "02", 2);
	//�����ӳ�,4,00
	memcpy(pSegdSH->m_pRefractionDelayExtended, "00", 2);
	//Tb �� T0 ʱ��,4,00
	memcpy(pSegdSH->m_pTBtoT0TimeExtended, "00", 2);
	//�ڲ�ʱ���ź�,4,00
	memcpy(pSegdSH->m_pInternalTimeBreakExtended, "00", 2);
	//Ұ���豸��Ԥ����,4,00
	memcpy(pSegdSH->m_pPrestackWithinFieldUnitsExtended, "00", 2);
	//������������,4,01
	memcpy(pSegdSH->m_pNoiseEliminationTypeExtended, "01", 2);
	//�ͼ�¼���ٷֱ�,4,00
	memcpy(pSegdSH->m_pLowTracePercentageExtended, "00", 2);
	//�ͼ�¼��ֵ,4,00
	memcpy(pSegdSH->m_pLowTraceValueExtended, "00", 2);
	//������Ŀ,4,00
	memcpy(pSegdSH->m_pNumberWindowsOrWindowLengthExtended, "00", 2);
	//��ʷ�༭����,4,00
	memcpy(pSegdSH->m_pHistoricEditingTypeOrOverlapExtended, "00", 2);
	//������¼���ٷֱ�,4,00
	memcpy(pSegdSH->m_pNoisyTracePercentageExtended, "00", 2);
	//��ʷ��Χ,4,00
	memcpy(pSegdSH->m_pHistoricRangeExtended, "00", 2);
	//��ʷ׶�γ��� 2 ��ָ��,4,00
	memcpy(pSegdSH->m_pHistoricTaperLengthExtended, "00", 2);
	//�ż�ֵ����/ �仯,4,00
	memcpy(pSegdSH->m_pThresholdHoldOrNotExtended, "00", 2);
	//��ʷ�ż�ֵ��ʼֵ,4,00
	memcpy(pSegdSH->m_pHistoricThresholdInitValueExtended, "00", 2);
	//��ʷ���㳤��,4,00
	memcpy(pSegdSH->m_pHistoricZeroingLengthExtended, "00", 2);
	//��������,4,01
	memcpy(pSegdSH->m_pTypeProcessExtended, "01", 2);
	//�ɼ����ͱ�,128,00
	memcpy(pSegdSH->m_pAcquisitionTypeTablesExtended, "00", 2);
	//�ż�ֵ���ͱ�,128,00
	memcpy(pSegdSH->m_pThresholdTypeTablesExtended, "00", 2);
	//���Ӵ���,4,01
	memcpy(pSegdSH->m_pStackingFoldExtended, "01", 2);
	//δʹ��,80,00
	memcpy(pSegdSH->m_pNotUsed1Extended, "02", 2);
	//��¼����,4,4000
	memcpy(pSegdSH->m_pRecordLengthExtended, "4000", 4);
	//����ط�ֵʱ��,4,00
	memcpy(pSegdSH->m_pAutocorrelationPeakTimeExtended, "00", 2);
	//δʹ��,4,00
	memcpy(pSegdSH->m_pNotUsed2Extended, "00", 2);
	//��زο��źű��,4,00
	memcpy(pSegdSH->m_pCorrelationPilotNoExtended, "00", 2);
	//�ο��źų���,4,00
	memcpy(pSegdSH->m_pPilotLengthExtended, "00", 2);
	//ɨ�賤��,4,00
	memcpy(pSegdSH->m_pSweepLengthExtended, "00", 2);
	//�ɼ���,4,01
	memcpy(pSegdSH->m_pAcquisitionNumberExtended, "01", 2);
	//��ศ���������ֵ,4,3041785.250000
	memcpy(pSegdSH->m_pMaxOfMaxAuxExtended, "3041785.250000", 14);
	//����������ֵ,4,-614945.500000
	memcpy(pSegdSH->m_pMaxOfMaxSeisExtended, "-614945.500000", 14);
	//ת�����Ӵ���,4,01
	memcpy(pSegdSH->m_pDumpStackingFoldExtended, "01", 2);
	//�Ŵ���ǩ,16,label
	memcpy(pSegdSH->m_pTapeLabelExtended, "label", 5);
	//�Ŵ���,4,50
	memcpy(pSegdSH->m_pTapeNumberExtended, "50", 2);
	//����汾,16,4.0
	memcpy(pSegdSH->m_pSoftwareVersionExtended, "4.0", 3);
	//����,12,05 Jul 2012
	memcpy(pSegdSH->m_pDateExtended, "05 Jul 2012", 11);
	//��Դƫ����,8,0
	memcpy(pSegdSH->m_pSourceEastingExtended, "0", 1);
	//��Դ����γ�Ȳ�,8,0
	memcpy(pSegdSH->m_pSourceNorthingExtended, "0", 1);
	//��Դ�߳�,4,0.000000
	memcpy(pSegdSH->m_pSourceElevationExtended, "0.000000", 8);
	//���õĻ���ɨ��ģʽ,4,00
	memcpy(pSegdSH->m_pSlipSweepModeUsedExtended, "00", 2);
	//ÿ���Ŵ����ļ���,4,2000
	memcpy(pSegdSH->m_pFilesPerTapeExtended, "2000", 4);
	//�ļ�����,4,01
	memcpy(pSegdSH->m_pFileCountExtended, "01", 2);
	//@@@@@δ��ֵ
	char m_pAcquisitionErrorDescriptionExtended[SIZE_BUFFER];//�ɼ�����˵��,160,

	//�˲�������,4,02
	memcpy(pSegdSH->m_pFilterTypeExtended, "02", 2);
	//������ת��,4,00
	memcpy(pSegdSH->m_pStackDumpedExtended, "00", 2);
	//���ӷ��ţ���ǰ��,4,01
	memcpy(pSegdSH->m_pStackSignExtended, "01", 2);
	//���õ� PRM ��б��У��,4,00
	memcpy(pSegdSH->m_pPRMTiltCorrectionUsedExtended, "00", 2);
	//������,64,D5
	memcpy(pSegdSH->m_pSwathNameExtended, "D5", 2);
	//����ģʽ,4,01
	memcpy(pSegdSH->m_pOperatingModeExtended, "01", 2);
	//����,4,79
	memcpy(pSegdSH->m_pReserved1Extended, "79", 2);
	//�޼�¼,4,00
	memcpy(pSegdSH->m_pNoLogExtended, "00", 2);
	//����ʱ��,4,4000
	memcpy(pSegdSH->m_pListeningTimeExtended, "4000", 4);
	//ת������,4,00
	memcpy(pSegdSH->m_pTypeDumpExtended, "00", 2);
	//����,4,00
	memcpy(pSegdSH->m_pReserved2Extended, "00", 2);
	//���� Id,4,01
	memcpy(pSegdSH->m_pSwathIdExtended, "01", 2);
	//,4,00
	memcpy(pSegdSH->m_pSeismicTraceOffsetRemovalDisabledExtended, "00", 2);
	//,8,0003a4ac0c90344f
	memcpy(pSegdSH->m_pGPSTimeAcquisitionTimeBreakExtended, "0003a4ac0c90344f", 16);
	//,8,0000000000000000
	memcpy(pSegdSH->m_pAlignedGPSTimeAcquisitionExtended, "0000000000000000", 16);
	//δʹ��,132,000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memcpy(pSegdSH->m_pNotUsed3Extended, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 264);
	
	//@@@@@δ��ֵ
	char* m_pConcatenationOfExternal;//�ⲿͷ��,m_pExternalHeaderLengthGeneral1*32,*SHOTPRO SP#    1/SL#    3.0/SN#   30.0/SI#1/SEQ# 1/STA:2/CTB:00.000/UH:000.0
}

// ��ʼ��SEGD�ļ����ݵ�ͷ
void OnInitSegdTH(m_oSegdTraceHeaderStruct* pSegdTH)
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
}
// ���浽Segd�ļ����ɹ�����true��ʧ�ܷ���false
bool SaveSegdFile(m_oSegdFileStruct* pSegdFileStruct)
{
	int iCountSeisChannel = 0;

	struct tm *newtime = NULL;
	char tmpbuf[128];
	time_t lt1;
	time(&lt1);
	localtime_s(newtime, &lt1);
	CString strTime = _T("");
	CString strFilePath = _T("");
	CString strPath = _T("");
	FILE* pNewSegdFile;
	string strTemp = "";
	strftime(tmpbuf, 128, "%Y%m%d %I%M%S", newtime);
	strTime.Format(_T("%s"), tmpbuf);
	strPath.Format(_T("%s"), pSegdFileStruct->m_strPath.c_str());
	strTime = strTime + _T(".segd"); 
	strFilePath = strPath + strTime;
	strTemp = (CStringA)strFilePath;
	if((0 != fopen_s(&pNewSegdFile, strTemp.c_str(), "wb+")) == NULL)
	{
		AfxMessageBox(_T("Open new segd failed!\n"));
	}

	ProcessGeneralHeaderBlock1BackNew(pNewSegdFile, pSegdFileStruct);
	ProcessGeneralHeaderBlock2BackNew(pNewSegdFile, pSegdFileStruct);
	ProcessGeneralHeaderBlock3BackNew(pNewSegdFile, pSegdFileStruct);
	for(int i = 1; i< COUNT_SCAN_TYPE_HEADER + 1; i++ )
	{
		ProcessScanTypeHeaderBackNew(pNewSegdFile, i, pSegdFileStruct);
	}
	ProcessExtendedHeaderBackNew(pNewSegdFile, pSegdFileStruct);

	ProcessExternalHeaderBackNew(pNewSegdFile, pSegdFileStruct);

	for(int i = 1; i< pSegdFileStruct->m_oSegdSH.m_iTotalTraceNum + 1; i++)
	{

		iCountSeisChannel++;

		if (iCountSeisChannel > pSegdFileStruct->m_oSegdSH.m_iAcqTraceNum)
		{
			iCountSeisChannel -= pSegdFileStruct->m_oSegdSH.m_iAcqTraceNum;
		}

		ProcessTraceHeaderBackNew(pNewSegdFile, iCountSeisChannel, pSegdFileStruct);
		ProcessTraceHeaderExtensionBlock1BackNew(pNewSegdFile, i, pSegdFileStruct);
		ProcessTraceHeaderExtensionBlock2BackNew(pNewSegdFile, iCountSeisChannel, pSegdFileStruct);
		ProcessTraceHeaderExtensionBlock3BackNew(pNewSegdFile, pSegdFileStruct);
		ProcessTraceHeaderExtensionBlock4BackNew(pNewSegdFile, pSegdFileStruct);
		ProcessTraceHeaderExtensionBlock5BackNew(pNewSegdFile, pSegdFileStruct);
		ProcessTraceHeaderExtensionBlock6BackNew(pNewSegdFile, pSegdFileStruct);
		ProcessTraceHeaderExtensionBlock7BackNew(pNewSegdFile, pSegdFileStruct);

		ProcessTraceDataBackNew(pNewSegdFile, i, pSegdFileStruct);

	}

	if (fclose(pNewSegdFile))
	{
		AfxMessageBox(_T("Close new segd file failed!"));
	}

	return true;
}

void ProcessGeneralHeaderBlock1BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	string strHigh = "";
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pFileNumberGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pFormatCodeGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 6, pSegdFileStruct->m_oSegdSH.m_pGeneralConstantsGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pLastTwoDigitsOfYearGeneral1);

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pNumberAdditionalBlocksGeneral1, &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pJulianDayGeneral1, strHigh);

	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pHourOfDayGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pMinuteOfHourGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pSecondOfMinuteGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pManufacturerCodeGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pManufacturerSerialNumberGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 3, pSegdFileStruct->m_oSegdSH.m_pBytesPerScanGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pBaseScanIntervalGeneral1);

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pPolarityGeneral1, &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pNotUsedGeneral1, strHigh);

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pRecordTypeGeneral1, &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pRecordLengthGeneral1, strHigh);

	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pScanTypePerRecordGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNumberChannelSetsPerRecordGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNumberSampleSkew32ByteExtensionsGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pExtendedHeaderLengthGeneral1);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pExternalHeaderLengthGeneral1);

}

void ProcessGeneralHeaderBlock2BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{
	ReadInitToWriteSegdNew_BIN(pFile, 3, pSegdFileStruct->m_oSegdSH.m_pExpandedFileNumberGeneral2);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pExpandedChannelSetsGeneral2);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pExtendedHeaderBlocksGeneral2);
	ReadInitToWriteSegdNew_BIN(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pExternalHeaderBlocksGeneral2);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNotUsed1General2);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pSegdRevisionNumberGeneral2);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pNumberBlocksGeneralTrailerGeneral2);

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleTime == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 3, pSegdFileStruct->m_oSegdSH.m_pExpandedRecordLengthGeneral2);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 3, pSegdFileStruct->m_oSegdSH.m_uiSampleTime);
	}

	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNotUsed2General2);
	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pGeneralHeaderBlockNumberGeneral2);
	ReadInitToWriteSegdNew_BCD(pFile, 13, pSegdFileStruct->m_oSegdSH.m_pNotUsed3General2);
}

void ProcessGeneralHeaderBlock3BackNew(FILE* pFile,m_oSegdFileStruct* pSegdFileStruct)
{
	ReadInitToWriteSegdNew_BCD(pFile, 3, pSegdFileStruct->m_oSegdSH.m_pExpandedFileNumberGeneral3);
	ReadInitToWriteSegdNew_BCD(pFile, 5, pSegdFileStruct->m_oSegdSH.m_pSourceLineNumberGeneral3);
	ReadInitToWriteSegdNew_BCD(pFile, 5, pSegdFileStruct->m_oSegdSH.m_pSourcePointNumberGeneral3);
	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pSourcePointIndexGeneral3);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pPhaseControlGeneral3);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pVibratorTypeGeneral3);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pPhaseAngleGeneral3);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pGeneralHeaderBlockNumberGeneral3);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pSourceSetNumberGeneral3);
	ReadInitToWriteSegdNew_BCD(pFile, 12, pSegdFileStruct->m_oSegdSH.m_pNotUsedGeneral3);
}

void ProcessScanTypeHeaderBackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct)
{

	string strHigh = "";
	int iNumTrace = 0;
	CString strNumTrace = _T("");

	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pScanTypeHeaderScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pChannelSetNumberScan[iChannel-1]);
	ReadInitToWriteSegdNew_BIN(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pChannelSetStartingTimeScan[iChannel-1]);
	ReadInitToWriteSegdNew_BIN(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pChannelSetEndTimeScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pDescaleMultiplierScan[iChannel-1]);
	if (iChannel == 1)
	{
		iNumTrace = pSegdFileStruct->m_oSegdSH.m_iAuxTraceNum;
	}
	else if(iChannel == 2)
	{
		iNumTrace = pSegdFileStruct->m_oSegdSH.m_iAcqTraceNum;
	}
	else
	{
		iNumTrace = 0;
	}

	if (iNumTrace == 0)
	{
		ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pNumberChannelsOfChannelSetScan[iChannel-1]);
	}
	else
	{
		ReadParameterToSegd_BCD(pFile, 2, iNumTrace);
	}

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pChannelTypeIdentificationScan[iChannel-1], &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNotUsedScan[iChannel-1], strHigh);
	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pNumberSubscansExponentScan[iChannel-1], &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pChannelGainControlMethodScan[iChannel-1], strHigh);

	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pAliasFilterFrequency3dBPointScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pAliasFilterSlopeScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pLowCutFilterFrequencyScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pLowCutFilterSlopeScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pFirstNotchFrequencyScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pSecondNotchFrequencyScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pThirdNotchFrequencyScan[iChannel-1]);
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pExtendedChannelSetNumberScan[iChannel-1]);

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pExtendedHeaderFlagScan[iChannel-1], &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pTraceHeaderExtensionsScan[iChannel-1], strHigh);

	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pVerticalStackScan[iChannel-1]);
	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pStreamerCableNumberScan[iChannel-1]);
	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pArrayFormingScan[iChannel-1]);
}

void ProcessExtendedHeaderBackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleTime == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_uiSampleTime = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pAcquisitionLengthExtended);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_uiSampleTime);
	}

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleRate == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_uiSampleRate = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSampleRateExtended);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_uiSampleRate);
	}


	if (pSegdFileStruct->m_oSegdSH.m_iTotalTraceNum == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_iTotalTraceNum = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTotalNumberTracesExtended);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_iTotalTraceNum);
	}

	if (pSegdFileStruct->m_oSegdSH.m_iAuxTraceNum == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_iAuxTraceNum = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberAuxesExtended);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_iAuxTraceNum);
	}

	if (pSegdFileStruct->m_oSegdSH.m_iAcqTraceNum == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_iAcqTraceNum = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberSeisTracesExtended);
	} 
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_iAcqTraceNum);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberDeadSeisTracesExtended);


	if (pSegdFileStruct->m_oSegdSH.m_iAcqTraceNum == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberLiveSeisTracesExtended);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_iAcqTraceNum);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTypeSourceExtended);


	if (pSegdFileStruct->m_oSegdSH.m_iSampleLength == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_iSampleLength = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberSamplesInTraceExtended);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_iSampleLength);
	}


	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pShotNumberExtended);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTBWindowExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTestRecordTypeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSpreadFirstLineExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSpreadFirstNumberExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSpreadNumberExtended);

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSpreadTypeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTimebreakExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pUpholeTimeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pBlasterIdExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pBlasterStatusExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pRefractionDelayExtended);

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTBtoT0TimeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pInternalTimeBreakExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pPrestackWithinFieldUnitsExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNoiseEliminationTypeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pLowTracePercentageExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pLowTraceValueExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberWindowsOrWindowLengthExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricEditingTypeOrOverlapExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNoisyTracePercentageExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricRangeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricTaperLengthExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pThresholdHoldOrNotExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricThresholdInitValueExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricZeroingLengthExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTypeProcessExtended);    //36*4=144
	ReadInitToWriteSegdNew_BIN(pFile, 128, pSegdFileStruct->m_oSegdSH.m_pAcquisitionTypeTablesExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 128, pSegdFileStruct->m_oSegdSH.m_pThresholdTypeTablesExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pStackingFoldExtended);
	ReadInitToWriteSegdNew_ASC(pFile, 80, pSegdFileStruct->m_oSegdSH.m_pNotUsed1Extended);

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleTime == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pRecordLengthExtended);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_uiSampleTime);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pAutocorrelationPeakTimeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNotUsed2Extended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pCorrelationPilotNoExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pPilotLengthExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSweepLengthExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pAcquisitionNumberExtended);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pMaxOfMaxAuxExtended);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pMaxOfMaxSeisExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pDumpStackingFoldExtended);
	ReadInitToWriteSegdNew_ASC(pFile, 16, pSegdFileStruct->m_oSegdSH.m_pTapeLabelExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTapeNumberExtended);
	ReadInitToWriteSegdNew_ASC(pFile, 16, pSegdFileStruct->m_oSegdSH.m_pSoftwareVersionExtended);
	ReadInitToWriteSegdNew_ASC(pFile, 12, pSegdFileStruct->m_oSegdSH.m_pDateExtended);
	ReadInitToWriteSegdNew_DOUBLE(pFile, 8, pSegdFileStruct->m_oSegdSH.m_pSourceEastingExtended);
	ReadInitToWriteSegdNew_DOUBLE(pFile, 8, pSegdFileStruct->m_oSegdSH.m_pSourceNorthingExtended);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSourceElevationExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSlipSweepModeUsedExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pFilesPerTapeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pFileCountExtended);
	ReadInitToWriteSegdNew_ASC(pFile, 160, pSegdFileStruct->m_oSegdSH.m_pAcquisitionErrorDescriptionExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pFilterTypeExtended);

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pStackDumpedExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pStackSignExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pPRMTiltCorrectionUsedExtended);
	ReadInitToWriteSegdNew_ASC(pFile, 64, pSegdFileStruct->m_oSegdSH.m_pSwathNameExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pOperatingModeExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pReserved1Extended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNoLogExtended);

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleTime == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pListeningTimeExtended);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_uiSampleTime);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTypeDumpExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pReserved2Extended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSwathIdExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSeismicTraceOffsetRemovalDisabledExtended);
	ReadInitToWriteSegdNew_BCD(pFile, 8, pSegdFileStruct->m_oSegdSH.m_pGPSTimeAcquisitionTimeBreakExtended);
	ReadInitToWriteSegdNew_BCD(pFile, 8, pSegdFileStruct->m_oSegdSH.m_pAlignedGPSTimeAcquisitionExtended);
	ReadInitToWriteSegdNew_BCD(pFile, 132, pSegdFileStruct->m_oSegdSH.m_pNotUsed3Extended);
}

void ProcessExternalHeaderBackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{
	int iLenth = 0;
	int iLenthExternalHeader = ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pExternalHeaderLengthGeneral1);
	iLenth = iLenthExternalHeader * 32;
	ReadInitToWriteSegdNew_ASC(pFile, iLenth, pSegdFileStruct->m_oSegdSH.m_pConcatenationOfExternal);
}

void ProcessTraceHeaderBackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_BCD(pFile, 2, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pFileNumberTrace);
	ReadInitToWriteSegdNew_BCD(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pScanTypeNumberTrace);
	ReadInitToWriteSegdNew_BCD(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelSetNumberTrace);

	if (iChannel == 0)
	{
		ReadInitToWriteSegdNew_BCD(pFile, 2, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceNumberTrace);
	}
	else
	{
		ReadParameterToSegd_BCD(pFile, 2, iChannel);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pFirstTimingWordTrace);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceHeaderExtensionTrace);
	ReadInitToWriteSegdNew_BCD(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSampleSkewTrace);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceEditTrace);
	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTimeBreakWindowTrace);
	ReadInitToWriteSegdNew_BCD(pFile, 2, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedChannelSetNumberTrace);
	ReadInitToWriteSegdNew_BCD(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedFileNumberTrace);
}

void ProcessTraceHeaderExtensionBlock1BackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct)//ichannel Ϊ��ţ�1-98
{

	ReadParameterToSegd_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_iLineIndex);

	if (iChannel == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointNumberTrace1);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_iPointIndex);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointIndexTrace1);

	if (pSegdFileStruct->m_oSegdSH.m_iSampleLength == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNumberSamplesPerTraceTrace1);
	} 
	else
	{
		ReadParameterToSegd_BIN(pFile, 3, pSegdFileStruct->m_oSegdSH.m_iSampleLength);
	}

	ReadInitToWriteSegdNew_BCD(pFile, 5, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedReceiverLineNumberTrace1);
	ReadInitToWriteSegdNew_BCD(pFile, 5, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedReceiverPointNumberTrace1);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSensorSEGDCodeTrace1);
	ReadInitToWriteSegdNew_BCD(pFile, 11, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace1);
}

void ProcessTraceHeaderExtensionBlock2BackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_DOUBLE(pFile, 8, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointEastingTrace2);
	ReadInitToWriteSegdNew_DOUBLE(pFile, 8, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointNorthingTrace2);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointElevationTrace2);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSensorTypeNumberTrace2);
	ReadInitToWriteSegdNew_BCD(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace2);
	ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pDSDIdentificationNoTrace2);

	if (iChannel == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedTraceNoTrace2);
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, iChannel);
	}

}

void ProcessTraceHeaderExtensionBlock3BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pResistanceLowLimitTrace3);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pResistanceHighLimitTrace3);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pResistanceResistanceValueTrace3);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTiltLimitTrace3);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTiltValueTrace3);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pResistanceErrorTrace3);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTiltErrorTrace3);
	ReadInitToWriteSegdNew_BCD(pFile, 10, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace3);
}

void ProcessTraceHeaderExtensionBlock4BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCapacitanceLowLimitTrace4);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCapacitanceHighLimitTrace4);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCapacitanceValueTrace4);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCutOffLowLimitTrace4);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCutOffHighLimitsTrace4);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCutOffValueTrace4);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCapacitanceErrorTrace4);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCutOffErrorTrace4);
	ReadInitToWriteSegdNew_BCD(pFile, 6, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace4);
}

void ProcessTraceHeaderExtensionBlock5BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pLeakageLimitTrace5);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pLeakageValueTrace5);
	ReadInitToWriteSegdNew_BCD(pFile, 16, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsed1Trace5);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pLeakageErrorTrace5);
	ReadInitToWriteSegdNew_BCD(pFile, 7, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsed2Trace5);

}

void ProcessTraceHeaderExtensionBlock6BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pUnitTypeTrace6);
	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pUnitSerialNumberTrace6);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelNumberTrace6);
	ReadInitToWriteSegdNew_BCD(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSpare1Trace6);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pAssemblyTypeTrace6);
	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pFDUorDSUAssemblySerialNumberTrace6);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pLocationInFDUorDSUAssemblyTrace6);
	ReadInitToWriteSegdNew_BCD(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSpare2Trace6);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSubunitTypeTrace6);

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelTypeTrace6);
	ReadInitToWriteSegdNew_BCD(pFile, 2, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSpare3Trace6);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSensorSensitivityTrace6);
	ReadInitToWriteSegdNew_BCD(pFile, 8, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace6);

}

void ProcessTraceHeaderExtensionBlock7BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pControlUnitTypeTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pControlUnitSerialNumberTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelGainScaleTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelFilterTrace7);

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelDataErrorTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelEditedStatusTrace7);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelSampleTomVConversionFactorTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNumberOfStacksNoisyTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNumberOfStacksLowTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelTypeIdTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelProcessTrace7);
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceMaxValueTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceMaxTimeTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNumberInterpolationsTrace7);
	ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSeismicTraceOffsetValueTrace7);

	pSegdFileStruct->m_pSegdDHList->pop_front();

}

void ProcessTraceDataBackNew(FILE* pFile, int iInstrNo, m_oSegdFileStruct* pSegdFileStruct)
{
	for(int i = 0; i<pSegdFileStruct->m_oSegdSH.m_iSampleLength; i++)
	{
		ReadArrayToWriteSegdData_FLOAT(pFile, iInstrNo, i, pSegdFileStruct);
	}
}

void ReadArrayToWriteSegdData_FLOAT(FILE* pFile, int iInstrNo, int iDataNo, m_oSegdFileStruct* pSegdFileStruct)
{
	int iResultNew = 0;
	int iTemp = 0;
	CString strTemp = _T("");
	float fTemp = 0;

	char charByte[SIZE_BUFFER];
	char charFinal[SIZE_BUFFER];
	unsigned char charTemp[SIZE_BUFFER];
	memset(charTemp, 0, sizeof(unsigned char)*SIZE_BUFFER);
	memset(charByte, 0, sizeof(char)*SIZE_BUFFER);
	memset(charFinal, 0, sizeof(char)*SIZE_BUFFER);


	memmove(charTemp, &pSegdFileStruct->m_pSegdDataBuf[(iInstrNo-1)*pSegdFileStruct->m_oSegdSH.m_iSampleLength*3 + 3*iDataNo], 3);
	memmove(&iTemp, charTemp, 3);
	if (iTemp - 0x800000 > 0) 
	{
		iTemp = iTemp - 16777216;
	}
	fTemp = (float)(iTemp);

	//floatת4byte char����4byteλ�õ���
	memcpy(charByte, (char*)&fTemp, 4);
	for (int i = 0; i<4; i++)
	{
		charFinal[i] = charByte[4-i-1];
	}

	iResultNew = fseek(pFile, 0, SEEK_CUR);
	fwrite(charFinal, sizeof(char), 4, pFile);

}

int ReadInitToWriteSegdNew_BCD(FILE* pFile, int iCountByte, char* pParameter)
{
	int iResultNew = 0;
	int iTemp = 0;
	CString strTemp = _T("");
	int iLenth = 0;

	char charByte[SIZE_BUFFER];
	memset(charByte, 0, sizeof(char)*SIZE_BUFFER);

	strTemp = CString(pParameter);
	for (int i = 0; i<iCountByte; i++)
	{
		_stscanf_s(strTemp.Mid(i*2, 2), _T("%02x"), &iTemp);
		charByte[i] = (char)iTemp;
	}
	iLenth = _ttoi(strTemp);

	iResultNew = fseek(pFile, 0, SEEK_CUR);
	fwrite(charByte, sizeof(char), iCountByte, pFile);

	return iLenth;
}

int ReadInitToWriteSegdNew_BIN(FILE* pFile, int iCountByte, char* pParameter)
{
	int iResultNew = 0;
	int iTemp = 0;
	CString strTemp = _T("");
	int iReturn = 0;
	char charByte[SIZE_BUFFER];
	memset(charByte, 0, sizeof(char)*SIZE_BUFFER);
	iReturn = _ttoi(CString(pParameter));
	if(iCountByte == 1)
	{
		strTemp.Format(_T("%02x"), iReturn);
	}
	else if(iCountByte == 2)
	{
		strTemp.Format(_T("%04x"), iReturn);
	}
	else if(iCountByte == 3)
	{
		strTemp.Format(_T("%06x"), iReturn);
	}
	else if(iCountByte == 4)
	{
		strTemp.Format(_T("%08x"), iReturn);
	}

	for(int i = 0; i< iCountByte; i++)
	{
		_stscanf_s(strTemp.Mid(i*2, 2), _T("%02x"), &iTemp);
		charByte[i] = (char)iTemp;
	}

	iResultNew = fseek(pFile, 0, SEEK_CUR);
	fwrite(charByte, sizeof(char), iCountByte, pFile);

	return iReturn;
}

void ReadInitToWriteSegdNew_BCD_addLow(FILE* pFile, int iCountByte, char* pParameter, string strHigh)
{
	int iResultNew = 0;
	CString strTemp = _T("");
	int iTemp = 0;
	CString cstrHigh = _T("");

	char charByte[SIZE_BUFFER];
	memset(charByte, 0, sizeof(char)*SIZE_BUFFER);

	cstrHigh.Format(_T("%s"), strHigh);

	strTemp = cstrHigh + CString(pParameter);

	for (int i = 0; i<iCountByte; i++)
	{
		_stscanf_s(strTemp.Mid(i*2, 2), _T("%02x"), &iTemp);
		charByte[i] = (char)iTemp;
	}

	iResultNew = fseek(pFile, 0, SEEK_CUR);
	fwrite(charByte, sizeof(char), iCountByte, pFile);
}

void ReadInitToWriteSegdNew_BCD_addHigh(char* pParameter, string* pstr)
{
	(*pstr).assign(pParameter, strlen(pParameter));
}

void ReadInitToWriteSegdNew_FLOAT(FILE* pFile, int iCountByte, char* pParameter)
{
	int iResultNew = 0;
	CString strTemp = _T("");
	float fTemp = 0;

	char charByte[SIZE_BUFFER];
	char charFinal[SIZE_BUFFER];
	memset(charByte, 0, sizeof(char)*SIZE_BUFFER);
	memset(charFinal, 0, sizeof(char)*SIZE_BUFFER);

	if (CString(pParameter) == "N+")
	{
		charFinal[0] = 0x7f;
		charFinal[1] = 0xff;
		charFinal[2] = 0xff;
		charFinal[3] = 0xff;
	} 
	else if (CString(pParameter) == "N-")
	{
		charFinal[0] = 0xff;
		charFinal[1] = 0xff;
		charFinal[2] = 0xff;
		charFinal[3] = 0xff;
	}
	else
	{
		fTemp = (float)_ttof(CString(pParameter));
		memcpy(charByte, (char*)&fTemp, iCountByte);
		for (int i = 0; i<iCountByte; i++)
		{
			charFinal[i] = charByte[iCountByte-i-1];
		}
	}
	iResultNew = fseek(pFile, 0, SEEK_CUR);
	fwrite(charFinal, sizeof(char), iCountByte, pFile);

}

void ReadInitToWriteSegdNew_DOUBLE(FILE* pFile, int iCountByte, char* pParameter)
{
	int iResultNew = 0;
	CString strTemp = _T("");
	double dTemp = 0;

	char charByte[SIZE_BUFFER];
	char charFinal[SIZE_BUFFER];
	memset(charByte, 0, sizeof(char)*SIZE_BUFFER);
	memset(charFinal, 0, sizeof(char)*SIZE_BUFFER);

	dTemp = _ttof(CString(pParameter));
	memcpy(charByte, (char*)&dTemp, iCountByte);
	for (int i = 0; i<iCountByte; i++) 
	{
		charFinal[i] = charByte[iCountByte-i-1];
	}

	iResultNew = fseek(pFile, 0, SEEK_CUR);
	fwrite(charFinal, sizeof(char), iCountByte, pFile);
}

void ReadInitToWriteSegdNew_ASC(FILE* pFile, int iCountByte, char* pParameter)
{
	int iResultNew = 0;
	CString strTemp = _T("");

	char charByte[1024];
	memset(charByte, 0, sizeof(char)*1024);
	if (iCountByte > 0)
	{

		iResultNew = fseek(pFile, 0, SEEK_CUR);
		fwrite(pParameter, sizeof(char), iCountByte, pFile);
	}
}

void ReadParameterToSegd_BIN(FILE* pFile, int iCountByte, int iValue)
{

	int iResultNew = 0;
	int iTemp = 0;
	CString strTemp = _T("");

	char charByte[SIZE_BUFFER];
	memset(charByte, 0, sizeof(char)*SIZE_BUFFER);

	if(iCountByte == 1)
	{
		strTemp.Format(_T("%02x"), iValue);
	}
	else if(iCountByte == 2)
	{
		strTemp.Format(_T("%04x"), iValue);
	}
	else if(iCountByte == 3)
	{
		strTemp.Format(_T("%06x"), iValue);
	}
	else if(iCountByte == 4)
	{
		strTemp.Format(_T("%08x"), iValue);
	}

	for(int i = 0; i< iCountByte; i++)
	{
		_stscanf_s(strTemp.Mid(i*2, 2), _T("%02x"), &iTemp);
		charByte[i] = (char)iTemp;
	}

	iResultNew = fseek(pFile, 0, SEEK_CUR);
	fwrite(charByte, sizeof(char), iCountByte, pFile);

}

void ReadParameterToSegd_BCD(FILE* pFile, int iCountByte, int iValue)
{

	int iResultNew = 0;
	CString strTemp = _T("");
	int iTemp = 0;
	CString strZero = _T("");
	char charByte[SIZE_BUFFER];
	memset(charByte, 0, sizeof(char)*SIZE_BUFFER);

	strTemp.Format(_T("%d"), iValue);
	for (int i = 0; i<iCountByte *2 - (int)_tcslen(strTemp); i++)
	{
		strZero += _T("0");
	}
	strTemp = strZero + strTemp;

	for (int i = 0; i<iCountByte; i++)
	{
		_stscanf_s(strTemp.Mid(i*2, 2), _T("%02x"), &iTemp);
		charByte[i] = (char)iTemp;
	}
	iResultNew = fseek(pFile, 0, SEEK_CUR);
	fwrite(charByte, sizeof(char), iCountByte, pFile);
}