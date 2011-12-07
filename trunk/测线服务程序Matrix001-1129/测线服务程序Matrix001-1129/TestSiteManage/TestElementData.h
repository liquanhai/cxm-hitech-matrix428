#pragma once

/**
*@brief ���Ե�Ԫ������
*/
class CTestElementData
{
public:
	CTestElementData();
	~CTestElementData();

public: //����	
	/** �������е�λ��*/
	unsigned int m_uiIndex;
	/** �Ƿ�ʹ����*/
	bool m_bInUsed;	
	/** IP��ַ*/
	unsigned int m_uiIP;
	/** ����������λ����*/
	unsigned int m_uiDataStep;
	/** ֡����*/
	unsigned int m_uiFrameIndex;
	/** ��һ�ε���������*/
	unsigned int m_uiDataIndexPreview;
	/** ��һ�ε���������*/
	unsigned int m_uiDataBegin;
	/** ��֡��������*/
	unsigned int IndexPreview;
	/** �ɼ��Ĵ���*/
	unsigned char ofccheck[6];
	// ADC�����������
	unsigned int m_uiADCSetOperationNb;

	/** ������������ֵ*/
	float m_fInstrumentNoiseValue;
	/** �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byInstrumentNoiseCheck;
	/** �������������о�*/
	float m_fInstrumentNoiseLimit;

	/** �����������ֵ*/
	float m_fInstrumentDistortionValue;
	/** ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byInstrumentDistortionCheck;
	/** ������������о�*/
	float m_fInstrumentDistortionLimit;

	/** ������������ֵ*/
	float m_fInstrumentCrosstalkValue;
	/** �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byInstrumentCrosstalkCheck;
	/** �������������о�*/
	float m_fInstrumentCrosstalkLimit;

	/** �����������ֵ*/
	float m_fInstrumentGainValue;
	/** ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byInstrumentGainCheck;
	/** ������������о�*/
	float m_fInstrumentGainLimit;
	/** ������λ����ֵ*/
	float m_fInstrumentPhaseValue;
	/** ������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byInstrumentPhaseCheck;
	/** ������λ�����о�*/
	float m_fInstrumentPhaseLimit;
	/** �����������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byInstrumentGainAndPhaseCheck;

	/** ������ģ����ֵ*/
	float m_fInstrumentCMRRValue;
	/** ������ģ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byInstrumentCMRRCheck;
	/** ������ģ�����о�*/
	float m_fInstrumentCMRRLimit;

	/** �������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byInstrumentCheck;

	/** Ұ��������ֵ*/
	float m_fSensorResistanceValue;
	/** Ұ�������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_bySensorResistanceCheck;
	/** Ұ���������оݣ�����*/
	float m_fSensorResistanceLimitMin;
	/** Ұ���������оݣ�����*/
	float m_fSensorResistanceLimitMax;

	/** Ұ��©�����ֵ*/
	float m_fSensorLeakageValue;
	/** Ұ��©����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_bySensorLeakageCheck;
	/** Ұ��©������о�*/
	float m_fSensorLeakageLimit;

	/** Ұ����������ֵ*/
	float m_fSensorNoiseValue;
	/** Ұ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_bySensorNoiseCheck;
	/** Ұ�����������о�*/
	float m_fSensorNoiseLimit;

	/** Ұ����б�Ȳ���ֵ*/
	float m_fSensorTiltValue;
	/** Ұ����б�Ȳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_bySensorTiltCheck;	
	/** Ұ����б�Ȳ����о�*/
	float m_fSensorTiltLimit;

	/** Ұ����б��ģ�Ͳ���ֵ*/
	float m_fSensorTiltModelValue;
	/** Ұ����б��ģ�Ͳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_bySensorTiltModelCheck;
	/** Ұ����б��ģ�Ͳ����о�*/
	float m_fSensorTiltModelLimit;

	/** Ұ����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_bySensorCheck;

	/** ����������ֵ*/
	float m_fSensorNoiseMonitorValue;
	/** ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_bySensorNoiseMonitorCheck;

	/** �첨���Ƿ�����˳�ʼ����*/
	byte m_byTestOnField;
	/** ��ʼ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byOnFieldCheck;
	/** ����������ɼ���*/
	int m_uigroupendcount;

public: //����
	// ����
	void Reset();
	// ���ò���
	void ResetTest();
	// ���ã�Ϊһ���µĲ�������
	void ResetForNewTestRequest();
	// ����õ����Խ��
	void CalculateTestResult(unsigned int uiTestType, byte* pData, unsigned int uiSamplingPointCount,float);
	//���������
	float MeanSquare(byte* pData,unsigned int uiSamplingPointCount);
	// �ж����Խ��
	void JudgeTestResult(unsigned int uiTestType);
	// �õ����Խ��
	int GetTestResult(unsigned int uiTestType, byte* pData);
};
