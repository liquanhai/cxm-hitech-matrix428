#include "StdAfx.h"
#include "TestElementData.h"
#include "Matrixline.h"

CTestElementData::CTestElementData()
{
}

CTestElementData::~CTestElementData()
{
}

/**
* ����
* @param void
* @return void
*/
void CTestElementData::Reset()
{
	m_bInUsed = false;	// �Ƿ�ʹ����	
	m_uiIP = 0;	// IP��ַ
	m_uiDataStep = 0;	// ����������λ����
	m_uiFrameIndex = 0;	// ֡����
	m_uiDataIndexPreview = 0;	// ��һ�ε���������
	m_uiDataBegin=-1;			// ����������ʼƫ����
	IndexPreview=-1;
	m_uiADCSetOperationNb = 0;

	// ���ò���
	ResetTest();
}

/**
* ���ò���
* @param void
* @return void
*/
void CTestElementData::ResetTest()
{
	// ������������ֵ
	m_fInstrumentNoiseValue = 0.0;
	// �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byInstrumentNoiseCheck = 0;
	// �������������о�
	m_fInstrumentNoiseLimit = 0.0;

	// �����������ֵ
	m_fInstrumentDistortionValue = 0.0;
	// ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byInstrumentDistortionCheck = 0;
	// ������������о�
	m_fInstrumentDistortionLimit = 0.0;

	// ������������ֵ
	m_fInstrumentCrosstalkValue = 0.0;
	// �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byInstrumentCrosstalkCheck = 0;
	// �������������о�
	m_fInstrumentCrosstalkLimit = 0.0;

	// �����������ֵ
	m_fInstrumentGainValue = 0.0;
	// ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byInstrumentGainCheck = 0;
	// ������������о�
	m_fInstrumentGainLimit = 0.0;
	// ������λ����ֵ
	m_fInstrumentPhaseValue = 0.0;
	// ������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byInstrumentPhaseCheck = 0;
	// ������λ�����о�
	m_fInstrumentPhaseLimit = 0.0;
	// �����������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byInstrumentGainAndPhaseCheck = 0;

	// ������ģ����ֵ
	m_fInstrumentCMRRValue = 0.0;
	// ������ģ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byInstrumentCMRRCheck = 0;
	// ������ģ�����о�
	m_fInstrumentCMRRLimit = 0.0;

	// �������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�
	m_byInstrumentCheck = 0;

	// Ұ��������ֵ
	m_fSensorResistanceValue = 0.0;
	// Ұ�������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_bySensorResistanceCheck = 0;
	/** Ұ���������оݣ�����*/
	m_fSensorResistanceLimitMin = 0.0;
	/** Ұ���������оݣ�����*/
	m_fSensorResistanceLimitMax = 0.0;

	// Ұ��©�����ֵ
	m_fSensorLeakageValue = 0.0;
	// Ұ��©����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_bySensorLeakageCheck = 0;
	// Ұ��©������о�
	m_fSensorLeakageLimit = 0.0;

	// Ұ����������ֵ
	m_fSensorNoiseValue = 0.0;
	// Ұ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_bySensorNoiseCheck = 0;
	// Ұ�����������о�
	m_fSensorNoiseLimit = 0.0;

	// Ұ����б�Ȳ���ֵ
	m_fSensorTiltValue = 0.0;
	// Ұ����б�Ȳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_bySensorTiltCheck = 0;
	// Ұ����б�Ȳ����о�
	m_fSensorTiltLimit = 0.0;

	// Ұ����б��ģ�Ͳ���ֵ
	m_fSensorTiltModelValue = 0.0;
	// Ұ����б��ģ�Ͳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_bySensorTiltModelCheck = 0;
	// Ұ����б��ģ�Ͳ����о�
	m_fSensorTiltModelLimit = 0.0;

	// Ұ����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_bySensorCheck = 0;

	// ����������ֵ
	m_fSensorNoiseMonitorValue = 0.0;
	// ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_bySensorNoiseMonitorCheck = 0;

	// �첨���Ƿ�����˳�ʼ����
	m_byTestOnField = 0;
	// ��ʼ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byOnFieldCheck = 0;
	m_uigroupendcount=0;
}

