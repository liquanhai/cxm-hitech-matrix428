
#include "stdafx.h"
#include "SiteData.h"

CSiteData::CSiteData(void)
{
	m_uiInstrumentCountAll = 20000;	// ����������������	
	m_uiChannelCountAll = 20000;	// �������

	// ���ڲ�����ͨѶ�ı���IP��ַ
	m_strIPForInterface = "192.168.0.11";
	// ���ڿͻ����ڲ�����������յ����޶˿ں�
	m_uiPortForCmdRev = 0x6200;
	// ���ڿͻ����ڲ���������͵���Դ�˿ں�
	m_uiPortForCmdSend = 0x6400;
	// ���ڷ������ڲ���������͵����޶˿ںţ����߷�����
	m_uiPortForCmdSendToServer = 0x6000;
	// ���ڷ������ڲ���������͵����޶˿ںţ�ʩ���ͻ���
	m_uiPortForCmdSendToOperation = 0xC010;
	// ���ڿͻ����ڲ��������ݽ��յ����޶˿ں�
	m_uiPortForDataRev = 0x6300;
}

CSiteData::~CSiteData(void)
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CSiteData::OnInit()
{
	// ��ʼ��SegdCode����
	InitSegdCodeList();
	// ��ʼ��BoxType����
	InitBoxTypeList();
	// ��ʼ��Gain����
	InitGainList();
	// ��ʼ��Orientation����
	InitOrientationList();
	// ��ʼ��FilterType����
	InitFilterTypeList();
	// ��ʼ��ADCType����
	InitADCTypeList();
	// ��ʼ��DACType����
	InitDACTypeList();

	//���ز��߷�����������������
	LoadLineServerAppSetupData();

	// �ֳ��������ݶ���
	m_oInstrumentList.m_uiCountAll = m_uiInstrumentCountAll;	// ����������������	
	m_oInstrumentList.OnInit();	// ��ʼ��

	// ·�ɶ��г�ʼ��
	m_oRoutList.OnInit();	// ��ʼ��

	// �ֳ�������ݶ��г�ʼ��
	m_oChannelList.m_uiCountAll = m_uiChannelCountAll;	// �������
	m_oChannelList.OnInit();	// ��ʼ��

	// ����ͼ����ͼ����ͼ�ε�Ԫ����
	m_oGraphInstrumentList.m_uiCountAll = m_uiChannelCountAll;	// ��������
	m_oGraphInstrumentList.m_pInstrumentList = &m_oInstrumentList;
	m_oGraphInstrumentList.OnInit();	// ��ʼ��

	// �첨��ͼ����ͼ�첨��ͼ�ε�Ԫ����
	m_oGraphSensorList.m_uiCountAll = m_uiChannelCountAll;	// �������
	m_oGraphSensorList.m_pChannelList = &m_oChannelList;
	m_oGraphSensorList.OnInit();	// ��ʼ��

	// ��FTP�������õ�Matrix�����ļ�
	GetMatrixIniFileFromFTPServer();

	// �������ļ�
	OpenMatrixIniXMLFile();
		// �������ö���
		m_oLineList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oLineList.OnInit();	// ��ʼ��
		// ��������ö���
		m_oPointCodeList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oPointCodeList.OnInit();	// ��ʼ��
		// �첨�����ö���
		m_oSensorList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oSensorList.OnInit();	// ��ʼ��

		// ��ǵ����ö���
		m_oMarkerList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oMarkerList.OnInit();	// ��ʼ��
		// ���������ö���
		m_oAuxList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oAuxList.OnInit();	// ��ʼ��
		// ��ը�����������ö���
		m_oBlastMachineList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oBlastMachineList.OnInit();	// ��ʼ��
		// �ػص����ö���
		m_oDetourList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oDetourList.OnInit();	// ��ʼ��
		// �Ƶ����ö���
		m_oMuteList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oMuteList.OnInit();	// ��ʼ��

		// �����������ö���
		m_oSpreadAbsoluteList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oSpreadAbsoluteList.OnInit();	// ��ʼ��
		// ����������ö���
		m_oSpreadGenericList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oSpreadGenericList.OnInit();	// ��ʼ��

		// �ڵ���������
		m_oShotPointMap.m_pXMLDOMDocument = &m_oXMLDOMDocument;

		// �������Ի����������У�����
		m_oTestBaseListInstrument.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
		m_oTestBaseListInstrument.m_uiAim = 1;	// ���Զ���	1-������2-�첨����3-ȫ��
		m_oTestBaseListInstrument.OnInit();
		// �첨�����Ի����������У��첨��
		m_oTestBaseListSensor.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
		m_oTestBaseListSensor.m_uiAim = 2;	// ���Զ���	1-������2-�첨����3-ȫ��
		m_oTestBaseListSensor.OnInit();

		// ���������оݲ������У�����
		m_oTestLimitListInstrument.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
		m_oTestLimitListInstrument.m_uiAim = 1;	// ���Զ���	1-������2-�첨��
		m_oTestLimitListInstrument.OnInit();
		// �첨�������оݲ������У��첨��
		m_oTestLimitListSensor.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
		m_oTestLimitListSensor.m_uiAim = 2;	// ���Զ���	1-������2-�첨��
		m_oTestLimitListSensor.OnInit();

		// �������ö��У���������
		m_oTestProjectListInstrument.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
		m_oTestProjectListInstrument.m_uiProjectType = 1;	 // ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		m_oTestProjectListInstrument.OnInit();
		// �������ö��У��첨������
		m_oTestProjectListSensor.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
		m_oTestProjectListSensor.m_uiProjectType = 2;	 // ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		m_oTestProjectListSensor.OnInit();
		// �������ö��У��첨������
		m_oTestProjectListMultiple.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
		m_oTestProjectListMultiple.m_uiProjectType = 3;	 // ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		m_oTestProjectListMultiple.OnInit();
		// �������ö��У��첨������
		m_oTestProjectListSeisMonitor.m_pXMLDOMDocument = &m_oXMLDOMDocument;	// XMLDOM�ļ�����
		m_oTestProjectListSeisMonitor.m_uiProjectType = 4;	 // ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		m_oTestProjectListSeisMonitor.OnInit();

		// FormLine���ö���
		m_oFormLineList.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oFormLineList.OnInit();	// ��ʼ��

		// Look���ö���
		m_oLookSetupData.m_pXMLDOMDocument = &m_oXMLDOMDocument;
		m_oLookSetupData.OnInit();	// ��ʼ��
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ��ʼ��TestType����
	InitTestTypeList();
	// ��ʼ�����ϲ������ƶ���
	InitMultipleTestNameList();


	// �����ͻ����ڲ���������ʹ����������
	m_oSocketInterfaceCmdSend.OnInit(m_strIPForInterface, m_uiPortForCmdSend, m_uiPortForCmdSendToServer, m_uiPortForCmdSendToOperation);	
	m_oSocketInterfaceCmdSend.SetBufferSize(65536 * 10);	// ��ʼ������˿ڽ��ջ�������С	

	// �����ͻ����ڲ���������֡���պʹ������	
	m_oSocketInterfaceCmdRev.OnInit(m_strIPForInterface, m_uiPortForCmdRev);	
	m_oSocketInterfaceCmdRev.SetBufferSize(65536 * 10);	// ��ʼ������˿ڽ��ջ�������С

	// �����ͻ����ڲ���������֡���պʹ������	
	m_oSocketInterfaceDataRev.OnInit(m_strIPForInterface, m_uiPortForDataRev);	
	m_oSocketInterfaceDataRev.SetBufferSize(65536 * 10);	// ��ʼ������˿ڽ��ջ�������С
}

/**
* ����
* @param void
* @return void
*/
void CSiteData::OnReset()
{
	m_oInstrumentList.OnReset();
	m_oRoutList.OnReset();
	m_oChannelList.OnReset();

	m_oGraphInstrumentList.OnReset();
	m_oGraphSensorList.OnReset();
}

/**
* �ر�
* @param void
* @return void
*/
void CSiteData::OnClose()
{
	// ���SegdCode����
	CleanSegdCodeList();
	// ���BoxType����
	CleanBoxTypeList();
	// ���Gain����
	CleanGainList();
	// ���Orientation����
	CleanOrientationList();
	// ���FilterType����
	CleanFilterTypeList();
	// ���ADCType����
	CleanADCTypeList();
	// ���DACType����
	CleanDACTypeList();
	// ���TestType����
	CleanTestTypeList();
	// ���MultipleTestName����
	CleanMultipleTestNameList();

	m_oInstrumentList.OnClose();
	m_oRoutList.OnClose();
	m_oChannelList.OnClose();

	m_oGraphInstrumentList.OnClose();
	m_oGraphSensorList.OnClose();

	// �������ö���
	m_oLineList.OnClose();
	// ��������ö���
	m_oPointCodeList.OnClose();	
	// �첨�����ö���
	m_oSensorList.OnClose();

	// ��ǵ����ö���
	m_oMarkerList.OnClose();
	// ���������ö���
	m_oAuxList.OnClose();
	// ��ը�����������ö���
	m_oBlastMachineList.OnClose();
	// �ػص����ö���
	m_oDetourList.OnClose();
	// �Ƶ����ö���
	m_oMuteList.OnClose();

	// �����������ö���
	m_oSpreadAbsoluteList.OnClose();
	// ����������ö���
	m_oSpreadGenericList.OnClose();

	// �������Ի����������У�����
	m_oTestBaseListInstrument.OnClose();
	// �첨�����Ի����������У��첨��
	m_oTestBaseListSensor.OnClose();

	// �������ö��У���������
	m_oTestProjectListInstrument.OnClose();
	// �������ö��У��첨������
	m_oTestProjectListSensor.OnClose();
	// �������ö��У��첨������
	m_oTestProjectListMultiple.OnClose();
	// �������ö��У��첨������
	m_oTestProjectListSeisMonitor.OnClose();

	// FormLine���ö���
	m_oFormLineList.OnClose();
}

/**
* ��ʼ��SegdCode����
* @param void
* @return void
*/
void CSiteData::InitSegdCodeList()
{
	CString strSegdCode;

	strSegdCode = "0:Not defined";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "1:Hydrophone";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "2:Geophone vertical";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "3:Geophone horizontal inline";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "4:Geophone horizontal cross-inline";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "5:Geophone horizontal other";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "6:Accelerometer vertical";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "7:Accelerometer horizontal inline";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "8:Accelerometer horizontal cross-inline";
	m_olsSegdCode.AddTail(strSegdCode);

	strSegdCode = "9:Accelerometer horizontal other";
	m_olsSegdCode.AddTail(strSegdCode);
}

/**
* ���SegdCode����
* @param void
* @return void
*/
void CSiteData::CleanSegdCodeList()
{
	m_olsSegdCode.RemoveAll();
}

/**
* �õ�SegdCode�ַ���
* @param unsigned int uiSegdCode SegdCode
* @return CString SegdCode�ַ���
*/
CString CSiteData::GetSegdCodeStringByID(unsigned int uiSegdCode)
{
	POSITION pos;
	CString strSegdCode = "";
	pos = m_olsSegdCode.FindIndex(uiSegdCode);
	if(NULL != pos)
	{
		strSegdCode = m_olsSegdCode.GetAt(pos);
	}

	return strSegdCode;
}

/**
* �õ�SegdCodeID
* @param CString strSegdCode SegdCode�ַ���
* @return unsigned int SegdCodeID 0���޶�ӦSegdCodeID
*/
unsigned int CSiteData::GetSegdCodeIDByString(CString strSegdCode)
{
	unsigned int uiSegdCode = 0;
	POSITION pos;
	pos = m_olsSegdCode.Find(strSegdCode);
	if(NULL != pos)
	{
		CString strSegdCode = m_olsSegdCode.GetAt(pos);
		strSegdCode = strSegdCode.Left(1);
		uiSegdCode = CXMLDOMTool::ConvertStringToUnsignedInt(strSegdCode);
	}
	return uiSegdCode;
}

/**
* ��ʼ��BoxType����
* @param void
* @return void
*/
void CSiteData::InitBoxTypeList()
{
	CString strBoxType;

	strBoxType = "1:LAUX";
	m_olsBoxType.AddTail(strBoxType);

	strBoxType = "2:LAUL";
	m_olsBoxType.AddTail(strBoxType);

	strBoxType = "3:FDU";
	m_olsBoxType.AddTail(strBoxType);
}

/**
* ���BoxType����
* @param void
* @return void
*/
void CSiteData::CleanBoxTypeList()
{
	m_olsBoxType.RemoveAll();
}

/**
* �õ�BoxType�ַ���
* @param unsigned int uiBoxType BoxType
* @return CString BoxType�ַ���
*/
CString CSiteData::GetBoxTypeStringByID(unsigned int uiBoxType)
{
	POSITION pos;
	CString strBoxType = "";
	pos = m_olsBoxType.FindIndex(uiBoxType - 1);
	if(NULL != pos)
	{
		strBoxType = m_olsBoxType.GetAt(pos);
	}

	return strBoxType;
}

/**
* �õ�BoxTypeID
* @param CString strBoxType BoxType�ַ���
* @return unsigned int BoxTypeID 0���޶�ӦBoxTypeID
*/
unsigned int CSiteData::GetBoxTypeIDByString(CString strBoxType)
{
	unsigned int uiBoxType = 0;
	POSITION pos;
	pos = m_olsBoxType.Find(strBoxType);
	if(NULL != pos)
	{
		CString strBoxType = m_olsBoxType.GetAt(pos);
		strBoxType = strBoxType.Left(1);
		uiBoxType = CXMLDOMTool::ConvertStringToUnsignedInt(strBoxType);
	}
	return uiBoxType;
}

