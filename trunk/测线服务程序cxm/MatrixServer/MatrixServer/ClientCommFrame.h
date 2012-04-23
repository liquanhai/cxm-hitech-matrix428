#pragma once
#include "CommProtocol.h"
#include <list>
#include <map>
using std::list;
using std::map;
class CClientCommFrame
{
public:
	CClientCommFrame(void);
	~CClientCommFrame(void);
public:
	// ���е�֡�ṹ����
	unsigned int m_uiCountFree;
	// ֡�ṹ������
	m_oCommFrameStruct m_oCommFrameArray[FrameStructNumMax];
	// ������Դͬ������
	CRITICAL_SECTION m_oSecClientFrame;
	// ����֡�ṹ�����
	list<m_oCommFrameStructPtr> m_olsCommFrameFree;
	// �ȴ�����֡�ṹ��
	list<m_oCommFrameStructPtr> m_olsCommWorkFrame;
	// ������ˮ��
	unsigned int m_uiPacketIndex;
	// ������ˮ��
	unsigned int m_uiCmdIndex;
	// �ѷ���֡�����ؼ���
	typedef struct SndFrameKey
	{
		SndFrameKey(unsigned short usCmd, unsigned int uiTimeStep, unsigned int uiPacketIndex)
		{
			this->m_usCmd = usCmd;
			this->m_uiServerTimeStep = uiTimeStep;
			this->m_uiPacketIndex = uiPacketIndex;
		}
		~SndFrameKey()
		{
		}
		bool operator < (const SndFrameKey& rhs) const
		{
			if (m_usCmd == rhs.m_usCmd)
			{
				if (m_uiServerTimeStep == rhs.m_uiServerTimeStep)
				{
					return(m_uiPacketIndex < rhs.m_uiPacketIndex);
				} 
				else
				{
					return(m_uiServerTimeStep < rhs.m_uiServerTimeStep);
				}
			}
			else
			{
				return (m_usCmd < rhs.m_usCmd);
			}
		}
		// ֡�����֣�����֡�Ĺ���
		unsigned short m_usCmd;
		// �����ʱ���
		unsigned int m_uiServerTimeStep;
		// ����ˮ��
		unsigned int m_uiPacketIndex;
	}m_oSndFrameKey;
	// �ѷ���֡����
	map<m_oSndFrameKey, m_oCommFrameStructPtr> m_oSndFrameMap;
public:
	// ���ý���֡�ṹ��
	void OnResetFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose(void);
	// �õ�һ�����н���֡�ṹ��
	m_oCommFrameStructPtr GetFreeFrameStruct(void);
	// ����һ�����н���֡�ṹ��
	void AddFreeFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	// �ж��������Ƿ��Ѽ���������
	BOOL IfFramePtrExistInSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
		unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap);
	// ���Ӷ���������
	void AddFramePtrToSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
		unsigned int m_uiPacketIndex, m_oCommFrameStructPtr pFrameStruct, 
		map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap);
	// �������������ţ���������õ�ָ��
	m_oCommFrameStructPtr GetFramePtrFromSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
		unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap);
	// ��������ɾ��������ָ�������ָ��
	BOOL DeleteFramePtrFromSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
		unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap);
};

