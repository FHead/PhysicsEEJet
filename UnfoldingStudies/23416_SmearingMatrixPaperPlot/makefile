Format = pdf

default: RunTest

Prepare:
	rm -f Input Systematics
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	mkdir -p Plots

RunTest: Execute
	./Execute --Input Input/DataJetENominal.root \
		--Output Plots/DataJetENominal.pdf --FinalOutput Plots/MatrixP.$(Format) \
		--WorldXMin 0 --WorldXMax 70 --WorldYMin 0 --WorldYMax 46 --WorldZMin 0.0001 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 46 --RecoPrimaryMin 0 --RecoPrimaryMax 100 \
		--Primary "Jet E (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 505 --YAxis 505 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1
	./Execute --Input Input/DataLeadingDiJetENominal.root \
		--Output Plots/DataLeadingDiJetENominal.pdf --FinalOutput Plots/MatrixLeadingDiJet.$(Format) \
		--WorldXMin 0 --WorldXMax 70 --WorldYMin 0 --WorldYMax 46 --WorldZMin 0.0001 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 46 --RecoPrimaryMin 0 --RecoPrimaryMax 100 \
		--Primary "Jet E (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 505 --YAxis 505 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1
	./Execute --Input Input/DataLeadingDiJetSumENominal.root \
		--Output Plots/DataLeadingDiJetSumENominal.pdf --FinalOutput Plots/MatrixLeadingDiJetSum.$(Format) \
		--WorldXMin 25 --WorldXMax 140 --WorldYMin 25 --WorldYMax 92 --WorldZMin 0.0001 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 92 --RecoPrimaryMin 0 --RecoPrimaryMax 200 \
		--Primary "Leading Dijet Sum E (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 505 --YAxis 505 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetZGNominal.root \
		--Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/MatrixZG.$(Format) \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 0.4999 --WorldZMin 0.01 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 --RecoPrimaryMin 0 --RecoPrimaryMax 0.5 \
		--Primary "z_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetRGNominal.root \
		--Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/MatrixRG.$(Format) \
		--WorldXMin 0 --WorldXMax 0.4999 --WorldYMin 0 --WorldYMax 0.4999 --WorldZMin 0.01 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 --RecoPrimaryMin 0 --RecoPrimaryMax 0.5 \
		--Primary "R_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetMGNominal.root \
		--Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/MatrixMG.$(Format) \
		--WorldXMin 0 --WorldXMax 11.999 --WorldYMin 0 --WorldYMax 11.999 --WorldZMin 0.01 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin -0.1 --GenPrimaryMax 15 --RecoPrimaryMin -0.1 --RecoPrimaryMax 15 \
		--Primary "M_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1
	./Execute --Input Input/DataJetMGENominal.root \
		--Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/MatrixMGE.$(Format) \
		--WorldXMin 0 --WorldXMax 0.37 --WorldYMin 0 --WorldYMax 0.37 --WorldZMin 0.01 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin -0.01 --GenPrimaryMax 0.5 --RecoPrimaryMin -0.01 --RecoPrimaryMax 0.5 \
		--Primary "M_{G}/E" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--IgnoreGroupRow 0 --IgnoreGroupColumn 0 --Row 1 --Column 1
	# cp -f Plots/Meow*.pdf ~/WindowsHome/Downloads/

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