/**
* ��ʼ��Gain����
* @param void
* @return void
*/
void CSiteData::InitGainList()
{
	CString strGain;

	strGain = "1600: g1";
	m_olsGain.AddTail(strGain);

	strGain = "400: g2";
	m_olsGain.AddTail(strGain);
}

/**
* ���Gain����
* @param void
* @return void
*/
void CSiteData::CleanGainList()
{
	m_olsGain.RemoveAll();
}

/**
* �õ�Gain�ַ���
* @param unsigned int uiGain Gain
* @return CString Gain�ַ���
*/
CString CSiteData::GetGainStringByGainData(unsigned int uiGain)
{
	POSITION pos;
	CString strGain = "";
	int iIndex = -1;
	if(1600 == uiGain)
	{
		iIndex = 0;
	}
	else if(400 == uiGain)
	{
		iIndex = 1;
	}
	if(-1 != iIndex)
	{
		pos = m_olsGain.FindIndex(iIndex);
		if(NULL != pos)
		{
			strGain = m_olsGain.GetAt(pos);
		}
	}
	return strGain;
}

/**
* �õ�Gain
* @param CString strGain Gain�ַ���
* @return unsigned int Gain 0���޶�ӦGain
*/
unsigned int CSiteData::GetGainByString(CString strGain)
{
	int iPos = strGain.Find(':');
	CString strData = strGain.Left(iPos);	
	unsigned int uiGain = CXMLDOMTool::ConvertStringToUnsignedInt(strData);
	return uiGain;
}

/**
* ��ʼ��Orientation����
* @param void
* @return void
*/
void CSiteData::InitOrientationList()
{
	CString strOrientation;

	strOrientation = "1:Top";
	m_olsOrientation.AddTail(strOrientation);

	strOrientation = "2:Down";
	m_olsOrientation.AddTail(strOrientation);

	strOrientation = "3:Left";
	m_olsOrientation.AddTail(strOrientation);
	
	strOrientation = "4:Right";
	m_olsOrientation.AddTail(strOrientation);	
}

/**
* ���Orientation����
* @param void
* @return void
*/
void CSiteData::CleanOrientationList()
{
	m_olsOrientation.RemoveAll();
}

/**
* �õ�Orientation�ַ���
* @param unsigned int uiOrientation Orientation
* @return CString Orientation�ַ���
*/
CString CSiteData::GetOrientationStringByID(unsigned int uiOrientation)
{
	POSITION pos;
	CString strOrientation = "";
	pos = m_olsOrientation.FindIndex(uiOrientation - 1);
	if(NULL != pos)
	{
		strOrientation = m_olsOrientation.GetAt(pos);
	}

	return strOrientation;
}

/**
* �õ�OrientationID
* @param CString strOrientation Orientation�ַ���
* @return unsigned int OrientationID 0���޶�ӦOrientationID
*/
unsigned int CSiteData::GetOrientationIDByString(CString strOrientation)
{
	unsigned int uiOrientation = 0;
	POSITION pos;
	pos = m_olsOrientation.Find(strOrientation);
	if(NULL != pos)
	{
		CString strOrientation = m_olsOrientation.GetAt(pos);
		strOrientation = strOrientation.Left(1);
		uiOrientation = CXMLDOMTool::ConvertStringToUnsignedInt(strOrientation);
	}
	return uiOrientation;
}

/**
* ��ʼ��FilterType����
* @param void
* @return void
*/
void CSiteData::InitFilterTypeList()
{
	CString strFilterType;

	strFilterType = "1:0.8 LIN";
	m_olsFilterType.AddTail(strFilterType);

	strFilterType = "2:0.8 MIN";
	m_olsFilterType.AddTail(strFilterType);
}

/**
* ���FilterType����
* @param void
* @return void
*/
void CSiteData::CleanFilterTypeList()
{
	m_olsFilterType.RemoveAll();
}

/**
* �õ�FilterType�ַ���
* @param unsigned int uiFilterType FilterType
* @return CString FilterType�ַ���
*/
CString CSiteData::GetFilterTypeStringByID(unsigned int uiFilterType)
{
	POSITION pos;
	CString strFilterType = "";
	pos = m_olsFilterType.FindIndex(uiFilterType - 1);
	if(NULL != pos)
	{
		strFilterType = m_olsFilterType.GetAt(pos);
	}

	return strFilterType;
}

/**
* �õ�FilterTypeID
* @param CString strFilterType FilterType�ַ���
* @return unsigned int FilterTypeID 0���޶�ӦFilterTypeID
*/
unsigned int CSiteData::GetFilterTypeIDByString(CString strFilterType)
{
	unsigned int uiFilterType = 0;
	POSITION pos;
	pos = m_olsFilterType.Find(strFilterType);
	if(NULL != pos)
	{
		CString strFilterType = m_olsFilterType.GetAt(pos);
		strFilterType = strFilterType.Left(1);
		uiFilterType = CXMLDOMTool::ConvertStringToUnsignedInt(strFilterType);
	}
	return uiFilterType;
}

/**
* ��ʼ��ADCType����
* @param void
* @return void
*/
void CSiteData::InitADCTypeList()
{
	CString strADCType;

	strADCType = "0:Close";
	m_olsADCType.AddTail(strADCType);

	strADCType = "1:Inner";
	m_olsADCType.AddTail(strADCType);
	
	strADCType = "2:Out";
	m_olsADCType.AddTail(strADCType);	
}

/**
* ���ADCType����
* @param void
* @return void
*/
void CSiteData::CleanADCTypeList()
{
	m_olsADCType.RemoveAll();
}

/**
* �õ�ADCType�ַ���
* @param unsigned int uiADCType ADCType
* @return CString ADCType�ַ���
*/
CString CSiteData::GetADCTypeStringByID(unsigned int uiADCType)
{
	POSITION pos;
	CString strADCType = "";
	pos = m_olsADCType.FindIndex(uiADCType);
	if(NULL != pos)
	{
		strADCType = m_olsADCType.GetAt(pos);
	}

	return strADCType;
}

/**
* �õ�ADCTypeID
* @param CString strADCType ADCType�ַ���
* @return unsigned int ADCTypeID 0���޶�ӦADCTypeID
*/
unsigned int CSiteData::GetADCTypeIDByString(CString strADCType)
{
	unsigned int uiADCType = 0;
	POSITION pos;
	pos = m_olsADCType.Find(strADCType);
	if(NULL != pos)
	{
		CString strADCType = m_olsADCType.GetAt(pos);
		strADCType = strADCType.Left(1);
		uiADCType = CXMLDOMTool::ConvertStringToUnsignedInt(strADCType);
	}
	return uiADCType;
}

