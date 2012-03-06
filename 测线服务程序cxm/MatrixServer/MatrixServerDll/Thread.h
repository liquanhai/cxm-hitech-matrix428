#include "ConstVar.h"
#include "LogOutPut.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _Thread_H
#define   _Thread_H
// �߳̽ṹ��
typedef struct Thread_Struct
{
	// �߳̾��
	HANDLE m_hThread;
	// �̺߳�
	DWORD m_dwThreadID;
	//�Ƿ���״̬
	bool m_bWork;
	// �Ƿ�ر��߳�
	bool m_bClose;
	// �߳̽����¼�
	HANDLE m_hThreadClose;
	// ����ָ��
	m_oConstVarStruct* m_pConstVar;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oThreadStruct;
#endif