#include "stdafx.h"
#include "OperaStruct.h"
#include "SocketParam.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////    CShotPoint  ////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/**
 * @brief CShotPoint���캯��
 */
CShotPoint::CShotPoint()
: m_VPState(VP_TODO)
, m_dwShotNb(0)
, m_byBreakPoint(SHOTPOINT_BREAK_NO)
, m_dwSwathNb(1)
, m_dwSourcePointIndex(1)
, m_fSourceLine(0)
, m_fSourceNb(0)
, m_dwSpreadNb(1)
, m_dwSpreadSFL(0)
, m_dwSpreadSFN(0)
, m_dwSuperSpread(1)
, m_dwProcessNb(0)
, m_szComments(_T(""))
{

}
/**
 * @brief CShotPoint��������
 */
CShotPoint::~CShotPoint(void)
{

}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////    CShotSource  ////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/**
 * @brief CShotSource���캯��
 */
CShotSource::CShotSource(void)
: m_dwSourceNb(0)
, m_dwSourceType(SHOTTYPE_EXPLO)
, m_strLabel(_T(""))
, m_dwShooterNb(0)
, m_strComment(_T(""))
, m_lStep(0)
, m_dwSourceIndex(0)
, m_dwReadyVPNb(0)
, m_bReady(FALSE)
{
	m_bySourceState = SHOTSOURCE_UNUSED;
}
/**
 * @brief CShotSource��������
 */
CShotSource::~CShotSource(void)
{
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////   CShotSourceExplo   //////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/**
 * @brief CShotSourceExplo���캯��
 */
CShotSourceExplo::CShotSourceExplo(void)
{
	m_dwSourceType=SHOTTYPE_EXPLO;
}
/**
 * @brief CShotSourceExplo��������
 */
CShotSourceExplo::~CShotSourceExplo(void)
{
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
///////////////////////////      CShotSourceVibro    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brief CShotSourceVibro���캯��
 */
CShotSourceVibro::CShotSourceVibro(void)
: m_bWorkByAcq(false)
, m_dwClusterNb(1)

{
	m_byMoving = VIBROMOVING_SEQUENTIAL;
	m_dwSourceType = SHOTTYPE_VIBRO;
}
/**
 * @brief CShotSourceVibro��������
 */
CShotSourceVibro::~CShotSourceVibro(void)
{
}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////      CAuxChannel      ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
CAuxChannel::~CAuxChannel(void)
{

}

CAuxChannels::~CAuxChannels(void)
{
	RemoveAll();
}
/**
 * @brief ɾ�����и���������
 * @note  ɾ�����и���������
 * @param void
 * @return void
 */
void   CAuxChannels::RemoveAll(void)
{
	int i,nCount = m_arrAuxChannel.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_arrAuxChannel[i])
		{
			delete m_arrAuxChannel[i];
			m_arrAuxChannel[i] = NULL;
		}	
	}
	m_arrAuxChannel.RemoveAll();
}
// ͨ��������ø���������������0��ʼ
/**
 * @brief ͨ��������ø���������������0��ʼ
 * @note  ͨ��������ø���������������0��ʼ
 * @param int iIndex��������
 * @return �ɹ��򷵻�ָ�룬ʧ���򷵻�NULL
 */
CAuxChannel* CAuxChannels::GetAuxChannel(int iIndex)
{
	int nCount = GetCount();
	if(iIndex>=nCount)
		return NULL;

	return m_arrAuxChannel[iIndex];
}
/**
 * @brief ͨ���ڵ��Ų��Ҷ���
 * @note  ͨ���ڵ��Ų��Ҷ��󣬷��ظ���������
 * @param DWORD dwNb�����
 * @return �ɹ��򷵻ظ���������ʧ���򷵻�NULL
 */
CAuxChannel* CAuxChannels::GetAuxChannelByNb(DWORD dwNb)
{
	int i,nCount = m_arrAuxChannel.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_arrAuxChannel[i]->m_dwNb == dwNb)
		{			
			return m_arrAuxChannel[i];
		}	
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////      CShotSpread      ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief CShotSpread���캯��
 */
CShotSpread::CShotSpread(void)
{
	m_dwNb = 0;
	m_strLabel = _T("");
	m_bySpreadType = SPREADTYPE_ABSOLUTE;
}
/**
 * @brief CShotSpread��������
 
 * �ͷ����еĲɼ������ݡ�
 */
CShotSpread::~CShotSpread(void)
{
	m_arrSpread.RemoveAll();
}

/**
 * @brief ���Ҳɼ�����
 * @note  ͨ��IP��ַ���Ҳɼ��� ��
 * @param  unsigned long dwIP���ɼ���IP��ַ��
 * @return ����ҵ������زɼ����������������ţ����û�ҵ����򷵻�-1��
 */