/**
* ��ʼ��DACType����
* @param void
* @return void
*/
void CSiteData::InitDACTypeList()
{
	CString strDACType;

	strDACType = "0:Close";
	m_olsDACType.AddTail(strDACType);

	strDACType = "1:Inner";
	m_olsDACType.AddTail(strDACType);
	
	strDACType = "2:Out";
	m_olsDACType.AddTail(strDACType);	
}

/**
* ���DACType����
* @param void
* @return void
*/
void CSiteData::CleanDACTypeList()
{
	m_olsDACType.RemoveAll();
}

/**
* �õ�DACType�ַ���
* @param unsigned int uiDACType DACType
* @return CString DACType�ַ���
*/
CString CSiteData::GetDACTypeStringByID(unsigned int uiDACType)
{
	POSITION pos;
	CString strDACType = "";
	pos = m_olsDACType.FindIndex(uiDACType);
	if(NULL != pos)
	{
		strDACType = m_olsDACType.GetAt(pos);
	}

	return strDACType;
}

/**
* �õ�DACTypeID
* @param CString strDACType DACType�ַ���
* @return unsigned int DACTypeID 0���޶�ӦDACTypeID
*/
unsigned int CSiteData::GetDACTypeIDByString(CString strDACType)
{
	unsigned int uiDACType = 0;
	POSITION pos;
	pos = m_olsDACType.Find(strDACType);
	if(NULL != pos)
	{
		CString strDACType = m_olsDACType.GetAt(pos);
		strDACType = strDACType.Left(1);
		uiDACType = CXMLDOMTool::ConvertStringToUnsignedInt(strDACType);
	}
	return uiDACType;
}

/**
* ��ʼ��TestType����
* @param void
* @return void
*/
void CSiteData::InitTestTypeList()
{
	CString strTestType;
	unsigned int uiTestType;
	POSITION pos = NULL;
	CTestBaseData oTestBaseData;
	unsigned int i;
	for(i = 0; i < m_oTestBaseListInstrument.m_uiCountAll; i++)
	{
		pos = m_oTestBaseListInstrument.m_olsTestBase.FindIndex(i);
		oTestBaseData = m_oTestBaseListInstrument.m_olsTestBase.GetAt(pos);
		strTestType = oTestBaseData.m_strDesc;
		uiTestType = oTestBaseData.m_uiType;
		m_olsTestTypeInstrument.AddTail(strTestType);
		m_olsTestTypeAll.AddTail(strTestType);
		m_oTestTypeMapString.SetAt(strTestType, (void*)uiTestType);
		m_oTestTypeMapID.SetAt(uiTestType, strTestType);
	}
	strTestType = "ALL INSTRUMENT TEST";
	uiTestType = 30;
	m_olsTestTypeInstrument.AddTail(strTestType);
	m_oTestTypeMapString.SetAt(strTestType, (void*)uiTestType);
	m_oTestTypeMapID.SetAt(uiTestType, strTestType);
	for(i = 0; i < (m_oTestBaseListSensor.m_uiCountAll - 1); i++)
	{
		pos = m_oTestBaseListSensor.m_olsTestBase.FindIndex(i);
		oTestBaseData = m_oTestBaseListSensor.m_olsTestBase.GetAt(pos);
		strTestType = oTestBaseData.m_strDesc;
		uiTestType = oTestBaseData.m_uiType;
		m_olsTestTypeSensor.AddTail(strTestType);
		m_olsTestTypeAll.AddTail(strTestType);
		m_oTestTypeMapString.SetAt(strTestType, (void*)uiTestType);
		m_oTestTypeMapID.SetAt(uiTestType, strTestType);
	}
	pos = m_oTestBaseListSensor.m_olsTestBase.FindIndex(m_oTestBaseListSensor.m_uiCountAll - 1);
	oTestBaseData = m_oTestBaseListSensor.m_olsTestBase.GetAt(pos);
	strTestType = oTestBaseData.m_strDesc;
	uiTestType = oTestBaseData.m_uiType;
	m_oTestTypeMapString.SetAt(strTestType, (void*)uiTestType);
	m_oTestTypeMapID.SetAt(uiTestType, strTestType);

	strTestType = "ALL SENSOR TEST";
	uiTestType = 40;
	m_olsTestTypeSensor.AddTail(strTestType);
	m_oTestTypeMapString.SetAt(strTestType, (void*)uiTestType);
	m_oTestTypeMapID.SetAt(uiTestType, strTestType);

	strTestType = "ALL INSTRUMENT TEST";
	uiTestType = 30;
	m_olsTestTypeAll.AddTail(strTestType);
	strTestType = "ALL SENSOR TEST";
	uiTestType = 40;
	m_olsTestTypeAll.AddTail(strTestType);
	strTestType = "ALL TEST";
	uiTestType = 50;
	m_olsTestTypeAll.AddTail(strTestType);
	m_oTestTypeMapString.SetAt(strTestType, (void*)uiTestType);
	m_oTestTypeMapID.SetAt(uiTestType, strTestType);
	strTestType = "CONTROL LOOP";
	uiTestType = 60;
	m_olsTestTypeAll.AddTail(strTestType);
	m_oTestTypeMapString.SetAt(strTestType, (void*)uiTestType);
	m_oTestTypeMapID.SetAt(uiTestType, strTestType);
}

/**
* ���TestType����
* @param void
* @return void
*/
void CSiteData::CleanTestTypeList()
{
	m_olsTestTypeInstrument.RemoveAll();
	m_olsTestTypeSensor.RemoveAll();
	m_olsTestTypeAll.RemoveAll();
	m_oTestTypeMapString.RemoveAll();
	m_oTestTypeMapID.RemoveAll();
}

/**
* �õ�TestType�ַ���
* @param unsigned int uiTestType TestType
* @return CString TestType�ַ���
*/
CString CSiteData::GetTestTypeStringByID(unsigned int uiTestType)
{
	CString strTestType;
	if(TRUE == m_oTestTypeMapID.Lookup(uiTestType, strTestType))
	{
		return strTestType;
	}
	return "";
}

/**
* �õ�TestTypeID
* @param CString strTestType TestType�ַ���
* @return unsigned int TestTypeID 0���޶�ӦTestTypeID
*/
unsigned int CSiteData::GetTestTypeIDByString(CString strTestType)
{
	void* uiTestType;
	if(TRUE == m_oTestTypeMapString.Lookup(strTestType, uiTestType))
	{
		return (unsigned int)uiTestType;
	}
	return 0;
}

