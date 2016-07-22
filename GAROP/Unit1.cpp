//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>
#include <stdlib.h>
#include "garop.hpp"
#pragma hdrstop

#include "Unit1.h"
#define leftBorder 201
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
void printCriteriaGraph();
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
dataLoaded=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::runAlgorithm1Click(TObject *Sender)
{
  loadDataFromFile("gaData.dat");
  dataLoaded=true;
  setParameters();
  printCriteriaGraph();
}
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
void printCriteriaGraph()
{
 float minCriteriaValue=minObjectiveValue();
 long  maximizedLevel;
 float maxCriteriaValue;  maxCriteriaValue=0.0;
 int yScale;
 int curXLevel; //текущий уровень оси Х
 int maxXLevel; //максимальная длина оси Х
 int maxYLevel; //массимальная высота оси Y
 maxYLevel=950; 				
 maxXLevel=Printer()->PageWidth-80;
 int minScale=maxYLevel*minCriteriaValue;
 int yMaxScale=0;
int xCord; xCord=leftBorder;
 Printer()->BeginDoc();
 Printer()->Canvas->Pen->Color=clBlack;

for(int i=0;i<2/*((max_Value-t_Value)/250)+1*/;i++)
{curXLevel=maxYLevel*(i+1);
 for(unsigned long  currentLevel=t_Value+250*i;currentLevel<t_Value+250*(i+1)&&currentLevel<max_Value;currentLevel++)
 {yScale=Objective(currentLevel)*maxYLevel;
   if(yMaxScale<yScale)
   { yMaxScale=yScale;
     maxCriteriaValue=Objective(currentLevel);
     maximizedLevel=currentLevel;
   }
   if(yScale>0)
    Printer()->Canvas->Rectangle(xCord,curXLevel+20-yScale,xCord+2,curXLevel+20);
   if(!yScale)
    Printer()->Canvas->Rectangle(xCord,curXLevel+20,xCord+2,curXLevel+35);
   int contain; contain=-(yScale/maxYLevel);
   char str[20]; itoa(contain,str,10);
   if(yScale<0)
   {
      Printer()->Canvas->Rectangle(xCord,curXLevel+20,xCord+2,curXLevel+45);
//      Printer()->Canvas->TextOutA(xCord,maxYLevel+50,str);
   }
   xCord+=7;
  }
   Printer()->Canvas->Rectangle(leftBorder-20,curXLevel+20-yMaxScale,leftBorder-30,curXLevel+20-minScale);
char maximizedString[80]; ltoa(maximizedLevel,maximizedString,10);
AnsiString str;
str=Objective(maximizedLevel);
AnsiString interval;
interval="d є [";
int lwrBorder=t_Value+250*i;
int uprBorder=t_Value+250*(i+1);
if(uprBorder>max_Value)uprBorder=max_Value;
interval=interval+ lwrBorder;
interval=interval+ ",";
interval=interval+ uprBorder;
interval=interval+ "]";
Printer()->Canvas->TextOutA(maxXLevel-300,curXLevel-200,"Поведінка критерія F(d)");
Printer()->Canvas->TextOutA(maxXLevel-300,curXLevel-150,interval);
Printer()->Canvas->TextOutA(maxXLevel-300,curXLevel-100,"Максимальне значення :");
Printer()->Canvas->TextOutA(maxXLevel-300,curXLevel-50,"F(");
Printer()->Canvas->TextOutA(maxXLevel-255,curXLevel-50,maximizedString);
Printer()->Canvas->TextOutA(maxXLevel-200,curXLevel-50,")=");
Printer()->Canvas->TextOutA(maxXLevel-170,curXLevel-50,FloatToStrF(Objective(maximizedLevel),ffFixed,6,6));
ltoa(maximizedLevel,maximizedString,2);
Printer()->Canvas->TextOutA(maxXLevel-170,curXLevel,maximizedString);
  xCord=leftBorder;
}// end of for()
//FloatToStrF(A[i][j],ffFixed,4,4);IntToStr(mm)
 for(int i=0;i<varCount;i++)
  Printer()->Canvas->TextOutA(200*i+leftBorder,curXLevel+100,FloatToStrF(p[i],ffFixed,4,4));
 for(int i=0;i<varCount;i++)
  Printer()->Canvas->TextOutA(150*i+leftBorder,curXLevel+150,IntToStr(J[i]));
 for(int j=0;j<conCount;j++)
  for(int i=0;i<=varCount;i++)
   Printer()->Canvas->TextOutA(220*i+leftBorder,50*j+curXLevel+200,FloatToStrF(C[j][i],ffFixed,4,4));

 Printer()->EndDoc();
}
//----------------------------------------------------------------------------
void __fastcall TForm1::exit1Click(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::printGraph1Click(TObject *Sender)
{
if(dataLoaded) printCriteriaGraph();
}
//---------------------------------------------------------------------------
