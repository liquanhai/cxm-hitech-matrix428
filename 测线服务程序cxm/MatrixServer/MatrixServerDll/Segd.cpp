#include "stdafx.h"
#include "MatrixServerDll.h"
// ��ʼ��SEGD�ļ���׼ͷ
void OnInitSegdSH(m_oSegdStandardHeaderStruct* pSegdSH)
{
	//˵�����ֽ���������
	//��λ���ļ���� (0-9999),2,0327
	pSegdSH->m_pFileNumberGeneral1 = "0327";
	//��ʽ����,2,8058
	pSegdSH->m_pFormatCodeGeneral1 = "8058";
	//��ͨ����,6,000000000005
	pSegdSH->m_pGeneralConstantsGeneral1 = "000000000005";
	//��ݵ������λ��(0-99),1,12
	pSegdSH->m_pLastTwoDigitsOfYearGeneral1 = "12";
	//��ͨͷ���ж������ݿ���Ŀ,H,2
	pSegdSH->m_pNumberAdditionalBlocksGeneral1 = "2";
	//�����գ�3 λ��(1-366),L+1,187
	pSegdSH->m_pJulianDayGeneral1 = "187";
	//һ���е�Сʱ��0-23��,1,08
	pSegdSH->m_pHourOfDayGeneral1 = "08";
	//Сʱ�еķ��ӣ�0-59��,1,36
	pSegdSH->m_pMinuteOfHourGeneral1 = "36";
	//�����е����ӣ�0-59��,1,06
	pSegdSH->m_pSecondOfMinuteGeneral1 = "06";
	//�����̴���,1,13
	pSegdSH->m_pManufacturerCodeGeneral1 = "13";
	//���������к�,2,0000
	pSegdSH->m_pManufacturerSerialNumberGeneral1 = "0000";
	//ÿ��ɨ���ֽ���,3,000000
	pSegdSH->m_pBytesPerScanGeneral1 = "000000";
	//����ɨ����,1,10
	pSegdSH->m_pBaseScanIntervalGeneral1 = "10";
	//����,H,0
	pSegdSH->m_pPolarityGeneral1 = "0";
	//δʹ��,L+1,000
	pSegdSH->m_pNotUsedGeneral1 = "000";
	//��¼����,H,8
	pSegdSH->m_pRecordTypeGeneral1 = "8";
	//��¼����,L+1,fff
	pSegdSH->m_pRecordLengthGeneral1 = "fff";
	//ÿ����¼��ɨ������,1,01
	pSegdSH->m_pScanTypePerRecordGeneral1 = "01";
	//ÿ����¼�ĵ��������Ŀ,1,16
	pSegdSH->m_pNumberChannelSetsPerRecordGeneral1 = "16";
	//����ʱ�� 32 �ֽ���չ����Ŀ,1,00
	pSegdSH->m_pNumberSampleSkew32ByteExtensionsGeneral1 = "00";
	//��չͷ�γ���,1,32
	pSegdSH->m_pExtendedHeaderLengthGeneral1 = "32";
	//�ⲿͷ�γ���,1,32
	pSegdSH->m_pExternalHeaderLengthGeneral1 = "32";
	
	//��չ�ļ����,3,327
	pSegdSH->m_pExpandedFileNumberGeneral2 = "327";
	//��չ�������/ ɨ�����ͣ�δʹ�ã�,2,0000
	pSegdSH->m_pExpandedChannelSetsGeneral2 = "0000";
	//��չͷ�����ݿ飨δʹ�ã�,2,0000
	pSegdSH->m_pExtendedHeaderBlocksGeneral2 = "0000";
	//�ⲿͷ�����ݿ�,2,00
	pSegdSH->m_pExternalHeaderBlocksGeneral2 = "00";
	//δʹ��,1,00
	pSegdSH->m_pNotUsed1General2 = "00";
	//SEG-D �汾��,2,0201
	pSegdSH->m_pSegdRevisionNumberGeneral2 = "0201";
	//��ͨβ�����ݿ���Ŀ,2,0000
	pSegdSH->m_pNumberBlocksGeneralTrailerGeneral2 = "0000";
	//��չ��¼���ȣ�0-128000 ���룩,3,4000
	pSegdSH->m_pExpandedRecordLengthGeneral2 = "4000";
	//δʹ��,1,00
	pSegdSH->m_pNotUsed2General2 = "00";
	//��ͨͷ�����ݿ���,1,02
	pSegdSH->m_pGeneralHeaderBlockNumberGeneral2 = "02";
	//δʹ��,13,00000000000000000000000000
	pSegdSH->m_pNotUsed3General2 = "00000000000000000000000000";
	//��չ�ļ����,3,000147
	pSegdSH->m_pExpandedFileNumberGeneral3 = "000147";
	//��Դ���ߺ�(0-99999.99),5,0000030000
	pSegdSH->m_pSourceLineNumberGeneral3 = "0000030000";
	//��Դ���(0-99999.99),5,00001e0000
	pSegdSH->m_pSourcePointNumberGeneral3 = "00001e0000";
	//��Դ������ (1-9),1,01
	pSegdSH->m_pSourcePointIndexGeneral3 = "01";
	//��λ���ƣ�δ��¼�ģ�,1,00
	pSegdSH->m_pPhaseControlGeneral3 = "00";
	//�ɿ���Դ���ͣ�δ��¼�ģ�,1,00
	pSegdSH->m_pVibratorTypeGeneral3 = "00";
	//��λ�ǣ�δ��¼�ģ�,2,0000
	pSegdSH->m_pPhaseAngleGeneral3 = "0000";
	//��ͨͷ�����ݿ���,1,03
	pSegdSH->m_pGeneralHeaderBlockNumberGeneral3 = "03";
	//��Դ���,1,01
	pSegdSH->m_pSourceSetNumberGeneral3 = "01";
	//δʹ��,12,000000000000000000000000
	pSegdSH->m_pNotUsedGeneral3 = "000000000000000000000000";

	//˵�����ֽ���������1������2������3���˺��ͬ����3������16
	//ɨ������ͷ��,1,01,01,00...
	pSegdSH->m_pScanTypeHeaderScan[0] = "01";
	pSegdSH->m_pScanTypeHeaderScan[1] = "01";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pScanTypeHeaderScan[i] = "00";
	}
	//��������,1,01,02,00...
	pSegdSH->m_pChannelSetNumberScan[0] = "01";
	pSegdSH->m_pChannelSetNumberScan[1] = "02";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pChannelSetNumberScan[i] = "00";
	}
	//���������ʼʱ��,2,00,00,00...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pChannelSetStartingTimeScan[i] = "00";
	}
	//����������ʱ��,2,2000,2000,00...
	pSegdSH->m_pChannelSetEndTimeScan[0] = "2000";
	pSegdSH->m_pChannelSetEndTimeScan[1] = "2000";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pChannelSetEndTimeScan[i] = "00";
	}
	//��С��������,2,6db7,6db7,0000...
	pSegdSH->m_pDescaleMultiplierScan[0] = "6db7";
	pSegdSH->m_pDescaleMultiplierScan[1] = "6db7";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pDescaleMultiplierScan[i] = "0000";
	}
	//�˵�������е������Ŀ,2,0002,0012,0000...
	pSegdSH->m_pNumberChannelsOfChannelSetScan[0] = "0002";
	pSegdSH->m_pNumberChannelsOfChannelSetScan[1] = "0012";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pNumberChannelsOfChannelSetScan[i] = "0000";
	}
	//��������ͱ�ʶ,H,9,1,0...
	pSegdSH->m_pChannelTypeIdentificationScan[0] = "9";
	pSegdSH->m_pChannelTypeIdentificationScan[1] = "1";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pChannelTypeIdentificationScan[i] = "0";
	}
	//δʹ��,L,0,0,0...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pNotUsedScan[i] = "0";
	}
	//��ɨ��ָ����Ŀ,H,0,0,0...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pNumberSubscansExponentScan[i] = "0";
	}
	//�����������Ʒ������̶����棩,L,3,3,0...
	pSegdSH->m_pChannelGainControlMethodScan[0] = "3";
	pSegdSH->m_pChannelGainControlMethodScan[1] = "3";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pChannelGainControlMethodScan[i] = "0";
	}
	//3dB �㴦�Ļ���˲���Ƶ��,2,0400,0400,0000...
	pSegdSH->m_pAliasFilterFrequency3dBPointScan[0] = "0400";
	pSegdSH->m_pAliasFilterFrequency3dBPointScan[1] = "0400";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pAliasFilterFrequency3dBPointScan[i] = "0000";
	}
	//����˲���б��,2,0370,0370,0000...
	pSegdSH->m_pAliasFilterSlopeScan[0] = "0370";
	pSegdSH->m_pAliasFilterSlopeScan[1] = "0370";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pAliasFilterSlopeScan[i] = "0000";
	}
	//�ͽ��˲���Ƶ��,2,0000,0000,0000...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pLowCutFilterFrequencyScan[i] = "0000";
	}
	//�ͽ��˲���б��,2,0000,0000,0000...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pLowCutFilterSlopeScan[i] = "0000";
	}
	//��һ�ݲ�Ƶ��,2,0000,0000,0000...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pFirstNotchFrequencyScan[i] = "0000";
	}
	//�ڶ��ݲ�Ƶ��,2,0000,0000,0000...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pSecondNotchFrequencyScan[i] = "0000";
	}
	//�����ݲ�Ƶ��,2,0000,0000,0000...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pThirdNotchFrequencyScan[i] = "0000";
	}
	//��չ��������,2,0000,0000,0000...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pExtendedChannelSetNumberScan[i] = "0000";
	}
	//��չͷ�α��,H,0,0,0...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pExtendedHeaderFlagScan[i] = "0";
	}
	//��ͷ��չ,L,7,7,0...
	pSegdSH->m_pTraceHeaderExtensionsScan[0] = "7";
	pSegdSH->m_pTraceHeaderExtensionsScan[1] = "7";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pTraceHeaderExtensionsScan[i] = "0";
	}
	//��ֱ����,1,01,01,00...
	pSegdSH->m_pVerticalStackScan[0] = "01";
	pSegdSH->m_pVerticalStackScan[1] = "01";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pVerticalStackScan[i] = "00";
	}
	//���µ��º�,1,00,00,00...
	for (int i = 0; i < 16; i++)
	{
		pSegdSH->m_pStreamerCableNumberScan[i] = "00";
	}
	//������ɣ���������ɣ�,1,01,01,00...
	pSegdSH->m_pArrayFormingScan[0] = "01";
	pSegdSH->m_pArrayFormingScan[1] = "01";
	for (int i = 2; i < 16; i++)
	{
		pSegdSH->m_pArrayFormingScan[i] = "00";
	}
	//�ɼ�����,4,4000
	pSegdSH->m_pAcquisitionLengthExtended = "4000";
	//������,4,1000
	pSegdSH->m_pSampleRateExtended = "1000";
	//��¼������,4,14
	pSegdSH->m_pTotalNumberTracesExtended = "14";
	//��������Ŀ,4,02
	pSegdSH->m_pNumberAuxesExtended = "02";
	//�����¼����Ŀ,4,12
	pSegdSH->m_pNumberSeisTracesExtended = "12";
	//ͣ�͵����¼����Ŀ,4,00
	pSegdSH->m_pNumberDeadSeisTracesExtended = "00";
	//������¼����Ŀ,4,12
	pSegdSH->m_pNumberLiveSeisTracesExtended = "12";
	//��Դ����,4,01
	pSegdSH->m_pTypeSourceExtended = "01";
	//��¼����������Ŀ,4,4001
	pSegdSH->m_pNumberSamplesInTraceExtended = "4001";
	//�ں�,4,01
	pSegdSH->m_pShotNumberExtended = "01";
	//TB ����,4,3000.000000
	pSegdSH->m_pTBWindowExtended = "3000.000000";
	//���Լ�¼����,4,00
	pSegdSH->m_pTestRecordTypeExtended = "00";
	//������һ������,4,01
	pSegdSH->m_pSpreadFirstLineExtended = "01";
	//������һ������,4,34
	pSegdSH->m_pSpreadFirstNumberExtended = "34";
	//���б��,4,01
	pSegdSH->m_pSpreadNumberExtended = "01";
	//��������,4,01
	pSegdSH->m_pSpreadTypeExtended = "01";
	//ʱ���ź�,4,00
	pSegdSH->m_pTimebreakExtended = "00";
	//����ʱ��,4,00
	pSegdSH->m_pUpholeTimeExtended = "00";
	//��ը����ʶ��,4,01
	pSegdSH->m_pBlasterIdExtended = "01";
	//��ը��״̬,4,02
	pSegdSH->m_pBlasterStatusExtended = "02";
	//�����ӳ�,4,00
	pSegdSH->m_pRefractionDelayExtended = "00";
	//Tb �� T0 ʱ��,4,00
	pSegdSH->m_pTBtoT0TimeExtended = "00";
	//�ڲ�ʱ���ź�,4,00
	pSegdSH->m_pInternalTimeBreakExtended = "00";
	//Ұ���豸��Ԥ����,4,00
	pSegdSH->m_pPrestackWithinFieldUnitsExtended = "00";
	//������������,4,01
	pSegdSH->m_pNoiseEliminationTypeExtended = "01";
	//�ͼ�¼���ٷֱ�,4,00
	pSegdSH->m_pLowTracePercentageExtended = "00";
	//�ͼ�¼��ֵ,4,00
	pSegdSH->m_pLowTraceValueExtended = "00";
	//������Ŀ,4,00
	pSegdSH->m_pNumberWindowsOrWindowLengthExtended = "00";
	//��ʷ�༭����,4,00
	pSegdSH->m_pHistoricEditingTypeOrOverlapExtended = "00";
	//������¼���ٷֱ�,4,00
	pSegdSH->m_pNoisyTracePercentageExtended = "00";
	//��ʷ��Χ,4,00
	pSegdSH->m_pHistoricRangeExtended = "00";
	//��ʷ׶�γ��� 2 ��ָ��,4,00
	pSegdSH->m_pHistoricTaperLengthExtended = "00";
	//�ż�ֵ����/ �仯,4,00
	pSegdSH->m_pThresholdHoldOrNotExtended = "00";
	//��ʷ�ż�ֵ��ʼֵ,4,00
	pSegdSH->m_pHistoricThresholdInitValueExtended = "00";
	//��ʷ���㳤��,4,00
	pSegdSH->m_pHistoricZeroingLengthExtended = "00";
	//��������,4,01
	pSegdSH->m_pTypeProcessExtended = "01";
	//�ɼ����ͱ�,128,00
	pSegdSH->m_pAcquisitionTypeTablesExtended = "00";
	//�ż�ֵ���ͱ�,128,00
	pSegdSH->m_pThresholdTypeTablesExtended = "00";
	//���Ӵ���,4,01
	pSegdSH->m_pStackingFoldExtended = "01";
	//δʹ��,80,00
	pSegdSH->m_pNotUsed1Extended = "02";
	//��¼����,4,4000
	pSegdSH->m_pRecordLengthExtended = "4000";
	//����ط�ֵʱ��,4,00
	pSegdSH->m_pAutocorrelationPeakTimeExtended = "00";
	//δʹ��,4,00
	pSegdSH->m_pNotUsed2Extended = "00";
	//��زο��źű��,4,00
	pSegdSH->m_pCorrelationPilotNoExtended = "00";
	//�ο��źų���,4,00
	pSegdSH->m_pPilotLengthExtended = "00";
	//ɨ�賤��,4,00
	pSegdSH->m_pSweepLengthExtended = "00";
	//�ɼ���,4,01
	pSegdSH->m_pAcquisitionNumberExtended = "01";
	//��ศ���������ֵ,4,3041785.250000
	pSegdSH->m_pMaxOfMaxAuxExtended = "3041785.250000";
	//����������ֵ,4,-614945.500000
	pSegdSH->m_pMaxOfMaxSeisExtended = "-614945.500000";
	//ת�����Ӵ���,4,01
	pSegdSH->m_pDumpStackingFoldExtended = "01";
	//�Ŵ���ǩ,16,label
	pSegdSH->m_pTapeLabelExtended = "label";
	//�Ŵ���,4,50
	pSegdSH->m_pTapeNumberExtended = "50";
	//����汾,16,4.0
	pSegdSH->m_pSoftwareVersionExtended = "4.0";
	//����,12,05 Jul 2012
	pSegdSH->m_pDateExtended = "05 Jul 2012";
	//��Դƫ����,8,0
	pSegdSH->m_pSourceEastingExtended = "0";
	//��Դ����γ�Ȳ�,8,0
	pSegdSH->m_pSourceNorthingExtended = "0";
	//��Դ�߳�,4,0.000000
	pSegdSH->m_pSourceElevationExtended = "0.000000";
	//���õĻ���ɨ��ģʽ,4,00
	pSegdSH->m_pSlipSweepModeUsedExtended = "00";
	//ÿ���Ŵ����ļ���,4,2000
	pSegdSH->m_pFilesPerTapeExtended = "2000";
	//�ļ�����,4,01
	pSegdSH->m_pFileCountExtended = "01";
	//�ɼ�����˵��,160,
	memset(pSegdSH->m_pAcquisitionErrorDescriptionExtended, 0, sizeof(char) * 160);
	
	//�˲�������,4,02
	pSegdSH->m_pFilterTypeExtended = "02";
	//������ת��,4,00
	pSegdSH->m_pStackDumpedExtended = "00";
	//���ӷ��ţ���ǰ��,4,01
	pSegdSH->m_pStackSignExtended = "01";
	//���õ� PRM ��б��У��,4,00
	pSegdSH->m_pPRMTiltCorrectionUsedExtended = "00";
	//������,64,D5
	pSegdSH->m_pSwathNameExtended = "D5";
	//����ģʽ,4,01
	pSegdSH->m_pOperatingModeExtended = "01";
	//����,4,79
	pSegdSH->m_pReserved1Extended = "79";
	//�޼�¼,4,00
	pSegdSH->m_pNoLogExtended = "00";
	//����ʱ��,4,4000
	pSegdSH->m_pListeningTimeExtended = "4000";
	//ת������,4,00
	pSegdSH->m_pTypeDumpExtended = "00";
	//����,4,00
	pSegdSH->m_pReserved2Extended = "00";
	//���� Id,4,01
	pSegdSH->m_pSwathIdExtended = "01";
	//,4,00
	pSegdSH->m_pSeismicTraceOffsetRemovalDisabledExtended = "00";
	//,8,0003a4ac0c90344f
	pSegdSH->m_pGPSTimeAcquisitionTimeBreakExtended = "0003a4ac0c90344f";
	//,8,0000000000000000
	pSegdSH->m_pAlignedGPSTimeAcquisitionExtended = "0000000000000000";
	//δʹ��,132,000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	pSegdSH->m_pNotUsed3Extended = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	//�ⲿͷ��,m_pExternalHeaderLengthGeneral1*32,*SHOTPRO SP#    1/SL#    3.0/SN#   30.0/SI#1/SEQ# 1/STA:2/CTB:00.000/UH:000.0
	pSegdSH->m_pConcatenationOfExternal = "*SHOTPRO SP#    1/SL#    3.0/SN#   30.0/SI#1/SEQ# 1/STA:2/CTB:00.000/UH:000.0";
}

