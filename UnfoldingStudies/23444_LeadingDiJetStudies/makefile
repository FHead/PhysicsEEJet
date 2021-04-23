Fraction        = 1

DataSample      = `ls SamplesData/LEP1Data1994*root | tr '\n' ',' | sed "s/,$$//"`
MCSample        = `ls SamplesMC/*root | head -n 100 | tr '\n' ',' | sed "s/,$$//"`
Pythia8Sample   = Pythia8Samples/PurePythia91.root
HerwigSample    = HerwigSamples/run_00/Belle_0_0.root,HerwigSamples/run_01/Belle_0_0.root
Herwig715Sample = Herwig715Samples/run_00/Belle_0_0.root
SherpaSample    = SherpaSamples/run_00/Belle_0_0.root

MCJEC       = ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
ResidualJEC = ../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
DataJEC     = $(MCJEC),$(ResidualJEC)

# default: Prepare DebugRun
default: DebugRunPlot

Prepare:
	rm -f Pythia8Samples SamplesData SamplesMC HerwigSamples SherpaSamples
	ln -sf ../../MCStudies/23417_PythiaWholeEvent/ Pythia8Samples
	ln -sf ../../Samples/ALEPH/ SamplesData
	ln -sf ../../Samples/ALEPHMC/ SamplesMC
	ln -sf ../../Samples/HERWIG7 HerwigSamples
	ln -sf ../../Samples/HERWIG715 Herwig715Samples
	ln -sf ../../Samples/SHERPA/ SherpaSamples

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .

ExecutePlot: MakePlots.cpp
	CompileRootMacro MakePlots.cpp ExecutePlot

RunPythia8: Execute
	time ./Execute --Input $(Pythia8Sample) --Fraction $(Fraction) --Output MCPythia8.root \
		--MC true --BaselineCut false --GenTreeName tgen

RunHerwig: Execute
	time ./Execute --Input $(HerwigSample) --Fraction $(Fraction) --Output MCHerwig.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco

RunHerwig715: Execute
	time ./Execute --Input $(Herwig715Sample) --Fraction $(Fraction) --Output MCHerwig715.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco

RunSherpa: Execute
	time ./Execute --Input $(SherpaSample) --Fraction $(Fraction) --Output MCSherpa.root \
		--MC true --BaselineCut false --GenTreeName t --RecoTreeName treco

DebugRun: Execute
	time ./Execute --Input $(Pythia8Sample) --Fraction 1.00 --Output MCNoCutDebug.root \
		--MC true --BaselineCut false --GenTreeName tgen --ThetaMin 0 --ThetaMax 3.1416 --HybridJetMin 1

DebugRunPlot: ExecutePlot
	time ./ExecutePlot --Input MCNoCutDebug.root --Output JetComparison_020.pdf \
		--JetThetaGap 0.2 --RecalculateSumE true --ParticleThetaGap 0.20
	time ./ExecutePlot --Input MCNoCutDebug.root --Output JetComparison_015.pdf \
		--JetThetaGap 0.2 --RecalculateSumE true --ParticleThetaGap 0.15
	time ./ExecutePlot --Input MCNoCutDebug.root --Output JetComparison_012.pdf \
		--JetThetaGap 0.2 --RecalculateSumE true --ParticleThetaGap 0.12
	time ./ExecutePlot --Input MCNoCutDebug.root --Output JetComparison_010.pdf \
		--JetThetaGap 0.2 --RecalculateSumE true --ParticleThetaGap 0.10
	time ./ExecutePlot --Input MCNoCutDebug.root --Output JetComparison_008.pdf \
		--JetThetaGap 0.2 --RecalculateSumE true --ParticleThetaGap 0.08
	time ./ExecutePlot --Input MCNoCutDebug.root --Output JetComparison_Stored020.pdf \
		--JetThetaGap 0.2 --RecalculateSumE false --SumEString 'GenSumE[4]'
	time ./ExecutePlot --Input MCNoCutDebug.root --Output JetComparison_Hybrid020.pdf \
		--JetThetaGap 0.2 --RecalculateSumE false --SumEString 'GenHybridE[4]'
