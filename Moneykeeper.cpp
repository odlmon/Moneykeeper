//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("uCreateNew.cpp", fCreateNew);
USEFORM("uAdd.cpp", fAdd);
USEFORM("uView.cpp", fView);
USEFORM("uSignIn.cpp", fSignIn);
USEFORM("uMain.cpp", fMain);
USEFORM("uEdit.cpp", fEdit);
USEFORM("uDiagrams.cpp", fDiagrams);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Tablet Light");
		Application->CreateForm(__classid(TfMain), &fMain);
		Application->CreateForm(__classid(TfSignIn), &fSignIn);
		Application->CreateForm(__classid(TfCreateNew), &fCreateNew);
		Application->CreateForm(__classid(TfAdd), &fAdd);
		Application->CreateForm(__classid(TfView), &fView);
		Application->CreateForm(__classid(TfEdit), &fEdit);
		Application->CreateForm(__classid(TfDiagrams), &fDiagrams);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
