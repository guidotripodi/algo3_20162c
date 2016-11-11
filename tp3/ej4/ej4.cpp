#include <iostream>	/* printf, cout*/
#include <vector> 
#include <algorithm> 
#include <fstream>
#include <utility>
#include <chrono>  /* clock */
#include <math.h>	/* pow */
#include <cstdlib> /* swap */
#include <list>
#include "SetTabu.hpp"
#include "MaestroPokemon.hpp"

#define ya chrono::high_resolution_clock::now

#define SEED 39
#define MAX_PODER 25
#define RADIO 100

#define TENOR 5
#define ITERMAX 4

using namespace std;

//Tipos
typedef pair <pair<int,int>, int> Gimnasio;
typedef pair<int,int> Pokeparada;
typedef pair<int,int> Arista;

//Funciones importantes
pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[]);
vector<int> tabuSearch(vector<int> solucionParcial);
list< pair< vector<int>, list<Arista> > > vecindadSwap(vector<int> solucionParcial);
list< pair< vector<int>, list<Arista> > > vecindad2opt(vector<int> solucionParcial);
list< pair< vector<int>, list<Arista> > > vecindad3opt(vector<int> solucionParcial);

//auxiliares
pair< vector<int>, list<Arista> > funcionAspiracion( SetTabu atributosTabu, list< pair< vector<int>, list<Arista> > > vecindad);
int tabuCount(SetTabu atributos, vector<int> solucion);
long long calcularCosto(vector<int> &camino);
void optimizarSolucion(vector<int> &solucion);

//variables globales
int cantGyms, cantPokeParadas, capMochila;
Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;

int main(){
	
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

	
	//mejorar solucion
	if(solucionParcial.size()){
		vector <int> mejorada = tabuSearch(solucionParcial);
		//imprimir solucion mejorada
		long long costo = calcularCosto(mejorada);
		printf("%lld %zu ", costo, mejorada.size());
		for(int i = 0; i < (int) mejorada.size(); i++){
			printf(" %d", mejorada[i]);
		}
		printf("\n");
	}else{
		printf("%d\n", -1);
		//no hubo solucion parcial a partir de la cual trabajar
	}

	return 0;
}

vector<int> tabuSearch(vector<int> solucionParcial)
{
	vector<int> solucionActual = solucionParcial;
	vector<int> mejorSolucion= solucionParcial;
	long long costoMejor = calcularCosto(mejorSolucion);
	long long costoMejorVecino;
	SetTabu atributosTabu;
    
    int cantidadNoMejoras = 0;
    
    while(cantidadNoMejoras < ITERMAX)
	{
		vector<int> mejorVecino;
		list<Arista> aristasModificadas; 
		//cada solucion esta asociada a las aristas que cambiaron
		// hacemos union entre swap, 2opt y 3opt
		list< pair< vector<int>, list<Arista> > > vecindad = vecindad2opt(solucionActual);

		if(vecindad.size() == 0) return mejorSolucion; //Esto es por las moscas. No deberia pasar	
		
		list< pair< vector<int>, list<Arista> > >::iterator iteradorVecindad; 
		for(iteradorVecindad = vecindad.begin(); iteradorVecindad != vecindad.end(); ++iteradorVecindad)
		{
			vector<int> candidatoActual = iteradorVecindad->first;
			long long costoActual = calcularCosto(candidatoActual);
			costoMejorVecino = calcularCosto(mejorVecino);

			// utilizamos long term memory 
			// porque no nos concentramos solamente en un subconjunto de una vecindad, 
			// si no en sucesivas vecindades.
			// Cuando todas las soluciones disponibles en la vecindad analizada son tabu active:
			// hay que elegir la menos tabu de todas o la que aun siendo tabu mejore la funcion objetivo
			
			if(	costoActual < costoMejor ||
				(!tabuCount(atributosTabu, candidatoActual) && 
				(costoActual < costoMejorVecino || costoMejorVecino == -1)))
			{
				aristasModificadas = iteradorVecindad->second;
				mejorVecino = candidatoActual;
			}

		}
		
		if(mejorVecino.size() == 0)
		{
			//no encontre un vecino no tabu
			pair< vector<int>, list<Arista> > menosTabu = funcionAspiracion(atributosTabu, vecindad);
			mejorVecino = menosTabu.first;
			//Hay que marcar las aristas que se usaron para esta solucion como tabu
			aristasModificadas = menosTabu.second;
		}
        
        costoMejorVecino = calcularCosto(mejorVecino);

		solucionActual = mejorVecino;
		if(costoMejorVecino < costoMejor)
		{
			mejorSolucion = mejorVecino;
			costoMejor = costoMejorVecino;
        }else {
            cantidadNoMejoras++;
        }
		
		list<Arista>::iterator it;
		for(it = aristasModificadas.begin(); it != aristasModificadas.end(); it++)
		{
			atributosTabu.push(*it);
		}
		
		//TODO es posta el mejor para borrar?
		//el orden en el que se guardan los objetos
		//no es cronologico como la lista.
		while(atributosTabu.size() > TENOR) 
		{
			atributosTabu.pop();
        }
	}

	return mejorSolucion;
}

