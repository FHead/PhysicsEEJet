DoMOD = true
Format = eps

default: RunTest Deploy

Prepare:
	rm -f OriginalInput Input Systematics JoaoInput FelixInput
	ln -sf ../23411_UnfoldingPreparation/Output OriginalInput
	ln -sf ../23412_ActualUnfold/Unfolded Input
	ln -sf ../23412_Systematics/ Systematics
	ln -sf ../23514_JoaoConversion/ JoaoInput
	ln -sf ../23472_LeadingDiJetStudies/Correction.dh .
	ln -sf ../23755_LeadingJetRecoCorrection/Step1Correction.dh .
	ln -fs ../24113_FelixResult/ FelixInput
	mkdir -p Plots Root

Deploy:
	mkdir -p ../FinalResult/UnfoldedFull/
	cp Plots/*.png ../FinalResult/UnfoldedFull/

PYQUEN = MCPyquen
# PYQUEN = MCPyquenStrong

RunTest: RunJetE RunDiJetE RunDiJetSumE RunJetZG RunJetRG RunJetMG RunJetMGE RunJetZG2 RunJetRG2 RunJetM RunJetME RunConversion

RunJetE: Execute
	bash RunJetE.sh

RunDiJetE: Execute
	bash RunDiJetE.sh

RunDiJetSumE: Execute
	bash RunDiJetSumE.sh

RunJetZG: Execute
	bash RunJetZG.sh

RunJetRG: Execute
	bash RunJetRG.sh

RunJetMG: Execute
	bash RunJetMG.sh

RunJetMGE: Execute
	bash RunJetMGE.sh

RunJetZG2: Execute
	bash RunJetZG2.sh

RunJetRG2: Execute
	bash RunJetRG2.sh

RunJetM: Execute
	bash RunJetM.sh

RunJetME: Execute
	bash RunJetME.sh

RunConversion:
	bash ConvertEPS.sh

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute
