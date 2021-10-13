
ThrustBin = --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 --RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0
ZGBin     = --GenPrimaryMin -0.010 --GenPrimaryMax 0.50 --RecoPrimaryMin -0.010 --RecoPrimaryMax 0.50
RGBin     = --GenPrimaryMin -0.015 --GenPrimaryMax 0.75 --RecoPrimaryMin -0.015 --RecoPrimaryMax 0.75
MGBin     = --GenPrimaryMin -0.1 --GenPrimaryMax 15 --RecoPrimaryMin -0.1 --RecoPrimaryMax 15
MGEBin    = --GenPrimaryMin -0.015 --GenPrimaryMax 0.75 --RecoPrimaryMin -0.015 --RecoPrimaryMax 0.75
MBin      = --GenPrimaryMin 0 --GenPrimaryMax 15 --RecoPrimaryMin 0 --RecoPrimaryMax 15
MEBin     = --GenPrimaryMin 0 --GenPrimaryMax 0.75 --RecoPrimaryMin 0 --RecoPrimaryMax 0.75


default: RunThrustUnfold

UnfoldAll: RunDataUnfoldNominal RunDataUnfold RunMCUnfold RunMCFakeUnfold RunThrustUnfold UnfoldIterations RunDataUnfoldFloored RunDataUnfoldTighter RunFakeDataUnfoldNominal

UnfoldIterations: RunIterationStudies RunDataIterationStudies

Prepare:
	rm -f Input InputToy
	ln -sf ../23411_UnfoldingPreparation/Output Input
	ln -sf ../23412_FakeData/Output InputToy
	mkdir -p Unfolded Plots

RunStatistics: Execute
	for i in `seq 1251 1500`; do \
		./Execute --Input InputToy/ToyDataJetEStatistics_$${i}.root --Output Unfolded/ToyDataJetEStatistics_$${i}.root; \
		./Execute --Input InputToy/ToyDataLeadingDiJetEStatistics_$${i}.root --Output Unfolded/ToyDataLeadingDiJetEStatistics_$${i}.root; \
		./Execute --Input InputToy/ToyDataLeadingDiJetSumEStatistics_$${i}.root --Output Unfolded/ToyDataLeadingDiJetSumEStatistics_$${i}.root; \
		./Execute --Input InputToy/ToyDataJetZGStatistics_$${i}.root --Output Unfolded/ToyDataJetZGStatistics_$${i}.root; \
		./Execute --Input InputToy/ToyDataJetRGStatistics_$${i}.root --Output Unfolded/ToyDataJetRGStatistics_$${i}.root; \
		./Execute --Input InputToy/ToyDataJetMGEStatistics_$${i}.root --Output Unfolded/ToyDataJetMGEStatistics_$${i}.root; \
		./Execute --Input InputToy/ToyDataJetMEStatistics_$${i}.root --Output Unfolded/ToyDataJetMEStatistics_$${i}.root; \
	done
		# ./Execute --Input InputToy/ToyDataJetMStatistics_$${i}.root --Output Unfolded/ToyDataJetMStatistics_$${i}.root; \
		# ./Execute --Input InputToy/ToyDataJetMGStatistics_$${i}.root --Output Unfolded/ToyDataJetMGStatistics_$${i}.root; \


RunThrustUnfold: Execute ExecutePlot
	./Execute --Input Input/MCThrustNominal.root --Output Unfolded/MCThrustNominal.root
	./Execute --Input Input/DataThrustNominal.root --Output Unfolded/DataThrustNominal.root
	./Execute --Input Input/MCThrustUniform.root --Output Unfolded/MCThrustUniform.root
	./Execute --Input Input/DataThrustUniform.root --Output Unfolded/DataThrustUniform.root
	./Execute --Input Input/MCNoCutThrustNominal.root --Output Unfolded/MCNoCutThrustNominal.root
	./Execute --Input Input/DataNoCutThrustNominal.root --Output Unfolded/DataNoCutThrustNominal.root
	./Execute --Input Input/MCNoCutThrustUniform.root --Output Unfolded/MCNoCutThrustUniform.root
	./Execute --Input Input/DataNoCutThrustUniform.root --Output Unfolded/DataNoCutThrustUniform.root
	./Execute --Input InputToy/ToyMCThrustNominal.root --Output Unfolded/ToyMCThrustNominal.root
	./ExecutePlot --Input Unfolded/MCThrustNominal.root --Original Input/MCThrustNominal.root \
		--Output Plots/MCThrustNominal.pdf $(ThrustBin)
	./ExecutePlot --Input Unfolded/DataThrustNominal.root --Original Input/DataThrustNominal.root \
		--Output Plots/DataThrustNominal.pdf $(ThrustBin)
	./ExecutePlot --Input Unfolded/MCThrustUniform.root --Original Input/MCThrustUniform.root \
		--Output Plots/MCThrustUniform.pdf $(ThrustBin)
	./ExecutePlot --Input Unfolded/DataThrustUniform.root --Original Input/DataThrustUniform.root \
		--Output Plots/DataThrustUniform.pdf $(ThrustBin)
	./ExecutePlot --Input Unfolded/MCNoCutThrustNominal.root --Original Input/MCNoCutThrustNominal.root \
		--Output Plots/MCNoCutThrustNominal.pdf $(ThrustBin)
	./ExecutePlot --Input Unfolded/DataNoCutThrustNominal.root --Original Input/DataNoCutThrustNominal.root \
		--Output Plots/DataNoCutThrustNominal.pdf $(ThrustBin)
	./ExecutePlot --Input Unfolded/MCNoCutThrustUniform.root --Original Input/MCNoCutThrustUniform.root \
		--Output Plots/MCNoCutThrustUniform.pdf $(ThrustBin)
	./ExecutePlot --Input Unfolded/DataNoCutThrustUniform.root --Original Input/DataNoCutThrustUniform.root \
		--Output Plots/DataNoCutThrustUniform.pdf $(ThrustBin)
	./ExecutePlot --Input Unfolded/ToyMCThrustNominal.root --Original InputToy/ToyMCThrustNominal.root \
		--Output Plots/ToyMCThrustNominal.pdf $(ThrustBin)

RunIterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyJetENominal.root --Output Unfolded/ToyJetENominal.root
	./Execute --Input InputToy/ToyLeadingDiJetENominal.root --Output Unfolded/ToyLeadingDiJetENominal.root
	./Execute --Input InputToy/ToyLeadingDiJetSumENominal.root --Output Unfolded/ToyLeadingDiJetSumENominal.root
	./Execute --Input InputToy/ToyJetZGNominal.root --Output Unfolded/ToyJetZGNominal.root
	./Execute --Input InputToy/ToyJetRGNominal.root --Output Unfolded/ToyJetRGNominal.root
	./Execute --Input InputToy/ToyJetMGNominal.root --Output Unfolded/ToyJetMGNominal.root
	./Execute --Input InputToy/ToyJetMGENominal.root --Output Unfolded/ToyJetMGENominal.root
	./Execute --Input InputToy/ToyJetMNominal.root --Output Unfolded/ToyJetMNominal.root
	./Execute --Input InputToy/ToyJetMENominal.root --Output Unfolded/ToyJetMENominal.root
	./ExecutePlot --Input Unfolded/ToyJetENominal.root --Original InputToy/ToyJetENominal.root \
		--Output Plots/ToyJetENominal.pdf
	./ExecutePlot --Input Unfolded/ToyLeadingDiJetENominal.root --Original InputToy/ToyLeadingDiJetENominal.root \
		--Output Plots/ToyLeadingDiJetENominal.pdf
	./ExecutePlot --Input Unfolded/ToyLeadingDiJetSumENominal.root --Original InputToy/ToyLeadingDiJetSumENominal.root \
		--Output Plots/ToyLeadingDiJetSumENominal.pdf
	./ExecutePlot --Input Unfolded/ToyJetZGNominal.root --Original InputToy/ToyJetZGNominal.root \
		--Output Plots/ToyJetZGNominal.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/ToyJetRGNominal.root --Original InputToy/ToyJetRGNominal.root \
		--Output Plots/ToyJetRGNominal.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/ToyJetMGNominal.root --Original InputToy/ToyJetMGNominal.root \
		--Output Plots/ToyJetMGNominal.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/ToyJetMGENominal.root --Original InputToy/ToyJetMGENominal.root \
		--Output Plots/ToyJetMGENominal.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/ToyJetMNominal.root --Original InputToy/ToyJetMNominal.root \
		--Output Plots/ToyJetMNominal.pdf $(MBin)
	./ExecutePlot --Input Unfolded/ToyJetMENominal.root --Original InputToy/ToyJetMENominal.root \
		--Output Plots/ToyJetMENominal.pdf $(MEBin)

RunDataIterationStudies: Execute ExecutePlot
	./Execute --Input InputToy/ToyDataJetENominal.root --Output Unfolded/ToyDataJetENominal.root
	./Execute --Input InputToy/ToyDataLeadingDiJetENominal.root --Output Unfolded/ToyDataLeadingDiJetENominal.root
	./Execute --Input InputToy/ToyDataLeadingDiJetSumENominal.root --Output Unfolded/ToyDataLeadingDiJetSumENominal.root
	./Execute --Input InputToy/ToyDataJetZGNominal.root --Output Unfolded/ToyDataJetZGNominal.root
	./Execute --Input InputToy/ToyDataJetRGNominal.root --Output Unfolded/ToyDataJetRGNominal.root
	./Execute --Input InputToy/ToyDataJetMGNominal.root --Output Unfolded/ToyDataJetMGNominal.root
	./Execute --Input InputToy/ToyDataJetMGENominal.root --Output Unfolded/ToyDataJetMGENominal.root
	./Execute --Input InputToy/ToyDataJetMNominal.root --Output Unfolded/ToyDataJetMNominal.root
	./Execute --Input InputToy/ToyDataJetMENominal.root --Output Unfolded/ToyDataJetMENominal.root
	./ExecutePlot --Input Unfolded/ToyDataJetENominal.root --Original InputToy/ToyDataJetENominal.root \
		--Output Plots/ToyDataJetENominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataLeadingDiJetENominal.root --Original InputToy/ToyDataLeadingDiJetENominal.root \
		--Output Plots/ToyDataLeadingDiJetENominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataLeadingDiJetSumENominal.root --Original InputToy/ToyDataLeadingDiJetSumENominal.root \
		--Output Plots/ToyDataLeadingDiJetSumENominal.pdf
	./ExecutePlot --Input Unfolded/ToyDataJetZGNominal.root --Original InputToy/ToyDataJetZGNominal.root \
		--Output Plots/ToyDataJetZGNominal.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/ToyDataJetRGNominal.root --Original InputToy/ToyDataJetRGNominal.root \
		--Output Plots/ToyDataJetRGNominal.pdf $(GBin)
	./ExecutePlot --Input Unfolded/ToyDataJetMGNominal.root --Original InputToy/ToyDataJetMGNominal.root \
		--Output Plots/ToyDataJetMGNominal.pdf $(GBin)
	./ExecutePlot --Input Unfolded/ToyDataJetMGENominal.root --Original InputToy/ToyDataJetMGENominal.root \
		--Output Plots/ToyDataJetMGENominal.pdf $(GBin)
	./ExecutePlot --Input Unfolded/ToyDataJetMNominal.root --Original InputToy/ToyDataJetMNominal.root \
		--Output Plots/ToyDataJetMNominal.pdf $(GBin)
	./ExecutePlot --Input Unfolded/ToyDataJetMENominal.root --Original InputToy/ToyDataJetMENominal.root \
		--Output Plots/ToyDataJetMENominal.pdf $(GBin)

