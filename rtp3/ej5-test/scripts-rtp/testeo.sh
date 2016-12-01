#!/bin/bash

#ATENCION: esto es muy croto
CASOA="../entradas-rtp/familiaWeak15x550.txt"
CASOB="../entradas-rtp/randomWeak15x550.txt"
OUTA="familiaChico"
OUTB="randomChico"

cp alfa.cpp randomRtp.cpp
cp ej4a2opt.cpp ej4.cpp
make
./randomRtp.test < $CASOA > "../salidas-rtp/"$OUTA"2optA.csv"
echo "!!! test A "$OUTA" 2opt"
./randomRtp.test < $CASOB > "../salidas-rtp/"$OUTB"2optA.csv"
echo "!!! test A "$OUTB" 2opt"
cp ej4aswap.cpp ej4.cpp
make
./randomRtp.test < $CASOA > "../salidas-rtp/"$OUTA"SwapA.csv"
echo "!!! test A "$OUTA" Swap"
./randomRtp.test < $CASOB > "../salidas-rtp/"$OUTB"SwapA.csv"
echo "!!! test A "$OUTB" Swap"
cp bravo.cpp randomRtp
cp ej4b2opt.cpp ej4.cpp
make
./randomRtp.test < $CASOA > "../salidas-rtp/"$OUTA"2optB.csv"
echo "!!! test B "$OUTA" 2opt"
./randomRtp.test < $CASOB > "../salidas-rtp/"$OUTB"2optB.csv"
echo "!!! test B "$OUTB" 2opt"
cp ej4bswap.cpp ej4.cpp
make
./randomRtp.test < $CASOA > "../salidas-rtp/"$OUTA"SwapB.csv"
echo "!!! test B"$OUTA" Swap"
./randomRtp.test < $CASOB > "../salidas-rtp/"$OUTB"SwapB.csv"
echo "!!! test B "$OUTB" Swap"
cp charlie.cpp randomRtp.cpp
cp ej4c2opt.cpp ej4.cpp
make
./randomRtp.test < $CASOA > "../salidas-rtp/"$OUTA"2optC.csv"
echo "!!! test C "$OUTA" 2opt"
./randomRtp.test < $CASOB > "../salidas-rtp/"$OUTB"2optC.csv"
echo "!!! test C "$OUTB" 2opt"
cp ej4cswap.cpp ej4.cpp
make
./randomRtp.test < $CASOA > "../salidas-rtp/"$OUTA"SwapC.csv"
echo "!!! test C "$OUTA" Swap"
./randomRtp.test < $CASOB > "../salidas-rtp/"$OUTB"SwapC.csv"
echo "!!! test C "$OUTB" Swap"
