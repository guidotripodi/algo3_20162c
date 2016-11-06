#include <iostream>	/* printf, cout*/
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>
#include <chrono>  /* clock */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>	/* pow */
#include <cstdlib> /* swap */
#include <list>
#include "ej4.hpp"

using namespace std;

//variables globales definidas en ej4.hpp

#define MAX_CANT_PP 20
#define MAX_CANT_GYMS 20

int main(){

    int test = 0;
    
    cin >> test;
    
    int j = 8;
    cantGyms = j+1;
    cantPokeParadas = j;
    pair <pair<int,int>, int> gimnasiosArr[MAX_CANT_GYMS];
    pair <int, int>  pokeParadasArr[MAX_CANT_PP];
    pair <int, int>  pokeParadasAux[MAX_CANT_PP];

    for (int i = 0; i < cantGyms; i++){
        pair <pair<int,int>, int> gymPuebloPaleta;
        gymPuebloPaleta.first.first = i;
        gymPuebloPaleta.first.second = i+1;
        gymPuebloPaleta.second = 0;
        gimnasiosArr[i] = gymPuebloPaleta;
        
    }
    
    for (int i = 0; i < cantPokeParadas; i++)	{
        pair <int, int> posicion;
        posicion.first = i;
        posicion.second = i+2;
        pokeParadasAux[i] = posicion;
        pokeParadasAux[i] = posicion;
    }
    
    capMochila = cantGyms*3;
    
    testear(
            cantGyms,
            cantPokeParadas,
            capMochila,
            gimnasiosArr,
            pokeParadasArr,
            pokeParadasAux, test);
    
    return 0;
}

