#include "StdAfx.h"
#include "ShotController.h"
#include "..\common\LineStruct.h"
CShotController::CShotController(void)
: m_dwFDUIP(0)
, m_dwFDUSN(0)
, m_pHostSocket(NULL)
{
	m_dwShotNb = 0;
	/** ��Դ����� */
	m_fSourceLine= 0;
	/** ��Դ��� */
	m_fSourceNb= 0;
	/** ��Դ������ */
	m_dwSwathID= 0;
	/** ��ը���� */
	m_dwSourceNb= 0;
	/** ��ը��״̬ */
	m_byBlasterState= 0; 
	/** ȷ��TBʱ�� */
	m_fConfirmedTB= 0;
	/** ����ʱ�� */
	m_fUpholeTime= 0;
	m_bNewState = FALSE;
}

CShotController::~CShotController(void)
{
}
void   CShotController::Reset(void)
{
	m_dwShotNb = 0;
	/** ��Դ����� */
	m_fSourceLine= 0;
	/** ��Դ��� */
	m_fSourceNb= 0;
	/** ��Դ������ */
	m_dwSwathID= 0;
	/** ��ը���� */
	m_dwSourceNb= 0;
	/** ��ը��״̬ */
	m_byBlasterState= 0; 
	/** ȷ��TBʱ�� */
	m_fConfirmedTB= 0;
	/** ����ʱ�� */
	m_fUpholeTime= 0;
	m_bNewState = FALSE;
}
/**
 * @brief ���ñ�ը�������������Ĳɼ�վSN��
 * @note  ���ñ�ը�������������Ĳɼ�վSN��
 * @param DWORD dwSN,��ը�������������Ĳɼ�վSN��
 * @return void
 */
void CShotController::SetFDUSN(DWORD dwSN)
{
	m_dwFDUSN = dwSN;
	m_dwFDUIP = CIPList::GetBlastMachineIP(dwSN);
	SendFDUConfigCmd();
}
/**
 * @brief ���ͱ�ը�����ݷ��ص�������ַ���˿�
 * @note  ϵͳ������
 * @param unsigned char* pBuf������֡������
 * @paramint nSize�����������ݴ�С
 * @return �����Ѿ������껺�����ֽ�����ʧ���򷵻�0��
 */
int CShotController::SendFDUConfigCmd(void)
{
	unsigned char pBuf[128];
	if(!m_pHostSocket)
		return 0;
	memset(pBuf,0xAA,15);
	memcpy_s(pBuf+16,4,&m_pHostSocket->m_dwHostIP,sizeof(DWORD));
	memcpy_s(pBuf+20,4,&m_dwFDUIP,sizeof(DWORD));
	memcpy_s(pBuf+24,2,&m_pHostSocket->m_wBlasterPort,sizeof(WORD));
	pBuf[26]=0x01;
	pBuf[27]=0;			// ��������

	pBuf[32]=0x07;		// ������:�Զ����ݷ��ص�ַ
	memcpy_s(pBuf+33,4,&(m_pHostSocket->m_dwHostIP),sizeof(DWORD));

	pBuf[37]=0x08;		// ������
	pBuf[38]=LOBYTE(m_pHostSocket->m_wBlasterPort); // �Զ����ݷ��ض˿�(SOCKET_REV8PORT: 0xB000)
	pBuf[39]=HIBYTE(m_pHostSocket->m_wBlasterPort);
	pBuf[40]=0x03;		//  ����2Byte,( �������λΪ1ʱ��ʶ����ѭ���˿�,��λ��0x03��ʾ������������)
	pBuf[41]=0x00;

	pBuf[42] = 0;
	return m_pHostSocket->SendToFDU(pBuf,128);
}
// ���͵������
int CShotController::SendFireOrder(CShotClient* pShotClient)
{
	return false;
}
/**
 * @brief ������ը������֡
 * @note  �����������б���ı�ը�����ݡ�
 * @param unsigned char* pBuf������֡������
 * @paramint nSize�����������ݴ�С
 * @return �����Ѿ������껺�����ֽ�����ʧ���򷵻�0��
 */
bool CShotController::AnalysisFrame(unsigned char* pBuf,int nSize)
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CShotCtrlProII::CShotCtrlProII(void)
{
	
}

