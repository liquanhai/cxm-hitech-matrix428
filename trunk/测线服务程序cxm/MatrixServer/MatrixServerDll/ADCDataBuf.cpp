#include "stdafx.h"
#include "MatrixServerDll.h"

// �������ݴ洢��������Ϣ
void OnADCDataBufReset(m_oADCDataBufStruct* pADCDataBuf)
{
	ASSERT(pADCDataBuf != NULL);
	m_oSegdDataHeaderStruct* pSegdDataHeader = NULL;
	// �Ƿ�ʹ����
	pADCDataBuf->m_bInUsed = false;
	/** ÿ��վ�洢�����ݵ���*/
	pADCDataBuf->m_uiSavePointNum = 0;
	// ����ʱ��
	pADCDataBuf->m_uiSampleTime = 0;
	/** �ж��Ƿ�д��SEGD�ļ���־λ*/
	pADCDataBuf->m_bSaveInSegd = false;
	/** ����ʩ���Ĳɼ�վ����*/
	pADCDataBuf->m_uiAcqTraceNum = 0;
	/** ��������Ŀ*/
	pADCDataBuf->m_uiAuxTraceNum = 0;
	/** ʩ������������ָ�룬�ؼ���ΪIP������Ϊ����ʩ���������ṹ��*/
	while(pADCDataBuf->m_olsSegdDataHeader.size() != 0)
	{
		pSegdDataHeader = *pADCDataBuf->m_olsSegdDataHeader.begin();
		delete pSegdDataHeader;
		pSegdDataHeader = NULL;
		pADCDataBuf->m_olsSegdDataHeader.pop_front();
	}
	/** ʩ���ں�*/
	pADCDataBuf->m_uiOptNo = 0;
	/** ������*/
	pADCDataBuf->m_iSampleRate = 0;
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