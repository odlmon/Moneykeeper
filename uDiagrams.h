//---------------------------------------------------------------------------

#ifndef uDiagramsH
#define uDiagramsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
typedef struct _Colors {
	TColor Color;
	int x1, y1, x2, y2;
} Colors;
Colors CategoryColors[8] =
{
	{RGB(255, 197, 0), 0, 0, 0, 0},
	{RGB(6, 0, 194), 0, 0, 0, 0},
	{RGB(250, 43, 90), 0, 0, 0, 0},
	{RGB(43, 195, 250), 0, 0, 0, 0},
	{RGB(12, 185, 0), 0, 0, 0, 0},
	{RGB(241, 43, 43), 0, 0, 0, 0},
	{RGB(171, 0, 235), 0, 0, 0, 0},
	{RGB(155, 80, 80), 0, 0, 0, 0}
};
class TfDiagrams : public TForm
{
__published:	// IDE-managed Components
	TImage *iDiagram;
	TImage *Image1;
	TLabel *Label1;
	TImage *Image2;
	TLabel *Label2;
	TImage *Image3;
	TLabel *Label3;
	TImage *Image4;
	TLabel *Label4;
	TImage *Image5;
	TLabel *Label5;
	TImage *Image6;
	TLabel *Label6;
	TImage *Image7;
	TLabel *Label7;
	TImage *Image8;
	TLabel *Label8;
	void __fastcall FormActivate(TObject *Sender);

private:	// User declarations
public:		// User declarations
	void __fastcall DrawCategories();
    void __fastcall ShowData(Currency SubTotal, double Percent, int Category);
	__fastcall TfDiagrams(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfDiagrams *fDiagrams;
//---------------------------------------------------------------------------
#endif
