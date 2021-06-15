#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
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
#include "TFitResult.h"
#include "TMatrix.h"
#include "TGraph.h"

#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooRealVar.h"
#include "RooMultiVarGaussian.h"
#include "RooDataSet.h"
using namespace RooFit;

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "DataHelper.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
string Print(TF1 &F, int I);
void AddPlot(PdfFileHelper &PdfFile, TProfile &P, DataHelper &DHFile, string State);

int main(int argc, char *argv[])
{
   SetThumbStyle();
   gStyle->SetPadRightMargin(0.15);

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input", "MCNoCutDebug.root");
   string Suffix        = CL.Get("Suffix", "");
   string DHFileName    = CL.Get("DHFile", "Correction.dh");
   double HybridECut    = CL.GetDouble("HybridECut", 83);

   TFile File(InputFileName.c_str());

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

   int N = 99999999999;
   T->Draw(Form("GenHybridE[4]>%f:GenJetE[0]+GenJetE[1]>>PS", HybridECut), "JetCut", "prof", N);
   T->Draw(Form("GenHybridE[4]>%f:GenJetE[1]:GenJetE[0]>>P", HybridECut), "JetCut", "prof2d colz", N);
   T->Draw(Form("GenHybridE[4]>%f:GenJetE[0]>>P1", HybridECut), "JetCut", "prof", N);
   T->Draw(Form("GenHybridE[4]>%f:GenJetE[1]>>P2", HybridECut), "JetCut", "prof", N);

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
   TFitResultPtr FF = PS.Fit(&F, "S");
   
   PdfFile.AddPlot(PS, "", false, false, true);

   PdfFile.AddPlot(P, "colz");
   
   TF2 F2("F2", "min([0]+[1]*x+[2]*y+[3]*x*y,1.0)");
   F2.SetParameters(0.2, 0.01, 0.01, 0.00);
   TFitResultPtr F2F = P.Fit(&F2, "S");
   
   PdfFile.AddPlot(P, "colz");

   PdfFile.AddPlot(P1, "", false, false, true);
   
   TF1 F3("F3", "min([0]+[1]*x,[2]+[3]*erf((x-[4])/[5]))");
   F3.SetParameters(0.20, 0.03, 0.9, 0.1, 35, 5);
   TFitResultPtr F3F = P1.Fit(&F3, "S");
   
   PdfFile.AddPlot(P1, "", false, false, true);
   
   TF1 F4("F4", "min([0]+[1]*x,[2]+[3]*erf((x-[4])/[5]))*(1+[6]*x)");
   F4.SetParameters(0.20, 0.03, 0.9, 0.1, 35, 5, -0.001);
   P1.Fit(&F4);
   TFitResultPtr F4F = P1.Fit(&F4, "S");
   
   PdfFile.AddPlot(P1, "", false, false, true);

   DataHelper DHFile(DHFileName);

   DHFile["DijetSumE"+Suffix]["Formula"] = "1/min([0]+[1]*x,1.0)";
   DHFile["DijetSumE"+Suffix]["N"] = 2;
   DHFile["DijetSumE"+Suffix]["P0"] = F.GetParameter(0);
   DHFile["DijetSumE"+Suffix]["E0"] = F.GetParError(0);
   DHFile["DijetSumE"+Suffix]["P1"] = F.GetParameter(1);
   DHFile["DijetSumE"+Suffix]["E1"] = F.GetParError(1);

   TMatrixDSym CovF = FF->GetCovarianceMatrix();
   for(int i = 0; i < 2; i++)
      for(int j = 0; j < 2; j++)
         DHFile["DijetSumE"+Suffix]["C_"+to_string(i)+"_"+to_string(j)] = CovF[i][j] * 25;

   DHFile["DijetJetE"+Suffix]["Formula"] = "1/(min([0]+[1]*x,[2]+[3]*erf((x-[4])/[5]))*(1+[6]*x))";
   DHFile["DijetJetE"+Suffix]["N"] = 7;
   DHFile["DijetJetE"+Suffix]["P0"] = F4.GetParameter(0);
   DHFile["DijetJetE"+Suffix]["E0"] = F4.GetParError(0);
   DHFile["DijetJetE"+Suffix]["P1"] = F4.GetParameter(1);
   DHFile["DijetJetE"+Suffix]["E1"] = F4.GetParError(1);
   DHFile["DijetJetE"+Suffix]["P2"] = F4.GetParameter(2);
   DHFile["DijetJetE"+Suffix]["E2"] = F4.GetParError(2);
   DHFile["DijetJetE"+Suffix]["P3"] = F4.GetParameter(3);
   DHFile["DijetJetE"+Suffix]["E3"] = F4.GetParError(3);
   DHFile["DijetJetE"+Suffix]["P4"] = F4.GetParameter(4);
   DHFile["DijetJetE"+Suffix]["E4"] = F4.GetParError(4);
   DHFile["DijetJetE"+Suffix]["P5"] = F4.GetParameter(5);
   DHFile["DijetJetE"+Suffix]["E5"] = F4.GetParError(5);
   DHFile["DijetJetE"+Suffix]["P6"] = F4.GetParameter(6);
   DHFile["DijetJetE"+Suffix]["E6"] = F4.GetParError(6);

   TMatrixDSym CovF4 = F4F->GetCovarianceMatrix();
   for(int i = 0; i < 7; i++)
   {
      for(int j = 0; j < 7; j++)
      {
         double Factor = 1;
         if(i == 0 || i == 1)   Factor = Factor * 2;
         else                   Factor = Factor * 20;
         if(j == 0 || j == 1)   Factor = Factor * 2;
         else                   Factor = Factor * 20;
         DHFile["DijetJetE"+Suffix]["C_"+to_string(i)+"_"+to_string(j)] = CovF4[i][j] * Factor;
      }
   }

   DHFile.SaveToFile(DHFileName);

   cout << " & Leading Dijet Jet Energy & Leading Dijet Total Energy \\\\\\hline" << endl;
   for(int i = 0; i <= 6; i++)
      cout << "$a_" << i << "$ & " << Print(F4, i) << " & " << Print(F, i) << " \\\\\\hline" << endl;

   AddPlot(PdfFile, PS, DHFile, "DijetSumE" + Suffix);
   AddPlot(PdfFile, P1, DHFile, "DijetJetE" + Suffix);

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

void AddPlot(PdfFileHelper &PdfFile, TProfile &P, DataHelper &DHFile, string State)
{
   int N = DHFile[State]["N"].GetInteger();

   RooArgList XVector;
   RooArgList MuVector;

   for(int i = 0; i < N; i++)
   {
      XVector.add(*(new RooRealVar(Form("X%d", i), "", 0)));
      MuVector.add(*(new RooRealVar(Form("Mu%d", i), "", DHFile[State][Form("P%d",i)].GetDouble())));
   }

   TMatrixDSym Covariance(N);
   for(int i = 0; i < N; i++)
   {
      for(int j = 0; j < N; j++)
      {
         if(i == j)
            Covariance(i, j) = DHFile[State][Form("C_%d_%d",i,j)].GetDouble();
         else
            Covariance(i, j) = 0;
      }
   }

   RooMultiVarGaussian Gaussian("Gaussian", "", XVector, MuVector, Covariance);

   TF1 Function("Function", DHFile[State]["Formula"].GetString().c_str());
  
   TGraph GDown, GUp;

   RooDataSet *Data = Gaussian.generate(XVector, 1000);
   
   int Index = 0;
   for(double x = 0; x < 100; x = x + 0.1, Index++)
   {
      vector<double> Values;

      for(int i = 0; i < 1000; i++)
      {
         const RooArgSet *Set = Data->get(i);

         for(int j = 0; j < N; j++)
         {
            RooRealVar *X = (RooRealVar *)Set->find(Form("X%d", j));
            Function.SetParameter(j, X->getValV());
         }

         Values.push_back(1 / Function.Eval(x));
      }

      sort(Values.begin(), Values.end());

      GUp.SetPoint(Index, x, Values[840]);
      GDown.SetPoint(Index, x, Values[160]);
   }

   TCanvas Canvas;

   P.Draw();

   GDown.Draw("l");
   GUp.Draw("l");

   PdfFile.AddCanvas(Canvas);
}
