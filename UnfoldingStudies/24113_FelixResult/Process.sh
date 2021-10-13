grep "^[0-9]" 2jet.tsv | tr '\n' ' ' | Reformat 8 | awk '{print $1,$5,$2,$3,$4}' | TextToTree 2jet.root 5 "XMin:XMax:YMin:YMax:Y"
grep "^[0-9]" inclusive.tsv | tr '\n' ' ' | Reformat 8 | awk '{print $1,$5,$2,$3,$4}' | TextToTree inclusive.root 5 "XMin:XMax:YMin:YMax:Y"
