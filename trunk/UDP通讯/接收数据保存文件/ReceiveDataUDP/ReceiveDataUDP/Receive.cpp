#include "StdAfx.h"
#include "Receive.h"
#include <string>
using namespace std;
extern void SaveReceiveDataToFile(vector<UCHAR> Buf);


CReceive::CReceive(void)
{
}

CReceive::~CReceive(void)
{
}
void CReceive::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	unsigned char		pBuf[128];
	WORD				wFrmLen = 128;		// ֡��: ��ʼ��Ϊ�������Ĵ�С����ReceiveFrom����ʹ��
	int				nSize;
	sockaddr_in sockClient;
	sockClient.sin_family = AF_INET;
	nSize = sizeof(sockClient);

	// �������Կͻ��˵�����
	int iCount = 128;
	while(iCount == 128)
	{
		iCount = ReceiveFrom( pBuf, wFrmLen, (SOCKADDR*)&sockClient , &nSize );
		for (int i=0;i<iCount;i++)
		{
			m_ReceiveData.push_back(pBuf[i]);
		}
	}
	
	SaveReceiveDataToFile(m_ReceiveData);

	m_ReceiveData.clear();

	CSocket::OnReceive(nErrorCode);
}
BOOL CReceive::OnInit()
{
	BOOL bReturn = false;
	u_short m_UDPSendDataPort = 0x5010;
	CString m_UDPSendDataIP = _T("192.168.1.56");

	// ��������˿�
	bReturn = Create(m_UDPSendDataPort, SOCK_DGRAM, m_UDPSendDataIP);

	m_ReceiveData.reserve(1000);

	return bReturn;	
}
//�����յ������ݱ��浽�ļ���
void SaveReceiveDataToFile(vector<UCHAR> Buf)
{
	CString sPathName;	//��ȡ�ļ��ľ���·��
	CString str;
	const wchar_t pszFilter[] = _T("TXT Document (*.txt)|*.txt||");
	CFileDialog dlg(FALSE, _T("EC"), _T("*.txt"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Text Document(*.txt)|*.txt")); 

	if ( dlg.DoModal() != IDOK )
		return;
	sPathName = dlg.GetPathName();


	//�����UNICODE��ʽ���ļ�
	// 	CFile savefile;	
	// 	savefile.Open(sPathName, CFile::modeCreate|CFile::modeWrite);
	// 	CArchive ar(&savefile, CArchive::store);
	// 	for (int j = 0; j < Buf.size(); j++)//ֻ�������һ�βɼ���������
	// 	{
	// 	
	// 		str.Format(_T("%c\r\n"), Buf[j]);
	// 		ar.WriteString(str);
	// 	}
	// 	ar.Close();
	// 	savefile.Close();

	//�����ANSI��ʽ���ļ�
	errno_t err;
	char cPath[1000];
	FILE * savefile;
	wchar_t wcPath[1000];

	//��CStringת��Ϊwchar_t����
	USES_CONVERSION_EX;
	wcscpy_s(wcPath, CT2CW(sPathName)); 

	wstring strtemp = (LPCTSTR)wcPath;

	//�ַ���ʽ��WideCharת��ΪMultiChar
	string return_value;
	//��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ֽڼ����
	int len = WideCharToMultiByte(CP_ACP,0,strtemp.c_str(),((int)strtemp.size()),NULL,0,NULL,NULL);
	char *buffer = new char[len+1];
	WideCharToMultiByte(CP_ACP,0,strtemp.c_str(),((int)strtemp.size()),buffer,len,NULL,NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ
	return_value.append(buffer);
	delete []buffer;

	string mstring = return_value;

	//��stringת��Ϊchar����
	strcpy_s( cPath, sizeof(cPath), mstring.c_str() );
	if((err = fopen_s(&savefile,cPath,"w+"))==NULL)
	{

		for (unsigned int j = 0; j < Buf.size(); j++)	//ֻ�������һ�βɼ���������
		{
			fprintf(savefile,"%c", Buf[j]); 
		}
	}
	fclose(savefile); 
}