int CShotSpread::Find(unsigned long dwIP)
{
	int i,nCount;
	nCount = m_arrSpread.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_arrSpread[i].m_dwIP == dwIP)
			return i;
	}
	return -1;
}
/**
 * @brief ��Ӳɼ�����
 * @note  ��ɼ����������һ���ɼ�����
 * @param  SHOTSPREAD&  ShotSpread���ɼ���
 * @return �����ڲɼ��������������š�
 */
int CShotSpread::Append(SHOTSPREAD&  ShotSpread)
{
	return m_arrSpread.Add(ShotSpread);
}
/**
 * @brief �ɼ���������
 * @note  ɾ���ɼ�������ȫ���ɼ������󣬱�ż���������������
 * @param  void
 * @return ���ظ�����������
*/
void CShotSpread::ReleaseAll(void)
{
	m_arrSpread.RemoveAll();
	m_dwNb = 0;
	m_dwAuxiCount= 0;
} 
/**
 * @brief ���㸨��������
 * @note  ���㸨��������
 * @param  void
 * @return ���ظ�����������

unsigned long CShotSpread::GetAuxiChannelCount(void)
{
	unsigned long  lSum = 0;
	int i,nCount=m_arrSpread.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_arrSpread[i].m_byType = CHN_AUXI)
			lSum++;
	}
	return lSum;
} */

/**
 * @brief �ɼ����е���ȫ����Ӧ��
 * @note  ��ɼ����е����󣬵��øú�����ͨ������ÿ���ɼ���m_lAckedType�����ж��Ƿ���Ӧ��
 * @param  long bAckedValue, Ӧ������
 * @return ������вɼ�������Ӧ���򷵻�true�������������false
 */
bool CShotSpread::IsAllAcked(long bAckedValue)
{
	int i,nCount=m_arrSpread.GetCount();
	for(i=0;i<nCount;i++)
	{
		if(m_arrSpread[i].m_byType!=CHN_MUTE) // �����Ƶ�
		{
			if(bAckedValue == SHOTSPREAD_ACKED_CONFIGCMD)
			{	// ����ǵ������������ֱ���ж�
				if(m_arrSpread[i].m_lAckedType!= bAckedValue )
					return false;
			}
			else
			{
				// ����Ӧ��״̬���ǵ�����������,����������ڣ���bAckedValue��Ӧ�𲻴��ڣ�����Ϊ��ǰ������Ӧ��
				if(m_arrSpread[i].m_lAckedType>SHOTSPREAD_ACKED_NULL && m_arrSpread[i].m_lAckedType!= bAckedValue)
					return false;
			}
			
		}		
	}
	return true;
}

/**
 * @brief ������Ӧ��Ĳɼ���������
 * @note  ͨ������ÿ���ɼ���m_lAckedType��������������Ӧ��Ĳɼ���������
          дSEGD�����е���
 * @param  void
 * @return ������Ӧ��Ĳɼ���������
 */
unsigned int  CShotSpread::TotalOfAcked(void)
{
	unsigned int nSum=0;
	int i,nCount=m_arrSpread.GetCount();
	for(i=0;i<nCount;i++)
	{
		if(m_arrSpread[i].m_lAckedType && m_arrSpread[i].m_byType!=CHN_AUXI)
		{
		    nSum++;
		}		
	}
	return nSum;
}
/**
 * @brief ���òɼ�����Ӧ���־
 * @note  ͨ��IP��ַ���Ҳɼ�����λ�ã���������Ӧ���־��
 * @param  DWORD dwIP���ɼ�����IP��ַ��
 * @return ����ҵ��ɼ���������Ӧ���־���򷵻�true�����û���ҵ��ɼ������򷵻�false��
 */
bool CShotSpread::SetAck(DWORD dwIP,long lAckedType)
{
	int i,nCount=m_arrSpread.GetCount();
	for(i=0;i<nCount;i++)
	{
		if(m_arrSpread[i].m_dwIP == dwIP)
		{
			m_arrSpread[i].m_lAckedType=lAckedType;
			return true;
		}
	}
	return false;
}

/////////////////////////////   ���ݴ������Ͷ���  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////      CProcessType      ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief CProcessType���캯��
 */
CProcessType::CProcessType(void)
: m_ProcessSetup(PROCESS_STANDARD)
, m_byProcessType(PROCESS_IMPULSIVE)
, m_dwRecordLen(1000)
{
}
/**
 * @brief CProcessType��������
 */
CProcessType::~CProcessType(void)
{
	m_arrAuxiChannel.RemoveAll();
}

/**
 * @brief ���㴦�����Ͷ�����ֽ���
 * @note  ���㴦�����Ͷ�������������ܵ��ֽڳ��ȣ�����ÿ���ַ�������Ҫ���������ֽڵ�'\0';
 �������飬Ҫ�����ĸ��ֽڵ��������ֵ��
 * @param  void
 * @return ���ش������Ͷ��������ܵ��ֽ�����
 */
