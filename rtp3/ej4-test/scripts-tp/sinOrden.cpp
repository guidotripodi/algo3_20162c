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

#define MAX_CANT_PP 100
#define MAX_CANT_GYMS 101

#define MAX_SIZE 20

int main(){
    
    for(int j = 0; j < MAX_SIZE; j++)
    {
        cantGyms = j;
        cantPokeParadas = j*2;
        pair <pair<int,int>, int> gimnasiosArr[MAX_CANT_GYMS];
        pair <int, int>  pokeParadasArr[MAX_CANT_PP];
        pair <int, int>  pokeParadasAux[MAX_CANT_PP];
        
        for (int i = 0; i < cantGyms; i++)
        {
            Gimnasio gymPuebloPaleta;
            gymPuebloPaleta.first.first = i;
            gymPuebloPaleta.first.second = i+1;
            if (i % 2 == 0){
                gymPuebloPaleta.second = 3;
            }else{
                gymPuebloPaleta.second = 6;
            }
            gimnasiosArr[i] = gymPuebloPaleta;
        }
        for (int i = 0; i < cantPokeParadas; i++)
        {
            Pokeparada posicion;
            posicion.first = i;
            posicion.second = i+2;
            pokeParadasArr[i] = posicion;
            pokeParadasAux[i] = posicion;
        }
        
        capMochila = MAX_CANT_GYMS*3;
        
        testear(
                cantGyms,
                cantPokeParadas,
                capMochila,
                gimnasiosArr,
                pokeParadasArr,
                pokeParadasAux);
    }
    
    return 0;
}
