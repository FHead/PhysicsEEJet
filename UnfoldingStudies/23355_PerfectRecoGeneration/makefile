
default: TestRun TestRunData TestRunDataRound2 TestRunDataRound3

ThrustRun: Execute
	./Execute --MC Input/MCThrustNominal.root --Yield Input/MCThrustNominal.root \
		--Output Output/PerfectThrustNominal.root
	./Execute --MC Input/MCThrustUniform.root --Yield Input/DataThrustUniform.root \
		--Gen ../23355_ThrustComparison/HEPData-ins636645-v1-Table54.root --GenHistogram "Table 54/Hist1D_y1" \
		--Output Output/PerfectHEPDataThrustUniform.root

TestRun: Execute
	./Execute --MC Input/MCJetPNominal.root --Yield Input/MCJetPNominal.root \
		--Output Output/PerfectJetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/MCJetZGNominal.root \
		--Output Output/PerfectJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/MCJetRGNominal.root \
		--Output Output/PerfectJetRGNominal.root

TestRunData: Execute
	./Execute --MC Input/MCJetPNominal.root --Yield Input/MCJetPNominal.root \
		--Gen UnfoldedInput/DataJetPNominal.root --GenHistogram HUnfoldedBayes2 \
		--Output Output/PerfectDataJetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/MCJetZGNominal.root \
		--Gen UnfoldedInput/DataJetZGNominal.root --GenHistogram HUnfoldedBayes2 \
		--Output Output/PerfectDataJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/MCJetRGNominal.root \
		--Gen UnfoldedInput/DataJetRGNominal.root --GenHistogram HUnfoldedBayes2 \
		--Output Output/PerfectDataJetRGNominal.root

TestRunDataRound2: Execute
	./Execute --MC Input/MCJetPNominal.root --Yield Input/MCJetPNominal.root \
		--Gen UnfoldedInput/DataJetPNominal.root --GenHistogram HUnfoldedBayes14 \
		--Output Output/PerfectDataRound2JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/MCJetZGNominal.root \
		--Gen UnfoldedInput/DataJetZGNominal.root --GenHistogram HUnfoldedBayes11 \
		--Output Output/PerfectDataRound2JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/MCJetRGNominal.root \
		--Gen UnfoldedInput/DataJetRGNominal.root --GenHistogram HUnfoldedBayes7 \
		--Output Output/PerfectDataRound2JetRGNominal.root

TestRunDataRound3: Execute
	./Execute --MC Input/MCJetPNominal.root --Yield Input/MCJetPNominal.root \
		--Gen UnfoldedInput/DataJetPNominal.root --GenHistogram HUnfoldedBayes44 \
		--Output Output/PerfectDataRound3JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/MCJetZGNominal.root \
		--Gen UnfoldedInput/DataJetZGNominal.root --GenHistogram HUnfoldedBayes23 \
		--Output Output/PerfectDataRound3JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/MCJetRGNominal.root \
		--Gen UnfoldedInput/DataJetRGNominal.root --GenHistogram HUnfoldedBayes16 \
		--Output Output/PerfectDataRound3JetRGNominal.root

TestRunDataRound4: Execute
	./Execute --MC Input/MCJetPNominal.root --Yield Input/MCJetPNominal.root \
		--Gen UnfoldedInput/DataJetPNominal.root --GenHistogram HUnfoldedBayes80 \
		--Output Output/PerfectDataRound4JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/MCJetZGNominal.root \
		--Gen UnfoldedInput/DataJetZGNominal.root --GenHistogram HUnfoldedBayes36 \
		--Output Output/PerfectDataRound4JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/MCJetRGNominal.root \
		--Gen UnfoldedInput/DataJetRGNominal.root --GenHistogram HUnfoldedBayes30 \
		--Output Output/PerfectDataRound4JetRGNominal.root

TestRunDataRound5: Execute
	./Execute --MC Input/MCJetPNominal.root --Yield Input/MCJetPNominal.root \
		--Gen UnfoldedInput/DataJetPNominal.root --GenHistogram HUnfoldedBayes100 \
		--Output Output/PerfectDataRound5JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/MCJetZGNominal.root \
		--Gen UnfoldedInput/DataJetZGNominal.root --GenHistogram HUnfoldedBayes50 \
		--Output Output/PerfectDataRound5JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/MCJetRGNominal.root \
		--Gen UnfoldedInput/DataJetRGNominal.root --GenHistogram HUnfoldedBayes44 \
		--Output Output/PerfectDataRound5JetRGNominal.root

TestRunDataRound6: Execute
	./Execute --MC Input/MCJetPNominal.root --Yield Input/MCJetPNominal.root \
		--Gen UnfoldedInput/DataJetPNominal.root --GenHistogram HUnfoldedBayes125 \
		--Output Output/PerfectDataRound6JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root --Yield Input/MCJetZGNominal.root \
		--Gen UnfoldedInput/DataJetZGNominal.root --GenHistogram HUnfoldedBayes60 \
		--Output Output/PerfectDataRound6JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root --Yield Input/MCJetRGNominal.root \
		--Gen UnfoldedInput/DataJetRGNominal.root --GenHistogram HUnfoldedBayes56 \
		--Output Output/PerfectDataRound6JetRGNominal.root

Execute: GeneratePerfectData.cpp
	CompileRootMacro GeneratePerfectData.cpp Execute
