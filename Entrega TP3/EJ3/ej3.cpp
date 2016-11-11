#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>
#include <chrono>
#include <math.h>
#include <cstdlib>
#include "MaestroPokemon.hpp"
#define ya chrono::high_resolution_clock::now
#define SEED 39
#define MAX_PODER 25
#define RADIO 100

using namespace std;

typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;

pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[]);
vector<int> mejorarSwap(vector<int> solucionParcial);
vector<int> mejorar2opt(vector<int> solucionParcial);
vector<int> mejorar3opt(vector<int> solucionParcial);

//Funciones Auxiliares
void optimizarSolucion(vector<int> &solucion);
long long calcularCosto(vector<int> &camino);

//variables globales
int cantGyms, cantPokeParadas, capMochila;
Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;

int main()
{
	
	cin >> cantGyms >> cantPokeParadas >> capMochila;
	Gimnasio* gimnasiosArr = new Gimnasio[cantGyms];

	for(int i = 0; i < cantGyms; i++)
	{
		Gimnasio gymPuebloPaleta;
		cin >> 
			gymPuebloPaleta.first.first >> 
			gymPuebloPaleta.first.second >>
			gymPuebloPaleta.second;
		gimnasiosArr[i] = gymPuebloPaleta;
	}

	Pokeparada *pokeParadasArr = new Pokeparada[cantPokeParadas];
	Pokeparada *pokeParadasAux = new Pokeparada[cantPokeParadas];
	for(int i = 0; i < cantPokeParadas; i++)
	{
		Pokeparada posicion;
		cin >> posicion.first >> posicion.second;
		pokeParadasArr[i] = posicion;
		pokeParadasAux[i] = posicion;
	}

	pair < int, list<int> * > * solucionInicial = algoritmoResolucion(
			cantGyms, 
			cantPokeParadas,
			capMochila, 
			gimnasiosArr, 
			pokeParadasArr, 
			pokeParadasAux);

	list<int> *solucionInicialLista = solucionInicial->second;
    
    if (solucionInicial->first == -1) {
        solucionInicialLista = new list<int>();
    }
    
	vector<int> solucionParcial;

	list<int>::iterator itLista;
	for(itLista = solucionInicialLista->begin();
			itLista != solucionInicialLista->end();
			itLista++ )
	{
		solucionParcial.push_back(*itLista);
	}

	gimnasiosArrPtr = gimnasiosArr;
	pokeParadasArrPtr = pokeParadasAux;
	if( solucionParcial.size())
	{
		vector <int> solucion2opt = mejorar2opt(solucionParcial);
		printf("%lld %zu", calcularCosto(solucion2opt), solucion2opt.size());
		for(int i = 0; i < (int) solucion2opt.size(); i++)
		{
			printf(" %d", solucion2opt[i]);
		}
		printf("\n");
	} 
	else{
		printf("%d\n", -1);
	}
    
    delete solucionInicial;
	delete[] pokeParadasArr;
	delete[] pokeParadasAux;
	delete[] gimnasiosArr;
	return 0;
}

vector<int> mejorarSwap(vector<int> solucionParcial){
    vector<int> solucion = solucionParcial;
    long long costoAnterior = calcularCosto(solucionParcial);
    int cantNodos = solucionParcial.size();
    
    vector<int> solucionAnterior;
    
    bool hayMejora = true;
    
    while (hayMejora) {
        
        long long costoActual = -1;
        
        for (int i = 0; i < cantNodos-1; i++) {
            for (int j = i+1; j < cantNodos; j++) {
                swap(solucionParcial[i], solucionParcial[j]);
                
                vector<int> solucionOptimizada = solucionParcial;
                optimizarSolucion(solucionOptimizada);
                costoActual = calcularCosto(solucionOptimizada);
                
                if (costoActual != -1 && costoActual < costoAnterior) {
                    costoAnterior = costoActual;
                    solucion = solucionOptimizada;
                }
                
                swap(solucionParcial[i], solucionParcial[j]);//volver al original
            }
        }
        
        if (costoActual == -1 || costoActual >= costoAnterior) {
            hayMejora = false;
        }
        
        solucionAnterior = solucionParcial;
        solucionParcial = solucion;
        
    }
    
    return solucion;
}

