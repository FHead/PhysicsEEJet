
default: TestRun

TestRunThrust: Execute
	./Execute --MC Input/MCThrustNominal.root \
		--Shape PerfectInput/PerfectThrustNominal.root \
		--Yield Input/MCThrustNominal.root \
		--Output Output/ToyMCThrustNominal.root

TestRun: Execute
	./Execute --MC Input/MCJetPNominal.root \
		--Shape PerfectInput/PerfectJetPNominal.root \
		--Yield Input/DataJetPNominal.root \
		--Output Output/ToyJetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectJetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectJetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyJetRGNominal.root

TestRunData: Execute
	./Execute --MC Input/MCJetPNominal.root \
		--Shape PerfectInput/PerfectDataJetPNominal.root \
		--Yield Input/DataJetPNominal.root \
		--Output Output/ToyDataJetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectDataJetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyDataJetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectDataJetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyDataJetRGNominal.root

TestRunDataRound2: Execute
	./Execute --MC Input/MCJetPNominal.root \
		--Shape PerfectInput/PerfectDataRound2JetPNominal.root \
		--Yield Input/DataJetPNominal.root \
		--Output Output/ToyDataRound2JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectDataRound2JetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyDataRound2JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectDataRound2JetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyDataRound2JetRGNominal.root

TestRunDataRound3: Execute
	./Execute --MC Input/MCJetPNominal.root \
		--Shape PerfectInput/PerfectDataRound3JetPNominal.root \
		--Yield Input/DataJetPNominal.root \
		--Output Output/ToyDataRound3JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectDataRound3JetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyDataRound3JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectDataRound3JetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyDataRound3JetRGNominal.root

TestRunDataRound4: Execute
	./Execute --MC Input/MCJetPNominal.root \
		--Shape PerfectInput/PerfectDataRound4JetPNominal.root \
		--Yield Input/DataJetPNominal.root \
		--Output Output/ToyDataRound4JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectDataRound4JetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyDataRound4JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectDataRound4JetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyDataRound4JetRGNominal.root

TestRunDataRound5: Execute
	./Execute --MC Input/MCJetPNominal.root \
		--Shape PerfectInput/PerfectDataRound5JetPNominal.root \
		--Yield Input/DataJetPNominal.root \
		--Output Output/ToyDataRound5JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectDataRound5JetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyDataRound5JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectDataRound5JetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyDataRound5JetRGNominal.root

TestRunDataRound6: Execute
	./Execute --MC Input/MCJetPNominal.root \
		--Shape PerfectInput/PerfectDataRound6JetPNominal.root \
		--Yield Input/DataJetPNominal.root \
		--Output Output/ToyDataRound6JetPNominal.root
	./Execute --MC Input/MCJetZGNominal.root \
		--Shape PerfectInput/PerfectDataRound6JetZGNominal.root \
		--Yield Input/DataJetZGNominal.root \
		--Output Output/ToyDataRound6JetZGNominal.root
	./Execute --MC Input/MCJetRGNominal.root \
		--Shape PerfectInput/PerfectDataRound6JetRGNominal.root \
		--Yield Input/DataJetRGNominal.root \
		--Output Output/ToyDataRound6JetRGNominal.root

Execute: GenerateFakeData.cpp
	CompileRootMacro GenerateFakeData.cpp Execute
