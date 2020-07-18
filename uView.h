//---------------------------------------------------------------------------

#ifndef uViewH
#define uViewH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TfView : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *mmMenu;
	TMenuItem *miSort;
	TMenuItem *miSum;
	TMenuItem *miForWeek;
	TMenuItem *miForMonth;
	TMenuItem *miForYear;
	TMenuItem *miByCategory;
	TMenuItem *miBySum;
	TMenuItem *miOld;
	TMenuItem *miNew;
	TStringGrid *sgView;
	TMenuItem *miSumOfGroup;
	void __fastcall FormActivate(TObject *Sender);
    void __fastcall SwapRows(int i, int j);
	void __fastcall ChainOut(double Days);
	void __fastcall ShowSum();
    void __fastcall ShowSort();
	void __fastcall SortByCategory();
	void __fastcall SortBySum();
	void __fastcall SortOldFirst();
    void __fastcall SortNewFirst();
	void __fastcall miSumClick(TObject *Sender);
	void __fastcall miSortClick(TObject *Sender);
	void __fastcall miSumOfGroupClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfView(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfView *fView;
//---------------------------------------------------------------------------
#endif
