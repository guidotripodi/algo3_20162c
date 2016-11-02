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

int main()
{
	
	int j = 8;
	cantGyms = j+1;
	cantPokeParadas = j;
	pair <pair<int,int>, int> gimnasiosArr[cantGyms];
	pair <int, int>  pokeParadasArr[cantPokeParadas];
	pair <int, int>  pokeParadasAux[cantPokeParadas];
	
	vector<long long> tiemposSwap(TEST_ITER);
	vector<long long> tiempos2opt(TEST_ITER);
	vector<long long> tiempos3opt(TEST_ITER);
	
	vector<int> solucionSwap;
	vector<int> solucion2opt;
	vector<int> solucion3opt;

	vector<int> solucionParcial;
	
		
	int i = 0;
	for (i = 0; i < cantGyms; i++)
	{
		Gimnasio gymPuebloPaleta;
		gymPuebloPaleta.first.first = i;
		gymPuebloPaleta.first.second = i+1;
		if(i % 3 == 0)
		{
			gymPuebloPaleta.second = 0;
		} else
		{
			gymPuebloPaleta.second = 1;
		}
		gimnasiosArr[i] = gymPuebloPaleta;
		
	}
	for (i = 0; i < cantPokeParadas; i++)	{
		Pokeparada posicion;
		posicion.first = i;
		posicion.second = i+2;
		pokeParadasArr[i] = posicion;
		pokeParadasAux[i] = posicion;
	}
	
	capMochila = cantGyms*3;

	pair < int, list<int> * > * solucionInicial = algoritmoResolucion(
			cantGyms, 
			cantPokeParadas,
			capMochila, 
			gimnasiosArr, 
			pokeParadasArr, 
			pokeParadasAux);


	list<int> *solucionInicialLista = solucionInicial->second;

	list<int>::iterator itLista;
	for(itLista = solucionInicialLista->begin();
			itLista != solucionInicialLista->end();
			itLista++ )
	{
		solucionParcial.push_back(*itLista);
		cout << *itLista << " ";
	}
	cout << "\n";

	gimnasiosArrPtr = gimnasiosArr;
	pokeParadasArrPtr = pokeParadasAux;
		
	for(int it = 0; it < TEST_ITER; it++)
	{
		//mejorar solucion
		if( solucionParcial.size())
		{
			auto start = ya();
			solucionSwap = mejorar2opt(solucionParcial);
			auto end = ya();
			tiemposSwap[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
			start = ya();
			solucion2opt = mejorar2opt(solucionParcial);
			end = ya();
			tiempos2opt[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
			start = ya();
			solucion3opt = mejorar2opt(solucionParcial);
			end = ya();
			tiempos3opt[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
		} 
		else{
			//
			printf("%d", -1);
		}

		//delete solucionInicial;
	}

	pair <float, float> estadisticasSwap = mediaPodadaVarianzaMuestral(tiemposSwap);
	pair <float, float> estadisticas2opt = mediaPodadaVarianzaMuestral(tiempos2opt);
	pair <float, float> estadisticas3opt = mediaPodadaVarianzaMuestral(tiempos3opt);

	long long mejoraSwap = calcularCosto(solucionParcial) - calcularCosto(solucionSwap);
	long long mejora2opt = calcularCosto(solucionParcial) - calcularCosto(solucion2opt);
	long long mejora3opt = calcularCosto(solucionParcial) - calcularCosto(solucion3opt);

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


	return 0;
}


pair<float, float> mediaPodadaVarianzaMuestral(vector<long long> &muestra)
{
	float alpha = 0.5;
	int n = TEST_ITER;
	int x1, x2;

	x1 = n*alpha/2; //quiero sacar de ambos lados
	x2 = n*alpha/2; 


	sort(muestra.begin(), muestra.end());
	
	for(int i = 0; i < x1; i++)
		muestra.pop_back();

	//for(int i = 0; i < x2; i++)
	//	muestra.pop_front();

	long long sum = 0;
	for(int i = x2; i < (int)muestra.size(); i++) sum += muestra[i];
	float mean = (float) sum / (float) (muestra.size() - x2);
	
	float sampleVariance;
	float total = 0;
	for(int i = x2; i < (int)muestra.size(); i++)
	{
		sampleVariance = muestra[i] - mean;
		sampleVariance *= sampleVariance;
		total += sampleVariance;
	}
	total = total / (float)(muestra.size() - x2);
	total = sqrt(total);

	return make_pair(mean, total);
}

vector<int> mejorarSwap(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = solucionParcial.size();

    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            swap(solucionParcial[i], solucionParcial[j]);

			long long costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				vector<int> solucionOptimizada = solucionParcial; 
				optimizarSolucion(solucionOptimizada);
				costoAnterior = costoActual;
				solucion = solucionOptimizada;
				//printf("Costo mejorado: %lld\n", costoActual);
			}

			swap(solucionParcial[i], solucionParcial[j]);//volver al original
		}
	}
	return solucion;
}

