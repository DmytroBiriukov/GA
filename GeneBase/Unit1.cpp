//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "genetic"
#pragma link "genetic"
#pragma link "genetic"
#pragma link "PERFGRAP"
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TReliabilityProblem *ReliabilityProblem;

//---------------------------------------------------------------------------
__fastcall TReliabilityProblem::TReliabilityProblem(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
double __fastcall  TReliabilityProblem ::Objective(TChromosome* chrom)
{double sysReliability=0.0;
 double subSysUnReliability;
 if(IsValidSolution(chrom))
   {sysReliability=1.0;
    for(int i=0;i<chrom->GeneCount;i++)
       {subSysUnReliability=1.0;
        for(int j=0;j<chrom->GeneAsInteger[i];j++)
            subSysUnReliability=subSysUnReliability*(1-p[i]);
        sysReliability=sysReliability*(1-subSysUnReliability);
       }
   }
 return sysReliability;
}

int TReliabilityProblem :: IsValidSolution(TChromosome* chrom)
{int isValid=1;
 double left;
 for(int j=0;j<chrom->GeneCount;j++)
   if(chrom->GeneAsInteger[j]>J[j])isValid=0;
 for(int k=0;k<constraintCount;k++)
 { left=0.0;
   for(int i=0;i<chrom->GeneCount;i++)
     left+=chrom->GeneAsInteger[i]*c[k][i];
   if(left>w[k])isValid=0;
 }
 return isValid;
}
void TReliabilityProblem :: LoadParameters(char* fileName)
{
 FILE* f=fopen(fileName,"rb");
 int d=0;
 float df=0.0; int i,j;
 fscanf(f,"%d",&d);   problemDimention=d;
 for(i=0; i<problemDimention;i++)
    {fscanf(f,"%f",&df); p[i]=df;}
 for(i=0; i<problemDimention;i++)
    {fscanf(f,"%d",&d); J[i]=d;}
 fscanf(f,"%d",&d);   constraintCount=d;
 for(i=0; i<constraintCount;i++)
    {for(j=0; j<problemDimention;j++)
        {fscanf(f,"%f",&df); c[i][j]=df;}
     fscanf(f,"%f",&df); w[i]=df;
    }
 fclose(f);
}

void __fastcall TReliabilityProblem::SpeedButton1Click(TObject *Sender)
{
if(OpenDialog1->Execute())
  {LoadParameters(OpenDialog1->FileName.c_str());
   SpeedButton2->Enabled=true;
   for(int i=0; i<constraintCount;i++)
     { for(int j=0; j<problemDimention;j++)
        {  F1Book1->Sheet=2;
           F1Book1->Col=j+1;
           F1Book1->Row=i+1;
           F1Book1->Text=FormatFloat("0.00",c[i][j]);
        }
       F1Book1->Col=problemDimention+1;
       F1Book1->Row=i+1;
       F1Book1->Text=FormatFloat("0.00",w[i]);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TReliabilityProblem::SpeedButton2Click(TObject *Sender)
{
 iterationCount=Edit1->Text.ToInt();
 evaluationCount=Edit6->Text.ToInt();
 GeneticAlgorithm1->GeneCount=problemDimention;         //кол-во генов в особи
 GeneticAlgorithm1->ChromosomeCount=Edit2->Text.ToInt();//объем популяции
 GeneticAlgorithm1->Mutation_P=Edit4->Text.ToDouble();
 GeneticAlgorithm1->Crossover_P=Edit3->Text.ToDouble();
 GeneticAlgorithm1->Inversion_P=Edit5->Text.ToDouble();
 GeneticAlgorithm1->GeneSize=4;//(Short_8, Midle_16, Long_32)
 GeneticAlgorithm1->OptimizeMethod=omMaximize; //(omMinimize, omMaximize)
 if(!ComboBox1->ItemIndex) GeneticAlgorithm1->UseElita=true;
   else GeneticAlgorithm1->UseElita=false;
     F1Book1->Sheet=3;
     F1Book1->Col=1; F1Book1->Row=1;
     F1Book1->Text="problem type";
     F1Book1->Col=2; F1Book1->Row=1;
     F1Book1->Text=problemType->Text;
     F1Book1->Col=1; F1Book1->Row=5;
     F1Book1->Text="iteration count";
     F1Book1->Col=2; F1Book1->Row=5;
     F1Book1->Text=Edit1->Text;
     F1Book1->Col=1; F1Book1->Row=4;
     F1Book1->Text="populaton size";
     F1Book1->Col=2; F1Book1->Row=4;
     F1Book1->Text=Edit2->Text;
     F1Book1->Col=1; F1Book1->Row=3;
     F1Book1->Text="evaluation count";
     F1Book1->Col=2; F1Book1->Row=3;
     F1Book1->Text= Edit6->Text;
     F1Book1->Col=1; F1Book1->Row=6;
     F1Book1->Text="Pc=";
     F1Book1->Col=2; F1Book1->Row=6;
     F1Book1->Text=Edit3->Text;
     F1Book1->Col=1; F1Book1->Row=7;
     F1Book1->Text="Pm=";
     F1Book1->Col=2; F1Book1->Row=7;
     F1Book1->Text=Edit4->Text;
 for(int k=0;k<evaluationCount;k++)
    {GeneticAlgorithm1->Init();
     for(int l=0;l< iterationCount;l++)
       {GeneticAlgorithm1->OneEpoch();
        F1Book1->Sheet=4;
        F1Book1->Col=1+k; F1Book1->Row=l+1;
        F1Book1->Text=FormatFloat("0.000000",GeneticAlgorithm1->BestChromosome->Suitability);
        F1Book1->Col=Edit6->Text.ToInt()+k+2; F1Book1->Row=l+1;
        F1Book1->Text=FormatFloat("0.000000",GeneticAlgorithm1->Suitability/GeneticAlgorithm1->ChromosomeCount);
       }
     for(int t=0;t<problemDimention ;t++)
       {F1Book1->Sheet=1;
        F1Book1->Col=1+k; F1Book1->Row=t+1;
        F1Book1->Text=FormatFloat("0",GeneticAlgorithm1->BestChromosome->GeneAsInteger[t]);
       }
     F1Book1->Row=problemDimention+2;
     F1Book1->Text=FormatFloat("0.000000",GeneticAlgorithm1->BestChromosome->Suitability);
     }
 SpeedButton3->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TReliabilityProblem::SpeedButton3Click(TObject *Sender)
{
double avr=0.0;
double ssv=0.0;
double v=0.0;
AnsiString val;

for(int i=0;i<iterationCount;i++)
  {int j,k;
   F1Book1->Sheet=4;
   for(j=0;j<evaluationCount;j++)
    {F1Book1->Col=j+1; F1Book1->Row=i+1;
     val=F1Book1->Text; v=0.0; v=val.ToDouble();
     avr=avr+v;
    }
   avr=avr/evaluationCount;
   for(k=0;k<evaluationCount;k++)
    {F1Book1->Col=k+1; F1Book1->Row=i+1;
     val=F1Book1->Text;  v=0.0; v=val.ToDouble();
     ssv=ssv+(v-avr)*(v-avr);
    }
   ssv=ssv/(evaluationCount-1);
   F1Book1->Sheet=5;
   F1Book1->Col=1; F1Book1->Row=i+1;
   F1Book1->Text=FormatFloat("0.00000000",avr);
   F1Book1->Col=3; F1Book1->Row=i+1;
   F1Book1->Text=FormatFloat("0.00000000",sqrt(ssv));
   ssv=0.0; avr=0.0;

   F1Book1->Sheet=4;
   for(j=0;j<evaluationCount;j++)
    {F1Book1->Col=j+evaluationCount+2; F1Book1->Row=i+1;
     val=F1Book1->Text; v=0.0; v=val.ToDouble();
     avr=avr+v;
    }
   avr=avr/evaluationCount;
   for(k=0;k<evaluationCount;k++)
    {F1Book1->Col=k+evaluationCount+2; F1Book1->Row=i+1;
     val=F1Book1->Text;  v=0.0; v=val.ToDouble();
     ssv=ssv+(v-avr)*(v-avr);
    }
   ssv=ssv/(evaluationCount-1);
   F1Book1->Sheet=5;
   F1Book1->Col=2; F1Book1->Row=i+1;
   F1Book1->Text=FormatFloat("0.00000000",avr);
   F1Book1->Col=4; F1Book1->Row=i+1;
   F1Book1->Text=FormatFloat("0.00000000",sqrt(ssv));
   ssv=0.0; avr=0.0;
  }

F1Book1->LaunchDesigner();
}
//---------------------------------------------------------------------------
void __fastcall TReliabilityProblem::problemTypeChange(TObject *Sender)
{
switch(problemType->ItemIndex){
case 0: GeneticAlgorithm1->OnGetSutability=Objective;break;
default : GeneticAlgorithm1->OnGetSutability=Objective;
}

}
//---------------------------------------------------------------------------

