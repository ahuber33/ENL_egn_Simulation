 #!/bin/bash

#energy[1]=1000
#energy[2]=5000

#for (( i=1 ; i<=2 ; i++ ))
#do

#  sed -e "s/%energy/"${energy[i]}"/g" vrml_base.mac > test_${i}.mac
 

# ./TPSim Dolphy_Beta_662keV_1000µSv_${i} 82663758 vrml_662keV.mac &
 #  sleep 10



#done

 #./TPSim Dolphy_Beta_662keV_1000µSv_10 82663758 vrml_662keV.mac 



echo "Début de traitement"
myArr=("10" "100" "250" "500" "750" "1000" "1500" "2000" "3000" "4000" "5000" "10000")

for idx in ${!myArr[*]}
do
    while [[ $(pgrep -x TPSim | wc -l) -gt 4 ]]
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
	./TPSim Cuivre_proton_${myArr[$idx]}keV 100000 base_$idx_fichier.mac &
	sleep 5
done
echo "Fin de traitement"


