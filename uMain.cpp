//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMain.h"
#include "uSignIn.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfMain *fMain;
//---------------------------------------------------------------------------
__fastcall TfMain::TfMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfMain::FormShow(TObject *Sender)
{
    fSignIn->ShowModal();
}
//---------------------------------------------------------------------------
