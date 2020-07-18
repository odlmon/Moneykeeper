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
	sgView->Cells[0][0] = "��������";
	sgView->Cells[1][0] = "���������";
	sgView->Cells[2][0] = "����";
	sgView->Cells[3][0] = "������";
	sgView->Cells[4][0] = "�����";
}
UnicodeString ConvertCategory(CategoryType Category)
{
	if (Category == 0) {
		return "��������";
	} else if (Category == 1) {
		return "����";
	} else if (Category == 2) {
		return "�����";
	} else if (Category == 3) {
		return "���������";
	} else if (Category == 4) {
		return "��������";
	} else if (Category == 5) {
		return "�������";
	} else if (Category == 6) {
		return "�����";
	} else if (Category == 7) {
		return "�������";
	} else if (Category == 8) {
		return "-";
	}
}
int ConvertCategoryString(UnicodeString Category)
{
	if (Category == "��������") {
		return 0;
	} else if (Category == "����") {
		return 1;
	} else if (Category == "�����") {
		return 2;
	} else if (Category == "���������") {
		return 3;
	} else if (Category == "��������") {
		return 4;
	} else if (Category == "�������") {
		return 5;
	} else if (Category == "�����") {
		return 6;
	} else if (Category == "�������") {
		return 7;
	} else if (Category == "-") {
		return 8;
	}
}
UnicodeString ConvertRepeat(RepeatType Repeat)
{
	switch (Repeat) {
		case 0:
			return "���";
		break;
		case 1:
			return "������ ����";
		break;
		case 2:
			return "������ 2 ���";
		break;
		case 3:
			return "������ ���";
		break;
		case 4:
			return "�������� ���";
		break;
		case 5:
			return "�����������";
		break;
		case 6:
			return "������ 2 ������";
		break;
		case 7:
			return "������ 4 ������";
		break;
		case 8:
			return "����������";
		break;
		case 9:
			return "������ 2 ������";
		break;
		case 10:
			return "������ 3 ������";
		break;
		case 11:
			return "������ 6 �������";
		break;
		case 12:
			return "��������";
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
		fView->Caption = "�������� ��������";
	} else if (fMain->ViewComeType == INCOME) {
		fView->Caption = "�������� �������";
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
	ShowMessage("C���� �� ��������� ������: " + CurrToStrF(Sum, ffFixed, 2) +
	  " " + fMain->CurrentWallet.CurrencyName);
}
//---------------------------------------------------------------------------