RunDataUnfoldNominal: Execute ExecutePlot
	./Execute --Input Input/DataJetENominal.root --Output Unfolded/DataJetENominal.root
	./Execute --Input Input/DataLeadingDiJetENominal.root --Output Unfolded/DataLeadingDiJetENominal.root
	./Execute --Input Input/DataLeadingDiJetSumENominal.root --Output Unfolded/DataLeadingDiJetSumENominal.root
	./Execute --Input Input/DataJetZGNominal.root --Output Unfolded/DataJetZGNominal.root
	./Execute --Input Input/DataJetRGNominal.root --Output Unfolded/DataJetRGNominal.root
	./Execute --Input Input/DataJetMGNominal.root --Output Unfolded/DataJetMGNominal.root
	./Execute --Input Input/DataJetMGENominal.root --Output Unfolded/DataJetMGENominal.root
	./Execute --Input Input/DataJetZG2Nominal.root --Output Unfolded/DataJetZG2Nominal.root
	./Execute --Input Input/DataJetRG2Nominal.root --Output Unfolded/DataJetRG2Nominal.root
	./Execute --Input Input/DataJetMNominal.root --Output Unfolded/DataJetMNominal.root
	./Execute --Input Input/DataJetMENominal.root --Output Unfolded/DataJetMENominal.root
	./ExecutePlot --Input Unfolded/DataJetENominal.root --Original Input/DataJetENominal.root \
		--Output Plots/DataJetENominal.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataLeadingDiJetENominal.root --Original Input/DataLeadingDiJetENominal.root \
		--Output Plots/DataLeadingDiJetENominal.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumENominal.root --Original Input/DataLeadingDiJetSumENominal.root \
		--Output Plots/DataLeadingDiJetSumENominal.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataJetZGNominal.root --Original Input/DataJetZGNominal.root \
		--Output Plots/DataJetZGNominal.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGNominal.root --Original Input/DataJetRGNominal.root \
		--Output Plots/DataJetRGNominal.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGNominal.root --Original Input/DataJetMGNominal.root \
		--Output Plots/DataJetMGNominal.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGENominal.root --Original Input/DataJetMGENominal.root \
		--Output Plots/DataJetMGENominal.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetZG2Nominal.root --Original Input/DataJetZG2Nominal.root \
		--Output Plots/DataJetZG2Nominal.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRG2Nominal.root --Original Input/DataJetRG2Nominal.root \
		--Output Plots/DataJetRG2Nominal.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMNominal.root --Original Input/DataJetMNominal.root \
		--Output Plots/DataJetMNominal.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMENominal.root --Original Input/DataJetMENominal.root \
		--Output Plots/DataJetMENominal.pdf $(MEBin)

RunFakeDataUnfoldNominal: Execute ExecutePlot
	./Execute --Input Input/FakeDataJetENominal.root             --Output Unfolded/FakeDataJetENominal.root
	./Execute --Input Input/FakeDataLeadingDiJetENominal.root    --Output Unfolded/FakeDataLeadingDiJetENominal.root
	./Execute --Input Input/FakeDataLeadingDiJetSumENominal.root --Output Unfolded/FakeDataLeadingDiJetSumENominal.root
	./Execute --Input Input/FakeDataJetZGNominal.root            --Output Unfolded/FakeDataJetZGNominal.root
	./Execute --Input Input/FakeDataJetRGNominal.root            --Output Unfolded/FakeDataJetRGNominal.root
	./Execute --Input Input/FakeDataJetMGNominal.root            --Output Unfolded/FakeDataJetMGNominal.root
	./Execute --Input Input/FakeDataJetMGENominal.root           --Output Unfolded/FakeDataJetMGENominal.root
	./Execute --Input Input/FakeDataJetZG2Nominal.root           --Output Unfolded/FakeDataJetZG2Nominal.root
	./Execute --Input Input/FakeDataJetRG2Nominal.root           --Output Unfolded/FakeDataJetRG2Nominal.root
	./Execute --Input Input/FakeDataJetMNominal.root             --Output Unfolded/FakeDataJetMNominal.root
	./Execute --Input Input/FakeDataJetMENominal.root            --Output Unfolded/FakeDataJetMENominal.root


RunDataUnfoldFloored: Execute ExecutePlot
	./Execute --Input Input/DataJetEFloored.root --Output Unfolded/DataJetEFloored.root
	./Execute --Input Input/DataLeadingDiJetEFloored.root --Output Unfolded/DataLeadingDiJetEFloored.root
	./Execute --Input Input/DataLeadingDiJetSumEFloored.root --Output Unfolded/DataLeadingDiJetSumEFloored.root
	./Execute --Input Input/DataJetZGFloored.root --Output Unfolded/DataJetZGFloored.root
	./Execute --Input Input/DataJetRGFloored.root --Output Unfolded/DataJetRGFloored.root
	./Execute --Input Input/DataJetMGFloored.root --Output Unfolded/DataJetMGFloored.root
	./Execute --Input Input/DataJetMGEFloored.root --Output Unfolded/DataJetMGEFloored.root
	./Execute --Input Input/DataJetZG2Floored.root --Output Unfolded/DataJetZG2Floored.root
	./Execute --Input Input/DataJetRG2Floored.root --Output Unfolded/DataJetRG2Floored.root
	./Execute --Input Input/DataJetMFloored.root --Output Unfolded/DataJetMFloored.root
	./Execute --Input Input/DataJetMEFloored.root --Output Unfolded/DataJetMEFloored.root
	./ExecutePlot --Input Unfolded/DataJetEFloored.root --Original Input/DataJetEFloored.root \
		--Output Plots/DataJetEFloored.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataLeadingDiJetEFloored.root --Original Input/DataLeadingDiJetEFloored.root \
		--Output Plots/DataLeadingDiJetEFloored.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumEFloored.root --Original Input/DataLeadingDiJetSumEFloored.root \
		--Output Plots/DataLeadingDiJetSumEFloored.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataJetZGFloored.root --Original Input/DataJetZGFloored.root \
		--Output Plots/DataJetZGFloored.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGFloored.root --Original Input/DataJetRGFloored.root \
		--Output Plots/DataJetRGFloored.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGFloored.root --Original Input/DataJetMGFloored.root \
		--Output Plots/DataJetMGFloored.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGEFloored.root --Original Input/DataJetMGEFloored.root \
		--Output Plots/DataJetMGEFloored.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetZG2Floored.root --Original Input/DataJetZG2Floored.root \
		--Output Plots/DataJetZG2Floored.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRG2Floored.root --Original Input/DataJetRG2Floored.root \
		--Output Plots/DataJetRG2Floored.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMFloored.root --Original Input/DataJetMFloored.root \
		--Output Plots/DataJetMFloored.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMEFloored.root --Original Input/DataJetMEFloored.root \
		--Output Plots/DataJetMEFloored.pdf $(MEBin)

