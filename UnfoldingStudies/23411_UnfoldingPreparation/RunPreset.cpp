#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "CommandLine.h"

int main(int argc, char *argv[]);
map<string, string> GetBinnings();
map<string, string> GetBinningsFine();
map<string, string> GetBinningsVeryFine();
string EqualBin(double Min, double Max, double Spacing);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   
   string DataFile       = CL.Get("Data",     "Data.root");
   string DataSumEFile   = CL.Get("DataSumE", "DataSumE.root");
   string MCFile         = CL.Get("MC",       "MC.root");
   string MCSumEFile     = CL.Get("MCSumE",   "MCSumE.root");
   string Prefix         = CL.Get("Prefix");
   string Suffix         = CL.Get("Suffix");

   string GenReweight    = CL.Get("GenReweight", "none");

   string JetShift       = CL.Get("Shift", "0.0");
   string JetSmear       = CL.Get("Smear", "1.025");
   string Flooring       = CL.Get("Flooring", "false");

   bool FineRecoBins     = CL.GetBool("FineRecoBins", false);
   bool VeryFineRecoBins = CL.GetBool("VeryFineRecoBins", false);
   
   map<string, string> Binnings;
   if(FineRecoBins == false && VeryFineRecoBins == false)
      Binnings = GetBinnings();
   else if(FineRecoBins == true && VeryFineRecoBins == false)
      Binnings = GetBinningsFine();
   else
      Binnings = GetBinningsVeryFine();

   vector<string> Observables = CL.GetStringVector("Observables", {"JetE", "LeadingDiJetE", "LeadingDiJetSumE",
      "JetZG", "JetRG", "JetMG", "JetMGE", "JetM", "JetME",
      "JetZG2", "JetRG2", "JetMG2", "JetMGE2"});

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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "LeadingJetE")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "LeadingJetE" << Suffix << ".root"
            << " --Observable LeadingJetE --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetEBins"]
            << " --BinningGenBins 0,1 --BinningRecoBins 0,1"
            << " --ObservableUncertaintyShift " << JetShift
            << " --ObservableUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "LeadingDiJetE")
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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "LeadingDiJetSumE")
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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetZG")
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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetRG")
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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetMG")
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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetMGE")
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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetM")
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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetME")
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
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetZG2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetZG2" << Suffix << ".root"
            << " --Observable JetZG --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetZGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetZGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetRG2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetRG2" << Suffix << ".root"
            << " --Observable JetRG --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetRGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetRGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetMG2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetMG2" << Suffix << ".root"
            << " --Observable JetMG --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMGBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMGBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "JetMGE2")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "JetMGE2" << Suffix << ".root"
            << " --Observable JetMGE --ObservableIndex 1 --Binning JetE --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetMGEBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetMGEBins"]
            << " --BinningGenBins " << Binnings["GenJetECoarseBins"]
            << " --BinningRecoBins " << Binnings["RecoJetECoarseBins"]
            << " --BinningUncertaintyShift " << JetShift
            << " --BinningUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << " --GenReweight " << GenReweight
            << ";" << endl;
      }
      else if(Observable == "Thrust")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "Thrust" << Suffix << ".root"
            << " --Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenThrustBins"]
            << " --ObservableRecoBins " << Binnings["RecoThrustBins"]
            << " --BinningGenBins 0,1"
            << " --BinningRecoBins 0,1"
            << " --Flooring " << Flooring << " --CheckMatchAngle false"
            << ";" << endl;
      }
      else if(Observable == "ThrustUniform")
      {
         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "Thrust" << Suffix << ".root"
            << " --Observable Thrust --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenThrustUniformBins"]
            << " --ObservableRecoBins " << Binnings["RecoThrustUniformBins"]
            << " --BinningGenBins 0,1"
            << " --BinningRecoBins 0,1"
            << " --Flooring " << Flooring << " --CheckMatchAngle false"
            << ";" << endl;
      }
      else
         cout << "time echo observable " << Observable << " not found" << endl;
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

