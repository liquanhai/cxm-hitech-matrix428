#include "StdAfx.h"
#include "Operation.h"
#include "MainFrm.h"
#include "ActiveShot.h"

/**
 * @brief CActiveShot���캯��
 */
CActiveShot::CActiveShot(void)
: m_pShotPoint(NULL)
, m_pShotSource(NULL)
, m_pSpread(NULL)
, m_pProcessType(NULL)
, m_pSvrSocket(NULL)
, m_dwShotNb(0)
, m_dwSourceNb(0)
, m_dwServerID(0)
, m_dwTimerID(1)
, m_dwRetransCount(0)
{
	m_dwThreadID = 0;
	m_dwServerIP = 0xFFFFFFFF;
	m_wServerPort = OPERATION_SVRPORT;
}
/**
 * @brief CActiveShot��������
 */
CActiveShot::~CActiveShot(void)
{
}
/**
 * @note ���õ�ǰ������ڵ㼰���Զ���
 * @note �ڴ�������������Ҫ���øú��������ڵ㼰���ڵ�����Ӧ�Ĳɼ����С��������͵����ԡ� 
 * @param CShotPoint*   pShotPoint ׼�����ڵ��ڵ����
 * @param CShotSpread*  pSpread    �ڵ�����Ӧ�Ĳɼ�����
 * @param CProcessType* pProcess   �ڵ��������Ĵ�������
 * @return void
 */
void CActiveShot::SetShotPoint(CShotPoint* pShotPoint,CShotSpread* pSpread,CProcessType* pProcess)
{ 
	m_pShotPoint = pShotPoint;
	m_pSpread = pSpread;
	m_pProcessType = pProcess;
	if(m_pShotPoint)
	{
		m_dwShotNb = m_pShotPoint->m_dwShotNb;
		m_dwSpreadNb =m_pShotPoint->m_dwSpreadNb;
		m_dwProcessNb=m_pShotPoint->m_dwProcessNb;
	}
	else
	{
		m_dwShotNb = 0;
		m_dwSpreadNb = 0;
		m_dwProcessNb=0;
	}
}
/**
 * @note  ���÷�����ʹ�õ���Դ���� 
 * @param CShotSource* pShotSrc ��Դ����
 * @return void
 */
void CActiveShot::SetShotSource(CShotSource* pShotSrc)
{
	m_pShotSource = pShotSrc;  
	if(m_pShotSource)
		m_dwSourceNb = m_pShotSource->m_dwSourceNb;
	else
		m_dwSourceNb = 0;
}
/**
 * @brief �Ƿ��ǵ�ǰ�������
 * @note  ������֡��ʽ�н������ڵ��ź���Դ��ź�ͨ�������������ж��Ƿ�Ϊ�ö���
 * @param DWORD dwShotNb   �ڵ���
 * @param DWORD dwSourceNb ��Դ���
 * @return ����ںź���Դ���뵱ǰ���󱣴���ںź���Դ�Ŷ���ȣ��򷵻�true�����򷵻�false��
 */
bool CActiveShot::IsActiveShot(DWORD dwShotNb,DWORD dwSourceNb )
{
	if(  m_dwSourceNb!=dwSourceNb || m_dwShotNb!=dwShotNb )
		return false;
	else
		return true;
}

/**
 * @brief ���������������
 * @note  �ú�����װ��������IP��ַ���˿�ת��������������ͺ��������ã���ʩ��������������Ϣ ��
 * @param unsigned char*  pBuf   ���ݻ�����
 * @param int nSize ���ݻ������ֽڴ�С
 * @return �����ѷ��͵��ֽ�����
 */
