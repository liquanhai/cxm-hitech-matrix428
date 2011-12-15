#pragma once

#include "FrameHead.h"
#include "..\\parameter\\Parameter.h"
/**
*@brief �����װ�֡��������ӿ���
*/
class CSocketHeadFrame : public CSocket
{
public:
	CSocketHeadFrame();
	virtual ~CSocketHeadFrame();

public: // ����
	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** ���ն˿ں�*/
	UINT m_uiPortForHeadFrame;
	/** �װ����ݶ���*/
	CFrameHead m_oFrameHead;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInstrument, UINT uiPortForHeadFrame);
	// �õ�������ջ������յ���֡����
	DWORD GetFrameCount();
	// ���ý��ջ��������Խ��յ�֡����
	BOOL SetBufferSize(int iFrameCount);
	// �õ�֡����
	BOOL GetFrameData();
};


