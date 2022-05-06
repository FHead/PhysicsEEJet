#include <vector>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

#include "CustomAssert.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName     = CL.Get("Input");
   string OutputFileName    = CL.Get("Output");
   vector<string> Export    = CL.GetStringVector("Export");
   vector<string> Selection = CL.GetStringVector("Selection");
   double MinX              = CL.GetDouble("MinX", -999);

   string ResultBase        = CL.Get("ResultBase", "Result");
   string SystematicsBase   = CL.Get("SystematicsBase", "Systematics");

   string XLabel            = CL.Get("XLabel", "X");
   string XUnit             = CL.Get("XUnit", "");
   string YLabel            = CL.Get("YLabel", "Y");
   string YUnit             = CL.Get("YUnit", "");

   TFile InputFile(InputFileName.c_str());

   vector<TGraphAsymmErrors *> Result;
   vector<TGraphAsymmErrors *> Systematics;

   for(int i = 0; i < (int)Export.size(); i++)
   {
      Result.push_back((TGraphAsymmErrors *)InputFile.Get(Form("%s%s", ResultBase.c_str(), Export[i].c_str())));
      Systematics.push_back((TGraphAsymmErrors *)InputFile.Get(Form("%s%s", SystematicsBase.c_str(), Export[i].c_str())));
   }

   Assert(Result.size() > 0,         "No results?");
   Assert(Systematics.size() > 0,    "No systematics?");
   Assert(Result[0] != nullptr,      "First result can't be invalid");
   Assert(Systematics[0] != nullptr, "First Systematics can't be invalid");

   vector<pair<double, double>> X;
   for(int i = 0; i < Result[0]->GetN(); i++)
   {
      double x   = Result[0]->GetPointX(i);
      double exl = Result[0]->GetErrorXlow(i);
      double exh = Result[0]->GetErrorXhigh(i);

      if(x < MinX)
         continue;

      X.push_back(pair<double, double>(x - exl, x + exh));
   }

   int NPoints = X.size();
   int NCurves = Result.size();

   XLabel = "name: '" + XLabel + "'";
   if(XUnit != "")
      XUnit = ", units: '" + XUnit + "'";
   YLabel = "name: '" + YLabel + "'";
   if(YUnit != "")
      YUnit = ", units: '" + YUnit + "'";

   ofstream out(OutputFileName);

   out << "independent_variables:" << endl;
   out << "- header: {" << XLabel << XUnit << "}" << endl;
   out << "  values:" << endl;
   for(int i = 0; i < NPoints; i++)
      out << "  - {low: " << X[i].first << ", high: " << X[i].second << "}" << endl;

   out << "dependent_variables:" << endl;
   for(int i = 0; i < NCurves; i++)
   {
      if(Result[i] == nullptr)
         continue;

      out << "- header: {" << YLabel << YUnit << "}" << endl;
      out << "  qualifiers:" << endl;
      out << "  - {name: RE, value: 'e+ e- -> jet X'}" << endl;
      out << "  - {name: SQRT(S), units: GEV, value: 91.2}" << endl;
      if(NCurves > 1)
      out << "  - {name: SELECTION, value: '" << Selection[i] + "'}" << endl;
      out << "  values:" << endl;

      for(int iP = 0; iP < NPoints; iP++)
      {
         double y = -1, yl = -1, yh = -1, ysl = -1, ysh = -1;

         for(int jP = 0; jP < Result[i]->GetN(); jP++)
         {
            double x = Result[i]->GetPointX(jP);
            if(x < X[iP].first || x > X[iP].second)
               continue;
            y = Result[i]->GetPointY(jP);
            yl = Result[i]->GetErrorYlow(jP);
            yh = Result[i]->GetErrorYhigh(jP);
         }

         if(Systematics[i] != nullptr)
         {
            for(int jP = 0; jP < Systematics[i]->GetN(); jP++)
            {
               double x = Systematics[i]->GetPointX(jP);
               if(x < X[iP].first || x > X[iP].second)
                  continue;
               ysl = Systematics[i]->GetErrorYlow(jP);
               ysh = Systematics[i]->GetErrorYhigh(jP);
            }
         }

         if(y > 0)
         {
            out << "  - value: " << y << endl;
            out << "    errors:" << endl;
            out << "    - {asymerror: {plus: " << yh << ", minus: " << -yl << "}, label: stat}" << endl;
            out << "    - {asymerror: {plus: " << ysh << ", minus: " << -ysl << "}, label: sys}" << endl;
         }
         else
            out << "  - value: '-'"<< endl;
      }
   }

   out.close();

   InputFile.Close();

   return 0;
}