int  CActiveShot::SendToServer(unsigned char* pBuf,int nSize)
{
	if(NULL==m_pSvrSocket)
		return -1;
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = m_dwServerIP;
	service.sin_port = htons(m_wServerPort);
	return  m_pSvrSocket->SendTo(pBuf,nSize,(SOCKADDR*)&service,sizeof(sockaddr_in));	
}
/*
*****************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� �������Է�����������
	          
			   ��CMainFrame���AnalysisProtocolOfServerSock��������

			   ����֡��ʽ��
			   ֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
			   ������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte��

    �޸���ʷ��

******************************************************************************
void CActiveShot::ParseServerData(unsigned char* pBuf,int nSize)
{	
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	WORD		wFrmCmdCode;	// ������
	wFrmCmdCode=MAKEWORD(pBuf[9],pBuf[10]);
	switch(wFrmCmdCode)
	{
	case OPERATION_CMD_REQUEST:		// ������ڷ�����Ӧ��
		{
			if(m_dwServerID)
				return;
			pBuf[4] = 0x01;		// ֡����
			pBuf[8] = 0x01;		// ֡����
			pBuf[9] = LOBYTE(OPERATION_CMD_CONFIRM);	// �������λ
			pBuf[10]= HIBYTE(OPERATION_CMD_CONFIRM);	// �������λ
			SendToServer(pBuf,nSize);
			pFrm->WriteLog(_T(" Request Acked!"));
			return;
		}
		break;
	case OPERATION_CMD_CONFIRM:		// ȷ�Ϸ��ڷ�����Ӧ��
		{	
			// �������ṩ��ͨ��ID
			memcpy_s(&m_dwServerID,4,pBuf+25,4);		
			// �߳�ID
			memcpy_s(&m_dwThreadID,4,pBuf+29,4);
			// �����ںż� ��Դ
			SendShotPointAndSource();
			// ���ʹ������Ͷ���
			SendProcessType();
			// ���Ͳɼ�����
			SendShotSpread();
			// ��������
			SendGeneralCMD(OPERATION_CMD_START);
			pFrm->WriteLog(_T("Confirm Ack!"));
			return;
		}
		break;
	case OPERATION_ACK_NAME:		// ������Ӧ��
		{
			// �������ɼ�������������Ӧ��ĸ���
			DWORD  dwNoAck;
			memcpy_s(&dwNoAck,4,pBuf+21,4);
			pFrm->WriteLog(_T("Named Ack!"));
			CString str;
			str.Format(_T("�ɼ�����������%d����Ӧ�����: %d,�Ƿ������"),m_pSpread->GetCount(), dwNoAck);
			if(pFrm->MessageBox(str,_T("����"),MB_YESNO|MB_ICONQUESTION)==IDYES)
			{
				// ȷ�Ϸ���
				
			}
		}
		break;
	default:
		break;
	}
}*/

/**
 * @brief ͨ������ͺ���
 * @note  ��ʩ����������ʩ���ͻ���ͨ�Ź����У��в��ֵ�����֡��ʽ��ͬ������������벻ͬ�����ø�ͨ�ú�����ʩ���������������ݡ�
 * @note  ֡��ʽΪ:
 * @note  ֡ͷ��2Byte����֡���ȣ�2Byte����֡������4Byte����֡���ͣ�1Byte����������(2Byte)�����ݸ�����2Byte������������ͨ�ű��ID(4byte)���߳�������(4byte)����У��λ��1Byte����֡β��2Byte��
 * @param  WORD  wCmdCode ������
 * @return �����ѷ��͵��ֽ�����
 */
int  CActiveShot::SendGeneralCMD(WORD  wCmdCode)
{
	if(!m_pShotSource ||!m_pShotPoint || !m_pSvrSocket)
		return -1;
	unsigned char		pBuf[26];
	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	// ֡��
	pBuf[2] = 24;
	pBuf[3] = 0;
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 0x01;
	// ������
	pBuf[9]  = LOBYTE(wCmdCode);
	pBuf[10] = HIBYTE(wCmdCode);
	// ���ݸ���
	pBuf[11] =0x08;
	pBuf[12] =0;
	// �ںš���Դ
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);
	// ֡У��
	pBuf[21]=0;
	// ֡β
	pBuf[22] = 0x14;
	pBuf[23] = 0x6F;

	return SendToServer(pBuf,24);
}
/**
 * @brief ���ͷ���������
 * @note  ��ѡ���ںź���Դ����ʩ�����������ͷ�������ʩ�����������յ������,Ѱ�ҿ����̡߳�
 * @note  ���øú���ǰ��Ӧ��������IP��ַ����m_dwServerIP��Ϊ�㲥��ַ��
 * @param  void
 * @return �����ѷ��͵��ֽ�����
 */
