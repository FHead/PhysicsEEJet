#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void FormatH1(TH1D *H);
void FormatH2(TH2D *H);
void MinMax(TH1D *H, int IgnoreBin = 0);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
void NonHumanPlots(PdfFileHelper &PdfFile,
   map<string, TH1D *> &H, vector<string> Names, vector<string> Labels, vector<int> Colors,
   string Title = "", string XTitle = "", string YTitle = "");
void HumanPlots(PdfFileHelper &PdfFile,
   map<string, TH1D *> &H, vector<string> Names, vector<string> Labels, vector<int> Colors,
   vector<double> Bins1, vector<double> Bins2,
   string BinningObservable = "", string Title = "", string XTitle = "", string YTitle = "");

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string InputFileName    = CL.Get("Input");
   string OriginalFileName = CL.Get("Original");
   string OutputFileName   = CL.Get("Output");
   double GenPrimaryMinOverwrite = CL.GetDouble("GenPrimaryMin", -999);
   double GenPrimaryMaxOverwrite = CL.GetDouble("GenPrimaryMax", 999);
   double RecoPrimaryMinOverwrite = CL.GetDouble("RecoPrimaryMin", -999);
   double RecoPrimaryMaxOverwrite = CL.GetDouble("RecoPrimaryMax", 999);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Unfolding plots");

   TFile InputFile(InputFileName.c_str());
   TFile OriginalFile(OriginalFileName.c_str());

   vector<string> H1Names{"HMCMeasured", "HMCTruth", "HInput", "HUnfoldedBayes1", "HUnfoldedBayes2",
      "HUnfoldedBayes3", "HUnfoldedBayes4", "HUnfoldedBayes6", "HUnfoldedBayes10", "HUnfoldedBayes20",
      "HUnfoldedBayes30", "HUnfoldedBayes50", "HUnfoldedBayes100", "HUnfoldedBayes200", "HUnfoldedSVD",
      "HUnfoldedInvert"};
   vector<string> H2Names{"HMCResponse"};

   map<string, TH1D *> H1;
   map<string, TH2D *> H2;

   for(string Name : H1Names)
   {
      H1[Name] = (TH1D *)InputFile.Get(Name.c_str());
      FormatH1(H1[Name]);
   }
   for(string Name : H2Names)
   {
      H2[Name] = (TH2D *)InputFile.Get(Name.c_str());
      FormatH2(H2[Name]);
   }

   TFile &FO = OriginalFile;
   vector<double> GenBins1
      = DetectBins((TH1D *)FO.Get("HGenPrimaryBinMin"), (TH1D *)FO.Get("HGenPrimaryBinMax"));
   vector<double> GenBins2
      = DetectBins((TH1D *)FO.Get("HGenBinningBinMin"), (TH1D *)FO.Get("HGenBinningBinMax"));
   vector<double> RecoBins1
      = DetectBins((TH1D *)FO.Get("HRecoPrimaryBinMin"), (TH1D *)FO.Get("HRecoPrimaryBinMax"));
   vector<double> RecoBins2
      = DetectBins((TH1D *)FO.Get("HRecoBinningBinMin"), (TH1D *)FO.Get("HRecoBinningBinMax"));
   vector<double> MatchedBins1
      = DetectBins((TH1D *)FO.Get("HMatchedPrimaryBinMin"), (TH1D *)FO.Get("HMatchedPrimaryBinMax"));
   vector<double> MatchedBins2
      = DetectBins((TH1D *)FO.Get("HMatchedBinningBinMin"), (TH1D *)FO.Get("HMatchedBinningBinMax"));

   GenBins1[0] = GenPrimaryMinOverwrite;
   GenBins1[GenBins1.size()-1] = GenPrimaryMaxOverwrite;
   RecoBins1[0] = RecoPrimaryMinOverwrite;
   RecoBins1[RecoBins1.size()-1] = RecoPrimaryMaxOverwrite;
   MatchedBins1[0] = RecoPrimaryMinOverwrite;
   MatchedBins1[MatchedBins1.size()-1] = RecoPrimaryMaxOverwrite;

   TCanvas Canvas;
   Canvas.SetGridx();
   Canvas.SetGridy();

   double ScalingFactor = H1["HInput"]->Integral() / H1["HMCMeasured"]->Integral();
   cout << "Scaling factor = " << ScalingFactor << endl;
   H1["HMCMeasured"]->Scale(ScalingFactor);
   H1["HMCTruth"]->Scale(ScalingFactor);

   H2["HMCResponse"]->SetTitle("Response matrix");
   H2["HMCResponse"]->GetXaxis()->SetTitle("Reco Bin Index");
   H2["HMCResponse"]->GetYaxis()->SetTitle("Gen Bin Index");
   PdfFile.AddPlot(H2["HMCResponse"], "colz");
   PdfFile.AddPlot(H2["HMCResponse"], "colz", false, true);

   NonHumanPlots(PdfFile, H1,
      {"HMCMeasured", "HInput"},
      {"MC (reco)", "Input (reco)"},
      Colors,
      "Input distributions", "Reco bin index", "a.u.");
   
   HumanPlots(PdfFile, H1,
      {"HMCMeasured", "HInput"},
      {"MC (reco)", "Input (reco)"},
      Colors,
      RecoBins1, RecoBins2,
      "Reco Jet P", "Input distributions", "Reco", "a.u.");

   NonHumanPlots(PdfFile, H1,
      {"HMCTruth", "HUnfoldedBayes100", "HUnfoldedSVD", "HUnfoldedInvert"},
      {"MC truth", "Unfolded (B-100)", "Unfolded (SVD)", "Unfolded (Invert)"},
      Colors,
      "Unfolded distribution", "Gen bin index", "a.u.");
   
   NonHumanPlots(PdfFile, H1,
      {"HMCTruth", "HUnfoldedBayes100", "HUnfoldedBayes10", "HUnfoldedSVD"},
      {"MC truth", "Unfolded (B-100)", "Unfolded (B-10)", "Unfolded (SVD)"},
      Colors,
      "Unfolded distribution", "Gen bin index", "a.u.");
   
   HumanPlots(PdfFile, H1,
      {"HMCTruth", "HUnfoldedBayes100", "HUnfoldedSVD", "HUnfoldedInvert"},
      {"MC truth", "Unfolded (B-100)", "Unfolded (SVD)", "Unfolded (Invert)"},
      Colors,
      GenBins1, GenBins2,
      "Gen Jet P", "Unfolded distributions", "Gen", "a.u.");

   HumanPlots(PdfFile, H1,
      {"HMCTruth", "HUnfoldedBayes100", "HUnfoldedBayes10", "HUnfoldedSVD"},
      {"MC truth", "Unfolded (B-100)", "Unfolded (B-10)", "Unfolded (SVD)"},
      Colors,
      GenBins1, GenBins2,
      "Gen Jet P", "Unfolded distributions", "Gen", "a.u.");

   TH1D *HRatioBayes2 = (TH1D *)H1["HUnfoldedBayes2"]->Clone("HRatioBayes2");
   HRatioBayes2->Divide(H1["HMCTruth"]);
   HRatioBayes2->Draw();
   HRatioBayes2->SetTitle("");
   HRatioBayes2->GetYaxis()->SetTitle("Unfolded (B-2) / MCTruth");
   MinMax(HRatioBayes2, 1);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HRatioBayes2->SetMinimum(0.95);
   HRatioBayes2->SetMaximum(1.05);
   HRatioBayes2->Draw();
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   NonHumanPlots(PdfFile, H1,
      {"HUnfoldedBayes1", "HUnfoldedBayes2", "HUnfoldedBayes4", "HUnfoldedBayes10", "HUnfoldedBayes100"},
      {"Unfolded (B-1)", "Unfolded (B-2)", "Unfolded (B-4)", "Unfolded (B-10)", "Unfolded (B-100)"},
      Colors,
      "Iteration comparison", "Gen bin index", "a.u.");
   
   OriginalFile.Close();
   InputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void FormatH1(TH1D *H)
{
   if(H == nullptr)
      return;

   H->SetMarkerStyle(20);
   H->SetLineWidth(2);
   H->SetStats(0);
}

