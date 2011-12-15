#pragma once

#include "frametail.h"

/**
*@brief ����β��֡��������ӿ���
*/
class CSocketTailFrame : public CSocket
{
public:
	CSocketTailFrame();
	virtual ~CSocketTailFrame();

public: // ����
	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** ����β�����յĶ˿ں�*/
	UINT m_uiPortForTailFrame;
	/** ����β��ת���Ķ˿ں�*/
	UINT m_uiPortForTailFrameSend;

	/** β�����ݶ���*/
	CFrameTail m_oFrameTail;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInstrument, UINT uiPortForTailFrame, UINT uiPortForTailFrameSend);
	// �õ�������ջ������յ���֡����
	DWORD GetFrameCount();
	// ���ý��ջ��������Խ��յ�֡����
	BOOL SetBufferSize(int iFrameCount);
	// �õ�֡����
	BOOL GetFrameData();
};