RunDataUnfoldTighter: Execute ExecutePlot
	./Execute --Input Input/DataJetETighter.root --Output Unfolded/DataJetETighter.root
	./Execute --Input Input/DataLeadingDiJetETighter.root --Output Unfolded/DataLeadingDiJetETighter.root
	./Execute --Input Input/DataLeadingDiJetSumETighter.root --Output Unfolded/DataLeadingDiJetSumETighter.root
	./Execute --Input Input/DataJetZGTighter.root --Output Unfolded/DataJetZGTighter.root
	./Execute --Input Input/DataJetRGTighter.root --Output Unfolded/DataJetRGTighter.root
	./Execute --Input Input/DataJetMGTighter.root --Output Unfolded/DataJetMGTighter.root
	./Execute --Input Input/DataJetMGETighter.root --Output Unfolded/DataJetMGETighter.root
	./Execute --Input Input/DataJetZG2Tighter.root --Output Unfolded/DataJetZG2Tighter.root
	./Execute --Input Input/DataJetRG2Tighter.root --Output Unfolded/DataJetRG2Tighter.root
	./Execute --Input Input/DataJetMTighter.root --Output Unfolded/DataJetMTighter.root
	./Execute --Input Input/DataJetMETighter.root --Output Unfolded/DataJetMETighter.root
	./ExecutePlot --Input Unfolded/DataJetETighter.root --Original Input/DataJetETighter.root \
		--Output Plots/DataJetETighter.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataLeadingDiJetETighter.root --Original Input/DataLeadingDiJetETighter.root \
		--Output Plots/DataLeadingDiJetETighter.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumETighter.root --Original Input/DataLeadingDiJetSumETighter.root \
		--Output Plots/DataLeadingDiJetSumETighter.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataJetZGTighter.root --Original Input/DataJetZGTighter.root \
		--Output Plots/DataJetZGTighter.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGTighter.root --Original Input/DataJetRGTighter.root \
		--Output Plots/DataJetRGTighter.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGTighter.root --Original Input/DataJetMGTighter.root \
		--Output Plots/DataJetMGTighter.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGETighter.root --Original Input/DataJetMGETighter.root \
		--Output Plots/DataJetMGETighter.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetZG2Tighter.root --Original Input/DataJetZG2Tighter.root \
		--Output Plots/DataJetZG2Tighter.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRG2Tighter.root --Original Input/DataJetRG2Tighter.root \
		--Output Plots/DataJetRG2Tighter.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMTighter.root --Original Input/DataJetMTighter.root \
		--Output Plots/DataJetMTighter.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMETighter.root --Original Input/DataJetMETighter.root \
		--Output Plots/DataJetMETighter.pdf $(MEBin)

