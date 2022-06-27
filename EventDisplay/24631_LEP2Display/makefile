
default: TestRun

Execute: ExportParticleList.cpp
	CompileRootMacro ExportParticleList.cpp Execute

TestRun: Execute
	mkdir -p txt
	./Execute --Input LEP2_merged.root --Event   453 --Run 45999  
	./Execute --Input LEP2_merged.root --Event   665 --Run 45689  
	./Execute --Input LEP2_merged.root --Event 17314 --Run 47193  
	./Execute --Input LEP2_merged.root --Event  2110 --Run 47567  
	./Execute --Input LEP2_merged.root --Event  9225 --Run 46964  
	./Execute --Input LEP2_merged.root --Event  5296 --Run 47007  
	./Execute --Input LEP2_merged.root --Event  4604 --Run 47916  
	./Execute --Input LEP2_merged.root --Event  8154 --Run 47054  
	./Execute --Input LEP2_merged.root --Event 13538 --Run 50122  
	./Execute --Input LEP2_merged.root --Event 15790 --Run 50508  
	./Execute --Input LEP2_merged.root --Event 10332 --Run 51445  
	./Execute --Input LEP2_merged.root --Event 12111 --Run 50039  
	./Execute --Input LEP2_merged.root --Event  3975 --Run 52230  
	./Execute --Input LEP2_merged.root --Event  2608 --Run 53452  
	./Execute --Input LEP2_merged.root --Event  2208 --Run 53688  
	./Execute --Input LEP2_merged.root --Event 11802 --Run 53714  
	./Execute --Input LEP2_merged.root --Event  8555 --Run 53848  
	./Execute --Input LEP2_merged.root --Event 17634 --Run 56260  
	./Execute --Input LEP2_merged.root --Event 12174 --Run 58112  
	./Execute --Input LEP2_merged.root --Event 15300 --Run 58387  
	./Execute --Input LEP2_merged.root --Event 11219 --Run 58332  
	./Execute --Input LEP1DataMerged_20190602.root --Event 1375 --Run 28159
	./Execute --Input LEP1DataMerged_20190602.root --Event 2552 --Run 16124
