 #!/bin/bash


echo "Début de traitement"
myArr=("1" "10" "50" "10" "20")

for idx in ${!myArr[*]}
do
    while [[ $(pgrep -x ENLegnSim | wc -l) -gt 4 ]]
    do 
echo "Boucle"
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
	./ENLegnSim test_${myArr[$idx]}MeV 1000000 base_$idx_fichier.mac &
	sleep 1
done
echo "Fin de traitement"


