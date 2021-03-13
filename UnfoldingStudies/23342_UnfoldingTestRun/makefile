
default: RunPlot

UnfoldAll: RunJetPUnfold RunJetRGUnfold RunJetZGUnfold

RunPlot: ExecutePlot
	./ExecutePlot --Input UnfoldedJetP.root --Output PlotsJetP.pdf
	./ExecutePlot --Input UnfoldedSmearedJetP.root --Output PlotsSmearedJetP.pdf
	./ExecutePlot --Input UnfoldedDataJetP.root --Output PlotsDataJetP.pdf
	./ExecutePlot --Input UnfoldedJetPMCPrior.root --Output PlotsJetPMCPrior.pdf
	./ExecutePlot --Input UnfoldedSmearedJetPMCPrior.root --Output PlotsSmearedJetPMCPrior.pdf
	./ExecutePlot --Input UnfoldedDataJetPMCPrior.root --Output PlotsDataJetPMCPrior.pdf
	./ExecutePlot --Input UnfoldedZG.root --Output PlotsZG.pdf
	./ExecutePlot --Input UnfoldedSmearedZG.root --Output PlotsSmearedZG.pdf
	./ExecutePlot --Input UnfoldedDataZG.root --Output PlotsDataZG.pdf
	./ExecutePlot --Input UnfoldedZGMCPrior.root --Output PlotsZGMCPrior.pdf
	./ExecutePlot --Input UnfoldedSmearedZGMCPrior.root --Output PlotsSmearedZGMCPrior.pdf
	./ExecutePlot --Input UnfoldedDataZGMCPrior.root --Output PlotsDataZGMCPrior.pdf
	./ExecutePlot --Input UnfoldedRG.root --Output PlotsRG.pdf
	./ExecutePlot --Input UnfoldedSmearedRG.root --Output PlotsSmearedRG.pdf
	./ExecutePlot --Input UnfoldedDataRG.root --Output PlotsDataRG.pdf
	./ExecutePlot --Input UnfoldedRGMCPrior.root --Output PlotsRGMCPrior.pdf
	./ExecutePlot --Input UnfoldedSmearedRGMCPrior.root --Output PlotsSmearedRGMCPrior.pdf
	./ExecutePlot --Input UnfoldedDataRGMCPrior.root --Output PlotsDataRGMCPrior.pdf

RunJetZGUnfold: Execute
	./Execute --Input MC.root --InputName HRecoJetZG \
		--Response MC.root --ResponseName H2DJetZG \
		--ResponseTruth HGenJetZG --ResponseMeasured HRecoJetZG \
		--Output UnfoldedZG.root
	./Execute --Input MC.root --InputName HRecoJetZGSmeared \
		--Response MC.root --ResponseName H2DJetZG \
		--ResponseTruth HGenJetZG --ResponseMeasured HRecoJetZG \
		--Output UnfoldedSmearedZG.root
	./Execute --Input Data.root --InputName HRecoJetZG \
		--Response MC.root --ResponseName H2DJetZG \
		--ResponseTruth HGenJetZG --ResponseMeasured HRecoJetZG \
		--Output UnfoldedDataZG.root
	./Execute --Input MC.root --InputName HRecoJetZG \
		--Response MC.root --ResponseName H2DJetZG \
		--ResponseTruth HGenJetZG --ResponseMeasured HRecoJetZG \
		--MCPrior true --Output UnfoldedZGMCPrior.root
	./Execute --Input MC.root --InputName HRecoJetZGSmeared \
		--Response MC.root --ResponseName H2DJetZG \
		--ResponseTruth HGenJetZG --ResponseMeasured HRecoJetZG \
		--MCPrior true --Output UnfoldedSmearedZGMCPrior.root
	./Execute --Input Data.root --InputName HRecoJetZG \
		--Response MC.root --ResponseName H2DJetZG \
		--ResponseTruth HGenJetZG --ResponseMeasured HRecoJetZG \
		--MCPrior true --Output UnfoldedDataZGMCPrior.root

RunJetRGUnfold: Execute
	./Execute --Input MC.root --InputName HRecoJetRG \
		--Response MC.root --ResponseName H2DJetRG \
		--ResponseTruth HGenJetRG --ResponseMeasured HRecoJetRG \
		--Output UnfoldedRG.root
	./Execute --Input MC.root --InputName HRecoJetRGSmeared \
		--Response MC.root --ResponseName H2DJetRG \
		--ResponseTruth HGenJetRG --ResponseMeasured HRecoJetRG \
		--Output UnfoldedSmearedRG.root
	./Execute --Input Data.root --InputName HRecoJetRG \
		--Response MC.root --ResponseName H2DJetRG \
		--ResponseTruth HGenJetRG --ResponseMeasured HRecoJetRG \
		--Output UnfoldedDataRG.root
	./Execute --Input MC.root --InputName HRecoJetRG \
		--Response MC.root --ResponseName H2DJetRG \
		--ResponseTruth HGenJetRG --ResponseMeasured HRecoJetRG \
		--MCPrior true --Output UnfoldedRGMCPrior.root
	./Execute --Input MC.root --InputName HRecoJetRGSmeared \
		--Response MC.root --ResponseName H2DJetRG \
		--ResponseTruth HGenJetRG --ResponseMeasured HRecoJetRG \
		--MCPrior true --Output UnfoldedSmearedRGMCPrior.root
	./Execute --Input Data.root --InputName HRecoJetRG \
		--Response MC.root --ResponseName H2DJetRG \
		--ResponseTruth HGenJetRG --ResponseMeasured HRecoJetRG \
		--MCPrior true --Output UnfoldedDataRGMCPrior.root

RunJetPUnfold: Execute
	./Execute --Input MC.root --InputName HRecoJetPBinned \
		--Response MC.root --ResponseName H2DJetPBinned \
		--ResponseTruth HGenJetPBinned --ResponseMeasured HRecoJetPBinned \
		--Output UnfoldedJetP.root
	./Execute --Input MC.root --InputName HRecoJetPBinnedSmeared \
		--Response MC.root --ResponseName H2DJetPBinned \
		--ResponseTruth HGenJetPBinned --ResponseMeasured HRecoJetPBinned \
		--Output UnfoldedSmearedJetP.root
	./Execute --Input Data.root --InputName HRecoJetPBinned \
		--Response MC.root --ResponseName H2DJetPBinned \
		--ResponseTruth HGenJetPBinned --ResponseMeasured HRecoJetPBinned \
		--Output UnfoldedDataJetP.root
	./Execute --Input MC.root --InputName HRecoJetPBinned \
		--Response MC.root --ResponseName H2DJetPBinned \
		--ResponseTruth HGenJetPBinned --ResponseMeasured HRecoJetPBinned \
		--MCPrior true --Output UnfoldedJetPMCPrior.root
	./Execute --Input MC.root --InputName HRecoJetPBinnedSmeared \
		--Response MC.root --ResponseName H2DJetPBinned \
		--ResponseTruth HGenJetPBinned --ResponseMeasured HRecoJetPBinned \
		--MCPrior true --Output UnfoldedSmearedJetPMCPrior.root
	./Execute --Input Data.root --InputName HRecoJetPBinned \
		--Response MC.root --ResponseName H2DJetPBinned \
		--ResponseTruth HGenJetPBinned --ResponseMeasured HRecoJetPBinned \
		--MCPrior true --Output UnfoldedDataJetPMCPrior.root

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute

ExecutePlot: MakeSummaryPlot.cpp
	CompileRootMacro MakeSummaryPlot.cpp ExecutePlot
