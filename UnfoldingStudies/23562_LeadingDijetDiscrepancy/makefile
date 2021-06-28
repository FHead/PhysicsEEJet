

default: TestRun

TestRun: Execute
	./Execute --MC MCSumE.root --Data DataSumE.root --Output MeowSumE.pdf
	./Execute --MC MC.root --Data Data.root --Output Meow.pdf

Execute: PlotLeadingJet.cpp
	CompileRootMacro PlotLeadingJet.cpp Execute
