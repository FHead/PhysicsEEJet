#include <iostream>
#include <fstream>
using namespace std;

#include "TString.h"

#include "DataHelper.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string DHFileName = CL.Get("DHFile");
   string OutputFileName = CL.Get("Output", "ResidualJEC.txt");
   string State = CL.Get("State");

   DataHelper DHFile(DHFileName);

   ofstream out(OutputFileName);

   double Bin[] = {0.0, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 1.00};

   out << "{1 JetTheta 1 JetP [0]*(1+[1]*x) L3Absolute}" << endl;
   for(int i = 0; i < 12; i++)
   {
      int B = i;
      if(i >= 6)
         B = 11 - i;
      out << Bin[i] * M_PI << " " << Bin[i+1] * M_PI;
      out << "  4 5 50 " << DHFile[State][Form("P1T%d",B)].GetDouble() << " " << DHFile[State]["P11"].GetDouble();
      out << endl;
   }

   out.close();

   return 0;
}