/**
* �õ�����TestType�о��ַ���
* @param unsigned int uiTestType TestType
* @return CString TestType�ַ���
*/
CString CSiteData::GetInsarumentTestTypeLimitStringByID(unsigned int uiTestType)
{
	CString strTestType = "";
	CTestLimitData oTestLimitData;
	unsigned int uiTestLimitNb = 0;
	switch(uiTestType)
	{
	case 4:	// ��������
		uiTestLimitNb = 400;
		break;
	case 5:	// ��������
		uiTestLimitNb = 500;
		break;
	case 7:	// ��������
		uiTestLimitNb = 700;
		break;
	case 8:	// ������ģ
		uiTestLimitNb = 800;
		break;
	}
	if(TRUE == m_oTestLimitListInstrument.m_oTestLimitDataMap.Lookup(uiTestLimitNb, oTestLimitData))
	{
		strTestType.Format("%3.2f%s", oTestLimitData.m_fLimit, oTestLimitData.m_strUnit);
		return strTestType;
	}

	// �жϣ�����/��λ����
	if(6 == uiTestType)
	{
		CString strTestTypeGain = "";
		CString strTestTypePhase = "";
		uiTestLimitNb = 600;
		if(TRUE == m_oTestLimitListInstrument.m_oTestLimitDataMap.Lookup(uiTestLimitNb, oTestLimitData))
		{
			strTestTypeGain.Format("%s:%3.2f%s", oTestLimitData.m_strDesc, oTestLimitData.m_fLimit, oTestLimitData.m_strUnit);
		}
		uiTestLimitNb = 610;
		if(TRUE == m_oTestLimitListInstrument.m_oTestLimitDataMap.Lookup(uiTestLimitNb, oTestLimitData))
		{
			strTestTypePhase.Format("%s:%3.2f%s", oTestLimitData.m_strDesc, oTestLimitData.m_fLimit, oTestLimitData.m_strUnit);
		}
		strTestType.Format("%s  %s", strTestTypeGain, strTestTypePhase);
		return strTestType;
	}

	return "";
}

/**
* �õ��첨��TestType�о��ַ���
* @param unsigned int uiTestType TestType
* @return CString TestLimit�ַ���
*/
CString CSiteData::GetSensorTestTypeLimitStringByID(unsigned int uiTestType)
{
	CString strTestLimit = "";
	CTestLimitData oTestLimitData;
	unsigned int uiTestLimitNb = 0;
	switch(uiTestType)
	{
	case 14:	// �첨��©��
		uiTestLimitNb = 1400;
		break;
	case 1:	// �첨������
		uiTestLimitNb = 100;
		break;
	case 20:	// �첨����б��
		uiTestLimitNb = 2000;
		break;
	case 21:	// �첨����б��ģ��
		uiTestLimitNb = 2100;
		break;
	case 22:	// �첨���������
		uiTestLimitNb = 2200;
		break;
	}
	if(TRUE == m_oTestLimitListSensor.m_oTestLimitDataMap.Lookup(uiTestLimitNb, oTestLimitData))
	{
		strTestLimit.Format("%3.2f%s", oTestLimitData.m_fLimit, oTestLimitData.m_strUnit);
		return strTestLimit;
	}
	// �жϣ��첨������
	if(15 == uiTestType)
	{
		CString strTestLimitLow = "";
		CString strTestLimitHight = "";
		uiTestLimitNb = 1500;
		if(TRUE == m_oTestLimitListSensor.m_oTestLimitDataMap.Lookup(uiTestLimitNb, oTestLimitData))
		{
			strTestLimitLow.Format("%3.2f", oTestLimitData.m_fLimit);
		}
		uiTestLimitNb = 1501;
		if(TRUE == m_oTestLimitListSensor.m_oTestLimitDataMap.Lookup(uiTestLimitNb, oTestLimitData))
		{
			strTestLimitHight.Format("%3.2f%s", oTestLimitData.m_fLimit, oTestLimitData.m_strUnit);
			strTestLimit.Format("%s-%s", strTestLimitLow, strTestLimitHight);
		}
		return strTestLimit;
	}
	return "";
}

/**
* �õ���������о�
* @param void
* @return float ��������о�
*/
float CSiteData::GetSeismonitorLimit()
{
	float fTestLimit = -66.0;
	CTestLimitData oTestLimitData;
	if(TRUE == m_oTestLimitListSensor.m_oTestLimitDataMap.Lookup(2200, oTestLimitData))
	{
		fTestLimit = oTestLimitData.m_fLimit;
	}
	return fTestLimit;
}

/**
* �õ�����TestType��λ�ַ���
* @param unsigned int uiTestType TestType
* @param unsigned int iSubItem ������
* @return CString TestType��λ�ַ���
*/
CString CSiteData::GetInsarumentTestTypeUnitStringByID(unsigned int uiTestType, int iSubItem)
{
	CString strTestUnit = "";
	CTestLimitData oTestLimitData;
	unsigned int uiTestLimitNb = 0;
	switch(uiTestType)
	{
	case 4:	// ��������
		uiTestLimitNb = 400;
		break;
	case 5:	// ��������
		uiTestLimitNb = 500;
		break;
	case 7:	// ��������
		uiTestLimitNb = 700;
		break;
	case 6:	// ��������/��λ
		// �жϣ�����
		if(1 == iSubItem)
		{
			uiTestLimitNb = 600;
		}
		// �жϣ���λ
		else if(2 == iSubItem)
		{
			uiTestLimitNb = 610;
		}
		break;
	case 8:	// ������ģ
		uiTestLimitNb = 800;
		break;
	}
	if(TRUE == m_oTestLimitListInstrument.m_oTestLimitDataMap.Lookup(uiTestLimitNb, oTestLimitData))
	{
		strTestUnit = oTestLimitData.m_strUnit;
	}
	return strTestUnit;
}

/**
* �õ��첨��TestType��λ�ַ���
* @param unsigned int uiTestType TestType
* @return CString TestType��λ�ַ���
*/
CString CSiteData::GetSensorTestTypeUnitStringByID(unsigned int uiTestType)
{
	CString strTestUnit = "";
	CTestLimitData oTestLimitData;
	unsigned int uiTestLimitNb = 0;
	switch(uiTestType)
	{
	case 15:	// �첨������
		uiTestLimitNb = 1500;
		break;
	case 14:	// �첨��©��
		uiTestLimitNb = 1400;
		break;
	case 1:	// �첨������
		uiTestLimitNb = 100;
		break;
	case 20:	// �첨����б��
		uiTestLimitNb = 2000;
		break;
	case 21:	// �첨����б��ģ��
		uiTestLimitNb = 2100;
		break;
	case 22:	// �첨���������
		uiTestLimitNb = 2200;
		break;
	}
	if(TRUE == m_oTestLimitListSensor.m_oTestLimitDataMap.Lookup(uiTestLimitNb, oTestLimitData))
	{
		strTestUnit = oTestLimitData.m_strUnit;
	}
	return strTestUnit;
}

// ��ʼ�����ϲ������ƶ���
void CSiteData::InitMultipleTestNameList()
{
	POSITION pos = NULL;
	CTestProject* pTestProject;
	for(unsigned int i = 0; i < m_oTestProjectListMultiple.m_uiCountAll; i++)
	{
		pos = m_oTestProjectListMultiple.m_olsTestProject.FindIndex(i);
		pTestProject = m_oTestProjectListMultiple.m_olsTestProject.GetAt(pos);
		m_olsMultipleTestName.AddTail(pTestProject->m_strTestName);
	}
}

