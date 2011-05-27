#pragma once
#include "Parameter.h"
class CADCFrameInfo
{
public:
	CADCFrameInfo(void);
	~CADCFrameInfo(void);
public:
	// �ļ�����·��
	CString m_csSaveFilePath;
	// �����ļ����ļ�ָ��
	FILE * m_pFileSave;
public:
	// ���ļ�
	void OnOpenFile(void);
	// �����ļ�
	void OnSaveFile(unsigned int uiInstrumentNb, unsigned int uiDataPointNum, unsigned int uiSysTime);
	// �ر��ļ�
	void OnCloseFile(void);
};
