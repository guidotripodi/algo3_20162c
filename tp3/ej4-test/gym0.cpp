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

#define ya chrono::high_resolution_clock::now
using namespace std;

//variables globales definidas en ej4.hpp

#define TEST_ITER 20

#define MAX_CANT_PP 20
#define MAX_CANT_GYMS 20

int main(){
    
    int j = 8;
    cantGyms = j+1;
    cantPokeParadas = j;
    pair <pair<int,int>, int> gimnasiosArr[MAX_CANT_GYMS];
    pair <int, int>  pokeParadasArr[MAX_CANT_PP];
    pair <int, int>  pokeParadasAux[MAX_CANT_PP];
    
    vector<long long> tiempos(TEST_ITER);
    vector<int> solucionMejorada;
    vector<int> solucionParcial;
    
    int i = 0;
    for (i = 0; i < cantGyms; i++)
    {
        Gimnasio gymPuebloPaleta;
        gymPuebloPaleta.first.first = i;
        gymPuebloPaleta.first.second = i+1;
        if( i % 2 == 0)
        {
            gymPuebloPaleta.second = 0;
        } else
        {
            gymPuebloPaleta.second  = i;
        }
        gimnasiosArr[i] = gymPuebloPaleta;
    }
    for (i = 0; i < cantPokeParadas; i++)
    {
        Pokeparada posicion;
        posicion.first = i;
        posicion.second = i+2;
        pokeParadasArr[i] = posicion;
        pokeParadasAux[i] = posicion;
    }
    
    capMochila = cantGyms*3;
    
    //Llamada a la heuristica(ej2)
    pair < int, list<int> * > * solucionInicial = algoritmoResolucion(
                                                                      cantGyms,
                                                                      cantPokeParadas,
                                                                      capMochila,
                                                                      gimnasiosArr,
                                                                      pokeParadasArr,
                                                                      pokeParadasAux);
    
    
    list<int> *solucionInicialLista = solucionInicial->second;
    
    list<int>::iterator itLista;
    
    /*
     for(itLista = solucionInicialLista->begin();
     itLista != solucionInicialLista->end();
     itLista++ )
     {
     printf("%d ", *itLista);
     }
     cout << "\n";
     */
    
    for(itLista = solucionInicialLista->begin();
        itLista != solucionInicialLista->end();
        itLista++ )
    {
        solucionParcial.push_back(*itLista);
    }
    
    gimnasiosArrPtr = gimnasiosArr;
    pokeParadasArrPtr = pokeParadasAux;
    
    //mejorar solucion
    if(solucionParcial.size()) {
        for(int it = 0; it < TEST_ITER; it++) {
            auto start = ya();
            solucionMejorada = tabuSearch(solucionParcial);
            auto end = ya();
            tiempos[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        }
        
        pair <float, float> estadisticas = mediaPodadaVarianzaMuestral(tiempos);
        
        long long mejoraParcial = calcularCosto(solucionParcial);
        
        long long mejoraMejorada = calcularCosto(solucionMejorada);
        
        //long long mejora =  mejoraInicial - mejoraMejorada;
        
        cout << estadisticas.first << " "
        << estadisticas.second << " "
        << mejoraParcial << " "
        << mejoraMejorada << "\n";

        for(int i = 0; i < (int) solucionParcial.size(); i++)
            cout << solucionParcial[i] << " ";
        cout << "\n";
        
        for(int i = 0; i < (int) solucionMejorada.size(); i++)
            cout << solucionMejorada[i] << " ";
        cout << "\n";
    }else {
        printf("%d", -1);
    }
    
    delete solucionInicial;
    
    return 0;
}

