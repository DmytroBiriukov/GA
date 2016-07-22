//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <math.h>
#include "genetic.hpp"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Db.hpp>
#include <DBChart.hpp>
#include <DBTables.hpp>
#include <AxCtrls.hpp>
#include <DBGrids.hpp>
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <OleCtrls.hpp>
#include <QrTee.hpp>
#include <QuickRpt.hpp>
#include <vcf1.hpp>
#include <vcfi.hpp>
#include <ImgList.hpp>


#define maxDimention 20
//---------------------------------------------------------------------------
class TReliabilityProblem : public TForm
{
__published:	// IDE-managed Components
        TGeneticAlgorithm *GeneticAlgorithm1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TOpenDialog *OpenDialog1;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TComboBox *ComboBox1;
        TTabSheet *TabSheet2;
        TLabel *Label6;
        TEdit *Edit6;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TF1Book *F1Book1;
        TSpeedButton *SpeedButton3;
        TImageList *ImageList1;
        TComboBox *problemType;
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall problemTypeChange(TObject *Sender);
private:
        double p[maxDimention];
        int x[maxDimention];
        int J[maxDimention];
        double c[maxDimention][maxDimention];
        double w[maxDimention];
        double __fastcall  Objective(TChromosome* chrom);
        int IsValidSolution(TChromosome* chrom);
        int problemDimention;
        int iterationCount;
        int evaluationCount;
        int constraintCount;
        void LoadParameters(char* fileName);
public:		// User declarations
        __fastcall TReliabilityProblem(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReliabilityProblem *ReliabilityProblem;
//---------------------------------------------------------------------------
#endif
