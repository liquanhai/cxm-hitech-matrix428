// SocketInterfaceDataSend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "SocketInterfaceDataSend.h"


// CSocketInterfaceDataSend

CSocketInterfaceDataSend::CSocketInterfaceDataSend()
{
	// �ͻ���Ŀ��IP��ַ
	m_strIPAim = "255.255.255.255";
}

CSocketInterfaceDataSend::~CSocketInterfaceDataSend()
{
}

/**
* ��ʼ��
* @param CString strIPForInterface ��ԴIP��ַ
* @param UINT uiPortForCommandSend ��Դ�˿ں�
* @param UINT uiPortAim ���޶˿ں�
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketInterfaceDataSend::OnInit(CString strIPForInterface, UINT uiPortForCommandSend, UINT uiPortAim)
{
	BOOL bReturn = false;

	// ���ڲ�ͨѶ�ı���IP��ַ
	m_strIPForInterface = strIPForInterface;
	// ��������֡�Ķ˿ں�
	m_uiPortForCommandSend = uiPortForCommandSend;
	// �ͻ���Ŀ��IP�˿ں�
	m_uiPortAim = uiPortAim;
	// ��������˿�
	bReturn = Create(m_uiPortForCommandSend, SOCK_DGRAM, m_strIPForInterface);

	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

	return bReturn;	
}

/**
* ���÷��ͻ�������С
* @param int iBufferSize ��������С
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketInterfaceDataSend::SetBufferSize(int iBufferSize)
{
	BOOL bReturn = false;

	int iOptionValue = iBufferSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}

/**
* ��������֡
* @param void
* @return void
*/
int CSocketInterfaceDataSend::SendDataFrame()
{
	int iCount = SendTo(m_oFrameInterface.m_pFrameData, m_oFrameInterface.m_usFrameSize, m_uiPortAim, m_strIPAim);
	//TRACE1("���Խ��֡���ͣ�֡��С%d\r\n", iCount);
	return iCount;
}

/**
* ���ɲ�������֡
* @param unsigned int uiTestType ��������
* @param unsigned unsigned int uiDataSize ÿ����������ռ���ֽ���
* @paramunsigned short usDataCount �������ݸ���
* @paramunsigned byte pData ��������
* @return void
*/
void CSocketInterfaceDataSend::CreateOutputDataFrameTest(unsigned int uiTestType, unsigned int uiDataSize, unsigned short usDataCount, byte* pData)
{
	m_oFrameInterface.CreateOutputDataFrameTest(uiTestType, uiDataSize, usDataCount, pData);
}