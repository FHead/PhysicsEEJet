#include <iostream>
#include <sstream>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"
#include "TProfile2D.h"
#include "TProfile.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TF1.h"
#include "TF2.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "DataHelper.h"

int main(int argc, char *argv[]);
string Print(TF1 &F, int I);

int main(int argc, char *argv[])
{
   SetThumbStyle();
   gStyle->SetPadRightMargin(0.15);

   TFile File("MCNoCutDebug.root");

   TTree *T = (TTree *)File.Get("UnfoldingTree");

   int NBin = 50;
   double Min = 10;
   double Max = 45.6;

   TProfile PS("PS", ";;", NBin, Min * 2, Max * 2);
   TProfile2D P("P", ";J1;J2", NBin, Min, Max, NBin, Min, Max);
   TProfile P1("P1", ";;", NBin, Min, Max);
   TProfile P2("P2", ";;", NBin, Min, Max);

   T->SetAlias("JetPE", "GenJetE[0]*(GenJetTheta[0]>GenJetTheta[1])+GenJetE[1]*(GenJetTheta[0]<=GenJetTheta[1])");
   T->SetAlias("JetME", "GenJetE[0]*(GenJetTheta[0]<=GenJetTheta[1])+GenJetE[1]*(GenJetTheta[0]>GenJetTheta[1])");
   T->SetAlias("JetCut", "(GenJetTheta[0] > 0.2 * 3.14159 && GenJetTheta[0] < 0.8 * 3.14159 && GenJetTheta[1] > 0.2 * 3.14159 && GenJetTheta[1] < 0.8 * 3.14159)");

   T->Draw("GenHybridE[4]>83:GenJetE[0]+GenJetE[1]>>PS", "JetCut", "prof");
   T->Draw("GenHybridE[4]>83:GenJetE[1]:GenJetE[0]>>P", "JetCut", "prof2d colz");
   T->Draw("GenHybridE[4]>83:GenJetE[0]>>P1", "JetCut", "prof");
   T->Draw("GenHybridE[4]>83:GenJetE[1]>>P2", "JetCut", "prof");

   P1.Add(&P2);
   
   P.SetStats(0);
   P.GetXaxis()->SetTitle("Leading jet E (GeV)");
   P.GetYaxis()->SetTitle("Subleading jet E (GeV)");
   P.SetTitle("");
   P.SetMinimum(0.5);

   PS.SetStats(0);
   PS.SetLineColor(kBlack);
   PS.SetLineWidth(2);
   PS.GetXaxis()->SetTitle("Leading Dijet Sum E (GeV)");
   
   P1.SetStats(0);
   P1.SetLineColor(kBlack);
   P1.SetLineWidth(2);
   P1.GetXaxis()->SetTitle("Leading Dijet Jet E (GeV)");

   PdfFileHelper PdfFile("CorrectionFactor.pdf");
   PdfFile.AddTextPage("Correction factors");

   PdfFile.AddPlot(PS, "", false, false, true);

   TF1 F("F", "min([0]+[1]*x,1.0)", 0, 100);
   F.SetParameters(0.2, 0.01);
   PS.Fit(&F);
   
   PdfFile.AddPlot(PS, "", false, false, true);

   PdfFile.AddPlot(P, "colz");
   
   TF2 F2("F2", "min([0]+[1]*x+[2]*y+[3]*x*y,1.0)");
   F2.SetParameters(0.2, 0.01, 0.01, 0.00);
   P.Fit(&F2);
   
   PdfFile.AddPlot(P, "colz");

   PdfFile.AddPlot(P1, "", false, false, true);
   
   TF1 F3("F3", "min([0]+[1]*x,[2]+[3]*erf((x-[4])/[5]))");
   F3.SetParameters(0.20, 0.03, 0.9, 0.1, 35, 5);
   P1.Fit(&F3);
   
   PdfFile.AddPlot(P1, "", false, false, true);

   DataHelper DHFile("Correction.dh");

   DHFile["DijetSumE"]["P0"] = F.GetParameter(0);
   DHFile["DijetSumE"]["E0"] = F.GetParError(0);
   DHFile["DijetSumE"]["P1"] = F.GetParameter(1);
   DHFile["DijetSumE"]["E1"] = F.GetParError(1);
   DHFile["DijetJetE"]["P0"] = F3.GetParameter(0);
   DHFile["DijetJetE"]["E0"] = F3.GetParError(0);
   DHFile["DijetJetE"]["P1"] = F3.GetParameter(1);
   DHFile["DijetJetE"]["E1"] = F3.GetParError(1);
   DHFile["DijetJetE"]["P2"] = F3.GetParameter(2);
   DHFile["DijetJetE"]["E2"] = F3.GetParError(2);
   DHFile["DijetJetE"]["P3"] = F3.GetParameter(3);
   DHFile["DijetJetE"]["E3"] = F3.GetParError(3);
   DHFile["DijetJetE"]["P4"] = F3.GetParameter(4);
   DHFile["DijetJetE"]["E4"] = F3.GetParError(4);
   DHFile["DijetJetE"]["P5"] = F3.GetParameter(5);
   DHFile["DijetJetE"]["E5"] = F3.GetParError(5);

   DHFile.SaveToFile("Correction.dh");

   cout << " & Leading Dijet Jet Energy & Leading Dijet Total Energy \\\\\\hline" << endl;
   for(int i = 0; i <= 5; i++)
      cout << "$a_" << i << "$ & " << Print(F3, i) << " & " << Print(F, i) << " \\\\\\hline" << endl;

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

string Print(TF1 &F, int I)
{
   stringstream str;
   if(I < F.GetNpar())
      str << "$" << fixed << F.GetParameter(I) << " \\pm " << fixed << F.GetParError(I) << "$";
   else
      str << "-";
   return str.str();
}
