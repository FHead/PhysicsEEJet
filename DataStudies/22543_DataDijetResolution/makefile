
default: RunSummary

Execute: DijetResidual.cpp
	CompileRootMacro DijetResidual.cpp Execute

TestRun: Execute
	./Execute --File MCAllR4.root --P3Cut 3 --PdfFile MCR43.pdf --DHFile DijetResult.dh --State MCR4_3
	./Execute --File MCAllR8.root --P3Cut 3 --PdfFile MCR83.pdf --DHFile DijetResult.dh --State MCR8_3
	./Execute --File DataRRAllR4.root --P3Cut 3 --PdfFile DataR43.pdf --DHFile DijetResult.dh --State DataR4_3
	./Execute --File DataRRAllR8.root --P3Cut 3 --PdfFile DataR83.pdf --DHFile DijetResult.dh --State DataR8_3
	./Execute --File MCAllR4.root --P3Cut 5 --PdfFile MCR45.pdf --DHFile DijetResult.dh --State MCR4_5
	./Execute --File MCAllR8.root --P3Cut 5 --PdfFile MCR85.pdf --DHFile DijetResult.dh --State MCR8_5
	./Execute --File DataRRAllR4.root --P3Cut 5 --PdfFile DataR45.pdf --DHFile DijetResult.dh --State DataR4_5
	./Execute --File DataRRAllR8.root --P3Cut 5 --PdfFile DataR85.pdf --DHFile DijetResult.dh --State DataR8_5
	cp *pdf ~/WindowsHome/Downloads/

RunToy: RunToy.cpp
	CompileRootMacro RunToy.cpp ExecuteToy
	./ExecuteToy
	cp *pdf ~/WindowsHome/Downloads/

ExecuteSummary: SummaryPlots.cpp
	CompileRootMacro SummaryPlots.cpp ExecuteSummary

RunSummary: ExecuteSummary
	./ExecuteSummary --MC MCR4_3 --Data DataR4_3 --Output SummaryR43.pdf --JER JR4_MomentumResolution.txt
	./ExecuteSummary --MC MCR8_3 --Data DataR8_3 --Output SummaryR83.pdf --JER JR8_MomentumResolution.txt
	./ExecuteSummary --MC MCR4_5 --Data DataR4_5 --Output SummaryR45.pdf --JER JR4_MomentumResolution.txt
	./ExecuteSummary --MC MCR8_5 --Data DataR8_5 --Output SummaryR85.pdf --JER JR8_MomentumResolution.txt
	cp *pdf ~/WindowsHome/Downloads/


