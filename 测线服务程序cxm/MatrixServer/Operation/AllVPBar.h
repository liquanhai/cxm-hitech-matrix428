#pragma once
#include "workspacebar.h"
class CAllVPBar :
	public CWorkSpaceBar
{
public:
	CAllVPBar(void);
	~CAllVPBar(void);
	// ���ñ�ͷ
	bool SetGridHead(void);
	// ����ȫ���ڵ���Ϣ
	void LoadShotPoints(void);
private:
	// ���뵥���ڵ���Ϣ
	void LoadShotPoint(void);

};

