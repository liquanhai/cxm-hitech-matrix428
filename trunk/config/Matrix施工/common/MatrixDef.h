#pragma once

//////////////////////////////////////////////////////////////////////////
// �����ļ������Զ�����Ϣ����
#define     MSG_XMLFILE_NEW				(_T("MSG_XMLFileNew"))

extern      UINT NEAR WM_NEWXMLFILE;		// ��SocketGlobalFunction.cpp�ļ��г�ʼ������

////////////////////////////////////////////////////////////////////////////////////////////////////
// �����Ŷ��壬������־�м�¼��־��Դ�������ļ�����֪ͨ
#define		MATRIX_START				1
#define		MATRIX_ADMIN				2
#define		MATRIX_ADMINSERVER			3
#define		MATRIX_INSTALL				4
#define		MATRIX_CONFIG				5
#define		MATRIX_LINE					6
#define		MATRIX_LINESERVER			7
#define		MATRIX_OPERATION			8
#define		MATRIX_OPERATIONSERVER		9

////////////////////////////////////////////////////////////////////////////
// Line���������ļ��޸�
#define		MATRIX_LINE_ALL				0		// �����ļ�����
#define		MATRIX_LINE_AUXI			1		// ������
#define		MATRIX_LINE_SPREAD          2		// �ɼ�����



//////////////////////////////////////////////////////////////////////////
// Config���������ļ�֪ͨ���Զ���
#define		MATRIX_CONFIG_ALL			0		// �����ļ�����
#define		MATRIX_CONFIG_CREWSETUP		1		// CrewSetup����
#define		MATRIX_CONFIG_USERINFO		2		// Userinfo����
#define		MATRIX_CONFIG_SEGDSETUP		3		// SEGDSetup����
#define		MATRIX_CONFIG_DISKRECORD	4		// DiskRecord����

//////////////////////////////////////////////////////////////////////////
// Install
#define		MATRIX_INSTALL_ALL			0

//////////////////////////////////////////////////////////////////////////
// operation���������ļ�
#define     MATRIX_OPERATION_ALL	    0