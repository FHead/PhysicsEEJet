
default: RunJECClosure

FullRun: Execute
	for i in `ls Samples/ | cut -b 28-30`; \
	do \
		echo $$i; \
		./Execute --FileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output Matched$${i}.root \
			--RecoTree akR4ESchemeJetTree \
			--GenTree akR4ESchemeGenJetTree \
			--JEC JEC.txt \
			--Fraction 1.00; \
		./Execute --FileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output ReverseMatched$${i}.root \
			--RecoTree akR4ESchemeGenJetTree \
			--GenTree akR4ESchemeJetTree \
			--JEC JEC.txt \
			--Fraction 1.00; \
		./Execute --FileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output MatchedR8$${i}.root \
			--RecoTree akR8ESchemeJetTree \
			--GenTree akR8ESchemeGenJetTree \
			--JEC JECR8.txt \
			--Fraction 1.00; \
	done
	hadd -f AllMatched.root Matched0*.root
	hadd -f AllMatchedR8.root MatchedR80*.root
	hadd -f AllReverseMatched.root ReverseMatched0*.root
	rm Matched0*.root ReverseMatched0*.root MatchedR80*.root

TestRun: Execute
	./Execute --FileName Samples/LEP1MC1994_recons_aftercut-011.root \
		--Output Matched011.root \
		--RecoTree akR4ESchemeJetTree \
		--GenTree akR4ESchemeGenJetTree \
		--JEC JEC.txt \
		--Fraction 1.00

Execute: JetMatcher.cpp
	CompileRootMacro JetMatcher.cpp Execute

TestRunPlot: ExecutePlot
	./ExecutePlot
	cp JetResponse.pdf ~/WindowsHome/Downloads/

ExecutePlot: JetExploration.cpp
	CompileRootMacro JetExploration.cpp ExecutePlot

ExecuteJEC: JetEnergyCorrection.cpp
	CompileRootMacro JetEnergyCorrection.cpp ExecuteJEC

RunJEC: ExecuteJEC
	time ./ExecuteJEC --Name AllMatched.root --Tree MatchedTree --Output JEC.txt --Check JECCheck.pdf
	time ./ExecuteJEC --Name AllMatchedR8.root --Tree MatchedTree --Output JECR8.txt --Check JECCheckR8.pdf
	cp JECCheck*.pdf ~/WindowsHome/Downloads

ExecuteJECClosure: JetEnergyClosure.cpp
	CompileRootMacro JetEnergyClosure.cpp ExecuteJECClosure

RunJECClosure: ExecuteJECClosure
	time ./ExecuteJECClosure --Name AllMatched.root --Output JECClosure.pdf
	time ./ExecuteJECClosure --Name AllMatchedR8.root --Output JECClosureR8.pdf
	cp JECClosure*.pdf ~/WindowsHome/Downloads

