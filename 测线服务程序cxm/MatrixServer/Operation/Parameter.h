#ifndef _Parameter_H
#define _Parameter_H

// ������Դ��������
#define ActiveSourceNumLimit	10
// ���ݴ����������
#define PROCESS_IMPULSIVE		0		// ����
#define PROCESS_STACKIMPULSIVE	1		// �������
#define PROCESS_CORRELAFTER		2		// ���Ӻ����
#define PROCESS_CORRELBEFORE	3		// ����ǰ���
#define PROCESS_STACK			4		// �ɿ���Դ�������
// ��������ѡ��
#define PROCESS_STANDARD		0		// ��׼
#define PROCESS_ADVANCE			1		// �߼�
#define ControlsInterval		5		// �ؼ�֮��ļ��
// ����ѡ���ַ���
#define VIBROMOVING_STRING_SEQ  _T("SEQUIENTIAL")
#define VIBROMOVING_STRING_RND  _T("RANDOM")
/** �������������ھ���λ�ã���ǰ����ӿո�*/
extern void MoveTitleToCenter(CWnd* pWnd);
#endif