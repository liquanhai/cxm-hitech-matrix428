#pragma once

#include "FrameTimeSet.h"
#include "Instrument.h"

/**
*@brief ����ʱ������֡��������ӿ���
*/
class CSocketTimeSetFrame : public CSocket
{
public:
	CSocketTimeSetFrame();
	virtual ~CSocketTimeSetFrame();

public: // ����
	/** LCI�豸IP��ַ*/
	CString m_strIPLCI;
	/**  LCI�豸IP��ַ�˿ں�*/
	UINT m_uiPortLCI;

	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	UINT m_uiIPForInstrument;
	/** ��������ʱ�����õĶ˿ں�*/
	UINT m_uiPortForTimeSet;

	// ֡�ֽ���*/
	int m_iFrameSize;
	// ����ʱ������֡���ݶ���*/
	CFrameTimeSet m_oFrameTimeSet;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInstrument, UINT uiIPForInstrument, UINT uiPortForTimeSet, CString strIPLCI, UINT uiPortLCI);
	// ���÷��ͻ��������Է��͵�֡����
	BOOL SetBufferSize(int iFrameCount);
	// ��������ʱ���ַ����֡
	void SendTimeSetFrame();
	// ��������ʱ���ַ����֡
	void MakeFrameData(CInstrument* pInstrument);
};


