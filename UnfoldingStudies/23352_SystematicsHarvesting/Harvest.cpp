#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TFile.h"

#include "CustomAssert.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> FileNames      = CL.GetStringVector("Input");
   vector<string> HistogramNames = CL.GetStringVector("Histogram");
   vector<string> Labels         = CL.GetStringVector("Label");
   string BinMappingFileName     = CL.Get("BinMapping");
   string OutputFileName         = CL.Get("Output");

   Assert(FileNames.size() > 0, "No file names specified");
   Assert(FileNames.size() == HistogramNames.size(), "Inconsistent file name and histogram name");
   Assert(FileNames.size() == Labels.size(), "Inconsistent file name and label name");

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TFile BinMappingFile(BinMappingFileName.c_str());

   OutputFile.cd();
   BinMappingFile.Get("HGenPrimaryBinMin")->Clone()->Write();
   BinMappingFile.Get("HGenPrimaryBinMax")->Clone()->Write();
   BinMappingFile.Get("HGenBinningBinMin")->Clone()->Write();
   BinMappingFile.Get("HGenBinningBinMax")->Clone()->Write();
   BinMappingFile.Get("HRecoPrimaryBinMin")->Clone()->Write();
   BinMappingFile.Get("HRecoPrimaryBinMax")->Clone()->Write();
   BinMappingFile.Get("HRecoBinningBinMin")->Clone()->Write();
   BinMappingFile.Get("HRecoBinningBinMax")->Clone()->Write();
   BinMappingFile.Get("HMatchedPrimaryBinMin")->Clone()->Write();
   BinMappingFile.Get("HMatchedPrimaryBinMax")->Clone()->Write();
   BinMappingFile.Get("HMatchedBinningBinMin")->Clone()->Write();
   BinMappingFile.Get("HMatchedBinningBinMax")->Clone()->Write();

   BinMappingFile.Close();

   for(int i = 0; i < (int)FileNames.size(); i++)
   {
      TFile File(FileNames[i].c_str());

      TH1D *H = (TH1D *)File.Get(HistogramNames[i].c_str());

      if(H != nullptr)
      {
         OutputFile.cd();
         H->Clone(Form("H%s", Labels[i].c_str()))->Write();
      }

      File.Close();
   }

   OutputFile.Close();

   return 0;
}


