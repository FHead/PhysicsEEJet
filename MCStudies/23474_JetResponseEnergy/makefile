
default: RunJECClosure

Prepare:
	ln -sf ../../Samples/ALEPHMC .

FullRun: Execute
	for i in `ls Samples/ | cut -b 28-30`; \
	do \
		echo $$i; \
		./Execute --FileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output MatchedR4$${i}.root \
			--RecoTree akR4ESchemeJetTree \
			--GenTree akR4ESchemeGenJetTree \
			--JEC JECR4.txt \
			--Fraction 1.00; \
		./Execute --FileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output ReverseMatchedR4$${i}.root \
			--RecoTree akR4ESchemeGenJetTree \
			--GenTree akR4ESchemeJetTree \
			--JEC JECR4.txt \
			--Fraction 1.00; \
		./Execute --FileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output MatchedR8$${i}.root \
			--RecoTree akR8ESchemeJetTree \
			--GenTree akR8ESchemeGenJetTree \
			--JEC JECR8.txt \
			--Fraction 1.00; \
	done
	hadd -f AllMatchedR4.root MatchedR40*.root
	hadd -f AllMatchedR8.root MatchedR80*.root
	hadd -f AllReverseMatchedR4.root ReverseMatchedR40*.root
	rm MatchedR40*.root ReverseMatchedR40*.root MatchedR80*.root

TestRun: Execute
	./Execute --FileName Samples/LEP1MC1994_recons_aftercut-011.root \
		--Output Matched011.root \
		--RecoTree akR4ESchemeJetTree \
		--GenTree akR4ESchemeGenJetTree \
		--JEC JECR4.txt \
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
	time ./ExecuteJEC --File AllMatchedR4.root --Tree MatchedTree --Output JECR4.txt --Check JECCheckR4.pdf --R 0.4
	time ./ExecuteJEC --File AllMatchedR8.root --Tree MatchedTree --Output JECR8.txt --Check JECCheckR8.pdf --R 0.8
	# cp JECCheck*.pdf ~/WindowsHome/Downloads

ExecuteJECClosure: JetEnergyClosure.cpp
	CompileRootMacro JetEnergyClosure.cpp ExecuteJECClosure

RunJECClosure: ExecuteJECClosure
	time ./ExecuteJECClosure --Name AllMatchedR4.root --Output JECClosureR4.pdf --R 0.4
	time ./ExecuteJECClosure --Name AllMatchedR8.root --Output JECClosureR8.pdf --R 0.8
	# cp JECClosure*.pdf ~/WindowsHome/Downloads

Deploy:
	cp JEC*txt ../../JetCorrection/23474_MC/