// ���MultipleTestName����
void CSiteData::CleanMultipleTestNameList()
{
	m_olsMultipleTestName.RemoveAll();
}

/**
* ��FTP�������õ�Matrix�����ļ�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CSiteData::GetMatrixIniFileFromFTPServer()
{
	bool bReturn = false;
	BOOL bData;
	int iCount = 0;
	CInternetSession oSession;
	CFtpConnection* pConnection = oSession.GetFtpConnection(m_strIPFTPServer);
	
	while(true)
	{
		bData = pConnection->GetFile("\\parameter\\Matrix.xml", "..\\parameter\\Matrix.xml", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD);
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
* ����Matrix�����ļ���FTP������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CSiteData::SaveMatrixIniFileToFTPServer()
{
	bool bReturn = false;
	BOOL bData;
	int iCount = 0;
	CInternetSession oSession;
	CFtpConnection* pConnection = oSession.GetFtpConnection(m_strIPFTPServer);
	
	while(true)
	{
		bData = pConnection->PutFile("..\\parameter\\Matrix.xml", "parameter\\Matrix.xml");
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
* ��FTP�������õ������ļ�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CSiteData::GetDataFileFromFTPServer()
{
	bool bReturn = false;
	CInternetSession oSession;
	BOOL bData;
	CFtpConnection* pConnection = oSession.GetFtpConnection(m_strIPFTPServer);

	bData = GetDataFileFromFTPServer(pConnection, "\\data\\FileInstrument.dat", "..\\data\\FileInstrument.dat");
	if(TRUE == bData)
	{
		bData = GetDataFileFromFTPServer(pConnection, "\\data\\FileRout.dat", "..\\data\\FileRout.dat");
		if(TRUE == bData)
		{
			bData = GetDataFileFromFTPServer(pConnection, "\\data\\FileChannel.dat", "..\\data\\FileChannel.dat");
			if(TRUE == bData)
			{
				bReturn = true;
			}
		}
	}
	pConnection->Close();
	delete pConnection;
	return bReturn;
}

/**
* ��FTP�������õ������ļ�
* @param CFtpConnection* pConnection FTP����
* @param CString strFileSource Դ�ļ���
* @param CString strFileAim Ŀ���ļ���
* @return bool true���ɹ���false��ʧ��
*/
bool CSiteData::GetDataFileFromFTPServer(CFtpConnection* pConnection, CString strFileSource, CString strFileAim)
{
	BOOL bData;
	int iCount = 0;
	while(true)
	{
		bData = pConnection->GetFile(strFileSource, strFileAim, FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD);
		if(TRUE == bData)
		{
			return true;
		}
		iCount++;
		if(4 <= iCount)
		{
			return false;
		}
		Sleep(50);
	}
	return false;
}

/**
* �����ֳ�����
* @param void
* @return void
*/
void CSiteData::LoadSiteData()
{
	// ��FTP�������õ������ļ�
	GetDataFileFromFTPServer();

	// �����ֳ��������ݶ���
	m_oInstrumentList.LoadSiteData();
	// ����·�ɶ���
	m_oRoutList.LoadSiteData();
	// �����ֳ�������ݶ���
	m_oChannelList.LoadSiteData();

	// ��������ͼ����ͼ����ͼ�ε�Ԫ����
	m_oGraphInstrumentList.LoadSiteData();
	// ���ؼ첨��ͼ����ͼ�첨��ͼ�ε�Ԫ����
	m_oGraphSensorList.LoadSiteData();
}

/**
* ��������	100-�ֳ������������֪ͨ����
* @param void
* @return void
*/
void CSiteData::ProcInterSiteDataOutputCMD()
{
	OnReset();

	// ��FTP�������õ������ļ�
	GetDataFileFromFTPServer();

	// �����ֳ��������ݶ���
	m_oInstrumentList.LoadSiteData();
	// ����·�ɶ���
	m_oRoutList.LoadSiteData();
	// �����ֳ�������ݶ���
	m_oChannelList.LoadSiteData();

	// ��������ͼ����ͼ����ͼ�ε�Ԫ����
	m_oGraphInstrumentList.LoadSiteData();
	// ���ؼ첨��ͼ����ͼ�첨��ͼ�ε�Ԫ����
	m_oGraphSensorList.LoadSiteData();
}

/**
* �򿪳��������ļ�
* @param void
* @return void
*/
void CSiteData::OpenAppIniXMLFile()
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = "msxml2.domdocument";
	BOOL bData = m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

	oVariant = "..\\parameter\\MatrixLineApp.xml";
	bData = m_oXMLDOMDocument.load(oVariant);
}

/**
* �رճ��������ļ�
* @param void
* @return void
*/
void CSiteData::CloseAppIniXMLFile()
{
	m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}

/**
* �������ļ�
* @param void
* @return void
*/
void CSiteData::OpenMatrixIniXMLFile()
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = "msxml2.domdocument";
	BOOL bData = m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

	oVariant = "..\\parameter\\Matrix.xml";
	bData = m_oXMLDOMDocument.load(oVariant);
}

/**
* �ر������ļ�
* @param void
* @return void
*/
void CSiteData::CloseMatrixIniXMLFile()
{
	m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CSiteData::SaveMatrixIniXMLFile()
{
	COleVariant oVariant;
	oVariant = "..\\parameter\\Matrix.xml";
	m_oXMLDOMDocument.save(oVariant);
}

/**
* ���ز��߷�����������������
* @param void
* @return void
*/
void CSiteData::LoadLineServerAppSetupData()
{
	// �򿪳��������ļ�
	OpenAppIniXMLFile();

	//����IP��ַ��������
	LoadIPSetupData();
	//���ض˿���������
	LoadPortSetupData();
	//�������ݻ�������С����
	LoadBufferSizeSetupData();

	// �رճ��������ļ�
	CloseAppIniXMLFile();
}

/**
* ����IP��ַ��������
* @param void
* @return void
*/
void CSiteData::LoadIPSetupData()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�IP��ַ������
	strKey = "LineClientAppIPSetup";
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	strKey = "IPFTPServer";
	m_strIPFTPServer = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);

	strKey = "IPForInterface";
	m_strIPForInterface = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
}

/**
* ���ض˿���������
* @param void
* @return void
*/
void CSiteData::LoadPortSetupData(void)
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�IP��ַ������
	strKey = "LineClientAppPortSetup";
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	strKey = "PortForCmdRev";
	m_uiPortForCmdRev = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = "PortForCmdSend";
	m_uiPortForCmdSend = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = "PortForCmdSendToServer";
	m_uiPortForCmdSendToServer = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = "PortForCmdSendToOperation";
	m_uiPortForCmdSendToOperation = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = "PortForDataRev";
	m_uiPortForDataRev = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
}

