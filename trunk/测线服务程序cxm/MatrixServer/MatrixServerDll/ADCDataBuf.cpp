#include "stdafx.h"
#include "MatrixServerDll.h"

// �������ݴ洢��������Ϣ
void OnADCDataBufReset(m_oADCDataBufStruct* pADCDataBuf)
{
	ASSERT(pADCDataBuf != NULL);
	// �Ƿ�ʹ����
	pADCDataBuf->m_bInUsed = false;
	/** ÿ��վ�洢�����ݵ���*/
	pADCDataBuf->m_uiSavePointNum = 0;
	/** �ж��Ƿ�д��SEGD�ļ���־λ*/
	pADCDataBuf->m_bSaveInSegd = false;
	/** ����ʩ���Ĳɼ�վ����*/
	pADCDataBuf->m_uiOptInstrNum = 0;
	/** ʩ���ں�*/
	pADCDataBuf->m_uiOptNo = 0;
	/** ʩ�����ݴ洢�ļ�·��*/
	pADCDataBuf->m_SaveFilePath = "";
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