CShotCtrlProII::~CShotCtrlProII(void)
{
}

/**
 * @brief ��ը�����������͵��FO����
 * @note  ������������֡��ʽ��ը�����������͵������
 * @note  ��ʽ��
				*SP#.../SL#.../SN#.../SI#.../SEQ#...<CR><LF>
	���У�
								��С	���
	�ں�			SP#sssss	1		99999
	��Դ�����		SL#lllll.l	0.0		99999.9
	��Դ���		SN#lllll.l	0.0		99999.9
	��Դ������		SI#1		1		9
	��ը����		SEQ#ss		01		16

	* @param CShotClient* pShotClient������֡������
	* @return ���ͳɹ�����true�����򷵻�false��
*/
int CShotCtrlProII::SendFireOrder(CShotClient* pShotClient)
{
	if(!pShotClient || !m_pHostSocket)
		return false;

	unsigned char pBuf[128];
	int		nPos;
	memset(pBuf,0xAA,15);

	// Դ��ַ������IP
	nPos = 16;
	memcpy_s(pBuf+nPos,4,&(m_pHostSocket->m_dwHostIP),4);
	nPos+=4;
	// Ŀ���ַ���ɼ�վIP
	memcpy_s(pBuf+nPos,4,&m_dwFDUIP,4);
	nPos+=4;
	// Դ��ַ�Ķ˿ڣ��뱬ը�������������Ĳɼ�վͨ��Socket�˿�
	pBuf[nPos++] = LOBYTE(m_pHostSocket->m_wBlasterPort);
	pBuf[nPos++] = HIBYTE(m_pHostSocket->m_wBlasterPort);
	// ����
	pBuf[nPos++] = 0x03;
	pBuf[nPos++] = 0x00;

	// ������
	nPos = 32;
	pBuf[nPos++] = 0xFF;
	pBuf[nPos++] = 0xFF;
	// *SP#11111
	pBuf[nPos++] = '*';
	pBuf[nPos++] = 'S';
	pBuf[nPos++] = 'P';
	pBuf[nPos++] = '#';
	// ���5λ���ں�
	sprintf_s((char*)(pBuf+nPos),6,"% 5d",pShotClient->m_pShotPoint->m_dwShotNb);
	nPos+=5;
	pBuf[nPos++]='/';
	// ��Դ����ߣ�SL#lllll.l
	pBuf[nPos++] = 'S';
	pBuf[nPos++] = 'L';
	pBuf[nPos++] = '#';
	sprintf_s((char*)(pBuf+nPos),8,"% 5.1f",pShotClient->m_pShotPoint->m_fSourceLine);
	nPos+=7;
	pBuf[nPos++]='/';

	// SN#lllll.l
	pBuf[nPos++] = 'S';
	pBuf[nPos++] = 'N';
	pBuf[nPos++] = '#';
	sprintf_s((char*)(pBuf+nPos),8,"% 5.1f",pShotClient->m_pShotPoint->m_fSourceNb);
	nPos+=7;
	pBuf[nPos++]='/';

	// SI#1
	pBuf[nPos++] = 'S';
	pBuf[nPos++] = 'I';
	pBuf[nPos++] = '#';
	sprintf_s((char*)(pBuf+nPos),2,"%1d",pShotClient->m_pShotPoint->m_dwSwathNb);
	nPos+=1;
	pBuf[nPos++]='/';

	// SEQ#ss
	pBuf[nPos++] = 'S';
	pBuf[nPos++] = 'E';
	pBuf[nPos++] = 'Q';
	pBuf[nPos++] = '#';
	sprintf_s((char*)(pBuf+nPos),3,"% 2d",pShotClient->m_pShotSource->m_dwSourceNb);	// ?????????���Nb����100�����������
	nPos+=2;

	// <CR><LF>
	pBuf[nPos++]='\r';
	pBuf[nPos++]='\n';
	pBuf[nPos++] = '\0';
	return m_pHostSocket->SendToFDU(pBuf,128);
	
}
/**
 * @brief ������ը������֡
 * @note  �����������б���ı�ը�����ݡ�
 * @note  ���Ա�ը��������֡������λ֡��ʽ����������Ĳ�ͬ���н�����
          ������Ϊ01ʱ����Ҫ���������òɼ�վ����Ļ�������֡��
		  ������Ϊ02ʱ��ʱ��ѯ�ɼ�վ�Ĳ���������ڱ�ը�������Ĳɼ�վһ�㲻��Ҫ��ѯ״̬��
		  ������Ϊ03ʱ���Ǵ��͵ı�ը�����ݣ�����AnalysisBlasterToHostFrame����������
 * @param int nSize�����������ݴ�С
 * @return �����Ѿ������껺�����ֽ�����ʧ���򷵻�0��
 */
