#pragma once

#include "FrameIPSet.h"
#include "Instrument.h"

/**
*@brief ����IP��ַ����֡���ͽ�������ӿ���
*/
class CSocketIPSetFrame : public CSocket
{
public:
	CSocketIPSetFrame();
	virtual ~CSocketIPSetFrame();

public: // ����
	/** LCI�豸IP��ַ*/
	CString m_strIPLCI;
	/**  LCI�豸IP��ַ�˿ں�*/
	UINT m_uiPortLCI;

	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	UINT m_uiIPForInstrument;
	/** ��������IP��ַ���õĶ˿ں�*/
	UINT m_uiPortForIPSet;

	/** ����IP����֡���ݶ���*/
	CFrameIPSet m_oFrameIPSet;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInstrument, UINT uiIPForInstrument, UINT uiPortForIPSet, CString strIPLCI, UINT uiPortLCI);
	// �õ�������ջ������յ���֡����
	DWORD GetFrameCount();
	// ���û����������շ��İ�֡����
	BOOL SetBufferSize(int iFrameCount);
	// �õ�֡����
	BOOL GetFrameData();
	// ��������IP��ַ����֡
	void SendIPSetFrame();
	// ��������IP��ַ����֡
	void MakeFrameData(CInstrument* pInstrument, unsigned short usCommand);
};


