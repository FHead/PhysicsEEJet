#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TMatrixD.h"

#include "RooUnfold.h"
#include "RooUnfoldInvert.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"

#include "CommandLine.h"

int main(int argc, char *argv[]);
RooUnfoldResponse *FillResponse(const TH2 *HResponse);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName    = CL.Get("Input",            "Input/DataJetPNominal.root");
   string DataName         = CL.Get("InputName",        "HDataReco");
   string ResponseName     = CL.Get("ResponseName",     "HResponse");
   string ResponseTruth    = CL.Get("ResponseTruth",    "HMCGen");
   string ResponseMeasured = CL.Get("ResponseMeasured", "HMCReco");
   string Output           = CL.Get("Output",           "Unfolded.root");
   bool MCPrior            = CL.GetBool("MCPrior",      false);

   TFile InputFile(InputFileName.c_str());

   const TH1 *HMeasured = (TH1 *)InputFile.Get(ResponseMeasured.c_str());
   const TH1 *HTruth    = (TH1 *)InputFile.Get(ResponseTruth.c_str());
   const TH2 *HResponse = (TH2 *)InputFile.Get(ResponseName.c_str());

   const TH1 *HInput    = (TH1 *)InputFile.Get(DataName.c_str())->Clone();

   map<string, TMatrixD> Covariance;

   RooUnfoldResponse *Response;
   if(MCPrior == true)
      Response = new RooUnfoldResponse(HMeasured, HTruth, HResponse);
   else
      Response = FillResponse(HResponse);
 
   vector<int> Iterations{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 80, 90, 100, 125, 150, 200, 250};
   vector<TH1 *> HUnfolded;
   for(int I : Iterations)
   {
      RooUnfoldBayes BayesUnfold(Response, HInput, I);
      HUnfolded.push_back((TH1 *)(BayesUnfold.Hreco()->Clone(Form("HUnfoldedBayes%d", I))));
      Covariance.insert(pair<string, TMatrixD>(Form("MUnfoldedBayes%d", I), BayesUnfold.Ereco()));
   }

   RooUnfoldInvert InvertUnfold(Response, HInput);
   HUnfolded.push_back((TH1 *)(InvertUnfold.Hreco()->Clone("HUnfoldedInvert")));
   Covariance.insert(pair<string, TMatrixD>("MUnfoldedInvert", InvertUnfold.Ereco()));
   
   vector<double> SVDRegularization{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 80, 90, 100, 125, 150};
   for(double D : SVDRegularization)
   {
      RooUnfoldSvd SVDUnfold(Response, HInput, D);
      HUnfolded.push_back((TH1 *)(SVDUnfold.Hreco()->Clone(Form("HUnfoldedSVD%.1f", D))));
      Covariance.insert(pair<string, TMatrixD>(Form("MUnfoldedSVD%.1f", D), SVDUnfold.Ereco()));
   }

   TFile OutputFile(Output.c_str(), "RECREATE");
   HMeasured->Clone("HMCMeasured")->Write();
   HTruth->Clone("HMCTruth")->Write();
   HResponse->Clone("HMCResponse")->Write();
   Response->Mresponse().Clone("HMCFilledResponse")->Write();
   HInput->Clone("HInput")->Write();
   for(TH1 *H : HUnfolded)
      if(H != nullptr)
         H->Write();
   for(auto I : Covariance)
      I.second.Write(I.first.c_str());

   InputFile.Get("HGenPrimaryBinMin")->Clone()->Write();
   InputFile.Get("HGenPrimaryBinMax")->Clone()->Write();
   InputFile.Get("HGenBinningBinMin")->Clone()->Write();
   InputFile.Get("HGenBinningBinMax")->Clone()->Write();
   InputFile.Get("HRecoPrimaryBinMin")->Clone()->Write();
   InputFile.Get("HRecoPrimaryBinMax")->Clone()->Write();
   InputFile.Get("HRecoBinningBinMin")->Clone()->Write();
   InputFile.Get("HRecoBinningBinMax")->Clone()->Write();
   InputFile.Get("HMatchedPrimaryBinMin")->Clone()->Write();
   InputFile.Get("HMatchedPrimaryBinMax")->Clone()->Write();
   InputFile.Get("HMatchedBinningBinMin")->Clone()->Write();
   InputFile.Get("HMatchedBinningBinMax")->Clone()->Write();

   if(InputFile.Get("MCEventCount") != nullptr)
      InputFile.Get("MCEventCount")->Clone("MCEventCount")->Write();
   if(InputFile.Get("DataEventCount") != nullptr)
      InputFile.Get("DataEventCount")->Clone("DataEventCount")->Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;
}

RooUnfoldResponse *FillResponse(const TH2 *HResponse)
{
   int NX = HResponse->GetNbinsX();
   int NY = HResponse->GetNbinsY();
   double XMin = HResponse->GetXaxis()->GetBinLowEdge(1);
   double YMin = HResponse->GetYaxis()->GetBinLowEdge(1);
   double XMax = HResponse->GetXaxis()->GetBinUpEdge(NX);
   double YMax = HResponse->GetYaxis()->GetBinUpEdge(NY);

   RooUnfoldResponse *Response = new RooUnfoldResponse(NX, XMin, XMax, NY, YMin, YMax);

   for(int i = 1; i <= HResponse->GetNbinsX(); i++)
   {
      for(int j = 1; j <= HResponse->GetNbinsY(); j++)
      {
         double x = HResponse->GetXaxis()->GetBinCenter(i);
         double y = HResponse->GetYaxis()->GetBinCenter(j);
         for(int k = 0; k < HResponse->GetBinContent(i, j); k++)
            Response->Fill(x, y);
      }
   }

   return Response;
}

