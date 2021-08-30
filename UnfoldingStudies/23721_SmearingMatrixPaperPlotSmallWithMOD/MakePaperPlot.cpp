#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TPaletteAxis.h"
#include "TLatex.h"
#include "TImage.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"
#include "CustomAssert.h"

#define MAX 1000

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
void SelfNormalize(TH1D *H, vector<double> Bins1, vector<double> Bins2);
TH1D *BuildSystematics(TH1D *HResult, TH1D *HVariation);
TH2D *Transcribe(TH2D *HMaster, int R, int C, vector<double> &XBinning, vector<double> &YBinning, bool DoRowNormalize, bool DoColumnNormalize);
void RowNormalize(TH2D *H);
void ColumnNormalize(TH2D *H);
void SetPad(TPad *P);
void SetAxis(TGaxis &A);
void SetWorld(TH2D *H);
TGraphAsymmErrors CalculateRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2);
double CalculateIntegral(TGraphAsymmErrors &G, double MinX = -999);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string InputFileName           = CL.Get("Input");
   string InputResponseName       = CL.Get("Response", "HMCResponse");
   string OutputFileName          = CL.Get("Output");
   string FinalOutputFileName     = CL.Get("FinalOutput", "Meow.pdf");
   double GenPrimaryMinOverwrite  = CL.GetDouble("GenPrimaryMin", -999);
   double GenPrimaryMaxOverwrite  = CL.GetDouble("GenPrimaryMax", 999);
   double RecoPrimaryMinOverwrite = CL.GetDouble("RecoPrimaryMin", -999);
   double RecoPrimaryMaxOverwrite = CL.GetDouble("RecoPrimaryMax", 999);

   bool LogZ                      = CL.GetBool("LogZ", true);
   bool DoRowNormalize            = CL.GetBool("RowNormalize", false);
   bool DoColumnNormalize         = CL.GetBool("ColumnNormalize", false);

   string PrimaryLabel            = CL.Get("Primary", "Jet P");
   string BinningLabel            = CL.Get("Binning", "Jet P");

   vector<int> GroupX             = CL.GetIntVector("GroupX", vector<int>{});
   vector<int> GroupY             = CL.GetIntVector("GroupY", vector<int>{});

   int XAxisSpacing               = CL.GetInt("XAxis", 505);
   int YAxisSpacing               = CL.GetInt("YAxis", 505);

   bool DoMOD                     = CL.GetBool("DoMOD", true);
   double CanvasScale             = DoMOD ? CL.GetDouble("CanvasScale", 1) : 1;

   Assert(DoRowNormalize == false || DoColumnNormalize == false, "Conflicting normalization options!");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Unfolding plots");

   TFile InputFile(InputFileName.c_str());

   vector<double> GenBins1
      = DetectBins((TH1D *)InputFile.Get("HGenPrimaryBinMin"), (TH1D *)InputFile.Get("HGenPrimaryBinMax"));
   vector<double> GenBins2
      = DetectBins((TH1D *)InputFile.Get("HGenBinningBinMin"), (TH1D *)InputFile.Get("HGenBinningBinMax"));
   GenBins1[0] = GenPrimaryMinOverwrite;
   GenBins1[GenBins1.size()-1] = GenPrimaryMaxOverwrite;
   
   vector<double> MatchedBins1
      = DetectBins((TH1D *)InputFile.Get("HMatchedPrimaryBinMin"), (TH1D *)InputFile.Get("HMatchedPrimaryBinMax"));
   vector<double> MatchedBins2
      = DetectBins((TH1D *)InputFile.Get("HMatchedBinningBinMin"), (TH1D *)InputFile.Get("HMatchedBinningBinMax"));
   MatchedBins1[0] = RecoPrimaryMinOverwrite;
   MatchedBins1[MatchedBins1.size()-1] = RecoPrimaryMaxOverwrite;

   double WorldXMin = CL.GetDouble("WorldXMin", MatchedBins1[0]);
   double WorldXMax = CL.GetDouble("WorldXMax", MatchedBins1[MatchedBins1.size()-1]);
   double WorldYMin = CL.GetDouble("WorldYMin", GenBins1[0]);
   double WorldYMax = CL.GetDouble("WorldYMax", GenBins1[GenBins1.size()-1]);
   double WorldZMin = CL.GetDouble("WorldZMin", (LogZ ? 0.001 : 0.000));
   double WorldZMax = CL.GetDouble("WorldZMax", 1.000);
   bool UseActualZMax = CL.GetBool("UseActualZMax", false);

   sort(GroupX.begin(), GroupX.end());
   sort(GroupY.begin(), GroupY.end());
   GroupX.erase(unique(GroupX.begin(), GroupX.end()), GroupX.end());
   GroupY.erase(unique(GroupY.begin(), GroupY.end()), GroupY.end());

   for(int i = 0; i < (int)GroupX.size(); i++)
   {
      if(GroupX[i] >= (int)MatchedBins2.size() - 1)
      {
         GroupX.erase(GroupX.begin() + i);
         i = i - 1;
      }
   }
   for(int i = 0; i < (int)GroupY.size(); i++)
   {
      if(GroupY[i] >= (int)GenBins2.size() - 1)
      {
         GroupY.erase(GroupY.begin() + i);
         i = i - 1;
      }
   }

   if(GroupX.size() == 0)
      for(int i = 0; i < (int)MatchedBins2.size() - 1; i++)
         GroupX.push_back(i);
   if(GroupY.size() == 0)
      for(int i = 0; i < (int)GenBins2.size() - 1; i++)
         GroupY.push_back(i);
   
   int Column            = MatchedBins2.size() - 1;
   int Row               = GenBins2.size() - 1;
   int VisibleColumn     = GroupX.size();
   int VisibleRow        = GroupY.size();

   TH2D *HMaster = (TH2D *)InputFile.Get(InputResponseName.c_str());
   Assert(HMaster != nullptr, "Response not found!");

   if(DoRowNormalize == true)
      RowNormalize(HMaster);
   if(DoColumnNormalize == true)
      ColumnNormalize(HMaster);

   vector<vector<TH2D *>> H2(Row);
   for(int R = 0; R < Row; R++)
   {
      H2[R].resize(Column, nullptr);
      for(int C = 0; C < Column; C++)
         H2[R][C] = Transcribe(HMaster, R, C, MatchedBins1, GenBins1, DoRowNormalize, DoColumnNormalize);
   }

   double ActualMaximum = 0;
   for(int R = 0; R < Row; R++)
   {
      for(int C = 0; C < Column; C++)
      {
         if(H2[R][C] == nullptr)
            continue;
         ActualMaximum = max(ActualMaximum, H2[R][C]->GetMaximum());
      }
   }
   if(UseActualZMax == true)
      WorldZMax = ActualMaximum;

   int PadWidth     = CanvasScale * 250;
   int PadHeight    = CanvasScale * 250;
   int MarginLeft   = CanvasScale * (50 + (VisibleColumn - 1) * 20);
   int MarginRight  = CanvasScale * (50 + (VisibleColumn - 1) * 10);
   int MarginTop    = CanvasScale * (25 + (VisibleColumn - 1) * 10);
   int MarginBottom = CanvasScale * (50 + (VisibleColumn - 1) * 20);
   int ColorGap     = CanvasScale * ( 5 + (VisibleColumn - 1) * 1.5);
   int ColorWidth   = CanvasScale * (10 + (VisibleColumn - 1) * 2);

   double CanvasWidth = MarginLeft + PadWidth * VisibleColumn + MarginRight;
   double CanvasHeight = MarginBottom + PadHeight * VisibleRow + MarginTop;

   double PadDX = PadWidth / CanvasWidth;
   double PadDY = PadHeight / CanvasHeight;
   double PadX0 = MarginLeft / CanvasWidth;
   double PadY0 = MarginBottom / CanvasHeight;
   double PadCG = ColorGap / CanvasWidth;
   double PadDC = ColorWidth / CanvasWidth;

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   double TextSize = 0.035 - max(VisibleColumn, VisibleRow) * 0.0015;
   // double TextSize = 0.0386 - max(VisibleColumn, VisibleRow) * 0.0018;

   // Setup pads
   vector<vector<TPad *>> Pads(VisibleRow);
   for(int R = 0; R < VisibleRow; R++)
   {
      int IndexR = R;
      Pads[IndexR].resize(VisibleColumn, nullptr);

      for(int C = 0; C < VisibleColumn; C++)
      {
         int IndexC = C;

         double XMin = PadX0 + PadDX * IndexC;
         double XMax = PadX0 + PadDX * (IndexC + 1);
         double YMin = PadY0 + PadDY * IndexR;
         double YMax = PadY0 + PadDY * (IndexR + 1);

         Pads[IndexR][IndexC] = new TPad(Form("P%d%d", R, C), "", XMin, YMin, XMax, YMax);

         if(LogZ == true)
            Pads[IndexR][IndexC]->SetLogz();
      }
   }

   for(vector<TPad *> V : Pads)
      for(TPad *P : V)
         SetPad(P);

   // Setup axes
   vector<TGaxis *> XAxis, YAxis;
   for(int i = 0; i < VisibleColumn; i++)
   {
      XAxis.emplace_back(new TGaxis(PadX0 + PadDX * i, PadY0, PadX0 + PadDX * (i + 1), PadY0,
         WorldXMin, WorldXMax, XAxisSpacing, ""));
      SetAxis(*XAxis[i]);
      XAxis[i]->SetLabelSize(TextSize);
   }
   for(int i = 0; i < VisibleRow; i++)
   {
      double YMin = PadY0 + PadDY * i;
      double YMax = YMin + PadDY;
      YAxis.emplace_back(new TGaxis(PadX0, YMin, PadX0, YMax,
         WorldYMin, WorldYMax, YAxisSpacing, ""));
      SetAxis(*YAxis[i]);
      YAxis[i]->SetLabelSize(TextSize);
   }

   // Setup axis labels
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(TextSize);
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(22);
   Latex.SetNDC();
   if(VisibleColumn == 1)
      Latex.DrawLatex(PadX0 + PadDX * 0.5, PadY0 * 0.5, ("Reco " + PrimaryLabel).c_str());
   else
   {
      for(int i = 0; i < VisibleColumn; i++)
      {
         string Label = "Reco " + PrimaryLabel;
         Latex.DrawLatex(PadX0 + PadDX * (i + 0.5), PadY0 * 0.5, Label.c_str());
         Label = "[";
         if(MatchedBins2[GroupX[i]] > -999)
            Label = Label + Form("%.1f", MatchedBins2[GroupX[i]]);
         Label = Label + " < ";
         if(MatchedBins2[GroupX[i]+1] < 999)
            Label = Label + Form("%.1f", MatchedBins2[GroupX[i]+1]);
         Label = Label + "]";
         Latex.DrawLatex(PadX0 + PadDX * (i + 0.5), PadY0 * 0.2, Label.c_str());
      }
   }
   Latex.SetTextAngle(90);
   Latex.SetTextAlign(22);
   if(VisibleRow == 1)
      Latex.DrawLatex(PadX0 * 0.5, PadY0 + PadDY * 0.5, ("Gen " + PrimaryLabel).c_str());
   else
   {
      for(int i = 0; i < VisibleRow; i++)
      {
         string Label = "Gen " + PrimaryLabel;
         Latex.DrawLatex(PadX0 * 0.2, PadY0 + PadDY * (i + 0.5), Label.c_str());
         Label = "[";
         if(GenBins2[GroupY[i]] > -999)
            Label = Label + Form("%.1f", GenBins2[GroupY[i]]);
         Label = Label + " < ";
         if(GenBins2[GroupY[i]+1] < 999)
            Label = Label + Form("%.1f", GenBins2[GroupY[i]+1]);
         Label = Label + "]";
         Latex.DrawLatex(PadX0 * 0.5, PadY0 + PadDY * (i + 0.5), Label.c_str());
      }
   }

   if(VisibleRow > 1 || VisibleColumn > 1)
   {
      Latex.SetTextAngle(45);
      Latex.DrawLatex(PadX0 * 0.41, PadY0 * 0.59, PrimaryLabel.c_str());
      Latex.DrawLatex(PadX0 * 0.59, PadY0 * 0.41, ("[" + BinningLabel + "]").c_str());
   }

   // Setup general information
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(11);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * Row + 0.01, "ALEPH Archived MC 1994, e^{+}e^{-} #sqrt{s} = 91.2 GeV");

   // Setup worlds
   vector<vector<TH2D *>> HWorld(VisibleRow);
   for(int R = 0; R < VisibleRow; R++)
   {
      int IndexR = R;
      HWorld[IndexR].resize(VisibleColumn, nullptr);
      for(int C = 0; C < VisibleColumn; C++)
      {
         int IndexC = C;

         HWorld[IndexR][IndexC]
            = new TH2D(Form("HWorld%d%d", R, C), ";;", 100, WorldXMin, WorldXMax, 100, WorldYMin, WorldYMax);

         HWorld[IndexR][IndexC]->SetNdivisions(XAxisSpacing, "X");
         HWorld[IndexR][IndexC]->SetNdivisions(YAxisSpacing, "Y");

         SetWorld(HWorld[IndexR][IndexC]);

         HWorld[IndexR][IndexC]->SetMinimum(WorldZMin);
         HWorld[IndexR][IndexC]->SetMaximum(WorldZMax);
      }
   }

   cout << "World done" << endl;

   // Plot the actual histograms
   TH2D *SomeH2 = nullptr;
   for(int R = 0; R < VisibleRow; R++)
   {
      for(int C = 0; C < VisibleColumn; C++)
      {
         int IndexR = GroupY[R];
         int IndexC = GroupX[C];

         Pads[R][C]->cd();

         HWorld[R][C]->Draw("axis");
         H2[IndexR][IndexC]->Draw("col same");
         HWorld[R][C]->Draw("axis same");

         if(SomeH2 == nullptr)
         {
            SomeH2 = H2[IndexR][IndexC];

            SomeH2->SetMinimum(WorldZMin);
            SomeH2->SetMaximum(WorldZMax);
            SomeH2->GetZaxis()->SetLabelSize(0.035 - max(Row, Column) * 0.00125);
            SomeH2->GetZaxis()->SetTickLength(PadDC);
            SomeH2->GetZaxis()->SetLabelOffset(0);
         }
      }
   }

   Canvas.cd();

   SomeH2->GetZaxis()->SetLabelSize(TextSize);
   TPaletteAxis ColorBar(PadX0 + PadDX * VisibleColumn + PadCG, PadY0,
      PadX0 + PadDX * VisibleColumn + PadCG + PadDC, PadY0 + PadDY * VisibleRow,
      SomeH2);
   ColorBar.SetLabelSize(TextSize);
   ColorBar.Draw();

   if(LogZ == true)
      Canvas.SetLogz();

   double LogoX = CL.GetDouble("LogoX", 0.90);
   double LogoY = CL.GetDouble("LogoY", 0.90);
   double LogoW = CL.GetDouble("LogoW", 0.05);
   double LogoH = LogoW * CanvasWidth / CanvasHeight * 0.4;

   Canvas.cd();
   TPad PadLogo("PadLogo", "", LogoX - LogoW / 2, LogoY - LogoH / 2, LogoX + LogoW / 2, LogoY + LogoH / 2);
   PadLogo.SetLeftMargin(0);
   PadLogo.SetTopMargin(0);
   PadLogo.SetRightMargin(0);
   PadLogo.SetBottomMargin(0);
   TImage *Logo = nullptr;
   if(DoMOD == true)
   {
      PadLogo.Draw();
      PadLogo.cd();
      Logo = (TImage *)TImage::Open("MOD.eps");
      // Logo->SetJpegDpi("MOD.jpg", 300);
      if(DoMOD == true)
         Logo->Draw("xxxz");
   }

   Canvas.SaveAs(FinalOutputFileName.c_str());

   for(vector<TH2D *> &V : HWorld)
      for(TH2D *H : V)
         if(H != nullptr)
            delete H;

   for(TGaxis *A : XAxis)   delete A;
   for(TGaxis *A : YAxis)   delete A;

   for(vector<TPad *> &V : Pads)
      for(TPad *P : V)
         if(P != nullptr)
            delete P;
   for(vector<TH2D *> &V : H2)
      for(TH2D *H : V)
         if(H != nullptr)
            delete H;

   InputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<double> DetectBins(TH1D *HMin, TH1D *HMax)
{
   if(HMin == nullptr || HMax == nullptr)
      return vector<double>{};

   vector<pair<double, double>> Bins;

   for(int i = 1; i <= HMin->GetNbinsX(); i++)
      Bins.push_back(pair<double, double>(HMin->GetBinContent(i), HMax->GetBinContent(i)));

   sort(Bins.begin(), Bins.end());
   auto iterator = unique(Bins.begin(), Bins.end());
   Bins.erase(iterator, Bins.end());

   vector<double> Result;
   for(auto iterator : Bins)
   {
      Result.push_back(iterator.first);
      Result.push_back(iterator.second);
   }
   
   sort(Result.begin(), Result.end());
   auto iterator2 = unique(Result.begin(), Result.end());
   Result.erase(iterator2, Result.end());

   return Result;
}

