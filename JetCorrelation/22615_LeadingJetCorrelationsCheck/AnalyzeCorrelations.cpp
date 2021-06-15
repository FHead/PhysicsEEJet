#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
void DrawSuite(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, TH2D &H);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string FileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output", "Result.pdf");
   string OutsideThreshold = CL.Get("OutsideThreshold", "08");
   string JetThreshold1 = CL.Get("JetThreshold1", "08");
   string JetThreshold2 = CL.Get("JetThreshold2", "20");

   TFile File(FileName.c_str());

   TTree *T = (TTree *)File.Get("T");

   int ON, J1N1, J1N2, J2N1, J2N2;
   double J1P, J1Theta, J1Phi;
   double J2P, J2Theta, J2Phi;

   T->SetBranchAddress(Form("O%s", OutsideThreshold.c_str()), &ON);
   T->SetBranchAddress(Form("J1%s", JetThreshold1.c_str()), &J1N1);
   T->SetBranchAddress(Form("J1%s", JetThreshold2.c_str()), &J1N2);
   T->SetBranchAddress(Form("J2%s", JetThreshold1.c_str()), &J2N1);
   T->SetBranchAddress(Form("J2%s", JetThreshold2.c_str()), &J2N2);
   T->SetBranchAddress("J1P", &J1P);
   T->SetBranchAddress("J1Theta", &J1Theta);
   T->SetBranchAddress("J1Phi", &J1Phi);
   T->SetBranchAddress("J2P", &J2P);
   T->SetBranchAddress("J2Theta", &J2Theta);
   T->SetBranchAddress("J2Phi", &J2Phi);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Dijet correlation");

   TH1D HON("HON", ";N(not in leading dijet jet);", 30, 0, 30);

   TH1D HJ1R("HJ1R", ";N2/N1(Jet);", 10, 0, 1);
   TH1D HJ2R("HJ2R", ";N2/N1(Jet);", 10, 0, 1);
   TH2D HJJR("HJJR", ";N2/N1(Jet1);N2/N1(Jet2)", 10, 0, 1, 10, 0, 1);

   int NBins = 6;
   int Bins[] = {0, 2, 4, 7, 11, 16, 30};

   TH1D HJ1RB0("HJ1RB0", ";N2/N1(Jet);", 10, 0, 1);
   TH1D HJ2RB0("HJ2RB0", ";N2/N1(Jet);", 10, 0, 1);
   TH2D HJJRB0("HJJRB0", ";N2/N1(Jet1);N2/N1(Jet2)", 10, 0, 1, 10, 0, 1);
   TH1D HJ1RB1("HJ1RB1", ";N2/N1(Jet);", 10, 0, 1);
   TH1D HJ2RB1("HJ2RB1", ";N2/N1(Jet);", 10, 0, 1);
   TH2D HJJRB1("HJJRB1", ";N2/N1(Jet1);N2/N1(Jet2)", 10, 0, 1, 10, 0, 1);
   TH1D HJ1RB2("HJ1RB2", ";N2/N1(Jet);", 10, 0, 1);
   TH1D HJ2RB2("HJ2RB2", ";N2/N1(Jet);", 10, 0, 1);
   TH2D HJJRB2("HJJRB2", ";N2/N1(Jet1);N2/N1(Jet2)", 10, 0, 1, 10, 0, 1);
   TH1D HJ1RB3("HJ1RB3", ";N2/N1(Jet);", 10, 0, 1);
   TH1D HJ2RB3("HJ2RB3", ";N2/N1(Jet);", 10, 0, 1);
   TH2D HJJRB3("HJJRB3", ";N2/N1(Jet1);N2/N1(Jet2)", 10, 0, 1, 10, 0, 1);
   TH1D HJ1RB4("HJ1RB4", ";N2/N1(Jet);", 10, 0, 1);
   TH1D HJ2RB4("HJ2RB4", ";N2/N1(Jet);", 10, 0, 1);
   TH2D HJJRB4("HJJRB4", ";N2/N1(Jet1);N2/N1(Jet2)", 10, 0, 1, 10, 0, 1);
   TH1D HJ1RB5("HJ1RB5", ";N2/N1(Jet);", 10, 0, 1);
   TH1D HJ2RB5("HJ2RB5", ";N2/N1(Jet);", 10, 0, 1);
   TH2D HJJRB5("HJJRB5", ";N2/N1(Jet1);N2/N1(Jet2)", 10, 0, 1, 10, 0, 1);

   HON.SetStats(0);

   int EntryCount = T->GetEntries();;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      if(J1Theta < 0.2 * M_PI || J1Theta > 0.8 * M_PI)
         continue;
      if(J2Theta < 0.2 * M_PI || J2Theta > 0.8 * M_PI)
         continue;

      if(J1P < 10)   continue;
      if(J2P < 10)   continue;

      HON.Fill(ON);

      double J1R = (double)J1N2 / J1N1;
      double J2R = (double)J2N2 / J2N1;

      HJ1R.Fill(J1R);
      HJ2R.Fill(J2R);
      HJJR.Fill(J1R, J2R);

      if(ON >= Bins[0] && ON < Bins[1])
      {
         HJ1RB0.Fill(J1R);
         HJ2RB0.Fill(J2R);
         HJJRB0.Fill(J1R, J2R);
      }
      if(ON >= Bins[1] && ON < Bins[2])
      {
         HJ1RB1.Fill(J1R);
         HJ2RB1.Fill(J2R);
         HJJRB1.Fill(J1R, J2R);
      }
      if(ON >= Bins[2] && ON < Bins[3])
      {
         HJ1RB2.Fill(J1R);
         HJ2RB2.Fill(J2R);
         HJJRB2.Fill(J1R, J2R);
      }
      if(ON >= Bins[3] && ON < Bins[4])
      {
         HJ1RB3.Fill(J1R);
         HJ2RB3.Fill(J2R);
         HJJRB3.Fill(J1R, J2R);
      }
      if(ON >= Bins[4] && ON < Bins[5])
      {
         HJ1RB4.Fill(J1R);
         HJ2RB4.Fill(J2R);
         HJJRB4.Fill(J1R, J2R);
      }
      if(ON >= Bins[5] && ON < Bins[6])
      {
         HJ1RB5.Fill(J1R);
         HJ2RB5.Fill(J2R);
         HJJRB5.Fill(J1R, J2R);
      }
   }

   PdfFile.AddPlot(HON);

   PdfFile.AddTextPage("Inclusive");
   DrawSuite(PdfFile, HJ1R, HJ2R, HJJR);
   PdfFile.AddTextPage(Form("N(outside) = %d-%d", Bins[0], Bins[1] - 1));
   DrawSuite(PdfFile, HJ1RB0, HJ2RB0, HJJRB0);
   PdfFile.AddTextPage(Form("N(outside) = %d-%d", Bins[1], Bins[2] - 1));
   DrawSuite(PdfFile, HJ1RB1, HJ2RB1, HJJRB1);
   PdfFile.AddTextPage(Form("N(outside) = %d-%d", Bins[2], Bins[3] - 1));
   DrawSuite(PdfFile, HJ1RB2, HJ2RB2, HJJRB2);
   PdfFile.AddTextPage(Form("N(outside) = %d-%d", Bins[3], Bins[4] - 1));
   DrawSuite(PdfFile, HJ1RB3, HJ2RB3, HJJRB3);
   PdfFile.AddTextPage(Form("N(outside) = %d-%d", Bins[4], Bins[5] - 1));
   DrawSuite(PdfFile, HJ1RB4, HJ2RB4, HJJRB4);
   PdfFile.AddTextPage(Form("N(outside) = %d-%d", Bins[5], Bins[6] - 1));
   DrawSuite(PdfFile, HJ1RB5, HJ2RB5, HJJRB5);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}

void DrawSuite(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, TH2D &H)
{
   H1.SetStats(0);
   H2.SetStats(0);
   H.SetStats(0);

   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());
   H.Scale(1 / H.Integral());

   TCanvas Canvas;
   H1.Draw("hist");
   H2.SetLineColor(kRed);
   H2.Draw("hist same");
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddPlot(H, "colz", false, true);

   for(int iX = 1; iX <= 10; iX++)
   {
      for(int iY = 1; iY <= 10; iY++)
      {
         H.SetBinContent(iX, iY,
            H.GetBinContent(iX, iY) / H1.GetBinContent(iX) / H2.GetBinContent(iY));
      }
   }

   H.SetMinimum(0.1);
   H.SetMaximum(10);

   PdfFile.AddPlot(H, "colz", false, true);

   TH1D HP("HP", "N2/N1 (J1+J2)", 20, 0, 2);
   HP.SetStats(0);

   for(int iX = 1; iX <= 10; iX++)
      for(int iY = 1; iY <= 10; iY++)
         HP.Fill((iX + iY) * 0.1, H.GetBinContent(iX, iY));

   HP.SetMaximum(14);
   PdfFile.AddPlot(HP, "hist");
}




