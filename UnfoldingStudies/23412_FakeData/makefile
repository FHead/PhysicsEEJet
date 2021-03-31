
default: TestRun TestRunThrust TestRunData TestRunStatistics

TestRunThrust: Execute
	./Execute --MC Input/MCThrustNominal.root \
		--Shape PerfectInput/PerfectThrustNominal.root \
		--Yield Input/MCThrustNominal.root \
		--Output Output/ToyMCThrustNominal.root

TestRun: Execute
	./Execute --MC Input/MCJetENominal.root \
		--Shape PerfectInput/PerfectJetENominal.root \
		--Yield Input/DataJetENominal.root \
		--Output Output/ToyJetENominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectJetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectJetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyJetRGNominal.root

TestRunStatistics: Execute
	for i in `seq 1001 1250`; do \
		echo $$i; \
		./Execute --MC Input/MCJetENominal.root \
			--Shape PerfectInput/PerfectDataJetENominal.root \
			--Yield Input/DataJetENominal.root \
			--Seed $$i \
			--Output Output/ToyDataJetEStatistics_$${i}.root; \
		./Execute --MC Input/MCJetZGNominal.root \
			--Shape PerfectInput/PerfectDataJetZGNominal.root \
			--Yield Input/DataJetZGNominal.root \
			--Seed $$i \
			--Output Output/ToyDataJetZGStatistics_$${i}.root; \
		./Execute --MC Input/MCJetRGNominal.root \
			--Shape PerfectInput/PerfectDataJetRGNominal.root \
			--Yield Input/DataJetRGNominal.root \
			--Seed $$i \
			--Output Output/ToyDataJetRGStatistics_$${i}.root; \
	done

TestRunData: Execute
	./Execute --MC Input/MCJetENominal.root \
		--Shape PerfectInput/PerfectDataJetENominal.root \
		--Yield Input/DataJetENominal.root \
		--Output Output/ToyDataJetENominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectDataJetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyDataJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectDataJetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyDataJetRGNominal.root

Execute: GenerateFakeData.cpp
	CompileRootMacro GenerateFakeData.cpp Execute
