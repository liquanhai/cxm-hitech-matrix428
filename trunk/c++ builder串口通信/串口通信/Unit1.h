//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MSCommLib_OCX.h"
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
#include <NMUDP.hpp>


#define FRAMELEN_SEND 128
#define FRAMELEN_REC 256
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMSComm *MSComm1;
        TButton *Button1;
        TNMUDP *nmdp_send;
        TNMUDP *nmdp_rec;
        TButton *Button2;
        TEdit *Edit1;
        void __fastcall FormCreate(TObject *Sender);

        void __fastcall MSComm1Comm(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall nmdp_recDataReceived(TComponent *Sender,
          int NumberBytes, AnsiString FromIP, int Port);
        void __fastcall serial_DataSend(unsigned char* buff,unsigned int uiCount);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        int rec_point;                      //�����ַ�ָ�룬ָ��ĿǰӦ�ô洢��λ�����
        int rec_length;                     //�����Ļ��ж����ַ���Ҫ����
        int send_lenth;
        int rec_lenth;
        unsigned char rec_buf[4096];        //���ڽ��ջ�����
       // int    send_length;                    //������Ҫ���͵��ַ�����

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