// ��ʼ��SEGD�ļ����ݵ�ͷ
void OnInitSegdTH(m_oSegdTraceHeaderStruct* pSegdTH, bool bAcqTrace)
{
	//˵�����ֽ������ɼ������ݣ�����������
	//��λ���ļ���(0-9999),2,0327,0327
	pSegdTH->m_pFileNumberTrace = "0327";
	//ɨ�����ͱ��,1,01,01
	pSegdTH->m_pScanTypeNumberTrace = "01";
	//��������,1,02,01
	if (bAcqTrace == true)
	{
		pSegdTH->m_pChannelSetNumberTrace = "02";
	}
	else
	{
		pSegdTH->m_pChannelSetNumberTrace = "01";
	}
	//��¼�����,2,0001,0001
	pSegdTH->m_pTraceNumberTrace = "0001";
	//��һ����ʱ��,3,00,00
	pSegdTH->m_pFirstTimingWordTrace = "00";
	//��ͷ��չ,1,07,07
	pSegdTH->m_pTraceHeaderExtensionTrace = "07";
	//����ʱ��,1,00,00
	pSegdTH->m_pSampleSkewTrace = "00";
	//��¼���༭,1,00,00
	pSegdTH->m_pTraceEditTrace = "00";
	//ʱ���źŴ���,3,00,00
	pSegdTH->m_pTimeBreakWindowTrace = "00";
	//��չ��������,2,0000,0000
	pSegdTH->m_pExtendedChannelSetNumberTrace = "0000";
	//��չ�ļ����,3,000147,000147
	pSegdTH->m_pExtendedFileNumberTrace = "000147";

	//���յ���ߺ�,3,01,00
	if (bAcqTrace == true)
	{
		pSegdTH->m_pReceiverLineNumberTrace1 = "01";
	}
	else
	{
		pSegdTH->m_pReceiverLineNumberTrace1 = "00";
	}
	//���յ��,3,34,01
	if (bAcqTrace == true)
	{
		pSegdTH->m_pReceiverPointNumberTrace1 = "34";
	}
	else
	{
		pSegdTH->m_pReceiverPointNumberTrace1 = "01";
	}
	//���յ�����,1,01,01
	pSegdTH->m_pReceiverPointIndexTrace1 = "01";
	//ÿ����¼��������Ŀ,3,4001,4001
	pSegdTH->m_pNumberSamplesPerTraceTrace1 = "4001";
	//��չ���յ���ߺ�,5,0000000000,0000000000
	pSegdTH->m_pExtendedReceiverLineNumberTrace1 = "0000000000";
	//��չ���յ��,5,0000000000,0000000000
	pSegdTH->m_pExtendedReceiverPointNumberTrace1 = "0000000000";
	//�첨�� SEGD ����,1,02,00
	if (bAcqTrace == true)
	{
		pSegdTH->m_pSensorSEGDCodeTrace1 = "02";
	}
	else
	{
		pSegdTH->m_pSensorSEGDCodeTrace1 = "00";
	}
	//δʹ��,11,0000000000000000000000,0000000000000000000000
	pSegdTH->m_pNotUsedTrace1 = "0000000000000000000000";
	//���յ�ƫ����,8,0,0
	pSegdTH->m_pReceiverPointEastingTrace2 = "0";
	//���յ㱱��γ�Ȳ�,8,0,0
	pSegdTH->m_pReceiverPointNorthingTrace2 = "0";
	//���յ�߳�,4,0.000000,0.000000
	pSegdTH->m_pReceiverPointElevationTrace2 = "0.000000";
	//�첨�����ͱ�ţ�1 �� 9��,1,01,00
	if (bAcqTrace == true)
	{
		pSegdTH->m_pSensorTypeNumberTrace2 = "01";
	}
	else
	{
		pSegdTH->m_pSensorTypeNumberTrace2 = "00";
	}
	//δʹ��,3,000000,000000
	pSegdTH->m_pNotUsedTrace2 = "000000";
	//δʹ��,4,00,00
	pSegdTH->m_pDSDIdentificationNoTrace2 = "00";
	//��չ��¼�����,4,01,01
	pSegdTH->m_pExtendedTraceNoTrace2 = "01";

	//��������,4,300.000000,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pResistanceLowLimitTrace3 = "300.000000";
	}
	else
	{
		pSegdTH->m_pResistanceLowLimitTrace3 = "0.000000";
	}
	//��������,4,500.000000,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pResistanceHighLimitTrace3 = "500.000000";
	}
	else
	{
		pSegdTH->m_pResistanceHighLimitTrace3 = "0.000000";
	}
	//����ֵ,4,1904.939941,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pResistanceResistanceValueTrace3 = "1904.939941";
	}
	else
	{
		pSegdTH->m_pResistanceResistanceValueTrace3 = "0.000000";
	}
	//��б�Ƚ���,4,15.000000,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pTiltLimitTrace3 = "15.000000";
	}
	else
	{
		pSegdTH->m_pTiltLimitTrace3 = "0.000000";
	}
	//��б��ֵ,4,N-,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pTiltValueTrace3 = "N-";
	}
	else
	{
		pSegdTH->m_pTiltValueTrace3 = "0.000000";
	}
	//�������,1,01,00
	if (bAcqTrace == true)
	{
		pSegdTH->m_pResistanceErrorTrace3 = "01";
	}
	else
	{
		pSegdTH->m_pResistanceErrorTrace3 = "00";
	}
	//��б�����,1,00,00
	pSegdTH->m_pTiltErrorTrace3 = "00";
	//δʹ��,10,00000000000000000000,00000000000000000000
	pSegdTH->m_pNotUsedTrace3 = "00000000000000000000";

	//��������,4,N-,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pCapacitanceLowLimitTrace4 = "N-";
	}
	else
	{
		pSegdTH->m_pCapacitanceLowLimitTrace4 = "0.000000";
	}
	//��������,4,N-,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pCapacitanceHighLimitTrace4 = "N-";
	}
	else
	{
		pSegdTH->m_pCapacitanceHighLimitTrace4 = "0.000000";
	}
	//����ֵ,4,N-,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pCapacitanceValueTrace4 = "N-";
	}
	else
	{
		pSegdTH->m_pCapacitanceValueTrace4 = "0.000000";
	}
	//��ֹ����,4,N-,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pCutOffLowLimitTrace4 = "N-";
	}
	else
	{
		pSegdTH->m_pCutOffLowLimitTrace4 = "0.000000";
	}
	//��ֹ����,4,N-,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pCutOffHighLimitsTrace4 = "N-";
	}
	else
	{
		pSegdTH->m_pCutOffHighLimitsTrace4 = "0.000000";
	}
	//��ֵֹ,4,N-,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pCutOffValueTrace4 = "N-";
	}
	else
	{
		pSegdTH->m_pCutOffValueTrace4 = "0.000000";
	}
	//�������,1,00,00
	pSegdTH->m_pCapacitanceErrorTrace4 = "00";
	//��ֹ���,1,00,00
	pSegdTH->m_pCutOffErrorTrace4 = "00";
	//δʹ��,6,000000000000,000000000000
	pSegdTH->m_pNotUsedTrace4 = "000000000000";

	//©�����,4,5.000000,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pLeakageLimitTrace5 = "5.000000";
	}
	else
	{
		pSegdTH->m_pLeakageLimitTrace5 = "0.000000";
	}
	//©��ֵ,4,5.000000,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pLeakageValueTrace5 = "5.000000";
	}
	else
	{
		pSegdTH->m_pLeakageValueTrace5 = "0.000000";
	}
	//δʹ��,16,00000000000000000000000000000000,00000000000000000000000000000000
	pSegdTH->m_pNotUsed1Trace5 = "00000000000000000000000000000000";
	//©�����,1,00,00
	pSegdTH->m_pLeakageErrorTrace5 = "00";
	//δʹ��,7,00000000000000,00000000000000
	pSegdTH->m_pNotUsed2Trace5 = "00000000000000";

	//�豸����,1,01,01
	pSegdTH->m_pUnitTypeTrace6 = "01";
	//�豸���к�,3,6104422,4819236
	if (bAcqTrace == true)
	{
		pSegdTH->m_pUnitSerialNumberTrace6 = "6104422";
	}
	else
	{
		pSegdTH->m_pUnitSerialNumberTrace6 = "4819236";
	}
	//��������,1,01,01
	pSegdTH->m_pChannelNumberTrace6 = "01";
	//����,3,000000,000000
	pSegdTH->m_pSpare1Trace6 = "000000";
	//�������,1,03,04
	if (bAcqTrace == true)
	{
		pSegdTH->m_pAssemblyTypeTrace6 = "03";
	}
	else
	{
		pSegdTH->m_pAssemblyTypeTrace6 = "04";
	}
	//FDU �� DSU ������к�,3,1791352,4819236
	if (bAcqTrace == true)
	{
		pSegdTH->m_pFDUorDSUAssemblySerialNumberTrace6 = "1791352";
	}
	else
	{
		pSegdTH->m_pFDUorDSUAssemblySerialNumberTrace6 = "4819236";
	}
	//�� FDU �� DSU����е�λ��,1,02,01
	if (bAcqTrace == true)
	{
		pSegdTH->m_pLocationInFDUorDSUAssemblyTrace6 = "02";
	}
	else
	{
		pSegdTH->m_pLocationInFDUorDSUAssemblyTrace6 = "01";
	}
	//����,3,000000,000000
	pSegdTH->m_pSpare2Trace6 = "000000";
	//FDU �� DSU �豸����,1,01,21
	if (bAcqTrace == true)
	{
		pSegdTH->m_pSubunitTypeTrace6 = "01";
	}
	else
	{
		pSegdTH->m_pSubunitTypeTrace6 = "21";
	}
	//���������,1,00,00
	pSegdTH->m_pChannelTypeTrace6 = "00";
	//����,2,0000,0000
	pSegdTH->m_pSpare3Trace6 = "0000";
	//�첨��������,4,4294967296.000000,4294967296.000000
	pSegdTH->m_pSensorSensitivityTrace6 = "4294967296.000000";
	//δʹ��,8,0000000000000000,0000000000000000
	pSegdTH->m_pNotUsedTrace6 = "0000000000000000";

	//���Ƶ�Ԫ����,1,02,49
	if (bAcqTrace == true)
	{
		pSegdTH->m_pControlUnitTypeTrace7 = "02";
	}
	else
	{
		pSegdTH->m_pControlUnitTypeTrace7 = "49";
	}
	//���Ƶ�Ԫ���к�,3,17693,2442269
	if (bAcqTrace == true)
	{
		pSegdTH->m_pControlUnitSerialNumberTrace7 = "17693";
	}
	else
	{
		pSegdTH->m_pControlUnitSerialNumberTrace7 = "2442269";
	}
	//���������̶�,1,02,02
	pSegdTH->m_pChannelGainScaleTrace7 = "02";
	//������˲���,1,02,02
	pSegdTH->m_pChannelFilterTrace7 = "02";
	//�����������������Χ,1,00,00
	pSegdTH->m_pChannelDataErrorTrace7 = "00";
	//������༭״̬,1,00,00
	pSegdTH->m_pChannelEditedStatusTrace7 = "00";
	//�������������ת��ϵ��,4,0.000067,0.000000
	if (bAcqTrace == true)
	{
		pSegdTH->m_pChannelSampleTomVConversionFactorTrace7 = "0.000067";
	}
	else
	{
		pSegdTH->m_pChannelSampleTomVConversionFactorTrace7 = "0.000000";
	}
	//���������Ӵ���,1,00,00
	pSegdTH->m_pNumberOfStacksNoisyTrace7 = "00";
	//�͵��Ӵ���,1,00,00
	pSegdTH->m_pNumberOfStacksLowTrace7 = "00";
	//��������ͱ�ʶ��,1,01,09
	if (bAcqTrace == true)
	{
		pSegdTH->m_pChannelTypeIdTrace7 = "01";
	}
	else
	{
		pSegdTH->m_pChannelTypeIdTrace7 = "09";
	}
	//���������,1,01,01
	pSegdTH->m_pChannelProcessTrace7 = "01";
	//��¼�����ֵ,4,0.000000,0.000000
	pSegdTH->m_pTraceMaxValueTrace7 = "0.000000";
	//��¼�����ʱ��,4,00,00
	pSegdTH->m_pTraceMaxTimeTrace7 = "00";
	//�ڲ����,4,00,00
	pSegdTH->m_pNumberInterpolationsTrace7 = "00";
	//δʹ��,4,00,00
	pSegdTH->m_pSeismicTraceOffsetValueTrace7 = "00";
}
// ���浽Segd�ļ����ɹ�����true��ʧ�ܷ���false
bool SaveSegdFile(m_oSegdFileStruct* pSegdFileStruct)
{
	int iCountSeisChannel = 0;

	struct tm newtime;
	TCHAR tmpbuf[128];
	time_t lt1;
	time(&lt1);
	localtime_s(&newtime, &lt1);
	CString strTime = _T("");
	CString strFilePath = _T("");
	CString strPath = _T("");
	FILE* pNewSegdFile;
	string strTemp = "";
	_tcsftime(tmpbuf, 128, _T("%Y%m%d %I%M%S"), &newtime);
	strTime.Format(_T("\\%s"), tmpbuf);
	strPath = pSegdFileStruct->m_strPath.c_str();
//	strPath.Format(_T("%s"), pSegdFileStruct->m_strPath.c_str());
	strTime = strTime + _T(".segd"); 
	strFilePath = strPath + strTime;
	strTemp = (CStringA)strFilePath;
	if(0 != fopen_s(&pNewSegdFile, strTemp.c_str(), "wb+"))
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

	for(int i = 1; i< pSegdFileStruct->m_iTotalTraceNum + 1; i++)
	{

		iCountSeisChannel++;

		if (iCountSeisChannel > pSegdFileStruct->m_iAcqTraceNum)
		{
			iCountSeisChannel -= pSegdFileStruct->m_iAcqTraceNum;
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
	// @@@@�ڴ��ͷű���
// 	if (pSegdFileStruct->m_oSegdSH.m_pConcatenationOfExternal != NULL)
// 	{
// 		delete[] pSegdFileStruct->m_oSegdSH.m_pConcatenationOfExternal;
// 		pSegdFileStruct->m_oSegdSH.m_pConcatenationOfExternal = NULL;
// 	}
	return true;
}

void ProcessGeneralHeaderBlock1BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	string strHigh = "";
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pFileNumberGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pFormatCodeGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 6, pSegdFileStruct->m_oSegdSH.m_pGeneralConstantsGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pLastTwoDigitsOfYearGeneral1.c_str());

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pNumberAdditionalBlocksGeneral1.c_str(), &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pJulianDayGeneral1.c_str(), strHigh);

	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pHourOfDayGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pMinuteOfHourGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pSecondOfMinuteGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pManufacturerCodeGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pManufacturerSerialNumberGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 3, pSegdFileStruct->m_oSegdSH.m_pBytesPerScanGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pBaseScanIntervalGeneral1.c_str());

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pPolarityGeneral1.c_str(), &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pNotUsedGeneral1.c_str(), strHigh);

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pRecordTypeGeneral1.c_str(), &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pRecordLengthGeneral1.c_str(), strHigh);

	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pScanTypePerRecordGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNumberChannelSetsPerRecordGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNumberSampleSkew32ByteExtensionsGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pExtendedHeaderLengthGeneral1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pExternalHeaderLengthGeneral1.c_str());

}

