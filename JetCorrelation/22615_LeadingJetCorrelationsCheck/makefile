

default: TestRunAnalyze

TestRun: Execute
	for i in 1 2 3; \
	do \
		./Execute \
			--Input Samples/ALEPH/20190602/LEP1Data1994P$${i}_recons_aftercut-MERGED.root \
			--Output DataP$${i}.root --Fraction 1.00; \
	done
	for i in `seq 1 40`; \
	do \
		j=`printf "%02d" $$i`; \
		./Execute --Input Samples/ALEPHMC/LEP1MC1994_recons_aftercut-0$$j.root \
			--Output MCP$$j.root --Fraction 1.00; \
	done
	hadd -f Data.root DataP*.root
	hadd -f MC.root MCP*.root
	rm DataP*.root MCP*.root

TestRunAnalyze: ExecuteAnalyze
	./ExecuteAnalyze --Input Data.root --Output ResultData.pdf \
		--JetThreshold1 08 --JetThreshold2 30
	./ExecuteAnalyze --Input MC.root --Output ResultMC.pdf \
		--JetThreshold1 08 --JetThreshold2 30
	cp Result*.pdf ~/WindowsHome/Downloads/

Execute: PrepareCorrelations.cpp
	CompileRootMacro PrepareCorrelations.cpp Execute

ExecuteAnalyze: AnalyzeCorrelations.cpp
	CompileRootMacro AnalyzeCorrelations.cpp ExecuteAnalyze
