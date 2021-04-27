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
   int Order = CL.GetInt("Order");

   DataHelper DHFile(DHFileName);

   ofstream out(OutputFileName);

   out << "{1 JetTheta 1 JetP [0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x L3Absolute}" << endl;
   out << "0 3.1415926535 8 5 50  ";
   out << " " << DHFile[State][Form("P%d0",Order)].GetDouble();
   out << " " << DHFile[State][Form("P%d1",Order)].GetDouble();
   out << " " << DHFile[State][Form("P%d2",Order)].GetDouble();
   out << " " << DHFile[State][Form("P%d3",Order)].GetDouble();
   out << " " << DHFile[State][Form("P%d4",Order)].GetDouble();
   out << " " << DHFile[State][Form("P%d5",Order)].GetDouble();

   out.close();

   return 0;
}


