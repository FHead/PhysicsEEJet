#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen


./Execute --Input Input/DataJetMNominal.root \
   --Systematic Systematics/DataJetMNormalized.root --Output Plots/DataJetMNominal.pdf --FinalOutput Plots/MeowM.${Format} \
   --MCFile "Input/DataJetMNominal.root","OriginalInput/MCPythia8JetM.root","OriginalInput/MCHerwigJetM.root",OriginalInput/MCSherpaJetM.root,OriginalInput/${PYQUEN}JetM.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 14.999 \
   --WorldXMin 0 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.599 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet M" --YLabel "1/N dN/d(Jet M)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

./Execute --Input Input/DataJetMNominal.root \
   --Systematic Systematics/DataJetMNormalized.root --Output Plots/DataJetMNominal.pdf --FinalOutput Plots/MeowMPythia.${Format} \
   --MCFile "Input/DataJetMNominal.root","OriginalInput/MCPythia8JetM.root","OriginalInput/MCVincia1JetM.root",OriginalInput/MCVincia2JetM.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","P8 Shower 1","P8 Shower 2" \
   --PrimaryName HUnfoldedBayes7 \
   --DoSelfNormalize true \
   --GenPrimaryMin 0 --GenPrimaryMax 14.999 \
   --WorldXMin 0 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.599 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
   --XLabel "Jet M" --YLabel "1/N dN/d(Jet M)" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

