#include "ej4.hpp"

using namespace std;

//variables globales
int cantGyms, cantPokeParadas, capMochila;
Gimnasio *gimnasiosArrPtr;
Pokeparada *pokeParadasArrPtr;

long long _maxIt;
long long _tenor;
bool _aristasNuevas;
bool _masTabu;

//http://crema.di.unimi.it/~righini/Didattica/Algoritmi%20Euristici/MaterialeAE/Taratura%20parametri%20TS.pdf
//http://www.uv.es/rmarti/paper/docs/ts1.pdf
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

void correr(vector<int> solucionParcial, long long itAct, long long tenorAct, long long attrAct, long long aspAct) {
    
    vector<long long> tiempos(TEST_ITER);
    
    vector<int> solucionMejorada;
    
    for(int it = 0; it < TEST_ITER; it++) {
        auto start = ya();
        solucionMejorada = tabuSearch(solucionParcial, itAct, tenorAct, attrAct, aspAct);
        auto end = ya();
        tiempos[it] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    }
    
    pair <float, float> est = estadisticas(tiempos);
    
    printResults(est, solucionMejorada);
}

void testear(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[], pair<int,int>  pp_aux[], int test) {
    
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
    
    long long _maxIt = 30;
    long long _tenor = 30;
    bool _aristasNuevas = false;
    bool _masTabu = false;
    
    if(solucionParcial.size()) {
        
        long long mejoraParcial = calcularCosto(solucionParcial);
        
        cout << mejoraParcial << ",";
        
        for(int i = 0; i < (int) solucionParcial.size(); i++)
            cout << solucionParcial[i] << " ";
        cout << "\n";
        
        if (test == 1) {
            for (int itAct = 0; itAct < _maxIt; itAct++) {
                correr(solucionParcial, itAct, _tenor, _aristasNuevas, _masTabu);
            }
        }
        
        if (test == 2) {
            for (int tenorAct = 1; tenorAct < _maxIt; tenorAct++) {
                correr(solucionParcial, _maxIt, tenorAct, _aristasNuevas, _masTabu);
            }
        }
        
        if (test == 3) {
            correr(solucionParcial, _maxIt, _tenor, _aristasNuevas, _masTabu);
        }
        
        if (test == 4) {
            correr(solucionParcial, _maxIt, _tenor, !_aristasNuevas, _masTabu);
        }
        
        if (test == 5) {
            correr(solucionParcial, _maxIt, _tenor, _aristasNuevas, _masTabu);
        }
        
        if (test == 6) {
            correr(solucionParcial, _maxIt, _tenor, _aristasNuevas, !_masTabu);
        }
    }else {
        printf("%d", -1);
    }
    
    delete solucionInicial;
}