void FormatH2(TH2D *H)
{
   if(H == nullptr)
      return;

   H->Fill(0.0, 0.0, 0.0);
   H->SetStats(0);
}

void MinMax(TH1D *H, int IgnoreBin)
{
   double Min = 999;
   double Max = -999;

   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      if(i <= IgnoreBin)
         continue;
      double X = H->GetBinContent(i);
      double E = H->GetBinError(i);
      if(X == 0 && E == 0)
         continue;
      if(Min > X - E)   Min = X - E;
      if(Max < X + E)   Max = X + E;
   }

   double D = Max - Min;
   Min = Min - D * 0.1;
   Max = Max + D * 0.1;

   H->SetMinimum(Min);
   H->SetMaximum(Max);
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

void NonHumanPlots(PdfFileHelper &PdfFile,
   map<string, TH1D *> &H, vector<string> Names, vector<string> Labels, vector<int> Colors,
   string Title, string XTitle, string YTitle)
{
   int N = Names.size();
   
   TLegend Legend(0.30, 0.85, 0.65, 0.85 - N * 0.05);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   // Legend.SetBorderSize(1);

   bool First = true;

   TCanvas Canvas;

   for(int i = 0; i < N; i++)
   {
      if(H[Names[i]] == nullptr)
         continue;

      H[Names[i]]->SetLineWidth(2);
      H[Names[i]]->SetLineColor(Colors[i]);
      H[Names[i]]->SetMarkerColor(Colors[i]);

      H[Names[i]]->SetTitle(Title.c_str());
      H[Names[i]]->GetXaxis()->SetTitle(XTitle.c_str());
      H[Names[i]]->GetYaxis()->SetTitle(YTitle.c_str());

      Legend.AddEntry(H[Names[i]], Labels[i].c_str(), "pl");

      if(First == true)
         H[Names[i]]->Draw();
      else
         H[Names[i]]->Draw("same");

      First = false;
   }

   Legend.Draw();

   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
}