vector<int> mejorar2opt(vector<int> solucionParcial){
    vector<int> solucion = solucionParcial;
    long long costoAnterior = calcularCosto(solucionParcial);
    int cantNodos = solucionParcial.size();
    
    vector<int> solucionAnterior;
    
    bool hayMejora = true;
    
    while (hayMejora) {
        
        long long costoActual = -1;
        
        for (int i = 0; i < cantNodos-1; i++) {
            for (int j = i+1; j < cantNodos; j++) {
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
                vector<int> solucionOptimizada = solucionParcial;
                optimizarSolucion(solucionOptimizada);
                costoActual = calcularCosto(solucionOptimizada);
                
                if (costoActual != -1 && costoActual < costoAnterior) {
                    costoAnterior = costoActual;
                    solucion = solucionOptimizada;
                }
                
                //volver al original
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
            }
        }
        
        if (costoActual == -1 || costoActual >= costoAnterior) {
            hayMejora = false;
        }
        
        solucionAnterior = solucionParcial;
        solucionParcial = solucion;
        
    }
    
    return solucion;
}

vector<int> mejorar3opt(vector<int> solucionParcial){
    vector<int> solucion = solucionParcial;
    long long costoAnterior = calcularCosto(solucionParcial);
    int cantNodos = solucionParcial.size();
    
    vector<int> solucionAnterior;
    
    bool hayMejora = true;
    
    while (hayMejora) {
        
        long long costoActual = -1;
        
        for (int i = 1; i < cantNodos-3; i++) {
            for (int j = i+1; j < cantNodos-2; j++) {
                for (int k = j+2; k < cantNodos; k++) {
                    
                    //Caso 1
                    
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
                    reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);
                    
                    vector<int> solucionOptimizada = solucionParcial;
                    optimizarSolucion(solucionOptimizada);
                    costoActual = calcularCosto(solucionOptimizada);
                    
                    if (costoActual != -1 && costoActual < costoAnterior)
                    {
                        costoAnterior = costoActual;
                        solucion = solucionOptimizada;
                    }
                    
                    /*
                     printf("Caso 1 - i: %d, j: %d k: %d\n", i, j ,k);
                     for(int i = 0; i < (int) solucionParcial.size(); i++){
                     printf("%d ", solucionParcial[i]);
                     }
                     printf("\n");
                     */
                    
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
                    reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);
                    
                    //Caso 2
                    
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j) );
                    reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
                    
                    solucionOptimizada = solucionParcial;
                    optimizarSolucion(solucionOptimizada);
                    costoActual = calcularCosto(solucionOptimizada);
                    
                    if (costoActual != -1 && costoActual < costoAnterior)
                    {
                        costoAnterior = costoActual;
                        solucion = solucionOptimizada;
                    }
                    
                    /*
                     printf("Caso 2 - i: %d, j: %d k: %d\n", i, j ,k);
                     for(int i = 0; i < (int) solucionParcial.size(); i++){
                     printf("%d ", solucionParcial[i]);
                     }
                     printf("\n");
                     */
                    
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
                    reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                    
                    //Caso 3
                    
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
                    
                    solucionOptimizada = solucionParcial;
                    optimizarSolucion(solucionOptimizada);
                    costoActual = calcularCosto(solucionOptimizada);
                    
                    if (costoActual != -1 && costoActual < costoAnterior)
                    {
                        costoAnterior = costoActual;
                        solucion = solucionOptimizada;
                    }
                    
                    /*
                     printf("Caso 3 - i: %d, j: %d k: %d\n", i, j ,k);
                     for(int i = 0; i < (int) solucionParcial.size(); i++){
                     printf("%d ", solucionParcial[i]);
                     }
                     printf("\n");
                     */
                    
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                    
                    //Caso 4
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                    reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
                    
                    solucionOptimizada = solucionParcial;
                    optimizarSolucion(solucionOptimizada);
                    costoActual = calcularCosto(solucionOptimizada);
                    
                    if (costoActual != -1 && costoActual < costoAnterior)
                    {
                        costoAnterior = costoActual;
                        solucion = solucionOptimizada;
                    }
                    
                    /*
                     printf("Caso 4 - i: %d, j: %d k: %d\n", i, j ,k);
                     for(int i = 0; i < (int) solucionParcial.size(); i++){
                     printf("%d ", solucionParcial[i]);
                     }
                     printf("\n");
                     */
                    
                    reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
                    reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                }
                
            }
        }
        
        if (costoActual == -1 || costoActual >= costoAnterior) {
            hayMejora = false;
        }
        
        solucionAnterior = solucionParcial;
        solucionParcial = solucion;
        
    }
    
    return solucion;
}