int  CActiveShot::SendRequestShotService()
{
	if(!m_pShotSource ||!m_pShotPoint || !m_pSvrSocket)
		return -1;
	unsigned char		pBuf[36];
	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	// ֡��
	pBuf[2] = 36;
	pBuf[3] = 0;
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 0x01;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_CMD_REQUEST);
	pBuf[10] = HIBYTE(OPERATION_CMD_REQUEST);
	// ���ݸ���
	pBuf[11] =20;
	pBuf[12] =0;
	// �ںš���Դ
	memcpy_s(pBuf+13,4,&m_dwShotNb,4);
	memcpy_s(pBuf+17,4,&m_dwSourceNb,4);
	// �ɼ�����
	memcpy_s(pBuf+21,4,&m_dwSpreadNb,4);
	// ��������
	memcpy_s(pBuf+25,4,&m_dwProcessNb,4);
	// �̣߳������������ɷ��������
	memset(pBuf+29,0,4);

	// ֡У��
	pBuf[33]=0;
	// ֡β
	pBuf[34] = 0x14;
	pBuf[35] = 0x6F;

	return SendToServer(pBuf,36);
}

int  CActiveShot::SendFDUConfig(CFDUConfig* pFDUConfig)
{
	if(!pFDUConfig)
		return -1;
	unsigned char		pBuf[52];
	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	// ֡��
	pBuf[2] = 52;
	pBuf[3] = 0;
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 0x02;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_CMD_FDUCONF);
	pBuf[10] = HIBYTE(OPERATION_CMD_FDUCONF);
	// ���ݸ���
	pBuf[11] =36;
	pBuf[12] =0;
	// �ںš���Դ
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);
	// �ɼ�վ������Ϣ
	memcpy_s(pBuf+21,4,&pFDUConfig->m_dwGain3301Index,4);	
	memcpy_s(pBuf+25,4,&pFDUConfig->m_dwMux3301Index,4);	
	memcpy_s(pBuf+29,4,&pFDUConfig->m_dwMode5373Index,4);
	memcpy_s(pBuf+33,4,&pFDUConfig->m_dwAttr5373Index,4);
	memcpy_s(pBuf+37,4,&pFDUConfig->m_dwSampleRateIndex,4);
	memcpy_s(pBuf+41,4,&pFDUConfig->m_dwFilterIIRIndex,4);
	memcpy_s(pBuf+45,4,&pFDUConfig->m_dwFilterFIRIndex,4);
	
	// ֡У��
	pBuf[49]=0;
	// ֡β
	pBuf[50] = 0x14;
	pBuf[51] = 0x6F;

	return SendToServer(pBuf,52);
}
/**
 * @brief ���Ͳɼ����еı�š���ǩ������
 * @note  ��ʩ��������������Ӻ��ڿ�ʼ����ǰ����������·��ɼ����С�
 ���Ͳɼ����з�Ϊ�������ȵ��øú������Ͳɼ����еı�š���ǩ�����ԣ�Ȼ�����SendShotSpreadChannel
 �������Ͳɼ����� 
 * @note  ֡��ʽΪ��֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
 ������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte����
 * @note  ��֡��ʽ��������������Ψһ���ID��4byte�����߳������ţ�4byte�� ,
                                �ɼ�����ţ�4Byte�����ɼ������ͣ�1Byte�����ɼ�����ǩ�����ֽ��ַ�������		  		  
 * @param  void
 * @return �����ѷ��͵��ֽ�����
 */
