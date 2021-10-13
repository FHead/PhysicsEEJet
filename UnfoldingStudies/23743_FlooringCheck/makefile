DoMOD = true
Format = eps

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

RunTest: RunJetE RunDiJetE RunDiJetSumE RunJetZG RunJetRG RunJetMGE RunJetME RunConversion

RunJetE: Execute
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowE.$(Format) \
		--MCFile Input/DataJetETighter.root,Input/DataJetEFloored.root \
		--MCHistogram HUnfoldedBayes17,HUnfoldedBayes17 \
		--MCLabel "Tighter","Floored" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.35 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.35 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunDiJetE: Execute
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Systematic Systematics/DataLeadingDiJetE.root --Output Plots/DataLeadingDiJetENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetECorrected.$(Format) \
		--MCFile Input/DataLeadingDiJetETighter.root,Input/DataLeadingDiJetEFloored.root \
		--MCHistogram HUnfoldedBayes7,HUnfoldedBayes7 \
		--MCLabel "Tighter","Floored" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 46 \
		--WorldXMin 10 --WorldXMax 46 --WorldYMin 0 --WorldYMax 0.21 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetJetE \
		--MCCorrection true,true,true,true,true \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunDiJetSumE: Execute
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Systematic Systematics/DataLeadingDiJetSumE.root --Output Plots/DataLeadingDiJetSumENominalCorrected.pdf --FinalOutput Plots/MeowLeadingDiJetSumECorrected.$(Format) \
		--MCFile Input/DataLeadingDiJetSumETighter.root,Input/DataLeadingDiJetSumEFloored.root \
		--MCHistogram HUnfoldedBayes15,HUnfoldedBayes15 \
		--MCLabel "Tighter","Floored" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--GenPrimaryMin 0 --GenPrimaryMax 92 \
		--WorldXMin 24 --WorldXMax 92 --WorldYMin 0 --WorldYMax 0.06 --WorldRMin 0.51 --WorldRMax 1.49 --LogY false \
		--XLabel "Leading dijet sum E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Leading dijet sum E)" --Binning "None" \
		--LegendX 0.15 --LegendY 0.25 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",0,0.1,0.75,"Leading dijet" \
		--IgnoreGroup 0 --Row 1 --Column 1 \
		--CorrectionFile Correction.dh --CorrectionState DijetSumE \
		--MCCorrection true,true,true,true,true \
		--DoMOD $(DoMOD) --CanvasScale 10 --LogoX 0.55 --LogoY 0.87 --LogoW 0.12

RunJetZG: Execute
	./Execute --Input Input/DataJetZGNominal.root \
		--Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZG.$(Format) \
		--MCFile Input/DataJetZGTighter.root,Input/DataJetZGFloored.root \
		--MCHistogram HUnfoldedBayes17,HUnfoldedBayes17 \
		--MCLabel "Tighter","Floored" \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.8 --WorldRMax 1.18 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 305 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetRG: Execute
	./Execute --Input Input/DataJetRGNominal.root \
		--Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRG.$(Format) \
		--MCFile Input/DataJetRGTighter.root,Input/DataJetRGFloored.root \
		--MCHistogram HUnfoldedBayes8,HUnfoldedBayes8 \
		--MCLabel "Tighter","Floored" \
		--PrimaryName HUnfoldedBayes8 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.015 --GenPrimaryMax 0.75 \
		--WorldXMin -0.015 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetMGE: Execute
	./Execute --Input Input/DataJetMGENominal.root \
		--Systematic Systematics/DataJetMGENormalized.root --Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MeowMGE.$(Format) \
		--MCFile Input/DataJetMGETighter.root,Input/DataJetMGEFloored.root \
		--MCHistogram HUnfoldedBayes16,HUnfoldedBayes16 \
		--MCLabel "Tighter","Floored" \
		--PrimaryName HUnfoldedBayes16 \
		--DoSelfNormalize true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 \
		--WorldXMin -0.01 --WorldXMax 0.5 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M_{G}/E" --YLabel "1/N dN/d(Jet M_{G}/E)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi",-1,0.76,0.75,"z_{cut} = 0.1 #beta = 0.0" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunJetME: Execute
	./Execute --Input Input/DataJetMENominal.root \
		--Systematic Systematics/DataJetMENormalized.root --Output Plots/DataJetMENominal.pdf --FinalOutput Plots/MeowME.$(Format) \
		--MCFile Input/DataJetMETighter.root,Input/DataJetMEFloored.root \
		--MCHistogram HUnfoldedBayes7,HUnfoldedBayes7 \
		--MCLabel "Tighter","Floored" \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.499 --WorldYMin 0 --WorldYMax 12 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet M/E" --YLabel "1/N dN/d(Jet M/E)" --Binning "Jet E" \
		--LegendX 0.48 --LegendY 0.4 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4 \
		--DoMOD $(DoMOD) --CanvasScale 2 --LogoX 0.85 --LogoY 0.57 --LogoW 0.08

RunConversion:
	bash ConvertEPS.sh

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