map<string, string> GetBinningsFine()
{
   map<string, string> Binnings;

   Binnings["GenJetEBins"]           = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45";
   Binnings["RecoJetEBins"]          = "1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5,10,10.5,11,11.5,12,12.5,13,13.5,14,14.5,15,15.5,16,16.5,17,17.5,18,18.5,19,19.5,20,20.5,21,21.5,22,22.5,23,23.5,24,24.5,25,25.5,26,26.5,27,27.5,28,28.5,29,29.5,30,30.5,31,31.5,32,32.5,33,33.5,34,34.5,35,35.5,36,36.5,37,37.5,38,38.5,39,39.5,40,40.5,41,41.5,42,42.5,43,43.5,44,44.5,45,45.5,46,46.5,47,47.5,48,48.5,49,49.5,50,51.25,52.5,53.75,55,56.25,57.5,58.75,60,62.5,65,67.5,70,75,80,90";
   Binnings["GenJetLEBins"]          = "10,12,14,16,18,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45";
   Binnings["RecoJetLEBins"]         = "10,11,12,13,14,15,16,17,18,19,20,20.5,21,21.5,22,22.5,23,23.5,24,24.5,25,25.5,26,26.5,27,27.5,28,28.5,29,29.5,30,30.5,31,31.5,32,32.5,33,33.5,34,34.5,35,35.5,36,36.5,37,37.5,38,38.5,39,39.5,40,40.5,41,41.5,42,42.5,43,43.5,44,44.5,45,45.5,46,46.5,47,47.5,48,48.5,49,49.5,50,51.25,52.5,53.75,55,56.25,57.5,58.75,60,62.5,65,67.5,70,75,80,90";
   Binnings["GenJetSEBins"]          = "20,24,28,32,36,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90";
   Binnings["RecoJetSEBins"]         = "20,22,24,26,28,30,32,34,36,38,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,102.5,105,107.5,110,112.5,115,117.5,120,125,130,135,140,150,160,180";
   Binnings["GenJetE1Bins"]          = "3,6,9,12,15,18,21,24,27,30,33,36,39,42,44";
   Binnings["RecoJetE1Bins"]         = "3,4.5,6,7.5,9,10.5,12,13.5,15,16.5,18,19.5,21,22.5,24,25.5,27,28.5,30,31.5,33,34.5,36,37.5,39,40.5,42,43.5,45,47.5,50,55,60,65,70,90";
   Binnings["GenJetE2Bins"]          = "3,6,9,12,15,18,21,24,27,30,33,36,39,42,44";
   Binnings["RecoJetE2Bins"]         = "3,4.5,6,7.5,9,10.5,12,13.5,15,16.5,18,19.5,21,22.5,24,25.5,27,28.5,30,31.5,33,34.5,36,37.5,39,40.5,42,43.5,45,47.5,50,55,60,65,70,90";
   Binnings["GenJetECoarseBins"]     = "5,10,15,20,25,30,35,40";
   Binnings["RecoJetECoarseBins"]    = "5,7.5,10,12.5,15,17.5,20,22.5,25,27.5,30,32.5,35,37.5,40,42.5,45,47.5,50,60";
   Binnings["GenJetMBins"]           = "0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0";
   Binnings["RecoJetMBins"]          = "0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.25,2.5,2.75,3.0,3.25,3.5,3.75,4.0,4.25,4.5,4.75,5.0,5.25,5.5,5.75,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0,12.0";
   Binnings["GenJetMEBins"]          = "0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26,0.30,0.37";
   Binnings["RecoJetMEBins"]         = "0.015,0.03,0.045,0.06,0.075,0.09,0.105,0.12,0.135,0.15,0.165,0.18,0.195,0.21,0.23,0.26,0.28,0.30,0.37";
   Binnings["GenJetZGBins"]          = "0,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45";
   Binnings["RecoJetZGBins"]         = "0,0.10,0.125,0.15,0.175,0.20,0.225,0.25,0.275,0.30,0.325,0.35,0.375,0.40,0.425,0.45";
   Binnings["GenJetRGBins"]          = "0,0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45";
   Binnings["RecoJetRGBins"]         = "0,0.025,0.05,0.075,0.10,0.125,0.15,0.175,0.20,0.225,0.25,0.275,0.30,0.325,0.35,0.375,0.40,0.45";
   Binnings["GenJetMGBins"]          = "0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0";
   Binnings["RecoJetMGBins"]         = "0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.25,2.5,2.75,3.0,3.25,3.5,3.75,4.0,4.25,4.5,4.75,5.0,5.25,5.5,5.75,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0,12.0";
   Binnings["GenJetMGEBins"]         = "0,0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26,0.30,0.37";
   Binnings["RecoJetMGEBins"]        = "0,0.015,0.03,0.045,0.06,0.075,0.09,0.105,0.12,0.135,0.15,0.165,0.18,0.195,0.21,0.23,0.26,0.28,0.30,0.37";
   Binnings["GenThrustBins"]         = "0.70,0.75,0.80,0.82,0.84,0.86,0.88,0.90,0.91,0.92,0.93,0.937,0.943,0.95,0.955,0.96,0.965,0.97,0.975,0.98,0.985";
   Binnings["RecoThrustBins"]        = "0.70,0.75,0.80,0.82,0.84,0.86,0.88,0.90,0.91,0.92,0.93,0.937,0.943,0.95,0.955,0.96,0.965,0.97,0.975,0.98,0.985";
   Binnings["GenThrustUniformBins"]  = "0.59,0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99";
   Binnings["RecoThrustUniformBins"] = "0.59,0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99";

   return Binnings;
}

