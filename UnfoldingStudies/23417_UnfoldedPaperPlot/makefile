Format = pdf

default: RunTest

Prepare:
	rm -f OriginalInput Input Systematics
	ln -sf ../23411_UnfoldingPreparation/Output OriginalInput
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	mkdir -p Plots

RunTest: Execute
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominalCount.pdf --FinalOutput Plots/MeowPCount.$(Format) \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 9000 --WorldYMax 500000 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "dN / d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.4 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowPLog.$(Format) \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.5 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowP.$(Format) \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.4 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MeowLeadingDiJetE.$(Format) \
		--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.45 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetZGNominal.root \
		--Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZG.$(Format) \
		--MCFile "Input/DataJetZGNominal.root","OriginalInput/MCPythia8JetZG.root","OriginalInput/MCHerwigJetZG.root",OriginalInput/MCSherpaJetZG.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.5 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetRGNominal.root \
		--Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRG.$(Format) \
		--MCFile "Input/DataJetRGNominal.root","OriginalInput/MCPythia8JetRG.root","OriginalInput/MCHerwigJetRG.root",OriginalInput/MCSherpaJetRG.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA" \
		--PrimaryName HUnfoldedBayes9 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.7 \
		--WorldXMin 0 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
		--LegendX 0.5 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetMGNominal.root \
		--Systematic Systematics/DataJetMGNormalized.root --Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/MeowMG.$(Format) \
		--MCFile "Input/DataJetMGNominal.root","OriginalInput/MCPythia8JetMG.root","OriginalInput/MCHerwigJetMG.root",OriginalInput/MCSherpaJetMG.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA" \
		--PrimaryName HUnfoldedBayes9 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.1 --GenPrimaryMax 14.999 \
		--WorldXMin -0.1 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.5 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M_{G}" --YLabel "1/N dN/d(Jet M_{G})" --Binning "Jet E" \
		--LegendX 0.5 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetMGENominal.root \
		--Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MeowMGE.$(Format) \
		--MCFile "Input/DataJetMGENominal.root","OriginalInput/MCPythia8JetMGE.root","OriginalInput/MCHerwigJetMGE.root",OriginalInput/MCSherpaJetMGE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA" \
		--PrimaryName HUnfoldedBayes9 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
		--LegendX 0.5 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetZG2Nominal.root \
		--Systematic None --Output Plots/DataJetZG2Nominal.pdf --FinalOutput Plots/MeowZG2.$(Format) \
		--MCFile Input/DataJetZG2Nominal.root \
		--MCHistogram HMCTruth \
		--MCLabel "PYTHIA 6" \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.5 --LegendY 0.5 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetRG2Nominal.root \
		--Systematic None --Output Plots/DataJetRG2Nominal.pdf --FinalOutput Plots/MeowRG2.$(Format) \
		--MCFile Input/DataJetRG2Nominal.root \
		--MCHistogram HMCTruth \
		--MCLabel "PYTHIA 6" \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.7 \
		--WorldXMin 0 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
		--LegendX 0.5 --LegendY 0.5 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4
	# cp -f Plots/Meow*.pdf ~/WindowsHome/Downloads/

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
