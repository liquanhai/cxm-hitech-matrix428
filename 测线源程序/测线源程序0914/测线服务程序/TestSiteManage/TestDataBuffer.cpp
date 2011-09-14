#include "StdAfx.h"
#include "TestDataBuffer.h"

CTestDataBuffer::CTestDataBuffer()
{
	m_uiTestElementCountAll = 0;	// ���Ե�Ԫ����

	m_pArrayTestData = NULL;	// ������������ָ��
	m_uiByteCountAll = 0;	// ���ֽ���

	m_uiDataByteSize = 3;	// ÿ������ռ���ֽ�
	m_uiGroupDataCount = FrameADCount;	// ÿ�����ݰ������ݸ���
	m_uiGroupDataByteSize = m_uiGroupDataCount * m_uiDataByteSize;	// ÿ������ռ���ֽ�
	m_uiBlockGroupCount = 0;	// ÿ�����ݰ������������
	m_uiBlockCount = 32;	// �����ݸ���	
	m_uiBlockByteSize = 0;	// ÿ������ռ���ֽ�
	/** ����������д�����ʼλ��*/
	m_uiBlockIndexForReWrite = 28;

	m_uiTestElementCountAllUsed = 0;	// ���Ե�Ԫ����������ʹ�õ�
	m_uiBlockGroupCountUsed = 0;	// ÿ�����ݰ��������������ʹ�õ�
	m_uiBlockByteSizeUsed = 0;	// ÿ������ռ���ֽڣ�ʹ�õ�
	m_uiByteCountAllUsed = 0;	// ���ֽ�����ʹ�õ�

	m_uiFrameIndex = 0;	// ����֡����
	m_uiFrameIndexWrite = 0;	// ����֡������д�����ļ���
}

CTestDataBuffer::~CTestDataBuffer()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CTestDataBuffer::OnInit()
{
	m_uiGroupDataByteSize = m_uiGroupDataCount * m_uiDataByteSize;	// ÿ������ռ���ֽ�
	m_uiBlockGroupCount = m_uiTestElementCountAll;	// ÿ�����ݰ������������
	m_uiBlockByteSize = m_uiBlockGroupCount * m_uiGroupDataByteSize;	// ÿ������ռ���ֽ�
	m_uiByteCountAll = m_uiBlockCount * m_uiBlockByteSize;	// ���ֽ���

	// ���ɲ������ݻ���������
	m_pArrayTestData = new byte[m_uiByteCountAll];
}

/**
* �ر�
* @param void
* @return void
*/
void CTestDataBuffer::OnClose()
{
	// ɾ���������ݻ���������
	delete[] m_pArrayTestData;
}

/**
* ����
* @param void
* @return void
*/
void CTestDataBuffer::OnReset()
{
	memset(m_pArrayTestData, 0xFF, m_uiByteCountAll);
}

/**
* ���ã�Ϊһ���µĲ�������
* @param void
* @return void
*/
void CTestDataBuffer::ResetForNewTestRequest()
{
	m_uiFrameIndex = 0;	// ����֡����
	m_uiFrameIndexWrite = 0;	// ����֡������д�����ļ���
	memset(m_pArrayTestData, 0xFF, m_uiByteCountAllUsed);
}

/**
* ��������
* @param unsigned int uiTestElementCountAllUsed ���Ե�Ԫ����������ʹ�õ�
* @return void
*/
void CTestDataBuffer::OnTestSetup(unsigned int uiTestElementCountAllUsed)
{
	m_uiTestElementCountAllUsed = uiTestElementCountAllUsed;	// ���Ե�Ԫ����������ʹ�õ�
	m_uiBlockGroupCountUsed = m_uiTestElementCountAllUsed;	// ÿ�����ݰ��������������ʹ�õ�
	m_uiBlockByteSizeUsed = m_uiBlockGroupCountUsed * m_uiGroupDataByteSize;	// ÿ������ռ���ֽڣ�ʹ�õ�
	m_uiByteCountAllUsed = m_uiBlockCount * m_uiBlockByteSizeUsed;	// ���ֽ�����ʹ�õ�
}

/**
* �õ�������
* @param void
* @return void
*/
int CTestDataBuffer::GetBlockIndexByFrameIndex(unsigned int uiFrameIndex)
{
	int iBlockIndex = 0;
	// �õ��������ݿ�����
	// �жϣ�����д��
	if(uiFrameIndex < m_uiBlockCount)
	{
		iBlockIndex = uiFrameIndex;
	}
	// �жϣ�����Ҫ����ԭ������д��
	else
	{
		iBlockIndex = (uiFrameIndex - m_uiBlockIndexForReWrite) % (m_uiBlockCount - m_uiBlockIndexForReWrite);
		iBlockIndex = iBlockIndex + m_uiBlockIndexForReWrite;
	}
	return iBlockIndex;
}

