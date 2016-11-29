#!/bin/bash

#ATENCION: esto es muy croto


cp alfa.cpp randomRtp.cpp
cp ej4a2opt.cpp ej4.cpp
make
./randomRtp.test < ../entradas-rtp/familiaWeak.txt > ../salidas-rtp/outFamiliaWeak2optA.csv
echo "!!! test A familiaWeak 2opt"
./randomRtp.test < ../entradas-rtp/randomWeak.txt > ../salidas-rtp/outRandomWeak2optA.csv
echo "!!! test A randomWeak 2opt"
cp ej4aswap.cpp ej4.cpp
make
./randomRtp.test < ../entradas-rtp/familiaWeak.txt > ../salidas-rtp/outFamiliaWeakSwapA.csv
echo "!!! test A familiaWeak Swap"
./randomRtp.test < ../entradas-rtp/randomWeak.txt > ../salidas-rtp/outRandomWeakSwapA.csv
echo "!!! test A randomWeak Swap"
cp bravo.cpp randomRtp
cp ej4b2opt ej4.cpp
make
./randomRtp.test < ../entradas-rtp/familiaWeak.txt > ../salidas-rtp/outFamiliaWeak2optB.csv
echo "!!! test B familiaWeak 2opt"
./randomRtp.test < ../entradas-rtp/randomWeak.txt > ../salidas-rtp/outRandomWeak2optB.csv
echo "!!! test B randomWeak 2opt"
cp ej4bswap.cpp ej4.cpp
make
./randomRtp.test < ../entradas-rtp/familiaWeak.txt > ../salidas-rtp/outFamiliaWeakSwapB.csv
echo "!!! test B familiaWeak Swap"
./randomRtp.test < ../entradas-rtp/randomWeak.txt > ../salidas-rtp/outRandomWeakSwapB.csv
echo "!!! test B randomWeak Swap"
