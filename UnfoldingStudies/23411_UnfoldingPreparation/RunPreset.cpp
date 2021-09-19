#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "CommandLine.h"

int main(int argc, char *argv[]);
map<string, string> GetBinnings();

int main(int argc, char *argv[])
{
   map<string, string> Binnings = GetBinnings();

   CommandLine CL(argc, argv);
   
   string DataFile     = CL.Get("Data",     "Data.root");
   string DataSumEFile = CL.Get("DataSumE", "DataSumE.root");
   string MCFile       = CL.Get("MC",       "MC.root");
   string MCSumEFile   = CL.Get("MCSumE",   "MCSumE.root");
   string Prefix       = CL.Get("Prefix");
   string Suffix       = CL.Get("Suffix");

   string JetShift     = CL.Get("Shift", "0.0");
   string JetSmear     = CL.Get("Smear", "1.025");
   string Flooring     = CL.Get("Flooring", "false");

   vector<string> Observables = CL.GetStringVector("Observables", {"JetE", "LeadingDiJetE", "LeadingDiJetSumE",
      "JetZG", "JetRG", "JetMG", "JetMGE", "JetM", "JetME",
      "JetZG2", "JetRG2", "JetMG2", "JetMGE2", "JetM2", "JetME2"});

   for(string Observable: Observables)
   {
      if(Observable == "JetE")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetE" << Suffix << ".root"
            << " --Observable JetE --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetEBins"]
            << " --BinningGenBins 0,1 --BinningRecoBins 0,1"
            << " --ObservableUncertaintyShift " << JetShift
            << " --ObservableUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "LeadingDiJetE")
      {
         cout << "time ./Execute --MC " << MCSumEFile << " --Data " << DataSumEFile
            << " --Output Output/" << Prefix << "LeadingDiJetE" << Suffix << ".root"
            << " --Observable LeadingDiJetE --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetLEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetLEBins"]
            << " --BinningGenBins 0,1 --BinningRecoBins 0,1"
            << " --ObservableUncertaintyShift " << JetShift
            << " --ObservableUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "LeadingDiJetSumE")
      {
         cout << "time ./Execute --MC " << MCSumEFile << " --Data " << DataSumEFile
            << " --Output Output/" << Prefix << "LeadingDiJetSumE" << Suffix << ".root"
            << " --Observable LeadingDiJetSumE --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetSEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetSEBins"]
            << " --BinningGenBins 0,1 --BinningRecoBins 0,1"
            << " --ObservableUncertaintyShift " << JetShift
            << " --ObservableUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetZG")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetZG" << Suffix << ".root"
            << " --Observable JetZG --ObservableIndex 0 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetZGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetZGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetRG")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetRG" << Suffix << ".root"
            << " --Observable JetRG --ObservableIndex 0 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetRGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetRGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetMG")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetMG" << Suffix << ".root"
            << " --Observable JetMG --ObservableIndex 0 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetMGE")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetMGE" << Suffix << ".root"
            << " --Observable JetMGE --ObservableIndex 0 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMGEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMGEBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetM")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetM" << Suffix << ".root"
            << " --Observable JetM --ObservableIndex 0 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetME")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetME" << Suffix << ".root"
            << " --Observable JetME --ObservableIndex 0 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMEBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetZG2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetZG" << Suffix << ".root"
            << " --Observable JetZG --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetZGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetZGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetRG2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetRG" << Suffix << ".root"
            << " --Observable JetRG --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetRGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetRGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetMG2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetMG" << Suffix << ".root"
            << " --Observable JetMG --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetMGE2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetMGE" << Suffix << ".root"
            << " --Observable JetMGE --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMGEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMGEBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetM2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetM" << Suffix << ".root"
            << " --Observable JetM --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "JetME2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetME" << Suffix << ".root"
            << " --Observable JetME --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMEBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
      if(Observable == "Thrust")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetME" << Suffix << ".root"
            << " --Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenThrustBins"]
            << " --ObservableRecoBins " << Binnings["RecoThrustBins"]
            << " --BinningGenBins 0,1"
            << " --BinningRecoBins 0,1"
            << " --Flooring " << Flooring << " --CheckMatchAngle false"
            << ";" << endl;
      }
      if(Observable == "ThrustUniform")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetME" << Suffix << ".root"
            << " --Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenThrustUniformBins"]
            << " --ObservableRecoBins " << Binnings["RecoThrustUniformBins"]
            << " --BinningGenBins 0,1"
            << " --BinningRecoBins 0,1"
            << " --Flooring " << Flooring << " --CheckMatchAngle false"
            << ";" << endl;
      }
   }
}

map<string, string> GetBinnings()
{
   map<string, string> Binnings;

   Binnings["GenJetEBins"]           = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45";
   Binnings["RecoJetEBins"]          = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,52.5,55,57.5,60,65,70,80,90";
   Binnings["GenJetLEBins"]          = "10,12,14,16,18,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45";
   Binnings["RecoJetLEBins"]         = "10,12,14,16,18,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,52.5,55,57.5,60,65,70,80,90";
   Binnings["GenJetSEBins"]          = "20,24,28,32,36,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90";
   Binnings["RecoJetSEBins"]         = "20,24,28,32,36,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,105,110,115,120,130,140,160,180";
   Binnings["GenJetE1Bins"]          = "3,6,9,12,15,18,21,24,27,30,33,36,39,42,44";
   Binnings["RecoJetE1Bins"]         = "3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,50,60,70,90";
   Binnings["GenJetE2Bins"]          = "3,6,9,12,15,18,21,24,27,30,33,36,39,42,44";
   Binnings["RecoJetE2Bins"]         = "3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,50,60,70,90";
   Binnings["GenJetECoarseBins"]     = "5,10,15,20,25,30,35,40";
   Binnings["RecoJetECoarseBins"]    = "5,10,15,20,25,30,35,40,45,50,60";
   Binnings["GenJetMBins"]           = "0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0";
   Binnings["RecoJetMBins"]          = "0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0";
   Binnings["GenJetMEBins"]          = "0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26,0.30,0.37";
   Binnings["RecoJetMEBins"]         = "0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26,0.30,0.37";
   Binnings["GenJetZGBins"]          = "0,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45";
   Binnings["RecoJetZGBins"]         = "0,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45";
   Binnings["GenJetRGBins"]          = "0,0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45";
   Binnings["RecoJetRGBins"]         = "0,0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45";
   Binnings["GenJetMGBins"]          = "0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0";
   Binnings["RecoJetMGBins"]         = "0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0";
   Binnings["GenJetMGEBins"]         = "0,0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26,0.30,0.37";
   Binnings["RecoJetMGEBins"]        = "0,0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26,0.30,0.37";
   Binnings["GenThrustBins"]         = "0.70,0.75,0.80,0.82,0.84,0.86,0.88,0.90,0.91,0.92,0.93,0.937,0.943,0.95,0.955,0.96,0.965,0.97,0.975,0.98,0.985";
   Binnings["RecoThrustBins"]        = "0.70,0.75,0.80,0.82,0.84,0.86,0.88,0.90,0.91,0.92,0.93,0.937,0.943,0.95,0.955,0.96,0.965,0.97,0.975,0.98,0.985";
   Binnings["GenThrustUniformBins"]  = "0.59,0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99";
   Binnings["RecoThrustUniformBins"] = "0.59,0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99";

   return Binnings;
}

