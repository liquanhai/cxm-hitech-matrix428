#pragma once
#include "workspacebar.h"
class CVPDoneBar :
	public CWorkSpaceBar
{
public:
	CVPDoneBar(void);
	~CVPDoneBar(void);
	// ���ñ�ͷ
	bool SetGridHead(void);
	// ����ȫ���ڵ���Ϣ
	void LoadShotPoints(void);
private:
	// ���뵥���ڵ���Ϣ
	void LoadShotPoint(void);
};