RunDataUnfold: Execute ExecutePlot
	./Execute --Input Input/DataJetENominal.root --Output Unfolded/DataJetEMCPrior.root --MCPrior true
	./Execute --Input Input/DataLeadingDiJetENominal.root --Output Unfolded/DataLeadingDiJetEMCPrior.root --MCPrior true
	./Execute --Input Input/DataLeadingDiJetSumENominal.root --Output Unfolded/DataLeadingDiJetSumEMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetZGNominal.root --Output Unfolded/DataJetZGMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetRGNominal.root --Output Unfolded/DataJetRGMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetMGNominal.root --Output Unfolded/DataJetMGMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetMGENominal.root --Output Unfolded/DataJetMGEMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetMNominal.root --Output Unfolded/DataJetMMCPrior.root --MCPrior true
	./Execute --Input Input/DataJetMENominal.root --Output Unfolded/DataJetMEMCPrior.root --MCPrior true
	./Execute --Input Input/DataLeadingDiJetELowerSumE.root --Output Unfolded/DataLeadingDiJetELowerSumE.root
	./Execute --Input Input/DataLeadingDiJetSumELowerSumE.root --Output Unfolded/DataLeadingDiJetSumELowerSumE.root
	./Execute --Input Input/DataLeadingDiJetEHigherSumE.root --Output Unfolded/DataLeadingDiJetEHigherSumE.root
	./Execute --Input Input/DataLeadingDiJetSumEHigherSumE.root --Output Unfolded/DataLeadingDiJetSumEHigherSumE.root
	./Execute --Input Input/DataJetELargeThetaGap.root --Output Unfolded/DataJetELargeThetaGap.root
	./Execute --Input Input/DataLeadingDiJetELargeThetaGap.root --Output Unfolded/DataLeadingDiJetELargeThetaGap.root
	./Execute --Input Input/DataLeadingDiJetSumELargeThetaGap.root --Output Unfolded/DataLeadingDiJetSumELargeThetaGap.root
	./Execute --Input Input/DataJetZGLargeThetaGap.root --Output Unfolded/DataJetZGLargeThetaGap.root
	./Execute --Input Input/DataJetRGLargeThetaGap.root --Output Unfolded/DataJetRGLargeThetaGap.root
	./Execute --Input Input/DataJetMGLargeThetaGap.root --Output Unfolded/DataJetMGLargeThetaGap.root
	./Execute --Input Input/DataJetMGELargeThetaGap.root --Output Unfolded/DataJetMGELargeThetaGap.root
	./Execute --Input Input/DataJetMLargeThetaGap.root --Output Unfolded/DataJetMLargeThetaGap.root
	./Execute --Input Input/DataJetMELargeThetaGap.root --Output Unfolded/DataJetMELargeThetaGap.root
	./Execute --Input Input/DataJetEPositiveTheta.root --Output Unfolded/DataJetEPositiveTheta.root
	./Execute --Input Input/DataLeadingDiJetEPositiveTheta.root --Output Unfolded/DataLeadingDiJetEPositiveTheta.root
	./Execute --Input Input/DataLeadingDiJetSumEPositiveTheta.root --Output Unfolded/DataLeadingDiJetSumEPositiveTheta.root
	./Execute --Input Input/DataJetZGPositiveTheta.root --Output Unfolded/DataJetZGPositiveTheta.root
	./Execute --Input Input/DataJetRGPositiveTheta.root --Output Unfolded/DataJetRGPositiveTheta.root
	./Execute --Input Input/DataJetMGPositiveTheta.root --Output Unfolded/DataJetMGPositiveTheta.root
	./Execute --Input Input/DataJetMGEPositiveTheta.root --Output Unfolded/DataJetMGEPositiveTheta.root
	./Execute --Input Input/DataJetMPositiveTheta.root --Output Unfolded/DataJetMPositiveTheta.root
	./Execute --Input Input/DataJetMEPositiveTheta.root --Output Unfolded/DataJetMEPositiveTheta.root
	./Execute --Input Input/DataJetENegativeTheta.root --Output Unfolded/DataJetENegativeTheta.root
	./Execute --Input Input/DataLeadingDiJetENegativeTheta.root --Output Unfolded/DataLeadingDiJetENegativeTheta.root
	./Execute --Input Input/DataLeadingDiJetSumENegativeTheta.root --Output Unfolded/DataLeadingDiJetSumENegativeTheta.root
	./Execute --Input Input/DataJetZGNegativeTheta.root --Output Unfolded/DataJetZGNegativeTheta.root
	./Execute --Input Input/DataJetRGNegativeTheta.root --Output Unfolded/DataJetRGNegativeTheta.root
	./Execute --Input Input/DataJetMGNegativeTheta.root --Output Unfolded/DataJetMGNegativeTheta.root
	./Execute --Input Input/DataJetMGENegativeTheta.root --Output Unfolded/DataJetMGENegativeTheta.root
	./Execute --Input Input/DataJetMNegativeTheta.root --Output Unfolded/DataJetMNegativeTheta.root
	./Execute --Input Input/DataJetMENegativeTheta.root --Output Unfolded/DataJetMENegativeTheta.root
	./Execute --Input Input/DataJetENoResidual.root --Output Unfolded/DataJetENoResidual.root
	./Execute --Input Input/DataLeadingDiJetENoResidual.root --Output Unfolded/DataLeadingDiJetENoResidual.root
	./Execute --Input Input/DataLeadingDiJetSumENoResidual.root --Output Unfolded/DataLeadingDiJetSumENoResidual.root
	./Execute --Input Input/DataJetZGNoResidual.root --Output Unfolded/DataJetZGNoResidual.root
	./Execute --Input Input/DataJetRGNoResidual.root --Output Unfolded/DataJetRGNoResidual.root
	./Execute --Input Input/DataJetMGNoResidual.root --Output Unfolded/DataJetMGNoResidual.root
	./Execute --Input Input/DataJetMGENoResidual.root --Output Unfolded/DataJetMGENoResidual.root
	./Execute --Input Input/DataJetMNoResidual.root --Output Unfolded/DataJetMNoResidual.root
	./Execute --Input Input/DataJetMENoResidual.root --Output Unfolded/DataJetMENoResidual.root
	./Execute --Input Input/DataJetEJECUp.root --Output Unfolded/DataJetEJECUp.root
	./Execute --Input Input/DataLeadingDiJetEJECUp.root --Output Unfolded/DataLeadingDiJetEJECUp.root
	./Execute --Input Input/DataLeadingDiJetSumEJECUp.root --Output Unfolded/DataLeadingDiJetSumEJECUp.root
	./Execute --Input Input/DataJetZGJECUp.root --Output Unfolded/DataJetZGJECUp.root
	./Execute --Input Input/DataJetRGJECUp.root --Output Unfolded/DataJetRGJECUp.root
	./Execute --Input Input/DataJetMGJECUp.root --Output Unfolded/DataJetMGJECUp.root
	./Execute --Input Input/DataJetMGEJECUp.root --Output Unfolded/DataJetMGEJECUp.root
	./Execute --Input Input/DataJetMJECUp.root --Output Unfolded/DataJetMJECUp.root
	./Execute --Input Input/DataJetMEJECUp.root --Output Unfolded/DataJetMEJECUp.root
	./Execute --Input Input/DataJetEJECDown.root --Output Unfolded/DataJetEJECDown.root
	./Execute --Input Input/DataLeadingDiJetEJECDown.root --Output Unfolded/DataLeadingDiJetEJECDown.root
	./Execute --Input Input/DataLeadingDiJetSumEJECDown.root --Output Unfolded/DataLeadingDiJetSumEJECDown.root
	./Execute --Input Input/DataJetZGJECDown.root --Output Unfolded/DataJetZGJECDown.root
	./Execute --Input Input/DataJetRGJECDown.root --Output Unfolded/DataJetRGJECDown.root
	./Execute --Input Input/DataJetMGJECDown.root --Output Unfolded/DataJetMGJECDown.root
	./Execute --Input Input/DataJetMGEJECDown.root --Output Unfolded/DataJetMGEJECDown.root
	./Execute --Input Input/DataJetMJECDown.root --Output Unfolded/DataJetMJECDown.root
	./Execute --Input Input/DataJetMEJECDown.root --Output Unfolded/DataJetMEJECDown.root
	./Execute --Input Input/DataJetEJECHalfUp.root --Output Unfolded/DataJetEJECHalfUp.root
	./Execute --Input Input/DataLeadingDiJetEJECHalfUp.root --Output Unfolded/DataLeadingDiJetEJECHalfUp.root
	./Execute --Input Input/DataLeadingDiJetSumEJECHalfUp.root --Output Unfolded/DataLeadingDiJetSumEJECHalfUp.root
	./Execute --Input Input/DataJetZGJECHalfUp.root --Output Unfolded/DataJetZGJECHalfUp.root
	./Execute --Input Input/DataJetRGJECHalfUp.root --Output Unfolded/DataJetRGJECHalfUp.root
	./Execute --Input Input/DataJetMGJECHalfUp.root --Output Unfolded/DataJetMGJECHalfUp.root
	./Execute --Input Input/DataJetMGEJECHalfUp.root --Output Unfolded/DataJetMGEJECHalfUp.root
	./Execute --Input Input/DataJetMJECHalfUp.root --Output Unfolded/DataJetMJECHalfUp.root
	./Execute --Input Input/DataJetMEJECHalfUp.root --Output Unfolded/DataJetMEJECHalfUp.root
	./Execute --Input Input/DataJetEJECHalfDown.root --Output Unfolded/DataJetEJECHalfDown.root
	./Execute --Input Input/DataLeadingDiJetEJECHalfDown.root --Output Unfolded/DataLeadingDiJetEJECHalfDown.root
	./Execute --Input Input/DataLeadingDiJetSumEJECHalfDown.root --Output Unfolded/DataLeadingDiJetSumEJECHalfDown.root
	./Execute --Input Input/DataJetZGJECHalfDown.root --Output Unfolded/DataJetZGJECHalfDown.root
	./Execute --Input Input/DataJetRGJECHalfDown.root --Output Unfolded/DataJetRGJECHalfDown.root
	./Execute --Input Input/DataJetMGJECHalfDown.root --Output Unfolded/DataJetMGJECHalfDown.root
	./Execute --Input Input/DataJetMGEJECHalfDown.root --Output Unfolded/DataJetMGEJECHalfDown.root
	./Execute --Input Input/DataJetMJECHalfDown.root --Output Unfolded/DataJetMJECHalfDown.root
	./Execute --Input Input/DataJetMEJECHalfDown.root --Output Unfolded/DataJetMEJECHalfDown.root
	./Execute --Input Input/DataJetEJERUp.root --Output Unfolded/DataJetEJERUp.root
	./Execute --Input Input/DataLeadingDiJetEJERUp.root --Output Unfolded/DataLeadingDiJetEJERUp.root
	./Execute --Input Input/DataLeadingDiJetSumEJERUp.root --Output Unfolded/DataLeadingDiJetSumEJERUp.root
	./Execute --Input Input/DataJetZGJERUp.root --Output Unfolded/DataJetZGJERUp.root
	./Execute --Input Input/DataJetRGJERUp.root --Output Unfolded/DataJetRGJERUp.root
	./Execute --Input Input/DataJetMGJERUp.root --Output Unfolded/DataJetMGJERUp.root
	./Execute --Input Input/DataJetMGEJERUp.root --Output Unfolded/DataJetMGEJERUp.root
	./Execute --Input Input/DataJetMJERUp.root --Output Unfolded/DataJetMJERUp.root
	./Execute --Input Input/DataJetMEJERUp.root --Output Unfolded/DataJetMEJERUp.root
	./Execute --Input Input/DataJetEJERDown.root --Output Unfolded/DataJetEJERDown.root
	./Execute --Input Input/DataLeadingDiJetEJERDown.root --Output Unfolded/DataLeadingDiJetEJERDown.root
	./Execute --Input Input/DataLeadingDiJetSumEJERDown.root --Output Unfolded/DataLeadingDiJetSumEJERDown.root
	./Execute --Input Input/DataJetZGJERDown.root --Output Unfolded/DataJetZGJERDown.root
	./Execute --Input Input/DataJetRGJERDown.root --Output Unfolded/DataJetRGJERDown.root
	./Execute --Input Input/DataJetMGJERDown.root --Output Unfolded/DataJetMGJERDown.root
	./Execute --Input Input/DataJetMGEJERDown.root --Output Unfolded/DataJetMGEJERDown.root
	./Execute --Input Input/DataJetMJERDown.root --Output Unfolded/DataJetMJERDown.root
	./Execute --Input Input/DataJetMEJERDown.root --Output Unfolded/DataJetMEJERDown.root
	./ExecutePlot --Input Unfolded/DataJetEMCPrior.root --Original Input/DataJetENominal.root \
		--Output Plots/DataJetEMCPrior.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataLeadingDiJetEMCPrior.root --Original Input/DataLeadingDiJetENominal.root \
		--Output Plots/DataLeadingDiJetEMCPrior.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumEMCPrior.root --Original Input/DataLeadingDiJetSumENominal.root \
		--Output Plots/DataLeadingDiJetSumEMCPrior.pdf --Iteration 14
	./ExecutePlot --Input Unfolded/DataJetZGMCPrior.root --Original Input/DataJetZGNominal.root \
		--Output Plots/DataJetZGMCPrior.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGMCPrior.root --Original Input/DataJetRGNominal.root \
		--Output Plots/DataJetRGMCPrior.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGMCPrior.root --Original Input/DataJetMGNominal.root \
		--Output Plots/DataJetMGMCPrior.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGEMCPrior.root --Original Input/DataJetMGENominal.root \
		--Output Plots/DataJetMGEMCPrior.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetMMCPrior.root --Original Input/DataJetMNominal.root \
		--Output Plots/DataJetMMCPrior.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMEMCPrior.root --Original Input/DataJetMENominal.root \
		--Output Plots/DataJetMEMCPrior.pdf $(MEBin)
	./ExecutePlot --Input Unfolded/DataJetENoResidual.root --Original Input/DataJetENoResidual.root \
		--Output Plots/DataJetENoResidual.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetENoResidual.root --Original Input/DataLeadingDiJetENoResidual.root \
		--Output Plots/DataLeadingDiJetENoResidual.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumENoResidual.root --Original Input/DataLeadingDiJetSumENoResidual.root \
		--Output Plots/DataLeadingDiJetSumENoResidual.pdf
	./ExecutePlot --Input Unfolded/DataJetZGNoResidual.root --Original Input/DataJetZGNoResidual.root \
		--Output Plots/DataJetZGNoResidual.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGNoResidual.root --Original Input/DataJetRGNoResidual.root \
		--Output Plots/DataJetRGNoResidual.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGNoResidual.root --Original Input/DataJetMGNoResidual.root \
		--Output Plots/DataJetMGNoResidual.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGENoResidual.root --Original Input/DataJetMGENoResidual.root \
		--Output Plots/DataJetMGENoResidual.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetMNoResidual.root --Original Input/DataJetMNoResidual.root \
		--Output Plots/DataJetMNoResidual.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMENoResidual.root --Original Input/DataJetMENoResidual.root \
		--Output Plots/DataJetMENoResidual.pdf $(MEBin)
	./ExecutePlot --Input Unfolded/DataJetEJECUp.root --Original Input/DataJetEJECUp.root \
		--Output Plots/DataJetEJECUp.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetEJECUp.root --Original Input/DataLeadingDiJetEJECUp.root \
		--Output Plots/DataLeadingDiJetEJECUp.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumEJECUp.root --Original Input/DataLeadingDiJetSumEJECUp.root \
		--Output Plots/DataLeadingDiJetSumEJECUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECUp.root --Original Input/DataJetZGJECUp.root \
		--Output Plots/DataJetZGJECUp.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGJECUp.root --Original Input/DataJetRGJECUp.root \
		--Output Plots/DataJetRGJECUp.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGJECUp.root --Original Input/DataJetMGJECUp.root \
		--Output Plots/DataJetMGJECUp.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGEJECUp.root --Original Input/DataJetMGEJECUp.root \
		--Output Plots/DataJetMGEJECUp.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetMJECUp.root --Original Input/DataJetMJECUp.root \
		--Output Plots/DataJetMJECUp.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMEJECUp.root --Original Input/DataJetMEJECUp.root \
		--Output Plots/DataJetMEJECUp.pdf $(MEBin)
	./ExecutePlot --Input Unfolded/DataJetEJECDown.root --Original Input/DataJetEJECDown.root \
		--Output Plots/DataJetEJECDown.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetEJECDown.root --Original Input/DataLeadingDiJetEJECDown.root \
		--Output Plots/DataLeadingDiJetEJECDown.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumEJECDown.root --Original Input/DataLeadingDiJetSumEJECDown.root \
		--Output Plots/DataLeadingDiJetSumEJECDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECDown.root --Original Input/DataJetZGJECDown.root \
		--Output Plots/DataJetZGJECDown.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGJECDown.root --Original Input/DataJetRGJECDown.root \
		--Output Plots/DataJetRGJECDown.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGJECDown.root --Original Input/DataJetMGJECDown.root \
		--Output Plots/DataJetMGJECDown.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGEJECDown.root --Original Input/DataJetMGEJECDown.root \
		--Output Plots/DataJetMGEJECDown.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetMJECDown.root --Original Input/DataJetMJECDown.root \
		--Output Plots/DataJetMJECDown.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMEJECDown.root --Original Input/DataJetMEJECDown.root \
		--Output Plots/DataJetMEJECDown.pdf $(MEBin)
	./ExecutePlot --Input Unfolded/DataJetEJECHalfUp.root --Original Input/DataJetEJECHalfUp.root \
		--Output Plots/DataJetEJECHalfUp.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetEJECHalfUp.root --Original Input/DataLeadingDiJetEJECHalfUp.root \
		--Output Plots/DataLeadingDiJetEJECHalfUp.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumEJECHalfUp.root --Original Input/DataLeadingDiJetSumEJECHalfUp.root \
		--Output Plots/DataLeadingDiJetSumEJECHalfUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECHalfUp.root --Original Input/DataJetZGJECHalfUp.root \
		--Output Plots/DataJetZGJECHalfUp.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGJECHalfUp.root --Original Input/DataJetRGJECHalfUp.root \
		--Output Plots/DataJetRGJECHalfUp.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGJECHalfUp.root --Original Input/DataJetMGJECHalfUp.root \
		--Output Plots/DataJetMGJECHalfUp.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGEJECHalfUp.root --Original Input/DataJetMGEJECHalfUp.root \
		--Output Plots/DataJetMGEJECHalfUp.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetMJECHalfUp.root --Original Input/DataJetMJECHalfUp.root \
		--Output Plots/DataJetMJECHalfUp.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMEJECHalfUp.root --Original Input/DataJetMEJECHalfUp.root \
		--Output Plots/DataJetMEJECHalfUp.pdf $(MEBin)
	./ExecutePlot --Input Unfolded/DataJetEJECHalfDown.root --Original Input/DataJetEJECHalfDown.root \
		--Output Plots/DataJetEJECHalfDown.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetEJECHalfDown.root --Original Input/DataLeadingDiJetEJECHalfDown.root \
		--Output Plots/DataLeadingDiJetEJECHalfDown.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumEJECHalfDown.root --Original Input/DataLeadingDiJetSumEJECHalfDown.root \
		--Output Plots/DataLeadingDiJetSumEJECHalfDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJECHalfDown.root --Original Input/DataJetZGJECHalfDown.root \
		--Output Plots/DataJetZGJECHalfDown.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGJECHalfDown.root --Original Input/DataJetRGJECHalfDown.root \
		--Output Plots/DataJetRGJECHalfDown.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGJECHalfDown.root --Original Input/DataJetMGJECHalfDown.root \
		--Output Plots/DataJetMGJECHalfDown.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGEJECHalfDown.root --Original Input/DataJetMGEJECHalfDown.root \
		--Output Plots/DataJetMGEJECHalfDown.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetMJECHalfDown.root --Original Input/DataJetMJECHalfDown.root \
		--Output Plots/DataJetMJECHalfDown.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMEJECHalfDown.root --Original Input/DataJetMEJECHalfDown.root \
		--Output Plots/DataJetMEJECHalfDown.pdf $(MEBin)
	./ExecutePlot --Input Unfolded/DataJetEJERUp.root --Original Input/DataJetEJERUp.root \
		--Output Plots/DataJetEJERUp.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetEJERUp.root --Original Input/DataLeadingDiJetEJERUp.root \
		--Output Plots/DataLeadingDiJetEJERUp.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumEJERUp.root --Original Input/DataLeadingDiJetSumEJERUp.root \
		--Output Plots/DataLeadingDiJetSumEJERUp.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJERUp.root --Original Input/DataJetZGJERUp.root \
		--Output Plots/DataJetZGJERUp.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGJERUp.root --Original Input/DataJetRGJERUp.root \
		--Output Plots/DataJetRGJERUp.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGJERUp.root --Original Input/DataJetMGJERUp.root \
		--Output Plots/DataJetMGJERUp.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGEJERUp.root --Original Input/DataJetMGEJERUp.root \
		--Output Plots/DataJetMGEJERUp.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetMJERUp.root --Original Input/DataJetMJERUp.root \
		--Output Plots/DataJetMJERUp.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMEJERUp.root --Original Input/DataJetMEJERUp.root \
		--Output Plots/DataJetMEJERUp.pdf $(MEBin)
	./ExecutePlot --Input Unfolded/DataJetEJERDown.root --Original Input/DataJetEJERDown.root \
		--Output Plots/DataJetEJERDown.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetEJERDown.root --Original Input/DataLeadingDiJetEJERDown.root \
		--Output Plots/DataLeadingDiJetEJERDown.pdf
	./ExecutePlot --Input Unfolded/DataLeadingDiJetSumEJERDown.root --Original Input/DataLeadingDiJetSumEJERDown.root \
		--Output Plots/DataLeadingDiJetSumEJERDown.pdf
	./ExecutePlot --Input Unfolded/DataJetZGJERDown.root --Original Input/DataJetZGJERDown.root \
		--Output Plots/DataJetZGJERDown.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/DataJetRGJERDown.root --Original Input/DataJetRGJERDown.root \
		--Output Plots/DataJetRGJERDown.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/DataJetMGJERDown.root --Original Input/DataJetMGJERDown.root \
		--Output Plots/DataJetMGJERDown.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/DataJetMGEJERDown.root --Original Input/DataJetMGEJERDown.root \
		--Output Plots/DataJetMGEJERDown.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/DataJetMJERDown.root --Original Input/DataJetMJERDown.root \
		--Output Plots/DataJetMJERDown.pdf $(MBin)
	./ExecutePlot --Input Unfolded/DataJetMEJERDown.root --Original Input/DataJetMEJERDown.root \
		--Output Plots/DataJetMEJERDown.pdf $(MEBin)

