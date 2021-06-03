default: TestRun

Prepare:
	ln -sf ../23474_JetResponseEnergy/AllMatchedR4.root
	ln -sf ../23474_JetResponseEnergy/AllMatchedR8.root

Execute: JetResolutionAnalysis.cpp 
	CompileRootMacro JetResolutionAnalysis.cpp Execute

TestRun: Execute
	./Execute --Input AllMatchedR4.root --OutputBase Resolution_JR4 --Tree MatchedTree --R 0.4
	./Execute --Input AllMatchedR8.root --OutputBase Resolution_JR8 --Tree MatchedTree --R 0.8
	# cp *pdf ~/WindowsHome/Downloads/

Deploy:
	mkdir -p ../../JetCorrection/23515_MCJER
	cp Resolution*txt ../../JetCorrection/23515_MCJER/

