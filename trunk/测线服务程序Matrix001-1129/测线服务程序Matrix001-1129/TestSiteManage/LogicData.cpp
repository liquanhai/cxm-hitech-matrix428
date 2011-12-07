#include "StdAfx.h"
#include "LogicData.h"

CLogicData::CLogicData()
{
}

CLogicData::~CLogicData()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CLogicData::OnInit()
{
	// �������ļ�
	OpenIniXMLFile();

	// �������ö���
	m_oSurveySetupData.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
	m_oSurveySetupData.m_uiLineCountAll = m_uiLineCountAll;	// ������������	
	m_oSurveySetupData.m_uiPointCountAll = m_uiPointCountAll;	// �����������	
	m_oSurveySetupData.m_uiChannelCountAll = m_uiChannelCountAll;	// �����������
	m_oSurveySetupData.OnInit();

	// �������ö���
	m_oLayoutSetupData.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
	m_oLayoutSetupData.OnInit();
	// �����Ƶ㵽���Ͳ��
	SetMuteToCSurveySetupData(true);

	// Look���ö���
	m_oLookSetupData.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
	m_oLookSetupData.OnInit();

	// �������ö���
	m_oTestSetupData.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
	m_oTestSetupData.m_uiTestElementCountAll = m_uiTestElementCountAll;	// // ���Ե�Ԫ��������
	m_oTestSetupData.OnInit();

	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ����
* @param void
* @return void
*/
void CLogicData::OnReset()
{
	// �������ö���
	m_oSurveySetupData.OnReset();
	// �������ö���
	m_oTestSetupData.OnReset();
}

/**
* ���¼���
* @param void
* @return void
*/
void CLogicData::OnReload()
{
	// �������ļ�
	OpenIniXMLFile();

	// �������ö���
	m_oSurveySetupData.OnReload();
	// �������ö���
	m_oLayoutSetupData.OnReload();
	// Look���ö���
	m_oLookSetupData.OnReload();
	// �������ö���
	m_oTestSetupData.OnReload();

	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* �ر�
* @param void
* @return void
*/
void CLogicData::OnClose()
{
	// �������ö���
	m_oSurveySetupData.OnClose();
	// �������ö���
	m_oLayoutSetupData.OnClose();
	// Look���ö���
	m_oLookSetupData.OnClose();
	// �������ö���
	m_oTestSetupData.OnClose();
}

/**
* �������ļ�
* @param void
* @return void
*/
void CLogicData::OpenIniXMLFile()
{
	// ��FTP�������õ�Matrix�����ļ�
	GetMatrixIniFileFromFTPServer();

	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = "msxml2.domdocument";
	BOOL bData = m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

	oVariant = m_strIniFile;
	bData = m_oXMLDOMDocument.load(oVariant);
}

/**
* �ر������ļ�
* @param void
* @return void
*/
void CLogicData::CloseIniXMLFile()
{
	m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}

/**
* ��FTP�������õ�Matrix�����ļ�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CLogicData::GetMatrixIniFileFromFTPServer()
{
	bool bReturn = false;
	BOOL bData;
	int iCount = 0;
	CInternetSession oSession;
	CFtpConnection* pConnection = oSession.GetFtpConnection(m_strIPFTPServer);
	CString strFileSource = "";
	strFileSource = m_strIniFile.Right(m_strIniFile.GetLength() - 2);
	
	while(true)
	{
		bData = pConnection->GetFile(strFileSource, m_strIniFile, FALSE);
		if(TRUE == bData)
		{
			bReturn = true;
			break;
		}
		iCount++;
		if(4 <= iCount)
		{
			break;
		}
		Sleep(50);
	}
	pConnection->Close();
	delete pConnection;
	return bReturn;
}

/**
* ���ò��Ͳ�����Ƶ�����
* @param bool bValue �Ƿ����Ƶ� true���ǣ�false����
* @return void
*/
void CLogicData::SetMuteToCSurveySetupData(bool bValue)
{
	POSITION pos = NULL;
	CMuteData* pMuteData = NULL;
	CPointSetupData* pPointSetupData = NULL;
	CChannelSetupData* pChannelSetupData = NULL;
	pos = m_oLayoutSetupData.m_oMuteList.m_olsMute.GetHeadPosition();
	while(NULL != pos)
	{
		pMuteData = m_oLayoutSetupData.m_oMuteList.m_olsMute.GetNext(pos);
		pPointSetupData = m_oSurveySetupData.m_oPointList.GetPoint(pMuteData->m_uiLineName, pMuteData->m_uiPointNb);
		if(NULL != pPointSetupData)
		{
			pPointSetupData->m_bMute = bValue;
			pChannelSetupData = pPointSetupData->m_pChannelHead;
			while(true)
			{
				pChannelSetupData->m_bMute = bValue;
				if(pChannelSetupData == pPointSetupData->m_pChannelTail)
				{
					break;
				}
				pChannelSetupData = pChannelSetupData->m_pChannelRight;
			}
		}
	}
}

/**
* ���û���������Ŀ�����Բ������õĲ�������
* @param unsigned int uiTestNb ���������
* @return bool true���ɹ���false��ʧ��
*/
bool CLogicData::OnSetupTestProjectForTestBaseFromTestSetup(unsigned int uiTestNb)
{
	// ���ò�����Ŀ
	if(false == m_oTestSetupData.OnSetupTestProjectForTestBaseFromTestSetup(uiTestNb))
	{
		return false;
	}
	// �������IP��ַ����
	m_oTestSetupData.m_oTestProjectBase.m_olsIP.RemoveAll();

	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	if((1 == m_oTestSetupData.m_oTestProjectBase.m_uiProjectType) || (3 == m_oTestSetupData.m_oTestProjectBase.m_uiProjectType))
	{
		// �������У��õ�IP��ַ���У�������
		if(false == m_oLayoutSetupData.ParseSpreadToIPListByAuxiliaryDescr(&m_oTestSetupData.m_oTestProjectBase.m_olsIP, m_oTestSetupData.m_oTestProjectBase.m_strAuxiliaryDescr))
		{
			return false;
		}
	}

	// �������У��õ�IP��ַ���У��ɼ���
	if(false == m_oSurveySetupData.ParseSpreadToIPListByAbsoluteSpread(&m_oTestSetupData.m_oTestProjectBase.m_olsIP, m_oTestSetupData.m_oTestProjectBase.m_strAbsoluteSpread))
	{
		return false;
	}
	// �жϣ�û��Ҫ���ԵĲ��
	if(0 == m_oTestSetupData.m_oTestProjectBase.m_olsIP.GetCount())
	{
		return false;
	}
	// ���ò��Ե�Ԫ����������
	m_oTestSetupData.OnSetupTestElementBase();
	// ���ò������ݻ���������������
	m_oTestSetupData.OnSetupTestDataBufferBase();

	return true;
}

/**
* ���û���������Ŀ�����Բ�����ͼ�Ĳ�������
* @param unsigned int uiTestAim ����Ŀ��
* @param unsigned int uiTestType ��������
* @param CString strTestAbsoluteSpread ��������
* @return bool true���ɹ���false��ʧ��
*/
bool CLogicData::OnSetupTestProjectForTestBaseFromTestView(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread)
{
	// ���û���������Ŀ�����Բ���ͼ�εĲ�������
	if(false == m_oTestSetupData.OnSetupTestProjectForTestBaseFromTestView(uiTestAim, uiTestType, strTestAbsoluteSpread))
	{
		return false;
	}
	
	// �������IP��ַ����
	m_oTestSetupData.m_oTestProjectBase.m_olsIP.RemoveAll();

	// �������У��õ�IP��ַ���У��ɼ���
	if(false == m_oSurveySetupData.ParseSpreadToIPListByAbsoluteSpread(&m_oTestSetupData.m_oTestProjectBase.m_olsIP, m_oTestSetupData.m_oTestProjectBase.m_strAbsoluteSpread))
	{
		return false;
	}
	// �жϣ�û��Ҫ���ԵĲ��
	if(0 == m_oTestSetupData.m_oTestProjectBase.m_olsIP.GetCount())
	{
		return false;
	}
	// ���ò��Ե�Ԫ����������
	m_oTestSetupData.OnSetupTestElementBase();
	// ���ò������ݻ���������������
	m_oTestSetupData.OnSetupTestDataBufferBase();

	return true;
}

/**
* ���û���������Ŀ�������¼Ӽ첨���ĳ�ʼ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CLogicData::OnSetupTestProjectForSensorTestOnField()
{
	// �жϣ�����Ҫ����
	if((0 == m_oLookSetupData.m_uiTestResistance) && (0 == m_oLookSetupData.m_uiTestTilt) && (0 == m_oLookSetupData.m_uiTestLeakage))
	{
		return false;
	}
	// ���û���������Ŀ�������¼Ӽ첨���ĳ�ʼ����
	if(false == m_oTestSetupData.OnSetupTestProjectForSensorTestOnField(m_oLookSetupData.m_uiTestResistance, m_oLookSetupData.m_uiTestTilt, m_oLookSetupData.m_uiTestLeakage))
	{
		return false;
	}

	// �������IP��ַ����
	m_oTestSetupData.m_oTestProjectBase.m_olsIP.RemoveAll();

	// �õ�IP��ַ���У��μ��¼Ӽ첨���ĳ�ʼ����
	if(false == m_oSurveySetupData.GetIPListForSensorTestOnField(&m_oTestSetupData.m_oTestProjectBase.m_olsIP))
	{
		return false;
	}
	// �жϣ�û��Ҫ���ԵĲ��
	if(0 == m_oTestSetupData.m_oTestProjectBase.m_olsIP.GetCount())
	{
		return false;
	}
	// ���ò��Ե�Ԫ����������
	m_oTestSetupData.OnSetupTestElementBase();
	// ���ò������ݻ���������������
	m_oTestSetupData.OnSetupTestDataBufferBase();

	return true;
}

/**
* ����������������Ŀ�����Բ������õĲ�������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CLogicData::OnSetupTestProjectForTestNoiseFromTestSetup()
{
	// ���ò�����Ŀ
	if(false == m_oTestSetupData.OnSetupTestProjectForTestNoise())
	{
		return false;
	}

	m_oTestSetupData.m_oTestProjectNoise.m_olsIP.RemoveAll();
	// �������У��õ�IP��ַ���У��ɼ���
	if(false == m_oSurveySetupData.ParseSpreadToIPListByAbsoluteSpread(&m_oTestSetupData.m_oTestProjectNoise.m_olsIP, m_oTestSetupData.m_oTestProjectNoise.m_strAbsoluteSpread))
	{
		return false;
	}
	// �жϣ�û��Ҫ���ԵĲ��
	if(0 == m_oTestSetupData.m_oTestProjectNoise.m_olsIP.GetCount())
	{
		return false;
	}
	// ���ò��Ե�Ԫ���������
	m_oTestSetupData.OnSetupTestElementNoise();
	// ���ò������ݻ��������������
	m_oTestSetupData.OnSetupTestDataBufferNoise();

	return true;
}

/**
* ����������������Ŀ���������������ͼ�Ĳ�������
* @param CString strTestAbsoluteSpread ��������
* @return bool true���ɹ���false��ʧ��
*/
bool CLogicData::OnSetupTestProjectForTestNoiseFromTestView(CString strTestAbsoluteSpread)
{
	// ���ò�����Ŀ
	if(false == m_oTestSetupData.OnSetupTestProjectForTestNoise())
	{
		return false;
	}

	m_oTestSetupData.m_oTestProjectNoise.m_strAbsoluteSpread = strTestAbsoluteSpread;
	m_oTestSetupData.m_oTestProjectNoise.m_olsIP.RemoveAll();
	// �������У��õ�IP��ַ���У��ɼ���
	if(false == m_oSurveySetupData.ParseSpreadToIPListByAbsoluteSpread(&m_oTestSetupData.m_oTestProjectNoise.m_olsIP, m_oTestSetupData.m_oTestProjectNoise.m_strAbsoluteSpread))
	{
		return false;
	}
	// �жϣ�û��Ҫ���ԵĲ��
	if(0 == m_oTestSetupData.m_oTestProjectNoise.m_olsIP.GetCount())
	{
		return false;
	}
	// ���ò��Ե�Ԫ���������
	m_oTestSetupData.OnSetupTestElementNoise();
	// ���ò������ݻ��������������
	m_oTestSetupData.OnSetupTestDataBufferNoise();

	return true;
}

/**
* �����ɾ��������Ӧ���������SN��
* @param unsigned int uiIP ����IP��ַ
* @return void
*/
void CLogicData::ClearSNInChannelWhenInstrumentDelete(unsigned int uiIP)
{
	CChannelSetupData* pChannel = NULL;
	if(TRUE == m_oSurveySetupData.m_oChannelList.GetChannelFromMap(uiIP, pChannel))
	{
		pChannel->m_uiSN = 0;
	}
}

/**
* ���������ļ�����	SurveySetup��ApplyAll
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForSurveySetupApplyAll()
{
	// �������ļ�
	OpenIniXMLFile();
	// �������ö���
	m_oSurveySetupData.OnReload();
	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ���������ļ�����	SurveySetup��ApplySensor
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForSurveySetupApplySensor()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���������ļ�����	SurveySetup��ApplySensor
	m_oSurveySetupData.m_oSensorList.OnSetupDataChangeForSurveySetupApplySensor();
	// �ر������ļ�
	CloseIniXMLFile();	
}

/**
* ���������ļ�����	LayoutSetup��ApplyBlast
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForLayoutSetupApplyBlast()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���������ļ�����	LayoutSetup��ApplySensor
	m_oLayoutSetupData.m_oBlastMachineList.OnReload();
	// �ر������ļ�
	CloseIniXMLFile();	
}

/**
* ���������ļ�����	LayoutSetup��ApplyAux
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForLayoutSetupApplyAux()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���������ļ�����	LayoutSetup��ApplySensor
	m_oLayoutSetupData.m_oAuxList.OnReload();
	// �ر������ļ�
	CloseIniXMLFile();	
}

/**
* ���������ļ�����	LayoutSetup��ApplyMarkers
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForLayoutSetupApplyMarkers()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���������ļ�����	LayoutSetup��ApplySensor
	m_oLayoutSetupData.m_oMarkerList.OnReload();
	// �ر������ļ�
	CloseIniXMLFile();	
}

/**
* ���������ļ�����	LayoutSetup��ApplyDetour
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForLayoutSetupApplyDetour()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���������ļ�����	LayoutSetup��ApplySensor
	m_oLayoutSetupData.m_oDetourList.OnReload();
	// �ر������ļ�
	CloseIniXMLFile();	
}

/**
* ���������ļ�����	LayoutSetup��ApplyDetour
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForLayoutSetupApplyMute()
{
	// ������ڲ��Ͳ���ϵ��Ƶ���
	SetMuteToCSurveySetupData(false);	// �����Ƶ㵽���Ͳ��
	// �������ļ�
	OpenIniXMLFile();
	// ���������ļ�����	LayoutSetup��ApplySensor
	m_oLayoutSetupData.m_oMuteList.OnReload();
	// �ر������ļ�
	CloseIniXMLFile();
	// �������ò��Ͳ���ϵ��Ƶ���
	SetMuteToCSurveySetupData(true);	// �����Ƶ㵽���Ͳ��
}

/**
* ���������ļ�����	LookSetup��Apply
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForLookSetupApply()
{
	// �������ļ�
	OpenIniXMLFile();
	// Look���ö���
	m_oLookSetupData.OnReload();
	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ���������ļ�����	TestSetup��ApplyInstrument
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForTestSetupApplyInstrument()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���¼����������������ļ�
	m_oTestSetupData.m_oTestProjectList.OnReloadTestSetupDataForApplyInstrument();
	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ���������ļ�����	TestSetup��ApplySensor
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForTestSetupApplySensor()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���¼����������������ļ�
	m_oTestSetupData.m_oTestProjectList.OnReloadTestSetupDataForApplySensor();
	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ���������ļ�����	TestSetup��ApplyMultiple
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForTestSetupApplyMultiple()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���¼����������������ļ�
	m_oTestSetupData.m_oTestProjectList.OnReloadTestSetupDataForApplyMultiple();
	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ���������ļ�����	TestSetup��ApplySeisMonitor
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForTestSetupApplySeisMonitor()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���¼����������������ļ�
	m_oTestSetupData.m_oTestProjectList.OnReloadTestSetupDataForApplySeisMonitor();
	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ���������ļ�����	TestSetup��ApplyInstrumentTestBase
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForTestSetupApplyInstrumentTestBase()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���¼��ز��������ļ�
	m_oTestSetupData.m_oTestBaseListInstrument.OnReloadTestSetupDataForApplyTestBase();
	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ���������ļ�����	TestSetup��ApplySensorTestBase
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForTestSetupApplySensorTestBase()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���¼��ز��������ļ�
	m_oTestSetupData.m_oTestBaseListSensor.OnReloadTestSetupDataForApplyTestBase();
	// �ر������ļ�
	CloseIniXMLFile();
}


/**
* ���������ļ�����	TestSetup��ApplyInstrumentTestLimit
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForTestSetupApplyInstrumentTestLimit()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���¼��ز��������ļ�
	m_oTestSetupData.m_oTestLimitListInstrument.OnReloadTestSetupDataForApplyTestLimit();
	// �ر������ļ�
	CloseIniXMLFile();
}

/**
* ���������ļ�����	TestSetup��ApplySensorTestLimit
* @param void
* @return void
*/
void CLogicData::OnSetupDataChangeForTestSetupApplySensorTestLimit()
{
	// �������ļ�
	OpenIniXMLFile();
	// ���¼��ز��������ļ�
	m_oTestSetupData.m_oTestLimitListSensor.OnReloadTestSetupDataForApplyTestLimit();
	// �ر������ļ�
	CloseIniXMLFile();
}

// ���ò��Ե�Ԫ�����о�
void CLogicData::SetTestElementListLimit(unsigned int uiType)
{
	switch(uiType)
	{
		// ��������
		// ���ò��Ե�Ԫ�����оݣ��������ԣ���������
	case 4:
		SetTestElementListLimitInstrumentNoise();
		break;
		// 	���ò��Ե�Ԫ�����оݣ��������ԣ���������
	case 5:
		SetTestElementListLimitInstrumentDistortion();
		break;
		// ���ò��Ե�Ԫ�����оݣ��������ԣ���������
	case 7:
		SetTestElementListLimitInstrumentCrosstalk();
		break;
		// ���ò��Ե�Ԫ�����оݣ��������ԣ������������λ
	case 6:	
		SetTestElementListLimitInstrumentGainAndPhase();
		break;
		// ���ò��Ե�Ԫ�����оݣ��������ԣ�������ģ
	case 8:
		SetTestElementListLimitInstrumentCMRR();
		break;
		// �첨������
		// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ�����
	case 15:
		SetTestElementListLimitISensorResistance();
		break;
		// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ��©��
	case 14:
		SetTestElementListLimitISensorLeakage();
		break;
		// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ������
	case 1:
		SetTestElementListLimitISensorNoise();
		break;
		// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ����б��
	case 20:	
		SetTestElementListLimitISensorTilt();
		break;
		// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ����б��ģʽ
	case 21:
		SetTestElementListLimitISensorTiltModel();
		break;
	}
}

/**
* ���ò��Ե�Ԫ�����оݣ��������ԣ���������
* @param void
* @return void
*/
void CLogicData::SetTestElementListLimitInstrumentNoise()
{
	// �������������о�
	float fLimit = m_oTestSetupData.m_oTestLimitListInstrument.GetTestLimitValueByIndex(400);
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		// ��Ԫ�ڵ�Ԫ�����е�λ��
		m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fInstrumentNoiseLimit = fLimit;
	}
}

/**
* ���ò��Ե�Ԫ�����оݣ��������ԣ���������
* @param void
* @return void
*/
void CLogicData::SetTestElementListLimitInstrumentDistortion()
{
	// ������������о�
	float fLimit = m_oTestSetupData.m_oTestLimitListInstrument.GetTestLimitValueByIndex(500);
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		// ��Ԫ�ڵ�Ԫ�����е�λ��
		m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fInstrumentDistortionLimit = fLimit;
	}
}