DWORD CProcessType::GetObjectByteSize()
{
	DWORD  dwSize =18;
	dwSize+=m_strLabel.GetLength()*sizeof(TCHAR)+2;
	dwSize+=m_arrAuxiChannel.GetCount()*sizeof(AUXICHANNEL)+4;	// ��Ҫ�����С���ڱ�������
	return dwSize;
}

/**
 * @brief ���洦�����Ͷ���
 * @note  ���������Ͷ�����������д�뻺����������ÿ���ַ�������Ҫ���������ֽڵ�'\0';
 �������飬Ҫ�����ĸ��ֽڵ��������ֵ��һ�����ڽ����󱣴��ڻ��������͸���һ�ˡ�
 * @param  unsigned char* pBuf��������ָ��
 * @return ���ر���Ĵ������Ͷ�����ռ���������ֽ�����
 */
int  CProcessType::SaveToBuf(unsigned char* pBuf)
{
	DWORD nLen=0;
	DWORD i=0,nCount=0;
	// �ȱ��洦������
	pBuf[0]=m_byProcessType;
	pBuf[1]=m_ProcessSetup;
	memcpy_s(pBuf+2,4,&(m_dwProcessNb),4);
	memcpy_s(pBuf+6,4,&(m_dwFDUSN),4);
	memcpy_s(pBuf+10,4,&(m_dwRecordLen),4);
	memcpy_s(pBuf+14,4,&(m_dwTBWindow),4);
	
	nCount = m_arrAuxiChannel.GetCount();
	memcpy_s(pBuf+18,4,&(nCount),4);
	nLen = 22;	// ��ǰ������ָ��
	for (i=0;i<nCount;i++)
	{
		memcpy_s(pBuf+nLen,sizeof(AUXICHANNEL),&(m_arrAuxiChannel[i]),sizeof(AUXICHANNEL));
		nLen+=sizeof(AUXICHANNEL);	// (i+1)*
	}
	nCount = m_strLabel.GetLength()*sizeof(TCHAR);
	memcpy_s(pBuf+nLen,nCount, LPCTSTR(m_strLabel),nCount);	
	pBuf[nLen+nCount]='\0';
	pBuf[nLen+nCount+1]='\0';
	return nLen+nCount+2;
}

/**
 * @brief ��ȡ�������Ͷ���
 * @note  ��SaveToBuf�������Ӧ�����������Ͷ����������Դӻ���������������ÿ���ַ�������Ҫ���������ֽڵ�'\0';
 �������飬Ҫ�ȶ��ĸ��ֽڵ������Сֵ��һ�����ڽ����󱣴��ڻ��������͸���һ�ˣ��ӻ�����������
 * @param  unsigned char* pBuf��������ָ��
 * @return ���ش������Ͷ�����ռ���������ֽ�����
 */
int  CProcessType::ReadFromBuf(unsigned char* pBuf)
{
	DWORD nLen=0;
	DWORD i=0,nCount=0;
	m_byProcessType=pBuf[0];
	m_ProcessSetup=pBuf[1];
	memcpy_s(&(m_dwProcessNb),4,pBuf+2,4);
	memcpy_s(&(m_dwFDUSN),4,pBuf+6,4);
	memcpy_s(&(m_dwRecordLen),4,pBuf+10,4);
	memcpy_s(&(m_dwTBWindow),4,pBuf+14,4);

	memcpy_s(&(nCount),4,pBuf+18,4);
	m_arrAuxiChannel.SetSize(nCount);	
	nLen = 22;	// ��ǰ������ָ��
	for (i=0;i<nCount;i++)
	{	
		memcpy_s(&(m_arrAuxiChannel[i]),sizeof(AUXICHANNEL),pBuf+nLen,sizeof(AUXICHANNEL));
		nLen+=sizeof(AUXICHANNEL);	// (i+1)*
	}	
	//memcpy_s(pBuf+nLen,nCount, LPCTSTR(m_strLabel),nCount);	
	m_strLabel = LPCTSTR(pBuf+nLen);
	nCount = m_strLabel.GetLength()*sizeof(TCHAR);
	return nLen+nCount+2;

}
/*
 * @brief ���ƴ������Ͷ���
 * @note  ����һ�����󽫴���Ҫ�󿽱�����������ȫ����һ���µĶ���
 * @param  CProcessType* pProcessSrc�����ݴ������
 * @return bool��
 
bool  CProcessType::Copy(CProcessType* pProcessSrc)
{
	unsigned char *pBuf;
	DWORD nSize =pProcessSrc->GetObjectByteSize();
	pBuf = new unsigned char[nSize];
	if(pBuf==NULL)
		return false;
	pProcessSrc->SaveToBuf(pBuf);
	this->ReadFromBuf(pBuf);
	delete[]pBuf;
	return true;
}
*/
/////////////////////////////   ���ݴ������Ͷ���  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////      CProcessImpulsive      ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief CProcessImpulsive���캯��
 */