RunMCUnfold: Execute ExecutePlot
	./Execute --Input Input/MCJetENominal.root --Output Unfolded/MCJetENominal.root
	./Execute --Input Input/MCLeadingDiJetENominal.root --Output Unfolded/MCLeadingDiJetENominal.root
	./Execute --Input Input/MCLeadingDiJetSumENominal.root --Output Unfolded/MCLeadingDiJetSumENominal.root
	./Execute --Input Input/MCJetZGNominal.root --Output Unfolded/MCJetZGNominal.root
	./Execute --Input Input/MCJetRGNominal.root --Output Unfolded/MCJetRGNominal.root
	./Execute --Input Input/MCJetMGNominal.root --Output Unfolded/MCJetMGNominal.root
	./Execute --Input Input/MCJetMGENominal.root --Output Unfolded/MCJetMGENominal.root
	./Execute --Input Input/MCJetMGELowECut.root --Output Unfolded/MCJetMGELowECut.root
	./Execute --Input Input/MCJetMNominal.root --Output Unfolded/MCJetMNominal.root
	./Execute --Input Input/MCJetMENominal.root --Output Unfolded/MCJetMENominal.root
	./Execute --Input Input/MCJetMELowECut.root --Output Unfolded/MCJetMELowECut.root
	./ExecutePlot --Input Unfolded/MCJetENominal.root --Original Input/MCJetENominal.root \
		--Output Plots/MCJetENominal.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCLeadingDiJetENominal.root --Original Input/MCLeadingDiJetENominal.root \
		--Output Plots/MCLeadingDiJetENominal.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCLeadingDiJetSumENominal.root --Original Input/MCLeadingDiJetSumENominal.root \
		--Output Plots/MCLeadingDiJetSumENominal.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCJetZGNominal.root --Original Input/MCJetZGNominal.root \
		--Output Plots/MCJetZGNominal.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/MCJetRGNominal.root --Original Input/MCJetRGNominal.root \
		--Output Plots/MCJetRGNominal.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/MCJetMGNominal.root --Original Input/MCJetMGNominal.root \
		--Output Plots/MCJetMGNominal.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/MCJetMGENominal.root --Original Input/MCJetMGENominal.root \
		--Output Plots/MCJetMGENominal.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/MCJetMGELowECut.root --Original Input/MCJetMGELowECut.root \
		--Output Plots/MCJetMGELowECut.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/MCJetMNominal.root --Original Input/MCJetMNominal.root \
		--Output Plots/MCJetMNominal.pdf $(MBin)
	./ExecutePlot --Input Unfolded/MCJetMENominal.root --Original Input/MCJetMENominal.root \
		--Output Plots/MCJetMENominal.pdf $(MEBin)
	./ExecutePlot --Input Unfolded/MCJetMELowECut.root --Original Input/MCJetMELowECut.root \
		--Output Plots/MCJetMELowECut.pdf $(MEBin)