int   CActiveShot::SendShotSpreadLabel()
{
	if(!m_pShotSource ||!m_pShotPoint|| !m_pSpread || !m_pSvrSocket)
		return -1;
	// �ɼ����б�ǩ�ַ������ֽڳ���
	WORD wLabelLen = WORD(m_pSpread->m_strLabel.GetLength()*sizeof(TCHAR));
	// ֡���ܳ��� 
	WORD wFrmLen =wLabelLen+16+13+2;
		
	unsigned char*		pBuf=new unsigned char[wFrmLen];
	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	// ֡��
	pBuf[2] = LOBYTE(wFrmLen);
	pBuf[3] = HIBYTE(wFrmLen);
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����,����Ҫ����
	pBuf[8] = 0x02;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_CMD_SPREAD);
	pBuf[10] = HIBYTE(OPERATION_CMD_SPREAD);
	// ���ݸ���: 13Byte+ �ַ�������+2����\0���ַ�
	pBuf[11] =LOBYTE(15+wLabelLen);
	pBuf[12] =HIBYTE(15+wLabelLen);
	// ������ID���߳�ID
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);
	// �ɼ����б��
	memcpy_s(pBuf+21,4,&m_pSpread->m_dwNb,4);
	// �ɼ���������
	pBuf[25] = m_pSpread->m_bySpreadType;
	// �ɼ����б�ǩ
	memcpy_s(pBuf+26,wLabelLen, LPCTSTR(m_pSpread->m_strLabel),wLabelLen);
	pBuf[26+wLabelLen]='\0';	// ������
	pBuf[27+wLabelLen]='\0';

	// ֡У��
	pBuf[28+wLabelLen]=0;
	// ֡β
	pBuf[29+wLabelLen] = 0x14;
	pBuf[30+wLabelLen] = 0x6F;

	SendToServer(pBuf,wFrmLen);
	delete []pBuf;
	return wFrmLen;

}
/**
 * @brief ���Ͳɼ����к���
 * @note  ��ʩ��������������Ӻ��ڿ�ʼ����ǰ�����øú�������������·��ɼ����С�
 * @note  �ú����ڲ�ÿ�η���1000����ѭ����η���ֱ���ɼ����з�����ϡ�
 * @note  ֡��ʽΪ��֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
 ������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte����
 * @note  ��֡��ʽ��������������Ψһ���ID��4byte�����߳������ţ�4byte�� ,�ɼ������ԣ�21Byte����
		  ���вɼ�������Ϊһ�飬������n�顣
		  ֡��ʽ���ܳ���Ϊ 16+8+21*n������nΪ�ɼ���������
 * @param  void
 * @return �����ѷ��͵��ֽ�����
 */
int   CActiveShot::SendShotSpreadChannel()
{
	if(!m_pShotSource ||!m_pShotPoint|| !m_pSpread || !m_pSvrSocket)
		return -1;

	DWORD	dwFrmIndex=1;
	int		i;
	int		nCount = m_pSpread->GetCount(); 
	WORD	wLen; 
	unsigned char* pBuf=new unsigned char[21024];		// ����һ�η���1000���ɼ�����
	SHOTSPREAD*	pChannel=NULL;

	// ÿ�η���3000���ɼ�������Ҫ���Ͷ��ٴ�
	int  nCycleNum = nCount/1000;
	int  nIndex;

	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	// ֡��,ÿ�ι̶��ĵ���
	pBuf[2] = LOBYTE(21024);
	pBuf[3] = HIBYTE(21024);
	
	// ֡����,����Ҫ����
	pBuf[8] = 0x02;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_CMD_CHANNEL);
	pBuf[10] = HIBYTE(OPERATION_CMD_CHANNEL);
	// ������ID���߳�ID
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);
	for(i=0;i<nCycleNum;i++)
	{		
		// ֡����
		memcpy_s(pBuf+4,4,&dwFrmIndex,4);
		dwFrmIndex++;
		// �ɼ��������������ֽ���
		pBuf[11] = LOBYTE(1000);
		pBuf[12] = HIBYTE(1000);
			
		for(nIndex=0;nIndex<1000;nIndex++)
		{
			pChannel = &(m_pSpread->m_arrSpread[nIndex+i*1000]);
			memcpy_s(pBuf+21+21*nIndex,4,&(pChannel->m_dwIP),4);
			memcpy_s(pBuf+25+21*nIndex,4,&(pChannel->m_dwGain),4);
			memcpy_s(pBuf+29+21*nIndex,4,&(pChannel->m_dwLineNb),4);
			memcpy_s(pBuf+33+21*nIndex,4,&(pChannel->m_dwPointNb),4);
			memcpy_s(pBuf+37+21*nIndex,4,&(pChannel->m_dwChannelNb),4);			
			pBuf[41+21*nIndex] = pChannel->m_byType;
		}		
		// ֡У��
		pBuf[21021]=0;
		// ֡β
		pBuf[21022] = 0x14;
		pBuf[21023] = 0x6F;
		SendToServer(pBuf,21024);
	}

	nIndex = nCount%1000;	// �������ʣ��Ĳɼ���
	if (nIndex<=0)
	{
		delete []pBuf;
		return 21024;
	}
	// �������һ֡�ĳ���,���һ֡����1000��
	wLen = 24+21*nIndex;		 
	pBuf[2] = LOBYTE(wLen);
	pBuf[3] = HIBYTE(wLen);

	// ֡����
	memcpy_s(pBuf+4,4,&dwFrmIndex,4);
	// �ɼ��������������ֽ���
	// wLen = 8+21*nIndex;
	pBuf[11] = LOBYTE(nIndex);
	pBuf[12] = HIBYTE(nIndex);
	
	for(i=0;i<nIndex;i++)
	{
		pChannel =&( m_pSpread->m_arrSpread[i+nCycleNum*1000] );
		memcpy_s(pBuf+21+21*i,4,&(pChannel->m_dwIP),4);
		memcpy_s(pBuf+25+21*i,4,&(pChannel->m_dwGain),4);
		memcpy_s(pBuf+29+21*i,4,&(pChannel->m_dwLineNb),4);
		memcpy_s(pBuf+33+21*i,4,&(pChannel->m_dwPointNb),4);
		memcpy_s(pBuf+37+21*i,4,&(pChannel->m_dwChannelNb),4);			
		pBuf[41+21*i] = pChannel->m_byType;
	}		
	// ֡У��
	pBuf[21+21*i]=0;
	// ֡β
	pBuf[21+21*i+1] = 0x14;
	pBuf[21+21*i+2] = 0x6F;
	nIndex = SendToServer(pBuf,24+21*nIndex);
	delete []pBuf;
	return nIndex;

}

