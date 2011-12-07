#pragma once

#include "FrameTestData.h"
#include "Matrixline.h"

#define MY_MSG WM_USER+100

/**
*@brief ������������֡��������ӿ���
*/
class CSocketTestDataFrame : public CSocket
{
public:
	CSocketTestDataFrame();
	virtual ~CSocketTestDataFrame();
	virtual void OnReceive(int nErrorCode);

public: // ����
	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** �������ݽ��յĶ˿ں�*/
	UINT m_uiPortForTestDataFrame;

	/** ����֡�ֽ���*/
	int m_iFrameSize;
	/** ���ݽ���֡����*/
	DWORD m_irevFrameCount;
	/** ����֡����֡����*/
	DWORD m_iFrameCount;
	/** ֡���ݶ���*/
	CFrameTestData m_oFrameTestData;
	/** Ϊ�ɼ������߳�ID����*/
	CSocket m_TestDataSocket;
	DWORD m_oProcTestThreadID;
	UINT	  m_dwMessage;
	byte * OnReceive_buf;
	int okBegin;

public: // ����
	// ��ʼ��
	BOOL OnInit(CString strIPForInstrument, UINT uiPortForTestDataFrame);
	// �õ�������ջ������յ���֡����
	DWORD GetFrameCount();
	DWORD GetFrameCount1();
	// ���ý��ջ��������Խ��յ�֡����
	BOOL SetBufferSize(int iFrameCount);
	// �õ�֡����
	BOOL GetFrameData();
	BOOL GetFrameData1();
	// �õ�֡���ݣ�������
	BOOL GetFrameDataNotParse();
	BOOL GetFrameDataNotParse1();

};