vector<int> mejorar2opt(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = solucionParcial.size();

	long long costoActual;
    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {

			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
			costoActual = calcularCosto(solucionParcial);

			if (costoActual != -1 && costoActual < costoAnterior) {
				vector<int> solucionOptimizada = solucionParcial;
				optimizarSolucion(solucionOptimizada);
				costoAnterior = costoActual;
				solucion = solucionOptimizada;
				//printf("Costo mejorado: %lld\n", costoActual);
			}
			
			//volver al original
			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
		}
	}
	return solucion;
}
		
vector<int> mejorar3opt(vector<int> solucionParcial){
	vector<int> solucion = solucionParcial;
	long long costoAnterior = calcularCosto(solucionParcial);
	int cantNodos = solucionParcial.size();
	long long costoActual;
	
	
	for (int i = 1; i < cantNodos-3; i++) {
		for (int j = i+1; j < cantNodos-2; j++) {
			for (int k = j+2; k < cantNodos; k++) {
				

				//Caso 1
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1 && costoActual < costoAnterior)
				{
					vector<int> solucionOptimizada = solucionParcial;
					optimizarSolucion(solucionOptimizada);
					costoAnterior = costoActual;
					solucion = solucionOptimizada;
					//printf("Costo mejorado: %lld\n", costoActual);
				}
			
				printf("Caso 1 - i: %d, j: %d k: %d\n", i, j ,k);
				for(int i = 0; i < (int) solucionParcial.size(); i++){
					printf("%d ", solucionParcial[i]);
				}
				printf("\n");


				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				//Caso 2

				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j) );
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1 && costoActual < costoAnterior) 
				{
					vector<int> solucionOptimizada = solucionParcial;
					optimizarSolucion(solucionOptimizada);
					costoAnterior = costoActual;
					solucion = solucionOptimizada;
				}

				printf("Caso 2 - i: %d, j: %d k: %d\n", i, j ,k);
				for(int i = 0; i < (int) solucionParcial.size(); i++){
					printf("%d ", solucionParcial[i]);
				}
				printf("\n");

				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				
				//Caso 3
				
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				
				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1 && costoActual < costoAnterior) {
					vector<int> solucionOptimizada = solucionParcial;
					optimizarSolucion(solucionOptimizada);
					costoAnterior = costoActual;
					solucion = solucionOptimizada;
				}
				printf("Caso 3 - i: %d, j: %d k: %d\n", i, j ,k);
				for(int i = 0; i < (int) solucionParcial.size(); i++){
					printf("%d ", solucionParcial[i]);
				}
				printf("\n");
			
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				
				//Caso 4
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1 && costoActual < costoAnterior) {
					vector<int> solucionOptimizada = solucionParcial;
					optimizarSolucion(solucionOptimizada);
					costoAnterior = costoActual;
					solucion = solucionOptimizada;
				}

				printf("Caso 4 - i: %d, j: %d k: %d\n", i, j ,k);
				for(int i = 0; i < (int) solucionParcial.size(); i++){
					printf("%d ", solucionParcial[i]);
				}
				printf("\n");

				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
			}

		}
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
	
	if (poderGym == 0 || capacidadParcial > poderGym)
	{
		return true;
	}
	
	return false;
}

