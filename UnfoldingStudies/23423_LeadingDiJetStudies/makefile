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
		--JEC ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt

TestRunPlot: ExecutePlot
	./ExecutePlot --Input MCNoCut.root --Tier Gen --Output ALEPHGen.pdf
	./ExecutePlot --Input MCNoCut.root --Tier Reco --Output ALEPHReco.pdf
	./ExecutePlot --Input MCPythiaNoCut.root --Tier Gen --Output PythiaGen.pdf
