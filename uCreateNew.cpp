//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uCreateNew.h"
#include "uSignIn.h"
#include "uMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfCreateNew *fCreateNew;
//---------------------------------------------------------------------------
__fastcall TfCreateNew::TfCreateNew(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfCreateNew::eNameChange(TObject *Sender)
{
	if (eName->Text.Length() == 0) {
		bCreate->Enabled = false;
	} else if (cbCurrency->ItemIndex != -1 && eBalance->Text.Length() != 0)
	{
		bCreate->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfCreateNew::cbCurrencyChange(TObject *Sender)
{
	if (cbCurrency->ItemIndex == -1) {
		bCreate->Enabled = false;
	} else if (eName->Text.Length() != 0 && eBalance->Text.Length() != 0)
	{
		bCreate->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfCreateNew::eBalanceChange(TObject *Sender)
{
	if (eBalance->Text.Length() == 0) {
		bCreate->Enabled = false;
	} else if (eName->Text.Length() != 0 && cbCurrency->ItemIndex != -1)
	{
		bCreate->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfCreateNew::bCreateClick(TObject *Sender)
{
	fSignIn->cbChoose->Items->Add(eName->Text);
	int Index = fSignIn->cbChoose->Items->IndexOf(eName->Text);
	fSignIn->cbChoose->ItemIndex = Index;
	fSignIn->bStartWork->Enabled = true;
	fMain->CurrentWallet.Name = eName->Text;
	Index = cbCurrency->ItemIndex;
	switch (Index) {
	case 0:
		fMain->CurrentWallet.CurrencyName = "BYN";
	break;
	case 1:
		fMain->CurrentWallet.CurrencyName = "RUB";
	break;
	case 2:
		fMain->CurrentWallet.CurrencyName = "USD";
	break;
	case 3:
		fMain->CurrentWallet.CurrencyName = "EUR";
	break;
	}
	fMain->CurrentWallet.Balance = StrToCurr(eBalance->Text);
	fMain->CurrentWallet.TransactionAmount = 0;
	fMain->CurrentWallet.TransactionChain = new Transaction[200];
	fMain->CurrentWallet.PossibleTransactionChain = 0;
	fMain->CurrentWallet.PossibleTransactionChain = new Transaction[200];
	fMain->RenewBalanceLabel();
	fMain->lName->Caption = "\"" + fMain->CurrentWallet.Name + "\"";
	if (!eSalary->Text.IsEmpty()) {
		Currency Value = StrToCurr(eSalary->Text);
		int Current = fMain->CurrentWallet.PossibleTransactionAmount;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Name = "Зарплата";
		fMain->CurrentWallet.PossibleTransactionChain[Current].Category = NONE;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Type = INCOME;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Repeat = EVERYMONTH;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Value = Value;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Date =
		  cpCalendarPicker->Date;
		fMain->CurrentWallet.PossibleTransactionAmount = Current + 1;
	}
	fCreateNew->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfCreateNew::FormActivate(TObject *Sender)
{
	cpCalendarPicker->Date = fMain->cpCalendarPicker->Date;
	eName->SetFocus();
}
//---------------------------------------------------------------------------

