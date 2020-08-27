default: TestRun

Execute: JetResolutionAnalysis.cpp 
	CompileRootMacro JetResolutionAnalysis.cpp Execute

TestRun: Execute
	./Execute --Input AllMatched.root --OutputBase JR4 --Tree MatchedTree --R 0.4
	./Execute --Input AllMatchedR8.root --OutputBase JR8 --Tree MatchedTree --R 0.8
	cp *pdf ~/WindowsHome/Downloads/



