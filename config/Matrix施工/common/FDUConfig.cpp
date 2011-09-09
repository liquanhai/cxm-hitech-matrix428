#include "stdafx.h"
#include "FDUConfig.h"

CFDUConfig::CFDUConfig(void)
: m_dwGain3301Index(0)
, m_dwMux3301Index(0)
, m_dwMode5373Index(0)
, m_dwAttr5373Index(0)
, m_dwSampleRateIndex(0)
, m_dwFilterIIRIndex(0)	
, m_dwFilterFIRIndex(0)
, m_strCrewName(_T(""))
{
	InitFUDConfig();
}

CFDUConfig::~CFDUConfig(void)
{
}
/**
 * @brief ��ʼ�����ò�������ȡֵ
 * @note  ����Ӳ����Ƶ�Ҫ�󣬶���ز�������������ֵ���г�ʼ����
 * @param void
 * @return void
 */
void CFDUConfig::InitFUDConfig()
{
	int i;
	////��ʼ��ad��ز�����////////////////////////////
	for(i=0; i<7; i++)
		set_3301_gain[i]=i;

	for(i=0; i<4; i++)
		set_3301_mux[i]=i<<3;

	for(i=0; i<8; i++)
		set_5373_mode[i]=i;

	for(i=0; i<8; i++)
		set_5373_att[i]=i<<3;

	ad_rate[0] =0x1000;
	ad_rate[1] =0x3000;
	ad_rate[2] =0x7000;
	ad_rate[3] =0xf000;
	ad_rate[4] =0x7080;
	ad_rate[5] =0xf040;
	ad_rate[6] =0x3240;
	ad_rate[7] =0xf140;
	ad_rate[8] =0x3540;
	ad_rate[9] =0x7540;
	ad_rate[10]=0x3640;
	ad_rate[11]=0xf540;
	ad_rate[12]=0x3d40;
	ad_rate[13]=0x7d40;
	ad_rate[14]=0xfd40;
	
	m_dwSampleRates[0]=250;		// 4k
	m_dwSampleRates[1]=500;		// 2k
	m_dwSampleRates[2]=1000;	// 1k
	m_dwSampleRates[3]=2000;	// 500
	m_dwSampleRates[4]=3000;	// 333
	m_dwSampleRates[5]=4000;	// 250
	m_dwSampleRates[6]=5000;	// 200
	m_dwSampleRates[7]=8000;	// 125
	m_dwSampleRates[8]=10000;	// 100
	m_dwSampleRates[9]=20000;	// 50
	m_dwSampleRates[10]=25000;	// 40
	m_dwSampleRates[11]=40000;	// 25
	m_dwSampleRates[12]=50000;	// 20
	m_dwSampleRates[13]=100000;	// 10
	m_dwSampleRates[14]=200000;	// 5

	filter_fir[0]=0x00;
	filter_fir[1]=0xa<<2;
	filter_fir[2]=0x5<<2;

	for(i=0; i<16; i++)
		filter_iir_low[i]=0x00;

	filter_iir_low[1] =0x03;
	filter_iir_low[11]=0x03;

	filter_iir_high[0] =0x00000000;

	filter_iir_high[1] =0x00000000;
	filter_iir_high[2] =0xc0000000;
	filter_iir_high[3] =0x30000000;
	filter_iir_high[4] =0x0c000000;
	filter_iir_high[5] =0x03000000;

	filter_iir_high[6] =0x00c00000;
	filter_iir_high[7] =0x00300000;
	filter_iir_high[8] =0x000c0000;
	filter_iir_high[9] =0x00030000;
	filter_iir_high[10]=0x0000c000;

	filter_iir_high[11]=0x00c00000;
	filter_iir_high[12]=0xc0300000;
	filter_iir_high[13]=0x300c0000;
	filter_iir_high[14]=0x0c030000;
	filter_iir_high[15]=0x0300c000;
}
/**
 * @brief ����Ӳ�����������
 * @note  ͨ���Ŵ�����ȡֵ�����㲻ͬ�Ŵ�����������룬�ô�����ײ�Ӳ����ء�
 Ŀǰ֧��7���Ŵ�����������뱣����set_3301_gain�����С�
 * @param  int nMultipleValue���Ŵ���
 * @return ����������롣
 */
unsigned char CFDUConfig::GetGainCode(int nMultipleValue)
{
	unsigned char byGain=0;
	switch(nMultipleValue)
	{
	case 1:
		byGain=set_3301_gain[0];
		break;
	case 2:
		byGain=set_3301_gain[1];
		break;
	case 4:
		byGain=set_3301_gain[2];
		break;
	case 8:
		byGain=set_3301_gain[3];
		break;
	case 16:
		byGain=set_3301_gain[4];
		break;
	case 32:
		byGain=set_3301_gain[5];
		break;
	case 64:
		byGain=set_3301_gain[6];
		break;	
	default:
		byGain=set_3301_gain[0];
		break;
	}
	return byGain;
}