Format = eps
DoMOD  = true
GroupX = 7,8,9
GroupY = 7,8

default: RunTest

Prepare:
	rm -f Input Systematics
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	mkdir -p Plots

Deploy:
	mkdir -p ../FinalResult/SmearingMatrixPartial
	cp Plots/*png ../FinalResult/SmearingMatrixPartial

RunTest: RunJetZG RunJetRG RunJetMG RunJetMGE RunJetM RunJetME RunConversion

RunJetZG: Execute
	./Execute --Input Input/DataJetZGNominal.root \
		--Output Plots/DataJetZGNominal.pdf --FinalOutput Plots/PartialMatrixZG.$(Format) \
		--WorldXMin -0.05 --WorldXMax 0.499 --WorldYMin -0.05 --WorldYMax 0.499 --WorldZMin 0.01 --WorldZMax 10 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin -0.05 --GenPrimaryMax 0.5 --RecoPrimaryMin -0.05 --RecoPrimaryMax 0.5 \
		--Primary "z_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX $(GroupX) --GroupY $(GroupY) --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.88 --LogoY 0.963 --LogoW 0.1

RunJetRG: Execute
	./Execute --Input Input/DataJetRGNominal.root \
		--Output Plots/DataJetRGNominal.pdf --FinalOutput Plots/PartialMatrixRG.$(Format) \
		--WorldXMin -0.05 --WorldXMax 0.499 --WorldYMin -0.05 --WorldYMax 0.499 --WorldZMin 0.01 --WorldZMax 10 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin -0.05 --GenPrimaryMax 0.75 --RecoPrimaryMin -0.05 --RecoPrimaryMax 0.75 \
		--Primary "R_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX $(GroupX) --GroupY $(GroupY) --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.88 --LogoY 0.963 --LogoW 0.1

RunJetMG: Execute
	./Execute --Input Input/DataJetMGNominal.root \
		--Output Plots/DataJetMGNominal.pdf --FinalOutput Plots/PartialMatrixMG.$(Format) \
		--WorldXMin -0.1--WorldXMax 11.99 --WorldYMin -0.1 --WorldYMax 11.99 --WorldZMin 0.01 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin -0.1 --GenPrimaryMax 15 --RecoPrimaryMin -0.1 --RecoPrimaryMax 15 \
		--Primary "M_{G}" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX $(GroupX) --GroupY $(GroupY) --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.88 --LogoY 0.963 --LogoW 0.1

RunJetMGE: Execute
	./Execute --Input Input/DataJetMGENominal.root \
		--Output Plots/DataJetMGENominal.pdf --FinalOutput Plots/PartialMatrixMGE.$(Format) \
		--WorldXMin -0.03 --WorldXMax 0.37 --WorldYMin -0.03 --WorldYMax 0.37 --WorldZMin 0.01 --WorldZMax 25 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin -0.03 --GenPrimaryMax 0.5 --RecoPrimaryMin -0.03 --RecoPrimaryMax 0.5 \
		--Primary "M_{G}/E" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX $(GroupX) --GroupY $(GroupY) --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.88 --LogoY 0.963 --LogoW 0.1

RunJetM: Execute
	./Execute --Input Input/DataJetMNominal.root \
		--Output Plots/DataJetMNominal.pdf --FinalOutput Plots/PartialMatrixM.$(Format) \
		--WorldXMin 0 --WorldXMax 11.99 --WorldYMin 0 --WorldYMax 11.99 --WorldZMin 0.01 --WorldZMax 1 --LogZ true \
		--GenPrimaryMin 0 --GenPrimaryMax 15 --RecoPrimaryMin 0 --RecoPrimaryMax 15 \
		--Primary "M" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX $(GroupX) --GroupY $(GroupY) --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.88 --LogoY 0.963 --LogoW 0.1

RunJetME: Execute
	./Execute --Input Input/DataJetMENominal.root \
		--Output Plots/DataJetMENominal.pdf --FinalOutput Plots/PartialMatrixME.$(Format) \
		--WorldXMin 0 --WorldXMax 0.37 --WorldYMin 0 --WorldYMax 0.37 --WorldZMin 0.01 --WorldZMax 10 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin 0 --GenPrimaryMax 0.5 --RecoPrimaryMin 0 --RecoPrimaryMax 0.5 \
		--Primary "M/E" --Binning "Jet E" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX $(GroupX) --GroupY $(GroupY) --Row 1 --Column 1 \
		--DoMOD $(DoMOD) --CanvasScale 4 --LogoX 0.88 --LogoY 0.963 --LogoW 0.1

RunConversion:
	bash ConvertEPS.sh

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute


