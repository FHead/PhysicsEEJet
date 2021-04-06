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
		--WorldXMin 0 --WorldXMax 70 --WorldYMin 0 --WorldYMax 50 --WorldZMin 0.0001 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 50 --RecoPrimaryMin 0 --RecoPrimaryMax 100 \
		--Primary "Jet E (GeV)" --Binning "None" --RowNormalize true \
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
	# cp -f Plots/Meow*.pdf ~/WindowsHome/Downloads/

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
