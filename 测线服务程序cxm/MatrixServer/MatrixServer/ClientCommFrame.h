#pragma once
/**
@brief ���ļ�Ϊ�������ͻ���ͨѶ֡�������ļ�
@details
@file ClientCommFrame.h
@note 
@see	
@version	
@author cxm
@bug
*/
#include "CommProtocol.h"
#include <list>
using std::list;
/**
* @class CClientCommFrame
* @brief ��ͻ���ͨѶ֡����
*/
class CClientCommFrame
{
public:
	/**
	* @fn CClientCommFrame(void)
	* @detail CClientCommFrame���캯��
	*/
	CClientCommFrame(void);
	/**
	* @fn ~CClientCommFrame(void)
	* @detail CClientCommFrame��������
	* @note �麯��
	*/
	virtual ~CClientCommFrame(void);
public:
	/** ���е�֡�ṹ����*/
	unsigned int m_uiCountFree;
	/** ֡�ṹ������*/
	m_oCommFrameStruct m_oCommFrameArray[FrameStructNumMax];
	/** ������Դͬ������*/
	CRITICAL_SECTION m_oSecClientFrame;
	/** ����֡�ṹ�����*/
	list<m_oCommFrameStructPtr> m_olsCommFrameFree;
	/** �ȴ�����֡�ṹ��*/
	list<m_oCommFrameStructPtr> m_olsCommWorkFrame;
	/** ������ˮ��*/
	unsigned int m_uiPacketIndex;
	/** ������ˮ��*/
	unsigned int m_uiCmdIndex;
	/** ���ݴ�������*/
	char m_cProcBuf[ProcBufferSize];
public:
	/**
	* @fn void OnResetFrameStruct(m_oCommFrameStructPtr pFrameStruct)
	* @detail ���ý���֡�ṹ��
	* @param[in] pFrameStruct ͨѶָ֡��	
	* @return void
	*/
	void OnResetFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	/**
	* @fn void OnInit(void)
	* @detail ��ʼ��
	* @param[in] void	
	* @return void
	*/
	void OnInit(void);
	/**
	* @fn void OnClose(void)
	* @detail �ر�
	* @param[in] void
	* @return void
	*/
	void OnClose(void);
	/**
	* @fn m_oCommFrameStructPtr GetFreeFrameStruct(void)
	* @detail �õ�һ�����н���֡�ṹ��
	* @param[in] void	
	* @return ����һ��ͨѶָ֡��
	*/
	m_oCommFrameStructPtr GetFreeFrameStruct(void);
	/**
	* @fn void AddFreeFrameStruct(m_oCommFrameStructPtr pFrameStruct)
	* @detail ����һ�����н���֡�ṹ��
	* @param[in] pFrameStruct ͨѶָ֡��
	* @return void
	*/
	void AddFreeFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	/**
	* @fn void OnResetProcBuf(void)
	* @detail �������ݴ�������
	* @param[in] void
	* @return void
	*/
	void OnResetProcBuf(void);
};

