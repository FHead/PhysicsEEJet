

Convert: Execute
	cat Inc_Jet_Energy_NLO.out | TextToTree Inc_Jet_Energy_NLO.root 6 "XLow:XHigh:Y:YStat:YSysLow:YSysHigh"
	./Execute

Execute: Convert.cpp
	CompileRootMacro Convert.cpp Execute
