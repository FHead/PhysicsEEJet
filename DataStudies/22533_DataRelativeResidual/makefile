
default: TestRunExport

Execute: DijetResidual.cpp
	CompileRootMacro DijetResidual.cpp Execute

TestRun: Execute
	./Execute --File MCAllR4.root --P3Cut 5 --PdfFile MCR4.pdf --DHFile DijetResult.dh --State MCR4_5
	./Execute --File MCAllR8.root --P3Cut 5 --PdfFile MCR8.pdf --DHFile DijetResult.dh --State MCR8_5
	./Execute --File DataAllR4.root --P3Cut 5 --PdfFile DataR4.pdf --DHFile DijetResult.dh --State DataR4_5
	./Execute --File DataAllR8.root --P3Cut 5 --PdfFile DataR8.pdf --DHFile DijetResult.dh --State DataR8_5
	./Execute --File DataAllR4.root --P3Cut 10 --PdfFile DataR4X.pdf --DHFile DijetResult.dh --State DataR4_10
	./Execute --File DataAllR8.root --P3Cut 10 --PdfFile DataR8X.pdf --DHFile DijetResult.dh --State DataR8_10
	./Execute --File DataAllR4.root --P3Cut 3 --PdfFile DataR4X2.pdf --DHFile DijetResult.dh --State DataR4_3
	./Execute --File DataAllR8.root --P3Cut 3 --PdfFile DataR8X2.pdf --DHFile DijetResult.dh --State DataR8_3
	./Execute --File DataRAllR4.root --P3Cut 3 --PdfFile DataRR4X2.pdf --DHFile DijetResultR.dh --State DataR4_3
	./Execute --File DataRAllR8.root --P3Cut 3 --PdfFile DataRR8X2.pdf --DHFile DijetResultR.dh --State DataR8_3
	cp *pdf ~/WindowsHome/Downloads/

ExecuteSummary: GrandSummaryPlots.cpp
	CompileRootMacro GrandSummaryPlots.cpp ExecuteSummary

TestRunSummary: ExecuteSummary
	./ExecuteSummary --DHFile DijetResult.dh --Output SummaryR4.pdf \
		--Labels "Data P_{3} > 10 GeV","Data P_{3} > 5 GeV","Data P_{3} > 3 GeV","MC P_{3} > 5 GeV" \
		--States "DataR4_10","DataR4_5","DataR4_3","MCR4_5" \
		--Colors 4,1,2,6 \
		--XMin 0.5 --XMax 0.8 --YMin 0.994 --YMax 1.005
	./ExecuteSummary --DHFile DijetResult.dh --Output SummaryR8.pdf \
		--Labels "Data P_{3} > 10 GeV","Data P_{3} > 5 GeV","Data P_{3} > 3 GeV","MC P_{3} > 5 GeV" \
		--States "DataR8_10","DataR8_5","DataR8_3","MCR8_5" \
		--Colors 4,1,2,6 \
		--XMin 0.5 --XMax 0.8 --YMin 0.994 --YMax 1.005
	cp *pdf ~/WindowsHome/Downloads/

ExecuteExport: ExportTextFile.cpp
	CompileRootMacro ExportTextFile.cpp ExecuteExport

TestRunExport: ExecuteExport
	./ExecuteExport --DHFile DijetResult.dh --State DataR4_3 --Output JECRelativeResidualR4.txt
	./ExecuteExport --DHFile DijetResult.dh --State DataR8_3 --Output JECRelativeResidualR8.txt



