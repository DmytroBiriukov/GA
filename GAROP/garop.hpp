#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define maxVariablesCount 20 
#define maxContainsCount 10 
#define yAmplitude 370 
#define xAmplitude 600 

int varCount; 
int conCount; 
int bitCount; 
long  t_Value; 
unsigned long max_Value;
unsigned long bitString; 
int mask[maxVariablesCount]; 
int J[maxVariablesCount]; 
float C[maxContainsCount][maxVariablesCount];
float p[maxVariablesCount];

float Objective(unsigned long level);
float minObjectiveValue();
void printCriteriaGraph();
void setParameters();
void loadDataFromFile(char* FileName);
void  printDataToScreen();
unsigned long getValue(unsigned long stringValue, int p, int n);
//----------------------------------------------------------------------------
float  Objective(unsigned long level)
{ float score;
  float q[maxVariablesCount];
  int x[maxVariablesCount];
  int flag; flag=1;
  for(int i=0;i<varCount;i++)
  { q[i]=(1-p[i]);
    x[i]=getValue(level, mask[i],mask[i]-mask[i+1]);

   if((x[i]<=J[i])&&(x[i]>0))
      for(int j=1;j<x[i];j++)
	q[i]=q[i]*(1-p[i]);
     else { q[i]=1; flag=0; i=varCount;
	  }
  }
  if(flag)
  score=(1-q[0])*(1-q[1])*(1-q[2]);
  else score=0;

  double w;
  if(flag)
  for(int k=0; k<conCount; k++)
   {w=0;
    for(int l=0;l<varCount;l++)
       w=w+C[k][l]*x[l];
    if(C[k][varCount]<w)//нарушается ограничение
    { score=-(k+1);
      k=conCount;
    }
   }
/*  for(i=1;i<varCount;i++)
     score=score*(1-q[i]);
*/  return score;
}
//----------------------------------------------------------------------------
void setParameters()
{ /*for(int i=0;i<varCount;i++)
  { mask[i]=i; 
  }*/
  mask[0]=9;
  mask[1]=6;
  mask[2]=3;
  mask[varCount]=-1;
  bitCount=10;
  max_Value=645;
  t_Value=145;
 /*long lowT=1;
 for(int i=0;i>varCount;i++)
 {lowT=1;
  for(int j=0;j<mask[i+1]+1;j++)
    lowT=lowT*2;
  t_Value=t_Value+lowT;
 }*/
}
//----------------------------------------------------------------------------
unsigned long getValue(unsigned long bitsString, int p, int n)
{  return (bitsString>>(p+1-n))&~(~0<<n); }
//----------------------------------------------------------------------------
void loadDataFromFile(char* FileName)
{ FILE*f=fopen(FileName,"r");
  fscanf(f,"%d",&varCount);
  for(int i=0;i<varCount;i++)
     fscanf(f,"%f",&p[i]);
  for(int i=0;i<varCount;i++)
     fscanf(f,"%d",&J[i]);
  fscanf(f,"%d",&conCount);
  for(int j=0;j<conCount;j++)
  for(int i=0;i<=varCount;i++)
     fscanf(f,"%f",&C[j][i]);
 fclose(f);
}
//----------------------------------------------------------------------------
void  printDataToScreen()
{
 printf("\n **************** gaData.dat *********************************\n");
 printf("varCount=%d \n",varCount);
 for(int i=0;i<varCount;i++)
  printf("p[%d]=%f  ",i+1,p[i]);
 printf("\n ограничения J[i] : ");
  for(int i=0;i<varCount;i++)
  printf("J[%d]=%d  ",i+1,J[i]);
 for(int j=0;j<conCount;j++)
  {printf("\n %d-ое ограничение\n",j+1);
   for(int i=0;i<=varCount;i++)
    printf("C[%d,%d]=%f  ",j+1,i+1,C[j][i]);
  }
}
//----------------------------------------------------------------------------
float minObjectiveValue()
{ return (1-(1-p[0]))*(1-(1-p[1]))*(1-(1-p[2]));
}
//----------------------------------------------------------------------------
