#include "StdAfx.h"
#include "InstrumentList.h"
#include "Parameter.h"
#include "Resource.h"
CInstrumentList::CInstrumentList(void)
: m_pInstrumentArray(NULL)
, m_uiCountFree(0)
, m_pWnd(NULL)
, m_pLogFile(NULL)
, m_pInstrumentGraph(NULL)
{
}

CInstrumentList::~CInstrumentList(void)
{
}

// 初始化
//************************************
// Method:    OnInit
// FullName:  CInstrumentList::OnInit
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::OnInit(void)
{
	m_pInstrumentArray = new CInstrument[InstrumentMaxCount];
	m_uiCountFree = InstrumentMaxCount;
// 	//初始化哈希表，并指定其大小
// 	m_oInstrumentMap.InitHashTable(InstrumentMaxCount);
}

// 关闭
//************************************
// Method:    OnClose
// FullName:  CInstrumentList::OnClose
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::OnClose(void)
{
	// 清空空闲仪器队列
	m_olsInstrumentFree.clear();
	if (m_pInstrumentArray != NULL)
	{
		delete[] m_pInstrumentArray;
	}
	// 删除索引表中所有仪器
	m_oInstrumentSNMap.clear();
}

// 得到一个空闲仪器
//************************************
// Method:    GetFreeInstrument
// FullName:  CInstrumentList::GetFreeInstrument
// Access:    public 
// Returns:   CInstrument*
// Qualifier:
// Parameter: void
//************************************
CInstrument* CInstrumentList::GetFreeInstrument(void)
{
	CInstrument* pInstrument = NULL;
	list <CInstrument*>::iterator iter;
	if(m_uiCountFree > 0)	//有空闲仪器
	{
		// 从空闲队列中得到一个仪器
		iter = m_olsInstrumentFree.begin();
		pInstrument = *iter;
		m_olsInstrumentFree.pop_front();	
		pInstrument->m_bInUsed = true;	// 设置仪器为使用中
		m_uiCountFree--;	// 空闲仪器总数减1
	}
	else
	{
		AfxMessageBox(_T("已无空闲仪器！"));
		m_pLogFile->OnWriteLogFile(_T("CInstrumentList::GetFreeInstrument"), _T("已无空闲仪器！"), ErrorStatus);
	}
	return pInstrument;
}

// 将一个仪器加入索引表
//************************************
// Method:    AddInstrumentToMap
// FullName:  CInstrumentList::AddInstrumentToMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument * pInstrument
//************************************
void CInstrumentList::AddInstrumentToSNMap(unsigned int uiIndex, CInstrument* pInstrument)
{
//	SetInstrumentLocation(pInstrument);
	m_oInstrumentSNMap.insert(hash_map<unsigned int, CInstrument*>::value_type (uiIndex, pInstrument));
}

