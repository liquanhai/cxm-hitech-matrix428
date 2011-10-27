#include "StdAfx.h"
#include "ADCDataSaveToFile.h"
#include <iostream>
#include <iomanip>

CADCDataSaveToFile::CADCDataSaveToFile(void)
: m_bOpenADCSaveFile(FALSE)
, m_uiADCSaveFileNum(0)
/*, m_pFileSave(NULL)*/
, m_uiADCDataToSaveNum(0)
, m_uiADCFileLength(0)
, m_csSaveFilePath(_T(""))
, m_arFileSave(NULL)
, m_uiSampleInstrumentNum(0)
, m_pInstrumentList(NULL)
{
}

CADCDataSaveToFile::~CADCDataSaveToFile(void)
{
}

// ��ADC���ݱ��浽�ļ���
void CADCDataSaveToFile::OnSaveADCToFile(int(* iADCDataBuf)[ADCDataTempDataSize], unsigned int* upADCDataNum,
										 unsigned int uiADCDataToSaveNum, bool bFinish)
{
	CString strOutput = _T("");
	CString strTemp = _T("");
	unsigned int uiDataLength = 0;
// 	char   buffer[_CVTBUFSIZE]; 
// 	int dec,sign;
	wchar_t buffer[_CVTBUFSIZE];
	if(m_bOpenADCSaveFile == FALSE)
	{
		OnOpenADCSaveFile();
	}
	// @@@@@@@@ֹͣ�ɼ�ʱ���ļ������
	// �����������������
	for (unsigned int i=0; i<uiADCDataToSaveNum; i++)
	{
		//		ProcessMessages();
		for (int j=0; j<InstrumentNum; j++)
		{
			//			ProcessMessages();
			uiDataLength = upADCDataNum[j];
			if (uiDataLength == 0 )
			{
//				strOutput += _T("  \t \t");
				continue;
			}
			if (uiDataLength > i)
			{
				// ����1��Ҳ����ʵ��doubleת��Ϊstring��ֻ��ת��������ݲ��ÿ�ѧ��������CPUռ���ʴﵽ22%
// 				_gcvt_s(buffer, _CVTBUFSIZE, dpADCDataBuf[j][i], 9);
// 				strOutput += buffer;
				ZeroMemory(buffer, _CVTBUFSIZE);
				// ����2������_stprintf_s�����ķ�����CPUռ���ʴﵽ10%
				_stprintf_s(buffer, _CVTBUFSIZE, _T("%*d"), DecimalPlaces, iADCDataBuf[j][i]);
				strOutput += buffer;
				strOutput +=  _T(" \t");

				// ����3������_fcvt_s�����ķ�����CPUռ���ʴﵽ25%
// 				_fcvt_s(buffer, _CVTBUFSIZE, dpADCDataBuf[j][i], DecimalPlaces, &dec, &sign);
// 				char* length = Convert(buffer,dec,sign);
// 				strOutput += length;
// 				strOutput +=  _T("\t");

				// ����4������Format�����ķ�����CPUռ���ʴﵽ20%
//				strTemp.Format(_T("%2.*lf\t"), DecimalPlaces, dpADCDataBuf[j][i]);
//				strOutput += strTemp;
			}
			else
			{
				// ����вɼ�վ���ݲ�ȫ��������ò��㴦��
				ZeroMemory(buffer, _CVTBUFSIZE);
				// ����2������_stprintf_s�����ķ�����CPUռ���ʴﵽ10%
				_stprintf_s(buffer, _CVTBUFSIZE, _T("%*d"), DecimalPlaces, 0);
				strOutput += buffer;
				strOutput +=  _T(" \t");
			}
		}
		strOutput += _T("\r\n");
	}
	//	fprintf(m_pFileSave, _T("%s"), strOutput); 
// 	CArchive ar(&m_FileSave, CArchive::store);
// 	ar.WriteString(strOutput);
// 	ar.Close();
	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
// 	WriteCHToCFile(m_arFileSave, strOutput);
	if (m_FileSave.m_hFile != CFile::hFileNull)
	{
		m_arFileSave->WriteString(strOutput);
	}

	if (bFinish == false)
	{
		m_uiADCDataToSaveNum += uiADCDataToSaveNum;
		if (m_uiADCDataToSaveNum == m_uiADCFileLength)
		{
			m_uiADCDataToSaveNum = 0;
			OnCloseADCSaveFile();
		}
	}
	else
	{
		OnCloseADCSaveFile();
		m_uiADCDataToSaveNum = 0;
		m_uiADCSaveFileNum = 0;
	}
}
// ��������ADC���������ļ�
void CADCDataSaveToFile::OnOpenADCSaveFile(void)
{
	CString strFileName = _T("");
	CString strOutput = _T("");
	CString strTemp = _T("");
	//	errno_t err;
	CString str = _T("");
	unsigned int uiADCStartNum = 0;
	unsigned int uiADCDataCovNb = ADCDataConvert;
	SYSTEMTIME  sysTime;
	// ѡ�е�������������
//	wchar_t cSelectObjectName[InstrumentNum][RcvFrameSize];
//	char cSelectObjectName[InstrumentNum][RcvFrameSize];
	strFileName += m_csSaveFilePath;
	m_uiADCSaveFileNum++;
	strTemp.Format(_T("\\%d.text"), m_uiADCSaveFileNum);
	strFileName += strTemp;
	// ��ADC�������ݱ����ANSI��ʽ���ļ�
	// 	if((err = fopen_s(&m_pFileSave,strFileName,"w+"))!=NULL)
	// 	{
	// 		AfxMessageBox(_T("ADC���ݴ洢�ļ�����ʧ�ܣ�"));	
	// 		return;
	// 	}
	//�����UNICODE��ʽ���ļ�
	if(m_FileSave.Open(strFileName, CFile::modeCreate|CFile::modeWrite) == FALSE)
	{
		AfxMessageBox(_T("ADC���ݴ洢�ļ�����ʧ�ܣ�"));	
		return;
	}
	m_FileSave.Write("\xff\xfe", 2);    // ����Unicode�����ļ�ͷ
	m_arFileSave = new CArchive(&m_FileSave, CArchive::store);
	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03d��ʼ��¼ADC�������ݣ�\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	strOutput += str;
	uiADCStartNum = (m_uiADCSaveFileNum - 1) * m_uiADCFileLength;
	str.Format(_T("�ɼ�վ�豸����%d���ӵ�%d�����ݿ�ʼ�洢ADC���ݣ�����ת����ʽ���÷�ʽ%d��\r\n"), m_uiSampleInstrumentNum, uiADCStartNum, uiADCDataCovNb);
	strOutput += str;
	CInstrument* pInstrument = NULL;
	// ���������ǩ
	for (unsigned int i=0; i<InstrumentNum; i++)
	{
		if (m_pInstrumentList->GetInstrumentFromIPMap(IPSetAddrStart + IPSetAddrInterval * (i + 1), pInstrument))
		{
			if ((pInstrument->m_bIPSetOK == true) 
				&& (pInstrument->m_uiInstrumentType == InstrumentTypeFDU)
				&& (pInstrument->m_iSelectObject == BST_CHECKED))
			{
				strTemp.Format(_T("����%d \t"), pInstrument->m_uiFDULocation + 1);
				int iLength = strTemp.GetLength();
				if (iLength < DecimalPlaces + ADCDataPlaces)
				{
					for (int j=0; j<(DecimalPlaces + ADCDataPlaces - iLength); j++)
					{
						strTemp = _T(" ") + strTemp;
					}
				}
				strOutput += strTemp;
			}
		}
	}

	strOutput += _T("\r\n");
	//	fprintf(m_pFileSave, _T("%s"), strOutput); 
// 	CArchive ar(&m_FileSave, CArchive::store);
// 	ar.WriteString(strOutput);
// 	ar.Close();

	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
//	WriteCHToCFile(m_arFileSave, strOutput);
	if (m_FileSave.m_hFile != CFile::hFileNull)
	{
		m_arFileSave->WriteString(strOutput);
	}
	m_bOpenADCSaveFile = TRUE;
}
// �ر�ADC���������ļ�
void CADCDataSaveToFile::OnCloseADCSaveFile(void)
{
	if(m_FileSave.m_hFile != CFile::hFileNull)    // virtual member function
	{
		m_arFileSave->Close();
		m_FileSave.Close();
		delete m_arFileSave;
		m_bOpenADCSaveFile = FALSE;
	}
}
// ��ֹ������ѭ���������޷���Ӧ��Ϣ
void CADCDataSaveToFile::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}