map<string, string> GetBinningsVeryFine()
{
   map<string, string> Binnings;

   Binnings["GenJetEBins"]           = EqualBin(1, 45, 1);
   Binnings["RecoJetEBins"]          = EqualBin(1, 49.75, 0.25) + ","
                                     + EqualBin(50, 59, 0.5) + ","
                                     + EqualBin(60, 70, 2) + ",75,80,90";
   Binnings["GenJetLEBins"]          = EqualBin(10, 18, 2) + "," + EqualBin(20, 45, 1);
   Binnings["RecoJetLEBins"]         = EqualBin(10, 19, 1) + ","
                                     + EqualBin(20, 49.75, 0.25) + ","
                                     + EqualBin(50, 59, 1) + ","
                                     + EqualBin(60, 70, 2.5) + ",80,90";
   Binnings["GenJetSEBins"]          = EqualBin(20, 36, 4) + "," + EqualBin(40, 90, 2);
   Binnings["RecoJetSEBins"]         = EqualBin(20, 38, 2) + ","
                                     + EqualBin(40, 99, 1) + ","
                                     + EqualBin(100, 118, 2) + ","
                                     + EqualBin(120, 140, 5) + ",150,160,180";
   Binnings["GenJetE1Bins"]          = EqualBin(3, 45, 3);
   Binnings["RecoJetE1Bins"]         = "3,4.5,6,7.5,9,10.5,12,13.5,15,16.5,18,19.5,21,22.5,24,25.5,27,28.5,30,31.5,33,34.5,36,37.5,39,40.5,42,43.5,45,47.5,50,55,60,65,70,90";
   Binnings["GenJetE2Bins"]          = EqualBin(3, 45, 3);
   Binnings["RecoJetE2Bins"]         = "3,4.5,6,7.5,9,10.5,12,13.5,15,16.5,18,19.5,21,22.5,24,25.5,27,28.5,30,31.5,33,34.5,36,37.5,39,40.5,42,43.5,45,47.5,50,55,60,65,70,90";
   Binnings["GenJetECoarseBins"]     = "5,10,15,20,25,30,35,40";
   Binnings["RecoJetECoarseBins"]    = "5,7.5,10,12.5,15,17.5,20,22.5,25,27.5,30,32.5,35,37.5,40,42.5,45,47.5,50,60";
   Binnings["GenJetMBins"]           = "0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0";
   Binnings["RecoJetMBins"]          = "0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.25,2.5,2.75,3.0,3.25,3.5,3.75,4.0,4.25,4.5,4.75,5.0,5.25,5.5,5.75,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0,12.0";
   Binnings["GenJetMEBins"]          = "0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26,0.30,0.37";
   Binnings["RecoJetMEBins"]         = "0.015,0.03,0.045,0.06,0.075,0.09,0.105,0.12,0.135,0.15,0.165,0.18,0.195,0.21,0.23,0.26,0.28,0.30,0.37";
   Binnings["GenJetZGBins"]          = "0,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45";
   Binnings["RecoJetZGBins"]         = "0,0.10,0.125,0.15,0.175,0.20,0.225,0.25,0.275,0.30,0.325,0.35,0.375,0.40,0.425,0.45";
   Binnings["GenJetRGBins"]          = "0,0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45";
   Binnings["RecoJetRGBins"]         = "0,0.025,0.05,0.075,0.10,0.125,0.15,0.175,0.20,0.225,0.25,0.275,0.30,0.325,0.35,0.375,0.40,0.45";
   Binnings["GenJetMGBins"]          = "0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0";
   Binnings["RecoJetMGBins"]         = "0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.25,2.5,2.75,3.0,3.25,3.5,3.75,4.0,4.25,4.5,4.75,5.0,5.25,5.5,5.75,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0,12.0";
   Binnings["GenJetMGEBins"]         = "0,0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.26,0.30,0.37";
   Binnings["RecoJetMGEBins"]        = "0,0.015,0.03,0.045,0.06,0.075,0.09,0.105,0.12,0.135,0.15,0.165,0.18,0.195,0.21,0.23,0.26,0.28,0.30,0.37";
   Binnings["GenThrustBins"]         = "0.70,0.75,0.80,0.82,0.84,0.86,0.88,0.90,0.91,0.92,0.93,0.937,0.943,0.95,0.955,0.96,0.965,0.97,0.975,0.98,0.985";
   Binnings["RecoThrustBins"]        = "0.70,0.75,0.80,0.82,0.84,0.86,0.88,0.90,0.91,0.92,0.93,0.937,0.943,0.95,0.955,0.96,0.965,0.97,0.975,0.98,0.985";
   Binnings["GenThrustUniformBins"]  = "0.59,0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99";
   Binnings["RecoThrustUniformBins"] = "0.59,0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99";

   return Binnings;
}

string EqualBin(double Min, double Max, double Spacing)
{
   string Result = to_string(Min);
   for(double X = Min + Spacing; X <= Max; X = X + Spacing)
      Result = Result + "," + to_string(X);
   return Result;
}
