#!/bin/bash

DoMOD=true
Format=eps
PYQUEN=MCPyquen


./Execute --Input Input/DataJetMGNominal.root \
   --Systematic Systematics/DataJetMGNormalized.root --Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/MeowMG.${Format} \
   --MCFile "Input/DataJetMGNominal.root","OriginalInput/MCPythia8JetMG.root","OriginalInput/MCHerwigJetMG.root",OriginalInput/MCSherpaJetMG.root,OriginalInput/${PYQUEN}JetMG.root \
   --MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
   --MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
   --PrimaryName HUnfoldedBayes16 \
   --DoSelfNormalize true \
   --GenPrimaryMin -0.1 --GenPrimaryMax 14.999 \
   --WorldXMin -0.1 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.5 --WorldRMin 0.45 --WorldRMax 1.75 --LogY false \
   --XLabel "Jet M_{G}" --YLabel "1/N dN/d(Jet M_{G})" --Binning "Jet E" \
   --LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
   --XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
   --Texts -1,0.76,0.9,"$Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
   --IgnoreGroup 2 --Row 2 --Column 4 \
   --DoMOD ${DoMOD} --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

