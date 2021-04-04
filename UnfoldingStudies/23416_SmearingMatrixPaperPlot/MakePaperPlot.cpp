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

   int XAxisSpacing               = CL.GetInt("XAxis", 505);
   int YAxisSpacing               = CL.GetInt("YAxis", 505);

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

   int IgnoreGroupColumn = CL.GetInt("IgnoreGroupColumn", 0);
   int IgnoreGroupRow    = CL.GetInt("IgnoreGroupRow", 0);
   int Column            = MatchedBins2.size() - 1;
   int Row               = GenBins2.size() - 1;

   if(Column == 1 && Row == 1)
   {
      IgnoreGroupColumn = 0;
      IgnoreGroupRow = 0;
   }

   Assert(IgnoreGroupColumn == 0 && IgnoreGroupRow == 0, "Ignore group not implemented yet!");

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

   int PadWidth     = 250;
   int PadHeight    = 250;
   int MarginLeft   = 50 + (Column - 1) * 15;
   int MarginRight  = 50 + (Column - 1) * 10;
   int MarginTop    = 25 + (Column - 1) * 10;
   int MarginBottom = 50 + (Column - 1) * 15;
   int ColorGap     = 5 + (Column - 1) * 1.5;
   int ColorWidth   = 10 + (Column - 1) * 2;

   double CanvasWidth = MarginLeft + PadWidth * Column + MarginRight;
   double CanvasHeight = MarginBottom + PadHeight * Row + MarginTop;

   double PadDX = PadWidth / CanvasWidth;
   double PadDY = PadHeight / CanvasHeight;
   double PadX0 = MarginLeft / CanvasWidth;
   double PadY0 = MarginBottom / CanvasHeight;
   double PadCG = ColorGap / CanvasWidth;
   double PadDC = ColorWidth / CanvasWidth;

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   // Setup pads
   vector<vector<TPad *>> Pads(Row - IgnoreGroupRow);
   for(int R = IgnoreGroupRow; R < Row; R++)
   {
      int IndexR = R - IgnoreGroupRow;
      Pads[IndexR].resize(Column - IgnoreGroupColumn, nullptr);

      for(int C = IgnoreGroupColumn; C < Column; C++)
      {
         int IndexC = C - IgnoreGroupColumn;

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
   for(int i = 0; i < Column; i++)
   {
      XAxis.emplace_back(new TGaxis(PadX0 + PadDX * i, PadY0, PadX0 + PadDX * (i + 1), PadY0,
         WorldXMin, WorldXMax, XAxisSpacing, ""));
      SetAxis(*XAxis[i]);
      XAxis[i]->SetLabelSize(0.035 - max(Row, Column) * 0.0015);
   }
   for(int i = 0; i < Row; i++)
   {
      double YMin = PadY0 + PadDY * i;
      double YMax = YMin + PadDY;
      YAxis.emplace_back(new TGaxis(PadX0, YMin, PadX0, YMax,
         WorldYMin, WorldYMax, YAxisSpacing, ""));
      SetAxis(*YAxis[i]);
      YAxis[i]->SetLabelSize(0.035 - max(Row, Column) * 0.0015);
   }

   // Setup axis labels
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035 - max(Column, Row) * 0.0015);
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(22);
   Latex.SetNDC();
   if(Column == 1)
      Latex.DrawLatex(PadX0 + PadDX * 0.5, PadY0 * 0.5, ("Reco " + PrimaryLabel).c_str());
   else
   {
      for(int i = 0; i < Column; i++)
      {
         string Label = "Reco " + PrimaryLabel;
         Latex.DrawLatex(PadX0 + PadDX * (i + 0.5), PadY0 * 0.5, Label.c_str());
         Label = "[";
         if(MatchedBins2[i] > -999)
            Label = Label + Form("%.1f", MatchedBins2[i]);
         Label = Label + " < ";
         if(MatchedBins2[i+1] < 999)
            Label = Label + Form("%.1f", MatchedBins2[i+1]);
         Label = Label + "]";
         Latex.DrawLatex(PadX0 + PadDX * (i + 0.5), PadY0 * 0.25, Label.c_str());
      }
   }
   Latex.SetTextAngle(90);
   Latex.SetTextAlign(22);
   if(Row == 1)
      Latex.DrawLatex(PadX0 * 0.5, PadY0 + PadDY * 0.5, ("Gen " + PrimaryLabel).c_str());
   else
   {
      for(int i = 0; i < Row; i++)
      {
         string Label = "Gen " + PrimaryLabel;
         Latex.DrawLatex(PadX0 * 0.25, PadY0 + PadDY * (i + 0.5), Label.c_str());
         Label = "[";
         if(GenBins2[i] > -999)
            Label = Label + Form("%.1f", GenBins2[i]);
         Label = Label + " < ";
         if(GenBins2[i+1] < 999)
            Label = Label + Form("%.1f", GenBins2[i+1]);
         Label = Label + "]";
         Latex.DrawLatex(PadX0 * 0.5, PadY0 + PadDY * (i + 0.5), Label.c_str());
      }
   }

   if(Row > 1 || Column > 1)
   {
      Latex.SetTextAngle(45);
      Latex.DrawLatex(PadX0 * 0.43, PadY0 * 0.57, PrimaryLabel.c_str());
      Latex.DrawLatex(PadX0 * 0.57, PadY0 * 0.43, ("[" + BinningLabel + "]").c_str());
   }

   // Setup general information
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(11);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * Row + 0.01, "ALEPH Archived MC 1994, e^{+}e^{-} #sqrt{s} = 91.2 GeV");

   // Setup worlds
   vector<vector<TH2D *>> HWorld(Row - IgnoreGroupRow);
   for(int R = IgnoreGroupRow; R < Row; R++)
   {
      int IndexR = R - IgnoreGroupRow;
      HWorld[IndexR].resize(Column - IgnoreGroupColumn, nullptr);
      for(int C = IgnoreGroupColumn; C < Column; C++)
      {
         int IndexC = C - IgnoreGroupColumn;

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
   for(int R = IgnoreGroupRow; R < Row; R++)
   {
      for(int C = IgnoreGroupColumn; C < Column; C++)
      {
         int IndexR = R - IgnoreGroupRow;
         int IndexC = C - IgnoreGroupColumn;

         Pads[IndexR][IndexC]->cd();

         HWorld[IndexR][IndexC]->Draw("axis");
         H2[R][C]->Draw("col same");
         HWorld[IndexR][IndexC]->Draw("axis same");

         if(SomeH2 == nullptr)
         {
            SomeH2 = H2[R][C];

            SomeH2->SetMinimum(WorldZMin);
            SomeH2->SetMaximum(WorldZMax);
            SomeH2->GetZaxis()->SetLabelSize(0.035 - max(Row, Column) * 0.00125);
            SomeH2->GetZaxis()->SetTickLength(PadDC);
            SomeH2->GetZaxis()->SetLabelOffset(0);
         }
      }
   }

   Canvas.cd();

   TPaletteAxis ColorBar(PadX0 + PadDX * Column + PadCG, PadY0,
      PadX0 + PadDX * Column + PadCG + PadDC, PadY0 + PadDY * Row,
      SomeH2);
   ColorBar.Draw();

   if(LogZ == true)
      Canvas.SetLogz();

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
      
      for(int i = 0; i < BinCount; i++)
      {
         H->SetBinContent(i + 1 + iB * BinCount, H->GetBinContent(i + 1 + iB * BinCount) / Total);
         H->SetBinError(i + 1 + iB * BinCount, H->GetBinError(i + 1 + iB * BinCount) / Total);
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

