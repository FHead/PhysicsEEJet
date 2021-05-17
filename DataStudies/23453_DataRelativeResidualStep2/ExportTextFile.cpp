#include <iostream>
#include <fstream>
using namespace std;

#include "TString.h"

#include "CommandLine.h"
#include "DataHelper.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string DHFileName     = CL.Get("DHFile");
   string State          = CL.Get("State");
   string OutputFileName = CL.Get("Output");

   ofstream out(OutputFileName);

   out << "{1 JetTheta 1 JetP [0]+0*x L2Relative}" << endl;

   DataHelper DHFile(DHFileName);

   int N = DHFile[State]["NBins"].GetInteger();

   double MaxMax = 0;
   double MaxRatio = 0;

   for(int i = 0; i < N; i++)
   {
      double Min = DHFile[State][Form("B%dMin",i)].GetDouble();
      double Max = DHFile[State][Form("B%dMax",i)].GetDouble();
      double Ratio = DHFile[State][Form("B%dPMR",i)].GetDouble();

      out << Min * M_PI << " " << Max * M_PI;
      out << "   3   ";
      out << " 5 50 ";
      out << 1 / sqrt(Ratio) << endl;
      
      out << (1 - Max) * M_PI << " " << (1 - Min) * M_PI;
      out << "   3   ";
      out << " 5 50 ";
      out << sqrt(Ratio) << endl;

      if(Max > MaxMax)
      {
         MaxMax = Max;
         MaxRatio = Ratio;
      }
   }

   if(MaxMax < 1)
   {
      out << MaxMax * M_PI << " " << M_PI;
      out << "   3   ";
      out << " 5 50 ";
      out << 1 / sqrt(MaxRatio) << endl;
      
      out << 0 << " " << (1 - MaxMax) * M_PI;
      out << "   3   ";
      out << " 5 50 ";
      out << sqrt(MaxRatio) << endl;
   }

   out.close();

   return 0;
}




