#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "CustomAssert.h"

#define MODE_E     0
#define MODE_THETA 1
#define MODE_PHI   2

int main(int argc, char *argv[]);
vector<double> JERFit(PdfFileHelper &PdfFile, TTree *Tree, double ThetaMin, double ThetaMax, double R, int Mode);

int main(int argc, char *argv[])
{
   SetThumbStyle();

   CommandLine CL(argc, argv);

   string FileName   = CL.Get("Input");
   string OutputBase = CL.Get("OutputBase");
   string TreeName   = CL.Get("Tree", "MatchedTree");
   double R          = CL.GetDouble("R", 0.4);

   PdfFileHelper PdfFile(OutputBase + "_Check.pdf");
   PdfFile.AddTextPage("Jet resolution studies");

   int ThetaBinCount = 14;
   double ThetaBins[] = {0, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 1.0};

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get(TreeName.c_str());

   ofstream out(OutputBase + "_EnergyResolution.txt");
   string Formula = "sqrt([0]+[1]/x+[2]/x/x+[3]/x/x/x)";
   out << "{1 JetTheta 1 JetE " << Formula << " EnergyResolution}" << endl;
   PdfFile.AddTextPage("E resolution");
   for(int i = 0; i < ThetaBinCount; i++)
   {
      vector<double> Result = JERFit(PdfFile, Tree, ThetaBins[i], ThetaBins[i+1], R, MODE_E);

      out << ThetaBins[i] * M_PI << " " << ThetaBins[i+1] * M_PI;
      out << " " << Result.size();
      for(int j = 0; j < (int)Result.size(); j++)
         out << " " << Result[j];
      out << endl;
   }
   out.close();
   
   ofstream outtheta(OutputBase + "_ThetaResolution.txt");
   Formula = "[0]+[1]*x+[2]*x*x+[3]*x*x*x";
   outtheta << "{1 JetTheta 1 JetE " << Formula << " ThetaResolution}" << endl;
   PdfFile.AddTextPage("Theta resolution");
   for(int i = 0; i < ThetaBinCount; i++)
   {
      vector<double> Result = JERFit(PdfFile, Tree, ThetaBins[i], ThetaBins[i+1], R, MODE_THETA);

      outtheta << ThetaBins[i] * M_PI << " " << ThetaBins[i+1] * M_PI;
      outtheta << " " << Result.size();
      for(int j = 0; j < (int)Result.size(); j++)
         outtheta << " " << Result[j];
      outtheta << endl;
   }
   outtheta.close();

   ofstream outphi(OutputBase + "_PhiResolution.txt");
   Formula = "[0]+[1]*x+[2]*x*x+[3]*x*x*x";
   outphi << "{1 JetTheta 1 JetE " << Formula << " PhiResolution}" << endl;
   PdfFile.AddTextPage("Phi resolution");
   for(int i = 0; i < ThetaBinCount; i++)
   {
      vector<double> Result = JERFit(PdfFile, Tree, ThetaBins[i], ThetaBins[i+1], R, MODE_PHI);

      outphi << ThetaBins[i] * M_PI << " " << ThetaBins[i+1] * M_PI;
      outphi << " " << Result.size();
      for(int j = 0; j < (int)Result.size(); j++)
         outphi << " " << Result[j];
      outphi << endl;
   }
   outphi.close();

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<double> JERFit(PdfFileHelper &PdfFile, TTree *Tree, double ThetaMin, double ThetaMax, double R, int Mode)
{
   PdfFile.AddTextPage(Form("Theta = %.2f#pi ~ %.2f#pi", ThetaMin, ThetaMax));

   vector<pair<double, double>> Data;
   Data.clear();

   double GenE, GenPT, GenTheta, GenPhi, RecoE, RecoPT, RecoTheta, RecoPhi, Angle;
   Tree->SetBranchAddress("GenE",        &GenE);
   Tree->SetBranchAddress("GenPT",       &GenPT);
   Tree->SetBranchAddress("GenTheta",    &GenTheta);
   Tree->SetBranchAddress("GenPhi",      &GenPhi);
   Tree->SetBranchAddress("CorrectedE",  &RecoE);
   Tree->SetBranchAddress("CorrectedPT", &RecoPT);
   Tree->SetBranchAddress("RecoTheta",   &RecoTheta);
   Tree->SetBranchAddress("RecoPhi",     &RecoPhi);
   Tree->SetBranchAddress("Angle",       &Angle);

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

      double GenP = GenPT / sin(GenTheta);
      double RecoP = RecoPT / sin(RecoTheta);

      if(GenP < 4.5)
         continue;

      if(Mode == MODE_E)
         Data.push_back(pair<double, double>(GenE, RecoE / GenE - 1));
      if(Mode == MODE_THETA)
         Data.push_back(pair<double, double>(GenE, RecoTheta - GenTheta));
      if(Mode == MODE_PHI)
      {
         double DPhi = RecoPhi - GenPhi;
         if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
         if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
         Data.push_back(pair<double, double>(GenE, DPhi));
      }
   }

   sort(Data.begin(), Data.end());

   double MinE = -1, MaxE = -1;

   if(Data.size() > 1)
   {
      MinE = Data.begin()->first;
      MaxE = (Data.begin() + (Data.size() - 1))->first;
   }
   
   PdfFile.AddTextPage(Form("N = %d, E range = %.1f-%.1f", (int)Data.size(), MinE, MaxE));

   int N = Data.size();

   double Bins[51];

   int BinCount = 50;

   Assert(N >= 1000, Form("Warning! N = %d, not good fits", N));
   if(N < 5000)
      BinCount = N / 100;

   for(int i = 0; i < BinCount; i++)
      Bins[i] = Data[N/BinCount*i].first;
   Bins[BinCount] = MaxE;

   vector<vector<double>> AllData(BinCount);

   TH1D H("H", ";GenE;Number of jets", BinCount, Bins);
   H.SetStats(0);
   TProfile P("P", ";GenE;Response", BinCount, Bins, "S");
   P.SetStats(0);
   TH1D HRMS("HRMS", ";GenE;RMS", BinCount, Bins);
   HRMS.SetStats(0);

   TH1D HR1("HR1", "GenE = 30-40 GeV;RecoE/GenE - 1;", 100, -1, 1);
   TH1D HR2("HR2", "GenE = 40-50 GeV;RecoE/GenE - 1;", 100, -1, 1);
   HR1.SetStats(0);
   HR2.SetStats(0);

   if(Mode == MODE_THETA)   HR1.GetYaxis()->SetTitle("RecoTheta - GenTheta");
   if(Mode == MODE_THETA)   HR2.GetYaxis()->SetTitle("RecoTheta - GenTheta");
   if(Mode == MODE_PHI)     HR1.GetYaxis()->SetTitle("RecoPhi - GenPhi");
   if(Mode == MODE_PHI)     HR2.GetYaxis()->SetTitle("RecoPhi - GenPhi");

   for(int i = 0; i < N; i++)
   {
      int iB = 0;
      for(int j = 0; j < BinCount; j++)
         if(Bins[j] <= Data[i].first && Data[i].second < Bins[j+1])
            iB = j;

      AllData[iB].push_back(Data[i].second);
   }
   for(int i = 0; i < BinCount; i++)
      sort(AllData[i].begin(), AllData[i].end());

   for(int i = 0; i < BinCount; i++)
   {
      int Size = AllData[i].size();
      double X = H.GetBinCenter(i);
      for(int j = Size * 0.025; j < Size * 0.975; j++)
      {
         H.Fill(X);
         P.Fill(X, AllData[i][j]);
      }
      for(int j = 0; j < Size; j++)
      {
         if(X > 30 && X < 40)
            HR1.Fill(AllData[i][j]);
         if(X > 40 && X < 50)
            HR2.Fill(AllData[i][j]);
      }
   }
   for(int i = 1; i <= BinCount; i++)
      HRMS.SetBinContent(i, P.GetBinError(i));

   PdfFile.AddPlot(H);
   PdfFile.AddPlot(P);
   PdfFile.AddPlot(HRMS);
   PdfFile.AddPlot(HR1, "", true);
   PdfFile.AddPlot(HR2, "", true);

   TF1 F1("F1", "sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/x/x+[3]*[3]/x/x/x)", 0, MaxE * 1.2);
   F1.SetParameters(1, 1, 1, 1);
   F1.SetLineColor(kBlue);
   F1.SetLineWidth(5);
   TF1 F2("F2", "sqrt([0]*[0]+[1]*[1]/x+[2]*[2]/x/x+[3]*[3]/x/x/x+[4]*[4]/x/x/x/x)", 0, MaxE * 1.2);
   F2.SetParameters(1, 1, 1, 1, 1);
   F2.SetLineColor(kRed);
   TF1 F3("F3", "([0]*[0]+[1]*[1]/x+[2]*[2]/x/x+[3]*[3]/x/x/x)", 0, MaxE * 1.2);
   F3.SetParameters(1, 1, 1, 1);
   F3.SetLineColor(kGreen);
   F3.SetLineWidth(5);
   TF1 F4("F4", "pol3", 0, MaxE * 1.2);
   F4.SetLineColor(kYellow + 3);

   HRMS.Fit(&F1, "0");
   HRMS.Fit(&F2, "0");
   HRMS.Fit(&F3, "0");
   HRMS.Fit(&F4, "0");

   for(int i = 1; i <= BinCount; i++)
      HRMS.SetBinError(i, 0.0001);
   
   TCanvas Canvas;

   HRMS.Draw();
   if(Mode == MODE_E)
   {
      F1.Draw("same");
      F2.Draw("same");
      F3.Draw("same");
   }
   if(Mode == MODE_THETA || Mode == MODE_PHI)
      F4.Draw("same");
   HRMS.Draw("same");

   HRMS.SetMarkerSize(2);

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.05);
   Latex.SetTextAlign(32);
   if(Mode == MODE_E)
      Latex.DrawLatex(0.85, 0.80, "#color[2]{sqrt(P3)} #color[4]{sqrt(P4)} #color[3]{P4}");

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.20, 0.20, Form("%.2f-%.2f#pi", ThetaMin, ThetaMax));
   
   PdfFile.AddCanvas(Canvas);

   vector<double> Result;

   if(Mode == MODE_E)
   {
      Result.push_back(5);
      Result.push_back(Bins[BinCount-1]);
      Result.push_back(F1.GetParameter(0) * F1.GetParameter(0));
      Result.push_back(F1.GetParameter(1) * F1.GetParameter(1));
      Result.push_back(F1.GetParameter(2) * F1.GetParameter(2));
      Result.push_back(F1.GetParameter(3) * F1.GetParameter(3));
   }
   if(Mode == MODE_THETA || Mode == MODE_PHI)
   {
      Result.push_back(5);
      Result.push_back(Bins[BinCount-1]);
      Result.push_back(F4.GetParameter(0));
      Result.push_back(F4.GetParameter(1));
      Result.push_back(F4.GetParameter(2));
      Result.push_back(F4.GetParameter(3));
   }

   return Result;
}