/**
 * @brief �����ڵ����Դ����
 * @note  ��ʩ��������������Ӻ��ڿ�ʼ����ǰ�����øú�����������·��ڵ����Լ���Դ���ԡ�
 * @note  ֡��ʽΪ��֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
 ������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte����
 * @note  ��֡��ʽ��������������������ID��4Byte�����߳�ID��4Byte����CShotPoint���󣨶��ֽڣ�,CShotSource���󣨶��ֽڣ���
 * @note  �ڴ洢����������У�ÿ���ַ����ĺ��涼���������ս�����'\0'��
 * @note  ���ڱ�ը����Դ�����������Ͳ�ͬ�洢�������Բ�ͬ������ʱҲҪ����������������ͬ����
 * @param  void
 * @return �����ѷ��͵��ֽ�����
 */
int  CActiveShot::SendShotPointAndSource()
{
	if(!m_pShotSource ||!m_pShotPoint || !m_pSvrSocket)
		return -1;

	unsigned char*		pBuf;
	WORD nFrmLen;	
	WORD nPointLen;
	WORD nLabelLen,nCommentLen; 
	LPCTSTR lpBuf;
	
	// �������ݳ���
	nPointLen = m_pShotPoint->m_szComments.GetLength()*sizeof(TCHAR);
	nLabelLen = m_pShotSource->m_strLabel.GetLength()*sizeof(TCHAR);
	nCommentLen = m_pShotSource->m_strComment.GetLength()*sizeof(TCHAR);
	nFrmLen = 97+nPointLen+nLabelLen+nCommentLen+4;
	pBuf = new unsigned char[nFrmLen + 9];
	if(!pBuf)
		return -1;
	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 0x01;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_CMD_SHOT);
	pBuf[10] = HIBYTE(OPERATION_CMD_SHOT);
	
	// ������ID���߳�ID
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);
	// �洢CShotPoint����		
	pBuf[21] = m_pShotPoint->m_VPState;
	pBuf[22] = m_pShotPoint->m_byBreakPoint;
	memcpy_s(pBuf+23,4,&(m_pShotPoint->m_dwShotNb),4);
	memcpy_s(pBuf+27,4,&(m_pShotPoint->m_dwSwathNb),4);
	memcpy_s(pBuf+31,4,&(m_pShotPoint->m_dwSourcePointIndex),4);
	memcpy_s(pBuf+35,4,&(m_pShotPoint->m_fSourceLine),4);
	memcpy_s(pBuf+39,4,&(m_pShotPoint->m_fSourceNb),4);
	memcpy_s(pBuf+43,4,&(m_pShotPoint->m_dwSpreadSFL),4);
	memcpy_s(pBuf+47,4,&(m_pShotPoint->m_dwSpreadSFN),4);
	memcpy_s(pBuf+51,4,&(m_pShotPoint->m_dwSpreadNb),4);
	memcpy_s(pBuf+55,4,&(m_pShotPoint->m_dwSuperSpread),4);
	memcpy_s(pBuf+59,4,&(m_pShotPoint->m_dwProcessNb),4);
	
	// �洢comment���������ַ������ַ���������Ҫ������������'\0'
	lpBuf= m_pShotPoint->m_szComments.GetBuffer();	
	memcpy_s(pBuf+63,nPointLen, LPCSTR(lpBuf),nPointLen); 
	m_pShotPoint->m_szComments.ReleaseBuffer();
	pBuf[63+nPointLen]='\0';	// ������
	pBuf[64+nPointLen]='\0';
	
	// �洢CShotSource����
