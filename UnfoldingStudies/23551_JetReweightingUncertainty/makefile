

default: TestRun

Prepare:
	ln -sf ../23551_JetReweighting/Reweight.dh .
	ln -sf ../23514_JetResponseClustering/MCPythia8.root .
	ln -sf ../23411_UnfoldingPreparation/Output Binning

Execute: CalculateUncertainty.cpp
	CompileRootMacro CalculateUncertainty.cpp Execute

TestRun: Execute
	./Execute --Input MCPythia8.root \
		--LeadingDiJetSum false \
		--Binning Binning/DataLeadingDiJetENominal.root \
		--Reweight Reweight.dh --State NominalReweight \
		--OutputBase LeadingDiJetE
	./Execute --Input MCPythia8.root \
		--LeadingDiJetSum true \
		--Binning Binning/DataLeadingDiJetSumENominal.root \
		--Reweight Reweight.dh --State NominalReweight \
		--OutputBase LeadingDiJetSumE




