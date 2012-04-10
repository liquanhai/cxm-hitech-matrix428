#pragma once
#include "CommProtocol.h"
#include <list>
using std::list;
// ������֡�ṹ����
#define RecFrameStructNumMax		5800
class CClientRecFrame
{
public:
	CClientRecFrame(void);
	~CClientRecFrame(void);
public:
	// ���еĽ���֡�ṹ����
	unsigned int m_uiCountFree;
	// ����֡�ṹ������
	m_oCommFrameStruct m_oCommFrameArray[RecFrameStructNumMax];
	// ������Դͬ������
	CRITICAL_SECTION m_oSecClientRecFrame;
	// ���еĽ���֡�ṹ�����
	list<m_oCommFrameStructPtr> m_olsCommFrameStructFree;
	// �ȴ�����֡�ṹ��
	list<m_oCommFrameStructPtr> m_olsCommRecFrame;
public:
	// ����֡
	void PhraseFrame(char* cpFrame, unsigned short usSize);
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

