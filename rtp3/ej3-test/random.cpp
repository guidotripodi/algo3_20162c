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

#define INSTANCIAS 2168 
//que es lo que quiero
//correr para cada instancia una sola vez
//tomar promedios de mierdas del mismo size
//no entra bien en una tabla csv eso
//a menos que quieras promedios de tiempos tambien
//por ahora programemos como va a quedar el loop

//MAXSIZE es reemplazado por INSTANCIAS creo
//TESST ITER CHAU
//CANT MAX PP Y GYMS cuanto son ahora? esta bien poner estos 
//arreglos de 1000~ elementos en el stack o uso dinamica

int main()
{
	
	int* tams = new int[INSTANCIAS];
	long long* mejorasParciales = new long long[INSTANCIAS];
	long long* mejorasSwap = new long long[INSTANCIAS];
	long long* mejoras2opt = new long long[INSTANCIAS];

	long long* tiemposSwap = new long long[INSTANCIAS];
	long long* tiempos2opt = new long long[INSTANCIAS];
	
	
	for(int j = 0; j < INSTANCIAS; j++)
	{
        vector<int> solucionSwap;
        vector<int> solucion2opt;
        vector<int> solucion3opt;
        vector<int> solucionParcial;
        
        cin >> cantGyms >> cantPokeParadas >> capMochila;
        
		pair <pair<int,int>, int> *gimnasiosArr = new pair <pair<int,int>, int>[cantGyms];
		pair <int, int>  *pokeParadasArr = new pair <int, int>[cantPokeParadas];
		pair <int, int>  *pokeParadasAux = new pair <int, int>[cantPokeParadas];
        gimnasiosArrPtr = gimnasiosArr;
        pokeParadasArrPtr = pokeParadasArr;
		
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

		pair < int, list<int> * > * solucionInicial = algoritmoResolucion(
				cantGyms, 
				cantPokeParadas,
				capMochila, 
				gimnasiosArr, 
				pokeParadasArr, 
				pokeParadasAux);
        
        list<int> *solucionInicialLista;
		//la idea de este fix es:
		//en casos invalidos hacer que solucionParcial
		//sea un vector vacio
		//en mejorasParciales[instancia] se guarda un 0 o -1
		//(depende lo que da calcularCosto en vector vacio)
		//chequeo eso para no promediar esos casos
        if(solucionInicial == NULL)
		{
            solucionInicialLista = new list<int>();
		}
		else if(solucionInicial->first == -1) 
		{
            solucionInicialLista = new list<int>();
        }
		else
		{
			solucionInicialLista = solucionInicial->second;
		}
        
        list<int>::iterator itLista;
        
        for(itLista = solucionInicialLista->begin();
            itLista != solucionInicialLista->end();
            itLista++ )
        {
            solucionParcial.push_back(*itLista);
        }
        
        
		//mejorar solucion
		if( solucionParcial.size())
		{
			auto start = ya();
			solucionSwap = mejorarSwap(solucionParcial);
			auto end = ya();
			tiemposSwap[j] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
			start = ya();
			solucion2opt = mejorar2opt(solucionParcial);
			end = ya();
			tiempos2opt[j] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
		}
		else
		{
			solucionSwap = solucionParcial;
			tiemposSwap[j] = 0;
			solucion2opt = solucionParcial;
			tiempos2opt[j] = 0;
		}
		
		//guardar datos
		tams[j] = cantGyms + cantPokeParadas; 
		mejorasParciales[j] = calcularCosto(solucionParcial);
		mejorasSwap[j] = calcularCosto(solucionSwap);
		mejoras2opt[j] = calcularCosto(solucion2opt);
        
		delete solucionInicial;
		delete[] gimnasiosArr;
		delete[] pokeParadasArr;
		delete[] pokeParadasAux;
    }
    
	//imprimir csv
	//tiempo queda pero no es promedio
	//varianzas se van
	cout
		<< "tamaño de instancia,"
		<< "distancia goloso,"
		<< "tiempo swap,"
		<< "distancia swap,"
		<< "solucion swap,"
		<< "tiempo 2opt,"
		<< "distancia 2opt,"
		<< "solucion 2opt,"
		<< "tiempo 3opt,"
		<< "distancia 3opt,"
		<< "solucion 3opt,"
		<< "\n";
    
    
    
	for( int k = 0; k < INSTANCIAS; k++ )
	{
		cout 
			<< tams[k] << "," 
			<< mejorasParciales[k] << ","
			<< tiemposSwap[k] << ","
			<< mejorasSwap[k] << ",";
        
        
		cout 
			<< tiempos2opt[k] << ","
			<< mejoras2opt[k] << ",";
	}
   
	// TODO
	// imprimir:
	// para cada instancia???
	// tiempo y mejora
	// tiro las soluciones?
	
	//para cada tamaño de instancia
	//promedio porcentajes de mejora 
	//(para cada local con respecto al goloso)
	//promedio de tiempos
	//promedio de mejoras
	int inst;
	int h = 0;
	while(h < INSTANCIAS)
	{
		int tam = tams[h];
		if(tam <= 20)
		{
			inst = tam;
		}
		else
		{
			inst = (int)(tam * 0.10);//techo o parte entera?
		}
		int acumTiemposSwap = 0;
		int acumTiempos2opt = 0;
		int acumMejoraSwap = 0;
		int acumMejora2opt = 0;
		float acumPercSwap = 0;
		float acumPerc2opt = 0;
		int t = 0;
		while(t < inst)
		{
			if(tams[h] != tam) cerr 
				<< "ERROR, tams[h]: " << tams[h] 
				<< " tam: " << tam << "\n";

			if(	mejorasParciales[h]== 0 ||
					mejorasParciales[h] == -1)
			{//INSTANCIA INVALIDA
				inst--;
				h++;
			}
			else
			{
				acumTiemposSwap += tiemposSwap[h];
				acumMejoraSwap += mejorasSwap[h];

				acumPercSwap += (mejorasSwap[h] * 100 )/ mejorasParciales[h];
				acumTiempos2opt += tiempos2opt[h];
				acumMejora2opt += mejoras2opt[h];
				acumPerc2opt += (mejoras2opt[h] * 100 )/ mejorasParciales[h];
				t++;
				h++;
			}
		}

		//promedios	
		cout 
			<< tam << ","
			<< (acumTiemposSwap / inst) << ","
			<< (acumMejoraSwap / inst) << ","
			<< (acumPercSwap / inst) << ","
			<< (acumTiempos2opt / inst) << ","
			<< (acumMejora2opt / inst) << ","
			<< (acumPerc2opt / inst) << "\n";
	}


	delete[] tams;
	delete[] mejorasParciales; 
	delete[] mejorasSwap; 
	delete[] mejoras2opt; 

	delete[] tiemposSwap; 
	delete[] tiempos2opt; 
	return 0;
}
/*
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
*/
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
    
    long long costoActual;
    
    vector<int> solucionAnterior;
    
    bool mejora1 = true;
    bool mejora2 = true;
    bool mejora3 = true;
    bool mejora4 = true;
    
    while (mejora1 || mejora2 || mejora3 || mejora4) {
        
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

