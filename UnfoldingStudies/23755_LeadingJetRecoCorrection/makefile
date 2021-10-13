
default: Prepare TestRun

Prepare:
	ln -sf ../23411_UnfoldingPreparation/Output/ Input

Execute: MakePlots.cpp
	CompileRootMacro MakePlots.cpp Execute

TestRun: Execute
	./Execute --GenPass "Input/MCPythia6LeadingDiJetE.root" \
		--BothPass "Input/MCLeadingDiJetENominal.root" \
		--Output "Step1LeadingDiJetE.pdf" \
		--DHFile "Step1Correction.dh" \
		--State "LeadingDiJetE"
	./Execute --GenPass "Input/MCPythia6LeadingDiJetSumE.root" \
		--BothPass "Input/MCLeadingDiJetSumENominal.root" \
		--Output "Step1LeadingDiJetSumE.pdf" \
		--DHFile "Step1Correction.dh" \
		--State "LeadingDiJetSumE"


