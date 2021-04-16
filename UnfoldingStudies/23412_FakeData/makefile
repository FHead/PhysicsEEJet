
default: TestRun TestRunThrust TestRunData TestRunStatistics

Prepare:
	rm -f PerfectInput Input
	ln -sf ../23412_PerfectRecoGeneration/Output PerfectInput
	ln -sf ../23411_UnfoldingPreparation/Output Input
	mkdir -p Output

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
	./Execute --MC Input/MCLeadingDiJetENominal.root \
		--Shape PerfectInput/PerfectLeadingDiJetENominal.root \
		--Yield Input/DataLeadingDiJetENominal.root \
		--Output Output/ToyLeadingDiJetENominal.root
	./Execute --MC Input/MCLeadingDiJetSumENominal.root \
		--Shape PerfectInput/PerfectLeadingDiJetSumENominal.root \
		--Yield Input/DataLeadingDiJetSumENominal.root \
		--Output Output/ToyLeadingDiJetSumENominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectJetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectJetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyJetRGNominal.root
	./Execute --MC Input/MCJetMGNominal.root \
		--Shape PerfectInput/PerfectJetMGNominal.root \
		--Yield Input/DataJetMGNominal.root \
		--Output Output/ToyJetMGNominal.root
	./Execute --MC Input/MCJetMGENominal.root \
		--Shape PerfectInput/PerfectJetMGENominal.root \
		--Yield Input/DataJetMGENominal.root \
		--Output Output/ToyJetMGENominal.root
	./Execute --MC Input/MCJetMNominal.root \
		--Shape PerfectInput/PerfectJetMNominal.root \
		--Yield Input/DataJetMNominal.root \
		--Output Output/ToyJetMNominal.root
	./Execute --MC Input/MCJetMENominal.root \
		--Shape PerfectInput/PerfectJetMENominal.root \
		--Yield Input/DataJetMENominal.root \
		--Output Output/ToyJetMENominal.root

TestRunStatistics: Execute
	for i in `seq 1001 1250`; do \
		echo $$i; \
		./Execute --MC Input/MCJetENominal.root \
			--Shape PerfectInput/PerfectDataJetENominal.root \
			--Yield Input/DataJetENominal.root \
			--Seed $$i \
			--Output Output/ToyDataJetEStatistics_$${i}.root; \
		./Execute --MC Input/MCLeadingDiJetENominal.root \
			--Shape PerfectInput/PerfectDataLeadingDiJetENominal.root \
			--Yield Input/DataLeadingDiJetENominal.root \
			--Seed $$i \
			--Output Output/ToyDataLeadingDiJetEStatistics_$${i}.root; \
		./Execute --MC Input/MCLeadingDiJetSumENominal.root \
			--Shape PerfectInput/PerfectDataLeadingDiJetSumENominal.root \
			--Yield Input/DataLeadingDiJetSumENominal.root \
			--Seed $$i \
			--Output Output/ToyDataLeadingDiJetSumEStatistics_$${i}.root; \
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
		./Execute --MC Input/MCJetMGNominal.root \
			--Shape PerfectInput/PerfectDataJetMGNominal.root \
			--Yield Input/DataJetMGNominal.root \
			--Seed $$i \
			--Output Output/ToyDataJetMGStatistics_$${i}.root; \
		./Execute --MC Input/MCJetMGENominal.root \
			--Shape PerfectInput/PerfectDataJetMGENominal.root \
			--Yield Input/DataJetMGENominal.root \
			--Seed $$i \
			--Output Output/ToyDataJetMGEStatistics_$${i}.root; \
		./Execute --MC Input/MCJetMNominal.root \
			--Shape PerfectInput/PerfectDataJetMNominal.root \
			--Yield Input/DataJetMNominal.root \
			--Seed $$i \
			--Output Output/ToyDataJetMStatistics_$${i}.root; \
		./Execute --MC Input/MCJetMENominal.root \
			--Shape PerfectInput/PerfectDataJetMENominal.root \
			--Yield Input/DataJetMENominal.root \
			--Seed $$i \
			--Output Output/ToyDataJetMEStatistics_$${i}.root; \
	done

TestRunData: Execute
	./Execute --MC Input/MCJetENominal.root \
		--Shape PerfectInput/PerfectDataJetENominal.root \
		--Yield Input/DataJetENominal.root \
		--Output Output/ToyDataJetENominal.root
	./Execute --MC Input/MCLeadingDiJetENominal.root \
		--Shape PerfectInput/PerfectDataLeadingDiJetENominal.root \
		--Yield Input/DataLeadingDiJetENominal.root \
		--Output Output/ToyDataLeadingDiJetENominal.root
	./Execute --MC Input/MCLeadingDiJetSumENominal.root \
		--Shape PerfectInput/PerfectDataLeadingDiJetSumENominal.root \
		--Yield Input/DataLeadingDiJetSumENominal.root \
		--Output Output/ToyDataLeadingDiJetSumENominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectDataJetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyDataJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectDataJetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyDataJetRGNominal.root
	./Execute --MC Input/MCJetMGNominal.root \
		--Shape PerfectInput/PerfectDataJetMGNominal.root \
		--Yield Input/DataJetMGNominal.root \
		--Output Output/ToyDataJetMGNominal.root
	./Execute --MC Input/MCJetMGENominal.root \
		--Shape PerfectInput/PerfectDataJetMGENominal.root \
		--Yield Input/DataJetMGENominal.root \
		--Output Output/ToyDataJetMGENominal.root
	./Execute --MC Input/MCJetMNominal.root \
		--Shape PerfectInput/PerfectDataJetMNominal.root \
		--Yield Input/DataJetMNominal.root \
		--Output Output/ToyDataJetMNominal.root
	./Execute --MC Input/MCJetMENominal.root \
		--Shape PerfectInput/PerfectDataJetMENominal.root \
		--Yield Input/DataJetMENominal.root \
		--Output Output/ToyDataJetMENominal.root

Execute: GenerateFakeData.cpp
	CompileRootMacro GenerateFakeData.cpp Execute
