#pragma once

#include "FrameInterface.h"

/**
*@brief ������������֡��������ӿ���
*/
class CSocketInterfaceDataSend : public CSocket
{
public:
	CSocketInterfaceDataSend();
	virtual ~CSocketInterfaceDataSend();
public: // ����

	/** ���ڲ�ͨѶ�ı���IP��ַ*/
	CString m_strIPForInterface;
	/** ��������֡�Ķ˿ں�*/
	UINT m_uiPortForCommandSend;
	/** �ͻ���Ŀ��IP��ַ*/
	CString m_strIPAim;
	/** �ͻ���Ŀ��IP�˿ں�*/
	UINT m_uiPortAim;

	/** ֡�ֽ���*/
	int m_iFrameSize;
	/** ����֡���ݶ���*/
	CFrameInterface m_oFrameInterface;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInterface, UINT uiPortForCommandSend, UINT uiPortAim);
	// ���û�������С
	BOOL SetBufferSize(int iBufferSize);
	// ��������֡
	int SendDataFrame();
	// ���ɲ�������֡
	void CreateOutputDataFrameTest(unsigned int uiTestType, unsigned int uiDataSize, unsigned short usDataCount, byte* pData);
};