//	memcpy_s(pBuf+23+nPointLen,nSourceLen,m_pShotSource,nSourceLen);
 	memcpy_s(pBuf+65+nPointLen,4,&(m_pShotSource->m_dwShotType),4);
 	pBuf[69+nPointLen]=m_pShotSource->m_bySourceState;
	memcpy_s(pBuf+70+nPointLen,4,&(m_pShotSource->m_dwSourceNb),4);
	memcpy_s(pBuf+74+nPointLen,4,&(m_pShotSource->m_dwShooterNb),4);
	memcpy_s(pBuf+78+nPointLen,4,&(m_pShotSource->m_lStep),4);
	memcpy_s(pBuf+82+nPointLen,4,&(m_pShotSource->m_dwSourceIndex),4);
	memcpy_s(pBuf+86+nPointLen,4,&(m_pShotSource->m_dwReadyVPNb),4);
	memcpy_s(pBuf+90+nPointLen,4,&(m_pShotSource->m_bReady),4);

	// �洢��ǩ����
	lpBuf= m_pShotSource->m_strLabel.GetBuffer();	
	memcpy_s(pBuf+94+nPointLen,nLabelLen, LPCSTR(lpBuf),nLabelLen);	
	m_pShotSource->m_strLabel.ReleaseBuffer();
	pBuf[94+nPointLen+nLabelLen]='\0';		// ������
	pBuf[95+nPointLen+nLabelLen]='\0';
	// Comment����
	lpBuf= m_pShotSource->m_strComment.GetBuffer();	
	memcpy_s(pBuf+96+nPointLen+nLabelLen, nCommentLen,LPCSTR(lpBuf), nCommentLen); 
	m_pShotSource->m_strComment.ReleaseBuffer();
	pBuf[96+nPointLen+nLabelLen+nCommentLen]='\0';		// ������
	pBuf[97+nPointLen+nLabelLen+nCommentLen]='\0';
	
	if(m_pShotSource->m_dwShotType == SHOTTYPE_EXPLO)	// ���屬ը��
	{
		// ���ݸ������ֽ���
		nFrmLen = 97+nPointLen+nLabelLen+nCommentLen-12;
		pBuf[11] =LOBYTE(nFrmLen);
		pBuf[12] =HIBYTE(nFrmLen);

		// ֡��
		nFrmLen = 97+nPointLen+nLabelLen+nCommentLen+4;
		pBuf[2] = LOBYTE(nFrmLen);
		pBuf[3] = HIBYTE(nFrmLen);	
	}
	else	// �ɿ���Դ��ը�� SHOTTYPE_VIBRO
	{
		CShotSourceVibro* pSource =(CShotSourceVibro*)m_pShotSource;
		pBuf[98+nPointLen+nLabelLen+nCommentLen]=pSource->m_byMoving;
		memcpy_s(pBuf+99+nPointLen+nLabelLen+nCommentLen,4,&(pSource->m_bWorkByAcq),4);
		memcpy_s(pBuf+103+nPointLen+nLabelLen+nCommentLen,4,&(pSource->m_dwClusterNb),4);

		// ���ݸ������ֽ���
		nFrmLen = 106+nPointLen+nLabelLen+nCommentLen-12;
		pBuf[11] =LOBYTE(nFrmLen);
		pBuf[12] =HIBYTE(nFrmLen);

		// ֡��
		nFrmLen = 106+nPointLen+nLabelLen+nCommentLen+4;
		pBuf[2] = LOBYTE(nFrmLen);
		pBuf[3] = HIBYTE(nFrmLen);	
	}

	// ֡У��
	pBuf[nFrmLen-3]=0;
	// ֡β
	pBuf[nFrmLen-2] = 0x14;
	pBuf[nFrmLen-1] = 0x6F;
	// �������ݰ�
	SendToServer(pBuf,nFrmLen);
	delete []pBuf;
	return 1;
}

