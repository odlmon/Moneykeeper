//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uEdit.h"
#include "uMain.h"
#include "uAdd.h"
#include <stack>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfEdit *fEdit;
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
__fastcall TfEdit::TfEdit(TComponent* Owner)
	: TForm(Owner)
{
	sgEdit->Cells[0][0] = "Название";
	sgEdit->Cells[1][0] = "Категория";
	sgEdit->Cells[2][0] = "Дата";
	sgEdit->Cells[3][0] = "Повтор";
	sgEdit->Cells[4][0] = "Сумма";
}
UnicodeString ConvertCategory(CategoryType Category)
{
	if (Category == 0) {
		return "Продукты";
	} else if (Category == 1) {
		return "Кафе";
	} else if (Category == 2) {
		return "Досуг";
	} else if (Category == 3) {
		return "Транспорт";
	} else if (Category == 4) {
		return "Здоровье";
	} else if (Category == 5) {
		return "Подарки";
	} else if (Category == 6) {
		return "Семья";
	} else if (Category == 7) {
		return "Покупки";
	} else if (Category == 8) {
		return "-";
	}
}
int ConvertCategoryString(UnicodeString Category)
{
	if (Category == "Продукты") {
		return 0;
	} else if (Category == "Кафе") {
		return 1;
	} else if (Category == "Досуг") {
		return 2;
	} else if (Category == "Транспорт") {
		return 3;
	} else if (Category == "Здоровье") {
		return 4;
	} else if (Category == "Подарки") {
		return 5;
	} else if (Category == "Семья") {
		return 6;
	} else if (Category == "Покупки") {
		return 7;
	} else if (Category == "-") {
		return 8;
	}
}
UnicodeString ConvertRepeat(RepeatType Repeat)
{
	switch (Repeat) {
		case 0:
			return "Нет";
		break;
		case 1:
			return "Каждый день";
		break;
		case 2:
			return "Каждые 2 дня";
		break;
		case 3:
			return "Будние дни";
		break;
		case 4:
			return "Выходные дни";
		break;
		case 5:
			return "Еженедельно";
		break;
		case 6:
			return "Каждые 2 недели";
		break;
		case 7:
			return "Каждые 3 недели";
		break;
		case 8:
			return "Ежемесячно";
		break;
		case 9:
			return "Каждые 2 месяца";
		break;
		case 10:
			return "Каждые 3 месяца";
		break;
		case 11:
			return "Каждые 6 месяцев";
		break;
		case 12:
			return "Ежегодно";
		break;
	}
}
int ConvertRepeatString(UnicodeString RepeatString)
{
	if (RepeatString == "Нет") {
		return 0;
	} else if (RepeatString == "Каждый день") {
		return 1;
	} else if (RepeatString == "Каждые 2 дня") {
		return 2;
	} else if (RepeatString == "Будние дни") {
		return 3;
	} else if (RepeatString == "Выходные дни") {
		return 4;
	} else if (RepeatString == "Еженедельно") {
		return 5;
	} else if (RepeatString == "Каждые 2 недели") {
		return 6;
	} else if (RepeatString == "Каждые 3 недели") {
		return 7;
	} else if (RepeatString == "Ежемесячно") {
		return 8;
	} else if (RepeatString == "Каждые 2 месяца") {
		return 9;
	} else if (RepeatString == "Каждые 3 месяца") {
		return 10;
	} else if (RepeatString == "Каждые 6 месяцев") {
		return 11;
	} else if (RepeatString == "Ежегодно") {
		return 12;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfEdit::ChainOut(double Days)
{
	for (int i = 1; i < sgEdit->RowCount; i++) {
		sgEdit->Rows[i]->Clear();
	}
    int Count = 0;
	for (int i = 0; i < fMain->CurrentWallet.PossibleTransactionAmount; i++) {
		if (fMain->CurrentWallet.PossibleTransactionChain[i].Type == fMain->EditComeType
		  && (fMain->CurrentWallet.PossibleTransactionChain[i].Date > Date() - Days)) {
			sgEdit->Cells[0][Count + 1] =
			  fMain->CurrentWallet.PossibleTransactionChain[i].Name;
			sgEdit->Cells[1][Count + 1] = ConvertCategory(
			  fMain->CurrentWallet.PossibleTransactionChain[i].Category);
			sgEdit->Cells[2][Count + 1] = DateToStr(
			  fMain->CurrentWallet.PossibleTransactionChain[i].Date);
			sgEdit->Cells[3][Count + 1] = ConvertRepeat(
			  fMain->CurrentWallet.PossibleTransactionChain[i].Repeat);
			FormatSettings.CurrencyString = fMain->CurrentWallet.CurrencyName;
			FormatSettings.CurrencyFormat = 4;
			sgEdit->Cells[4][Count + 1] = CurrToStrF(
			  fMain->CurrentWallet.PossibleTransactionChain[i].Value, ffFixed, 2) +
			  " " + fMain->CurrentWallet.CurrencyName;
			Count++;
		}
	}
	if (Count == 0) {
		sgEdit->RowCount = 2;
	} else {
		sgEdit->RowCount = Count + 1;
	}
}

void __fastcall TfEdit::FormActivate(TObject *Sender)
{
	if (fMain->EditComeType == LOSS) {
		fEdit->Caption = "Редактирование расходов";
		lSum->Caption = "Расход";
		cbCategory->Enabled = true;
		bAdd->Visible = false;
	} else if (fMain->EditComeType == INCOME) {
		fEdit->Caption = "Редактирование доходов";
		lSum->Caption = "Доход";
		cbCategory->Enabled = false;
        bAdd->Visible = true;
	}
	eName->SetFocus();
	eName->Text = "";
	cbCategory->ItemIndex = 0;
	eSum->Text = "";
	cpCalendarPicker->Date = Date();
	cbRepeat->ItemIndex = 0;
    ChainOut(Date());
}
bool __fastcall TfEdit::NotEmpty()
{
	bool Result = false;
	if (sgEdit->RowCount == 2) {
		for (int i = 0; i < 5; i++) {
			if (!sgEdit->Cells[i][1].IsEmpty()) {
				Result = true;
			}
		}
	} else if (sgEdit->RowCount > 2) {
		Result = true;
	}
    return Result;
}
//---------------------------------------------------------------------------
void __fastcall TfEdit::sgEditSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	CurrentRow = ARow;
	if (NotEmpty()) {
        eName->Text = sgEdit->Cells[0][ARow];
		cbCategory->ItemIndex = ConvertCategoryString(sgEdit->Cells[1][ARow]);
		eSum->Text = sgEdit->Cells[4][ARow]
		  .SubString(1, sgEdit->Cells[4][ARow].Length() - 4);
		cpCalendarPicker->Date = StrToDate(sgEdit->Cells[2][ARow]);
		cbRepeat->ItemIndex = ConvertRepeatString(sgEdit->Cells[3][ARow]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfEdit::bEditClick(TObject *Sender)
{
	sgEdit->Cells[0][CurrentRow] = eName->Text;
	sgEdit->Cells[1][CurrentRow] = ConvertCategory(cbCategory->ItemIndex);
	sgEdit->Cells[2][CurrentRow] = DateToStr(cpCalendarPicker->Date);
	sgEdit->Cells[3][CurrentRow] = ConvertRepeat(cbRepeat->ItemIndex);
	sgEdit->Cells[4][CurrentRow] = CurrToStrF(GetValue(eSum->Text), ffFixed, 2)
	  + " " + fMain->CurrentWallet.CurrencyName;
}
//---------------------------------------------------------------------------

void __fastcall TfEdit::bDeleteClick(TObject *Sender)
{
    sgEdit->RowCount = sgEdit->RowCount + 1;
	for (int i = CurrentRow; i < sgEdit->RowCount - 1; i++) {
        sgEdit->Rows[i] = sgEdit->Rows[i + 1];
	}
	if (sgEdit->RowCount > 3) {
        sgEdit->RowCount = sgEdit->RowCount - 2;
	} else {
		sgEdit->RowCount = sgEdit->RowCount - 1;
    }
}
//---------------------------------------------------------------------------
Transaction __fastcall TfEdit::RowToTransaction(int Row)
{
	Transaction Temp;
	Temp.Name = sgEdit->Cells[0][Row];
	Temp.Category = ConvertCategoryString(sgEdit->Cells[1][Row]);
	Temp.Date = StrToDate(sgEdit->Cells[2][Row]);
	Temp.Repeat = ConvertRepeatString(sgEdit->Cells[3][Row]);
	Temp.Value = sgEdit->Cells[4][Row]
	  .SubString(1, sgEdit->Cells[4][Row].Length() - 4);
	Temp.Type = fMain->EditComeType;
    return Temp;
}

void __fastcall TfEdit::FormClose(TObject *Sender, TCloseAction &Action)
{
	Transaction *Temp = new Transaction[200];
	int Count = 0;
	for (int i = 0; i < fMain->CurrentWallet.PossibleTransactionAmount; i++) {
		if (fMain->CurrentWallet.PossibleTransactionChain[i].Type !=
		  fMain->EditComeType) {
			Temp[Count] = fMain->CurrentWallet.PossibleTransactionChain[i];
			Count++;
		}
	}
	if (NotEmpty()) {
		for (int i = 1; i < sgEdit->RowCount; i++) {
			Temp[Count] = RowToTransaction(i);
			Count++;
		}
    }
	fMain->CurrentWallet.PossibleTransactionAmount = Count;
    fMain->CurrentWallet.PossibleTransactionChain = Temp;
}
//---------------------------------------------------------------------------

void __fastcall TfEdit::bAddClick(TObject *Sender)
{
	sgEdit->Cells[0][sgEdit->RowCount] = eName->Text;
	sgEdit->Cells[1][sgEdit->RowCount] = "-";
	sgEdit->Cells[2][sgEdit->RowCount] = DateToStr(cpCalendarPicker->Date);
	sgEdit->Cells[3][sgEdit->RowCount] = ConvertRepeat(cbRepeat->ItemIndex);
	sgEdit->Cells[4][sgEdit->RowCount] = CurrToStrF(GetValue(eSum->Text), ffFixed, 2)
	  + " " + fMain->CurrentWallet.CurrencyName;
	sgEdit->RowCount = sgEdit->RowCount + 1;
}
//---------------------------------------------------------------------------

