#include "stdafx.h"
#include "MatrixServerDll.h"

// �������ݴ洢��������Ϣ
void OnADCDataBufReset(m_oADCDataBufStruct* pADCDataBuf)
{
	ASSERT(pADCDataBuf != NULL);
	// �Ƿ�ʹ����
	pADCDataBuf->m_bInUsed = false;
	if (pADCDataBuf->m_pADCDataBuf != NULL)
	{
		memset(pADCDataBuf->m_pADCDataBuf, 0, pADCDataBuf->m_uiBufLength);
	}
// 	// ÿ���ɼ�վ���ݴ洢֡��
// 	pADCDataBuf->m_uiFrameNb = 0;
// 	// SEGDЭ��ͷ����
// 	pADCDataBuf->m_uiSEGDHeaderLen = 0;
// 	// �ɼ�վ����ͷ����
// 	pADCDataBuf->m_uiDataHeaderLen = 0;
}