/**
 * @brief �������ݴ�����
 * @note  ��ʩ��������������Ӻ��ڿ�ʼ����ǰ�����øú�����������·��ڵ����Լ���Դ���ԡ�
 * @note  ֡��ʽΪ��֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
 ������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte����
 * @note  ��֡��ʽ��������������������ID��4Byte�����߳�ID��4Byte����CProcessType���󣨶��ֽڣ���
 * @note  �ڴ洢����������У�ÿ���ַ����ĺ��涼���������ս�����'\0'��
 * @note  �������Ͳ�ͬ�洢�������Բ�ͬ������ʱҲҪ����������������ͬ����
 * @param  void
 * @return �����ѷ��͵��ֽ�����
 */
int  CActiveShot::SendProcessType(void)
{
	if(!m_pProcessType || !m_pSvrSocket)
		return -1;

	WORD  wFrmLen = WORD(m_pProcessType->GetObjectByteSize())+24;
	BYTE* pBuf=new BYTE[wFrmLen];

	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	// ֡��
	pBuf[2] = LOBYTE(wFrmLen);
	pBuf[3] = HIBYTE(wFrmLen);
	// ֡����
	memset(pBuf+4,1,4);
	// ֡����
	pBuf[8] = 0x02;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_CMD_PROCESS);
	pBuf[10] = HIBYTE(OPERATION_CMD_PROCESS);
	// ���ݸ���
	pBuf[11] =LOBYTE(wFrmLen-8);
	pBuf[12] =HIBYTE(wFrmLen-8);

	// ������ID���߳�ID
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);
	m_pProcessType->SaveToBuf(pBuf+21);
	
	pBuf[wFrmLen-3]=0;
	pBuf[wFrmLen-2]=0x14;
	pBuf[wFrmLen-1]=0x6F;

	// �������ݰ�
	SendToServer(pBuf,wFrmLen);
	delete []pBuf;
	return 1;

}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////    CActiveShots   /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
CActiveShots::CActiveShots(void)
{
}

CActiveShots::~CActiveShots(void)
{
	int i,nCount = m_arrActiveShot.GetCount();
	for (i=0;i<nCount;i++)
	{
		delete m_arrActiveShot[i];
		m_arrActiveShot[i] = NULL;
	}
	m_arrActiveShot.RemoveAll();
}
CActiveShot* CActiveShots::GetActiveShot(int iIndex)
{
	int nCount = GetCount();
	if(iIndex>=nCount)
		return NULL;

	return m_arrActiveShot[iIndex];
}
int CActiveShots::GetCount(void)
{
	return m_arrActiveShot.GetCount();
}
int CActiveShots::Add(CActiveShot* pActiveShot)
{
	return m_arrActiveShot.Add(pActiveShot);
}
CActiveShot* CActiveShots::LookActiveShot(CShotSource* pSource)
{
	int i,nCount = m_arrActiveShot.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(pSource==m_arrActiveShot[i]->m_pShotSource)
			return m_arrActiveShot[i];
	}
	return NULL;
}

void  CActiveShots::RemoveAt(int iIndex)
{
	m_arrActiveShot.RemoveAt(iIndex);
}