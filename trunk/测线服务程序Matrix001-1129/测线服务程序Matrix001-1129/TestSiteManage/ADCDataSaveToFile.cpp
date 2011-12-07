#include "StdAfx.h"
#include "ADCDataSaveToFile.h"
//#include "..\common\OperaStruct.h"
//#include "..\common\SocketParam.h"

CADCDataSaveToFile::CADCDataSaveToFile(void)
: m_uiADCSaveFileNum(0)
, m_uiADCDataToSaveNum(0)
,m_uiSaveNum(0)
, m_uiADCFileLength(0)
//, m_csSaveFilePath(_T(""))
{
}

CADCDataSaveToFile::~CADCDataSaveToFile(void)
{
	OnCloseADCSaveFile();
}

// ��ADC���ݱ��浽�ļ���
// dpADCDataBuf=����ָ��pRevBuf->m_RevBuf[�ɼ�վ][����]��upADCDataNum=m_Revidx[�ɼ�վ][֡��]=ƫ�����ۼƣ�Revidx=pRevBuf->rev_count[�ɼ�վ]=�ɼ�����
// ȡ��һ�����ݣ������յ��ɼ�վ�ڶ�֡ʱ���洢����վ��һ֡����
// ƫ����idx,lineCount=��ǰλ�� m_uiADCDataToSaveNum=�洢λ��
//void CADCDataSaveToFile::OnSaveADCToFile(unsigned char  *dpADCDataBuf, int (*upADCDataNum)[MaxrevFfameSize+ReceiveDataPoint],
void CADCDataSaveToFile::OnSaveADCToFile(unsigned char  *dpADCDataBuf, int *upADCDataNum,
										int *Revidx,int SpreadCount, bool bFinish,int type,int lineCount)
{
	CString strOutput = _T("");
	int iline=0,idata;
	float jdata=0;
	char charTemp[128];
	//char buf[8192];
	int idx=0,lastidx=0;

	if(lineCount<0 )
		return;
	if( lineCount==m_uiADCDataToSaveNum)
		return;
	strOutput.Empty(); 
	//strOutput.ReleaseBuffer(); 
	
	ProcessMessages();

	//int i=m_uiADCDataToSaveNum;
	int i=0;
	lineCount=1;
	while(true)
	{
	if(lineCount==i)
		break;
		//����ÿ�вɼ�վ����
		for(int k=0;k<ReceiveDataPoint;k++){
			//for (int j=0; j<SpreadCount; j++)
			for (int j=0; j<1; j++)
			{
				idata=0;
				//memcpy(&idata,dpADCDataBuf+i*ADDataSize+j*(SHOT_RECORDLEN+TB_WINDOW)*ADDataSize,ADDataSize);
				//memcpy(&idata,dpADCDataBuf+j*RecvBuf+i*+SAMPFRM_DATALEN+k*ADDataSize,ADDataSize);
				//memcpy(&idata,dpADCDataBuf+j*RecvBuf++SAMPFRM_DATALEN+k*ADDataSize,ADDataSize);
				memcpy(&idata, &dpADCDataBuf[(k+j) * 4], 4);
				if(type==1){
					if(idata>0x800000){
						idata=0xffffff-idata;
						jdata=-(float)(2.5*idata/8388608.0);
					}
					else{
						jdata=(float)(2.5*idata/8388608.0);
					}
				}
					
				//strTemp.Format(_T("%f \t"), jdata);
				charTemp[0]=0x0;
				if(type==1)
					sprintf_s(charTemp,"%2.8f  \t",jdata);
				else{
					if(idata>0x800000)
						idata=(0xffffff-idata);
					sprintf_s(charTemp,"%d \t",idata);
				}
				//strOutput += strTemp;
				strOutput += charTemp;
			}
			//strOutput += "\r\n";
			int iLen=strOutput.GetLength();
			//ÿ�δ���64������
			if(iline>=1){
				m_Sec.Lock();
/*				//*arP<<strOutput;
				arP->WriteString(strOutput);
				arP-> Flush();
				m_Sec.Unlock();
				Sleep(0);
				//strOutput.ReleaseBuffer(); 
				strOutput.Empty(); 
*/				iline=0;
			}
			else
				iline++;
		}
	i++;
	if(i>=MaxrevFramePoint)
		i=0;
	}
	strOutput += "\r\n";
	arP->WriteString(strOutput);
	arP-> Flush();
	m_uiADCDataToSaveNum=i;
	if(iline>0 ){
		//*arP<<strOutput;
		arP->WriteString(strOutput);
		//arP->Write(strOutput.GetBuffer(),strOutput.GetLength()); 
		arP-> Flush();
		Sleep(0);
	}
}

