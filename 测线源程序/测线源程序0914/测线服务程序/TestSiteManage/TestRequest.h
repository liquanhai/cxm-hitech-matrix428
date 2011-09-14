#pragma once

/**
*@brief ����������
*
@note �������ͣ�
@note 0 ������¼��
@note 1 Ұ��������Noise
@note 2 Ұ�����塣Pluse
@note 3 Ұ�⴮����Crosstalk
@note 4 ����������Noise
@note 5 �������䡣Distortion
@note 6 ��������/ ��λ��Gain/Phase
@note 7 ����������Crosstalk
@note 8 ������ģ��Common Mode Rejection
@note 9 �ϳɡ�
@note 10 һ���ԣ����� CM408����
@note 11 �������塣Pluse
@note 12 Ұ����䡣Distortion
@note 13 ����������
@note 14 Ұ��©�硣Leakage
@note 15 Ұ����衣Resistance

@note 16 �������衣Resistance
@note 17 ����©�硣Leakage
@note 18 ������б�ȡ�Tilt
@note 19 ������б��ģʽ��Tilt Model
@note 20 Ұ����б�ȡ�Tilt
@note 21 Ұ����б��ģʽ��Tilt Model
@note 22 Ұ��������⡣

@note ��������
@note ���� CMRR ����
@note �ο���ѹ�����޽�ͨ�����ϵ�Դ��ʹ�� TMS428 ʱ��
@note �첨����б�Ȳ���
@note �첨�� CMRR ���ԣ����� LT428 �� TMS428��

@note 30 ����ȫ��������Ŀ
@note 40 �첨��ȫ��������Ŀ
@note 45 �¼Ӽ첨���ĳ�ʼ����
@note 50 �����ͼ첨��ȫ��������Ŀ
@note 60 ���Կ���

@note �������������п�ѡ������
@note 4 ���� Noise
@note 5 ���� Distortion
@note 7 ���� Crosstalk
@note 6 ���� Gain/Phase ���
@note 8 Common Mode Rejection

@note �첨�����������п�ѡ������
@note 15 Resistance(ohms) �˲����������鿴�Ƿ������˼첨�������������û�ѡ��
@note 14 �첨�� Leakage(Mohms) �˲�����ʾ�����豸��·����������֮��Ĵ��©����衣���������û�ѡ��
@note 1 �첨�� Noise��΢���� �ڴ˲����У�½�ϼ첨���������Ұ��������ͨ�������޵����������ݲɼ��������ġ����������û�ѡ��
@note 20 Tilt(%) ��б�Ȳ���
@note 21 Tilt Model ��бģ�͹������ڸ�����֪��������ά��״̬�ļ���½�ϼ첨��@note ���У����洢��½�ϼ첨���������Ӧ��ģ�͡�
*/
class CTestRequest
{
public:
	CTestRequest();
	~CTestRequest();

public: //����
	/** ������*/
	unsigned int m_uiIndex;
	/** ���Զ���	1-������2-�첨����3-ȫ��*/
	unsigned int m_uiAim;
	/** ��������*/
	unsigned int m_uiType;
	/** ����*/
	unsigned int m_uiGain;
	/** ��ת����������*/
	unsigned int m_uiLoopNb;
	/** ѭ������*/
	unsigned int m_uiLoopCount;

	/** AD�ɼ���ʼʱ��*/
	unsigned int m_uiTimeADBegin;
	/** �ɼ���ʼʱ��*/
	unsigned int m_uiTimeCollectBegin;
	/** �ɼ�����ʱ��*/
	unsigned int m_uiTimeCollectEnd;

public: //����
	// ����
	void OnReset();
	// ����XML����������
	void ParseXMLForInstrument(CXMLDOMElement* pElement);
	// ����XML���첨������
	void ParseXMLForSensor(CXMLDOMElement* pElement);
	// ����XML�����ϲ���
	void ParseXMLForMultiple(CXMLDOMElement* pElement);
};
