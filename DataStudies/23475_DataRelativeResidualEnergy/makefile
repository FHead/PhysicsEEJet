
DHFile = --DHFile DijetResult.dh

default: Prepare TestRun TestRunSummary TestRunExport

Execute: DijetResidual.cpp
	CompileRootMacro DijetResidual.cpp Execute

Prepare:
	ln -sf ../23475_DataMCComparisonEnergy/MCAllR4.root .
	ln -sf ../23475_DataMCComparisonEnergy/MCAllR8.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataAllR4.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataAllR8.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataRAllR4.root .
	ln -sf ../23475_DataMCComparisonEnergy/DataRAllR8.root .

TestRun: Execute
	./Execute --File MCAllR4.root    --E3Cut 5  --PdfFile ResidualSideMCR4.pdf     $(DHFile) --State MCR4_5
	./Execute --File MCAllR8.root    --E3Cut 5  --PdfFile ResidualSideMCR8.pdf     $(DHFile) --State MCR8_5
	./Execute --File DataAllR4.root  --E3Cut 5  --PdfFile ResidualSideDataR4.pdf   $(DHFile) --State DataR4_5
	./Execute --File DataAllR8.root  --E3Cut 5  --PdfFile ResidualSideDataR8.pdf   $(DHFile) --State DataR8_5
	./Execute --File DataAllR4.root  --E3Cut 10 --PdfFile ResidualSideDataR4X.pdf  $(DHFile) --State DataR4_10
	./Execute --File DataAllR8.root  --E3Cut 10 --PdfFile ResidualSideDataR8X.pdf  $(DHFile) --State DataR8_10
	./Execute --File DataAllR4.root  --E3Cut 3  --PdfFile ResidualSideDataR4X2.pdf $(DHFile) --State DataR4_3
	./Execute --File DataAllR8.root  --E3Cut 3  --PdfFile ResidualSideDataR8X2.pdf $(DHFile) --State DataR8_3
	./Execute --File DataRAllR4.root --E3Cut 3  --PdfFile ResidualSideDataRR4X2.pdf --DHFile DijetResultR.dh --State DataR4_3
	./Execute --File DataRAllR8.root --E3Cut 3  --PdfFile ResidualSideDataRR8X2.pdf --DHFile DijetResultR.dh --State DataR8_3
	# cp *pdf ~/WindowsHome/Downloads/

ExecuteSummary: GrandSummaryPlots.cpp
	CompileRootMacro GrandSummaryPlots.cpp ExecuteSummary

TestRunSummary: ExecuteSummary
	./ExecuteSummary --DHFile DijetResult.dh --Output ResidualSideSummaryR4.pdf \
		--Labels "Data E_{3} < 10 GeV","Data E_{3} < 5 GeV","Data E_{3} < 3 GeV","MC E_{3} < 5 GeV" \
		--States "DataR4_10","DataR4_5","DataR4_3","MCR4_5" \
		--Colors 4,1,2,6 \
		--XMin 0.5 --XMax 0.8 --YMin 0.992 --YMax 1.007
	./ExecuteSummary --DHFile DijetResult.dh --Output ResidualSideSummaryR8.pdf \
		--Labels "Data E_{3} < 10 GeV","Data E_{3} < 5 GeV","Data E_{3} < 3 GeV","MC E_{3} < 5 GeV" \
		--States "DataR8_10","DataR8_5","DataR8_3","MCR8_5" \
		--Colors 4,1,2,6 \
		--XMin 0.5 --XMax 0.8 --YMin 0.994 --YMax 1.005
	# cp *pdf ~/WindowsHome/Downloads/

ExecuteExport: ExportTextFile.cpp
	CompileRootMacro ExportTextFile.cpp ExecuteExport

TestRunExport: ExecuteExport
	./ExecuteExport --DHFile DijetResult.dh --State DataR4_3 --Output JECRelativeResidualR4.txt
	./ExecuteExport --DHFile DijetResult.dh --State DataR8_3 --Output JECRelativeResidualR8.txt

Deploy:
	mkdir -p ../../JetCorrection/23475_DataRel/
	cp JECRelativeResidualR4.txt ../../JetCorrection/23475_DataRel/
	cp JECRelativeResidualR8.txt ../../JetCorrection/23475_DataRel/
