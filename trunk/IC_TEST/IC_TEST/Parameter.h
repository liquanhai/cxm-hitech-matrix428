
#ifndef Parameter_h
#define Parameter_h

// �Ƿ����Ա��½��־λ
extern bool m_bAdmin;
// ��ͷ����
#define FrameHead1					0x55
#define FrameHead2					0xAA
// ƥ������
#define MatchCmd					0xAC
// ��ƥ������
#define NoMatchCmd					0xAB
// ProgramVPPStd������
#define ProgramVPPStdCmd			0xA1
// ProgramVPPLo������
#define ProgramVPPLoCmd				0xA2
// ReadVddLo������
#define ReadVddLoCmd				0xA3
// ReadVddHi������
#define ReadVddHiCmd				0xA4
// ReadMargin1������
#define ReadMargin1Cmd				0xA5
// ReadMargin2������
#define ReadMargin2Cmd				0xA6
// ReadMarginOffState������
#define ReadMarginOffStateCmd		0xA7
// ����IRC������
#define TestIRCCmd					0xA8
// ��дIRC������
#define ProgramIRCCmd				0xAA
// ��дSCR������
#define ProgramSCRCmd				0xAD
// ����������
#define EndCmd						0xAF
// Programѡ��
#define ProgramVPPStd		_T("OTP Program with VPP_std")
#define ProgramVPPLo		_T("OTP Program with VPP_Lo")
// Readbackѡ��
#define ReadVddLo			_T("Read with Vdd_Lo")
#define ReadVddHi			_T("Read with Vdd_Hi")
#define ReadMargin1			_T("Margin-1 Read")
#define ReadMargin2			_T("Margin-2 Read")
#define	ReadMarginOffState	_T("off-state Margin Read")
// �Զ���������ݴ洢�ļ���Ϣ
#define WM_RECV_SAVE_DATA	WM_USER + 101
#endif
