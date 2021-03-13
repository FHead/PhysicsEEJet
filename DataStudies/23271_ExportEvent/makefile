JetColor = true

default: TestRun

TestRun: Execute
	awk '{print $$5,$$4}' FullEventListBatch2.txt > EventList.txt
	mkdir -p txt/
	./Execute --jetcolor $(JetColor) --input Samples/LEP1Data1992_recons_aftercut-MERGED.root --eventlist EventList.txt
	./Execute --jetcolor $(JetColor) --input Samples/LEP1Data1993_recons_aftercut-MERGED.root --eventlist EventList.txt
	./Execute --jetcolor $(JetColor) --input Samples/LEP1Data1994P1_recons_aftercut-MERGED.root --eventlist EventList.txt
	./Execute --jetcolor $(JetColor) --input Samples/LEP1Data1994P2_recons_aftercut-MERGED.root --eventlist EventList.txt
	./Execute --jetcolor $(JetColor) --input Samples/LEP1Data1994P3_recons_aftercut-MERGED.root --eventlist EventList.txt
	./Execute --jetcolor $(JetColor) --input Samples/LEP1Data1995_recons_aftercut-MERGED.root --eventlist EventList.txt
	mv Event_*.txt txt/

Execute: ExportEvent.cpp
	CompileRootMacro ExportEvent.cpp Execute


