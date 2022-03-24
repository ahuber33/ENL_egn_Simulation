 #!/bin/bash


for (( i=1 ; i<=10 ; i++ ))
do
    while [[ $(pgrep -x ENLegnSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
    ./ENLegnSim a_${i} 100000 vrml.mac &
    sleep 10
    done
