
default: Prepare TestRun

Prepare:
	ln -sf ../23472_LeadingDiJetStudies/Correction.dh .
	ln -sf ../23411_UnfoldingPreparation/Output Input

Execute: CalculateUncertainty.cpp
	CompileRootMacro CalculateUncertainty.cpp Execute

TestRun: Execute
	./Execute --Input Correction.dh --State DijetJetE \
		--Binning Input/DataLeadingDiJetENominal.root \
		--Output DijetJetE.root
	./Execute --Input Correction.dh --State DijetSumE \
		--Binning Input/DataLeadingDiJetSumENominal.root \
		--Output DijetSumE.root



