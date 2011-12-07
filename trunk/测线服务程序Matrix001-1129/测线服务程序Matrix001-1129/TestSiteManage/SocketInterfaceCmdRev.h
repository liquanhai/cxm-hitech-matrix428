#pragma once

#include "NetProcInterface.h"
#include "FrameInterface.h"

class CNetProcInterface;

/**
*@brief ������������֡��������ӿ���
*/
class CSocketInterfaceCmdRev : public CSocket
{
public:
	CSocketInterfaceCmdRev();
	virtual ~CSocketInterfaceCmdRev();
	virtual void OnReceive(int nErrorCode);

public: // ����

	/** ���ڲ�ͨѶ�ı���IP��ַ*/
	CString m_strIPForInterface;
	/** ��������֡���յĶ˿ں�*/
	UINT m_uiPortForCommandReceive;
	/** �ͻ�����ԴIP��ַ*/
	CString m_strIPSource;
	/** �ͻ�����ԴIP�˿ں�*/
	UINT m_uiPortSource;
	/** �ͻ���Ŀ��IP��ַ*/
	CString m_strIPAim;
	/** �ͻ���Ŀ��IP�˿ں�*/
	UINT m_uiPortAim;

	/** ֡�ֽ���*/
	int m_iFrameSize;
	/** ����֡���ݶ���*/
	CFrameInterface m_oFrameInterface;
	/** Ӧ��֡���ݶ���*/
	CFrameInterface m_oFrameReply;

	/** �յ�����֡��֡����������󳤶�*/
	int m_iFrameCountListLengthMaxReceive;
	/** �յ�����֡��֡��������*/
	CList<UINT, UINT> m_oFrameCountListReceive;
	/** �յ�����֡��֡����������*/
	CMap<UINT, UINT, UINT, UINT> m_oFrameCountMapReceive;

	/** �ڲ�����������մ������ָ��*/
	CNetProcInterface* m_pNetProcInterface;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInterface, UINT uiPortForCommandReceive);
	// ���ý��ջ�������С
	BOOL SetBufferSize(int iBufferSize);
	// ���ͻ���֡
	void SendReplyFrame();
	// ����Ƿ����ظ����յ�������֡
	bool CheckIfRepeatFrameCommand();
};