long long distancia(pair<int, int> origen, pair<int, int> destino){
	return pow(origen.first - destino.first, 2) + pow(origen.second - destino.second, 2);//gusanito
}

long long calcularCosto(vector<int> &camino){
	long long costo = 0;
	int capacidadParcial = 0;
	
	for(int i = 1; i < (int) camino.size(); i++){
		if(pasoPosible(camino[i], capacidadParcial)){
			
			pair<int, int> pOrigen;
			pair<int, int> pDestino;
			
			int origen = camino[i-1];
			int destino = camino[i];
			
			bool destinoEsPP = false;
			
			if (origen < cantGyms)
			{
				pOrigen = gimnasiosArrPtr[origen].first;
			}else {
				pOrigen = pokeParadasArrPtr[origen-cantGyms];
			}
			
			if (destino < cantGyms)
			{
				pDestino = gimnasiosArrPtr[destino].first;
			}else {
				pDestino = pokeParadasArrPtr[destino-cantGyms];
				destinoEsPP = true;
			}			
			
			costo = costo + distancia(pOrigen, pDestino);
			
		//	printf("Distancia de (%d,%d) a (%d,%d) = %lld \n", pOrigen.first, pOrigen.second, pDestino.first, pDestino.second, distancia(pOrigen, pDestino));
			
			if(destinoEsPP){
				capacidadParcial += 3;
				if(capacidadParcial > capMochila){
					capacidadParcial = capMochila;
				}
			} else {
				capacidadParcial = capacidadParcial - gimnasiosArrPtr[destino].second;
			}
		} else{
			return -1;
		}
	}
	
	return costo;
}

void optimizarSolucion(vector<int> &solucion)
{
	int i = solucion.size() -1;
	while(solucion[i] >= cantGyms && i > 0)
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


	for (int x = 0; x < cant_pokeParadas; ++x)
	{

		posible = true;
		MaestroPokemon ash = MaestroPokemon(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp); //Aca se registran en el Pokedex
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
		//cout << "termine rama\n";
		pair <int, int> posicion;
		for (int h = 0; h < cant_pokeParadas; ++h){
			/*Luego de la vuelta completa reordeno el array pp pasando al primer pp al ultimo y 
			muevo todo de esta forma me garantizo que todas las pp van a tener su rama como inicial*/
			if (h == 0)	{
				posicion.first = posiciones_pp[cant_pokeParadas-1].first; 
				posicion.second = posiciones_pp[cant_pokeParadas-1].second; 
			//	printf("Posicion : %d posicion: %d \n",posicion.first, posicion.second );
				posiciones_pp[cant_pokeParadas-1].first = posiciones_pp[0].first;
				posiciones_pp[cant_pokeParadas-1].second = posiciones_pp[0].second;
				posiciones_pp[0].first = posiciones_pp[1].first;
				posiciones_pp[0].second = posiciones_pp[1].second;
			}else{
				if (h+1 < cant_pokeParadas-1)	{
					posiciones_pp[h].first = posiciones_pp[h+1].first;
					posiciones_pp[h].second = posiciones_pp[h+1].second;
					
				}else{
					posiciones_pp[cant_pokeParadas-2].first = posicion.first;
					posiciones_pp[cant_pokeParadas-2].second = posicion.second;
				
				}
			}
		}

	}

	pair <int,std::list<int>*> * final = new pair <int,std::list<int> * >;
	final->first = minimo;
	final->second = camino;
	return final;
}
