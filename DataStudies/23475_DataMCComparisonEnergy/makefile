


default: Prepare FullRun RunComparison

Prepare:
	ln -sf ../../Samples/ALEPH/ DataSamples
	ln -sf ../../Samples/ALEPHMC/ MCSamples
	ln -sf ../../JetCorrection/23474_MC/*txt .
	ln -sf ../../JetCorrection/23475_DataRel/*txt .
	ln -sf ../../JetCorrection/23475_DataAbs/*txt .

FullRun: Execute
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root --Output DataP1R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt
	./Execute --Input DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root --Output DataP2R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt
	./Execute --Input DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root --Output DataP3R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root --Output DataP1R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt
	./Execute --Input DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root --Output DataP2R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt
	./Execute --Input DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root --Output DataP3R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root --Output DataRP1R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt,JECRelativeResidualR4.txt
	./Execute --Input DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root --Output DataRP2R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt,JECRelativeResidualR4.txt
	./Execute --Input DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root --Output DataRP3R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt,JECRelativeResidualR4.txt
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root --Output DataRP1R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt,JECRelativeResidualR8.txt
	./Execute --Input DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root --Output DataRP2R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt,JECRelativeResidualR8.txt
	./Execute --Input DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root --Output DataRP3R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt,JECRelativeResidualR8.txt
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root --Output DataRRP1R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt,JECRelativeResidualR4.txt,JECResidualR4.txt
	./Execute --Input DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root --Output DataRRP2R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt,JECRelativeResidualR4.txt,JECResidualR4.txt
	./Execute --Input DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root --Output DataRRP3R4.root \
		--Tree akR4ESchemeJetTree --JEC JECR4.txt,JECRelativeResidualR4.txt,JECResidualR4.txt
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root --Output DataRRP1R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt,JECRelativeResidualR8.txt,JECResidualR8.txt
	./Execute --Input DataSamples/LEP1Data1994P2_recons_aftercut-MERGED.root --Output DataRRP2R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt,JECRelativeResidualR8.txt,JECResidualR8.txt
	./Execute --Input DataSamples/LEP1Data1994P3_recons_aftercut-MERGED.root --Output DataRRP3R8.root \
		--Tree akR8ESchemeJetTree --JEC JECR8.txt,JECRelativeResidualR8.txt,JECResidualR8.txt
	for i in `ls MCSamples/ | cut -b 28-30`; do \
		echo $$i; \
		./Execute --Input MCSamples/LEP1MC1994_recons_aftercut-$$i.root --Output MCP$${i}R4.root \
			--Tree akR4ESchemeJetTree --JEC JECR4.txt; \
		./Execute --Input MCSamples/LEP1MC1994_recons_aftercut-$$i.root --Output MCP$${i}R8.root \
			--Tree akR8ESchemeJetTree --JEC JECR8.txt; \
	done
	hadd -f DataRRAllR4.root DataRRP[123]R4.root
	hadd -f DataRRAllR8.root DataRRP[123]R8.root
	hadd -f DataRAllR4.root DataRP[123]R4.root
	hadd -f DataRAllR8.root DataRP[123]R8.root
	hadd -f DataAllR4.root DataP[123]R4.root
	hadd -f DataAllR8.root DataP[123]R8.root
	hadd -f MCAllR4.root MCP*R4.root
	hadd -f MCAllR8.root MCP*R8.root
	rm DataP[123]R[48].root DataRP[123]R[48].root DataRRP[123]R[48].root MCP*R[48].root

TestRun: Execute
	./Execute --Input DataSamples/LEP1Data1994P1_recons_aftercut-MERGED.root \
		--Output DataP1.root \
		--Tree akR4ESchemeJetTree \
		--Fraction 0.05 --JEC JECR4.txt

Execute: ProcessTree.cpp
	CompileRootMacro ProcessTree.cpp Execute -I../../CommonCode/include

ExecuteComparison: CompareSamples.cpp
	CompileRootMacro CompareSamples.cpp ExecuteComparison

RunComparison: ExecuteComparison
	./ExecuteComparison --Data DataAll.root --MC MCAll.root --Output DataMCComparison.pdf
	./ExecuteComparison --Data DataAllFull.root --MC MCAll.root --Output DataMCComparisonFull.pdf
	cp DataMCComparison*.pdf ~/WindowsHome/Downloads/
