default: RunHarvest

Execute: JECFitter.cpp
	CompileRootMacro JECFitter.cpp Execute

TestRun: Execute
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation.pdf \
		--NJet 3 --PCut 5 --State TestRun
	cp FitValidation.pdf ~/WindowsHome/Downloads/

RunNScan: Execute
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_2_5.pdf \
		--NJet 2 --PCut 5 --State Scan_2_5
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_3_5.pdf \
		--NJet 3 --PCut 5 --State Scan_3_5
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_4_5.pdf \
		--NJet 4 --PCut 5 --State Scan_4_5
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_5_5.pdf \
		--NJet 5 --PCut 5 --State Scan_5_5

RunXScan: Execute
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_3_6.pdf \
		--NJet 3 --PCut 6 --State Scan_3_6
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_3_7.pdf \
		--NJet 3 --PCut 7 --State Scan_3_7
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_3_8.pdf \
		--NJet 3 --PCut 8 --State Scan_3_8
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_3_9.pdf \
		--NJet 3 --PCut 9 --State Scan_3_9
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_3_10.pdf \
		--NJet 3 --PCut 10 --State Scan_3_10

RunXScanV2: Execute
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_4_6.pdf \
		--NJet 4 --PCut 6 --State Scan_4_6
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_4_7.pdf \
		--NJet 4 --PCut 7 --State Scan_4_7
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_4_8.pdf \
		--NJet 4 --PCut 8 --State Scan_4_8
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_4_9.pdf \
		--NJet 4 --PCut 9 --State Scan_4_9
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_4_10.pdf \
		--NJet 4 --PCut 10 --State Scan_4_10

RunNScanV2: Execute
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_2_3.pdf \
		--NJet 2 --PCut 3 --State Scan_2_3
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_3_3.pdf \
		--NJet 3 --PCut 3 --State Scan_3_3
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_4_3.pdf \
		--NJet 4 --PCut 3 --State Scan_4_3
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_5_3.pdf \
		--NJet 5 --PCut 3 --State Scan_5_3

RunXScanV3: Execute
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_9_3.pdf \
		--NJet 9 --PCut 3 --State Scan_9_3
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_9_5.pdf \
		--NJet 9 --PCut 5 --State Scan_9_5
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_9_6.pdf \
		--NJet 9 --PCut 6 --State Scan_9_6
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_9_8.pdf \
		--NJet 9 --PCut 8 --State Scan_9_8
	time ./Execute --MC MCAll.root --Data DataAll.root --Validation FitValidation_9_10.pdf \
		--NJet 9 --PCut 10 --State Scan_9_10

RunHarvest: Harvest.cpp
	CompileRootMacro Harvest.cpp ExecuteHarvest
	./ExecuteHarvest --DHFile FitResults.dh --PdfFile ScanResult.pdf
	cp ScanResult.pdf ~/WindowsHome/Downloads/

RunExport: MakeTextFile.cpp
	CompileRootMacro MakeTextFile.cpp ExecuteTextFile
	./ExecuteTextFile --DHFile FitResults.dh --Output JECResidual.txt --Order 1 --State Scan_9_3
