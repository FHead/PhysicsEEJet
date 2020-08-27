
default: TestRun


TestRun: Execute
	./Execute --Data DataAll.root --MC MCAll.root --Check CheckResidual.pdf
	cp CheckResidual.pdf ~/WindowsHome/Downloads/

Execute: ResidualAnalysis.cpp
	CompileRootMacro ResidualAnalysis.cpp Execute
