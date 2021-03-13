#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void PlotCorrelation(PdfFileHelper &PdfFile, string FileName, int Moment, int Bin, double Min, double Max, double MinTheta, double MinP, bool Inverse = false);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string Input = CL.Get("input");
   string Output = CL.Get("output");

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Correlation plots");

   int Bin = 25;
   double MinP = 30;
   bool Inverse = false;
   PlotCorrelation(PdfFile, Input, 0, 30, 0, 30, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 1, Bin, 0, 10, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 2, Bin, 0, 5, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 3, Bin, 0, 3.5, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 4, Bin, 1, 1.08, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 5, Bin, 0, 0.5, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 6, Bin, 0, 0.30, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 7, Bin, 0, 0.15, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 8, 10, 0, 200, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 8, Bin, 0, 600, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 9, Bin, 0, 200, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 10, Bin, 0, 120, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 11, Bin, 0, 80, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 12, Bin, 0, 1, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 13, Bin, 0, 0.05, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 14, Bin, 0, 25, 0.25 * M_PI, MinP, Inverse);
   
   Inverse = true;
   PlotCorrelation(PdfFile, Input, 1, Bin, 0, 10, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 2, Bin, 0, 15, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 3, Bin, 0, 40, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 4, Bin, 0.93, 1, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 5, Bin, 0, 40, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 6, Bin, 0, 100, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 7, Bin, 0, 200, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 8, Bin, 0, 0.1, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 9, Bin, 0, 0.5, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 10, Bin, 0, 2, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 11, Bin, 0, 7.5, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 12, Bin, 0, 100, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 13, Bin, 0, 600, 0.25 * M_PI, MinP, Inverse);
   PlotCorrelation(PdfFile, Input, 14, Bin, 0, 80, 0.25 * M_PI, MinP, Inverse);
   
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotCorrelation(PdfFileHelper &PdfFile, string FileName, int Moment, int Bin, double Min, double Max, double MinTheta, double MinP, bool Inverse)
{
   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");
   if(Tree == nullptr)
      return;

   double J1P, J1Theta, J1Phi;
   double J2P, J2Theta, J2Phi;
   int NMoment;
   double Alpha[100], Beta[100];
   double J1M[100], J2M[100];

   Tree->SetBranchAddress("J1P", &J1P);
   Tree->SetBranchAddress("J1Theta", &J1Theta);
   Tree->SetBranchAddress("J1Phi", &J1Phi);
   Tree->SetBranchAddress("J2P", &J2P);
   Tree->SetBranchAddress("J2Theta", &J2Theta);
   Tree->SetBranchAddress("J2Phi", &J2Phi);
   Tree->SetBranchAddress("NMoment", &NMoment);
   Tree->SetBranchAddress("Alpha", &Alpha);
   Tree->SetBranchAddress("Beta", &Beta);
   Tree->SetBranchAddress("J1M", &J1M);
   Tree->SetBranchAddress("J2M", &J2M);

   TH1D HTheta1("HTheta1", ";#theta_{1};", 100, 0, M_PI);
   TH1D HTheta2("HTheta2", ";#theta_{2};", 100, 0, M_PI);
   TH2D HTheta12("HTheta12", ";#theta_{1};#theta_{2}", 100, 0, M_PI, 100, 0, M_PI);
   TH2D HPhi12("HPhi12", ";#Phi_{1};#Phi_{2}", 100, -M_PI, M_PI, 100, -M_PI, M_PI);
   TH1D HM1("HM1", ";Jet 1 moment;", Bin, Min, Max);
   TH1D HM2("HM2", ";Jet 2 moment;", Bin, Min, Max);
   TH2D HM12("HM12", ";Jet 1 moment;Jet 2 moment", Bin, Min, Max, Bin, Min, Max);
   TH2D HM12Corr("HM12Corr", ";Jet 1 moment;Jet 2 moment", Bin, Min, Max, Bin, Min, Max);

   if(Inverse == true)
   {
      HM1.GetXaxis()->SetTitle(Form("(%s)^{-1}", HM1.GetXaxis()->GetTitle()));
      HM2.GetXaxis()->SetTitle(Form("(%s)^{-1}", HM2.GetXaxis()->GetTitle()));
      HM12.GetXaxis()->SetTitle(Form("(%s)^{-1}", HM12.GetXaxis()->GetTitle()));
      HM12.GetYaxis()->SetTitle(Form("(%s)^{-1}", HM12.GetYaxis()->GetTitle()));
      HM12Corr.GetXaxis()->SetTitle(Form("(%s)^{-1}", HM12Corr.GetXaxis()->GetTitle()));
      HM12Corr.GetYaxis()->SetTitle(Form("(%s)^{-1}", HM12Corr.GetYaxis()->GetTitle()));
   }

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(J1Theta < MinTheta)          continue;
      if(J1Theta > M_PI - MinTheta)   continue;
      if(J2Theta < MinTheta)          continue;
      if(J2Theta > M_PI - MinTheta)   continue;

      if(J1P < MinP)   continue;
      if(J2P < MinP)   continue;
      if(J1P > 42.5)   continue;
      if(J2P > 42.5)   continue;

      double M1 = -1, M2 = -1;
      if(Moment < NMoment && Moment >= 0)
      {
         M1 = J1M[Moment];
         M2 = J2M[Moment];
      }
      if(Inverse == true)
      {
         M1 = 1 / M1;
         M2 = 1 / M2;
      }

      HTheta1.Fill(J1Theta);
      HTheta2.Fill(J2Theta);
      HTheta12.Fill(J1Theta, J2Theta);
      HPhi12.Fill(J1Phi, J2Phi);
      HM1.Fill(M1);
      HM2.Fill(M2);
      HM12.Fill(M1, M2);
   }

   for(int i1 = 1; i1 <= Bin; i1++)
   {
      for(int i2 = 1; i2 <= Bin; i2++)
      {
         double M1 = HM1.GetBinContent(i1);
         double M2 = HM2.GetBinContent(i2);
         double M12 = HM12.GetBinContent(i1, i2);
         if(M1 > 1e-10 && M2 > 1e-10)
            HM12Corr.SetBinContent(i1, i2, M12 / M1 / M2);
      }
   }
   HM12Corr.Scale(HM1.GetEntries());
   HM12Corr.SetMinimum(0.0);
   HM12Corr.SetMaximum(2.0);

   double alpha = -1, beta = -1;
   if(Moment < NMoment && Moment >= 0)
      alpha = Alpha[Moment], beta = Beta[Moment];
   PdfFile.AddTextPage(Form("[%d]: #alpha = %.02f, #beta = %.02f", Moment, alpha, beta));

   HM12.SetStats(0);
   HM12.SetTitle(Form("#alpha = %.02f, #beta = %.02f", alpha, beta));

   HM12Corr.SetStats(0);
   HM12Corr.SetTitle(Form("#alpha = %.02f, #beta = %.02f", alpha, beta));

   PdfFile.AddPlot(HTheta1);
   PdfFile.AddPlot(HTheta2);
   PdfFile.AddPlot(HTheta12, "colz");
   PdfFile.AddPlot(HPhi12, "colz");
   PdfFile.AddPlot(HM1);
   PdfFile.AddPlot(HM2);
   PdfFile.AddPlot(HM12, "colz");
   PdfFile.AddPlot(HM12, "colz", false, true);
   PdfFile.AddPlot(HM12Corr, "colz");

   File.Close();
}




