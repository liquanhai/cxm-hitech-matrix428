#include "StdAfx.h"
#include "ChannelSetupData.h"

CChannelSetupData::CChannelSetupData(void)
{
}

CChannelSetupData::~CChannelSetupData(void)
{
}

// ���ݲ��ߺš����š�����ţ�����IP��ַ
unsigned int CChannelSetupData::CreateIP(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel)
{
	// IP��ַ
	return  uiNbLine * 1000000 + uiNbPoint * 10 + uiNbChannel;
}