void SelfNormalize(TH1D *H, vector<double> Bins1, vector<double> Bins2)
{
   if(H == nullptr)
      return;
   
   int BinningCount = Bins2.size() - 1;
   if(BinningCount <= 0)
      BinningCount = 1;

   for(int iB = 0; iB < BinningCount; iB++)
   {
      int BinCount = Bins1.size() - 1;
      if(BinCount <= 0)
         BinCount = 1;

      double Total = 0;
      for(int i = 0; i < BinCount; i++)
         Total = Total + H->GetBinContent(i + 1 + iB * BinCount);
     
      if(Total > 0)
      {
         for(int i = 0; i < BinCount; i++)
         {
            H->SetBinContent(i + 1 + iB * BinCount, H->GetBinContent(i + 1 + iB * BinCount) / Total);
            H->SetBinError(i + 1 + iB * BinCount, H->GetBinError(i + 1 + iB * BinCount) / Total);
         }
      }
   }
}

TH1D *BuildSystematics(TH1D *HBase, TH1D *HVariation)
{
   if(HBase == nullptr)
      return nullptr;

   TH1D *HSystematics = (TH1D *)HBase->Clone();

   if(HVariation == nullptr)
      return HSystematics;

   HSystematics->Reset();
   for(int i = 1; i <= HBase->GetNbinsX(); i++)
   {
      double V = HBase->GetBinContent(i);
      double R = HVariation->GetBinContent(i);
      HSystematics->SetBinContent(i, fabs(R / V - 1));
   }

   return HSystematics;
}