RunMCFakeUnfold: Execute ExecutePlot
	./Execute --Input Input/MCJetENominal.root --Output Unfolded/MCJetEFake.root --InputName HMCMatched
	./Execute --Input Input/MCLeadingDiJetENominal.root --Output Unfolded/MCLeadingDiJetEFake.root --InputName HMCMatched
	./Execute --Input Input/MCLeadingDiJetSumENominal.root --Output Unfolded/MCLeadingDiJetSumEFake.root --InputName HMCMatched
	./Execute --Input Input/MCJetZGNominal.root --Output Unfolded/MCJetZGFake.root --InputName HMCMatched
	./Execute --Input Input/MCJetRGNominal.root --Output Unfolded/MCJetRGFake.root --InputName HMCMatched
	./Execute --Input Input/MCJetMGNominal.root --Output Unfolded/MCJetMGFake.root --InputName HMCMatched
	./Execute --Input Input/MCJetMGENominal.root --Output Unfolded/MCJetMGEFake.root --InputName HMCMatched
	./Execute --Input Input/MCJetMNominal.root --Output Unfolded/MCJetMFake.root --InputName HMCMatched
	./Execute --Input Input/MCJetMENominal.root --Output Unfolded/MCJetMEFake.root --InputName HMCMatched
	./ExecutePlot --Input Unfolded/MCJetEFake.root --Original Input/MCJetENominal.root \
		--Output Plots/MCJetEFake.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCLeadingDiJetEFake.root --Original Input/MCLeadingDiJetENominal.root \
		--Output Plots/MCLeadingDiJetEFake.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCLeadingDiJetSumEFake.root --Original Input/MCLeadingDiJetSumENominal.root \
		--Output Plots/MCLeadingDiJetSumEFake.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCJetZGFake.root --Original Input/MCJetZGNominal.root \
		--Output Plots/MCJetZGFake.pdf $(ZGBin)
	./ExecutePlot --Input Unfolded/MCJetRGFake.root --Original Input/MCJetRGNominal.root \
		--Output Plots/MCJetRGFake.pdf $(RGBin)
	./ExecutePlot --Input Unfolded/MCJetMGFake.root --Original Input/MCJetMGNominal.root \
		--Output Plots/MCJetMGFake.pdf $(MGBin)
	./ExecutePlot --Input Unfolded/MCJetMGEFake.root --Original Input/MCJetMGENominal.root \
		--Output Plots/MCJetMGEFake.pdf $(MGEBin)
	./ExecutePlot --Input Unfolded/MCJetMFake.root --Original Input/MCJetMNominal.root \
		--Output Plots/MCJetMFake.pdf $(MBin)
	./ExecutePlot --Input Unfolded/MCJetMEFake.root --Original Input/MCJetMENominal.root \
		--Output Plots/MCJetMEFake.pdf $(MEBin)

