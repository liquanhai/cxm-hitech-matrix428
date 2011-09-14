#pragma once

#include "FrameTailTime.h"
#include "Instrument.h"

/**
*@brief ����β��ʱ�̲�ѯ֡���ͽ�������ӿ���
*/

class CSocketTailTimeFrame : public CSocket
{
public:
	CSocketTailTimeFrame();
	virtual ~CSocketTailTimeFrame();
public: // ����
	/** LCI�豸IP��ַ*/
	CString m_strIPLCI;
	/**  LCI�豸IP��ַ�˿ں�*/
	UINT m_uiPortLCI;

	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	UINT m_uiIPForInstrument;
	/** ��������β��ʱ�̲�ѯ�Ķ˿ں�*/
	UINT m_uiPortForTailTime;

	/** ֡�ֽ���*/
	int m_iFrameSize;
	/** ����β��ʱ�̲�ѯ֡���ݶ���*/
	CFrameTailTime m_oFrameTailTime;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInstrument, UINT uiIPForInstrument, UINT uiPortForTailTime, CString strIPLCI, UINT uiPortLCI);
	// �õ�������ջ������յ���֡����
	DWORD GetFrameCount();
	// ���ý��ջ��������Խ��յ�֡����
	BOOL SetBufferSize(int iFrameCount);
	// �õ�֡����
	BOOL GetFrameData();
	// ��������β��ʱ�̲�ѯ֡
	void SendTailTimeFrame();
	// ��������β��ʱ�̲�ѯ֡
	void MakeFrameData(CInstrument* pInstrument);
	// ����������ջ�����
	void RemoveFrameDataAll();
};


