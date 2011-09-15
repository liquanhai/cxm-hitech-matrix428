#include "stdafx.h"
#include "LineStruct.h"

CIPList::CIPList()
{

}

CIPList::~CIPList()
{

}

// �õ�һ���ɼ�վIP��ַ
unsigned int CIPList::GetCollectIP(unsigned int uiLineNb, unsigned int uiPointNb, unsigned int uiChannelNb)
{
	//�����С�ڣ�����С�ڣ����ߺ�С��
	return uiChannelNb + uiPointNb * 10 + uiLineNb * 1000000;
}

// �õ�һ����ը��IP��ַ
unsigned int CIPList::GetBlastMachineIP(unsigned int uiNb)
{
	//20��+ ��ը����
	return uiNb + 2000000000;
}

// �õ�һ��������IP��ַ
unsigned int CIPList::GetAuxIP(unsigned int uiNb)
{
	//20��+ 100 + ��������
	return uiNb + 2000000000 + 100;
}
// �õ���ǰ������һ��IP��ַ
DWORD CIPList::GetLocalIP()
{
    char szhn[256]; 
	int nStatus = gethostname(szhn, sizeof(szhn));
    if (nStatus == SOCKET_ERROR ) 
	{
		return false; 
	}
	
	struct addrinfo aiHints;
	struct addrinfo *aiList = NULL;

	memset(&aiHints, 0, sizeof(aiHints));
	aiHints.ai_family = AF_INET;
	if ((getaddrinfo(szhn, NULL, &aiHints, &aiList)) != 0) 
	{
		return 0;
	}

	sockaddr_in *pAddr = (sockaddr_in*)(aiList->ai_addr);
	do 
	{
		if(pAddr->sin_addr.S_un.S_addr == 0x0100007f)
		{
			aiList = aiList->ai_next;
			pAddr = (sockaddr_in*)(aiList->ai_addr);
		}
		else
		{
			return pAddr->sin_addr.S_un.S_addr;
		}
	} while (pAddr!=NULL);
	
	return  0;

}