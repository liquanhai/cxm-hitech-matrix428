#include "stdafx.h"
#include "MatrixServerDll.h"

// �������ݴ洢��������Ϣ
void OnADCDataBufReset(m_oADCDataBufStruct* pADCDataBuf)
{
	ASSERT(pADCDataBuf != NULL);
	// �Ƿ�ʹ����
	pADCDataBuf->m_bInUsed = false;
	// ���ݴ洢֡��ţ���0��ʼ
	pADCDataBuf->m_uiFrameNb = 0;
	// ��������SN
	pADCDataBuf->m_uiIP = 0;
	// ֡�ı���ʱ��
	pADCDataBuf->m_uiSysTime = 0;
}