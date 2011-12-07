#include "StdAfx.h"
#include "TestSetupData.h"

CTestSetupData::CTestSetupData()
{
}

CTestSetupData::~CTestSetupData()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CTestSetupData::OnInit()
{
	// �������Ի�����������
	m_oTestBaseListInstrument.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oTestBaseListInstrument.m_uiAim = 1;	// ���Զ���	1-������2-�첨��
	m_oTestBaseListInstrument.OnInit();
	// �첨�����Ի�����������
	m_oTestBaseListSensor.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oTestBaseListSensor.m_uiAim = 2;	// ���Զ���	1-������2-�첨��
	m_oTestBaseListSensor.OnInit();

	// ���������оݲ�������
	m_oTestLimitListInstrument.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oTestLimitListInstrument.m_uiAim = 1;	// ���Զ���	1-������2-�첨��
	m_oTestLimitListInstrument.OnInit();
	// �첨�������оݲ�������
	m_oTestLimitListSensor.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oTestLimitListSensor.m_uiAim = 2;	// ���Զ���	1-������2-�첨��
	m_oTestLimitListSensor.OnInit();

	// ������Ŀ���ж���
	m_oTestProjectList.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oTestProjectList.m_pTestBaseListInstrument = &m_oTestBaseListInstrument;	// �������Ի�����������ָ��
	m_oTestProjectList.m_pTestBaseListSensor = &m_oTestBaseListSensor;	// �첨�����Ի�����������ָ��
	m_oTestProjectList.OnInit();
	
	// ���Ե�Ԫ���У���������
	m_oTestElementListBase.m_uiCountAll = m_uiTestElementCountAll;	// ���Ե�Ԫ��������
	m_oTestElementListBase.OnInit();
	// ���Ե�Ԫ���У��������
	m_oTestElementListNoise.m_uiCountAll = m_uiTestElementCountAll;	// ���Ե�Ԫ��������
	m_oTestElementListNoise.OnInit();
	// �������ݻ���������������
	m_oTestDataBufferBase.m_uiTestElementCountAll = m_uiTestElementCountAll;	// ���Ե�Ԫ��������
	m_oTestDataBufferBase.OnInit();
	// �������ݻ��������������
	m_oTestDataBufferNoise.m_uiTestElementCountAll = m_uiTestElementCountAll;	// ���Ե�Ԫ��������
	m_oTestDataBufferNoise.OnInit();

	// ������Ŀ���ж��󣬻�������
	m_oTestProjectBase.m_pTestBaseListInstrument = &m_oTestBaseListInstrument;
	m_oTestProjectBase.m_pTestBaseListSensor = &m_oTestBaseListSensor;
	// ������Ŀ���ж����������
	m_oTestProjectNoise.m_pTestBaseListInstrument = &m_oTestBaseListInstrument;
	m_oTestProjectNoise.m_pTestBaseListSensor = &m_oTestBaseListSensor;
}	

/**
* ����
* @param void
* @return void
*/
void CTestSetupData::OnReset()
{
	// ������Ŀ���ж����������
	m_oTestProjectNoise.OnReset();
}

/**
* ���¼���
* @param void
* @return void
*/
void CTestSetupData::OnReload()
{
	// �������Ի�����������
	m_oTestBaseListInstrument.OnReload();
	// �첨�����Ի�����������
	m_oTestBaseListSensor.OnReload();

	// ���������оݲ�������
	m_oTestLimitListInstrument.OnReload();
	// �첨�������оݲ�������
	m_oTestLimitListSensor.OnReload();

	// ������Ŀ���ж���
	m_oTestProjectList.OnReload();
	// ���Ե�Ԫ���У���������
	m_oTestElementListBase.OnReset();
	// ���Ե�Ԫ���У��������
	m_oTestElementListNoise.OnReset();
	// �������ݻ���������������
	m_oTestDataBufferBase.OnReset();
	// �������ݻ��������������
	m_oTestDataBufferNoise.OnReset();
}