TH2D *Transcribe(TH2D *HMaster, int R, int C, vector<double> &XBinning, vector<double> &YBinning, bool DoRowNormalize, bool DoColumnNormalize)
{
   if(HMaster == nullptr)
      return nullptr;

   double XBins[MAX], YBins[MAX];
   for(int i = 0; i < XBinning.size(); i++)
      XBins[i] = XBinning[i];
   for(int i = 0; i < YBinning.size(); i++)
      YBins[i] = YBinning[i];

   int NX = XBinning.size() - 1;
   int NY = YBinning.size() - 1;

   TH2D *HResult = new TH2D(Form("H%d%d", R, C), ";;", NX, XBins, NY, YBins);

   for(int iX = 1; iX <= NX; iX++)
   {
      for(int iY = 1; iY <= NY; iY++)
      {
         double V = HMaster->GetBinContent(NX * C + iX, NY * R + iY);

         if(DoColumnNormalize == false)
            V = V / (XBins[iX] - XBins[iX-1]);
         if(DoRowNormalize == false)
            V = V / (YBins[iY] - YBins[iY-1]);

         HResult->SetBinContent(iX, iY, V);
      }
   }

   HResult->SetStats(0);

   return HResult;
}

void RowNormalize(TH2D *H)
{
   if(H == nullptr)
      return;

   for(int iY = 1; iY <= H->GetNbinsY(); iY++)
   {
      double Total = 0;
      for(int iX = 1; iX <= H->GetNbinsX(); iX++)
         Total = Total + H->GetBinContent(iX, iY);
      if(Total > 0)
         for(int iX = 1; iX <= H->GetNbinsX(); iX++)
            H->SetBinContent(iX, iY, H->GetBinContent(iX, iY) / Total);
   }
}

