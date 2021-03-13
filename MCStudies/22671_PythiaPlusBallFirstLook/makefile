Fraction = 1
R = 0.4

default: TestRunPlot

TestRunPlot: ExecutePlot ExecuteFinalPlot
	./ExecutePlot --Input Tree_Pythia90_Ball0.root --Output Plots_Pythia90_Ball0.root
	./ExecutePlot --Input Tree_Pythia80_Ball10.root --Output Plots_Pythia80_Ball10.root
	./ExecutePlot --Input Tree_Pythia70_Ball20.root --Output Plots_Pythia70_Ball20.root
	./ExecuteFinalPlot --Input Plots_Pythia90_Ball0.root,Plots_Pythia80_Ball10.root,Plots_Pythia70_Ball20.root \
		--Label "Pythia 91.2","Pythia 81.2 + Ball 10","Pythia 71.2 + Ball 20"

TestRun: Execute
	./Execute --Input Samples/Pythia90_Ball0_Mean020.root --Output Tree_Pythia90_Ball0.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/Pythia80_Ball10_Mean020.root --Output Tree_Pythia80_Ball10.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/Pythia70_Ball20_Mean020.root --Output Tree_Pythia70_Ball20.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/Pythia60_Ball30_Mean020.root --Output Tree_Pythia60_Ball30.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/Pythia50_Ball40_Mean020.root --Output Tree_Pythia50_Ball40.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/Pythia40_Ball50_Mean020.root --Output Tree_Pythia40_Ball50.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/Pythia30_Ball60_Mean020.root --Output Tree_Pythia30_Ball60.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/Pythia20_Ball70_Mean020.root --Output Tree_Pythia20_Ball70.root --Fraction $(Fraction) --R $(R)
	./Execute --Input Samples/Pythia10_Ball80_Mean020.root --Output Tree_Pythia10_Ball80.root --Fraction $(Fraction) --R $(R)

Execute: JetCorrelations.cpp
	rm -f Execute
	CompileRootMacro JetCorrelations.cpp Execute

ExecutePlot: MakePlots.cpp
	rm -f ExecutePlot
	CompileRootMacro MakePlots.cpp ExecutePlot

ExecuteFinalPlot: MakeComparisonPlots.cpp
	rm -f ExecuteFinalPlot
	CompileRootMacro MakeComparisonPlots.cpp ExecuteFinalPlot
