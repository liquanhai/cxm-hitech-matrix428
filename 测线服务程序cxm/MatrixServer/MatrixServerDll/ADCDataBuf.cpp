#include "stdafx.h"
#include "MatrixServerDll.h"

// �������ݴ洢��������Ϣ
void OnADCDataBufReset(m_oADCDataBufStruct* pADCDataBuf)
{
	ASSERT(pADCDataBuf != NULL);
	// �Ƿ�ʹ����
	pADCDataBuf->m_bInUsed = false;
	// ÿ���ɼ�վ���ݴ洢֡��
	pADCDataBuf->m_uiFrameNb = 0;
	// SEGDЭ��ͷ����
	pADCDataBuf->m_uiSEGDHeaderLen = 0;
	// �ɼ�վ����ͷ����
	pADCDataBuf->m_uiDataHeaderLen = 0;
}