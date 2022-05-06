#!/bin/bash

Prefix=$1
shift
Suffix=$1
shift
Tag=$1
shift

# ObservableList="JetE LeadingDiJetE LeadingDiJetSumE JetZG JetRG JetMG JetMGE JetMGELowE JetM JetME JetMELowE"
ObservableList="JetE LeadingDiJetE LeadingDiJetSumE JetZG JetRG JetMG JetMGE JetM JetME"
# ObservableList="JetE"

ZGBin="--GenPrimaryMin -0.010 --GenPrimaryMax 0.50 --RecoPrimaryMin -0.010 --RecoPrimaryMax 0.50"
RGBin="--GenPrimaryMin -0.015 --GenPrimaryMax 0.75 --RecoPrimaryMin -0.015 --RecoPrimaryMax 0.75"
MGBin="--GenPrimaryMin -0.1 --GenPrimaryMax 15 --RecoPrimaryMin -0.1 --RecoPrimaryMax 15"
MGEBin="--GenPrimaryMin -0.015 --GenPrimaryMax 0.75 --RecoPrimaryMin -0.015 --RecoPrimaryMax 0.75"
MBin="--GenPrimaryMin 0 --GenPrimaryMax 15 --RecoPrimaryMin 0 --RecoPrimaryMax 15"
MEBin="--GenPrimaryMin 0 --GenPrimaryMax 0.75 --RecoPrimaryMin 0 --RecoPrimaryMax 0.75"


echo "Prefix = $Prefix, Suffix = $Suffix, Tag = $Tag"

for Observable in $ObservableList
do
   echo "   Running Observable $Observable"

   POS=${Prefix}${Observable}${Suffix}
   POT=${Prefix}${Observable}${Tag}

   IPOS=Input/$POS.root
   if [[ "$Prefix" = "Toy"* ]]; then
      IPOS=InputToy/$POS.root
   fi
   OPOT=Unfolded/$POT.root

   Bin=
   if [[ $Observable == "JetZG" ]]; then
      Bin=$ZGBin
   elif [[ $Observable == "JetRG" ]]; then
      Bin=$RGBin
   elif [[ $Observable == "JetMG" ]]; then
      Bin=$MGBin
   elif [[ $Observable == "JetMGE" ]]; then
      Bin=$MGEBin
   elif [[ $Observable == "JetM" ]]; then
      Bin=$MBin
   elif [[ $Observable == "JetME" ]]; then
      Bin=$MEBin
   fi

	./Execute --Input $IPOS --Output $OPOT --DoToyError false --DoFit false $@
	# ./ExecutePlot --Input $OPOT --Original $IPOS --Output Plots/$POT.pdf $Bin
done



