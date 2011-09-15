#include "stdafx.h"
#include "MatrixDef.h"
#include <afxinet.h>

////////////////////////////////////////////////////////////////////////////////////////////
/// �Զ�����Ϣ
UINT NEAR WM_NEWXMLFILE = RegisterWindowMessage(MSG_XMLFILE_NEW);

/**
* ��FTP�������õ�Matrix�����ļ�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool GetMatrixXMLFromFTPServer(LPCTSTR strFTPServerIP,LPCTSTR strFTPFile,LPCTSTR strLocalFile)
{
	bool bReturn = false;
	BOOL bData;
	int iCount = 0;
	CInternetSession oSession;
	CFtpConnection* pConnection = oSession.GetFtpConnection(strFTPServerIP);
		
	while(true)
	{
		bData = pConnection->GetFile(strFTPFile, strLocalFile, FALSE);
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
bool PutMatrixXMLToFTPServer(LPCTSTR strFTPServerIP,LPCTSTR strFTPFile,LPCTSTR strLocalFile)
{
	bool bReturn = false;
	BOOL bData;
	int iCount = 0;
	CInternetSession oSession;
	CFtpConnection* pConnection = oSession.GetFtpConnection(strFTPServerIP);
	
	while(true)
	{
		//bData = pConnection->PutFile(strLocalFile, strFTPFile);
		bData = pConnection->PutFile(strLocalFile, strLocalFile);
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