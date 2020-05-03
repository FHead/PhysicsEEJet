
default: TestRunPlot

FullRun: Execute
	for i in `ls Samples/ -t | cut -b 28-30`; \
	do \
		echo $$i; \
		./Execute --FileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output Matched$${i}.root \
			--RecoTree akR4ESchemeJetTree \
			--GenTree akR4ESchemeGenJetTree \
			--Fraction 1.00; \
		./Execute --FileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output ReverseMatched$${i}.root \
			--RecoTree akR4ESchemeGenJetTree \
			--GenTree akR4ESchemeJetTree \
			--Fraction 1.00; \
	done
	hadd -f AllMatched.root Matched0*.root
	hadd -f AllReverseMatched.root ReverseMatched0*.root
	rm Matched0*.root ReverseMatched0*.root

TestRun: Execute
	./Execute --FileName Samples/LEP1MC1994_recons_aftercut-011.root \
		--Output Matched011.root \
		--RecoTree akR4ESchemeJetTree \
		--GenTree akR4ESchemeGenJetTree \
		--Fraction 1.00

Execute: JetMatcher.cpp
	CompileRootMacro JetMatcher.cpp Execute

TestRunPlot: ExecutePlot
	./ExecutePlot
	cp JetResponse.pdf ~/WindowsHome/Downloads/

ExecutePlot: JetExploration.cpp
	CompileRootMacro JetExploration.cpp ExecutePlot


