//---------------------------------------------------------------------------

#ifndef uAddH
#define uAddH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.WinXCalendars.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
//---------------------------------------------------------------------------
class TfAdd : public TForm
{
__published:	// IDE-managed Components
	TCalendarPicker *cpCalendarPicker;
	TEdit *eSum;
	TLabel *lSum;
	TLabel *lDate;
	TComboBox *cbRepeat;
	TLabel *lRepeat;
	TButton *bAccept;
	TImage *iCategory;
	TLabel *lName;
	TEdit *eName;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall bAcceptClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfAdd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfAdd *fAdd;
//---------------------------------------------------------------------------
#endif
