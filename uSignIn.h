//---------------------------------------------------------------------------

#ifndef uSignInH
#define uSignInH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TfSignIn : public TForm
{
__published:	// IDE-managed Components
	TImage *IconImage;
	TLabel *lMainLogo;
	TLabel *lChoose;
	TComboBox *cbChoose;
	TLabel *lOr;
	TButton *bCreateNew;
	TButton *bStartWork;
	TButton *bQuit;
	void __fastcall cbChooseChange(TObject *Sender);
	void __fastcall bStartWorkClick(TObject *Sender);
	void __fastcall bCreateNewClick(TObject *Sender);
	void __fastcall bQuitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfSignIn(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfSignIn *fSignIn;
//---------------------------------------------------------------------------
#endif
