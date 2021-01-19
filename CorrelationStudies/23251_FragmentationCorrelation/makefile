
default: TestRunPlot

TestRunPlot: ExecutePlot
	./ExecutePlot --data MeowData.root --mc MeowMC.root --output Meow.pdf

TestRun: Execute
	./Execute --input `ls MC/* | tr '\n' ','` --output MeowMC.root --fraction 1.00 \
		--JEC ../../JetCorrection/22525_MC/JEC_R8.txt
	./Execute --input `ls Data/*1994* | tr '\n' ','` --output MeowData.root --fraction 1.00 \
		--JEC ../../JetCorrection/22525_MC/JEC_R8.txt,../../JetCorrection/22533_DataRel/JECRelativeResidualR8.txt,../../JetCorrection/22533_DataAbs/JECResidualR8.txt

ExecutePlot: PlotCorrelation.cpp
	CompileRootMacro PlotCorrelation.cpp ExecutePlot

Execute: FragmentationCorrelation.cpp
	CompileRootMacro FragmentationCorrelation.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o

