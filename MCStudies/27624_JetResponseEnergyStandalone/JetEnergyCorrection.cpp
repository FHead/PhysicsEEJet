#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#include "TCanvas.h"
#include "TLatex.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TF1.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
vector<double> JECFit(PdfFileHelper &PdfFile, TTree *Tree, double ThetaMin, double ThetaMax, double R);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName             = CL.Get("File", "AllMatched.root");
   string TreeName             = CL.Get("Tree", "MatchedTree");
   string OutputFileName       = CL.Get("Output", "JEC.txt");
   string QualityCheckFileName = CL.Get("Check", "JECCheck.pdf");
   double R                    = CL.GetDouble("R", 0.4);

   PdfFileHelper PdfFile(QualityCheckFileName);
   PdfFile.AddTextPage("JEC Quality Check");

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get(TreeName.c_str());

   Assert(Tree != nullptr, "Tree not found!  Check file name or tree name");

   int ThetaBinCount = 18;
   double ThetaBins[] = {0, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 1.0};

   string Formula = "1/([0]+[1]*x+[2]*x*x+[3]*x*x*x)";

   ofstream out(OutputFileName);

   out << "{1 JetTheta 1 JetE " << Formula << " L2Relative}" << endl;

   for(int i = 0; i < ThetaBinCount; i++)
   {
      vector<double> Result = JECFit(PdfFile, Tree, ThetaBins[i], ThetaBins[i+1], R);

      out << ThetaBins[i] * M_PI << " " << ThetaBins[i+1] * M_PI;
      out << " " << Result.size();
      for(int j = 0; j < (int)Result.size(); j++)
         out << " " << Result[j];
      out << endl;
   }

   out.close();

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<double> JECFit(PdfFileHelper &PdfFile, TTree *Tree, double ThetaMin, double ThetaMax, double R)
{
   PdfFile.AddTextPage(Form("Theta = %.2f#pi ~ %.2f#pi", ThetaMin, ThetaMax));

   vector<pair<double, double>> Data;
   Data.clear();

   double GenE, GenTheta, RecoE, RecoTheta, Angle;
   Tree->SetBranchAddress("GenE",      &GenE);
   Tree->SetBranchAddress("GenTheta",  &GenTheta);
   Tree->SetBranchAddress("RecoE",     &RecoE);
   Tree->SetBranchAddress("RecoTheta", &RecoTheta);
   Tree->SetBranchAddress("Angle",     &Angle);

   // double Threshold = 0.2;
   // if(fabs(R - 0.8) < 1e-5)
   //    Threshold = 0.37;
   
   double Threshold = 0.08;
   if(fabs(R - 0.8) < 1e-5)
      Threshold = 0.10;

   int EntryCount = Tree->GetEntries();
   cout << "Number of entries in the tree: " << EntryCount << endl;
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);
      if(GenTheta <= ThetaMin * M_PI)
         continue;
      if(GenTheta > ThetaMax * M_PI)
         continue;
      if(1 - cos(Angle) > Threshold)
         continue;

      if(GenE < 5)
         continue;

      Data.push_back(pair<double, double>(GenE, RecoE));
   }

   sort(Data.begin(), Data.end());

   double MinE = -1, MaxE = -1;

   if(Data.size() > 1)
   {
      MinE = Data.begin()->first;
      MaxE = (Data.begin() + (Data.size() - 1))->first;
   }
   
   PdfFile.AddTextPage(Form("N = %d, P range = %.1f-%.1f", (int)Data.size(), MinE, MaxE));

   int N = Data.size();

   double Bins[51];

   int BinCount = 50;

   Assert(N >= 1000, Form("Warning! N = %d, not good fits", N));
   if(N < 5000)
      BinCount = N / 100;

   for(int i = 0; i < BinCount; i++)
      Bins[i] = Data[N/BinCount*i].first;
   Bins[BinCount] = MaxE;

   TH1D H("H", ";GenE;Number of jets", BinCount, Bins);
   H.SetStats(0);
   TProfile P("E", ";GenE;Response", BinCount, Bins);
   P.SetStats(0);

   TH1D HR("HR", "GenE = 30-40 GeV;RecoE/GenE;", 100, 0, 2);
   // HR.SetStats(0);

   for(int i = 0; i < N; i++)
   {
      H.Fill(Data[i].first);
      P.Fill(Data[i].first, Data[i].second / Data[i].first);

      if(Data[i].first > 30 && Data[i].first < 40)
         HR.Fill(Data[i].second / Data[i].first);
   }

   PdfFile.AddPlot(H);
   PdfFile.AddPlot(P);
   PdfFile.AddPlot(HR);

   TF1 F1("F1", "pol2",               0, MaxE * 1.2);
   TF1 F2("F2", "[0]+[1]*exp([2]*x)", 0, MaxE * 1.2);
   TF1 F3("F3", "pol3",               0, MaxE * 1.2);
   TF1 F4("F4", "pol4",               0, MaxE * 1.2);

   F2.SetParameters(0.9, 0.1, 0.0001);

   F1.SetLineColor(kBlue);
   F2.SetLineColor(kRed);
   F3.SetLineColor(kGreen);
   F4.SetLineColor(kMagenta);

   P.Fit(&F1, "0");
   P.Fit(&F2, "0");
   P.Fit(&F3, "0");
   P.Fit(&F4, "0");

   TCanvas Canvas;

   P.Draw();
   F1.Draw("same");
   F2.Draw("same");
   F3.Draw("same");
   F4.Draw("same");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.025);
   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.12, 0.87, "#color[2]{exp} #color[4]{pol2} #color[3]{pol3} #color[6]{pol4}");
   
   PdfFile.AddCanvas(Canvas);

   vector<double> Result;

   Result.push_back(MinE);
   Result.push_back(MaxE);
   Result.push_back(F3.GetParameter(0));
   Result.push_back(F3.GetParameter(1));
   Result.push_back(F3.GetParameter(2));
   Result.push_back(F3.GetParameter(3));

   return Result;
}



