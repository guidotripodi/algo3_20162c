#include "ej4.hpp"

using namespace std;

//variables globales
int cantGyms, cantPokeParadas, capMochila;
Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;

#define OLD_EDGES 1
#define LESS_TABU 1

int _tenor;
int _maxIter;
int _maxRep = 10;

pair<float, float> estadisticas(vector<long long> &muestra)
{
    //asume TEST_ITER divisible por 4
    float alpha = 0.5;
    int n = (int) muestra.size();
    int x1, x2;
    
    x1 = n*alpha/2; //quiero sacar de ambos lados
    x2 = n*alpha/2;
    
    
    sort(muestra.begin(), muestra.end());
    
    for(int i = 0; i < x1; i++)
        muestra.pop_back();
    
    //for(int i = 0; i < x2; i++)
    //	muestra.pop_front(); pop front no existe!
    
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

void printResults(pair < float, float > estadisticas, vector<int> solucionMejorada) {
    long long mejoraMejorada = calcularCosto(solucionMejorada);
    
    cout << estadisticas.first << ","
    << estadisticas.second << ","
    << mejoraMejorada << ",";
    
    for(int i = 0; i < (int) solucionMejorada.size(); i++)
        cout << solucionMejorada[i] << " ";
    cout << "\n";
}

pair<long long, long long> correr(vector<int> solucionParcial, vector<long long> &iteraciones) 
{
    
    long long tiempo = 0;
    vector<int> solucionMejorada;
    long long it = 0;
	while(it < _maxRep)
	{
		auto start = ya();
		solucionMejorada = tabuSearch(solucionParcial, it, iteraciones);
		auto end = ya();
		tiempo = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
		iteraciones.push_back(calcularCosto(solucionMejorada));
		it++;
	}  

//    pair <float, float> est = estadisticas(tiempos);
    
//    printResults(est, solucionMejorada);
	return make_pair(tiempo, calcularCosto(solucionMejorada));//solo lo de la ultima iteracion
}

pair< pair<long long, long long>, long long > testear(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[], vector<long long> &iteraciones) 
{
    
    gimnasiosArrPtr = posiciones_gym;
    pokeParadasArrPtr = posiciones_pp;
    
    vector<int> solucionParcial;
    
    //Llamada a la heuristica(ej2)
    pair < int, list<int> * > * solucionInicial = algoritmoResolucion(
                                                                      cant_gimnasios,
                                                                      cant_pokeParadas,
                                                                      cap_mochila,
                                                                      posiciones_gym,
                                                                      posiciones_pp,
                                                                      pp_aux);
    list<int> *solucionInicialLista;
    if(solucionInicial == NULL)
    {
        solucionInicialLista = new list<int>();
	}
	else 
	{
		solucionInicialLista = solucionInicial->second;
    
		if (solucionInicial->first == -1) {
			solucionInicialLista = new list<int>();
		}
	}
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
   
	//ALFA
	if(cantGyms+cantPokeParadas > 20)
	{
		_maxIter = (cantGyms+cantPokeParadas)*0.3;
	}
	else
	{
    	_maxIter = cantGyms+cantPokeParadas;
	}
    _tenor = _maxIter*0.5;
	//END ALFA
    pair< pair<long long, long long>, long long> res;
    if(solucionParcial.size()) {
        
        /*long long mejoraParcial = calcularCosto(solucionParcial);
        
        cout << mejoraParcial << ",";
        
        for(int i = 0; i < (int) solucionParcial.size(); i++)
            cout << solucionParcial[i] << " ";
        cout << "\n";*/
        
        res.first = correr(solucionParcial, iteraciones); 
		res.second = calcularCosto(solucionParcial);
    }
    else
    {
        res.first.first = 0; 
        res.first.second = 0; 
        res.second = 0; 
    }
    
    delete solucionInicial;
	return res;
}

vector<int> tabuSearch(vector<int> solucionParcial, long long it, vector<long long> &iteraciones)
{
    vector<int> solucionActual = solucionParcial;
    vector<int> mejorSolucion= solucionParcial;
    long long costoMejor = calcularCosto(mejorSolucion);
    long long costoMejorVecino;
    SetTabu atributosTabu;

    int iter = 0;
    int cantidadNoMejoras = 0;//BRAVO
    
    //while(iter < _maxIter && cantidadNoMejoras < ITERMAXREP)//CHARLIE ?
    while(cantidadNoMejoras < it)//BRAVO
    //while(iter < _maxIter)//ALFA
    {
        vector<int> mejorVecino;
        list<Arista> aristasModificadas;
        
        list< pair< vector<int>, list<Arista> > > vecindad = vecindad2opt(solucionActual);
        //list< pair< vector<int>, list<Arista> > > vecindad = vecindadSwap(solucionActual);
        
        //list< pair< vector<int>, list<Arista> > > vecindad = vecindad3opt(solucionActual);
        if(vecindad.size() == 0) return mejorSolucion;
        
        list< pair< vector<int>, list<Arista> > >::iterator iteradorVecindad;
        for(iteradorVecindad = vecindad.begin(); iteradorVecindad != vecindad.end(); ++iteradorVecindad)
        {
            vector<int> candidatoActual = iteradorVecindad->first;
            long long costoActual = calcularCosto(candidatoActual);
            costoMejorVecino = calcularCosto(mejorVecino);
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
            
			cantidadNoMejoras=0;//BRAVO
        }else {
            cantidadNoMejoras++;//BRAVO
        }
    
        /*
		if (it == 1) {
            cout << costoMejor << ",";
            
            for(int i = 0; i < (int) mejorSolucion.size(); i++)
                cout << mejorSolucion[i] << " ";
            cout << "\n";
        }
        */

        list<Arista>::iterator itList;
        for(itList = aristasModificadas.begin(); itList != aristasModificadas.end(); itList++)
        {
            atributosTabu.push(*itList);
        }
        
        while(atributosTabu.size() > _tenor)
        {
            atributosTabu.pop();
        }
       
		
		//iteraciones.push_back(costoMejor);//ALFA
		

        //iter++;
    }
    
    return mejorSolucion;
}

pair< vector<int>, list<Arista> > funcionAspiracion( SetTabu atributosTabu, list< pair< vector<int>, list<Arista> > > vecindad)
{
    pair< vector<int>, list<Arista> > solucionMenosTabu = vecindad.front();
    int cantidad = tabuCount(atributosTabu, solucionMenosTabu.first);
    list< pair< vector<int>, list<Arista> > >::iterator iteradorVecindad;
    
    for(iteradorVecindad = next(vecindad.begin(), 1); iteradorVecindad != vecindad.end(); ++iteradorVecindad)
    {
        int cantidadAtributos = tabuCount(atributosTabu, iteradorVecindad->first);
        
        if (LESS_TABU) 
		{
            if( cantidadAtributos < cantidad )
            {
                solucionMenosTabu = *iteradorVecindad;
                cantidad = cantidadAtributos;
            }
        }
		else 
		{
            if( cantidadAtributos > cantidad )
            {
                solucionMenosTabu = *iteradorVecindad;
                cantidad = cantidadAtributos;
            }
        }
    }
    return solucionMenosTabu;
}

//en vez de decir si una funcion es tabu o no, cuenta cuantos
//atributos tabu tiene.
int tabuCount(SetTabu atributos, vector<int> solucion)
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
            if (OLD_EDGES) {
                aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                aristasModificadas.push_back( Arista( solucionParcial[i], solucionParcial[i+1]) );
                aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
                aristasModificadas.push_back( Arista( solucionParcial[(j-1)%cantNodos], solucionParcial[j]) );
            }
            
            swap(solucionParcial[i], solucionParcial[j]);
            
            if (!OLD_EDGES) {
                aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                aristasModificadas.push_back( Arista( solucionParcial[i], solucionParcial[i+1]) );
                aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
                aristasModificadas.push_back( Arista( solucionParcial[(j-1)%cantNodos], solucionParcial[j]) );
            }
            
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
            
            if (OLD_EDGES) {
                aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
            }
            
            reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
            
            if (!OLD_EDGES) {
                aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
            }
            
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
                
                if (OLD_EDGES) {
                    aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[j+1]) );
                    aristasModificadas.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
                reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);
                
                if (!OLD_EDGES) {
                    aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[j+1]) );
                    aristasModificadas.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
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
                
                if (OLD_EDGES) {
                    aristasModificadas2.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas2.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas2.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j) );//len(rango 2)
                reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
                
                if (!OLD_EDGES) {
                    aristasModificadas2.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas2.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas2.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
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
                
                if (OLD_EDGES) {
                    aristasModificadas3.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas3.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas3.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
                
                if (!OLD_EDGES) {
                    aristasModificadas3.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas3.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas3.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
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
                
                if (OLD_EDGES) {
                    aristasModificadas4.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas4.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas4.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
                
                if (!OLD_EDGES) {
                    aristasModificadas4.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas4.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas4.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
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