void ColumnNormalize(TH2D *H)
{
   if(H == nullptr)
      return;

   for(int iX = 1; iX <= H->GetNbinsX(); iX++)
   {
      double Total = 0;
      for(int iY = 1; iY <= H->GetNbinsY(); iY++)
         Total = Total + H->GetBinContent(iX, iY);
      if(Total > 0)
         for(int iY = 1; iY <= H->GetNbinsY(); iY++)
            H->SetBinContent(iX, iY, H->GetBinContent(iX, iY) / Total);
   }
}

void SetPad(TPad *P)
{
   if(P == nullptr)
      return;
   P->SetLeftMargin(0);
   P->SetTopMargin(0);
   P->SetRightMargin(0);
   P->SetBottomMargin(0);
   P->SetTickx();
   P->SetTicky();
   P->Draw();
}

void SetAxis(TGaxis &A)
{
   A.SetLabelFont(42);
   A.SetLabelSize(0.030);
   A.SetMaxDigits(6);
   A.SetMoreLogLabels();
   // A.SetNoExponent();
   A.Draw();
}

void SetWorld(TH2D *H)
{
   if(H == nullptr)
      return;
   H->SetStats(0);
}

TGraphAsymmErrors CalculateRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2)
{
   TGraphAsymmErrors G;

   int N = G2.GetN();
   for(int i = 0; i < N; i++)
   {
      double X1, X2, Y1, Y2, E1YH, E1YL, E1XH, E1XL;

      G1.GetPoint(i, X1, Y1);
      E1YH = G1.GetErrorYhigh(i);
      E1YL = G1.GetErrorYlow(i);
      E1XH = G1.GetErrorXhigh(i);
      E1XL = G1.GetErrorXlow(i);
      G2.GetPoint(i, X2, Y2);

      if(Y2 == 0)
         continue;

      G.SetPoint(i, X1, Y1 / Y2);
      G.SetPointError(i, E1XL, E1XH, E1YL / Y2, E1YH / Y2);
   }

   return G;
}

double CalculateIntegral(TGraphAsymmErrors &G, double MinX)
{
   double Total = 0;

   int N = G.GetN();
   for(int i = 0; i < N; i++)
   {
      double EX1, EX2, X, Y;

      G.GetPoint(i, X, Y);
      EX1 = G.GetErrorXlow(i);
      EX2 = G.GetErrorXhigh(i);

      if(X < MinX)
         continue;

      Total = Total + Y * (EX1 + EX2);
   }

   return Total;
}

