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
#define VIBROMOVING_STRING_SEQ	_T("SEQUIENTIAL")
#define VIBROMOVING_STRING_RND	_T("RANDOM")
#define SHOTBREAKPOINT_STRING_NO	_T("No")
#define SHOTBREAKPOINT_STRING_YES	_T("Yes")
#define ACQSIGNSTACK_STRING_PLUS	_T("plus")
#define ACQOUTPUT_STRING_NONE		_T("none")
#define ACQOUTPUT_STRING_DUMP		_T("dump")
#define ACQOUTPUT_STRING_XDUMP		_T("xdump")
// OutPut�������
#define OutPutStoreRowsLimit	200
/** C/S���ջ�������С*/
#define ClientRecBufferSize					8192000
/** C/S���ͻ�������С*/
#define ClientSndBufferSize					8192000
/** �������������ھ���λ�ã���ǰ����ӿո�*/
extern void MoveTitleToCenter(CWnd* pWnd);
#endif