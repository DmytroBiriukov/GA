//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Printers.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *ROP1;
        TMenuItem *printGraph1;
        TMenuItem *runAlgorithm1;
        TImageList *ImageList1;
        TMenuItem *loadData1;
        TMenuItem *exit1;
        void __fastcall runAlgorithm1Click(TObject *Sender);
        void __fastcall exit1Click(TObject *Sender);
        void __fastcall printGraph1Click(TObject *Sender);
private:	// User declarations
bool dataLoaded;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