/**
* �ر�
* @param void
* @return void
*/
void CTestSetupData::OnClose()
{
	// �������Ի�����������
	m_oTestBaseListInstrument.OnClose();
	// �첨�����Ի�����������
	m_oTestBaseListSensor.OnClose();

	// ���������оݲ�������
	m_oTestLimitListInstrument.OnClose();
	// �첨�������оݲ�������
	m_oTestLimitListSensor.OnClose();

	// ������Ŀ���ж���
	m_oTestProjectList.OnClose();
	// ���Ե�Ԫ���У���������
	m_oTestElementListBase.OnClose();
	// ���Ե�Ԫ���У��������
	m_oTestElementListNoise.OnClose();
	// �������ݻ���������������
	m_oTestDataBufferBase.OnClose();
	// �������ݻ��������������
	m_oTestDataBufferNoise.OnClose();
}

/**
* ���û���������Ŀ�����Բ������õĲ�������
* @param unsigned int uiTestNb ���Ժ�
* @return bool true���ɹ���false��ʧ��
*/
bool CTestSetupData::OnSetupTestProjectForTestBaseFromTestSetup(unsigned int uiTestNb)
{
	// ������Ŀ������
	if(FALSE == m_oTestProjectList.IfIndexExistInMap(uiTestNb))
	{
		return false;
	}
	// �õ�������Ŀ
	CTestProject* pTestProject = NULL;
	m_oTestProjectList.GetTestProject(uiTestNb, pTestProject);
	// ���Ʋ�����Ŀ
	m_oTestProjectBase.OnReset();	// ������Ŀ���ж��󣬻�������
	m_oTestProjectBase.Clone(pTestProject);

	return true;
}

/**
* ���û���������Ŀ�����Բ���ͼ�εĲ�������
* @param unsigned int uiTestAim ������Ŀ���� 1-�������ԣ�2-�첨������
* @param unsigned int uiTestType ��������
* @param unsigned CString strTestAbsoluteSpread ��������
* @return bool true���ɹ���false��ʧ��
*/
bool CTestSetupData::OnSetupTestProjectForTestBaseFromTestView(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread)
{
	// ���Ʋ�����Ŀ
	m_oTestProjectBase.OnReset();	// ������Ŀ���ж��󣬻�������
	m_oTestProjectBase.m_uiProjectType = uiTestAim;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	if(1 == uiTestAim)
	{
		m_oTestProjectBase.m_uiTestNb = 1000;
	}
	else if(2 == uiTestAim)
	{
		m_oTestProjectBase.m_uiTestNb = 2000;
	}	
	m_oTestProjectBase.m_uiRecordResult = 0;	// �Ƿ��¼��������  0-����¼��1-��¼
	m_oTestProjectBase.m_uiRecordLength  = 0;	// ���Լ�¼ʱ�䣨���룩
	m_oTestProjectBase.m_strAuxiliaryDescr = "";	// ����������
	m_oTestProjectBase.m_strAbsoluteSpread = strTestAbsoluteSpread;	// �������ж���
	m_oTestProjectBase.m_uiDelayBetweenTest = 0;	// ÿ�β���֮��ļ�������룩

	// ���ò�����Ŀ�����Բ�����ͼ
	m_oTestProjectBase.SetupTestProjectFromView(uiTestAim, uiTestType);

	return true;
}

/**
* ���û���������Ŀ�������¼Ӽ첨���ĳ�ʼ����
* @param UINT uiTestResistance �������Ƿ����Resistance
* @param UINT uiTestTilt �������Ƿ����Tilt
* @param UINT uiTestLeakage �������Ƿ����Leakage
* @return bool true���ɹ���false��ʧ��
*/
bool CTestSetupData::OnSetupTestProjectForSensorTestOnField(UINT uiTestResistance, UINT uiTestTilt, UINT uiTestLeakage)
{
	// ���Ʋ�����Ŀ
	m_oTestProjectBase.OnReset();	// ������Ŀ���ж��󣬻�������
	m_oTestProjectBase.m_uiProjectType = 2;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	m_oTestProjectBase.m_uiTestNb = 2000;	
	m_oTestProjectBase.m_uiRecordResult = 0;	// �Ƿ��¼��������  0-����¼��1-��¼
	m_oTestProjectBase.m_uiRecordLength  = 0;	// ���Լ�¼ʱ�䣨���룩
	m_oTestProjectBase.m_strAuxiliaryDescr = "";	// ����������
	m_oTestProjectBase.m_strAbsoluteSpread = "";	// �������ж���
	m_oTestProjectBase.m_uiDelayBetweenTest = 1000;	// ÿ�β���֮��ļ�������룩

	// ���ò�����Ŀ�������¼Ӽ첨���ĳ�ʼ����
	m_oTestProjectBase.SetupTestProjectForSensorTestOnField(uiTestResistance, uiTestTilt, uiTestLeakage);

	return true;
}

