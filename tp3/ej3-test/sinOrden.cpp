#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <cstdlib>
#include "MaestroPokemon.hpp"

#define ya chrono::high_resolution_clock::now
#define TEST_ITER 20

using namespace std;

typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;

pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[]);
vector<int> mejorarSwap(vector<int> solucionParcial);
vector<int> mejorar2opt(vector<int> solucionParcial);
vector<int> mejorar3opt(vector<int> solucionParcial);

//Funciones Auxiliares
pair<float, float> mediaPodadaVarianzaMuestral(vector<long long> &muestra);
void optimizarSolucion(vector<int> &solucion);
long long calcularCosto(vector<int> &camino);

//variables globales
int cantGyms, cantPokeParadas, capMochila;
Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;

#define CANT_MAX_GYMS 101
#define CANT_MAX_PP 100
#define MAX_SIZE 20

int main()
{
	vector<int> solucionesSwap[MAX_SIZE];
	vector<int> soluciones2opt[MAX_SIZE];
	vector<int> soluciones3opt[MAX_SIZE];
	
	vector<long long> mejorasSwap;
	vector<long long> mejoras2opt;
	vector<long long> mejoras3opt;

	vector< pair <float, float> > estadisticasSwap;
	vector< pair <float, float> > estadisticas2opt;
	vector< pair <float, float> > estadisticas3opt;

	for(int j = 0; j < MAX_SIZE; j++)
	{
        vector<long long> tiemposSwap(TEST_ITER);
        vector<long long> tiempos2opt(TEST_ITER);
        vector<long long> tiempos3opt(TEST_ITER);
        vector<int> solucionSwap;
        vector<int> solucion2opt;
        vector<int> solucion3opt;
        vector<int> solucionParcial;
        
        cantGyms = j;
        cantPokeParadas = j*2;
        
        pair <pair<int,int>, int> gimnasiosArr[CANT_MAX_GYMS];
        pair <int, int>  pokeParadasArr[CANT_MAX_PP];
        pair <int, int>  pokeParadasAux[CANT_MAX_PP];
        
        gimnasiosArrPtr = gimnasiosArr;
        pokeParadasArrPtr = pokeParadasArr;
        
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
        
        capMochila = CANT_MAX_GYMS*3;

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
        
        list<int>::iterator itLista;

		for(itLista = solucionInicialLista->begin();
				itLista != solucionInicialLista->end();
				itLista++ )
		{
			solucionParcial.push_back(*itLista);
		}
        
		/*cout << calcularCosto(solucionParcial) << "\n";
		for(itLista = solucionInicialLista->begin();
				itLista != solucionInicialLista->end();
				itLista++ )
		{
			cout << *itLista << " ";
		}
		cout << "\n";*/
    
		for(int it = 0; it < TEST_ITER; it++)
		{
			//mejorar solucion
            if( solucionParcial.size())
			{
				auto start = ya();
				solucionSwap = mejorarSwap(solucionParcial);
				auto end = ya();
				tiemposSwap[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
				start = ya();
				solucion2opt = mejorar2opt(solucionParcial);
				end = ya();
				tiempos2opt[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
				start = ya();
				solucion3opt = mejorar3opt(solucionParcial);
				end = ya();
				tiempos3opt[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
			} 
			else{
                solucionSwap = solucionParcial;
                tiemposSwap[it] = 0;
                solucion2opt = solucionParcial;
                tiempos2opt[it] = 0;
                solucion3opt = solucionParcial;
                tiempos3opt[it] = 0;
			}

		}

        estadisticasSwap.push_back(mediaPodadaVarianzaMuestral(tiemposSwap));
		estadisticas2opt.push_back( mediaPodadaVarianzaMuestral(tiempos2opt) );
		estadisticas3opt.push_back( mediaPodadaVarianzaMuestral(tiempos3opt) );
		mejorasSwap.push_back( calcularCosto(solucionSwap) );
		mejoras2opt.push_back( calcularCosto(solucion2opt) );
		mejoras3opt.push_back( calcularCosto(solucion3opt) );
		solucionesSwap[j] = solucionSwap;
		soluciones2opt[j] = solucion2opt;
		soluciones3opt[j] = solucion3opt;
/*
		cout << estadisticasSwap.first << " " 
			<< estadisticasSwap.second << " "
			<< mejoraSwap << "\n";

		for(int i = 0; i < (int) solucionSwap.size(); i++) 
			cout << solucionSwap[i] << " ";
		cout << "\n";

		
		cout << estadisticas2opt.first << " "
			<< estadisticas2opt.second << " "
			<< mejora2opt << "\n";

		for(int i = 0; i < (int) solucion2opt.size(); i++) 
			cout << solucion2opt[i] << " ";
		cout << "\n";

		
		cout << estadisticas3opt.first << " "
			<< estadisticas3opt.second << " " 
			<< mejora3opt << "\n";
		for(int i = 0; i < (int) solucion3opt.size(); i++) 
			cout << solucion3opt[i] << " ";
		cout << "\n";
*/
		delete solucionInicial;
	}

	//imprimir csv
	cout 
		<< "tiempo swap,"
		<< "varianza swap,"
		<< "distancia swap,"
		<< "solucion swap,"
		<< "tiempo 2opt,"
		<< "varianza 2opt,"
		<< "distancia 2opt,"
		<< "solucion 2opt,"
		<< "tiempo 3opt,"
		<< "varianza 3opt,"
		<< "distancia 3opt,"
		<< "solucion 3opt,"
		<< "\n";
		


	for( int k = 0; k < MAX_SIZE; k++ )
	{
		cout << estadisticasSwap[k].first << "," 
			<< estadisticasSwap[k].second << ","
			<< mejorasSwap[k] << ",";

		for(int i = 0; i < (int) solucionesSwap[k].size(); i++) 
			cout << solucionesSwap[k][i] << " ";
		cout << ",";

		cout << estadisticas2opt[k].first << "," 
			<< estadisticas2opt[k].second << ","
			<< mejoras2opt[k] << ",";

		for(int i = 0; i < (int) soluciones2opt[k].size(); i++) 
			cout << soluciones2opt[k][i] << " ";
		cout << ",";

		cout << estadisticas3opt[k].first << "," 
			<< estadisticas3opt[k].second << ","
			<< mejoras3opt[k] << ",";

		for(int i = 0; i < (int) soluciones3opt[k].size(); i++) 
			cout << soluciones3opt[k][i] << " ";
		cout << "\n";
	}


	return 0;
}



pair<float, float> mediaPodadaVarianzaMuestral(vector<long long> &muestra) 
{
	//asume TEST_ITER divisible por 4
	float alpha = 0.5;
	int n = TEST_ITER;
	int x1, x2;

	x1 = n*alpha/2; //quiero sacar de ambos lados
	x2 = n*alpha/2; 


	sort(muestra.begin(), muestra.end());
	for(int i = 0; i < x1; i++)
		muestra.pop_back();

	long long sum = 0;
	for(int i = x2; i < (int)muestra.size(); i++) sum += muestra[i];
	float mean = (float) sum / (float) (muestra.size() - x2);
	
	float sampleVariance;
	float total = 0.0;
	for(int i = x2; i < (int)muestra.size(); i++)
	{
		sampleVariance = muestra[i] - mean;
		sampleVariance = sampleVariance * sampleVariance;
		total = total + sampleVariance;
	}
	total = total / (float)(muestra.size() - x2);
	total = sqrt(total);

	return make_pair(mean, total);
}

vector<int> mejorarSwap(vector<int> solucionParcial){
    vector<int> solucion = solucionParcial;
    long long costoAnterior = calcularCosto(solucionParcial);
    int cantNodos = solucionParcial.size();
    
    vector<int> solucionAnterior;
    
    bool hayMejora = true;
    
    while (hayMejora) {
        
        for (int i = 0; i < cantNodos-1; i++) {
            for (int j = i+1; j < cantNodos; j++) {
                swap(solucionParcial[i], solucionParcial[j]);
                
                vector<int> solucionOptimizada = solucionParcial;
                optimizarSolucion(solucionOptimizada);
                long long costoActual = calcularCosto(solucionOptimizada);
                
                if (costoActual != -1 && costoActual < costoAnterior) {
                    hayMejora = true;
                    costoAnterior = costoActual;
                    solucion = solucionOptimizada;
                }else {
                    hayMejora = false;
                }
                
                swap(solucionParcial[i], solucionParcial[j]);//volver al original
            }
        }
        
        if (solucion == solucionParcial) {
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
        
        for (int i = 0; i < cantNodos-1; i++) {
            for (int j = i+1; j < cantNodos; j++) {
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
                vector<int> solucionOptimizada = solucionParcial;
                optimizarSolucion(solucionOptimizada);
                long long costoActual = calcularCosto(solucionOptimizada);
                
                if (costoActual != -1 && costoActual < costoAnterior) {
                    hayMejora = true;
                    costoAnterior = costoActual;
                    solucion = solucionOptimizada;
                }else {
                    hayMejora = false;
                }
                
                //volver al original
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
            }
        }
        
        if (solucion == solucionParcial) {
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
    
    long long costoActual;
    
    vector<int> solucionAnterior;
    
    bool mejora1 = true;
    bool mejora2 = true;
    bool mejora3 = true;
    bool mejora4 = true;
    
    while (mejora1 || mejora2 || mejora3 || mejora4) {
        
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
                        mejora1 = true;
                        costoAnterior = costoActual;
                        solucion = solucionOptimizada;
                    }else {
                        mejora1 = false;
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
                        mejora2 = true;
                        costoAnterior = costoActual;
                        solucion = solucionOptimizada;
                    }else {
                        mejora2 = false;
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
                        mejora3 = true;
                        costoAnterior = costoActual;
                        solucion = solucionOptimizada;
                    }else {
                        mejora3 = false;
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
                        mejora4 = true;
                        costoAnterior = costoActual;
                        solucion = solucionOptimizada;
                    }else {
                        mejora4 = false;
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
        
        if (solucion == solucionParcial) {
            mejora1 = false;
            mejora2 = false;
            mejora3 = false;
            mejora4 = false;
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
			//printf("no se que es esto error \n");
			return NULL;
		}
	}
	if(pocionesANecesitar > cantidadTotalDePocionesConSuerte){
        //Sin solucion!
        //printf("pociones a necesitar > cantidad total de pociones con suerte \n");
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

