default: ProductionRun

Execute: JECFitter.cpp
	CompileRootMacro JECFitter.cpp Execute

Prepare:
	ln -sf ../23475_DataMCComparisonEnergy/DataAllR4.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataAllR8.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataRAllR4.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataRAllR8.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataRRAllR4.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataRRAllR8.root .
	ln -sf ../23475_DataMCComparisonEnergy/MCAllR4.root .
	ln -sf ../23475_DataMCComparisonEnergy/MCAllR8.root .

ProductionRun: Execute
	time ./Execute --MC MCAllR4.root --Data DataRAllR4.root --Validation FitValidationR4.pdf \
		--NJet 9 --PCut 3 --State R4_9_3 --Percentage 1.00
	time ./Execute --MC MCAllR8.root --Data DataRAllR8.root --Validation FitValidationR8.pdf \
		--NJet 9 --PCut 3 --State R8_9_3 --Percentage 1.00
	# cp FitValidationR[48].pdf ~/WindowsHome/Downloads/

RunExport: MakeTextFile.cpp
	CompileRootMacro MakeTextFile.cpp ExecuteTextFile
	./ExecuteTextFile --DHFile FitResults.dh --Output JECResidualR4.txt --Order 1 --State R4_9_3
	./ExecuteTextFile --DHFile FitResults.dh --Output JECResidualR8.txt --Order 1 --State R8_9_3

Deploy:
	mkdir -p ../../JetCorrection/23475_DataAbs/
	cp JECResidualR4.txt ../../JetCorrection/23475_DataAbs/
	cp JECResidualR8.txt ../../JetCorrection/23475_DataAbs/
