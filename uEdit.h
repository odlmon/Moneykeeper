//---------------------------------------------------------------------------

#ifndef uEditH
#define uEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.WinXCalendars.hpp>
#include "uMain.h"
//---------------------------------------------------------------------------
class TfEdit : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *sgEdit;
	TLabel *lSum;
	TLabel *lDate;
	TLabel *lRepeat;
	TLabel *lName;
	TCalendarPicker *cpCalendarPicker;
	TEdit *eSum;
	TComboBox *cbRepeat;
	TEdit *eName;
	TLabel *lCategory;
	TComboBox *cbCategory;
	TButton *bEdit;
	TButton *bDelete;
	TButton *bAdd;
	void __fastcall FormActivate(TObject *Sender);
    void __fastcall ChainOut(double Days);
	void __fastcall sgEditSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall bEditClick(TObject *Sender);
	void __fastcall bDeleteClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	Transaction __fastcall RowToTransaction(int Row);
    bool __fastcall NotEmpty();
	void __fastcall bAddClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    int CurrentRow;
	__fastcall TfEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfEdit *fEdit;
//---------------------------------------------------------------------------
#endif