bool pasoPosible(int destino, int capacidadParcial){
    Gimnasio gym;
    
    int poderGym = 0;
    
    if (destino < cantGyms)
    {
        poderGym = gimnasiosArrPtr[destino].second;
    }
    
    if (poderGym == 0 || capacidadParcial >= poderGym)
    {
        return true;
    }
    
    return false;
}

long long distancia(pair<int, int> origen, pair<int, int> destino){
    return pow(origen.first - destino.first, 2) + pow(origen.second - destino.second, 2);//gusanito
}

long long calcularCosto(vector<int> &camino){
    if (!camino.size()) {
        return -1;
    }
    
    long long costo = 0;
    int capacidadParcial = 0;
    
    if(camino[0] > cantGyms) {
        capacidadParcial = 3;
    }
    
    for(int i = 0; i < (int) camino.size() -1; i++){
        if(pasoPosible(camino[i+1]-1, capacidadParcial)){
            
            pair<int, int> pOrigen;
            pair<int, int> pDestino;
            
            int origen = camino[i]-1;
            int destino = camino[i+1]-1;
            
            bool destinoEsPP = false;
            
            if (origen < cantGyms)
            {
                pOrigen = gimnasiosArrPtr[origen].first;
            }else {
                pOrigen = pokeParadasArrPtr[origen - cantGyms];
            }
            
            if (destino < cantGyms)
            {
                pDestino = gimnasiosArrPtr[destino].first;
            }else {
                pDestino = pokeParadasArrPtr[destino - cantGyms];
                destinoEsPP = true;
            }
            
            costo = costo + distancia(pOrigen, pDestino);
            
            if(destinoEsPP){
                capacidadParcial += 3;
                if(capacidadParcial > capMochila){
                    capacidadParcial = capMochila;
                }
            } else {
                capacidadParcial = capacidadParcial - gimnasiosArrPtr[destino].second;
            }
        } else{
            /*
             cout << "ERROR\n"
             << "capacidad " << capMochila << "\n"
             << "capacidad Parcial " << capacidadParcial << "\n"
             << "origen " << camino[i] << "\n"
             << "destino " << camino[i+1] << "\n";
             if(camino[i+1] <= cantGyms)
             {
             cout << "poder Gym: " << gimnasiosArrPtr[camino[i+1] - 1].second << "\n";
             }
             */
            return -1;
        }
    }
    
    return costo;
}

void optimizarSolucion(vector<int> &solucion)
{
    int i = solucion.size() -1;
    while(solucion[i] > cantGyms && i > 0)
    {
        solucion.pop_back();
        i--;
    }
}

pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int>  posiciones_pp[], pair<int,int>  pp_aux[])
{
	int cantidadTotalDePocionesConSuerte = 3 * cant_pokeParadas;
	int pocionesANecesitar = 0;
	for (int i = 0; i < cant_gimnasios; ++i){
		pocionesANecesitar = pocionesANecesitar + posiciones_gym[i].second;
		if (posiciones_gym[i].second > cap_mochila || posiciones_gym[i].second > cantidadTotalDePocionesConSuerte){
			//Sin solucion!
			
			return NULL;
		}
	}
	if(pocionesANecesitar > cantidadTotalDePocionesConSuerte){
			//Sin solucion!

		return NULL;
	}
		
		
	bool posible = true;
	
	int minimo = -1; 
	std::list<int> * camino;


	for (int x = 0; x < cant_pokeParadas + cant_gimnasios; ++x)
	{

		posible = true;
		MaestroPokemon ash = MaestroPokemon(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp, x); //Aca se registran en el Pokedex
		while(posible){
			//ash.printStatus();
			if (ash.gane())
			{
				if (ash.distancia < minimo || minimo == -1)
				{
					//cout<<"minimo alcanzado\n";
					minimo = ash.distancia;
					camino = ash.caminoRecorrido(pp_aux);

				}
				
			}

			posible = ash.eleccionGolosa();
			posible = posible && (minimo == -1 || ash.distancia<minimo);
			
		}
	}

	pair <int,std::list<int>*> * final = new pair <int,std::list<int> * >;
	final->first = minimo;
	final->second = camino;
	return final;
}

