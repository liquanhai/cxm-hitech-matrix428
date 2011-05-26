#pragma once

#include "FrameInterface.h"

// CSocketInterfaceCmdSend ����Ŀ��

class CSocketInterfaceCmdSend : public CSocket
{
public:
	CSocketInterfaceCmdSend();
	virtual ~CSocketInterfaceCmdSend();
	virtual void OnReceive(int nErrorCode);

public: // ����

	// ���ڲ�ͨѶ�ı���IP��ַ
	CString m_strIPForInterface;
	// ��������֡�Ķ˿ں�
	UINT m_uiPortForCommandSend;
	// �ͻ���Ŀ��IP��ַ
	CString m_strIPAim;
	// �ͻ���Ŀ��IP�˿ں�
	UINT m_uiPortAim;

	// ֡�ֽ���
	int m_iFrameSize;
	// ����֡���ݶ���
	CFrameInterface m_oFrameInterface;
	// Ӧ��֡���ݶ���
	CFrameInterface m_oFrameReply;

	// �յ�Ӧ��֡��֡����������󳤶�
	int m_iFrameCountListLengthMaxReply;
	// �յ�Ӧ��֡��֡��������
	CList<UINT, UINT> m_oFrameCountListReply;
	// �յ�Ӧ��֡��֡����������
	CMap<UINT, UINT, UINT, UINT> m_oFrameCountMapReply;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInterface, UINT uiPortForCommandSend, UINT uiPortAim);
	// ���û�������С
	BOOL SetBufferSize(int iBufferSize);
	// ��������֡
	void SendCommandFrame();
	// �����յ���Ӧ��֡
	void SaveReplyFrame();
};


