DoMOD = false
Group = --Group 2,8 --Row 1 --Column 2

default: RunTest

Prepare:
	rm -f OriginalInput Input Systematics
	ln -sf ../23411_UnfoldingPreparation/Output OriginalInput
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	ln -sf ../23514_JoaoConversion/ JoaoInput
	ln -sf ../23472_LeadingDiJetStudies/Correction.dh .
	mkdir -p Plots

PYQUEN = MCPyquen
# PYQUEN = MCPyquenStrong

# RunTest: RunJetE RunDiJetE RunDiJetSumE RunJetZG RunJetRG RunJetMG RunJetMGE RunJetZG2 RunJetRG2 RunJetM RunJetME RunConversion
RunTest: RunJetZG RunConversion

RunJetE: Execute
	# Jet E: Count
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominalCount.pdf --FinalOutput Plots/MeowECount.eps \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/$(PYQUEN)JetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 722","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 9000 --WorldYMax 500000 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "dN / d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--Group 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Jet E: Normalized
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowELog.eps \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/$(PYQUEN)JetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.5 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--Group 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Jet E: Normalized - log
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowE.eps \
		--MCFile "Input/DataJetENominal.root","OriginalInput/MCPythia8JetE.root","OriginalInput/MCHerwigJetE.root",OriginalInput/MCSherpaJetE.root,OriginalInput/$(PYQUEN)JetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--Group 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# Jet E: Normalized, Joao comparison
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowELogJoao.eps \
		--MCFile "JoaoInput/GraphsNLO.root","JoaoInput/GraphsNLO.root","Input/DataJetENominal.root" \
		--MCHistogram GSys,GStat,HMCTruth \
		--MCLabel "NLO Scale","NLO Stat","PYTHIA 6" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0.015 --WorldYMax 0.75 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--Group 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunDiJetE: Execute
	# DiJet E
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MeowLeadingDiJetE.eps \
		--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/$(PYQUEN)LeadingDiJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.21 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--Group 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet E: log
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MeowLeadingDiJetELog.eps \
		--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/$(PYQUEN)LeadingDiJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0.000000004 --WorldYMax 6 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.45 --LegendY 0.10 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--Group 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet E Corr
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetECorrected.eps \
		--MCFile "Input/DataLeadingDiJetENominal.root","OriginalInput/MCPythia8LeadingDiJetE.root","OriginalInput/MCHerwigLeadingDiJetE.root",OriginalInput/MCSherpaLeadingDiJetE.root,OriginalInput/$(PYQUEN)LeadingDiJetE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.21 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--Group 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetJetE \
		--MCCorrection true,true,true,true,true \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunDiJetSumE: Execute
	# DiJet SumE
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominal.pdf --FinalOutput Plots/MeowLeadingDiJetSumE.eps \
		--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/$(PYQUEN)LeadingDiJetSumE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 92 \
		--WorldXMin 24 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.06 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--Group 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet SumE: log
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominal.pdf --FinalOutput Plots/MeowLeadingDiJetSumELog.eps \
		--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/$(PYQUEN)LeadingDiJetSumE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes16 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 92 \
		--WorldXMin 24 --WorldXMax 92 --WorldYMin 0.000000004 --WorldYMax 0.6 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)" --Binning "None" \
		--LegendX 0.45 --LegendY 0.10 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--Group 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12
	# DiJet SumE corrected
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetSumECorrected.eps \
		--MCFile "Input/DataLeadingDiJetSumENominal.root","OriginalInput/MCPythia8LeadingDiJetSumE.root","OriginalInput/MCHerwigLeadingDiJetSumE.root",OriginalInput/MCSherpaLeadingDiJetSumE.root,OriginalInput/$(PYQUEN)LeadingDiJetSumE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 92 \
		--WorldXMin 24 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.06 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--Group 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetSumE \
		--MCCorrection true,true,true,true,true \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunJetZG: Execute
	./Execute --Input Input/DataJetZGNominal.root \
		--Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZG.eps \
		--MCFile "OriginalInput/DataJetZGNominal.root","OriginalInput/MCPythia8JetZG.root","OriginalInput/MCHerwigJetZG.root",OriginalInput/MCSherpaJetZG.root,OriginalInput/$(PYQUEN)JetZG.root \
		--MCHistogram HMCGen,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		$(Group) \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetRG: Execute
	./Execute --Input Input/DataJetRGNominal.root \
		--Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRG.eps \
		--MCFile "Input/DataJetRGNominal.root","OriginalInput/MCPythia8JetRG.root","OriginalInput/MCHerwigJetRG.root",OriginalInput/MCSherpaJetRG.root,OriginalInput/$(PYQUEN)JetRG.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes8 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
		--WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		$(Group) \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetMG: Execute
	./Execute --Input Input/DataJetMGNominal.root \
		--Systematic Systematics/DataJetMGNormalized.root --Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/MeowMG.eps \
		--MCFile "Input/DataJetMGNominal.root","OriginalInput/MCPythia8JetMG.root","OriginalInput/MCHerwigJetMG.root",OriginalInput/MCSherpaJetMG.root,OriginalInput/$(PYQUEN)JetMG.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes16 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.1 --GenPrimaryMax 14.999 \
		--WorldXMin -0.1 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.5 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M_{G}" --YLabel "1/N dN/d(Jet M_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		$(Group) \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetMGE: Execute
	./Execute --Input Input/DataJetMGENominal.root \
		--Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MeowMGE.eps \
		--MCFile "Input/DataJetMGENominal.root","OriginalInput/MCPythia8JetMGE.root","OriginalInput/MCHerwigJetMGE.root",OriginalInput/MCSherpaJetMGE.root,OriginalInput/$(PYQUEN)JetMGE.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes16 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		$(Group) \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetZG2: Execute
	./Execute --Input Input/DataJetZG2Nominal.root \
		--Systematic None --Output Plots/DataJetZG2Nominal.pdf --FinalOutput Plots/MeowZG2.eps \
		--MCFile "Input/DataJetZG2Nominal.root","OriginalInput/MCPythia8JetZG2.root","OriginalInput/MCHerwigJetZG2.root",OriginalInput/MCSherpaJetZG2.root,OriginalInput/$(PYQUEN)JetZG2.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.015 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.5 #beta = 1.5" \
		$(Group) \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetRG2: Execute
	./Execute --Input Input/DataJetRG2Nominal.root \
		--Systematic None --Output Plots/DataJetRG2Nominal.pdf --FinalOutput Plots/MeowRG2.eps \
		--MCFile "Input/DataJetRG2Nominal.root","OriginalInput/MCPythia8JetRG2.root","OriginalInput/MCHerwigJetRG2.root",OriginalInput/MCSherpaJetRG2.root,OriginalInput/$(PYQUEN)JetRG2.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
		--WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.5 #beta = 1.5" \
		$(Group) \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetM: Execute
	./Execute --Input Input/DataJetMNominal.root \
		--Systematic Systematics/DataJetMNormalized.root --Output Plots/DataJetMNominal.pdf --FinalOutput Plots/MeowM.eps \
		--MCFile "Input/DataJetMNominal.root","OriginalInput/MCPythia8JetM.root","OriginalInput/MCHerwigJetM.root",OriginalInput/MCSherpaJetM.root,OriginalInput/$(PYQUEN)JetM.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 14.999 \
		--WorldXMin 0 --WorldXMax 14.999 --WorldYMin 0 --WorldYMax 0.599 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M" --YLabel "1/N dN/d(Jet M)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		$(Group) \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetME: Execute
	./Execute --Input Input/DataJetMENominal.root \
		--Systematic Systematics/DataJetMENormalized.root --Output Plots/DataJetMENominal.pdf --FinalOutput Plots/MeowME.eps \
		--MCFile "Input/DataJetMENominal.root","OriginalInput/MCPythia8JetME.root","OriginalInput/MCHerwigJetME.root",OriginalInput/MCSherpaJetME.root,OriginalInput/$(PYQUEN)JetME.root \
		--MCHistogram HMCTruth,HMCGen,HMCGen,HMCGen,HMCGen \
		--MCLabel "PYTHIA 6","PYTHIA 8","HERWIG 7","SHERPA","PYQUEN" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 12 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M/E" --YLabel "1/N dN/d(Jet M/E)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		$(Group) \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunConversion:
	bash ConvertEPS.sh

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