/**
* �������ݻ�������С����
* @param void
* @return void
*/
void CSiteData::LoadBufferSizeSetupData(void)
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ����ݻ�������С������
	strKey = "LineClientAppBufferSizeSetup";
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	strKey = "InstrumentCountAll";
	m_uiInstrumentCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = "ChannelCountAll";
	m_uiChannelCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
}

/**
* ���ص�����������
* @param void
* @return void
*/
void CSiteData::OnLoadSurveySetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �������ö���
		m_oLineList.OnReload();
		// ��������ö���
		m_oPointCodeList.OnReload();
		// �첨�����ö���
		m_oSensorList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ��������������ݣ�ApplyAll
* @param void
* @return void
*/
void CSiteData::OnApplyAllSurveySetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �������ö���
		m_oLineList.OnSave();
		// ��������ö���
		m_oPointCodeList.OnSave();
		// �첨�����ö���
		m_oSensorList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* ��������������ݣ�ApplySensor
* @param void
* @return void
*/
void CSiteData::OnApplySensorSurveySetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
	// �첨�����ö���
	m_oSensorList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* ���͵�������ApplyAll֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyAllSurveySetupData()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	1-SurveySetup��ApplyAll
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(1);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���͵�������ApplySensor֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplySensorSurveySetupData()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	2-SurveySetup��ApplySensor
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(2);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���ز�����������
* @param void
* @return void
*/
void CSiteData::OnLoadLayoutSetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ��ǵ����ö���
		m_oMarkerList.OnReload();
		// ���������ö���
		m_oAuxList.OnReload();
		// ��ը�����������ö���
		m_oBlastMachineList.OnReload();
		// �ػص����ö���
		m_oDetourList.OnReload();
		// �Ƶ����ö���
		m_oMuteList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ���ر�ǵ���������
* @param void
* @return void
*/
void CSiteData::OnLoadLayoutSetupDataOfMarker()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ��ǵ����ö���
		m_oMarkerList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ���ظ�������������
* @param void
* @return void
*/
void CSiteData::OnLoadLayoutSetupDataOfAux()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ���������ö���
		m_oAuxList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ���ر�ը����������������
* @param void
* @return void
*/
void CSiteData::OnLoadLayoutSetupDataOfBlastMachine()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ��ը�����������ö���
		m_oBlastMachineList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* �����ػص���������
* @param void
* @return void
*/
void CSiteData::OnLoadLayoutSetupDataOfDetour()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �ػص����ö���
		m_oDetourList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* �����Ƶ���������
* @param void
* @return void
*/
void CSiteData::OnLoadLayoutSetupDataOfMute()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �Ƶ����ö���
		m_oMuteList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* Apply��ǵ���������
* @param void
* @return void
*/
void CSiteData::OnApplyLayoutSetupDataOfMarker()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ��ǵ����ö���
		m_oMarkerList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* Apply��������������
* @param void
* @return void
*/
void CSiteData::OnApplyLayoutSetupDataOfAux()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ���������ö���
		m_oAuxList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();

	::PostMessage(HWND_BROADCAST, WM_NEWXMLFILE , MATRIX_LINE, MATRIX_LINE_AUXI);
}

/**
* Apply��ը����������������
* @param void
* @return void
*/
void CSiteData::OnApplyLayoutSetupDataOfBlastMachine()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ��ը�����������ö���
		m_oBlastMachineList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* Apply�ػص���������
* @param void
* @return void
*/
void CSiteData::OnApplyLayoutSetupDataOfDetour()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �ػص����ö���
		m_oDetourList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* Apply�Ƶ���������
* @param void
* @return void
*/
void CSiteData::OnApplyLayoutSetupDataOfMute()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �Ƶ����ö���
		m_oMuteList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* ���ͱ�ǵ��������ݱ仯֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyLayoutSetupDataOfMarker()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	12-LayoutSetup��ApplyMarkers
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(12);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���͸������������ݱ仯֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyLayoutSetupDataOfAux()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	13-LayoutSetup��ApplyAux
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(13);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���ͱ�ը���������������ݱ仯֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyLayoutSetupDataOfBlastMachine()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	11-LayoutSetup��ApplyBlast
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(11);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* �����ػص��������ݱ仯֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyLayoutSetupDataOfDetour()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	14-LayoutSetup��ApplyDetour
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(14);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* �����Ƶ��������ݱ仯֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyLayoutSetupDataOfMute()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	15-LayoutSetup��ApplyMute
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(15);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ����������������
* @param void
* @return void
*/
void CSiteData::OnLoadSpreadSetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �����������ö���
		m_oSpreadAbsoluteList.OnReload();
		// ����������ö���
		m_oSpreadGenericList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}
/**
* �����ڵ�����еĶ�Ӧ��ϵ����
* @param void
* @return void
*/
void CSiteData::OnLoadShotPointSetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �ڵ���������
		m_oShotPointMap.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}
/**
* ���ؾ���������������
* @param void
* @return void
*/
void CSiteData::OnLoadSpreadSetupDataForAbsolute()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �����������ö���
		m_oSpreadAbsoluteList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* �������������������
* @param void
* @return void
*/
void CSiteData::OnLoadSpreadSetupDataForGeneric()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ����������ö���
		m_oSpreadGenericList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* Apply����������������
* @param void
* @return void
*/
void CSiteData::OnApplySpreadSetupDataForAbsolute()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// �����������ö���
		m_oSpreadAbsoluteList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();

	::PostMessage(HWND_BROADCAST, WM_NEWXMLFILE , MATRIX_LINE, MATRIX_LINE_SPREAD);
}

/**
* Apply���������������
* @param void
* @return void
*/
void CSiteData::OnApplySpreadSetupDataForGeneric()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ����������ö���
		m_oSpreadGenericList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();

	::PostMessage(HWND_BROADCAST, WM_NEWXMLFILE , MATRIX_LINE, MATRIX_LINE_SPREAD);
}

