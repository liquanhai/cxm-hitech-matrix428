#pragma once

// CSocketTailFrame ����Ŀ��
///////////////////////////////////////////////////////////////////////////
/**
 * @class CSocketTailFrame
 * @brief β������
 *
 * β�����ն��󣬽���β�����ݣ�������ǰ������ʱ��
 */
class CSocketTailFrame : public CSocket
{
public:
	CSocketTailFrame();
	virtual ~CSocketTailFrame();
	virtual void OnReceive(int nErrorCode);
	bool CreateTailFrameSocket(UINT wPort, LPCTSTR strHostIP);
};