/**
* ���ã�Ϊһ���µĲ�������
* @param void
* @return void
*/
void CTestElementData::ResetForNewTestRequest()
{
	m_uiDataStep = 0;	// ����������λ����
	m_uiFrameIndex = 0;	// ֡����
	m_uiDataIndexPreview = 0;	// ��һ�ε���������
	m_uiDataBegin=-1;			// ����������ʼƫ����
	IndexPreview=-1;

	// ���ò���
	ResetTest();
}

float CTestElementData::MeanSquare(byte* pData,unsigned int uiSamplingPointCount)
{
	int uiData,iNoiseGain;
	double iAVG=0,Value2=0,m_AVGNoiseValue,itmp;
	//iNoiseGain=NoiseGain;
	iNoiseGain=1;
	char charTemp[128];
	CString strOutput = _T("");
	for(int j = 0; j < uiSamplingPointCount; j++){
		memcpy(&uiData, &pData[(j) * 4], 4);
		if(uiData>0x800000)
			uiData=(0xffffff-uiData);
		//sprintf_s(charTemp,"%d \t",uiData);
		//strOutput += charTemp;
		if(uiData>0x4000)
			uiData=uiData;
		iAVG+=(double)uiData*iNoiseGain;
	}
	//TRACE1("strOutput=%s\r\n",strOutput);
	iAVG=iAVG/uiSamplingPointCount;
	for(int i = 0; i < uiSamplingPointCount; i++){
		memcpy(&uiData, &pData[(i) * 4], 4);
		if(uiData>0x800000)
			uiData=(0xffffff-uiData);
		itmp=(double)uiData*iNoiseGain;
		Value2+=(itmp-iAVG)*(itmp-iAVG);
	}
	Value2=Value2/(uiSamplingPointCount-1);
	if(Value2==0)
		Value2=1.0;
	m_AVGNoiseValue=pow(Value2,0.5);
	return (float)m_AVGNoiseValue;
}
/**
* ����õ����Խ��
* @param unsigned int uiTestType ��������
* @param byte* pData ��������
* @param unsigned int uiSamplingPointCount ���������� ��λ��
* @return void
*/
void CTestElementData::CalculateTestResult(unsigned int uiTestType, byte* pData, unsigned int uiSamplingPointCount,float m_AVGNoiseValue)
{
	int uiData = 0;
	//memcpy(&uiData, &pData[(FrameADCount) * 4], 4);	
	memcpy(&uiData, &pData[(uiSamplingPointCount-1) * 4], 4);	
	if(uiTestType==22)
		m_AVGNoiseValue=MeanSquare(pData,uiSamplingPointCount);
	else
		m_AVGNoiseValue=MeanSquare(pData+(FrameADCount)*4,FrameADCount);
	//uiData=m_AVGNoiseValue;
	if(uiData>0x800000){
		uiData=-(0xffffff-uiData);
	}
	switch(uiTestType)
	{
		// ��������
		// �������ԣ���������
	case 4:
		if(0x7FFFFF == uiData)
		//if(0x7fffff == uiData)
		{
			m_byInstrumentNoiseCheck = 3;
		}
		else
		{
			m_byInstrumentNoiseCheck = 4;
		}
		//ת����uV
		m_fInstrumentNoiseValue =(float)(m_AVGNoiseValue*5/16.777216);
		//TRACE1("m_AVGNoiseValue=%f\r\n",m_AVGNoiseValue);
		//m_fInstrumentNoiseValue =(float)uiData*NoiseGain*5/16.777216;
		break;
		// 	�������ԣ���������
	case 5:
		if(0x7fffff == uiData)
		{
			m_byInstrumentDistortionCheck = 3;
		}
		else
		{
			m_byInstrumentDistortionCheck = 4;
		}
		m_fInstrumentDistortionValue = (float)uiData;
		break;
		// �������ԣ���������
	case 7:	
		if(0x7fffff == uiData)
		{
			m_byInstrumentCrosstalkCheck = 3;
		}
		else
		{
			m_byInstrumentCrosstalkCheck = 4;
		}
		m_fInstrumentCrosstalkValue = (float)uiData;
		break;
		// �������ԣ������������λ
	case 6:
		if(0x7fffff == uiData)
		{
			m_byInstrumentGainCheck = 3;
			m_byInstrumentPhaseCheck = 3;
			m_byInstrumentGainAndPhaseCheck = 3;
		}
		else
		{
			m_byInstrumentGainCheck = 4;
			m_byInstrumentPhaseCheck = 4;
			m_byInstrumentGainAndPhaseCheck = 4;
		}
		// �����������ֵ
		m_fInstrumentGainValue = (float)uiData;
		// ������λ����ֵ
		m_fInstrumentPhaseValue = (float)uiData;
		break;
		// �������ԣ�������ģ
	case 8:
		if(0x7fffff == uiData)
		{
			m_byInstrumentCMRRCheck = 3;
		}
		else
		{
			m_byInstrumentCMRRCheck = 4;
		}
		m_fInstrumentCMRRValue = (float)uiData;
		break;
		// �첨������
		// �첨�����ԣ�Ұ�����
	case 15:
		if(0x7fffff == uiData)
		{
			m_bySensorResistanceCheck = 3;
		}
		else
		{
			m_bySensorResistanceCheck = 4;
		}
		m_fSensorResistanceValue = (float)uiData;
		break;
		// �첨�����ԣ�Ұ��©��
	case 14:
		if(0x7fffff == uiData)
		{
			m_bySensorLeakageCheck = 3;
		}
		else
		{
			m_bySensorLeakageCheck = 4;
		}
		m_fSensorLeakageValue = (float)uiData;
		break;
		// �첨�����ԣ�Ұ������
	case 1:
		if(0x7fffff == uiData)
		{
			m_bySensorNoiseCheck = 3;
		}
		else
		{
			m_bySensorNoiseCheck = 4;
		}
		m_fSensorNoiseValue = (float)uiData;
		break;
		// �첨�����ԣ�Ұ����б��
	case 20:
		if(0x7fffff == uiData)
		{
			m_bySensorTiltCheck = 3;
		}
		else
		{
			m_bySensorTiltCheck = 4;
		}
		m_fSensorTiltValue = (float)uiData;
		break;
		// �첨�����ԣ�Ұ����б��ģʽ
	case 21:
		if(0x7fffff == uiData)
		{
			m_bySensorTiltModelCheck = 3;
		}
		else
		{
			m_bySensorTiltModelCheck = 4;
		}
		m_fSensorTiltModelValue = (float)uiData;
		break;
		// �첨�����ԣ��������
	case 22:
		if(0x7fffff == uiData)
		{
			m_bySensorNoiseMonitorCheck = 3;
		}
		else
		{
			m_bySensorNoiseMonitorCheck = 4;
		}
		
/*		//��ԭֵ
		if(uiData<0)
			uiData=abs(uiData);
		if(uiData==0)
			uiData++;
		//m_fSensorNoiseMonitorValue = 20.0 * (float)log(((double)uiData) / 16777216.0);
		//�۳�-102db
		//m_fSensorNoiseMonitorValue = 170 * (float)log(((double)uiData/16777216.0));
		m_fSensorNoiseMonitorValue = 20 * (float)log(((double)uiData*5*30/16777216.0) );
		//TRACE2("MrValue =%d %f ",uiData, m_fSensorNoiseMonitorValue);
		
		//m_fSensorNoiseMonitorValue =(float)uiData-100;
		
*/		m_fSensorNoiseMonitorValue=20 * (float)log10(m_AVGNoiseValue*5/16777216.0 );
		break;
	}
}

