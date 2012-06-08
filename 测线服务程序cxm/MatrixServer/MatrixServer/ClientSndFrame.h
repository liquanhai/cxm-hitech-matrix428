#pragma once
#include "ClientCommFrame.h"
#include "ClientSocket.h"
#include <map>
using std::map;
/**
* @class CClientSndFrame
* @brief ��ͻ���ͨѶ����֡��
*/
class CClientSndFrame : public CClientCommFrame
{
public:
	CClientSndFrame(void);
	~CClientSndFrame(void);
public:
	/** �ͻ���Socket��ָ��*/
	CClientSocket* m_pClientSocket;
	/**
	* @brief �ѷ���֡�����ؼ���
	*/
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
		/** ֡�����֣�����֡�Ĺ���*/
		unsigned short m_usCmd;
		/** �����ʱ���*/
		unsigned int m_uiServerTimeStep;
		/** ����ˮ��*/
		unsigned int m_uiPacketIndex;
	}m_oSndFrameKey;
	/** �ѷ���֡����*/
	map<m_oSndFrameKey, m_oCommFrameStructPtr> m_oSndFrameMap;
public:
	// ����Ӧ��֡
	void MakeReturnFrame(m_oCommFrameStructPtr ptrFrame);
	// ��������֡
	void MakeSetFrame(unsigned short usCmd, char* pChar, unsigned int uiSize);
	// ���ɷ���֡
	void MakeSendFrame(m_oCommFrameStructPtr ptrFrame);
	// �ط�����֡
	bool OnReSendFrame(void);
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

