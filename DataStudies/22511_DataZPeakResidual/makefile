default: TestRun

Execute: JECFitter.cpp
	CompileRootMacro JECFitter.cpp Execute

TestRun: Execute
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation.pdf
	cp FitValidation.pdf ~/WindowsHome/Downloads/