// ��������ADC���������ļ�
void CADCDataSaveToFile::OnOpenADCSaveFile( int SpreadCount)
{
	CString m_strFileName = _T("");
	CString strOutput = _T("");
	CString strTemp = _T("");
//	errno_t err;
	CString str = _T("");
	SYSTEMTIME  sysTime;

	// ѡ�е�������������
	GetLocalTime(&sysTime);
	strTemp.Format(_T("..\\LogFileLine\\%d%02d%02d%02d%02d%02d_%d.text"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,sysTime.wHour,sysTime.wMinute,sysTime.wSecond,m_uiSaveNum);
	m_strFileName += strTemp;
/*	// ��ADC�������ݱ����ANSI��ʽ���ļ�
	if((err = fopen_s(&m_pFileSave,strFileName,"w+"))!=NULL)
	{
		AfxMessageBox(_T("ADC���ݴ洢�ļ�����ʧ�ܣ�"));	
		return;
	}
*/
	//�����UNICODE��ʽ���ļ�
	// ����ļ��Ѵ򿪣����ȹر�ԭ���ļ�
	if(m_pFileSave.m_hFile!= CFile::hFileNull)
	{
		TRACE1("Failed to Close datafile %s !\r\n",m_strFileName);
		m_pFileSave.Close();
	}
	if(!m_pFileSave.Open(m_strFileName,CFile::modeCreate|CFile::modeWrite)){
		;
		TRACE1("Failed to Create datafile %s !",m_strFileName);
	}
	//CArchive ar(&m_pFileSave, CArchive::store);
	arP=new   CArchive(&m_pFileSave,CArchive::store);
	//arP=&ar;
	//m_pFileSave.Write("\xff\xfe",2);
	strOutput.Empty(); 
	str.Empty();
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03d��ʼ��¼ADC�������ݣ�\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	strOutput += str;
	str.Empty();
	str.Format(_T("�ɼ�վ�豸����%d���ӵ�0�����ݿ�ʼ�洢ADC���ݣ�����ת����ʽ���÷�ʽ1��\r\n"),SpreadCount);
	strOutput += str;
	// ���������ǩ
	for (int i=0; i<FDU_MAXINUM; i++)
	{
		//ProcessMessages();
		strTemp.Empty();
		strTemp.Format(_T("����%d\t\t\t\t\t"), i+1);
/*		char* pchar = (char *)strTemp.GetBuffer(0); 
		strcpy_s(cSelectObjectName[i],pchar);
		strTemp.Format(_T("%s\t\t"), cSelectObjectName[i]);
*/		strOutput += strTemp;
	}
	
	strOutput += _T("\r\n");
	int i=strOutput.GetLength();
	//*arP<<strOutput;
	arP->WriteString(strOutput);
    arP-> Flush();

	m_uiSaveNum++;
	iline=0;
	m_bOpenADCSaveFile = TRUE;
}

// ��������ADC���������ļ�
// �ر�ADC���������ļ�
void CADCDataSaveToFile::OnCloseADCSaveFile(void)
{
	if (m_pFileSave == NULL || m_pFileSave ==INVALID_HANDLE_VALUE)
	{
		return;
	}
	arP-> Flush();
	arP->Close();
	m_pFileSave.Close();
	//fclose(m_pFileSave); 
	m_bOpenADCSaveFile = FALSE;
}
// ��ֹ������ѭ���������޷���Ӧ��Ϣ
void CADCDataSaveToFile::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

