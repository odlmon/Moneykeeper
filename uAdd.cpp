//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAdd.h"
#include "uMain.h"
#include <stack>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfAdd *fAdd;
typedef struct _Notation {
	UnicodeString Value;
	int RelPrior, StackPrior, Rank;
} Notation;
//---------------------------------------------------------------------------
Notation MakeNotation(UnicodeString Value, int RelPrior, int StackPrior, int Rank)
{
	Notation Item;
	Item.Value = Value;
	Item.RelPrior = RelPrior;
	Item.StackPrior = StackPrior;
	Item.Rank = Rank;
	return Item;
}
Notation* _fastcall ParseInputStr(UnicodeString Str, int *size)
{
	Notation* PostFix = new Notation[*size];
	int i = 1, Current = 0;
	while (i <= *size)
	{
		if (UnicodeString(Str[i]) == "+" || UnicodeString(Str[i]) == "-") {
			PostFix[Current++] = MakeNotation(Str[i], 1, 2, -1);
		} else if (UnicodeString(Str[i]) == "*" || UnicodeString(Str[i]) == "/") {
			PostFix[Current++] = MakeNotation(Str[i], 3, 4, -1);
		} else if (UnicodeString(Str[i]) == "^") {
			PostFix[Current++] = MakeNotation(Str[i], 6, 5, -1);
		} else if (UnicodeString(Str[i]) == "(") {
			PostFix[Current++] = MakeNotation(Str[i], 9, 0, -2);
		} else if (UnicodeString(Str[i]) == ")") {
			PostFix[Current++] = MakeNotation(Str[i], 0, -2, -2);
		} else if ((UnicodeString(Str[i]) >= "0" && UnicodeString(Str[i]) <= "9")
		  || UnicodeString(Str[i]) == ",")
		{
			UnicodeString Value = "";
			while (i <= *size && ((UnicodeString(Str[i]) >= "0" &&
			  UnicodeString(Str[i]) <= "9") || UnicodeString(Str[i]) == ","))
			{
				Value = Value + UnicodeString(Str[i]);
				i++;
			}
			i--;
			PostFix[Current++] = MakeNotation(Value, 7, 8, 1);
		}
        i++;
	}
	Notation *Temp = new Notation[Current];
	for (int i = 0; i < Current; i++) {
		Temp[i] = PostFix[i];
	}
    *size = Current;
	return Temp;
}
Notation* _fastcall StackConversion(Notation *PostFix, int *size) {
	int Current = 0;
	Notation* Result = new Notation[*size];
	stack<Notation> Stack;
	for (int i = 0 ; i < *size; i++) {
		if (Stack.empty()) {
			Stack.push(PostFix[i]);
		} else if (PostFix[i].RelPrior > Stack.top().StackPrior) {
			Stack.push(PostFix[i]);
		} else if (PostFix[i].Value == ")") {
			while (Stack.top().Value != "(")
			{
				Result[Current++] = Stack.top();
				Stack.pop();
			}
			Stack.pop();
		} else {
			while (!Stack.empty() &&
			  (PostFix[i].RelPrior <= Stack.top().StackPrior)) {
				Result[Current++] = Stack.top();
				Stack.pop();
			}
			Stack.push(PostFix[i]);
        }
	}
	while (!Stack.empty()) {
		Result[Current++] = Stack.top();
		Stack.pop();
	}
	Notation* Temp = new Notation[Current];
	for (int i = 0; i < Current; i++) {
		Temp[i] = Result[i];
	}
	*size = Current;
	return Temp;
}
Currency _fastcall Calculate(Notation* PostFix, int size) {
	stack<Currency> Stack;
	for (int i = 0; i < size; i++) {
		if (PostFix[i].Rank == 1) {
			Stack.push(StrToCurr(PostFix[i].Value));
		} else {
			Currency a = Stack.top();
			Stack.pop();
			Currency b = Stack.top();
			Stack.pop();
			if (PostFix[i].Value == "+") {
				a = b + a;
			} else if (PostFix[i].Value == "-") {
				a = b - a;
			} else if (PostFix[i].Value == "*") {
				a = b * a;
			} else if (PostFix[i].Value == "/") {
				a = b / a;
			} else if (PostFix[i].Value == "^") {
				a = (Currency) pow(b, (int) a);
			}
			Stack.push(a);
        }
	}
	return Stack.top();
}
Currency _fastcall GetValue(UnicodeString Str)
{
	int size = Str.Length();
	Notation *PostFix = new Notation[size];
	PostFix = ParseInputStr(Str, &size);
	PostFix = StackConversion(PostFix, &size);
	return Calculate(PostFix, size);
}
//---------------------------------------------------------------------------
__fastcall TfAdd::TfAdd(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfAdd::FormShow(TObject *Sender)
{
	cpCalendarPicker->Date = fMain->cpCalendarPicker->Date;
	eSum->Text = "";
	eName->Text = "";
	cbRepeat->ItemIndex = 0;
    cpCalendarPicker->Date = Date();
	TPngImage *Png = new TPngImage();
	Png->LoadFromResourceName((int) HInstance, fMain->LastCategoryName);
	iCategory->Picture->Graphic = Png;
	delete Png;
}
//---------------------------------------------------------------------------
void __fastcall TfAdd::bAcceptClick(TObject *Sender)
{
	Currency Value = GetValue(eSum->Text);
	fMain->CurrentWallet.Balance -= Value;
	int Current = fMain->CurrentWallet.TransactionAmount;
	fMain->CurrentWallet.TransactionChain[Current].Name = eName->Text;
	fMain->CurrentWallet.TransactionChain[Current].Category =
	  fMain->LastCategoryClicked;
	fMain->CurrentWallet.TransactionChain[Current].Type = LOSS;
	fMain->CurrentWallet.TransactionChain[Current].Repeat = cbRepeat->ItemIndex;
	fMain->CurrentWallet.TransactionChain[Current].Value = Value;
	fMain->CurrentWallet.TransactionChain[Current].Date = cpCalendarPicker->Date;
	fMain->CurrentWallet.TransactionAmount = Current + 1;
	fMain->RenewBalanceLabel();
	if (cbRepeat->ItemIndex != 0) {
		int Current = fMain->CurrentWallet.PossibleTransactionAmount;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Name = eName->Text;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Category =
		  fMain->LastCategoryClicked;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Type = LOSS;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Repeat = cbRepeat->ItemIndex;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Value = Value;
		fMain->CurrentWallet.PossibleTransactionChain[Current].Date = cpCalendarPicker->Date;
		fMain->CurrentWallet.PossibleTransactionAmount = Current + 1;
	}
	fAdd->Close();
}
//---------------------------------------------------------------------------