bool CShotCtrlProII::AnalysisFrame(unsigned char* pBuf,int nSize)
{
	// �ж�������
	WORD	wFrmCode;
	wFrmCode = MAKEWORD(pBuf[26],pBuf[27]);
	unsigned char*  pBufTemp=NULL;
	switch(wFrmCode)
	{
	case 1:
		{
			// ��ɼ�վ���ò����Ļ���, ����ú���SendFDUConfigCmd�Ļ���
			// �Ȳ�������ֱ�Ӷ���
			break;
		}
	case 2:
		{
			break;
		}
	case 3:
		{
			// ��ɼ�վ�������ݵĻ���Ȳ�����
			
			// ���Ա�ը��������,�Ƿ�Ϊ"*SHOTPRO "
			pBufTemp = pBuf+30;			
			if(    pBufTemp[0]=='*' && pBufTemp[1]=='S' && pBufTemp[2]=='H'
				&& pBufTemp[3]=='O' && pBufTemp[4]=='T' && pBufTemp[5]=='P'
				&& pBufTemp[6]=='R' && pBufTemp[7]=='O' && pBufTemp[8]==' ')
				AnalysisBlasterToHostFrame(pBuf+30,228);
			break;
		}
	default:
		return false;
	}
	return true;
}
/**
 * @brief ������ը������֡
 * @note  �����������б���ı�ը�����ݡ�
 * @note  ��ʽ��*SHOTPRO SP#.../SL#.../SN#.../SI#.../SEQ#.../STA:../CTB:00.000/UH:000.0
 ����: SHOTPRO ����ʶ�����ϵͳ���ַ���

									��С	���
 �ں�					SP#sssss	1		99999
 ��Դ�����				SL#lllll.l	0.0		99999.9
 ��Դ���				SN#lllll.l	0.0		99999.9
 ��Դ������				SI#1		1		9
 ��ը����				SEQ#ss		01		16
 ��ը��״̬				STA:s		0		7
 ȷ�ϵ�ʱ���ź�			CTB:cc.ccc	00.000	33.000
 ����ʱ�䣨������ʰȡ�� UH:uuu.u	000.0	999.5 ��.5 ���벽����

 * @param unsigned char* pBuf������֡������,����λ֡�е�����������30���ֽڿ�ʼ����
 * @param int nSize�����������ݴ�С
 * @return �����Ѿ������껺�����ֽ�����ʧ���򷵻�0��
 */