/**
* �ж����Խ��
* @param unsigned int uiTestType ��������
* @return void
*/
void CTestElementData::JudgeTestResult(unsigned int uiTestType)
{
	switch(uiTestType)
	{
		// ��������
		// �������ԣ���������
	case 4:
		if(4 == m_byInstrumentNoiseCheck)
		{
			m_byInstrumentNoiseCheck = 1;		// by zl 3.31
			//����1/2m_fInstrumentNoiseLimit��Ч
			if(m_fInstrumentNoiseValue>m_fInstrumentNoiseLimit || m_fInstrumentNoiseValue<-m_fInstrumentNoiseLimit)
				m_byInstrumentNoiseCheck = 2;
		}
		break;
		// 	�������ԣ���������
	case 5:
		if(4 == m_byInstrumentDistortionCheck)
		{
			m_byInstrumentDistortionCheck = 1;
			if(m_fInstrumentDistortionValue>m_fInstrumentDistortionLimit || m_fInstrumentDistortionValue<-m_fInstrumentDistortionLimit)
				m_byInstrumentDistortionCheck = 2;
		}
		break;
		// �������ԣ���������
	case 7:	
		if(4 == m_byInstrumentCrosstalkCheck)
		{
			m_byInstrumentCrosstalkCheck = 1;
			if(m_fInstrumentCrosstalkValue>m_fInstrumentCrosstalkLimit || m_fInstrumentCrosstalkValue<-m_fInstrumentCrosstalkLimit)
				m_byInstrumentCrosstalkCheck = 2;
		}
		break;
		// �������ԣ������������λ
	case 6:
		if(4 == m_byInstrumentGainCheck)
		{
			m_byInstrumentGainCheck = 1;
			if(m_fInstrumentGainValue>m_fInstrumentGainLimit || m_fInstrumentGainValue<-m_fInstrumentGainLimit)
				m_byInstrumentGainCheck = 2;
		}
		if(4 == m_byInstrumentPhaseCheck)
		{
			m_byInstrumentPhaseCheck = 1;
			if(m_fInstrumentGainValue>m_fInstrumentPhaseLimit || m_fInstrumentGainValue<-m_fInstrumentPhaseLimit)
				m_byInstrumentPhaseCheck = 2;
		}
		if((1 == m_byInstrumentGainCheck) && (1 == m_byInstrumentPhaseCheck))
		{
			m_byInstrumentGainAndPhaseCheck = 1;
		}
		if((2 == m_byInstrumentGainCheck) || (2 == m_byInstrumentPhaseCheck))
		{
			m_byInstrumentGainAndPhaseCheck = 2;
		}
		break;
		// �������ԣ�������ģ
	case 8:
		if(4 == m_byInstrumentCMRRCheck)
		{
			m_byInstrumentCMRRCheck = 1;
			if(m_fInstrumentCMRRValue>m_fInstrumentCMRRLimit || m_fInstrumentCMRRValue<-m_fInstrumentCMRRLimit)
				m_byInstrumentCMRRCheck = 2;
		}
		break;
		// �첨������
		// �첨�����ԣ�Ұ�����
	case 15:
		if(4 == m_bySensorResistanceCheck)
		{
			m_bySensorResistanceCheck = 1;
			if(m_fSensorResistanceValue>m_fSensorResistanceLimitMin || m_fSensorResistanceValue<-m_fSensorResistanceLimitMin)
				m_bySensorResistanceCheck = 2;
		}
		break;
		// �첨�����ԣ�Ұ��©��
	case 14:
		if(4 == m_bySensorLeakageCheck)
		{
			m_bySensorLeakageCheck = 1;
			if(m_fSensorLeakageValue>m_fSensorLeakageLimit || m_fSensorLeakageValue<-m_fSensorLeakageLimit)
				m_bySensorLeakageCheck = 2;
		}
		break;
		// �첨�����ԣ�Ұ������
	case 1:
		if(4 == m_bySensorNoiseCheck)
		{
			m_bySensorNoiseCheck = 1;
			if(m_fSensorNoiseValue>m_fSensorNoiseLimit || m_fSensorNoiseValue<-m_fSensorNoiseLimit)
				m_bySensorNoiseCheck = 2;
		}
		break;
		// �첨�����ԣ�Ұ����б��
	case 20:
		if(4 == m_bySensorTiltCheck)
		{
			m_bySensorTiltCheck = 1;
			if(m_fSensorTiltValue>m_fSensorTiltLimit || m_fSensorTiltValue<-m_fSensorTiltLimit)
				m_bySensorTiltCheck = 2;
		}
		break;
		// �첨�����ԣ�Ұ����б��ģ��
	case 21:
		if(4 == m_bySensorTiltModelCheck)
		{
			m_bySensorTiltModelCheck = 1;
			if(m_fSensorTiltModelValue>m_fSensorTiltModelLimit || m_fSensorTiltModelValue<-m_fSensorTiltModelLimit)
				m_bySensorTiltModelCheck = 2;
		}
		break;
	}
}

