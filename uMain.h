//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.WinXPickers.hpp>
#include <Vcl.WinXCalendars.hpp>
//---------------------------------------------------------------------------
enum ComeType {
		LOSS = 0,
		INCOME
};
enum RepeatType {
	NO = 0,
	EVERYDAY,
	EVERY2DAYS,
	WEEKDAYS,
	WEEKEND,
	EVERYWEEK,
	EVERY2WEEKS,
	EVERY3WEEKS,
	EVERYMONTH,
	EVERY2MONTH,
	EVERY3MONTH,
	EVERY6MONTH,
	EVERYYEAR
};
enum CategoryType {
	PRODUCTS = 0,
	CAFE,
	LEISURE,
	TRANSPORT,
	HEALTH,
	GIFTS,
	FAMILY,
	PURCHASES,
    NONE
};
 typedef struct _Transaction {
	UnicodeString Name;
	CategoryType Category;
	ComeType Type; //Loss or Income перечисление
	Currency Value;
	RepeatType Repeat;   //отдельное перечисление
	TDateTime Date;
} Transaction;
class TfMain : public TForm
{
__published:	// IDE-managed Components
	TLabel *lBalanceLabel;
	TMainMenu *mmMenu;
	TMenuItem *miView;
	TMenuItem *miEdit;
	TMenuItem *miViewOut;
	TMenuItem *miViewIn;
	TMenuItem *miDiagrams;
	TImage *iProducts;
	TImage *iBalance;
	TPanel *pBalance;
	TLabel *lTime;
	TLabel *lName;
	TImage *iCafe;
	TImage *iLeisure;
	TImage *iTransport;
	TImage *iHealth;
	TImage *iGifts;
	TImage *iFamily;
	TImage *iPurchases;
	TMenuItem *miChange;
	TLabel *lBalance;
	TCalendarPicker *cpCalendarPicker;
	TMenuItem *miEditOut;
	TMenuItem *miEditIn;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CategoryClick(TObject *Sender);
	void __fastcall miChangeClick(TObject *Sender);
	void __fastcall miViewOutClick(TObject *Sender);
	void __fastcall miViewInClick(TObject *Sender);
	void __fastcall miEditOutClick(TObject *Sender);
	void __fastcall miEditInClick(TObject *Sender);
	void __fastcall miDiagramsClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	typedef struct _Wallet{
		UnicodeString Name;
		UnicodeString CurrencyName;
		Transaction *TransactionChain;
		int TransactionAmount;
		Transaction *PossibleTransactionChain;
        int PossibleTransactionAmount;
        Currency Balance;
	} Wallet;
    Wallet CurrentWallet;
	bool IsQuiting;
	int LastCategoryClicked;
	ComeType ViewComeType;
    ComeType EditComeType;
	UnicodeString LastCategoryName;
    void _fastcall RenewBalanceLabel();
	__fastcall TfMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfMain *fMain;
//---------------------------------------------------------------------------
#endif
