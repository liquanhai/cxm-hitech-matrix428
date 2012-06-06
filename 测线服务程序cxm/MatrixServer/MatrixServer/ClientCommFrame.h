#pragma once
#include "CommProtocol.h"
#include <list>
using std::list;
/**
* @brief ��ͻ���ͨѶ֡����
*/
class CClientCommFrame
{
public:
	CClientCommFrame(void);
	virtual ~CClientCommFrame(void);
public:
	/** ���е�֡�ṹ����*/
	unsigned int m_uiCountFree;
	/** ֡�ṹ������*/
	m_oCommFrameStruct m_oCommFrameArray[FrameStructNumMax];
	/** ������Դͬ������*/
	CRITICAL_SECTION m_oSecClientFrame;
	/** ����֡�ṹ�����*/
	list<m_oCommFrameStructPtr> m_olsCommFrameFree;
	/** �ȴ�����֡�ṹ��*/
	list<m_oCommFrameStructPtr> m_olsCommWorkFrame;
	/** ������ˮ��*/
	unsigned int m_uiPacketIndex;
	/** ������ˮ��*/
	unsigned int m_uiCmdIndex;
	/** ���ݴ�������*/
	char m_cProcBuf[ProcBufferSize];
public:
	/** ���ý���֡�ṹ��*/
	void OnResetFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	/** ��ʼ��*/
	void OnInit(void);
	/** �ر�*/
	void OnClose(void);
	/** �õ�һ�����н���֡�ṹ��*/
	m_oCommFrameStructPtr GetFreeFrameStruct(void);
	/** ����һ�����н���֡�ṹ��*/
	void AddFreeFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	/** �������ݴ�������*/
	void OnResetProcBuf(void);
};

