Format = eps

default: RunTest

Prepare:
	rm -f Input Systematics
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	mkdir -p Plots

RunTest: RunJetE RunDiJetE RunDiJetSumE RunJetZG RunJetRG RunJetMG RunJetMGE RunJetM RunJetME RunConversion

RunJetE: Execute
	./Execute --Input Input/DataJetENominal.root \
		--Output Plots/DataJetENominal.pdf --FinalOutput Plots/MatrixP.$(Format) \
		--WorldXMin 0 --WorldXMax 70 --WorldYMin 0 --WorldYMax 46 --WorldZMin 0.0001 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 46 --RecoPrimaryMin 0 --RecoPrimaryMax 100 \
		--Primary "Jet E (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 505 --YAxis 505 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 5 --LogoX 0.75 --LogoY 0.22 --LogoW 0.12

RunDiJetE: Execute
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MatrixLeadingDiJet.$(Format) \
		--WorldXMin 0 --WorldXMax 70 --WorldYMin 0 --WorldYMax 46 --WorldZMin 0.0001 --WorldZMax 0.2 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 46 --RecoPrimaryMin 0 --RecoPrimaryMax 100 \
		--Primary "Jet E (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 505 --YAxis 505 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 5 --LogoX 0.75 --LogoY 0.22 --LogoW 0.12

RunDiJetSumE: Execute
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Output Plots/DataLeadingDiJetSumENominal.pdf --FinalOutput Plots/MatrixLeadingDiJetSum.$(Format) \
		--WorldXMin 25 --WorldXMax 140 --WorldYMin 25 --WorldYMax 92 --WorldZMin 0.0001 --WorldZMax 0.2 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin 0 --GenPrimaryMax 92 --RecoPrimaryMin 0 --RecoPrimaryMax 200 \
		--Primary "Leading Dijet Sum E (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 505 --YAxis 505 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 5 --LogoX 0.75 --LogoY 0.22 --LogoW 0.12

RunJetZG: Execute
	./Execute --Input Input/DataJetZGNominal.root \
		--Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MatrixZG.$(Format) \
		--WorldXMin -0.05 --WorldXMax 0.499 --WorldYMin -0.05 --WorldYMax 0.499 --WorldZMin 0.01 --WorldZMax 10 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin -0.05 --GenPrimaryMax 0.5 --RecoPrimaryMin -0.05 --RecoPrimaryMax 0.5 \
		--Primary "z_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 1 --LogoX 0.88 --LogoY 0.125 --LogoW 0.12

RunJetRG: Execute
	./Execute --Input Input/DataJetRGNominal.root \
		--Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MatrixRG.$(Format) \
		--WorldXMin -0.05 --WorldXMax 0.499 --WorldYMin -0.05 --WorldYMax 0.499 --WorldZMin 0.01 --WorldZMax 10 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin -0.05 --GenPrimaryMax 0.75 --RecoPrimaryMin -0.05 --RecoPrimaryMax 0.75 \
		--Primary "R_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 1 --LogoX 0.88 --LogoY 0.125 --LogoW 0.12

RunJetMG: Execute
	./Execute --Input Input/DataJetMGNominal.root \
		--Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/MatrixMG.$(Format) \
		--WorldXMin -0.1--WorldXMax 11.99 --WorldYMin -0.1 --WorldYMax 11.99 --WorldZMin 0.01 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin -0.1 --GenPrimaryMax 15 --RecoPrimaryMin -0.1 --RecoPrimaryMax 15 \
		--Primary "M_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 1 --LogoX 0.88 --LogoY 0.125 --LogoW 0.12

RunJetMGE: Execute
	./Execute --Input Input/DataJetMGENominal.root \
		--Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MatrixMGE.$(Format) \
		--WorldXMin -0.03 --WorldXMax 0.37 --WorldYMin -0.03 --WorldYMax 0.37 --WorldZMin 0.01 --WorldZMax 25 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin -0.03 --GenPrimaryMax 0.5 --RecoPrimaryMin -0.03 --RecoPrimaryMax 0.5 \
		--Primary "M_{G}/E" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 1 --LogoX 0.88 --LogoY 0.125 --LogoW 0.12

RunJetM: Execute
	./Execute --Input Input/DataJetMNominal.root \
		--Output Plots/DataJetMNominal.pdf --FinalOutput Plots/MatrixM.$(Format) \
		--WorldXMin 0 --WorldXMax 11.99 --WorldYMin 0 --WorldYMax 11.99 --WorldZMin 0.01 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 15 --RecoPrimaryMin 0 --RecoPrimaryMax 15 \
		--Primary "M" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 1 --LogoX 0.88 --LogoY 0.125 --LogoW 0.12

RunJetME: Execute
	./Execute --Input Input/DataJetMENominal.root \
		--Output Plots/DataJetMENominal.pdf --FinalOutput Plots/MatrixME.$(Format) \
		--WorldXMin 0 --WorldXMax 0.37 --WorldYMin 0 --WorldYMax 0.37 --WorldZMin 0.01 --WorldZMax 10 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 --RecoPrimaryMin 0 --RecoPrimaryMax 0.5 \
		--Primary "M/E" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 1 --LogoX 0.88 --LogoY 0.125 --LogoW 0.12

RunThrust: Execute
	./Execute --Input Input/DataNoCutThrustUniform.root \
		--Output Plots/DataThrustNominal.pdf --FinalOutput Plots/MatrixThrust.$(Format) \
		--WorldXMin 0.58 --WorldXMax 1 --WorldYMin 0.58 --WorldYMax 1 --WorldZMin 0.1 --WorldZMax 100 --LogZ true \
		--GenPrimaryMin 0.58 --GenPrimaryMax 1 --RecoPrimaryMin 0.58 --RecoPrimaryMax 1 \
		--Primary "Thrust" --Binning "None" --RowNormalize true \
		--XAxis 505 --YAxis 505 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1 \
		--CanvasScale 5 --LogoX 0.75 --LogoY 0.22 --LogoW 0.12

RunConversion:
	bash ConvertEPS.sh

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute


