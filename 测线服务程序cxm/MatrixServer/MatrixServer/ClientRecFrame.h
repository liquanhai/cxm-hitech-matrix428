#pragma once
/**
@brief ���ļ�Ϊ�������ͻ���ͨѶ����֡�������ļ�
@details
@file ClientRecFrame.h
@note 
@see	
@version	
@author cxm
@bug
*/
#include "ClientCommFrame.h"
/**
* @class CClientRecFrame
* @brief ��ͻ���ͨѶ����֡��
* @note �̳���CClientCommFrame
*/
class CClientRecFrame : public CClientCommFrame
{
public:
	/**
	* @fn CClientRecFrame(void)
	* @detail CClientRecFrame���캯��
	*/
	CClientRecFrame(void);
	/**
	* @fn ~CClientRecFrame(void)
	* @detail CClientRecFrame��������
	*/
	~CClientRecFrame(void);
public:
	/**
	* @fn void PhraseFrame(char* cpFrame, unsigned short usSize)
	* @detail ����֡
	* @param[in] cpFrame ������ָ��
	* @param[in] usSize ��Ҫ������ֽ���
	* @return void
	*/
	void PhraseFrame(char* cpFrame, unsigned short usSize);
};

