#include "StdAfx.h"
#include "IPList.h"

CIPList::CIPList()
{
}

CIPList::~CIPList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CIPList::OnInit()
{
	// ����IP��ַ����
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// IP��ַ���ڿ���IP��ַ����β��
		m_olsIPFree.AddTail( i + 2000000000 + 200);
	}
}

/**
* �ر�
* @param void
* @return void
*/
void CIPList::OnClose()
{
	// ��տ���IP��ַ����
	m_olsIPFree.RemoveAll();
}

/**
* ����
* @param void
* @return void
*/
void CIPList::OnReset()
{
	// ��տ���IP��ַ����
	m_olsIPFree.RemoveAll();
	// ����IP��ַ����
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// IP��ַ���ڿ���IP��ַ����β��
		m_olsIPFree.AddTail( i + 2000000000 + 200);
	}
}

/**
* �õ�һ����������IP��ַ
* @param void
* @return unsigned int ����IP��ַ 0��û�п���IP��ַ
*/
unsigned int CIPList::GetFreeInstrumentIP()
{
	unsigned int uiIP = 0;

	if(m_uiCountFree > 0)	//�п�������
	{
		uiIP = m_olsIPFree.RemoveHead();
		m_uiCountFree--;
	}

	return uiIP;
}

/**
* ����һ����������
* @param unsigned int uiIP IP��ַ
* @return void
*/
void CIPList::AddFreeInstrumentIP(unsigned int uiIP)
{
	//������ж���
	m_olsIPFree.AddTail(uiIP);
	m_uiCountFree++;
}

/**
* �õ�һ�����н���վIP��ַ
* @param void
* @return unsigned int ����IP��ַ 0��û�п���IP��ַ
*/
unsigned int CIPList::GetFreeCrossIP()
{
	unsigned int uiIP = 0;

	if(m_uiCountFree > 0)	//�п�������
	{
		uiIP = m_olsIPFree.RemoveHead();
		m_uiCountFree--;
	}

	return uiIP;
}

/**
* ����һ�����н���վIP��ַ
* @param unsigned int uiIP IP��ַ
* @return void
*/
void CIPList::AddFreeCrossIP(unsigned int uiIP)
{
	//������ж���
	m_olsIPFree.AddTail(uiIP);
	m_uiCountFree++;
}

/**
* �õ�һ�����е�ԴվIP��ַ
* @param void
* @return unsigned int ����IP��ַ 0��û�п���IP��ַ
*/
unsigned int CIPList::GetFreePowerIP()
{
	unsigned int uiIP = 0;

	if(m_uiCountFree > 0)	//�п�������
	{
		uiIP = m_olsIPFree.RemoveHead();
		m_uiCountFree--;
	}

	return uiIP;
}

/**
* ����һ�����е�ԴվIP��ַ
* @param unsigned int uiIP IP��ַ
* @return void
*/
void CIPList::AddFreePowerIP(unsigned int uiIP)
{
	//������ж���
	m_olsIPFree.AddTail(uiIP);
	m_uiCountFree++;
}

/**
* �õ�һ�������ػص�IP��ַ
* @param void
* @return unsigned int ����IP��ַ 0��û�п���IP��ַ
*/
unsigned int CIPList::GetDetourIP()
{
	unsigned int uiIP = 0;

	if(m_uiCountFree > 0)	//�п�������
	{
		uiIP = m_olsIPFree.RemoveHead();
		m_uiCountFree--;
	}

	return uiIP;
}

/**
* ����һ�������ػص�IP��ַ
* @param unsigned int uiIP IP��ַ
* @return void
*/
void CIPList::AddDetourIP(unsigned int uiIP)
{
	//������ж���
	m_olsIPFree.AddTail(uiIP);
	m_uiCountFree++;
}

/**
* �õ�һ���ɼ�վIP��ַ
* @param unsigned int uiLineNb ���ߺ�
* @param unsigned int uiPointNb ����
* @param unsigned int uiChannelNb �����
* @return unsigned int IP��ַ
*/
unsigned int CIPList::GetCollectIP(unsigned int uiLineNb, unsigned int uiPointNb, unsigned int uiChannelNb)
{
	//�����С��10������С��100000�����ߺ�С��2000
	return uiChannelNb + uiPointNb * 10 + uiLineNb * 1000000;
}

/**
* �õ�һ����ը��IP��ַ
* @param unsigned int uiNb ��ʶ��
* @return unsigned int IP��ַ
*/
unsigned int CIPList::GetBlastMachineIP(unsigned int uiNb)
{
	//20�� + ��ը����
	return uiNb + 2000000000;
}

/**
* �õ�һ��������IP��ַ
* @param unsigned int uiNb ��ʶ��
* @return unsigned int IP��ַ
*/
unsigned int CIPList::GetAuxIP(unsigned int uiNb)
{
	//20�� + 100 + ��������
	return uiNb + 2000000000 + 100;
}

/**
* �ַ���ת��Ϊ�޷�������
* @param CString strData �ַ���
* @return unsigned int �޷�������
*/
unsigned int CIPList::ConvertStringToUnsignedInt(CString strData)
{
	COleVariant oVariant = strData;
	oVariant.ChangeType(VT_UINT);
	unsigned int uiData = oVariant.uintVal;
	return uiData;
}

/**
* ����IP��ַת��Ϊ�ַ���IP��ַ
* @param UINT uiIP ����IP��ַ
* @return CString �ַ���IP��ַ
*/
CString CIPList::IPToString(UINT uiIP)
{
	CString strIP;
	UINT uiPart1, uiPart2, uiPart3, uiPart4;
	UINT uiRemain;
	strIP = "";
	uiPart1 = uiIP / 0x1000000;
	uiRemain = uiIP % 0x1000000;

	uiPart2 = uiRemain / 0x10000;
	uiRemain = uiRemain % 0x10000;;

	uiPart3 = uiRemain / 0x100;
	uiRemain = uiRemain % 0x100;

	uiPart4 = uiRemain;

	strIP.Format(("%d.%d.%d.%d"), uiPart4, uiPart3, uiPart2, uiPart1);
	return strIP;
}

/**
* �ַ���IP��ַת��Ϊ����IP��ַ
* @param CString strIP �ַ���IP��ַ
* @return UINT ����IP��ַ
*/
UINT CIPList::StringToIP(CString strIP)
{
	return inet_addr(strIP);
}

/**
* �õ�����IP��ַ������	1-�̶�IP��ַ��2-����IP��ַ
* @param unsigned int uiIP IP��ַ
* @return int IP��ַ������	1-�̶�IP��ַ��2-����IP��ַ
*/
int CIPList::GetInstrumentIPType(unsigned int uiIP)
{
	int iType = 1;
	if(uiIP >= 2000000200)
	{
		iType = 2;
	}
	return iType;
}