
ThrustBin = --GenPrimaryMin 0.6 --GenPrimaryMax 1.0 --RecoPrimaryMin 0.6 --RecoPrimaryMax 1.0

default: RunDataUnfoldFineRecoBin RunDataUnfoldMCPrior

UnfoldAll: RunDataUnfoldNominal RunDataUnfold RunMCUnfold RunMCFakeUnfold RunThrustUnfold UnfoldIterations RunDataUnfoldFloored RunDataUnfoldTighter RunFakeDataUnfoldNominal RunDataUnfoldNoNeutral RunDataUnfoldGenWeight RunDataUnfoldSJSmear

UnfoldIterations: RunIterationStudies RunDataIterationStudies

Prepare:
	rm -f Input InputToy
	ln -sf ../23411_UnfoldingPreparation/Output Input
	ln -sf ../23412_FakeData/Output InputToy
	mkdir -p Unfolded Plots

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute -lUnfold

ExecutePlot: MakeSummaryPlot.cpp
	CompileRootMacro MakeSummaryPlot.cpp ExecutePlot

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
	bash RunSet.sh Toy Nominal Nominal

RunDataIterationStudies: Execute ExecutePlot
	bash RunSet.sh ToyData Nominal Nominal

RunDataUnfoldNominal: Execute ExecutePlot
	bash RunSet.sh Data Nominal Nominal

RunDataUnfoldGenWeight: Execute ExecutePlot
	# bash RunSet.sh Data GenReweightN05Test GenReweightN05Test --DoSVD false
	# bash RunSet.sh Data GenReweightN10Test GenReweightN10Test --DoSVD false
	# bash RunSet.sh Data GenReweightN15Test GenReweightN15Test --DoSVD false
	bash RunSet.sh Data GenReweightZGDown  GenReweightZGDown  --DoSVD false
	bash RunSet.sh Data GenReweightZGUp    GenReweightZGUp    --DoSVD false
	bash RunSet.sh Data GenReweightRGDown  GenReweightRGDown  --DoSVD false
	bash RunSet.sh Data GenReweightRGUp    GenReweightRGUp    --DoSVD false

RunDataUnfoldNoNeutral: Execute ExecutePlot
	bash RunSet.sh Data NoNeutral NoNeutral

RunFakeDataUnfoldNominal: Execute ExecutePlot
	bash RunSet.sh FakeData Nominal Nominal

RunDataUnfoldFloored: Execute ExecutePlot
	bash RunSet.sh Data Floored Floored

RunDataUnfoldTighter: Execute ExecutePlot
	bash RunSet.sh Data Tighter Tighter

RunDataUnfoldFineRecoBin: Execute ExecutePlot
	bash RunSet.sh Data FineRecoBin     FineRecoBin     --Prior MC
	bash RunSet.sh Data VeryFineRecoBin VeryFineRecoBin --Prior MC

RunDataUnfoldSJSmear: Execute ExecutePlot
	bash RunSet.sh Data SJSmear         SJSmear

RunDataUnfoldMCPrior: Execute
	bash RunSet.sh Data Nominal        MCPrior       --Prior MC

RunDataUnfold: Execute ExecutePlot
	bash RunSet.sh Data LargeThetaGap  LargeThetaGap
	bash RunSet.sh Data PositiveTheta  PositiveTheta
	bash RunSet.sh Data NegativeTheta  NegativeTheta
	bash RunSet.sh Data NoResidual     NoResidual
	bash RunSet.sh Data JECUp          JECUp
	bash RunSet.sh Data JECDown        JECDown
	bash RunSet.sh Data JECHalfUp      JECHalfUp
	bash RunSet.sh Data JECHalfDown    JECHalfDown
	bash RunSet.sh Data JERUp          JERUp
	bash RunSet.sh Data JERDown        JERDown
	./Execute --Input Input/DataLeadingDiJetELowerSumE.root --Output Unfolded/DataLeadingDiJetELowerSumE.root
	./Execute --Input Input/DataLeadingDiJetSumELowerSumE.root --Output Unfolded/DataLeadingDiJetSumELowerSumE.root
	./Execute --Input Input/DataLeadingDiJetEHigherSumE.root --Output Unfolded/DataLeadingDiJetEHigherSumE.root
	./Execute --Input Input/DataLeadingDiJetSumEHigherSumE.root --Output Unfolded/DataLeadingDiJetSumEHigherSumE.root

RunMCUnfold: Execute ExecutePlot
	bash RunSet.sh MC Nominal

RunMCFakeUnfold: Execute ExecutePlot
	bash RunSet.sh MC Nominal  Fake --InputName HMCMatched

RunMCSmearSumEUnfold: Execute ExecutePlot
	./Execute --Input Input/MCLeadingDiJetESmearedSumE.root --Output Unfolded/MCLeadingDiJetESmearedSumE.root --InputName HMCMatched
	./Execute --Input Input/MCLeadingDiJetSumESmearedSumE.root --Output Unfolded/MCLeadingDiJetSumESmearedSumE.root --InputName HMCMatched
	./ExecutePlot --Input Unfolded/MCLeadingDiJetESmearedSumE.root --Original Input/MCLeadingDiJetESmearedSumE.root \
		--Output Plots/MCLeadingDiJetESmearedSumE.pdf --Iteration 2
	./ExecutePlot --Input Unfolded/MCLeadingDiJetSumESmearedSumE.root --Original Input/MCLeadingDiJetSumESmearedSumE.root \
		--Output Plots/MCLeadingDiJetSumESmearedSumE.pdf --Iteration 2

RunMCNoJECUnfold: Execute ExecutePlot
	bash RunSet.sh MC NoJEC NoJEC