CProcessImpulsive::CProcessImpulsive(void)
{
	m_dwRefractionDelay = 0;
	m_dwTBWindow = 1000;
}
/**
 * @brief CProcessImpulsive��������
 */
CProcessImpulsive::~CProcessImpulsive(void)
{
}
/**
 * @brief ���㴦�����Ͷ�����ֽ���
 * @note  ���㴦�����Ͷ�������������ܵ��ֽڳ��ȣ�����ÿ���ַ�������Ҫ���������ֽڵ�'\0';
 �������飬Ҫ�����ĸ��ֽڵ��������ֵ��
 * @param  void
 * @return ���ش������Ͷ��������ܵ��ֽ�����
 */
DWORD CProcessImpulsive::GetObjectByteSize()
{
	return CProcessType::GetObjectByteSize()+4;
}
/**
 * @brief ���洦�����Ͷ���
 * @note  ���������Ͷ�����������д�뻺����������ÿ���ַ�������Ҫ���������ֽڵ�'\0';
 �������飬Ҫ�����ĸ��ֽڵ��������ֵ��һ�����ڽ����󱣴��ڻ��������͸���һ�ˡ�
 �ȵ��û���Ķ��������Ӹö������е����ԡ�
 * @param  unsigned char* pBuf��������ָ��
 * @return ���ر���Ĵ������Ͷ�����ռ���������ֽ�����
 */
int  CProcessImpulsive::SaveToBuf(unsigned char* pBuf)
{
	int nLen = CProcessType::SaveToBuf(pBuf);
	memcpy_s(pBuf+nLen,4,&m_dwRefractionDelay,4);
	return nLen+4;

}
/**
 * @brief ��ȡ�������Ͷ���
 * @note  ��SaveToBuf�������Ӧ�����������Ͷ����������Դӻ���������������ÿ���ַ�������Ҫ���������ֽڵ�'\0';
 �������飬Ҫ�ȶ��ĸ��ֽڵ������Сֵ��һ�����ڽ����󱣴��ڻ��������͸���һ�ˣ��ӻ�����������
 * @param  unsigned char* pBuf��������ָ��
 * @return ���ش������Ͷ�����ռ���������ֽ�����
 */
int  CProcessImpulsive::ReadFromBuf(unsigned char* pBuf)
{
	int nLen = CProcessType::ReadFromBuf(pBuf);
	memcpy_s(&m_dwRefractionDelay,4,pBuf+nLen,4);
	return nLen+4;
}
/////////////////////////////   ʩ���ͻ������Թ���  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////       CShotClient      ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief CShotClient���캯��
 */
CShotClient::CShotClient(void)
: m_dwClientIP ( 0xC00A8C0)
, m_wClientPort( OPERATION_CLIENTPORT  )
, m_pShotSource(NULL),m_pShotPoint(NULL),m_pSpread(NULL), m_pProcessType(NULL)
, m_pFDUConfig(NULL)
, m_strNormalFilePath(_T("D:\\"))
, m_strTestFilePath(_T("D:\\"))
, m_dwFileNumber(1)
, m_strFileName(_T(""))
, m_strSEGDFileName(_T(""))
{
	if(m_pShotSource)
	{
		delete m_pShotSource;
		m_pShotSource = NULL;
	}
	if(m_pShotPoint)
	{
		delete m_pShotPoint;
		m_pShotPoint = NULL;
	}
	if(m_pSpread)
	{
		delete m_pSpread;
		m_pSpread = NULL;
	}
	if(m_pProcessType)
	{
		delete m_pProcessType;
		m_pProcessType = NULL;
	}
	if(m_pFDUConfig)
	{
		delete m_pFDUConfig;
		m_pFDUConfig = NULL;
	}
}
/**
 * @brief CShotClient��������
 �ͷ��ڵ㡢��Դ���ɼ����С��������Ͷ���
 */
CShotClient::~CShotClient(void)
{
	if(m_pShotSource)
	{
		delete m_pShotSource;
		m_pShotSource = NULL;
	}
	if(m_pShotPoint)
	{
		delete m_pShotPoint;
		m_pShotPoint = NULL;
	}
	if(m_pSpread)
	{
		delete m_pSpread;
		m_pSpread = NULL;
	}
	if(m_pProcessType)
	{
		delete m_pProcessType;
		m_pProcessType = NULL;
	}
	if(m_pFDUConfig)
	{
		delete m_pFDUConfig;
		m_pFDUConfig = NULL;
	}
}
