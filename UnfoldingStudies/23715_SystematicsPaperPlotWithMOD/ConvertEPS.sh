for i in `ls Plots/ | grep eps$`
do
   ps2pdf -dPDFSETTINGS=/prepress -dEPSCrop -dPDFFitPage Plots/$i Plots/${i/eps/pdf}
   convert -density 150 Plots/${i/eps/pdf} Plots/${i/eps/png}
done