void ProcessGeneralHeaderBlock2BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{
	ReadInitToWriteSegdNew_BIN(pFile, 3, pSegdFileStruct->m_oSegdSH.m_pExpandedFileNumberGeneral2.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pExpandedChannelSetsGeneral2.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pExtendedHeaderBlocksGeneral2.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pExternalHeaderBlocksGeneral2.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNotUsed1General2.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pSegdRevisionNumberGeneral2.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pNumberBlocksGeneralTrailerGeneral2.c_str());

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleTime == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 3, pSegdFileStruct->m_oSegdSH.m_pExpandedRecordLengthGeneral2.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 3, pSegdFileStruct->m_oSegdSH.m_uiSampleTime);
	}

	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNotUsed2General2.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pGeneralHeaderBlockNumberGeneral2.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 13, pSegdFileStruct->m_oSegdSH.m_pNotUsed3General2.c_str());
}

void ProcessGeneralHeaderBlock3BackNew(FILE* pFile,m_oSegdFileStruct* pSegdFileStruct)
{
	ReadInitToWriteSegdNew_BCD(pFile, 3, pSegdFileStruct->m_oSegdSH.m_pExpandedFileNumberGeneral3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 5, pSegdFileStruct->m_oSegdSH.m_pSourceLineNumberGeneral3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 5, pSegdFileStruct->m_oSegdSH.m_pSourcePointNumberGeneral3.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pSourcePointIndexGeneral3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pPhaseControlGeneral3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pVibratorTypeGeneral3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pPhaseAngleGeneral3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pGeneralHeaderBlockNumberGeneral3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pSourceSetNumberGeneral3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 12, pSegdFileStruct->m_oSegdSH.m_pNotUsedGeneral3.c_str());
}

void ProcessScanTypeHeaderBackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct)
{

	string strHigh = "";
	int iNumTrace = 0;
	CString strNumTrace = _T("");

	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pScanTypeHeaderScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pChannelSetNumberScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pChannelSetStartingTimeScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pChannelSetEndTimeScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pDescaleMultiplierScan[iChannel-1].c_str());
	if (iChannel == 1)
	{
		iNumTrace = pSegdFileStruct->m_iAuxTraceNum;
	}
	else if(iChannel == 2)
	{
		iNumTrace = pSegdFileStruct->m_iAcqTraceNum;
	}
	else
	{
		iNumTrace = 0;
	}

	if (iNumTrace == 0)
	{
		ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pNumberChannelsOfChannelSetScan[iChannel-1].c_str());
	}
	else
	{
		ReadParameterToSegd_BCD(pFile, 2, iNumTrace);
	}

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pChannelTypeIdentificationScan[iChannel-1].c_str(), &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pNotUsedScan[iChannel-1].c_str(), strHigh);
	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pNumberSubscansExponentScan[iChannel-1].c_str(), &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pChannelGainControlMethodScan[iChannel-1].c_str(), strHigh);

	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pAliasFilterFrequency3dBPointScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pAliasFilterSlopeScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pLowCutFilterFrequencyScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pLowCutFilterSlopeScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pFirstNotchFrequencyScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pSecondNotchFrequencyScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pThirdNotchFrequencyScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, pSegdFileStruct->m_oSegdSH.m_pExtendedChannelSetNumberScan[iChannel-1].c_str());

	ReadInitToWriteSegdNew_BCD_addHigh(pSegdFileStruct->m_oSegdSH.m_pExtendedHeaderFlagScan[iChannel-1].c_str(), &strHigh);
	ReadInitToWriteSegdNew_BCD_addLow(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pTraceHeaderExtensionsScan[iChannel-1].c_str(), strHigh);

	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pVerticalStackScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pStreamerCableNumberScan[iChannel-1].c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pArrayFormingScan[iChannel-1].c_str());
}

void ProcessExtendedHeaderBackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleTime == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_uiSampleTime = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pAcquisitionLengthExtended.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_uiSampleTime);
	}

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleRate == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_uiSampleRate = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSampleRateExtended.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_uiSampleRate);
	}


	if (pSegdFileStruct->m_iTotalTraceNum == 0)
	{
		pSegdFileStruct->m_iTotalTraceNum = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTotalNumberTracesExtended.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_iTotalTraceNum);
	}

	if (pSegdFileStruct->m_iAuxTraceNum == 0)
	{
		pSegdFileStruct->m_iAuxTraceNum = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberAuxesExtended.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_iAuxTraceNum);
	}

	if (pSegdFileStruct->m_iAcqTraceNum == 0)
	{
		pSegdFileStruct->m_iAcqTraceNum = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberSeisTracesExtended.c_str());
	} 
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_iAcqTraceNum);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberDeadSeisTracesExtended.c_str());


	if (pSegdFileStruct->m_iAcqTraceNum == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberLiveSeisTracesExtended.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_iAcqTraceNum);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTypeSourceExtended.c_str());


	if (pSegdFileStruct->m_oSegdSH.m_iSampleLength == 0)
	{
		pSegdFileStruct->m_oSegdSH.m_iSampleLength = ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberSamplesInTraceExtended.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_iSampleLength);
	}


	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pShotNumberExtended.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTBWindowExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTestRecordTypeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSpreadFirstLineExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSpreadFirstNumberExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSpreadNumberExtended.c_str());

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSpreadTypeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTimebreakExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pUpholeTimeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pBlasterIdExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pBlasterStatusExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pRefractionDelayExtended.c_str());

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTBtoT0TimeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pInternalTimeBreakExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pPrestackWithinFieldUnitsExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNoiseEliminationTypeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pLowTracePercentageExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pLowTraceValueExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNumberWindowsOrWindowLengthExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricEditingTypeOrOverlapExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNoisyTracePercentageExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricRangeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricTaperLengthExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pThresholdHoldOrNotExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricThresholdInitValueExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pHistoricZeroingLengthExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTypeProcessExtended.c_str());    //36*4=144
	ReadInitToWriteSegdNew_BIN(pFile, 128, pSegdFileStruct->m_oSegdSH.m_pAcquisitionTypeTablesExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 128, pSegdFileStruct->m_oSegdSH.m_pThresholdTypeTablesExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pStackingFoldExtended.c_str());
	ReadInitToWriteSegdNew_ASC(pFile, 80, pSegdFileStruct->m_oSegdSH.m_pNotUsed1Extended.c_str());

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleTime == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pRecordLengthExtended.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_uiSampleTime);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pAutocorrelationPeakTimeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNotUsed2Extended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pCorrelationPilotNoExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pPilotLengthExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSweepLengthExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pAcquisitionNumberExtended.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pMaxOfMaxAuxExtended.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pMaxOfMaxSeisExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pDumpStackingFoldExtended.c_str());
	ReadInitToWriteSegdNew_ASC(pFile, 16, pSegdFileStruct->m_oSegdSH.m_pTapeLabelExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTapeNumberExtended.c_str());
	ReadInitToWriteSegdNew_ASC(pFile, 16, pSegdFileStruct->m_oSegdSH.m_pSoftwareVersionExtended.c_str());
	ReadInitToWriteSegdNew_ASC(pFile, 12, pSegdFileStruct->m_oSegdSH.m_pDateExtended.c_str());
	ReadInitToWriteSegdNew_DOUBLE(pFile, 8, pSegdFileStruct->m_oSegdSH.m_pSourceEastingExtended.c_str());
	ReadInitToWriteSegdNew_DOUBLE(pFile, 8, pSegdFileStruct->m_oSegdSH.m_pSourceNorthingExtended.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSourceElevationExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSlipSweepModeUsedExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pFilesPerTapeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pFileCountExtended.c_str());
	ReadInitToWriteSegdNew_ASC(pFile, 160, pSegdFileStruct->m_oSegdSH.m_pAcquisitionErrorDescriptionExtended);
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pFilterTypeExtended.c_str());

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pStackDumpedExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pStackSignExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pPRMTiltCorrectionUsedExtended.c_str());
	ReadInitToWriteSegdNew_ASC(pFile, 64, pSegdFileStruct->m_oSegdSH.m_pSwathNameExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pOperatingModeExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pReserved1Extended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pNoLogExtended.c_str());

	if (pSegdFileStruct->m_oSegdSH.m_uiSampleTime == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pListeningTimeExtended.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_uiSampleTime);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pTypeDumpExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pReserved2Extended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSwathIdExtended.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, pSegdFileStruct->m_oSegdSH.m_pSeismicTraceOffsetRemovalDisabledExtended.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 8, pSegdFileStruct->m_oSegdSH.m_pGPSTimeAcquisitionTimeBreakExtended.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 8, pSegdFileStruct->m_oSegdSH.m_pAlignedGPSTimeAcquisitionExtended.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 132, pSegdFileStruct->m_oSegdSH.m_pNotUsed3Extended.c_str());
}

void ProcessExternalHeaderBackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{
	int iLenth = 0;
	int iLenthExternalHeader = ReadInitToWriteSegdNew_BCD(pFile, 1, pSegdFileStruct->m_oSegdSH.m_pExternalHeaderLengthGeneral1.c_str());
	iLenth = iLenthExternalHeader * 32;
	ReadInitToWriteSegdNew_ASC(pFile, iLenth, pSegdFileStruct->m_oSegdSH.m_pConcatenationOfExternal.c_str());
}

void ProcessTraceHeaderBackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_BCD(pFile, 2, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pFileNumberTrace.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pScanTypeNumberTrace.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelSetNumberTrace.c_str());

	if (iChannel == 0)
	{
		ReadInitToWriteSegdNew_BCD(pFile, 2, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceNumberTrace.c_str());
	}
	else
	{
		ReadParameterToSegd_BCD(pFile, 2, iChannel);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pFirstTimingWordTrace.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceHeaderExtensionTrace.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSampleSkewTrace.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceEditTrace.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTimeBreakWindowTrace.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedChannelSetNumberTrace.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedFileNumberTrace.c_str());
}

void ProcessTraceHeaderExtensionBlock1BackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct)//ichannel Ϊ��ţ�1-98
{

	ReadParameterToSegd_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_iLineIndex);

	if (iChannel == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointNumberTrace1.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_iPointIndex);
	}

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointIndexTrace1.c_str());

	if (pSegdFileStruct->m_oSegdSH.m_iSampleLength == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNumberSamplesPerTraceTrace1.c_str());
	} 
	else
	{
		ReadParameterToSegd_BIN(pFile, 3, pSegdFileStruct->m_oSegdSH.m_iSampleLength);
	}

	ReadInitToWriteSegdNew_BCD(pFile, 5, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedReceiverLineNumberTrace1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 5, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedReceiverPointNumberTrace1.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSensorSEGDCodeTrace1.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 11, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace1.c_str());
}

