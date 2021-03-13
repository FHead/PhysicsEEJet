#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"

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

   string InputData        = CL.Get("Input",            "Data.root");
   string DataName         = CL.Get("InputName",        "HRecoJetPBinned");
   string InputResponse    = CL.Get("Response",         "MC.root");
   string ResponseName     = CL.Get("ResponseName",     "H2DJetPBinned");
   string ResponseTruth    = CL.Get("ResponseTruth",    "HGenJetPBinned");
   string ResponseMeasured = CL.Get("ResponseMeasured", "HRecoJetPBinned");
   string Output           = CL.Get("Output",           "Unfolded.root");
   bool MCPrior            = CL.GetBool("MCPrior",      false);

   TFile ResponseFile(InputResponse.c_str());
   TFile InputDataFile(InputData.c_str());

   const TH1 *HMeasured = (TH1 *)ResponseFile.Get(ResponseMeasured.c_str());
   const TH1 *HTruth    = (TH1 *)ResponseFile.Get(ResponseTruth.c_str());
   const TH2 *HResponse = (TH2 *)ResponseFile.Get(ResponseName.c_str());

   const TH1 *HInput    = (TH1 *)InputDataFile.Get(DataName.c_str())->Clone();

   RooUnfoldResponse *Response;
   if(MCPrior == true)
      Response = new RooUnfoldResponse(HMeasured, HTruth, HResponse);
   else
      Response = FillResponse(HResponse);
 
   RooUnfoldBayes BayesUnfold1(Response, HInput, 1);
   RooUnfoldBayes BayesUnfold2(Response, HInput, 2);
   RooUnfoldBayes BayesUnfold3(Response, HInput, 3);
   RooUnfoldBayes BayesUnfold4(Response, HInput, 4);
   RooUnfoldBayes BayesUnfold6(Response, HInput, 6);
   RooUnfoldBayes BayesUnfold10(Response, HInput, 10);
   RooUnfoldBayes BayesUnfold20(Response, HInput, 20);
   RooUnfoldBayes BayesUnfold30(Response, HInput, 30);
   RooUnfoldBayes BayesUnfold50(Response, HInput, 50);
   RooUnfoldBayes BayesUnfold100(Response, HInput, 100);
   RooUnfoldBayes BayesUnfold200(Response, HInput, 200);

   TH1 *HUnfoldedBayes1 = (TH1 *)BayesUnfold1.Hreco();
   TH1 *HUnfoldedBayes2 = (TH1 *)BayesUnfold2.Hreco();
   TH1 *HUnfoldedBayes3 = (TH1 *)BayesUnfold3.Hreco();
   TH1 *HUnfoldedBayes4 = (TH1 *)BayesUnfold4.Hreco();
   TH1 *HUnfoldedBayes6 = (TH1 *)BayesUnfold6.Hreco();
   TH1 *HUnfoldedBayes10 = (TH1 *)BayesUnfold10.Hreco();
   TH1 *HUnfoldedBayes20 = (TH1 *)BayesUnfold20.Hreco();
   TH1 *HUnfoldedBayes30 = (TH1 *)BayesUnfold30.Hreco();
   TH1 *HUnfoldedBayes50 = (TH1 *)BayesUnfold50.Hreco();
   TH1 *HUnfoldedBayes100 = (TH1 *)BayesUnfold100.Hreco();
   TH1 *HUnfoldedBayes200 = (TH1 *)BayesUnfold200.Hreco();

   TFile OutputFile(Output.c_str(), "RECREATE");
   HMeasured->Clone("HMCMeasured")->Write();
   HTruth->Clone("HMCTruth")->Write();
   HResponse->Clone("HMCResponse")->Write();
   Response->Mresponse().Clone("HMCFilledResponse")->Write();
   HInput->Clone("HInput")->Write();
   HUnfoldedBayes1->Clone("HUnfoldedBayes1")->Write();
   HUnfoldedBayes2->Clone("HUnfoldedBayes2")->Write();
   HUnfoldedBayes3->Clone("HUnfoldedBayes3")->Write();
   HUnfoldedBayes4->Clone("HUnfoldedBayes4")->Write();
   HUnfoldedBayes6->Clone("HUnfoldedBayes6")->Write();
   HUnfoldedBayes10->Clone("HUnfoldedBayes10")->Write();
   HUnfoldedBayes20->Clone("HUnfoldedBayes20")->Write();
   HUnfoldedBayes30->Clone("HUnfoldedBayes30")->Write();
   HUnfoldedBayes50->Clone("HUnfoldedBayes50")->Write();
   HUnfoldedBayes100->Clone("HUnfoldedBayes100")->Write();
   HUnfoldedBayes200->Clone("HUnfoldedBayes200")->Write();
   OutputFile.Close();

   InputDataFile.Close();
   ResponseFile.Close();

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

