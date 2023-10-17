

for i in `ls Plots/*${1}* | grep eps$`
do
   j=`basename $i`
   ps2pdf -dPDFSETTINGS=/prepress -dEPSCrop -dPDFFitPage Plots/$j Plots/${j/eps/pdf}
   convert -density 150 Plots/${j/eps/pdf} Plots/${j/eps/png}
done
