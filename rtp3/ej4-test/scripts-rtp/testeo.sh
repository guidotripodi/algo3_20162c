#!/bin/bash

#ATENCION: esto es muy croto


cp alfa.cpp randomRtp.cpp
cp ej4a2opt.cpp ej4.cpp
make
./randomRtp.test < ../entradas-rtp/familiaWeak.txt > ../salidas-rtp/outFamiliaWeak2optA.csv
./randomRtp.test < ../entradas-rtp/randomWeak.txt > ../salidas-rtp/outRandomWeak2optA.csv
cp ej4aswap.cpp ej4.cpp
make
./randomRtp.test < ../entradas-rtp/familiaWeak.txt > ../salidas-rtp/outFamiliaWeakSwapA.csv
./randomRtp.test < ../entradas-rtp/randomWeak.txt > ../salidas-rtp/outRandomWeakSwapA.csv
cp bravo.cpp randomRtp
cp ej4b2opt ej4.cpp
make
./randomRtp.test < ../entradas-rtp/familiaWeak.txt > ../salidas-rtp/outFamiliaWeak2optB.csv
./randomRtp.test < ../entradas-rtp/randomWeak.txt > ../salidas-rtp/outRandomWeak2optB.csv
cp ej4bswap.cpp ej4.cpp
make
./randomRtp.test < ../entradas-rtp/familiaWeak.txt > ../salidas-rtp/outFamiliaWeakSwapB.csv
./randomRtp.test < ../entradas-rtp/randomWeak.txt > ../salidas-rtp/outRandomWeakSwapB.csv