/**
* ���ò��Ե�Ԫ�����оݣ��������ԣ���������
* @param void
* @return void
*/
void CLogicData::SetTestElementListLimitInstrumentCrosstalk()
{
	// �������������о�
	float fLimit = m_oTestSetupData.m_oTestLimitListInstrument.GetTestLimitValueByIndex(700);
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		// ��Ԫ�ڵ�Ԫ�����е�λ��
		m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fInstrumentCrosstalkLimit = fLimit;
	}
}

/**
* ���ò��Ե�Ԫ�����оݣ��������ԣ������������λ
* @param void
* @return void
*/
void CLogicData::SetTestElementListLimitInstrumentGainAndPhase()
{
	// ������������о�
	float fLimitGain = m_oTestSetupData.m_oTestLimitListInstrument.GetTestLimitValueByIndex(600);
	// ������λ�����о�
	float fLimitPhase = m_oTestSetupData.m_oTestLimitListInstrument.GetTestLimitValueByIndex(610);
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		// ��Ԫ�ڵ�Ԫ�����е�λ��
		m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fInstrumentGainLimit = fLimitGain;
		m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fInstrumentPhaseLimit = fLimitPhase;
	}
}

/**
* ���ò��Ե�Ԫ�����оݣ��������ԣ�������ģ
* @param void
* @return void
*/
void CLogicData::SetTestElementListLimitInstrumentCMRR()
{
	float fLimit = m_oTestSetupData.m_oTestLimitListInstrument.GetTestLimitValueByIndex(800);
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		// ��Ԫ�ڵ�Ԫ�����е�λ��
		m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fInstrumentCMRRLimit = fLimit;
	}
}

// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ�����
void CLogicData::SetTestElementListLimitISensorResistance()
{
	bool bValue = false;
	float fLimit = 0.0;
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		bValue = m_oSurveySetupData.GetTestLimitValue(1500, m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_uiIP, fLimit);
		if(true == bValue)
		{
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorResistanceLimitMin = fLimit;
		}
		else
		{
			fLimit = m_oTestSetupData.m_oTestLimitListSensor.GetTestLimitValueByIndex(1500);
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorResistanceLimitMin = fLimit;
		}

		bValue = m_oSurveySetupData.GetTestLimitValue(1501, m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_uiIP, fLimit);
		if(true == bValue)
		{
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorResistanceLimitMax = fLimit;
		}
		else
		{
			fLimit = m_oTestSetupData.m_oTestLimitListSensor.GetTestLimitValueByIndex(1501);
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorResistanceLimitMax = fLimit;
		}
	}
}

// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ��©��
void CLogicData::SetTestElementListLimitISensorLeakage()
{
	bool bValue = false;
	float fLimit = 0.0;
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		bValue = m_oSurveySetupData.GetTestLimitValue(1400, m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_uiIP, fLimit);
		if(true == bValue)
		{
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorLeakageLimit = fLimit;
		}
		else
		{
			fLimit = m_oTestSetupData.m_oTestLimitListSensor.GetTestLimitValueByIndex(1400);
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorLeakageLimit = fLimit;
		}
	}
}

// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ������
void CLogicData::SetTestElementListLimitISensorNoise()
{
	bool bValue = false;
	float fLimit = 0.0;
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		bValue = m_oSurveySetupData.GetTestLimitValue(100, m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_uiIP, fLimit);
		if(true == bValue)
		{
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorNoiseLimit = fLimit;
		}
		else
		{
			fLimit = m_oTestSetupData.m_oTestLimitListSensor.GetTestLimitValueByIndex(100);
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorNoiseLimit = fLimit;
		}
	}
}

// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ����б��
void CLogicData::SetTestElementListLimitISensorTilt()
{
	bool bValue = false;
	float fLimit = 0.0;
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		bValue = m_oSurveySetupData.GetTestLimitValue(2000, m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_uiIP, fLimit);
		if(true == bValue)
		{
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorTiltLimit = fLimit;
		}
		else
		{
			fLimit = m_oTestSetupData.m_oTestLimitListSensor.GetTestLimitValueByIndex(2000);
			m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorTiltLimit = fLimit;
		}
	}
}

// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ����б��ģʽ
void CLogicData::SetTestElementListLimitISensorTiltModel()
{
	float fLimit = 0.0;
	fLimit = m_oTestSetupData.m_oTestLimitListSensor.GetTestLimitValueByIndex(2100);
	for(unsigned int i = 0; i < m_oTestSetupData.m_oTestElementListBase.m_uiCountUsed; i++)
	{
		m_oTestSetupData.m_oTestElementListBase.m_pArrayTestElementData[i].m_fSensorTiltModelLimit = fLimit;
	}
}

