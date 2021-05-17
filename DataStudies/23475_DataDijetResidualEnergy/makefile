
default: TestRun

Prepare:
	ln -sf ../23475_DataMCComparisonEnergy/DataAllR4.root DataAll.root
	ln -sf ../23475_DataMCComparisonEnergy/MCAllR4.root MCAll.root

TestRun: Execute
	./Execute --Data DataAll.root --MC MCAll.root --Check CheckDijetResidualVariation.pdf --AlphaMax 0.20
	./Execute --Data DataAll.root --MC MCAll.root --Check CheckDijetResidual.pdf --AlphaMax 0.15
	./Execute --Data DataAll.root --MC MCAll.root --Check CheckDijetResidualNoAlpha.pdf --AlphaMax 1.00
	# cp CheckResidual.pdf ~/WindowsHome/Downloads/

Execute: ResidualAnalysis.cpp
	CompileRootMacro ResidualAnalysis.cpp Execute
