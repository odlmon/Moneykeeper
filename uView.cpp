//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uView.h"
#include "uMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfView *fView;
//---------------------------------------------------------------------------
__fastcall TfView::TfView(TComponent* Owner)
	: TForm(Owner)
{
	sgView->Cells[0][0] = "Название";
	sgView->Cells[1][0] = "Категория";
	sgView->Cells[2][0] = "Дата";
	sgView->Cells[3][0] = "Повтор";
	sgView->Cells[4][0] = "Сумма";
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
			return "Каждые 4 недели";
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
void __fastcall TfView::ChainOut(double Days)
{
    for (int i = 1; i < sgView->RowCount; i++) {
		sgView->Rows[i]->Clear();
	}
    int Count = 0;
	for (int i = 0; i < fMain->CurrentWallet.TransactionAmount; i++) {
		if (fMain->CurrentWallet.TransactionChain[i].Type == fMain->ViewComeType
		  && (fMain->CurrentWallet.TransactionChain[i].Date > Date() - Days)) {
			sgView->Cells[0][Count + 1] =
			  fMain->CurrentWallet.TransactionChain[i].Name;
			sgView->Cells[1][Count + 1] = ConvertCategory(
			  fMain->CurrentWallet.TransactionChain[i].Category);
			sgView->Cells[2][Count + 1] = DateToStr(
			  fMain->CurrentWallet.TransactionChain[i].Date);
			sgView->Cells[3][Count + 1] = ConvertRepeat(
			  fMain->CurrentWallet.TransactionChain[i].Repeat);
			FormatSettings.CurrencyString = fMain->CurrentWallet.CurrencyName;
			FormatSettings.CurrencyFormat = 4;
			sgView->Cells[4][Count + 1] = CurrToStrF(
			  fMain->CurrentWallet.TransactionChain[i].Value, ffFixed, 2) +
			  " " + fMain->CurrentWallet.CurrencyName;
			Count++;
		}
	}
	if (Count == 0) {
		sgView->RowCount = 2;
	} else {
		sgView->RowCount = Count + 1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfView::FormActivate(TObject *Sender)
{
	if (fMain->ViewComeType == LOSS) {
		fView->Caption = "Просмотр расходов";
	} else if (fMain->ViewComeType == INCOME) {
		fView->Caption = "Просмотр доходов";
	}
	miByCategory->Checked = false;
	miBySum->Checked = false;
	miOld->Checked = false;
	miNew->Checked = false;
	miForWeek->Checked = false;
	miForMonth->Checked = false;
	miForYear->Checked = false;
	ChainOut(Date());
}
//---------------------------------------------------------------------------
void __fastcall TfView::ShowSum()
{
    if (miForWeek->Checked) {
		ChainOut(7);
	} else if (miForMonth->Checked) {
		ChainOut(30);
	} else if (miForYear->Checked) {
		ChainOut(365);
	} else {
		ChainOut(Date());
	}
}

void __fastcall TfView::ShowSort()
{
    if (miByCategory->Checked) {
		SortByCategory();
	} else if (miBySum->Checked) {
		SortBySum();
	} else if (miOld->Checked) {
		SortOldFirst();
	} else if (miNew->Checked) {
		SortNewFirst();
	} else {
		ChainOut(Date());
	}
}

void __fastcall TfView::miSumClick(TObject *Sender)
{
	ShowSum();
	ShowSort();
}

void __fastcall TfView::SwapRows(int i, int j)
{
	UnicodeString *Temp = new UnicodeString[5];
	for (int m = 0; m < 5; m++) {
		Temp[m] = sgView->Cells[m][i];
	}
	sgView->Rows[i] = sgView->Rows[j];
	for (int m = 0; m < 5; m++) {
        sgView->Cells[m][j] = Temp[m];
	}
}
//---------------------------------------------------------------------------
void __fastcall TfView::SortByCategory()
{
	for (int i = 1; i < sgView->RowCount - 1; i++) {
		for (int j = 1; j < sgView->RowCount - i; j++) {
			if (ConvertCategoryString(sgView->Cells[1][j]) >
			  ConvertCategoryString(sgView->Cells[1][j + 1])) {
				SwapRows(j, j + 1);
			}
		}
	}
}

void __fastcall TfView::SortBySum()
{
	for (int i = 1; i < sgView->RowCount - 1; i++) {
		for (int j = 1; j < sgView->RowCount - i; j++) {
			UnicodeString Str1 = sgView->Cells[4][j]
			  .SubString(1, sgView->Cells[4][j].Length() - 4);
			UnicodeString Str2 = sgView->Cells[4][j + 1]
			  .SubString(1, sgView->Cells[4][j + 1].Length() - 4);
			if (StrToCurr(Str1) > StrToCurr(Str2)) {
				SwapRows(j, j + 1);
			}
		}
	}
}

void __fastcall TfView::SortOldFirst()
{
	for (int i = 1; i < sgView->RowCount - 1; i++) {
		for (int j = 1; j < sgView->RowCount - i; j++) {
			UnicodeString Str1 = sgView->Cells[2][j];
			UnicodeString Str2 = sgView->Cells[2][j + 1];
			if (StrToDate(Str1) > StrToDate(Str2)) {
				SwapRows(j, j + 1);
			}
		}
	}
}

void __fastcall TfView::SortNewFirst()
{
    for (int i = 1; i < sgView->RowCount - 1; i++) {
		for (int j = 1; j < sgView->RowCount - i; j++) {
			UnicodeString Str1 = sgView->Cells[2][j];
			UnicodeString Str2 = sgView->Cells[2][j + 1];
			if (StrToDate(Str1) < StrToDate(Str2)) {
				SwapRows(j, j + 1);
			}
		}
	}
}

void __fastcall TfView::miSortClick(TObject *Sender)
{
	ShowSum();
    ShowSort();
}
//---------------------------------------------------------------------------

void __fastcall TfView::miSumOfGroupClick(TObject *Sender)
{
	Currency Sum = 0;
	for (int i = 1; i < sgView->RowCount; i++) {
		Sum = Sum + StrToCurr(sgView->Cells[4][i]
		  .SubString(1, sgView->Cells[4][i].Length() - 4));
	}
	ShowMessage("Cумма за выбранный период: " + CurrToStrF(Sum, ffFixed, 2) +
	  " " + fMain->CurrentWallet.CurrencyName);
}
//---------------------------------------------------------------------------

