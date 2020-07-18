//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSignIn.h"
#include "uMain.h"
#include "uCreateNew.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfSignIn *fSignIn;
//---------------------------------------------------------------------------
__fastcall TfSignIn::TfSignIn(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfSignIn::cbChooseChange(TObject *Sender)
{
	if (cbChoose->ItemIndex != -1) {
		bStartWork->Enabled = true;
	} else {
        bStartWork->Enabled = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TfSignIn::bStartWorkClick(TObject *Sender)
{
	fSignIn->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfSignIn::bCreateNewClick(TObject *Sender)
{
    fCreateNew->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfSignIn::bQuitClick(TObject *Sender)
{
	fMain->IsQuiting = true;
    Close();
}
//---------------------------------------------------------------------------

