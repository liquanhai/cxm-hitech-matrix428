// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATRIXCOMMDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATRIXCOMMDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifndef _MatrixCommDll_H
#define _MatrixCommDll_H
/*
*	if using C++ Compiler to compile the file, adopting C linkage mode
*/
#ifdef __cplusplus
extern "C" {
#endif

	// according to the control macro, deciding whether export or import functions
#ifdef MATRIXCOMMDLL_EXPORTS
#define MATRIXCOMMDLL_API __declspec(dllexport)
#else
#define MATRIXCOMMDLL_API __declspec(dllimport)
#endif

// �����Ǵ� MatrixCommDll.dll ������
/**
* @class CCommClient
* @brief ��Dll�����Ŀͻ���Socket��
*/
class MATRIXCOMMDLL_API CCommClient : public CAsyncSocket
{
public:
	/**
	* @fn CCommServer(void)
	* @detail ���캯��
	*/
	CCommClient();
	/**
	* @fn ~CCommServer(void)
	* @detail ��������
	*/
	~CCommClient();
};
/**
* @class CMatrixCommDll
* @brief ��Dll������ͨѶ�ӿ���
*/
class MATRIXCOMMDLL_API CMatrixCommDll {
public:
	/**
	* @fn CMatrixCommDll()
	* @detail ���캯��
	*/
	CMatrixCommDll();
	/**
	* @fn ~CMatrixCommDll()
	* @detail ��������
	*/
	~CMatrixCommDll();
	// TODO: �ڴ�������ķ�����
	/**
	* @fn void OnInit(void)
	* @detail ��ʼ��
	* @return void
	*/
	virtual void OnInit(void);
	/**
	* @fn void OnClose(void)
	* @detail �ر�
	* @return void
	*/
	virtual void OnClose(void);
	/**
	* @fn void OnInitSocketLib(void)
	* @detail ��ʼ���׽��ֿ�
	* @return void
	*/
	virtual void OnInitSocketLib(void);
	/**
	* @fn void OnCloseSocketLib(void)
	* @detail �ͷ��׽��ֿ�
	* @return void
	*/
	virtual void OnCloseSocketLib(void);
public:
	/** �ͻ���Socket��ָ��*/
	CCommClient* m_pCommClient;
};
extern MATRIXCOMMDLL_API int nMatrixCommDll;

MATRIXCOMMDLL_API int fnMatrixCommDll(void);

MATRIXCOMMDLL_API CMatrixCommDll* CreateMatrixCommDll(void);
MATRIXCOMMDLL_API void DeleteMatrixCommDll(CMatrixCommDll* pClass);
/**
* @fn CCommClient* CreateCommClient(void)
* @detail �����ͻ���
*/
MATRIXCOMMDLL_API CCommClient* CreateCommClient(void);
/**
* @fn void DeleteCommClient(CCommClient* pClass)
* @detail �ͷſͻ���
*/
MATRIXCOMMDLL_API void DeleteCommClient(CCommClient* pClass);
#undef MATRIXCOMMDLL_API
#ifdef __cplusplus
}
#endif

#endif