
default: TestRunPlot

TestRunPlot: ExecutePlot
	./ExecutePlot --data MeowData_MinP10.root --mc MeowMC_MinP10.root --output Meow_MinP10.pdf
	./ExecutePlot --data MeowData_MinP05.root --mc MeowMC_MinP05.root --output Meow_MinP05.pdf
	./ExecutePlot --data MeowData_MinP20.root --mc MeowMC_MinP20.root --output Meow_MinP20.pdf

RunMC: Execute
	./Execute --input `ls MC/* | tr '\n' ','` --output MeowMC_MinP10.root --fraction 1.00 --minp 1 \
		--JEC ../../JetCorrection/22525_MC/JEC_R8.txt
	./Execute --input `ls MC/* | tr '\n' ','` --output MeowMC_MinP05.root --fraction 1.00 --minp 0.5 \
		--JEC ../../JetCorrection/22525_MC/JEC_R8.txt
	./Execute --input `ls MC/* | tr '\n' ','` --output MeowMC_MinP20.root --fraction 1.00 --minp 2 \
		--JEC ../../JetCorrection/22525_MC/JEC_R8.txt

RunData: Execute
	./Execute --input `ls Data/*1994* | tr '\n' ','` --output MeowData_MinP10.root --fraction 1.00 --minp 1 \
		--JEC ../../JetCorrection/22525_MC/JEC_R8.txt,../../JetCorrection/22533_DataRel/JECRelativeResidualR8.txt,../../JetCorrection/22533_DataAbs/JECResidualR8.txt
	./Execute --input `ls Data/*1994* | tr '\n' ','` --output MeowData_MinP05.root --fraction 1.00 --minp 0.5 \
		--JEC ../../JetCorrection/22525_MC/JEC_R8.txt,../../JetCorrection/22533_DataRel/JECRelativeResidualR8.txt,../../JetCorrection/22533_DataAbs/JECResidualR8.txt
	./Execute --input `ls Data/*1994* | tr '\n' ','` --output MeowData_MinP20.root --fraction 1.00 --minp 2.0 \
		--JEC ../../JetCorrection/22525_MC/JEC_R8.txt,../../JetCorrection/22533_DataRel/JECRelativeResidualR8.txt,../../JetCorrection/22533_DataAbs/JECResidualR8.txt

TestRunData: Execute
	./Execute --input `ls Data/*1994* | tr '\n' ','` --output MeowData.root --fraction 0.05 \
		--JEC "../../JetCorrection/22525_MC/JEC_R8.txt","../../JetCorrection/22533_DataRel/JECRelativeResidualR8.txt"

ExecutePlot: PlotCorrelation.cpp
	CompileRootMacro PlotCorrelation.cpp ExecutePlot

Execute: FragmentationCorrelation.cpp
	CompileRootMacro FragmentationCorrelation.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o

