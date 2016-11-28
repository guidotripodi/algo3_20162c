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

#define INSTANCIAS 20

int main(){

	cout
		<< "tamaño,"
		<< "distancia goloso,"
		<< "distancia tabu,"
		<< "tiempo tabu\n";
	
	int* tams = new int[INSTANCIAS];
	long long* mejorasParciales = new long long[INSTANCIAS];
	long long* mejorasLocal = new long long[INSTANCIAS];
	long long* tiempos = new long long[INSTANCIAS];

    for(int j = 0; j < INSTANCIAS; j++)
    {
        cin >> cantGyms >> cantPokeParadas >> capMochila;
       
		int size = cantGyms + cantPokeParadas;
        pair <pair<int,int>, int>* gimnasiosArr = new pair <pair<int,int>, int>[size];
        pair <int, int>*  pokeParadasArr = new pair<int, int>[size];
        pair <int, int>*  pokeParadasAux = new pair<int, int>[size];
        
        for (int i = 0; i < cantGyms; i++)
        {
            Gimnasio gymPuebloPaleta;
        
            cin >> gymPuebloPaleta.first.first >> gymPuebloPaleta.first.second >> gymPuebloPaleta.second;
            
            gimnasiosArr[i] = gymPuebloPaleta;
        }
        for (int i = 0; i < cantPokeParadas; i++)
        {
            Pokeparada posicion;

            cin >> posicion.first >> posicion.second;
            
            pokeParadasArr[i] = posicion;
            pokeParadasAux[i] = posicion;
        }
        
        pair< pair<long long, long long>, long long> test = testear(
                cantGyms,
                cantPokeParadas,
                capMochila,
                gimnasiosArr,
                pokeParadasArr,
                pokeParadasAux);

		long long tiempoLocal = test.first.first;
		long long distanciaLocal = test.first.second;
		long long distanciaGoloso = test.second;

		cout 
			<< cantGyms + cantPokeParadas << ","
			<< distanciaGoloso << ","
			<< distanciaLocal << ","
			<< tiempoLocal << ",";
		
		tams[j] = cantGyms + cantPokeParadas;
		mejorasParciales[j] = distanciaGoloso;
		mejorasLocal[j] = distanciaLocal;
		tiempos[j] = tiempoLocal;
			
		delete[] gimnasiosArr;
		delete[] pokeParadasArr;
		delete[] pokeParadasAux;
    }
    
    cout 
		<< "tamaño,"
		<< "promedio tiempos,"
		<< "promedio distancias goloso,"
		<< "promedio distancias tabu,"
		<< "promedio porcentaje\n";
	
	int h = 0;
	while(h < INSTANCIAS)
	{
		long long inst = 0;
		int tam = tams[h];
		long long acumTiempos = 0;
		long long acumMejoraGoloso = 0;
		long long acumMejoraLocal = 0;
		while(tams[h] == tam)
		{

			if(	mejorasParciales[h]== 0 ||
					mejorasParciales[h] == -1)
			{//INSTANCIA INVALIDA
				h++;
			}
			else
			{
				acumTiempos += tiempos[h];
				acumMejoraLocal += mejorasLocal[h];
				acumMejoraGoloso += mejorasParciales[h];
				inst++;
				h++;
			}
		}

		float promLocal = (float)(acumMejoraLocal / inst);
		float promGoloso = (float)(acumMejoraGoloso / inst);
		float promPerc = (float) 100 - ((promLocal * 100 )/ promGoloso);
		
		cout 
			<< tam << ","
			<< (float) (acumTiempos / inst) << ","
			<< promGoloso << ","
			<< promLocal<< ","
			<< promPerc << "\n";
	}

    
    return 0;
}
