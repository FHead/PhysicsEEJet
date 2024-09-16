#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen




./Execute --Input Input/DataJetMENominal.root \
   --Systematic Systematics/DataJetMENormalized.root --Output Plots/DataJetMENominal.pdf --FinalOutput Plots/MeowME.${Format} \
   --RootOutput Root/DataJetMENominal.root \
   --MCFile "Input/DataJetMENominal.root","OriginalInput/MCPythia8JetME.root","OriginalInput/MCHerwigJetME.root",OriginalInput/MCSherpaJetME.root,OriginalInput/${PYQUEN}JetME.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
   --WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 12 --WorldRMin 0.45 --WorldRMax 1.75 --LogY false \
   --XLabel "Jet M/E" --YLabel "1/N dN/d(Jet M/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08
   
./Execute --Input Input/DataJetMENominal.root \
   --Systematic Systematics/DataJetMENormalized.root --Output Plots/DataJetMENominal.pdf --FinalOutput Plots/MeowMEPythia.${Format} \
   --RootOutput Root/DataJetMENominalPythia.root \
   --MCFile "Input/DataJetMENominal.root","OriginalInput/MCPythia8JetME.root","OriginalInput/MCVincia1JetME.root",OriginalInput/MCVincia2JetME.root,Input/DataJetMETighter.root,OriginalInput/MCJetScapeJetME.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HUnfoldedBayes7,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2","Tighter","JetScape" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
   --WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 12 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet M/E" --YLabel "1/N dN/d(Jet M/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetMENominal.root \
   --Systematic Systematics/DataJetMENormalized.root --Output Plots/DataJetMENominal.pdf --FinalOutput Plots/MeowMEJetScape.${Format} \
   --RootOutput Root/DataJetMENominalPythia.root \
   --MCFile "Input/DataJetMENominal.root","OriginalInput/MCPythia8JetME.root",OriginalInput/MCJetScapeJetME.root,OriginalInput/MCJetScapeBypassJetME.root,OriginalInput/MCJetScapeSmashJetME.root,OriginalInput/MCJetScapeLHEJetME.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","JS Matter","JS FSR","JS Matter+Smash","JS Madgraph" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
   --WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 12 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet M/E" --YLabel "1/N dN/d(Jet M/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08


./Execute --Input Input/DataJetMENominal.root \
   --Systematic None --Output Plots/DataJetMEReco.pdf --FinalOutput Plots/MeowMEReco.${Format} \
   --RootOutput Root/DataJetMEReco.root \
   --MCFile "Input/DataJetMENominal.root" \
   --MCHistogram HMCMeasured \
   --MCLabel "PYTHIA 6" \
   --PrimaryName HInput \
   --DoSelfNormalize true \
   --DoReco true \
   --GenPrimaryMin 0 --GenPrimaryMax 0.5 \
   --RecoPrimaryMin 0 --RecoPrimaryMax 0.5 \
   --WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 12 --WorldRMin 0.45 --WorldRMax 1.75 --LogY false \
   --XLabel "Jet M/E" --YLabel "1/N dN/d(Jet M/E)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 2 --Row 3 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08



