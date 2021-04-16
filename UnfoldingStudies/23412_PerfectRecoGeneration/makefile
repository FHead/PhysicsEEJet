
default: ThrustRun TestRun TestRunData

Prepare:
	mkdir -p Output
	rm -f Input UnfoldedInput
	ln -sf ../23411_UnfoldingPreparation/Output Input
	ln -sf ../23412_ActualUnfold/Unfolded UnfoldedInput

ThrustRun: Execute
	./Execute --MC Input/MCThrustNominal.root --Yield Input/MCThrustNominal.root \
		--Output Output/PerfectThrustNominal.root
	./Execute --MC Input/MCThrustUniform.root --Yield Input/DataThrustUniform.root \
		--Gen ../23355_ThrustComparison/HEPData-ins636645-v1-Table54.root --GenHistogram "Table 54/Hist1D_y1" \
		--Output Output/PerfectHEPDataThrustUniform.root

TestRun: Execute
	./Execute --MC Input/MCJetENominal.root --Yield Input/MCJetENominal.root \
		--Output Output/PerfectJetENominal.root
	./Execute --MC Input/MCLeadingDiJetENominal.root --Yield Input/MCLeadingDiJetENominal.root \
		--Output Output/PerfectLeadingDiJetENominal.root
	./Execute --MC Input/MCLeadingDiJetSumENominal.root --Yield Input/MCLeadingDiJetSumENominal.root \
		--Output Output/PerfectLeadingDiJetSumENominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/MCJetZGNominal.root \
		--Output Output/PerfectJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/MCJetRGNominal.root \
		--Output Output/PerfectJetRGNominal.root
	./Execute --MC Input/MCJetMGNominal.root --Yield Input/MCJetMGNominal.root \
		--Output Output/PerfectJetMGNominal.root
	./Execute --MC Input/MCJetMGENominal.root --Yield Input/MCJetMGENominal.root \
		--Output Output/PerfectJetMGENominal.root
	./Execute --MC Input/MCJetMNominal.root --Yield Input/MCJetMNominal.root \
		--Output Output/PerfectJetMNominal.root
	./Execute --MC Input/MCJetMENominal.root --Yield Input/MCJetMENominal.root \
		--Output Output/PerfectJetMENominal.root

TestRunData: Execute
	./Execute --MC Input/MCJetENominal.root --Yield Input/DataJetENominal.root \
		--Gen UnfoldedInput/DataJetENominal.root --GenHistogram HUnfoldedBayes2 \
		--Output Output/PerfectDataJetENominal.root
	./Execute --MC Input/MCLeadingDiJetENominal.root --Yield Input/DataLeadingDiJetENominal.root \
		--Gen UnfoldedInput/DataLeadingDiJetENominal.root --GenHistogram HUnfoldedBayes1 \
		--Output Output/PerfectDataLeadingDiJetENominal.root
	./Execute --MC Input/MCLeadingDiJetSumENominal.root --Yield Input/DataLeadingDiJetSumENominal.root \
		--Gen UnfoldedInput/DataLeadingDiJetSumENominal.root --GenHistogram HUnfoldedBayes1 \
		--Output Output/PerfectDataLeadingDiJetSumENominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/DataJetZGNominal.root \
		--Gen UnfoldedInput/DataJetZGNominal.root --GenHistogram HUnfoldedBayes6 \
		--Output Output/PerfectDataJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/DataJetRGNominal.root \
		--Gen UnfoldedInput/DataJetRGNominal.root --GenHistogram HUnfoldedBayes2 \
		--Output Output/PerfectDataJetRGNominal.root
	./Execute --MC Input/MCJetMGNominal.root --Yield Input/DataJetMGNominal.root \
		--Gen UnfoldedInput/DataJetMGNominal.root --GenHistogram HUnfoldedBayes3 \
		--Output Output/PerfectDataJetMGNominal.root
	./Execute --MC Input/MCJetMGENominal.root --Yield Input/DataJetMGENominal.root \
		--Gen UnfoldedInput/DataJetMGENominal.root --GenHistogram HUnfoldedBayes2 \
		--Output Output/PerfectDataJetMGENominal.root
	./Execute --MC Input/MCJetMNominal.root --Yield Input/DataJetMNominal.root \
		--Gen UnfoldedInput/DataJetMNominal.root --GenHistogram HUnfoldedBayes2 \
		--Output Output/PerfectDataJetMNominal.root
	./Execute --MC Input/MCJetMENominal.root --Yield Input/DataJetMENominal.root \
		--Gen UnfoldedInput/DataJetMENominal.root --GenHistogram HUnfoldedBayes2 \
		--Output Output/PerfectDataJetMENominal.root

Execute: GeneratePerfectData.cpp
	CompileRootMacro GeneratePerfectData.cpp Execute
