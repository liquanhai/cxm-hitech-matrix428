#pragma once
#include "workspacebar.h"
class CVPToDoBar :
	public CWorkSpaceBar
{
public:
	CVPToDoBar(void);
	~CVPToDoBar(void);
	// ���ñ�ͷ
	bool SetGridHead(void);
	// ����ȫ���ڵ���Ϣ
	void LoadShotPoints(void);
private:
	// ���뵥���ڵ���Ϣ
	void LoadShotPoint(void);
};