// 判断仪器索引号是否已加入索引表
//************************************
// Method:    IfIndexExistInMap
// FullName:  CInstrumentList::IfIndexExistInMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
//************************************
BOOL CInstrumentList::IfIndexExistInSNMap(unsigned int uiIndex)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentSNMap.find(uiIndex);
	if (iter != m_oInstrumentSNMap.end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// 根据输入索引号，由索引表得到仪器指针
//************************************
// Method:    GetInstrumentFromMap
// FullName:  CInstrumentList::GetInstrumentFromMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument *  & pInstrument
//************************************
BOOL CInstrumentList::GetInstrumentFromSNMap(unsigned int uiIndex, CInstrument* &pInstrument)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentSNMap.find(uiIndex);
	if (iter != m_oInstrumentSNMap.end())
	{
		pInstrument = iter->second;
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// 将一个仪器加入IP地址索引表
//************************************
// Method:    AddInstrumentToIPMap
// FullName:  CInstrumentList::AddInstrumentToIPMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument * pInstrument
//************************************
void CInstrumentList::AddInstrumentToIPMap(unsigned int uiIndex, CInstrument* pInstrument)
{
	m_oInstrumentIPMap.insert(hash_map<unsigned int, CInstrument*>::value_type (uiIndex, pInstrument));
}

// 判断仪器索引号是否已加入IP地址索引表
//************************************
// Method:    IfIndexExistInIPMap
// FullName:  CInstrumentList::IfIndexExistInIPMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
//************************************
BOOL CInstrumentList::IfIndexExistInIPMap(unsigned int uiIndex)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentIPMap.find(uiIndex);
	if (iter != m_oInstrumentIPMap.end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// 根据输入IP地址索引号，由IP地址索引表得到仪器指针
//************************************
// Method:    GetInstrumentFromIPMap
// FullName:  CInstrumentList::GetInstrumentFromIPMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument *  & pInstrument
//************************************
BOOL CInstrumentList::GetInstrumentFromIPMap(unsigned int uiIndex, CInstrument* &pInstrument)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentIPMap.find(uiIndex);
	if (iter != m_oInstrumentIPMap.end())
	{
		pInstrument = iter->second;
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// 设备根据首包时刻排序
//************************************
// Method:    SetInstrumentLocation
// FullName:  CInstrumentList::SetInstrumentLocation
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CInstrument * pInstrument
//************************************
void CInstrumentList::SetInstrumentLocation(CInstrument* pInstrument)
{
	int iLocation = 0;
	unsigned int uiFDULocation = 0;
	CString str = _T("");
	// hash_map迭代器，效率比map高
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
//		ProcessMessages();
		if (NULL != iter->second)
		{
			// 线号相同
			if (iter->second->m_iLineIndex == pInstrument->m_iLineIndex)
			{
				// 方向相同并包含交叉线上的交叉站或LCI
				if ((iter->second->m_uiLineDirection == pInstrument->m_uiLineDirection)
					|| (iter->second->m_uiLineDirection == DirectionCenter)
					|| (iter->second->m_uiLineDirection == DirectionTop)
					|| (iter->second->m_uiLineDirection == DirectionDown))
				{
					if (pInstrument->m_uiHeadFrameTime > iter->second->m_uiHeadFrameTime)
					{
						if (pInstrument->m_uiLineDirection == DirectionLeft)
						{
							iLocation--;
						}
						else if (pInstrument->m_uiLineDirection == DirectionRight)
						{
							iLocation++;
						}
						if ((pInstrument->m_uiInstrumentType == InstrumentTypeFDU)
							&& (iter->second->m_uiInstrumentType == InstrumentTypeFDU))
						{
							uiFDULocation++;
						}
					}
				}
 			}
		}
	}

	if (iLocation == pInstrument->m_iLocation)
	{
		// 首包计数器加一
		pInstrument->m_iHeadFrameCount++;
	}
	else
	{
		pInstrument->m_iHeadFrameCount = 0;
		pInstrument->m_iLocation = iLocation;
		pInstrument->m_uiFDULocation = uiFDULocation;
//		pInstrumentAdd->m_uiFDULocation = uiLocation - 1;
	}
	str.Format(_T("仪器SN%x，仪器首包时刻%d，仪器位置%d，采集站位置%d，仪器类型%d！"), pInstrument->m_uiSN, 
		pInstrument->m_uiHeadFrameTime, pInstrument->m_iLocation, pInstrument->m_uiFDULocation, pInstrument->m_uiInstrumentType);
	m_pLogFile->OnWriteLogFile(_T("CInstrumentList::SetInstrumentLocation"), str, SuccessStatus);
}

// 删除尾包之后的仪器
//************************************
// Method:    TailFrameDeleteInstrument
// FullName:  CInstrumentList::TailFrameDeleteInstrument
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CInstrument * pInstrumentDelete
//************************************
void CInstrumentList::TailFrameDeleteInstrument(CInstrument* pInstrumentDelete)
{
	// 删除交叉线尾包之后的仪器
	if (pInstrumentDelete->m_iLocation == 0)
	{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
	// 删除大线方向尾包之后的仪器
	else
	{
		TailFrameDeleteInstrumentLine(pInstrumentDelete);
	}
}	

// 清理过期的尾包时刻查询结果
//************************************
// Method:    ClearExperiedTailTimeResult
// FullName:  CInstrumentList::ClearExperiedTailTimeResult
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::ClearExperiedTailTimeResult(void)
{
	// hash_map迭代器
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
//		ProcessMessages();
		if (NULL != iter->second)
		{
			// 发送尾包时刻查询但是在下一个尾包接收之前未回复的设置过期标志
			if (iter->second->m_bSendTailTimeFrame == true)
			{
				if (iter->second->m_bTailTimeReturnOK == false)
				{
					iter->second->m_bTailTimeExpired = true;
				}
			}
			iter->second->m_bSendTailTimeFrame = false;
			iter->second->m_bTailTimeReturnOK = false;
		}
	}
	m_pLogFile->OnWriteLogFile(_T("CInstrumentList::ClearExperiedTailTimeResult"), _T("清理过期的尾包时刻查询帧！"), WarningStatus);
}

// 开始
//************************************
// Method:    OnOpen
// FullName:  CInstrumentList::OnOpen
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::OnOpen(void)
{
	// 清空空闲仪器队列
	m_olsInstrumentFree.clear();
	// 删除索引表中所有仪器
	m_oInstrumentSNMap.clear();
	m_oInstrumentIPMap.clear();
	if (m_pInstrumentArray != NULL)
	{
		delete []m_pInstrumentArray;
	}
	m_pInstrumentArray = new CInstrument[InstrumentMaxCount];

	for(unsigned int i = 0; i < InstrumentMaxCount; i++)
	{
		// 重置仪器
		m_pInstrumentArray[i].OnReset();
		// 仪器在仪器数组中的位置
		m_pInstrumentArray[i].m_uiIndex = i;
		// 仪器加在空闲仪器队列尾部
		m_olsInstrumentFree.push_back(&m_pInstrumentArray[i]);
	}
	m_uiCountFree = InstrumentMaxCount;
}
// 停止
//************************************
// Method:    OnStop
// FullName:  CInstrumentList::OnStop
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::OnStop(void)
{
	// 清空空闲仪器队列
	m_olsInstrumentFree.clear();
	m_pInstrumentArray = NULL;
	// 删除索引表中所有仪器
	m_oInstrumentSNMap.clear();
	m_oInstrumentIPMap.clear();
}

// 删除所有仪器
//************************************
// Method:    DeleteAllInstrument
// FullName:  CInstrumentList::DeleteAllInstrument
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::DeleteAllInstrument(void)
{
	unsigned int icount = m_oInstrumentSNMap.size();
	if (icount == 0)
	{
		return;
	}
	// hash_map迭代器
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentIPMap.begin(); iter!=m_oInstrumentIPMap.end();)
	{
		//		ProcessMessages();
		if (NULL != iter->second)
		{
			//@@@@@@@ 暂时不加入界面显示设备
// 			// 显示设备断开连接的图标
// 			OnShowDisconnectedIcon(iter->second->m_uiIPAddress);
			// 将仪器从IP索引表中删除
			m_oInstrumentIPMap.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
	// 清除界面仪器和连接线显示
	m_pInstrumentGraph->OnClearAllInstrumentGraph();
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end();)
	{
		//		ProcessMessages();
		if (NULL != iter->second)
		{
			// 重置仪器
			iter->second->OnReset();
			// 仪器加在空闲仪器队列尾部
			m_olsInstrumentFree.push_back(iter->second);
			m_uiCountFree++;
			// 将仪器从索引表中删除
			m_oInstrumentSNMap.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
	m_pLogFile->OnWriteLogFile(_T("CInstrumentList::DeleteAllInstrument"), _T("未收到尾包，删除所有在线仪器！"), WarningStatus);
}
//@@@@@@@ 暂时不加入界面显示设备
// 根据IP地址显示设备断开连接的图标
//************************************
// Method:    OnShowDisconnectedIcon
// FullName:  CInstrumentList::OnShowDisconnectedIcon
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIPAddress
//************************************
// void CInstrumentList::OnShowDisconnectedIcon(unsigned int uiIPAddress)
// {
// 	CButton* iconbutton = NULL;
// 	CStatic* iconstatic = NULL;
// 	CButton* pButton = NULL;
// 
// 	// hash_map迭代器
// 	hash_map<unsigned int, CInstrument*>::iterator  iter;
// 	CInstrument* pInstrument = NULL;
// 	if (GetInstrumentFromIPMap(uiIPAddress, pInstrument))
// 	{
// 		if (pInstrument->m_uiInstrumentType == InstrumentTypeLAUX)
// 		{
// 			iconstatic =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_LAUX);
// 			iconstatic->SetIcon(m_iconLAUXDisconnected);
// 		}
// 		else if (pInstrument->m_uiInstrumentType == InstrumentTypeFDU)
// 		{
// 
// 			iconbutton = (CButton*)m_pwnd->GetDlgItem(m_iButtonIDFDU[pInstrument->m_uiLocation - 1]);
// 			iconbutton->SetIcon(m_iconFDUDisconnected);
// 			pButton = (CButton*)m_pwnd->GetDlgItem(m_iCheckIDInstrumentFDU[pInstrument->m_uiLocation - 1]);
// 			pButton->SetCheck(0);
// 		}
// 	}
// }

// 防止程序在循环中运行无法响应消息
//************************************
// Method:    ProcessMessages
// FullName:  CInstrumentList::ProcessMessages
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// 判断仪器连接线号
void CInstrumentList::OnSetInstrumentLineIndex(CInstrument* pInstrument)
{
	// hash_map迭代器
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
		if (NULL != iter->second)
		{
			if ((iter->second->m_uiInstrumentType == InstrumentTypeLCI)
				|| (iter->second->m_uiInstrumentType == InstrumentTypeLAUX))
			{
				if (iter->second->m_uiRoutAddressTop == pInstrument->m_uiRoutAddress)
				{
					pInstrument->m_iLineIndex = iter->second->m_iLineIndex - 1;
					if (pInstrument->m_uiInstrumentType == InstrumentTypeLAUX)
					{
						iter->second->m_pInstrumentTop = pInstrument;
						pInstrument->m_pInstrumentDown = iter->second;
					}
					break;
				}
				else if (iter->second->m_uiRoutAddressDown == pInstrument->m_uiRoutAddress)
				{
					pInstrument->m_iLineIndex = iter->second->m_iLineIndex + 1;
					if (pInstrument->m_uiInstrumentType == InstrumentTypeLAUX)
					{
						iter->second->m_pInstrumentDown = pInstrument;
						pInstrument->m_pInstrumentTop = iter->second;
					}
					break;
				}
				else if ((iter->second->m_uiRoutAddressLeft == pInstrument->m_uiRoutAddress)
					|| (iter->second->m_uiRoutAddressRight == pInstrument->m_uiRoutAddress))
				{
					pInstrument->m_iLineIndex = iter->second->m_iLineIndex;
					break;
				}
			}
		}
	}
}

// 建立仪器的连接关系
void CInstrumentList::OnInstrumentConnect(CInstrument* pInstrument)
{
	int iLocation = pInstrument->m_iLocation;
	// 找到前一个仪器
	if (pInstrument->m_uiLineDirection == DirectionLeft)
	{
		iLocation++;
	}
	else if (pInstrument->m_uiLineDirection == DirectionRight)
	{
		iLocation--;
	}
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
		if (NULL != iter->second)
		{
			if (iter->second->m_iLineIndex == pInstrument->m_iLineIndex)
			{
				if (iter->second->m_iLocation == iLocation)
				{
					if (pInstrument->m_uiLineDirection == DirectionLeft)
					{
						iter->second->m_pInstrumentLeft = pInstrument;
						pInstrument->m_pInstrumentRight = iter->second;
					}
					else if (pInstrument->m_uiLineDirection == DirectionRight)
					{
						iter->second->m_pInstrumentRight = pInstrument;
						pInstrument->m_pInstrumentLeft= iter->second;
					}
					break;
				}
			}
		}
	}
}

// 清除相同路由仪器的尾包计数
void CInstrumentList::OnClearSameRoutTailCount(CInstrument* pInstrument)
{
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
		if (NULL != iter->second)
		{
			if (iter->second->m_uiRoutAddress == pInstrument->m_uiRoutAddress)
			{
				if (pInstrument->m_uiLineDirection == DirectionLeft)
				{
					if (iter->second->m_iLocation > pInstrument->m_iLocation)
					{
						iter->second->m_iTailFrameCount = 0;
					}
				}
				else if (pInstrument->m_uiLineDirection == DirectionRight)
				{
					if (iter->second->m_iLocation < pInstrument->m_iLocation)
					{
						iter->second->m_iTailFrameCount = 0;
					}
				}
			}
		}
	}
}

// 删除大线方向尾包之后的仪器
void CInstrumentList::TailFrameDeleteInstrumentLine(CInstrument* pInstrumentDelete)
{
	// hash_map迭代器
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	hash_map<unsigned int, CInstrument*>::iterator  iter2;
	CString str = _T("");
	// 删除大线方向尾包之后的仪器
	for(iter=m_oInstrumentIPMap.begin(); iter!=m_oInstrumentIPMap.end();)
	{
		if (NULL != iter->second)
		{
			if (iter->second->m_iLineIndex == pInstrumentDelete->m_iLineIndex)
			{
				if ((pInstrumentDelete->m_uiLineDirection == DirectionLeft)
					&& (pInstrumentDelete->m_iLocation > iter->second->m_iLocation))
				{
					m_pInstrumentGraph->DrawUnit(iter->second->m_iLocation, iter->second->m_iLineIndex, 
						iter->second->m_uiLineDirection, iter->second->m_uiInstrumentType, iter->second->m_uiSN, iter->second->m_uiFDULocation,
						GraphInstrumentOffLine, true);

					iter2 = m_oInstrumentSNMap.find(iter->second->m_uiSN);
					// 将仪器从SN索引表中删除
					m_oInstrumentSNMap.erase(iter2);
					str.Format(_T("清理尾包之后的仪器IP为%d"), iter->first);
					m_pLogFile->OnWriteLogFile(_T("CInstrumentList::TailFrameDeletRoutInstrument"), str, WarningStatus);
					// 重置仪器
					iter->second->OnReset();
					// 仪器加在空闲仪器队列尾部
					m_olsInstrumentFree.push_back(iter->second);
					m_uiCountFree++;
					// 将仪器从IP索引表中删除
					m_oInstrumentIPMap.erase(iter++);
					pInstrumentDelete->m_pInstrumentLeft = NULL;
				}
				else if ((pInstrumentDelete->m_uiLineDirection == DirectionRight)
					&& (pInstrumentDelete->m_iLocation < iter->second->m_iLocation))
				{
					m_pInstrumentGraph->DrawUnit(iter->second->m_iLocation, iter->second->m_iLineIndex, 
						iter->second->m_uiLineDirection, iter->second->m_uiInstrumentType, iter->second->m_uiSN, iter->second->m_uiFDULocation,
						GraphInstrumentOffLine, true);

					iter2 = m_oInstrumentSNMap.find(iter->second->m_uiSN);
					// 将仪器从SN索引表中删除
					m_oInstrumentSNMap.erase(iter2);
					str.Format(_T("清理尾包之后的仪器IP为%d"), iter->first);
					m_pLogFile->OnWriteLogFile(_T("CInstrumentList::TailFrameDeletRoutInstrument"), str, WarningStatus);
					// 重置仪器
					iter->second->OnReset();
					// 仪器加在空闲仪器队列尾部
					m_olsInstrumentFree.push_back(iter->second);
					m_uiCountFree++;
					// 将仪器从IP索引表中删除
					m_oInstrumentIPMap.erase(iter++);
					pInstrumentDelete->m_pInstrumentRight = NULL;
				}
				else
				{
					iter++;
				}
			}
			else
			{
				iter++;
			}
		}
		else
		{
			iter++;
		}
	}
}
