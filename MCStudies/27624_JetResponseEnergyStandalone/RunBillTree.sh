mkdir -p Matched

for R in 1 2 3 4 5 6 8 10 12
do
   echo "Matching R = $R" now...

   RR=`echo $R | DivideConst 10`
   RR=`printf "%.1f" $RR`

   if [[ $R == 8 ]]; then
      Tree="t_r$RR"
   else
      Tree="t_R$RR"
   fi

   ./Execute --RecoFileName 20250409_BillTrees/JetClustering_t_R${R}_4MC.root \
		--GenFileName 20250409_BillTrees/JetClustering_tgen_R${R}_4MC.root \
		--Output Matched/MatchedR${R}.root \
		--RecoTree "${Tree}" \
		--GenTree "${Tree}" \
		--JEC JECR${R}.txt \
		--Fraction 1.00

	./ExecuteJEC --File Matched/MatchedR${R}.root \
      --Tree MatchedTree \
      --Output JECR${R}.txt \
      --Check JECCheckR${R}.pdf --R $RR

   ./Execute --RecoFileName 20250409_BillTrees/JetClustering_t_R${R}_4MC.root \
		--GenFileName 20250409_BillTrees/JetClustering_tgen_R${R}_4MC.root \
		--Output Matched/MatchedR${R}.root \
		--RecoTree "${Tree}" \
		--GenTree "${Tree}" \
		--JEC JECR${R}.txt \
		--Fraction 1.00
done
