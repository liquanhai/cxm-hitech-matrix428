#pragma once
#include "InstrumentList.h"
#include "LogFile.h"
// CHeadFrameSocket 命令目标

class CHeadFrameSocket : public CSocket
{
public:
	CHeadFrameSocket();
	virtual ~CHeadFrameSocket();
	virtual void OnReceive(int nErrorCode);
protected:
	// 仪器串号
	DWORD m_uiSN;
	// 首包时刻
	DWORD m_uiHeadFrameTime;
	// 路由地址
	DWORD m_uiRoutAddress;
	// 首包接收数据缓冲
	byte m_pHeadFrameData[RcvFrameSize];
	// 设置IP地址缓冲
	byte m_pIPSetFrameData[SndFrameSize];
public:
	// 仪器列表指针
	CInstrumentList* m_pInstrumentList;
	// 源IP地址
	CString m_csIPSource;
	// 发送端口
	unsigned int m_uiSendPort;
	// 界面指针
	CWnd* m_pwnd;
	// 日志类指针
	CLogFile* m_pLogFile;
protected:
	// 处理单个首包
	void ProcHeadFrameOne();
	// 解析首包
	BOOL ParseHeadFrame(void);
	// 防止程序在循环中运行无法响应消息
	void ProcessMessages(void);
public:
	// 生成IP地址设置帧
	void MakeIPSetFrame(CInstrument* pInstrument, BOOL bSetIP);
	// 发送IP地址设置帧
	void SendIPSetFrame(void);
	// 监测IP地址设置应答帧
	bool OnMonitorIPSetReturn(void);
};