#pragma once

#include "FrameInterface.h"

// CSocketInterfaceDataRev ����Ŀ��

class CSocketInterfaceDataRev : public CSocket
{
public:
	CSocketInterfaceDataRev();
	virtual ~CSocketInterfaceDataRev();
	virtual void OnReceive(int nErrorCode);

public: // ����

	// ���ڲ�ͨѶ�ı���IP��ַ
	CString m_strIPForInterface;
	// ��������֡���յĶ˿ں�
	UINT m_uiPortForDataReceive;
	// �ͻ�����ԴIP��ַ
	CString m_strIPSource;
	// �ͻ�����ԴIP�˿ں�
	UINT m_uiPortSource;

	// ֡�ֽ���
	int m_iFrameSize;
	// ����֡���ݶ���
	CFrameInterface m_oFrameInterface;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInterface, UINT uiPortForDataReceive);
	// ���ý��ջ�������С
	BOOL SetBufferSize(int iBufferSize);
};