/**
* ���Ͳ��Ծ��������������ݱ仯֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplySpreadSetupDataForAbsolute()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	61-SpreadSetup��ApplySpreadSetupDataForAbsolute
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(61);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���Ͳ�����������������ݱ仯֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplySpreadSetupDataForGeneric()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	62-SpreadSetup��ApplySpreadSetupDataForGeneric
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(62);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���ز��Ի����������ݣ�����
* @param void
* @return void
*/
void CSiteData::OnLoadTestBaseSetupDataForInstrument()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestBaseListInstrument.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ���ز��Ի����������ݣ��첨��
* @param void
* @return void
*/
void CSiteData::OnLoadTestBaseSetupDataForSensor()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestBaseListSensor.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* Apply���Ի����������ݣ�����
* @param void
* @return void
*/
void CSiteData::OnApplyTestBaseSetupDataForInstrument()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestBaseListInstrument.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* Apply���Ի����������ݣ��첨��
* @param void
* @return void
*/
void CSiteData::OnApplyTestBaseSetupDataForSensor()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestBaseListSensor.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* ���Ͳ��Ի����������ݱ仯֪ͨ����֡������
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyTestBaseSetupDataOfInstrument()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestBase
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(41);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���Ͳ��Ի����������ݱ仯֪ͨ����֡���첨��
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyTestBaseSetupDataOfSensor()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	42-TestSetup��ApplySensorTestBase
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(42);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���ز����о��������ݣ�����
* @param void
* @return void
*/
void CSiteData::OnLoadTestLimitSetupDataForInstrument()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestLimitListInstrument.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ���ز����о��������ݣ��첨��
* @param void
* @return void
*/
void CSiteData::OnLoadTestLimitSetupDataForSensor()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestLimitListSensor.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* Apply�����о��������ݣ�����
* @param void
* @return void
*/
void CSiteData::OnApplyTestLimitSetupDataForInstrument()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestLimitListInstrument.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* Apply�����о��������ݣ��첨��
* @param void
* @return void
*/
void CSiteData::OnApplyTestLimitSetupDataForSensor()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestLimitListSensor.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* ���Ͳ����о��������ݱ仯֪ͨ����֡������
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyTestLimitSetupDataOfInstrument()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestLimit
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(51);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���Ͳ����о��������ݱ仯֪ͨ����֡���첨��
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyTestLimitSetupDataOfSensor()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	42-TestSetup��ApplySensorTestLimit
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(52);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���ز����������ݣ���������
* @param void
* @return void
*/
void CSiteData::OnLoadTestSetupDataForInstrument()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestProjectListInstrument.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ���ز����������ݣ��첨������
* @param void
* @return void
*/
void CSiteData::OnLoadTestSetupDataForSensor()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestProjectListSensor.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ���ز����������ݣ����ϲ���
* @param void
* @return void
*/
void CSiteData::OnLoadTestSetupDataForMultiple()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestProjectListMultiple.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ���ز����������ݣ��������
* @param void
* @return void
*/
void CSiteData::OnLoadTestSetupDataForSeisMonitor()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestProjectListSeisMonitor.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* Apply�����������ݣ���������
* @param void
* @return void
*/
void CSiteData::OnApplyTestSetupDataForInstrument()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestProjectListInstrument.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* Apply�����������ݣ��첨������
* @param void
* @return void
*/
void CSiteData::OnApplyTestSetupDataForSensor()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestProjectListSensor.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* Apply�����������ݣ����ϲ���
* @param void
* @return void
*/
void CSiteData::OnApplyTestSetupDataForMultiple()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestProjectListMultiple.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* Apply�����������ݣ��������
* @param void
* @return void
*/
void CSiteData::OnApplyTestSetupDataForSeisMonitor()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		m_oTestProjectListSeisMonitor.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* ���Ͳ����������ݱ仯֪ͨ����֡����������
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyTestSetupDataOfInstrument()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	31-TestSetup��ApplyInstrument
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(31);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���Ͳ����������ݱ仯֪ͨ����֡���첨������
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyTestSetupDataOfSensor()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	32-TestSetup��ApplySensor
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(32);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���Ͳ����������ݱ仯֪ͨ����֡�����ϲ���
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyTestSetupDataOfMultiple()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	33-TestSetup��ApplyMultiple
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(33);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ���Ͳ����������ݱ仯֪ͨ����֡���������
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyTestSetupDataOfSeisMonitor()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	34-TestSetup��ApplySeisMonitor
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(34);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ����TestSetup����GO֪ͨ����֡
* @param unsigned short usCommand ���� 4-Test From InstrumentTestSetup��5-Test From SensorTestSetup��6-Test From MultipleTestSetup��7-Test From SeismonitorTestSetup
* @param UINT uiTestNb ����������
* @return void
*/
void CSiteData::OnSendCMDFrameForTestSetupGO(unsigned short usCommand, UINT uiTestNb)
{
	// ���� 4-Test From InstrumentTestSetup��5-Test From SensorTestSetup��6-Test From MultipleTestSetup��7-Test From SeismonitorTestSetup
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeTestCmdFrameForTestSetup(usCommand, uiTestNb);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ����FormLine��������
* @param void
* @return void
*/
void CSiteData::OnLoadFormLineSetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ���¼���
		m_oFormLineList.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ����FormLine�������ݣ�Apply
* @param void
* @return void
*/
void CSiteData::OnApplyFormLineSetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ����FormLine����
		m_oFormLineList.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* ����FormLine����GO֪ͨ����֡
* @param unsigned int uiSN ����SN��
* @return void
*/
void CSiteData::OnSendFormLineCMDFrameGO(unsigned int uiSN)
{
	// ����	2-FormLine
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeFormLineFrame(uiSN);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ����Look��������
* @param void
* @return void
*/
void CSiteData::OnLoadLookSetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ���¼���
		m_oLookSetupData.OnReload();
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

/**
* ����Look�������ݣ�Apply
* @param void
* @return void
*/
void CSiteData::OnApplyLookSetupData()
{
	// �������ļ�
	OpenMatrixIniXMLFile();
		// ����Look����
		m_oLookSetupData.OnSave();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

	// ����Matrix�����ļ���FTP������
	SaveMatrixIniFileToFTPServer();
}

/**
* ����Look����Apply֪ͨ����֡
* @param void
* @return void
*/
void CSiteData::OnSendCMDFrameForApplyLookSetupData()
{
	// ����	20-���������ļ�����������ĵ�Ŀ��	21-LookSetup��Apply
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeSiteDataOutputCmdFrame(21);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ��Ӧ�������첨��ͼ����ͼ����GO��ť
* @param unsigned unsigned int uiTestAim ���Զ���	1-������2-�첨��
* @param unsigned unsigned int uiTestType ��������
* @param unsigned CString strTestAbsoluteSpread �������ж���
* @return void
*/
void CSiteData::OnSendCMDFrameForGraphViewInstrumentOrSensorTestGOButton(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread)
{
	// ���ɲ�������֡����Ӧ�������첨��ͼ����ͼ����GO��ť
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeTestCmdFrameForGraphViewGOButton(uiTestAim, uiTestType, strTestAbsoluteSpread);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}

/**
* ��Ӧ�������ͼ����ͼSeismonitor��ť
* @param byte byTestOperation ���� 1-�������ԣ�0-ֹͣ����
* @param unsigned CString strTestAbsoluteSpread �������ж���
* @return void
*/
void CSiteData::OnSendCMDFrameForGraphViewNoiseSeismonitorButton(byte byTestOperation, CString strTestAbsoluteSpread)
{
	// ���ɲ�������֡����Ӧ�������ͼ����ͼSeismonitor��ť
	m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeTestCmdFrameForGraphViewSeismonitorButton(byTestOperation, strTestAbsoluteSpread);
	m_oSocketInterfaceCmdSend.SendCommandFrame();
}