Format = pdf

default: RunTest

Prepare:
	rm -f Input Systematics
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	mkdir -p Plots

RunTest: Execute
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominalCount.pdf --FinalOutput Plots/MeowPCount.$(Format) \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false \
		--WorldXMin 10 --WorldXMax 50 --WorldYMin 9000 --WorldYMax 500000 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "dN / d(Jet E)" --Binning "None" \
		--LegendX 0.2 --LegendY 0.5 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetENominal.root \
		--Systematic Systematics/DataJetE.root --Output Plots/DataJetENominal.pdf --FinalOutput Plots/MeowP.$(Format) \
		--PrimaryName HUnfoldedBayes17 \
		--DoSelfNormalize false --DoEventNormalize true --ExtraScale 1 \
		--WorldXMin 10 --WorldXMax 50 --WorldYMin 0.007 --WorldYMax 0.6 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet E (GeV)" --YLabel "1/N_{event} dN_{jet}/d(Jet E)" --Binning "None" \
		--LegendX 0.2 --LegendY 0.5 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.1,0.9,"Preliminary",0,0.1,0.85,"Anti-k_{T} jet R = 0.4",0,0.1,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetZGNominal.root \
		--Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZG.$(Format) \
		--PrimaryName HUnfoldedBayes7 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet E" \
		--LegendX 0.5 --LegendY 0.5 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetRGNominal.root \
		--Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRG.$(Format) \
		--PrimaryName HUnfoldedBayes9 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.7 \
		--WorldXMin 0 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet E" \
		--LegendX 0.5 --LegendY 0.5 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--Texts -1,0.76,0.9,"Preliminary",-1,0.76,0.85,"Anti-k_{T} jet R = 0.4",-1,0.76,0.8,"0.2 #pi < #theta_{jet} < 0.8 #pi" \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetZG2Nominal.root \
		--Systematic None --Output Plots/DataJetZG2Nominal.pdf --FinalOutput Plots/MeowZG2.$(Format) \
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
