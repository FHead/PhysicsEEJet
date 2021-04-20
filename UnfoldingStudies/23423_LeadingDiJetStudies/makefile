Fraction = 1

default: TestRunPlot

Prepare:
	rm -f Pythia8Samples SamplesData SamplesMC HerwigSamples SherpaSamples
	ln -sf ../../MCStudies/23417_PythiaWholeEvent/ Pythia8Samples
	ln -sf ../../Samples/ALEPH/ SamplesData
	ln -sf ../../Samples/ALEPHMC/ SamplesMC
	ln -sf ../../Samples/HERWIG7 HerwigSamples
	ln -sf ../../Samples/SHERPA/ SherpaSamples

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .

ExecutePlot: MakePlots.cpp
	CompileRootMacro MakePlots.cpp ExecutePlot

TestRun: Execute
	time ./Execute --Input `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"` \
		--Fraction $(Fraction) \
		--Output MCNoCut.root --MC true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
	
TestRunPythia:
	time ./Execute --Input Pythia8Samples/PurePythia91.root \
		--Fraction $(Fraction) \
		--Output MCPythiaNoCut.root --MC true \
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt \
		--GenTreeName tgen

TestRunPlot: ExecutePlot
	./ExecutePlot --Input MCNoCut.root --Tier Gen --Output ALEPHGen008.pdf --Acceptance 008
	./ExecutePlot --Input MCNoCut.root --Tier Gen --Output ALEPHGen010.pdf --Acceptance 010
	./ExecutePlot --Input MCNoCut.root --Tier Gen --Output ALEPHGen012.pdf --Acceptance 012
	./ExecutePlot --Input MCNoCut.root --Tier Gen --Output ALEPHGen015.pdf --Acceptance 015
	./ExecutePlot --Input MCNoCut.root --Tier Gen --Output ALEPHGen020.pdf --Acceptance 020
	# ./ExecutePlot --Input MCNoCut.root --Tier Reco --Output ALEPHReco.pdf
	./ExecutePlot --Input MCPythiaNoCut.root --Tier Gen --Output PythiaGen008.pdf --Acceptance 008
	./ExecutePlot --Input MCPythiaNoCut.root --Tier Gen --Output PythiaGen010.pdf --Acceptance 010
	./ExecutePlot --Input MCPythiaNoCut.root --Tier Gen --Output PythiaGen012.pdf --Acceptance 012
	./ExecutePlot --Input MCPythiaNoCut.root --Tier Gen --Output PythiaGen015.pdf --Acceptance 015
	./ExecutePlot --Input MCPythiaNoCut.root --Tier Gen --Output PythiaGen020.pdf --Acceptance 020
