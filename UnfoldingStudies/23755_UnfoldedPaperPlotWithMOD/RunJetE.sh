#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen

# Jet E: Count
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root --Output Plots/DataJetENominalCount.pdf --FinalOutput Plots/MeowECount.$Format \
   --RootOutput Root/DataJetENominalCount.root \
   --MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/${PYQUEN}JetE.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 722","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 9000 --WorldYMax 500000 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Jet E (GeV)" --YLabel "dN / d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: Normalized
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowELog.$Format \
   --RootOutput Root/DataJetENominal.root \
   --MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/${PYQUEN}JetE.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.5 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
   
# Jet E: Normalized - log
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowE.$Format \
   --RootOutput Root/DataJetENominal.root \
   --MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/${PYQUEN}JetE.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
   
# Jet E: pythia variations only
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowEPythia.$Format \
   --RootOutput Root/DataJetEPythia.root \
   --MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCVincia1JetE.root",OriginalInput/MCVincia2JetE.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: Normalized, Joao comparison
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowELogJoao.$Format \
   --RootOutput Root/DataJetEJoao.root \
   --MCFile "Input/DataJetENominal.root","FelixInput/Graph_inclusive.root","JoaoInput/GraphsNLO.root" \
   --MCHistogram HMCTruth,GFelix,GBoth \
   --MCLabel "PYTHIA 6","NLL' resummed","NLO (Scale+Stat)" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.75 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: normalized, felix comparison
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowELogFelix.$Format \
   --RootOutput Root/DataJetEFelix.root \
   --MCFile "Input/DataJetENominal.root","FelixInput/Graph_inclusive.root" \
   --MCHistogram HMCTruth,GFelix \
   --MCLabel "PYTHIA 6","Felix" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.75 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: TUnfold
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root \
   --Output Plots/DataJetETUnfold.pdf \
   --FinalOutput Plots/MeowETUnfold.$Format \
   --RootOutput Root/DataJetETUnfold.root \
   --MCFile "Input/DataJetENominal.root" \
   --MCHistogram HUnfoldedTUnfold \
   --MCLabel "TUnfold" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.5 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: reco bin count comparison
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root \
   --Output Plots/DataJetEBinning.pdf \
   --FinalOutput Plots/MeowEBinning.$Format \
   --RootOutput Root/DataJetEBinning.root \
   --MCFile "Input/DataJetEMCPrior.root","Input/DataJetEFineRecoBin.root","Input/DataJetEVeryFineRecoBin.root" \
   --MCHistogram HUnfoldedTUnfold,HUnfoldedTUnfold,HUnfoldedTUnfold \
   --MCLabel "TUnfold","TUnfold 2x reco bin","TUnfold 4x reco bin" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.5 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: reco bin count comparison Bayes
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root \
   --Output Plots/DataJetEBayesBinning.pdf \
   --FinalOutput Plots/MeowEBayesBinning.$Format \
   --RootOutput Root/DataJetEBinningBayes.root \
   --MCFile "Input/DataJetEFineRecoBin.root","Input/DataJetEVeryFineRecoBin.root" \
   --MCHistogram HUnfoldedBayes17,HUnfoldedBayes17 \
   --MCLabel "2x reco bin","4x reco bin" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.5 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: gen reweight
./Execute --Input Input/DataJetENominal.root \
   --Systematic Systematics/DataJetE.root \
   --Output Plots/DataJetEGenReweight.pdf \
   --FinalOutput Plots/MeowEGenReweight.$Format \
   --RootOutput Root/DataJetEGenReweight.root \
   --MCFile "Input/DataJetEGenReweightN05Test.root","Input/DataJetEGenReweightN10Test.root","Input/DataJetEGenReweightN15Test.root","Input/DataJetEGenReweightZGDown.root","Input/DataJetEGenReweightZGUp.root","Input/DataJetEGenReweightRGDown.root","Input/DataJetEGenReweightRGUp.root" \
   --MCHistogram HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17,HUnfoldedBayes17 \
   --MCLabel "N05Test","N10Test","N15Test","ZGDown","ZGUp","RGDown","RGUp" \
   --PrimaryName HUnfoldedBayes17 \
   --DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.5 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: Fake data for MC closure
./Execute --Input Input/ToyJetENominal.root \
   --Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowEMC.$Format \
   --RootOutput Root/DataJetEToy.root \
   --DataLabel "BayesUnfold + data systematics" \
   --MCFile "Input/ToyJetENominal.root","Input/ToyJetENominal.root" \
   --MCHistogram HMCTruth,HUnfoldedTUnfold \
   --MCLabel "MC truth","TUnfold" \
   --PrimaryName HUnfoldedBayes2 \
   --DoSelfNormalize true --DoEventNormalize false --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 46 \
   --WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.06 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Jet E (GeV)" --YLabel "1/N dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

# Jet E: reco plots
./Execute --Input Input/DataJetENominal.root \
   --Systematic None --Output Plots/DataJetENominalReco.pdf --FinalOutput Plots/MeowEReco.$Format \
   --RootOutput Root/DataJetEReco.root \
   --MCFile "Input/MCJetENominal.root" \
   --MCHistogram HInput \
   --MCLabel "PYTHIA 6" \
   --PrimaryName HInput \
   --DoReco true \
   --DoSelfNormalize true --DoEventNormalize false --ExtraScale 1 \
   --GenPrimaryMin 0 --GenPrimaryMax 84 \
   --RecoPrimaryMin 0 --RecoPrimaryMax 84 \
   --WorldXMin 10 --WorldXMax 84 --WorldYMin 0 --WorldYMax 0.03 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
   --XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)  (GeV^{-1})" --Binning "None" \
   --LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
   --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
   --Texts 0,0.1,0.9,"$Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 0 --Row 1 --Column 1 \
   --DoMOD $DoMOD --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12


