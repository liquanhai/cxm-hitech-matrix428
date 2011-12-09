#pragma once

#include "FrameHeartBeat.h"

/**
*@brief ��������֡��������ӿ���
*/
class CSocketHeartBeatFrame : public CSocket
{
public:
	CSocketHeartBeatFrame();
	virtual ~CSocketHeartBeatFrame();

public: // ����
	/** LCI�豸IP��ַ*/
	CString m_strIPLCI;
	/**  LCI�豸IP��ַ�˿ں�*/
	UINT m_uiPortLCI;

	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** ��������֡���͵Ķ˿ں�*/
	UINT m_uiPortForHeartBeat;

	/** ����֡���ݶ���*/
	CFrameHeartBeat m_oFrameHeartBeat;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInstrument, UINT uiPortForHeartBeat, CString strIPLCI, UINT uiPortLCI);
	// ��������֡
	void SendIHeartBeatFrame();

};