vector<int> tabuSearch(vector<int> solucionParcial, long long maxIt, long long tenor, bool aristasNuevas, bool masTabu)
{
    _maxIt = maxIt;
    _tenor = tenor;
    _aristasNuevas = aristasNuevas;
    _masTabu = masTabu;
    
    vector<int> solucionActual = solucionParcial;
    vector<int> mejorSolucion= solucionParcial;
    long long costoMejor = calcularCosto(mejorSolucion);
    long long costoMejorVecino;
    SetTabu atributosTabu;
    int iteraciones = 0;
    while(iteraciones < _maxIt)
    {
        vector<int> mejorCandidato;
        list<Arista> aristasModificadas;
        //cada solucion esta asociada a las aristas que cambiaron
        // hacemos union entre swap, 2opt y 3opt
        list< pair< vector<int>, list<Arista> > > vecindad = vecindad2opt(solucionActual);
        list< pair< vector<int>, list<Arista> > > vecindad3 = vecindad3opt(solucionActual);
        list< pair< vector<int>, list<Arista> > > vecindadS = vecindadSwap(solucionActual);
        
        vecindad.splice(vecindad.end(), vecindad3);
        vecindad.splice(vecindad.end(), vecindadS);
        if(vecindad.size() == 0) return mejorSolucion; //Esto es por las moscas. No deberia pasar
        
        list< pair< vector<int>, list<Arista> > >::iterator iteradorVecindad;
        for(iteradorVecindad = vecindad.begin(); iteradorVecindad != vecindad.end(); ++iteradorVecindad)
        {
            vector<int> candidatoActual = iteradorVecindad->first;
            long long costoActual = calcularCosto(candidatoActual);
            costoMejorVecino = calcularCosto(mejorCandidato);
            
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
                mejorCandidato = candidatoActual;
            }
            
        }
        
        if(mejorCandidato.size() == 0)
        {
            //no encontre un vecino no tabu
            pair< vector<int>, list<Arista> > menosTabu = funcionAspiracion(atributosTabu, vecindad);
            mejorCandidato = menosTabu.first;
            //Hay que marcar las aristas que se usaron para esta solucion como tabu
            aristasModificadas = menosTabu.second;
        }
        
        solucionActual = mejorCandidato;
        if(costoMejorVecino < costoMejor)
        {
            mejorSolucion = mejorCandidato;
            costoMejor = costoMejorVecino;
        }
        
        list<Arista>::iterator it;
        for(it = aristasModificadas.begin(); it != aristasModificadas.end(); it++)
        {
            atributosTabu.push(*it);
        }
        
        //TODO es posta el mejor para borrar?
        //el orden en el que se guardan los objetos
        //no es cronologico como la lista.
        while(atributosTabu.size() > _tenor)
        {
            atributosTabu.pop();
        }
        
        iteraciones++;
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
        
        if (!_masTabu) {
            if( cantidadAtributos < cantidad )
            {
                solucionMenosTabu = *iteradorVecindad;
                cantidad = cantidadAtributos;
            }
        }else {
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
            if (!_aristasNuevas) {
                aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                aristasModificadas.push_back( Arista( solucionParcial[i], solucionParcial[i+1]) );
                aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
                aristasModificadas.push_back( Arista( solucionParcial[(j-1)%cantNodos], solucionParcial[j]) );
            }
            
            swap(solucionParcial[i], solucionParcial[j]);
            
            if (_aristasNuevas) {
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
            
            if (!_aristasNuevas) {
                aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[(j+1)%cantNodos]) );
            }
            
            reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
            
            if (_aristasNuevas) {
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
                
                if (!_aristasNuevas) {
                    aristasModificadas.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas.push_back( Arista( solucionParcial[j], solucionParcial[j+1]) );
                    aristasModificadas.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + j);
                reverse(solucionParcial.begin() + j, solucionParcial.begin() + k);
                
                if (_aristasNuevas) {
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
                
                if (!_aristasNuevas) {
                    aristasModificadas2.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas2.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas2.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j) );//len(rango 2)
                reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
                
                if (_aristasNuevas) {
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
                
                if (!_aristasNuevas) {
                    aristasModificadas3.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas3.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas3.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + i + (k - j));//len(rango 2)
                
                if (_aristasNuevas) {
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
                
                if (!_aristasNuevas) {
                    aristasModificadas4.push_back( Arista( solucionParcial[i-1], solucionParcial[i]) );
                    aristasModificadas4.push_back( Arista( solucionParcial[i + (k - j)], solucionParcial[i+ (k - j)+1]) );
                    aristasModificadas4.push_back( Arista( solucionParcial[k], solucionParcial[(k+1)%cantNodos]) );
                }
                
                reverse(solucionParcial.begin() + i, solucionParcial.begin() + k);
                reverse(solucionParcial.begin() + i + (k - j - 1), solucionParcial.begin() + (j - i - 1));
                
                if (_aristasNuevas) {
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
        poderGym = gimnasiosArrPtr[destino-1].second;
    }
    
    if (poderGym == 0 || capacidadParcial >= poderGym)
    {
        return true;
    }
    
    return false;
}


long long calcularCosto(vector<int> &camino){
    long long costo = 0;
    int capacidadParcial = 0;
    
    
    
    for(int i = 0; i < (int) camino.size() -1; i++){
        if(pasoPosible(camino[i+1], capacidadParcial)){
            
            pair<int, int> pOrigen;
            pair<int, int> pDestino;
            
            int origen = camino[i];
            int destino = camino[i+1];
            
            bool destinoEsPP = false;
            
            if (origen <= cantGyms)
            {
                pOrigen = gimnasiosArrPtr[origen - 1].first;
            }else {
                pOrigen = pokeParadasArrPtr[origen - cantGyms - 1];
            }
            
            if (destino <= cantGyms)
            {
                pDestino = gimnasiosArrPtr[destino - 1].first;
            }else {
                pDestino = pokeParadasArrPtr[destino - cantGyms - 1];
                destinoEsPP = true;
            }			
            
            costo = costo + distancia(pOrigen, pDestino);
            
            
            if(destinoEsPP){
                capacidadParcial += 3;
                if(capacidadParcial > capMochila){
                    capacidadParcial = capMochila;
                }
            } else {
                capacidadParcial = capacidadParcial - gimnasiosArrPtr[destino - 1].second;
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

