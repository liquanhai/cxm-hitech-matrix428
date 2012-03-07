#include "StdAfx.h"
#include "CLogbase.h"

UINT WM_NEWLOG = RegisterWindowMessage(MSG_LOG_NEW);
/**
 * @brief CLogBase���캯��
 */
CLogBase::CLogBase(void)
{
		
}
/**
 * @brief CLogBase��������
 */
CLogBase::~CLogBase(void)
{

}
void CLogBase::SetHostAndProgram(LPCTSTR strIP,DWORD dwProgramNum)
{
	USES_CONVERSION;
	LPSTR  str = T2A(strIP);
	unsigned long dwIP = inet_addr(str);
	SetHostAndProgram(dwIP,dwProgramNum);
}
/** 
 * @brief ������־��Ϣ
 * @note  ����һ����־����Ϣ��λ�á����������͡��Ƿ���ʾ���û���
 * @param LPCTSTR strPosition,��־������λ��
 * @param LPCTSTR strDesc,��־����
 * @param WORD wType,��־���ͣ����������桢�쳣�����Լ�����
 * @param BOOL bShowed���Ƿ���ʾ���û�
 * @return void
*/
void  CLogBase::SetLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType,BOOL bShowed)
{	
	// ������־��Ϣ��ʱ��	
	GetLocalTime(&m_sysTime);	
	// λ��
	_tcscpy_s(m_strPosition,_countof(m_strPosition),strPosition);
	// ˵��
	_tcscpy_s(m_strDescription,_countof(m_strDescription),strDesc);
	// ����
	m_wType = wType;
	m_bShowed = bShowed;
}
/** 
 * @brief ����������ʾ���ַ���
 * @note  ����������ʾ���ַ�����������ʱ�������
 * @param CString& strLog,�����������������һ���ı�����־��¼
 * @return void
*/
void  CLogBase::GetShowString(CString& strLog)
{
	strLog.Format(_T("%02d:%02d:%02d [%d] %s"),m_sysTime.wHour,m_sysTime.wMinute,m_sysTime.wSecond,m_dwProgramNum,m_strDescription);
}
/** 
 * @brief ������־��¼�ı�
 * @note  �����е���־���չ̶���ʽ��ϣ�����һ���ı�����־��¼
 * @param CString& strLog,�����������������һ���ı�����־��¼
 * @return void
*/
void  CLogBase::GetAllAttributes(CString& strLog)
{
	CString   strTemp;
	strLog.Format(_T("%04d-%02d-%02d\t%02d:%02d:%02d\t%02d\t"),
		m_sysTime.wYear,m_sysTime.wMonth,m_sysTime.wDay,m_sysTime.wHour,m_sysTime.wMinute,m_sysTime.wSecond,m_wType);
	if(m_bShowed)
	{
		strLog+=_T("true\t");
	}
	else
	{
		strLog+=_T("false\t");
	}
	strTemp.Format(_T("0x%08x\t"),m_dwHostIP);
	strLog+=strTemp;
	strTemp.Format(_T("0x%08x\t"),m_dwProgramNum);
	strLog+=strTemp;
	strTemp.Format(_T("%s\t\t"),m_strPosition);
	strLog+=strTemp;
	strLog+=m_strDescription;
}
/** 
 * @brief ������־����֡���ֽ���
 * @note  ���㷢��һ����־��¼������֡�ֽڴ�С������֮֡ǰ���øú�������ȡ�ֽڴ�С���ٶ�̬���仺������
 * @param void
 * @return int ,��־����֡�ֽ���
*/
int CLogBase::GetFrameByteSize(void)
{
	int nSize = GetObjectByteSize();
	// 16Ϊ����֡֡ͷ��֡�����ֽ���
	return 16 + nSize;
}
/** 
 * @brief д�뻺����
 * @note ����־��Ϣ����д�뻺����
 * @param BYTE* pBuf,���ݻ�����
 * @return int ,�����ֽڳ���
*/
int CLogBase::WriteToBuf(BYTE* pBuf)
{
	if(!pBuf)
		return 0;
	// ʱ����Ϣ
	int nLen = 0;
	pBuf[nLen++] = LOBYTE(m_sysTime.wYear);
	pBuf[nLen++] = HIBYTE(m_sysTime.wYear);
	pBuf[nLen++] = LOBYTE(m_sysTime.wMonth);
	pBuf[nLen++] = HIBYTE(m_sysTime.wMonth);
	pBuf[nLen++] = LOBYTE(m_sysTime.wDay);
	pBuf[nLen++] = HIBYTE(m_sysTime.wDay);
	pBuf[nLen++] = LOBYTE(m_sysTime.wHour);
	pBuf[nLen++] = HIBYTE(m_sysTime.wHour);
	pBuf[nLen++] = LOBYTE(m_sysTime.wMinute);
	pBuf[nLen++] = HIBYTE(m_sysTime.wMinute);
	pBuf[nLen++] = LOBYTE(m_sysTime.wSecond);
	pBuf[nLen++] = HIBYTE(m_sysTime.wSecond);
	// ����
	pBuf[nLen++] = LOBYTE(m_wType);
	pBuf[nLen++] = HIBYTE(m_wType);
	memcpy_s(pBuf+nLen,sizeof(BOOL),&m_bShowed,sizeof(BOOL));
	nLen+=sizeof(BOOL);
	// Դ�����IP��ַ
	memcpy_s(pBuf+nLen,sizeof(DWORD),&m_dwHostIP,sizeof(DWORD));
	nLen+=sizeof(DWORD);
	// ������־�ĳ������
	memcpy_s(pBuf+nLen,sizeof(DWORD),&m_dwProgramNum,sizeof(DWORD));
	nLen+=sizeof(DWORD);
	// Դ����λ��˵������תΪwchar���ٷ���
	LPWSTR		wstr = T2W(m_strPosition);
	memcpy_s(pBuf+nLen,_countof(m_strPosition)*2,wstr,_countof(m_strPosition)*2);
	nLen+=_countof(m_strPosition)*2;
	// ��־��Ϣ����תΪwchar���ٷ���
	LPWSTR		wstrDesc = T2W(m_strDescription);
	memcpy_s(pBuf+nLen,_countof(m_strDescription)*2,wstrDesc,_countof(m_strDescription)*2);
	nLen+=_countof(m_strDescription)*2;
	return nLen;
}
/** 
 * @brief д����־����֡
 * @note ����־��Ϣ������־����ͨ��Э�飬д�뻺�������γ���־����֡��
 * @param BYTE* pBuf
 * @return int ,�����ֽڳ���
*/
int CLogBase::WriteToSocketFrame(BYTE* pBuf)
{
	if(!pBuf)
		return 0;
	// int     nLen;
	WORD	wFrmLen;
	// ֡ͷ
	pBuf[0]= 0xEB;
	pBuf[1]= 0x90;
	// ֡��
	wFrmLen = (WORD)GetFrameByteSize();
	pBuf[2] = LOBYTE(wFrmLen);
	pBuf[3] = HIBYTE(wFrmLen);
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����	
	if(m_dwProgramNum==MATRIX_ADMINSERVER)
		pBuf[8] = 0xFF;
	else
		pBuf[8] = 0x01;	
	// ������
	pBuf[9] = 0xFF;
	pBuf[10] = 0xFF;
	// ���ݸ���
	pBuf[11]= 1;
	pBuf[12]= 0;
	// д�뻺����
	WriteToBuf(pBuf+13);
	
	// ֡У��
	pBuf[wFrmLen-3]= 0x00;
	// ֡β
	pBuf[wFrmLen-2]= 0x14;
	pBuf[wFrmLen-1]= 0x6F;	
	return wFrmLen;
}
/** 
 * @brief �ӻ�������������
 * @note �ӻ�������������
 * @param BYTE* pBuf��ָ����־�������Ի�����
 * @return int ,�����ֽڳ���
*/
int CLogBase::ReadFromBuf(BYTE* pBuf)
{
	// ��־����
	// ʱ����Ϣ
	int nLen = 0;
	m_sysTime.wYear = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_sysTime.wMonth = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_sysTime.wDay = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_sysTime.wHour = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_sysTime.wMinute = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_sysTime.wSecond = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;		
	// ����
	m_wType = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;	
	// �Ƿ���ʾ
	memcpy_s(&m_bShowed,sizeof(BOOL),pBuf+nLen,sizeof(BOOL));
	nLen+=sizeof(BOOL);
	// Դ�����IP��ַ
	memcpy_s(&m_dwHostIP,sizeof(DWORD),pBuf+nLen,sizeof(DWORD));
	nLen+=sizeof(DWORD);
	// ������־�ĳ������
	memcpy_s(&m_dwProgramNum,sizeof(DWORD),pBuf+nLen,sizeof(DWORD));
	nLen+=sizeof(DWORD);
	// Դ����λ��˵�������յ��ַ���Ϊwchar����ת��ΪTCHAR���ͣ��ٴ���
	LPTSTR		strPos = W2T(LPTSTR(pBuf+nLen));
	memcpy_s(m_strPosition,_countof(m_strPosition)*sizeof(TCHAR),strPos,_countof(m_strPosition)*sizeof(TCHAR));
	nLen+=_countof(m_strPosition)*2;
	// ��־��Ϣ�����յ��ַ���Ϊwchar����ת��ΪTCHAR���ͣ��ٴ���
	LPTSTR		strDesc = W2T(LPTSTR(pBuf+nLen));
	memcpy_s(m_strDescription,_countof(m_strDescription)*sizeof(TCHAR),strDesc,_countof(m_strDescription)*sizeof(TCHAR));
	nLen+=_countof(m_strDescription)*2;		
	return nLen+3;
}
/** 
 * @brief ����־����֡������־����
 * @note ����־����֡������־����
 * @param BYTE* pBuf��ָ����־����֡�ĵ�ַ
 * @return int ,�����ֽڳ���
*/
int CLogBase::ReadFromSocketFrame(BYTE* pBuf)
{
	if(!pBuf)
		return 0;	
	// ��־����,������֡�б�����־���Ե��������ӵ�ʮ�����ֽڿ�ʼ
	return ReadFromBuf(pBuf+13);	
}