void HumanPlots(PdfFileHelper &PdfFile,
   map<string, TH1D *> &H, vector<string> Names, vector<string> Labels, vector<int> Colors,
   vector<double> Bins1, vector<double> Bins2,
   string BinningObservable, string Title, string XTitle, string YTitle)
{
   static int Index = 0;
   Index = Index + 1;

   int N = Names.size();
   
   TLegend Legend(0.45, 0.85, 0.80, 0.85 - N * 0.05);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   // Legend.SetBorderSize(1);
   Legend.SetFillStyle(0);
   
   int BinningCount = Bins2.size() - 1;
   if(BinningCount <= 0)
      BinningCount = 1;

   for(int iB = 0; iB < BinningCount; iB++)
   {
      string BinLabel = "";
      if(BinningCount == 1)
         BinLabel = "";
      else
      {
         if(Bins2[iB] > -999)
            BinLabel = BinLabel + Form("%.1f < ", Bins2[iB]);
         BinLabel = BinLabel + BinningObservable;
         if(Bins2[iB+1] < 999)
            BinLabel = BinLabel + Form(" < %.1f", Bins2[iB+1]);
      }

      int PrimaryBinCount = Bins1.size() - 1;
      double PrimaryBins[1000] = {0};
      for(int i = 0; i <= PrimaryBinCount; i++)
         PrimaryBins[i] = Bins1[i];
      double Delta = PrimaryBins[PrimaryBinCount-1] - PrimaryBins[1];

      if(PrimaryBins[0] < -998)
         PrimaryBins[0] = PrimaryBins[1] - Delta * 0.05;
      if(PrimaryBins[PrimaryBinCount] > 998)
         PrimaryBins[PrimaryBinCount] = PrimaryBins[PrimaryBinCount-1] + Delta * 0.05;
      if(PrimaryBins[0] < 0 && PrimaryBins[1] > 0)
         PrimaryBins[0] = 0;

      // for(int i = 0; i <= PrimaryBinCount; i++)
      //    cout << i << " " << PrimaryBins[i] << endl;

      bool First = true;
      TCanvas Canvas;

      vector<TH1D *> HHuman;
      for(int i = 0; i < N; i++)
      {
         HHuman.emplace_back(new TH1D(Form("H_%d_%d_%d", Index, iB, i), "", PrimaryBinCount, PrimaryBins));
         
         if(H[Names[i]] == nullptr)
            continue;

         for(int j = 1; j <= PrimaryBinCount; j++)
         {
            double Width = PrimaryBins[j] - PrimaryBins[j-1];
            HHuman[i]->SetBinContent(j, H[Names[i]]->GetBinContent(j + iB * PrimaryBinCount) / Width);
            HHuman[i]->SetBinError(j, H[Names[i]]->GetBinError(j + iB * PrimaryBinCount) / Width);
         }

         HHuman[i]->SetStats(0);

         HHuman[i]->SetLineWidth(2);
         HHuman[i]->SetLineColor(Colors[i]);
         HHuman[i]->SetMarkerColor(Colors[i]);

         if(BinningCount > 1)
            HHuman[i]->SetTitle((Title + " (" + BinLabel + ")").c_str());
         else
            HHuman[i]->SetTitle(Title.c_str());
         HHuman[i]->GetXaxis()->SetTitle(XTitle.c_str());
         HHuman[i]->GetYaxis()->SetTitle(YTitle.c_str());

         if(iB == 0)
            Legend.AddEntry(HHuman[i], Labels[i].c_str(), "pl");

         if(First == true)
            HHuman[i]->Draw();
         else
            HHuman[i]->Draw("same");
         HHuman[i]->Draw("hist same");

         First = false;
      }

      Legend.Draw();

      Canvas.SetGridx();
      Canvas.SetGridy();
      PdfFile.AddCanvas(Canvas);

      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
   }
}


