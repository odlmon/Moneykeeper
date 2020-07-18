//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMain.h"
#include "uSignIn.h"
#include "uAdd.h"
#include "uView.h"
#include "uEdit.h"
#include "uDiagrams.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfMain *fMain;
//---------------------------------------------------------------------------
__fastcall TfMain::TfMain(TComponent* Owner)
	: TForm(Owner)
{
	lTime->Caption = DateToStr(Date());
	IsQuiting = false;
}
//---------------------------------------------------------------------------
void __fastcall TfMain::FormShow(TObject *Sender)
{
    cpCalendarPicker->Date = Date();
	fSignIn->ShowModal();
	if (IsQuiting) {
        Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfMain::CategoryClick(TObject *Sender)
{
	LastCategoryClicked = ((TImage*)(Sender))->Tag;
	switch (LastCategoryClicked) {
		case 0:
			LastCategoryName = "products";
			break;
		case 1:
			LastCategoryName = "cafe";
			break;
		case 2:
			LastCategoryName = "leisure";
			break;
		case 3:
			LastCategoryName = "transport";
			break;
		case 4:
			LastCategoryName = "health";
			break;
		case 5:
			LastCategoryName = "gifts";
			break;
		case 6:
			LastCategoryName = "family";
			break;
		case 7:
			LastCategoryName = "purchases";
			break;
	}
    fAdd->ShowModal();
}
//---------------------------------------------------------------------------

void _fastcall TfMain::RenewBalanceLabel()
{
	FormatSettings.CurrencyString = CurrentWallet.CurrencyName;
	FormatSettings.CurrencyFormat = 4;
	lBalance->Caption = CurrToStrF(CurrentWallet.Balance, ffCurrency, 2);
}

void __fastcall TfMain::miChangeClick(TObject *Sender)
{
    fSignIn->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::miViewOutClick(TObject *Sender)
{
	ViewComeType = LOSS;
	fView->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::miViewInClick(TObject *Sender)
{
	ViewComeType = INCOME;
    fView->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::miEditOutClick(TObject *Sender)
{
	EditComeType = LOSS;
	fEdit->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::miEditInClick(TObject *Sender)
{
	EditComeType = INCOME;
    fEdit->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfMain::miDiagramsClick(TObject *Sender)
{
	fDiagrams->ShowModal();
}
//---------------------------------------------------------------------------

