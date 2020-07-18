//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uDiagrams.h"
#include "uMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfDiagrams *fDiagrams;
//---------------------------------------------------------------------------
__fastcall TfDiagrams::TfDiagrams(TComponent* Owner)
	: TForm(Owner)
{
	  Image1->Canvas->Brush->Color = CategoryColors[0].Color;
	  Image1->Canvas->FillRect(Rect(0, 0, 16, 16));
	  Image2->Canvas->Brush->Color = CategoryColors[1].Color;
	  Image2->Canvas->FillRect(Rect(0, 0, 16, 16));
	  Image3->Canvas->Brush->Color = CategoryColors[2].Color;
	  Image3->Canvas->FillRect(Rect(0, 0, 16, 16));
	  Image4->Canvas->Brush->Color = CategoryColors[3].Color;
	  Image4->Canvas->FillRect(Rect(0, 0, 16, 16));
	  Image5->Canvas->Brush->Color = CategoryColors[4].Color;
	  Image5->Canvas->FillRect(Rect(0, 0, 16, 16));
	  Image6->Canvas->Brush->Color = CategoryColors[5].Color;
	  Image6->Canvas->FillRect(Rect(0, 0, 16, 16));
	  Image7->Canvas->Brush->Color = CategoryColors[6].Color;
	  Image7->Canvas->FillRect(Rect(0, 0, 16, 16));
	  Image8->Canvas->Brush->Color = CategoryColors[7].Color;
	  Image8->Canvas->FillRect(Rect(0, 0, 16, 16));
}
void __fastcall TfDiagrams::ShowData(Currency SubTotal, double Percent, int Category)
{
	if (Category == 0) {
		Label1->Caption = "Продукты, " + CurrToStrF(SubTotal, ffFixed, 2) + " " +
		fMain->CurrentWallet.CurrencyName + ", " + FloatToStrF(Percent * 100, ffFixed, 6, 2) + "%";
	} else if (Category == 1) {
		Label2->Caption = "Кафе, " + CurrToStrF(SubTotal, ffFixed, 2) + " " +
		fMain->CurrentWallet.CurrencyName + ", " + FloatToStrF(Percent * 100, ffFixed, 6, 2) + "%";
	} else if (Category == 2) {
		Label3->Caption = "Досуг, " + CurrToStrF(SubTotal, ffFixed, 2) + " " +
		fMain->CurrentWallet.CurrencyName + ", " + FloatToStrF(Percent * 100, ffFixed, 6, 2) + "%";
	} else if (Category == 3) {
		Label4->Caption = "Транспорт, " + CurrToStrF(SubTotal, ffFixed, 2) + " " +
		fMain->CurrentWallet.CurrencyName + ", " + FloatToStrF(Percent * 100, ffFixed, 6, 2) + "%";
	} else if (Category == 4) {
		Label5->Caption = "Здоровье, " + CurrToStrF(SubTotal, ffFixed, 2) + " " +
		fMain->CurrentWallet.CurrencyName + ", " + FloatToStrF(Percent * 100, ffFixed, 6, 2) + "%";
	} else if (Category == 5) {
		Label6->Caption = "Подарки, " + CurrToStrF(SubTotal, ffFixed, 2) + " " +
		fMain->CurrentWallet.CurrencyName + ", " + FloatToStrF(Percent * 100, ffFixed, 6, 2) + "%";
	} else if (Category == 6) {
		Label7->Caption = "Семья, " + CurrToStrF(SubTotal, ffFixed, 2) + " " +
		fMain->CurrentWallet.CurrencyName + ", " + FloatToStrF(Percent * 100, ffFixed, 6, 2) + "%";
	} else if (Category == 7) {
		Label8->Caption = "Покупки, " + CurrToStrF(SubTotal, ffFixed, 2) + " " +
		fMain->CurrentWallet.CurrencyName + ", " + FloatToStrF(Percent * 100, ffFixed, 6, 2) + "%";
	}
}
void __fastcall TfDiagrams::DrawCategories()
{
	Currency Total = 0;
	int Width = 338;
	for (int i = 0; i < fMain->CurrentWallet.TransactionAmount; i++) {
		if (fMain->CurrentWallet.TransactionChain[i].Type == LOSS) {
			Total += fMain->CurrentWallet.TransactionChain[i].Value;
		}
	}
	int x1 = 169, y1 = 0, x2 = 0, y2 = 0;
	double TotalAngle = 0;
	for (int j = 0; j < 8; j++) {
		Currency SubTotal = 0;
		for (int i = 0; i < fMain->CurrentWallet.TransactionAmount; i++) {
			if (fMain->CurrentWallet.TransactionChain[i].Type == LOSS &&
			  fMain->CurrentWallet.TransactionChain[i].Category == j) {
				SubTotal += fMain->CurrentWallet.TransactionChain[i].Value;
			}
		}
		double Percent = ((double) SubTotal) / ((double) Total);
        ShowData(SubTotal, Percent, j);
		if (Percent != 0) {
			TotalAngle += 2 * 3.14 * Percent;
			if (TotalAngle <= 0.5 * 3.14) {
				y2 = Width / 2 * (1 - Cos(TotalAngle));
				x2 = Width / 2 * (1 + Sin(TotalAngle));
			} else if (TotalAngle <= 3.14) {
				y2 = Width / 2 * (1 + Sin(TotalAngle - 0.5 * 3.14));
				x2 = Width / 2 * (1 + Cos(TotalAngle - 0.5 * 3.14));
			} else if (TotalAngle <= 1.5 * 3.14) {
				y2 = Width / 2 * (1 + Cos(TotalAngle - 3.14));
				x2 = Width / 2 * (1 - Sin(TotalAngle - 3.14));
			} else if (TotalAngle <= 2 * 3.14) {
				y2 = Width / 2 * (1 - Sin(TotalAngle - 1.5 * 3.14));
				x2 = Width / 2 * (1 - Cos(TotalAngle - 1.5 * 3.14));
			}
			iDiagram->Canvas->Brush->Color = CategoryColors[j].Color;
			iDiagram->Canvas->Pie(0, 0, Width, Width,
			x2, y2, x1, y1);
			x1 = x2;
			y1 = y2;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfDiagrams::FormActivate(TObject *Sender)
{
	iDiagram->Canvas->Pen->Color = clBlack;
	DrawCategories();
}
//---------------------------------------------------------------------------
