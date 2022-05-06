


default: TestRun Validate

Prepare:
	rm -f Input
	ln -sf ../23755_UnfoldedPaperPlotWithMOD/Root Input

Execute: MakeYAML.cpp
	CompileRootMacro MakeYAML.cpp Execute

TestRun: Execute
	./Execute --Input Input/DataJetENominal.root --Output DataJetE.yaml --Export 0 \
		--Selection "None" --XLabel "JetE" --XUnit "GEV" --YLabel "1/NEvent dNJet/d(JetE)" --YUnit "1/GEV" \
		--MinX 10
	./Execute --Input Input/DataLeadingDiJetENominalCorrected.root --Output DataDiJetE.yaml --Export 0 \
		--Selection "None" --XLabel "JetE" --XUnit "GEV" --YLabel "1/NEvent dN/d(JetE)" --YUnit "1/GEV" \
		--MinX 20
	./Execute --Input Input/DataLeadingDiJetSumENominalCorrected.root --Output DataDiJetSumE.yaml --Export 0 \
		--Selection "None" --XLabel "JetSumE" --XUnit "GEV" --YLabel "1/NEvent dN/d(JetSumE)" --YUnit "1/GEV" \
		--MinX 40
	./Execute --Input Input/DataJetZGNominal.root --Output DataJetZG.yaml --Export 2,3,4,5,6,7,8 \
		--Selection "10-15 GeV","15-20 GeV","20-25 GeV","25-30 GeV","30-35 GeV","35-40 GeV","40-inf GeV" \
		--XLabel "ZG" --XUnit "" --YLabel "1/N dN/d(ZG)" --YUnit ""
	./Execute --Input Input/DataJetRGNominal.root --Output DataJetRG.yaml --Export 2,3,4,5,6,7,8 \
		--Selection "10-15 GeV","15-20 GeV","20-25 GeV","25-30 GeV","30-35 GeV","35-40 GeV","40-inf GeV" \
		--XLabel "RG" --XUnit "" --YLabel "1/N dN/d(RG)" --YUnit ""
	./Execute --Input Input/DataJetMENominal.root --Output DataJetME.yaml --Export 2,3,4,5,6,7,8 \
		--Selection "10-15 GeV","15-20 GeV","20-25 GeV","25-30 GeV","30-35 GeV","35-40 GeV","40-inf GeV" \
		--XLabel "M/E" --XUnit "" --YLabel "1/N dN/d(M/E)" --YUnit ""
	./Execute --Input Input/DataJetMGENominal.root --Output DataJetMGE.yaml --Export 2,3,4,5,6,7,8 \
		--Selection "10-15 GeV","15-20 GeV","20-25 GeV","25-30 GeV","30-35 GeV","35-40 GeV","40-inf GeV" \
		--XLabel "MG/E" --XUnit "" --YLabel "1/N dN/d(MG/E)" --YUnit ""
	rm -f Meow.tar.gz
	tar zcvf Meow.tar.gz *yaml

Validate:
	hepdata-validate -a Meow.tar.gz


