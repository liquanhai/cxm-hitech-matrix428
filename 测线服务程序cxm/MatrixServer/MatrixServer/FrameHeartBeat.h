#pragma once
#include "..\\parameter\\Parameter.h"
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
