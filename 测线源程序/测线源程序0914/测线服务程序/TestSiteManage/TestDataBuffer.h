#pragma once

/**
*@brief �������ݻ�������
*/
#include "Matrixline.h"

class CTestDataBuffer
{
public:
	CTestDataBuffer();
	~CTestDataBuffer();

public: //����	
	/** ���Ե�Ԫ����*/
	unsigned int m_uiTestElementCountAll;

	/** ������������ָ�룬һ�����Ե�Ԫ�ģ�74 * 4 * 28 = 8288��2048 * 4 = 8192*/
	//4��վ�ɼ�30�� 74*4*4*30=35520,48��վ=426240
	//byte m_pArrayTestDataOfOneElement[35520];
	byte m_pArrayTestDataOfOneElement[ArrayTestDataOfOne];
		
	/** ������������ָ��*/
	byte* m_pArrayTestData;
	/** ���ֽ���*/
	unsigned int m_uiByteCountAll;

	/** ÿ������ռ���ֽ�*/
	unsigned int m_uiDataByteSize;
	/** ÿ�����ݰ������ݸ���*/
	unsigned int m_uiGroupDataCount;
	/** ÿ������ռ���ֽ�*/
	unsigned int m_uiGroupDataByteSize;
	/** �����ݸ���*/
	unsigned int m_uiBlockCount;
	/** ÿ�����ݰ������������*/
	unsigned int m_uiBlockGroupCount;
	/** ÿ������ռ���ֽ�*/
	unsigned int m_uiBlockByteSize;
	/** ����������д�����ʼλ��*/
	unsigned int m_uiBlockIndexForReWrite;

	/** ���Ե�Ԫ����������ʹ�õ�*/
	unsigned int m_uiTestElementCountAllUsed;
	/** ÿ�����ݰ��������������ʹ�õ�*/
	unsigned int m_uiBlockGroupCountUsed;
	/** ÿ������ռ���ֽڣ�ʹ�õ�*/
	unsigned int m_uiBlockByteSizeUsed;
	/** ���ֽ�����ʹ�õ�*/
	unsigned int m_uiByteCountAllUsed;
	/** ������������ֵ*/
	int m_AVGNoiseValue;
	/** ����֡����*/
	unsigned int m_uiFrameIndex;
	/** ����֡������д�����ļ���*/
	unsigned int m_uiFrameIndexWrite;

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// ���ã�Ϊһ���µĲ�������
	void ResetForNewTestRequest();
	// ��������
	void OnTestSetup(unsigned int uiTestElementCountAllUsed);
	// �õ�������
	int GetBlockIndexByFrameIndex(unsigned int uiFrameIndex);
	// ���ò��Ե�Ԫһ֡��������
	void SetElementTestDataOfOneFrame(byte* lpData, unsigned int uiElementIndex, unsigned int uiFrameIndex);
	// �õ����Ե�Ԫһ֡��������
	byte* GetElementTestDataOfOneFrame(unsigned int uiElementIndex, unsigned int uiFrameIndex);
	// �õ�һ֡�������ݣ���λ��
	byte* GetBlockTestDataOneFrame(unsigned int uiFrameIndex);
	// �õ����Ե�Ԫһ�β�������
	byte* GetElementTestDataOfOneTest(unsigned int uiElementIndex, unsigned int uiSamplingPointCount);
	// �õ����Ե�Ԫһ�β������ݣ��������
	byte* GetElementTestDataOfOneTestForNoiseMonitor(unsigned int uiFrameIndex, unsigned int uiElementIndex);
};