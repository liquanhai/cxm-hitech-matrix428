#pragma once
#include "CommProtocol.h"
#include <list>
using std::list;
class CClientFrame
{
public:
	CClientFrame(void);
	~CClientFrame(void);
public:
	// ���еĽ���֡�ṹ����
	unsigned int m_uiCountFree;
	// ����֡�ṹ������
	m_oCommFrameStruct m_oCommFrameArray[FrameStructNumMax];
	// ������Դͬ������
	CRITICAL_SECTION m_oSecClientFrame;
	// ���еĽ���֡�ṹ�����
	list<m_oCommFrameStructPtr> m_olsCommFrameFree;
	// �ȴ�����֡�ṹ��
	list<m_oCommFrameStructPtr> m_olsCommWorkFrame;
public:
	// ���ý���֡�ṹ��
	void OnResetRecFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose(void);
	// �õ�һ�����н���֡�ṹ��
	m_oCommFrameStructPtr GetFreeRecFrameStruct(void);
	// ����һ�����н���֡�ṹ��
	void AddFreeRecFrameStruct(m_oCommFrameStructPtr pFrameStruct);
};