void ProcessTraceHeaderExtensionBlock2BackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_DOUBLE(pFile, 8, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointEastingTrace2.c_str());
	ReadInitToWriteSegdNew_DOUBLE(pFile, 8, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointNorthingTrace2.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pReceiverPointElevationTrace2.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSensorTypeNumberTrace2.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace2.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pDSDIdentificationNoTrace2.c_str());

	if (iChannel == 0)
	{
		ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pExtendedTraceNoTrace2.c_str());
	}
	else
	{
		ReadParameterToSegd_BIN(pFile, 4, iChannel);
	}

}

void ProcessTraceHeaderExtensionBlock3BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pResistanceLowLimitTrace3.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pResistanceHighLimitTrace3.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pResistanceResistanceValueTrace3.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTiltLimitTrace3.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTiltValueTrace3.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pResistanceErrorTrace3.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTiltErrorTrace3.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 10, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace3.c_str());
}

void ProcessTraceHeaderExtensionBlock4BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCapacitanceLowLimitTrace4.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCapacitanceHighLimitTrace4.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCapacitanceValueTrace4.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCutOffLowLimitTrace4.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCutOffHighLimitsTrace4.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCutOffValueTrace4.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCapacitanceErrorTrace4.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pCutOffErrorTrace4.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 6, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace4.c_str());
}

