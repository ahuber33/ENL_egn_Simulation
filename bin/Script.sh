 #!/bin/bash


echo "Début de traitement"
myArr=("10" "11" "12" "14" "16" "17" "18" "19" "20" "25" "30" "40" "50")

for idx in ${!myArr[*]}
do
    while [[ $(pgrep -x ENLegnSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
        #Init
        value=${myArr[$idx]}
        idx_fichier=$(($idx))
        echo Index : $idx / Fichier : $value
        # Creation du fichier a partir du fichier de base (fichier temporaire)
        cp vrml_base.mac base_$idx_fichier_bis.mac
        # Mise en place de la variable
        sed -e "s/%energy/$value/g" base_$idx_fichier_bis.mac > base_$idx_fichier.mac
        # Suppression fichier temporaire
        rm base_$idx_fichier_bis.mac
	./ENLegnSim Section_efficace_gn_Tungstene_${myArr[$idx]}MeV 10000000 base_$idx_fichier.mac &
	sleep 5
done
echo "Fin de traitement"