pair< vector<int>, list<Arista> > funcionAspiracion( SetTabu atributosTabu, list< pair< vector<int>, list<Arista> > > vecindad)
{
	pair< vector<int>, list<Arista> > solucionMenosTabu = vecindad.front();
	int menorCantidad = tabuCount(atributosTabu, solucionMenosTabu.first);
	list< pair< vector<int>, list<Arista> > >::iterator iteradorVecindad;
	
	for(iteradorVecindad = next(vecindad.begin(), 1); iteradorVecindad != vecindad.end(); ++iteradorVecindad)
	{
		int cantidadAtributos = tabuCount(atributosTabu, iteradorVecindad->first); 
		if( cantidadAtributos < menorCantidad )
		{
			solucionMenosTabu = *iteradorVecindad;
			menorCantidad = cantidadAtributos;
		}
	}
	return solucionMenosTabu;
}

//en vez de decir si una funcion es tabu o no, cuenta cuantos
//atributos tabu tiene.
int tabuCount( SetTabu atributos, vector<int> solucion )
{
	int tabuAtributeCount = 0;
	vector<int>::iterator itSolucion;
	for(itSolucion = solucion.begin(); itSolucion != solucion.end()-1; itSolucion++){

		if(atributos.belongs( Arista(*itSolucion, *(itSolucion+1)) ))
		{
			tabuAtributeCount++;
		} 
		else
		{
			Arista inversa = Arista(*(itSolucion+1), *itSolucion);
			if(atributos.belongs(inversa)) tabuAtributeCount++;
		}

	}

	if(atributos.belongs( Arista( *itSolucion, *solucion.begin() ) ))
		//mas parentesis que lisp
		tabuAtributeCount++;
	return 0;
}
list< pair< vector<int>, list<Arista> > > vecindadSwap(vector<int> solucionParcial)
{
	list< pair< vector<int>, list<Arista> > > soluciones;
	int cantNodos = solucionParcial.size();
    long long costoActual; 
	for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            list<Arista> aristasModificadas;
			
			//en un swap cambian cuatro aristas
			//quiero guardar las aristas antes de que sean modificadas
			//TODO casos borde, o quizas no; el set tabu me los va a planchar si meto cosas repetidas aca.
			aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
			aristasModificadas.push_back( Arista( solucionParcial[i], solucionParcial[i+1]) );
			aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
			aristasModificadas.push_back( Arista( solucionParcial[(j-1)%cantNodos], solucionParcial[j]) );
			
			swap(solucionParcial[i], solucionParcial[j]);


			costoActual = calcularCosto(solucionParcial);
			if (costoActual != -1)
			{
				vector<int> solucionOptimizada = solucionParcial; //copia
				optimizarSolucion(solucionOptimizada);
				pair< vector<int>, list<Arista> > solucionConAtributos;
				solucionConAtributos.first = solucionOptimizada;
				solucionConAtributos.second = aristasModificadas;
				soluciones.push_back(solucionConAtributos);
			}
			swap(solucionParcial[i], solucionParcial[j]);//volver al original
		}
	}
	return soluciones;
}