/**
* �õ����Խ��
* @param unsigned int uiTestType ��������
* @param byte* pData ��������
* @return int ����ռ���ֽ��� 
*/
int CTestElementData::GetTestResult(unsigned int uiTestType, byte* pData)
{
	int iPosition = 0;
	memcpy(&pData[iPosition], &m_uiIP, 4);
	iPosition = iPosition + 4;
	switch(uiTestType)
	{
		// ��������
		// �������ԣ���������
	case 4:
		memcpy(&pData[iPosition], &m_fInstrumentNoiseValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_byInstrumentNoiseCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_byInstrumentCheck, 1);
		iPosition = iPosition + 1;
		break;
		// 	�������ԣ���������
	case 5:
		memcpy(&pData[iPosition], &m_fInstrumentDistortionValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_byInstrumentDistortionCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_byInstrumentCheck, 1);
		iPosition = iPosition + 1;
		break;
	// �������ԣ���������
	case 7:		
		memcpy(&pData[iPosition], &m_fInstrumentCrosstalkValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_byInstrumentCrosstalkCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_byInstrumentCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �������ԣ������������λ
	case 6:
		memcpy(&pData[iPosition], &m_fInstrumentGainValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_byInstrumentGainCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_fInstrumentPhaseValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_byInstrumentPhaseCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_byInstrumentGainAndPhaseCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_byInstrumentCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �������ԣ�������ģ
	case 8:
		memcpy(&pData[iPosition], &m_fInstrumentCMRRValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_byInstrumentCMRRCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_byInstrumentCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �첨������
		// �첨�����ԣ�Ұ�����
	case 15:
		memcpy(&pData[iPosition], &m_fSensorResistanceValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_bySensorResistanceCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_bySensorCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �첨�����ԣ�Ұ��©��
	case 14:
		memcpy(&pData[iPosition], &m_fSensorLeakageValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_bySensorLeakageCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_bySensorCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �첨�����ԣ�Ұ������
	case 1:
		memcpy(&pData[iPosition], &m_fSensorNoiseValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_bySensorNoiseCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_bySensorCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �첨�����ԣ�Ұ����б��
	case 20:
		memcpy(&pData[iPosition], &m_fSensorTiltValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_bySensorTiltCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_bySensorCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �첨�����ԣ�Ұ����б��ģʽ
	case 21:		
		memcpy(&pData[iPosition], &m_fSensorTiltModelValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_bySensorTiltModelCheck, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_bySensorCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �첨�����ԣ�Ұ���������
	case 22:		
		memcpy(&pData[iPosition], &m_fSensorNoiseMonitorValue, 4);
		iPosition = iPosition + 4;
		memcpy(&pData[iPosition], &m_bySensorNoiseMonitorCheck, 1);
		iPosition = iPosition + 1;
		break;
		// �첨�����ԣ��¼Ӽ첨���ĳ�ʼ����
	case 45:		
		memcpy(&pData[iPosition], &m_byTestOnField, 1);
		iPosition = iPosition + 1;
		memcpy(&pData[iPosition], &m_byOnFieldCheck, 1);
		iPosition = iPosition + 1;
		break;
	}
	return iPosition;
}