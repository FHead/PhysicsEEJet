


default: FullRun RunComparison

FullRun: Execute
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root --Output DataP1.root \
		--Tree akR4ESchemeJetTree --JEC JEC.txt
	./Execute --Input DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root --Output DataP2.root \
		--Tree akR4ESchemeJetTree --JEC JEC.txt
	./Execute --Input DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root --Output DataP3.root \
		--Tree akR4ESchemeJetTree --JEC JEC.txt
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root --Output DataP1Full.root \
		--Tree akR4ESchemeJetTree --JEC JEC.txt,JECRelativeResidual.txt
	./Execute --Input DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root --Output DataP2Full.root \
		--Tree akR4ESchemeJetTree --JEC JEC.txt,JECRelativeResidual.txt
	./Execute --Input DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root --Output DataP3Full.root \
		--Tree akR4ESchemeJetTree --JEC JEC.txt,JECRelativeResidual.txt
	for i in `ls MCSamples/ | cut --b 28-30`; do \
		echo $$i; \
		./Execute --Input MCSamples/LEP1MC1994_recons_aftercut-$$i.root --Output MCP$$i.root --Tree akR4ESchemeJetTree --JEC JEC.txt; \
	done
	hadd -f DataAll.root DataP[123].root
	hadd -f DataAllFull.root DataP[123]Full.root
	hadd -f MCAll.root MCP*.root
	rm DataP[123].root MCP*.root

TestRun: Execute
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root \
		--Output DataP1.root \
		--Tree akR4ESchemeJetTree \
		--Fraction 0.05 --JEC JEC.txt

Execute: ProcessTree.cpp
	CompileRootMacro ProcessTree.cpp Execute

ExecuteComparison: CompareSamples.cpp
	CompileRootMacro CompareSamples.cpp ExecuteComparison

RunComparison: ExecuteComparison
	./ExecuteComparison --Data DataAll.root --MC MCAll.root --Output DataMCComparison.pdf
	./ExecuteComparison --Data DataAllFull.root --MC MCAll.root --Output DataMCComparisonFull.pdf
	cp DataMCComparison*.pdf ~/WindowsHome/Downloads/