bool CShotCtrlProII::AnalysisBlasterToHostFrame(unsigned char* pBuf,int nSize)
{
	unsigned char byTemp[10];
	int nPos=0;
	// �ж����ݳ���
	// WORD  wDataLen = MAKEWORD(pBuf[nPos],pBuf[nPos+1]);
	// if(wDataLen<77)
	// 	return false;
	// nPos+=2; 
	// *
	if(pBuf[nPos++]!='*')
		return false;

	// �Ƿ�Ϊ"SHOTPRO "
	if(    pBuf[nPos]  !='S'|| pBuf[nPos+1]!='H'
		|| pBuf[nPos+2]!='O'|| pBuf[nPos+3]!='T'
		|| pBuf[nPos+4]!='P'|| pBuf[nPos+5]!='R'
		|| pBuf[nPos+6]!='O'|| pBuf[nPos+7]!=' ')
		return false;
	nPos+=8;
	// �ж� "SP#" 
	if( pBuf[nPos]!='S'|| pBuf[nPos+1]!='P'|| pBuf[nPos+2]!='#')
		return false;
	nPos+=3;
	// �ں�
	byTemp[0] = pBuf[nPos++];
	byTemp[1] = pBuf[nPos++];
	byTemp[2] = pBuf[nPos++];
	byTemp[3] = pBuf[nPos++];
	byTemp[4] = pBuf[nPos++];
	byTemp[5] = '\0';
	byTemp[6] = '\0';

	if(pBuf[nPos++]!='/')
		return false;
	m_dwShotNb = atoi((char *)byTemp);

	// �ж� "SL#" 
	if( pBuf[nPos]!='S'|| pBuf[nPos+1]!='L'|| pBuf[nPos+2]!='#')
		return false;
	nPos+=3;
	byTemp[0] = pBuf[nPos++];
	byTemp[1] = pBuf[nPos++];
	byTemp[2] = pBuf[nPos++];
	byTemp[3] = pBuf[nPos++];
	byTemp[4] = pBuf[nPos++];
	byTemp[5] = pBuf[nPos++];
	byTemp[6] = pBuf[nPos++];
	byTemp[7] = '\0';
	byTemp[8] = '\0';
	if(pBuf[nPos++]!='/')
		return false;
	m_fSourceLine =(float)atof((char *)byTemp);

	// �ж� "SN#" 
	if( pBuf[nPos]!='S'|| pBuf[nPos+1]!='N'|| pBuf[nPos+2]!='#')
		return 0;
	nPos+=3;
	byTemp[0] = pBuf[nPos++];
	byTemp[1] = pBuf[nPos++];
	byTemp[2] = pBuf[nPos++];
	byTemp[3] = pBuf[nPos++];
	byTemp[4] = pBuf[nPos++];
	byTemp[5] = pBuf[nPos++];
	byTemp[6] = pBuf[nPos++];
	byTemp[7] = '\0';
	byTemp[8] = '\0';
	if(pBuf[nPos++]!='/')
		return false;
	m_fSourceNb =(float)atof((char *)byTemp);

	// �ж� "SI#" 
	if( pBuf[nPos]!='S'|| pBuf[nPos+1]!='I'|| pBuf[nPos+2]!='#')
		return false;
	nPos+=3;
	byTemp[0] = pBuf[nPos++];
	byTemp[1] = '\0';
	byTemp[2] = '\0';
	if(pBuf[nPos++]!='/')
		return false;
	m_dwSwathID =atoi((char *)byTemp);

	// �ж�SEQ#
	if( pBuf[nPos]!='S'|| pBuf[nPos+1]!='E'|| pBuf[nPos+2]!='Q'|| pBuf[nPos+3]!='#')
		return 0;
	nPos+=4;
	byTemp[0] = pBuf[nPos++];
	byTemp[1] = pBuf[nPos++];
	byTemp[2] = '\0';
	byTemp[3] = '\0';
	if(pBuf[nPos++]!='/')
		return false;
	m_dwSourceNb =atoi((char *)byTemp);
	// �ж�STA:
	if( pBuf[nPos]!='S'|| pBuf[nPos+1]!='T'|| pBuf[nPos+2]!='A'|| pBuf[nPos+3]!=':')
		return false;
	nPos+=4;
	byTemp[0] = pBuf[nPos++];	
	byTemp[1] = '\0';
	byTemp[2] = '\0';
	if(pBuf[nPos++]!='/')
		return false;
	m_byBlasterState =byTemp[0]-'0';

	// �ж�CTB:cc.ccc
	if( pBuf[nPos]!='C'|| pBuf[nPos+1]!='T'|| pBuf[nPos+2]!='B'|| pBuf[nPos+3]!=':')
		return false;
	nPos+=4;
	byTemp[0] = pBuf[nPos++];
	byTemp[1] = pBuf[nPos++];
	byTemp[2] = pBuf[nPos++];
	byTemp[3] = pBuf[nPos++];
	byTemp[4] = pBuf[nPos++];
	byTemp[5] = pBuf[nPos++];
	byTemp[6] = '\0';
	byTemp[7] = '\0';
	byTemp[8] = '\0';
	if(pBuf[nPos++]!='/')
		return false;
	m_fUpholeTime =(float)atof((char *)byTemp);
	// ����״̬
	m_bNewState = TRUE;
	return true;
}