/**
* ���ò��Խ������������
* @param int iTestType
* @param CTestElementList* pTestElementList
* @param bool bProcSensorTestOnField
* @return void
*/
void CLogicData::SetTestResultBase(int iTestType, CTestElementList* pTestElementList, bool bProcSensorTestOnField)
{
	CTestElementData* pTestElementData = NULL;
	CChannelSetupData* pChannel = NULL;
	for(unsigned int i = 0; i < pTestElementList->m_uiCountUsed; i++)
	{
		pTestElementData = pTestElementList->GetTestElementDataByIndex(i);
		pChannel = m_oSurveySetupData.GetChannel(pTestElementData->m_uiIP);
		if(NULL != pChannel)
		{
			switch(iTestType)
			{
				// �첨������
				// Ұ�����
			case 15:
				pChannel->m_fResistanceValue = pTestElementData->m_fSensorResistanceValue;
				pChannel->m_byResistanceCheck = pTestElementData->m_bySensorResistanceCheck;
				pChannel->m_fResistanceLimitMax = pTestElementData->m_fSensorResistanceLimitMax;
				pChannel->m_fResistanceLimitMin = pTestElementData->m_fSensorResistanceLimitMin;
				break;
				// Ұ��©��
			case 14:
				pChannel->m_fLeakageValue = pTestElementData->m_fSensorLeakageValue;
				pChannel->m_byLeakageCheck = pTestElementData->m_bySensorLeakageCheck;
				pChannel->m_fLeakageLimit = pTestElementData->m_fSensorLeakageLimit;
				break;
				// Ұ������
			case 1:
				pChannel->m_fNoiseValue = pTestElementData->m_fSensorNoiseValue;
				pChannel->m_byNoiseCheck = pTestElementData->m_bySensorNoiseCheck;
				pChannel->m_fNoiseLimit = pTestElementData->m_fSensorNoiseLimit;
				break;
				// Ұ����б��
			case 20:
				pChannel->m_fTiltValue = pTestElementData->m_fSensorTiltValue;
				pChannel->m_byTiltCheck = pTestElementData->m_bySensorTiltCheck;
				pChannel->m_fTiltLimit = pTestElementData->m_fSensorTiltLimit;
				break;
				// Ұ����б��ģʽ
			case 21:
				pChannel->m_fTiltModelValue = pTestElementData->m_fSensorTiltModelValue;
				pChannel->m_byTiltModelCheck = pTestElementData->m_bySensorTiltModelCheck;
				pChannel->m_fTiltModelLimit = pTestElementData->m_fSensorTiltModelLimit;
				break;
			}
			pChannel->CheckResultAll();
			pTestElementData->m_bySensorCheck = pChannel->m_byCheck;

			// �жϣ������¼Ӽ첨���ĳ�ʼ����
			if(true == bProcSensorTestOnField)
			{
				pChannel->CheckResultOnField(m_oLookSetupData.m_uiTestResistance, m_oLookSetupData.m_uiTestTilt, m_oLookSetupData.m_uiTestLeakage);
				pChannel->m_byTestOnField = 1;

				// �첨���Ƿ�����˳�ʼ����
				pTestElementData->m_byTestOnField = pChannel->m_byTestOnField;
				// ��ʼ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
				pTestElementData->m_byOnFieldCheck = pChannel->m_byOnFieldCheck;
			}
		}
	}
}