void ProcessTraceHeaderExtensionBlock5BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pLeakageLimitTrace5.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pLeakageValueTrace5.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 16, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsed1Trace5.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pLeakageErrorTrace5.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 7, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsed2Trace5.c_str());

}

void ProcessTraceHeaderExtensionBlock6BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pUnitTypeTrace6.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pUnitSerialNumberTrace6.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelNumberTrace6.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSpare1Trace6.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pAssemblyTypeTrace6.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pFDUorDSUAssemblySerialNumberTrace6.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pLocationInFDUorDSUAssemblyTrace6.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSpare2Trace6.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSubunitTypeTrace6.c_str());

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelTypeTrace6.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 2, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSpare3Trace6.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSensorSensitivityTrace6.c_str());
	ReadInitToWriteSegdNew_BCD(pFile, 8, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNotUsedTrace6.c_str());

}

void ProcessTraceHeaderExtensionBlock7BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct)
{

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pControlUnitTypeTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 3, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pControlUnitSerialNumberTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelGainScaleTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelFilterTrace7.c_str());

	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelDataErrorTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelEditedStatusTrace7.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelSampleTomVConversionFactorTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNumberOfStacksNoisyTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNumberOfStacksLowTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelTypeIdTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 1, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pChannelProcessTrace7.c_str());
	ReadInitToWriteSegdNew_FLOAT(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceMaxValueTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pTraceMaxTimeTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pNumberInterpolationsTrace7.c_str());
	ReadInitToWriteSegdNew_BIN(pFile, 4, (*pSegdFileStruct->m_pSegdDHList->begin())->m_oSegdTH.m_pSeismicTraceOffsetValueTrace7.c_str());

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

int ReadInitToWriteSegdNew_BCD(FILE* pFile, int iCountByte, const char* pParameter)
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

int ReadInitToWriteSegdNew_BIN(FILE* pFile, int iCountByte, const char* pParameter)
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

void ReadInitToWriteSegdNew_BCD_addLow(FILE* pFile, int iCountByte, const char* pParameter, string strHigh)
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

void ReadInitToWriteSegdNew_BCD_addHigh(const char* pParameter, string* pstr)
{
	(*pstr).assign(pParameter, strlen(pParameter));
}

void ReadInitToWriteSegdNew_FLOAT(FILE* pFile, int iCountByte, const char* pParameter)
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

void ReadInitToWriteSegdNew_DOUBLE(FILE* pFile, int iCountByte, const char* pParameter)
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

void ReadInitToWriteSegdNew_ASC(FILE* pFile, int iCountByte, const char* pParameter)
{
	int iResultNew = 0;
	CString strTemp = _T("");
	char* pBuf = NULL;
	if (iCountByte > 0)
	{
		iResultNew = fseek(pFile, 0, SEEK_CUR);
		pBuf = new char[iCountByte];
		memset(pBuf, 0, iCountByte);
		memcpy(pBuf, pParameter, strlen(pParameter));
		fwrite(pBuf, sizeof(char), iCountByte, pFile);
		delete[] pBuf;
		pBuf = NULL;
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