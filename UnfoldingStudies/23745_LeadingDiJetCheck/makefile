
default: TestRun

Prepare:
	ln -sf ../23411_UnfoldingPreparation/Output/ Input

Execute: Compare.cpp
	CompileRootMacro Compare.cpp Execute

TestRun: Execute
	./Execute --Output LeadingDiJet.pdf \
   	--Files1 "Input/MCHerwigLeadingDiJetE.root","Input/MCPyquenLeadingDiJetE.root","Input/MCPyquenStrongLeadingDiJetE.root","Input/MCPythia8LeadingDiJetE.root","Input/MCSherpaLeadingDiJetE.root","Input/MCVincia1LeadingDiJetE.root","Input/MCVincia2LeadingDiJetE.root" \
	   --Files2 "Input/MCHerwigTrueLeadingDiJetE.root","Input/MCPyquenTrueLeadingDiJetE.root","Input/MCPyquenStrongTrueLeadingDiJetE.root","Input/MCPythia8TrueLeadingDiJetE.root","Input/MCSherpaTrueLeadingDiJetE.root","Input/MCVincia1TrueLeadingDiJetE.root","Input/MCVincia2TrueLeadingDiJetE.root" \
		--Labels "HERWIG","PYQUEN","PYQUEN (strong)","PYTHIA8","SHERPA","P8 Shower 1","P8 Shower 2"
	./Execute --Output LeadingDiJetSum.pdf \
   	--Files1 "Input/MCHerwigLeadingDiJetSumE.root","Input/MCPyquenLeadingDiJetSumE.root","Input/MCPyquenStrongLeadingDiJetSumE.root","Input/MCPythia8LeadingDiJetSumE.root","Input/MCSherpaLeadingDiJetSumE.root","Input/MCVincia1LeadingDiJetSumE.root","Input/MCVincia2LeadingDiJetSumE.root" \
	   --Files2 "Input/MCHerwigTrueLeadingDiJetSumE.root","Input/MCPyquenTrueLeadingDiJetSumE.root","Input/MCPyquenStrongTrueLeadingDiJetSumE.root","Input/MCPythia8TrueLeadingDiJetSumE.root","Input/MCSherpaTrueLeadingDiJetSumE.root","Input/MCVincia1TrueLeadingDiJetSumE.root","Input/MCVincia2TrueLeadingDiJetSumE.root" \
		--Labels "HERWIG","PYQUEN","PYQUEN (strong)","PYTHIA8","SHERPA","P8 Shower 1","P8 Shower 2"



