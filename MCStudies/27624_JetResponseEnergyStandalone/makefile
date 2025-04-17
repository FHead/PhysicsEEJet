
default: RunBillTree

Prepare:
	ln -sf ../../Samples/ALEPHMC Samples

RunBillTree: Execute ExecuteJEC
	bash RunBillTree.sh

FullRun: Execute
	for i in `ls Samples/ | cut -b 28-30`; \
	do \
		echo $$i; \
		./Execute --RecoFileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--GenFileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output MatchedR4$${i}.root \
			--RecoTree akR4ESchemeJetTree \
			--GenTree akR4ESchemeGenJetTree \
			--JEC JECR4.txt \
			--Fraction 1.00; \
		./Execute --RecoFileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--GenFileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--Output ReverseMatchedR4$${i}.root \
			--RecoTree akR4ESchemeGenJetTree \
			--GenTree akR4ESchemeJetTree \
			--JEC JECR4.txt \
			--Fraction 1.00; \
		./Execute --RecoFileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
			--GenFileName Samples/LEP1MC1994_recons_aftercut-$${i}.root \
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

DrawRandom2.o: DrawRandom2.h DrawRandom2.cpp
	g++ DrawRandom2.cpp -c -o DrawRandom2.o

TauHelperFunctions3.o: TauHelperFunctions3.h TauHelperFunctions3.cpp
	g++ TauHelperFunctions3.cpp -c -o TauHelperFunctions3.o

TestRun: Execute
	./Execute --RecoFileName Samples/LEP1MC1994_recons_aftercut-011.root \
		--GenFileName Samples/LEP1MC1994_recons_aftercut-011.root \
		--Output Matched011.root \
		--RecoTree akR4ESchemeJetTree \
		--GenTree akR4ESchemeGenJetTree \
		--JEC JECR4.txt \
		--Fraction 1.00

Execute: JetMatcher.cpp TauHelperFunctions3.o DrawRandom2.o
	g++ JetMatcher.cpp -o Execute `root-config --cflags --libs` TauHelperFunctions3.o DrawRandom2.o

TestRunPlot: ExecutePlot
	./ExecutePlot
	cp JetResponse.pdf ~/WindowsHome/Downloads/

ExecutePlot: JetExploration.cpp
	g++ JetExploration.cpp -o ExecutePlot `root-config --cflags --libs`

ExecuteJEC: JetEnergyCorrection.cpp
	g++ JetEnergyCorrection.cpp -o ExecuteJEC `root-config --cflags --libs`

RunJEC: ExecuteJEC
	time ./ExecuteJEC --File AllMatchedR4.root --Tree MatchedTree --Output JECR4.txt --Check JECCheckR4.pdf --R 0.4
	time ./ExecuteJEC --File AllMatchedR8.root --Tree MatchedTree --Output JECR8.txt --Check JECCheckR8.pdf --R 0.8
	# cp JECCheck*.pdf ~/WindowsHome/Downloads

ExecuteJECClosure: JetEnergyClosure.cpp
	g++ JetEnergyClosure.cpp -o ExecuteJECClosure `root-config --cflags --libs`

RunJECClosure: ExecuteJECClosure
	time ./ExecuteJECClosure --Name AllMatchedR4.root --Output JECClosureR4.pdf --R 0.4
	time ./ExecuteJECClosure --Name AllMatchedR8.root --Output JECClosureR8.pdf --R 0.8
	# cp JECClosure*.pdf ~/WindowsHome/Downloads

Deploy:
	cp JEC*txt ../../JetCorrection/23474_MC/