/**
* �������������Ŀ
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CTestSetupData::OnSetupTestProjectForTestNoise()
{
	// ������Ŀ������
	if(FALSE == m_oTestProjectList.IfIndexExistInMap(4000))
	{
		return false;
	}
	// �õ�������Ŀ
	CTestProject* pTestProject = NULL;
	m_oTestProjectList.GetTestProject(4000, pTestProject);
	// ���Ʋ�����Ŀ
	m_oTestProjectNoise.OnReset();	// ������Ŀ���ж���
	m_oTestProjectNoise.Clone(pTestProject);

	return true;
}

/**
* ���ò��Ե�Ԫ����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CTestSetupData::OnSetupTestElementBase()
{
	m_oTestElementListBase.OnReset();

	int iIPCount;	// IP��ַ����
	unsigned int uiIP;	// IP��ַ
	int iIndex = 0;
	iIPCount = m_oTestProjectBase.m_olsIP.GetCount();
	m_oTestElementListBase.m_uiCountUsed = iIPCount;
	while(false == m_oTestProjectBase.m_olsIP.IsEmpty())
	{
		uiIP = m_oTestProjectBase.m_olsIP.RemoveHead();
		m_oTestElementListBase.m_pArrayTestElementData[iIndex].m_uiIP = uiIP;
		m_oTestElementListBase.m_pArrayTestElementData[iIndex].m_bInUsed = true;
		// ����һ����Ԫ��������
		m_oTestElementListBase.AddTestElementDataToMap(uiIP, &m_oTestElementListBase.m_pArrayTestElementData[iIndex]);
		iIndex++;
	}
	return true;
}

/**
* ���ò��Ե�Ԫ���������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CTestSetupData::OnSetupTestElementNoise()
{
	m_oTestElementListNoise.OnReset();

	int iIPCount;	// IP��ַ����
	unsigned int uiIP;	// IP��ַ
	int iIndex = 0;
	iIPCount = m_oTestProjectNoise.m_olsIP.GetCount();
	m_oTestElementListNoise.m_uiCountUsed = iIPCount;
	while(false == m_oTestProjectNoise.m_olsIP.IsEmpty())
	{
		uiIP = m_oTestProjectNoise.m_olsIP.RemoveHead();
		m_oTestElementListNoise.m_pArrayTestElementData[iIndex].m_uiIP = uiIP;
		m_oTestElementListNoise.m_pArrayTestElementData[iIndex].m_bInUsed = true;
		// ����һ����Ԫ��������
		m_oTestElementListNoise.AddTestElementDataToMap(uiIP, &m_oTestElementListNoise.m_pArrayTestElementData[iIndex]);
		iIndex++;
	}
	return true;
}

/**
* ���ò������ݻ���������������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CTestSetupData::OnSetupTestDataBufferBase()
{
	m_oTestDataBufferBase.OnReset();
	// ��������
	m_oTestDataBufferBase.OnTestSetup(m_oTestElementListBase.m_uiCountUsed);
	return true;
}

/**
* ���ò������ݻ��������������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CTestSetupData::OnSetupTestDataBufferNoise()
{
	m_oTestDataBufferNoise.OnReset();
	// ��������
	m_oTestDataBufferNoise.OnTestSetup(m_oTestElementListNoise.m_uiCountUsed);
	return true;
}