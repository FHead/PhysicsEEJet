
default: TestRunPlot

TestRunPlot: ExecutePlot
	./ExecutePlot --input MeowMC.root --output MeowMC.pdf
	./ExecutePlot --input MeowData.root --output MeowData.pdf

TestRun: Execute
	./Execute --input `ls MC/* | tr '\n' ','` --output MeowMC.root
	./Execute --input `ls Data/*1994* | tr '\n' ','` --output MeowData.root

ExecutePlot: PlotCorrelation.cpp
	CompileRootMacro PlotCorrelation.cpp ExecutePlot

Execute: FragmentationCorrelation.cpp
	CompileRootMacro FragmentationCorrelation.cpp Execute

