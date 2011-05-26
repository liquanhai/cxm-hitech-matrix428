#pragma once
#include "afxsock.h"
#include <vector>
#include "OScopeCtrl.h"
#include "Parameter.h"
#include <afxmt.h>
using namespace std;

// ADDataThread

class CADDataThread : public CWinThread
{
	DECLARE_DYNCREATE(CADDataThread)

public:
	CADDataThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CADDataThread();
	virtual int Run();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:

	// ��ʼ��
	void OnInit(void);

	// �رղ������߳�
	void OnClose(void);
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hADDDataThreadClose;
	// AD���ݽ���Socket
	CSocket m_ADDataSocket;
	
	// ��
	byte ADData[256];
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// ���ղ�������
	void ReceiveSampleData(byte* pSampleData);
	// ѡ����������
	int* m_pSelectObject;
	// ѡ�������������������
	int* m_pSelectObjectNoise;
	// �ɼ���������
	vector <double>*m_pSampleData[GraphViewNum];
	// ͼ��ģ��ָ��
	COScopeCtrl* m_pOScopeCtrl[GraphViewNum];
	// �����ٽ�������
	CCriticalSection m_Sec;
};


