#pragma once
#include "Parameter.h"
/**
*@brief ��������֡��
*/
class CFrameHeartBeat
{
public:
	CFrameHeartBeat();
	~CFrameHeartBeat();

public: // ����
	/** ֡����*/
	byte m_pFrameData[SndFrameSize];
public: // ����
	// ���ö���
	void MakeHeartBeatFrame();
};
