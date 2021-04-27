
default: TestRun

Prepare:
	ln -sf ../22437_DataMCComparison/DataAll.root .
	ln -sf ../22437_DataMCComparison/MCAll.root .

TestRun: Execute
	./Execute --Data DataAll.root --MC MCAll.root --Check CheckDijetResidualVariation.pdf --AlphaMax 0.10
	./Execute --Data DataAll.root --MC MCAll.root --Check CheckDijetResidual.pdf --AlphaMax 0.15
	# cp CheckResidual.pdf ~/WindowsHome/Downloads/

Execute: ResidualAnalysis.cpp
	CompileRootMacro ResidualAnalysis.cpp Execute