/**
* ���ò��Ե�Ԫһ֡��������
* @param byte* lpData ����ָ��
* @param unsigned int uiElementIndex ��Ԫ����
* @param unsigned int uiFrameIndex ֡����
* @return void
*/
void CTestDataBuffer::SetElementTestDataOfOneFrame(byte* lpData, unsigned int uiElementIndex, unsigned int uiFrameIndex)
{
	// �õ��������ݿ�����
	int iBlockIndex = GetBlockIndexByFrameIndex(uiFrameIndex);
	// �õ����ݱ���λ��
	int iSaveIndex = iBlockIndex * m_uiBlockByteSizeUsed + uiElementIndex * m_uiGroupDataByteSize;
	// ��������
	memcpy(&m_pArrayTestData[iSaveIndex], lpData, m_uiGroupDataByteSize);
}

/**
* �õ����Ե�Ԫһ֡��������
* @param unsigned int uiElementIndex ��Ԫ����
* @param unsigned int uiFrameIndex ֡����
* @return byte* ����ָ��
*/
byte* CTestDataBuffer::GetElementTestDataOfOneFrame(unsigned int uiElementIndex, unsigned int uiFrameIndex)
{
	// �õ��������ݿ�����
	int iBlockIndex = GetBlockIndexByFrameIndex(uiFrameIndex);
	// �õ����ݱ���λ��
	int iSaveIndex = iBlockIndex * m_uiBlockByteSizeUsed + uiElementIndex * m_uiGroupDataByteSize;
	// �õ�����
	return &m_pArrayTestData[iSaveIndex];
}

/**
* �õ�һ֡�������ݣ���λ��
* @param unsigned int uiFrameIndex ֡����
* @return byte* ����ָ��
*/
byte* CTestDataBuffer::GetBlockTestDataOneFrame(unsigned int uiFrameIndex)
{
	// �õ��������ݿ�����
	int iBlockIndex = GetBlockIndexByFrameIndex(uiFrameIndex);
	// �õ����ݱ���λ��
	int iSaveIndex = iBlockIndex * m_uiBlockByteSizeUsed;
	// �õ�����
	return &m_pArrayTestData[iSaveIndex];
}

/**
* �õ����Ե�Ԫһ�β�������
* @param unsigned int uiElementIndex ��Ԫ����
* @param unsigned int uiSamplingPointCount ����������
* @return byte* ����ָ��
*/
byte* CTestDataBuffer::GetElementTestDataOfOneTest(unsigned int uiElementIndex, unsigned int uiSamplingPointCount)
{
	// �жϣ�������������2048
	//if(uiSamplingPointCount > ADoffset)
	if(uiSamplingPointCount > m_uiTestElementCountAll)
	{
		TRACE1("m_uiTestElementCountAll ERROR! %d TBH=%d\r\n",m_uiTestElementCountAll);
		return NULL;
	}
	// ������0
	//memset(m_pArrayTestDataOfOneElement, 0x00, 8288);
	memset(m_pArrayTestDataOfOneElement, 0x00, ArrayTestDataOfOne);
	// �õ�����֡��
	int iFrameCount = uiSamplingPointCount / m_uiGroupDataCount;
	if((uiSamplingPointCount % m_uiGroupDataCount) > 0)
	{
		iFrameCount++;
	}
	m_AVGNoiseValue=0;
	int iAVG=0;
	int iAVGCount=0;
	for(int i = 0; i < iFrameCount; i++)
	{
		// �õ����Ե�Ԫһ֡��������
		byte* byDataFrame = GetElementTestDataOfOneFrame(uiElementIndex, i);
		for(int j = 0; j < m_uiGroupDataCount; j++)
		{
			memcpy(&m_pArrayTestDataOfOneElement[(i * m_uiGroupDataCount * 4) + (j * 4)], &byDataFrame[j * 3], 3);
			int idata=0;
			if(j>1 && FrameADCount72==72){
				memcpy(&idata, &byDataFrame[j * 3], 3);
/*				if(idata>0x800000){
					idata=-(0xffffff-idata);
				}
*/				iAVG=iAVG+idata;
				iAVG=iAVG&0xffffff;
				iAVGCount++;
			}
			if(FrameADCount72==74){
				memcpy(&idata, &byDataFrame[j * 3], 3);
				if(idata>0x800000){
					idata=-(0xffffff-idata);
				}
				iAVG=iAVG+idata;
				iAVGCount++;
			}
		}
	}
	// �õ�����
	if(iAVG>0x400000)
		m_AVGNoiseValue=0xffffff-(0xffffff-iAVG)/iAVGCount;
	else
		m_AVGNoiseValue=(int)iAVG/iAVGCount;
	return m_pArrayTestDataOfOneElement;
}

/**
* �õ����Ե�Ԫһ�β������ݣ��������
* @param unsigned int uiFrameIndex ֡����
* @param unsigned int uiElementIndex ��Ԫ����
* @return byte* ����ָ��
*/
byte* CTestDataBuffer::GetElementTestDataOfOneTestForNoiseMonitor(unsigned int uiFrameIndex, unsigned int uiElementIndex)
{
	// ������0
	memset(m_pArrayTestDataOfOneElement, 0x00, 296);
	// �õ����Ե�Ԫһ֡��������
	byte* byDataFrame = GetElementTestDataOfOneFrame(uiElementIndex, uiFrameIndex);
	for(int i = 0; i < m_uiGroupDataCount; i++)
	{
		memcpy(&m_pArrayTestDataOfOneElement[i * 4], &byDataFrame[i * 3], 3);
	}
	// �õ�����
	return m_pArrayTestDataOfOneElement;
}