
default: RunTest

RunTest: Execute
	./Execute --Input Input/DataJetPNominal.root \
		--Systematic Systematics/DataJetP.root --Output Plots/DataJetPNominal.pdf --FinalOutput Plots/MeowP.pdf \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize false \
		--WorldXMin 10 --WorldXMax 50 --WorldYMin 1000 --WorldYMax 500000 --WorldRMin 0.51 --WorldRMax 1.49 --LogY true \
		--XLabel "Jet P (GeV)" --YLabel "dN / d(Jet P)" --Binning "None" \
		--LegendX 0.2 --LegendY 0.2 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetZGNominal.root \
		--Systematic Systematics/DataJetZGNormalized.root --Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MeowZG.pdf \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet P" \
		--LegendX 0.5 --LegendY 0.5 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetRGNominal.root \
		--Systematic Systematics/DataJetRGNormalized.root --Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MeowRG.pdf \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.7 \
		--WorldXMin 0 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet P" \
		--LegendX 0.5 --LegendY 0.5 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetZG2Nominal.root \
		--Systematic None --Output Plots/DataJetZG2Nominal.pdf --FinalOutput Plots/MeowZG2.pdf \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 7 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet z_{G}" --YLabel "1/N dN/d(Jet z_{G})" --Binning "Jet P" \
		--LegendX 0.5 --LegendY 0.5 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--IgnoreGroup 2 --Row 2 --Column 4
	./Execute --Input Input/DataJetRG2Nominal.root \
		--Systematic None --Output Plots/DataJetRG2Nominal.pdf --FinalOutput Plots/MeowRG2.pdf \
		--PrimaryName HUnfoldedBayes14 \
		--DoSelfNormalize true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.7 \
		--WorldXMin 0 --WorldXMax 0.7 --WorldYMin 0 --WorldYMax 9 --WorldRMin 0.76 --WorldRMax 1.34 --LogY false \
		--XLabel "Jet R_{G}" --YLabel "1/N dN/d(Jet R_{G})" --Binning "Jet P" \
		--LegendX 0.5 --LegendY 0.5 --LegendSize 0.075 \
		--XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1.25 \
		--IgnoreGroup 2 --Row 2 --Column 4
	cp Plots/Meow*.pdf ~/WindowsHome/Downloads/

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