RunMCSmearSumEUnfold: Execute ExecutePlot
	./Execute --Input Input/MCLeadingDiJetESmearedSumE.root --Output Unfolded/MCLeadingDiJetESmearedSumE.root --InputName HMCMatched
	./Execute --Input Input/MCLeadingDiJetSumESmearedSumE.root --Output Unfolded/MCLeadingDiJetSumESmearedSumE.root --InputName HMCMatched
	./ExecutePlot --Input Unfolded/MCLeadingDiJetESmearedSumE.root --Original Input/MCLeadingDiJetESmearedSumE.root \
		--Output Plots/MCLeadingDiJetESmearedSumE.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCLeadingDiJetSumESmearedSumE.root --Original Input/MCLeadingDiJetSumESmearedSumE.root \
		--Output Plots/MCLeadingDiJetSumESmearedSumE.pdf --Iteration 2

RunMCNoJECUnfold: Execute ExecutePlot
	./Execute --Input Input/MCJetENoJEC.root --Output Unfolded/MCJetENoJEC.root
	./ExecutePlot --Input Unfolded/MCJetENoJEC.root --Original Input/MCJetENoJEC.root \
		--Output Plots/MCJetENoJEC.pdf

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute

ExecutePlot: MakeSummaryPlot.cpp
	CompileRootMacro MakeSummaryPlot.cpp ExecutePlot
