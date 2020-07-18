//---------------------------------------------------------------------------

#ifndef uCreateNewH
#define uCreateNewH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.WinXCalendars.hpp>
//---------------------------------------------------------------------------
class TfCreateNew : public TForm
{
__published:	// IDE-managed Components
	TLabel *lName;
	TLabel *lBalance;
	TLabel *lCurrency;
	TEdit *eName;
	TComboBox *cbCurrency;
	TEdit *eBalance;
	TButton *bCreate;
	TEdit *eSalary;
	TLabel *lSalary;
	TCalendarPicker *cpCalendarPicker;
	TLabel *lDate;
	void __fastcall eNameChange(TObject *Sender);
	void __fastcall cbCurrencyChange(TObject *Sender);
	void __fastcall eBalanceChange(TObject *Sender);
	void __fastcall bCreateClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfCreateNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfCreateNew *fCreateNew;
//---------------------------------------------------------------------------
#endif