//version 2opt
list< pair< vector<int>, list<Arista> > > vecindad2opt(vector<int> solucionParcial)
{
	list< pair< vector<int>, list<Arista> > > soluciones;
	int cantNodos = solucionParcial.size();
	long long costoActual; 
    for (int i = 0; i < cantNodos-1; i++) {
        for (int j = i+1; j < cantNodos; j++) {
            list<Arista> aristasModificadas;
			
			//quiero guardar las aristas antes de que sean modificadas
			//TODO casos borde, o quizas no; el set tabu me los va a planchar si meto cosas repetidas aca.
			aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
			aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
			
			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
			
			
			costoActual = calcularCosto(solucionParcial);
			if (costoActual != -1) 
			{
				vector<int> solucionOptimizada = solucionParcial; //copia
				optimizarSolucion(solucionOptimizada);
				pair< vector<int>, list<Arista> > solucionConAtributos;
				solucionConAtributos.first = solucionOptimizada;
				solucionConAtributos.second = aristasModificadas;
				soluciones.push_back(solucionConAtributos);
			}
			reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
		}
	}
	return soluciones;
}

//version 3opt
list< pair< vector<int>, list<Arista> > > vecindad3opt(vector<int> solucionParcial)
{
	list< pair< vector<int>, list<Arista> > > soluciones;
	int cantNodos = solucionParcial.size();
	long long costoActual; 
	
	for (int i = 1; i < cantNodos-3; i++) {
		for (int j = i+1; j < cantNodos-2; j++) {
			for (int k = j+2; k < cantNodos; k++) {
				
				list<Arista> aristasModificadas;
				//Caso 1
				aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
				aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[j+1]) );
				aristasModificadas.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1) 
				{
					vector<int> solucionOptimizada = solucionParcial; //copia
					optimizarSolucion(solucionOptimizada);
					pair< vector<int>, list<Arista> > solucionConAtributos;
					solucionConAtributos.first = solucionOptimizada;
					solucionConAtributos.second = aristasModificadas;
					soluciones.push_back(solucionConAtributos);
				}
			
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
				reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);

				//Caso 2

				list<Arista> aristasModificadas2;
				aristasModificadas2.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
				aristasModificadas2.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
				aristasModificadas2.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j) );//len(rango 2)
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));

				costoActual = calcularCosto(solucionParcial);


				if (costoActual != -1) 
				{
					vector<int> solucionOptimizada = solucionParcial; //copia
					optimizarSolucion(solucionOptimizada);
					pair< vector<int>, list<Arista> > solucionConAtributos;
					solucionConAtributos.first = solucionOptimizada;
					solucionConAtributos.second = aristasModificadas2;
					soluciones.push_back(solucionConAtributos);
				}

				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				
				//Caso 3
				
				list<Arista> aristasModificadas3;
				aristasModificadas3.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
				aristasModificadas3.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
				aristasModificadas3.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				
				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1) 
				{
					vector<int> solucionOptimizada = solucionParcial; //copia
					optimizarSolucion(solucionOptimizada);
					pair< vector<int>, list<Arista> > solucionConAtributos;
					solucionConAtributos.first = solucionOptimizada;
					solucionConAtributos.second = aristasModificadas3;
					soluciones.push_back(solucionConAtributos);
				}
				
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				
				//Caso 4
				list<Arista> aristasModificadas4;
				aristasModificadas4.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
				aristasModificadas4.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
				aristasModificadas4.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));

				costoActual = calcularCosto(solucionParcial);

				if (costoActual != -1) 
				{
					vector<int> solucionOptimizada = solucionParcial; //copia
					optimizarSolucion(solucionOptimizada);
					pair< vector<int>, list<Arista> > solucionConAtributos;
					solucionConAtributos.first = solucionOptimizada;
					solucionConAtributos.second = aristasModificadas4;
					soluciones.push_back(solucionConAtributos);
				}

				reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
				reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
			}
		}
	}

	return soluciones;
}

long long distancia(pair<int, int> origen, pair<int, int> destino){
	return 
		pow(origen.first - destino.first, 2) + 
		pow(origen.second - destino.second, 2);
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

